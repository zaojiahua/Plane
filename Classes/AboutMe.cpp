#include "AboutMe.h"
#include "WapsAd.h"

AboutMe::AboutMe(void)
{
}

AboutMe::~AboutMe(void)
{
	//移除监听器
	_eventDispatcher->removeEventListenersForTarget(this);
}

Scene * AboutMe::createScene()
{
	auto scene = Scene::create();
	auto layer = AboutMe::create();
	scene->addChild(layer);

	return scene;
}

bool AboutMe::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	//设置背景图片
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//设置logo
	auto logo = Sprite::create("xiaota_copyright.png");
	logo->setPosition(Point(size.width/2,size.height-logo->getContentSize().height));
	this->addChild(logo);

	//监听器
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(AboutMe::back,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//设置文本信息
	auto dictionary = Dictionary::createWithContentsOfFile("font/text.xml");
	auto label = Label::createWithTTF(((__String *)(dictionary->objectForKey("aboutme")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",30);
	label->setColor(Color3B(120,120,120));
	//设置文本域，文本域的大小要装的下字体，否则就出错了
	label->setDimensions(size.width-80,size.height*0.5);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	label->setPosition(size.width/2,size.height*0.4);
	this->addChild(label);
    
    //调用banner广告
    WapsAd::showAd(13);

	return true;
}

void AboutMe::back(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		Director::getInstance()->popScene();
}
