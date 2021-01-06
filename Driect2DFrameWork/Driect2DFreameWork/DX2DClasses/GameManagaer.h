#pragma once

namespace DX2DClasses
{
	__interface IGameManager
	{
	public:
		void Initialize() = 0; //�ʱ�ȭ
		void Release() = 0; //������ü ����

		void Update() = 0; //��������
		void Draw() = 0; //��ü �׸���
	};
}