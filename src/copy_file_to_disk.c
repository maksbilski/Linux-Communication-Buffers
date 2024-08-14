
#include "../include/bitmap.h"
#include "../include/virtual_disk.h"
#include "../include/filesystem_utils.h"

void
getAmountOfBlocksNeededAndFileSize(FILE *source_file, int* blocks_needed, int* file_size) {
  fseek(source_file, 0, SEEK_END);
  (*file_size) = ftell(source_file);
  rewind(source_file);
  (*blocks_needed) = ((*file_size) + BLOCK_SIZE - 1) / BLOCK_SIZE;
}

int
findFreeInodeIndex(Inode *inodes, int* new_inode_index)
{
  int inode_index;
  for (inode_index = 0; inode_index < MAX_FILES; inode_index++)
  {
    if (!inodes[inode_index].used)
    {
      (*new_inode_index) = inode_index;
      return 0;
    }
  }
  return -1;
}

void
initializeNewInodeFieldsValues(Inode* inodes, int new_inode_index, const char *destination_file_name, int file_size)
{
  strncpy(inodes[new_inode_index].name, destination_file_name, MAX_FILENAME_LENGTH);
  inodes[new_inode_index].size = file_size;
  inodes[new_inode_index].used = 1;
}

int
processBlock(FILE *source_file, FILE *virtual_disk_file, char *buffer, int block_index)
{
    long offset;
    if (fread(buffer, 1, BLOCK_SIZE, source_file) < BLOCK_SIZE && !feof(source_file))
    {
        perror("Couldn't read source file");
        return -1;
    }

    offset = (long)MAX_FILES * sizeof(Inode) + BITMAP_SIZE + block_index * BLOCK_SIZE;
    fseek(virtual_disk_file, offset, SEEK_SET);

    if (fwrite(buffer, 1, BLOCK_SIZE, virtual_disk_file) < BLOCK_SIZE){
        perror("Couldn't save to virtual disk");
        return -1;
    }
    return 0;
}

static void
cleanup(FILE *file1, FILE *file2, Inode *inodes, unsigned char *bitmap) {
    if (file1) fclose(file1);
    if (file2) fclose(file2);
    free(inodes);
    free(bitmap);
}

void
copyFileToDisk(const char *disk_file_name, const char *source_file_name, const char *destination_file_name) {
  FILE *source_file, *virtual_disk_file;
  Inode *inodes;
  unsigned char *bitmap;
  char buffer[BLOCK_SIZE];
  int block_index, i;
  int file_size, blocks_needed;
  int new_inode_index;

  source_file = openFile(source_file_name, "rb");
  virtual_disk_file = openFile(disk_file_name, "r+b");

  allocateAndReadInodesAndBitmap(virtual_disk_file, &inodes, &bitmap);
  getAmountOfBlocksNeededAndFileSize(source_file, &blocks_needed, &file_size);

  if (findInodeByName(inodes, source_file_name)) {
    fprintf(stderr, "There is already a file with name: '%s' in FS\n", source_file_name);
    cleanup(source_file, virtual_disk_file, inodes, bitmap);
    return;
  }

  if (findFreeInodeIndex(inodes, &new_inode_index) == -1)
  {
    fprintf(stderr, "No more free I-Nodes (You tried to exceeding file amount limit)\n");
    cleanup(source_file, virtual_disk_file, inodes, bitmap);
    return;
  }

  initializeNewInodeFieldsValues(inodes, new_inode_index,
    destination_file_name ? destination_file_name : source_file_name, file_size);

  if (blocks_needed > MAX_FILESIZE_IN_BLOCKS)
  {
    fprintf(stderr, "File: '%s' exceeds maximum file size\n", source_file_name);
    cleanup(source_file, virtual_disk_file, inodes, bitmap);
    return;
  }

  for (i = 0; i < blocks_needed; i++)
  {
      block_index = find_free_bit(bitmap);
      if (block_index == -1)
      {
          fprintf(stderr, "Not sufficient space for file: '%s' \n", source_file_name);
          cleanup(source_file, virtual_disk_file, inodes, bitmap);
          return;
      }
      set_bit(bitmap, block_index);

      inodes[new_inode_index].block_pointers[i] = block_index;

      processBlock(source_file, virtual_disk_file, buffer, block_index);
  }

  rewind(virtual_disk_file);

  if (fwrite(inodes, sizeof(Inode), MAX_FILES, virtual_disk_file) != MAX_FILES ||
      fwrite(bitmap, sizeof(unsigned char), BITMAP_SIZE, virtual_disk_file) != BITMAP_SIZE)
  {
      perror("Couldnt save inode changes to disc file");
      cleanup(source_file, virtual_disk_file, inodes, bitmap);
      return;
  }
  printf("FILE: '%s' COPIED TO FS.\n", source_file_name);
  cleanup(source_file, virtual_disk_file, inodes, bitmap);
}
