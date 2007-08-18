#include "libxcpy.h"

int buf_size = 4096;    /* buffer size int Bytes */

int set_bufsize(int sz) {
    buf_size = sz;
    return 0;
}

/***** fexists ***************************************************************
** Description: Check if a file exists or not.
** Parameters : fname - the name of the file
** Returns    : 0 - file don't exists, 1 - file exists
** Date added : 2002-03-16
** Notes      :
******************************************************************************/
int fexists(FILENAME fname) {
    int fdesc;
    int res = 0;

    if ( (fdesc = open(fname, 0)) != -1 ) {
        res = 1;
        close(fdesc);
    }

    return res;
}

/***** filecopy **************************************************************
** Description: Performs copy of a file
** Parameters : srcf - source file, destf - destination file
** Returns    : status of the operation, 0 if the copy was successful
** Date added : 2002-03-16
** Notes      :
******************************************************************************/
int filecopy(FILENAME srcf, FILENAME destf) {
    int srcfd;      /* source file descriptor */
    int destfd;     /* destination file descriptor */
    struct stat f_stat;
    char * buffer;  /* file copy buffer */
    int readbts = 0;

    /* check existance of the source file */
    if ( !fexists(srcf) ) {
        printf("error 45: Source file '%s' don't exists!\n", srcf);
        return -1;
    }

    /* check existance of the destination file */
    if ( !fexists(destf) ) {
        if ( (destfd = creat(destf, 00600)) == -1 ) {
#ifdef _ERRNO_H
            printf("error 53: %s\n", strerror(errno));
#else
            printf("error: Can't create file '%s'!\n", destf);
#endif
            return -1;
        }
        close(destfd);
    }
    else {
        printf("error: Destination file '%s' exists!\n", destf);
        return -1;
    }

    /* open the source file */
    if ( (srcfd = open(srcf, 0)) == -1 ) {
#ifdef _ERRNO_H
        printf("error 69: %s\n", strerror(errno));
#else
        printf("error: Can't open file '%s'!\n", srcf);
#endif
        return -1;
    }

    /* open the destination file */
    if ( (destfd = open(destf, 1)) == -1 ) {
#ifdef _ERRNO_H
        printf("error 79: %s\n", strerror(errno));
#else
        printf("error: Can't open file '%s'!\n", srcf);
#endif
        return -1;
    }

    if ( (buffer = malloc(buf_size)) == NULL ) {
#ifdef _ERRNO_H
        printf("error 88: %s", strerror(errno));
#else
        printf("error: Can't allocate memory for the copy operation!");
#endif
        return -1;
    }

    while ( (readbts = read(srcfd, buffer, buf_size)) > 0 ) {
        if ( write(destfd, buffer, readbts) != readbts ) {
            free(buffer);
            return -1;
        }
    }

    free(buffer);

    /* close file descriptors */
    if ( close(destfd) == -1 ) {
#ifdef _ERRNO_H
        printf("error 107: %s\n", strerror(errno));
#else
        printf("error: Error closing file '%s'!\n", destf);
#endif
        return -1;
    }
    if ( close(srcfd) == -1 ) {
#ifdef _ERRNO_H
        printf("error 115: %s\n", strerror(errno));
#else
        printf("error: Error closing file '%s'!\n", srcf);
#endif
        return -1;
    }

    /* set the appropriate file permitions to the destination file */
#ifdef _SYS_STAT_H
    if ( stat(srcf, &f_stat) == 0 ) {
        chmod(destf, f_stat.st_mode);
    }
#endif

    return 0;
}

