#include <string>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <thread>

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/timer.hpp>
#include "subclass.h"
#include "WindowProperty.h"

using std::string;
using namespace nana;

const int HOTKEY_BUTTON = 0x47; //g
const int HOTKEY_MOD = MOD_NOREPEAT | MOD_CONTROL | MOD_SHIFT;
const int HOTKEY_ID = 1020304;

bool SetTransparent(HWND);
bool SetTopmost(HWND);
bool SetClickThrough(HWND);

timer msgQ;
HWND optionHandle = NULL;

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

bool onHotkeyPress(UINT id, WPARAM wParam, LPARAM lParam, LRESULT* lResult) {
	printf("%i\n", id);
	printf("%i\n", wParam);
	printf("%i\n", lParam);
	printf("%i\n", lResult);

	return true;
}

int main() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	HWND topmost = GetForegroundWindow();
	if (topmost == GetDesktopWindow() || topmost == NULL) {
		printf("Could not find topmost window");
		return 404;
	}

	WindowProperty testWindow(topmost);
	testWindow.setTransparent(true);
	testWindow.setTransparent(true);

	/*bool madeTransparent = SetTransparent(topmost);
	bool madeTopmost = SetTopmost(topmost);
	bool madeClickThrough = SetClickThrough(topmost);*/

	form optionForm;
	optionForm.caption("LookThroughWindows - Options");
	optionHandle = reinterpret_cast<HWND>(optionForm.native_handle());

	subclass sc(optionForm);
	sc.make_before(WM_HOTKEY, onHotkeyPress);

	RegisterHotKey(optionHandle, HOTKEY_ID, HOTKEY_MOD, HOTKEY_BUTTON);

	optionForm.show();

	//msgQ.elapse(msges);
	//msgQ.start();

	exec();

	return 0;
}

bool SetTransparent(HWND window) {
	LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
	exStyle |= WS_EX_LAYERED;
	LONG ret = SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
	SetLayeredWindowAttributes(window, NULL, 128, LWA_ALPHA);

	return ret;
}

bool SetTopmost(HWND window) {
	/*LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
	exStyle |= WS_EX_TOPMOST;
	LONG ret = SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
	
	return ret;*/

	return SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

bool SetClickThrough(HWND window) {
	return SetWindowLongPtr(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
}