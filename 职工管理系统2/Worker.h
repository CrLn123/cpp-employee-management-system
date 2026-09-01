#pragma once
#include<iostream>
#include<string>
using namespace std;


class Worker
{
public:
	// 通过 Worker* 删除派生类对象时，必须有虚析构函数。
	virtual ~Worker() {}

	virtual void showInfo() = 0;

	virtual string getDepName() = 0;

	int m_ID;
	string m_Name;
	int m_DepId;
};
