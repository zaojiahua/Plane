#include "MainGame.h"


MainGame::MainGame(void)
{
}


MainGame::~MainGame(void)
{
	//�Ƴ��¼�������
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_touchListener);
	//�ͷŹ�����
	Manager::freeInstance();
}

Scene * MainGame::createScene()
{
	auto scene = Scene::create();
	auto layer = MainGame::create();
	scene->addChild(layer);

	return scene;
}

//�ǵ�ж����Դ
void MainGame::onExit()
{
	//��ס����ķ���Ҫ�ȵ���
	Layer::onExit();
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("shoot.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

bool MainGame::init()
{
	if(!Layer::init())
		return false;

	m_size = Director::getInstance()->getWinSize();

	//��ӵ�ͼ��
	auto background = Background::create();
	this->addChild(background);

	//���android���ؼ��ļ�����
	m_listener = EventListenerKeyboard::create();
	m_listener->onKeyReleased = CC_CALLBACK_2(MainGame::onKeyReleased,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener,this);

	//���ؾ���֡����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

	//�����ҷɻ�
	m_player = Player::create();
	m_player->setPosition(Point(m_size.width/2,m_size.height*0.2));
	this->addChild(m_player);

	//ΪUFO��ʼ��
	this->m_ufo = NULL;
	//�ӵ����Ƶĳ�ʼ��
	this->m_bulletName = "bullet1.png";

	//���UI��
	m_ui = UILayer::create();
	this->addChild(m_ui);

	//���㴥���ļ�����
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan,this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved,this);
	//�������ɴ���
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener,this);

	//��ʼ����Ҽ���
	m_level = 0;

	return true;
}

//�����л���ϵ���
void MainGame::onEnterTransitionDidFinish()
{
	//�����ȵ��ø���ĺ���
	Layer::onEnterTransitionDidFinish();
	//��ӵл���ÿ�����һ��
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
	//����ӵ�
	this->schedule(SEL_SCHEDULE(&MainGame::addBullet),0.1f);
	//���UFO��ը����ÿʮ�����һ��UFO������ը��
	this->schedule(SEL_SCHEDULE(&MainGame::addUfo),10.0f);
	//��ײ���
	this->schedule(SEL_SCHEDULE(&MainGame::isHitEnemy));
}

//���UFO��ը��
void MainGame::addUfo(float tm)
{
	m_ufo = Ufo::create();
	int num = CCRANDOM_0_1()*3+1;
	//�ڲ�ͬ�ĸ�������Ӳ�ͬ����Ʒ
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
	//���߳��ֵ�ʱ�����Ч
	Sound::getInstance()->playEffect(EFFECT_TYPE_OUT_PORP);
	this->addChild(m_ufo);
}

