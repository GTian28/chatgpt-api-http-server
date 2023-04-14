// http_server.cpp
#include "http_server.hpp"

HTTPServer::HTTPServer(int port) {
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
            std::string response = chat_gpt_client.send_message(message);

            crow::json::wvalue result;
            result["response"] = response;

            return crow::response(200, result);
        });

    CROW_ROUTE(app, "/reset")
        .methods("POST"_method)
        ([this](const crow::request &req) {
            chat_gpt_client.reset_conversation();
            return crow::response(200);
        });
}
