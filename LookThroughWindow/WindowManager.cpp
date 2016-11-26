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
	//TODO: Unregister hotkeys
}

void WindowManager::registerHotkeys(subclass* sc)
{
	sc->make_after(WM_HOTKEY, [this](UINT u, WPARAM w, LPARAM l, LRESULT* r) {
		bool ret = this->onHotkeyPressed(u, w, l, r);
		//printf("%i", ret);
		return ret;
	});
	HWND handle = sc->getWindow();
	RegisterHotKey(handle, watchable_id, MOD_NOREPEAT|MOD_CONTROL|MOD_SHIFT, 0x47); //g
	RegisterHotKey(handle, moveable_id, MOD_NOREPEAT | MOD_CONTROL | MOD_SHIFT, 0x48); //h
}

void WindowManager::addWindow(HWND window)
{
	window_map::iterator it = windows.find(window);
	if (it == windows.end()) {
		WindowProperties* prop = new WindowProperties(window);
		prop->setTopmost(true);
		prop->setTransparent(true);
		prop->setClickThrough(true);

		windows.insert(std::pair<HWND, WindowProperties*>(window, prop));
	}
}

void WindowManager::delWindow(HWND window)
{
	window_map::iterator it = windows.find(window);
	if (it != windows.end()) {
		WindowProperties* prop = it->second;
		delete prop; //MAYBE: not rely on deconstructor but write the reset explicitly.
		windows.erase(it);
	}
}

bool WindowManager::onHotkeyPressed(UINT msg, WPARAM hotkeyID, LPARAM lParam, LRESULT * lResult)
{
	HWND top = GetForegroundWindow();

	switch (hotkeyID)
	{
	case watchable_id:
		addWindow(top);
		break;
	case moveable_id:
		delWindow(top);
		break;
	default:
		printf("%i is not an ID recognised by this WindowManager\n", hotkeyID);
		break;
	}
	
	/*window_map::iterator it = windows.find(top);
	if (it != windows.end()) {
		WindowProperties* prop = it->second;

	}*/

	//WindowProperties topmostProp(NULL);
	//if (hotkeyID == watchable_id) {
	//	topmostProp.setTopmost(true);
	//	topmostProp.setTransparent(true);
	//	topmostProp.setClickThrough(true);
	//}
	//else if (hotkeyID == moveable_id) {
	//	topmostProp.setTopmost(false);
	//	topmostProp.setTransparent(false);
	//	topmostProp.setClickThrough(false);
	//}
	//else {
	//	//wat is dis
	//	throw std::exception("that hotkey id us not registered");
	//}
	return true;
}
