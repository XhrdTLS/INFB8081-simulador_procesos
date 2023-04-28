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
	case WM_COMMAND: {
		if (LOWORD(wparam) == BTN_SHOW && HIWORD(wparam) == BN_CLICKED) {
			HWND hName = GetDlgItem(hwnd, TXT_NAME);
			int iTextLength = GetWindowTextLength(hName);
			char cName[100];
			GetWindowText(hName, cName, ++iTextLength);
			MessageBox(NULL, cName, "Nombre", MB_OK);
		}
	}break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(117);
		break;
	}
	return FALSE;
}
