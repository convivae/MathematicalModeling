#ifndef MATHEMATICALMODELING_CROSSRIVER_H
#define MATHEMATICALMODELING_CROSSRIVER_H

/**
 * Created by convi on 2020/3/23.
 *
 * 在河的一侧，有N个商人和N个随从需要过河，河中有一条小船，一次最多只能载重M人。
 * 随从们密约，在河的任一岸，一旦随从的人数多于商人的人数，就杀人越货，乘船渡河的方案由商人决定。
 * 问：商人们有安全过河的方案吗？如果有，怎样才能安全过河？
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

struct Coordinate {    //坐标
    int x, y;

    explicit Coordinate(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    Coordinate operator-(const Coordinate &r) {
        return Coordinate(this->x - r.x, this->y - r.y);
    }
};

struct qnode {
    int v, c;

    explicit qnode(int _v = 0, int _c = 0) : v(_v), c(_c) {}

    bool operator<(const qnode &r) const {
        return c > r.c;
    }
};

struct Edge {
    int v;

    explicit Edge(int _v) : v(_v) {}
};


class CrossRiver {
private:
    int people_num;        //既是商人的人数，也是随从的人数
    int ship_capacity;    //船的容量
    int status_num;        //格点的数目（允许的状态的数目）
    int start_pos;    //源点标号，从图上来看，源点为右上角的点，将其记录为 1 号节点
    int end_pos;        //终点标号，从图上来看，其位于左下角（0，0）这个点，它的标号需要根据人数来计算

    void Dijkstra(int start); //使用优先队列优化的迪杰斯特拉算法

    void storeStatus();    //存储所有允许的状态

    void buildEdge(); //建边
public:
    CrossRiver(int peopleNum, int shipCapacity);

    void run();
};


#endif //MATHEMATICALMODELING_CROSSRIVER_H
