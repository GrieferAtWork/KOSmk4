/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_STRING_C
#define GUARD_LIBC_USER_STRING_C 1

#include "../api.h"
#include "string.h"

#include "../libc/errno.h"
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <assert.h>
#include <errno.h>
#include <parts/dos/errno.h>

DECL_BEGIN


/*[[[start:implementation]]]*/

/*[[[head:strdup,hash:CRC-32=0xb1c886cb]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.strdup.strdup") char *
NOTHROW_NCX(LIBCCALL libc_strdup)(char const *__restrict string)
/*[[[body:strdup]]]*/
/*AUTO*/{
	size_t resultsize = (libc_strlen(string) + 1) * sizeof(char);
	char *result = (char *)libc_malloc(resultsize);
	if likely(result)
		memcpy(result, string, resultsize);
	return result;
}
/*[[[end:strdup]]]*/

/*[[[head:strndup,hash:CRC-32=0xcaa7a55f]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.strdup.strndup") char *
NOTHROW_NCX(LIBCCALL libc_strndup)(char const *__restrict string,
                                   size_t max_chars)
/*[[[body:strndup]]]*/
/*AUTO*/{
	size_t resultlen = libc_strnlen(string, max_chars);
	char *result = (char *)libc_malloc((resultlen + 1) * sizeof(char));
	if likely(result)
		*(char *)mempcpy(result, string, resultlen * sizeof(char)) = '\0';
	return result;
}
/*[[[end:strndup]]]*/



PRIVATE ATTR_SECTION(".bss.crt.errno.strerror.strerror_buf") char strerror_buf[64];
PRIVATE ATTR_SECTION(".bss.crt.errno.strsignal.strsignal_buf") char strsignal_buf[32];
PRIVATE ATTR_SECTION(".rodata.crt.errno.strerror.unknown_error_format") char const unknown_error_format[] = "Unknown error %d";
PRIVATE ATTR_SECTION(".rodata.crt.errno.strsignal.unknown_error_format") char const unknown_signal_format[] = "Unknown signal %d";

/* These 2 functions are implemented in libc/errno.c */
/*[[[skip:strerror_s]]]*/
/*[[[skip:strerrorname_s]]]*/


/*[[[head:strerror,hash:CRC-32=0x5febe1d5]]]*/
INTERN WUNUSED ATTR_RETNONNULL
ATTR_WEAK ATTR_SECTION(".text.crt.errno.strerror") char *
NOTHROW_NCX(LIBCCALL libc_strerror)(int errnum)
/*[[[body:strerror]]]*/
{
	char *result = strerror_buf;
	char const *string;
	string = strerror_s(errnum);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strerror_buf) - 1] = '\0';
		strncpy(result, string, COMPILER_LENOF(strerror_buf) - 1);
	} else {
		sprintf(result, unknown_error_format, errnum);
	}
	return result;
}
/*[[[end:strerror]]]*/

#ifndef sys_siglist
#undef _sys_siglist
#ifndef ____p_sys_siglist_defined
#define ____p_sys_siglist_defined 1
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED __ATTR_RETNONNULL,char const *const *,__NOTHROW_NCX,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined */
#define _sys_siglist  __p_sys_siglist()
#define sys_siglist   __p_sys_siglist()
#endif /* !sys_siglist */

/*[[[head:strsignal_s,hash:CRC-32=0xfa78e701]]]*/
INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.errno.strsignal_s") char const *
NOTHROW(LIBCCALL libc_strsignal_s)(int signum)
/*[[[body:strsignal_s]]]*/
{
	if unlikely(signum >= NSIG)
		return NULL;
	return sys_siglist[signum];
}
/*[[[end:strsignal_s]]]*/

/*[[[head:strsignal,hash:CRC-32=0xb6c64ee8]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strsignal") char *
NOTHROW_NCX(LIBCCALL libc_strsignal)(int signo)
/*[[[body:strsignal]]]*/
{
	char *result = strsignal_buf;
	char const *string;
	string = strsignal_s(signo);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strsignal_buf) - 1] = '\0';
		strncpy(result, string, COMPILER_LENOF(strsignal_buf) - 1);
	} else {
		sprintf(result, unknown_signal_format, signo);
	}
	return result;
}
/*[[[end:strsignal]]]*/

