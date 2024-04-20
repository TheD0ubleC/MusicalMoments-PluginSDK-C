#ifndef PLUGIN_SDK_H
#define PLUGIN_SDK_H

#include <stdbool.h>

typedef struct {
    char* serverAddress;  //服务器地址
} PluginSDK;

//构造和析构函数
PluginSDK* PluginSDK_Create(const char* serverAddress);
void PluginSDK_Destroy(PluginSDK* sdk);

char* PluginSDK_GetPluginVer(PluginSDK* sdk);
bool PluginSDK_GetPlaying(PluginSDK* sdk);
bool PluginSDK_GetPlayAudio(PluginSDK* sdk);
char* PluginSDK_GetMMVer(PluginSDK* sdk);
char* PluginSDK_GetMMRunning(PluginSDK* sdk);
char* PluginSDK_GetPlayAudioKey(PluginSDK* sdk);
char* PluginSDK_GetToggleStreamKey(PluginSDK* sdk);
int PluginSDK_GetVBVolume(PluginSDK* sdk);
int PluginSDK_GetVolume(PluginSDK* sdk);
int PluginSDK_GetTipsVolume(PluginSDK* sdk);
char* PluginSDK_GetListViewInfo(PluginSDK* sdk, const char* responseType);
char* PluginSDK_PlayAudio(PluginSDK* sdk, const char* audioName);

#endif
