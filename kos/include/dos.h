/* HASH CRC-32:0x10e9899f */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _DOS_H
#define _DOS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/host.h>
#ifdef __USE_OLD_DOS
#include <bits/types.h>
#endif /* __USE_OLD_DOS */
#if defined(__i386__) || defined(__x86_64__)
#include <asm/intrin.h>
#endif /* __i386__ || __x86_64__ */

__SYSDECL_BEGIN

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

/* Use the better name by default. */
#define _diskfree_t diskfree_t
#ifndef _DISKFREE_T_DEFINED
#define _DISKFREE_T_DEFINED 1
struct _diskfree_t {
	__UINT32_TYPE__ total_clusters;
	__UINT32_TYPE__ avail_clusters;
	__UINT32_TYPE__ sectors_per_cluster;
	__UINT32_TYPE__ bytes_per_sector;
};
#endif /* !_DISKFREE_T_DEFINED */

#ifndef _GETDISKFREE_DEFINED
#define _GETDISKFREE_DEFINED 1
#ifndef ___getdiskfree_defined
#define ___getdiskfree_defined 1
#if defined(__CRT_HAVE__getdiskfree)
__CDECLARE(,unsigned int,__NOTHROW_RPC,_getdiskfree,(unsigned int __drive, struct _diskfree_t *__diskfree),(__drive,__diskfree))
#else /* LIBC: _getdiskfree */
#undef ___getdiskfree_defined
#endif /* _getdiskfree... */
#endif /* !___getdiskfree_defined */
#endif /* !_GETDISKFREE_DEFINED */

#if defined(__i386__) || defined(__x86_64__)
__FORCELOCAL void (__LIBCCALL _disable)(void) { __cli(); }
__FORCELOCAL void (__LIBCCALL _enable)(void) { __sti(); }
#endif /* __i386__ || __x86_64__ */

#ifdef __USE_OLD_DOS
#if defined(__CRT_HAVE_delay)
/* Sleep for `mill' milliseconds (1/1.000 seconds) */
__CDECLARE_VOID(,__NOTHROW_RPC,delay,(unsigned int __mill),(__mill))
#elif defined(__CRT_HAVE___crtSleep)
/* Sleep for `mill' milliseconds (1/1.000 seconds) */
__CREDIRECT_VOID(,__NOTHROW_RPC,delay,(unsigned int __mill),__crtSleep,(__mill))
#else /* LIBC: delay */
#include <local/dos/delay.h>
/* Sleep for `mill' milliseconds (1/1.000 seconds) */
__NAMESPACE_LOCAL_USING_OR_IMPL(delay, __FORCELOCAL void __NOTHROW_RPC(__LIBCCALL delay)(unsigned int __mill) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(delay))(__mill); })
#endif /* delay... */
#if defined(__CRT_HAVE__getdiskfree)
__CREDIRECT(,unsigned int,__NOTHROW_RPC,_dos_getdiskfree,(int __drive, struct diskfree_t *__diskfree),_getdiskfree,(__drive,__diskfree))
#endif /* _dos_getdiskfree... */
#ifndef __sleep_defined
#define __sleep_defined 1
#if defined(__CRT_HAVE_sleep)
__CDECLARE_VOID(,__NOTHROW_RPC,sleep,(unsigned int __seconds),(__seconds))
#else /* LIBC: _sleep */
#undef __sleep_defined
#endif /* sleep... */
#endif /* !__sleep_defined */
#ifndef __unlink_defined
#define __unlink_defined 1
#if defined(__CRT_HAVE_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* CUSTOM: unlink */
#undef __unlink_defined
#endif /* unlink... */
#endif /* !__unlink_defined */

#if defined(__i386__) || defined(__x86_64__)
__LOCAL __INT8_TYPE__ (__LIBCCALL inp)(__UINT16_TYPE__ __port) { return __inb(__port); }
__LOCAL __UINT8_TYPE__ (__LIBCCALL inportb)(__UINT16_TYPE__ __port) { return __inb(__port); }
__LOCAL __UINT16_TYPE__ (__LIBCCALL inpw)(__UINT16_TYPE__ __port) { return __inw(__port); }
__LOCAL __UINT16_TYPE__ (__LIBCCALL inport)(__UINT16_TYPE__ __port) { return __inw(__port); }
__LOCAL __INT8_TYPE__ (__LIBCCALL outp)(__UINT16_TYPE__ __port, __INT8_TYPE__ __val) { __outb(__port, (__UINT8_TYPE__)__val); return __val; }
__LOCAL void (__LIBCCALL outportb)(__UINT16_TYPE__ __port, __UINT8_TYPE__ __val) { __outb(__port, __val); }
__LOCAL __UINT16_TYPE__ (__LIBCCALL outpw)(__UINT16_TYPE__ __port, __UINT16_TYPE__ __val) { __outw(__port, __vall); return __val; }
__LOCAL void (__LIBCCALL outport)(__UINT16_TYPE__ __port, __UINT16_TYPE__ __val) { __outw(__port, __vall); }
#define disable           _disable
#define enable            _enable
#endif /* __i386__ || __x86_64__ */

#endif /* __USE_OLD_DOS */

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
#ifndef SEEK_SET
#define SEEK_SET  0
#define SEEK_CUR  1
#define SEEK_END  2
#endif /* !SEEK_SET */
#endif /* __USE_OLD_DOS */


__SYSDECL_END

#endif /* !_DOS_H */
