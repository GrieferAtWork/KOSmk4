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
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(xlatb) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XLATB
case EMU86_OPCODE_ENCODE(0xd7): {
	/*         D7     XLAT m8     Set AL to memory byte DS:[(E)BX + unsigned AL].
	 *         D7     XLATB       Set AL to memory byte DS:[(E)BX + unsigned AL].
	 * REX.W + D7     XLATB       Set AL to memory byte [RBX + unsigned AL]. */
	byte_t *baseaddr;
	u8 al = EMU86_GETAL();
#ifdef EMU86_GETSEGBASE_IS_NOOP_DS
	EMU86_ADDRSIZE_SWITCH({
		baseaddr = (byte_t *)(uintptr_t)EMU86_GETRBX();
	}, {
		baseaddr = (byte_t *)(uintptr_t)EMU86_GETEBX();
	}, {
		baseaddr = (byte_t *)(uintptr_t)EMU86_GETBX();
	});
	baseaddr += al;
#else /* EMU86_GETSEGBASE_IS_NOOP_DS */
	EMU86_ADDRSIZE_SWITCH({
		baseaddr = (byte_t *)EMU86_GETRBX() + al;
	}, {
		baseaddr = EMU86_SEGADDR(EMU86_GETDSBASE(), EMU86_GETEBX() + al);
	}, {
		baseaddr = EMU86_SEGADDR(EMU86_GETDSBASE(), EMU86_GETBX() + al);
	});
#endif /* !EMU86_GETSEGBASE_IS_NOOP_DS */
	(void)baseaddr;
#if EMU86_EMULATE_CONFIG_WANT_XLATB
	/* Read memory from the specified address */
	{
		u8 value;
		EMU86_READ_USER_MEMORY(baseaddr, 1);
		value = EMU86_MEMREADB(baseaddr);
		EMU86_SETAL(value);
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_XLATB */
	EMU86_UNSUPPORTED_MEMACCESS(baseaddr, 1, true, false);
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_XLATB */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XLATB */


}
EMU86_INTELLISENSE_END
