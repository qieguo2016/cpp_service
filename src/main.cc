#include "cache/hashtable.h"
#include "server/recommend.h"
#include <brpc/server.h>
#include <butil/hash.h>
#include <cstdio>
#include <cstdlib>
#include <execinfo.h>
#include <functional>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <string>

DEFINE_int32(port, 8080, "TCP Port of this server");
DEFINE_int32(idle_timeout_s, -1,
             "Connection will be closed if there is no "
             "read/write operations during the last `idle_timeout_s'");

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, false);
  google::InitGoogleLogging("cpp_service");
  google::SetStderrLogging(google::GLOG_INFO);
  google::InstallFailureSignalHandler();
  srand((unsigned)time(NULL));

  LOG(INFO) << "cpp_service start";

  // Generally you only need one Server.
  brpc::Server server;

  // Add the service into server. Notice the second parameter, because the
  // service is put on stack, we don't want server to delete it, otherwise
  // use brpc::SERVER_OWNS_SERVICE.
  cpp_service::server::RecommendServiceImpl rcmd_service_impl;
  if (server.AddService(&rcmd_service_impl, brpc::SERVER_DOESNT_OWN_SERVICE) !=
      0) {
    LOG(ERROR) << "Fail to add recommend service";
    return -1;
  }

  // Start the server.
  brpc::ServerOptions options;
  options.idle_timeout_sec = FLAGS_idle_timeout_s;
  options.server_info_name = "cpp_service";
  if (server.Start(FLAGS_port, &options) != 0) {
    LOG(ERROR) << "fail to start server";
    return -1;
  }

  // Wait until Ctrl-C is pressed, then Stop() and Join() the server.
  server.RunUntilAskedToQuit();
  return 0;
}