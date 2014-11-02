#ifndef _START_GAME_H_
#define _START_GAME_H_
#include "cocos2d.h"
//������Ϸ������
#include "MainGame.h"
//������
#include "ScoreScene.h"
//��������
#include "Sound\Sound.h"
//��������
#include "AboutMe.h"

USING_NS_CC;

class StartGame : public Layer
{
public:
	//�̳�layer��Ҫ��д�ļ�������
	static Scene * createScene();
	bool init();
	CREATE_FUNC(StartGame);
	//����Դ��ж�طŵ���������
	void onExit();
public:
	//����������������½���Ŀ��ʱ����Զ�Ϊ���ǽ������ˣ�vs���Ǻܷ����
	StartGame(void);
	~StartGame(void);
public:
	//����Ϸ��ʼ�˵�����Ӧ����
	void play(Ref * ref);
	//������˵�����Ӧ
	void scoreScene(Ref * ref);
	//��������
	void aboutMe(Ref * ref);
	//�Լ��̵���Ӧ����
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
private:
	//�¼�������
	EventListenerKeyboard * m_listener;
	//��������
	Sound * m_sound;
};

#endif

