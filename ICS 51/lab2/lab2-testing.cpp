#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#include "lodepng.h"


extern char *yourName;
extern char *yourStudentID;


// These functions should be implemented in lab2.cpp
void imageThresholding(unsigned char* buffer, int dim);
void imageFlip(unsigned int* image, int dim, int direction);

int main() {
	int i, j;
  
  printf("ICS 51, Lab 2 \nName: %s\nStudentID: %s\n\n", yourName, yourStudentID);
  
  
#define TEST_P1 1
#define TEST_P2 1

	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	std::vector<unsigned char> image2;
	unsigned int width, height;
	lodepng::State state;
	std::string filename, outFilename;
	
#if TEST_P1
	// Part 1 tests
	unsigned char testStr0[3][3] = { {0,   30,  60},
									 {90,  120, 150},
									 {180, 210, 240} };

	unsigned char exptectedStr0[3][3] = { {0,   0,   0},
										  {0,   0,   255},
										  {255, 255, 255} };
  
	imageThresholding(&testStr0[0][0], 3);

	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j) {
			if (testStr0[i][j] != exptectedStr0[i][j]) {
				std::cout << "Part 1: Test 1 failed at index: " << i << "," << j << " got: " << int(testStr0[i][j]) << " expected: " << int(exptectedStr0[i][j]) << std::endl;
				break;
			}
		}
	if (i*j == 9)
		std::cout << "Part 1: Test 1 passed." << std::endl;

	unsigned char testStr1[4][4] = {{0,   30,  90,  120},
									{127, 45,  130, 60},
									{127, 128, 0,   130},
									{27, 228, 255, 255 }};
	unsigned char exptectedStr1[4][4] = {{0, 0,   0,   0},
	                                     {0, 0,   255, 0 },
										 {0, 255, 0,   255},
										 {0, 255, 255, 255 }};

	imageThresholding(&testStr1[0][0], 4);
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j) {
			if (testStr1[i][j] != exptectedStr1[i][j]) {
				std::cout << "Part 1: Test 2 failed at index: " << i << "," << j << " got: " <<int(testStr1[i][j]) << " expected: " << int(exptectedStr1[i][j]) << std::endl;
				break;
			}
		}
	if (i*j == 16)
		std::cout << "Part 1: Test 2 passed." << std::endl;

	// Load a grayscale png (1Byte per pixel)
	// Make a binary image by thresholding

	filename = "lena.png";
	lodepng::decode(image, width, height, filename, LCT_GREY, 8U);

	if (image.size() == 0) {
		std::cerr << "lena.png not found. Make sure it exists in your solution directory." << std::endl;
		return -1;
	}
	assert(width == height);
	imageThresholding((unsigned char*)&image[0], width);

	outFilename = "lena_binary.png";
	lodepng::encode(outFilename, image, width, height, LCT_GREY, 8U);
	image.clear();

	std::cout << "Check Lena_binary.png." << std::endl;
#endif

#if TEST_P2
	// Part 2 tests
	unsigned int testStr2[3][3] = { {0x0,        0x10101010, 0x20202020},
	                                {0x30303030, 0x40404040, 0x50505050},
	                                {0x60606060, 0x70707070, 0x80808080} };


	unsigned int exptectedStr2[3][3] = { {0x20202020,  0x10101010, 0x0},
                                         {0x50505050,  0x40404040, 0x30303030},
                                         {0x80808080,  0x70707070, 0x60606060} };

	imageFlip(&testStr2[0][0], 3, 0);
	
	for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)	{
		if (testStr2[i][j] != exptectedStr2[i][j]) {
			std::cout << std::hex << "Part 2: Test 1 failed at index: "<< i<< ","<< j << " got: " << testStr2[i][j] <<" expected: " << exptectedStr2[i][j]<<  std::endl;
			break;
		}
	}
	if (i*j == 9)
		std::cout << "Part 2: Test 1 passed." << std::endl;

	unsigned int testStr2_1[3][3] = { { 0x0,        0x10101010, 0x20202020 },
	                                  { 0x30303030, 0x40404040, 0x50505050 },
	                                  { 0x60606060, 0x70707070, 0x80808080 } };

	unsigned int exptectedStr2_1[3][3] = { { 0x60606060,  0x70707070, 0x80808080 },
										   { 0x30303030,  0x40404040, 0x50505050 },
										   { 0x0,  0x10101010, 0x20202020 } };

	imageFlip(&testStr2_1[0][0], 3, 1);

	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j) {
			if (testStr2_1[i][j] != exptectedStr2_1[i][j]) {
				std::cout << std::hex<< "Part 2: Test 2 failed at index: " << i << "," << j << " got: " << testStr2_1[i][j] << " expected: " << exptectedStr2_1[i][j] << std::endl;
				break;
			}
		}
	if (i*j == 9)
		std::cout << "Part 2: Test 2 passed." << std::endl;

	unsigned int testStr3[4][4] = { {0, 1,   2,  3},
									{4, 5,   6,  7},
									{8, 9,  10, 11},
									{12, 13, 14, 15} };

	unsigned int exptectedStr3[4][4] = { {3,  2, 1, 0},
										 {7,  6, 5, 4},
										 {11, 10, 9, 8},
										 {15, 14, 13, 12}};

	imageFlip(&testStr3[0][0], 4, 0);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (testStr3[i][j]!= exptectedStr3[i][j]) {
				std::cout << "Part 2: Test 3 failed at index: " << i <<","<<j<< " got: " << testStr3[i][j] << " expected: " << exptectedStr3[i][j] << std::endl;
				break;
			}
		}
	}
	if (i*j == 16)
		std::cout << "Part 2: Test 3 passed." << std::endl;

	unsigned int testStr3_1[4][4] = { { 0, 1,   2,  3 },
										{ 4, 5,   6,  7 },
										{ 8, 9,  10, 11 },
										{ 12, 13, 14, 15 } };

	unsigned int exptectedStr3_1[4][4] = { { 12,  13, 14, 15 },
											{ 8,  9, 10, 11 },
											{ 4, 5, 6, 7 },
											{ 0, 1, 2, 3 } };

	imageFlip(&testStr3_1[0][0], 4, -1);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (testStr3_1[i][j] != exptectedStr3_1[i][j]) {
				std::cout << "Part 2: Test 4 failed at index: " << i << "," << j << " got: " << testStr3_1[i][j] << " expected: " << exptectedStr3_1[i][j] << std::endl;
				break;
			}
		}
	}
	if (i*j == 16)
		std::cout << "Part 2: Test 4 passed." << std::endl;
	// Load a RGBA png (4-Bytes per pixel)
	// Rotate it to left
	filename = "lena_color.png";
	lodepng::decode(image, width, height, filename, LCT_RGBA, 8U);
	if (image.size() == 0) {
		std::cerr << "lena_color.png not found. Make sure you have this file in your solution directory." << std::endl;
		return -1;
	}
	assert(width == height);

	imageFlip((unsigned int*)&image[0], width, 0);
	//imageFlip((unsigned int*)&image[0], width, 1);


	outFilename = "Lena_flipped.png";
	lodepng::encode(outFilename, image, width, height, LCT_RGBA, 8U);
	
	std::cout << "Check Lena_flipped.png." << std::endl;
#endif
	return 0;
}
