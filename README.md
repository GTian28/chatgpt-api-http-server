# ChatGPT API HTTP Server

调用ChatGPT的API，并部署一个HTTP服务

## 现有功能：

1. 直接对话（支持连续多轮对话）（每次会话的第一句会作为系统消息发给ChatGPT）
2. `reset` - 重置会话
3. `conversation` - 查看当前会话记录
4. `切换AI AI名` - 切换名为“AI名”的聊天机器人。（目前仅支持chatgpt）

为了省钱，设置了token上限，超过上限时会删除最早的聊天记录

## 使用方法（以Debian 11为例）：

### 1. 安装必要的开发工具和库

```
sudo apt-get update
sudo apt-get install build-essential cmake libcurl4-openssl-dev
```

### 2. 克隆源代码

```
git clone https://github.com/GTian28/chatgpt-api-http-server.git
cd chatgpt-api-http-server
```

### 3. 编译项目

在刚刚的路径下，依次执行以下代码：

```
mkdir build
cd build
cmake ..
make
```

如果cmake过程中报错，尝试更新cmake。

### 4. 配置ChatGPT API Key的环境变量（避免Key暴露在代码中）

执行 `vi ~/.bashrc` ，保证在英文输入模式下，按 `i` 进入编辑模式，在最后添加 `export CHATGPT_API_KEY=你的chatgpt_api_key`。然后按 `Esc` 退出编辑模式，`Shift + :` 进入命令行模式，输入 `wq` ，然后回车保存退出。

### 5. 运行程序

```
./chat_gpt_api_client
```

默认端口设置为8069，之后就可以通过8069端口发POST请求与ChatGPT聊天了。
