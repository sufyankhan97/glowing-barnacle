/* For the size of the file. */
#include <sys/stat.h>
/* This contains the mmap calls. */
#include <sys/mman.h> 
/* These are for error printing. */
#include <errno.h>
#include <string.h>
#include <stdarg.h>
/* This is for open. */
#include <fcntl.h>
#include <stdio.h>
/* For exit. */
#include <stdlib.h>
/* For the final part of the example. */
#include <ctype.h>

/* "check" checks "test" and prints an error and exits if it is
   true. */

static void
check (int test, const char * message, ...)
{
    if (test) {
        va_list args;
        va_start (args, message);
        vfprintf (stderr, message, args);
        va_end (args);
        fprintf (stderr, "\n");
        exit (EXIT_FAILURE);
    }
}

int main ()
{
    /* The file descriptor. */
    int fd;
    /* Information about the file. */
    struct stat s;
    int status;
    size_t size;
    /* The file name to open. */
    const char * file_name = "me.c";
    /* The memory-mapped thing itself. */
    const char * mapped;
    int i;
    int count = 1;

    /* Open the file for reading. */
    fd = open ("zip.txt", O_RDONLY);
    check (fd < 0, "open %s failed: %s", file_name, strerror (errno));

    /* Get the size of the file. */
    status = fstat (fd, & s);
    check (status < 0, "stat %s failed: %s", file_name, strerror (errno));
    size = s.st_size;

    /* Memory-map the file. */
    mapped = mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    check (mapped == MAP_FAILED, "mmap %s failed: %s",
           file_name, strerror (errno));

    /* Now do something with the information. */
    // for (i = 0; i < size; i++) {
    //     char c;
    //     printf("%c", mapped[i]);
    //      }


    while (mapped[i]!='\0'){
        while(mapped[i]==mapped[i+1]){
            count++;
            i++;
        }
        // if(count==1) {
        //     printf("%c",mapped[i]);
        // }
        // else{
            count = count + '0';
            printf("%d%c",count,mapped[i]);
            count = 1; 
            
        // }

        i++;

    }

    return 0;
}