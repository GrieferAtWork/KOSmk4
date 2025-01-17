/* HASH CRC-32:0x18ca256e */
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
#ifndef __local__ungetwch_nolock_defined
#define __local__ungetwch_nolock_defined
#include <__crt.h>
#if defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ungetwc_unlocked_defined
#define __local___localdep_ungetwc_unlocked_defined
#ifdef __CRT_HAVE_ungetwc_unlocked
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetwc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_ungetwc_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <libc/template/stdtty.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_ungetwch_nolock) __WINT_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ungetwch_nolock))(__WINT_TYPE__ __ch) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ungetwc_unlocked)(__ch, __LOCAL_stdtty);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ungetwch_nolock_defined
#define __local___localdep__ungetwch_nolock_defined
#define __localdep__ungetwch_nolock __LIBC_LOCAL_NAME(_ungetwch_nolock)
#endif /* !__local___localdep__ungetwch_nolock_defined */
#else /* __CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE__ungetwc_nolock || __CRT_HAVE_ungetwc) */
#undef __local__ungetwch_nolock_defined
#endif /* !__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetwc_unlocked && !__CRT_HAVE__ungetwc_nolock && !__CRT_HAVE_ungetwc) */
#endif /* !__local__ungetwch_nolock_defined */
