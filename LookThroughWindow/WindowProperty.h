#pragma once
#include <Windows.h>
#include <stdio.h>

class WindowProperties
{
public:
	WindowProperties(HWND);
	~WindowProperties();

	bool setTransparent(bool look_through);
	bool isTransparent();
	bool setTopmost(bool top_most);
	bool isTopmost();
	bool setClickThrough(bool click_through);
	bool isClickThrough();

	bool autoClose = true;

private:
	HWND handle = NULL;

	bool transparent = false;
	bool topmost = false;
	bool clickThrough = false;
};

