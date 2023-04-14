# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(chat_gpt_api_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(crow/include)

add_executable(chat_gpt_api_client
    src/chat_gpt_client.cpp
    src/chatbot_adapter.cpp
    src/http_server.cpp
    src/main.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(chat_gpt_api_client Threads::Threads)

find_package(CURL REQUIRED)
target_link_libraries(chat_gpt_api_client CURL::libcurl)

#add_subdirectory(crow)
#target_link_libraries(chat_gpt_api_client crow)

# 如果使用了其它第三方库，例如 Pistache 或 CppRestSDK，也需要在此处添加依赖
