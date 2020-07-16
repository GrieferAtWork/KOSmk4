/* HASH CRC-32:0x2ff2abcc */
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
#ifndef __local_fparseln_defined
#define __local_fparseln_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && defined(__CRT_HAVE_realloc)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fgetc from stdio */
#ifndef __local___localdep_fgetc_defined
#define __local___localdep_fgetc_defined 1
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE_getc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE__IO_getc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
__NAMESPACE_LOCAL_END
#include <local/stdio/fgetc.h>
__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
#define __localdep_fgetc __LIBC_LOCAL_NAME(fgetc)
#else /* ... */
#undef __local___localdep_fgetc_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_defined */
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
/* Dependency: getline from stdio */
#ifndef __local___localdep_getline_defined
#define __local___localdep_getline_defined 1
#if defined(__CRT_HAVE_getline_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,__localdep_getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline_unlocked,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,__localdep_getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,__localdep_getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline_unlocked,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getdelim) || defined(__CRT_HAVE_getdelim_unlocked) || defined(__CRT_HAVE___getdelim) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_LOCAL_END
#include <local/stdio/getline.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getline __LIBC_LOCAL_NAME(getline)
#else /* ... */
#undef __local___localdep_getline_defined
#endif /* !... */
#endif /* !__local___localdep_getline_defined */
/* Dependency: malloc from stdlib */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined 1
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
/* Dependency: memcpyc from string */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined 1
#ifdef __CRT_HAVE_memcpyc
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
/* Dependency: memmovedownc from string */
#ifndef __local___localdep_memmovedownc_defined
#define __local___localdep_memmovedownc_defined 1
#ifdef __CRT_HAVE_memmovedownc
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
__NAMESPACE_LOCAL_END
#include <local/string/memmovedownc.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovedownc __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__CRT_HAVE_memmovedownc */
#endif /* !__local___localdep_memmovedownc_defined */
/* Dependency: realloc from stdlib */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#else /* __has_builtin(__builtin_realloc) && __LIBC_BIND_CRTBUILTINS */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#endif /* !__has_builtin(__builtin_realloc) || !__LIBC_BIND_CRTBUILTINS */
#endif /* !__local___localdep_realloc_defined */
/* Dependency: ungetc from stdio */
#ifndef __local___localdep_ungetc_defined
#define __local___localdep_ungetc_defined 1
#if defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc_unlocked)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetc_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
#include <asm/stdio.h>
#include <asm/util.h>
__NAMESPACE_LOCAL_BEGIN
/* Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line, that must be `free(3)'ed by the caller once they are done
 *                  using it.
 *                  The the result would be empty as the result of `feof(stream)' upon
 *                  return of this function, `strdup("")' will be returned. (i.e. NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
__LOCAL_LIBC(fparseln) __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fparseln))(__FILE *__stream, __SIZE_TYPE__ *__plen, __SIZE_TYPE__ *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags) {
	char *__result;
	__SIZE_TYPE__ __result_alloc;
	__SIZE_TYPE__ __result_length;
	char *__linebuf_ptr;
	__SIZE_TYPE__ __linebuf_alloc;
	char __delim_escape   = '\\';
	char __delim_continue = '\\';
	char __delim_comment  = '#';
	if (__delim) {
		__delim_escape   = __delim[0];
		__delim_continue = __delim[1];
		__delim_comment  = __delim[2];
	}
	__result        = __NULLPTR;
	__result_alloc  = 0;
	__result_length = 0;
	__linebuf_ptr   = __NULLPTR;
	__linebuf_alloc = 0;
	for (;;) {
		__SSIZE_TYPE__ __line_len;
		__SIZE_TYPE__ __i;
__again_getline:
		__line_len = __localdep_getline(&__linebuf_ptr, &__linebuf_alloc, __stream);
		if __unlikely(__line_len < 0)
			goto __err;
		if (!__line_len)
			break; /* End-of-file! */
		if (__plineno)
			++*__plineno;
		/* Scan the read line for abnormalities */
		for (__i = 0;; ++__i) {
			char __ch;
__again_scan_linech_at_i:
			if (__i >= (__SIZE_TYPE__)__line_len) {
__apped_current_line_and_stop:
				__stream = __NULLPTR; /* Cause `apped_current_line_and_continue_or_stop' to stop scanning. */
				goto __apped_current_line_and_continue_or_stop;
			}
			__ch = __linebuf_ptr[__i];
			if (__ch == __delim_escape && __delim_escape) {
				++__i;
				if (__i >= (__SIZE_TYPE__)__line_len)
					goto __apped_current_line_and_stop;
				__ch = __linebuf_ptr[__i];
				if (__ch == __delim_escape && (__flags & __FPARSELN_UNESCESC)) {
__do_erase_character_preceding_i_without_rescan:
					__localdep_memmovedownc(&__linebuf_ptr[__i - 1],
					             &__linebuf_ptr[__i],
					             (__SIZE_TYPE__)__line_len - __i,
					             sizeof(char));
					--__line_len;
					goto __again_scan_linech_at_i;
				}
				if (__ch == '\n' && (__flags & __FPARSELN_UNESCCONT) &&
				    __delim_escape == __delim_continue) {
					/* Escaped line-feed */
					--__i;
__deleted_escaped_newline_starting_at_i:
					__line_len -= 2;
					__localdep_memmovedownc(&__linebuf_ptr[__i],
					             &__linebuf_ptr[__i + 2],
					             (__SIZE_TYPE__)__line_len - __i,
					             sizeof(char));
__continue_line_if_i_at_line_len:
					if __likely(__i >= (__SIZE_TYPE__)__line_len) {
__apped_current_line_and_continue_or_stop:
						if (!__result) {
							/* Simple case: Inherit the already-allocated buffer from getline() */
							__result        = __linebuf_ptr;
							__result_alloc  = __linebuf_alloc;
							__result_length = (__SIZE_TYPE__)__line_len;
							__linebuf_ptr   = __NULLPTR;
							__linebuf_alloc = 0;
						} else {
							__SIZE_TYPE__ __total_length;
							/* Complicated case: Must append the line returned by `getline()' onto `result' */
							__total_length = __result_length + (__SIZE_TYPE__)__line_len;
							if (__total_length > __result_alloc) {
								char *__new_result;
								__SIZE_TYPE__ __new_alloc = __result_alloc * 2;
								if (__new_alloc < __total_length)
									__new_alloc = __total_length + 1;
								__new_result = (char *)__localdep_realloc(__result, __new_alloc * sizeof(char));
								if __unlikely(!__new_result) {
									__new_alloc = __total_length + 1;
									__new_result = (char *)__localdep_realloc(__result, __new_alloc * sizeof(char));
									if __unlikely(!__new_result)
										goto __err;
								}
								__result       = __new_result;
								__result_alloc = __new_alloc;
							}
							__localdep_memcpyc(__result + __result_length, __linebuf_ptr,
							        (__SIZE_TYPE__)__line_len, sizeof(char));
							__result_length = __total_length;
						}
						/* `stream' is set to NULL to indicate that we're to stop scanning! */
						if (!__stream)
							goto __got_result;
						goto __again_getline;
					}
					goto __again_scan_linech_at_i;
				}
				/* Check if we're still supposed to unescape this character. */
				if ((__flags & __FPARSELN_UNESCREST) ||
				    ((__flags & __FPARSELN_UNESCCOMM) && __ch == __delim_comment && __delim_comment))
					goto __do_erase_character_preceding_i_without_rescan;
				continue;
			}
			if (__ch == __delim_continue && (__i + 1) < (__SIZE_TYPE__)__line_len &&
			    __linebuf_ptr[__i + 1] == '\n' && __delim_continue) {
				if (__flags & __FPARSELN_UNESCCONT)
					goto __deleted_escaped_newline_starting_at_i;
				++__i;
				goto __continue_line_if_i_at_line_len;
			}
			if (__ch == __delim_comment && __delim_comment) {
				/* Got it! - The line actually stops here! */
				/* Check for special case: Escaped line-feed at the end of a comment */
				if ((__SIZE_TYPE__)__line_len >= 2 && __delim_continue &&
				    __linebuf_ptr[(__SIZE_TYPE__)__line_len - 2] == __delim_continue &&
				    __linebuf_ptr[(__SIZE_TYPE__)__line_len - 1] == '\n') {
					/* Must keep on scanning (and discarding characters) until after
					 * the next unescaped line-feed. Note that to prevent additional
					 * heap allocations, we use fgetc() for this, rather than getline(),
					 * though because of this we must still account for all 3 types of
					 * linefeeds that exist.
					 * HINT: Right now, the previous call to getline() will have left
					 *       the given `stream' pointed at the first character of the
					 *       line succeeding the one returned by getline()! */
					for (;;) {
						int __comment_ch = __localdep_fgetc(__stream);
__again_check_ch_in_comment:
						if (__comment_ch == __EOF)
							break; /* end-of-file */
						if (__comment_ch == __delim_escape && __delim_escape) {
							__comment_ch = __localdep_fgetc(__stream);
							if (__comment_ch == '\r' || __comment_ch == '\n') {
								if (__plineno)
									++*__plineno;
								if (__comment_ch == '\r') {
									__comment_ch = __localdep_fgetc(__stream);
									if (__comment_ch != '\n')
										__localdep_ungetc(__comment_ch, __stream);
								}
								if (__delim_escape == __delim_continue)
									continue;
								break;
							}
							continue;
						}
						if (__comment_ch == __delim_continue && __delim_continue) {
							__comment_ch = __localdep_fgetc(__stream);
							if (__comment_ch == '\r' || __comment_ch == '\n') {
								if (__plineno)
									++*__plineno;
								if (__comment_ch == '\r') {
									__comment_ch = __localdep_fgetc(__stream);
									if (__comment_ch != '\n')
										__localdep_ungetc(__comment_ch, __stream);
								}
								continue; /* Escaped line-feed */
							}
							goto __again_check_ch_in_comment;
						}
						if (__comment_ch == '\n') {
__do_increment_lineno_and_break_comment:
							if (__plineno)
								++*__plineno;
							break;
						}
						if (__comment_ch == '\r') {
							__comment_ch = __localdep_fgetc(__stream);
							if (__comment_ch != '\n')
								__localdep_ungetc(__comment_ch, __stream);
							goto __do_increment_lineno_and_break_comment;
						}
					}
				}
				__line_len = (__SSIZE_TYPE__)__i;
				goto __apped_current_line_and_stop;
			}
		}
	}
