#include "http_request.hpp"
#include "router.hpp"

bool match_method(evhttp_cmd_type m, HttpMethod r) {
    switch (r) {
        case HttpMethod::GET:  return m == EVHTTP_REQ_GET;
        case HttpMethod::POST: return m == EVHTTP_REQ_POST;
        case HttpMethod::ANY:  return true;
    }
    return false;
}

void Router::handle(const HttpRequest& req) const {
    auto path = req.path();
    auto method = req.method();

    for (const auto& r : routes_) {
        if (r.path == path && match_method(method, r.method)) {
            r.handler(req);
            return;
        }
    }

    req.send(404, "Not Found\n");
}
