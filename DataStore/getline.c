// https://gist.github.com/jstaursky/84cf1ddf91716d31558d6f0b5afc3feb
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>

typedef ptrdiff_t ssize_t;
/*******************************************************************************
 * getline -- Stores line of text from stream.                                 *
 *                                                                             *
 * Parameters                                                                  *
 *      lineptr -- Storing address for the line of text. Buffer is NUL         *
 *                 terminated and includes newline character if found.         *
 *                 lineptr is malloc'd and must be free'd by caller.           *
 *      n       -- Buffer size(in bytes) stored in linepter. Reallocates as    *
 *                 necessary capture input stream.                             *
 *      stream  -- Source where line of text originates from.                  *
 *                                                                             *
 * Returns                                                                     *
 *      On success, returns the number of characters read, including newline,  *
 *      but not including the terminating null byte ('\0'). Return -1 on       *
 *      failure to read a line (including end-of-file condition).              *
 *      In the event of an error, errno is set to indicate the cause.          *
 *******************************************************************************/

/* Based on the spec found here
   http://man7.org/linux/man-pages/man3/getline.3.html */

ssize_t
getline( char   **lineptr, /* input/output - storage address for input stream */
		 size_t  *n,       /* input/output - string size in bytes */
		 FILE    *stream ) /* input - text stream */
{
  char    *buffer_tmp, *position;
  size_t   block,      offset;
  int      c;

  if( !stream || !lineptr || !n ) {
	errno = EINVAL;
	return -1;
	/* Minimum length for strings is 2 bytes. */
  } else if( *lineptr == NULL || *n <= 1 ) {
	*n = 128;
	if( !(*lineptr = malloc(*n)) ) {
	  errno = ENOMEM;
	  return -1;
	}
  }
  block = *n;
  position = *lineptr;

  while( (c = fgetc(stream)) != EOF \
            && (*position++ = c) != '\n' ) {
	offset = position - *lineptr; /* realloc doesn't guarantee it can keep '*lineptr' in same memory spot.
                                               * so needs keep track of offset. */
	if( offset >= *n ) {
	  buffer_tmp = realloc(*lineptr, *n += block);
	  if( !buffer_tmp ) { /* Do not free. Return *lineptr. */
		errno = ENOMEM;
		return -1;
	  }
	  *lineptr = buffer_tmp;
	  position = *lineptr + offset;
	}
  }
  *position = '\0';
  return (position - *lineptr - 1);
}