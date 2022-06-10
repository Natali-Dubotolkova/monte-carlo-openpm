#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <ctime>

using namespace std;

const unsigned int DIM1 = 3; //три значения: х,у и r
const unsigned int DIM2 = 3; //кол-во кругов

int input_array[DIM1][DIM2] = {
    { -6, 10, 3 },
    { 5, 10, 8 },
    { -8, 0, 6 }
};

struct Center
{
    int x;
    int y;
};

struct Circle{
    Center center;
    int rad;
};
 
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Circle * array_of_circles = new Circle[DIM2];
    
    for (int i = 0; i < DIM1; i++) {
        array_of_circles[i].center.x = input_array[i][0];
        array_of_circles[i].center.y = input_array[i][1];
        array_of_circles[i].rad = input_array[i][2];
    }

    //находим уравнения прямых, ограничивающих круги
	int max_x, min_x, max_y, min_y;

    max_x = array_of_circles[0].center.x + array_of_circles[0].rad;
	min_x = array_of_circles[0].center.x - array_of_circles[0].rad;
	max_y = array_of_circles[0].center.y + array_of_circles[0].rad;
	min_y = array_of_circles[0].center.y - array_of_circles[0].rad;

    for (int i = 1; i < (DIM2); i++)
	{
		int temp = array_of_circles[i].center.x + array_of_circles[i].rad;
		if (max_x < temp)
			max_x = temp;
		temp = array_of_circles[i].center.x - array_of_circles[i].rad;
		if (min_x > temp)
			min_x = temp;
		temp = array_of_circles[i].center.y + array_of_circles[i].rad;
		if (max_y < temp)
			max_y = temp;
		temp = array_of_circles[i].center.y - array_of_circles[i].rad;
		if (min_y > temp)
			min_y = temp;
	}

	// cout << " " << max_x << " " <<  min_x << " " << max_y << " " <<  min_y << endl;

	double height_rectangle = sqrt(pow((min_x-max_x),2)+pow((max_y-max_y),2));
	double width_rectangle = sqrt(pow((max_x-max_x),2)+pow((min_y-max_y),2));
	double s_rectangle = height_rectangle * width_rectangle;

    srand(time(0)); // генерация случайных чисел

    int positives = 1000000;

    int sum = 0;

	for (int i = 0; i < positives; i++)
	{
		double x0 = rand();
		double y0 = rand();
		x0 = x0/RAND_MAX*(max_x-min_x) + min_x;
		y0 = y0/RAND_MAX*(max_y-min_y) + min_y;

		// cout << x0 << " " << y0 << " " << endl;
		bool t = false;
		for (int j = 0; j < DIM2; j++)
		{
			double len = pow((x0-array_of_circles[j].center.x),2) + pow((y0-array_of_circles[j].center.y),2);
			len = sqrt(len);
			// cout << "len: " << len << " radius: " << array_of_circles[j].rad << endl;
			if (len <= array_of_circles[j].rad)
				t = true;
		}
		if (t) {
			sum++;
		}
		
		// cout << "             " << sum << endl;
	}

	// cout << sum << endl;
    double s = s_rectangle*((double)(sum)/(double)(positives));
    cout << "Result: " << s << endl;
	double check_sum;
	for (int j = 0; j < DIM2; j++){
		check_sum = check_sum + 3.1415926 * pow(array_of_circles[j].rad, 2);
	}
	cout << "Check sum: " << check_sum << endl;

    cout << "runtime = " << clock()/1000.0 << endl; // время работы программы  
    return 0;
}
