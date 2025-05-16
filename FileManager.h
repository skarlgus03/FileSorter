#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "FileInfo.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

class FileManager {
public:
    // 파일 목록 수집
    static std::vector<FileInfo> collectFileInfos(const std::string& directoryPath) {
        std::vector<FileInfo> files;

        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                FileInfo info;
                info.keyword = entry.path().filename().string();
                info.extension = entry.path().extension().string();
                info.moveToPath = ""; // 추후 Classifier가 채움
                info.size = std::filesystem::file_size(entry.path());
                info.creationTime = decltype(info.creationTime)(
                    std::filesystem::last_write_time(entry.path()).time_since_epoch().count());
                info.originalFullPath = entry.path().string();
                files.push_back(info);
            }
        }

        return files;
    }

    // 파일 이동
    static bool moveFile(const FileInfo& fileInfo) {
        try {
            std::string toPath = fileInfo.moveToPath + "/" + fileInfo.keyword;
            std::filesystem::create_directories(fileInfo.moveToPath); // 없으면 폴더 생성
            std::filesystem::rename(fileInfo.originalFullPath, toPath);
            return true;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "File move error: " << e.what() << std::endl;
            return false;
        }
    }
};

#endif // FILE_MANAGER_H
