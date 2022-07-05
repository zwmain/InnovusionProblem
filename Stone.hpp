/**
 * @file Stone.hpp
 * @author zwmain (zwmain@outlook.com)
 * @brief Find stone pair(s) 题解
 * @version 1.0
 * @date 2022-07-05
 *
 * @copyright Copyright (c) 2022 zwmain
 *
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * @brief 寻找一对重量差为指定值的石头
 *
 * @param stoneArr 石头重量数组
 * @param diff 差值
 * @return std::pair<size_t, size_t> 差值为diff的一对石头的索引，当找不到时，值为{-1, -1}
 */
std::pair<size_t, size_t> findStonePairB1(const std::vector<double>& stoneArr, double diff)
{
    std::pair<size_t, size_t> res { -1, -1 };
    // 从第一个数开始向后遍历
    for (size_t i = 0; i < stoneArr.size(); ++i) {
        // 从第一个石头的位置后一位开始向后遍历
        for (size_t j = i + 1; j < stoneArr.size(); ++j) {
            // 如果两个石头重量差的绝对值与diff相同，返回
            if (std::fabs(stoneArr[j] - stoneArr[i]) == diff) {
                res = { i, j };
                return res;
            }
        }
    }
    // 没找到重量差为diff的两个石头
    return res;
}

/**
 * @brief 寻找一对重量差为指定值的石头
 *
 * @param stoneArr 石头重量数组
 * @param diff 差值
 * @return std::pair<size_t, size_t> 差值为diff的一对石头的索引，当找不到时，值为{-1, -1}
 */
std::pair<size_t, size_t> findStonePairB2(const std::vector<double>& stoneArr, double diff)
{
    std::pair<size_t, size_t> res { -1, -1 };
    // 石头重量和石头索引的字典
    std::unordered_map<double, size_t> stoneMap;
    for (size_t i = 0; i < stoneArr.size(); ++i) {
        // 计算当前石头加上差值后的值
        double tarVal = stoneArr[i] + diff;
        // 只有当目标值不存在时，加入字典
        if (stoneMap.find(tarVal) == stoneMap.end()) {
            stoneMap[tarVal] = i;
        }
    }
    for (size_t i = 0; i < stoneArr.size(); ++i) {
        // 把当前值当作目标值查询
        auto it = stoneMap.find(stoneArr[i]);
        // 如果查询到结果，说明目标值存在
        // 目标值对应的索引就是加上diff之前的石头的索引
        if (it != stoneMap.end() && it->second != i) {
            res = std::minmax(i, it->second);
            return res;
        }
    }
    return res;
}

/**
 * @brief 获取所有差值为指定值的石头
 *
 * @param stoneArr 石头重量数组
 * @param diff 差值
 * @return std::vector<std::pair<size_t, size_t>> 差值为diff的一组石头索引，找不到时数组为空
 */
std::vector<std::pair<size_t, size_t>> findStonePairs(const std::vector<double>& stoneArr, double diff)
{
    std::vector<std::pair<size_t, size_t>> res;
    // 石头重量和索引数组的字典
    std::unordered_map<double, std::vector<size_t>> stoneMap;
    for (size_t i = 0; i < stoneArr.size(); ++i) {
        // 计算目标值
        // 并将目标值相同的石头索引放入数组中
        double tarVal = stoneArr[i] + diff;
        auto it = stoneMap.find(tarVal);
        if (it == stoneMap.end()) {
            stoneMap.emplace(tarVal, std::vector<size_t>({ i }));
        } else {
            it->second.push_back(i);
        }
    }
    for (size_t i = 0; i < stoneArr.size(); ++i) {
        // 把当前值当作目标值查询
        auto it = stoneMap.find(stoneArr[i]);
        if (it == stoneMap.end()) {
            continue;
        }
        // 如果查询到结果，说明有一组石头加上差值后可以与当前石头相同
        for (size_t j : it->second) {
            res.push_back(std::minmax(i, j));
        }
    }
    return res;
}
