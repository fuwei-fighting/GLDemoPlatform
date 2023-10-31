//
// Created by fuwei on 2023/10/31.
//

#ifndef GLDEMOPLATFORM_FILEUTIL_H
#define GLDEMOPLATFORM_FILEUTIL_H

#include <fstream>
#include <string>

class FileUtil {
public:
  static std::string getModulesAbsNamePath(const std::string &filePath) {
    std::string absPath = std::string(PROJECT_SOURCE_DIR) +
                          "/Glitter/Sources/modules/" + filePath;
    std::ifstream fileStream(absPath);
    if (!fileStream.good()) {
      fprintf(stderr, "[FileUtil] getModulesAbsNamePath: %s not exists.",
              absPath.c_str());
      return "";
    }
    return absPath;
  }
};

#endif // GLDEMOPLATFORM_FILEUTIL_H