//��ײ���
void MainGame::isHitEnemy(float tm)
{
	/*�ӵ��͵л�����ײ���*/

	//�ӹ������л���ӵ��͵л�����������
	auto & enemyVector = Manager::getInstance()->getEnemyVector();
	auto & bulletVector = Manager::getInstance()->getBulletVector();
	for(int i=enemyVector.size()-1;i>=0;i--)
	{
		//����л�����Ქ�Ŷ�����ʱ������ӹ��������Ƴ�����������Ҫ�ж�һ���Ƿ��Ѿ�����
		if(enemyVector.at(i)->getHp() == 0)
		{
			//����Ѿ�����Ͳ�Ҫ������ײ�����
			continue;
		}
		//��õл���rect
		auto rect = enemyVector.at(i)->getBoundingBox();
		for(int j=bulletVector.size()-1;j>=0;j--)
		{
			//�ж��ӵ���λ���Ƿ��ڵл���rect��Χ�ڣ�����ڣ���������ײ
			auto point = bulletVector.at(j)->getPosition();
			if(rect.containsPoint(point))
			{
				//�л�������ֵ����
				enemyVector.at(i)->setHp(enemyVector.at(i)->getHp()-1);
				//����Ļ�͹��������Ƴ��ӵ����л����Ƴ��Ѿ�д����blowup�����У�ע���������仰�ĵ���˳�򣬷���
				//������bug�����ų�
				bulletVector.at(j)->removeFromParentAndCleanup(true);
				bulletVector.eraseObject(bulletVector.at(j));
				//����ֵΪ0�л���ը,����л��Ѿ������Ͳ�Ҫ��ʣ�µ��ӵ������ж��ˣ�����Ҫbreak
				if(enemyVector.at(i)->getHp() == 0)
				{
					//��ը����
					enemyVector.at(i)->blowUp();
					//��ը����
					auto hp = enemyVector.at(i)->getOriginalHp();
					if(hp == 5)
						Sound::getInstance()->playEffect(EFFECT_TYPE_ENEMY1_DOWN);
					else if(hp == 10)
						Sound::getInstance()->playEffect(EFFECT_TYPE_ENEMY2_DOWN);
					else
						Sound::getInstance()->playEffect(EFFECT_TYPE_ENEMY3_DOWN);

					//�ı����
					auto saveData = m_ui->getSaveData();
					//���Ϸ�������������ǵл�������ֵ������getOriginalHp���¼ӵ�
					saveData->setScore(saveData->getScore()+hp);
					break;
				}
				else
				{
					//���ŵл����˵Ķ���
					enemyVector.at(i)->hit();
				}
			}
		}
	}

	/*��ҷɻ���UFO����ײ���*/

	//�ж��Ƿ������UFO���ǵ�UFOҪ��init�����г�ʼ��
	if(m_ufo != NULL)
	{
		auto rect = m_player->getBoundingBox();
		auto point = m_ufo->getPosition();
		//�����Һ�UFO��ײ����
		if(rect.containsPoint(point))
		{
			//���Ż�õ��ߵ�����
			Sound::getInstance()->playEffect(EFFECT_TYPE_GET_UFO);
			//������ײ���Ĳ�ͬ���ߣ�����ͬ�Ĵ���
			if(m_ufo->getName() == "ufo1.png")
			{
				//�����ӵ�������
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
			//����˫���ӵ�������ʱ����4s
			this->schedule(SEL_SCHEDULE(&MainGame::addBulletByUfo),0.1f,40,0);
			//ֹͣ�����ӵ��ķ���
			this->unschedule(SEL_SCHEDULE(&MainGame::addBullet));
			//4s���ٷ��䵥���ӵ�
			this->schedule(SEL_SCHEDULE(&MainGame::addBullet),0.1f,-1,4.0f);
			//�����ײ��⵽�ˣ����������UFOΪ���ɼ�����Ϊ�Ƴ��Ĺ�������UFOִ���궯���Ժ����
			m_ufo->setVisible(false);
			//��󽫳�Ա��������Ϊnull
			m_ufo = NULL;
		}
		//���UFO�뿪����Ļ������Ϊnull
		if(m_ufo != NULL && point.y < -m_ufo->getContentSize().height/2)
		{
			m_ufo = NULL;
		}
	}

	/*��ҷɻ��͵л�����ײ���*/
	for(auto enemy : enemyVector)
	{
		//����л�����Ქ�Ŷ�����ʱ������ӹ��������Ƴ�����������Ҫ�ж�һ���Ƿ��Ѿ�����
		if(enemy->getHp() == 0)
		{
			//����Ѿ�����Ͳ�Ҫ������ײ�����
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

//��Ϸ����
void MainGame::gameOver()
{
	//������Ϸ����
	this->m_ui->getSaveData()->save();

	//ֹͣ�����ӵ�
	this->unschedule(SEL_SCHEDULE(&MainGame::addBullet));
	this->unschedule(SEL_SCHEDULE(&MainGame::addBulletByUfo));

	//��ҷɻ�ը�ٵĶ���
	Vector<SpriteFrame *> vector;
	for(int i=0;i<4;i++)
	{
		auto frameName = __String::createWithFormat("hero_blowup_n%d.png",i+1);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		vector.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.3f,1);
	auto animate = Animate::create(animation);
	//�л�����
	auto func = []()
	{
		//����ը���Ĵ���������л��Ĵ�������ͬ��
		Director::getInstance()->replaceScene(GameOver::createScene());
	};
	//ִ�ж�������
	auto sequence = Sequence::create(animate,CallFunc::create(func),NULL);
	this->m_player->runAction(sequence);
	//������Ч
	Sound::getInstance()->playEffect(EFFECT_TYPE_GAME_OVER);
}

//����ҷɻ���UFO��ײ�Ժ�����ӵ�
void MainGame::addBulletByUfo(float tm)
{
	//����˫���ӵ�
	auto bullet1 = Bullet::create();
	bullet1->setVisible(false);
	bullet1->initBullet(m_bulletName);
	auto bullet2 = Bullet::create();
	bullet2->setVisible(false);
	bullet2->initBullet(m_bulletName);
	
	//����λ��
	auto point1 = Point(m_player->getPositionX()-23,
		m_player->getPositionY()+m_player->getContentSize().height/2+45);
	bullet1->setPosition(point1);
	auto point2 = Point(m_player->getPositionX()+23,
		m_player->getPositionY()+m_player->getContentSize().height/2+45);
	bullet2->setPosition(point2);
	
	//����ӵ�
	this->addChild(bullet1);
	this->addChild(bullet2);
	//���ӵ���ӵ���������
	auto & vector = Manager::getInstance()->getBulletVector();
	vector.pushBack(bullet1);
	vector.pushBack(bullet2);
	//���ŷ����ӵ�������
	Sound::getInstance()->playEffect(EFFECT_TYPE_BULLET);
	Sound::getInstance()->playEffect(EFFECT_TYPE_BULLET);
}

//����ӵ�
void MainGame::addBullet(float tm)
{
	auto bullet = Bullet::create();
	bullet->setVisible(false);
	bullet->initBullet(m_bulletName);
	auto point = Point(m_player->getPositionX(),
		m_player->getPositionY()+m_player->getContentSize().height/2+45);
	bullet->setPosition(point);
	
	this->addChild(bullet);
	//���ӵ���ӵ���������
	auto & vector = Manager::getInstance()->getBulletVector();
	vector.pushBack(bullet);
	//���ŷ����ӵ�������
	Sound::getInstance()->playEffect(EFFECT_TYPE_BULLET);
}

//��ӵл�
void MainGame::addEnemy(float tm)
{
	//�����Ǹ��ݷ������ı�л����ֵĿ���
	int score = m_ui->getSaveData()->getScore();
	//����scheduleֻ����һ�Σ�ʹ��level������
	if(score<50 && m_level == 0)
	{
		m_level = 1;
	}
	else if(score>50 && score<=200 && m_level == 1)
	{
		//���µ���schedule�����ʱ���
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

	/*���˴�Ϊֹ�������û���޸��ˣ��ϱ����޸Ĺ��Ĵ���*/

	auto enemy = EnemyBase::create();
	//���ݲ�ͬ�ĸ�������Ӳ�ͬ����ķɻ�
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
		//�л����õ��ı���ͼƬ��̫һ�������ﵥ���Ľ�����
		count = 6;
		enemy->initEnemy("enemy3_n1",count);
		//�����л����Ķ���
		Vector<SpriteFrame *> vector;
		vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		auto animation = Animation::createWithSpriteFrames(vector,0.2f,-1);
		auto animate = Animate::create(animation);
		enemy->runAction(animate);
		//��ӵ���ǰ�Ĳ���
		this->addChild(enemy);
		//���л���ӵ���������
		auto & enemyVector = Manager::getInstance()->getEnemyVector();
		enemyVector.pushBack(enemy);
		//ֱ�ӷ��أ�����ִ����������
		return;
	}
	//���µ���仰һ��Ҫ����
	auto str = __String::createWithFormat("enemy%d",enemy_x);
	enemy->initEnemy(str->getCString(),count);
	this->addChild(enemy);
	//���л���ӵ���������
	auto & vector = Manager::getInstance()->getEnemyVector();
	vector.pushBack(enemy);
}

//android���ؼ��ļ���
void MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	//�л�����ʼ��Ϸ����
	Director::getInstance()->replaceScene(StartGame::createScene());
	//�˳�֮ǰ�����û�����
	m_ui->getSaveData()->save();
	//�������
	Sound::getInstance()->playEffect(EFFECT_TYPE_BUTTON);
}

//���㴥���ļ�������
bool MainGame::onTouchBegan(Touch * touch,Event * pEvent)
{
	//��ô�����
	auto point = touch->getLocation();

	//�ж���ָ�Ƿ�������ͣ��ť����Ϊ��android����ָ�ĵ����Χ�е�С���������õĴ�һЩ
	auto menuRect = m_ui->getMenu()->getBoundingBox();
	//origin��ͼƬ�����Ͻǵ㣬�����rect���õķ�Χ��һЩ
	menuRect = Rect(menuRect.origin.x-menuRect.size.width*3,
		menuRect.origin.y-menuRect.size.height,menuRect.size.width*3,menuRect.size.height*2);
	if(menuRect.containsPoint(point))
	{
		m_ui->getMenu()->setSelectedIndex(1);
		m_ui->menuCallback(m_ui->getMenu());
	}

	//�ж���ָ����������Ƿ��ڷɻ���
	auto rect = m_player->getBoundingBox();
	if(rect.containsPoint(point))
		return true;

	return false;
}
void MainGame::onTouchMoved(Touch * touch,Event * pEvent)
{
	//������ָ�ƶ��ɻ���λ��
	auto addPoint = touch->getLocation()-touch->getPreviousLocation();
	m_player->setPosition(m_player->getPosition()+addPoint);

	//�жϷɻ��ƶ��ķ�Χ����Ҫ�����˱߽�
	auto size = m_player->getContentSize();
	//���x���������С�������Լ���ȵ�һ�㣬�����Ǵ�������Ļ�Ŀ�ȼ�ȥ�Լ���ȵ�һ��Ĵ�С��Խ����
	if(m_player->getPositionX() < size.width/2)
	{
		m_player->setPositionX(size.width/2);
	}
	else if(m_player->getPositionX() > m_size.width-size.width/2)
	{
		m_player->setPositionX(m_size.width-size.width/2);
	}
	//y�������x������жϷ�����������
	if(m_player->getPositionY() < size.height/2)
	{
		m_player->setPositionY(size.height/2);
	}
	else if(m_player->getPositionY() > m_size.height-size.height/2)
	{
		m_player->setPositionY(m_size.height-size.height/2);
	}
}
