#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK fVentana1(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow) {
	HWND hVentana1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, fVentana1);
	ShowWindow(hVentana1, cShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK fVentana1(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(117);
		break;
	}
	return FALSE;
}
