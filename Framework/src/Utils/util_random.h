#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H
#include<random>
#include<vector>
#include<iostream>
#define MAX_INT 2147483647
using namespace std;
class UtilRandom{
mt19937 rng;
default_random_engine generator;
uniform_real_distribution<double> real_distribution;//(0.0,1.0);
uniform_int_distribution<int> int_distribution;

int seed;
public:
    UtilRandom(int seed);
    double random();
    vector<double> random(int n);
    int randInt(int min, int max);
    vector<int> choice(int n, int k, vector<double> p);
    vector<int> choice(int n, int k);
    vector<int> choice(vector<int> v, int k);
    vector<int> choice(vector<int> v, int k, vector<double> p);
    void shuffle(vector<int> &v);
    void reset();
};

#endif // UTIL_RANDOM_H
