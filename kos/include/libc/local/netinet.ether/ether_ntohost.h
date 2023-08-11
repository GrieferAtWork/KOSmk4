/* HASH CRC-32:0x253fcd59 */
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
#ifndef __local_ether_ntohost_defined
#define __local_ether_ntohost_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#if ((defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
struct ether_addr;
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ether_line_np_defined
#define __local___localdep_ether_line_np_defined
#ifdef __CRT_HAVE_ether_line_np
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_ether_line_np,(char *__line, struct ether_addr *__addr),ether_line_np,(__line,__addr))
#else /* __CRT_HAVE_ether_line_np */
__NAMESPACE_LOCAL_END
#include <libc/local/netinet.ether/ether_line_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ether_line_np __LIBC_LOCAL_NAME(ether_line_np)
#endif /* !__CRT_HAVE_ether_line_np */
#endif /* !__local___localdep_ether_line_np_defined */
#ifndef __local___localdep_fclose_defined
#define __local___localdep_fclose_defined
#ifdef __CRT_HAVE_fclose
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fclose,(__FILE *__restrict __stream),fclose,(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fclose,(__FILE *__restrict __stream),_fclose_nolock,(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fclose,(__FILE *__restrict __stream),_IO_fclose,(__stream))
#else /* ... */
#undef __local___localdep_fclose_defined
#endif /* !... */
#endif /* !__local___localdep_fclose_defined */
#ifndef __local___localdep_fopen_defined
#define __local___localdep_fopen_defined
#if defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),_IO_fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#else /* ... */
#undef __local___localdep_fopen_defined
#endif /* !... */
#endif /* !__local___localdep_fopen_defined */
#ifndef __local___localdep_fparseln_defined
#define __local___localdep_fparseln_defined
#ifdef __CRT_HAVE_fparseln
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2),char *,__NOTHROW_CB_NCX,__localdep_fparseln,(__FILE *__stream, __SIZE_TYPE__ *__plen, __SIZE_TYPE__ *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags),fparseln,(__stream,__plen,__plineno,__delim,__flags))
#elif (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/util/fparseln.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fparseln __LIBC_LOCAL_NAME(fparseln)
#else /* ... */
#undef __local___localdep_fparseln_defined
#endif /* !... */
#endif /* !__local___localdep_fparseln_defined */
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
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined
#ifdef __CRT_HAVE_memcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),__gcc_bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
#ifndef __local___localdep_strcpy_defined
#define __local___localdep_strcpy_defined
#if __has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,{ return __builtin_strcpy(__dst, __src); })
#elif defined(__CRT_HAVE_strcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,(__dst,__src))
#elif defined(__CRT_HAVE__mbscpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),_mbscpy,(__dst,__src))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcpy __LIBC_LOCAL_NAME(strcpy)
#endif /* !... */
#endif /* !__local___localdep_strcpy_defined */
__LOCAL_LIBC(ether_ntohost) __ATTR_IN(2) __ATTR_OUT(1) int
__NOTHROW_RPC_KOS(__LIBCCALL __LIBC_LOCAL_NAME(ether_ntohost))(char *__hostname, struct ether_addr const *__addr) {
	char *__line;
	__FILE *__fp = (__NAMESPACE_LOCAL_SYM __localdep_fopen)("/etc/ethers", "rb");
	if __unlikely(!__fp)
		goto __err;
	while ((__line = (__NAMESPACE_LOCAL_SYM __localdep_fparseln)(__fp, __NULLPTR, __NULLPTR, "\0\0#", 0)) != __NULLPTR) {
		struct ether_addr __laddr;
		char *__lhost;
		if (!*__line) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__line);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
			break;
		}
		__lhost = (__NAMESPACE_LOCAL_SYM __localdep_ether_line_np)(__line, &__laddr);
		if (__lhost && (__NAMESPACE_LOCAL_SYM __localdep_memcmp)(&__laddr, __addr, sizeof(__laddr)) == 0) {
			(__NAMESPACE_LOCAL_SYM __localdep_strcpy)(__hostname, __lhost); /* Yes: no way to prevent overflow here :( */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__line);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_fclose)(__fp);
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
			return 0;
		}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__line);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	}
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
	(void)(__NAMESPACE_LOCAL_SYM __localdep_fclose)(__fp);
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ether_ntohost_defined
#define __local___localdep_ether_ntohost_defined
#define __localdep_ether_ntohost __LIBC_LOCAL_NAME(ether_ntohost)
#endif /* !__local___localdep_ether_ntohost_defined */
#else /* ((__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
#undef __local_ether_ntohost_defined
#endif /* ((!__CRT_HAVE_fopen || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && (!__CRT_HAVE__IO_fopen || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_fopen64) || (!__CRT_HAVE_fparseln && ((!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
#endif /* !__local_ether_ntohost_defined */
