#ifndef HEURISTICS_H
#define HEURISTICS_H
#include<vector>
#include <algorithm>
#include "Learners/learner.h"
#include "HypothesesGenerator/hypotheses_generator.h"
using namespace std;

class Heuristics
{
public:
    Heuristics();
    vector<int> getMinimalCover(HypothesesGenerator *hipGenerator, vector<int> &teachingSet);
    vector<int> getGreedyCover(HypothesesGenerator* hipGenerator);

    bool checkMinimalCover(Learner& learner, vector<int> &teachingSet, vector<int> &heuristicSolution);
    bool checkGreedyCover(HypothesesGenerator* hipGenerator, vector<int> &greedySolution);
};

#endif // HEURISTICS_H
