/*##################################
Direct2D(수업용)
파일명: Driect2D.cpp (원본프로젝트 및 소스제공: http://vsts2010.tistory.com/) 
작성자: 김홍규 (downkhg@gmail.com)
마지막수정날짜: 2018.08.14
버전: 1.01
###################################*/


// Direct2D.cpp: 응용 프로그램의 진입점을 정의합니다.

#include "stdafx.h"
#include "DX2DClasses/Driect2DFramework.h"
#include "DX2DClasses/Vector2.h"
#include "DX2DClasses/ColorBrush.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/SceneManager.h"
#include "DX2DClasses/ColorBrushPalettet.h"
#include "DX2DClasses/DebugHelper.h"
#include "TestScene.h"
#include "MoveSampleScene.h"
#include "CollisionTestScene.h"
#include "GameScene.h"
#include "MemoryLeakTestScene.h"
#include "main.h"
#include <string.h>

using namespace DX2DClasses;

#define MAX_LOADSTRING 100
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_MARGIN_WIDHT 32 //타이틀 30, 외곽라인 2
#define WINDOW_MARGIN_HEIGHT 2 //외곽라인 2
#define RENDER_TARGET_WIDTH 800 //렌더타겟사이즈와 실 텍스처의 사이즈가 다름 이유 확인필요
#define RENDER_TARGET_HEIGHT 450
#define WINDOW_WIDTH RENDER_TARGET_WIDTH + WINDOW_MARGIN_WIDHT
#define WINDOW_HEIGTH RENDER_TARGET_HEIGHT + WINDOW_MARGIN_HEIGHT

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WindowProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Initialize(HWND hWnd); //초기화
void Update(); //
void Release();
void Draw();


CDriect2DFramwork g_cDX2DFramework;
ISceneManager* g_pGameManager;

void Initialize(HWND hWnd)
{
  
	g_cDX2DFramework.Initialize(hWnd, RENDER_TARGET_WIDTH, RENDER_TARGET_HEIGHT);
    //g_pGameManager = new CTestScene();
    //g_pGameManager = new CMoveSampleScene();
    //g_pGameManager = new CollisionTestScene();
    g_pGameManager = new CGameScene();
    //g_pGameManager = new CMemoryLeakTestScene();
    g_pGameManager->Initialize(hWnd, &g_cDX2DFramework);
	SetTimer(hWnd, 1, 60, NULL); //타이머 시작
}

void Release()
{
    if (g_pGameManager)
    {
        g_pGameManager->Release();
        delete g_pGameManager;
        g_pGameManager = NULL;
    }
	g_cDX2DFramework.Release();
}

void Update()
{
    if (g_pGameManager)
        g_pGameManager->Update();
}

void Draw()
{
	HRESULT hr = E_FAIL;
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Blue));

    if (g_pGameManager)
	    g_pGameManager->Draw();

	hr = pRenderTarget->EndDraw();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    //_CrtSetBreakAlloc(77); //메모리 누수시 번호를 넣으면 할당하는 위치에 브레이크 포인트를 건다.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //메모리 누수 검사 

	CDebugHelper::OpenConsole(); //콘솔화면 만들기

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DIRECT2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECT2D));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	Release();
	assert(hr == S_OK);
	CDebugHelper::CloseConsole(); //콘솔화면 끄기

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WindowProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECT2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGTH,
       nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

    switch (message)
    {
	case WM_CREATE:
	    {
		    Initialize(hWnd);
	    }
		break;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,FALSE); //타이머 호출시 마다, 윈도우영역을 초기화
		break;
	case WM_KEYDOWN:
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
		Update();
		hdc = BeginPaint(hWnd, &ps);
		Draw();
		EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

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