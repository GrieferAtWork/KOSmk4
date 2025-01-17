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
#ifndef _LIBEMU86_EMU_STRING_UTIL_H
#define _LIBEMU86_EMU_STRING_UTIL_H 1

#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

/* Read a from %DS:%(|E|R)SI into a variant `value', then expand `useval<addrsize>',
 * and write-back the incremented/decremented  (based on EFLAGS.DF) string  pointer.
 * Also handle a `rep' prefix when `isrep' evaluates to non-zero. */
#define EMU86_READ_STRING(DS, SI, BWLQ, Nbits, Nbytes, value, useval) \
	EMU86_READ_STRING_EX(DS, SI, BWLQ, Nbits, Nbytes, value,          \
	                     op_flags & EMU86_F_REP, useval)
#define EMU86_READ_STRING_EX(DS, SI, BWLQ, Nbits, Nbytes,      \
                             value, isrep, useval)             \
	do {                                                       \
		u##Nbits value;                                        \
		EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH,       \
		                          DS, SI, BWLQ, Nbits, Nbytes, \
		                          value, isrep, useval)        \
	}	__WHILE0
#define EMU86_READ_STRING_EX_IMPL(addrsize_switch,              \
                                  DS, SI, BWLQ, Nbits, Nbytes,  \
                                  value, isrep, useval)         \
	{                                                           \
		EMU86_UREG_TYPE ptrreg;                                 \
		byte_t *addr;                                           \
		addrsize_switch({                                       \
			if ((isrep) && EMU86_GETRCX() == 0)                 \
				goto done;                                      \
			ptrreg = EMU86_GETR##SI();                          \
			addr = (byte_t *)ptrreg;                            \
		}, {                                                    \
			if ((isrep) && EMU86_GETECX() == 0)                 \
				goto done;                                      \
			ptrreg = EMU86_GETE##SI();                          \
			addr = EMU86_SEGADDR(EMU86_GET##DS##BASE(),         \
			                     (u32)ptrreg);                  \
		}, {                                                    \
			if ((isrep) && EMU86_GETCX() == 0)                  \
				goto done;                                      \
			ptrreg = EMU86_GET##SI();                           \
			addr = EMU86_SEGADDR(EMU86_GET##DS##BASE(),         \
			                     (u16)ptrreg);                  \
		})                                                      \
		EMU86_READ_USER_MEMORY(addr, Nbytes);                   \
		value = EMU86_MEMREAD##BWLQ(addr);                      \
		useval;                                                 \
		if (EMU86_GETFLAGS() & EFLAGS_DF) {                     \
			ptrreg -= Nbytes;                                   \
		} else {                                                \
			ptrreg += Nbytes;                                   \
		}                                                       \
		addrsize_switch({                                       \
			EMU86_SETR##SI(ptrreg);                             \
			if (isrep) {                                        \
				u64 rcx = EMU86_GETRCX() - 1;                   \
				EMU86_SETRCX(rcx);                              \
				if (!rcx)                                       \
					goto done;                                  \
			}                                                   \
		}, {                                                    \
			EMU86_SETE##SI(ptrreg);                             \
			if (isrep) {                                        \
				u32 ecx = EMU86_GETECX() - 1;                   \
				EMU86_SETECX(ecx);                              \
				if (!ecx)                                       \
					goto done;                                  \
			}                                                   \
		}, {                                                    \
			EMU86_SET##SI(ptrreg);                              \
			if (isrep) {                                        \
				u16 cx = EMU86_GETCX() - 1;                     \
				EMU86_SETCX(cx);                                \
				if (!cx)                                        \
					goto done;                                  \
			}                                                   \
		})                                                      \
	}


/* Write   `value'   to   %ES:%(|E|R)DI,   and   write-back   the
 * incremented/decremented (based on  EFLAGS.DF) string  pointer.
 * Also handle a `rep' prefix when `isrep' evaluates to non-zero. */
#define EMU86_WRITE_STRING(ES, DI, BWLQ, Nbits, Nbytes, value) \
	EMU86_WRITE_STRING_EX(ES, DI, BWLQ, Nbits, Nbytes, value, op_flags & EMU86_F_REP)
#define EMU86_WRITE_STRING_EX(ES, DI, BWLQ, Nbits, Nbytes, value, isrep) \
	do {                                                                 \
		EMU86_WRITE_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH, ES, DI, BWLQ,  \
		                           Nbits, Nbytes, value, isrep)          \
	}	__WHILE0
