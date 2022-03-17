# ECE 113DB Final Project
This is the final project for ECE 113DB at UCLA, Winter 2022 done by Brandon Le and Alethea Sung-Miller.
This repo contains the STM32 CubeIDE code for two STM projects.
The two projects are as follows:
- training_system
- testing_system

## Repository Structure and Usage
The code for taking training data for chroma vectors for a KNN model is in the training_system directory.
- 'main.c' defines the basic microcontroller code
- 'chroma.c' and 'chroma.h' define the algorithm for obtaining chroma vectors for our project
- 'const.h' defines any pertinent constants needed for the project such as size of ADC buffers, number of training samples, etc.

The code for taking testing data for the final system is in the testing_system directory.
- 'main.c' defines the basic microcontroller code
- 'chroma.c' and 'chroma.h' define the algorithm for obtaining chroma vectors for our project
- 'const.h' defines any pertinent constants needed for the project such as size of ADC buffers, number of training samples, etc.
- 'knn.c' and 'knn.h' define the algorithm for finding the K-Nearest Neighbors to the test point.
- 'data.h' holds a CSV-style array of all the chroma vectors obtained from training
- 'ssd1306.c', 'ssd1306.h', 'fonts.c', and 'fonts.h' define the library for controlling a mini-OLED display using STM32 microcontroller functions.

Credit to 4ilo, afiskon, and Jackhammer88 for developing the mini-OLED display library code, which can be found at the following [Github repository](https://github.com/4ilo/ssd1306-stm32HAL)