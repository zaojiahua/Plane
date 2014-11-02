#include "StartGame.h"

StartGame::StartGame(void)
{
	//���ű�������
	m_sound = Sound::getInstance();
	m_sound->playBgMusic(MUSIC_TYPE_BACKGROUND);
}

StartGame::~StartGame(void)
{
	//�Ƴ�������
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}

Scene * StartGame::createScene()
{
	 auto scene = Scene::create();
	auto layer = StartGame::create();
	scene->addChild(layer);

	return scene;
}

//�ǵ�ж����Դ
void StartGame::onExit()
{
	//��ס����ķ���Ҫ�ȵ���
	Layer::onExit();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

bool StartGame::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	//���ػ����ļ�
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui.plist");

	//ʹ�û����ļ���������
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//����logo
	auto logo = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	logo->setPosition(Point(size.width/2,size.height-logo->getContentSize().height));
	//����͸������0
	logo->setOpacity(0);
	this->addChild(logo);

	//����logo�Ķ���
	auto fade = FadeIn::create(1.0f);
	logo->runAction(fade);

	//���ÿ�ʼ��Ϸ�������Ķ���
	auto animation = Animation::create();
	for(int i=0;i<4;i++)
	{
		auto spriteFrameName = String::createWithFormat("game_loading%d.png",i+1);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(-1);
	//ָ����һִ֡��loading����
	auto sprite = Sprite::createWithSpriteFrameName("game_loading1.png");
	sprite->setPosition(size.width/2,size.height*0.6);
	this->addChild(sprite);
	//����
	auto animate = Animate::create(animation);
	sprite->runAction(animate);

	//��xml�ļ��ж�ȡ������ʾ����
	auto dictionary = Dictionary::createWithContentsOfFile("font/text.xml");
	
	//���һ����Ϸ��ʼ��ť
	auto playText = Label::createWithTTF(((__String *)(dictionary->objectForKey("play")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",40);
	playText->setColor(Color3B(100,100,100));
	auto playMenu = MenuItemLabel::create(playText,CC_CALLBACK_1(StartGame::play,this));

	//��ӷ�����ť
	auto scoreText = Label::createWithTTF(((__String *)(dictionary->objectForKey("scoreMenu")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",40);
	scoreText->setColor(Color3B(100,100,100));
	auto scoreMenu = MenuItemLabel::create(scoreText,CC_CALLBACK_1(StartGame::scoreScene,this));

	//��ӹ������߲˵�
	auto authorText = Label::createWithTTF(((__String *)(dictionary->objectForKey("aboutMe")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",40);
	authorText->setColor(Color3B(100,100,100));
	auto authorMenu = MenuItemLabel::create(authorText,CC_CALLBACK_1(StartGame::aboutMe,this));

	auto menu = Menu::create(playMenu,scoreMenu,authorMenu,NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setPosition(size.width/2,size.height*0.3);
	this->addChild(menu);

	//���ֻ����ؼ��ļ���
	m_listener = EventListenerKeyboard::create();
	//�ͻص�������
	m_listener->onKeyReleased = CC_CALLBACK_2(StartGame::onKeyReleased,this);
	//��ӵ��¼��ַ�����
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener,this);
	
	return true;
}
//��������Ӧ����
void StartGame::scoreScene(Ref * ref)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	Director::getInstance()->pushScene(ScoreScene::createScene());
}
//����������Ӧ����
void StartGame::aboutMe(Ref * ref)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	Director::getInstance()->pushScene(AboutMe::createScene());
}

//��android���ؼ�����Ӧ����
void StartGame::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	m_sound->freeInstance();
	Director::getInstance()->end();
}
//��ʼ��Ϸ��ť����Ӧ����
void StartGame::play(Ref * ref)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	//�л�����
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f,MainGame::createScene(),false));
}

