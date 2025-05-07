#include "Classifier.h"

void Classifier::classifyFile(FileInfo& fileInfo, const std::shared_ptr<Block>& rootBlock) {
    std::shared_ptr<Block> current = rootBlock;

    while (current) {
        bool match = false;

        switch (current->getFilterType()) {
            case filterType::EXTENSION:
                if (fileInfo.extension == current->getCondition())
                    match = true;
                break;

            case filterType::KEYWORD:
                if (fileInfo.keyword.find(current->getCondition()) != std::string::npos)
                    match = true;
                break;

            case filterType::SIZE:
                if (fileInfo.size >= std::stoull(current->getCondition()))
                    match = true;
                break;

            case filterType::DATE:
                if (fileInfo.creationTime >= std::stoll(current->getCondition()))
                    match = true;
                break;
        }

        if (!match) break;

        // 말단이면 movePath 저장
        if (current->isLeaf()) {
            fileInfo.moveToPath = current->getMovePath();
            break;
        }

        // 자식이 여러 개일 경우 여기선 첫 번째만 타고 감 (간단한 예시)
        const auto& children = current->getChildren();
        if (!children.empty()) {
            current = children.front();
        } else {
            break;
        }
    }
}
