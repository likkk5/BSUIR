//������� ���� � ������ ��� ���� � ����������� �� �������� �������� ��������� ����������.
//���� ���� ����������� � ������� � ����������������� ��� ��������� ������� ���������.
#include <Windows.h>
#include <string>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SetBackgroundColor(HWND hwnd, COLORREF color);
COLORREF GetStoredColor();
void StoreColor(COLORREF color);
COLORREF reg_color = RGB(0, 255, 0);//������� �� ���������
LANGID langId;//������� ���������
const wchar_t CLASS_NAME[] = L"LanguageColorChangeWindow";
const wchar_t REGISTRY_KEY[] = L"Software\\LanguageColorChangeApp"; // ���� � ����� � ������� Windows
const wchar_t REGISTRY_VALUE[] = L"BackgroundColor"; // ��� �������� � �������

//����� ����� � ���������. ������� ���� � ��������� ���� ��������� ���������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Language Color Change",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (hwnd == NULL) {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}
//������� ��������� ��������� ����
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        SetTimer(hwnd, 1, 1000, NULL);
        StoreColor(reg_color);//c�������� ������� ���� � ������ Windows.
        break;
    case WM_TIMER:
        langId = LOWORD(GetKeyboardLayout(0));
        COLORREF backgroundColor;
        if (langId == 0x0409) {  // ����������
            backgroundColor = RGB(255, 0, 0);  // �������
        }
        else if (langId == 0x0419) {  // �������
            backgroundColor = RGB(0, 0, 255);  // �����
        }
        else {
            backgroundColor = GetStoredColor();  // ���� �� ���������,������ ����������� ���� �� ������� Windows.
        }
        SetBackgroundColor(hwnd, backgroundColor);
        break;
    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
//������ ���� ���� ����
void SetBackgroundColor(HWND hwnd, COLORREF color) {
    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(color));//������ ��� ���� �� ����� ����.
    InvalidateRect(hwnd, NULL, TRUE);//�������������� ���� � ����� ������
}
//������ ����������� ���� �� ������� Windows, ���� ��� �� ����� �� ���������
COLORREF GetStoredColor() {
    HKEY hKey;
    COLORREF color = GetSysColor(COLOR_BTNFACE);
    // ������� ���� ������� ��� ������
    if (RegOpenKeyEx(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD dataSize = sizeof(color);
        // �������� �������� ����� �� �������
        RegQueryValueEx(hKey, REGISTRY_VALUE, nullptr, nullptr, reinterpret_cast<LPBYTE>(&color), &dataSize);
        // ������� ���� �������
        RegCloseKey(hKey);
    }
    return color;
}
//��������� ������� ���� � ������ Windows.
void StoreColor(COLORREF color) {
    HKEY hKey;
    // ������� ��� ������� ���� ������� ��� ������
    if (RegCreateKeyEx(HKEY_CURRENT_USER, REGISTRY_KEY, 0, nullptr, 0, KEY_WRITE, nullptr, &hKey, nullptr) == ERROR_SUCCESS) {
        DWORD dwData = color;
        // �������� �������� ����� � ������
        RegSetValueEx(hKey, REGISTRY_VALUE, 0, REG_DWORD, reinterpret_cast<BYTE*>(&dwData), sizeof(dwData));
        // ������� ���� �������
        RegCloseKey(hKey);
    }
}
