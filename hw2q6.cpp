#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <deque>

using namespace std;

struct course{
  string name;
  double work;
  double learn;
};

double backtrack(deque<double>, deque<double>, double, double, double, double, double, int);

int main(int argc, char ** argv){
    ifstream file(argv[1]);
    int numLines = 0;
    string line;
    string word;
    double tempWork = 0;
    double tempLearn = 0;
    course *courses;
    double totalWork = 0;

    file >> numLines;
    file >> totalWork;
    courses = new course[numLines];


    string lines[numLines];
    getline(file, line);
    // create an array of each individual line to look through
    for (int i = 0; i < numLines; i++){
      getline(file, line); 
      lines[i] = line;
    }

    // fill the array of courses with information
    for (int j = 0; j < numLines; j++){
      getline(file, line);
      stringstream stream(lines[j]);
      stream >> word;
      courses[j].name = word; 
      stream >> tempWork;
      courses[j].work = tempWork;
      stream >> tempLearn;
      courses[j].learn = tempLearn;
    }

    deque<double> allWork;
    deque<double> allLearn;

    for (int i = 0; i < numLines; i++){
      allWork.push_back(courses[i].work);
      allLearn.push_back(courses[i].learn);
    }

    double result = backtrack(allWork, allLearn, numLines, totalWork, 0, allWork[0], 0, 1);

    delete [] courses;

    return 0;
}

double backtrack(deque<double> allWork, deque<double> allLearn, double numCourses, double totalWork, double tempMax, double tempWork, double tempLearn, int iterator){

    // if we have exceeded the current max, make that value the new max.
    if (tempLearn >= tempMax){
      tempMax = tempLearn;
    }

    // base case: if size of allWork is 1, return tempMax
    if (allWork.size() == 1){
cout << "Maximum Learning: " << tempMax << endl;
      return tempMax;
    }

    // 	if the current course's work + the next course's
    //  work is less than totalWork
    //		tempWork += current course's work
    //          tempLearn += current course's learn
    //            try current course with next course
     if ((tempWork + allWork[iterator] < totalWork) && iterator < numCourses-1){
       tempWork += allWork[iterator];
       tempLearn += allLearn[iterator];
       backtrack(allWork, allLearn, numCourses, totalWork, tempMax, tempWork, tempLearn, iterator+1);
    //    else
    //    	remove that course
    //            try what's left
     } else if ((tempWork + allWork[iterator] > totalWork) && iterator < numCourses-1){
       backtrack(allWork, allLearn, numCourses, totalWork, tempMax, tempWork, tempLearn, iterator+2);
     } else {
       allWork.pop_front();
       allLearn.pop_front();
       backtrack(allWork, allLearn, numCourses, totalWork, tempMax, allWork[0], allLearn[0], 1);
      }
}











