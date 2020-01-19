// dipHeader.h
// Created by Yining HE on 1/19/18.
// Copyright © 2020 Yining HE. All rights reserved.

#ifndef dipHeader_h
#define dipHeader_h 
#endif
#define _CRT_SECURE_NO_WARNINGS

// not implemented now  
// #define R 0  
// #define G 1
// #define B 2 


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std; 

// Initialize system for argument input 
void dip_init();

// print image error information 
void print_image_info();

// Allocate memory for image
unsigned char** alloc2DImage( int width , int height, int BytePerPixel);
unsigned char*** alloc3DImage(int width, int height, int BytePerPixel); 

// Delete memory for image 
int delete2DImage(int width, int height, int BytesPerPixe); 
int delete3DImage(int width, int height, int BytesPerPixe);


// IO function for image input and output for file 
void read2DImage(FILE *file, unsigned char**imageData, int width , int height , int BytePerPixel  ); 
void read3DImage(FILE *file, unsigned char*** imageData, int width, int height , int channels); 
void write2DImage(FILE *file , unsigned char **imageData, int width , int height); 
void write3DImage(FILE* file, unsigned char*** imageData, int width, int height , int channels);

// contained file open function and use IO function for image data read 
void read2DImageFile(char* filename, unsigned char** imageData, int width, int height, int BytesPerPixel); 
void read3DImageFile(char* filename, unsigned char** imageData, int width, int height, int BytesPerPixel); 
void write2DImageFile(char* filename, unsigned char** imageData, int width, int height, int BytesPerPixel);
void write3DImageFile(char* filename, unsigned char** imageData, int width, int height, int BytesPerPixel);

// extend image edges 
void extend2DImageEdge(unsigned char **imageData, unsigned char **extendedImage , int width , int height, int BytePerPixel); 
void extend3DImageEdge(unsigned char ***imageData, unsigned char **extendedImage , int width , int height, int BytePerPixel); 

// for linear filter
int aver2DImage(unsigned char** imageData, int row, int col, int BytesPerPixel, int widsize);


// return a number that indicates color of current pixels 
// RGB  R 0 G 1 B 2  
// input the position of current pixel
// the row and col indicates the position of the pixel, the start pixel is at position (0,0)   
int judgePixelColor(int row , int col);



int judgePixelColor(int row , int col){
    if(row%2==1 &&col%2==1||row%2==0&&col%2==0){
        return 1 ; 
    }else if(row%2==0&&col%2==1){
        return 0 ; 
    }else{
        return 2 ; 
    }
}


// test library inclusion 
void testHeaderIncluded(){
    cout<<"Hello World"<<endl;     
}


// if the input image only contains one pixel, this will return null ;  
// the copied image obeys the reflection rule
void extend2DImageEdge(unsigned char **imageData, unsigned char **extendedImage,  int width , int height , int BytePerPixel){
    int extendedWidth = width +4 ; 
    int extendedHeight = height+4; 
    for (int row=0 ;row<extendedHeight;row++){
        for (int col = 0; col < extendedWidth; col++) {
            //assign space for columns 

            if (row == 0) {
                extendedImage[0][0] = imageData[1][1];
                extendedImage[0][1] = imageData[0][1];
                extendedImage[0][width + 2] = imageData[0][width - 2];
                extendedImage[0][width + 3] = imageData[0][width - 1];
                for (int col = 2; col < extendedWidth - 2; col++) {
                    extendedImage[0][col] = imageData[1][col - 2];
                }
            }

            if (row == 1) {
                extendedImage[1][0] = imageData[1][1];
                extendedImage[1][1] = imageData[0][1];
                extendedImage[1][width + 2] = imageData[0][width - 2];
                extendedImage[1][width + 3] = imageData[0][width - 1];
                for (int col = 2; col < extendedWidth - 2; col++) {
                    extendedImage[1][col] = imageData[0][col - 2];
                }
            }

            if (row == extendedHeight - 1) {
                extendedImage[extendedHeight - 1][0] = imageData[height - 1][1];
                extendedImage[extendedHeight - 1][1] = imageData[height - 1][0];
            }

            if (row == extendedHeight - 2) {

            }
            if (row>=2&&col == 0&&row<extendedHeight-2) {

            }
            if (col == 1&& row>=2&&row<extendedHeight-2) {

            }



        }
       
    }


}


