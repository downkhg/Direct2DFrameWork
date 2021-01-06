#pragma once
#include <Windows.h>

struct ID2D1Factory;
struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;

namespace DX2DClasses
{
	class CDriect2DFramwork
	{
		ID2D1Factory* m_pD2DFactory = nullptr;
		ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
		IWICImagingFactory* m_pWICImagingFactory = nullptr;
	public:
		void Initialize(HWND hWnd);
		void Release();
	private:
		void _InitializeD2D(ID2D1Factory* &pD2DFactory, IWICImagingFactory* &pWICImagingFactory);
		void _InitializeRect(HWND hWnd, ID2D1HwndRenderTarget* &pRenderTaget);
	};
}