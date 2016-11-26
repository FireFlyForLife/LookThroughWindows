#include <string>
#include <cstring>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <stdexcept>

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/timer.hpp>
#include "subclass.h"
#include "WindowManager.h"
#include "WindowProperties.h"

#define str(s) std::to_string(s)
#define println(s) if(typeid(s) == typeid(bool)){\
	printf("%i\n", s);\
}else{\
	printf("%\n", str(s));}


using std::string;
using namespace nana;

struct HOTKEY_INFO {
	HOTKEY_INFO(int id, int mod, int button) : id(id), mod(mod), button(button)
	{}
public:
	int id;
	int mod;
	int button;
};

const HOTKEY_INFO watchable(1, MOD_NOREPEAT | MOD_CONTROL | MOD_SHIFT, 0x47);
const HOTKEY_INFO moveable(2, MOD_NOREPEAT | MOD_CONTROL | MOD_SHIFT, 0x48);

const int HOTKEY_BUTTON0 = 0x47; //g
const int HOTKEY_BUTTON1 = 0x48; //h
const int HOTKEY_MOD = MOD_NOREPEAT | MOD_CONTROL | MOD_SHIFT;
const int HOTKEY_ID = 1020304;

WindowManager manager;

bool SetTransparent(HWND);
bool SetTopmost(HWND);
bool SetClickThrough(HWND);

timer msgQ;
HWND optionHandle = NULL;
WindowProperties* topmostProp = NULL;



std::recursive_mutex subclass::mutex_;
std::map<HWND, subclass*> subclass::table_;

void msges(const nana::arg_elapse& elapsed) {
	MSG msgstruct;
	BOOL available = PeekMessage(&msgstruct, optionHandle, WM_HOTKEY, WM_HOTKEY, PM_REMOVE);

	if (available) {
		printf("%i\n", msgstruct.message);
		printf("%i\n", msgstruct.lParam);
		printf("%i\n", msgstruct.wParam);
		printf("%i\n", msgstruct.hwnd);
	}
	else {
		printf("msg Q is empty...\n");
	}
}

bool onHotkeyPress(UINT msg, WPARAM hotkeyID, LPARAM lParam, LRESULT* lResult) {
	return true; //this needs to be called in WindowManager#onHotkeyPressed

	printf("Hotkey1 pressed!\n");
	if (hotkeyID == watchable.id) {
		topmostProp->setTopmost(true);
		topmostProp->setTransparent(true);
		topmostProp->setClickThrough(true);
	}
	else if (hotkeyID == moveable.id) {
		topmostProp->setTopmost(false);
		topmostProp->setTransparent(false);
		topmostProp->setClickThrough(false);
	}
	else {
		//wat is dis
		throw std::exception("that hotkey id us not registered");
	}

	return true;
}

void registerHotkeyWithInfo(HOTKEY_INFO info) {
	RegisterHotKey(optionHandle, info.id, info.mod, info.button);
}

int main() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	HWND topmost = GetForegroundWindow();
	if (topmost == GetDesktopWindow() || topmost == NULL) {
		printf("Could not find topmost window");
		return 404;
	}

	topmostProp = new WindowProperties(topmost);

	/*WindowProperties testWindow(topmost);
	println(testWindow.isTransparent())
	testWindow.setTransparent(true);
	println(testWindow.isTransparent())
	println(testWindow.isTopmost())
	testWindow.setTopmost(true);
	println(testWindow.isTopmost())
	println(testWindow.isClickThrough())
	testWindow.setClickThrough(true);
	println(testWindow.isClickThrough())*/

	form optionForm;
	optionForm.caption("LookThroughWindows - Options");
	optionHandle = reinterpret_cast<HWND>(optionForm.native_handle());

	subclass sc(optionForm);
	sc.make_before(WM_HOTKEY, onHotkeyPress);
	manager.registerHotkeys(&sc);

	//RegisterHotKey(optionHandle, HOTKEY_ID, HOTKEY_MOD, HOTKEY_BUTTON0);
	//RegisterHotKey(optionHandle, HOTKEY_ID+1, HOTKEY_MOD, HOTKEY_BUTTON1);
	//registerHotkeyWithInfo(watchable);
	//registerHotkeyWithInfo(moveable);

	optionForm.show();

	//msgQ.elapse(msges);
	//msgQ.start();

	exec();

	return 0;
}

//bool SetTransparent(HWND window) {
//	LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
//	exStyle |= WS_EX_LAYERED;
//	LONG ret = SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
//	SetLayeredWindowAttributes(window, NULL, 128, LWA_ALPHA);
//
//	return ret;
//}
//
//bool SetTopmost(HWND window) {
//	/*LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
//	exStyle |= WS_EX_TOPMOST;
//	LONG ret = SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
//	
//	return ret;*/
//
//	return SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
//}
//
//bool SetClickThrough(HWND window) {
//	return SetWindowLongPtr(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
//}