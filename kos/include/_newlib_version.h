#ifndef _NEWLIB_VERSION_H__
#define _NEWLIB_VERSION_H__ 1

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/_newlib_version.h' */

#include <__stdinc.h>

#if defined(__CYGWIN__) || defined(__CYGWIN32__)
#if __has_include("/usr/local/include/_newlib_version.h")
#include "/usr/local/include/_newlib_version.h"
#elif __has_include("/usr/include/_newlib_version.h")
#include "/usr/include/_newlib_version.h"
#endif
#endif /* __CYGWIN__ || __CYGWIN32__ */

#ifndef _NEWLIB_VERSION
#define _NEWLIB_VERSION      "2.5.0"
#define __NEWLIB__            2
#define __NEWLIB_MINOR__      5
#define __NEWLIB_PATCHLEVEL__ 0
#endif /* !_NEWLIB_VERSION */

#endif /* !_NEWLIB_VERSION_H__ */
