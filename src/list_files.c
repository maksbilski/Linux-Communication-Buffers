#include "../include/virtual_disk.h"
#include "../include/bitmap.h"
#include "../include/filesystem_utils.h"


void
listFiles(const char *virtual_disk_filename)
{
  FILE *file;
  Inode *inodes;
  int i;
  int file_count;

  file = openFile(virtual_disk_filename, "rb");

  inodes = (Inode *)calloc(MAX_FILES, sizeof(Inode));
  if (fread(inodes, sizeof(Inode), MAX_FILES, file) != MAX_FILES)
  {
      perror("Couldn't read from file");
      fclose(file);
      exit(EXIT_FAILURE);
  }

  fclose(file);

  printf("\n=========== FILE LIST ===========\n");
  for (i = 0; i < MAX_FILES; ++i)
  {
    if (inodes[i].used)
    {
      printf("NAME: %s, SIZE: %d bytes\n", inodes[i].name, inodes[i].size);
      ++file_count;
    }
  }
  if (file_count)
  {
    printf("File count: %d", file_count);
  }
  else
  {
    printf("There are no files currently on the system.");
  }
  printf("\n");
  free(inodes);
}
