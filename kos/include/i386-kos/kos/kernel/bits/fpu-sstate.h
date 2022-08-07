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
#ifndef _I386_KOS_KOS_KERNEL_BITS_FPU_SSTATE_H
#define _I386_KOS_KOS_KERNEL_BITS_FPU_SSTATE_H 1

#include <__stdinc.h>

#include <bits/types.h>

#include <ieee754.h>

__SYSDECL_BEGIN

#define OFFSET_SFPUENV_FCW   0
#define OFFSET_SFPUENV_FSW   4
#define OFFSET_SFPUENV_FTW   8
#define OFFSET_SFPUENV_FIP   12
#define OFFSET_SFPUENV_FCS   16
#define OFFSET_SFPUENV_FOP   18
#define OFFSET_SFPUENV_FDP   20
#define OFFSET_SFPUENV_FDS   24
#define SIZEOF_SFPUENV       28
#define ALIGNOF_SFPUENV      4
#ifdef __CC__
struct __ATTR_ALIGNED(ALIGNOF_SFPUENV) __ATTR_PACKED sfpuenv /*[PREFIX(fe_)]*/ {
	/* FPU environment structure, as described here:
	 *   - https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-1-manual.pdf
	 *   - https://c9x.me/x86/html/file_module_x86_id_112.html */
	__uint16_t            fe_fcw;       /* Floating point control word. (Set of `FCW_*')
	                                     * Get using `__fstcw()'/`__fnstcw()'; Set using `__fldcw()' */
	__uint16_t          __fe_pad1;      /* ... */
	__uint16_t            fe_fsw;       /* Floating point status word. (Set of `FSW_*')
	                                     * Get  using   `__fstsw()'   /   `__fnstsw()'; */
	__uint16_t          __fe_pad2;      /* ... */
	__uint16_t            fe_ftw;       /* Floating point tag word. (Indicates the contents of `fs_regs' with 2 bits per register; set of `FTW_*') */
	__uint16_t          __fe_pad3;      /* ... */
	__uint32_t            fe_fip;       /* FPU instruction pointer. */
	__uint16_t            fe_fcs;       /* FPU code segment selector. */
	__uint16_t            fe_fop;       /* Lower 11-bit f.p. opcode (bits 0:10). */
	__uint32_t            fe_fdp;       /* FPU data pointer. */
	__uint16_t            fe_fds;       /* FPU data segment selector. */
	__uint16_t          __fe_pad4;      /* ... */
};
#endif /* __CC__ */

