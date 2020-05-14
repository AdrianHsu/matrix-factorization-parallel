#include <cstring>
#include "readInput.h"

#define ROOT 0
#define FIRST_ELEMENT(id, p, n) ((id)*(n)/(p))
#define LAST_ELEMENT(id, p, n) (FIRST_ELEMENT((id)+1,p,n)-1)
#define BLOCK_SIZE(id, p, n) (LAST_ELEMENT(id,p,n)-FIRST_ELEMENT(id,p,n)+1)

void readInput(std::string &inputFileName, std::vector<std::vector<double>> &A,
               std::vector<int> &nonZeroUserIndexes, std::vector<int> &nonZeroItemIndexes,
               std::vector<double> &nonZeroElements,
               int &numberOfIterations, int &numberOfFeatures, double &convergenceCoefficient, int &numberOfUsers,
               int &numberOfItems, int &numberOfNonZeroElements, int &processId, int &numberOfProcesses) {


    std::vector<std::string> fileCopy;
    std::string line;
    int numberOfLines;

    // TODO: GET COPY AND NUMBER OF LINES
    // if (processId == ROOT) {
        std::ifstream countFileLines(inputFileName);
        for (numberOfLines = 0; std::getline(countFileLines, line); numberOfLines++) {
            fileCopy.push_back(line);
        };
        countFileLines.close();
    // }

    //TODO
    // MPI_Bcast(&numberOfLines, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
//    printf("process %d has numberOfLines %d\n", processId, numberOfLines);
//    fflush(stdout);

    if (processId == ROOT) {
        for (int k = 0; k < 4; k++) {
            line = fileCopy[k];
            switch (k) {
                case 0: {
                    numberOfIterations = std::stoi(line);
                    break;
                }
                case 1: {
                    convergenceCoefficient = std::stod(line);
                    break;
                }
                case 2: {
                    numberOfFeatures = std::stoi(line);
                    break;
                }
                case 3: {
                    std::istringstream iss(line);

                    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                                     std::istream_iterator<std::string>());
                    numberOfUsers = std::stoi(results[0]);
                    numberOfItems = std::stoi(results[1]);
                    numberOfNonZeroElements = std::stoi(results[2]);
                    break;
                }
            }
        }
    }

    //TODO
    // MPI_Bcast(&numberOfUsers, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
//    printf("process %d has numberOfUsers %d\n", processId, numberOfUsers);
//    fflush(stdout);

    //TODO
    // MPI_Bcast(&numberOfItems, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
//    printf("process %d has numberOfItems %d\n", processId, numberOfItems);
//    fflush(stdout);

    //TODO
    // MPI_Bcast(&numberOfNonZeroElements, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
//    printf("process %d has numberOfNonZeroElements %d\n", processId, numberOfNonZeroElements);
//    fflush(stdout);


    std::vector<std::vector<double>> ResizeA(numberOfUsers, std::vector<double>(numberOfItems, 0));
    A = ResizeA;

    std::vector<int> ResizeIndexes(numberOfNonZeroElements);
    nonZeroUserIndexes = ResizeIndexes;
    nonZeroItemIndexes = ResizeIndexes;

    std::vector<double> ResizeElements(numberOfNonZeroElements);
    nonZeroElements = ResizeElements;

    // TODO
    //    if (processId == ROOT) {
        for (int m = 0; m < numberOfNonZeroElements; m++) {
            line = fileCopy[m + 4];
            std::istringstream iss(line);
            std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                             std::istream_iterator<std::string>());
            int userIndex = std::stoi(results[0]);
            int itemIndex = std::stoi(results[1]);
            double element = std::stod(results[2]);

            nonZeroUserIndexes[m] = userIndex;
            nonZeroItemIndexes[m] = itemIndex;
            nonZeroElements[m] = element;
        }
    //  }

    // TODO
    //    MPI_Bcast(&numberOfNonZeroElements, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

    // TODO: DIVIDE THIS
    //    MPI_Bcast(&nonZeroUserIndexes[0], numberOfNonZeroElements, MPI_INT, ROOT, MPI_COMM_WORLD);
    //    MPI_Bcast(&nonZeroItemIndexes[0], numberOfNonZeroElements, MPI_INT, ROOT, MPI_COMM_WORLD);
    //    MPI_Bcast(&nonZeroElements[0], numberOfNonZeroElements, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);

//    for (int n = 0; n < numberOfNonZeroElements; n++) {
//        std::cout << nonZeroUserIndexes[n] << " StoreNonZeroUserIndexes OK process " << processId << std::endl;
//        fflush(stdout);
//    }

    std::vector<std::vector<double>> StoreA(numberOfUsers, std::vector<double>(numberOfItems, 0));

//    if (processId != ROOT) {
        for (int l = 0; l < numberOfNonZeroElements; l++) {
            StoreA[nonZeroUserIndexes[l]][nonZeroItemIndexes[l]] = nonZeroElements[l];
//            std::cout << nonZeroUserIndexes[l] << ", " << nonZeroItemIndexes[l] << std::endl;
        }
//    }

    A = StoreA;

    for (int i = 0; i < numberOfUsers ; i++) {
        for (int j = 0; j < numberOfItems; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

//    double MatrixA[StoreNumberOfUsers][StoreNumberOfItems];
//    if (processId == ROOT) {
//        for (int i = 0; i < StoreNumberOfUsers; i++) {
//            for (int j = 0; j < StoreNumberOfItems; j++) {
//                MatrixA[i][j] = 0;
//            }
//        }
//    }



//    MPI_Reduce(&StoreA[0][0], &A[0][0], numberOfUsers * numberOfItems, MPI_DOUBLE, MPI_MAX, ROOT,
//               MPI_COMM_WORLD);

//    printf("process %d ended readInput\n", processId);

}
