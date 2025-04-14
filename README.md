#get_next_line


The main purpose for this project is to create a function that reads from a file descriptor and returns the line red.

The function signatature is : 

    char* get_next_line(int fd)

This functions returns either

    1) A pointer to a memory allocated on the heap with the line red from the fd

    2) NULL if EOF was encountered.

Please note that is the caller's job to free the memory when is not needed anymore. 

IMPORTANT CONCEPTS:

- File descriptor 

    A non-negative number that refers to a specific file in the system.