#define EMU86_WRITE_STRING_EX_IMPL(addrsize_switch, ES, DI, BWLQ, \
                                   Nbits, Nbytes, value, isrep)   \
	{                                                             \
		EMU86_UREG_TYPE ptrreg;                                   \
		byte_t *addr;                                             \
		addrsize_switch({                                         \
			if ((isrep) && EMU86_GETRCX() == 0)                   \
				goto done;                                        \
			ptrreg = EMU86_GETR##DI();                            \
			addr = (byte_t *)ptrreg;                              \
		}, {                                                      \
			if ((isrep) && EMU86_GETECX() == 0)                   \
				goto done;                                        \
			ptrreg = EMU86_GETE##DI();                            \
			addr = EMU86_SEGADDR(EMU86_GET##ES##BASE(),           \
			                     (u32)ptrreg);                    \
		}, {                                                      \
			if ((isrep) && EMU86_GETCX() == 0)                    \
				goto done;                                        \
			ptrreg = EMU86_GET##DI();                             \
			addr = EMU86_SEGADDR(EMU86_GET##ES##BASE(),           \
			                     (u16)ptrreg);                    \
		})                                                        \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                    \
		EMU86_MEMWRITE##BWLQ(addr, value);                        \
		if (EMU86_GETFLAGS() & EFLAGS_DF) {                       \
			ptrreg -= Nbytes;                                     \
		} else {                                                  \
			ptrreg += Nbytes;                                     \
		}                                                         \
		addrsize_switch({                                         \
			EMU86_SETR##DI(ptrreg);                               \
			if (isrep) {                                          \
				u64 rcx = EMU86_GETRCX() - 1;                     \
				EMU86_SETRCX(rcx);                                \
				if (!rcx)                                         \
					goto done;                                    \
			}                                                     \
		}, {                                                      \
			EMU86_SETE##DI(ptrreg);                               \
			if (isrep) {                                          \
				u32 ecx = EMU86_GETECX() - 1;                     \
				EMU86_SETECX(ecx);                                \
				if (!ecx)                                         \
					goto done;                                    \
			}                                                     \
		}, {                                                      \
			EMU86_SET##DI(ptrreg);                                \
			if (isrep) {                                          \
				u16 cx = EMU86_GETCX() - 1;                       \
				EMU86_SETCX(cx);                                  \
				if (!cx)                                          \
					goto done;                                    \
			}                                                     \
		})                                                        \
	}


#define EMU86_PSIPDIn_LOAD_POINTERS(psi, pdi, psi_addr, pdi_addr, isrep) \
	EMU86_ADDRSIZE_SWITCH64({                                            \
		if ((isrep) && EMU86_GETRCX() == 0)                              \
			goto done;                                                   \
		psi      = EMU86_GETRSI();                                       \
		pdi      = EMU86_GETRDI();                                       \
		psi_addr = (byte_t *)psi;                                        \
		pdi_addr = (byte_t *)pdi;                                        \
	}, {                                                                 \
		if ((isrep) && EMU86_GETECX() == 0)                              \
			goto done;                                                   \
		psi      = EMU86_GETESI();                                       \
		pdi      = EMU86_GETEDI();                                       \
		psi_addr = EMU86_SEGADDR(EMU86_GETDSBASE(), (u32)psi);           \
		pdi_addr = EMU86_SEGADDR(EMU86_GETESBASE(), (u32)pdi);           \
	}, {                                                                 \
		if ((isrep) && EMU86_GETCX() == 0)                               \
			goto done;                                                   \
		psi      = EMU86_GETSI();                                        \
		pdi      = EMU86_GETDI();                                        \
		psi_addr = EMU86_SEGADDR(EMU86_GETDSBASE(), (u16)psi);           \
		pdi_addr = EMU86_SEGADDR(EMU86_GETESBASE(), (u16)pdi);           \
	})

#define EMU86_PSIPDIn_SAVE_POINTERS(psi, pdi, isrep) \
	EMU86_ADDRSIZE_SWITCH64({                        \
		EMU86_SETRSI(psi);                           \
		EMU86_SETRDI(pdi);                           \
		if (isrep) {                                 \
			u64 rcx = EMU86_GETRCX() - 1;            \
			EMU86_SETRCX(rcx);                       \
			if (!rcx)                                \
				goto done;                           \
		}                                            \
	}, {                                             \
		EMU86_SETESI(psi);                           \
		EMU86_SETEDI(pdi);                           \
		if (isrep) {                                 \
			u32 ecx = EMU86_GETECX() - 1;            \
			EMU86_SETECX(ecx);                       \
			if (!ecx)                                \
				goto done;                           \
		}                                            \
	}, {                                             \
		EMU86_SETSI(psi);                            \
		EMU86_SETDI(pdi);                            \
		if (isrep) {                                 \
			u16 cx = EMU86_GETCX() - 1;              \
			EMU86_SETCX(cx);                         \
			if (!cx)                                 \
				goto done;                           \
		}                                            \
	})


#endif /* !_LIBEMU86_EMU_STRING_UTIL_H */
