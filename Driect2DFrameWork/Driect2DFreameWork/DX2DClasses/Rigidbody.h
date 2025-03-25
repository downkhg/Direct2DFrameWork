#pragma once
#include <Windows.h>
#include "Time.h"
#include "Vector2.h"
#include "GameObject.h"

namespace DX2DClasses
{
	class CTransform;

	class CRigidbody
	{
	public:
		bool isGravity = true;
		SVector2 velocity;
		SVector2 acceleration;
		SVector2 gravity;

		void SetVelocity(float x, float y)
		{
			velocity = SVector2(x, y);
		}

		void SetGravity(float x, float y)
		{
			gravity = SVector2(x, y);
		}
	public:
		CRigidbody(float vel_x = 0, float vel_y = 0, float gravity_x = 0, float gravity_y = 9.8f, bool _isgravity = true)
		{
			//Initialize(SVector2(vel_x,vel_x), SVector2(gravity_x, gravity_y), _isgravity);
		}

		CRigidbody(SVector2 _velocity, SVector2 _gravity, bool _isgravity)
		{
			//Initialize(_velocity, _gravity, _isgravity);
		}

		void Initialize(SVector2 _velocity, SVector2 _gravity, bool _isgravity)
		{
			velocity = _velocity;
			acceleration = SVector2();
			gravity = _gravity;
			isGravity = _isgravity;
		}

		void Update(CTransform& transform)
		{
			float deltaTime = CTime::GetDeltaTime();
			// �߷� ���ӵ��� ����
			if(isGravity)
				acceleration = acceleration + gravity;

			// ���ӵ��� �ӵ��� ����
			velocity = velocity + (acceleration * deltaTime);

			// �ӵ��� ����Ͽ� ���� ������Ʈ�� ��ġ�� ������
			transform.Transrate(velocity * deltaTime);

			// ���ӵ� �ʱ�ȭ (�� �����Ӹ��� �߷¸� ����)
			acceleration = SVector2();
		}
	};
}