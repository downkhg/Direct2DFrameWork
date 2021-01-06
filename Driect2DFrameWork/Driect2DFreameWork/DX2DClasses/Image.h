#pragma once
#include <Windows.h>
#include "Vector2.h"

#define ANI_SIZE 7

struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;
struct IWICFormatConverter;
struct ID2D1Bitmap;

namespace DX2DClasses
{
	class CImage
	{
		IWICFormatConverter*		m_pConvertedSrcBmp[ANI_SIZE]; //포맷변환기
		ID2D1Bitmap*				m_pD2DBitmap[ANI_SIZE]; //비트맵
		SVector2				m_sPointSize;

	public:
		ID2D1HwndRenderTarget*		m_pRenderTarget;
		IWICImagingFactory*			m_pWICFactory;

		SVector2 GetSize();
		SVector2 GetCenter();

		void CreateD2DBitmapFromFile(HWND hWnd, TCHAR* pImageFullPath, int idx);

		void ManualLoadImage(HWND hWnd, const TCHAR* format);

		void DrawBitmap(const SVector2& pos, const SVector2& size, const float& angle, int idx);
		//void DrawBitmap(const D2D1::Matrix3x2F &mat, int idx);
	};
}