#include "pch.h"
#include "pch.h"
#include "SynonymDictionary.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <stdexcept>

void CSynonymDictionary::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open synonyms file");

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        iss >> word;

        std::vector<std::string> synonyms;
        std::string synonym;

        while (iss >> synonym)
        {
            synonyms.push_back(synonym);
        }

        if (!synonyms.empty())
        {
            m_dictionary[word] = synonyms;
        }
    }
}

bool CSynonymDictionary::Contains(const std::string& word) const
{
    return m_dictionary.find(word) != m_dictionary.end();
}

std::string CSynonymDictionary::GetRandomSynonym(const std::string& word) const
{
    auto it = m_dictionary.find(word);
    if (it == m_dictionary.end())
        return word;

    const auto& synonyms = it->second;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(synonyms.size() - 1));

    return synonyms[dist(gen)];
}
