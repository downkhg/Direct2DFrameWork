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

		void Initialize(); //초기화
		void Release(); //동적객체 제거

		void Update(); //정보변경
		void Draw(); //객체 그리기
	};
}