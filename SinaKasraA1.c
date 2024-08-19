#include "givenA1.h"



/*----------------------------------------------------- Task 1------------------------------------------------------- */
int readFromFile (char fName [30], struct Animal dataZoo[NUM_SAMPLES]){
    FILE *file = fopen(fName, "r");//attempt to open file

    if(file == NULL){//checks to see if it opened successfuly
        return -1;
    }

    int i = 0;

    //read the file
    while(i < NUM_SAMPLES && fscanf(file, "%s", dataZoo[i].animalName) == 1){//read the name

        for(int j = 0; j < NUM_FEATURES; j++){// read the features
            fscanf(file, "%d", &dataZoo[i].features[j]);            
        }
        fscanf(file, "%d", &dataZoo[i].classLabel);// read the class
        i++;
    }

    fclose(file);
    return 0;
}

/* ------------------------------------------------------Task 2 ------------------------------------------------------*/
int generateStatisticsFeatureX (struct Animal dataZoo [NUM_SAMPLES], int whichFeature, float * mean, int * mode){
    if (whichFeature < 1 || whichFeature > 16){// input validation
        return -1;
    }

    float sum = 0;
    int featureArr[10] = {0};

    for (int i = 0; i < NUM_SAMPLES; i++){//counting the features and also their sum
        sum += dataZoo[i].features[whichFeature - 1];

        for (int j = 0; j < 10; j++){
            if(dataZoo[i].features[whichFeature - 1] == j){
                featureArr[j]++;
            }
        }
    }
    *mean = sum / NUM_SAMPLES;//calculates mean 

    //------

    int maxIndex = 0, mx = 0;
    *mode = -1;

    for(int i = 0; i < 10 - 1; i++){//calculates mode, counts the number of repetitions and compares them
        if (featureArr[i] > mx){
            mx = featureArr[i];
            maxIndex = i;
        }
    }
    *mode = maxIndex;
    return 0;
}

/* ------------------------------------------------------Task 3 ------------------------------------------------------*/
void classDistribution (struct Animal dataZoo [NUM_SAMPLES]){
    int count[NUM_CLASSES] = {0};
    
    for(int i = 0; i < NUM_SAMPLES; i++){//populate the array that counts each class
        count[dataZoo[i].classLabel - 1]++;
    }
    
    int maxCount = 0;
    for(int i = 0; i < NUM_CLASSES; i++){//finds the maximum count
        if(count[i] > maxCount){
            maxCount = count[i];
        }
    }
    
    for(int i = maxCount + 1; i > 0; i--){//prints the histogram
        for(int j = 0; j < NUM_CLASSES; j++){
            if(i - count[j] == 1 ){
                if (count[j]/10 != 0){
                    printf("  (%d) ", count[j]);
                }
                else {
                    printf("  (%d)  ", count[j]);
                }
                
            }
            else if (count[j] >= i){
                printf("   *   ");
            }
            else {
                printf("       ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < NUM_CLASSES; i++){//prints the classes in the end
        printf("class%d ", i + 1);
    }
    printf("\n");

}

/* ------------------------------------------------------Task 4 ------------------------------------------------------*/
float euclideanDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
    float sum = 0;

    for (int i = 0; i < NUM_FEATURES; i++){//calculates accoriding to the formula for euclidean distance
        sum += powf((vector1[i] - vector2[i]), 2);
    }
    return sqrtf(sum);//returns the square root
}

/* ------------------------------------------------------Task 5------------------------------------------------------*/
int hammingDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
    int sum = 0;

    for (int i = 0; i < NUM_FEATURES; i++){//calculates accoriding to the formula for hamming distance
        if(vector1[i] != vector2[i]){
            sum++;
        }
    }
    return sum;
}

/* ------------------------------------------------------Task 6------------------------------------------------------ */
float jaccardSimilarity (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
    float ones = 0, zeros = 0;

    for (int i = 0; i < NUM_FEATURES; i++){ //calculates accoriding to the formula for jaccard similarity
        if(vector1[i] == vector2[i] && vector1[i] == 1){
            ones++;
        }
        else if (vector1[i] == vector2[i] && vector1[i] == 0){
            zeros++;
        }
    }

    return ones / (NUM_FEATURES - zeros);
}

/*------------------------------------------------------ Task 7 ------------------------------------------------------*/
void findKNearestNeighbors(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors[NUM_SAMPLES]) {
    int indices[NUM_SAMPLES];
    float distance[NUM_SAMPLES];
    float temp = 0;

    for (int i = 0; i < NUM_SAMPLES; i++) {//uses the correct distance
        switch (whichDistanceFunction) {
            case 1:
                temp = euclideanDistance(dataZoo[i].features, newSample);
                break;
            case 2:
                temp = (float)hammingDistance(dataZoo[i].features, newSample);
                break;
            case 3:
                temp = 1 - jaccardSimilarity(dataZoo[i].features, newSample); //Inverts Jaccard similarity for sorting
                break;
            default:
                break;
        }

        distance[i] = temp;
        indices[i] = i; 
    }

    //Selection Sort to sort distances and indices ( WRITTEN BY MYSELF BUT GOT HELP FROM CHATGPT TOO )
    int minx, tempi;
    float tempd;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        minx = i;
        for (int j = i + 1; j < NUM_SAMPLES; j++) {
            if (distance[j] < distance[minx]) {
                minx = j;
            }
        }
        //Swaps the minimum element found with the first element
        tempd = distance[minx];
        distance[minx] = distance[i];
        distance[i] = tempd;

        //Swaps the indices
        tempi = indices[minx];
        indices[minx] = indices[i];
        indices[i] = tempi;
    }

    //Assigning the k nearest indices
    for (int i = 0; i < k; i++) {
        kNearestNeighbors[i] = indices[i];
    }

}


/* ------------------------------------------------------Task 8------------------------------------------------------ */
int predictClass(struct Animal dataZoo[NUM_SAMPLES], int neighborsForNewSample[NUM_SAMPLES], int newSample[NUM_FEATURES], int k) {
    int classCount[10] = {0};

    //Counts class labels
    for (int i = 0; i < k; i++) {
        int classLabel = dataZoo[neighborsForNewSample[i]].classLabel;
        //adds one to the count for this class    
        classCount[classLabel - 1]++;
        
    }

    int maxIndex = 0;
    int mx = 0;

    //Calculates mode, counts the number of repetitions and compares them
    for (int i = 0; i < 10; i++) { 
        if (classCount[i] > mx) {
            mx = classCount[i];
            maxIndex = i;
        }
    }

    return maxIndex + 1;

}
/*------------------------------------------------------Task 9 ------------------------------------------------------*/
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], struct Animal testData [NUM_TEST_DATA], int k){
    

    int correct = 0;
    int kNearestNeighbors[NUM_SAMPLES];
    int whichDistanceFunction ;

    printf("choose a distance method, (1, 2 or 3): ");//get input
    scanf("%d", &whichDistanceFunction);

    if (whichDistanceFunction > 3 || whichDistanceFunction < 1){//input validation
        printf("invalid");
        return 0;
    }
    
    for (int i = 0; i < NUM_TEST_DATA; i++){

        findKNearestNeighbors(dataZoo, testData[i].features, k, whichDistanceFunction, kNearestNeighbors);//calling 7 and 8
        int predictedClass = predictClass(dataZoo, kNearestNeighbors, testData[i].features, k);
        
        if (predictedClass == testData[i].classLabel) {//count correct predictions
            correct++;
        }
    }
    return (float)correct / NUM_TEST_DATA * 100; //Calculate percentage

}


