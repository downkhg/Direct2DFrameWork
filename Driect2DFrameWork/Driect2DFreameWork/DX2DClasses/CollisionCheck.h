#pragma once

namespace DX2DClasses
{
	struct SVector2;

	class CCollisionCheck
	{
	public:
		static bool OverlapPointToCircle(SVector2& vPos, SVector2& vCenter, const float fRad);
		static bool OverlapCircleToCircle(SVector2& vCenterA, const float fRadA, SVector2& vCenterB, const float fRadB);
		static bool OverlapPointToAABB(SVector2& vPos, SVector2& tl, SVector2& br);
		static bool OverlapAABBtoAABB(SVector2& vTL_A, SVector2& vBR_A, SVector2& vTL_B, SVector2& vTR_B);
	};
}