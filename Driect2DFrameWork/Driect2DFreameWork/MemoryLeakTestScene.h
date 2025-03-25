#pragma once
#include "DX2DClasses/SceneManager.h"
#include "DX2DClasses/Driect2DFramework.h"

namespace DX2DClasses
{
    class CMemoryLeakTestScene : public ISceneManager
    {
    private:
        CDriect2DFramwork* m_pDX2DFramework = nullptr;
        class CImage* m_pImage = nullptr;
        class CGameObject* m_pGameObject = nullptr;
        class CColorBrushPalettet* m_pColorBrushPalettet = nullptr;

    public:
        CMemoryLeakTestScene();
        ~CMemoryLeakTestScene();

        virtual void Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework) override;
        virtual void Release() override;
        virtual void Update() override;
        virtual void Draw() override;

        // �޸� ���� �׽�Ʈ�� ���� �Լ� (�ǵ������� �������� ����)
        void CreateMemoryLeak();

        // �޸𸮸� �ùٸ��� �����ϴ� �Լ�
        void ReleaseMemory();
    };
}