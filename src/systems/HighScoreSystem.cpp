#include "systems/HighScoreSystem.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

bool HighScoreSystem::load(const std::string& path)
{
    scores.clear();
    std::ifstream in(path);
    if (!in)
    {
        return false;
    }
    std::string line;
    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        HighScoreEntry e;
        if (iss >> e.name >> e.score)
        {
            scores.push_back(e);
        }
    }
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) { return a.score > b.score; });
    if (scores.size() > MaxEntries)
        scores.resize(MaxEntries);
    return true;
}

bool HighScoreSystem::save(const std::string& path) const
{
    std::ofstream out(path);
    if (!out)
        return false;
    for (const auto& e : scores)
    {
        out << e.name << " " << e.score << "\n";
    }
    return true;
}

void HighScoreSystem::submit(const std::string& name, int score)
{
    scores.push_back({name, score});
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) { return a.score > b.score; });
    if (scores.size() > MaxEntries)
        scores.resize(MaxEntries);
}
