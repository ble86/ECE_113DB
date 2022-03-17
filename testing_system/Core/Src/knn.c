/*
 * knn.c
 *
 *  Created on: Feb 3, 2022
 *      Author: ble
 */

#include "knn.h"
#include "const.h"
#include "arm_math.h"
#include "data.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const int DIMENSION = 24;
//static const int OCTAVE_DIM = 12;
static const int PITCH_DIM = 12;

//Definition of the Meaning of Classes
static char* classes[] = {
    /*CLASS 0:*/ "G3   ",
    /*CLASS 1:*/ "G#3  ",
    /*CLASS 2:*/ "A3   ",
    "A#3  ",
    "B3   ",
    "C4   ",
    "C#4  ",
    "D4   ",
    "D#4  ",
    "E4   ",
    "F4   ",
    "F#4  ",
    "G4   ",
    "G#4  ",
    "A4   ",
    "A#4  ",
    "B4   ",
    "C5   ",
    "C#5  ",
    "D5   ",
    "D#5  ",
    "E5   ",
    "F5   ",
    "F#5  ",
    "G5   ",
    "G#5  ",
    "A5   ",
    "A#5  ",
    "B5   ",
	"CAug ",
	"CM   ",
	"Cm   ",
	"Cdim ",
	"C#Aug",
	"C#M  ",
	"C#m  ",
	"C#dim",
	"DAug ",
	"DM   ",
	"Dm   ",
	"Ddim ",
	"D#Aug",
	"D#M  ",
	"D#m  ",
	"D#dim",
	"EAug ",
	"EM   ",
	"Em   ",
	"Edim ",
	"FAug ",
	"FM   ",
	"Fm   ",
	"Fdim ",
	"F#Aug",
	"F#M  ",
	"F#m  ",
	"F#dim",
	"GAug ",
	"GM   ",
	"Gm   ",
	"Gdim ",
	"G#Aug",
	"G#M  ",
	"G#m  ",
	"G#dim",
	"AAug ",
	"AM   ",
	"Am   ",
	"Adim ",
	"A#Aug",
	"A#M  ",
	"A#m  ",
	"A#dim",
	"BAug ",
	"BM   ",
	"Bm   ",
	"Bdim "
};

/*
static char* octaves[] = {
    "3 ",
    "3",
    "3 ",
    "3",
    "3 ",
    "4 ",
    "4",
    "4 ",
    "4",
    "4 ",
    "4 ",
    "4",
    "4 ",
    "4",
    "4 ",
    "4",
    "4 ",
    "5 ",
    "5",
    "5 ",
    "5",
    "5 ",
    "5 ",
    "5",
    "5 ",
    "5",
    "5 ",
    "5",
    "5 "
};
*/

/**
 * Calculating the Euclidean Distance
 *
 * √((p1_1 - p2_1)^2 + (p1_2 - p2_2)^2 + ... + (p1_x - p2_x)^2))
 *
 * Input Parameters:
 *  dimensions: Count of Dimensions the Euklid should work
 *  point1: Array of float coordinates
 *  point2: Array of float coordinates
 *
 *   *
 */
static double eukl_distance(int dimensions, float* point1, float* point2) {//, int pitch){
  double temp = 0;
  for (int i = 0; i < dimensions; ++i) {
	  float weight;

	  if (i < CHROMA_SIZE) {
		  weight = 1;
	  }
	  else {
		  weight = 1.25;
	  }
	  temp += (weight * pow(point1[i] - point2[i], 2.0));

	  temp += pow(point1[i] - point2[i], 2.0);
  }
  return temp;
  /*
  int startIndex = pitch ? 0 : PITCH_DIM;
  int endIndex = pitch ? dimensions : PITCH_DIM + dimensions;
  for(int i = startIndex; i < endIndex; i++){
	  temp += pow(point1[i] - point2[i], 2.0);
  }
  return sqrt(temp);
  */
}

/**
 * Comparator Function to Compare 2 Classified Distances by their Distance
 */
static int compareCdistances(const void* a, const void* b){
  ClassifiedDistance d1 = *((ClassifiedDistance*) a);
  ClassifiedDistance d2 = *((ClassifiedDistance*) b);

  if(d1.distance == d2.distance) return 0;
  else if(d1.distance < d2.distance) return -1;
  else return 1;
}

/**
 * Sorting Function to Sort Array of ClassifiedDistances
 */
static void sortCD(ClassifiedDistance* data, int size){
  qsort(data, size, sizeof(ClassifiedDistance), compareCdistances);
}

/**
 * Classification function K-Nearest-Neighbour
 *
 * Input Parameters:
 *  dimensions: count of Dimensions the Knn works with
 *  trainedData: ClassifiedPoint Array of the Trained Data
 *  trainedSize: Size of the Trained Array
 *  toClassify: Float Array that represents the Point to be classified
 */

static ClassifiedDistance* classify(int dimensions, const ClassifiedPoint* trainedData, int trainedSize, float* toClassify) {//, int pitch){


  ClassifiedDistance * distances = malloc(sizeof(ClassifiedDistance) * trainedSize);

  //Calculating the Euklid distance to every trained Datapoint
  for (int i = 0; i < trainedSize; i++)
  {
    ClassifiedDistance distance;
    distance.classification = (trainedData)[i].classification;
    distance.distance = eukl_distance(dimensions, (trainedData)[i].point, toClassify); //, pitch);
    distances[i] = distance;
  }

  //Sort the Calculated Distances
  sortCD(distances, trainedSize);

  return distances;
}


static ClassifiedPoint* convertToPoint(float* inp){
  ClassifiedPoint* point = malloc(sizeof(ClassifiedPoint));
  float * pos = malloc(DIMENSION * sizeof(float));
  memcpy(pos, inp, DIMENSION * sizeof(float));
  /*
  for (int i = 0; i < DIMENSION; i++) {
    pos[i] = inp[i];
  }
  */
  point->point = pos;
  //Target
  point->classification = inp[24];

  return point;
}


/**
 * Reading Data from the specified File
 *
 * Input Parameter:
 *  numOfLines: Number of Lines to Read
 *  ret: Array the Points should be saved to
 */
void readTrainingData(int numOfLines, ClassifiedPoint* ret) {
	for (int i = 0; i < numOfLines; i++) {
		float trainPointBuffer[25] = {0};
		/*
		for (int j = 0; j < DIMENSION + 1; j++) {
			trainPointBuffer[j] = trainDataArray[i * 25 + j];
		}
		*/
		memcpy(trainPointBuffer, trainDataArray + (i * 25), 25 * sizeof(float));
		ClassifiedPoint* p =  convertToPoint(trainPointBuffer);
		ret[i] = *p;
	}
}


char * getTestClass(float *testPoint,  ClassifiedPoint *trainData) {//, int pitch) {
	const int trainDataSize = TRAINDATASIZE;
	ClassifiedDistance *distances = classify(DIMENSION, trainData, trainDataSize, testPoint);
	char *classification = classes[distances[0].classification];
	/*
	ClassifiedDistance *distances = classify(DIMENSION / 2, trainData, trainDataSize, testPoint, pitch);
	char *classification;
	if (pitch) {
		classification = classes[distances[0].classification];
	}
	else {
		classification = octaves[distances[0].classification];
	}
	*/
	free(distances);
	return classification;
}
