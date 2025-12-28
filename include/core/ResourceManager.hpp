#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

// Generic resource manager to cache SFML resources by string key

template <typename Resource>
class ResourceManager
{
public:
    Resource& get(const std::string& id)
    {
        auto found = resources.find(id);
        if (found == resources.end())
        {
            throw std::runtime_error("Resource not loaded: " + id);
        }
        return *found->second;
    }

    bool load(const std::string& id, const std::string& filename)
    {
        auto res = std::make_unique<Resource>();
        if (!res->loadFromFile(filename))
        {
            return false;
        }
        resources[id] = std::move(res);
        return true;
    }

    bool contains(const std::string& id) const
    {
        return resources.find(id) != resources.end();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> resources;
};
