#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>

using std::vector;

int main()
{
	std::ofstream file_out("hotPlateFinished.txt", std::ofstream::out);
	const float PLATE_SIZE = 1024;
	const float NEUTRAL_TEMP = 50;
	//vectors one initialized to having all 50's
	//vector<vector<float>> previous_plate (PLATE_SIZE, vector<float>(PLATE_SIZE, NEUTRAL_TEMP));
	vector<vector<float>> previous_plate;
	vector<vector<float>> current_plate;


	//initialize vector to have correct starting temperatures
	//Make them all have 50
	for (int i = 0; i < PLATE_SIZE; ++i)
	{
		vector<float> tmp;
		previous_plate.push_back(tmp);
		for (int j = 0; j < PLATE_SIZE; ++j)
		{
			previous_plate[i].push_back(50);
		}
	}
		//bottom row
	for (int i = 0; i < PLATE_SIZE; ++i)
	{
		previous_plate[PLATE_SIZE-1][i] = 100;
	}
		//mid section
	for (int i = 0; i < 331; ++i)
	{
		previous_plate[400][i] = 100;
	}
		//single point
	previous_plate[200][500] = 100;
	current_plate = previous_plate;


	//Start iterating
		//Start time
	auto start_time = std::chrono::high_resolution_clock::now();

		//Run
	int converged = 0;
	int cycles = 0;
	do
	{
		converged = 0;
		//Determine new plate
		for (int i = 1; i < PLATE_SIZE; ++i)
		{
			for (int j = 1; j < PLATE_SIZE; ++j)
			{
				//new temperature
				current_plate[i][j] = (previous_plate[i + 1][j] + previous_plate[i - 1][j] +
					previous_plate[i][j + 1] + previous_plate[i][j - 1] + 4 * previous_plate[i][j]) / 8;
				//steady state check
				if (abs(previous_plate[i][j] - (previous_plate[i + 1][j] + previous_plate[i-1][j] + 
												previous_plate[i][j+1] + previous_plate[i][j-1]) / 4) > 0.1)
				{
					++converged;
				}
			}
		}

		//Swap
		previous_plate = current_plate;

	} while (converged > 0);





	//End time
	auto end_time = std::chrono::high_resolution_clock::now();

	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
	file_out << "Total running time: " << time_span.count() << " seconds\n";
	file_out << "Iterations: " << cycles;
}
