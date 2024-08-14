#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/virtual_disk.h"
#include "../include/bitmap.h"

FILE
*openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        perror("Couldn't open file");
        return NULL;
    }
    return file;
}

int
allocateAndReadInodesAndBitmap(FILE *virtual_disk_file, Inode **inodes, unsigned char **bitmap) {
    *inodes = (Inode *)calloc(MAX_FILES, sizeof(Inode));
    *bitmap = (unsigned char *)calloc(BITMAP_SIZE, sizeof(unsigned char));
    if (!*inodes || !*bitmap) {
        perror("Memory allocation failed");
        free(*inodes);
        free(*bitmap);
        return -1;
    }

    if (fread(*inodes, sizeof(Inode), MAX_FILES, virtual_disk_file) != MAX_FILES ||
        fread(*bitmap, sizeof(unsigned char), BITMAP_SIZE, virtual_disk_file) != BITMAP_SIZE) {
        perror("Couldn't read virtual disk");
        free(*inodes);
        free(*bitmap);
        return -1;
    }
    return 0;
}

Inode*
findInodeByName(Inode *inodes, const char *source_filename) {
    int inode_index;
    for (inode_index = 0; inode_index < MAX_FILES; inode_index++) {
        if (inodes[inode_index].used && strcmp(inodes[inode_index].name, source_filename) == 0) {
            return &inodes[inode_index];
        }
    }
    return NULL;
}
