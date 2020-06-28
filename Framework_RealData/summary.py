#!/usr/bin/env python
# coding: utf-8

# In[5]:


import pandas as pd
import numpy as np
import os
import sys

# In[37]:


ordered_acc = [0.9, 0.95, 0.99]


# In[38]:


path = sys.argv[1]


# In[39]:


csv_paths = []
if os.path.isfile(path):
    csv_paths = [path]
else:
    if path[-1] != '/':
        path +='/'
    for p in os.listdir(path):
        if not os.path.isdir(path+p):
            continue
        for file in os.listdir(path+p):
            if 'csv' in file:                
                csv_paths.append(path+p+'/'+file)


# In[40]:


summary_csv = open(sys.argv[2],'w')


# In[41]:


line  = 'TEACHER,LEARNER,DATASET,DATASET_SIZE,ACC_FULL_DATASET,SCENARIOS,'
for acc in ordered_acc:
    line += 'REACHED_'+str(100*acc)+'%,'
    line += 'AVG_EXAMPLES_'+str(100*acc)+'%,'
    line += 'MIN_EXAMPLES_'+str(100*acc)+'%,'
    line += 'MAX_EXAMPLES_'+str(100*acc)+'%,'
    line += 'STD_EXAMPLES_'+str(100*acc)+'%,'
line = line[:-1]+'\n'
summary_csv.write(line)


# In[42]:


for csv_path in csv_paths:
    results_table = pd.read_csv(csv_path, sep=',')
    teachers = np.unique(results_table['TEACHER'].values)
    learners = np.unique(results_table['LEARNER'].values)
    map_learner_teacher = {}
    for l in learners:
        for t in teachers:
            map_learner_teacher[l+t] = [[] for x in ordered_acc]
            temp_table = results_table[(results_table['LEARNER']== l) & (results_table['TEACHER']==t)]
            learner_seeds = np.unique(temp_table['LEARNER SEED'])
            teacher_seeds = np.unique(temp_table['TEACHER SEED'])
            n_scenarios = len(learner_seeds)*len(teacher_seeds)

            for ls in learner_seeds:
                for ts in teacher_seeds:
                    for i, acc in enumerate(ordered_acc):
                        full_acc = temp_table[(temp_table['LEARNER SEED']==ls) & (temp_table['TEACHER SEED']==ts)].iloc[0]['FULL DATA ACCURACY']
                        acc_r = full_acc*acc
                        result = temp_table[(temp_table['LEARNER SEED']==ls) & (temp_table['TEACHER SEED']==ts) & (temp_table['ACCURACY']>=acc_r)]
                        if result.shape[0] > 0:
                            result = result.iloc[0]
                            map_learner_teacher[l+t][i].append(result['TEACHING SET SIZE'])

            line  =  t+','+l+','+results_table.iloc[0]['DATASET']+','+str(results_table.iloc[0]['DATASET_SIZE'])+','
            line += str(results_table.iloc[0]['FULL DATA ACCURACY'])+','+str(n_scenarios)+','
            for i, acc in enumerate(ordered_acc):
                line += str(len(map_learner_teacher[l+t][i]))+','
                if len(map_learner_teacher[l+t][i]) == 0:
                    line +='-,-,-,-,'
                else:
                    line += str(np.mean(map_learner_teacher[l+t][i]))+','
                    line += str(np.min(map_learner_teacher[l+t][i]))+','
                    line += str(np.max(map_learner_teacher[l+t][i]))+','
                    line += str(np.std(map_learner_teacher[l+t][i]))+','
            line = line[:-1]+'\n'
            summary_csv.write(line)
summary_csv.close()


