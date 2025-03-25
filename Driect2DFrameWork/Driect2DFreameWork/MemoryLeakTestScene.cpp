#include "MemoryLeakTestScene.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/ColorBrushPalettet.h"
#include "DX2DClasses/Image.h"
#include "DX2DClasses/GameObject.h"
#include "DX2DClasses/DebugHelper.h"

using namespace DX2DClasses;

CMemoryLeakTestScene::CMemoryLeakTestScene()
{
}

CMemoryLeakTestScene::~CMemoryLeakTestScene()
{
    Release();
}

void CMemoryLeakTestScene::Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework)
{
    m_pDX2DFramework = pDX2DFramework;
    ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

    m_pColorBrushPalettet = new CColorBrushPalettet();
    m_pColorBrushPalettet->Initialize(pRenderTarget);

    m_pImage = new CImage(m_pDX2DFramework->GetD2DRenderTarget(), m_pDX2DFramework->GetImagingFactory(),6);
    m_pImage->ManualLoadImage(hWnd, L"Images\\Player\\player%02d.png"); // ������ �̹��� ���

    m_pGameObject = new CGameObject();
    m_pGameObject->Initialize(m_pImage, true);

    // �޸� ������ �߻���Ű���� �Ʒ� �ּ��� �����ϼ���.
    // CreateMemoryLeak();

    // �޸𸮸� �ùٸ��� �����Ϸ��� �Ʒ� �Լ��� ȣ���ϼ���. (�⺻������ Release���� ó��)
    // ReleaseMemory();
}

void CMemoryLeakTestScene::Release()
{
    CDebugHelper::LogConsole("MemoryLeakTestScene::Release()\n");
    if (m_pGameObject)
    {
        m_pGameObject->Release();
        delete m_pGameObject;
        m_pGameObject = nullptr;
    }
    if (m_pImage)
    {
        delete m_pImage;
        m_pImage = nullptr;
    }
    if (m_pColorBrushPalettet)
    {
        m_pColorBrushPalettet->Release();
        delete m_pColorBrushPalettet;
        m_pColorBrushPalettet = nullptr;
    }
}

void CMemoryLeakTestScene::Update()
{
    if (m_pGameObject)
        m_pGameObject->Update();
}

void CMemoryLeakTestScene::Draw()
{
    if (m_pGameObject)
    {
        m_pGameObject->Draw();
    }
}

void CMemoryLeakTestScene::CreateMemoryLeak()
{
    CDebugHelper::LogConsole("Intentional Memory Leak �߻�!\n");
    // �ǵ������� m_pGameObject, m_pImage, m_pColorBrushPalettet�� �������� ����
    // Release() �Լ����� �ش� ��ü���� delete �ڵ带 �ּ� ó���ϰų�,
    // CreateMemoryLeak() �Լ��� ȣ���� �� ReleaseMemory()�� ȣ������ ������ ������ �߻��մϴ�.
}

void CMemoryLeakTestScene::ReleaseMemory()
{
    CDebugHelper::LogConsole("Forcefully releasing memory.\n");
    if (m_pGameObject)
    {
        m_pGameObject->Release();
        delete m_pGameObject;
        m_pGameObject = nullptr;
    }
    if (m_pImage)
    {
        delete m_pImage;
        m_pImage = nullptr;
    }
    if (m_pColorBrushPalettet)
    {
        m_pColorBrushPalettet->Release();
        delete m_pColorBrushPalettet;
        m_pColorBrushPalettet = nullptr;
    }
}