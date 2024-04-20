#include "PluginSDK.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

//内部结构，用于管理从libcurl接收到的数据
typedef struct {
    char *data;
    size_t length;
} CurlData;

//libcurl的写入回调函数
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t real_size = size * nmemb;
    CurlData *mem = (CurlData *)userp;

    char *ptr = realloc(mem->data, mem->length + real_size + 1);
    if (ptr == NULL) {
        return 0;  //内存爆炸
    }

    mem->data = ptr;
    memcpy(&(mem->data[mem->length]), contents, real_size);
    mem->length += real_size;
    mem->data[mem->length] = '\0';
    return real_size;
}

//GET
static char* http_get(const char* url) {
    CURL *curl;
    CURLcode res;
    CurlData buffer = { .data = NULL, .length = 0 };

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(buffer.data);
            buffer.data = NULL;
        }
        curl_easy_cleanup(curl);
    }
    return buffer.data;
}

PluginSDK* PluginSDK_Create(const char* serverAddress) {
    PluginSDK* sdk = malloc(sizeof(PluginSDK));
    if (sdk) {
        sdk->serverAddress = strdup(serverAddress);
    }
    return sdk;
}

void PluginSDK_Destroy(PluginSDK* sdk) {
    if (sdk) {
        free(sdk->serverAddress);
        free(sdk);
    }
}

char* PluginSDK_GetPluginVer(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/SDKVer", sdk->serverAddress);
    return http_get(url);
}

bool PluginSDK_GetPlaying(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/isPlaying", sdk->serverAddress);
    char *result = http_get(url);
    bool playing = result && strcmp(result, "true") == 0;
    free(result);
    return playing;
}

bool PluginSDK_GetPlayAudio(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/playAudio", sdk->serverAddress);
    char *result = http_get(url);
    bool playAudio = result && strcmp(result, "true") == 0;
    free(result);
    return playAudio;
}

char* PluginSDK_GetMMVer(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/nowVer", sdk->serverAddress);
    return http_get(url);
}

char* PluginSDK_GetMMRunning(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/runningDirectory", sdk->serverAddress);
    return http_get(url);
}

char* PluginSDK_GetPlayAudioKey(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/playAudioKey", sdk->serverAddress);
    return http_get(url);
}

char* PluginSDK_GetToggleStreamKey(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/toggleStreamKey", sdk->serverAddress);
    return http_get(url);
}

int PluginSDK_GetVBVolume(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/VBvolume", sdk->serverAddress);
    char *result = http_get(url);
    int volume = result ? atoi(result) : 0;
    free(result);
    return volume;
}

int PluginSDK_GetVolume(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/volume", sdk->serverAddress);
    char *result = http_get(url);
    int volume = result ? atoi(result) : 0;
    free(result);
    return volume;
}

int PluginSDK_GetTipsVolume(PluginSDK* sdk) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/tipsvolume", sdk->serverAddress);
    char *result = http_get(url);
    int volume = result ? atoi(result) : 0;
    free(result);
    return volume;
}

char* PluginSDK_GetListViewInfo(PluginSDK* sdk, const char* responseType) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/listViewInfo?type=%s", sdk->serverAddress, responseType);
    return http_get(url);
}

char* PluginSDK_PlayAudio(PluginSDK* sdk, const char* audioName) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/api/playAudio?name=%s", sdk->serverAddress, audioName);
    return http_get(url);
}
