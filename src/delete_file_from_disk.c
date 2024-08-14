#include "../include/bitmap.h"
#include "../include/virtual_disk.h"
#include "../include/fs_utils.h"


static void
cleanup(FILE *file, Inode *inodes, unsigned char *bitmap) {
    fclose(file);
    free(inodes);
    free(bitmap);
}

void
deleteFileFromDisk(const char *disk_file_name, const char *filename_for_deletion)
{
    FILE *virtual_disk_file;
    Inode *inode = NULL;
    Inode *inodes;
    unsigned char* bitmap;
    int i;

    virtual_disk_file = openFile(disk_file_name, "r+b");
    allocateAndReadInodesAndBitmap(virtual_disk_file, &inodes, &bitmap);

    inode = findInodeByName(inodes, filename_for_deletion);

    if (!inode)
    {
      fprintf(stderr, "No files with given filename!\n");
      return;
    }

    for (i = 0; i < MAX_FILESIZE_IN_BLOCKS && inode->block_pointers[i] != -1; i++)
    {
      clear_bit(bitmap, inode->block_pointers[i]);
    }

    inode->used = 0;

    rewind(virtual_disk_file);

    if (fwrite(inodes, sizeof(Inode), MAX_FILES, virtual_disk_file) != MAX_FILES ||
        fwrite(bitmap, sizeof(unsigned char), BITMAP_SIZE, virtual_disk_file) != BITMAP_SIZE)
    {
      perror("Couldn't save changes to virtual disc");
      cleanup(virtual_disk_file, inodes, bitmap);
      return;
    }

    printf("FILE '%s' DELETED FROM FS.\n", filename_for_deletion);
    cleanup(virtual_disk_file, inodes, bitmap);
}