unsigned char compRedForGreenBL(unsigned char **imageData, int row, int col) {
    unsigned char result; 
    if (row % 2 == 0) {
        result = 0.5 * (imageData[row][col+1] + imageData[row][col-1]);
    }else {
        result = 0.5 * (imageData[row + 1][col] + imageData[row - 1][col]); 
    }
    return result; 
}


unsigned char compRedforBlueBL(unsigned char** imageData, int row, int col) {
    unsigned char result; 
    result = 0.25 * (imageData[row + 1][col + 1] +imageData[row+1][col-1] +imageData[row-1][col+1]+imageData[row-1][col-1]);
    return result; 
}

unsigned char compGreenforRedBL(unsigned char** imageData, int row, int col) {
    unsigned char result; 
    result = 0.25 * (imageData[row + 1][col + 1] + imageData[row + 1][col - 1] + imageData[row - 1][col + 1] + imageData[row - 1][col - 1]);

    return result; 
}

unsigned char compGreenforBlueBL(unsigned char** imageData, int row, int col) {
    unsigned char result;
    result = 0.25 * (imageData[row + 1][col + 1] + imageData[row + 1][col - 1] + imageData[row - 1][col + 1] + imageData[row - 1][col - 1]);

    return result; 
}   

unsigned char compBlueforRedBL(unsigned char** imageData, int row, int col) {
    unsigned char result; 
    result = 0.25 * (imageData[row + 1][col + 1] + imageData[row + 1][col - 1] + imageData[row - 1][col + 1] + imageData[row - 1][col - 1]);

    return result;
}

unsigned char compBlueforGreenBL(unsigned char** imageData, int row, int col) {
    unsigned char result;
    if (row % 2 == 0) {
        result = 0.5 * (imageData[row + 1][col] + imageData[row - 1][col]); 
    }else {
        result = 0.5 * (imageData[row][col + 1] + imageData[row][col - 1]); 
    }
    return result; 
}



void read2DImage(FILE *file, unsigned char** imageData, int width, int height ,int BytesPerPixel) {
    for (int row = 0; row < height; row++) {
       fread(imageData[row], sizeof(unsigned char),  width * BytesPerPixel, file);
    }
}

void read3DImage(FILE* file, unsigned char*** imageData, int width, int height, int channels) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            fread(imageData[row][col], sizeof(unsigned char), channels, file); 
        }
    }
}

void write2DImage(FILE* file, unsigned char** imageData, int width, int height, int BytesPerPixel) {
    for (int row = 0; row < height; row++) {
        fwrite(imageData[row], sizeof(unsigned char), width * BytesPerPixel, file); 
    }

}

void write3DImage(FILE* file, unsigned char*** imageData, int width, int height, int channels) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            fwrite(imageData[row][col], sizeof(unsigned char), channels, file); 
        }
    }
}

void read2DImageFile(char* filename, unsigned char** imageData, int width, int height, int BytesPerPixel) {
    FILE* file;
    if (!(file = fopen(filename, "rb"))) {
        cout << "Cannot open file: " << filename<< endl;
        exit(1);
    }
    read2DImage(file, imageData, width, height, BytesPerPixel);
    fclose(file);
}

void read3DImageFile(char* filename, unsigned char*** imageData, int width, int height, int BytesPerPixel) {
    FILE* file;
    if (!(file = fopen(filename, "rb"))) {
        cout << "Cannot open file: " << filename << endl;
        exit(1);
    }
    read3DImage(file, imageData, width, height, BytesPerPixel);
    fclose(file);
}

void write2DImageFile(char* filename, unsigned char** imageData, int width, int height, int BytesPerPixel) {
    FILE* file;
    if (!(file = fopen(filename, "wb"))) {
        cout << "Cannot open file: " << filename << endl;
        exit(1);
    }
    write2DImage(file, imageData, width, height, BytesPerPixel);
    fclose(file);
}

void write3DImageFile(char* filename, unsigned char*** imageData, int width, int height, int BytesPerPixel) {
    FILE* file;
    if (!(file = fopen(filename, "rb"))) {
        cout << "Cannot open file: " << filename << endl;
        exit(1);
    }
    write3DImage(file, imageData, width, height, BytesPerPixel);
    fclose(file);
}