#define OFFSET_SFPUSTATE_FCW    0
#define OFFSET_SFPUSTATE_FSW    4
#define OFFSET_SFPUSTATE___PAD2 6 /* [FIELD(__fs_pad2)] */
#define OFFSET_SFPUSTATE_FTW    8
#define OFFSET_SFPUSTATE_FIP    12
#define OFFSET_SFPUSTATE_FCS    16
#define OFFSET_SFPUSTATE_FOP    18
#define OFFSET_SFPUSTATE_FDP    20
#define OFFSET_SFPUSTATE_FDS    24
#define OFFSET_SFPUSTATE_ST(i)  (28 + (i) * 10)
#define OFFSET_SFPUSTATE_ST0    28 /* [FIELD(fs_regs[0])] */
#define OFFSET_SFPUSTATE_ST1    38 /* [FIELD(fs_regs[1])] */
#define OFFSET_SFPUSTATE_ST2    48 /* [FIELD(fs_regs[2])] */
#define OFFSET_SFPUSTATE_ST3    58 /* [FIELD(fs_regs[3])] */
#define OFFSET_SFPUSTATE_ST4    68 /* [FIELD(fs_regs[4])] */
#define OFFSET_SFPUSTATE_ST5    78 /* [FIELD(fs_regs[5])] */
#define OFFSET_SFPUSTATE_ST6    88 /* [FIELD(fs_regs[6])] */
#define OFFSET_SFPUSTATE_ST7    98 /* [FIELD(fs_regs[7])] */
#define OFFSET_SFPUSTATE_MM(i)  (28 + (i) * 10)
#define OFFSET_SFPUSTATE_MM0    28 /* [FIELD(fs_regs[0])] */
#define OFFSET_SFPUSTATE_MM1    38 /* [FIELD(fs_regs[1])] */
#define OFFSET_SFPUSTATE_MM2    48 /* [FIELD(fs_regs[2])] */
#define OFFSET_SFPUSTATE_MM3    58 /* [FIELD(fs_regs[3])] */
#define OFFSET_SFPUSTATE_MM4    68 /* [FIELD(fs_regs[4])] */
#define OFFSET_SFPUSTATE_MM5    78 /* [FIELD(fs_regs[5])] */
#define OFFSET_SFPUSTATE_MM6    88 /* [FIELD(fs_regs[6])] */
#define OFFSET_SFPUSTATE_MM7    98 /* [FIELD(fs_regs[7])] */
#define SIZEOF_SFPUSTATE        108
#define ALIGNOF_SFPUSTATE       4
#ifdef __CC__
#undef fs_env
#undef fs_fcw
#undef fs_fsw
#undef fs_ftw
#undef fs_fip
#undef fs_fcs
#undef fs_fop
#undef fs_fdp
#undef fs_fds
struct __ATTR_ALIGNED(ALIGNOF_SFPUSTATE) __ATTR_PACKED sfpustate /*[PREFIX(fs_)]*/ {
	/* FPU context structure, as described here:
	 *   - https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-1-manual.pdf
	 *   - https://c9x.me/x86/html/file_module_x86_id_112.html */
	union __ATTR_ALIGNED(ALIGNOF_SFPUENV) __ATTR_PACKED {
		struct sfpuenv            fs_env;     /* FPU environment */
		struct __ATTR_PACKED {
			__uint16_t            fs_fcw;     /* Floating point control word. (Set of `FCW_*')
			                                   * Get using `__fstcw()'/`__fnstcw()'; Set using `__fldcw()' */
			__uint16_t          __fs_pad1;    /* ... */
			__uint16_t            fs_fsw;     /* Floating point status word. (Set of `FSW_*')
			                                   * Get  using   `__fstsw()'   /   `__fnstsw()'; */
			/* NOTE: We use  `__fs_pad2 == 0xffff' <=>  is-a-sfpustate as  indicator
			 *       for sfpustate vs.  xfpustate. All that's  needed is that  every
			 *       time sfpustate is created, we follow up with __fs_pad2 = 0xffff
			 * `sfpustate::__fs_pad2'  overlaps  with `xfpustate::fx_fop',  which  is an
			 * 11-bit field who's upper 5 bits are undefined, meaning that by  following
			 * up the creation  of a  xfpustate with `fx_fop &= 0x07ff',  we can  ensure
			 * that there exists a fixed, detectable difference between the two structs. */
			__uint16_t          __fs_pad2;    /* ... */
			__uint16_t            fs_ftw;     /* Floating point tag word. (Indicates the contents of `fs_regs' with 2 bits per register; set of `FTW_*') */
			__uint16_t          __fs_pad3;    /* ... */
			__uint32_t            fs_fip;     /* FPU instruction pointer. */
			__uint16_t            fs_fcs;     /* FPU code segment selector. */
			__uint16_t            fs_fop;     /* Lower 11-bit f.p. opcode (bits 0:10). */
			__uint32_t            fs_fdp;     /* FPU data pointer. */
			__uint16_t            fs_fds;     /* FPU data segment selector. */
			__uint16_t          __fs_pad4;    /* ... */
		}
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
		_fs_env_struct
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
		;
	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_fs_env_union
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
	union ieee854_float80         fs_regs[8]; /* ST(i) / STi / MMi */
};

#if !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && !defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#define fs_env _fs_env_union.fs_env
#define fs_fcw _fs_env_union._fs_env_struct.fs_fcw
#define fs_fsw _fs_env_union._fs_env_struct.fs_fsw
#define fs_ftw _fs_env_union._fs_env_struct.fs_ftw
#define fs_fip _fs_env_union._fs_env_struct.fs_fip
#define fs_fcs _fs_env_union._fs_env_struct.fs_fcs
#define fs_fop _fs_env_union._fs_env_struct.fs_fop
#define fs_fdp _fs_env_union._fs_env_struct.fs_fdp
#define fs_fds _fs_env_union._fs_env_struct.fs_fds
#elif !defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#define fs_env _fs_env_union.fs_env
#define fs_fcw _fs_env_union.fs_fcw
#define fs_fsw _fs_env_union.fs_fsw
#define fs_ftw _fs_env_union.fs_ftw
#define fs_fip _fs_env_union.fs_fip
#define fs_fcs _fs_env_union.fs_fcs
#define fs_fop _fs_env_union.fs_fop
#define fs_fdp _fs_env_union.fs_fdp
#define fs_fds _fs_env_union.fs_fds
#elif !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
#define fs_fcw _fs_env_struct.fs_fcw
#define fs_fsw _fs_env_struct.fs_fsw
#define fs_ftw _fs_env_struct.fs_ftw
#define fs_fip _fs_env_struct.fs_fip
#define fs_fcs _fs_env_struct.fs_fcs
#define fs_fop _fs_env_struct.fs_fop
#define fs_fdp _fs_env_struct.fs_fdp
#define fs_fds _fs_env_struct.fs_fds
#endif

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_BITS_FPU_SSTATE_H */
