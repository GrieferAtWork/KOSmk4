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
#ifndef _LIBEMU86_EMU_PUSHPOP_UTIL_H
#define _LIBEMU86_EMU_PUSHPOP_UTIL_H 1

#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

/* 66 XX push16
 *    XX push32 (in 32-bit  mode)
 *    XX illegal (in 64-bit mode) */
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
#define EMU86_PUSH1632(T, value)                     \
	do {                                             \
		byte_t *sp;                                  \
		T _value;                                    \
		IF_64BIT({                                   \
			if (EMU86_F_IS64(op_flags))              \
				goto return_unsupported_instruction; \
		});                                          \
		_value = (value);                            \
		sp     = EMU86_GETSTACKPTR();                \
		if (IS_16BIT()) {                            \
			sp -= 2;                                 \
			EMU86_EMULATE_PUSH(sp, 2);               \
			EMU86_WRITE_USER_MEMORY(sp, 2);          \
			EMU86_MEMWRITEW(sp, _value);             \
		} else {                                     \
			sp -= 4;                                 \
			EMU86_EMULATE_PUSH(sp, 4);               \
			EMU86_WRITE_USER_MEMORY(sp, 4);          \
			EMU86_MEMWRITEL(sp, _value);             \
		}                                            \
		EMU86_SETSTACKPTR(sp);                       \
	}	__WHILE0
#define EMU86_PUSH1632_NOSUP()                               \
	do {                                                     \
		byte_t *sp;                                          \
		IF_64BIT({                                           \
			if (EMU86_F_IS64(op_flags))                      \
				goto return_unsupported_instruction;         \
		});                                                  \
		sp = EMU86_GETSTACKPTR();                            \
		if (IS_16BIT()) {                                    \
			sp -= 2;                                         \
			EMU86_EMULATE_PUSH(sp, 2);                       \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 2, false, true); \
		} else {                                             \
			sp -= 4;                                         \
			EMU86_EMULATE_PUSH(sp, 4);                       \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 4, false, true); \
		}                                                    \
		goto return_unsupported_instruction;                 \
	}	__WHILE0
#elif EMU86_EMULATE_CONFIG_CHECKERROR
#define EMU86_PUSH1632(T, value) goto return_unsupported_instruction
#define EMU86_PUSH1632_NOSUP()   goto return_unsupported_instruction
#endif


/* 66 XX pop16
 *    XX pop32   (in 32-bit mode)
 *    XX illegal (in 64-bit mode) */
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
#define EMU86_POP1632(T, setter)                     \
	do {                                             \
		byte_t *sp;                                  \
		T _value;                                    \
		IF_64BIT({                                   \
			if (EMU86_F_IS64(op_flags))              \
				goto return_unsupported_instruction; \
		});                                          \
		sp = EMU86_GETSTACKPTR();                    \
		if (IS_16BIT()) {                            \
			EMU86_EMULATE_POP(sp, 2);                \
			EMU86_READ_USER_MEMORY(sp, 2);           \
			_value = (T)EMU86_MEMREADW(sp);          \
			sp += 2;                                 \
		} else {                                     \
			EMU86_EMULATE_POP(sp, 4);                \
			EMU86_READ_USER_MEMORY(sp, 4);           \
			_value = (T)EMU86_MEMREADL(sp);          \
			sp += 4;                                 \
		}                                            \
		setter(_value);                              \
		EMU86_SETSTACKPTR(sp);                       \
	}	__WHILE0
#define EMU86_POP1632_PEEK(T, setter)                \
	do {                                             \
		byte_t *sp;                                  \
		T _value;                                    \
		IF_64BIT({                                   \
			if (EMU86_F_IS64(op_flags))              \
				goto return_unsupported_instruction; \
		});                                          \
		sp = EMU86_GETSTACKPTR();                    \
		if (IS_16BIT()) {                            \
			EMU86_EMULATE_POP(sp, 2);                \
			EMU86_READ_USER_MEMORY(sp, 2);           \
			_value = (T)EMU86_MEMREADW(sp);          \
			sp += 2;                                 \
		} else {                                     \
			EMU86_EMULATE_POP(sp, 4);                \
			EMU86_READ_USER_MEMORY(sp, 4);           \
			_value = (T)EMU86_MEMREADL(sp);          \
			sp += 4;                                 \
		}                                            \
		setter(_value);                              \
	}	__WHILE0
