#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cocos2d.h"

USING_NS_CC;

//�̳���Sprite
class Player : public Sprite
{
public:
	Player(void);
	~Player(void);
public:
	bool init();
	CREATE_FUNC(Player);
	//�ɻ��Ķ���
	void flyAction();
};

#endif

