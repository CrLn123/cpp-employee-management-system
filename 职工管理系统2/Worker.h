#pragma once
#include<iostream>
#include<string>
using namespace std;


class Worker
{
public:

	virtual ~Worker() = default;

	virtual void showInfo() const = 0;

	virtual string getDepName() const = 0;

	int m_ID;
	string m_Name;
	int m_DepId;
};
