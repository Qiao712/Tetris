#pragma once
#include "Texture.h"
#include "Menu.h"
class Button :
    public Menu
{
public:
    Button();

private:
    Texture* texture_normal;     //����״̬
    Texture* texture_on;         //�����ͣ�ڰ�ť��ʱ��״̬
    Texture* texture_pressed;    //����ʱ״̬
};

