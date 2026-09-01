#pragma once
#include<iostream>
#include"Worker.h"
using namespace std;

class Boss :public Worker
{
public:

	Boss(int id, string name, int depId);

	virtual void showInfo();

	virtual string getDepName();
};