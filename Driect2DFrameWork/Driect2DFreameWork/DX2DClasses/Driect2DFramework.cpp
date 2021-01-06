#include "Driect2DFramework.h"
#include "SingletonRenderTarget.h"

#include <wincodec.h>
#include <d2d1.h>
#include <d2d1helper.h>

#include <assert.h>

using namespace DX2DClasses;

void CDriect2DFramwork::Initialize(HWND hWnd)
{
	_InitializeD2D(m_pD2DFactory, m_pWICImagingFactory);
	_InitializeRect(hWnd, m_pRenderTarget);
	CSingletonRenderTarget::SetRenderTarget(m_pRenderTarget);
}

void CDriect2DFramwork::Release()
{
	
	m_pRenderTarget->Release();
	m_pD2DFactory->Release();
	m_pWICImagingFactory->Release();
}

void CDriect2DFramwork::_InitializeD2D(ID2D1Factory* &pD2DFactory, IWICImagingFactory* &pWICImagingFactory)
{
	HRESULT hr = E_FAIL;

	//-----------------------------------------------------------------------
	//	D2D Factory 를 생성한다.
	//-----------------------------------------------------------------------
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	assert(hr == S_OK);

	//-----------------------------------------------------------------------
	//	Windows Imaging Component Factory 를 생성한다.
	//-----------------------------------------------------------------------
	hr = CoCreateInstance(CLSID_WICImagingFactory,
		NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pWICImagingFactory));

	assert(hr == S_OK);
}

void CDriect2DFramwork::_InitializeRect(HWND hWnd, ID2D1HwndRenderTarget* &pRenderTaget)
{
	assert(m_pRenderTarget == nullptr);
	assert(hWnd != 0);

	HRESULT hr = E_FAIL;
	RECT rc;
	GetClientRect(hWnd, &rc);

	D2D1_RENDER_TARGET_PROPERTIES dxRTProperties = D2D1::RenderTargetProperties();
	D2D1_SIZE_U dxSize = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	hr = m_pD2DFactory->CreateHwndRenderTarget(dxRTProperties, D2D1::HwndRenderTargetProperties(hWnd, dxSize), &pRenderTaget);

	assert(hr == S_OK);
}
