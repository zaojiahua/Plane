#include "SaveData.h"

SaveData::SaveData(void)
{
}

SaveData::~SaveData(void)
{
}

bool SaveData::init()
{
	//�ȶԳ�Ա�������г�ʼ��
	m_userDefault = UserDefault::getInstance();
	//��ʼ��vector����
	m_vector = ValueVector();
	//��ʼ��������Ϸ��ҵ÷�
	m_score = 0;

	//ÿ��һ����Ϸ�������ļ�¼�����ͻ��һ
	m_userDefault->setIntegerForKey("count",(m_userDefault->getIntegerForKey("count",0))+1);

	//�����ж�XML�ļ��Ƿ���ڣ���������ڵĻ��ͻ�ִ��if�е����
	if(m_userDefault->getBoolForKey("isExit",false) == false)
	{
		//��ҳ�������Ϸ��ִ������
		m_userDefault->setBoolForKey("isExit",true);
	}
	else
	{
			//��������¼������vector������
			for(int i=0;i<m_userDefault->getIntegerForKey("count")-1;i++)
			{
				__String * index = String::createWithFormat("%d",i);
				//��Ҫ�ŵ�����ʹ��Value��װһ��
				m_vector.push_back(Value(m_userDefault->getIntegerForKey(index->getCString())));
			}
	}
	
	return true;
}

void SaveData::save()
{
	/*������������˼·���ȶ�vector�б����������ݽ�������Ȼ������д�뵽xml�ļ���*/

	//����ҵķ������浽set�����У��Ա����򣬷�����ԭ�ȵķ�����ͬ�ű���
	int i=0;
	for(auto tem:m_vector)
	{
		if(tem.asInt() == m_score)
		{
			break;
		}
		i++;
	}
	if(i == m_vector.size())
	{
		m_vector.push_back(Value(m_score));
		//�Զ�������������m_vector�е����ݽ������򣬷����Ժ�����ݵĲ���
		auto sortData = [](Value value1,Value value2)
		{
			return value1.asInt()>value2.asInt();
		};
		//����c++ģ���е�sort������������ǰ��������������ĵ�ַ�����һ��������ʹ�õ�������
		std::sort(m_vector.begin(),m_vector.end(),sortData);
	
		//����ҵĵ÷ֱ������ļ���
		for(int i=0;i<m_vector.size();i++)
		{
			auto value = m_vector.at(i);
			auto index = __String::createWithFormat("%d",i);
			m_userDefault->setIntegerForKey(index->getCString(),value.asInt());
		}
	}
	
	//�������汾����Ϸ�ĵ÷�
	UserDefault::getInstance()->setIntegerForKey("currentScore",m_score);
	//��������һ��count
	UserDefault::getInstance()->setIntegerForKey("count",m_vector.size());

	//ˢ��
	m_userDefault->flush();
}
