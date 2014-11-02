#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "cocos2d.h"

USING_NS_CC;

//地图层
class Background : public Layer
{
public:
	Background(void);
	~Background(void);
public:
	bool init();
	CREATE_FUNC(Background);
public:
	//滚动底涂层
	void move(float tm);
	void onEnterTransitionDidFinish();
private:
	//俩张背景图片
	Sprite * m_background_1;
	Sprite * m_background_2;
	//设备大小
	Size m_size;
	//背景图片移动的大小
	enum{OFFSET = 3};
};

#endif

