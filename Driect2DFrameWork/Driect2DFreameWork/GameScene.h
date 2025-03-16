#pragma once
#include "DX2DClasses/SceneManager.h"
#include "DX2DClasses/Vector2.h"
#include <vector>
#include <list>
#include <queue>

namespace DX2DClasses
{
	class CImage;
	class CColorBrushPalettet;
	class CGameObject;

	class CGameScene : public ISceneManager
	{
		//���������� ������ ��ü ����׵���̿� �Բ� ����Ѵ�.
		CColorBrushPalettet* m_pColorBrushPalettet;

		enum E_SUNNYLAND_IMAGE
		{ 
			Player, 
			Opossum, 
			Eagle, 
			Cherry, 
			Gem, 
			ItemEffect, 
			DeathEffect, 
			MAX
		};
		
		//������ �ʿ��� �̹����� �������� ��ü
		std::vector<CImage*> m_listImages;
		
		std::vector<CGameObject*> m_listItem;
		std::list<CGameObject*> m_listEnableItem;
		std::queue<CGameObject*> m_listDiableItem;

		std::vector<CGameObject*> m_listBullet;
		std::queue<CGameObject*> m_queueEnableBullet;
		std::queue<CGameObject*> m_queueDisableBullet;

		//������ �ε�� �̹����� ���� �ִϸ��̼� �� ������ �����Ѵ�.
		//���ӿ�����Ʈ�� ���������� ��ü�� ���Ե��Ƿ� �� ������ �Ϲ����̴�.
		CGameObject* m_pPlayerObject;

		std::vector<CGameObject*> m_listOpossumObject;
		std::vector<CGameObject*> m_listEagleObject;

		std::vector<CGameObject*> m_listItemEffectObject;
		std::vector<CGameObject*> m_listpDeathEffectObject;

		float m_fPlayerSpeed = 2;
		float m_fPlayerJumpHigher = 7;
		float m_fOpossumSpeed = 3;
		float m_fEangleSpeed = 5;

		int m_nScore;

		void _InitImagesList(HWND hWnd, CDriect2DFramwork* pDX2DFramework);
	public:
		CGameScene();
		~CGameScene();

		void Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework) override; //�ʱ�ȭ
		void Release() override; //������ü ����

		void Update() override; //��������
		void Draw() override; //��ü �׸���
	};
}