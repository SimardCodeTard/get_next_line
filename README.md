# get_next_line
## Line-by-line file reader
Reads the next line from a given file descriptor
## Behaviour
Get next line handles up to MAX_FD file descriptors, 1024 by default. You can redefine this macro using the flag -D during compilation I.E:

`-D MAX_FD=42`

You can also redefine the size of the buffer used to read from the file descriptor by overriding the macro BUFFER_SIZE I.E:

`-D BUFFER_SIZE=42`

- GNL returns NULL when the end of the file is reached
- GNL returns NULL when an error occurs (memory allocation fail, read fail)
- GNL will return NULL when the file descriptor is invalid (-1) or is closed
- GNL will return NULL when the given file descriptor is superior to MAX_FD
### Undefined behaviour
GNL exhibist undefined behaviour in the following cases :
- When edits are made to the file associated with the given file descriptor between to calls to GNL  
- A binary file is associated with the given file descriptor

# Usage

You are free to use this code anywhere, to edit it or do anything you want with it

A release will be uploaded *soon*™ with a header file and an archive
