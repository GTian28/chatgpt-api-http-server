// http_server.cpp
#include "http_server.hpp"
#include "chatbot_adapter.hpp"

HTTPServer::HTTPServer(int port, const std::string & api_key)
    : chatbot_adapter(std::make_unique<ChatGPTClient>()) {
    chatbot_adapter.initialize(api_key);
    app.port(port);
    setup_routes();
}

void HTTPServer::run() {
    app.run();
}

void HTTPServer::setup_routes() {
    CROW_ROUTE(app, "/")
        .methods("POST"_method)
        ([this](const crow::request &req) {
            auto request_json = crow::json::load(req.body);
            std::string message = request_json["message"].s();
            std::string response = chatbot_adapter.send_message(message);

            crow::json::wvalue result;
            result["response"] = response;

            return crow::response(200, result);
        });

}
