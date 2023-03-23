#pragma once

#include "src/proto_gen/recommend.pb.h"

namespace cpp_service {
namespace server {
class RecommendServiceImpl : public recommend::RecommendService {
public:
  RecommendServiceImpl();
  virtual ~RecommendServiceImpl();
  virtual void Recommend(google::protobuf::RpcController *cntl_base,
                         const recommend::RecommendRequest *request,
                         recommend::RecommendResponse *response,
                         google::protobuf::Closure *done);
};
} // namespace server
} // namespace cpp_service