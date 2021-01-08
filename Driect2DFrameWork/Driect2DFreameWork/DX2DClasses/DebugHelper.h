#pragma once

namespace DX2DClasses
{
	class CColorBrush;
	struct SVector2;

	class CDebugHelper
	{
	public: //콘솔디버깅
		static void OpenConsole();
		static void CloseConsole();
		static void LogConsole(const char* msg, ...);
	public: //그래픽디버깅
		static void DrawCircle(SVector2& pos, float rad, CColorBrush* pColorBrush, float stroke = 1.0f);
		static void DrawRect(SVector2& tl, SVector2& br, CColorBrush* pColorBrush, float stroke = 1.0f);
		static void DrawPolygon(SVector2 posArr[], int size, CColorBrush* pColorBrush, float stroke = 1.0f);
	};
}