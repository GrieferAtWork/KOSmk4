#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H 1
#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_ 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/sys/config.h' */

#if !defined(__KOS__) && __has_include("/usr/local/include/sys/config.h")
#include "/usr/local/include/sys/config.h"
#elif !defined(__KOS__) && __has_include("/usr/include/sys/config.h")
#include "/usr/include/sys/config.h"
#else /* ... */
#include <features.h>
#define __DYNAMIC_REENT__ 1
#define _READ_WRITE_RETURN_TYPE  __SSIZE_TYPE__
#define _READ_WRITE_BUFSIZE_TYPE __SIZE_TYPE__
#define __LINUX_ERRNO_EXTENSIONS__ 1
#endif /* !... */

#ifndef _READ_WRITE_RETURN_TYPE
#define _READ_WRITE_RETURN_TYPE  int
#endif
#ifndef _READ_WRITE_BUFSIZE_TYPE
#define _READ_WRITE_BUFSIZE_TYPE int
#endif

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#endif /* !_SYS_CONFIG_H_ */
#endif /* !_SYS_CONFIG_H */
