#include<windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{

	//Register the window class
	const wchar_t CLASS_NAME[] = L"Text Editor Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,							//Optional window styles
		CLASS_NAME,					//Window Class
		L"Text Editor",				//Window Text
		WS_OVERLAPPEDWINDOW,		//Window Style

		//Size and Position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,			//Parent Window
		NULL,			//Menu
		hInstance,		//Instance handle
		NULL			//Additional application data

		);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);


	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		//rcPaint has the update region for painting
		FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);

	}
	return 0;					// return 0 to indicate message is handled
	case WM_CLOSE:
	{
		if (MessageBox(hwnd, L"Really Quit?", L"My Application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
	}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
