#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

bool Player::init()
{
	//先初始化父类的init函数
	if(!Sprite::init())
		return false;

	//调用父类的initWithSpriteFrameName函数，传入framename，这样我们的player就有了图片了，在MainGame中
	//首先要将用到的纹理加载进精灵帧缓存
	this->initWithSpriteFrameName("hero1.png");
	//播放飞机的动画
	this->flyAction();

	return true;
}

//飞机的动画
void Player::flyAction()
{
	//这里使用另一种方式来播放动画
	Vector<SpriteFrame *> vector;
	for(int i=0;i<2;i++)
	{
		auto frameName = __String::createWithFormat("hero%d.png",i+1);
		auto temSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		vector.pushBack(temSpriteFrame);
	}
	//设置不断播放飞机的动画
	auto animation = Animation::createWithSpriteFrames(vector,0.2f,-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}
