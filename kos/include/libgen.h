/* HASH CRC-32:0x57de2fb */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/libgen.h) */
/* (#) Portability: DragonFly BSD (/include/libgen.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/libgen.h) */
/* (#) Portability: FreeBSD       (/include/libgen.h) */
/* (#) Portability: GNU C Library (/misc/libgen.h) */
/* (#) Portability: GNU Hurd      (/usr/include/libgen.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/libgen.h) */
/* (#) Portability: NetBSD        (/include/libgen.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/libgen.h) */
/* (#) Portability: OpenBSD       (/include/libgen.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libgen.h) */
/* (#) Portability: diet libc     (/include/libgen.h) */
/* (#) Portability: libc6         (/include/libgen.h) */
/* (#) Portability: mintlib       (/include/libgen.h) */
/* (#) Portability: musl libc     (/include/libgen.h) */
/* (#) Portability: uClibc        (/include/libgen.h) */
#ifndef _LIBGEN_H
#define _LIBGEN_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_dirname
/* Return the directory, that is everything leading up to, but not
 * including the last slash of `path'. If no such path exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> dirname("/usr/include///"); // Returns "/usr"
 * >> dirname("/usr/include/");   // Returns "/usr"
 * >> dirname("/usr/include");    // Returns "/usr"
 * >> dirname("/usr/");           // Returns "/"
 * >> dirname("/usr");            // Returns "/"
 * >> dirname("/");               // Returns "/"
 * >> dirname("///");             // Returns "/"
 * >> dirname("foo/bar/");        // Returns "foo"
 * >> dirname("foo/bar");         // Returns "foo"
 * >> dirname("foo/");            // Returns "."
 * >> dirname("foo");             // Returns "."
 * >> dirname(".");               // Returns "."
 * >> dirname("..");              // Returns "."
 * >> dirname("");                // Returns "."
 * >> dirname(NULL);              // Returns "."
 * Note  that for this purpose, `path' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,dirname,(char *__path),(__path))
#else /* __CRT_HAVE_dirname */
#include <libc/local/libgen/dirname.h>
/* Return the directory, that is everything leading up to, but not
 * including the last slash of `path'. If no such path exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> dirname("/usr/include///"); // Returns "/usr"
 * >> dirname("/usr/include/");   // Returns "/usr"
 * >> dirname("/usr/include");    // Returns "/usr"
 * >> dirname("/usr/");           // Returns "/"
 * >> dirname("/usr");            // Returns "/"
 * >> dirname("/");               // Returns "/"
 * >> dirname("///");             // Returns "/"
 * >> dirname("foo/bar/");        // Returns "foo"
 * >> dirname("foo/bar");         // Returns "foo"
 * >> dirname("foo/");            // Returns "."
 * >> dirname("foo");             // Returns "."
 * >> dirname(".");               // Returns "."
 * >> dirname("..");              // Returns "."
 * >> dirname("");                // Returns "."
 * >> dirname(NULL);              // Returns "."
 * Note  that for this purpose, `path' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string. */
__NAMESPACE_LOCAL_USING_OR_IMPL(dirname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN_OPT(1) char *__NOTHROW_NCX(__LIBCCALL dirname)(char *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dirname))(__path); })
#endif /* !__CRT_HAVE_dirname */
#ifdef __CRT_HAVE___xpg_basename
/* Return the filename-part, that is everything following
 * the last slash of `filename'. If no such part exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> basename("/usr/include///"); // Returns "include"
 * >> basename("/usr/include/");   // Returns "include"
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns "usr"
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns "/"
 * >> basename("///");             // Returns "/"
 * >> basename("foo/bar/");        // Returns "bar"
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns "foo"
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns "."
 * >> basename(NULL);              // Returns "."
 * Note that for this purpose, `filename' may be modified in-place, meaning
 * that  you should really  always pass an  strdup()'d, or writable string.
 *
 * Also note that a different version of this function exists in <string.h>,
 * where if you  include both  <libgen.h> and  <string.h>, you  can use  the
 * alternate function from <string.h>  by `#undef basename', or calling  the
 * function as `(basename)(...)' (as opposed to `basename(...)') */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__xpg_basename,(char *__filename),(__filename))
