#include "WindowProperty.h"



WindowProperty::WindowProperty(HWND handle) : handle(handle)
{
}


WindowProperty::~WindowProperty()
{
}

//MAYBE: Make the return values a little more usefull
bool WindowProperty::setTransparent(bool look_through) {
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
		exStyle |= WS_EX_LAYERED;
		LONG ret = SetWindowLongPtr(handle, GWL_EXSTYLE, exStyle);
		SetLayeredWindowAttributes(handle, NULL, 128, LWA_ALPHA);

		return (bool)ret;
	}
}

bool WindowProperty::isTransparent()
{
	LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
	return (bool)(exStyle & WS_EX_LAYERED);
}

bool WindowProperty::setTopmost(bool top_most) {
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

bool WindowProperty::isTopmost()
{
	LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
	return (bool)(exStyle & WS_EX_TOPMOST);
}

bool WindowProperty::setClickThrough(bool click_through) {
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
		return SetWindowLongPtr(handle, GWL_EXSTYLE, GetWindowLongPtr(handle, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	}
}

//TODO: Test this method
bool WindowProperty::isClickThrough()
{
	LONG_PTR exStyle = GetWindowLongPtr(handle, GWL_EXSTYLE);
	return (bool)(exStyle & WS_EX_LAYERED & WS_EX_TRANSPARENT);
}
