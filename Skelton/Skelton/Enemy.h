#pragma once
namespace Battle {
	// �^�̃v���g�^�C�v�錾
	class Player;

	class Enemy
	{
		Player* player_;
		int life_ = 100;
	public:
		void OnDamage(int damage);
		void Attack();
	};

}