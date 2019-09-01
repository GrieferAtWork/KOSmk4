#ifndef __NEWLIB_H__

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/newlib.h' */

#include <__stdinc.h>
#if __has_include("/usr/local/include/newlib.h")
#include "/usr/local/include/newlib.h"
#elif __has_include("/usr/include/newlib.h")
#include "/usr/include/newlib.h"
#else
/* Generic settings, as seen in a default installation of cygwin. */
#define _WANT_IO_C99_FORMATS             1
#define _WANT_IO_LONG_LONG               1
#define _WANT_IO_LONG_DOUBLE             1
#define _WANT_IO_POS_ARGS                1
#define _MB_CAPABLE                      1
#define _MB_LEN_MAX                      8
#define _ATEXIT_DYNAMIC_ALLOC            1
#define _HAVE_LONG_DOUBLE                1
#define _HAVE_CC_INHIBIT_LOOP_TO_LIBCALL 1
#define _FVWRITE_IN_STREAMIO             1
#define _FSEEK_OPTIMIZATION              1
#define _WIDE_ORIENT                     1
#define _UNBUF_STREAM_OPT                1
#endif

#ifndef __NEWLIB_H__
#define __NEWLIB_H__ 1
#endif /* !__NEWLIB_H__ */
#endif /* !__NEWLIB_H__ */
