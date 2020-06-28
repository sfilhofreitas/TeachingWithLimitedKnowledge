import numpy as np

class PacTeacher():	
	def __init__(self, m, k, seed=0, frac_start=0.01, frac_stop=0.2):
		self.k = int(np.ceil(k*m))
		self.name = 'PacTeacher'
		self.m = m
		self.seed = seed
		self.is_subset = True #In the future can be insteresting the possibility of change for False
		self.__random = np.random.RandomState(self.seed)
		self.aux = [i for i in range(self.m)]
		if self.is_subset:
			self.__random.shuffle(self.aux)
		self.frac_stop = frac_stop
		self.frac_start = frac_start
		
	def get_example(self, qtd, i=0):
		if self.is_subset:
			return self.aux[i:i+qtd]
		else:
			return [x for x in self.__random.choice(self.m, qtd, replace=False)]
		
	def teaching(self, learner):	
		## evitar testes desnecessarios
		if learner.seed != 0 and self.is_subset:
			return [], [], ''
		##
		self.__random = np.random.RandomState(self.seed)
		
		log = ''
		learner.restart()
		S = learner.initialize(self.frac_start)
		self.aux = [ x for x in self.aux if x not in S]
		acc_list = []
		i, it = 0, 1
		log += str(0)+','+self.name+','+learner.name+','+learner.data_instance.name+','+str(self.m)+','+str(self.seed)+','+str(learner.seed)+','+str(learner.data_instance.seed)+','+str(self.k)+','+str(0)+','+str(0)+','+str(0)+','+str(0)+','+str(learner.full_data_acc)+'\n'
		while True:
			#print(len(S))
			delta_h = learner.get_h(S)
			acc_list.append((i,1-(len(delta_h)/self.m)))
			acc_S = 1 - (np.intersect1d(delta_h, S).size/len(S))

			log += str(it)+','+self.name+','+learner.name+','+learner.data_instance.name+','+str(self.m)+','+str(self.seed)+','+str(learner.seed)+','+str(learner.data_instance.seed)+','+str(self.k)+','+str(self.k)+','+str(len(S))+','+str(acc_S)+','+str(acc_list[-1][1])+','+str(learner.full_data_acc)+'\n'
			
			if (self.is_subset and len(np.setdiff1d(delta_h, S)) == 0) or (len(S)>=int(self.m*self.frac_stop)):
				break

			if self.is_subset: 
				samples = self.get_example(self.k,i)
				S += samples[: int(self.m*self.frac_stop)-len(S)]
				i += self.k

			else: 
				S = self.get_example(i)
				i += 1
			it += 1
		
		return S, acc_list, log