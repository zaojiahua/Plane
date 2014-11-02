#ifndef _SAVE_DATA_H_
#define _SAVE_DATA_H_
#include "cocos2d.h"

USING_NS_CC;

class SaveData : public Ref
{
public:
	SaveData(void);
	~SaveData(void);
public:
	bool init();
	CREATE_FUNC(SaveData);
private:
	//用户数据操作的成员变量
	UserDefault * m_userDefault;
	//该集合中保存的是分数的记录，因为分数是基本数据类型，放到vector中的内容必须是Ref的子类，所以要用Value
	//封装一下，但封装完毕却不是使用vector来存放，而是用ValueVector
	ValueVector m_vector;
	//记录玩家的当前分数
	CC_SYNTHESIZE(int,m_score,Score);
public:
	void save();
};

#endif