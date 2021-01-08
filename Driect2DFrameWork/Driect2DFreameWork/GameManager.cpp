#include "GameManager.h"
#include "DX2DClasses/Driect2DFramework.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/ColorBrush.h"
#include "DX2DClasses/Shape.h"
#include "DX2DClasses/Vector2.h"
#include "DX2DClasses/Image.h"
#include "DX2DClasses/InputManager.h"
#include "DX2DClasses/CollisionCheck.h"
#include "DX2DClasses/ColorBrushPalettet.h"
#include "DX2DClasses/DebugHelper.h"
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

	m_pColorBrushPalettet = new CColorBrushPalettet();
	m_pColorBrushPalettet->Initialize(pRenderTarget);
	
	m_pPlayer= new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(),6);
	m_pPlayer->ManualLoadImage(hWnd, L"Images\\player%02d.png");

	m_pOpossum = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	m_pOpossum->ManualLoadImage(hWnd, L"Images\\opossum%02d.png");

	m_pEagle = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	m_pEagle->ManualLoadImage(hWnd, L"Images\\eagle%02d.png");

	m_pCherry = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	m_pCherry->ManualLoadImage(hWnd, L"Images\\cherry%02d.png");

	m_pGem = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 5);
	m_pGem->ManualLoadImage(hWnd, L"Images\\gem%02d.png");

	m_pItemEffect = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	m_pItemEffect->ManualLoadImage(hWnd, L"Images\\itemeffect%02d.png");

	m_pDeathEffect = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	m_pDeathEffect->ManualLoadImage(hWnd, L"Images\\death%02d.png");
}

void CGameManager::Release()
{
	delete m_pDeathEffect;
	delete m_pItemEffect;
	delete m_pGem;
	delete m_pCherry;
	delete m_pEagle;
	delete m_pOpossum;
	delete m_pPlayer;

	delete m_pColorBrushPalettet;
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
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	static int nAniIdx = 0;

	SVector2 vScale(1,1);
	SVector2 vSize = m_pPlayer->GetImageSize();
	SVector2 vTL_A = vSize;
	SVector2 vBR_A = vTL_A + vSize;
	

	SVector2 vTL_B = m_vPos;
	SVector2 vBR_B = m_vPos + vSize;


	m_pPlayer->DrawBitmap(vTL_A, vScale, 0, nAniIdx);
	m_pPlayer->DrawBitmap(m_vPos, vScale, 0, nAniIdx);

	m_pOpossum->DrawBitmap(SVector2(), vScale, 0, 0);

	
	CColorBrush* pRedBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::RED);
	CColorBrush* pBlackBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::BLACK);

	if (CCollisionCheck::OverlapAABBtoAABB(vTL_A, vBR_A, vTL_B, vBR_B))
	{
		CDebugHelper::LogConsole("A: %s,", vTL_A.GetChar());
		CDebugHelper::LogConsole("%s\n", vBR_A.GetChar());
		CDebugHelper::LogConsole("B: %s,", vTL_B.GetChar());
		CDebugHelper::LogConsole("%s\n", vBR_B.GetChar());

		CDebugHelper::DrawRect(vTL_A, vBR_A, pRedBrush);
		CDebugHelper::DrawRect(vTL_B, vBR_B, pRedBrush);
	}
	else
	{
		CDebugHelper::DrawRect(vTL_A, vBR_A, pBlackBrush);
		CDebugHelper::DrawRect(vTL_B, vBR_B, pBlackBrush);
	}

	if (nAniIdx < m_pPlayer->GetAnimationCount() - 1)
		nAniIdx++;
	else
		nAniIdx = 0;
}