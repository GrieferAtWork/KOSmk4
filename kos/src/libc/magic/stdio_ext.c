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
/* (#) Portability: Cygwin        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/stdio_ext.h) */
/* (#) Portability: GNU C Library (/include/stdio_ext.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdio_ext.h) */
/* (#) Portability: diet libc     (/include/stdio_ext.h) */
/* (#) Portability: libc6         (/include/stdio_ext.h) */
/* (#) Portability: musl libc     (/include/stdio_ext.h) */
/* (#) Portability: uClibc        (/include/stdio_ext.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.FILE.utility.ext")]

%{
}%[insert:prefix(
#include <stdio.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <asm/crt/stdio_ext.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

/************************************************************************/
/* Possible values for `__fsetlocking(3)'                               */
/************************************************************************/
/* Don't change the locking type. */
#if !defined(FSETLOCKING_QUERY) && defined(__FSETLOCKING_QUERY)
#define FSETLOCKING_QUERY __FSETLOCKING_QUERY
#endif /* !FSETLOCKING_QUERY && __FSETLOCKING_QUERY */

/* Automatically acquire/release locks during file operators. */
#if !defined(FSETLOCKING_INTERNAL) && defined(__FSETLOCKING_INTERNAL)
#define FSETLOCKING_INTERNAL __FSETLOCKING_INTERNAL
#endif /* !FSETLOCKING_INTERNAL && __FSETLOCKING_INTERNAL */

/* Never automatically acquire  locks. The  only way file  locks are  still
 * acquired is through manual calls to `flockfile(3)' and `funlockfile(3)'.
 * This is the  equivalent of `__USE_STDIO_UNLOCKED'  on a per-file  basis. */
#if !defined(FSETLOCKING_BYCALLER) && defined(__FSETLOCKING_BYCALLER)
#define FSETLOCKING_BYCALLER __FSETLOCKING_BYCALLER
#endif /* !FSETLOCKING_BYCALLER && __FSETLOCKING_BYCALLER */
/************************************************************************/


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

}

@@>> __fbufsize(3)
@@Returns the used buffer size of the given `stream' (s.a. `setvbuf(3)')
@@@return: * : Used buffer size of `stream'
[[pure, wunused, decl_include("<features.h>", "<hybrid/typecore.h>")]]
size_t __fbufsize([[in]] $FILE __KOS_FIXED_CONST *stream);

@@>> __freading(3)
@@Returns  non-zero if the `stream' is read-only, or "the last operation
@@performed on `stream' was a read-operation". On KOS, this last part is
@@implemented such that we check for unsaved changes to `stream'.
[[pure, wunused, decl_include("<features.h>")]]
int __freading([[in]] $FILE __KOS_FIXED_CONST *stream);

@@>> __fwriting(3)
@@Returns non-zero if the `stream'  is "write-only", or "the last  operation
@@performed on `stream' was a write-operation". On KOS, our stdio impl  does
@@not support write-only files (if reading isn't allowed, this will only  be
@@enforced on an fd-level by the kernel). Instead, we implement `__fwriting'
@@to return indicative of `stream' containing any unwritten changes.
[[pure, wunused, decl_include("<features.h>")]]
int __fwriting([[in]] $FILE __KOS_FIXED_CONST *stream);

@@>> __freadable(3)
@@Returns non-zero if `stream'  allows for reading (s.a.  `fread(3)')
@@On  KOS, all stdio files can be  read from (except those opened for
@@file descriptors opened as `O_WRONLY', though in this case write(2)
@@is still attempted). As such, KOS  considers all stdio files to  be
@@readable, meaning that on KOS this function always returns `1'.
[[pure, wunused, decl_include("<features.h>")]]
int __freadable([[in]] $FILE __KOS_FIXED_CONST *stream);

@@>> __fwritable(3)
@@Returns non-zero if `stream' is writable, that is: has been opened
@@with "w",  "r+", or  some similar  flag that  allows for  writing.
[[pure, wunused, decl_include("<features.h>")]]
int __fwritable([[in]] $FILE __KOS_FIXED_CONST *stream);

@@>> __flbf(3)
@@Return  non-zero  if `stream'  is line-buffered.  (s.a. `_IOLBF')
@@Note  that on KOS, the line-buffered attribute of stdio files may
@@be determined  lazily, based  on  an underlying  file  descriptor
@@referring to a TTY. If this is the case, this function will  make
@@the appropriate call to `isatty(3)' and set the internal is-line-
@@buffered flag accordingly, before returning its state.
[[pure, wunused]]
int __flbf([[inout]] $FILE *stream);

@@>> __fpurge(3)
@@Discard all modified, but unwritten data from `stream', as  well
@@as  all unread data previously buffered, but not yet read. After
@@a call to this function, the next `fread(3)' or `fwrite(3)' will
@@start off from a blank state.
[[export_alias("fpurge")]]
void __fpurge([[inout]] $FILE *stream);

@@>> __fpending(3)
@@Returns the number of pending, but not-yet-written bytes of modified
@@file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
@@to write all modified data to the system, and following such a call,
@@this function will return `0' until new unwritten data appears.
[[pure, wunused, decl_include("<features.h>", "<hybrid/typecore.h>")]]
size_t __fpending([[in]] $FILE __KOS_FIXED_CONST *stream);

@@>> _flushlbf(3)
@@Perform  a call  `fflush(stream)' for  every open  line-buffered stdio file.
@@Note that usually call this function isn't necessary, since the same already
@@happens automatically when  writing a line-feed  to any line-buffered  stdio
@@file (where line-buffered files are usually those opened on TTYs)
[[cp_stdio, export_alias("_IO_flush_all_linebuffered")]]
void _flushlbf();

@@>> __fsetlocking(3)
@@Set the locking type for `stream' to `type'. This affects all stdio functions
@@that aren't already lock-less by nature (iow: everything but `*_unlocked(3)')
@@@param: type: One of `FSETLOCKING_*', as defined in `<stdio_ext.h>'
@@@return: * : The locking type prior to this call (one of `FSETLOCKING_INTERNAL' or `FSETLOCKING_BYCALLER')
int __fsetlocking([[inout]] $FILE *stream, int type);

@@>> __fseterr(3)
@@Set the error indicator of `stream', the same an error file error would, such
@@that `ferror(stream) != 0', and `clearerr(stream)' must be used if one wishes
@@to clear the error once again.
void __fseterr([[inout]] $FILE *stream);

%{

__SYSDECL_END
#endif /* __CC__ */

/* Never actually needed */
#ifndef enable_extended_FILE_stdio
#define enable_extended_FILE_stdio(fd, act) 0
#endif /* !enable_extended_FILE_stdio */

}
