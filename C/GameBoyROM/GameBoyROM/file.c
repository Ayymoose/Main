#include "file.h"

#define FILE_ERROR -1

//File size in bytes
long fileSize(FILE* file) {
  if (file) {
    //Save file pointer
    long current = ftell(file);
    //Seek to end
    fseek(file, 0, SEEK_END);
    //Get size
    long size = ftell(file);
    //Restore file pointer
    fseek(file, current, SEEK_SET);

    return size;
  }
  return FILE_ERROR;
}