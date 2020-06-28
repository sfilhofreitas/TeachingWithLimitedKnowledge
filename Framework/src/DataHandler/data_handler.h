#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>


using namespace std;

class DataHandler
{
private:
    std::string output_path;
    std::string output_folder;
    std::string configPath;
    std::vector<std::string> teachersLine;
    std::vector<std::string> learnersLine;
    std::vector<std::string> hypothesesLine;
    int numExamples, numHypotheses, teacherRepetitions, learnerRepetitions;

    std::vector<std::string> getList(std::string line);
    void setSolutionPath(std::string line);

public:
    DataHandler(string configPath);
    const std::vector<std::string> split(const std::string& s, const char& c);

    //std::vector<RandomIterative> getRandomIterativeTeachers(std::string teacherStr);


    std::vector<std::string> getHypothesesLine() const;
    int getNumExamples() const;
    int getNumHypotheses() const;
    int getTeacherRepetitions() const;
    int getLearnerRepetitions() const;
    std::vector<std::string> getLearnersLine() const;
    std::vector<std::string> getTeachersLine() const;
    std::string getOutput_path() const;
    std::string getOutput_folder() const;
};

#endif // DATA_HANDLER_H
