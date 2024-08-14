#include "./include/virtual_disk.h"
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    char *operation;
    if (argc < 2)
    {
        printf("Usage: %s [operation] [arguments...]\n", argv[0]);
        return 1;
    }
    operation = argv[1];


    if (strcmp(operation, "init") == 0)
    {
        initializeAndSaveFileSystem(argv[2]);
        printf("FS INITIALIZED.\n");
    } else if (strcmp(operation, "copy_to_disk") == 0)
    {
        if ((argc != 4 ) && (argc != 5))
        {
            printf("Usage: %s copy_to_disk [source_file] [destination_file_name]\n", argv[0]);
            return 1;
        }
        copyFileToDisk(argv[2], argv[3], argv[4] ? argv[4] : NULL);
    } else if (strcmp(operation, "copy_from_disk") == 0)
    {
        if (argc != 5)
        {
            printf("Usage: %s copy_from_disk [source_file_on_disk] [destination_filename]\n", argv[0]);
            return 1;
        }
        copyFileFromDisk(argv[2], argv[3], argv[4]);
    } else if (strcmp(operation, "delete") == 0)
    {
        if (argc != 4)
        {
            printf("Usage: %s delete [disk_filename]\n", argv[0]);
            return 1;
        }
        deleteFileFromDisk(argv[2], argv[3]);
    } else if (strcmp(operation, "list") == 0)
    {
        listFiles(argv[2]);
    } else if (strcmp(operation, "show_usage") == 0)
    {
        showDiskUsage(argv[2]);
    } else
    {
        printf("Unknown operation: '%s'\n", operation);
        return 1;
    }

    return 0;
}
