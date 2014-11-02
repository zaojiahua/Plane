#include "EnemyBase.h"
#include "Manager\Manager.h"

EnemyBase::EnemyBase(void)
{
}


EnemyBase::~EnemyBase(void)
{
}

bool EnemyBase::init()
{
	if(!Sprite::init())
		return false;

	return true;
}

//���ﴫ���������������ʼ���л�
void EnemyBase::initEnemy(std::string name,int count)
{
	auto size = Director::getInstance()->getWinSize();

	//Ϊ��Ա������ֵ
	m_frameName = name;
	m_count = count;
	//������ַ���һ�������ַ�����ȥ�ַ�0���Ѫ��ֵ
	m_hp = (name[5]-'0')*5;

	//ʹ�þ���ͼƬ��ʼ��
	std::string str = name+".png";
	this->initWithSpriteFrameName(str);
	//�������갴�����µķ�������
	auto point = Point(getRandomNumber(this->getContentSize().width/2,size.width-this->getContentSize().width/2),
		size.height);
	this->setPosition(point);
}

//���Ҫ���a~b֮���һ�����������Ӧ����CCRANDOM_0_1*(b-a)+a������Ĳ�������a��b
int EnemyBase::getRandomNumber(int start,int end)
{
	return CCRANDOM_0_1()*(end-start)+start;
}

//�����л������
void EnemyBase::onEnterTransitionDidFinish()
{
	//�ȵ��ø����
	Sprite::onEnterTransitionDidFinish();
	//����schedule���������ı�л�������
	this->schedule(SEL_SCHEDULE(&EnemyBase::move));
}

//�л����ƶ�
void EnemyBase::move(float tm)
{
	auto point = this->getPositionY()-OFFSET;
	this->setPositionY(point);
	//����ƶ�������Ļ��Ӹ��ڵ����Ƴ�
	if(point < -this->getContentSize().height)
	{
		this->removeFromParentAndCleanup(true);
		//�ӹ��������Ƴ�
		auto & vector = Manager::getInstance()->getEnemyVector();
		vector.eraseObject(this);
	}
}

//�л���ը������������ǵл���Ļ��࣬���Եл������ֺ��õ��Ķ���֡���ǲ�ȷ���ģ���Ҫ�ڲ����д���
void EnemyBase::blowUp()
{
	Vector<SpriteFrame *> vector;
	for(int i=0;i<m_count;i++)
	{
		auto frameName = __String::createWithFormat("_down%d.png",i+1);
		//��������ַ�����frameNameƴ��������str�����ʹ�õ�spriteframe������
		std::string str = m_frameName+frameName->getCString();
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		vector.pushBack(spriteFrame);
	}
	//���ö���֡�ļ����ͬʱ����ִֻ��һ��
	auto animation = Animation::createWithSpriteFrames(vector,0.2f,1);
	auto animate = Animate::create(animation);
	//�Ƴ��Լ��Ķ���
	auto removeSelf = RemoveSelf::create();
	auto removeFromManager = CallFunc::create(CC_CALLBACK_0(EnemyBase::removeFromManager,this));
	auto sequence = Sequence::create(animate,removeSelf,removeFromManager,NULL);
	this->runAction(sequence);
}

//��ը��ϴӹ��������Ƴ��Լ�
void EnemyBase::removeFromManager()
{
	auto & vector = Manager::getInstance()->getEnemyVector();
	vector.eraseObject(this);
}

void EnemyBase::hit()
{
	int index = m_frameName[5]-'0';
	//�л�1û�����˵Ķ���
	if(index == 1)
		return;
	auto animation = Animation::create();
	//ʹ����������ͼƬ���Ŷ���Ч��
	std::string frameName1 = m_frameName+"_hit.png";
	auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName1);
	std::string frameName2 = m_frameName+".png";
	auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName2);
	animation->addSpriteFrame(spriteFrame1);
	animation->addSpriteFrame(spriteFrame2);
	animation->setDelayPerUnit(0.05f);
	animation->setLoops(2);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}
