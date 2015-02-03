// AutoKey.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "AutoKey.h"
#include "stdio.h"

#define MAX_LOADSTRING 100

#define AUTO_KEY_TIMER_ID 999

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名


TCHAR szTargetWindowTitle[MAX_LOADSTRING];			// 目标窗口标题
bool isTimerStart;

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	TimerDialgProc(HWND, UINT, WPARAM, LPARAM);
void StartAutoKey(HWND hWnd);
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_AUTOKEY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AUTOKEY));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AUTOKEY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_AUTOKEY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			
		case ID_START_TIMER_AUTO_KEY:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_TIMER), hWnd, TimerDialgProc);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
		
	case WM_KEYDOWN:
		 if(wParam ==VK_SNAPSHOT)
		 {
			 int a = wParam;
		 }
		break;
	case WM_KEYUP:
		 if(wParam ==VK_SNAPSHOT)
		 {
			 int a = wParam;
		 }
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime )
{
	HWND otherHwnd=FindWindow(0,szTargetWindowTitle);
	if(otherHwnd == NULL)
	{
		::MessageBox( NULL, _T("无法找到该窗口，窗口可能已经关闭，请重新打开该窗口。"), _T("错误"), MB_OK );
		KillTimer(hwnd,AUTO_KEY_TIMER_ID);
		return ;
	}
	PostMessage(otherHwnd,WM_KEYDOWN,VK_PAUSE,0);
	
	//HWND otherHwnd=FindWindow(0,TEXT("123.txt - 记事本"));
	//PostMessage(otherHwnd,WM_KEYDOWN,VK_F1,0);
	//SendMessage(otherHwnd,VK_F1,0,0);

	//keybd_event(VK_SNAPSHOT,0,0,0);
	//keybd_event(VK_PAUSE,0,0,0);
	//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
}

void StartAutoKey(HWND hWnd,int interval)
{
	SetTimer(hWnd,AUTO_KEY_TIMER_ID,interval,(TIMERPROC)TimerProc);
}


// “定时”框的消息处理程序。
INT_PTR CALLBACK TimerDialgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			HWND hWndEditTargetWndTitle1 = ::GetDlgItem(hDlg,IDC_EDIT_TAGET_WND_TITLE);
			SetWindowText(hWndEditTargetWndTitle1,TEXT("百区.1.908.风v云."));
			
			HWND hWndEditHour1 = ::GetDlgItem(hDlg,IDC_EDIT_HOUR);
			SetWindowText(hWndEditHour1,TEXT("0"));
			
			HWND hWndEditMin1 = ::GetDlgItem(hDlg,IDC_EDIT_MINUTE);
			SetWindowText(hWndEditMin1,TEXT("30"));

			HWND hWndEditSecond1 = ::GetDlgItem(hDlg,IDC_EDIT_SECOND);
			SetWindowText(hWndEditSecond1,TEXT("0"));

			isTimerStart = false;
			return (INT_PTR)TRUE;
		}
		
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{
			if(isTimerStart == false)
			{
				char sztextC[8];
				int len = sizeof(sztextC);
				char c_str[8];
				memset(sztextC,0,len);
				memset(c_str,0,sizeof(c_str));
				//小时
				HWND hWndEditHour = ::GetDlgItem(hDlg,IDC_EDIT_HOUR);
				GetWindowText(hWndEditHour,(LPWSTR)sztextC,4);
				 WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)sztextC, -1, c_str, len, NULL,NULL);
				int hour = atoi(c_str);
			
				memset(sztextC,0,sizeof(sztextC));
				memset(c_str,0,sizeof(c_str));
				//分钟
				HWND hWndEditMin = ::GetDlgItem(hDlg,IDC_EDIT_MINUTE);
				GetWindowText(hWndEditMin,(LPWSTR)sztextC,4);
				 WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)sztextC, -1, c_str, len, NULL,NULL);
				int minute = atoi(c_str);
			
				memset(sztextC,0,sizeof(sztextC));
				memset(c_str,0,sizeof(c_str));
				//秒
				HWND hWndEditSecond = ::GetDlgItem(hDlg,IDC_EDIT_SECOND);
				GetWindowText(hWndEditSecond,(LPWSTR)sztextC,4);
				 WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)sztextC, -1, c_str, len, NULL,NULL);
				int second = atoi(c_str);

				int interval = ((hour * 60 * 60) + (minute * 60) +second) * 1000;

				if(interval == 0)
				{
					::MessageBox( NULL, _T("请输入正确的时间（1,2,3,4....n）。"), _T("错误"), MB_OK );
					return (INT_PTR)TRUE;
				}
				memset(szTargetWindowTitle,0,sizeof(szTargetWindowTitle));
			
				//目标窗口标题
				HWND hWndEditTargetWndTitle = ::GetDlgItem(hDlg,IDC_EDIT_TAGET_WND_TITLE);
				GetWindowText(hWndEditTargetWndTitle,(LPWSTR)szTargetWindowTitle,sizeof(szTargetWindowTitle));
			
				HWND otherHwnd=FindWindow(0,szTargetWindowTitle);
	
				if(otherHwnd == NULL)
				{
					::MessageBox( NULL, _T("无法找到该窗口，请确认后重新输入。"), _T("错误"), MB_OK );
					KillTimer(hDlg,AUTO_KEY_TIMER_ID);
					return (INT_PTR)TRUE;
				}

				StartAutoKey(hDlg,interval);

				isTimerStart = true;
				HWND hWndOKBtn = ::GetDlgItem(hDlg,IDOK);
				SetWindowText(hWndOKBtn,TEXT("取消"));
			}
			else
			{
				isTimerStart = false;
				KillTimer(hDlg,AUTO_KEY_TIMER_ID);

				HWND hWndOKBtn = ::GetDlgItem(hDlg,IDOK);
				SetWindowText(hWndOKBtn,TEXT("确定"));
			}
			

			return (INT_PTR)TRUE;
		}
		if ( LOWORD(wParam) == IDCANCEL)
		{
			KillTimer(hDlg,AUTO_KEY_TIMER_ID);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		
		break;
	}
	return (INT_PTR)FALSE;
}
