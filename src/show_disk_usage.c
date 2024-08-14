#include "../include/bitmap.h"
#include "../include/virtual_disk.h"


void
showDiskUsage(const char *disk_file_name)
{
    FILE *virtual_disk_file;
    unsigned char *bitmap;
    int start;
    int current_status;
    int i;
    int size;

    virtual_disk_file = fopen(disk_file_name, "rb");
    if (!virtual_disk_file)
    {
        perror("Cannot open the virtual disk");
        return;
    }

    fseek(virtual_disk_file, sizeof(Inode) * MAX_FILES, SEEK_SET);
    bitmap = (unsigned char *)calloc(BITMAP_SIZE, sizeof(unsigned char));
    if (fread(bitmap, sizeof(unsigned char), BITMAP_SIZE, virtual_disk_file) != BITMAP_SIZE)
    {
        perror("Error reading bitmap from disk");
        fclose(virtual_disk_file);
        return;
    }

    fclose(virtual_disk_file);

    start = 0, current_status = get_bit(bitmap, 0);

    printf("\n======= DISK USAGE MAP =======\n");
    for (i = 1; i <= NUM_BLOCKS; i++)
    {
        if (i < NUM_BLOCKS && get_bit(bitmap, i) == current_status)
        {
            continue;
        }

        size = i - start;
        printf("ADDR %d TO %d: %s, SIZE: %d BLOCKS\n",
              start, i - 1, current_status ? "OCCUPIED" : "FREE", size);

        if (i < NUM_BLOCKS)
        {
            start = i;
            current_status = get_bit(bitmap, i);
        }
    }
    printf("\n");
    free(bitmap);
}
