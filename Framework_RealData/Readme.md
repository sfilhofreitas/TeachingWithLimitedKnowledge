# File config.txt:
	* Output path: Output directory to be created. (Only the last folder in the directory will be created)
	* Teachers: Teachers that will be used in the test with its respective parameters
	* Learners: Learners that will be used
	* Dataset path: Dataset directory to be used and its respective parameters 
	* Number of teacher seeds: Number of times the test will be performed modifying only the teacher's seed
	* Number of learner seeds: Number of times the test will be performed modifying only the learner's seed

# Teachers:
	* Each parameter must be separated by space.
	* Each teacher must be separated by a comma.

## (${\cal A}_ {agno}$):
	In Python code, the teacher (${\cal A}_{agno}$) is called WeightsTheoreticalFounded.

	Usage syntax: WeightsTheoreticalFounded p1 p2
		* p1: fraction of examples chosen uniformly random from the dataset to generate the first hypothesis (In our experiments the value 0.01 was used).
		* p2: maximum fraction of examples to be selected from the dataset (In our experiments the value 1 was used).


## NIT
	In Python code, the teacher NIT is called PacTeacher.

	* Usage syntax: PacTeacher p1 p2 p3
		* p1: fraction of examples that are sent by iteration (In our experiments the value 0.005 was used).
		* p2: fraction of examples chosen uniformly random from the dataset to generate the first hypothesis (In our experiments the value 0.01 was used).
		* p3: maximum fraction of examples to be selected from the dataset (In our experiments the value 1 was used).

# Learners:
	* RandomForest and LGBM (Light Gradient Boosting Machine), both without parameters.
	* Each learner must be separated by a comma.

# Dataset Path
	* Usage syntax: dataset_path/dataset.csv p1 p2
		* p1: True if all attributes are numeric and False if all attributes are categorical. Currently, are not supported datasets whose attributes are divided into numeric and categorical.
		* p2: dataset name in the log file.

# Run:
	* Run the file main.py with python3

# Install basic requirements:
	* pip3 install -r requirements.txt

# Install all requirements (if the above step is not enough):
	* pip3 install -r requirements_all.txt


# Output:
	* Folder containing three files:
		* CSV file with experiment logs (for each iteration);
		* Copy of the config.txt file that generated the experiment;
		* Experiment runtime.

	* Main columns of the log file:
		* FULL DATA ACCURACY: Accuracy using whole dataset.
		* ACCURACY: Total accuracy in the current iteration.
		* TEACHING SET ACCURACY: Accuracy in the current teaching set.		
		* TEACHING SET SIZE: Teaching set size in the current iteration.
		* DATASET_SIZE: Number of dataset examples.
		* MAX_EXEMPLES_ITER: Maximum number of examples that can be drawn in the current iteration.
		* EXAMPLES_ITERATION: Number of examples drawn in the current iteration.


# Instance of config.txt:
	OUTPUT PATH: ../Tests/Python/output_name
	TEACHERS: WeightsTheoreticalFounded 0.01 1, PacTeacher 0.005 0.01 1
	LEARNERS: RandomForest, LGBM
	DATASET PATH: ./datasets/car.csv False car
	TEACHER REPETITIONS: 30
	LEARNER REPETITIONS: 1


# Run script to summarize the log files to compare algorithm (${\cal A}_ {agno}$) with NIT

## Output script:
	* Columns of the summary file (For each variation of Teacher, Learner and Dataset):
		* TEACHER: Teacher used in the experiment.
		* LEARNER: Learner used in the experiment.
		* DATASET: Dataset used in the experiment.
		* DATASET_SIZE: Number of dataset examples.
		* ACC_FULL_DATASET: Accuracy using whole dataset.
		* SCENARIOS: Number of experiment scenarios.
		* REACHED_X%: In how many scenarios were reached X% of ACC_FULL_DATASET.
		* AVG_EXAMPLES_X%: Average number of examples sent to reach (for the first time) X% of ACC_FULL_DATASET in the REACHED_X% scenarios.
		* MIN_EXAMPLES_X%: Minimum number of examples sent to reach (for the first time) X% of ACC_FULL_DATASET in the REACHED_X% scenarios.
		* MAX_EXAMPLES_X%: Maximum number of examples sent to reach (for the first time) X% of ACC_FULL_DATASET in the REACHED_X% scenarios.
		* STD_EXAMPLES_X%: Standard deviation of the distribution of the number of examples sent (for the first time) to reach X% of ACC_FULL_DATASET in the REACHED_X% scenarios.


	* Usage syntax: python summary.py p1 p2
		* p1: Path to the experiment folders.
		* p2: Path to output file.

	* Example: python summary.py ../Tests/Python ../Tests/Python/summay.csv


