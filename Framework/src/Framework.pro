TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    DataHandler/data_handler.cpp \
    Utils/util_random.cpp \
    Learners/optimal_no_perfect.cpp \
    HypothesesGenerator/simple_random_hypotheses.cpp \
    Teachers/weights_theoretical_founded.cpp \
    Utils/util_list.cpp \
    Utils/heuristics.cpp 

HEADERS += \
    DataHandler/data_handler.h \
    Utils/util_random.h \
    Learners/optimal_no_perfect.h \
    HypothesesGenerator/simple_random_hypotheses.h \
    Teachers/weights_theoretical_founded.h \
    Teachers/teacher.h \
    Learners/learner.h \
    HypothesesGenerator/hypotheses_generator.h \
    Utils/util_list.h \
    Utils/heuristics.h 
