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

	//从xml文件中读取中文显示出来
	auto dictionary = Dictionary::createWithContentsOfFile("font/text.xml");
	score_label = Label::createWithTTF(((__String *)(dictionary->objectForKey("score")))->getCString(),"font/DFPShaoNvW5-GB.ttf",40);
	score_label->setPosition(score_label->getContentSize().width/2,
		size.height-score_label->getContentSize().height/2);
	this->addChild(score_label);

	//添加显示分数的标签
	m_saveData = SaveData::create();
	//这里一定要retain一下saveData，在析构函数中release一下
	m_saveData->retain();
	auto str = __String::createWithFormat("%d",m_saveData->getScore());
	m_score = Label::createWithBMFont("font/font.fnt",str->getCString());
	m_score->setPosition(Point(score_label->getContentSize().width+m_score->getContentSize().width/2+30,
		size.height-score_label->getContentSize().height/2));
	this->addChild(m_score);
	//记得更新分数的显示
	this->scheduleUpdate();

	//添加游戏暂停和开始的开关菜单
	auto toggle1 = MenuItemImage::create();
	toggle1->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pause_button.png"));
	auto toggle2 = MenuItemImage::create();
	toggle2->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("resume_button.png"));
	menuToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UILayer::menuCallback,this),toggle1,toggle2,NULL);
	//刚开始设置选择的index是0，如果点击了暂停设置index为1，toggle中的index是从0开始的，第一个添加进去的
	//item的index为0
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
	//更新分数和坐标
	m_score->setString(str->getCString());
	m_score->setPositionX(score_label->getContentSize().width+m_score->getContentSize().width/2+30);
}

void UILayer::menuCallback(Ref * ref)
{
	auto toggle = (MenuItemToggle *)ref;
	//根据用户选择的不同做不同的处理，刚开始我们设置的时候是0，一点击系统就进行了切换，将index设置为了1
	if(toggle->getSelectedIndex() == 1)
	{
		//可以直接使用pause方法暂停当前的场景，但是这样做有一个bug，就是不能够屏蔽触摸事件，所以采用截图的方法
		//Director::getInstance()->pause();

		/*截取当前场景的图片并且保存*/
		this->screenShoot();
		
		//对声音的处理 UILayer中暂停按钮按下的时候
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

		//3.0截屏需要在截完屏的下一帧才能处理RenderTexture，这点要注意
		auto _schedule = this->getScheduler();
		auto replaceScene = [](float tm)
		{
			//最后切换场景
			Director::getInstance()->pushScene(Pause::createScene());
		};
		 _schedule->schedule(replaceScene, this, 0.0f,0,0.0f, false, "screenshot");

		 toggle->setSelectedIndex(0);
	}
}

//屏幕截图
void UILayer::screenShoot()
{
	auto size = Director::getInstance()->getWinSize();
	//RenderTexture是一个纹理渲染类，我们需要把要渲染的当前场景放进去，这是初始化它的大小
	auto render = RenderTexture::create(size.width,size.height);
	//开始获取内容
	render->begin();
	//是用节点的visit方法加入到渲染中
	Director::getInstance()->getRunningScene()->visit();
	//结束
	render->end();
		
	//这里要特别的说明一下，如果保存的文件的名称不变，那在第二次以后暂停的时候用的图片还是第一次的图片
	//虽然路径下的图片发生了改变，但是第一次的图片已经放到了缓存中，所以使用如下的方法解决
	auto index = UserDefault::getInstance()->getIntegerForKey("index",0);
	UserDefault::getInstance()->setIntegerForKey("index",index+1);
	auto str = __String::createWithFormat("pause%d.png",index);

	//我们每次截图都改变了图片的名称，这样在设备上会有很多的图片，所以要把之前的图片删除掉
	if(index != 0)
	{
		auto str = __String::createWithFormat("pause%d.png",index-1);
		auto fullPath = FileUtils::getInstance()->getWritablePath() + str->getCString();
		if(FileUtils::getInstance()->isFileExist(fullPath))
		{
			remove(fullPath.c_str());
		}
	}

	//保存图片为PNG格式，当我们想要获取这个文件的时候使用
	//FileUtils::getInstance()->getWritablePath() + "pause.png";，通过这个方法就可以取得我们保存的图片啦
	render->saveToFile(str->getCString(),Image::Format::PNG);
}