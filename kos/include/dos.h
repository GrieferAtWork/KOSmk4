/* HASH CRC-32:0x36483298 */
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
/* (#) Portability: DJGPP        (/include/dos.h) */
/* (#) Portability: MSVC         (/include/dos.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/dos.h) */
/* (#) Portability: Windows Kits (/ucrt/dos.h) */
#ifndef _DOS_H
#define _DOS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h> /* __USE_OLD_DOS */

#include <hybrid/host.h> /* __i386__, __x86_64__ */

#include <bits/crt/_diskfree_t.h>

#ifdef __USE_OLD_DOS
#include <bits/types.h>
#include <asm/os/stdio.h> /* __SEEK_SET, __SEEK_... */
#endif /* __USE_OLD_DOS */

#if defined(__i386__) || defined(__x86_64__)
#include <asm/intrin.h>
#endif /* __i386__ || __x86_64__ */

#ifndef _A_NORMAL
#define _A_NORMAL 0x00
#define _A_RDONLY 0x01
#define _A_HIDDEN 0x02
#define _A_SYSTEM 0x04
#define _A_VOLID  0x08
#define _A_SUBDIR 0x10
#define _A_ARCH   0x20
#endif /* !_A_NORMAL */

#ifdef __CC__
__SYSDECL_BEGIN

#define diskfree_t _diskfree_t

#if !defined(_GETDISKFREE_DEFINED) && defined(__CRT_HAVE__getdiskfree)
#define _GETDISKFREE_DEFINED
__CDECLARE(__ATTR_OUT(2),unsigned int,__NOTHROW_RPC,_getdiskfree,(unsigned int __drive, struct _diskfree_t *__diskfree),(__drive,__diskfree))
#endif /* !_GETDISKFREE_DEFINED && __CRT_HAVE__getdiskfree */

#if defined(__i386__) || defined(__x86_64__)
__FORCELOCAL void (_disable)(void) { __cli(); }
__FORCELOCAL void (_enable)(void) { __sti(); }
#endif /* __i386__ || __x86_64__ */

#ifdef __USE_OLD_DOS
#ifndef __delay_defined
#define __delay_defined
#ifdef __CRT_HAVE__sleep
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
__CREDIRECT_VOID(,__NOTHROW_RPC,delay,(__UINT32_TYPE__ __milli),_sleep,(__milli))
#elif defined(__CRT_HAVE___crtSleep)
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
__CREDIRECT_VOID(,__NOTHROW_RPC,delay,(__UINT32_TYPE__ __milli),__crtSleep,(__milli))
#else /* ... */
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/stdlib/_sleep.h>
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL delay)(__UINT32_TYPE__ __milli) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sleep))(__milli); }
#else /* __CRT_HAVE_nanosleep64 || __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep || __CRT_HAVE___libc_nanosleep */
#undef __delay_defined
#endif /* !__CRT_HAVE_nanosleep64 && !__CRT_HAVE_nanosleep && !__CRT_HAVE___nanosleep && !__CRT_HAVE___libc_nanosleep */
#endif /* !... */
#endif /* !__delay_defined */
#ifdef __CRT_HAVE__getdiskfree
__CREDIRECT(__ATTR_OUT(2),unsigned int,__NOTHROW_RPC,_dos_getdiskfree,(unsigned int __drive, struct _diskfree_t *__diskfree),_getdiskfree,(__drive,__diskfree))
#endif /* __CRT_HAVE__getdiskfree */
#ifndef __sleep_defined
#define __sleep_defined
#ifdef __CRT_HAVE_sleep
/* >> sleep(3)
 * Dos-specific prototype for `sleep(3)'
 * This one simply returns void, thus being unable to handle the EINTR-case. */
__CDECLARE_VOID(,__NOTHROW_RPC,sleep,(unsigned int __duration),(__duration))
#else /* __CRT_HAVE_sleep */
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE__sleep) || defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/unistd/sleep.h>
/* >> sleep(3)
 * Dos-specific prototype for `sleep(3)'
 * This one simply returns void, thus being unable to handle the EINTR-case. */
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL sleep)(unsigned int __duration) { (void)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sleep))(__duration); }
#else /* __CRT_HAVE__sleep || __CRT_HAVE___crtSleep || __CRT_HAVE_nanosleep64 || __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep || __CRT_HAVE___libc_nanosleep */
#undef __sleep_defined
#endif /* !__CRT_HAVE__sleep && !__CRT_HAVE___crtSleep && !__CRT_HAVE_nanosleep64 && !__CRT_HAVE_nanosleep && !__CRT_HAVE___nanosleep && !__CRT_HAVE___libc_nanosleep */
#endif /* !__CRT_HAVE_sleep */
#endif /* !__sleep_defined */
#ifndef __unlink_defined
#define __unlink_defined
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),__libc_unlink,(__file))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <libc/local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* __AT_FDCWD && __CRT_HAVE_unlinkat */
#undef __unlink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_unlinkat */
#endif /* !... */
#endif /* !__unlink_defined */

#if defined(__i386__) || defined(__x86_64__)
__LOCAL __INT8_TYPE__ (inp)(__UINT16_TYPE__ __port) { return __inb(__port); }
__LOCAL __UINT8_TYPE__ (inportb)(__UINT16_TYPE__ __port) { return __inb(__port); }
__LOCAL __UINT16_TYPE__ (inpw)(__UINT16_TYPE__ __port) { return __inw(__port); }
__LOCAL __UINT16_TYPE__ (inport)(__UINT16_TYPE__ __port) { return __inw(__port); }
__LOCAL __INT8_TYPE__ (outp)(__UINT16_TYPE__ __port, __INT8_TYPE__ __val) { __outb(__port, (__UINT8_TYPE__)__val); return __val; }
__LOCAL void (outportb)(__UINT16_TYPE__ __port, __UINT8_TYPE__ __val) { __outb(__port, __val); }
__LOCAL __UINT16_TYPE__ (outpw)(__UINT16_TYPE__ __port, __UINT16_TYPE__ __val) { __outw(__port, __vall); return __val; }
__LOCAL void (outport)(__UINT16_TYPE__ __port, __UINT16_TYPE__ __val) { __outw(__port, __vall); }
#define disable           _disable
#define enable            _enable
#endif /* __i386__ || __x86_64__ */

#endif /* __USE_OLD_DOS */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_OLD_DOS
#ifndef FA_NORMAL
#define FA_NORMAL _A_NORMAL
#define FA_RDONLY _A_RDONLY
#define FA_HIDDEN _A_HIDDEN
#define FA_SYSTEM _A_SYSTEM
#define FA_LABEL  _A_VOLID
#define FA_DIREC  _A_SUBDIR
#define FA_ARCH   _A_ARCH
#endif /* !FA_NORMAL */

#if !defined(SEEK_SET) && defined(__SEEK_SET)
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#endif /* !SEEK_SET && __SEEK_SET */
#if !defined(SEEK_CUR) && defined(__SEEK_CUR)
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#endif /* !SEEK_CUR && __SEEK_CUR */
#if !defined(SEEK_END) && defined(__SEEK_END)
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_END && __SEEK_END */
#endif /* __USE_OLD_DOS */

#endif /* !_DOS_H */
