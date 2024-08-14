#ifndef FILESYSTEM_UTILS_H
#define FILESYSTEM_UTILS_H

#include "virtual_disk.h"

FILE *openFile(const char *filename, const char *mode);
int allocateAndReadInodesAndBitmap(FILE *virtual_disk_file, Inode **inodes, unsigned char **bitmap);
Inode *findInodeByName(Inode *inodes, const char *source_filename);

#endif // FILESYSTEM_UTILS_H