__got_result:
	/* Special case: Nothing was read (this can
	 * happen if `stream' was at its EOF location) */
	if __unlikely(!__result) {
		__result_length = 0;
		if __likely(__linebuf_ptr) {
			__result       = __linebuf_ptr;
			__result_alloc = __linebuf_alloc;
			__linebuf_ptr  = __NULLPTR;
			/*linebuf_alloc = 0;*/ /* Not needed */
		} else {

			__result = (char *)__localdep_malloc(sizeof(char));



			if __unlikely(!__result)
				goto __done;
			__result_alloc = 1;
		}
	}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	__localdep_free(__linebuf_ptr);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	/* Trim a potential trailing line-feed */
	if (__result_length && __result[__result_length - 1] == '\n')
		--__result_length;
	/* Finalize the resulting buffer. */
	if (__result_length + 1 < __result_alloc) {
		/* Try to release unused memory. */
		char *__new_result;
		__new_result = (char *)__localdep_realloc(__result,
		                             (__result_length + 1) *
		                             sizeof(char));
		if __likely(__new_result)
			__result = __new_result;
	}
	/* Ensure NUL-termination */
	__result[__result_length] = '\0';
	if (__plen)
		*__plen = __result_length;
__done:
	return __result;
__err:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	__localdep_free(__linebuf_ptr);
	__localdep_free(__result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fparseln_defined
#define __local___localdep_fparseln_defined 1
#define __localdep_fparseln __LIBC_LOCAL_NAME(fparseln)
#endif /* !__local___localdep_fparseln_defined */
#else /* (__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && __CRT_HAVE_realloc */
#undef __local_fparseln_defined
#endif /* (!__CRT_HAVE_fgetc && !__CRT_HAVE_getc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock && !__CRT_HAVE__IO_fread) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || !__CRT_HAVE_realloc */
#endif /* !__local_fparseln_defined */
