#!/bin/sh

# Name already on system

PROGRAM_NAME="../file_system"
FILE_SYSTEM_BINARY_NAME="../file_system.bin"

$PROGRAM_NAME init $FILE_SYSTEM_BINARY_NAME

$PROGRAM_NAME copy_to_disk $FILE_SYSTEM_BINARY_NAME test_file_1.txt
$PROGRAM_NAME copy_to_disk $FILE_SYSTEM_BINARY_NAME test_file_2.txt
$PROGRAM_NAME copy_to_disk $FILE_SYSTEM_BINARY_NAME test_file_3.txt
$PROGRAM_NAME copy_to_disk $FILE_SYSTEM_BINARY_NAME test_file_3.txt

$PROGRAM_NAME list $FILE_SYSTEM_BINARY_NAME
$PROGRAM_NAME show_usage $FILE_SYSTEM_BINARY_NAME

$PROGRAM_NAME copy_from_disk $FILE_SYSTEM_BINARY_NAME test_file_1.txt restored_test_file_1
$PROGRAM_NAME copy_from_disk $FILE_SYSTEM_BINARY_NAME test_file_2.txt restored_test_file_2
$PROGRAM_NAME copy_from_disk $FILE_SYSTEM_BINARY_NAME test_file_3.txt restored_test_file_3

$PROGRAM_NAME delete $FILE_SYSTEM_BINARY_NAME test_file_1.txt
$PROGRAM_NAME delete $FILE_SYSTEM_BINARY_NAME test_file_2.txt
$PROGRAM_NAME delete $FILE_SYSTEM_BINARY_NAME test_file_3.txt

$PROGRAM_NAME list $FILE_SYSTEM_BINARY_NAME
$PROGRAM_NAME show_usage $FILE_SYSTEM_BINARY_NAME
