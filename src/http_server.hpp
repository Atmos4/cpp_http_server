#pragma once
#include <event2/event.h>
#include <event2/http.h>
#include "router.hpp"

class HttpServer {
public:
    HttpServer();

    void setRouter(Router* r);
    int run(const char* addr, int port);

private:
    static void dispatch(evhttp_request* req, void* arg);

    event_base* base_;
    evhttp* http_;
    Router* router_;
};
