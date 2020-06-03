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

%{
#include <features.h> /* __USE_OLD_DOS */

#include <hybrid/host.h> /* __i386__, __x86_64__ */

#ifdef __USE_OLD_DOS
#include <bits/types.h>
#ifndef SEEK_SET
#include <asm/stdio.h> /* __SEEK_SET, __SEEK_... */
#endif /* !SEEK_SET */
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

}

%#ifndef _GETDISKFREE_DEFINED
%#define _GETDISKFREE_DEFINED 1
%[insert:extern(_getdiskfree)]
%#endif /* !_GETDISKFREE_DEFINED */

%{

#if defined(__i386__) || defined(__x86_64__)
__FORCELOCAL void (__LIBCCALL _disable)(void) { __cli(); }
__FORCELOCAL void (__LIBCCALL _enable)(void) { __sti(); }
#endif /* __i386__ || __x86_64__ */

}


%#ifdef __USE_OLD_DOS
%[default_impl_section(.text.crt.dos.system)]

@@Sleep for `mill' milliseconds (1/1.000 seconds)
[[cp, userimpl, export_alias(__crtSleep)]]
delay:(unsigned int mill) {
	usleep((__useconds_t)__mill * 1000);
}

%[default_impl_section(.text.crt.dos.fs.property)]
_dos_getdiskfree(*) = _getdiskfree;

[[cp, guard, nocrt, alias(_sleep, sleep), exposed_name(sleep)]]
dos_sleep:(unsigned int seconds);

%[default_impl_section(.text.crt.fs.modify)]
%[insert:extern(unlink)]

%{

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

}
%#endif /* __USE_OLD_DOS */


%{

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
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_SET */
#endif /* __USE_OLD_DOS */


__SYSDECL_END

}