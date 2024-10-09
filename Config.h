#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
    public:
        std::string regionFile;
        int timeLimit;
        int refreshRate;

        void loadConfig(const std::string& fileName);
};

#endif