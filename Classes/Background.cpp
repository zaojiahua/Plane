#include "Background.h"

Background::Background(void)
{
}

Background::~Background(void)
{
}

bool Background::init()
{
	if(!Layer::init())
		return false;

	m_size = Director::getInstance()->getWinSize();
	//添加俩张背景图片
	m_background_1 = Sprite::createWithSpriteFrameName("background.png");
	m_background_1->setAnchorPoint(CCPoint::ZERO);
	m_background_1->setPosition(Point::ZERO);
	//设置精灵贴图无锯齿，用来解决移动过程中的黑边（叫白边也行）问题
	m_background_1->getTexture()->setAliasTexParameters();
	this->addChild(m_background_1);

	m_background_2 = Sprite::createWithSpriteFrameName("background.png");
	m_background_2->setAnchorPoint(Point::ZERO);
	//设置坐标的时候减个数值来使得最后不出现黑线
	m_background_2->setPosition(Point(0,
		m_background_1->getContentSize().height-2));
	m_background_2->getTexture()->setAliasTexParameters();
	this->addChild(m_background_2);

	return true;
}

//函数初始化完毕调用的函数，实现的效果就是切换场景的动画播放完毕才移动地图
void Background::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	//改变图片的坐标，产生移动的效果
	this->schedule(SEL_SCHEDULE(&Background::move),0.01f);
}

//地图移动
void Background::move(float tm)
{
	float y1 = m_background_1->getPositionY()-OFFSET;
	float y2 = m_background_2->getPositionY()-OFFSET;
	//改变坐标位置
	m_background_1->setPositionY(y1);
	m_background_2->setPositionY(y2);
	//判断是否超出了屏幕的边界
	if(y1 < -m_background_1->getContentSize().height)
	{
		m_background_1->setPositionY(m_background_2->getPositionY()+m_background_2->getContentSize().height-2);
	}
	else if(y2 < -m_background_2->getContentSize().height)
	{
		m_background_2->setPositionY(m_background_1->getPositionY()+m_background_1->getContentSize().height-2);
	}
}
