#ifndef WEIGHTS_THEORETICAL_FOUNDED_H
#define WEIGHTS_THEORETICAL_FOUNDED_H
#include<string>
#include<vector>
#include<iostream>
#include <bits/stdc++.h>
#include "Learners/learner.h"
#include "../Learners/optimal_no_perfect.h"
#include "teacher.h"
#include "../Utils/heuristics.h"

using namespace std;


class WeightsTheoreticalFounded: public Teacher{
    int m;
    vector<double> weights;
    int n;

    vector<int> get_example(vector<int>& Examples, vector<double> delta_w);
public:
    WeightsTheoreticalFounded(int m, int seed);
    pair<vector<int>, string> teaching(Learner &learner);
};

#endif // WEIGHTS_THEORETICAL_FOUNDED_H
