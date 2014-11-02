#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "cocos2d.h"
#include "Sound\Sound.h"

USING_NS_CC;

class Pause : public Layer
{
public:
	Pause(void);
	~Pause(void);
public:
	bool init();
	static Scene * createScene();
	CREATE_FUNC(Pause);
};

#endif