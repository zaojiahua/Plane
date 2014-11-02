#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "cocos2d.h"

USING_NS_CC;

//��ͼ��
class Background : public Layer
{
public:
	Background(void);
	~Background(void);
public:
	bool init();
	CREATE_FUNC(Background);
public:
	//������Ϳ��
	void move(float tm);
	void onEnterTransitionDidFinish();
private:
	//���ű���ͼƬ
	Sprite * m_background_1;
	Sprite * m_background_2;
	//�豸��С
	Size m_size;
	//����ͼƬ�ƶ��Ĵ�С
	enum{OFFSET = 3};
};

#endif

