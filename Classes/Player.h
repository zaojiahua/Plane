#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cocos2d.h"

USING_NS_CC;

//继承自Sprite
class Player : public Sprite
{
public:
	Player(void);
	~Player(void);
public:
	bool init();
	CREATE_FUNC(Player);
	//飞机的动作
	void flyAction();
};

#endif

