#include "GameManager.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/ColorBush.h"
#include "DX2DClasses/Shape.h"
#include "DX2DClasses/Vector2.h"

using namespace DX2DClasses;

CGameManager::CGameManager()
{
	//Initialize();
}

CGameManager::~CGameManager()
{
	Release();
}

void CGameManager::Initialize()
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	m_pColorBrush = new CColorBrush();
	m_pColorBrush->CreateColorBrush(pRenderTarget, D2D1::ColorF(D2D1::ColorF::Black));
	ID2D1SolidColorBrush* pColorBlush = m_pColorBrush->GetColorBrush();
	m_pRect = new CRect();
	

	m_pCircle = new CCircle();
	

	m_pTriangle = new CTriangle();
	

	m_pPolygon = new CPolygon();
	
	
}

void CGameManager::Release()
{
	delete m_pRect;
	delete m_pCircle;
	delete m_pTriangle;
	delete m_pPolygon;

	delete m_pColorBrush;
}

void CGameManager::Update()
{
	m_pRect->Set(0, 0, 500, 200);
	m_pCircle->Set(50, 50, 100);
	m_pTriangle->Set(0, 0, 0, 50, 50, 50);
	SVector2 rect[5] = { {0,0},{0,100},{50,150},{100,100},{100,0} };
	m_pPolygon->Set(rect, 5);
}

void CGameManager::Draw()
{
	m_pRect->Draw(m_pColorBrush);
	m_pCircle->Draw(m_pColorBrush);
	m_pTriangle->Draw(m_pColorBrush);
	m_pPolygon->Draw(m_pColorBrush);
}