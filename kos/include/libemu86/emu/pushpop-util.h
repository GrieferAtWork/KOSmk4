/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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
 *    XX push32  (in 32-bit mode)
 *    XX illegal (in 64-bit mode) */
#define EMU86_PUSH1632(T, value)                 \
	do {                                         \
		byte_t *sp;                              \
		T _value;                                \
		IF_64BIT({                               \
			if (EMU86_F_IS64(op_flags))          \
				goto return_unknown_instruction; \
		});                                      \
		_value = (value);                        \
		sp     = (byte_t *)EMU86_GETSP();        \
		if (IS_16BIT()) {                        \
			sp -= 2;                             \
			EMU86_EMULATE_PUSH(sp, 2);           \
			EMU86_WRITE_USER_MEMORY(sp, 2);      \
			EMU86_EMULATE_WRITEW(sp, _value);    \
		} else {                                 \
			sp -= 4;                             \
			EMU86_EMULATE_PUSH(sp, 4);           \
			EMU86_WRITE_USER_MEMORY(sp, 4);      \
			EMU86_EMULATE_WRITEL(sp, _value);    \
		}                                        \
		EMU86_SETSP(sp);                         \
	} __WHILE0


/* 66 XX pop16
 *    XX pop32   (in 32-bit mode)
 *    XX illegal (in 64-bit mode) */
#define EMU86_POP1632(T, setter)                 \
	do {                                         \
		byte_t *sp;                              \
		T _value;                                \
		IF_64BIT({                               \
			if (EMU86_F_IS64(op_flags))          \
				goto return_unknown_instruction; \
		});                                      \
		sp = (byte_t *)EMU86_GETSP();            \
		if (IS_16BIT()) {                        \
			EMU86_EMULATE_POP(sp, 2);            \
			EMU86_READ_USER_MEMORY(sp, 2);       \
			_value = (T)EMU86_EMULATE_READW(sp); \
			sp += 2;                             \
		} else {                                 \
			EMU86_EMULATE_POP(sp, 4);            \
			EMU86_READ_USER_MEMORY(sp, 4);       \
			_value = (T)EMU86_EMULATE_READL(sp); \
			sp += 4;                             \
		}                                        \
		setter(_value);                          \
		EMU86_SETSP(sp);                         \
	} __WHILE0


/* 66 XX push16
 *    XX push32  (in 32-bit mode)
 *    XX push64  (in 64-bit mode) */
#define EMU86_PUSH163264(value16, value32, value64)                    \
	do {                                                               \
		byte_t *sp;                                                    \
		sp = (byte_t *)EMU86_GETSP();                                  \
		if (IS_16BIT()) {                                              \
			sp -= 2;                                                   \
			EMU86_EMULATE_PUSH(sp, 2);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 2);                            \
			EMU86_EMULATE_WRITEW(sp, value16);                         \
		}                                                              \
		IF_64BIT(else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) { \
			sp -= 8;                                                   \
			EMU86_EMULATE_PUSH(sp, 8);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 8);                            \
			EMU86_EMULATE_WRITEQ(sp, value64);                         \
		})                                                             \
		IF_16BIT_OR_32BIT(else {                                       \
			sp -= 4;                                                   \
			EMU86_EMULATE_PUSH(sp, 4);                                 \
			EMU86_WRITE_USER_MEMORY(sp, 4);                            \
			EMU86_EMULATE_WRITEL(sp, value32);                         \
		})                                                             \
		EMU86_SETSP(sp);                                               \
	} __WHILE0

/* 66 XX pop16
 *    XX pop32  (in 32-bit mode)
 *    XX pop64  (in 64-bit mode) */
#define EMU86_POP163264(setter16, setter32, setter64)                  \
	do {                                                               \
		byte_t *sp;                                                    \
		sp = (byte_t *)EMU86_GETSP();                                  \
		if (IS_16BIT()) {                                              \
			u16 value;                                                 \
			EMU86_EMULATE_POP(sp, 2);                                  \
			EMU86_READ_USER_MEMORY(sp, 2);                             \
			value = EMU86_EMULATE_READW(sp);                           \
			setter16(value);                                           \
			sp += 2;                                                   \
		}                                                              \
		IF_64BIT(else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) { \
			u64 value;                                                 \
			EMU86_EMULATE_POP(sp, 8);                                  \
			EMU86_READ_USER_MEMORY(sp, 8);                             \
			value = EMU86_EMULATE_READQ(sp);                           \
			setter64(value);                                           \
			sp += 8;                                                   \
		})                                                             \
		IF_16BIT_OR_32BIT(else {                                       \
			u32 value;                                                 \
			EMU86_EMULATE_POP(sp, 4);                                  \
			EMU86_READ_USER_MEMORY(sp, 4);                             \
			value = EMU86_EMULATE_READL(sp);                           \
			setter32(value);                                           \
			sp += 4;                                                   \
		})                                                             \
		EMU86_SETSP(sp);                                               \
	} __WHILE0



#endif /* !_LIBEMU86_EMU_PUSHPOP_UTIL_H */
