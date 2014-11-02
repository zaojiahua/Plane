#include "Bullet.h"
#include "Manager\Manager.h"

Bullet::Bullet(void)
{
}


Bullet::~Bullet(void)
{
}

bool Bullet::init()
{
	if(!Sprite::init())
		return false;

	return true;
}

void Bullet::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	//每隔一定时间移动子弹
	this->schedule(SEL_SCHEDULE(&Bullet::move),0.1f);
}

//根据传入的纹理名称来初始化子弹类
void Bullet::initBullet(std::string name)
{
	this->initWithSpriteFrameName(name);
}

//子弹移动
void Bullet::move(float tm)
{
	this->setVisible(true);
	auto move = MoveBy::create(0.1f,Point(0,OFFSET));
	this->runAction(move);
	//子弹移动出了屏幕
	if(this->getPositionY() > Director::getInstance()->getWinSize().height)
	{
		this->removeFromParentAndCleanup(true);
		//从管理器中移除出去
		auto & vector = Manager::getInstance()->getBulletVector();
		vector.eraseObject(this);
	}
}
