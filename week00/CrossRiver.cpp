//
// Created by convi on 2020/3/23.
//

#include "CrossRiver.h"

const int INF = 0x3f3f3f3f;
const int maxn = 1000010;

bool vis[maxn];
int dist[maxn];
int front[maxn];    //记录前驱结点

Coordinate status[maxn];     //用于存储所有的允许状态
std::vector<Edge> edges[maxn];

CrossRiver::CrossRiver(int peopleNum, int shipCapacity) : people_num(peopleNum), ship_capacity(shipCapacity) {
    status_num = 3 * people_num + 1;
    end_pos = 2 * (people_num + 1) + status_num;
    start_pos = 1;
}

void CrossRiver::Dijkstra(int start) {
    memset(vis, false, sizeof(vis));
    memset(dist, INF, sizeof(dist));

    std::priority_queue<qnode> que;
    dist[start] = 0;
    que.push(qnode(start, 0));
    qnode tmp;
    while (!que.empty()) {
        tmp = que.top();
        que.pop();
        int u = tmp.v;
        if (vis[u])
            continue;
        vis[u] = true;
        for (size_t i = 0; i < edges[u].size(); ++i) {
            int v = edges[tmp.v][i].v;
            int cost = 1; //无权图可以看作权重全是1的图
            if (!vis[v] && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push(qnode(v, dist[v]));
                front[v] = u;
            }
        }
    }
}

void CrossRiver::storeStatus() {
    int s_pos = 1; //status 的下标
    for (int j = people_num; j >= 0; j--) {
        status[s_pos] = status[s_pos + status_num] = Coordinate(people_num, j);    //将图存成两份
        s_pos++;
        status[s_pos] = status[s_pos + status_num] = Coordinate(0, j);
        s_pos++;
    }
    for (int i = 1; i < people_num; i++) {
        status[s_pos] = status[s_pos + status_num] = Coordinate(i, i);
        s_pos++;
    }
}

void CrossRiver::buildEdge() {
    for (int i = 1; i <= status_num; i++) {
        for (int j = 1; j <= status_num; j++) {
            int x_gap = status[i].x - status[j].x;
            int y_gap = status[i].y - status[j].y;
            int sum_gap = x_gap + y_gap;
            //允许的策略
            if (x_gap >= 0 && y_gap >= 0 && sum_gap >= 1 && sum_gap <= ship_capacity) {
                edges[i].emplace_back(j + status_num);
                edges[j + status_num].emplace_back(i);
            }
        }
    }
}

void CrossRiver::run() {
    storeStatus();
    buildEdge();
    Dijkstra(start_pos);

    std::vector<Coordinate> out_left;    //河这岸的状态（人数）变化
    std::vector<Coordinate> out_right;    //河对岸的状态（人数）变化

    int pos = end_pos;
    out_left.push_back(status[pos]);
    while (pos != start_pos) {        //通过 front 数组不断迭代前驱结点，记录路径
        out_left.push_back(status[front[pos]]);
        pos = front[pos];
        if (pos < 1 || pos > status_num * 2) {
            std::cout << "The method doesn't exit." << std::endl;
            return;
        }
    }

    //河对岸的人数等于总人数减去这岸的人数
    out_right.resize(out_left.size());
    for (size_t i = 0; i < out_left.size(); i++) {
        out_right[i] = Coordinate(people_num, people_num) - out_left[i];
    }

    //输出
    printf("%40s", "The method is:\n");
    printf("%10s%10s%17s%10s%10s\n", "Salesman", "Follower", "River(S,F)River", "Salesman", "Follower");

    Coordinate on_boat(0, 0);
    bool this_bank = true; //小船在河的此岸
    for (int i = (int) out_left.size() - 1; i >= 0; i--) {
        if (this_bank) {
            printf(" %5d     %5d    ", out_left[i].x, out_left[i].y);
            on_boat = out_right[i - 1] - out_right[i];
            printf("  --->(%-2d,%2d)--->", on_boat.x, on_boat.y);
            printf("      %-5d     %-5d\n", out_right[i].x, out_right[i].y);
            printf("%54c\n", '|');
        } else {
            printf(" %5d     %5d    ", out_left[i].x, out_left[i].y);
            if (i == 0) {
                printf("%17s", " ");
                printf("      %-5d     %-5d\n", out_right[i].x, out_right[i].y);
                printf("\n\n");
                break;
            }
            on_boat = out_left[i - 1] - out_left[i];
            printf("  <---(%-2d,%2d)<---", on_boat.x, on_boat.y);
            printf("      %-5d     %-5d\n", out_right[i].x, out_right[i].y);
            i == 1 ? printf("\n") : printf("%6c\n", '|');
        }
        this_bank = !this_bank;
    }
    std::cout << out_left.size() - 1 << " steps in total.\n" << std::endl;
}