
#include "Boss.h"

Boss::Boss(int id, string name, int depId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepId = depId;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDepName()
		<< "\t岗位职务：给经理下发任务" << endl;
}

string Boss::getDepName()
{
	return string("老板");
}