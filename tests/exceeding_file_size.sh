#!/bin/sh

# Exceeding file size

PROGRAM_NAME="../file_system"
FILE_SYSTEM_BINARY_NAME="../file_system.bin"

$PROGRAM_NAME init $FILE_SYSTEM_BINARY_NAME

$PROGRAM_NAME copy_to_disk $FILE_SYSTEM_BINARY_NAME too_large_file.txt

$PROGRAM_NAME list $FILE_SYSTEM_BINARY_NAME
$PROGRAM_NAME show_usage $FILE_SYSTEM_BINARY_NAME