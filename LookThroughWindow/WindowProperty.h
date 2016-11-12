#pragma once
#include <Windows.h>
#include <stdio.h>

class WindowProperty
{
public:
	WindowProperty(HWND);
	~WindowProperty();

	bool setTransparent(bool look_through);
	bool isTransparent();
	bool setTopmost(bool top_most);
	bool isTopmost();
	bool setClickThrough(bool click_through);
	bool isClickThrough();

private:
	HWND handle = NULL;

	bool transparent = false;
	bool topmost = false;
	bool clickThrough = false;
};

