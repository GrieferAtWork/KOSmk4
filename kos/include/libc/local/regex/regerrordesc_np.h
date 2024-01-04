/* HASH CRC-32:0x9eeb8d59 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_regerrordesc_np_defined
#define __local_regerrordesc_np_defined
#include <__crt.h>
#include <asm/crt/regex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(regerrordesc_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(regerrordesc_np))(int __errcode) {
	char const *__result;
	switch (__errcode) {
#ifdef __REG_ENOSYS
	case __REG_ENOSYS: /*  */ __result = "Unable to load regex sub-system"; break;
#endif /* __REG_ENOSYS */
#ifdef __REG_NOERROR
	case __REG_NOERROR: /* */ __result = "Success"; break;
#endif /* __REG_NOERROR */
#ifdef __REG_NOMATCH
	case __REG_NOMATCH: /* */ __result = "No match"; break;
#endif /* __REG_NOMATCH */
#ifdef __REG_BADPAT
	case __REG_BADPAT: /*  */ __result = "Invalid regex pattern"; break;
#endif /* __REG_BADPAT */
#ifdef __REG_ECOLLATE
	case __REG_ECOLLATE: /**/ __result = "Invalid collation character"; break;
#endif /* __REG_ECOLLATE */
#ifdef __REG_ECTYPE
	case __REG_ECTYPE: /*  */ __result = "Invalid character class name"; break;
#endif /* __REG_ECTYPE */
#ifdef __REG_EESCAPE
	case __REG_EESCAPE: /* */ __result = "Trailing backslash"; break;
#endif /* __REG_EESCAPE */
#ifdef __REG_ESUBREG
	case __REG_ESUBREG: /* */ __result = "Invalid back reference"; break;
#endif /* __REG_ESUBREG */
#ifdef __REG_EBRACK
	case __REG_EBRACK: /*  */ __result = "Unmatched [, [^, [:, [., or [="; break;
#endif /* __REG_EBRACK */
#ifdef __REG_EPAREN
	case __REG_EPAREN: /*  */ __result = "Unmatched ("; break;
#endif /* __REG_EPAREN */
#ifdef __REG_EBRACE
	case __REG_EBRACE: /*  */ __result = "Unmatched {"; break;
#endif /* __REG_EBRACE */
#ifdef __REG_BADBR
	case __REG_BADBR: /*   */ __result = "Invalid content of {...}"; break;
#endif /* __REG_BADBR */
#ifdef __REG_ERANGE
	case __REG_ERANGE: /*  */ __result = "Set-range start is greater than its end"; break;
#endif /* __REG_ERANGE */
#ifdef __REG_ESPACE
	case __REG_ESPACE: /*  */ __result = "Out of memory"; break;
#endif /* __REG_ESPACE */
#ifdef __REG_BADRPT
	case __REG_BADRPT: /*  */ __result = "Nothing precedes +, *, ?, or {"; break;
#endif /* __REG_BADRPT */
#ifdef __REG_EEND
	case __REG_EEND: /*    */ __result = "Unexpected end of pattern"; break;
#endif /* __REG_EEND */
#ifdef __REG_ESIZE
	case __REG_ESIZE: /*   */ __result = "Regular expression violates a hard upper limit"; break;
#endif /* __REG_ESIZE */
#ifdef __REG_ERPAREN
	case __REG_ERPAREN: /* */ __result = "Unmatched )"; break;
#endif /* __REG_ERPAREN */
#ifdef __REG_EILLSEQ
	case __REG_EILLSEQ: /* */ __result = "Illegal unicode character"; break;
#endif /* __REG_EILLSEQ */
#ifdef __REG_EILLSET
	case __REG_EILLSET: /* */ __result = "Cannot combine raw bytes with unicode characters in charsets"; break;
#endif /* __REG_EILLSET */
#ifdef __REG_EMPTY
	case __REG_EMPTY: /*   */ __result = "?"; break;
#endif /* __REG_EMPTY */
#ifdef __REG_ASSERT
	case __REG_ASSERT: /*  */ __result = "?"; break;
#endif /* __REG_ASSERT */
#ifdef __REG_INVARG
	case __REG_INVARG: /*  */ __result = "?"; break;
#endif /* __REG_INVARG */
	default: __result = __NULLPTR; break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_regerrordesc_np_defined
#define __local___localdep_regerrordesc_np_defined
#define __localdep_regerrordesc_np __LIBC_LOCAL_NAME(regerrordesc_np)
#endif /* !__local___localdep_regerrordesc_np_defined */
#endif /* !__local_regerrordesc_np_defined */
