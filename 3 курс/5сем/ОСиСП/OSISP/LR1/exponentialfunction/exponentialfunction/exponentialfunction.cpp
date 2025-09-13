// ������������� ���������� ������ �������
// ������ ����� ��������� ������ �������� ���������� ��� ��������� ������������� ����� �. 
// ������ ��������� ���������� ���������� ���� �� ����� � � ������ ��������� ���������� �������� ���������� ���������� (����������� ����), �� ������ ���������� ������ �������.
//���������� ������������ ���� �� ����� ���������� ���� ������
#include <windows.h>
#include <tchar.h>
#include <cmath>
#include <vector>
#include <thread>
#include <string>
#include <atomic>
std::vector<std::thread> threads; //������ �������, � ������� ����� ����������� ���������� ����������
double result = 0.0; //���������� ��� �������� �������� ���������� ���������� ����������
double inputX = 0.0;  // ��������� ��� �������� ���������� �������� x
HANDLE mutex; //������ �������� ��� ������������� ������� � ����������� �������� (��������, � ����������)
std::atomic<bool> exitFlag(false); //��������� ����������, ������������ ��� ���������� ������ �������.
std::vector<double> inputPoints; //������, ������� ������ ��������� ������������� �������� x
double previousResult = 0.0; // ���������� ��� ������������ ����������� ����������

//������� ������, ������� ��������� �� ���� �������� x, ����������� ���� ����� � ��������� ����, ��������� �, 
//��������� �������� � result, ���� ��� ���������� �� �����������, �� ���� ����� �����������
//�������� � ����������� ����� �� ��� ���, ���� �� ���������� ���� ���������� exitFlag
void CalculateExponential(double x, HWND hInputEdit, HWND hWnd) {
    while (true) {
        // ����������� �������
        WaitForSingleObject(mutex, INFINITE);
        // ��������� ���� ����������
        if (exitFlag) {
            ReleaseMutex(mutex);
            break;
        }
        // �������� ������ ��������
        result = exp(x);
        // ��������� ��������� �������� x
        inputX = x;
        // ��������� ��������� �������� x
        inputPoints.push_back(x);
        // ���������� ��������� ��� ��������� ������ � ���� ����� ������ ��� ��������� ����������
        if (result != previousResult) {
            previousResult = result;
            // ��������� ����� � ���� �����
            SetWindowText(hInputEdit, std::to_wstring(result).c_str());
            // �������������� ����
            InvalidateRect(hWnd, NULL, TRUE);
        }
        // ����������� �������
        ReleaseMutex(mutex);
        // ���� ������� �������, ����� ���������� ������ ��������� ����� ��������� ���������
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}
//������� ��������� ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
 //��� ������� �� ������, ��������� �������� ��������� ������������� �������� � ��������� ����� ��� ���������� ����������.
    case WM_COMMAND: 
        if (HIWORD(wParam) == BN_CLICKED) {
            if (LOWORD(wParam) == 1) {
                // �������� �������� �� ���� ��� �����
                TCHAR buffer[256];
                GetWindowText(GetDlgItem(hWnd, 0), buffer, sizeof(buffer) / sizeof(buffer[0]));
                double x = _ttof(buffer);
                //// ��������� ������ ��� ����������
                //threads.emplace_back(CalculateExponential, x, GetDlgItem(hWnd, 0), hWnd);
                // 
                // ��������� ����� ����� ��� ���������� ����������
                std::thread newThread(CalculateExponential, x, GetDlgItem(hWnd, 0), hWnd);

                // �������� ���������� ������ � ������������� ���������
                HANDLE hThread = newThread.native_handle();
                SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);

                threads.push_back(std::move(newThread)); // ��������� �����
            }
        }
        break;
//��� �������� ���� ��������������� ���� ���������� ��� �������, � ��� ��������� �����������. ����������� �������
    case WM_DESTROY: 
        // ������������� ���� ����������
        exitFlag.store(true);
        // ���� ���������� �������
        for (std::thread& t : threads) {
            t.join();
        }
        // ��������� ���������� ��������
        CloseHandle(mutex);
        // ��������� ���������
        PostQuitMessage(0);
        break;
//�������� �� ��������� ���� � ������� �������. ����� �������� ������ ���������� � �������� ������������� �����
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // �������� ������� ���������� ������� ����
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        // ������� ������� ���� ��� ��������� �����
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        HGDIOBJ hOldPen = SelectObject(hdc, hPen);
        // ������ ������ ����������
        MoveToEx(hdc, 0, clientRect.bottom, NULL);
        for (int i = 0; i < clientRect.right; ++i) {
            double x = static_cast<double>(i);
            double y = exp(x / 50.0) * 50.0;  // ���������������� �������, ���������������� ��� ������ ���������
            LineTo(hdc, i, clientRect.bottom - static_cast<int>(y));
        }
        // ������ ����� ��������� ��������
        for (double x : inputPoints) {
            Ellipse(hdc, static_cast<int>(x), clientRect.bottom - static_cast<int>(exp(x / 50.0) * 50.0),
                static_cast<int>(x) + 5, clientRect.bottom - static_cast<int>(exp(x / 50.0) * 50.0) + 5);
        }
        // ������� �������
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
        EndPaint(hWnd, &ps);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
//����� ����� � ���������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    const TCHAR szWindowClass[] = _T("Win32App");
    WNDCLASSEX wcex;//����������� ����
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Win32 Guided Tour"), NULL);
        return 1;
    }
    // �������� ����
    HWND hWnd = CreateWindow(szWindowClass, _T("Exponential function"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (!hWnd) {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL);
        return 1;
    }
    // �������� ��������
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        MessageBox(NULL, _T("Mutex creation failed."), _T("Error"), NULL);
        return 1;
    }
    // ������� ���� ��� �����
    HWND hEdit = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        10, 10, 100, 20, hWnd, NULL, hInstance, NULL);
    // ������� ������
    HWND hButton = CreateWindow(_T("BUTTON"), _T("Calculate"), WS_CHILD | WS_VISIBLE,
        120, 10, 80, 20, hWnd, (HMENU)1, hInstance, NULL);
    // ����������� ����
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    // ���� ��������� ���������
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
//mutex-������������� �������� ��� ������������� ������� � ���������� ���������� ����������� ��������.�������������� ������