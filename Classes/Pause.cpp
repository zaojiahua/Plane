#include "Pause.h"


Pause::Pause(void)
{
}


Pause::~Pause(void)
{
}

Scene * Pause::createScene()
{
	auto scene = Scene::create();
	auto layer = Pause::create();
	scene->addChild(layer);

	return scene;
}

bool Pause::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	auto index = UserDefault::getInstance()->getIntegerForKey("index");
	auto str = __String::createWithFormat("pause%d.png",index-1);
	//CCFileUtils::sharedFileUtils()->getWritablePath();提供了一个可以存储的路径
	auto fullPath = FileUtils::getInstance()->getWritablePath() + str->getCString();
	//这里把截屏的那张图片做为背景图片
	auto background = Sprite::create(fullPath);
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//添加恢复游戏的按钮
	auto resume = MenuItemImage::create();
	resume->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("resume_button.png"));
	auto sound = Sound::getInstance();
	auto callback = [& sound](Ref * ref)
	{
		sound->playEffect(EFFECT_TYPE_BUTTON);
		//恢复背景音乐 Pause中恢复场景的时候调用
		sound->playBgMusic(MUSIC_TYPE_BACKGROUND);
		//弹出保存的场景
		Director::getInstance()->popScene();
	};
	resume->setCallback(callback);
	auto menu = Menu::create(resume,NULL);
	menu->setPosition(Point(size.width*0.95,size.height*0.97));
	this->addChild(menu);

	//loading的动画效果
	Vector<SpriteFrame *> vector;
	for(int i=0;i<6;i++)
	{
		auto str = __String::createWithFormat("loading_%d.png",i+1);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		vector.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.2f,-1);
	auto animate = Animate::create(animation);
	//设置用来执行动画的loading图片
	auto loading = Sprite::createWithSpriteFrameName("loading_1.png");
	loading->setPosition(Point(size.width*0.85,size.height*0.1));
	this->addChild(loading);

	loading->runAction(animate);

	return true;
}
