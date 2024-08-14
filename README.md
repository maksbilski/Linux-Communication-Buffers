## Inter-process Commucation Buffers 

This project implements communication buffers designed to facilitate inter-process communication in a Linux environment. The implementation leverages semaphores to ensure proper synchronization between processes accessing the buffers.

## Communication Buffers

A communication buffer is a data structure that can hold up to `M` elements of the same type. The elements in the buffer can be retrieved in the order they were inserted (FIFO) or in reverse order (LIFO, stack). These buffers are intended for use in scenarios where multiple processes need to communicate by exchanging messages.

## Features

The implementation ensures the following synchronization features:

- **Read/Write Safety:** Prevents reading from an empty buffer and writing to a full buffer.
- **Process Coordination:** Ensures that multiple processes can read from and write to the buffer without interfering with each other.
- **Special Message Handling:** Supports the insertion of a "special" message into all buffers, which is prioritized in subsequent reads.

## Implementation Details

- **communication_buffers.c / communication_buffers.h:** Defines and implements the communication buffers and associated operations.
- **resource_management.c / resource_management.h:** Manages resources such as memory and buffer allocation.
- **process_semaphores.c / process_semaphores.h:** Implements synchronization mechanisms using Linux IPC semaphores.

## Building and Running the Project

This project uses a `Makefile` for easy compilation. To build the project, use the following command:

make

This will compile the source files and generate the executable.

To run the program, execute the generated binary as follows:

./your_program_name

## Testing

The project includes several test cases to verify the correct operation of the communication buffers under different conditions. These tests simulate various scenarios where processes interact with the buffers, ensuring that the synchronization mechanisms function as expected.

### Test Files

- **consumer_recieving_messages_in_FIFO_order.c:** Tests whether messages are retrieved in FIFO order from the buffer.
- **consumer_recieving_special_messages_in_LIFO_order.c:** Verifies that special messages are retrieved in LIFO order.
- **consumer_recieving_special_messages_stack_overflow.c:** Checks how the buffer handles stack overflow when special messages are prioritized.
- **consumers_waiting_on_empty_buffer.c:** Tests the behavior of consumers waiting on an empty buffer.
- **consumers_waiting_on_empty_buffer_special.c:** Ensures correct handling when special messages are introduced into an empty buffer.
- **producer_waiting_on_full_buffer.c:** Validates the behavior of producers when the buffer is full.

### Running Tests

To run a specific test, compile the corresponding test file using the `Makefile`, or manually compile it using a command like:

gcc -o test_binary test_file.c communication_buffers.c resource_management.c process_semaphores.c -lpthread -lrt

Then execute the compiled binary:

./test_binary

These tests are crucial for ensuring the reliability and correctness of the inter-process communication implemented in this project.
