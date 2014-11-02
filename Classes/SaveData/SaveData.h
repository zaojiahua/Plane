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
	//�û����ݲ����ĳ�Ա����
	UserDefault * m_userDefault;
	//�ü����б�����Ƿ����ļ�¼����Ϊ�����ǻ����������ͣ��ŵ�vector�е����ݱ�����Ref�����࣬����Ҫ��Value
	//��װһ�£�����װ���ȴ����ʹ��vector����ţ�������ValueVector
	ValueVector m_vector;
	//��¼��ҵĵ�ǰ����
	CC_SYNTHESIZE(int,m_score,Score);
public:
	void save();
};

#endif