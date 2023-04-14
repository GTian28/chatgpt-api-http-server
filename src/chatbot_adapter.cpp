// chatbot_adapter.cpp
#include "chatbot_adapter.hpp"
#include "chat_gpt_client.hpp"
#include <regex>

ChatBotAdapter::ChatBotAdapter() {
    // 初始化工厂函数映射
    chatbot_factories["chatgpt"] = []() { return std::make_unique<ChatGPTClient>(); };
    // 默认使用 chatgpt 聊天机器人
    switch_chatbot("chatgpt");
    chatbots["chatgpt"] = current_chatbot;
}

std::string ChatBotAdapter::send_message(std::string &message) {
    std::regex switch_regex(R"(切换AI\s(\S+))");
    std::smatch match;
    
    if (std::regex_search(message, match, switch_regex)) {
        std::string new_chatbot_name = match[1].str();
        
        return switch_chatbot(new_chatbot_name);
    }
    return current_chatbot->send_message(message);
}

void ChatBotAdapter::reset_conversation() {
    current_chatbot->reset_conversation();
}

void ChatBotAdapter::initialize(const std::string &config) {
    current_chatbot->initialize(config);
}

std::string ChatBotAdapter::switch_chatbot(const std::string &name) {
    auto it = chatbots.find(name);
    if (it != chatbots.end()) {
        current_chatbot = it->second;
    } else {
        auto factory_it = chatbot_factories.find(name);
        if (factory_it != chatbot_factories.end()) {
            current_chatbot = factory_it->second();
            chatbots[name] = factory_it->second();
        } else {
            return "未找到名为 " + name + " 的聊天机器人";
        }
    }
    return "已切换至 " + name;
}