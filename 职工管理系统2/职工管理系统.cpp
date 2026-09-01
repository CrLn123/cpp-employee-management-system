#include <iostream>
#include "workManager.h"
using namespace std;


int main()
{
	WorkManager wm;
	

	
	int choice;
	
	while (1)
	{	
		system("cls");	
	    wm.Show_Menu();
		cout << "请选择你要使用的功能：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:		
			wm.exitSystem();
			break;
		
		case 1:
			system("cls");
			wm.addWorker();
			break;

		case 2:
			system("cls");
			wm.showWorker();
			system("pause");
			break;

		case 3:
			system("cls");
			wm.deleteWorker();
			break;

		case 4:
			system("cls");
			wm.changeWorker();
			system("pause");
			break;

		case 5:
			system("cls");
			wm.findWorker();
			system("pause");
			break;
		
		case 6:
			wm.sortWorker();
			system("pause");
			break;

		case 7:
			wm.clearWorker();
			system("pause");
			break;	

		default:
			system("cls");
			break;
		}
	}

	

	system("pause");

	return 0;
}