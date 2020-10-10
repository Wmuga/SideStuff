#include <windows.h>


HINSTANCE hInst;
HWND    hwnd;
HWND    hBtn;
HWND    hBtn2;
HWND    hwnd_c;
bool isMain = true;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//функция регистрации класса окон
BOOL RegClass(WNDPROC Proc, LPCTSTR szName, UINT brBackground)
{
    WNDCLASS wcex;
    wcex.style = wcex.cbClsExtra = wcex.cbWndExtra = 0;
    wcex.lpfnWndProc = Proc;
    wcex.hInstance = hInst;
    //wcex.hIcon=LoadIcon(NULL,MAKEINTRESOURCE(IDI_ICON1));
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szName;
    return (RegisterClass(&wcex) != 0);
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    MSG msg;
    hInst = hInstance;
    if (!RegClass(WndProc, "WinAPI Form", COLOR_WINDOW))
        return FALSE;


    hwnd = CreateWindowEx(0, "WinAPI Form", "WinAPI Test", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
                          0, 0,
                          300, 300, nullptr, nullptr, hInstance, nullptr);


    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
            if (isMain) PostQuitMessage(0);
            else isMain = true;
            return 0;
        case WM_CREATE:

            hBtn  = CreateWindowEx(0,"button", "Button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 10, 70, 30, hwnd, (HMENU)10999, hInst, nullptr);
            hBtn2 = CreateWindowEx(0,"button","Button2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 90, 10 ,70, 30, hwnd, (HMENU)11000, hInst, nullptr);

            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case 10999:
                    RegClass(WndProc,"WinApi Form 2",COLOR_WINDOW);
                    if (!hwnd_c) hwnd_c = CreateWindowEx(0,"WinApi Form 2","WinApi Pop Up", WS_OVERLAPPED | WS_VISIBLE,10,10,300,300,hwnd,nullptr,hInst,nullptr);
                    ShowWindow(hwnd_c,SW_SHOWNORMAL);
                    break;
                case 11000:
                    if (hwnd_c){isMain = false; DestroyWindow(hwnd_c); hwnd_c = nullptr; }
            }
            break;

    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}