#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_
#include "cocos2d.h"
//������ͼ��
#include "Layer/Background.h"
//��ʼ��Ϸ����
#include "StartGame.h"
//�����
#include "Player\Player.h"
//�л���
#include "Enemy\EnemyBase.h"
//�ӵ���
#include "Bullet\Bullet.h"
//������
#include "Manager\Manager.h"
//UFO��
#include "Ufo\Ufo.h"
//ui��
#include "Layer\UILayer.h"
//��Ϸ��������
#include "GameOver.h"

USING_NS_CC;
//��Ϸ������
class MainGame : public Layer
{
public:
	MainGame(void);
	~MainGame(void);
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(MainGame);
	//ж����Դ
	void onExit();
public:
	//�Է��ؼ��ļ�������
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
	//��Ļ�����ļ�������
	bool onTouchBegan(Touch * touch,Event * pEvent);
	void onTouchMoved(Touch * touch,Event * pEvent);
	//�����л���ϵ���
	void onEnterTransitionDidFinish();
private:
	//������
	EventListenerKeyboard * m_listener;
	EventListenerTouchOneByOne * m_touchListener;
	//�豸��С
	Size m_size;
	//���
	Player * m_player;
	//UFO������ը��
	Ufo * m_ufo;
	//ui
	UILayer * m_ui;
	//�ӵ�����
	std::string m_bulletName;
	//��ӵл�
	void addEnemy(float tm);
	//����ӵ�
	void addBullet(float tm);
	//����ҷɻ���UFO��ײ�Ժ�����ӵ�
	void addBulletByUfo(float tm);
	//���UFO��ը��
	void addUfo(float tm);
	//��ײ���
	void isHitEnemy(float tm);
	//��Ҽ���
	int m_level;
	//��Ϸ����
	void gameOver();
};

#endif

