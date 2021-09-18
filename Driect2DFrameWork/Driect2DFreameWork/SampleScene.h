#pragma once
#include "DX2DClasses/SceneManager.h"
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
	class CGameObject;

	class CSampleScene : public ISceneManager
	{
		CColorBrushPalettet* m_pColorBrushPalettet;

		CImage* m_pPlayerImage;
		CGameObject* m_pPlayerObject;
		CImage* m_pOpossumImage;
		CGameObject* m_pOpossumObject;
		CImage* m_pEagleImage;
		CGameObject* m_pEagleObject;

		CImage* m_pCherryImage;
		CGameObject* m_pCherryObject;
		CImage* m_pGemImage;
		CGameObject* m_pGemObject;

		CImage* m_pItemEffectImage;
		CGameObject* m_pItemEffectObject;
		CImage* m_pDeathEffectImage;
		CGameObject* m_pDeathEffectObject;
		
		SVector2 m_vPos;
	public:
		CSampleScene();
		~CSampleScene();

		void Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework) override; //�ʱ�ȭ
		void Release() override; //������ü ����

		void Update() override; //��������
		void Draw() override; //��ü �׸���
	};
}