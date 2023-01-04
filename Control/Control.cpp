#include <windows.h>
#include <windowsx.h> // Static_SetText 等のマクロ用
#include "resource.h"
#include <string>

static const int WIN_WIDTH = 235;
static const int WIN_HEIGHT = 120;

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

std::wstring strEdit;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    TCHAR szAppName[] = L"ControlApp";
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    hInst = hInstance;

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
        L"Control", // タイトル文字
        WS_OVERLAPPEDWINDOW,
        50, 50, WIN_WIDTH, WIN_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);

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
    static HWND hClearBtn;

    switch (uMsg) {
    case WM_CREATE:
        // https://learn.microsoft.com/ja-jp/windows/win32/controls/create-a-button
        // ボタンコントロール（編集ボタン）
        hEditBtn = CreateWindow(
            L"BUTTON", // ウィンドウクラス名
            L"編集", // ボタン文字
            WS_CHILD | WS_VISIBLE,
            30, 40, 60, 25,
            hwnd, // 親ウィンドウ
            NULL,
            hInst,
            NULL
        );

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
            hInst,
            NULL
        );

        // ボタンコントロール（クリアボタン）
        hClearBtn = CreateWindow(
            L"BUTTON", // ウィンドウクラス名
            L"Label", // テキスト
            WS_CHILD | WS_VISIBLE,
            0, 0, 40, 30,
            hwnd, // 親ウィンドウ
            NULL,
            hInst,
            NULL
        );

        return 0;
    case WM_COMMAND:
        if ((HWND)lParam == hClearBtn) {
            // コントロールに対する操作は3通り
            // 1) メッセージ
            SendMessage(hLabel, WM_SETTEXT, 0, (LPARAM)L"");
            // 2) 関数
            // SetWindowText(hLabel, L"");
            // 3) マクロ
            // Static_SetText(hLabel, L"");
        }
        else if ((HWND)lParam == hEditBtn) {
            // 編集ダイアログを開く
            /*
            INT_PTR result = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)MyDlgProc);
            if (result == IDOK) {
                SetWindowText(hLabel, strEdit.c_str());
            }
            */
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
// ダイアログプロシージャ
/*
INT_PTR CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    wchar_t wcEdit[128] = { 0 };
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK: 
            GetDlgItemText(hDlg, IDC_EDIT1, wcEdit, wcslen(wcEdit) - 1);
            EndDialog(hDlg, IDOK);
            strEdit = wcEdit;
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
*/