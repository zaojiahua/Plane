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

	//获得坐标
	auto size = Director::getInstance()->getWinSize();
	auto contentSize = this->getContentSize();
	//横纵坐标按照以下的方法设置
	auto point = Point(getRandomNumber(contentSize.width/2,
		size.width-this->getContentSize().width/2),
		size.height);
	this->setPosition(point);

	//设置一个曲线动作让ufo来执行
	ccBezierConfig bezier;
	//贝塞尔曲线的俩个控制点都在屏幕内
	bezier.controlPoint_1 = Point(getRandomNumber(contentSize.width/2,
		size.width-contentSize.width/2),
		getRandomNumber(contentSize.height/2,size.height-contentSize.height/2));
	bezier.controlPoint_2 = Point(getRandomNumber(contentSize.width/2,
		size.width-contentSize.width/2),
		getRandomNumber(contentSize.height/2,size.height-contentSize.height/2));
	//贝塞尔曲线的结束点是屏幕的下边，这样UFO就相当于飞走了
	bezier.endPosition = Point(getRandomNumber(contentSize.width/2,
		size.width-contentSize.width/2),-contentSize.height);

	//使用BezierTo动作，因为上边的控制点配置信息使用的都是绝对坐标点
	auto bezierAction = BezierTo::create(2.0f,bezier);
	//移除自己
	auto removeAction = RemoveSelf::create();
	auto action = Sequence::create(bezierAction,removeAction,NULL);
	//执行上边的动作
	this->runAction(action);
}

//如果要获得a~b之间的一个随机数，则应该是CCRANDOM_0_1*(b-a)+a，传入的参数就是a和b
int Ufo::getRandomNumber(int start,int end)
{
	return CCRANDOM_0_1()*(end-start)+start;
}
