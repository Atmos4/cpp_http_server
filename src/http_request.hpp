#pragma once
#include <event2/http.h>
#include <event2/buffer.h>
#include <string>
#include <cstring>

class HttpRequest {
public:
    explicit HttpRequest(evhttp_request* req)
        : req_(req) {}

    void send(int code, const char* body) const {
        evbuffer* buf = evbuffer_new();
        evbuffer_add(buf, body, std::strlen(body));
        evhttp_send_reply(req_, code, nullptr, buf);
        evbuffer_free(buf);
    }

    void send(int code, const std::string& body) const {
        send(code, body.c_str());
    }

    std::string body() const {
        evbuffer* buf = evhttp_request_get_input_buffer(req_);
        size_t len = evbuffer_get_length(buf);
        std::string out(len, '\0');
        evbuffer_copyout(buf, out.data(), len);
        return out;
    }

    std::string path() const {
        const char* uri = evhttp_request_get_uri(req_);
        struct evhttp_uri* parsed = evhttp_uri_parse(uri);
        if (!parsed) return "";
        const char* p = evhttp_uri_get_path(parsed);
        std::string result = p ? p : "/";
        evhttp_uri_free(parsed);
        return result;
    }

    evhttp_cmd_type method() const {
      return evhttp_request_get_command(req_);
    }

    evhttp_request* raw() const { return req_; }

private:
    evhttp_request* req_;
};
