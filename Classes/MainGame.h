#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_
#include "cocos2d.h"
//包含地图层
#include "Background.h"
//开始游戏场景
#include "StartGame.h"
//玩家类
#include "Player.h"
//敌机类
#include "EnemyBase.h"
//子弹类
#include "Bullet.h"
//管理类
#include "Manager.h"
//UFO类
#include "Ufo.h"
//ui层
#include "UILayer.h"
//游戏结束场景
#include "GameOver.h"

USING_NS_CC;
//游戏主场景
class MainGame : public Layer
{
public:
	MainGame(void);
	~MainGame(void);
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(MainGame);
	//卸载资源
	void onExit();
public:
	//对返回键的监听函数
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
	//屏幕触摸的监听函数
	bool onTouchBegan(Touch * touch,Event * pEvent);
	void onTouchMoved(Touch * touch,Event * pEvent);
	//场景切换完毕调用
	void onEnterTransitionDidFinish();
private:
	//监听器
	EventListenerKeyboard * m_listener;
	EventListenerTouchOneByOne * m_touchListener;
	//设备大小
	Size m_size;
	//玩家
	Player * m_player;
	//UFO或者是炸弹
	Ufo * m_ufo;
	//ui
	UILayer * m_ui;
	//子弹名称
	std::string m_bulletName;
	//添加敌机
	void addEnemy(float tm);
	//添加子弹
	void addBullet(float tm);
	//当玩家飞机和UFO碰撞以后添加子弹
	void addBulletByUfo(float tm);
	//添加UFO和炸弹
	void addUfo(float tm);
	//碰撞检测
	void isHitEnemy(float tm);
	//玩家级别
	int m_level;
	//游戏结束
	void gameOver();
};

#endif

