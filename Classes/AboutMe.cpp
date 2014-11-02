#include "AboutMe.h"

AboutMe::AboutMe(void)
{
}

AboutMe::~AboutMe(void)
{
	//�Ƴ�������
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

	//���ñ���ͼƬ
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//����logo
	auto logo = Sprite::create("xiaota_copyright.png");
	logo->setPosition(Point(size.width/2,size.height-logo->getContentSize().height));
	this->addChild(logo);

	//������
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(AboutMe::back,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//�����ı���Ϣ
	auto dictionary = Dictionary::createWithContentsOfFile("font/text.xml");
	auto label = Label::createWithTTF(((__String *)(dictionary->objectForKey("aboutme")))->getCString(),
		"font/DFPShaoNvW5-GB.ttf",30);
	label->setColor(Color3B(120,120,120));
	//�����ı����ı���Ĵ�СҪװ�������壬����ͳ�����
	label->setDimensions(size.width-80,size.height*0.5);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	label->setPosition(size.width/2,size.height*0.4);
	this->addChild(label);

	return true;
}

void AboutMe::back(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		Director::getInstance()->popScene();
}
