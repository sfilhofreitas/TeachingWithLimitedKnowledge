import numpy as np
import pandas as pd
from sklearn import preprocessing  

class RealData():	
	def __init__(self, dataset_path, is_numeric=True, name='RealData', seed=0):
		self.name = name
		self.__random = np.random.RandomState(seed)
		data  = pd.read_csv(dataset_path, header=None, sep=',')
		self.y = data[0].values
		le = preprocessing.LabelEncoder()		
		self.y = le.fit_transform(self.y)
		if is_numeric:			
			self.X = data.drop(columns=[0]).values
		else:
			data = data.drop(columns=[0])
			self.X = pd.get_dummies(data, columns=data.columns).values
				
		self.classes = np.unique(self.y)
		self.m = len(self.y) 		
		self.seed = seed
		
		

