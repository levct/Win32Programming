#include <Windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // 窗口过程

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Hello World"); // 窗口标题
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW; // windows风格
	wndclass.lpfnWndProc = WndProc; // 调用窗口过程
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // LoadIcon:加载图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // LoadCursor:加载光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // GetStockObject：获取一个图形对象，用来对窗口背景进行重绘的画刷
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass)) // RegisterClass：为应用程序的窗口注册一个窗口类
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
	}

	// CreateWindow：基于窗口类创建一个窗口
	hwnd = CreateWindow(szAppName, TEXT("This hello program"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow); // 在屏幕中显示窗口
	UpdateWindow(hwnd); // 指使窗口对其自身进行重绘
	while (GetMessage(&msg, NULL, 0, 0)) // GetMessage：从消息队列中获取消息
	{
		TranslateMessage(&msg); // 翻译键盘消息
		DispatchMessage(&msg); // 将消息发送给窗口过程
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT point;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	TCHAR text[] = L"hello world";
	std::string pos = "pos";
	switch (message)
	{
	case WM_PAINT:
		GetCursorPos(&point);
		ScreenToClient(hwnd, &point);
		GetClientRect(hwnd, &rect);

		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, rect.left, rect.top, text, ARRAYSIZE(text));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam); // 执行默认的消息处理;
};