#elif defined(__CRT_HAVE___gnu_basename)
/* Return the filename-part, that is everything following
 * the last slash of `filename'. If no such part exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> basename("/usr/include///"); // Returns "include"
 * >> basename("/usr/include/");   // Returns "include"
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns "usr"
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns "/"
 * >> basename("///");             // Returns "/"
 * >> basename("foo/bar/");        // Returns "bar"
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns "foo"
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns "."
 * >> basename(NULL);              // Returns "."
 * Note that for this purpose, `filename' may be modified in-place, meaning
 * that  you should really  always pass an  strdup()'d, or writable string.
 *
 * Also note that a different version of this function exists in <string.h>,
 * where if you  include both  <libgen.h> and  <string.h>, you  can use  the
 * alternate function from <string.h>  by `#undef basename', or calling  the
 * function as `(basename)(...)' (as opposed to `basename(...)') */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__xpg_basename,(char *__filename),__gnu_basename,(__filename))
#else /* ... */
#include <libc/local/libgen/__xpg_basename.h>
/* Return the filename-part, that is everything following
 * the last slash of `filename'. If no such part exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> basename("/usr/include///"); // Returns "include"
 * >> basename("/usr/include/");   // Returns "include"
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns "usr"
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns "/"
 * >> basename("///");             // Returns "/"
 * >> basename("foo/bar/");        // Returns "bar"
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns "foo"
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns "."
 * >> basename(NULL);              // Returns "."
 * Note that for this purpose, `filename' may be modified in-place, meaning
 * that  you should really  always pass an  strdup()'d, or writable string.
 *
 * Also note that a different version of this function exists in <string.h>,
 * where if you  include both  <libgen.h> and  <string.h>, you  can use  the
 * alternate function from <string.h>  by `#undef basename', or calling  the
 * function as `(basename)(...)' (as opposed to `basename(...)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(__xpg_basename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT_OPT(1) char *__NOTHROW_NCX(__LIBCCALL __xpg_basename)(char *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__xpg_basename))(__filename); })
#endif /* !... */
#define basename(path) __xpg_basename(path)

#ifdef __USE_SOLARIS
#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t;
#endif /* !__mode_t_defined */

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#ifdef __CRT_HAVE_bgets
/* >> bgets(3)
 * Read at most `buflen_minus_one' characters from `fp' and into `buf'
 * Afterwards, a trailing  NUL-character is appended  to `buf'  (hence
 * the `minus_one' in  `buflen_minus_one'). Stop  reading (and  append
 * the trailing NUL) once `fgetc(fp) == EOF', or `fgetc(fp)' returns a
 * character from `stop_chars'. In this last case, the read  character
 * is NOT ungetc'd, meaning it will be lost.
 * @param: buf:   Output buffer. (Assuming success), this function always
 *                writes at least  `1' (trailing NUL)  character to  this
 *                buffer.
 * @return: NULL: `buflen_minus_one != 0', and the  first character  read
 *                from `fp' was `EOF'. The case where the first character
 *                read is in `stop_chars' doesn't cause a NULL-return.
 * @return: * :   Returns a pointer to the trailing NUL written to `buf'
 *                There is no true error  case; read errors are  treated
 *                the same way as end-of-file. */
