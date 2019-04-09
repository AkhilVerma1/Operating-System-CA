
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> // read the number of the last error
#include <fcntl.h> 

int main (int count_arguments, char *files_array[]) {

    int pipe_endpoints[2]; 
    int byte_length;
    char main_buffer[100];
    char child_buffer[100];
    
    // Check if 3 arguments were supplied.
    if (count_arguments != 3) {
      perror("Filecopy: filecopy.exe [target] [destination]. \n");
      exit(1);
    }
    
    char* source_file = files_array[1];
    char* destination_file = files_array[2];

    // Attempt to create a pipe.
    if (pipe(pipe_endpoints) < 0) {
      printf("Something went wrong creating the pipe! %s\n", strerror(errno));
      exit(1);
    }

    // Fork child process
    switch(fork()) {

      // If there was an error forking a child process. then accordingly the error message will be printed on the user screen.
      case -1:
        printf("Error forking child process. %s\n", strerror(errno));
        exit(1);
      case 0: 
        close(pipe_endpoints[1]);                                                        // Close_Writing.
        ssize_t num_bytes_child = read(pipe_endpoints[0], child_buffer, sizeof(child_buffer));   
        close(pipe_endpoints[0]);                                                     

        int t_target_desc = open(destination_file, O_CREAT | O_WRONLY);                                  
        write(t_target_desc, child_buffer, num_bytes_child);                            
        

      // If the current process is the parent process.
      // Read the file and send it down to the child process to write.
      default: 
        close(pipe_endpoints[0]); //close reading the file.
        int fileInDesc = open(source_file, O_RDONLY);                       // Read file 
        ssize_t num_bytes = read(fileInDesc, main_buffer, sizeof(main_buffer));   // Get size to read
        write(pipe_endpoints[1], main_buffer, num_bytes);                           // Write bytes to the Child Process.!.
        close(pipe_endpoints[1]);                                              // Close writing when we are done with this.

    }

    return 0;
}
