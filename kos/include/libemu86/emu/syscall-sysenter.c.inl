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

EMU86_INTELLISENSE_BEGIN(syscall_sysenter) {

#ifndef EMU86_EMULATE_ONLY_MEMORY

#if CONFIG_LIBEMU86_WANT_64BIT
#ifdef EMU86_EMULATE_RETURN_AFTER_SYSCALL
case 0x0f05: {
	/* 0F 05     SYSCALL     Fast call to privilege level 0 system procedures. */
	if unlikely(op_flags & EMU86_F_LOCK)
		goto return_unknown_instruction;
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	if unlikely(!EMU86_F_IS64(op_flags))
		goto return_unknown_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_SYSCALL();
	__builtin_unreachable();
}
#endif /* EMU86_EMULATE_RETURN_AFTER_SYSCALL */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#ifdef EMU86_EMULATE_RETURN_AFTER_SYSENTER
case 0x0f34: {
	/* 0F 34     SYSENTER     Fast call to privilege level 0 system procedures. */
	if unlikely(op_flags & EMU86_F_LOCK)
		goto return_unknown_instruction;
#if CONFIG_LIBEMU86_WANT_16BIT
	/* Intel documents that sysenter cannot be used from
	 * real-mode (i.e. 16-bit mode, or in this case: vm86) */
	if unlikely(EMU86_F_IS16(op_flags))
		goto return_unknown_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
	/* Canonically, sysenter override the return IP, so no need to write it back here! */
	/*EMU86_SETPCPTR(REAL_IP());*/
	EMU86_EMULATE_RETURN_AFTER_SYSENTER();
	__builtin_unreachable();
}
#endif /* EMU86_EMULATE_RETURN_AFTER_SYSENTER */

#endif /* !EMU86_EMULATE_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
