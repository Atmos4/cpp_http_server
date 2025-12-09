#include "http_server.hpp"
#include "router.hpp"

int main() {
    Router router;
    router.add(HttpMethod::GET, "/", [](const HttpRequest& req) {
        req.send(200, "Hello from clean C++!\n");
    });
    router.add(HttpMethod::POST, "/echo", [](const HttpRequest& req) {
        req.send(200, "You said: " + req.body());
    });

    HttpServer server;
    server.setRouter(&router);
    return server.run("0.0.0.0", 8080);
}
