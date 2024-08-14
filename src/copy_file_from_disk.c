#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/virtual_disk.h"
#include "../include/bitmap.h"
#include "../include/filesystem_utils.h"

static void
cleanup(FILE *file1, FILE *file2, Inode *inodes, unsigned char *bitmap) {
    if (file1) fclose(file1);
    if (file2) fclose(file2);
    free(inodes);
    free(bitmap);
}

int
copyBlocksFromDisk(FILE *virtual_disk_file, FILE *destination_file, Inode *inode) {
    char buffer[BLOCK_SIZE];
    int blocks_needed = inode->size / BLOCK_SIZE + (inode->size % BLOCK_SIZE != 0);
    long offset;
    int i;
    for (i = 0; i < blocks_needed; i++) {
        offset = (long)MAX_FILES * sizeof(Inode) + BITMAP_SIZE + inode->block_pointers[i] * BLOCK_SIZE;
        fseek(virtual_disk_file, offset, SEEK_SET);

        size_t bytes_to_read = (i == blocks_needed - 1 && inode->size % BLOCK_SIZE != 0) ? inode->size % BLOCK_SIZE : BLOCK_SIZE;
        if (fread(buffer, 1, bytes_to_read, virtual_disk_file) < bytes_to_read && !feof(virtual_disk_file)) {
            perror("Couldn't read from virtual disk");
            return -1;
        }

        if (fwrite(buffer, 1, bytes_to_read, destination_file) < bytes_to_read) {
            perror("Couldn't save to file");
            return -1;
        }
    }
    return 0;
}

void
copyFileFromDisk(const char *disk_file_name, const char *source_filename, const char *destination_filename) {
  Inode *inodes;
  Inode *inode;
  unsigned char *bitmap;
  FILE *virtual_disk_file = openFile(disk_file_name, "rb");

  if (allocateAndReadInodesAndBitmap(virtual_disk_file, &inodes, &bitmap) == -1) {
    cleanup(NULL, virtual_disk_file, inodes, bitmap);
    return;
  }

  inode = findInodeByName(inodes, source_filename);

  if (!inode) {
    fprintf(stderr, "File %s doesn't exist on virtual disk\n", source_filename);
    cleanup(NULL, virtual_disk_file, inodes, bitmap);
    return;
  }
  FILE *destination_file = openFile(destination_filename, "wb");

  if (copyBlocksFromDisk(virtual_disk_file, destination_file, inode) == -1) {
    cleanup(destination_file, virtual_disk_file, inodes, bitmap);
    return;
  }

  printf("FILE '%s' COPIED FROM FS '%s'.\n", source_filename, destination_filename);
  cleanup(destination_file, virtual_disk_file, inodes, bitmap);
}
