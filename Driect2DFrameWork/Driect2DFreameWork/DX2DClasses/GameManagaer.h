#pragma once

namespace DX2DClasses
{
	__interface IGameManager
	{
	public:
		void Initialize() = 0; //초기화
		void Release() = 0; //동적객체 제거

		void Update() = 0; //정보변경
		void Draw() = 0; //객체 그리기
	};
}