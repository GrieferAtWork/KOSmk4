/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVM86_API_H
#define GUARD_LIBVM86_API_H 1

#include <hybrid/compiler.h>

#include <libvm86/api.h>

#include <__crt.h>

#define CC         LIBVM86_CC

#if !defined(NDEBUG) && 0
#ifdef __KERNEL__
#include <kernel/printk.h>
#undef TRACE
#define DOTRACE(...)      (printk(KERN_RAW "%s(%d) : %s : ",__FILE__,__LINE__,__FUNCTION__),printk(KERN_RAW __VA_ARGS__))
#define ERROR(err)      do{printk(KERN_RAW "%s(%d) : %s : Error : %s\n",__FILE__,__LINE__,__FUNCTION__,#err); goto err;}__WHILE0
#define ERRORF(err,...) do{printk(KERN_RAW "%s(%d) : %s : Error : %s : ",__FILE__,__LINE__,__FUNCTION__,#err); printk(KERN_RAW __VA_ARGS__); goto err;}__WHILE0
#elif defined(__CRT_HAVE_syslog)
#include <syslog.h>
#define DOTRACE(...)      (syslog(LOG_DEBUG,"%s(%d) : %s : ",__FILE__,__LINE__,__FUNCTION__),syslog(LOG_DEBUG,__VA_ARGS__))
#define ERROR(err)      do{syslog(LOG_ERR,"%s(%d) : %s : Error : %s\n",__FILE__,__LINE__,__FUNCTION__,#err); goto err;}__WHILE0
#define ERRORF(err,...) do{syslog(LOG_ERR,"%s(%d) : %s : Error : %s : ",__FILE__,__LINE__,__FUNCTION__,#err); syslog(LOG_ERR,__VA_ARGS__); goto err;}__WHILE0
#endif
#define CASE(x)         __IF0{case x: TRACE("%s\n",#x);}
#endif
#ifndef CASE
#define CASE(x)         case x:
#endif
#ifndef ERROR
#define ERROR(err)      goto err
#endif
#ifndef ERRORF
#define ERRORF(err,...) goto err
#endif

#ifdef DOTRACE
#define TRACE  DOTRACE
#else
#define DOTRACE  TRACE
#endif

#if !defined(TRACE) || 1
#undef TRACE
#define TRACE(...)      (void)0
#undef CASE
#define CASE(x)         case x:
#endif

/* In kernel-space, memory accesses can also cause E_WOULDBLOCK to be thrown
 * when preemption is disabled. - Handle that error like we do SEGFAULTS. */
#ifdef __KERNEL__
#define WAS_SEGFAULT_THROWN() (was_thrown(E_SEGFAULT) || was_thrown(E_WOULDBLOCK))
#else /* __KERNEL__ */
#define WAS_SEGFAULT_THROWN()  was_thrown(E_SEGFAULT)
#endif /* !__KERNEL__ */


#endif /* !GUARD_LIBVM86_API_H */
