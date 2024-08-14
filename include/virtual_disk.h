#ifndef VIRTUAL_DISK_H
#define VIRTUAL_DISK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 20
#define MAX_FILENAME_LENGTH 255
#define BLOCK_SIZE 524
#define MAX_FILESIZE_IN_BLOCKS 150
#define NUM_BLOCKS 400
#define BITMAP_SIZE (NUM_BLOCKS / 8)

typedef struct {
  char name[MAX_FILENAME_LENGTH];
  int size;
  int block_pointers[MAX_FILESIZE_IN_BLOCKS];
  int used;
} Inode;

int initializeAndSaveFileSystem(const char *filename);
void copyFileToDisk(const char *disk_file_name, const char *source_file_name, const char *destination_file_name);
void copyFileFromDisk(const char *disk_file_name, const char *source_filename, const char *destination_filename);
void deleteFileFromDisk(const char *disk_file_name, const char *filename_for_deletion);
void listFiles(const char *disk_file_name);
void showDiskUsage(const char *disk_file_name);

#endif // VIRTUAL_DISK_H