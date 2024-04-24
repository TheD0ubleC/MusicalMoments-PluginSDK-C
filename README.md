# 简介
MusicalMoments 插件 API 使用 TCP Sockets 获取数据，因此需要发送 Get 请求。

你可以调用这些 API 来获取 MusicalMoments 的各种数据。

详情示例可看 MMPluginSDKExample。

# 获取输入
首先需要获取 Main 函数输入的第一个参数（API 地址），如下所示：
```cpp
#include <iostream>
#include <string>
#include <cstdlib>
#include "PluginSDK.h"  // 假设这是包含 PluginSDK 类的头文件

class Program {
public:
    static std::string serverAddress;
    static PluginSDK* pluginSDK;

    static void Main(int argc, char* argv[]) {
        if (argc < 2) {
            std::cout << "No server address provided. Exiting program." << std::endl;
            std::exit(1);  // 直接退出程序
        } else {
            serverAddress = argv[1];
        }
    }
};

std::string Program::serverAddress;
PluginSDK* Program::pluginSDK = nullptr;
```
如果获取成功，将继续执行；否则将退出。

# 调用
首先需要实例化一个 PluginSDK 对象，并使用 Main 的第一个参数来传入创建的实例化对象，如下所示：
```cpp
pluginSDK = new PluginSDK(serverAddress.c_str());
```
接着尝试输出 MusicalMoments 的版本号：
```cpp
static void Main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No server address provided. Exiting program." << std::endl;
        std::exit(1);
    } else {
        serverAddress = argv[1];
        pluginSDK = new PluginSDK(serverAddress.c_str());
        std::string mmVersion = pluginSDK->GetMMVer();
        std::cout << "MM版本号: " << mmVersion << std::endl;
        delete pluginSDK;
    }
}
```
