#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>

using namespace std;

int sumFor = 0;
int sumRecursive = 0;
int sum(int[], int);

int main(int argc, char ** argv){
    const int ITERATE = 1000;
    clock_t startFor, startRecursive, finishFor, finishRecursive;
    double durFor, durRecursive;
    int numNums = 0;
    string line;
    int *nums;

    ifstream file(argv[1]);
    file >> numNums;
    nums = new int[numNums];
    getline(file, line);

    for (int i = 0; i < numNums; i++){
      getline(file, line);
      nums[i] = atoi(line.c_str());
    }

   //startFor = clock();
    for (int k = 0; k < ITERATE; k++){
      for (int j = 0; j < numNums; j++){
        int temp = nums[j];
        sumFor += temp;
      }
    }
cout << "HERE " << startFor << endl;
   // finishFor = clock();

    durFor = (double)(finishFor - startFor);
    durFor /= (CLOCKS_PER_SEC * ITERATE);

   // startRecursive = clock();
    for (int a = 0; a < ITERATE; a++){
      sumRecursive = sum(nums, numNums-1);
    }
   // finishRecursive = clock();

    durRecursive = (double)(finishRecursive - startRecursive);
    durRecursive /= (CLOCKS_PER_SEC * ITERATE);

    cout << "Sum via for loop: " << sumFor << endl;
    cout << "Runtime of for loop: " << scientific << durFor << endl;
    cout << "Sum via recursion: " << sumRecursive << endl;
    cout << "Runtime of recursive function: " << scientific << durRecursive << endl;

    delete [] nums;
    return 0;
}

int sum(int nums[], int x){
    if (x == 0){
      return sumRecursive;
    } else {
      sumRecursive = nums[x] + sum(nums, x-1);
      return sumRecursive;
    }
}
