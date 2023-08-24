#include <atomic>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <future>

using VoidTask = std::function<void()>;

class Graph;

// 并发安全的dag node
class Node {
public:
  Node() {}
  ~Node() {}

public:
  // 入度是依赖节点
  std::unordered_set<Node *> in_nodes;
  // 出度是被依赖的节点
  std::unordered_set<Node *> out_nodes;
  std::atomic<int> state; // 0未执行，1执行中、2已完成，不可重复执行
  // 原子变量记录入度依赖ready情况
  std::atomic<int32_t> in_ready{0};
  VoidTask task;
  Graph *graph;
};

class Graph {
public:
  Graph(){};
  ~Graph(){};
  std::vector<Node *> node_list;
  // 增加依赖
  Node *add_node(VoidTask task, std::vector<Node *> &depends) {
    return nullptr;
  };
};

class Context {
public:
  Graph graph;
  std::atomic<int> wait_num = 0;
  std::mutex mutex;
  std::condition_variable cond;
};

class Executor {
public:
  void run(const Graph &graph) {
    // 构造执行上下文
    Context ctx;

    // 遍历node map, 将入度为0的节点交给executor执行
    for (auto *node : graph.node_list) {
      if (node->in_nodes.empty()) {
        submit(std::bind(&Executor::invoke, this, &ctx, node));
      }
    }

    // 等待所有节点执行完毕，增加超时控制可选项
    std::unique_lock<std::mutex> lock(ctx.mutex);
    ctx.cond.wait(lock, [&ctx] { return ctx.wait_num == 0; });
  };

protected:
  void submit(VoidTask task);

private:
  void invoke(Context *ctx, Node *node) {
    // 重复调用则跳过
    if (node->state.load(std::memory_order_acquire) > 0) {
      return;
    }
    // 判断依赖是否ready
    if (node->in_ready.load(std::memory_order_acquire) > 0) {
      return;
    }

    node->state.store(1, std::memory_order_release);
    node->task();  // 节点超时由内部控制
    node->state.store(2, std::memory_order_release);

    if (!node->out_nodes.empty()) {
      // 触发下游节点计数更新，调用invoke
      for (auto *out : node->out_nodes) {
        int cnt = out->in_ready.fetch_sub(1, std::memory_order_release);
        if (cnt == 1) { // use lock
          submit(std::bind(&Executor::invoke, this, ctx, out));
        }
      }
    }
    // 触发ctx任务计数更新，判断是否完成
    ctx->wait_num.fetch_sub(1, std::memory_order_release);
    ctx->cond.notify_one();
  }
};

class PThreadExecutor : Executor {
public:
  void submit(VoidTask task){

  };
};