#include "workManager.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

#include "Boss.h"
#include "Employee.h"
#include "Manager.h"

namespace
{
    const char* const kWorkerFile = "职工名单.txt";

    void clearInput()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool readInt(const std::string& prompt, int& value)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            return true;
        }

        std::cout << "输入必须是整数，请重新输入。" << std::endl;
        clearInput();
        return false;
    }

    std::string readName()
    {
        std::string name;
        std::cout << "请输入职工姓名：";
        std::getline(std::cin >> std::ws, name);
        return name;
    }
}

WorkManager::WorkManager()
{
    readFile();
}

void WorkManager::Show_Menu() const
{
    std::cout << "********************************" << std::endl;
    std::cout << "****** 欢迎使用职工管理系统 ******" << std::endl;
    std::cout << "********* 0. 退出管理系统 ********" << std::endl;
    std::cout << "********* 1. 增加职工信息 ********" << std::endl;
    std::cout << "********* 2. 显示职工信息 ********" << std::endl;
    std::cout << "********* 3. 删除职工信息 ********" << std::endl;
    std::cout << "********* 4. 修改职工信息 ********" << std::endl;
    std::cout << "********* 5. 查找职工信息 ********" << std::endl;
    std::cout << "********* 6. 按编号排序 **********" << std::endl;
    std::cout << "********* 7. 清空所有文档 ********" << std::endl;
    std::cout << "********************************" << std::endl;
}

void WorkManager::exitSystem() const
{
    std::cout << "欢迎下次使用！" << std::endl;
}

void WorkManager::addWorker()
{
    int count = 0;
    while (!readInt("请输入要添加的职工数量：", count) || count <= 0)
    {
        if (count <= 0)
        {
            std::cout << "数量必须大于 0。" << std::endl;
        }
    }

    for (int i = 0; i < count; ++i)
    {
        int id = 0;
        do
        {
            while (!readInt("请输入第 " + std::to_string(i + 1) + " 位职工的 ID：", id)) {}
            if (idExists(id))
            {
                std::cout << "ID 已存在，请使用新的 ID。" << std::endl;
            }
        } while (idExists(id));

        const std::string name = readName();
        int depId = 0;
        std::unique_ptr<Worker> worker;
        while (!worker)
        {
            while (!readInt("请输入岗位编号（1-老板，2-经理，3-员工）：", depId)) {}
            worker = createWorker(id, name, depId);
            if (!worker)
            {
                std::cout << "岗位编号只能是 1、2 或 3。" << std::endl;
            }
        }
        workers.push_back(std::move(worker));
    }

    writeFile();
    std::cout << "成功添加 " << count << " 位职工。" << std::endl;
}

void WorkManager::writeFile() const
{
    std::ofstream output(kWorkerFile, std::ios::out | std::ios::trunc);
    if (!output)
    {
        std::cout << "无法写入职工文件。" << std::endl;
        return;
    }

    for (const auto& worker : workers)
    {
        output << worker->m_ID << ' ' << std::quoted(worker->m_Name) << ' ' << worker->m_DepId << '\n';
    }
}

void WorkManager::readFile()
{
    std::ifstream input(kWorkerFile);
    if (!input)
    {
        return;
    }

    int id = 0;
    int depId = 0;
    std::string name;
    while (input >> id >> std::quoted(name) >> depId)
    {
        std::unique_ptr<Worker> worker = createWorker(id, name, depId);
        if (!worker || idExists(id))
        {
            std::cout << "已跳过一条无效或重复 ID 的职工记录。" << std::endl;
            continue;
        }
        workers.push_back(std::move(worker));
    }
}

void WorkManager::showWorker() const
{
    if (workers.empty())
    {
        std::cout << "当前没有职工信息。" << std::endl;
        return;
    }

    for (const auto& worker : workers)
    {
        worker->showInfo();
    }
}

void WorkManager::deleteWorker()
{
    if (workers.empty())
    {
        std::cout << "当前没有职工信息。" << std::endl;
        return;
    }

    int id = 0;
    while (!readInt("请输入要删除的职工 ID：", id)) {}

    const int index = findWorkerIndexById(id);
    if (index == -1)
    {
        std::cout << "未找到该 ID 的职工。" << std::endl;
        return;
    }

    workers.erase(workers.begin() + index);
    writeFile();
    std::cout << "删除成功。" << std::endl;
}

