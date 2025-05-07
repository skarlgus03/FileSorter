#include "FileManager.h"
#include <filesystem>
#include <iostream>
#include <vector>
#include "FileInfo.h"

std::vector<FileInfo> FileManager::collectFileInfos(const std::string& directoryPath) {
    std::vector<FileInfo> files;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            FileInfo info;
            info.keyword = entry.path().filename().string();
            info.extension = entry.path().extension().string();
            info.moveToPath = ""; // 추후 Classifier가 결정
            info.size = std::filesystem::file_size(entry.path());
            info.creationTime = decltype(info.creationTime)(std::filesystem::last_write_time(entry.path()).time_since_epoch().count());
            info.originalFullPath = entry.path().string(); // 실제 경로 저장 (중요!)
            files.push_back(info);
        }
    }

    return files;
}

bool FileManager::moveFile(const FileInfo& fileInfo) {
    try {
        std::string toPath = fileInfo.moveToPath + "/" + fileInfo.keyword;
        std::filesystem::create_directories(fileInfo.moveToPath); // 경로가 없으면 생성
        std::filesystem::rename(fileInfo.originalFullPath, toPath);
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "File move error: " << e.what() << std::endl;
        return false;
    }
}
