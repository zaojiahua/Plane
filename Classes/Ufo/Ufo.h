#ifndef _UFO_H_
#define _UFO_H_
#include "cocos2d.h"

USING_NS_CC;

//ufo��ը���࣬�̳���sprite
class Ufo : public Sprite
{
public:
	Ufo(void);
	~Ufo(void);
public:
	bool init();
	CREATE_FUNC(Ufo);
public:
	//���ݲ�ͬ�������ʼ����ͬ��ufo��ը��
	void initUfo(std::string name);
	int getRandomNumber(int start,int end);
	//�������ֵ�����
	CC_SYNTHESIZE_READONLY(std::string,m_name,Name);
};

#endif

