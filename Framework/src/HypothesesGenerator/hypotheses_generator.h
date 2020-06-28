#ifndef HYPOTHESES_GENERATOR_H
#define HYPOTHESES_GENERATOR_H
#include "../Utils/util_random.h"
//#include "../Utils/heuristics.h"
#include <bits/stdc++.h>
#include<vector>

using namespace std;

class HypothesesGenerator{
    protected:
        string name;
        UtilRandom randomState = NULL;
        int seed;
        int n;
        int m;
        bool hasPerfect;
        vector<vector<int>> cover;
        vector<vector<int>> H;
        vector<int> greedySolution;
        vector<double> acc;
        vector<bool> sorted;

    public:
        string getName() const{return name;}
        int getSeed() const{return seed;}
        int getN() const{return n;}
        bool getHasPerfect() const{return hasPerfect;}
        vector<int> getCover(int i) const{return cover[i];}
        vector<int> getH(int i) const{return H[i];}
//        vector<int>& getH(int i) {return H[i];}
        int getM() const{return m;}
        vector<int> const & getGreedySolution(){return greedySolution;}
        int getGreedySolutionSize(){return greedySolution.size();}
        double getAcc(int i) {return acc[i];}
        vector<double> const & getAcc(){return acc;}
        bool getSorted(int i) {return sorted[i];}
        void setSorted(int i, bool value){this->sorted[i]=value;}
        void sortH(int i){
            sort(this->H[i].begin(), this->H[i].end());
            this->sorted[i] = true;
        }
};

#endif // HYPOTHESES_GENERATOR_H

