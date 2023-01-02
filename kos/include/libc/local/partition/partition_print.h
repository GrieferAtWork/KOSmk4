/* HASH CRC-32:0xfdbab3bf */
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
#ifndef __local_partition_print_defined
#define __local_partition_print_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <bits/crt/partition.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fprintf_defined
#define __local___localdep_fprintf_defined
#if defined(__USE_STDIO_UNLOCKED) && __has_builtin(__builtin_fprintf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf_unlocked) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fprintf,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf_unlocked,{ return __builtin_fprintf_unlocked(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif __has_builtin(__builtin_fprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fprintf,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf,{ return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fprintf __LIBC_LOCAL_NAME(fprintf)
#endif /* !... */
#endif /* !__local___localdep_fprintf_defined */
#ifndef __local___localdep_fputc_defined
#define __local___localdep_fputc_defined
#if defined(__USE_STDIO_UNLOCKED) && __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_putc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fputc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fputc __LIBC_LOCAL_NAME(fputc)
#else /* ... */
#undef __local___localdep_fputc_defined
#endif /* !... */
#endif /* !__local___localdep_fputc_defined */
__LOCAL_LIBC(partition_print) __ATTR_IN(1) __ATTR_INOUT(2) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(partition_print))(struct partition_def __KOS_FIXED_CONST *__self, __FILE *__fp) {
	unsigned int __i;
	(__NAMESPACE_LOCAL_SYM __localdep_fputc)('[', __fp);
	for (__i = 0; __i < (unsigned int)__self->num_elements; ++__i) {
		struct partition_elem const *__elem = &__self->elements[__i];
		struct partition_elem const *__iter;
		unsigned int __prev_index;

		/* Check if the class of `elem' contains any element < i.
		 * -> If so, then we've already printed this class. */
		__iter = __elem->next;
		while (__iter != __elem) {
			if ((unsigned int)(__iter - __self->elements) < __i)
				goto __already_printed;
			__iter = __iter->next;
		}

		/* At this point we know that `i' is the smallest
		 * member  of whatever class it belongs to. Since
		 * we need to print sorted, we can start with `i' */
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__fp, "(%u", __i);
		__prev_index = __i;
		for (;;) {
			unsigned int __winner_index;
			struct partition_elem const *__winner;
			__winner_index = (unsigned int)-1;
			__winner       = __NULLPTR;
			/* Check if the class contains an element `> prev_index && < winner_index' */
			__iter = __elem->next;
			for (;;) {
				unsigned int __iter_index;
				if (__iter == __elem)
					break;
				__iter_index = (unsigned int)(__iter - __self->elements);
				if (__iter_index > __prev_index && __iter_index < __winner_index) {
					__winner       = __iter;
					__winner_index = __iter_index;
				}
				__iter = __iter->next;
			}
			if (!__winner)
				break; /* Last element was printed. */
			(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__fp, " %u", __winner_index);
			__prev_index = __winner_index;
		}
		(__NAMESPACE_LOCAL_SYM __localdep_fputc)(')', __fp);
__already_printed:
		;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_fputc)(']', __fp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_partition_print_defined
#define __local___localdep_partition_print_defined
#define __localdep_partition_print __LIBC_LOCAL_NAME(partition_print)
#endif /* !__local___localdep_partition_print_defined */
#else /* __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#undef __local_partition_print_defined
#endif /* !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock */
#endif /* !__local_partition_print_defined */
