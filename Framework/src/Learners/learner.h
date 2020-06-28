#ifndef LEARNER_H
#define LEARNER_H
#include<iostream>
#include<vector>
#include "../Utils/util_random.h"
//#include "../HypothesesGenerator/simple_random_hypotheses.h"
#include "../HypothesesGenerator/hypotheses_generator.h"
using namespace std;

class Learner{
protected:
    string name;
    UtilRandom randomState = NULL;
    HypothesesGenerator *hipGenerator;
    int seed;

public:
    string getName() const{return this->name;}
    HypothesesGenerator *getHipGenerator() const{return hipGenerator;}
    int getSeed() const{return this->seed;}
    virtual vector<int> get_h(const vector<int> &samples) = 0;
    virtual void restart() = 0;

};

#endif // LEARNER_H
