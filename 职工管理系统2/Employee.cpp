
#include "Employee.h"


Employee::Employee(int id, string name, int depId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepId = depId;
}

void Employee::showInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDepName()
	    << "\t岗位职务：完成经理交给的任务" << endl;
}

string Employee::getDepName()
{
	return string("员工");
}