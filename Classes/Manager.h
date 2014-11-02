#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "cocos2d.h"
//包含敌机和子弹的头文件
#include "Bullet\Bullet.h"
#include "Enemy\EnemyBase.h"

USING_NS_CC;

//子弹和敌机管理器，做成单例
class Manager
{
public:
	static Manager * getInstance();
	static void freeInstance(void);
private:
	static Manager * m_manager;
	Manager();
	bool init();
public:
	//使用以下的方法定义了俩个容器，并且实现了get方法，一定要注意get的返回值，这个返回的是引用
	//官方建议容器最好不要在堆上分配内存空间，当我们在栈上分配内存空间的时候一定要传递引用，否则就出错了
	Vector<EnemyBase *> & getEnemyVector(){return m_enemyVector;};
	Vector<Bullet *> & getBulletVector(){return m_bulletVector;};
private:
	Vector<EnemyBase *> m_enemyVector;
	Vector<Bullet *> m_bulletVector;
};

#endif

