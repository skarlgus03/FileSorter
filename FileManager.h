#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "FileInfo.h"
#include <vector>
#include <string>

class FileManager {
public:
    std::vector<FileInfo> collectFileInfos(const std::string& directoryPath);
    bool moveFile(const FileInfo& fileInfo);
};

#endif // FILE_MANAGER_H
