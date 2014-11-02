#include "StartGame.h"

StartGame::StartGame(void)
{
	//播放背景音乐
	m_sound = Sound::getInstance();
	m_sound->playBgMusic(MUSIC_TYPE_BACKGROUND);
}

StartGame::~StartGame(void)
{
	//移除监听器
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}

Scene * StartGame::createScene()
{
	 auto scene = Scene::create();
	auto layer = StartGame::create();
	scene->addChild(layer);

	return scene;
}

//记得卸载资源
void StartGame::onExit()
{
	//记住父类的方法要先调用
	Layer::onExit();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

bool StartGame::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	//加载缓存文件
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui.plist");

	//使用缓存文件创建精灵
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//设置logo
	auto logo = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	logo->setPosition(Point(size.width/2,size.height-logo->getContentSize().height));
	//设置透明度是0
	logo->setOpacity(0);
	this->addChild(logo);

	//设置logo的动作
	auto fade = FadeIn::create(1.0f);
	logo->runAction(fade);

	//设置开始游戏场景处的动画
	auto animation = Animation::create();
	for(int i=0;i<4;i++)
	{
		auto spriteFrameName = String::createWithFormat("game_loading%d.png",i+1);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(-1);
	//指定第一帧执行loading动画
	auto sprite = Sprite::createWithSpriteFrameName("game_loading1.png");
	sprite->setPosition(size.width/2,size.height*0.6);
	this->addChild(sprite);
	//动作
	auto animate = Animate::create(animation);
	sprite->runAction(animate);

	//从xml文件中读取中文显示出来
	auto dictionary = Dictionary::createWithContentsOfFile("font/text.xml");
	
	//添加一个游戏开始按钮
	auto playText = Label::createWithTTF(((__String *)(dictionary->objectForKey("play")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",40);
	playText->setColor(Color3B(100,100,100));
	auto playMenu = MenuItemLabel::create(playText,CC_CALLBACK_1(StartGame::play,this));

	//添加分数榜按钮
	auto scoreText = Label::createWithTTF(((__String *)(dictionary->objectForKey("scoreMenu")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",40);
	scoreText->setColor(Color3B(100,100,100));
	auto scoreMenu = MenuItemLabel::create(scoreText,CC_CALLBACK_1(StartGame::scoreScene,this));

	//添加关于作者菜单
	auto authorText = Label::createWithTTF(((__String *)(dictionary->objectForKey("aboutMe")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",40);
	authorText->setColor(Color3B(100,100,100));
	auto authorMenu = MenuItemLabel::create(authorText,CC_CALLBACK_1(StartGame::aboutMe,this));

	auto menu = Menu::create(playMenu,scoreMenu,authorMenu,NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setPosition(size.width/2,size.height*0.3);
	this->addChild(menu);

	//对手机返回键的监听
	m_listener = EventListenerKeyboard::create();
	//和回调函数绑定
	m_listener->onKeyReleased = CC_CALLBACK_2(StartGame::onKeyReleased,this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener,this);
	
	return true;
}
//分数榜响应函数
void StartGame::scoreScene(Ref * ref)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	Director::getInstance()->pushScene(ScoreScene::createScene());
}
//关于作者响应函数
void StartGame::aboutMe(Ref * ref)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	Director::getInstance()->pushScene(AboutMe::createScene());
}

//对android返回键的响应函数
void StartGame::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	m_sound->freeInstance();
	Director::getInstance()->end();
}
//开始游戏按钮的响应函数
void StartGame::play(Ref * ref)
{
	m_sound->playEffect(EFFECT_TYPE_BUTTON);
	//切换场景
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f,MainGame::createScene(),false));
}

