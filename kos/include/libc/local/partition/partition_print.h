/* HASH CRC-32:0xd2fdcc2d */
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
#ifndef __local_partition_print_defined
#define __local_partition_print_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__flsbuf) && !defined(__CRT_HAVE___swbuf)))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__flsbuf) && !defined(__CRT_HAVE___swbuf)))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__flsbuf) && !defined(__CRT_HAVE___swbuf)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <bits/crt/partition.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_flockfile_defined
#define __local___localdep_flockfile_defined
#ifdef __CRT_HAVE_flockfile
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),flockfile,(__stream))
#elif defined(__CRT_HAVE__lock_file)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_lock_file,(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#else /* ... */
#undef __local___localdep_flockfile_defined
#endif /* !... */
#endif /* !__local___localdep_flockfile_defined */
#ifndef __local___localdep_fprintf_unlocked_defined
#define __local___localdep_fprintf_unlocked_defined
#if __has_builtin(__builtin_fprintf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf_unlocked) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_fprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf_unlocked,{ return __builtin_fprintf_unlocked(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf_s)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fprintf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fprintf_unlocked __LIBC_LOCAL_NAME(fprintf_unlocked)
#else /* ... */
#undef __local___localdep_fprintf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fprintf_unlocked_defined */
#ifndef __local___localdep_fputc_unlocked_defined
#define __local___localdep_fputc_unlocked_defined
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
__CEIREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__flsbuf) && !defined(__CRT_HAVE___swbuf)))
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__flsbuf) && !defined(__CRT_HAVE___swbuf)))
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__flsbuf) && !defined(__CRT_HAVE___swbuf)))
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fputc_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fputc_unlocked __LIBC_LOCAL_NAME(fputc_unlocked)
#else /* ... */
#undef __local___localdep_fputc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fputc_unlocked_defined */
#ifndef __local___localdep_funlockfile_defined
#define __local___localdep_funlockfile_defined
#ifdef __CRT_HAVE_funlockfile
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),funlockfile,(__stream))
#elif defined(__CRT_HAVE__unlock_file)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_unlock_file,(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#else /* ... */
#undef __local___localdep_funlockfile_defined
#endif /* !... */
#endif /* !__local___localdep_funlockfile_defined */
__LOCAL_LIBC(partition_print) __ATTR_IN(1) __ATTR_INOUT(2) void
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(partition_print))(struct partition_def __KOS_FIXED_CONST *__self, __FILE *__fp) {
	unsigned int __i;
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_flockfile)(__fp);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
	(__NAMESPACE_LOCAL_SYM __localdep_fputc_unlocked)('[', __fp);
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
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf_unlocked)(__fp, "(%u", __i);
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
			(__NAMESPACE_LOCAL_SYM __localdep_fprintf_unlocked)(__fp, " %u", __winner_index);
			__prev_index = __winner_index;
		}
		(__NAMESPACE_LOCAL_SYM __localdep_fputc_unlocked)(')', __fp);
__already_printed:
		;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_fputc_unlocked)(']', __fp);
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_funlockfile)(__fp);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_partition_print_defined
#define __local___localdep_partition_print_defined
#define __localdep_partition_print __LIBC_LOCAL_NAME(partition_print)
#endif /* !__local___localdep_partition_print_defined */
#else /* (__CRT_HAVE_fprintf_unlocked || __CRT_HAVE_fprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_HAVE_putc && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf))) || (__CRT_HAVE_fputc && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf))) || (__CRT_HAVE__IO_putc && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf))) || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __local_partition_print_defined
#endif /* (!__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__local_partition_print_defined */