void WorkManager::changeWorker()
{
    if (workers.empty())
    {
        std::cout << "当前没有职工信息。" << std::endl;
        return;
    }

    int oldId = 0;
    while (!readInt("请输入要修改的职工原 ID：", oldId)) {}
    const int index = findWorkerIndexById(oldId);
    if (index == -1)
    {
        std::cout << "未找到该 ID 的职工。" << std::endl;
        return;
    }

    int newId = 0;
    do
    {
        while (!readInt("请输入修改后的 ID：", newId)) {}
        if (newId != oldId && idExists(newId))
        {
            std::cout << "ID 已存在，请使用新的 ID。" << std::endl;
        }
    } while (newId != oldId && idExists(newId));

    const std::string newName = readName();
    int depId = 0;
    std::unique_ptr<Worker> replacement;
    while (!replacement)
    {
        while (!readInt("请输入修改后的岗位编号（1-老板，2-经理，3-员工）：", depId)) {}
        replacement = createWorker(newId, newName, depId);
        if (!replacement)
        {
            std::cout << "岗位编号只能是 1、2 或 3。" << std::endl;
        }
    }

    // 先构造并校验新对象，最后才替换旧对象，避免非法输入破坏原数据。
    workers[index] = std::move(replacement);
    writeFile();
    std::cout << "修改成功。" << std::endl;
}

void WorkManager::findWorker() const
{
    if (workers.empty())
    {
        std::cout << "当前没有职工信息。" << std::endl;
        return;
    }

    int choice = 0;
    while (!readInt("请选择查找方式（1-ID，2-姓名）：", choice)) {}

    if (choice == 1)
    {
        int id = 0;
        while (!readInt("请输入职工 ID：", id)) {}
        const int index = findWorkerIndexById(id);
        if (index == -1)
        {
            std::cout << "未找到该职工。" << std::endl;
            return;
        }
        workers[index]->showInfo();
    }
    else if (choice == 2)
    {
        const std::string name = readName();
        bool found = false;
        for (const auto& worker : workers)
        {
            if (worker->m_Name == name)
            {
                worker->showInfo();
                found = true;
            }
        }
        if (!found)
        {
            std::cout << "未找到该职工。" << std::endl;
        }
    }
    else
    {
        std::cout << "查找方式只能是 1 或 2。" << std::endl;
    }
}

void WorkManager::sortWorker()
{
    if (workers.empty())
    {
        std::cout << "当前没有职工信息。" << std::endl;
        return;
    }

    std::sort(workers.begin(), workers.end(), [](const std::unique_ptr<Worker>& left, const std::unique_ptr<Worker>& right)
    {
        return left->m_ID < right->m_ID;
    });
    writeFile();
    std::cout << "排序成功。" << std::endl;
    showWorker();
}

void WorkManager::clearWorker()
{
    if (workers.empty())
    {
        std::cout << "当前没有职工信息。" << std::endl;
        return;
    }

    int choice = 0;
    while (!readInt("确定清空所有职工吗？1-确定，2-取消：", choice)) {}
    if (choice == 1)
    {
        workers.clear();
        writeFile();
        std::cout << "清空成功。" << std::endl;
    }
    else if (choice == 2)
    {
        std::cout << "已取消清空。" << std::endl;
    }
    else
    {
        std::cout << "输入无效，已取消清空。" << std::endl;
    }
}

int WorkManager::findWorkerIndexById(int id) const
{
    for (std::size_t i = 0; i < workers.size(); ++i)
    {
        if (workers[i]->m_ID == id)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool WorkManager::idExists(int id) const
{
    return findWorkerIndexById(id) != -1;
}

std::unique_ptr<Worker> WorkManager::createWorker(int id, const std::string& name, int depId) const
{
    switch (depId)
    {
    case 1:
        return std::make_unique<Boss>(id, name, depId);
    case 2:
        return std::make_unique<Manager>(id, name, depId);
    case 3:
        return std::make_unique<Employee>(id, name, depId);
    default:
        return nullptr;
    }
}
