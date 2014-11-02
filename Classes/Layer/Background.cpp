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
	//������ű���ͼƬ
	m_background_1 = Sprite::createWithSpriteFrameName("background.png");
	m_background_1->setAnchorPoint(CCPoint::ZERO);
	m_background_1->setPosition(Point::ZERO);
	//���þ�����ͼ�޾�ݣ���������ƶ������еĺڱߣ��аױ�Ҳ�У�����
	m_background_1->getTexture()->setAliasTexParameters();
	this->addChild(m_background_1);

	m_background_2 = Sprite::createWithSpriteFrameName("background.png");
	m_background_2->setAnchorPoint(Point::ZERO);
	//���������ʱ�������ֵ��ʹ����󲻳��ֺ���
	m_background_2->setPosition(Point(0,
		m_background_1->getContentSize().height-2));
	m_background_2->getTexture()->setAliasTexParameters();
	this->addChild(m_background_2);

	return true;
}

//������ʼ����ϵ��õĺ�����ʵ�ֵ�Ч�������л������Ķ���������ϲ��ƶ���ͼ
void Background::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	//�ı�ͼƬ�����꣬�����ƶ���Ч��
	this->schedule(SEL_SCHEDULE(&Background::move),0.01f);
}

//��ͼ�ƶ�
void Background::move(float tm)
{
	float y1 = m_background_1->getPositionY()-OFFSET;
	float y2 = m_background_2->getPositionY()-OFFSET;
	//�ı�����λ��
	m_background_1->setPositionY(y1);
	m_background_2->setPositionY(y2);
	//�ж��Ƿ񳬳�����Ļ�ı߽�
	if(y1 < -m_background_1->getContentSize().height)
	{
		m_background_1->setPositionY(m_background_2->getPositionY()+m_background_2->getContentSize().height-2);
	}
	else if(y2 < -m_background_2->getContentSize().height)
	{
		m_background_2->setPositionY(m_background_1->getPositionY()+m_background_1->getContentSize().height-2);
	}
}
