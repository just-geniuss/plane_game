#pragma once

#include <vector>
#include <string>

struct HighScoreEntry
{
    std::string name;
    int score;
};

class HighScoreSystem
{
public:
    bool load(const std::string& path);
    bool save(const std::string& path) const;

    void submit(const std::string& name, int score);
    const std::vector<HighScoreEntry>& entries() const { return scores; }

private:
    std::vector<HighScoreEntry> scores;
    static constexpr std::size_t MaxEntries = 10;
};
