#pragma once
#include <functional>
#include <map>
#include <Windows.h>
#include "subclass.h"
#include "WindowProperties.h"

class WindowManager
{
public:
	static const int watchable_id = 1;
	static const int moveable_id = 2;

	WindowManager();
	WindowManager(subclass*);
	~WindowManager();

	void registerHotkeys(subclass*);
	bool onHotkeyPressed(UINT, WPARAM, LPARAM, LRESULT*);

protected:
	virtual void addWindow(HWND);
	virtual void delWindow(HWND);

	typedef std::map<HWND, WindowProperties*> window_map;
	window_map windows;
};

