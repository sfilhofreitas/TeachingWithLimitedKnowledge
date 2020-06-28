import numpy as np

class WeightsTheoreticalFounded():	
	def __init__(self, m, seed=0, frac_start=0.01, frac_stop=0.5):
		self.name = 'WeightsTheoreticalFounded'
		self.m = m
		self.seed = seed
		self.__random = np.random.RandomState(self.seed)
		self.n = 1
		self.w = np.array([1/(2.0*self.m) for x in range(self.m)])
		self.frac_stop = frac_stop
		self.frac_start = frac_start
		
	

	def get_example(self, X, delta_w):
		random_numbers = self.__random.rand(self.n)
		random_numbers = np.sort(random_numbers)
		j = 0
		i = 0
		aux = 0
		flag = True
		len_X = len(X)
		S = []
		while j<self.n and i < len_X:
			if flag:
				aux+=delta_w[i]
			flag = False
			if random_numbers[j]<=aux:				
				if random_numbers[j]>(aux-delta_w[i]):
					S.append(X[i])
					flag = True
					i+=1
				j+=1      
			else:
				i+=1
				flag = True
		if len(S)==0: return None
		return S
		
	def teaching(self, learner):	
		self.__random = np.random.RandomState(self.seed)
		self.n = 1
		self.w.fill(1/(2.0*self.m))		
		learner.restart()
		S = learner.initialize(self.frac_start)    
		acc_list = []
		log = ''
		i = 1
		samples = []
		flag = True
		log += str(0)+','+self.name+','+learner.name+','+learner.data_instance.name+','+str(self.m)+','+str(self.seed)+','+str(learner.seed)+','+str(learner.data_instance.seed)+','+str(self.n)+','+str(0)+','+str(0)+','+str(0)+','+str(0)+','+str(learner.full_data_acc)+'\n'
		while(True):
			if samples != None:
				delta_h = learner.get_h(S)
				acc = 1-(len(delta_h)/self.m)
				acc_list.append((1,acc))
				acc_S = 1 - (np.intersect1d(delta_h, S).size/len(S))
				delta_h = np.setdiff1d(delta_h, S)
			if flag:
				log += str(i)+','+self.name+','+learner.name+','+learner.data_instance.name+','+str(self.m)+','+str(self.seed)+','+str(learner.seed)+','+str(learner.data_instance.seed)+','+str(self.n)+','+str(len(samples))+','+str(len(S))+','+str(acc_S)+','+str(acc)+','+str(learner.full_data_acc)+'\n'

			
			if (len(delta_h) == 0) or (len(S)>=int(self.m*self.frac_stop)):
				break
			
			v = np.sum(self.w[delta_h])
			if v >= 1.0:
				self.n *= 2
				self.w.fill(1/(2*self.m))
				v = (1/(2*self.m))*len(delta_h)
			
			k = 1
			while v*k < 1.0:
				k = k*2

			old_w = [self.w[x] for x in delta_h]			
			self.w[delta_h] *= k			    
			delta_w = [(self.w[x]-old_w[i])/2 for i,x in enumerate(delta_h)]
			
			samples = self.get_example(delta_h, delta_w)
			if samples != None:
				S += samples[:int(self.m*self.frac_stop)-len(S)]#min(len(samples), int(self.m*1)-len(S))
				flag = True
				i += 1
			else:
				flag = False
				self.n *= 2
				self.w.fill(1/(2*self.m))
				
		return S, acc_list, log