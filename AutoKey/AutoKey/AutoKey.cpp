// AutoKey.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "AutoKey.h"
#include "stdio.h"

#define MAX_LOADSTRING 100

#define AUTO_KEY_TIMER_ID 999

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������


TCHAR szTargetWindowTitle[MAX_LOADSTRING];			// Ŀ�괰�ڱ���
bool isTimerStart;

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_AUTOKEY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AUTOKEY));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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
		::MessageBox( NULL, _T("�޷��ҵ��ô��ڣ����ڿ����Ѿ��رգ������´򿪸ô��ڡ�"), _T("����"), MB_OK );
		KillTimer(hwnd,AUTO_KEY_TIMER_ID);
		return ;
	}
	PostMessage(otherHwnd,WM_KEYDOWN,VK_PAUSE,0);
	
	//HWND otherHwnd=FindWindow(0,TEXT("123.txt - ���±�"));
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


// ����ʱ�������Ϣ�������
INT_PTR CALLBACK TimerDialgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			HWND hWndEditTargetWndTitle1 = ::GetDlgItem(hDlg,IDC_EDIT_TAGET_WND_TITLE);
			SetWindowText(hWndEditTargetWndTitle1,TEXT("����.1.908.��v��."));
			
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
				char sztextC[4];
				memset(sztextC,0,sizeof(sztextC));
				//Сʱ
				HWND hWndEditHour = ::GetDlgItem(hDlg,IDC_EDIT_HOUR);
				GetWindowText(hWndEditHour,(LPWSTR)sztextC,4);
				int hour = atoi(sztextC);
			
				memset(sztextC,0,sizeof(sztextC));
				//����
				HWND hWndEditMin = ::GetDlgItem(hDlg,IDC_EDIT_MINUTE);
				GetWindowText(hWndEditMin,(LPWSTR)sztextC,4);
				int minute = atoi(sztextC);
			
				memset(sztextC,0,sizeof(sztextC));
				//��
				HWND hWndEditSecond = ::GetDlgItem(hDlg,IDC_EDIT_SECOND);
				GetWindowText(hWndEditSecond,(LPWSTR)sztextC,4);
				int second = atoi(sztextC);

				int interval = ((hour * 60 * 60) + (minute * 60) +second) * 1000;

				if(interval == 0)
				{
					::MessageBox( NULL, _T("��������ȷ��ʱ�䣨1,2,3,4....n����"), _T("����"), MB_OK );
					return (INT_PTR)TRUE;
				}
				memset(szTargetWindowTitle,0,sizeof(szTargetWindowTitle));
			
				//Ŀ�괰�ڱ���
				HWND hWndEditTargetWndTitle = ::GetDlgItem(hDlg,IDC_EDIT_TAGET_WND_TITLE);
				GetWindowText(hWndEditTargetWndTitle,(LPWSTR)szTargetWindowTitle,sizeof(szTargetWindowTitle));
			
				HWND otherHwnd=FindWindow(0,szTargetWindowTitle);
	
				if(otherHwnd == NULL)
				{
					::MessageBox( NULL, _T("�޷��ҵ��ô��ڣ���ȷ�Ϻ��������롣"), _T("����"), MB_OK );
					KillTimer(hDlg,AUTO_KEY_TIMER_ID);
					return (INT_PTR)TRUE;
				}

				StartAutoKey(hDlg,interval);

				isTimerStart = true;
				HWND hWndOKBtn = ::GetDlgItem(hDlg,IDOK);
				SetWindowText(hWndOKBtn,TEXT("ȡ��"));
			}
			else
			{
				isTimerStart = false;
				KillTimer(hDlg,AUTO_KEY_TIMER_ID);

				HWND hWndOKBtn = ::GetDlgItem(hDlg,IDOK);
				SetWindowText(hWndOKBtn,TEXT("ȷ��"));
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
