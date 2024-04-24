#include "PluginSDK.h"
#include <curl/curl.h>
#include <string>
#include <cstring>
#include <iostream>
#include <memory>

// 内部结构，用于管理从libcurl接收到的数据
struct CurlData {
    std::string data;
};

// libcurl的写入回调函数
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t real_size = size * nmemb;
    CurlData *mem = static_cast<CurlData*>(userp);
    mem->data.append(static_cast<char*>(contents), real_size);
    return real_size;
}

// GET请求
static std::string http_get(const char* url) {
    CURL *curl;
    CURLcode res;
    CurlData buffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        }
        curl_easy_cleanup(curl);
    }
    return buffer.data;
}

PluginSDK* PluginSDK_Create(const char* serverAddress) {
    PluginSDK* sdk = new PluginSDK;
    if (sdk) {
        sdk->serverAddress = serverAddress;
    }
    return sdk;
}

void PluginSDK_Destroy(PluginSDK* sdk) {
    if (sdk) {
        delete sdk;
    }
}

std::string PluginSDK_GetPluginVer(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/SDKVer";
    return http_get(url.c_str());
}

bool PluginSDK_GetPlaying(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/isPlaying";
    std::string result = http_get(url.c_str());
    return result == "true";
}

bool PluginSDK_GetPlayAudio(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/playAudio";
    std::string result = http_get(url.c_str());
    return result == "true";
}

std::string PluginSDK_GetMMVer(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/nowVer";
    return http_get(url.c_str());
}

std::string PluginSDK_GetMMRunning(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/runningDirectory";
    return http_get(url.c_str());
}

std::string PluginSDK_GetPlayAudioKey(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/playAudioKey";
    return http_get(url.c_str());
}

std::string PluginSDK_GetToggleStreamKey(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/toggleStreamKey";
    return http_get(url.c_str());
}

int PluginSDK_GetVBVolume(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/VBvolume";
    std::string result = http_get(url.c_str());
    return std::stoi(result);
}

int PluginSDK_GetVolume(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/volume";
    std::string result = http_get(url.c_str());
    return std::stoi(result);
}

int PluginSDK_GetTipsVolume(PluginSDK* sdk) {
    std::string url = sdk->serverAddress + "/api/tipsvolume";
    std::string result = http_get(url.c_str());
    return std::stoi(result);
}

std::string PluginSDK_GetListViewInfo(PluginSDK* sdk, const char* responseType) {
    std::string url = sdk->serverAddress + "/api/listViewInfo?type=" + std::string(responseType);
    return http_get(url.c_str());
}

std::string PluginSDK_PlayAudio(PluginSDK* sdk, const char* audioName) {
    std::string url = sdk->serverAddress + "/api/playAudio?name=" + std::string(audioName);
    return http_get(url.c_str());
}
