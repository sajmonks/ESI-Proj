//
// Created by Tomek on 06.06.2018.
//

#ifndef ESIPROJ_DIRECTORY_H
#define ESIPROJ_DIRECTORY_H


class DirectoryEntry {
private:

    bool m_isDirectory;
    std::string m_name;
    std::string m_dateOfModify;
    std::string m_size;
public:
    DirectoryEntry() noexcept : m_isDirectory(true), m_name(""), m_dateOfModify(""), m_size("") {

    }

    DirectoryEntry(bool isDirectory, std::string name, std::string dateOfModify, std::string size) noexcept :
    m_isDirectory(isDirectory), m_name(name), m_dateOfModify(dateOfModify), m_size(size)  {
    }

    DirectoryEntry(DirectoryEntry&&) = default;
    DirectoryEntry& operator=(DirectoryEntry&&) = default;

    DirectoryEntry(DirectoryEntry&) = default;
    DirectoryEntry& operator=(DirectoryEntry&) = default;

    inline bool isDirectory() noexcept {
        return m_isDirectory;
    }

    inline std::string& getName() noexcept {
        return m_name;
    }

    inline std::string getModifyDate() noexcept  {
        return m_dateOfModify;
    }

    inline std::string getSize() noexcept {
        return m_size;
    }

};


#endif //ESIPROJ_DIRECTORY_H
