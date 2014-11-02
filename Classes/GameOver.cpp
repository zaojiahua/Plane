#include "GameOver.h"

GameOver::GameOver(void)
{
}

GameOver::~GameOver(void)
{
}

Scene * GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	//设置背景图片
	auto background = Sprite::createWithSpriteFrameName("gameover.png");
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//添加回到游戏的菜单
	auto returnItem = MenuItemImage::create();
	returnItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_finish.png"));
	returnItem->setCallback(CC_CALLBACK_1(GameOver::backGame,this));
	auto menu = Menu::create(returnItem,NULL);
	menu->setPosition(Point(size.width/2,size.height*0.3));
	this->addChild(menu);

	//添加玩家得分
	auto score_int = UserDefault::getInstance()->getIntegerForKey("currentScore");
	auto score_str = __String::createWithFormat("%d",score_int);
	auto score = Label::createWithTTF(score_str->getCString(),"font/arial.ttf",40);
	score->setPosition(Point(size.width/2,size.height/2));
	score->setColor(Color3B(100,100,100));
	this->addChild(score);


	return true;
}

void GameOver::backGame(Ref * ref)
{
	//切换到开始游戏的场景
	Director::getInstance()->replaceScene(StartGame::createScene());
	Sound::getInstance()->playEffect(EFFECT_TYPE_BUTTON);
}