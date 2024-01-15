/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color* p = *(image->image+ (row) * image->cols + col);
	Color* white = (Color*) malloc(sizeof(Color));
	white->R = 255;
	white->G = 255;
	white->B = 255;
	Color* black = (Color*) malloc(sizeof(Color));
	white->R = 0;
	white->G = 0;
	white->B = 0;
	if( p->B %2){
		free(black);
		return white;
	}
	else{
		free(white);
		return black;
	}

}
//Now, we can look at just the rightmost bit in order to determine whether that pixel in the hidden message is white or black. Given that white is 
//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image* img = (Image*) malloc(sizeof(Image));
	img->cols = image->cols;
	img->rows = image->rows;
	img->image = (Color**) malloc(sizeof(Color*) * image->cols * image->rows);
	Color** p = img->image;
	for(int i=0;i<image->rows;i++){
		for(int j=0;j<image->cols;j++){
			*p = evaluateOnePixel(image,i,j);
			p++;
		}
	}
	return img;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc!=2)
	return -1;
	Image* image = readData(argv[1]);
	Image* img = steganography(image);
	writeData(img);
	freeImage(image);
	freeImage(img);
	


}
