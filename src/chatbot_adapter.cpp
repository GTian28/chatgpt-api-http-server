// chatbot_adapter.cpp
#include "chatbot_adapter.hpp"

ChatBotAdapter::ChatBotAdapter(std::unique_ptr<ChatBotInterface> chatbot)
    : chatbot(std::move(chatbot)) {}

std::string ChatBotAdapter::send_message(std::string &message) {
    return chatbot->send_message(message);
}

void ChatBotAdapter::reset_conversation() {
    chatbot->reset_conversation();
}

void ChatBotAdapter::initialize(const std::string &config) {
    chatbot->initialize(config);
}