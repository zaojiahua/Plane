#ifndef _START_GAME_H_
#define _START_GAME_H_
#include "cocos2d.h"
//包含游戏主场景
#include "MainGame.h"
//分数榜
#include "ScoreScene.h"
//声音处理
#include "Sound.h"
//关于作者
#include "AboutMe.h"

USING_NS_CC;

class StartGame : public Layer
{
public:
	//继承layer需要覆写的几个函数
	static Scene * createScene();
	bool init();
	CREATE_FUNC(StartGame);
	//将资源的卸载放到这里来做
	void onExit();
public:
	//构造和析构函数，新建项目的时候就自动为我们建立好了，vs还是很方便的
	StartGame(void);
	~StartGame(void);
public:
	//对游戏开始菜单的响应函数
	void play(Ref * ref);
	//分数榜菜单的响应
	void scoreScene(Ref * ref);
	//关于作者
	void aboutMe(Ref * ref);
	//对键盘的响应函数
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
private:
	//事件监听器
	EventListenerKeyboard * m_listener;
	//声音处理
	Sound * m_sound;
};

#endif

