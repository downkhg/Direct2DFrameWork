#include "GameManager.h"
#include "DX2DClasses/Driect2DFramework.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/ColorBush.h"
#include "DX2DClasses/Shape.h"
#include "DX2DClasses/Vector2.h"
#include "DX2DClasses/Image.h"
#include "DX2DClasses/InputManager.h"
#include "DX2DClasses/CollisionCheck.h"
#include <conio.h>

using namespace DX2DClasses;

CGameManager::CGameManager()
{
	//Initialize();
}

CGameManager::~CGameManager()
{
	Release();
}

void CGameManager::Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework)
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	m_pColorBrush = new CColorBrush();
	m_pColorBrush->CreateColorBrush(pRenderTarget, D2D1::ColorF(D2D1::ColorF::Black));
	ID2D1SolidColorBrush* pColorBlush = m_pColorBrush->GetColorBrush();
	m_pRedBrush = new CColorBrush();
	m_pRedBrush->CreateColorBrush(pRenderTarget, D2D1::ColorF(D2D1::ColorF::Red));

	m_pRect = new CRect();
	m_pCircle = new CCircle();
	m_pTriangle = new CTriangle();
	m_pPolygon = new CPolygon();
	
	m_pImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(),7);
	//m_pImage->m_pWICFactory = pDX2DFramework->GetImagingFactory();
	//m_pImage->m_pRenderTarget = pDX2DFramework->GetD2DRenderTarget();
	m_pImage->ManualLoadImage(hWnd, L"Images\\sonic_%04d.png");
}

void CGameManager::Release()
{
	delete m_pImage;

	delete m_pRedBrush;
	delete m_pColorBrush;
}

void CGameManager::Update()
{
	if (CInputManager::GetAsyncKeyStatePress(VK_RIGHT))
		m_vPos.x++;
	if (CInputManager::GetAsyncKeyStatePress(VK_LEFT))
		m_vPos.x--;
	if (CInputManager::GetAsyncKeyStatePress(VK_DOWN))
		m_vPos.y++;
	if (CInputManager::GetAsyncKeyStatePress(VK_UP))
		m_vPos.y--;
}

void CGameManager::Draw()
{
	static int nAniIdx = 0;

	SVector2 vScale(1,1);
	SVector2 vSize = m_pImage->GetImageSize();
	SVector2 vTL_A = vSize;
	SVector2 vBR_A = vTL_A + vSize;
	

	SVector2 vTL_B = m_vPos;
	SVector2 vBR_B = m_vPos + vSize;


	m_pImage->DrawBitmap(vTL_A, vScale, 0, nAniIdx, m_pColorBrush);
	m_pImage->DrawBitmap(m_vPos, vScale, 0, nAniIdx,m_pColorBrush);

	ID2D1RenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	ID2D1SolidColorBrush* pRedBrush = m_pRedBrush->GetColorBrush();
	ID2D1SolidColorBrush* pBlackBrush = m_pColorBrush->GetColorBrush();
	if (CCollisionCheck::OverlapAABBtoAABB(vTL_A, vBR_A, vTL_B, vBR_B))
	{
		_cprintf("A: %s,", vTL_A.GetChar());
		_cprintf("%s\n", vBR_A.GetChar());
		_cprintf("B: %s,", vTL_B.GetChar());
		_cprintf("%s\n", vBR_B.GetChar());
		
		pRenderTarget->DrawRectangle(D2D1::RectF(vTL_A.x, vTL_A.y, vBR_A.x, vBR_A.y), pRedBrush,1);
		pRenderTarget->DrawRectangle(D2D1::RectF(vTL_B.x, vTL_B.y, vBR_B.x, vBR_B.y), pRedBrush, 1);
	}
	else
	{
		pRenderTarget->DrawRectangle(D2D1::RectF(vTL_A.x, vTL_A.y, vBR_A.x, vBR_A.y), pBlackBrush, 1);
		pRenderTarget->DrawRectangle(D2D1::RectF(vTL_B.x, vTL_B.y, vBR_B.x, vBR_B.y), pBlackBrush, 1);
	}

	if (nAniIdx < 6)
		nAniIdx++;
	else
		nAniIdx = 0;
}