#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "cocos2d.h"
//�����л����ӵ���ͷ�ļ�
#include "Bullet\Bullet.h"
#include "Enemy\EnemyBase.h"

USING_NS_CC;

//�ӵ��͵л������������ɵ���
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
	//ʹ�����µķ�����������������������ʵ����get������һ��Ҫע��get�ķ���ֵ��������ص�������
	//�ٷ�����������ò�Ҫ�ڶ��Ϸ����ڴ�ռ䣬��������ջ�Ϸ����ڴ�ռ��ʱ��һ��Ҫ�������ã�����ͳ�����
	Vector<EnemyBase *> & getEnemyVector(){return m_enemyVector;};
	Vector<Bullet *> & getBulletVector(){return m_bulletVector;};
private:
	Vector<EnemyBase *> m_enemyVector;
	Vector<Bullet *> m_bulletVector;
};

#endif

