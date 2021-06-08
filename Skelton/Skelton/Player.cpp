#include "Player.h"
#include "Enemy.h"

using namespace Battle;

void Player::OnDamage(int damage){
	life_ = -damage;	// ダメージを食らう
}

void Player::Attack(){
	enemy_->OnDamage(10);	// 敵にダメージを与える
}
