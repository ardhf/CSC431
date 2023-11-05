#include <iostream>
using namespace std;

int main() {
    // Initalizes the number of processes and their resources
    int numOfProcesses = 5;
    int numOfResources = 3;

    //  2D allocation matrix for the processes and their needs of A, B and C respectively
    int allocationMatrix[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    // 2D max matrix for the max of A, B and C for each process
    int maxMatrix[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};

    // Creates a 2D need Matrix
    int needMatrix[5][3];

    // The number of available A, B and C resouces
    int availableMatrix[3] = {3, 3, 2};

    int finishMatrix[5];  // Creates an array with 5 elements
    int index = 0;

    // Sets all of the elements in the array to 0
    for (int i = 0; i < numOfProcesses; i++) {
        finishMatrix[i] = 0;
    }

    // Sets the need matrix for each element to the max - the allocation
    // One of the first steps to the bankers algorithm
    for (int i = 0; i < numOfProcesses; i++) {
        for (int j = 0; j < numOfResources; j++)
            needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
    }

    // Loops through all of the processes
    for (int x = 0; x < 5; x++) {
        for (int j = 0; j < numOfProcesses; j++) {
            // Will originally be true and go through the entire array
            if (finishMatrix[j] == 0) {
                int dlCount = 0;
                for (int i = 0; i < numOfResources; i++) {
                    // Checks to see if the current element of the 2D need matrix
                    // is bigger than the available matrix and if so, set the variable to 1
                    if (needMatrix[j][i] > availableMatrix[i]) {
                        dlCount = 1;
                        break;
                    }
                }

                // If the previous loop worked
                if (dlCount == 0) {
                    // Loops through for each number of resources and sets the available
                    // to the allocation of the current element
                    for (int y = 0; y < numOfResources; y++) {
                        availableMatrix[y] += allocationMatrix[j][y];
                    }
                    // Sets the current element to a 1 to show no deadlock
                    finishMatrix[j] = 1;
                }
            }
        }
    }

    // Variable to check if there is a deadlock
    bool isDeadlock = false;

    // Checks if there is a deadlock, and if there is it will display to the user
    for (int i = 0; i < numOfProcesses; i++) {
        if (finishMatrix[i] == 0) {
            isDeadlock = true;
            cout << "There is a deadlock";
            break;  // Break out of loop bceause there is no point to continue
        }
    }

    // Checks if there is no deadlock and then will tell the user
    if (isDeadlock == false) {
        cout << "There is no deadlock" << endl;
    }

    return 0;
}
