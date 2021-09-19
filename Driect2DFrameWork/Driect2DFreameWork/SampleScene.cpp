#include "SampleScene.h"
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

CSampleScene::CSampleScene()
{
	//Initialize();
}

CSampleScene::~CSampleScene()
{
	//Release();
}

void CSampleScene::Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework)
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	m_pPlayerImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	m_pPlayerImage->ManualLoadImage(hWnd, L"Images\\player%02d.png");
	m_pPlayerObject = new CGameObject();
	m_pPlayerObject->Initialize(m_pPlayerImage, true);

	m_pOpossumImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(),6);
	m_pOpossumImage->ManualLoadImage(hWnd, L"Images\\opossum%02d.png");
	m_pOpossumObject = new CGameObject();
	m_pOpossumObject->Initialize(m_pOpossumImage, true);

	m_pEagleImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	m_pEagleImage->ManualLoadImage(hWnd, L"Images\\eagle%02d.png");
	m_pEagleObject = new CGameObject();
	m_pEagleObject->Initialize(m_pEagleImage, true);

	m_pCherryImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	m_pCherryImage->ManualLoadImage(hWnd, L"Images\\cherry%02d.png");
	m_pCherryObject = new CGameObject();
	m_pCherryObject->Initialize(m_pCherryImage, true);

	m_pGemImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 5);
	m_pGemImage->ManualLoadImage(hWnd, L"Images\\gem%02d.png");
	m_pGemObject = new CGameObject();
	m_pGemObject->Initialize(m_pGemImage, true);

	m_pItemEffectImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	m_pItemEffectImage->ManualLoadImage(hWnd, L"Images\\itemeffect%02d.png");
	m_pItemEffectObject = new CGameObject();
	m_pItemEffectObject->Initialize(m_pItemEffectImage, true);

	m_pDeathEffectImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 5);
	m_pDeathEffectImage->ManualLoadImage(hWnd, L"Images\\death%02d.png");
	m_pDeathEffectObject = new CGameObject();
	m_pDeathEffectObject->Initialize(m_pDeathEffectImage, true);
}

void CSampleScene::Release()
{
	m_pPlayerObject->Release();
	delete m_pPlayerObject;
	m_pOpossumObject->Release();
	delete m_pOpossumObject;
	m_pEagleObject->Release();
	delete m_pEagleObject;
	m_pCherryObject->Release();
	delete m_pCherryObject;
	m_pGemObject->Release();
	delete m_pGemObject;
	m_pItemEffectObject->Release();
	delete m_pItemEffectObject;
	m_pDeathEffectObject->Release();
	delete m_pDeathEffectObject;

	delete m_pPlayerImage;
	delete m_pOpossumImage;
	delete m_pEagleImage;
	delete m_pCherryImage;
	delete m_pGemImage;
	delete m_pItemEffectImage;
	delete m_pDeathEffectImage;
}

void CSampleScene::Update()
{
	if (CInputManager::GetAsyncKeyStatePress(VK_RIGHT))
		m_vPos.x++;
	if (CInputManager::GetAsyncKeyStatePress(VK_LEFT))
		m_vPos.x--;
	if (CInputManager::GetAsyncKeyStatePress(VK_DOWN))
		m_vPos.y++;
	if (CInputManager::GetAsyncKeyStatePress(VK_UP))
		m_vPos.y--;

	static float fAngle = 0;
	{
		CTransform& cTrnasform = m_pPlayerObject->GetTransform();
		SVector2 vSize = m_pPlayerObject->GetImage()->GetImageSize();
		SVector2 vScale(1, 1);
		cTrnasform.SetTransrate(m_vPos);
		SVector2 vAsix = vSize * 0.5f;
		cTrnasform.SetAsixPoint(vAsix);
		cTrnasform.SetTRS(m_vPos, fAngle, vScale);
	}
	m_pPlayerObject->Update();

	static SVector2 vOpossumPos(1000, 0);
	{
		CTransform& cTrnasform = m_pOpossumObject->GetTransform();
		SVector2 vSize = m_pOpossumObject->GetImage()->GetImageSize();
		SVector2 vScale(1, 1);
		cTrnasform.SetTransrate(vOpossumPos);
		SVector2 vAsix = vSize * 0.5f;
		cTrnasform.SetAsixPoint(vAsix);
		cTrnasform.SetTRS(vOpossumPos, 0, vScale);
	}
	vOpossumPos.x--;
	m_pOpossumObject->Update();

	m_pEagleObject->Update();

	m_pCherryObject->Update();
	m_pCherryObject->GetTransform().SetTransrate(0, 50);
	m_pGemObject->Update();
	m_pGemObject->GetTransform().SetTransrate(0, 80);
	m_pItemEffectObject->Update();
	m_pItemEffectObject->GetTransform().SetTransrate(0, 100);
	m_pDeathEffectObject->Update();
	m_pDeathEffectObject->GetTransform().SetTransrate(0, 120);
}

void CSampleScene::Draw()
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	
	m_pPlayerObject->Draw();

	m_pOpossumObject->Draw();

	m_pEagleObject->Draw();

	m_pCherryObject->Draw();
	m_pGemObject->Draw();

	m_pItemEffectObject->Draw();
	m_pDeathEffectObject->Draw();
}