__CDECLARE(__ATTR_INOUT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1),char *,__NOTHROW_NCX,bgets,(char *__buf, size_t __buflen_minus_one, FILE *__fp, char __KOS_FIXED_CONST *__stop_chars),(__buf,__buflen_minus_one,__fp,__stop_chars))
#elif defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/libgen/bgets.h>
/* >> bgets(3)
 * Read at most `buflen_minus_one' characters from `fp' and into `buf'
 * Afterwards, a trailing  NUL-character is appended  to `buf'  (hence
 * the `minus_one' in  `buflen_minus_one'). Stop  reading (and  append
 * the trailing NUL) once `fgetc(fp) == EOF', or `fgetc(fp)' returns a
 * character from `stop_chars'. In this last case, the read  character
 * is NOT ungetc'd, meaning it will be lost.
 * @param: buf:   Output buffer. (Assuming success), this function always
 *                writes at least  `1' (trailing NUL)  character to  this
 *                buffer.
 * @return: NULL: `buflen_minus_one != 0', and the  first character  read
 *                from `fp' was `EOF'. The case where the first character
 *                read is in `stop_chars' doesn't cause a NULL-return.
 * @return: * :   Returns a pointer to the trailing NUL written to `buf'
 *                There is no true error  case; read errors are  treated
 *                the same way as end-of-file. */
