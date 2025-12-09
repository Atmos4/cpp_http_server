#include "http_server.hpp"
#include "http_request.hpp"
#include <iostream>

HttpServer::HttpServer()
    : router_(nullptr)
{
    base_ = event_base_new();
    http_ = evhttp_new(base_);
}

void HttpServer::setRouter(Router* r) {
    router_ = r;
    evhttp_set_gencb(http_, &HttpServer::dispatch, this);
}

int HttpServer::run(const char* addr, int port) {
    if (evhttp_bind_socket_with_handle(http_, addr, port) == nullptr){
      return 1;
    }
    std::cout << "Server running at http://" << addr << ":" << port << std::endl;
    event_base_dispatch(base_);
    return 0;
}

void HttpServer::dispatch(evhttp_request* req, void* arg) {
    auto* server = static_cast<HttpServer*>(arg);
    HttpRequest request(req);

    if (server->router_)
        server->router_->handle(request);
    else
        request.send(500, "No router installed\n");
}