/*[[[head:strerror_r,hash:CRC-32=0x97942068]]]*/
INTERN ATTR_RETNONNULL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.errno.strerror_r") char *
NOTHROW_NCX(LIBCCALL libc_strerror_r)(int errnum,
                                      char *buf,
                                      size_t buflen)
/*[[[body:strerror_r]]]*/
{
	char const *string;
	string = strerror_s(errnum);
	if (!buf || !buflen) {
		buf    = strerror_buf;
		buflen = COMPILER_LENOF(strerror_buf);
	}
	if (string) {
		/* Copy the descriptor text. */
		size_t msg_len = (strlen(string) + 1) * sizeof(char);
		if (msg_len > buflen) {
			buf    = strerror_buf;
			buflen = COMPILER_LENOF(strerror_buf);
			if unlikely(msg_len > buflen) {
				msg_len      = buflen - 1;
				buf[msg_len] = '\0';
			}
		}
		memcpy(buf, string, msg_len);
	} else {
again_unknown:
		if (snprintf(buf, buflen, unknown_error_format, errnum) >= buflen) {
			assert(buf != strerror_buf);
			buf    = strerror_buf;
			buflen = COMPILER_LENOF(strerror_buf);
			goto again_unknown;
		}
	}
	return buf;
}
/*[[[end:strerror_r]]]*/

DEFINE_PUBLIC_WEAK_ALIAS(__xpg_strerror_r, libc___xpg_strerror_r);
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.__xpg_strerror_r") errno_t
NOTHROW_NCX(LIBCCALL libc___xpg_strerror_r)(int errnum,
                                            char *buf,
                                            size_t buflen) {
	size_t msg_len;
	char const *string;
	string = strerror_s(errnum);
	if (!buf)
		buflen = 0;
	if (!string)
		return EINVAL;
	/* Copy the descriptor text. */
	msg_len = (strlen(string) + 1) * sizeof(char);
	if (msg_len > buflen)
		return ERANGE;
	memcpy(buf, string, msg_len);
	return EOK;
}


