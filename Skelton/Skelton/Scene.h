#ifndef SCENE_H_INCLIDED
#define SCENE_H_INCLIDED

#include "Player.h"

namespace Battle {
	class Player;
}

class Scene
{
private:
	Battle::Player* player_;
public:
	void Updata();
};

#endif // ! SCENE_H_INCLIDED
