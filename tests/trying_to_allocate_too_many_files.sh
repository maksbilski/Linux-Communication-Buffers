#!/bin/sh

# Exceeding file amount limit

PROGRAM_NAME="../file_system"
FILE_SYSTEM_BINARY_NAME="../file_system.bin"

$PROGRAM_NAME init $FILE_SYSTEM_BINARY_NAME


for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
  $PROGRAM_NAME copy_to_disk $FILE_SYSTEM_BINARY_NAME very_small_file.txt "very_small_file_${i}.txt"
done

$PROGRAM_NAME list $FILE_SYSTEM_BINARY_NAME
$PROGRAM_NAME show_usage $FILE_SYSTEM_BINARY_NAME

$PROGRAM_NAME copy_to_disk $FILE_SYSTEM_BINARY_NAME very_small_file.txt "very_small_file_${i}.txt"


for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
  $PROGRAM_NAME delete $FILE_SYSTEM_BINARY_NAME "very_small_file_${i}.txt"
done

$PROGRAM_NAME list $FILE_SYSTEM_BINARY_NAME
$PROGRAM_NAME show_usage $FILE_SYSTEM_BINARY_NAME
