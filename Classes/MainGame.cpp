#include "MainGame.h"


MainGame::MainGame(void)
{
}


MainGame::~MainGame(void)
{
	//移除事件监听器
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_touchListener);
	//释放管理器
	Manager::freeInstance();
}

Scene * MainGame::createScene()
{
	auto scene = Scene::create();
	auto layer = MainGame::create();
	scene->addChild(layer);

	return scene;
}

//记得卸载资源
void MainGame::onExit()
{
	//记住父类的方法要先调用
	Layer::onExit();
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("shoot.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

bool MainGame::init()
{
	if(!Layer::init())
		return false;

	m_size = Director::getInstance()->getWinSize();

	//添加地图层
	auto background = Background::create();
	this->addChild(background);

	//添加android返回键的监听器
	m_listener = EventListenerKeyboard::create();
	m_listener->onKeyReleased = CC_CALLBACK_2(MainGame::onKeyReleased,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener,this);

	//加载精灵帧缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

	//添加玩家飞机
	m_player = Player::create();
	m_player->setPosition(Point(m_size.width/2,m_size.height*0.2));
	this->addChild(m_player);

	//为UFO初始化
	this->m_ufo = NULL;
	//子弹名称的初始化
	this->m_bulletName = "bullet1.png";

	//添加UI层
	m_ui = UILayer::create();
	this->addChild(m_ui);

	//单点触摸的监听器
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan,this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved,this);
	//设置吞噬触摸
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener,this);

	//初始化玩家级别
	m_level = 0;

	return true;
}

//场景切换完毕调用
void MainGame::onEnterTransitionDidFinish()
{
	//必须先调用父类的函数
	Layer::onEnterTransitionDidFinish();
	//添加敌机，每秒添加一个
	float tm = 1.0f;
	if(m_level == 1)
		tm = 0.8f;
	else if(m_level == 2)
		tm = 0.5f;
	else if(m_level == 3)
		tm = 0.4f;
	else if(m_level == 4)
		tm = 0.3f;
	this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),tm);
	//添加子弹
	this->schedule(SEL_SCHEDULE(&MainGame::addBullet),0.1f);
	//添加UFO和炸弹，每十秒出现一个UFO或者是炸弹
	this->schedule(SEL_SCHEDULE(&MainGame::addUfo),10.0f);
	//碰撞检测
	this->schedule(SEL_SCHEDULE(&MainGame::isHitEnemy));
}

//添加UFO和炸弹
void MainGame::addUfo(float tm)
{
	m_ufo = Ufo::create();
	int num = CCRANDOM_0_1()*3+1;
	//在不同的概率下添加不同的物品
	if(num == 1)
	{
		m_ufo->initUfo("ufo1.png");
	}
	else if(num == 2)
	{
		m_ufo->initUfo("ufo2.png");
	}
	else
	{
		m_ufo->initUfo("bomb.png");
	}
	//道具出现的时候的音效
	Sound::getInstance()->playEffect(EFFECT_TYPE_OUT_PORP);
	this->addChild(m_ufo);
}

