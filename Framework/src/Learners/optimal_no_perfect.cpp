#include "optimal_no_perfect.h"

//int getIndexMinElement(vector<int> const &v){
//    int min_id = 0;
//    int min_elem = v[0];
//    if(min_elem == 0) return 0;
//    for(int i=1; i<v.size(); i++){
//        if(v[i]<min_elem){
//            if(min_elem == 0) break;
//            min_id = i;
//            min_elem = v[i];
//        }
//    }
//    return min_id;
//}

//int getIndexMinElement(vector<int> const &v, vector<int> const &index){
//    int min_id = index[0];
//    int min_elem = v[index[0]];
//    if(min_elem == 0) return index[0];
//    for(int i=1; i<v.size(); i++){
//        if(v[index[i]]<min_elem){
//            if(min_elem == 0) break;
//            min_id = index[i];
//            min_elem = v[index[i]];
//        }
//    }
//    return min_id;
//}


int OptimalNoPerfect::getIndexMinElement(){
    int min_id = index[0];
    int min_elem = errors_h[index[0]];
    if(min_elem == 0) return index[0];
    for(unsigned int i=1; i<errors_h.size(); i++){
        if(errors_h[index[i]]<min_elem){
            if(min_elem == 0) break;
            min_id = index[i];
            min_elem = errors_h[index[i]];
        }
    }
    return min_id;

}

OptimalNoPerfect::OptimalNoPerfect(HypothesesGenerator *hipGenerator, int seed){
    this->name = "OptimalNoPerfect";
    this->hipGenerator = hipGenerator;
    this->n = hipGenerator->getN();
    this->seed = seed;
    this->randomState = UtilRandom(this->seed);
    int k = this->n - (this->hipGenerator->getHasPerfect() ? 1:0);
    for(int i=0; i<k; i++)
        this->index.push_back(i);
    this->randomState.shuffle(this->index);
    if(this->hipGenerator->getHasPerfect())
        this->index.push_back(this->n - 1);

    this->errors_h = vector<int>(this->n, 0);
    this->index_start = 0;

}

//vector<int> OptimalNoPerfect::get_h(const vector<int> & samples){
//    vector<int> errors_h(this->n, 0);
//    for(int i=0; i<samples.size(); i++){
//        vector<int> const &v = this->hipGenerator->getCover(samples[i]);
//        for(int j=0; j<v.size(); j++){
//            errors_h[v[j]] += 1;
//        }
//    }
//    vector<int> v(this->n, 0);
//    for(int i=0; i<this->n; i++){
//        v[i] = errors_h[this->index[i]];
//    }
//    int i = getIndexMinElement(v);
//    return this->hipGenerator->getH(this->index[i]);
//}

vector<int> OptimalNoPerfect::get_h(const vector<int> & samples){
    for(unsigned int i=this->index_start; i<samples.size(); i++){
        vector<int> const &v = this->hipGenerator->getCover(samples[i]);
        for(int j=0; j<v.size(); j++)
            errors_h[v[j]] += 1;
    }
    this->index_start = samples.size();

    int min_index = getIndexMinElement();
    return this->hipGenerator->getH(min_index);
}



void OptimalNoPerfect::restart(){
    this->index_start = 0;
    fill(this->errors_h.begin(), this->errors_h.end(), 0);
}

