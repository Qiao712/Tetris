#pragma once
class Menu
{
public:
	virtual void render();
	virtual void update();
	virtual void click();
	static void updateMousePosition(int x, int y);
protected:
	// Û±ÍŒª÷√
	static int mouse_x;
	static int mouse_y;
};

