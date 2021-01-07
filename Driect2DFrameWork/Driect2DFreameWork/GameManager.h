#pragma once
#include "DX2DClasses/GameManagaer.h"
#include "DX2DClasses/Vector2.h"

namespace DX2DClasses
{
	class CRect;
	class CPolygon;
	class CTriangle;
	class CCircle;
	class CImage;
	class CColorBrush;

	class CGameManager : public IGameManager
	{
		CColorBrush* m_pColorBrush;
		CColorBrush* m_pRedBrush;

		CRect* m_pRect;
		CPolygon* m_pPolygon;
		CTriangle* m_pTriangle;
		CCircle* m_pCircle;

		CImage* m_pImage;
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