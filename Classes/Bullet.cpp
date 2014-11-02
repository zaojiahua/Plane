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
	//ÿ��һ��ʱ���ƶ��ӵ�
	this->schedule(SEL_SCHEDULE(&Bullet::move),0.1f);
}

//���ݴ����������������ʼ���ӵ���
void Bullet::initBullet(std::string name)
{
	this->initWithSpriteFrameName(name);
}

//�ӵ��ƶ�
void Bullet::move(float tm)
{
	this->setVisible(true);
	auto move = MoveBy::create(0.1f,Point(0,OFFSET));
	this->runAction(move);
	//�ӵ��ƶ�������Ļ
	if(this->getPositionY() > Director::getInstance()->getWinSize().height)
	{
		this->removeFromParentAndCleanup(true);
		//�ӹ��������Ƴ���ȥ
		auto & vector = Manager::getInstance()->getBulletVector();
		vector.eraseObject(this);
	}
}
