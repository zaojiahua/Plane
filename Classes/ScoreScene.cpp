#include "ScoreScene.h"
#include "WapsAd.h"

ScoreScene::ScoreScene(void)
{
}

ScoreScene::~ScoreScene(void)
{
	//在析构函数中移除监听器，这里传递的参数this就是添加监听器到事件分发器中的this
	_eventDispatcher->removeEventListenersForTarget(this);
}

Scene * ScoreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ScoreScene::create();
	scene->addChild(layer);
	return scene;
}

bool ScoreScene::init()
{
	if(!Layer::init())
		return false;

	size = Director::getInstance()->getWinSize();

	//添加背景图片
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//创建tableView并设置一些参数
	auto tableView = TableView::create(this,Size(size.width,size.height*0.6));
	//设置滑动方向
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//设置TableViewDelegate
	tableView->setDelegate(this);
	//index的大小是从上到下依次增大
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//用当前的配置刷新cell
	tableView->reloadData();
	this->addChild(tableView);

	//排行榜
	auto rank = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	rank->setPosition(Point(size.width/2,size.height-rank->getContentSize().height));
	this->addChild(rank);

	//排名
	auto rankNum = Label::createWithTTF("rank","font/arial.ttf",40);
	rankNum->setColor(Color3B(100,100,100));
	rankNum->setPosition(Point(size.width*0.4,size.height*0.7));
	this->addChild(rankNum);
	//得分
	auto rankScore = Label::createWithTTF("score","font/arial.ttf",40);
	rankScore->setPosition(Point(size.width*0.8,size.height*0.7));
	rankScore->setColor(Color3B(100,100,100));
	this->addChild(rankScore);

	//对用户返回键的响应
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ScoreScene::onKeyReleased,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    //调用迷你广告
    WapsAd::showAd(14);

	return true;
}

//对返回键的响应
void ScoreScene::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		//将开始场景弹出
		Director::getInstance()->popScene();
    WapsAd::uninstallAd(14);
}

//这个函数比较关键，是用来设置每个cell的内容的
TableViewCell * ScoreScene::tableCellAtIndex(TableView * table,ssize_t index)
{
	//设置每条记录前边的文本内容
	auto index_text = __String::createWithFormat("%ld",index+1);

	//dequeuecell这个函数是获得一个可用的cell，因为如果我们没增加一条分数记录就创建一个cell，可想而知如果
	//分数记录很多的话，cell不是超级的多了吗，这个时候内存占用就会很大，而这个函数的功能是把那些没有渲染的
	//cell拿过来，这样的话就减小了内存的消耗
	TableViewCell * cell = table->dequeueCell();
	if(cell == NULL)
	{
		//创建一个cell
		cell = new TableViewCell();
		cell->autorelease();

		//创建显示排名的文本信息
		auto text = Label::createWithTTF(index_text->getCString(),"font/arial.ttf",24);
		text->setTag(1024);
		text->setColor(Color3B(100,100,100));
		//文本信息在cell的中间
		text->setPosition(Point(size.width*0.4,size.height*0.025));
		cell->addChild(text);

		//显示用户得分的文本信息
		auto index_score = __String::createWithFormat("%d",index);
		//根据index值获得得分的文本，因为这个时候的score是int型，所以还需要转化一下类型，这里有点麻烦
		int i_score = UserDefault::getInstance()->getIntegerForKey(index_score->getCString());
		auto * str = __String::createWithFormat("%d",i_score);
		auto score = Label::createWithTTF(
			str->getCString(),"font/arial.ttf",24);
		score->setTag(2048);
		//设置坐标
		score->setPosition(Point(size.width*0.8,size.height*0.025));
		score->setColor(Color3B(100,100,100));
		cell->addChild(score);

	}
	//这里获得的cell是原来的cell，所以原来cell的文本信息等还是原来的，所以要做一些改变
	else
	{
		//通过tag值获得文本，并且改变，虽然LabelTTF调用setString函数不好，但是这里为了省事就这么用吧
		auto text = (Label *)cell->getChildByTag(1024);
		text->setString(index_text->getCString());

		//改变分数
		auto * score = (Label *)cell->getChildByTag(2048);
		auto * index_score = __String::createWithFormat("%d",index);
		//根据index值获得得分的文本，因为这个时候的score是int型，所以还需要转化一下类型，这里有点麻烦
		int i_score = UserDefault::getInstance()->getIntegerForKey(index_score->getCString());
		auto * str = __String::createWithFormat("%d",i_score);
		score->setString(str->getCString());

		if(cell->getChildByTag(100) != NULL)
		{
			Sprite * sprite = (Sprite *)cell->getChildByTag(100);
			sprite->removeFromParentAndCleanup(true);
		}
	}

	if(index == 0 || index==1 || index==2)
	{
		Sprite * sprite;
		switch(index)
		{
			//代表的是冠军
		case 0:
			sprite = Sprite::create("gold.png");
			break;
		case 1:
			sprite = Sprite::create("silvere.png");
			break;
		case 2:
			sprite = Sprite::create("tong.png");
			break;
		}
		sprite->setPosition(Point(size.width*0.15,size.height*0.025));
		sprite->setTag(100);
		cell->addChild(sprite);
	}

	return cell;
}

//这个函数是用来设置每个cell的大小的
Size ScoreScene::tableCellSizeForIndex(TableView * table,ssize_t index)
{
	return Size(size.width,size.height*0.05);
}

//这个函数是用来设置cell的个数的
ssize_t ScoreScene::numberOfCellsInTableView(TableView * table)
{
	//个数是从XML文件中读取到的，有多少条记录，就设置多少个cell，如果刚开始没有count这个字段，就返回0
	int count = UserDefault::getInstance()->getIntegerForKey("count",0);

	return count;
}
