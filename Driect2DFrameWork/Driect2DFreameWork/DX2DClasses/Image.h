#pragma once
#include <Windows.h>
#include <vector>
#include "Vector2.h"

struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;
struct IWICFormatConverter;
struct ID2D1Bitmap;

namespace DX2DClasses
{
	class CImage
	{
		std::vector<IWICFormatConverter*>	m_pConvertedSrcBmp; //포맷변환기
		std::vector<ID2D1Bitmap*>	m_pD2DBitmap; //비트맵
		SVector2				m_sPointSize;

		void _CreateD2DBitmapFromFile(HWND hWnd, TCHAR* pImageFullPath, int idx);
	public:
		ID2D1HwndRenderTarget*		m_pRenderTarget;
		IWICImagingFactory*			m_pWICFactory;

		CImage(ID2D1HwndRenderTarget* pRenderTarget, IWICImagingFactory* pWICFactory, int nSize = 1);

		SVector2 GetSize();
		SVector2 GetCenter();

		void ManualLoadImage(HWND hWnd, const TCHAR* format);

		void DrawBitmap(const SVector2& pos, const SVector2& size, const float& angle, int idx);
		//void DrawBitmap(const D2D1::Matrix3x2F &mat, int idx);
	};
}