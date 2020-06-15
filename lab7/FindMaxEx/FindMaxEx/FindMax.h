#pragma once
#include "stdafx.h"
#include "Sportsman.h"

template <typename T>
bool Less(T const& a, T const& b)
{
    return a < b;
}

bool LessHeight(Sportsman const& a, Sportsman const& b)
{
    return a.Height < b.Height;
}

bool LessWeight(Sportsman const& a, Sportsman const& b)
{
    return a.Weight < b.Weight;
}

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
    if (arr.empty())
    {
        return false;
    }

    for (auto t : arr)
    {
        if (less(maxValue, t))
        {
            maxValue = t;
        }
    }

    return true;
}