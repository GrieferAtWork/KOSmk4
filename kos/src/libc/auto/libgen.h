/* HASH CRC-32:0x38196826 */
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
#ifndef GUARD_LIBC_AUTO_LIBGEN_H
#define GUARD_LIBC_AUTO_LIBGEN_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <libgen.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_RETNONNULL ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_dirname)(char *path);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_RETNONNULL ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBCCALL libc_dirname)(char *path);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_RETNONNULL ATTR_INOUT_OPT(1) char *NOTHROW_NCX(LIBDCALL libd___xpg_basename)(char *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_RETNONNULL ATTR_INOUT_OPT(1) char *NOTHROW_NCX(LIBCCALL libc___xpg_basename)(char *filename);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_INOUT(3) ATTR_IN_OPT(4) ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_bgets)(char *buf, size_t buflen_minus_one, FILE *fp, char __KOS_FIXED_CONST *stop_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_INOUT(3) ATTR_IN_OPT(4) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_bgets)(char *buf, size_t buflen_minus_one, FILE *fp, char __KOS_FIXED_CONST *stop_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_INOUT_OPT(1) ATTR_OUT_OPT(3) size_t NOTHROW_NCX(LIBDCALL libd_bufsplit)(char *string, size_t result_c, char **result_v);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_INOUT_OPT(1) ATTR_OUT_OPT(3) size_t NOTHROW_NCX(LIBCCALL libc_bufsplit)(char *string, size_t result_c, char **result_v);
INTDEF ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_fcopylist_sz)(fd_t fd, size_t *p_filesize);
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_copylist_sz)(char const *filename, size_t *p_filesize);
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_copylist_sz)(char const *filename, size_t *p_filesize);
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
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_RPC(LIBDCALL libd_copylist)(char const *filename, __PIO_OFFSET *p_filesize);
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
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_RPC(LIBCCALL libc_copylist)(char const *filename, __PIO_OFFSET *p_filesize);
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
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_RPC(LIBDCALL libd_copylist64)(char const *filename, __PIO_OFFSET64 *p_filesize);
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
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_RPC(LIBCCALL libc_copylist64)(char const *filename, __PIO_OFFSET64 *p_filesize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcadd(3)
 * Decode C-style escape sequences from `string' and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) + 1'
 * bytes long (the +1 because this function appends a trailing '\0')
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_strcadd)(char *dstbuf, char const *string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strcadd(3)
 * Decode C-style escape sequences from `string' and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) + 1'
 * bytes long (the +1 because this function appends a trailing '\0')
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_strcadd)(char *dstbuf, char const *string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strccpy(3)
 * Same as `strcadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_strccpy)(char *dstbuf, char const *string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strccpy(3)
 * Same as `strcadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_strccpy)(char *dstbuf, char const *string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcadd(3)
 * Encode a given `string' using C-style escape sequences, and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) * 4 + 1' bytes
 * long (the +1 because this function appends a trailing '\0')
 * When non-NULL, characters from `dont_encode' are not encoded, but instead kept as-is.
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_IN_OPT(3) ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_streadd)(char *dstbuf, char const *string, char const *dont_encode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strcadd(3)
 * Encode a given `string' using C-style escape sequences, and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) * 4 + 1' bytes
 * long (the +1 because this function appends a trailing '\0')
 * When non-NULL, characters from `dont_encode' are not encoded, but instead kept as-is.
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_IN_OPT(3) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_streadd)(char *dstbuf, char const *string, char const *dont_encode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strecpy(3)
 * Same as `streadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_IN_OPT(3) ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_strecpy)(char *dstbuf, char const *string, char const *dont_encode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strecpy(3)
 * Same as `streadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_IN_OPT(3) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_strecpy)(char *dstbuf, char const *string, char const *dont_encode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strfind(3)
 * Same as `p = strstr(haystack, needle); p ? p - haystack : -1'
 * @return: * : `needle' found at `haystack + return'
 * @return: -1: `needle' not found in `haystack' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_strfind)(char const *haystack, char const *needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strfind(3)
 * Same as `p = strstr(haystack, needle); p ? p - haystack : -1'
 * @return: * : `needle' found at `haystack + return'
 * @return: -1: `needle' not found in `haystack' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_strfind)(char const *haystack, char const *needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strrspn(3)
 * Scanning from the right, return a pointer to last character in  `haystack'
 * for which `strchr(accept, ch) != NULL'. If `haystack' consists entirely of
 * characters from `accept', re-returns `haystack'. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBDCALL libd_strrspn)(char const *haystack, char const *accept);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strrspn(3)
 * Scanning from the right, return a pointer to last character in  `haystack'
 * for which `strchr(accept, ch) != NULL'. If `haystack' consists entirely of
 * characters from `accept', re-returns `haystack'. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBCCALL libc_strrspn)(char const *haystack, char const *accept);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strtrns(3)
 * Copy `string' to `result'  (including its trailing NUL),  but
 * replace any characters that appear at `find_map[i]' with  the
 * character from `repl_map[i]'. For this purpose, this function
 * assumes that at least the first `strlen(find_map)' characters
 * of `repl_map' can be accessed,  and that the `result'  buffer
 * has space for at least `strlen(string) + 1' characters.
 * @return: result: Always re-returns `result' */
INTDEF ATTR_RETNONNULL ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) ATTR_OUT(4) char *NOTHROW_NCX(LIBDCALL libd_strtrns)(char const *string, char const *find_map, char const *repl_map, char *result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strtrns(3)
 * Copy `string' to `result'  (including its trailing NUL),  but
 * replace any characters that appear at `find_map[i]' with  the
 * character from `repl_map[i]'. For this purpose, this function
 * assumes that at least the first `strlen(find_map)' characters
 * of `repl_map' can be accessed,  and that the `result'  buffer
 * has space for at least `strlen(string) + 1' characters.
 * @return: result: Always re-returns `result' */
INTDEF ATTR_RETNONNULL ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) ATTR_OUT(4) char *NOTHROW_NCX(LIBCCALL libc_strtrns)(char const *string, char const *find_map, char const *repl_map, char *result);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LIBGEN_H */
