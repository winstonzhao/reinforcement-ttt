#pragma once
#include <array>
#include <unordered_map>
#include <vector>
#include <map>

using Board = std::array<int, 9>;
struct BoardHasher
{
    std::size_t operator()(const Board &a) const
    {
        std::size_t h = 0;

        for (auto e : a)
        {
            h ^= std::hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};
using StateActionPairs = std::unordered_multimap<Board, int, BoardHasher>;
struct StateActionHasher
{
    std::size_t operator()(const std::pair<Board, int> &a) const
    {
        std::size_t h = 0;

        for (auto e : a.first)
        {
            h ^= std::hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        h ^= std::hash<int>{}(a.second) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};
using Policy = std::unordered_map<Board, std::vector<std::pair<int, double>>, BoardHasher>;

template <typename T>
using QMap = std::map<std::pair<Board, int>, T>;