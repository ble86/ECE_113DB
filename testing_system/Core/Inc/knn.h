/*
 * knn.h
 *
 *  Created on: Feb 3, 2022
 *      Author: ble
 */

#ifndef INC_KNN_H_
#define INC_KNN_H_

#define K 1
#define TRAINDATASIZE 742//406

typedef struct{
  float * point;
  int classification;
} ClassifiedPoint;

typedef struct{
  int classification;
  double distance;
} ClassifiedDistance;

char * getTestClass(float *testPoint, ClassifiedPoint *trainData); //, int pitch);
void readTrainingData(int numOfLines, ClassifiedPoint* ret);

#endif /* INC_KNN_H_ */
