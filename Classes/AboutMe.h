#ifndef _ABOUT_ME_H_
#define _ABOUT_ME_H_
#include "cocos2d.h"

USING_NS_CC;

//关于小塔
class AboutMe : public Layer
{
public:
	AboutMe(void);
	~AboutMe(void);
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(AboutMe);
public:
	void back(EventKeyboard::KeyCode keyCode,Event * pEvent);
};

#endif