#pragma once
#include<iostream>
#include"Worker.h"
using namespace std;

class Manager :public Worker
{
public:

	Manager(int id, string name, int depId);

	virtual void showInfo();

	virtual string getDepName();
};