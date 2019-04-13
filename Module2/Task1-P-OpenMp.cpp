#include <iostream>
#include <array>
#include <sys/time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <omp.h>

using namespace std;

const bool PRINT_MATRIX = false;

vector<int> populateMatrix(const int rows, const int columns) {
    vector<int> pInt;

    for (int r = 0; r < rows; r++) {
        if (PRINT_MATRIX)
            printf("{");

        for (int c = 0; c < columns; c++) {
            int val = rand() % 99;

            pInt.push_back(val);

            if (PRINT_MATRIX)
                printf("%d%s", val, c < columns - 1 ? "," : "");
        }

        if (PRINT_MATRIX)
            printf("}\n");
    }
    return pInt;


}



void saveToFile(string file_name,vector<int> C, int A_rows, int B_columns) {
    printf("SAVING : %d x %d\n",A_rows,B_columns);
    ofstream myfile;
    myfile.open(file_name);


    for (int y = 0; y < A_rows; y++) {
        myfile << ("{");
        for (int x = 0; x < B_columns; x++) {
            //int index = (y*A_columns);
            std::ostringstream stringStream;
            stringStream << C[((y * B_columns) + x)];
            if (x < (B_columns - 1))
                stringStream << ",";
            myfile << stringStream.str();
        }

        myfile << "}";
        if (y < (A_rows - 1))
            myfile << "\n";

    }

    myfile.close();
}


int main() {

    double time_elapsed = 0.0;

    const int A_rows = 500;
    const int A_columns = A_rows;
    const int B_rows = A_columns;
    const int B_columns = B_rows;

    vector<int> A;
    vector<int> B;

    A = populateMatrix(A_rows, A_columns);
    printf("A has been initialized.\n");
    B = populateMatrix(B_rows, B_columns);
    printf("B has been initialized.\n");

    //measuring time using system time
    //TIME STATRT
    struct timeval timecheck;
    gettimeofday(&timecheck, NULL);
    double timeofday_start = ((long) timecheck.tv_sec * 1000) + ((long) timecheck.tv_usec / 1000);
    // y for y axis
    // x for x axis
    // e for element

    //multiply A and B

    int THREAD_COUNT = 8;   //5 main threads and 1 thread to process all remaining

    vector<int> results[THREAD_COUNT];

#pragma omp parallel num_threads(THREAD_COUNT) shared(results)
    {
        int i = omp_get_thread_num();

#pragma omp for
        for (int y = 0; y <= A_rows; y++) {
            for (int x = 0; x < A_columns; x++) {
                int val = 0;
                for (int e = 0; e < A_columns; e++) {
                    int Aindex = (y * A_columns) + e;
                    int Bindex = (e * B_columns) + x;
                    int j = A[Aindex];//A[y][e];
                    int k = B[Bindex];

                    val += j * k;
                }
                results[i].push_back(val);
            }
        }
    }

    vector<int> C;
    //JOINING PROCESS OF RESULT
    for(int i=0;i<THREAD_COUNT;i++){
        vector<int> vect = results[i];
        if(vect.size()>0){
            C.insert(C.end(),vect.begin(),vect.end());
//            printf("ADDED RESULT FROM THREAD %d \n",i);
        }
    }


    //TIME END
    gettimeofday(&timecheck, NULL);
    double timeofday_end = ((long) timecheck.tv_sec * 1000) + ((long) timecheck.tv_usec / 1000);
    time_elapsed = (timeofday_end - timeofday_start) / 1000;
    printf("Time elapsed: %f second(s)\n", time_elapsed);
    printf("VECTOR SIZE : %d\n",C.size());
    saveToFile("results.txt", C, A_rows, B_columns);

    return 0;
}



