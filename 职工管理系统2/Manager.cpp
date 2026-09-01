
#include "Manager.h"


Manager::Manager(int id, string name, int depId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepId = depId;
}

void Manager::showInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDepName()
		<< "\t岗位职务：完成老板交给的任务，给员工下发任务" << endl;
}

string Manager::getDepName()
{
	return string("经理");
}