#pragma once
namespace Battle {
	// 型のプロトタイプ宣言
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