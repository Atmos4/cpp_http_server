#pragma once
#include "http_request.hpp"
#include <functional>
#include <string>
#include <vector>

enum class HttpMethod { GET, POST, ANY };
using HandlerFunc = std::function<void(const HttpRequest&)>;

struct Route {
    HttpMethod method;
    std::string path;
    HandlerFunc handler;
};

class Router {
public:
    void add(HttpMethod m, const std::string& path, HandlerFunc h) {
        routes_.push_back({m, path, h});
    }

    void handle(const HttpRequest& req) const;

private:
    std::vector<Route> routes_;
};
