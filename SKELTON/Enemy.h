#pragma once
#include"Player.h"

namespace Battle {
	class Player;

	class Enemy
	{
		Player* player_;
		int life_ = 100;
	public:
		void OnDamage(int damage);	// �_���[�W��H�炤
		void Attack();	// �G�Ƀ_���[�W��^����
	};
}