//碰撞检测
void MainGame::isHitEnemy(float tm)
{
	/*子弹和敌机的碰撞检测*/

	//从管理器中获得子弹和敌机的数组引用
	auto & enemyVector = Manager::getInstance()->getEnemyVector();
	auto & bulletVector = Manager::getInstance()->getBulletVector();
	for(int i=enemyVector.size()-1;i>=0;i--)
	{
		//如果敌机毁灭会播放动画暂时还不会从管理器中移除，所以这里要判断一下是否已经毁灭
		if(enemyVector.at(i)->getHp() == 0)
		{
			//如果已经毁灭就不要进行碰撞检测了
			continue;
		}
		//获得敌机的rect
		auto rect = enemyVector.at(i)->getBoundingBox();
		for(int j=bulletVector.size()-1;j>=0;j--)
		{
			//判断子弹的位置是否在敌机的rect范围内，如果在，则满足碰撞
			auto point = bulletVector.at(j)->getPosition();
			if(rect.containsPoint(point))
			{
				//敌机的生命值减掉
				enemyVector.at(i)->setHp(enemyVector.at(i)->getHp()-1);
				//从屏幕和管理器中移除子弹，敌机的移除已经写在了blowup函数中，注意以下俩句话的调用顺序，否则
				//产生的bug很难排除
				bulletVector.at(j)->removeFromParentAndCleanup(true);
				bulletVector.eraseObject(bulletVector.at(j));
				//生命值为0敌机爆炸,如果敌机已经死亡就不要和剩下的子弹进行判断了，所以要break
				if(enemyVector.at(i)->getHp() == 0)
				{
					//爆炸动画
					enemyVector.at(i)->blowUp();
					//爆炸声音
					auto hp = enemyVector.at(i)->getOriginalHp();
					if(hp == 5)
						Sound::getInstance()->playEffect(EFFECT_TYPE_ENEMY1_DOWN);
					else if(hp == 10)
						Sound::getInstance()->playEffect(EFFECT_TYPE_ENEMY2_DOWN);
					else
						Sound::getInstance()->playEffect(EFFECT_TYPE_ENEMY3_DOWN);

					//改变分数
					auto saveData = m_ui->getSaveData();
					//加上分数，这个分数是敌机的生命值，函数getOriginalHp是新加的
					saveData->setScore(saveData->getScore()+hp);
					break;
				}
				else
				{
					//播放敌机受伤的动画
					enemyVector.at(i)->hit();
				}
			}
		}
	}

	/*玩家飞机和UFO的碰撞检测*/

	//判断是否添加了UFO，记得UFO要在init函数中初始化
	if(m_ufo != NULL)
	{
		auto rect = m_player->getBoundingBox();
		auto point = m_ufo->getPosition();
		//如何玩家和UFO碰撞到了
		if(rect.containsPoint(point))
		{
			//播放获得道具的声音
			Sound::getInstance()->playEffect(EFFECT_TYPE_GET_UFO);
			//根据碰撞到的不同道具，做不同的处理
			if(m_ufo->getName() == "ufo1.png")
			{
				//设置子弹的名称
				m_bulletName = "bullet2.png";
			}
			else if(m_ufo->getName() == "ufo2.png")
			{
				m_bulletName = "bullet1.png";
			}
			else
			{
				this->gameOver();
				return;
			}
			//发射双发子弹，持续时间是4s
			this->schedule(SEL_SCHEDULE(&MainGame::addBulletByUfo),0.1f,40,0);
			//停止单发子弹的发射
			this->unschedule(SEL_SCHEDULE(&MainGame::addBullet));
			//4s后再发射单发子弹
			this->schedule(SEL_SCHEDULE(&MainGame::addBullet),0.1f,-1,4.0f);
			//如果碰撞检测到了，则设置这个UFO为不可见，因为移除的工作会在UFO执行完动作以后进行
			m_ufo->setVisible(false);
			//最后将成员变量设置为null
			m_ufo = NULL;
		}
		//如果UFO离开了屏幕就设置为null
		if(m_ufo != NULL && point.y < -m_ufo->getContentSize().height/2)
		{
			m_ufo = NULL;
		}
	}

	/*玩家飞机和敌机的碰撞检测*/
	for(auto enemy : enemyVector)
	{
		//如果敌机毁灭会播放动画暂时还不会从管理器中移除，所以这里要判断一下是否已经毁灭
		if(enemy->getHp() == 0)
		{
			//如果已经毁灭就不要进行碰撞检测了
			continue;
		}

		auto rect = this->m_player->getBoundingBox();
		auto point = enemy->getPosition();
		if(rect.containsPoint(point))
		{
			this->gameOver();
		}
	}
}

//游戏结束
void MainGame::gameOver()
{
	//保存游戏数据
	this->m_ui->getSaveData()->save();

	//停止发射子弹
	this->unschedule(SEL_SCHEDULE(&MainGame::addBullet));
	this->unschedule(SEL_SCHEDULE(&MainGame::addBulletByUfo));

	//玩家飞机炸毁的动画
	Vector<SpriteFrame *> vector;
	for(int i=0;i<4;i++)
	{
		auto frameName = __String::createWithFormat("hero_blowup_n%d.png",i+1);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		vector.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.3f,1);
	auto animate = Animate::create(animation);
	//切换场景
	auto func = []()
	{
		//碰到炸弹的处理和碰到敌机的处理是相同的
		Director::getInstance()->replaceScene(GameOver::createScene());
	};
	//执行动作序列
	auto sequence = Sequence::create(animate,CallFunc::create(func),NULL);
	this->m_player->runAction(sequence);
	//播放音效
	Sound::getInstance()->playEffect(EFFECT_TYPE_GAME_OVER);
}

//当玩家飞机和UFO碰撞以后添加子弹
void MainGame::addBulletByUfo(float tm)
{
	//创建双发子弹
	auto bullet1 = Bullet::create();
	bullet1->setVisible(false);
	bullet1->initBullet(m_bulletName);
	auto bullet2 = Bullet::create();
	bullet2->setVisible(false);
	bullet2->initBullet(m_bulletName);
	
	//设置位置
	auto point1 = Point(m_player->getPositionX()-23,
		m_player->getPositionY()+m_player->getContentSize().height/2+45);
	bullet1->setPosition(point1);
	auto point2 = Point(m_player->getPositionX()+23,
		m_player->getPositionY()+m_player->getContentSize().height/2+45);
	bullet2->setPosition(point2);
	
	//添加子弹
	this->addChild(bullet1);
	this->addChild(bullet2);
	//将子弹添加到管理器中
	auto & vector = Manager::getInstance()->getBulletVector();
	vector.pushBack(bullet1);
	vector.pushBack(bullet2);
	//播放发射子弹的声音
	Sound::getInstance()->playEffect(EFFECT_TYPE_BULLET);
	Sound::getInstance()->playEffect(EFFECT_TYPE_BULLET);
}

