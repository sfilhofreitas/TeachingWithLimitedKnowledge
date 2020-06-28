import numpy as np
from sklearn.metrics import accuracy_score 
import lightgbm as lgb

class LGBM():
	def __init__(self, data_instance, seed=0):
		self.name = 'LGBM'
		self.seed = seed
		self.data_instance = data_instance
		self.full_data_acc = self.set_full_data_acc()
		self.restart()
		
	def get_h(self, X):
		self.clf.fit(self.data_instance.X[X], self.data_instance.y[X])
		h = self.clf.predict(self.data_instance.X)
		
		delta_h = [i for i in range(self.data_instance.m) if h[i] != self.data_instance.y[i]]
		
		return delta_h
	
	def initialize(self, prop):
		S = []
		n_samples = prop*self.data_instance.m
		class_distribution = [0 for c in self.data_instance.classes]
		for c in self.data_instance.y:
			class_distribution[c] += 1
		class_samples = [np.ceil((c/self.data_instance.m)*n_samples) for c in class_distribution]
		n_samples = np.sum(class_samples)
		cont = 0
		classes_number = len(self.data_instance.classes)
		v_cont = [0 for x in range(classes_number)]
		aux = [i for i in range(self.data_instance.m)]
		self.__random.shuffle(aux)
		i = 0
		while (cont < n_samples):
			if v_cont[self.data_instance.y[aux[i]]] < class_samples[self.data_instance.y[aux[i]]]:
				S.append(aux[i])
				cont+=1
				v_cont[self.data_instance.y[aux[i]]] += 1
			i+=1

		return S
	
	
	def set_full_data_acc(self):
		self.restart()
		self.clf.fit(self.data_instance.X, self.data_instance.y)
		h = self.clf.predict(self.data_instance.X)
		
		delta_h = [i for i in range(self.data_instance.m) if h[i] != self.data_instance.y[i]]
		acc = 1-(len(delta_h)/self.data_instance.m)
		return acc

	def restart(self):
		self.clf = lgb.LGBMClassifier(random_state=self.seed, n_jobs=1)
		self.__random = np.random.RandomState(self.seed)
        
            