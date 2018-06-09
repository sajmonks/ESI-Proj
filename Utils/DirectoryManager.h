//
// Created by Tomek on 06.06.2018.
//
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <iterator>
#include <algorithm>

#ifndef ESIPROJ_DIRECTORYMANAGER_H
#define ESIPROJ_DIRECTORYMANAGER_H

#include "DirectoryEntry.h"

class DirectoryManager {
private:
    static inline std::vector<std::string> split(const std::string &input, char delim) {
        auto elements = std::vector<std::string>();
        split(input, std::back_inserter(elements), delim);
        return elements;
    }

    template <typename Inserter>
    static inline void split(const std::string &input, Inserter output, char delim) {
        auto stream = std::stringstream(input);
        auto item = std::string();
        while(std::getline(stream, item, delim)) {
            *(output++) = item;
        }
    }

    static void removeSpecial(std::string &input) {
        auto len = input.length();
        for(uint32_t i = 0; i  < len; i++) {
            auto character = input[i];
            if(((character>='0')&&(character<='9'))||((character>='A')
                                                      &&(character<='Z'))||((character>='a')&&(character<='z')))
            {
                continue;
            }
            else {
                input.erase(i, 1);
                --len;
                --i;
                continue;
            }
        }
    }

    static inline bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }

public:
    static std::string executeCommand(std::string command);
    static std::vector<DirectoryEntry> getEntries(std::string directory);
};


#endif //ESIPROJ_DIRECTORYMANAGER_H
