#include <iostream>
#include <string>

using namespace std;

/*
    Steps to find the average wait time

    1) Find the process with the shortest burst time where the arrival time is less than or equal to the current time
    2) Set completion time to itself + the burst time of the new process
    3) Repeat steps 1 and 2 until all processes are completed

*/

// Initalizes the processes with their arrival times and burst times
int processNo[5] = {1, 2, 3, 4, 5};
int arrTime[5] = {0, 1, 2, 3, 4};
int burstTime[5] = {2, 1, 8, 4, 5};

// An array to hold the values of each processes' completion time if wanted at a a later time
int completionTime[5];

// Returns the index of the shortest burstTime at a given currentTime
int findShortestJobIndex(int currTime) {
    // Local variables used to keep track of the shortest job and its corresponding index
    int shortestJobIndex = 0;
    int shortestJobTime = 20;

    // Loop that will run through all of the processes in the array
    for (int i = 0; i < 5; i++) {
        // Will check to see if there is a shorter job at a given time
        if (arrTime[i] <= currTime) {
            // Makes sure that process hasnt already been completed
            if (processNo[i] != -1) {
                // Will make sure the burst time at the given index is the smallest one encountered yet
                if (burstTime[i] < shortestJobTime) {
                    // Will set the variables to keep track of what the shortest burst time is and its index
                    shortestJobTime = burstTime[i];
                    shortestJobIndex = i;
                }
            }
        }
    }

    // Returns the index of the shortest job at a given time
    return shortestJobIndex;
}

double shortestJobFirst() {
    // Local variables used to keep track of the current time, index of the shortest job, and calculation of the average wait time
    int currentTime = 0;
    int shortestJobIndex = 0;
    double avgWaitTime = 0.0;

    // Loops through all of the processes in the list
    for (int i = 0; i < 5; i++) {
        // stores the shortest job index returned from the method
        shortestJobIndex = findShortestJobIndex(currentTime);
        // Adds the burst time of the new shortest job to the current time
        currentTime += burstTime[shortestJobIndex];
        // Sets the process number of the evaluated job to -1 so that it doesn't get processed again
        processNo[shortestJobIndex] = -1;
        // stores the completion time for the job in its array postion based on the process number
        completionTime[shortestJobIndex] = currentTime;
    }

    // Calculates the average wait time for the processes
    for (int i = 0; i < 5; i++) {
        avgWaitTime += completionTime[i] - (arrTime[i] + burstTime[i]);
    }

    // Returns the average wait time to the user
    return avgWaitTime / 5;
}

int main() {
    // Displays the results to the user
    cout << endl << "The average wait time is: " << shortestJobFirst() << " ms" << endl << endl;

    return 0;
}