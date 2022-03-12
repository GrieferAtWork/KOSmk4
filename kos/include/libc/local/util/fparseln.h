/* HASH CRC-32:0xf0ed73c7 */
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
#ifndef __local_fparseln_defined
#define __local_fparseln_defined
#include <__crt.h>
#include <features.h>
#if (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc_defined
#define __local___localdep_fgetc_defined
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetc __LIBC_LOCAL_NAME(fgetc)
#else /* ... */
#undef __local___localdep_fgetc_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_getline_defined
#define __local___localdep_getline_defined
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
#elif defined(__CRT_HAVE___getline)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,__localdep_getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),__getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE__IO_getline)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,__localdep_getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),_IO_getline,(__lineptr,__pcount,__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/getline.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getline __LIBC_LOCAL_NAME(getline)
#endif /* !... */
#endif /* !__local___localdep_getline_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
#ifndef __local___localdep_memmovedownc_defined
#define __local___localdep_memmovedownc_defined
#ifdef __CRT_HAVE_memmovedownc
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovedownc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovedownc __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__CRT_HAVE_memmovedownc */
#endif /* !__local___localdep_memmovedownc_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_ungetc_defined
#define __local___localdep_ungetc_defined
#if defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetc_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
#include <asm/os/stdio.h>
#include <asm/crt/util.h>
__NAMESPACE_LOCAL_BEGIN
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
		__line_len = (__NAMESPACE_LOCAL_SYM __localdep_getline)(&__linebuf_ptr, &__linebuf_alloc, __stream);
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
					(__NAMESPACE_LOCAL_SYM __localdep_memmovedownc)(&__linebuf_ptr[__i - 1],
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
					(__NAMESPACE_LOCAL_SYM __localdep_memmovedownc)(&__linebuf_ptr[__i],
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
								__new_result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __new_alloc * sizeof(char));
								if __unlikely(!__new_result) {
									__new_alloc = __total_length + 1;
									__new_result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __new_alloc * sizeof(char));
									if __unlikely(!__new_result)
										goto __err;
								}
								__result       = __new_result;
								__result_alloc = __new_alloc;
							}
							(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__result + __result_length, __linebuf_ptr,
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
					/* Must keep  on scanning  (and discarding  characters) until  after
					 * the next  unescaped line-feed.  Note that  to prevent  additional
					 * heap allocations, we use fgetc() for this, rather than getline(),
					 * though  because of this we must still  account for all 3 types of
					 * linefeeds that exist.
					 * HINT: Right now, the previous call to getline() will have left
					 *       the given `stream' pointed at the first character of the
					 *       line succeeding the one returned by getline()! */
					for (;;) {
						int __comment_ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
__again_check_ch_in_comment:
						if (__comment_ch == __EOF)
							break; /* end-of-file */
						if (__comment_ch == __delim_escape && __delim_escape) {
							__comment_ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
							if (__comment_ch == '\r' || __comment_ch == '\n') {
								if (__plineno)
									++*__plineno;
								if (__comment_ch == '\r') {
									__comment_ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
									if (__comment_ch != '\n')
										(__NAMESPACE_LOCAL_SYM __localdep_ungetc)(__comment_ch, __stream);
								}
								if (__delim_escape == __delim_continue)
									continue;
								break;
							}
							continue;
						}
						if (__comment_ch == __delim_continue && __delim_continue) {
							__comment_ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
							if (__comment_ch == '\r' || __comment_ch == '\n') {
								if (__plineno)
									++*__plineno;
								if (__comment_ch == '\r') {
									__comment_ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
									if (__comment_ch != '\n')
										(__NAMESPACE_LOCAL_SYM __localdep_ungetc)(__comment_ch, __stream);
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
							__comment_ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
							if (__comment_ch != '\n')
								(__NAMESPACE_LOCAL_SYM __localdep_ungetc)(__comment_ch, __stream);
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
	/* Special case:  Nothing was  read (this  can
	 * happen if `stream' was at its EOF location) */
	if __unlikely(!__result) {
		__result_length = 0;
		if __likely(__linebuf_ptr) {
			__result       = __linebuf_ptr;
			__result_alloc = __linebuf_alloc;
			__linebuf_ptr  = __NULLPTR;
			/*linebuf_alloc = 0;*/ /* Not needed */
		} else {

			__result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(char));



			if __unlikely(!__result)
				goto __done;
			__result_alloc = 1;
		}
	}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__linebuf_ptr);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	/* Trim a potential trailing line-feed */
	if (__result_length && __result[__result_length - 1] == '\n')
		--__result_length;
	/* Finalize the resulting buffer. */
	if (__result_length + 1 < __result_alloc) {
		/* Try to release unused memory. */
		char *__new_result;
		__new_result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result,
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
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__linebuf_ptr);
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fparseln_defined
#define __local___localdep_fparseln_defined
#define __localdep_fparseln __LIBC_LOCAL_NAME(fparseln)
#endif /* !__local___localdep_fparseln_defined */
#else /* (__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_fparseln_defined
#endif /* (!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_fparseln_defined */
