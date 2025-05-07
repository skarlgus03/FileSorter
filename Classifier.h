#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "FileInfo.h"
#include "Block.h"
#include <memory>

class Classifier {
public:
    void classifyFile(FileInfo& fileInfo, const std::shared_ptr<Block>& rootBlock);
};

#endif // CLASSIFIER_H
