#include <iostream>
#include<chrono>
#include<fstream>
#include<algorithm>
#include "DataHandler/data_handler.h"
#include "HypothesesGenerator/simple_random_hypotheses.h"
#include "HypothesesGenerator/hypotheses_generator.h"
#include "Learners/optimal_no_perfect.h"
#include "Learners/learner.h"
#include "Teachers/teacher.h"
#include "Teachers/weights_theoretical_founded.h"
#include "Utils/util_list.h"
#include "Utils/heuristics.h"

using namespace std;

// function to initialize the hypotheses generator following  **************************************
vector<HypothesesGenerator*> getHypotheses(DataHandler &dh);
// **************************************************************************************************

// function to initialize the learners following  **************************************************
vector<Learner*> getLearners(DataHandler &dh, vector<HypothesesGenerator *> hypotheses);
// **************************************************************************************************


// function to initialize the teachers following  **************************************************
vector<Teacher *> getTeachers(DataHandler &dh);
// **************************************************************************************************



int main(int argc, char* argv[]){
    string configPath;
    if(argc==1)
        configPath = "config.txt";
    else
        configPath = string(argv[1]);

    DataHandler dh = DataHandler(configPath);
    //auto start = std::chrono::high_resolution_clock::now();
    cout << "Criando hipoteses\n";
    vector<HypothesesGenerator*> hypotheses = getHypotheses(dh);

    cout << "Criando learners\n";
    vector<Learner*> learners = getLearners(dh, hypotheses);

    cout << "Criando teachers\n";
    vector<Teacher*> teachers = getTeachers(dh);

    cout << "Iniciando...\n";
    int tot = learners.size()*teachers.size();
    int i = 1;

    ofstream output_log(dh.getOutput_path());
    ofstream output_runtime(dh.getOutput_folder()+"runtime.txt");
    string logHeader = "ITER,TEACHER,LEARNER,HYPOTHESES GENERATOR,TEACHER SEED,LEARNER SEED,HYP_GENERATOR SEED,EXAMPLES_ITERATION,TEACHING SET SIZE,HEURISTIC SOLUTION,GREEDY SOLUTION,TEACHING SET ACCURACY,ACCURACY\n";
    output_log << logHeader;

    auto start = std::chrono::high_resolution_clock::now();
    for(auto learner: learners){
        for(auto teacher: teachers){
            cout << "Iter: "<<i << "\\"<<tot<<"\n";
            i++;

            pair<vector<int>, string> solution = teacher->teaching((*learner));
            output_log << solution.second;

        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    output_runtime << elapsed.count();
    output_log.close();
    output_runtime.close();

    return 0;
}


// Code about hypotheses generator following  *****************************************************

vector<HypothesesGenerator*> getSimpleRandomHypotheses(DataHandler &dh, vector<string> &hypothesis){
    vector<HypothesesGenerator*> hypotheses;
    vector<double> accList;
    for(string s: dh.split(hypothesis[1], '_'))
        accList.push_back(stod(s));

    double hardSamples = stod(hypothesis[2]);
    double hardSamplesProp = stod(hypothesis[3]);
    bool hasOpt = hypothesis[4] == "True" ? true: false;

    for(int i=0; i<stoi(hypothesis[5]); i++)
        hypotheses.push_back(new SimpleRandomHypotheses(dh.getNumHypotheses(),
                                 dh.getNumExamples(), accList, hardSamples,
                                 hardSamplesProp, hasOpt, i));
    return hypotheses;
}

vector<HypothesesGenerator*> getHypotheses(DataHandler &dh){
    vector<HypothesesGenerator*> hypotheses;
    for(string h: dh.getHypothesesLine()){
        vector<string> hypothesis = dh.split(h, ' ');
        if(hypothesis[0] == "SimpleRandomHypotheses"){
            vector<HypothesesGenerator*> hyp = getSimpleRandomHypotheses(dh, hypothesis);
            hypotheses.insert(hypotheses.end(), hyp.begin(), hyp.end());
        }else{
            cout << "Problem in creating instances of hypotheses generator, review the config file!";
            exit(-1);

        }
    }

    return hypotheses;
}

// **************************************************************************************************



// functions to initialize the learners following  **************************************************

vector<Learner*> getOptimalNoPerfectLearners(DataHandler &dh, vector<HypothesesGenerator*> hypotheses){
    vector<Learner*> learners;
    for(auto hipothesis: hypotheses){
        for(int i=0; i<dh.getLearnerRepetitions(); i++){
            learners.push_back(new OptimalNoPerfect(hipothesis, i));
        }
    }
    return learners;
}

vector<Learner*> getLearners(DataHandler &dh, vector<HypothesesGenerator*> hypotheses){
    vector<Learner*> learners;
    for(string l: dh.getLearnersLine()){
        vector<string> learner = dh.split(l, ' ');
        if(learner[0] == "OptimalNoPerfect"){
            vector<Learner*> learnersTemp = getOptimalNoPerfectLearners(dh, hypotheses);
            learners.insert(learners.end(), learnersTemp.begin(), learnersTemp.end());
        }else{
            cout << "Problem in creating instances of learners, review the config file!";
            exit(-1);
        }


    }
    return learners;
}

// **************************************************************************************************



// functions to initialize the teachers following  **************************************************


vector<Teacher*> getWeightsTheoreticalFoundedTeacher(DataHandler &dh){
    vector<Teacher*> teachers;
    for(int i=0; i<dh.getTeacherRepetitions(); i++)
        teachers.push_back(new WeightsTheoreticalFounded(dh.getNumExamples(), i));
    return teachers;
}

vector<Teacher*> getTeachers(DataHandler &dh){
    vector<Teacher*> teachers;
    for(string t: dh.getTeachersLine()){
        vector<string> teacher = dh.split(t, ' ');

        if(teacher[0] == "WeightsTheoreticalFounded"){
            vector<Teacher*> teachersTemp = getWeightsTheoreticalFoundedTeacher(dh);
            teachers.insert(teachers.end(), teachersTemp.begin(), teachersTemp.end());
        }else{
            cout << "Problem in creating instances of teachers, review the config file!";
            exit(-1);
        }
    }

    return teachers;
}

// **************************************************************************************************
