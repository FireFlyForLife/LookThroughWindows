#include "WindowProperty.h"



WindowProperties::WindowProperties(HWND handle) : handle(handle)
{
}


WindowProperties::~WindowProperties()
{
	if (autoClose) {
		setTopmost(false);
		setClickThrough(false);
		setTransparent(false);
		printf("CLOSING");//TODO: rm this
	}
}

//MAYBE: Make the return values a little more usefull
bool WindowProperties::setTransparent(bool look_through) {
	if (look_through) {
		if (isTransparent())
			return false;

		LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
		exStyle |= WS_EX_LAYERED;
		LONG ret = SetWindowLongPtr(handle, GWL_EXSTYLE, exStyle);
		SetLayeredWindowAttributes(handle, NULL, 128, LWA_ALPHA);

		return (bool)ret;
	}
	else {
		if (!isTransparent())
			return false;

		LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
		exStyle &= ~(WS_EX_LAYERED);
		LONG ret = SetWindowLongPtr(handle, GWL_EXSTYLE, exStyle);
		SetLayeredWindowAttributes(handle, NULL, 256, LWA_ALPHA);

		return (bool)ret;
	}
}

bool WindowProperties::isTransparent()
{
	LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
	return (bool)(exStyle & WS_EX_LAYERED);
}

bool WindowProperties::setTopmost(bool top_most) {
	if (top_most) {
		if (isTopmost())
			return false;

		return SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else {
		if (!isTopmost())
			return false;

		return SetWindowPos(handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}

bool WindowProperties::isTopmost()
{
	LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
	return (bool)(exStyle & WS_EX_TOPMOST);
}

bool WindowProperties::setClickThrough(bool click_through) {
	if (click_through) {
		if (isClickThrough())
			return false;

		LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
		exStyle = exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT;
		return SetWindowLongPtr(handle, GWL_EXSTYLE, exStyle);//TODO: Does this still work?
	}
	else {
		if (!isClickThrough())
			return false;

		LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
		exStyle &= ~(WS_EX_LAYERED | WS_EX_TRANSPARENT);
		return SetWindowLongPtr(handle, GWL_EXSTYLE, GetWindowLongPtr(handle, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	}
}

bool WindowProperties::isClickThrough()
{
	LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE); 
	return ((bool)(exStyle & WS_EX_LAYERED)) && ((bool)(exStyle & WS_EX_TRANSPARENT));//TODO: A more elegant solution
}

HWND WindowProperties::getWindow(HWND)
{
	return handle;
}
