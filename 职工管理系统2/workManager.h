#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Worker.h"

class WorkManager
{
public:
    WorkManager();

    void Show_Menu() const;
    void exitSystem() const;
    void addWorker();
    void showWorker() const;
    void deleteWorker();
    void changeWorker();
    void findWorker() const;
    void sortWorker();
    void clearWorker();

private:
    std::vector<std::unique_ptr<Worker>> workers;

    void writeFile() const;
    void readFile();
    int findWorkerIndexById(int id) const;
    bool idExists(int id) const;
    std::unique_ptr<Worker> createWorker(int id, const std::string& name, int depId) const;
};
