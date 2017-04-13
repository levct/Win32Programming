#include <Windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // ���ڹ���

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Hello World"); // ���ڱ���
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW; // windows���
	wndclass.lpfnWndProc = WndProc; // ���ô��ڹ���
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // LoadIcon:����ͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // LoadCursor:���ع��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // GetStockObject����ȡһ��ͼ�ζ��������Դ��ڱ��������ػ�Ļ�ˢ
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass)) // RegisterClass��ΪӦ�ó���Ĵ���ע��һ��������
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
	}

	// CreateWindow�����ڴ����ഴ��һ������
	hwnd = CreateWindow(szAppName, TEXT("This hello program"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow); // ����Ļ����ʾ����
	UpdateWindow(hwnd); // ָʹ���ڶ�����������ػ�
	while (GetMessage(&msg, NULL, 0, 0)) // GetMessage������Ϣ�����л�ȡ��Ϣ
	{
		TranslateMessage(&msg); // ���������Ϣ
		DispatchMessage(&msg); // ����Ϣ���͸����ڹ���
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
	return DefWindowProc(hwnd, message, wParam, lParam); // ִ��Ĭ�ϵ���Ϣ����;
};