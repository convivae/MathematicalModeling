#ifndef MATHEMATICALMODELING_SHEEPDISTRIBUTION_H
#define MATHEMATICALMODELING_SHEEPDISTRIBUTION_H

/**
 * Created by convi on 2020/3/22.
 *
 * 一农民有羊17，分三儿，各得 1/x > 1/y > 1/z (1 < x < y < z)
 * 分得的羊须完整，怎么分
 * 四儿？邻居牵来两只羊怎么分？
 */

#include <vector>
#include <cstdarg>
#include <iostream>
#include <cmath>
#include <fstream>

#include "../lib/Fraction.h"

class SheepDistribution {
private:
    Fraction _neighbor_sheep_num{};    //已知量，常数
    Fraction _son_num{};               //已知量，常数
    Fraction _assigned_sheep_num{};    //待分羊的数目，未知量，待求
    std::vector<Fraction> _sons;     //分配方法，未知量，待求
    std::vector<std::vector<int>> _result;  //最终结果

    void dfs(Fraction remain_num, Fraction left, Fraction equal);

    void save_vec(std::vector<Fraction> vec, Fraction n);

    void print_res(std::ostream &out);

    bool Divisibility(const int &a, const std::vector<Fraction> &b); // a >= b && a % b == 0

public:
    SheepDistribution(int borrow_sheep_num, int son_num)
            : _neighbor_sheep_num(borrow_sheep_num), _son_num(son_num) {
        _sons.resize(son_num);
    }

    void calculate(std::ostream &out);
};

#endif //MATHEMATICALMODELING_SHEEPDISTRIBUTION_H
