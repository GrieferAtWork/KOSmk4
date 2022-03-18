/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: DJGPP        (/include/dos.h) */
/* (#) Portability: MSVC         (/include/dos.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/dos.h) */
/* (#) Portability: Windows Kits (/ucrt/dos.h) */
}

%[insert:prefix(
#include <features.h> /* __USE_OLD_DOS */
)]%{

}%[insert:prefix(
#include <hybrid/host.h> /* __i386__, __x86_64__ */
)]%{

}%[insert:prefix(
#include <bits/crt/_diskfree_t.h>
)]%{

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

}

%[insert:function(_getdiskfree = _getdiskfree, guardName: "_GETDISKFREE_DEFINED")]

%{

#if defined(__i386__) || defined(__x86_64__)
__FORCELOCAL void (_disable)(void) { __cli(); }
__FORCELOCAL void (_enable)(void) { __sti(); }
#endif /* __i386__ || __x86_64__ */

}


%#ifdef __USE_OLD_DOS
%[default:section(".text.crt.dos.system")]

%[insert:guarded_function(delay = _sleep)]

%[insert:function(_dos_getdiskfree = _getdiskfree)]

@@>> sleep(3)
@@Dos-specific prototype for `sleep(3)'
@@This one simply returns void, thus being unable to handle the EINTR-case.
[[cp, guard, exposed_name("sleep")]]
void dos_sleep(unsigned int duration) = sleep;

%[default:section(".text.crt{|.dos}.fs.modify")]
%[insert:extern(unlink)]

%{

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

}
%#endif /* __USE_OLD_DOS */


%{

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

}
