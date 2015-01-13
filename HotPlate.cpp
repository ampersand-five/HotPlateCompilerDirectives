#include <vector>;

using std::vector;

double when();

int main()
{
	const float PLATE_SIZE = 1024;
	const float NEUTRAL_TEMP = 50;
	//vectors one initialized to having all 50's
	vector<vector<float>> previous_plate (1024, vector<float>(PLATE_SIZE, NEUTRAL_TEMP));
	vector<vector<float>> current_plate;


	//initialize vector to have correct starting temperatures

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


	//Start iterating

	//Start time


}

double when()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return((double)tp.tv_sec + (double)tp.tv_usec*1e-6);
}