#define EMU86_POP1632_NOSUP()                                \
	do {                                                     \
		byte_t *sp;                                          \
		IF_64BIT({                                           \
			if (EMU86_F_IS64(op_flags))                      \
				goto return_unsupported_instruction;         \
		});                                                  \
		sp = EMU86_GETSTACKPTR();                            \
		if (IS_16BIT()) {                                    \
			EMU86_EMULATE_POP(sp, 2);                        \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 2, true, false); \
		} else {                                             \
			EMU86_EMULATE_POP(sp, 4);                        \
			EMU86_READ_USER_MEMORY(sp, 4);                   \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 4, true, false); \
		}                                                    \
		goto return_unsupported_instruction;                 \
	}	__WHILE0
#elif EMU86_EMULATE_CONFIG_CHECKERROR
#define EMU86_POP1632(T, setter)      goto return_unsupported_instruction
#define EMU86_POP1632_PEEK(T, setter) goto return_unsupported_instruction
#define EMU86_POP1632_NOSUP()         goto return_unsupported_instruction
#endif


/* 66 XX push16
 *    XX push32 (in 32-bit mode)
 *    XX push64 (in 64-bit mode) */
#define EMU86_PUSH163264(value16, value32, value64)                    \
	do {                                                               \
		byte_t *sp;                                                    \
		sp = EMU86_GETSTACKPTR();                                      \
		if (IS_16BIT()) {                                              \
			sp -= 2;                                                   \
			EMU86_EMULATE_PUSH(sp, 2);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 2);                            \
			EMU86_MEMWRITEW(sp, value16);                              \
		}                                                              \
		IF_64BIT(else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) { \
			sp -= 8;                                                   \
			EMU86_EMULATE_PUSH(sp, 8);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 8);                            \
			EMU86_MEMWRITEQ(sp, value64);                              \
		})                                                             \
		IF_16BIT_OR_32BIT(else {                                       \
			sp -= 4;                                                   \
			EMU86_EMULATE_PUSH(sp, 4);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 4);                            \
			EMU86_MEMWRITEL(sp, value32);                              \
		})                                                             \
		EMU86_SETSTACKPTR(sp);                                         \
	}	__WHILE0

#define EMU86_PUSH163264_NOSUP()                                       \
	do {                                                               \
		byte_t *sp;                                                    \
		sp = EMU86_GETSTACKPTR();                                      \
		if (IS_16BIT()) {                                              \
			sp -= 2;                                                   \
			EMU86_EMULATE_PUSH(sp, 2);                                 \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 2, false, true);           \
		}                                                              \
		IF_64BIT(else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) { \
			sp -= 8;                                                   \
			EMU86_EMULATE_PUSH(sp, 8);                                 \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 8, false, true);           \
		})                                                             \
		IF_16BIT_OR_32BIT(else {                                       \
			sp -= 4;                                                   \
			EMU86_EMULATE_PUSH(sp, 4);                                 \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 4, false, true);           \
		})                                                             \
	}	__WHILE0

/* [66] XX push64  (in 64-bit mode)
 *  66  XX push16 (outside 64-bit mode)
 *      XX push32 (outside 64-bit mode) */
#define EMU86_PUSH163264_FORCE64(value16, value32, value64)            \
	do {                                                               \
		byte_t *sp;                                                    \
		sp = EMU86_GETSTACKPTR();                                      \
		IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {      \
			sp -= 8;                                                   \
			EMU86_EMULATE_PUSH(sp, 8);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 8);                            \
			EMU86_MEMWRITEQ(sp, value64);                              \
		} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT(if (IS_16BIT()) { \
			sp -= 2;                                                   \
			EMU86_EMULATE_PUSH(sp, 2);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 2);                            \
			EMU86_MEMWRITEW(sp, value16);                              \
		} else {                                                       \
			sp -= 4;                                                   \
			EMU86_EMULATE_PUSH(sp, 4);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 4);                            \
			EMU86_MEMWRITEL(sp, value32);                              \
		})                                                             \
		EMU86_SETSTACKPTR(sp);                                         \
	}	__WHILE0

