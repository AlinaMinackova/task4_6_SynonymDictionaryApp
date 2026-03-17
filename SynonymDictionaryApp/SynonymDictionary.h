#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class CSynonymDictionary
{
public:
    void LoadFromFile(const std::string& filename);
    std::string GetRandomSynonym(const std::string& word) const;
    bool Contains(const std::string& word) const;

private:
    std::unordered_map<std::string, std::vector<std::string>> m_dictionary;
};