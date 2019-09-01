/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_GDB_STUB_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_GDB_STUB_H 1
#define _KOS_KERNEL_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/debugger.h>
#include <kernel/types.h>
#include <hybrid/typecore.h>
#include <kos/kernel/cpu-state.h>

#ifndef CONFIG_NO_DEBUGGER
#ifndef CONFIG_NO_GDB
DECL_BEGIN

/* Register indices for GDB */
#define GDB_I386_REGISTER_EAX    0x00
#define GDB_I386_REGISTER_ECX    0x01
#define GDB_I386_REGISTER_EDX    0x02
#define GDB_I386_REGISTER_EBX    0x03
#define GDB_I386_REGISTER_ESP    0x04
#define GDB_I386_REGISTER_EBP    0x05
#define GDB_I386_REGISTER_ESI    0x06
#define GDB_I386_REGISTER_EDI    0x07
#define GDB_I386_REGISTER_EIP    0x08
#define GDB_I386_REGISTER_EFLAGS 0x09
#define GDB_I386_REGISTER_CS     0x0a
#define GDB_I386_REGISTER_SS     0x0b
#define GDB_I386_REGISTER_DS     0x0c
#define GDB_I386_REGISTER_ES     0x0d
#define GDB_I386_REGISTER_FS     0x0e
#define GDB_I386_REGISTER_GS     0x0f


#define GDB_TRAP_MAXPACKETSIZE   36
#ifdef __CC__
#ifndef TOHEX
PRIVATE char const __hexchars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
#define TOHEX(x)   __hexchars[x]
#endif /* !TOHEX */

LOCAL byte_t *FCALL
gdb_i386_encode_pointer(byte_t *__restrict buffer, u32 value) {
	*buffer++ = TOHEX((value & __UINT32_C(0xf0000000)) >> 28);
	*buffer++ = TOHEX((value & __UINT32_C(0x0f000000)) >> 24);
	*buffer++ = TOHEX((value & __UINT32_C(0x00f00000)) >> 20);
	*buffer++ = TOHEX((value & __UINT32_C(0x000f0000)) >> 16);
	*buffer++ = TOHEX((value & __UINT32_C(0x0000f000)) >> 12);
	*buffer++ = TOHEX((value & __UINT32_C(0x00000f00)) >> 8);
	*buffer++ = TOHEX((value & __UINT32_C(0x000000f0)) >> 4);
	*buffer++ = TOHEX((value & __UINT32_C(0x0000000f)) >> 0);
	return buffer;
}

LOCAL size_t FCALL
gdb_trap_buildpacket(byte_t buffer[GDB_TRAP_MAXPACKETSIZE], uintptr_t signo) {
	*buffer++ = 'T';
	*buffer++ = TOHEX((signo & 0xf0) >> 4);
	*buffer++ = TOHEX((signo & 0x0f));

	*buffer++ = TOHEX(GDB_I386_REGISTER_ESP);
	*buffer++ = ':';
	buffer    = gdb_i386_encode_pointer(buffer, dbg_exitstate.fcs_gpregs.gp_esp);
	*buffer++ = ';';

	*buffer++ = TOHEX(GDB_I386_REGISTER_EBP);
	*buffer++ = ':';
	buffer    = gdb_i386_encode_pointer(buffer, dbg_exitstate.fcs_gpregs.gp_ebp);
	*buffer++ = ';';

	*buffer++ = TOHEX(GDB_I386_REGISTER_EIP);
	*buffer++ = ':';
	buffer    = gdb_i386_encode_pointer(buffer, dbg_exitstate.fcs_eip);
	*buffer++ = ';';
	return GDB_TRAP_MAXPACKETSIZE;
}

#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_NO_GDB */
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_GDB_STUB_H */
