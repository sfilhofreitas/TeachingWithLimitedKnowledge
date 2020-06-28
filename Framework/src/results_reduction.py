#!/usr/bin/env python
# coding: utf-8

# In[9]:


import os
import numpy as np
import pandas as pd
import sys


# In[10]:


path = sys.argv[1]


# In[11]:


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


# In[12]:


for file in csv_paths:
    table_log = pd.read_csv(file, sep=',')
    table_log = table_log[table_log['ACCURACY']>= 1.0]
    output = '/'.join(file.split('/')[:-1])+'/reduction_performance.txt'
    output_file = open(output, 'w')
    output_file.write('AVG TEACHING SET SIZE,AVG HEURISTIC SOLUTION SIZE,AVG REDUCTION PERFORMANCE\n')
    table_log['TEACHING SET SIZE'] = table_log['TEACHING SET SIZE'].astype('int64')
    table_log['HEURISTIC SOLUTION'] = table_log['HEURISTIC SOLUTION'].astype('int64')
    string  = str(table_log['TEACHING SET SIZE'].mean())+','
    string += str(table_log['HEURISTIC SOLUTION'].mean())+','
    string += str((1-(table_log['HEURISTIC SOLUTION']/table_log['TEACHING SET SIZE'])).mean())+'\n'
    output_file.write(string)
    output_file.close()


# In[ ]:




