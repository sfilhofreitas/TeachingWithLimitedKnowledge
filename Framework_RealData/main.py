import re
import os
from time import time
import datetime
import numpy as np
import sys
sys.path.append('./Teachers/')
sys.path.append('./Learners/')
sys.path.append('./DataManager/')
from PacTeacher import PacTeacher
from WeightsTheoreticalFounded import WeightsTheoreticalFounded
from RandomForest import RandomForest
from LGBM import LGBM
from RealData import RealData

class data_handler():
	def __init__(self):
		try:
			config_file = open('config.txt', 'r')
			f = config_file.readline().split(':')[1].strip()
			self.output_path = self.__get_solution_path(f)
			self.teachers_line = [teacher.strip() for teacher in re.sub(r" +", " ", config_file.readline().split(':')[1]).split(',')]
			self.learners_line = [learner.strip() for learner in re.sub(r" +", " ", config_file.readline().split(':')[1]).split(',')]
			self.dataset_line = [dataset.strip() for dataset in re.sub(r" +", " ", config_file.readline().split(':')[1]).split(',')]
			self.teacher_repetitions = int(config_file.readline().split(':')[1].strip())
			self.learner_repetitions = int(config_file.readline().split(':')[1].strip())
			config_file.close()
			file = open(self.dataset_line[0].split(' ')[0], 'r')
			self.num_examples = len(file.readlines())
			file.close()

		except :
			print ('Error trying to read config.txt')

		

	def __get_solution_path(self, output_path):
		time_now = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
		if output_path[-1] =='/':
			output_path = output_path[:-1]
		output_path += '_'+time_now
		self.output_folder = output_path
		try:
		    os.mkdir(output_path)
		except OSError:
		    print ("Creation of the directory %s failed" % output_path)
		
		output_path+= '/'+time_now + '.csv'

		return output_path

def __get_PacTeacher(data_handler, teacher):
	teachers = []
	for i in range(data_handler.teacher_repetitions):
		teachers.append(PacTeacher(data_handler.num_examples, float(teacher[1]), i,float(teacher[2]), float(teacher[3])))
	return teachers


def __get_WeightsTheoreticalFounded_teacher(data_handler, teacher):
	teachers = []
	for i in range(data_handler.teacher_repetitions):
		teachers.append(WeightsTheoreticalFounded(data_handler.num_examples, i, float(teacher[1]), float(teacher[2])))
	return teachers


def __get_RandomForest_learner(data_handler, data_instance):
	learners = []
	for i in range(data_handler.learner_repetitions):
		learners.append(RandomForest(data_instance, i))
	return learners


def __get_LGBM_learner(data_handler, data_instance):
	learners = []
	for i in range(data_handler.learner_repetitions):
		learners.append(LGBM(data_instance, i))
	return learners

def __get_RealData(dataset_path):		
	return RealData(dataset_path[0], is_numeric=(dataset_path[1]=='True'), name=dataset_path[2])

def get_learners(data_handler, data_instance):
	learners = []
	for learner	in data_handler.learners_line:
		learner = learner.split(' ')
		if learner[0] == 'RandomForest':
			learners+=__get_RandomForest_learner(data_handler, data_instance)
		elif learner[0] == 'LGBM':
			learners+=__get_LGBM_learner(data_handler, data_instance)

	return learners

def get_teachers(data_handler):
	teachers = []
	for teacher in data_handler.teachers_line:
		teacher = teacher.split(' ')
		if teacher[0] == 'PacTeacher':
			teachers += __get_PacTeacher(data_handler, teacher)
		elif teacher[0] == 'WeightsTheoreticalFounded':
			teachers += __get_WeightsTheoreticalFounded_teacher(data_handler, teacher)
		
	return teachers

def get_data_instance(data_handler):
	data_instance = data_handler.dataset_line[0]
	data_instance = data_instance.split(' ')
	data_instance = __get_RealData(data_instance)
	return data_instance


if __name__ == '__main__':
	dh = data_handler()
	os.popen('cp config.txt '+dh.output_folder+'/config.txt')
	ttotal = time()
	
	print('Loading dataset...')
	hypotheses = get_data_instance(dh)
	
	print('Generating learners...')
	learners = get_learners(dh, hypotheses)
	
	print('Generating teachers...')
	teachers = get_teachers(dh)	
	print('Starting iterations...')
	
	output = open(dh.output_path, mode='w')
	header = 'ITER,TEACHER,LEARNER,DATASET,DATASET_SIZE,TEACHER SEED,'
	header += 'LEARNER SEED,HYP_GENERATOR SEED, MAX_EXEMPLES_ITER,EXAMPLES_ITERATION,'
	header += 'TEACHING SET SIZE,TEACHING SET ACCURACY,ACCURACY,FULL DATA ACCURACY\n'
	output.write(header)
	
	i = 1
	qtd = len(teachers)*len(learners)
	output_log = ''
	for teacher in teachers:
		for learner in learners:
			print('iter: ', i,'/',qtd, teacher.name, learner.name)
			i+=1
			S, acc_list, log = teacher.teaching(learner)
			#output.write(log)
			output_log+=log
	ttotal = time() - ttotal
	output.write(output_log)	
	output.close()
	with open(dh.output_folder+'/runtime.txt', 'w') as f:
		f.write('\nTOTAL TIME(s): '+str(ttotal))
	