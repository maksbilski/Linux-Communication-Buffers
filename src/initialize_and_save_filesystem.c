#include "../include/virtual_disk.h"
#include "../include/bitmap.h"

void
initializeInodesAndBitmap(Inode *inodes, unsigned char *bitmap)
{
    int i;
    int j;
    for (i = 0; i < MAX_FILES; ++i)
    {
        inodes[i].used = 0;
        for (j = 0; j < MAX_FILESIZE_IN_BLOCKS; ++j)
        {
            inodes[i].block_pointers[j] = -1;
        }
    }

    memset(bitmap, 0, BITMAP_SIZE);
}

void
saveFilesystemToFile(const Inode *inodes, const unsigned char *bitmap, const char *filename)
{
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Couldn't open file");
        exit(EXIT_FAILURE);
    }

    if (fwrite(inodes, sizeof(Inode), MAX_FILES, file) != MAX_FILES ||
        fwrite(bitmap, sizeof(bitmap[0]), BITMAP_SIZE, file) != BITMAP_SIZE)
    {
        perror("Couldn't save to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fseek(file, NUM_BLOCKS * BLOCK_SIZE, SEEK_CUR);
    fclose(file);
}

int
initializeAndSaveFileSystem(const char *filename)
{
  Inode* inodes;
  unsigned char* bitmap;

  inodes = (Inode *)calloc(MAX_FILES, sizeof(Inode));
  bitmap = (unsigned char *)calloc(BITMAP_SIZE, sizeof(unsigned char));

  if (!inodes || !bitmap) {
      perror("Memory allocation failed");
      free(inodes);
      free(bitmap);
      return -1;
  }

  initializeInodesAndBitmap(inodes, bitmap);
  saveFilesystemToFile(inodes, bitmap, filename);
  return 0;
};
