#ifndef _UILAYER_H_
#define _UILAYER_H_
#include "cocos2d.h"
//暂停场景
#include "Pause.h"
//玩家分数操作类
#include "SaveData.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

//UI层
class UILayer : public Layer
{
public:
	UILayer(void);
	~UILayer(void);
public:
	bool init();
	CREATE_FUNC(UILayer);
public:
	//按钮的回调函数
	void menuCallback(Ref * ref);
	//对玩家分数操作的成员变量
	CC_SYNTHESIZE_READONLY(SaveData *,m_saveData,SaveData);
	void update(float tm);
	//截图功能
	void screenShoot();
	MenuItemToggle * getMenu(){return menuToggle;};
private:
	Label * m_score;
	Label * score_label;
	MenuItemToggle * menuToggle;
};

#endif

