/* HASH CRC-32:0x9d91c16e */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/mntent.h) */
/* (#) Portability: DJGPP         (/include/mntent.h) */
/* (#) Portability: GNU C Library (/misc/mntent.h) */
/* (#) Portability: GNU Hurd      (/usr/include/mntent.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/mntent.h) */
/* (#) Portability: diet libc     (/include/mntent.h) */
/* (#) Portability: libc4/5       (/include/mntent.h) */
/* (#) Portability: libc6         (/include/mntent.h) */
/* (#) Portability: mintlib       (/include/mntent.h) */
/* (#) Portability: musl libc     (/include/mntent.h) */
/* (#) Portability: uClibc        (/include/mntent.h) */
#ifndef _MNTENT_H
#define _MNTENT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <paths.h>
#include <kos/anno.h>
#include <bits/crt/db/mntent.h>


/* Filename for the mounting-point table (/etc/fstab) */
#define MNTTAB _PATH_MNTTAB /* Deprecated alias. */

/* Filename for currently mounted filesystems (/proc/self/mounts) */
#define MOUNTED _PATH_MOUNTED /* Deprecated alias. */

/* Some filesystem type names. */
#define MNTTYPE_IGNORE "ignore" /* Ignore this entry. */
#define MNTTYPE_NFS    "nfs"    /* Network file system. */
#define MNTTYPE_SWAP   "swap"   /* Swap device. */

/* Some filesystem mount options. */
#define MNTOPT_DEFAULTS "defaults" /* Default options */
#define MNTOPT_RO       "ro"       /* Read-only file access.            (s.a. `ST_RDONLY') */
#define MNTOPT_RW       "rw"       /* Read/write file access.           (s.a. `ST_RDONLY') */
#define MNTOPT_SUID     "suid"     /* Allow `S_ISUID' and `S_ISGID'.    (s.a. `ST_NOSUID') */
#define MNTOPT_NOSUID   "nosuid"   /* Disallow `S_ISUID' and `S_ISGID'. (s.a. `ST_NOSUID') */
#define MNTOPT_NOAUTO   "noauto"   /* Don't auto-mount.                 (s.a. `mount -a') */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

#ifdef __CRT_HAVE_setmntent
/* >> setmntent(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),(__file,__mode))
#elif defined(__CRT_HAVE___setmntent)
/* >> setmntent(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),__setmntent,(__file,__mode))
#elif defined(__CRT_HAVE_fopen)
/* >> setmntent(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),fopen,(__file,__mode))
#elif defined(__CRT_HAVE__IO_fopen)
/* >> setmntent(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),_IO_fopen,(__file,__mode))
#elif defined(__CRT_HAVE_fopen64)
/* >> setmntent(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),fopen64,(__file,__mode))
#endif /* ... */
#ifdef __CRT_HAVE_endmntent
/* >> endmntent(3) */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE___endmntent)
/* >> endmntent(3) */
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),__endmntent,(__stream))
#elif defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
#include <libc/local/mntent/endmntent.h>
/* >> endmntent(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(endmntent, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_RPC_NOKOS(__LIBCCALL endmntent)(__FILE *__stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(endmntent))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_getmntent
/* >> getmntent(3), getmntent_r(3) */
__CDECLARE(__ATTR_INOUT(1),struct mntent *,__NOTHROW_CB_NCX,getmntent,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE_getmntent_r) || defined(__CRT_HAVE___getmntent_r) || defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
#include <libc/local/mntent/getmntent.h>
/* >> getmntent(3), getmntent_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getmntent, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) struct mntent *__NOTHROW_CB_NCX(__LIBCCALL getmntent)(__FILE *__stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getmntent))(__stream); })
#endif /* ... */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_getmntent_r
/* >> getmntent(3), getmntent_r(3) */
__CDECLARE(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUTS(3, 4),struct mntent *,__NOTHROW_CB_NCX,getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),(__stream,__result,__buffer,__bufsize))
#elif defined(__CRT_HAVE___getmntent_r)
/* >> getmntent(3), getmntent_r(3) */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUTS(3, 4),struct mntent *,__NOTHROW_CB_NCX,getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),__getmntent_r,(__stream,__result,__buffer,__bufsize))
#elif defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
#include <libc/local/mntent/getmntent_r.h>
/* >> getmntent(3), getmntent_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getmntent_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUTS(3, 4) struct mntent *__NOTHROW_CB_NCX(__LIBCCALL getmntent_r)(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getmntent_r))(__stream, __result, __buffer, __bufsize); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __CRT_HAVE_addmntent
/* >> addmntent(3)
 * Append a  line  `"%s %s %s %s %d %d\n"  %  (mnt_fsname,  mnt_dir,
 * mnt_type, mnt_opts, mnt_freq, mnt_passno)' to the end of `stream'
 * @return: 0: Success
 * @return: 1: Error (WARNING: `errno' is left undefined) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,addmntent,(__FILE *__restrict __stream, struct mntent const *__restrict __mnt),(__stream,__mnt))
#else /* __CRT_HAVE_addmntent */
#include <asm/os/stdio.h>
#include <bits/types.h>
#if defined(__SEEK_END) && (defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock)) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/mntent/addmntent.h>
/* >> addmntent(3)
 * Append a  line  `"%s %s %s %s %d %d\n"  %  (mnt_fsname,  mnt_dir,
 * mnt_type, mnt_opts, mnt_freq, mnt_passno)' to the end of `stream'
 * @return: 0: Success
 * @return: 1: Error (WARNING: `errno' is left undefined) */
__NAMESPACE_LOCAL_USING_OR_IMPL(addmntent, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_CB_NCX(__LIBCCALL addmntent)(__FILE *__restrict __stream, struct mntent const *__restrict __mnt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(addmntent))(__stream, __mnt); })
#endif /* __SEEK_END && (__CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock) && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) */
#endif /* !__CRT_HAVE_addmntent */
#ifdef __CRT_HAVE_hasmntopt
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_IN_OPT(2),char *,__NOTHROW_NCX,hasmntopt,(struct mntent const *__mnt, char const *__opt),(__mnt,__opt))
#else /* __CRT_HAVE_hasmntopt */
#include <libc/local/mntent/hasmntopt.h>
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
__NAMESPACE_LOCAL_USING_OR_IMPL(hasmntopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) char *__NOTHROW_NCX(__LIBCCALL hasmntopt)(struct mntent const *__mnt, char const *__opt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hasmntopt))(__mnt, __opt); })
#endif /* !__CRT_HAVE_hasmntopt */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_MNTENT_H */
