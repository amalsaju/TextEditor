#include<windows.h>

#define BUFSIZE 65535
#define SHIFTED 0x8000

LONG APIENTRY MainWindowProc(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;					// handle to device context
	TEXTMETRIC tm;				// structure for text metrics
	static DWORD dwCharX;		// average width of characters
	static DWORD dwCharY;		// height of characters
	static DWORD dwClientX;		// width of client area
	static DWORD dwClientY;		// height of client area
	static DWORD dwLineLen;		// line length
	static DWORD dwLines;		// text lines in client area
	static int nCaretPosX = 0;	// horizontal position of caret
	static int nCaretPosY = 0;	// veritical postiion of caret
	static int nCharWidth = 0;	// width of a character
	static int cch = 0;			// characters in buffer
	static int nCurChar = 0;	// index of current character
	static PTCHAR pchInputBuf;	// input buffer
	int i, j;					// loop counter
	int cCR = 0;				// count of carriage returns
	int nCRIndex = 0;			// index of last carriage return
	int nVirtKey;				// virtual-key code
	TCHAR szBuf[128];			// temporary buffer
	TCHAR ch;					// current character
	PAINTSTRUCT  ps;			// required by BeginPaint
	RECT rc;					//output rectangle for DrawText
	SIZE sz;					// string dimensions
	COLORREF crPrevText;		// previous text color
	COLORREF crPrevBk;			// previous background color
	size_t* pcch;
	HRESULT hResult;
	
	switch (uMsg)
	{
	case WM_CREATE:

			// Get the metrics of the current font

			hdc = GetDC(hwndMain);
			GetTextMetrics(hdc, &tm);
			ReleaseDC(hwndMain, hdc);

			//Save the average character width and height

			dwCharX = tm.tmAveCharWidth;
			dwCharY = tm.tmHeight;

			//Allocate a buffer to store keyboard input

			pchInputBuf = (LPTSTR)GlobalAlloc(GPTR,
				BUFSIZE * sizeof(TCHAR));
			return 0;

	case WM_SIZE:

		//save the new widht and height of the client area

		dwClientX = LOWORD(lParam);
		dwClientY = HIWORD(lParam);

		// Calculate the maximum width of a line and the
		// maximum number of lines in the client area

		dwLineLen = dwClientX = dwCharX;
		dwLines = dwClientY / dwCharY;
		break;


	}

}

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
