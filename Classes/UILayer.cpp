#include "UILayer.h"


UILayer::UILayer(void)
{
}


UILayer::~UILayer(void)
{
	m_saveData->release();
}

bool UILayer::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	//��xml�ļ��ж�ȡ������ʾ����
	auto dictionary = Dictionary::createWithContentsOfFile("font/text.xml");
	score_label = Label::createWithTTF(((__String *)(dictionary->objectForKey("score")))->getCString(),"font/DFPShaoNvW5-GB.ttf",40);
	score_label->setPosition(score_label->getContentSize().width/2,
		size.height-score_label->getContentSize().height/2);
	this->addChild(score_label);

	//�����ʾ�����ı�ǩ
	m_saveData = SaveData::create();
	//����һ��Ҫretainһ��saveData��������������releaseһ��
	m_saveData->retain();
	auto str = __String::createWithFormat("%d",m_saveData->getScore());
	m_score = Label::createWithBMFont("font/font.fnt",str->getCString());
	m_score->setPosition(Point(score_label->getContentSize().width+m_score->getContentSize().width/2+30,
		size.height-score_label->getContentSize().height/2));
	this->addChild(m_score);
	//�ǵø��·�������ʾ
	this->scheduleUpdate();

	//�����Ϸ��ͣ�Ϳ�ʼ�Ŀ��ز˵�
	auto toggle1 = MenuItemImage::create();
	toggle1->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pause_button.png"));
	auto toggle2 = MenuItemImage::create();
	toggle2->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("resume_button.png"));
	menuToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UILayer::menuCallback,this),toggle1,toggle2,NULL);
	//�տ�ʼ����ѡ���index��0������������ͣ����indexΪ1��toggle�е�index�Ǵ�0��ʼ�ģ���һ����ӽ�ȥ��
	//item��indexΪ0
	menuToggle->setSelectedIndex(0);
	menuToggle->setPosition(Point(size.width*0.95,size.height*0.97));
	auto menu = Menu::create(menuToggle,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void UILayer::update(float tm)
{
	auto str = __String::createWithFormat("%d",m_saveData->getScore());
	//���·���������
	m_score->setString(str->getCString());
	m_score->setPositionX(score_label->getContentSize().width+m_score->getContentSize().width/2+30);
}

void UILayer::menuCallback(Ref * ref)
{
	auto toggle = (MenuItemToggle *)ref;
	//�����û�ѡ��Ĳ�ͬ����ͬ�Ĵ����տ�ʼ�������õ�ʱ����0��һ���ϵͳ�ͽ������л�����index����Ϊ��1
	if(toggle->getSelectedIndex() == 1)
	{
		//����ֱ��ʹ��pause������ͣ��ǰ�ĳ�����������������һ��bug�����ǲ��ܹ����δ����¼������Բ��ý�ͼ�ķ���
		//Director::getInstance()->pause();

		/*��ȡ��ǰ������ͼƬ���ұ���*/
		this->screenShoot();
		
		//�������Ĵ��� UILayer����ͣ��ť���µ�ʱ��
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

		//3.0������Ҫ�ڽ���������һ֡���ܴ���RenderTexture�����Ҫע��
		auto _schedule = this->getScheduler();
		auto replaceScene = [](float tm)
		{
			//����л�����
			Director::getInstance()->pushScene(Pause::createScene());
		};
		 _schedule->schedule(replaceScene, this, 0.0f,0,0.0f, false, "screenshot");

		 toggle->setSelectedIndex(0);
	}
}

//��Ļ��ͼ
void UILayer::screenShoot()
{
	auto size = Director::getInstance()->getWinSize();
	//RenderTexture��һ��������Ⱦ�࣬������Ҫ��Ҫ��Ⱦ�ĵ�ǰ�����Ž�ȥ�����ǳ�ʼ�����Ĵ�С
	auto render = RenderTexture::create(size.width,size.height);
	//��ʼ��ȡ����
	render->begin();
	//���ýڵ��visit�������뵽��Ⱦ��
	Director::getInstance()->getRunningScene()->visit();
	//����
	render->end();
		
	//����Ҫ�ر��˵��һ�£����������ļ������Ʋ��䣬���ڵڶ����Ժ���ͣ��ʱ���õ�ͼƬ���ǵ�һ�ε�ͼƬ
	//��Ȼ·���µ�ͼƬ�����˸ı䣬���ǵ�һ�ε�ͼƬ�Ѿ��ŵ��˻����У�����ʹ�����µķ������
	auto index = UserDefault::getInstance()->getIntegerForKey("index",0);
	UserDefault::getInstance()->setIntegerForKey("index",index+1);
	auto str = __String::createWithFormat("pause%d.png",index);

	//����ÿ�ν�ͼ���ı���ͼƬ�����ƣ��������豸�ϻ��кܶ��ͼƬ������Ҫ��֮ǰ��ͼƬɾ����
	if(index != 0)
	{
		auto str = __String::createWithFormat("pause%d.png",index-1);
		auto fullPath = FileUtils::getInstance()->getWritablePath() + str->getCString();
		if(FileUtils::getInstance()->isFileExist(fullPath))
		{
			remove(fullPath.c_str());
		}
	}

	//����ͼƬΪPNG��ʽ����������Ҫ��ȡ����ļ���ʱ��ʹ��
	//FileUtils::getInstance()->getWritablePath() + "pause.png";��ͨ����������Ϳ���ȡ�����Ǳ����ͼƬ��
	render->saveToFile(str->getCString(),Image::Format::PNG);
}