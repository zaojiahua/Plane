#ifndef _BULLET_H_
#define _BULLET_H_
#include "cocos2d.h"

USING_NS_CC;

//�ӵ��࣬�̳���Sprite
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
	//��ʼ���ӵ�
	void initBullet(std::string name);
	//�ӵ��ƶ�
	void move(float tm);
private:
	//�ӵ��ƶ��ľ���
	enum {OFFSET = 200};
};

#endif

