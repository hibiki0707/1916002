#include "Enemy.h"
#include"Player.h"

using namespace Battle;

void Enemy::OnDamage(int damage){
	life_ -= damage;	// �_���[�W��H�炤
}

void Enemy::Attack(){
	player_->OnDamage(10);	// �v���C���[�Ƀ_���[�W��^����
}
