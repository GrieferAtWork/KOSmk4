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
#include "string-util.h"

EMU86_INTELLISENSE_BEGIN(io) {

#if EMU86_EMULATE_CONFIG_CHECKUSER && !defined(EMU86_VALIDATE_IO_IS_NOOP)
#define VERIFY_USER_PORT_ACCESS(portno, num_ports) \
	do {                                           \
		if (EMU86_ISUSER())                        \
			EMU86_VALIDATE_IO(portno, num_ports);  \
	}	__WHILE0
#else /* EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_VALIDATE_IO_IS_NOOP */
#define VERIFY_USER_PORT_ACCESS(portno, num_ports) (void)0
#endif /* !EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_VALIDATE_IO_IS_NOOP */


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xe4): {
	/* E4 ib     IN AL,imm8      Input byte from imm8 I/O port address into AL. */
	u8 value;
	u8 portno;
	portno = *(u8 const *)pc;
	pc += 1;
	VERIFY_USER_PORT_ACCESS(portno, 1);
	EMU86_EMULATE_INB(portno, value);
	EMU86_SETAL(value);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xe4):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xe5): {
	/* E5 ib     IN AX,imm8      Input word from imm8 I/O port address into AX.
	 * E5 ib     IN EAX,imm8     Input dword from imm8 I/O port address into EAX. */
	u8 portno;
	portno = *(u8 const *)pc;
	pc += 1;
	if (!IS_16BIT()) {
		u32 value;
		VERIFY_USER_PORT_ACCESS(portno, 4);
		EMU86_EMULATE_INL(portno, value);
		EMU86_SETEAX(value);
	} else {
		u16 value;
		VERIFY_USER_PORT_ACCESS(portno, 2);
		EMU86_EMULATE_INW(portno, value);
		EMU86_SETAX(value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xe5):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xec): {
	/* EC        IN AL,DX        Input byte from I/O port in DX into AL. */
	u8 value;
	u16 portno = EMU86_GETDX();
	VERIFY_USER_PORT_ACCESS(portno, 1);
	EMU86_EMULATE_INB(portno, value);
	EMU86_SETAL(value);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xec):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xed): {
	/* ED        IN AX,DX        Input word from I/O port in DX into AX.
	 * ED        IN EAX,DX       Input doubleword from I/O port in DX into EAX. */
	u16 portno = EMU86_GETDX();
	if (!IS_16BIT()) {
		u32 value;
		VERIFY_USER_PORT_ACCESS(portno, 4);
		EMU86_EMULATE_INL(portno, value);
		EMU86_SETEAX(value);
	} else {
		u16 value;
		VERIFY_USER_PORT_ACCESS(portno, 2);
		EMU86_EMULATE_INW(portno, value);
		EMU86_SETAX(value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xed):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xe6): {
	/* E6 ib     OUT imm8, AL      Output byte in AL to I/O port address imm8. */
	u8 value;
	u8 portno;
	portno = *(u8 const *)pc;
	pc += 1;
	value = EMU86_GETAL();
	VERIFY_USER_PORT_ACCESS(portno, 1);
	EMU86_EMULATE_OUTB(portno, value);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xe6):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xe7): {
	/* E7 ib     OUT imm8, AX      Output word in AX to I/O port address imm8.
	 * E7 ib     OUT imm8, EAX     Output doubleword in EAX to I/O port address imm8. */
	u8 portno;
	portno = *(u8 const *)pc;
	pc += 1;
	if (!IS_16BIT()) {
		u32 value;
		value = EMU86_GETEAX();
		VERIFY_USER_PORT_ACCESS(portno, 4);
		EMU86_EMULATE_OUTL(portno, value);
	} else {
		u16 value;
		value = EMU86_GETAX();
		VERIFY_USER_PORT_ACCESS(portno, 2);
		EMU86_EMULATE_OUTW(portno, value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xe7):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xee): {
	/* EE        OUT DX, AL        Output byte in AL to I/O port address in DX. */
	u8 value;
	u16 portno;
	portno = EMU86_GETDX();
	value  = EMU86_GETAL();
	VERIFY_USER_PORT_ACCESS(portno, 1);
	EMU86_EMULATE_OUTB(portno, value);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xee):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0xef): {
	/* EF        OUT DX, AX        Output word in AX to I/O port address in DX.
	 * EF        OUT DX, EAX       Output doubleword in EAX to I/O port address in DX. */
	u16 portno = EMU86_GETDX();
	if (!IS_16BIT()) {
		u32 value;
		value = EMU86_GETEAX();
		VERIFY_USER_PORT_ACCESS(portno, 4);
		EMU86_EMULATE_OUTL(portno, value);
	} else {
		u16 value;
		value = EMU86_GETAX();
		VERIFY_USER_PORT_ACCESS(portno, 2);
		EMU86_EMULATE_OUTW(portno, value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xef):
	goto notsup_userprivileged;
#define NEED_notsup_userprivileged
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */




#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_IO
case EMU86_OPCODE_ENCODE(0x6e): {
	/* 6E     OUTSB     Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX. */
#if EMU86_EMULATE_CONFIG_WANT_IO
	u16 portno = EMU86_GETDX();
	VERIFY_USER_PORT_ACCESS(portno, 1);
#ifdef EMU86_EMULATE_OUT_IS_NOEXCEPT
	{
		u8 value;
		EMU86_READ_STRING(DS, SI, B, 8, 1,
		                  _value, value = _value);
		EMU86_EMULATE_OUTB(portno, value);
	}
#else /* EMU86_EMULATE_OUT_IS_NOEXCEPT */
	EMU86_READ_STRING(DS, SI, B, 8, 1, value,
	                  EMU86_EMULATE_OUTB(portno, value));
#endif /* !EMU86_EMULATE_OUT_IS_NOEXCEPT */
	/* Repeat the instruction */
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_IO */
	goto notsup_lodsb_userprivileged;
#define NEED_notsup_lodsb_userprivileged
#endif /* !EMU86_EMULATE_CONFIG_WANT_IO */
}


case EMU86_OPCODE_ENCODE(0x6f): {
	/* 6F     OUTSW     Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	 * 6F     OUTSD     Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX. */
#if EMU86_EMULATE_CONFIG_WANT_IO
	u16 portno = EMU86_GETDX();
	if (!IS_16BIT()) {
		VERIFY_USER_PORT_ACCESS(portno, 4);
#ifdef EMU86_EMULATE_OUT_IS_NOEXCEPT
		{
			u32 value;
			EMU86_READ_STRING(DS, SI, L, 32, 4,
			                  _value, value = _value);
			EMU86_EMULATE_OUTL(portno, value);
		}
#else /* EMU86_EMULATE_OUT_IS_NOEXCEPT */
		EMU86_READ_STRING(DS, SI, W, 32, 4, value,
		                  EMU86_EMULATE_OUTL(portno, value));
#endif /* !EMU86_EMULATE_OUT_IS_NOEXCEPT */
	} else {
		VERIFY_USER_PORT_ACCESS(portno, 2);
#ifdef EMU86_EMULATE_OUT_IS_NOEXCEPT
		{
			u16 value;
			EMU86_READ_STRING(DS, SI, W, 16, 2,
			                  _value, value = _value);
			EMU86_EMULATE_OUTW(portno, value);
		}
#else /* EMU86_EMULATE_OUT_IS_NOEXCEPT */
		EMU86_READ_STRING(DS, SI, W, 16, 2, value,
		                  EMU86_EMULATE_OUTW(portno, value));
#endif /* !EMU86_EMULATE_OUT_IS_NOEXCEPT */
	}
	/* Repeat the instruction */
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_IO */
	goto notsup_lodswlq_userprivileged;
#define NEED_notsup_lodswlq_userprivileged
#endif /* !EMU86_EMULATE_CONFIG_WANT_IO */
}


case EMU86_OPCODE_ENCODE(0x6c): {
	/* 6C     INSB      Input byte from I/O port specified in DX into memory location specified with ES:(E)DI or RDI. */
#if EMU86_EMULATE_CONFIG_WANT_IO
	u16 portno = EMU86_GETDX();
	u8 value;
	VERIFY_USER_PORT_ACCESS(portno, 1);
	EMU86_EMULATE_INB(portno, value);
	EMU86_WRITE_STRING(ES, DI, B, 8, 1, value);
	/* Repeat the instruction */
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_IO */
	goto notsup_stosb_userprivileged;
#define NEED_notsup_stosb_userprivileged
#endif /* !EMU86_EMULATE_CONFIG_WANT_IO */
}


case EMU86_OPCODE_ENCODE(0x6d): {
	/* 6D     INSW      Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.
	 * 6D     INSD      Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI. */
#if EMU86_EMULATE_CONFIG_WANT_IO
	u16 portno = EMU86_GETDX();
	if (!IS_16BIT()) {
		u32 value;
		VERIFY_USER_PORT_ACCESS(portno, 4);
		EMU86_EMULATE_INL(portno, value);
		EMU86_WRITE_STRING(ES, DI, L, 32, 4, value);
	} else {
		u16 value;
		VERIFY_USER_PORT_ACCESS(portno, 2);
		EMU86_EMULATE_INW(portno, value);
		EMU86_WRITE_STRING(ES, DI, W, 16, 2, value);
	}
	/* Repeat the instruction */
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_IO */
	goto notsup_stoswlq_userprivileged;
#define NEED_notsup_stoswlq_userprivileged
#endif /* !EMU86_EMULATE_CONFIG_WANT_IO */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_IO */


}
EMU86_INTELLISENSE_END
