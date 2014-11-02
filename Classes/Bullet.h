#ifndef _BULLET_H_
#define _BULLET_H_
#include "cocos2d.h"

USING_NS_CC;

//子弹类，继承自Sprite
class Bullet : public Sprite
{
public:
	Bullet(void);
	~Bullet(void);
public:
	bool init();
	CREATE_FUNC(Bullet);
	void onEnterTransitionDidFinish();
public:
	//初始化子弹
	void initBullet(std::string name);
	//子弹移动
	void move(float tm);
private:
	//子弹移动的距离
	enum {OFFSET = 200};
};

#endif

