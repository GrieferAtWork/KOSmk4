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

#include "pushpop-util.h"

EMU86_INTELLISENSE_BEGIN(loop) {


#ifndef EMU86_EMULATE_ONLY_MEMORY

case 0xe0: {
	/* E0 cb     LOOPNE rel8     Decrement count; jump short if count!=0 and ZF=0. */
	if ((EMU86_GETFLAGS() & EFLAGS_ZF) != 0) {
		pc += 1;
		goto done; /* Don't jump */
	}
	goto do_loop;
}


case 0xe1: {
	/* E1 cb     LOOPE rel8      Decrement count; jump short if count!=0 and ZF=1. */
	if ((EMU86_GETFLAGS() & EFLAGS_ZF) == 0) {
		pc += 1;
		goto done; /* Don't jump */
	}
	goto do_loop;
}


case 0xe2: {
	/* E2 cb     LOOP rel8       Decrement count; jump short if count!=0. */
	s8 offset;
do_loop:
	offset = *(s8 *)pc;
	pc += 1;
	EMU86_ADDRSIZE_SWITCH({
		u64 rax;
		rax = EMU86_GETRAX() - 1;
		EMU86_SETRAX(rax);
		if (!rax)
			goto done;
	}, {
		u32 eax;
		eax = EMU86_GETEAX() - 1;
		EMU86_SETEAX(eax);
		if (!eax)
			goto done;
	}, {
		u16 ax;
		ax = EMU86_GETAX() - 1;
		EMU86_SETAX(ax);
		if (!ax)
			goto done;
	});
	{
		EMU86_UREG_TYPE dest_ip;
		dest_ip = REAL_IP() + offset;
		if (IS_16BIT())
			dest_ip &= 0xffff;
		EMU86_SETIPREG(dest_ip);
	}
	goto done_dont_set_pc;
}

#endif /* !EMU86_EMULATE_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
