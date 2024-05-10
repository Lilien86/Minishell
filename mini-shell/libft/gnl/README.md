# get_next_line

This project involves the implementation of the get_next_line function, a function that reads a line from a file descriptor or standard input stream.

## Features

The get_next_line function reads a line (up to a newline character) from a file descriptor and stores this line in a dynamically allocated character string. With each function call, the next line of the file is read until a newline is found or the end of the file is reached.



## Instalation

1. Clone this repository to your local machine.
	```bash
	git clone https://github.com/Lilien86/42-get_next_line.git
	```
2. Compile the program with the source files of the function (and your own main.c).
	```bash
	cc get_next_line.c get_next_line.h get_next_line_utils.c main.c
	```
## Usage

1. Include the header file get_next_line.h and fcntl.h.
	```c
	#include "get_next_line.h"
	#include "<fcntl.h>"
	```
2. Use the get_next_line function.
	```c
	int main() {
    int fd = open("exemple.txt", O_RDONLY);
    char *line;

    while (get_next_line(fd, &line) > 0) {
        // Traitement de la ligne lue
        printf("Ligne lue : %s\n", line);
        free(line);
    }

    close(fd);
    return 0;
	}
	```

