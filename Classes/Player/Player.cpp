#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

bool Player::init()
{
	//�ȳ�ʼ�������init����
	if(!Sprite::init())
		return false;

	//���ø����initWithSpriteFrameName����������framename���������ǵ�player������ͼƬ�ˣ���MainGame��
	//����Ҫ���õ���������ؽ�����֡����
	this->initWithSpriteFrameName("hero1.png");
	//���ŷɻ��Ķ���
	this->flyAction();

	return true;
}

//�ɻ��Ķ���
void Player::flyAction()
{
	//����ʹ����һ�ַ�ʽ�����Ŷ���
	Vector<SpriteFrame *> vector;
	for(int i=0;i<2;i++)
	{
		auto frameName = __String::createWithFormat("hero%d.png",i+1);
		auto temSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		vector.pushBack(temSpriteFrame);
	}
	//���ò��ϲ��ŷɻ��Ķ���
	auto animation = Animation::createWithSpriteFrames(vector,0.2f,-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}
