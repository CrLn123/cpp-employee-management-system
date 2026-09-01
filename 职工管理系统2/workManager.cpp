#include "workManager.h"
#include "Worker.h"

WorkManager::WorkManager()
{
	ifstream ifs;

	ifs.open("职工名单.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->workerArray = NULL;
		this->workerNum = 0;
		this->fileIsEmp = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->workerArray = NULL;
		this->workerNum = 0;
		this->fileIsEmp = true;
		ifs.close();
		return;
	}
	
	ifs.close();

	readFile();

}



void WorkManager::Show_Menu()
{
	cout << "********************************" << endl;
	cout << "******欢迎使用职工管理系统******" << endl;
	cout << "*********0.推出管理系统*********" << endl;
	cout << "*********1.增加职工信息*********" << endl;
	cout << "*********2.显示职工信息*********" << endl;
	cout << "*********3.删除职工信息*********" << endl;
	cout << "*********4.修改职工信息*********" << endl;
	cout << "*********5.查找职工信息*********" << endl;
	cout << "*********6.按照编号排序*********" << endl;
	cout << "*********7.清空所有文档*********" << endl;
	cout << "********************************" << endl;
}

void WorkManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0); //程序直接退出
}

void WorkManager::addWorker()
{
	cout << "请输入添加数量" << endl;
	int addWorkerNum;
	cin >> addWorkerNum;
	int newSize = this->workerNum + addWorkerNum;

	Worker** newSpace = new Worker * [newSize];

	if (this->workerArray != NULL)
	{
		for (int i = 0; i < workerNum; i++)
		{
			newSpace[i] = workerArray[i];
		}
	}

	delete[] workerArray;

	for (int i = 1; i <= addWorkerNum; i++)
	{
		FLAG1:
		int id = 0;
		string name;
		int depId;
		cout << "请输入新增第" << i << "位职工的ID：" << endl;
		cin >> id;
		cout << "请输入新增第" << i << "位职工的姓名：" << endl;
		cin >> name;
		cout << "请输入新增第" << i << "位职工的职位代码：" << endl;
		cin >> depId;
		if (depId == 1)
		{
			newSpace[workerNum + i - 1] = new Boss(id, name, depId);
		}
		else if (depId == 2)
		{
			newSpace[workerNum + i - 1] = new Manager(id, name, depId);
		}
		else if (depId == 3)
		{
			newSpace[workerNum + i - 1] = new Employee(id, name, depId);
		}
		else
		{
			cout << "输入错误" << endl;
			goto FLAG1;
		}
	}
    
	this->workerArray = newSpace;

	this->workerNum = newSize;

	this->fileIsEmp = false;

	writeFile();

	cout << "成功添加" << addWorkerNum << "名新职工" << endl;

	system("pause");
}

void WorkManager::writeFile()
{
	ofstream ofs;
    
	ofs.open("职工名单.txt", ios::out);

	for (int i = 0; i < workerNum; i++)
	{
		ofs  << workerArray[i]->m_ID << " "
			 << workerArray[i]->m_Name << " "
			 << workerArray[i]->m_DepId << endl;
	}

	ofs.close();
	
}

int WorkManager::getWorkerNum()
{
	ifstream ifs;

	ifs.open("职工名单.txt", ios::in);

	int id;
	string name;
	int depId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> depId)
	{
		num++;
		this->fileIsEmp = false;
	}

	ifs.close();

	return num;
}

void WorkManager::readFile()
{
	int num = getWorkerNum();

	workerNum = num; // 前面已经读取过一次文件，不必重复读取。

	workerArray = new Worker * [num];

	ifstream ifs;

	ifs.open("职工名单.txt", ios::in);

	int id;
	string name;
	int depId;

	int n = 0;
	while (ifs >> id && ifs >> name && ifs >> depId)
	{
		Worker* worker = NULL;
		if (depId == 1)
		{
			worker = new Boss(id, name, depId);
		}
		else if (depId == 2)
		{
			worker = new Manager(id, name, depId);
		}
		else if (depId == 3)
		{
			worker = new Employee(id, name, depId);
		}
		this->workerArray[n] = worker;

		n++;
	}


	ifs.close();
}

void WorkManager::showWorker()
{
	if (fileIsEmp)
	{
		cout << "暂无职工" << endl;
		return;
	}
	for (int i = 0; i < workerNum; i++)
	{
		
		workerArray[i]->showInfo();
	}
	
}

void WorkManager::deleteWorker()
{
	if (fileIsEmp)
	{
		cout << "暂无职工" << endl;
		return;
	}

	cout << "请选择删除方式 1.通过ID删除 2.通过姓名删除" << endl;
	int select = 0;
	cin >> select;

	int index = -1;
	if (select == 1)
	{
		cout << "请输入要删除的职工ID" << endl;
		int id = 0;
		cin >> id;
		for (int i = 0; i < workerNum; i++)
		{
			if (workerArray[i]->m_ID == id)
			{
				index = i;
				break;
			}
		}
	}
	else if (select == 2)
	{
		cout << "请输入要删除的职工姓名" << endl;
		string name;
		cin >> name;
		for (int i = 0; i < workerNum; i++)
		{
			if (workerArray[i]->m_Name == name)
			{
				index = i; // 同名时只删除第一位，避免一次删掉多条记录。
				break;
			}
		}
	}
	else
	{
		cout << "输入错误" << endl;
		return;
	}

	if (index == -1)
	{
		cout << "不存在" << endl;
		return;
	}

	deleteWorkerByIndex(index);
	writeFile();
	cout << "删除成功" << endl;
}

