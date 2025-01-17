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
#ifndef _BITS_CRT_REGEX_H
#define _BITS_CRT_REGEX_H 1

#include <__stdinc.h>

#include <features.h>
#include <hybrid/typecore.h>

#define __SIZEOF_REG_SYNTAX_T__ __SIZEOF_POINTER__
#define __SIZEOF_REGOFF_T__     4

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __USE_GNU
#define __REPB_PREFIX(name) name
#else /* __USE_GNU */
#define __REPB_PREFIX(name) __##name
#endif /* !__USE_GNU */

#ifndef __RE_TRANSLATE_TYPE
#define __RE_TRANSLATE_TYPE unsigned char *
#endif /* !__RE_TRANSLATE_TYPE */

typedef __ULONGPTR_TYPE__ __reg_syntax_t; /* Set of `RE_*' */
typedef __INT32_TYPE__ __regoff_t;

struct re_pattern_buffer {
	unsigned char *__REPB_PREFIX(buffer);         /* [1..1][const] Pointer to the linked `struct re_code' */
	__ULONG32_TYPE__ __REPB_PREFIX(allocated);    /* Unused... */
	__ULONG32_TYPE__ __REPB_PREFIX(used);         /* Unused... */
	__reg_syntax_t __REPB_PREFIX(syntax);         /* [const] Syntax options that were used during compilation */
	char *__REPB_PREFIX(fastmap);                 /* Unused... (KOS integrates the fast-map with `struct re_code') */
	__RE_TRANSLATE_TYPE __REPB_PREFIX(translate); /* Unused... */
	__SIZE_TYPE__ re_nsub;                        /* [== ((struct re_code *)buffer)->rc_ngrps] */
	unsigned __REPB_PREFIX(can_be_null) : 1;      /* [== (((struct re_code *)buffer)->rc_minmatch == 0)] */
	unsigned __REPB_PREFIX(regs_allocated) : 2;   /* Unused... */
	unsigned __REPB_PREFIX(fastmap_accurate) : 1; /* [== 0] We don't provide glibc's "fastmap", so it can't be accurate. */
	unsigned __REPB_PREFIX(no_sub) : 1;           /* [== ((syntax & RE_SYNTAX_NO_SUB) != 0)] */
	unsigned __REPB_PREFIX(not_bol) : 1;          /* Input argument bit for `re_match[_2](3)' and `re_search[_2](3)' (`== REG_NOTBOL') */
	unsigned __REPB_PREFIX(not_eol) : 1;          /* Input argument bit for `re_match[_2](3)' and `re_search[_2](3)' (`== REG_NOTEOL') */
	unsigned __REPB_PREFIX(newline_anchor) : 1;   /* [== ((syntax & RE_SYNTAX_ANCHORS_IGNORE_EFLAGS) != 0)] */
};

#ifdef __USE_KOS
#define regex_getcode(self) \
	((struct re_code const *)(self)->__REPB_PREFIX(buffer))
#endif /* __USE_KOS */

#ifdef __USE_GNU
#define __re_registers re_registers
struct re_registers
#else /* __USE_GNU */
struct __re_registers
#endif /* !__USE_GNU */
{
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("num_regs")
#pragma push_macro("start")
#pragma push_macro("end")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef num_regs
#undef start
#undef end
	__UINT32_TYPE__ num_regs;
	__regoff_t     *start;
	__regoff_t     *end;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("end")
#pragma pop_macro("start")
#pragma pop_macro("num_regs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
};

struct __regmatch {
	__regoff_t rm_so; /* Byte offset to the start of the match. */
	__regoff_t rm_eo; /* Byte offset to the end of the match. */
};


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_REGEX_H */
