#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable : 4996)

//Maximum file size to view is 128KB
#define MAX_FILE_SIZE 131072
#define LINE_WIDTH 16
typedef const char* string;
typedef unsigned char byte;

/*
Simple Hex viewer in C
Don't know why I called it Hex Editor!
Some bugs still
*/

//Returns the size in bytes for the given file
int fileSize(FILE* file) {
  int current = ftell(file);
  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, SEEK_SET, current);
  return length;
}

void printInformation(string fileName, int size, int lineWidth, int maxFileSize) {
  printf("File:              %s\n", fileName);
  printf("File size:         %d bytes\n", size);
  printf("Line width:        %d\n", lineWidth);
  printf("Maximum file size: %d bytes\n\n", maxFileSize);
}

int main(int argc,char** argv) {

  /*
  Invoke via command line
  filename lineWidth
  */

  //Filename to view
  string fileName = argv[1];

  //Try to open the file
  FILE* file = fopen(fileName, "r");

  if (file) {

    //Determine file size in bytes
    int size = fileSize(file);

    if (size <= MAX_FILE_SIZE) {

      //Information
      printInformation(fileName, size, LINE_WIDTH, MAX_FILE_SIZE);

      //Read all data into 128KB buffer
      byte* buffer = (byte*)malloc(size * sizeof(byte));
      fread(buffer, size, 1, file);

      //Print address bar
      //2 + 5
      printf("         ");
      for (int i = 0; i < LINE_WIDTH; i++) {
        printf("%02X ", i);
      }
      printf("\n       ");
      for (int i = 0; i < (LINE_WIDTH * 1.5); i++) {
        printf("--", i);
      }
      printf("\n");
 
      //Addresses on the column should be at most length of the MAX_FILE_SIZE bytes long (in hex)
      //1. Print address first (i)
      //2. Print one line of file 
      //3. Print ASCII equivalent 
      //All in one line!

      char* line = (char*)malloc(sizeof(char)*(LINE_WIDTH+1));
      //Clear array as it contains garbage
      memset(line, 0, LINE_WIDTH);

      for (int i = 0,j = 0,k = 0; i < size; i++) {
        //1. Print address 
        if (j == 0) {
          printf(" %05X | ", i);
          j++;
        }
        else if (j == LINE_WIDTH+1) {
          //3. Print ASCII equivalent
          int n = 0;
          while (line[n] != '\0') {
            printf("%c", (int)line[n]);
            n++;
          }
          printf("\n");
          j = 0;
          strcpy(line, "");
          k = 0;
        } else {
          //2. Print one line of file 
          printf("%02X ", buffer[i]);
          line[k] = buffer[i];
          k++;
          j++;
        }
      }

      //Deallocate memory
      free(line);
      free(buffer);
    }
    else {
      fprintf(stderr,"File is too large to be viewed.\nMaximum file size is %d bytes.\n",MAX_FILE_SIZE);
    }
    fclose(file);
  }
  else {
    fprintf(stderr,"Error reading from file %s\nDoes it exist?", fileName);
  }

  getchar();
  return 0;
}