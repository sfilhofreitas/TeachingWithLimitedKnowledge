# File config.txt:
	* Output path: Output directory to be created. (Only the last folder in the directory will be created)
	* Teachers: Teachers that will be used in the test with its respective parameters
	* Learners: Learners that will be used with its parameters
	* Hyptheses generator: Hyptheses Generator that will be used with its parameters
	* Number of examples: Number of examples of the synthetic dataset
	* Number of hypotheses: Learner hypotheses class size
	* Number of teacher seeds: Number of times the test will be performed modifying only the teacher's seed
	* Number of learner seeds: Number of times the test will be performed modifying only the learner's seed


# Teachers:
	
## (${\cal A}_ {agno}$):
	In C code, the teacher (${\cal A}_{agno}$) is called WeightsTheoreticalFounded.

	Usage syntax: WeightsTheoreticalFounded


# Learners:

## OptimalNoPerfect (Random Learner)
	The learner randomly (uniformly) chooses a hypothesis that is not covered by the set of examples received. The perfect hypothesis is only returned when all others are covered.

	* Usage syntax: OptimalNoPerfect


# Hyptheses Generator
	* List values are separated by '_' and without spaces as: v1_v2 _..._ v_n.

## SimpleRandomHypotheses
	A set of hypotheses (without repetitions) is generated randomly following the specified parameters.

	* Usage syntax: SimpleRandomHypotheses p1 p2 p3 p4 p5
		* p1: Accuracy list of the hyphoteses
		* p2: Fraction of examples that are more hard
		* p3: Fraction of hard examples that appear in each hypothesis. If p is 0.3, 30% of the examples that each hypothesis misses are of the set of set of hard examples and 70% of the other examples
		* p4: True if you have the perfect hypothesis, False otherwise. Currently this value must always be True
		# p5: Number of hypothesis sets generated for the previously defined parameters



# Run:
	The code was developed on Ubuntu 18.04.3 LTS using Qt Creator IDE (QMake version 3.1 Using Qt version 5.9.7) and can be loaded in the same tool using the .pro file in the src folder.

	* Run ./Framework (src folder)


# Instance of config.txt:
	OUTPUT PATH: ../../Tests/C/output_name
	TEACHERS: WeightsTheoreticalFounded
	LEARNERS: OptimalNoPerfect
	HYPOTHESES GENERATOR: SimpleRandomHypotheses 0.9_0.95_0.99 0 0 True 5
	NUMBER OF EXAMPLES: 12500
	NUMBER OF HYPOTHESES: 30000
	TEACHER REPETITIONS: 10
	LEARNER REPETITIONS: 10


# Output:
	* Folder containing three files:
		* CSV file with experiment logs (for each iteration);
		* Copy of the config.txt file that generated the experiment;
		* Experiment runtime.

	* Main columns of the log file:
		* TEACHING SET ACCURACY: Accuracy in the current teaching set.
		* ACCURACY: Total accuracy in the current iteration.
		* TEACHING SET SIZE: Teaching set size in the current iteration.
		* HEURISTIC SOLUTION: Number of examples after the redundant example removal procedure. Only applies when ACCURACY equal to 1.0.


# Run script for analyze the heuristic performance of removing redundant examples
	* Usage syntax: python results_reduction.py p1
		* p1: Path to the experiment folders.

	* Example: python results_reduction.py ../../Tests/C/

	* For each experiment carried out in the specified directory, a reduction_performance.txt file is added in the experiment folder.

	* The file reduction_performance.txt contains three values:
		* AVG TEACHING SET SIZE: The average of the sizes of the teaching sets;
		* AVG HEURISTIC SOLUTION SIZE: The average of the sizes of the teaching sets after the procedure of removing the redundant examples;
		* AVG REDUCTION PERFORMANCE: Average teaching set reduction (in proportion from 0.0 to 1.0).

		