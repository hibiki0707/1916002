#include "Player.h"
#include "Enemy.h"

using namespace Battle;

void Player::OnDamage(int damage){
	life_ = -damage;	// �_���[�W��H�炤
}

void Player::Attack(){
	enemy_->OnDamage(10);	// �G�Ƀ_���[�W��^����
}
