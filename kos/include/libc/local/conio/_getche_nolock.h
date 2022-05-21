/* HASH CRC-32:0xa10fc8ec */
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
#ifndef __local__getche_nolock_defined
#define __local__getche_nolock_defined
#include <__crt.h>
#include <asm/os/termios.h>
#include <features.h>
#include <asm/os/tty.h>
#if defined(__ECHO) && defined(__TCSANOW) && defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc_unlocked_defined
#define __local___localdep_fgetc_unlocked_defined
#ifdef __CRT_HAVE_fgetc_unlocked
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetc_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetc_unlocked __LIBC_LOCAL_NAME(fgetc_unlocked)
#else /* ... */
#undef __local___localdep_fgetc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_unlocked_defined */
#ifndef __local___localdep_fileno_defined
#define __local___localdep_fileno_defined
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_fileno_defined
#endif /* !... */
#endif /* !__local___localdep_fileno_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_tcgetattr_defined
#define __local___localdep_tcgetattr_defined
#ifdef __CRT_HAVE_tcgetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),tcgetattr,(__fd,__termios_p))
#elif defined(__CRT_HAVE___tcgetattr)
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),__tcgetattr,(__fd,__termios_p))
#elif (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcgetattr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tcgetattr __LIBC_LOCAL_NAME(tcgetattr)
#else /* ... */
#undef __local___localdep_tcgetattr_defined
#endif /* !... */
#endif /* !__local___localdep_tcgetattr_defined */
#ifndef __local___localdep_tcsetattr_defined
#define __local___localdep_tcsetattr_defined
#ifdef __CRT_HAVE_tcsetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_tcsetattr,(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p),tcsetattr,(__fd,__optional_actions,__termios_p))
#elif defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcsetattr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tcsetattr __LIBC_LOCAL_NAME(tcsetattr)
#else /* ... */
#undef __local___localdep_tcsetattr_defined
#endif /* !... */
#endif /* !__local___localdep_tcsetattr_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/os/termios.h>
#include <libc/template/stdtty.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_getche_nolock) __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_getche_nolock))(void) {
	int __result;
	struct termios __oios, __nios;
	__FILE *__fp = __LOCAL_stdtty;
	__fd_t __fd  = (__NAMESPACE_LOCAL_SYM __localdep_fileno)(__fp);
	(__NAMESPACE_LOCAL_SYM __localdep_tcgetattr)(__fd, &__oios);
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(&__nios, &__oios, sizeof(__nios));
	__nios.c_lflag |= __ECHO;
	(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fd, __TCSANOW, &__nios);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fgetc_unlocked)(__fp);
	(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fd, __TCSANOW, &__oios);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getche_nolock_defined
#define __local___localdep__getche_nolock_defined
#define __localdep__getche_nolock __LIBC_LOCAL_NAME(_getche_nolock)
#endif /* !__local___localdep__getche_nolock_defined */
#else /* __ECHO && __TCSANOW && __CRT_HAVE_stdtty && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE_fgetc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
#undef __local__getche_nolock_defined
#endif /* !__ECHO || !__TCSANOW || !__CRT_HAVE_stdtty || (!__CRT_HAVE_fileno && !__CRT_HAVE__fileno && !__CRT_HAVE_fileno_unlocked) || (!__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_HAVE_getc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_HAVE_fgetc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_HAVE__IO_getc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) */
#endif /* !__local__getche_nolock_defined */
