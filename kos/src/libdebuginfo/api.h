/* Copyright (c) 2019-2023 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDEBUGINFO_API_H
#define GUARD_LIBDEBUGINFO_API_H 1
#define LIBUNWIND_WANT_PROTOTYPES

#include <__crt.h>
#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */

#include <libdebuginfo/api.h>

#define CC LIBDEBUGINFO_CC

#ifndef REF
#define REF __REF
#endif /* !REF */

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */

#ifdef __KERNEL__
#include <kernel/compiler.h>
#define TEXTSECTION         ATTR_COLDTEXT
#define STRINGSECTION       ATTR_COLDRODATA
#define REPR_TEXTSECTION    ATTR_COLDTEXT
#define REPR_RODATASECTION  ATTR_COLDRODATA
#define REPR_STRINGSECTION  ATTR_COLDRODATA
#define PRINT_TEXTSECTION   ATTR_COLDTEXT
#define PRINT_STRINGSECTION ATTR_COLDRODATA
#else /* __KERNEL__ */
#define TEXTSECTION         /*ATTR_SECTION(".text")*/   /* nothing */
#define STRINGSECTION       /*ATTR_SECTION(".rodata")*/ /* nothing */
#define REPR_TEXTSECTION    ATTR_SECTION(".text.repr")
#define REPR_RODATASECTION  ATTR_SECTION(".rodata.repr")
#define REPR_STRINGSECTION  ATTR_SECTION(".rodata.repr")
#define PRINT_TEXTSECTION   ATTR_SECTION(".text.print")
#define PRINT_STRINGSECTION ATTR_SECTION(".rodata.print")
#endif /* !__KERNEL__ */

#define REPR_STRING(s)                                         \
	XBLOCK({                                                   \
		PRIVATE REPR_STRINGSECTION char const _repr_str[] = s; \
		XRETURN _repr_str;                                     \
	})
#define PRINT_STRING(s)                                         \
	XBLOCK({                                                    \
		PRIVATE PRINT_STRINGSECTION char const _repr_str[] = s; \
		XRETURN _repr_str;                                      \
	})


#if !defined(NDEBUG) && 1
#ifdef __KERNEL__
#include <kernel/printk.h>
#undef TRACE
#define DOTRACE(...)      (printk(KERN_RAW "%s(%d) : %s : ",__FILE__,__LINE__,__builtin_FUNCTION()),printk(KERN_RAW __VA_ARGS__))
#define CORRUPT()          printk(KERN_RAW "%s(%d) : %s : Corruption\n",__FILE__,__LINE__,__builtin_FUNCTION())
#define ERROR(err)      do{printk(KERN_RAW "%s(%d) : %s : Error : %s\n",__FILE__,__LINE__,__builtin_FUNCTION(),#err); goto err;}__WHILE0
#define ERRORF(err,...) do{printk(KERN_RAW "%s(%d) : %s : Error : %s : ",__FILE__,__LINE__,__builtin_FUNCTION(),#err); printk(KERN_RAW __VA_ARGS__); goto err;}__WHILE0
#elif defined(__CRT_HAVE_syslog)
#include <syslog.h>
#define DOTRACE(...)      (syslog(LOG_DEBUG,"%s(%d) : %s : ",__FILE__,__LINE__,__builtin_FUNCTION()),syslog(LOG_DEBUG,__VA_ARGS__))
#define CORRUPT()          syslog(LOG_ERR,"%s(%d) : %s : Corruption\n",__FILE__,__LINE__,__builtin_FUNCTION())
#define ERROR(err)      do{syslog(LOG_ERR,"%s(%d) : %s : Error : %s\n",__FILE__,__LINE__,__builtin_FUNCTION(),#err); goto err;}__WHILE0
#define ERRORF(err,...) do{syslog(LOG_ERR,"%s(%d) : %s : Error : %s : ",__FILE__,__LINE__,__builtin_FUNCTION(),#err); syslog(LOG_ERR,__VA_ARGS__); goto err;}__WHILE0
#endif /* ... */
#define CASE(x)         __IF0{case x: TRACE("%s\n",#x);}
#endif /* !NDEBUG */

#ifndef CASE
#define CASE(x)         case x:
#endif /* !CASE */
#ifndef CORRUPT
#define CORRUPT()       (void)0
#endif /* !CORRUPT */
#ifndef ERROR
#define ERROR(err)      goto err
#endif /* !ERROR */
#ifndef ERRORF
#define ERRORF(err,...) goto err
#endif /* !ERRORF */

#ifdef DOTRACE
#define TRACE DOTRACE
#else /* DOTRACE */
#define DOTRACE TRACE
#endif /* !DOTRACE */

#if !defined(TRACE) || 0
#undef TRACE
#define TRACE(...) (void)0
#undef CASE
#define CASE(x) case x:
#endif /* !TRACE */


#endif /* !GUARD_LIBDEBUGINFO_API_H */