void extend2DImageEdge(unsigned char** imageData, unsigned char** extendedImage, int width, int height, int BytePerPixel,int widsize) {
    for (int row = 0; row < height+2*widsize; row++) {
        for (int col = 0; col < width + 2 * widsize; col++) {
            //the
            if (row < widsize && col < widsize) {
                extendedImage[row][col] = imageData[widsize - 1 - row][widsize - 1 - col];
            }

            if (row<widsize && col>=width + widsize&& col<width+widsize) {
                extendedImage[row][col] = imageData[widsize - 1 - row][col]; 
            }

            if (row < widsize && col >= widsize + width) {
                extendedImage[row][col] = imageData[widsize - 1 - row][widsize + 2 * width - 1-col]; 
            }
            if (row >= widsize && row < widsize + height && col < widsize) {
                extendedImage[row][col] = imageData[row][widsize-1-col]; 
            }
            if (row >= widsize && row < widsize + height && col >= widsize && col < widsize + width) {
                extendedImage[row][col] = imageData[row-widsize][col-widsize]; 
            }
            if (row >= widsize && row < widsize + height && col >= widsize+width&&col<widsize*2+width) {
                extendedImage[row][col] = imageData[row][widsize + 2 * width - 1 - col]; 
            }
            if (row >= widsize + height && row < widsize * 2 + height && col < widsize) {
                extendedImage[row][col] = imageData[2 * height + widsize - 1 - row][widsize - 1 - col]; 
            }
            if (row >= widsize + height && row < widsize * 2 + height && col >= widsize && col < widsize + width) {
                extendedImage[row][col] = imageData[2*height+widsize-1-row][col]; 
            }
            if (row >= widsize + height && row < widsize * 2 + height && col >= widsize + width && col < widsize * 2 + width) {
                extendedImage[row][col] = imageData[2 * height + widsize - 1 - row][2 * width + widsize - 1 - col]; 
            }


        }
    
    }

}

unsigned char** alloc2DImage(int width, int height, int BytePerPixel) {
    unsigned char** imageData; 
    imageData = new unsigned char* [height]; 
    for (int row = 0; row < height; row++) {
        imageData[row] = new unsigned char[width]; 
    }
    return imageData;  
}

unsigned char *** alloc3DImage(int width, int height, int BytePerPixel) {
    unsigned char*** imageData; 
    imageData = new unsigned char**[height]; 
	for(int row=0 ; row<height ; row++){
		imageData[row] = new unsigned char *[width];
		for(int col=0; col<width; col++){
			imageData[row][col] = new unsigned char[3]; 
		}
	}
    return imageData; 
}

int dip_init(int argc , char *argv[],int *height, int *width ,int *BytePerPixel ) {
    // Define file pointer and variables
    FILE* file;
//  const  int BytesPerPixel;
    const  int Size = 256;
    int rows;
    int cols;


    // Check for proper syntax
    if (argc < 3) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4) {
       // BytesPerPixel = 1; // default is grey image
    }
    else {
       // BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5) {
       //     Size = atoi(argv[4]);
            *width = atoi(argv[4]); 
            *height = atoi(argv[5]); 
        }
    }

    // Allocate image data array
 //   unsigned char Imagedata[Size][Size][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
 //   fread(Imagedata, sizeof(unsigned char), Size * Size * BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
//    fwrite(Imagedata, sizeof(unsigned char), Size * Size * BytesPerPixel, file);
    fclose(file);

    return 0;

}

double eval2DImagePSNR(unsigned char **oriImage , unsigned char** tarImage ,int width ,int height, int BytesPerPixel) {
    double result = 0.0;  
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            
        }
    }
        return result; 
}

double eval3DImagePSNR(unsigned char ***oriImage , unsigned char ***tarImage, int width , int height , int BytesPerPixel) {
    double result = 0.0; 
    return result; 
}

int aver2DImage(unsigned char **imageData ,int row ,int col , int BytesPerPixel , int widsize) {
    double average;
    double sum = 0.0; 
    int result; 
    int startx = row - widsize / 2; 
    int endx = row + widsize / 2; 
    int starty = col - widsize / 2; 
    int endy = col + widsize / 2; 
    for (int i = startx; i <= endx; i++) {
        for (int j = starty; j <= endy; j++) {
            sum += imageData[i][j]; 
        }
    }
    int total = (endx - startx + 1) * (endx - startx + 1); 
    average = sum/total; 
    return (int)average; 

}