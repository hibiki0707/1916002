#pragma once
#include"Enemy.h"

namespace Battle {
	class Enemy;

	class Player
	{
		Enemy* enemy_;
		int life_ = 100;
	public:
		void OnDamage(int damage);	// ダメージを食らう
		void Attack();	// 敵にダメージを与える
	};

}