#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Worker.h"
#include "Boss.h"
#include "Manager.h"
#include "Employee.h"


class WorkManager
{
public:

	WorkManager();

	void Show_Menu(); //展示菜单

	void exitSystem(); //退出系统

	void addWorker(); //添加员工

	void writeFile(); //写入文档

	int getWorkerNum(); //获取职工数量

	void readFile(); //读取文档

	void showWorker();

	void deleteWorker();

	void changeWorker();

	void findWorker();

	void sortWorker();

	void clearWorker();

	int workerNum;
	Worker** workerArray;

	bool fileIsEmp;

	~WorkManager();
};