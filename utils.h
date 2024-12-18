#pragma once
#include <vector>


// Returns a filtered vector with values from `src` for which corresponding value in
// `inliers` is "true".
template<class T, class U>
std::vector<T> filter(const std::vector<T>& src, const std::vector<U>& inliers) {
    std::vector<T> dst;

    auto it = src.begin();
    auto it2 = inliers.begin();

    for (; it != src.end(); ++it, ++it2) {
        if (*it2)
            dst.push_back(*it);
    }

    return dst;
}
