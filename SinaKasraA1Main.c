#include "givenA1.h"

int main() {
    struct Animal dataZoo[NUM_SAMPLES];
    struct Animal testData[NUM_TEST_DATA];
    int choice;
    int k;
    char fName[30] = "a1Data.txt";
    char testFName[30] = "testData.csv";
    int newSample[NUM_FEATURES] = { 1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1 }; //can be changed
    int kNearestNeighbors[NUM_SAMPLES];
    int whichDistanceFunction;
    float mean;
    int mode, whichFeature;
    int x, y;

    while (1) {

        printf("choose command:\n");// the menu
        printf("1- Load Data\n");
        printf("2- Generate statistics for a feature\n");
        printf("3- Display class distribution\n");
        printf("4- Calculate euclidean distance\n"); 
        printf("5- Calculate hamming distance\n"); 
        printf("6- Calculate jaccard similarity\n"); 
        printf("7- Find k-nearest neighbors\n"); 
        printf("8- Predict class\n"); //Requires Task 7 to be ran first
        printf("9- Find accuracy\n"); //Requires loaded testData
        printf("Enter choice (1 to 9): ");

        scanf("%d", &choice);//inputs the choice

        readFromFile(fName, dataZoo);//reads the file anyway

        switch (choice) {

            case 1: //task 1
                if (readFromFile(fName, dataZoo) == 0) { //attempt to load the file
                    printf("data loaded.\n\n");
                } 
                else {
                    printf("Failed to load\n\n");
                }
                break;

            case 2: //task 2

                printf("Enter feature number: ");
                scanf("%d", &whichFeature);//input wanted feature

                if(generateStatisticsFeatureX(dataZoo, whichFeature, &mean, &mode) != -1){//calls the task
                    printf("Mean: %.2f, Mode: %d\n\n", mean, mode);
                }
                else{
                    printf("Invalid feature.\n\n");
                }
                break;
            
            
            case 3: //task 3
                classDistribution(dataZoo); //calls the task
                printf("\n");
                break;

            case 4: //task 4
                printf("Enter the index of two animals (0 - 99): ");
                scanf("%d %d", &x, &y);

                printf("%.2f\n\n", euclideanDistance(dataZoo[x].features, dataZoo[y].features)); //calls the task
                break;

            case 5: //task 5
                printf("Enter the index of two animals (0 - 99): ");
                scanf("%d %d", &x, &y);

                printf("%d\n\n", hammingDistance (dataZoo[x].features, dataZoo[y].features)); //calls the task
                break;

            case 6: //task 6
                printf("Enter the index of two animals (0 - 99): ");
                scanf("%d %d", &x, &y);

                printf("%.2f\n\n", jaccardSimilarity (dataZoo[x].features, dataZoo[y].features)); //calls the task
                break;

            case 7: //task 7

                printf("Enter distance function (1 2 or 3): "); // input the distance and the k wanted
                scanf("%d", &whichDistanceFunction);
                printf("Enter k: ");
                scanf("%d", &k);

                // newSample is hard coded in the beginning
                findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors); //calls the task
                for(int i = 0; i < k; i++){
                    printf("%d ", kNearestNeighbors[i]);
                }
                printf("\n\n");

                break;
            
            case 8: //task 8

                //task 7 must be ran first
                printf("%d\n\n", predictClass ( dataZoo , kNearestNeighbors, newSample , k)); //calls the task
                break; 

            case 9: //task 9

                if (readFromFile(testFName, testData) == 0) {
                    float accuracy = findAccuracy(dataZoo, testData, k); //calls the task
                    printf("Accuracy: %.2f%%\n\n", accuracy);

                }
                else {
                    printf("Failed to load data.\n\n");
                }
                break;

            default: 

                printf("Invalid choice.\n\n");
                return 0;
        }
    }

    return 0;
}
