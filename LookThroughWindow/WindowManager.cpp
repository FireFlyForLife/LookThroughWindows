#include "WindowManager.h"



WindowManager::WindowManager()
{
}

WindowManager::WindowManager(subclass * sc)
{
	registerHotkeys(sc);
}


WindowManager::~WindowManager()
{
}

void WindowManager::registerHotkeys(subclass* sc)
{
	typedef std::function<bool(UINT, WPARAM, LPARAM, LRESULT*)> hotkey_callback;
	//hotkey_callback callback = std::bind(&WindowManager::onHotkeyPressed, this, std::placeholders::_1);
	sc->make_after(WM_HOTKEY, [this](UINT u, WPARAM w, LPARAM l, LRESULT* r) {
		bool ret = this->onHotkeyPressed(u, w, l, r);
		printf("%i", ret);
		return ret;
	});
	HWND handle = sc->getWindow();
	RegisterHotKey(handle, watchable_id, MOD_NOREPEAT|MOD_CONTROL|MOD_SHIFT, 0x47); //g
	RegisterHotKey(handle, moveable_id, MOD_NOREPEAT | MOD_CONTROL | MOD_SHIFT, 0x48); //h
}

void WindowManager::addForegroundWindow()
{
}

bool WindowManager::onHotkeyPressed(UINT msg, WPARAM hotkeyID, LPARAM lParam, LRESULT * lResult)
{
	HWND top = GetForegroundWindow();
	for each (WindowProperties prop in windows)
	{
		if(prop)
	}
	WindowProperties topmostProp(NULL);
	if (hotkeyID == watchable_id) {
		topmostProp.setTopmost(true);
		topmostProp.setTransparent(true);
		topmostProp.setClickThrough(true);
	}
	else if (hotkeyID == moveable_id) {
		topmostProp.setTopmost(false);
		topmostProp.setTransparent(false);
		topmostProp.setClickThrough(false);
	}
	else {
		//wat is dis
		throw std::exception("that hotkey id us not registered");
	}
	return true;
}
