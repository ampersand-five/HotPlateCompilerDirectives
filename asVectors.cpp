#include <vector>
#include <array>
//#include <iostream>
#include <chrono>
#include <fstream>
#include <math.h>

#define PLATE_SIZE 4096
#define NEUTRAL_TEMP 50

using std::vector;
//using std::array;

int main()
{

	std::string file = "hotPlateFinished" + std::to_string((int)PLATE_SIZE) + ".txt";
	std::ofstream file_out(file, std::ofstream::out);

	//std::ofstream png_out("hotPlateFinished.png", std::ofstream::out);
	//png_out << "137 80 78 71 13 10 26 10 ";

	//vectors one initialized to having all 50's
	//vector<vector<double>> previous_plate (PLATE_SIZE, vector<double>(PLATE_SIZE, NEUTRAL_TEMP));
	vector<vector<double>> previous_plate;
	vector<vector<double>> current_plate;

	//auto initalize_start_time = std::chrono::high_resolution_clock::now();
	//initialize vector to have correct starting temperatures
	//Make them all have 50
	for (int i = 0; i < PLATE_SIZE; ++i)
	{
		vector<double> tmp;
		previous_plate.push_back(tmp);
		for (int j = 0; j < PLATE_SIZE; ++j)
		{
			previous_plate[i].push_back(NEUTRAL_TEMP);
		}
	}
		//bottom row get's 100 degrees
	for (int i = 0; i < PLATE_SIZE; ++i)
	{
		previous_plate[PLATE_SIZE-1][i] = 100;
	}
		//mid section (400,0-330) gets 100 degrees
	for (int i = 0; i < 331; ++i)
	{
		previous_plate[400][i] = 100;
	}
		//single point gets 100 degrees
	previous_plate[200][500] = 100;
		//Top & side bars get 0 degrees
	for (int i = 0; i < PLATE_SIZE; ++i)
	{
		previous_plate[0][i] = 0; //top bar
		previous_plate[i][0] = 0; //left bar
		previous_plate[i][PLATE_SIZE-1] = 0; //right bar
	}


	//Set current_plate to also have the same setup
	current_plate = previous_plate;

	//auto initalize_end_time = std::chrono::high_resolution_clock::now();

	//auto init_time = std::chrono::duration_cast<std::chrono::duration<double>>(initalize_end_time - initalize_start_time);
	//file_out << "Initialize time: " << init_time.count() << " seconds\n";

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
		for (int i = 1; i < PLATE_SIZE - 1; ++i)
		{
			for (int j = 1; j < PLATE_SIZE - 1; ++j)
			{
				//new temperature
					//Skip fixed points
				if ((i == 400 && j < 331) || (i == 200 && j == 500))
				{
					//file_out << previous_plate[i][j] << " ";
					//png_out << (int)previous_plate[i][j] << " ";
				}
				else
				{
					//Debug purposes
					//double new_val = (previous_plate[i + 1][j] + previous_plate[i - 1][j] +
					//	previous_plate[i][j + 1] + previous_plate[i][j - 1] + 4 * previous_plate[i][j]) / 8;
					//current_plate[i][j] = new_val;

					//file_out << new_val << " ";
					//png_out << (int)new_val << " ";


					current_plate[i][j] = (previous_plate[i + 1][j] + previous_plate[i - 1][j] +
						previous_plate[i][j + 1] + previous_plate[i][j - 1] + 4 * previous_plate[i][j]) / 8;
					//steady state check
					if (fabs(previous_plate[i][j] - (previous_plate[i + 1][j] + previous_plate[i - 1][j] +
						previous_plate[i][j + 1] + previous_plate[i][j - 1]) / 4) > 0.1)
					{
						++converged;
					}
				}

			}
			//file_out << "\n"; //debug
		}

		//Swap
		previous_plate = current_plate;
		++cycles;
		//file_out << "\n"; //debug
		//file_out << "\n Cycle: " << cycles << " Converged: " << converged << "\n";

	} while (converged > 0);


	//End time
	auto end_time = std::chrono::high_resolution_clock::now();

	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
	file_out << "Total running time: " << time_span.count() << " seconds\n";
	file_out << "Iterations: " << cycles;
}
