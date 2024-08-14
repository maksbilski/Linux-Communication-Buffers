CC=gcc
CFLAGS=-Wall -Wextra -g
DEPS = virtual_disk.h bitmap.h
OBJ = main.o src/filesystem_utils.o src/list_files.o src/copy_file_to_disk.o src/bitmap.o src/show_disk_usage.o src/copy_file_from_disk.o src/delete_file_from_disk.o src/initialize_and_save_filesystem.o

%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

file_system: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o src/*.o file_system file_system.bin ./tests/restored_test_file_*
