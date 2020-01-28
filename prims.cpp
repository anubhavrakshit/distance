#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <bits/stdc++.h> 

using std::priority_queue;
using std::vector;
using std::set;

class Point {
public:
    int x;
    int y;
    int idx;
    double c; // cost
    Point(int x, int y, int idx)
    {
        this->c = INT_MAX;
        this->x = x;
        this->y = y;
        this->idx = idx;
    }

    double dist(Point p) {
        double xd = p.x - x;
        double yd = p.y - y;
        return sqrt(xd*xd + yd*yd);
    }
};

struct Compare {
    constexpr bool operator()(std::pair<double, Point> const & a,
                              std::pair<double, Point> const & b) const noexcept
    { return a.first > b.first; }
};
double minimum_distance(vector<int> x, vector<int> y) {
    double result = 0;

    vector <Point> points;
    for (unsigned int i = 0; i < x.size(); i++) {
        Point tmp(x[i], y[i], i);
        points.push_back(tmp);
    }
    set<int> in_tree;
    // Set start Point cost to 0
    points[0].c = 0;
    // Start of our MST
    in_tree.insert(0);
    // Pair (Cost, Point) to store in PQ
    priority_queue <std::pair<double, Point>, vector<std::pair<double, Point> >, Compare > PQ;
    // Insert Points by cost to PQ
    for (auto p: points) {
        PQ.push(std::make_pair(p.c, p));
    }
    while (!PQ.empty()) {
        std::pair<int, Point> p = PQ.top();
        PQ.pop();
        Point p_min = p.second;
        // Insert to our MST
        in_tree.insert(p_min.idx);
        //std::cout << "Min Point x = " << p_min.x << " y = " << p_min.y << " c = " << p_min.c << std::endl;
        // Go through neighbours and change Cost if necessary
        for (auto& p_nbr: points) {
            //std::cout << "Examine Nbr Point x = " << p_nbr.x << " y = " << p_nbr.y << " c = " << p_nbr.c << "Edge Wt = " << p_nbr.dist(p_min) <<std::endl;
            if (in_tree.find(p_nbr.idx) == in_tree.end() && p_nbr.dist(p_min) < p_nbr.c) {
                // Update cost of this nbr
                p_nbr.c = p_nbr.dist(p_min);
                //std::cout << "Upd Nbr Point x = " << p_nbr.x << " y = " << p_nbr.y << " c = " << p_nbr.c << std::endl;
                PQ.push(std::make_pair(p_nbr.c, p_nbr));
            }
        }
    }

    for (auto p: points) {
        result += p.c;
    }

    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
