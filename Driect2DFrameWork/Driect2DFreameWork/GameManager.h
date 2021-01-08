#pragma once
#include "DX2DClasses/GameManager.h"
#include "DX2DClasses/Vector2.h"

namespace DX2DClasses
{
	class CRect;
	class CPolygon;
	class CTriangle;
	class CCircle;
	class CImage;
	class CColorBrush;
	class CColorBrushPalettet;

	class CGameManager : public IGameManager
	{
		
		CColorBrushPalettet* m_pColorBrushPalettet;

		CImage* m_pPlayer;
		CImage* m_pOpossum;
		CImage* m_pEagle;
		CImage* m_pCherry;
		CImage* m_pGem;
		CImage* m_pItemEffect;
		CImage* m_pDeathEffect;

		SVector2 m_vPos;
	public:
		CGameManager();
		~CGameManager();

		void Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework) override; //�ʱ�ȭ
		void Release() override; //������ü ����

		void Update() override; //��������
		void Draw() override; //��ü �׸���
	};
}