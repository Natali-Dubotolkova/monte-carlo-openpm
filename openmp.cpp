#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <omp.h>

using namespace std;

#define NUMBER_OF_POINTS 1000000000

const unsigned int DIM1 = 3; //три значения: х,у и r
const unsigned int DIM2 = 3; //кол-во кругов

int point_count = 0; //кол-во точек в кругах

int input_array[DIM1][DIM2] = {
    { -6, 10, 3 },
    { 5, 10, 8 },
    { -8, 0, 6 }
};

int MIN_X, MIN_Y, MAX_X, MAX_Y;

struct Center
{
    int x;
    int y;
};

struct Circle{
    Center center;
    int rad;
};

Circle * array_of_circles = new Circle[DIM2];

void FindRectangleArea(){
   MAX_X = array_of_circles[0].center.x + array_of_circles[0].rad;
	MIN_X = array_of_circles[0].center.x - array_of_circles[0].rad;
	MAX_Y = array_of_circles[0].center.y + array_of_circles[0].rad;
	MIN_Y = array_of_circles[0].center.y - array_of_circles[0].rad;
   // cout << " " << MAX_X << " " <<  MIN_X << " " << MAX_Y << " " <<  MIN_Y << endl;
   for (int i = 1; i < (DIM2); i++)
	{
		int temp = array_of_circles[i].center.x + array_of_circles[i].rad;
		if (MAX_X < temp)
			MAX_X = temp;
		temp = array_of_circles[i].center.x - array_of_circles[i].rad;
		if (MIN_X > temp)
			MIN_X = temp;
		temp = array_of_circles[i].center.y + array_of_circles[i].rad;
		if (MAX_Y < temp)
			MAX_Y = temp;
		temp = array_of_circles[i].center.y - array_of_circles[i].rad;
		if (MIN_Y > temp)
			MIN_Y = temp;
	}
}

float FindRectangleSquare(){
   float height_rectangle = sqrt(pow((MIN_X-MAX_X),2)+pow((MAX_Y-MAX_Y),2));
	float width_rectangle = sqrt(pow((MAX_X-MAX_X),2)+pow((MIN_Y-MAX_Y),2));
	return height_rectangle * width_rectangle;
}

double random_double()
{
    return rand() / ((double)RAND_MAX + 1);
}

int main(int argc, const char * argv[])
{
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);
   
   //инициализация структур 
   for (int i = 0; i < DIM1; i++) {
        array_of_circles[i].center.x = input_array[i][0];
        array_of_circles[i].center.y = input_array[i][1];
        array_of_circles[i].rad = input_array[i][2];
   }

   FindRectangleArea();
   //находим площадь прямоугольника
   double s_rectangle = FindRectangleSquare();

   int i;

   srand(time(0)); // генерация случайных чисел
   #pragma omp parallel num_threads(15)
   {
      int hit_count = 0;
      double x0, y0;
      #pragma omp for private(hit_count) 
      {
         for (int i = 0; i < NUMBER_OF_POINTS; i++) {
                  x0 = random_double()*(MAX_X-MIN_X) + MIN_X;
                  y0 = random_double()*(MAX_Y-MIN_Y) + MIN_Y;
                  // cout << "x0: "<< x0 << "; " << "y0: " << y0 << endl;
                  bool t = false;
                  for (int j = 0; j < DIM2; j++)
                  {
                     double len = pow((x0-array_of_circles[j].center.x),2) + pow((y0-array_of_circles[j].center.y),2);
                     len = sqrt(len);
                     if (len <= array_of_circles[j].rad)
                        t = true;
                  }
                  if (t) {
                     hit_count++;
                  }
               }
      }
      #pragma omp critical
         point_count += hit_count;
   }

   double s = s_rectangle*((double)(point_count)/(double)(NUMBER_OF_POINTS));
   cout << "s_rectangle: " << s_rectangle <<"; " << "point_count: " << point_count << "; " << "NUMBER_OF_POINTS: "<< NUMBER_OF_POINTS << endl; 
   cout << "NUMBER OF POINTS = " << NUMBER_OF_POINTS << endl;
   cout << "Result: " << s << endl;
	double check_point_count;
	for (int j = 0; j < DIM2; j++){
		check_point_count = check_point_count + 3.1415926 * pow(array_of_circles[j].rad, 2);
	}
	cout << "Check result (formula): " << check_point_count << endl;

   cout << "Runtime = " << clock()/1000.0 << endl; // время работы программы  
   return 0;
}
