#include <windows.h>
#include <windowsx.h> // Static_SetText 等のマクロ用
#include "resource.h"
#include <string>

static const int WIN_WIDTH = 235;
static const int WIN_HEIGHT = 120;

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    TCHAR szAppName[] = L"ControlApp";
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    // ウィンドウクラスの属性を設定
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = 0;
    wc.lpszClassName = szAppName;

    // ウィンドウクラスを登録
    if (!RegisterClass(&wc)) return 0;

    // ウィンドウを作成
    hwnd = CreateWindow(
        szAppName, // ウィンドウクラス名
        L"コントロールの練習",
        WS_OVERLAPPEDWINDOW,
        50, 50, WIN_WIDTH, WIN_HEIGHT,
        NULL, NULL,
        hInstance, NULL);

    if (!hwnd) return 0;

    // ウィンドウを表示
    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hLabel;
    static HWND hEditBtn;
    static HWND hResetBtn;

    switch (uMsg) {
    case WM_CREATE:
        // テキスト静的コントロール
        // （文字を表示するコントロール）
        // https://learn.microsoft.com/ja-jp/windows/win32/controls/about-static-controls#text-static-control
        hLabel = CreateWindow(
            L"STATIC", // ウィンドウクラス名
            L"こんにちは", // テキスト
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 10, 200, 25,
            hwnd, // 親ウィンドウ
            NULL,
            ((LPCREATESTRUCT)(lParam))->hInstance,
            NULL
        );

        // ボタンコントロール（編集ボタン）
        // https://learn.microsoft.com/ja-jp/windows/win32/controls/create-a-button
        hEditBtn = CreateWindow(
            L"BUTTON", // ウィンドウクラス名
            L"編集", // テキスト
            // ボタンスタイル
            // https://learn.microsoft.com/ja-jp/windows/win32/controls/button-styles
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
            30, 40, 60, 25,
            hwnd, // 親ウィンドウ
            NULL,
            ((LPCREATESTRUCT)(lParam))->hInstance,
            NULL
        );

        // ボタンコントロール（リセットボタン）
        hResetBtn = CreateWindow(
            L"BUTTON", // ウィンドウクラス名
            L"リセット", // テキスト
            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            110, 40, 80, 25,
            hwnd, // 親ウィンドウ
            NULL,
            ((LPCREATESTRUCT)(lParam))->hInstance,
            NULL
        );
        return 0;
    case WM_COMMAND:
        if ((HWND)lParam == hResetBtn) {
            // コントロールに対する操作は3通り
            // 1) 関数
            SetWindowText(hLabel, L"");
            // 2) メッセージ
            // SendMessage(hLabel, WM_SETTEXT, 0, (LPARAM)L"");
            // 3) マクロ
            // Static_SetText(hLabel, L"");
        }
        else if ((HWND)lParam == hResetBtn) {
            // 編集ダイアログを開く
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}