#pragma once
#include <d2d1_1helper.h>

namespace DX2DClasses
{
	struct SVector2
	{
		float x;
		float y;

		SVector2(float x = 0, float y = 0);
		SVector2(D2D1_POINT_2F& pos);
		SVector2 operator+(const SVector2& vec);
		SVector2 operator-(const SVector2& vec);
		SVector2 operator*(float dist);
		float Magnitude();
		SVector2 Normalize();
		D2D1_POINT_2F ToPoint();

		const char* GetChar(const char* msg =  "");

		static float Dot(const SVector2& a, const SVector2& b);
		static float Cross(const SVector2& a, const SVector2& b);//2D공간상에서 z축은 없으므로 계산결과 z축의 스칼라만 남는다.//출처:https://allenchou.net/2013/07/cross-product-of-2d-vectors/
		static float Angle(const SVector2& a, const SVector2& b);

		static SVector2& up() { static SVector2 up(1, 0); return up; };
		static SVector2& right() { static SVector2 right(0, 1); return right; }
		static SVector2& down() { static SVector2 down(0, -1); return down; }
		static SVector2& left() { static SVector2 left(-1, 0); return left; }

		static void TestMain();
	};
}