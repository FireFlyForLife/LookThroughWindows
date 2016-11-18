#pragma once
#include <functional>
#include <vector>
#include <Windows.h>
#include "subclass.h"
#include "WindowProperty.h"

class WindowManager
{
public:
	const int watchable_id = 1;
	const int moveable_id = 2;

	WindowManager();
	WindowManager(subclass*);
	~WindowManager();

	void registerHotkeys(subclass*);
	void addForegroundWindow();
	bool onHotkeyPressed(UINT, WPARAM, LPARAM, LRESULT*);

private:
	std::vector<WindowProperties> windows;
};

