#include "Ufo.h"

Ufo::Ufo(void)
{
}


Ufo::~Ufo(void)
{
}

bool Ufo::init()
{
	if(!Sprite::init())
		return false;

	return true;
}

void Ufo::initUfo(std::string name)
{
	m_name = name;
	this->initWithSpriteFrameName(name);

	//�������
	auto size = Director::getInstance()->getWinSize();
	auto contentSize = this->getContentSize();
	//�������갴�����µķ�������
	auto point = Point(getRandomNumber(contentSize.width/2,
		size.width-this->getContentSize().width/2),
		size.height);
	this->setPosition(point);

	//����һ�����߶�����ufo��ִ��
	ccBezierConfig bezier;
	//���������ߵ��������Ƶ㶼����Ļ��
	bezier.controlPoint_1 = Point(getRandomNumber(contentSize.width/2,
		size.width-contentSize.width/2),
		getRandomNumber(contentSize.height/2,size.height-contentSize.height/2));
	bezier.controlPoint_2 = Point(getRandomNumber(contentSize.width/2,
		size.width-contentSize.width/2),
		getRandomNumber(contentSize.height/2,size.height-contentSize.height/2));
	//���������ߵĽ���������Ļ���±ߣ�����UFO���൱�ڷ�����
	bezier.endPosition = Point(getRandomNumber(contentSize.width/2,
		size.width-contentSize.width/2),-contentSize.height);

	//ʹ��BezierTo��������Ϊ�ϱߵĿ��Ƶ�������Ϣʹ�õĶ��Ǿ��������
	auto bezierAction = BezierTo::create(2.0f,bezier);
	//�Ƴ��Լ�
	auto removeAction = RemoveSelf::create();
	auto action = Sequence::create(bezierAction,removeAction,NULL);
	//ִ���ϱߵĶ���
	this->runAction(action);
}

//���Ҫ���a~b֮���һ�����������Ӧ����CCRANDOM_0_1*(b-a)+a������Ĳ�������a��b
int Ufo::getRandomNumber(int start,int end)
{
	return CCRANDOM_0_1()*(end-start)+start;
}
