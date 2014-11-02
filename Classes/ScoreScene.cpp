#include "ScoreScene.h"

ScoreScene::ScoreScene(void)
{
}

ScoreScene::~ScoreScene(void)
{
	//�������������Ƴ������������ﴫ�ݵĲ���this������Ӽ��������¼��ַ����е�this
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

	//��ӱ���ͼƬ
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(Point(size.width/2,size.height/2));
	this->addChild(background);

	//����tableView������һЩ����
	auto tableView = TableView::create(this,Size(size.width,size.height*0.6));
	//���û�������
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//����TableViewDelegate
	tableView->setDelegate(this);
	//index�Ĵ�С�Ǵ��ϵ�����������
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//�õ�ǰ������ˢ��cell
	tableView->reloadData();
	this->addChild(tableView);

	//���а�
	auto rank = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	rank->setPosition(Point(size.width/2,size.height-rank->getContentSize().height));
	this->addChild(rank);

	//����
	auto rankNum = Label::createWithTTF("rank","font/arial.ttf",40);
	rankNum->setColor(Color3B(100,100,100));
	rankNum->setPosition(Point(size.width*0.4,size.height*0.7));
	this->addChild(rankNum);
	//�÷�
	auto rankScore = Label::createWithTTF("score","font/arial.ttf",40);
	rankScore->setPosition(Point(size.width*0.8,size.height*0.7));
	rankScore->setColor(Color3B(100,100,100));
	this->addChild(rankScore);

	//���û����ؼ�����Ӧ
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ScoreScene::onKeyReleased,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

//�Է��ؼ�����Ӧ
void ScoreScene::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		//����ʼ��������
		Director::getInstance()->popScene();
}

//��������ȽϹؼ�������������ÿ��cell�����ݵ�
TableViewCell * ScoreScene::tableCellAtIndex(TableView * table,ssize_t index)
{
	//����ÿ����¼ǰ�ߵ��ı�����
	auto index_text = __String::createWithFormat("%ld",index+1);

	//dequeuecell��������ǻ��һ�����õ�cell����Ϊ�������û����һ��������¼�ʹ���һ��cell�������֪���
	//������¼�ܶ�Ļ���cell���ǳ����Ķ��������ʱ���ڴ�ռ�þͻ�ܴ󣬶���������Ĺ����ǰ���Щû����Ⱦ��
	//cell�ù����������Ļ��ͼ�С���ڴ������
	TableViewCell * cell = table->dequeueCell();
	if(cell == NULL)
	{
		//����һ��cell
		cell = new TableViewCell();
		cell->autorelease();

		//������ʾ�������ı���Ϣ
		auto text = Label::createWithTTF(index_text->getCString(),"font/arial.ttf",24);
		text->setTag(1024);
		text->setColor(Color3B(100,100,100));
		//�ı���Ϣ��cell���м�
		text->setPosition(Point(size.width*0.4,size.height*0.025));
		cell->addChild(text);

		//��ʾ�û��÷ֵ��ı���Ϣ
		auto index_score = __String::createWithFormat("%d",index);
		//����indexֵ��õ÷ֵ��ı�����Ϊ���ʱ���score��int�ͣ����Ի���Ҫת��һ�����ͣ������е��鷳
		int i_score = UserDefault::getInstance()->getIntegerForKey(index_score->getCString());
		auto * str = __String::createWithFormat("%d",i_score);
		auto score = Label::createWithTTF(
			str->getCString(),"font/arial.ttf",24);
		score->setTag(2048);
		//��������
		score->setPosition(Point(size.width*0.8,size.height*0.025));
		score->setColor(Color3B(100,100,100));
		cell->addChild(score);

	}
	//�����õ�cell��ԭ����cell������ԭ��cell���ı���Ϣ�Ȼ���ԭ���ģ�����Ҫ��һЩ�ı�
	else
	{
		//ͨ��tagֵ����ı������Ҹı䣬��ȻLabelTTF����setString�������ã���������Ϊ��ʡ�¾���ô�ð�
		auto text = (Label *)cell->getChildByTag(1024);
		text->setString(index_text->getCString());

		//�ı����
		auto * score = (Label *)cell->getChildByTag(2048);
		auto * index_score = __String::createWithFormat("%d",index);
		//����indexֵ��õ÷ֵ��ı�����Ϊ���ʱ���score��int�ͣ����Ի���Ҫת��һ�����ͣ������е��鷳
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
			//������ǹھ�
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

//�����������������ÿ��cell�Ĵ�С��
Size ScoreScene::tableCellSizeForIndex(TableView * table,ssize_t index)
{
	return Size(size.width,size.height*0.05);
}

//�����������������cell�ĸ�����
ssize_t ScoreScene::numberOfCellsInTableView(TableView * table)
{
	//�����Ǵ�XML�ļ��ж�ȡ���ģ��ж�������¼�������ö��ٸ�cell������տ�ʼû��count����ֶΣ��ͷ���0
	int count = UserDefault::getInstance()->getIntegerForKey("count",0);

	return count;
}
