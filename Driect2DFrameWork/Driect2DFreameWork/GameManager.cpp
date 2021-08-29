#include "GameManager.h"
#include "DX2DClasses/Driect2DFramework.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/ColorBrush.h"
#include "DX2DClasses/Vector2.h"
#include "DX2DClasses/Image.h"
#include "DX2DClasses/InputManager.h"
#include "DX2DClasses/CollisionCheck.h"
#include "DX2DClasses/ColorBrushPalettet.h"
#include "DX2DClasses/DebugHelper.h"
#include "DX2DClasses/GameObject.h"
#include <conio.h>

using namespace DX2DClasses;

CGameManager::CGameManager()
{
	//Initialize();
}

CGameManager::~CGameManager()
{
	//Release();
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

	m_pPlayerObject = new CGameObject();
	m_pPlayerObject->Initialize(m_pPlayer, true);
}

void CGameManager::Release()
{
	m_pPlayerObject->Release();
	delete m_pPlayerObject;

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
	//static CAnimator2D cAnimator(m_pPlayer->GetAnimationCount());
	static float fAngle = 0;

	SVector2 vScale(1,1);
	SVector2 vSize = m_pPlayer->GetImageSize();
	SVector2 vTL_A = vSize;
	SVector2 vBR_A = vTL_A + vSize;
	SVector2 vTR_A(vBR_A.x, vTL_A.y);
	SVector2 vBL_A(vTL_A.x, vBR_A.y);

	SVector2 vTL_B;
	//SVector2 vTL_B = m_vPos;
	SVector2 vBR_B = vTL_B + vSize;
	SVector2 vTR_B(vBR_B.x, vTL_B.y);
	SVector2 vBL_B(vTL_B.x, vBR_B.y);

	CTransform& cTrnasform = m_pPlayerObject->GetTransform();

	cTrnasform.SetTransrate(m_vPos);
	SVector2 vAsix = vSize * 0.5f;
	//vAsix = m_vPos + vAsix;
	cTrnasform.SetAsixPoint(vAsix);
	cTrnasform.SetTRS(m_vPos, fAngle, vScale);
	//cTrnasform.Rotate(fAngle);
	//cTrnasform.Scale(SVector2(2, 2));
	

	m_pPlayer->DrawBitmap(vTL_A, vScale, 0, nAniIdx);
	m_pPlayer->DrawBitmap(m_vPos, vScale, 0, nAniIdx);
	m_pPlayer->DrawBitmap(cTrnasform.GetTransfrom(), nAniIdx);
	//cAnimator.DrawImage(m_pPlayer, cTrnasform);
	m_pPlayerObject->Draw();
	m_pOpossum->DrawBitmap(SVector2(), vScale, 0, 0);

	//cAnimator.UpdateFrame();
	m_pPlayerObject->Update();
	CColorBrush* pRedBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::RED);
	CColorBrush* pGreenBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::GREEN);
	CColorBrush* pYellowBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::YELLOW);
	CColorBrush* pBlackBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::BLACK);
	
	SVector2 vCirclePos = vTL_A + vAsix;
	float fCircleRadius = 10;
	SVector2 rect[] = { vTL_B, vTR_B, vBR_B, vBL_B };
	for (int i = 0; i < 4; i++)
		rect[i] = CTransform::MutipleVectorToMatrix(rect[i], cTrnasform.GetTransfrom());
	if (CCollisionCheck::OverlapCircleToOBB(vCirclePos, fCircleRadius, rect[0], rect[1], rect[2], rect[3]))
	{

	}

	SVector2 vRight(1, 0);
	SVector2 vUp(0, 1);
	SVector2 vRU(1, 1);
	vRU = vRU.Normalize();
	SVector2 vLineStart(100, 100);
	SVector2 vLineEnd;
	float fLineDist = 100;
	/*vLineEnd = vLineStart + vRight * fLineDist;
	CDebugHelper::DrawLine(vLineStart, vLineEnd, pRedBrush);
	vLineEnd = vLineStart + vUp * fLineDist;
	CDebugHelper::DrawLine(vLineStart, vLineEnd, pGreenBrush);
	SVector2 vCrossZRight = SVector2::CrossZ(vRight);
	vLineEnd = vLineStart + vCrossZRight * fLineDist;
	CDebugHelper::DrawLine(vLineStart, vLineEnd, pYellowBrush);
	SVector2 vCrossZUp = SVector2::CrossZ(vUp);
	vLineEnd = vLineStart + vCrossZUp * fLineDist;
	CDebugHelper::DrawLine(vLineStart, vLineEnd, pBlackBrush);*/
	/*vLineEnd = vLineStart + vRU * fLineDist;
	CDebugHelper::DrawLine(vLineStart, vLineEnd, pRedBrush);
	SVector2 vCrossZRU = SVector2::CrossZ(vRU);
	vLineEnd = vLineStart + vCrossZRU * fLineDist;
	CDebugHelper::DrawLine(vLineStart, vLineEnd, pYellowBrush);*/
	/*SVector2 vDir = m_vPos - vLineStart;
	vDir = vDir.Normalize();
	vLineEnd = vLineStart + vDir * fLineDist;
	CDebugHelper::DrawLine(vLineStart, m_vPos, pRedBrush);
	SVector2 vCrossZ = SVector2::CrossZ(vDir);
	vLineEnd = vLineStart + vCrossZ * fLineDist;
	CDebugHelper::DrawLine(vLineStart, vLineEnd, pYellowBrush);
	*/
	vLineEnd = vLineStart + (SVector2::left() * fLineDist);
	//CDebugHelper::DrawLine(vLineStart, vLineEnd, pBlackBrush);

	CDebugHelper::DrawCircle(m_vPos, 1, pRedBrush);
	int nCheck;
	CCollisionCheck::OverlapPointToLine(m_vPos, vLineStart, vLineEnd, nCheck);


	//SVector2 vCirclePos = m_vPos + vAsix;
	//float fCircleRadius = vSize.y * 0.5f;
	/*
	if (CCollisionCheck::OverlapPointToOBB(vCirclePos, vTL_A, vTR_A, vBR_A, vBL_A))
	{
		CDebugHelper::DrawRect(vTL_A, vBR_A, pRedBrush);
		CDebugHelper::DrawCircle(vCirclePos, fCircleRadius, pRedBrush);

	}
	else
	{
		CDebugHelper::DrawRect(vTL_A, vBR_A, pBlackBrush);
		CDebugHelper::DrawCircle(vCirclePos, fCircleRadius, pBlackBrush);
	}*/

	/*if (CCollisionCheck::OverlapAABBtoCircle(vTL_A, vBR_A, vCirclePos, fCircleRadius))
	{
		CDebugHelper::DrawRect(vTL_A, vBR_A, pRedBrush);
		CDebugHelper::DrawCircle(vCirclePos, fCircleRadius, pRedBrush);
		
	}
	else
	{
		CDebugHelper::DrawRect(vTL_A, vBR_A, pBlackBrush);
		CDebugHelper::DrawCircle(vCirclePos, fCircleRadius, pBlackBrush);	
	}*/

	/*if (CCollisionCheck::OverlapAABBtoAABB(vTL_A, vBR_A, vTL_B, vBR_B))
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
	}*/

	if (nAniIdx < m_pPlayer->GetAnimationCount() - 1)
		nAniIdx++;
	else
		nAniIdx = 0;

	if (fAngle < 360)
		fAngle++;
	else
		fAngle = 0;
}