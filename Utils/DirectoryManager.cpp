//
// Created by Tomek on 06.06.2018.
//

#include "DirectoryManager.h"

std::string DirectoryManager::executeCommand(std::string command) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

std::vector<DirectoryEntry> DirectoryManager::getEntries(std::string directory) {
    auto entries = std::vector<DirectoryEntry>();
    auto dirString = std::string("dir ");
    auto command = dirString + directory;
    auto commandOutput = executeCommand(dirString + directory);
    auto splitLineOutput = split(commandOutput, '\n' );

    //For each line
    for(auto line : splitLineOutput) {

        if(line.length() <= 2)
            continue;

        auto splitSpaceOutput = split(line, ' ');
        //std::cout << "\nFor each line" << std::endl;

        std::string fileDate;
        std::string fileHour;
        bool isDirectory = false;
        bool isFile = false;
        std::string fileSize;
        std::string fileName;

        for(auto space : splitSpaceOutput) {
            if(space.length() < 2)
                continue;

            if(space.compare("..") == 0)
                continue;

            if(split(space, '.').size() == 3) {
                fileDate = space;
                //std::cout << "Data: " << space << std::endl;
                continue;
            }

            if(split(space, ':').size() == 2) {
                fileHour = space;
                //std::cout << "Hour: " << space << std::endl;
                continue;
            }

            if(space.compare("<DIR>") == 0) {
                isDirectory = true;
                //std::cout << "Directory: TRUE" << std::endl;
                continue;
            }

            if(isDirectory == true || isFile == true) {
                fileName += space + " ";
                //std::cout << "File: " << fileName << std::endl;
                continue;
            }

            if(fileHour.length() > 0 && !isFile) {
                removeSpecial(space);
                if(is_number(space)) {
                    isFile = true;
                    fileSize = space;
                    //std::cout << "Size: " << fileSize << std::endl;
                    continue;
                }
            }
        }

        if(fileDate.length() > 0 && fileHour.length() > 0 && (isDirectory || isFile) &&
           fileName.length() > 0)
        {
            entries.push_back(DirectoryEntry(isDirectory, fileName, fileDate + " " + fileHour, fileSize));
        }
    }
    return entries;
}