/*[[[head:vstrdupf,hash:CRC-32=0x2baa3863]]]*/
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_LIBC_PRINTF(1, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.heap.strdup.vstrdupf") char *
NOTHROW_NCX(LIBCCALL libc_vstrdupf)(char const *__restrict format,
                                    va_list args)
/*[[[body:vstrdupf]]]*/
/*AUTO*/{
	char *result;
	return libc_vasprintf(&result, format, args) >= 0 ? result : 0;
}
/*[[[end:vstrdupf]]]*/

/*[[[head:strdupf,hash:CRC-32=0xe2953fe2]]]*/
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_LIBC_PRINTF(1, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.heap.strdup.strdupf") char *
NOTHROW_NCX(VLIBCCALL libc_strdupf)(char const *__restrict format,
                                    ...)
/*[[[body:strdupf]]]*/
/*AUTO*/{
	char * result;
	va_list args;
	va_start(args, format);
	result = libc_vstrdupf(format, args);
	va_end(args);
	return result;
}
/*[[[end:strdupf]]]*/

/*[[[head:_strerror,hash:CRC-32=0xe56d28c3]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._strerror") char *
NOTHROW_RPC(LIBCCALL libc__strerror)(char const *message)
/*[[[body:_strerror]]]*/
{
	_strerror_s(strerror_buf,
	            COMPILER_LENOF(strerror_buf),
	            message);
	return strerror_buf;
}
/*[[[end:_strerror]]]*/


PRIVATE ATTR_SECTION(".rodata.crt.dos.errno._strerror_s._strerror_s_format") char const libc__strerror_s_format[] = "%s: %s\n";
PRIVATE ATTR_SECTION(".rodata.crt.dos.errno._strerror_s._strerror_s_unknown") char const libc__strerror_s_unknown[] = "%s: Unknown error %d\n";

/*[[[head:_strerror_s,hash:CRC-32=0x275fbe96]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._strerror_s") errno_t
NOTHROW_RPC(LIBCCALL libc__strerror_s)(char *__restrict buf,
                                       size_t buflen,
                                       char const *message)
/*[[[body:_strerror_s]]]*/
{
	char const *string;
	size_t reqlen;
	string = strerror_s(libc_geterrno());
	if (string) {
		if (message) {
			reqlen = snprintf(buf, buflen, libc__strerror_s_format, message, string);
		} else {
			reqlen = snprintf(buf, buflen, libc__strerror_s_format + 4, string);
		}
	} else if (message) {
		reqlen = snprintf(buf, buflen, libc__strerror_s_unknown, message, libc_geterrno());
	} else {
		reqlen = snprintf(buf, buflen, libc__strerror_s_unknown + 4, libc_geterrno());
	}
	if (reqlen > buflen)
		return ERANGE;
	return 0;
}
/*[[[end:_strerror_s]]]*/

/*[[[head:DOS$_strerror_s,hash:CRC-32=0x890a62e4]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._strerror_s") errno_t
NOTHROW_RPC(LIBDCALL libd__strerror_s)(char *__restrict buf,
                                       size_t buflen,
                                       char const *message)
/*[[[body:DOS$_strerror_s]]]*/
{
	char const *string;
	size_t reqlen;
	string = strerror_s(libc_geterrno());
	if (string) {
		if (message) {
			reqlen = snprintf(buf, buflen, libc__strerror_s_format, message, string);
		} else {
			reqlen = snprintf(buf, buflen, libc__strerror_s_format + 4, string);
		}
	} else if (message) {
		reqlen = snprintf(buf, buflen, libc__strerror_s_unknown, message, libd_geterrno());
	} else {
		reqlen = snprintf(buf, buflen, libc__strerror_s_unknown + 4, libd_geterrno());
	}
	if (reqlen > buflen)
		return __DOS_ERANGE;
	return 0;
}
/*[[[end:DOS$_strerror_s]]]*/

/*[[[head:strerror_l,hash:CRC-32=0xe0b038e7]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.errno.strerror_l") char *
NOTHROW_NCX(LIBCCALL libc_strerror_l)(int errnum,
                                      locale_t locale)
/*[[[body:strerror_l]]]*/
/*AUTO*/{
	(void)locale;
	return libc_strerror(errnum);
}
/*[[[end:strerror_l]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x21cfbba1]]]*/
#undef strdupf
DEFINE_PUBLIC_WEAK_ALIAS(strerror, libc_strerror);
DEFINE_PUBLIC_WEAK_ALIAS(strerror_l, libc_strerror_l);
DEFINE_PUBLIC_WEAK_ALIAS(strsignal, libc_strsignal);
DEFINE_PUBLIC_WEAK_ALIAS(strndup, libc_strndup);
DEFINE_PUBLIC_WEAK_ALIAS(__strndup, libc_strndup);
DEFINE_PUBLIC_WEAK_ALIAS(strdup, libc_strdup);
DEFINE_PUBLIC_WEAK_ALIAS(__strdup, libc_strdup);
DEFINE_PUBLIC_WEAK_ALIAS(_strdup, libc_strdup);
DEFINE_PUBLIC_WEAK_ALIAS(strerror_r, libc_strerror_r);
DEFINE_PUBLIC_WEAK_ALIAS(__strerror_r, libc_strerror_r);
DEFINE_PUBLIC_WEAK_ALIAS(strsignal_s, libc_strsignal_s);
DEFINE_PUBLIC_WEAK_ALIAS(vstrdupf, libc_vstrdupf);
DEFINE_PUBLIC_WEAK_ALIAS(strdupf, libc_strdupf);
DEFINE_PUBLIC_WEAK_ALIAS(_strerror, libc__strerror);
DEFINE_PUBLIC_WEAK_ALIAS(_strerror_s, libc__strerror_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_strerror_s, libd__strerror_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STRING_C */
