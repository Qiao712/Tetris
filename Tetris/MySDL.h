#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
using namespace std;

//��ʼ�����ں���Ⱦ��
bool init();
//�˳�ǰ�����
void clean();

//������Ϣ���
void logError(string message);
//��ȡʱ����
unsigned long long getTimeInterval(bool last = 0);

//��ȡʱ���
unsigned int getTime();