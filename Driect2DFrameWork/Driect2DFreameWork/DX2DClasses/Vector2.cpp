#include "Vector2.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>


using namespace DX2DClasses;

SVector2::SVector2(float x, float y) 
{ 
	this->x = x; this->y = y;
}
SVector2::SVector2(D2D1_POINT_2F& pos)
{
	this->x = pos.x; this->y = pos.y;
}
SVector2 SVector2::operator+(const SVector2& vec)
{
	SVector2 vTemp(x + vec.x, y + vec.y);
	return vTemp;
}
SVector2 SVector2::operator-(const SVector2& vec)
{
	SVector2 vTemp(x - vec.x, y - vec.y);
	return vTemp;
}
SVector2 SVector2::operator*(float dist)
{
	SVector2 vTemp(x * dist, y * dist);
	return vTemp;
}
float SVector2::Magnitude()
{
	return sqrtf(x*x + y * y);
}
SVector2 SVector2::Normalize()
{
	float fDist = Magnitude();
	SVector2 vDir(x / fDist, y / fDist);
	return vDir;
}

D2D1_POINT_2F SVector2::ToPoint()
{
	D2D1_POINT_2F sPoint = D2D1::Point2F(x, y);
	return sPoint;
}

const char* SVector2::GetChar(const char* msg)
{
	static char strName[256];
	sprintf_s(strName, sizeof(strName), "%s(%f,%f)", msg, x, y);
	return strName;
}

float SVector2::Dot(const SVector2& a, const SVector2& b)
{
	return a.x * b.x + a.y * b.y;
}

float SVector2::Cross(const SVector2& a, const SVector2& b)
{
	return a.x * b.y - a.y * b.x;
}

float SVector2::Angle(const SVector2& a, const SVector2& b)
{
	const float fRad2Deg = 57.29578f;
	int fTheta = Dot(a, b);
	return acosf(fTheta) * fRad2Deg;
}

void SVector2::TestMain()
{
	const float fRad2Deg = 57.29578f;
	float fDot= SVector2::Dot(SVector2::up(), SVector2::right());
	float fCosA = acosf(fDot);
	float fCosAtoRad = fCosA * fRad2Deg;
	float fAngle = SVector2::Angle(SVector2::up(), SVector2::right());
	SVector2 vTan = SVector2::up() + SVector2::right();
	vTan.Normalize();
	float fTanA = vTan.y / vTan.x;
	float fTanAToRad = atanf(fTanA) * fRad2Deg;
	float fTanA2ToRad = atan2(vTan.y, vTan.x) * fRad2Deg;

	_cprintf("dot: %f / cosA: %f / cosAtoRad: %f \n", fDot, fCosA, fCosAtoRad);
	_cprintf("vTan %s / tanA: %f / tanAtoRad1/2: %f/%f \n", vTan.GetChar(), fTanA, fTanAToRad, fTanA2ToRad);
	_cprintf("Angle: %f \n", fAngle);
}

float CosAtoAngle(float fDot)
{
	const float fRad2Deg = 57.29578f;
	return acosf(fDot) * fRad2Deg;
}

float TanAtoAngle(const SVector2& vec)
{
	const float fRad2Deg = 57.29578f;
	float fTanA = vec.y / vec.x;
	return atanf(fTanA) * fRad2Deg;
}

//SVector2 SVector2::Cross(SVector2 a, SVector2 b)
//{
//	/*
//	 temp.x = vector_a.y * vector_b.z - vector_a.z * vector_b.y;
//   temp.y = vector_a.z * vector_b.x - vector_a.x * vector_b.z;
//   temp.z = vector_a.x * vector_b.y - vector_a.y * vector_b.x;
//	*/
//
//	SVector2 vTemp;
//	//float fAz;
//	//float fBz;
//	//float fTempZ;
//
//	vTemp.x = a.y * fBz - fAz * b.y;
//	vTemp.y = a.x * fBz - fAz * b.x;
//	fTempZ = a.x * b.y - a.y * b.x;
//
//
//	return vTemp;
//}