/*
** ========================================
**    XCopy library v. 0.0.1
** ========================================
**  Written by George D. Sotirov
**  Start date: 2002-03-16
** ========================================
**  This library is completely free and is
**  distributed under the GNU GPL license.
**  You have the freedom to use it ;-) and
**  fuck Microsoft ...
*/

#ifndef _LIBXCP_H
#define _LIBXCP_H 1
#define __DeBuG__ 1

#if __unix__ || unix || linux
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

/* types definitions */
typedef char* FILENAME;

/* library functions */
int set_bufsize(int);
int fexists(FILENAME);
int filecopy(FILENAME, FILENAME);

#endif /* libxcpy.h */

