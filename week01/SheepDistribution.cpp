//
// Created by convi on 2020/3/22.
//

#include "SheepDistribution.h"

void SheepDistribution::calculate(std::ostream &out) {
    _result.clear();
    dfs(_son_num + _neighbor_sheep_num, Fraction(1), Fraction(1));
    print_res(out);
}

void SheepDistribution::dfs(Fraction remain_num, Fraction left, Fraction equal) {
    if (remain_num == _neighbor_sheep_num) {
        Fraction tmp = (_neighbor_sheep_num / equal) - _neighbor_sheep_num;

        // 判断此时的 n 是否是正整数以及判断能否整除
        if (tmp.has_value() && Divisibility((tmp + _neighbor_sheep_num).value(), _sons)) {
            _assigned_sheep_num = tmp.value();
            save_vec(_sons, _assigned_sheep_num);
        }
        return;
    }

    Fraction right_bound = remain_num / equal;
    int start = left.ceil();
    int end = right_bound.floor();
    if (remain_num == _neighbor_sheep_num + 1 && right_bound.has_value()) {
        end = right_bound.value();
    }

    for (auto i = start; i <= end; i++) {
        _sons[(_son_num + _neighbor_sheep_num - remain_num).value()] = i;
        dfs(remain_num - 1, Fraction(i), equal - Fraction(1) / i);
    }
}

bool SheepDistribution::Divisibility(const int &a, const std::vector<Fraction> &b) {
    for (auto i : b) {
        if (a < i.value() || a % i.value() != 0)
            return false;
    }
    return true;
}

void SheepDistribution::save_vec(std::vector<Fraction> vec, Fraction n) {
    std::vector<int> tmp;
    for (auto i : vec)
        tmp.push_back(i.value());
    tmp.push_back(n.value());
    _result.emplace_back(tmp);
}

void SheepDistribution::print_res(std::ostream &out) {
    for (auto i = 0; i < _son_num.value(); ++i)
        out << "x" << i + 1 << "\t";
    out << "n\t" << "formula" << std::endl;
    for (auto i : _result) {
        for (auto j : i)
            out << j << "\t";
        for (auto j = 0; j < _son_num.value(); ++j) {
            out << "(" << i[_son_num.value()] << "+" << _neighbor_sheep_num.value() << ")" << "/" << i[j];
            if (j != _son_num.value() - 1)
                out << " + ";
        }
        out << " = " << i[_son_num.value()] << std::endl;
    }
    out << "total: " << _result.size() << std::endl;
}