#define EMU86_PUSH163264_FORCE64_NOSUP()                               \
	do {                                                               \
		byte_t *sp;                                                    \
		sp = EMU86_GETSTACKPTR();                                      \
		IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {      \
			sp -= 8;                                                   \
			EMU86_EMULATE_PUSH(sp, 8);                                 \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 8, false, true);           \
		} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT(if (IS_16BIT()) { \
			sp -= 2;                                                   \
			EMU86_EMULATE_PUSH(sp, 2);                                 \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 2, false, true);           \
		} else {                                                       \
			sp -= 4;                                                   \
			EMU86_EMULATE_PUSH(sp, 4);                                 \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 4, false, true);           \
		})                                                             \
	}	__WHILE0


/* 66 XX pop16
 *    XX pop32 (in 32-bit mode)
 *    XX pop64 (in 64-bit mode) */
#define EMU86_POP163264(setter16, setter32, setter64)      \
	do {                                                   \
		byte_t *sp;                                        \
		sp = EMU86_GETSTACKPTR();                          \
		EMU86_POP163264_IMPL(setter16, setter32, setter64) \
		EMU86_SETSTACKPTR(sp);                             \
	}	__WHILE0
#define EMU86_POP163264_PEEK(setter16, setter32, setter64) \
	do {                                                   \
		byte_t *sp;                                        \
		sp = EMU86_GETSTACKPTR();                          \
		EMU86_POP163264_IMPL(setter16, setter32, setter64) \
	}	__WHILE0
#define EMU86_POP163264_IMPL(setter16, setter32, setter64)             \
		if (IS_16BIT()) {                                              \
			u16 _value;                                                \
			EMU86_EMULATE_POP(sp, 2);                                  \
			EMU86_READ_USER_MEMORY(sp, 2);                             \
			_value = EMU86_MEMREADW(sp);                               \
			setter16(_value);                                          \
			sp += 2;                                                   \
		}                                                              \
		IF_64BIT(else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) { \
			u64 _value;                                                \
			EMU86_EMULATE_POP(sp, 8);                                  \
			EMU86_READ_USER_MEMORY(sp, 8);                             \
			_value = EMU86_MEMREADQ(sp);                               \
			setter64(_value);                                          \
			sp += 8;                                                   \
		})                                                             \
		IF_16BIT_OR_32BIT(else {                                       \
			u32 _value;                                                \
			EMU86_EMULATE_POP(sp, 4);                                  \
			EMU86_READ_USER_MEMORY(sp, 4);                             \
			_value = EMU86_MEMREADL(sp);                               \
			setter32(_value);                                          \
			sp += 4;                                                   \
		})


#define EMU86_POP163264_NOSUP()           \
	do {                                  \
		byte_t *sp = EMU86_GETSTACKPTR(); \
		(void)sp;                         \
		EMU86_POP163264_NOSUP_IMPL()      \
	}	__WHILE0
#define EMU86_POP163264_NOSUP_IMPL()                                   \
		if (IS_16BIT()) {                                              \
			EMU86_EMULATE_POP(sp, 2);                                  \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 2, true, false);           \
		}                                                              \
		IF_64BIT(else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) { \
			EMU86_EMULATE_POP(sp, 8);                                  \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 8, true, false);           \
		})                                                             \
		IF_16BIT_OR_32BIT(else {                                       \
			EMU86_EMULATE_POP(sp, 4);                                  \
			EMU86_UNSUPPORTED_MEMACCESS(sp, 4, true, false);           \
		})



#endif /* !_LIBEMU86_EMU_PUSHPOP_UTIL_H */
