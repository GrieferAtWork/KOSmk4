/* HASH CRC-32:0x63c87810 */
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
#ifndef __local_bgets_defined
#define __local_bgets_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc_defined
#define __local___localdep_fgetc_defined
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetc __LIBC_LOCAL_NAME(fgetc)
#else /* ... */
#undef __local___localdep_fgetc_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_defined */
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(bgets) __ATTR_INOUT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bgets))(char *__buf, __SIZE_TYPE__ __buflen_minus_one, __FILE *__fp, char __KOS_FIXED_CONST *__stop_chars) {
	char *__iter = __buf;
	if (__stop_chars == __NULLPTR)
		__stop_chars = (char __KOS_FIXED_CONST *)"";
	for (; __buflen_minus_one; --__buflen_minus_one) {
		int __ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__fp);
		if (__ch == __EOF) {
			if (__iter == __buf)
				return __NULLPTR;
			break;
		}
		if ((__NAMESPACE_LOCAL_SYM __localdep_strchr)(__stop_chars, __ch))
			break;
		*__iter++ = __ch;
	}
	*__iter = '\0';
	return __iter;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_bgets_defined
#define __local___localdep_bgets_defined
#define __localdep_bgets __LIBC_LOCAL_NAME(bgets)
#endif /* !__local___localdep_bgets_defined */
#else /* __CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#undef __local_bgets_defined
#endif /* !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock */
#endif /* !__local_bgets_defined */
