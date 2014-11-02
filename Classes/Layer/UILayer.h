#ifndef _UILAYER_H_
#define _UILAYER_H_
#include "cocos2d.h"
//��ͣ����
#include "Pause.h"
//��ҷ���������
#include "SaveData\SaveData.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

//UI��
class UILayer : public Layer
{
public:
	UILayer(void);
	~UILayer(void);
public:
	bool init();
	CREATE_FUNC(UILayer);
public:
	//��ť�Ļص�����
	void menuCallback(Ref * ref);
	//����ҷ��������ĳ�Ա����
	CC_SYNTHESIZE_READONLY(SaveData *,m_saveData,SaveData);
	void update(float tm);
	//��ͼ����
	void screenShoot();
	MenuItemToggle * getMenu(){return menuToggle;};
private:
	Label * m_score;
	Label * score_label;
	MenuItemToggle * menuToggle;
};

#endif

