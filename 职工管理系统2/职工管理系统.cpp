#include <cstdlib>
#include <iostream>
#include <limits>

#include "workManager.h"

namespace
{
    void waitForEnter()
    {
        std::cout << "按回车键继续...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    bool readMenuChoice(int& choice)
    {
        std::cout << "请输入要使用的功能：";
        if (std::cin >> choice)
        {
            return true;
        }

        std::cout << "输入必须是数字。" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
}

int main()
{
    WorkManager manager;
    bool running = true;

    while (running)
    {
        std::system("cls");
        manager.Show_Menu();

        int choice = 0;
        if (!readMenuChoice(choice))
        {
            waitForEnter();
            continue;
        }

        std::system("cls");
        switch (choice)
        {
        case 0:
            manager.exitSystem();
            running = false;
            break;
        case 1:
            manager.addWorker();
            break;
        case 2:
            manager.showWorker();
            break;
        case 3:
            manager.deleteWorker();
            break;
        case 4:
            manager.changeWorker();
            break;
        case 5:
            manager.findWorker();
            break;
        case 6:
            manager.sortWorker();
            break;
        case 7:
            manager.clearWorker();
            break;
        default:
            std::cout << "菜单编号只能是 0 到 7。" << std::endl;
            break;
        }

        if (running)
        {
            waitForEnter();
        }
    }

    return 0;
}
