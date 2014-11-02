#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_
#include "cocos2d.h"

USING_NS_CC;

//�л���ĸ��࣬�̳���Sprite
class EnemyBase : public Sprite
{
public:
	EnemyBase(void);
	~EnemyBase(void);
public:
	bool init();
	CREATE_FUNC(EnemyBase);
public:
	//��ը����
	void blowUp();
	//���˶���
	void hit();
	//��ը��ϴӹ��������Ƴ��Լ�
	void removeFromManager();
	void onEnterTransitionDidFinish();
	//�ı�л�������
	void move(float tm);
	//��ʼ���л�����ߴ�����Ҫʹ�õ��������֣��ṩĬ�ϲ���
	void initEnemy(std::string name = "enemy1",int count = 4);
	//��õл�ԭʼ��Ѫ��ֵ
	int getOriginalHp(){return (m_frameName[5]-'0')*5;};
private:
	//���start-end��Χ�ڵ�һ�������
	int getRandomNumber(int start,int end);
	//�л���ƫ����
	enum {OFFSET = 5};
	//��ʼ���л��õ�����������
	std::string m_frameName;
	//��ըЧ������������
	int m_count;
	//�л���Ѫ��ֵ��ʵ����get��set����
	//int m_hp;
	CC_SYNTHESIZE(int,m_hp,Hp);
};

#endif

