#pragma once

namespace DX2DClasses
{
	struct SVector2
	{
		float x;
		float y;

		SVector2(float x = 0, float y = 0);
		SVector2 operator+(const SVector2& vec);
		SVector2 operator-(const SVector2& vec);
		SVector2 operator*(float dist);
		float Magnitude();
		SVector2 Normalize();
		const char* GetChar(const char* msg =  "");

		static float Dot(const SVector2& a, const SVector2& b);
		static float Angle(const SVector2& a, const SVector2& b);

		static SVector2& up() { static SVector2 up(1, 0); return up; };
		static SVector2& right() { static SVector2 right(0, 1); return right; }
		static SVector2& down() { static SVector2 down(0, -1); return down; }
		static SVector2& left() { static SVector2 left(-1, 0); return left; }

		static void TestMain();
	};
}