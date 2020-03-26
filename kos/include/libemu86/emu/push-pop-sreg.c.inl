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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(push_pop_sreg) {

/************************************************************************/
/* PUSH ES                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_PUSH_ES && \
      (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x06): {
#if EMU86_EMULATE_CONFIG_WANT_PUSH_ES
#if CONFIG_LIBEMU86_WANT_64BIT
#define NEED_return_unsupported_instruction
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	EMU86_PUSH1632(u16, EMU86_GETES());
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	goto done;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#else /* EMU86_EMULATE_CONFIG_WANT_PUSH_ES */
	goto notsup_pushwl;
#define NEED_notsup_pushwl
#endif /* !EMU86_EMULATE_CONFIG_WANT_PUSH_ES */
}
#endif /* ... */


/************************************************************************/
/* POP ES                                                               */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_POP_ES && \
      (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x07): {
#if EMU86_EMULATE_CONFIG_WANT_POP_ES
#if CONFIG_LIBEMU86_WANT_64BIT
#define NEED_return_unsupported_instruction
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	EMU86_POP1632(u16, EMU86_SETES);
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	goto done;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#else /* EMU86_EMULATE_CONFIG_WANT_POP_ES */
	goto notsup_popwl;
#define NEED_notsup_popwl
#endif /* !EMU86_EMULATE_CONFIG_WANT_POP_ES */
}
#endif /* ... */


/************************************************************************/
/* PUSH CS                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_PUSH_CS && \
      (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x0e): {
#if EMU86_EMULATE_CONFIG_WANT_PUSH_CS
#if CONFIG_LIBEMU86_WANT_64BIT
#define NEED_return_unsupported_instruction
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	EMU86_PUSH1632(u16, EMU86_GETCS());
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	goto done;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#else /* EMU86_EMULATE_CONFIG_WANT_PUSH_CS */
	goto notsup_pushwl;
#define NEED_notsup_pushwl
#endif /* !EMU86_EMULATE_CONFIG_WANT_PUSH_CS */
}
#endif /* ... */


/************************************************************************/
/* PUSH SS                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_PUSH_SS && \
      (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x16): {
#if EMU86_EMULATE_CONFIG_WANT_PUSH_SS
#if CONFIG_LIBEMU86_WANT_64BIT
#define NEED_return_unsupported_instruction
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	EMU86_PUSH1632(u16, EMU86_GETSS());
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	goto done;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#else /* EMU86_EMULATE_CONFIG_WANT_PUSH_SS */
	goto notsup_pushwl;
#define NEED_notsup_pushwl
#endif /* !EMU86_EMULATE_CONFIG_WANT_PUSH_SS */
}
#endif /* ... */


/************************************************************************/
/* POP SS                                                               */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_POP_SS && \
      (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x17): {
#if EMU86_EMULATE_CONFIG_WANT_POP_SS
#if CONFIG_LIBEMU86_WANT_64BIT
#define NEED_return_unsupported_instruction
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	EMU86_POP1632(u16, EMU86_SETSS);
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	goto done;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#else /* EMU86_EMULATE_CONFIG_WANT_POP_SS */
	goto notsup_popwl;
#define NEED_notsup_popwl
#endif /* !EMU86_EMULATE_CONFIG_WANT_POP_SS */
}
#endif /* ... */


/************************************************************************/
/* PUSH DS                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_PUSH_DS && \
      (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x1e): {
#if EMU86_EMULATE_CONFIG_WANT_PUSH_DS
#if CONFIG_LIBEMU86_WANT_64BIT
#define NEED_return_unsupported_instruction
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	EMU86_PUSH1632(u16, EMU86_GETDS());
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	goto done;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#else /* EMU86_EMULATE_CONFIG_WANT_PUSH_DS */
	goto notsup_pushwl;
#define NEED_notsup_pushwl
#endif /* !EMU86_EMULATE_CONFIG_WANT_PUSH_DS */
}
#endif /* ... */


/************************************************************************/
/* POP DS                                                               */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_POP_DS && \
      (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x1f): {
#if EMU86_EMULATE_CONFIG_WANT_POP_DS
#if CONFIG_LIBEMU86_WANT_64BIT
#define NEED_return_unsupported_instruction
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	EMU86_POP1632(u16, EMU86_SETDS);
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	goto done;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#else /* EMU86_EMULATE_CONFIG_WANT_POP_DS */
	goto notsup_popwl;
#define NEED_notsup_popwl
#endif /* !EMU86_EMULATE_CONFIG_WANT_POP_DS */
}
#endif /* ... */


/************************************************************************/
/* PUSH FS                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_PUSH_FS)
case EMU86_OPCODE_ENCODE(0x0fa0): {
#if EMU86_EMULATE_CONFIG_WANT_PUSH_FS
	EMU86_PUSH163264(EMU86_GETFS(),
	                 EMU86_GETFS(),
	                 EMU86_GETFS());
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_PUSH_FS */
	goto notsup_pushwlq;
#define NEED_notsup_pushwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_PUSH_FS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_PUSH_FS */


/************************************************************************/
/* POP FS                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_POP_FS)
case EMU86_OPCODE_ENCODE(0x0fa1): {
#if EMU86_EMULATE_CONFIG_WANT_POP_FS
	EMU86_POP163264(EMU86_SETFS,
	                EMU86_SETFS,
	                EMU86_SETFS);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_POP_FS */
	goto notsup_popwlq;
#define NEED_notsup_popwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_POP_FS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_POP_FS */


/************************************************************************/
/* PUSH GS                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_PUSH_GS)
case EMU86_OPCODE_ENCODE(0x0fa8): {
#if EMU86_EMULATE_CONFIG_WANT_PUSH_GS
	EMU86_PUSH163264(EMU86_GETGS(),
	                 EMU86_GETGS(),
	                 EMU86_GETGS());
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_PUSH_GS */
	goto notsup_pushwlq;
#define NEED_notsup_pushwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_PUSH_GS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_PUSH_GS */


/************************************************************************/
/* POP GS                                                              */
/************************************************************************/
#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_POP_GS)
case EMU86_OPCODE_ENCODE(0x0fa9): {
#if EMU86_EMULATE_CONFIG_WANT_POP_GS
	EMU86_POP163264(EMU86_SETGS,
	                EMU86_SETGS,
	                EMU86_SETGS);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_POP_GS */
	goto notsup_popwlq;
#define NEED_notsup_popwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_POP_GS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_POP_GS */




}
EMU86_INTELLISENSE_END
