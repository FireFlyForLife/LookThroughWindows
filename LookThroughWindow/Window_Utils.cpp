#include "Window_Utils.h"

int GetZOrder(HWND hwd)
{
	int z = 0;
	for (HWND h = hwd; h != 0; h = GetWindow(h, GW_HWNDPREV)) z++;
	return z;
}

HWND GetTopZOrderWindow()
{
	return NULL;
}

