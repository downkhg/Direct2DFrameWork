#pragma once
#include "DX2DClasses/GameManagaer.h"

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

		CRect* m_pRect;
		CPolygon* m_pPolygon;
		CTriangle* m_pTriangle;
		CCircle* m_pCircle;
	public:
		CGameManager();
		~CGameManager();

		void Initialize(); //�ʱ�ȭ
		void Release(); //������ü ����

		void Update(); //��������
		void Draw(); //��ü �׸���
	};
}