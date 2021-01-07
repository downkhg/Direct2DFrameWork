#include "CollisionCheck.h"
#include "Vector2.h"

using namespace DX2DClasses;

bool CCollisionCheck::OverlapPointToCircle(SVector2& vPos, SVector2& vCenter, const float fRad)
{
	SVector2 vDist = vCenter - vPos;
	float fDist = vDist.Magnitude();

	if (fDist < fRad)
		return true;
	else
		return false;
}

bool CCollisionCheck::OverlapCircleToCircle(SVector2& vCenterA, const float fRadA, SVector2& vCenterB, const float fRadB)
{
	SVector2 vDist = vCenterB - vCenterA;
	float fDist = vDist.Magnitude();

	if (fDist < (fRadA + fRadB))
		return true;
	else
		return false;
}

bool CCollisionCheck::OverlapPointToAABB(SVector2& vPos, SVector2& tl, SVector2& br)
{
	if ((tl.x < vPos.x && vPos.x < br.x) &&
		(tl.y < vPos.y && vPos.y < br.y))
	{
		//_cprintf("AABBtoPosCollider:(%f,%f)<(%f,%f)<(%f,%f)", tl.x, tl.y, br.x, br.y, pos.x, pos.y);
		return true;
	}
	else
		return false;
}
//3D버전 변경함. 문제점 수정필요
bool CCollisionCheck::OverlapAABBtoAABB(SVector2& vTL_A, SVector2& vBR_A, SVector2& vTL_B, SVector2& vBR_B)
{
	if(vBR_A.x < vTL_B.x || vTL_A.x > vBR_B.x) return false;
	if(vBR_A.y < vTL_B.y || vTL_A.y > vBR_B.y) return false;

	return true;
}