#ifndef OPTIMAL_NO_PERFECT_H
#define OPTIMAL_NO_PERFECT_H
#include<iostream>
#include "../HypothesesGenerator/hypotheses_generator.h"
#include "learner.h"
using namespace std;

class OptimalNoPerfect: public Learner{
private:
    int n;
    vector<int> index;
    vector<int> errors_h;
    int index_start;
    int getIndexMinElement();

public:
    OptimalNoPerfect(HypothesesGenerator *hipGenerator, int seed);
    vector<int> get_h(const vector<int> &samples);
    void restart();
};

#endif // OPTIMAL_NO_PERFECT_H