__NAMESPACE_LOCAL_USING_OR_IMPL(bgets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL bgets)(char *__buf, size_t __buflen_minus_one, FILE *__fp, char __KOS_FIXED_CONST *__stop_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bgets))(__buf, __buflen_minus_one, __fp, __stop_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_bufsplit
/* >> bufsplit(3)
 * Split `string' on field-separator characters (by default "\t" or  "\n"),
 * replacing  those characters with  '\0'. The produced  list of strings is
 * then stored in up to `result_c' pointers of `result_v', with the  actual
 * number  of produced  strings returned  (any unused  trailing pointers of
 * `result_v' are  filled  with  the  empty  string  at  `strend(string)').
 * In  case `string' contains  more than `result_c'  fields, only the first
 * `result_c' fields are actually split and `result_v[result_c-1]' contains
 * the remaining of `string', including any unsplit trailing fields.
 *
 * The set of characters used as field-separators can also be changed  for
 * this function in a  call `bufsplit(NEW_FIELDS, 0, NULL)'. Note that  in
 * this case, `string' must remain  allocated and usable until fields  are
 * changed yet again. There is no way to reset the default ("\t\n") set of
 * field separator characters.
 *
 * @return: * : The number of  field strings extracted  from `string'  and
 *              stored in `result_v'. All remaining pointers in `result_v'
 *              beyond `return' (and  before `result_c')  are filled  with
 *              the empty string found at `strend(IN:string)'. */
__CDECLARE(__ATTR_INOUT_OPT(1) __ATTR_OUT_OPT(3),size_t,__NOTHROW_NCX,bufsplit,(char *__string, size_t __result_c, char **__result_v),(__string,__result_c,__result_v))
#else /* __CRT_HAVE_bufsplit */
#include <libc/local/libgen/bufsplit.h>
/* >> bufsplit(3)
 * Split `string' on field-separator characters (by default "\t" or  "\n"),
 * replacing  those characters with  '\0'. The produced  list of strings is
 * then stored in up to `result_c' pointers of `result_v', with the  actual
 * number  of produced  strings returned  (any unused  trailing pointers of
 * `result_v' are  filled  with  the  empty  string  at  `strend(string)').
 * In  case `string' contains  more than `result_c'  fields, only the first
 * `result_c' fields are actually split and `result_v[result_c-1]' contains
 * the remaining of `string', including any unsplit trailing fields.
 *
 * The set of characters used as field-separators can also be changed  for
 * this function in a  call `bufsplit(NEW_FIELDS, 0, NULL)'. Note that  in
 * this case, `string' must remain  allocated and usable until fields  are
 * changed yet again. There is no way to reset the default ("\t\n") set of
 * field separator characters.
 *
 * @return: * : The number of  field strings extracted  from `string'  and
 *              stored in `result_v'. All remaining pointers in `result_v'
 *              beyond `return' (and  before `result_c')  are filled  with
 *              the empty string found at `strend(IN:string)'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(bufsplit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __ATTR_OUT_OPT(3) size_t __NOTHROW_NCX(__LIBCCALL bufsplit)(char *__string, size_t __result_c, char **__result_v) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bufsplit))(__string, __result_c, __result_v); })
#endif /* !__CRT_HAVE_bufsplit */
#if defined(__CRT_HAVE_copylist) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_RPC,copylist,(char const *__filename, __PIO_OFFSET *__p_filesize),(__filename,__p_filesize))
#elif defined(__CRT_HAVE_copylist64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_RPC,copylist,(char const *__filename, __PIO_OFFSET *__p_filesize),copylist64,(__filename,__p_filesize))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_copylist64) && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/libgen/copylist.h>
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
__NAMESPACE_LOCAL_USING_OR_IMPL(copylist, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_RPC(__LIBCCALL copylist)(char const *__filename, __PIO_OFFSET *__p_filesize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copylist))(__filename, __p_filesize); })
#endif /* (__CRT_HAVE_copylist64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_copylist) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_RPC,copylist64,(char const *__filename, __PIO_OFFSET64 *__p_filesize),copylist,(__filename,__p_filesize))
#elif defined(__CRT_HAVE_copylist64)
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_RPC,copylist64,(char const *__filename, __PIO_OFFSET64 *__p_filesize),(__filename,__p_filesize))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/libgen/copylist64.h>
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
__NAMESPACE_LOCAL_USING_OR_IMPL(copylist64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_RPC(__LIBCCALL copylist64)(char const *__filename, __PIO_OFFSET64 *__p_filesize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copylist64))(__filename, __p_filesize); })
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#ifndef __eaccess_defined
#define __eaccess_defined
#ifdef __CRT_HAVE_euidaccess
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),euidaccess,(__file,__type))
#elif defined(__CRT_HAVE_eaccess)
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE__access) && defined(__CRT_DOS)
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <libc/local/unistd/euidaccess.h>
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL eaccess)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(euidaccess))(__file, __type); }
#else /* __AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#undef __eaccess_defined
#endif /* !__AT_FDCWD || !__AT_EACCESS || !__CRT_HAVE_faccessat */
#endif /* !... */
#endif /* !__eaccess_defined */
#ifdef __CRT_HAVE_strcadd
/* >> strcadd(3)
 * Decode C-style escape sequences from `string' and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) + 1'
 * bytes long (the +1 because this function appends a trailing '\0')
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,strcadd,(char *__dstbuf, char const *__string),(__dstbuf,__string))
#else /* __CRT_HAVE_strcadd */
#include <libc/local/libgen/strcadd.h>
/* >> strcadd(3)
 * Decode C-style escape sequences from `string' and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) + 1'
 * bytes long (the +1 because this function appends a trailing '\0')
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcadd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL strcadd)(char *__dstbuf, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcadd))(__dstbuf, __string); })
#endif /* !__CRT_HAVE_strcadd */
#ifdef __CRT_HAVE_strccpy
/* >> strccpy(3)
 * Same as `strcadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,strccpy,(char *__dstbuf, char const *__string),(__dstbuf,__string))
#else /* __CRT_HAVE_strccpy */
#include <libc/local/libgen/strccpy.h>
/* >> strccpy(3)
 * Same as `strcadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strccpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL strccpy)(char *__dstbuf, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strccpy))(__dstbuf, __string); })
#endif /* !__CRT_HAVE_strccpy */
#ifdef __CRT_HAVE_streadd
/* >> strcadd(3)
 * Encode a given `string' using C-style escape sequences, and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) * 4 + 1' bytes
 * long (the +1 because this function appends a trailing '\0')
 * When non-NULL, characters from `dont_encode' are not encoded, but instead kept as-is.
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_OUT(1),char *,__NOTHROW_NCX,streadd,(char *__dstbuf, char const *__string, char const *__dont_encode),(__dstbuf,__string,__dont_encode))
#else /* __CRT_HAVE_streadd */
#include <libc/local/libgen/streadd.h>
/* >> strcadd(3)
 * Encode a given `string' using C-style escape sequences, and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) * 4 + 1' bytes
 * long (the +1 because this function appends a trailing '\0')
 * When non-NULL, characters from `dont_encode' are not encoded, but instead kept as-is.
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(streadd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL streadd)(char *__dstbuf, char const *__string, char const *__dont_encode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(streadd))(__dstbuf, __string, __dont_encode); })
#endif /* !__CRT_HAVE_streadd */
#ifdef __CRT_HAVE_strecpy
/* >> strecpy(3)
 * Same as `streadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_OUT(1),char *,__NOTHROW_NCX,strecpy,(char *__dstbuf, char const *__string, char const *__dont_encode),(__dstbuf,__string,__dont_encode))
#else /* __CRT_HAVE_strecpy */
#include <libc/local/libgen/strecpy.h>
/* >> strecpy(3)
 * Same as `streadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strecpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL strecpy)(char *__dstbuf, char const *__string, char const *__dont_encode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strecpy))(__dstbuf, __string, __dont_encode); })
#endif /* !__CRT_HAVE_strecpy */
#ifdef __CRT_HAVE_strfind
/* >> strfind(3)
 * Same as `p = strstr(haystack, needle); p ? p - haystack : -1'
 * @return: * : `needle' found at `haystack + return'
 * @return: -1: `needle' not found in `haystack' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,strfind,(char const *__haystack, char const *__needle),(__haystack,__needle))
#else /* __CRT_HAVE_strfind */
#include <libc/local/libgen/strfind.h>
/* >> strfind(3)
 * Same as `p = strstr(haystack, needle); p ? p - haystack : -1'
 * @return: * : `needle' found at `haystack + return'
 * @return: -1: `needle' not found in `haystack' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strfind, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL strfind)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strfind))(__haystack, __needle); })
#endif /* !__CRT_HAVE_strfind */
#ifdef __CRT_HAVE_strrspn
/* >> strrspn(3)
 * Scanning from the right, return a pointer to last character in  `haystack'
 * for which `strchr(accept, ch) != NULL'. If `haystack' consists entirely of
 * characters from `accept', re-returns `haystack'. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strrspn,(char const *__haystack, char const *__accept),(__haystack,__accept))
#else /* __CRT_HAVE_strrspn */
#include <libc/local/libgen/strrspn.h>
/* >> strrspn(3)
 * Scanning from the right, return a pointer to last character in  `haystack'
 * for which `strchr(accept, ch) != NULL'. If `haystack' consists entirely of
 * characters from `accept', re-returns `haystack'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strrspn)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrspn))(__haystack, __accept); })
#endif /* !__CRT_HAVE_strrspn */
#ifdef __CRT_HAVE_strtrns
/* >> strtrns(3)
 * Copy `string' to `result'  (including its trailing NUL),  but
 * replace any characters that appear at `find_map[i]' with  the
 * character from `repl_map[i]'. For this purpose, this function
 * assumes that at least the first `strlen(find_map)' characters
 * of `repl_map' can be accessed,  and that the `result'  buffer
 * has space for at least `strlen(string) + 1' characters.
 * @return: result: Always re-returns `result' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3) __ATTR_OUT(4),char *,__NOTHROW_NCX,strtrns,(char const *__string, char const *__find_map, char const *__repl_map, char *__result),(__string,__find_map,__repl_map,__result))
#else /* __CRT_HAVE_strtrns */
#include <libc/local/libgen/strtrns.h>
/* >> strtrns(3)
 * Copy `string' to `result'  (including its trailing NUL),  but
 * replace any characters that appear at `find_map[i]' with  the
 * character from `repl_map[i]'. For this purpose, this function
 * assumes that at least the first `strlen(find_map)' characters
 * of `repl_map' can be accessed,  and that the `result'  buffer
 * has space for at least `strlen(string) + 1' characters.
 * @return: result: Always re-returns `result' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtrns, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3) __ATTR_OUT(4) char *__NOTHROW_NCX(__LIBCCALL strtrns)(char const *__string, char const *__find_map, char const *__repl_map, char *__result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtrns))(__string, __find_map, __repl_map, __result); })
#endif /* !__CRT_HAVE_strtrns */
#endif /* __USE_SOLARIS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBGEN_H */