void WorkManager::changeWorker()
{
	if (fileIsEmp)
	{
		cout << "暂无职工" << endl;
		return;
	}

	showWorker();

	cout << "请输入要修改的员工的原始ID：" << endl;
	int id;
	cin >> id;
	

	int index = -1;
	for (int i = 0; i < workerNum; i++)
	{
		if (workerArray[i]->m_ID == id)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		cout << "不存在" << endl;
		return;
	}

	// 先读取并校验新数据，确认无误后再删除旧对象。
	cout << "请输入修改后ID" << endl;
	int new_ID;
	cin >> new_ID;
	cout << "请输入修改后姓名" << endl;
	string new_Name;
	cin >> new_Name;
	cout << "请输入修改后职位代码" << endl;
	int new_depId;
	cin >> new_depId;

	Worker* newWorker = NULL;
	if (new_depId == 1)
	{
		newWorker = new Boss(new_ID, new_Name, new_depId);
	}
	else if (new_depId == 2)
	{
		newWorker = new Manager(new_ID, new_Name, new_depId);
	}
	else if (new_depId == 3)
	{
		newWorker = new Employee(new_ID, new_Name, new_depId);
	}
	else
	{
		cout << "输入错误" << endl;
		return;
	}

	delete workerArray[index];
	workerArray[index] = newWorker;
	writeFile();
	cout << "修改成功" << endl;
}

void WorkManager::findWorker()
{
	if (fileIsEmp)
	{
		cout << "暂无职工" << endl;
		return;
	}
	cout << "请输入查找方式： 1.通过ID  2.通过姓名" << endl;
	int select1;
	cin >> select1;

	if (select1 == 1)
	{
		cout << "请输入ID查找" << endl;
		int u_ID;
		cin >> u_ID;

		int temp = 0;

		for (int i = 0; i < this->workerNum; i++)
		{
			if (workerArray[i]->m_ID == u_ID)
			{
				workerArray[i]->showInfo();
				temp++;
			}
		}

		if (temp == 0)
		{
			cout << "未查到" << endl;
		}
	}

	else if (select1 == 2)
	{
		cout << "请输入姓名查找" << endl;
		string u_Name;
		cin >> u_Name;

		int temp = 0;

		for (int i = 0; i < this->workerNum; i++)
		{
			if (workerArray[i]->m_Name == u_Name)
			{
				workerArray[i]->showInfo();
				temp++;
			}
		}

		if (temp == 0)
		{
			cout << "未查到" << endl;
		}
	}

	else
	{
		cout << "输入错误" << endl;
	}
}

void WorkManager::sortWorker()
{
	if (fileIsEmp)
	{
		cout << "暂无职工" << endl;
		return;
	}
	int basic = 0;
	Worker* temp = NULL;
	for (int i = 0; i < this->workerNum; i++)
	{
		for (int j = i; j < this->workerNum; j++)
		{
			if (workerArray[j]->m_ID < workerArray[basic]->m_ID)
			{
				temp = workerArray[j];
				workerArray[j] = workerArray[basic];
				workerArray[basic] = temp;
				temp = NULL;
			}
		}
		basic++;
	}
	cout << "排序成功" << endl;
	writeFile();	
	showWorker();
}

void WorkManager::clearWorker()
{
	if (fileIsEmp)
	{
		cout << "暂无职工" << endl;
		return;
	}
	
	cout << "请问是否确认清空： 1.确认 2.放弃" << endl;
	int select;
	cin >> select;
	ofstream ofs;

	switch (select)
	{
	case 1:
		
		ofs.open("职工名单.txt", ios::trunc);
		ofs.close();

		for (int i = 0; i < this->workerNum; i++)
		{
			if (this->workerArray[i] != NULL)
			{
				delete workerArray[i];
			}
		}
		delete[] this->workerArray;
		workerArray = NULL;
		workerNum = 0;
		fileIsEmp = true;
		cout << "清除成功" << endl;
		break;
	
	case 2:
		break;
	
	default:
		cout << "输入错误" << endl;
		break;
	}
	
	
}

void WorkManager::deleteWorkerByIndex(int index)
{
	// 先释放真正被删除的对象，再移动后面的指针补上空位。
	delete workerArray[index];
	for (int i = index; i < workerNum - 1; i++)
	{
		workerArray[i] = workerArray[i + 1];
	}

	workerArray[workerNum - 1] = NULL;
	workerNum--;
	if (workerNum == 0)
	{
		fileIsEmp = true;
	}
}

WorkManager::~WorkManager()
{
	if (this->workerArray != NULL)
	{
		// delete[] 只能释放指针数组，数组里的每个 Worker 也要单独释放。
		for (int i = 0; i < workerNum; i++)
		{
			delete workerArray[i];
		}
		delete[] this->workerArray;
		this->workerArray = NULL;
	}
}
