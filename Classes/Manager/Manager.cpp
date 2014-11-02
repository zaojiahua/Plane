#include "Manager.h"

Manager * Manager::m_manager = NULL;

//�ڹ��캯���ĳ�ʼ���б��г�ʼ������
Manager::Manager() : m_enemyVector(),m_bulletVector()
{
}

Manager * Manager::getInstance()
{
	if(m_manager == NULL)
	{
		m_manager = new Manager();
	}

	return m_manager;
}

void Manager::freeInstance(void)
{
	if(m_manager != NULL)
	{
		delete m_manager;
		m_manager = NULL;
	}
}