#pragma once
#include "FilesArchiver.h"
#include <queue>
#include <mutex>

class FilesArchiverImp :
    public FilesArchiver
{
private:
    std::queue<std::string> filesQueue;
    void createQueue(std::string path);
    void queueMyltiThreadManage(std::mutex* queueMutex);
public:
    void archive(std::string path) override;
};

