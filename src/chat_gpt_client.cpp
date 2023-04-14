// chat_gpt_client.cpp
#include "chat_gpt_client.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <mutex>

using namespace std;

size_t ChatGPTClient::write_to_string(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t total_size = size * nmemb;
    std::string *response = (std::string *) stream;
    response->append((char *) ptr, total_size);
    return total_size;
}

ChatGPTClient::ChatGPTClient() {
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error initializing CURL library" << std::endl;
        exit(1);
    }
}

ChatGPTClient::~ChatGPTClient() {
    curl_easy_cleanup(curl);
}

void ChatGPTClient::initialize(const string &api_key) {
    this->api_key = api_key;
}

void ChatGPTClient::reset_conversation() {
    first_message = true;
    conversation.clear();
}

string ChatGPTClient::send_message(string &message) {
    std::unique_lock<std::mutex> lock(conversation_mutex);


    if (message == "conversation") {
        string result;
        for (auto &conver : conversation) {
            result += conver["role"].get<std::string>() + ": ";
            result += conver["content"].get<std::string>() + "\n";
        }
        return result;
    }
    if (message == "reset"){
        reset_conversation();
        return "reset conversation";
    }
    if (first_message) {
        conversation.push_back({{"role", "system"}, {"content", message}});
        first_message = false;
    } else {
        conversation.push_back({{"role", "user"}, {"content", message}});
    }
    token_count += message.size();

    nlohmann::json request_json = {
        {"model", "gpt-3.5-turbo"},
        {"messages", conversation}
    };

    string request_body = request_json.dump();
    string response = perform_request(request_body);
    nlohmann::json response_json = nlohmann::json::parse(response);
    string answer = response_json["choices"][0]["message"]["content"];

    answer.erase(std::remove(answer.begin(), answer.end(), '\n'), answer.end());
    token_count += answer.size();
    conversation.push_back({{"role", "assistant"}, {"content", answer}});

    while (token_count > token_limit && conversation.size() > 2) {
        token_count -= conversation[1]["content"].get<std::string>().size();
        conversation.erase(conversation.begin() + 1);
    }

    lock.unlock();
    return answer;
}

string ChatGPTClient::perform_request(const string &request_body) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_body.c_str());
    //std::cout<<"api_key:"<<api_key<<std::endl;

    std::vector<std::string> header_string = {
        "Authorization: Bearer " + api_key,
        "max_tokens: 256"
    };

    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    for (const auto &header : header_string) {
      headers = curl_slist_append(headers, header.c_str());
    }
    //headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "Error making request: " << curl_easy_strerror(res) << endl;
        curl_slist_free_all(headers);
        exit(1);
    }

    curl_slist_free_all(headers);
    return response;
}