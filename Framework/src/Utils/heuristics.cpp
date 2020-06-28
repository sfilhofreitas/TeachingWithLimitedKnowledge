#include "heuristics.h"

Heuristics::Heuristics(){

}

vector<int> Heuristics::getMinimalCover(HypothesesGenerator *hipGenerator, vector<int>& teachingSet){
    vector<int> S;
    int n = hipGenerator->getN();
    vector<int> hist(n, 0);

    for (auto x: teachingSet){
        for (auto h: hipGenerator->getCover(x)){
            hist[h] ++;
        }
    }

    for (auto x: teachingSet){
        bool canRemove = true;
        for (auto h: hipGenerator->getCover(x)){
            if(hist[h] <= 1){
                canRemove = false;
                break;
            }
        }

        if(!canRemove){
            S.push_back(x);
        }else{
            for(auto h: hipGenerator->getCover(x))
                hist[h] --;
        }
    }
    return S;

}

bool isTrue(vector<bool> &U){
    for(auto flag: U)
        if(!flag)
            return false;
    return true;
}

int count(const vector<int>& S, vector<bool>& U){
    int c = 0;
    for(auto v: S)
        if(!U[v])
            c++;
    return c;
}

vector<int> Heuristics::getGreedyCover(HypothesesGenerator *hipGenerator){
    vector<bool> U(hipGenerator->getN(), false);
    U.back() = true; //the optimal hip
    int c = 1;
    int m = hipGenerator->getM();
    int n = hipGenerator->getN();
    vector<int> hist(m);
    int max = 0;
    int max_x = 0;
    for(int x=0; x<m; x++){
        hist[x] = hipGenerator->getCover(x).size();
        if (hist[x] > max){
            max = hist[x];
            max_x = x;
        }
    }

    vector<int> cover = hipGenerator->getCover(max_x);
    c += hist[max_x];
    for(auto h: cover){
        if(U[h])  continue;
        U[h] = true;
        vector<int> delta_h = hipGenerator->getH(h);
        for(auto x: delta_h)
            hist[x] --;
    }

    vector<int> S;
    S.push_back(max_x);
    while(c<n){
        int max = 0;
        int max_x = 0;
        for(int x=0; x<m; x++){
            if (hist[x] > max){
                max = hist[x];
                max_x = x;
            }
        }

        cover = hipGenerator->getCover(max_x);
        c += hist[max_x];
        for(auto h: cover){
            if(U[h])  continue;
            U[h] = true;
            vector<int> delta_h = hipGenerator->getH(h);
            for(auto x: delta_h)
                hist[x] --;
        }
        S.push_back(max_x);
    }

    return S;

}

bool Heuristics::checkMinimalCover(Learner &learner, vector<int> &teachingSet, vector<int> &heuristicSolution){
    vector<bool> U(learner.getHipGenerator()->getN(), false);
    U.back() = true;
    for(auto x: heuristicSolution){
        if(find(teachingSet.begin(), teachingSet.end(), (int)x) == teachingSet.end())
            return false;

        vector<int> cover = learner.getHipGenerator()->getCover(x);
        for(int i=0; i<cover.size(); i++)
            U[cover[i]] = true;
    }

    if(!isTrue(U))
        return false;
    return true;
}

bool Heuristics::checkGreedyCover(HypothesesGenerator *hipGenerator, vector<int> &greedySolution){
    vector<bool> U(hipGenerator->getN(), false);
    U.back() = true;
    for(auto x: greedySolution){
        vector<int> cover = hipGenerator->getCover(x);
        for(auto h: cover)
            U[h] = true;
    }

    if(!isTrue(U))
        return false;
    return true;

}


