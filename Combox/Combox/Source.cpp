#include <Windows.h>
#include "resource.h"

int indiceActual = 0;
int arregloIndices[3] = { 33, 45, 2 };

LRESULT CALLBACK fVentana1(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow) {
	HWND hVentana1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, fVentana1);**
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	ShowWindow(hVentana1, cShow);
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK fVentana1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

	case WM_COMMAND: {

		if (LOWORD(wParam) == IDC_BUTTON3 && HIWORD(wParam) == BN_CLICKED) {
			HWND hListName = GetDlgItem(hwnd, IDC_LIST1);
			int indiceListbox = SendMessage(hListName, LB_GETCURSEL, NULL, NULL);
			int data = SendMessage(hListName, LB_GETITEMDATA, (WPARAM)indiceListbox, NULL);
			char intChar[3];
			_itoa(data, intChar, 10);
			MessageBox(NULL, "Dato de Fondo", intChar, MB_OK);

		}else if (LOWORD(wParam) == IDC_BUTTON2 && HIWORD(wParam) == BN_CLICKED) {
			HWND hComboName = GetDlgItem(hwnd, IDC_COMBO1);
			HWND hListName = GetDlgItem(hwnd, IDC_LIST1);
			int iComboLength = GetWindowTextLength(hComboName);
			char comboText[100];
			GetWindowText(hComboName, comboText, ++iComboLength);
			SendMessage(hListName,LB_ADDSTRING,NULL,(LPARAM)comboText);
			SendMessage(hListName, LB_SETITEMDATA, (WPARAM)indiceActual, (LPARAM)arregloIndices[indiceActual]);
			indiceActual++;
			
		}else if (LOWORD(wParam) == IDC_BUTTON1 && HIWORD(wParam) == BN_CLICKED) {
			//MessageBox(NULL, "Hola", "Funciono", MB_OK);
			HWND hName = GetDlgItem(hwnd, IDC_EDIT1);
			int iTextLength = GetWindowTextLength(hName);
			char name[100];
			GetWindowText(hName, name, iTextLength + 1);
			//MessageBox(NULL, name, "Texto vacio", MB_OK);

			HWND hComboName = GetDlgItem(hwnd, IDC_COMBO1);
			SendMessage(hComboName,CB_ADDSTRING,NULL,(LPARAM)name);
			SendMessage(hComboName, CB_SETCURSEL, (WPARAM)0, NULL);
			SetWindowText(hName,"");
			//if(iTextLength < 1)
				//MessageBox(NULL, "Ups", "Texto vacio", MB_OK);
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