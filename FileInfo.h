#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <string>
#include <cstdint>

struct FileInfo {
    std::string keyword; //키워드
    std::string extension;  //확장자
    std::string moveToPath; //이동할 위치
    std::string originalFullPath; //현재 파일이 있는 위치
    uintmax_t size;          // 파일 크기 (바이트)
    std::int64_t creationTime; // 생성/수정 시간 (epoch 기반)(마지막으로 수정된 시간)
};

#endif // FILE_INFO_H
