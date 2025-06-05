#include "FilesArchiverImp.h"
#include "ArchiverImp.h"
#include <filesystem>  
#include <mutex>
#include <thread>
#include <windows.h>
#include <vector>

void FilesArchiverImp::createQueue(std::string path) {
    using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
    std::queue<std::string> empty;
    std::swap(filesQueue, empty);
    for (const auto& dirEntry : recursive_directory_iterator(path)) {
        if (dirEntry.is_regular_file()) {
            filesQueue.push(dirEntry.path().string());
        }
    }
}

void FilesArchiverImp::queueMyltiThreadManage(std::mutex* queueMutex) {
    bool queueIsEmpty = false;
    while (!queueIsEmpty) {
        std::string filePath = "";
        queueMutex->lock();
        if (!filesQueue.empty()) {
            filePath = filesQueue.front();
            filesQueue.pop();
        }
        else {
            queueIsEmpty = true;
        }
        queueMutex->unlock();
        if (queueIsEmpty) return;
        ArchiverImp::archiveFile(filePath);
    }
}

void FilesArchiverImp::archive(std::string path) {
    createQueue(path);

    int threadsCount = max(2, processorsCount() / 2);

    std::vector<std::thread> threads;
    std::mutex queueMutex;
    for (int i = 0; i < threadsCount; ++i) {
        threads.push_back(std::thread(&FilesArchiverImp::queueMyltiThreadManage, this, &queueMutex));
    }
    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
}

int processorsCount() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}
