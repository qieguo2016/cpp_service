#include "recommend.h"
#include "brpc/closure_guard.h"
#include "brpc/controller.h"
#include <ctime>
#include <string>

namespace cpp_service {
namespace server {
RecommendServiceImpl::RecommendServiceImpl() {}

RecommendServiceImpl::~RecommendServiceImpl() {}

void RecommendServiceImpl::Recommend(google::protobuf::RpcController *cntl_base,
                                     const recommend::RecommendRequest *request,
                                     recommend::RecommendResponse *response,
                                     google::protobuf::Closure *done) {
  // This object helps you to call done->Run() in RAII style. If you need
  // to process the request asynchronously, pass done_guard.release().
  brpc::ClosureGuard done_guard(done);

  brpc::Controller *cntl = static_cast<brpc::Controller *>(cntl_base);
  // The purpose of following logs is to help you to understand
  // how clients interact with servers more intuitively. You should
  // remove these logs in performance-sensitive servers.
  LOG(INFO) << "Received recommend request[log_id=" << cntl->log_id() << "] from "
            << cntl->remote_side() << " to " << cntl->local_side() << ": "
            << request->DebugString();

  // Fill response.
  response->set_code(0);
  response->set_message("success: " + std::to_string(time(0)));
}

} // namespace server
} // namespace cpp_service