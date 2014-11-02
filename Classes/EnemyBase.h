#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_
#include "cocos2d.h"

USING_NS_CC;

//敌机类的父类，继承自Sprite
class EnemyBase : public Sprite
{
public:
	EnemyBase(void);
	~EnemyBase(void);
public:
	bool init();
	CREATE_FUNC(EnemyBase);
public:
	//爆炸动画
	void blowUp();
	//受伤动画
	void hit();
	//爆炸完毕从管理器中移除自己
	void removeFromManager();
	void onEnterTransitionDidFinish();
	//改变敌机的坐标
	void move(float tm);
	//初始化敌机，里边传入需要使用的纹理名字，提供默认参数
	void initEnemy(std::string name = "enemy1",int count = 4);
	//获得敌机原始的血量值
	int getOriginalHp(){return (m_frameName[5]-'0')*5;};
private:
	//获得start-end范围内的一个随机数
	int getRandomNumber(int start,int end);
	//敌机的偏移量
	enum {OFFSET = 5};
	//初始化敌机用到的纹理名称
	std::string m_frameName;
	//爆炸效果的纹理数量
	int m_count;
	//敌机的血量值，实现了get和set方法
	//int m_hp;
	CC_SYNTHESIZE(int,m_hp,Hp);
};

#endif

