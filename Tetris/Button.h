#pragma once
#include "Texture.h"
#include "Menu.h"
class Button :
    public Menu
{
public:
    Button();

private:
    Texture* texture_normal;     //正常状态
    Texture* texture_on;         //鼠标悬停在按钮上时的状态
    Texture* texture_pressed;    //按下时状态
};