//添加子弹
void MainGame::addBullet(float tm)
{
	auto bullet = Bullet::create();
	bullet->setVisible(false);
	bullet->initBullet(m_bulletName);
	auto point = Point(m_player->getPositionX(),
		m_player->getPositionY()+m_player->getContentSize().height/2+45);
	bullet->setPosition(point);
	
	this->addChild(bullet);
	//将子弹添加到管理器中
	auto & vector = Manager::getInstance()->getBulletVector();
	vector.pushBack(bullet);
	//播放发射子弹的声音
	Sound::getInstance()->playEffect(EFFECT_TYPE_BULLET);
}

//添加敌机
void MainGame::addEnemy(float tm)
{
	//这里是根据分数来改变敌机出现的快慢
	int score = m_ui->getSaveData()->getScore();
	//更新schedule只更新一次，使用level来控制
	if(score<50 && m_level == 0)
	{
		m_level = 1;
	}
	else if(score>50 && score<=200 && m_level == 1)
	{
		//重新调用schedule会更新时间的
		this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.8f);
		m_level = 2;
	}
	else if(score>200 && score<=400 && m_level == 2)
	{
		this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.5f);
		m_level = 3;
	}
	else if(score>400 && score<=800 && m_level == 3)
	{
		this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.4f);
		m_level = 4;
	}
	else if(score>800 && m_level == 4)
	{
		this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.3f);
		m_level = 5;
	}

	/*到此处为止，代码就没有修改了，上边是修改过的代码*/

	auto enemy = EnemyBase::create();
	//根据不同的概率来添加不同种类的飞机
	int enemy_x = CCRANDOM_0_1()*9+1;
	int count = 0;
	if(enemy_x > 0 && enemy_x <7)
	{
		enemy_x = 1;
		count = 4;
	}
	else if(enemy_x >= 7 && enemy_x < 9)
	{
		enemy_x = 2;
		count = 4;
	}
	else
	{
		//敌机三用到的背景图片不太一样，这里单独的建立下
		count = 6;
		enemy->initEnemy("enemy3_n1",count);
		//创建敌机三的动画
		Vector<SpriteFrame *> vector;
		vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		auto animation = Animation::createWithSpriteFrames(vector,0.2f,-1);
		auto animate = Animate::create(animation);
		enemy->runAction(animate);
		//添加到当前的层中
		this->addChild(enemy);
		//将敌机添加到管理器中
		auto & enemyVector = Manager::getInstance()->getEnemyVector();
		enemyVector.pushBack(enemy);
		//直接返回，不再执行下面的语句
		return;
	}
	//以下的这句话一定要调用
	auto str = __String::createWithFormat("enemy%d",enemy_x);
	enemy->initEnemy(str->getCString(),count);
	this->addChild(enemy);
	//将敌机添加到管理器中
	auto & vector = Manager::getInstance()->getEnemyVector();
	vector.pushBack(enemy);
}

//android返回键的监听
void MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	//切换到开始游戏场景
	Director::getInstance()->replaceScene(StartGame::createScene());
	//退出之前保存用户数据
	m_ui->getSaveData()->save();
	//添加声音
	Sound::getInstance()->playEffect(EFFECT_TYPE_BUTTON);
}

//单点触摸的监听函数
bool MainGame::onTouchBegan(Touch * touch,Event * pEvent)
{
	//获得触摸点
	auto point = touch->getLocation();

	//判断手指是否点击了暂停按钮，因为在android上手指的点击范围有点小，这里设置的大一些
	auto menuRect = m_ui->getMenu()->getBoundingBox();
	//origin是图片的左上角点，这里把rect设置的范围大一些
	menuRect = Rect(menuRect.origin.x-menuRect.size.width*3,
		menuRect.origin.y-menuRect.size.height,menuRect.size.width*3,menuRect.size.height*2);
	if(menuRect.containsPoint(point))
	{
		m_ui->getMenu()->setSelectedIndex(1);
		m_ui->menuCallback(m_ui->getMenu());
	}

	//判断手指点击的区域是否在飞机上
	auto rect = m_player->getBoundingBox();
	if(rect.containsPoint(point))
		return true;

	return false;
}
void MainGame::onTouchMoved(Touch * touch,Event * pEvent)
{
	//跟随手指移动飞机的位置
	auto addPoint = touch->getLocation()-touch->getPreviousLocation();
	m_player->setPosition(m_player->getPosition()+addPoint);

	//判断飞机移动的范围，不要超出了边界
	auto size = m_player->getContentSize();
	//如果x方向的坐标小于了它自己宽度的一般，或者是大于了屏幕的宽度减去自己宽度的一半的大小就越界了
	if(m_player->getPositionX() < size.width/2)
	{
		m_player->setPositionX(size.width/2);
	}
	else if(m_player->getPositionX() > m_size.width-size.width/2)
	{
		m_player->setPositionX(m_size.width-size.width/2);
	}
	//y方向根据x方向的判断方法进行类推
	if(m_player->getPositionY() < size.height/2)
	{
		m_player->setPositionY(size.height/2);
	}
	else if(m_player->getPositionY() > m_size.height-size.height/2)
	{
		m_player->setPositionY(m_size.height-size.height/2);
	}
}
