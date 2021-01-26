#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
using namespace std;

//初始化窗口和渲染器
bool init();
//退出前的清楚
void clean();

//错误信息输出
void logError(string message);
//获取时间间隔
unsigned long long getTimeInterval(bool last = 0);

//获取时间戳
unsigned int getTime();