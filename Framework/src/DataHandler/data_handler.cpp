#include "data_handler.h"

std::string removeExtraSpaces(std::string str){
    int n = str.length();
    std::string newStr = "";
    int i=0;
    int j=n-1;
    for(i=0; i<n; i++)
        if(str[i] != ' ') break;
    for(j=n-1; j>0; j--)
        if(str[j] != ' ') break;

    int k=0;
    while(i<=j){
        if(str[i]!='\r' && ((str[i] != ' ') || (newStr[k-1] != ' '))){
            newStr += str[i];
            k++;
        }
        i++;
    }
    return newStr;
}

DataHandler::DataHandler(string configPath){
    this->configPath = configPath;
    std::string line = "";
    //std::ifstream config("../src/config.txt");
    std::ifstream config(this->configPath);

    if (config.is_open()){
       getline (config,line);
       this->setSolutionPath(line);
       getline (config,line);
       teachersLine = this->getList(line);
       getline (config,line);
       learnersLine = this->getList(line);
       getline (config,line);
       hypothesesLine = this->getList(line);
       getline (config,line);
       numExamples = stoi(this->getList(line)[0]);
       getline (config,line);
       numHypotheses = stoi(this->getList(line)[0]);
       getline (config,line);
       teacherRepetitions = stoi(this->getList(line)[0]);
       getline (config,line);
       learnerRepetitions = stoi(this->getList(line)[0]);
       config.close();
     }
     else std::cout << "Unable to open file\n";

}

std::string current_datetime(){
    time_t timer;
    struct tm *horarioLocal;

    time(&timer); // Obtem informações de data e hora
    horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

    string dia = std::to_string(horarioLocal->tm_mday);
    dia = dia.size() == 1 ? "0"+dia : dia;
    string mes = std::to_string(horarioLocal->tm_mon + 1);
    mes = mes.size() == 1 ? "0"+mes : mes;
    string ano = std::to_string(horarioLocal->tm_year + 1900);

    string hora = std::to_string(horarioLocal->tm_hour);
    hora = hora.size() == 1 ? "0"+hora : hora;
    string min  = std::to_string(horarioLocal->tm_min);
    min = min.size() == 1 ? "0"+min : min;
    string sec  = std::to_string(horarioLocal->tm_sec);
    sec = sec.size() == 1 ? "0"+sec : sec;

    return ano+mes+dia+hora+min+sec;
}

void DataHandler::setSolutionPath(std::string line){
    line = split(line, ':')[1];
    line = removeExtraSpaces(line);
    if(line[line.size()-1]=='/')
        line.erase(line.size()-1, line.size()-1);
    string timeNow = current_datetime();
    line += "_"+timeNow;
    this->output_folder = line+"/";
    this->output_path = line + "/"+timeNow + ".csv";
    if(system(("mkdir "+this->output_folder).c_str()) != 0){
        cout << "Error creating output directory!!!";
        exit(-1);
    }
    //system(("cp ./../src/config.txt "+this->output_folder).c_str());
    system(("cp "+this->configPath+" "+this->output_folder).c_str());

}

const std::vector<string> DataHandler::split(const string &s, const char &c){
    std::string buff{""};
    std::vector<std::string> v;

    for(auto n:s){
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

std::vector<std::string> DataHandler::getHypothesesLine() const{
    return hypothesesLine;
}

int DataHandler::getNumExamples() const
{
    return numExamples;
}

int DataHandler::getNumHypotheses() const
{
    return numHypotheses;
}

int DataHandler::getTeacherRepetitions() const
{
    return teacherRepetitions;
}

int DataHandler::getLearnerRepetitions() const
{
    return learnerRepetitions;
}

std::vector<std::string> DataHandler::getLearnersLine() const
{
    return learnersLine;
}

std::vector<std::string> DataHandler::getTeachersLine() const
{
    return teachersLine;
}

std::string DataHandler::getOutput_path() const
{
    return output_path;
}

std::string DataHandler::getOutput_folder() const
{
    return output_folder;
}


std::vector<string> DataHandler::getList(string line){
    std::vector<std::string> v;
    line = split(line, ':')[1];
    line = removeExtraSpaces(line);
    v = split(line, ',');
    for (unsigned int i=0; i<v.size(); i++){
        v[i] = removeExtraSpaces(v[i]);
    }
    return v;
}



//std::vector<RandomIterative> DataHandler::getRandomIterativeTeachers(std::string teacherStr){

//}
