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
#ifdef __INTELLISENSE__
#include "register.c"
#define SET_REGISTER 1
#endif /* __INTELLISENSE__ */

#include <hybrid/host.h>

#if (defined(GET_REGISTER) + defined(SET_REGISTER)) != 1
#error "Must either defined GET_REGISTER or SET_REGISTER"
#endif


DECL_BEGIN

#ifdef GET_REGISTER
#define FUNC(x) GDB_Get##x
#define FIELD4(field)                                \
	do {                                             \
		if (bufsize >= 4)                            \
			UNALIGNED_SET32((u32 *)buf, (u32)field); \
		return 4;                                    \
	}	__WHILE0
#define FIELD8(field)                                \
	do {                                             \
		if (bufsize >= 8)                            \
			UNALIGNED_SET64((u64 *)buf, (u64)field); \
		return 8;                                    \
	}	__WHILE0
#define GETSET4(get, set)                       \
	do {                                        \
		if (bufsize >= 4) {                     \
			u32 value;                          \
			value = get;                        \
			UNALIGNED_SET32((u32 *)buf, value); \
		}                                       \
		return 4;                               \
	}	__WHILE0
#define GETSET8(get, set)                       \
	do {                                        \
		if (bufsize >= 8) {                     \
			u64 value;                          \
			value = get;                        \
			UNALIGNED_SET64((u64 *)buf, value); \
		}                                       \
		return 8;                               \
	}	__WHILE0
#define GETSET4_NOOP()                      \
	do {                                    \
		if (bufsize >= 4) {                 \
			UNALIGNED_SET32((u32 *)buf, 0); \
		}                                   \
		return 4;                           \
	}	__WHILE0
#define GETSET8_NOOP()                      \
	do {                                    \
		if (bufsize >= 8) {                 \
			UNALIGNED_SET64((u64 *)buf, 0); \
		}                                   \
		return 8;                           \
	}	__WHILE0
#define STATE       state
#define STATE_PARAM const *__restrict state
#define STATE_CONST const
#define BUF_CONST   /* nothing */
#elif defined(SET_REGISTER)
#define FUNC(x) GDB_Set##x
#define FIELD4(field)                                                     \
	do {                                                                  \
		if (bufsize == 4)                                                 \
			field = (__typeof__(field))UNALIGNED_GET32((u32 const *)buf); \
		return 4;                                                         \
	}	__WHILE0
#define FIELD8(field)                                                     \
	do {                                                                  \
		if (bufsize == 8)                                                 \
			field = (__typeof__(field))UNALIGNED_GET64((u64 const *)buf); \
		return 8;                                                         \
	}	__WHILE0
#define GETSET4(get, set)                              \
	do {                                               \
		if (bufsize == 4) {                            \
			u32 value;                                 \
			value = UNALIGNED_GET32((u32 const *)buf); \
			set;                                       \
		}                                              \
		return 4;                                      \
	}	__WHILE0
#define GETSET8(get, set)                              \
	do {                                               \
		if (bufsize == 8) {                            \
			u64 value;                                 \
			value = UNALIGNED_GET64((u64 const *)buf); \
			set;                                       \
		}                                              \
		return 8;                                      \
	}	__WHILE0
#define GETSET4_NOOP() \
	do {               \
		return 4;      \
	}	__WHILE0
#define GETSET8_NOOP() \
	do {               \
		return 8;      \
	}	__WHILE0
#define STATE       (*pstate)
#define STATE_PARAM **__restrict pstate
#define STATE_CONST /* nothing */
#define BUF_CONST   const
#endif







DECL_END


#ifndef __INTELLISENSE__

#ifdef __x86_64__
#include "register64-impl.c.inl"
#else /* __x86_64__ */
#include "register32-impl.c.inl"
#endif /* !__x86_64__ */

#undef FUNC
#undef SET_REGISTER
#undef GET_REGISTER
#undef FIELD4
#undef FIELD8
#undef GETSET4
#undef GETSET8
#undef GETSET4_NOOP
#undef GETSET8_NOOP
#undef BUF_CONST
#undef STATE
#undef STATE_PARAM
#undef STATE_CONST
#endif /* !__INTELLISENSE__ */
