#ifndef SIMPLE_RANDOM_HYPOTHESES_H
#define SIMPLE_RANDOM_HYPOTHESES_H
#include<vector>
#include<iostream>
#include <bits/stdc++.h>
#include<math.h>
#include "hypotheses_generator.h"
#include "../Utils/heuristics.h"

using namespace std;

class SimpleRandomHypotheses: public HypothesesGenerator{
private:
    vector<double> accList;
    double hardSamples;
    double hardFrac;
    vector<int> sum;
    int c;
    void generateH();
    vector<int> get_h();

public:
    SimpleRandomHypotheses(int n, int m, vector<double> accList, double hardSamples, double hardFrac, bool hasPerfect, int seed);
    int getM() const;

};

#endif // SIMPLE_RANDOM_HYPOTHESES_H
