#ifndef _UFO_H_
#define _UFO_H_
#include "cocos2d.h"

USING_NS_CC;

//ufo和炸弹类，继承自sprite
class Ufo : public Sprite
{
public:
	Ufo(void);
	~Ufo(void);
public:
	bool init();
	CREATE_FUNC(Ufo);
public:
	//根据不同的纹理初始化不同的ufo和炸弹
	void initUfo(std::string name);
	int getRandomNumber(int start,int end);
	//包含名字的属性
	CC_SYNTHESIZE_READONLY(std::string,m_name,Name);
};

#endif

