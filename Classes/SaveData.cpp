#include "SaveData.h"

SaveData::SaveData(void)
{
}

SaveData::~SaveData(void)
{
}

bool SaveData::init()
{
	//先对成员变量进行初始化
	m_userDefault = UserDefault::getInstance();
	//初始化vector集合
	m_vector = ValueVector();
	//初始化本次游戏玩家得分
	m_score = 0;

	//每玩一次游戏，分数的记录条数就会加一
	m_userDefault->setIntegerForKey("count",(m_userDefault->getIntegerForKey("count",0))+1);

	//首先判断XML文件是否存在，如果不存在的话就会执行if中的语句
	if(m_userDefault->getBoolForKey("isExit",false) == false)
	{
		//玩家初次玩游戏会执行这里
		m_userDefault->setBoolForKey("isExit",true);
	}
	else
	{
			//将分数记录保存在vector集合中
			for(int i=0;i<m_userDefault->getIntegerForKey("count")-1;i++)
			{
				__String * index = String::createWithFormat("%d",i);
				//将要放的数据使用Value包装一下
				m_vector.push_back(Value(m_userDefault->getIntegerForKey(index->getCString())));
			}
	}
	
	return true;
}

void SaveData::save()
{
	/*本函数的整体思路是先对vector中保存的玩家数据进行排序，然后重新写入到xml文件中*/

	//将玩家的分数保存到set集合中，以便排序，分数和原先的分数不同才保存
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
		//自定义排序函数，对m_vector中的内容进行排序，方便以后对数据的操作
		auto sortData = [](Value value1,Value value2)
		{
			return value1.asInt()>value2.asInt();
		};
		//调用c++模板中的sort函数进行排序，前俩个参数是数组的地址，最后一个参数是使用的排序函数
		std::sort(m_vector.begin(),m_vector.end(),sortData);
	
		//将玩家的得分保存在文件中
		for(int i=0;i<m_vector.size();i++)
		{
			auto value = m_vector.at(i);
			auto index = __String::createWithFormat("%d",i);
			m_userDefault->setIntegerForKey(index->getCString(),value.asInt());
		}
	}
	
	//单独保存本次游戏的得分
	UserDefault::getInstance()->setIntegerForKey("currentScore",m_score);
	//重新设置一下count
	UserDefault::getInstance()->setIntegerForKey("count",m_vector.size());

	//刷新
	m_userDefault->flush();
}
