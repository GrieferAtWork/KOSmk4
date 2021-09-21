/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C
#define GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C 1
#define _KOS_SOURCE 1
#define _LIBC_SOURCE 1 /* For `__USE_PTHREAD_INTERNALS' */

#include "../../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <bits/crt/pthreadtypes.h>
#include <kos/except.h>
#include <kos/syscalls.h>
#include <kos/types.h>

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include <libgen86/gen.h>
#include <libservice/client.h>

#include "../../com.h"

DECL_BEGIN

#ifndef __LIBC_CONFIG_HAVE_USERPROCMASK
#error "Generated wrapper functions assume that userprocmask is available and supported!"
#endif /* !__LIBC_CONFIG_HAVE_USERPROCMASK */

/*
 * Function arguments are serialized (and potentially deserialized) as follows:
 *   - SERVICE_TYPE_386_R32:      putl(VALUE);
 *   - SERVICE_TYPE_386_R64:      putl(VALUE & 0xffffffff); putl((VALUE >> 32) & 0xffffffff);
 *   - SERVICE_TYPE_X86_64_R64:   putq(VALUE);
 *   - SERVICE_TYPE_STR_IN:       putP(MAP_BUFFER_DATA(VALUE, (strlen(VALUE) + 1) * sizeof(char)).offset_in_shm);
 *   - SERVICE_TYPE_ARGBUF_IN:    putP(MAP_BUFFER_DATA(VALUE, (size_t)PARAMS[sizearg_index]).offset_in_shm);
 *   - SERVICE_TYPE_ARGBUF_OUT:   putP(ALLOC_BUFFER_DATA((size_t)PARAMS[sizearg_index]).offset_in_shm);
 *   - SERVICE_TYPE_ARGBUF_INOUT: putP(MAP_BUFFER_DATA(VALUE, (size_t)PARAMS[sizearg_index]).offset_in_shm);
 *   - SERVICE_TYPE_FIXBUF_IN:    putP(MAP_BUFFER_DATA(VALUE, BUFFER_SIZE).offset_in_shm);
 *   - SERVICE_TYPE_FIXBUF_OUT:   putP(ALLOC_BUFFER_DATA(BUFFER_SIZE).offset_in_shm);
 *   - SERVICE_TYPE_FIXBUF_INOUT: putP(MAP_BUFFER_DATA(VALUE, BUFFER_SIZE).offset_in_shm);
 *
 * Deserialization only does anything for out and in/out buffer arguments, where it will
 * copy back data from the SHM buffer to the user's buffer (unless the user's buffer was
 * located within SHM (s.a. `service_buffer_malloc()')).
 *
 * Serialized data is stored as a tightly packed datastream
 * in `service_com::sc_generic::g_data'. Because all values
 * written to this  stream are 4  bytes long, alignment  is
 * always guarantied  as `struct service_com'  also has  an
 * alignment at least  that large (and  the `g_data'  field
 * is at an offset that is a multiple of `4') */
STATIC_ASSERT(IS_ALIGNED(offsetof(struct service_com, sc_generic.g_data), 4));


#define IS_NONBUFFER_TYPE(typ)                                                                    \
	((((typ) & _SERVICE_TYPE_CLASSMASK) == (_SERVICE_TYPE_ARCH_MIN & _SERVICE_TYPE_CLASSMASK)) && \
	 (((typ) & _SERVICE_TYPE_PARAMMASK) >= (_SERVICE_TYPE_ARCH_MIN & _SERVICE_TYPE_PARAMMASK)))

#ifdef __x86_64__
#define REGISTER_ARGUMENT_COUNT COMPILER_LENOF(sysvabi_registers)
static uint8_t const sysvabi_registers[] = {
	GEN86_R_RDI, GEN86_R_RSI, GEN86_R_RDX,
	GEN86_R_RCX, GEN86_R_R8, GEN86_R_R9
};
#else /* __x86_64__ */
#define REGISTER_ARGUMENT_COUNT 0
#endif /* !__x86_64__ */

#define USE_LODS_THRESHOLD 2 /* Use `lodsP' for stack arguments when there are at least this many word-sized reads */
#define USE_STOS_THRESHOLD 4 /* Use `stosP' when there are at least this many word-sized writes */


/* Auxiliary helper function called by wrapper functions. */
PRIVATE void FCALL
aux_check_pending_signals(struct pthread *__restrict me) {
	unsigned int i;
	sigset_t *sigmaskptr;
	ATOMIC_AND(me->pt_pmask.lpm_pmask.pm_flags, ~USERPROCMASK_FLAG_HASPENDING);
	sigmaskptr = me->pt_pmask.lpm_pmask.pm_sigmask;
	for (i = 0; i < __SIGSET_NWORDS; ++i) {
		ulongptr_t pending_word;
		ulongptr_t newmask_word;
		pending_word = ATOMIC_READ(me->pt_pmask.lpm_pmask.pm_pending.__val[i]);
		if (!pending_word)
			continue; /* Nothing pending in here. */

		/* Check if any of the pending signals are currently unmasked. */
		newmask_word = sigmaskptr->__val[i];
		if ((pending_word & ~newmask_word) != 0) {

			/* Clear the set of pending signals (because the kernel won't do this)
			 * Also  note that  there is no  guaranty that the  signal that became
			 * available in the mean time is still available now. - The signal may
			 * have  been directed at  our process as a  whole, and another thread
			 * may have already handled it. */
			sigemptyset(&me->pt_pmask.lpm_pmask.pm_pending);

			/* Calls the kernel's `sigmask_check()' function */
			sys_sigmask_check();
			break;
		}
	}
}




/* Implemented  by  arch-specific code:  Assemble  a custom
 * function that invokes a function as specified by `info',
 * returning a pointer to the base of said function.
 * @param: info:   Information about the function to-be called.
 * @param: result: [in|out] Buffer   storage   info.   Actually   used   buffer
 *                 sizes  are  written  back  to  `swb_txsiz'  and  `swb_ehsiz'
 *                 prior to returning `LIBSERVICE_DLSYM_CREATE_WRAPPER_SUCCESS'
 * @param: flags:  Set of `SERVICE_WRAPPER_FLAG_*'
 * @return: * : One of `LIBSERVICE_DLSYM_CREATE_WRAPPER_*' */
INTDEF WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW(CC libservice_dlsym_create_wrapper)(struct service *__restrict self,
                                            struct service_com_funinfo const *__restrict info,
                                            struct service_wrapper_buffer *__restrict buffers,
                                            unsigned int flags) {
	/* The stack-frame of a wrapper function looks like this:
	 *
	 *      CFA+locvar_cfa_offset              [<start of locals>]
	 *                           +0*P           sigset_t *oldset;   # Old signal maks pointer (return value of `setsigmaskfullptr()')
	 *                           +1*P           pthread_t me;       # Return value of `pthread_self()'
	 *                                          ...                 # TODO: Information about user-buffer locations
	 *      CFA+locvar_cfa_offset+locvar_size  [<end of locals>]
	 *                                          ...                 # Additional register/argument save area
	 *  /   CFA-3*P                            [SAVED: %Pbx]        # %Pbx is used for `R_service_com'
	 *  |   CFA-2*P                            [SAVED: %Pbp]        # %Pbp is used for `R_service_shm_handle'
	 *  |   CFA-1*P                            [RETURN_PC]
	 *  |   CFA                                [STACK_ARG[0]]
	 *  |   CFA+1*P                            [STACK_ARG[1]]
	 *  |                                       ...
	 *  \   CFA+n*P                            [STACK_ARG[n]]
	 *
	 * Where CFA == (%Psp + cfa_offset)
	 * Where P   == sizeof(void *)
	 *
	 *
	 * Assembly implementation of wrapper functions:
	 *
	 * >>     .cfi_startproc
	 * >> .Ltx_lazy_init_userprocmask_entry:
	 * >>     .cfi_def_cfa_offset <...>
	 * >>     .cfi_offset ...  // For registered also pushed below...
	 * >>     leaP   {offsetof(struct pthread, pt_pmask.lpm_masks[0])}(%Pax), %Pdx
	 * >>     movP   %Pdx, {offsetof(struct pthread, pt_pmask.lpm_pmask.pm_sigmask)}(%Pax)
	 * >>     leaP   {offsetof(struct pthread, pt_pmask.lpm_pmask)}(%Pax), %PSYSCALL_REG0
	 * >>     movP   $SYS_set_userprocmask_address, %Pax
	 * >>     std
	 * >>     .cfi_escape  [[[{register='%Pflags'} push %Pflags; and ~$EFLAGS_DF;]]]
	 * >>     syscall  // Or int80h
	 * >>     .cfi_restore %Pflags
	 * >>     cld
	 * >>     movP   0(%Psp), %Pax
	 * >>     jmp    .Ltx_lazy_init_userprocmask_ret
	 * >>
	 * >> ENTRY:
	 * >>     .cfi_def_cfa_offset 0
	 * >>
	 * >> // Save registers & allocate stack space
	 * >>     pushP_cfi_r %Pbp        # %Pbp is used for `R_service_shm_handle'
	 * >>     pushP_cfi_r %Pbx        # %Pbx is used for `R_service_com'
	 * >>     ...                     # Additional registers are pushed here (including all argument registers on x86_64)
	 * >>     subP   $<LOCVAR_SPACE>, %Psp
	 * >>
	 * >> // Disable preemption
	 * >>     // TODO: Instead of all of this libc-internals-reliant nonsense, export 2 functions
	 * >>     //       from libc under [crt_impl_if(defined(__LIBC_CONFIG_HAVE_USERPROCMASK))]:
	 * >>     //       >> struct userprocmask *getuserprocmask(void); // Returns initialized `&pthread_self()->pt_pmask.lpm_pmask'
	 * >>     //       >> void chkuserprocmask(void);                 // Does the job of `aux_check_pending_signals(pthread_self())'
	 * >>     // Unlike the other sigmaskptr functions, these only get exported when the kernel is
	 * >>     // configured for userprocmask support (iow: `#ifdef __NR_set_userprocmask_address')!
	 * >>     call   pthread_self
	 * >>     pushP_cfi %Pax          # Local variable: `pthread_t me'
	 * >>     movP   {offsetof(struct pthread, pt_pmask.lpm_pmask.pm_sigmask)}(%Pax), %Pdx
	 * >>     testP  %Pdx, %Pdx
	 * >>     jz     .Ltx_lazy_init_userprocmask_entry
	 * >>     pushP_cfi %Pdx          # Local variable: `sigset_t *oldset'
	 * >>     movP   $ss_full, {offsetof(struct pthread, pt_pmask.lpm_pmask.pm_sigmask)}(%Pax)
	 * >> .Leh_preemption_pop_begin:
	 * >>
	 * >> // Allocate the com buffer
	 * >>     TODO
	 * >>
	 * >>
	 * >>
	 * >> .Leh_preemption_pop_end:
	 * >>     .cfi_remember_state
	 * >>     movP   0(%Psp), %Pdx       # `oldset'
	 * >>     movP   P(%Psp), %R_fcall0P # `me'
	 * >>     movP   %Pdx, {offsetof(struct pthread, pt_pmask.lpm_pmask.pm_sigmask)}(%R_fcall0P)
	 * >>     test   $USERPROCMASK_FLAG_HASPENDING, {offsetof(struct pthread, pt_pmask.lpm_pmask.pm_flags)}(%R_fcall0P)
	 * >>     jnz    1f
	 * >> 2:  addP   $<LOCVAR_SPACE+...>, %Psp
	 * >>     popP_cfi_r %Pbx            # Only on i386
	 * >>     popP_cfi_r %Pbp            # Only on i386
	 * >>     ret
	 * >>
	 * >>     .cfi_restore_state
	 * >> 1:  call   aux_check_pending_signals
	 * >>     jmp    2b
	 * >>
	 * >> .Leh_preemption_pop_entry:
	 * >>     movP   0(%Psp), %Pdx       # `oldset'
	 * >>     movP   P(%Psp), %R_fcall0P # `me'
	 * >>     movP   %Pdx, {offsetof(struct pthread, pt_pmask.lpm_pmask.pm_sigmask)}(%R_fcall0P)
	 * >>     test   $USERPROCMASK_FLAG_HASPENDING, {offsetof(struct pthread, pt_pmask.lpm_pmask.pm_flags)}(%R_fcall0P)
	 * >>     jnz    1f
	 * >>     call   error_rethrow
	 * >> 1:  call   aux_check_pending_signals
	 * >>     call   error_rethrow
	 * >>     .cfi_endproc
	 *
	 */

#define except_enabled ((flags & SERVICE_WRAPPER_FLAG_EXCEPT) != 0)
	byte_t *tx_ptr, *tx_end;
	byte_t *Ltx_lazy_init_userprocmask_entry; /* Entry point for lazy userprocmask initialization */
	int8_t *Ltx_lazy_init_userprocmask_ret;   /* Relocation for return-jump */
	size_t serial_alloc;
	size_t serial_alloc_with_extra;
	size_t cfa_offset;         /* Offset from `%Psp' until _after_ the return-pc */
	size_t locvar_size;        /* Amount of space allocated for local variables. */
	ssize_t locvar_cfa_offset; /* (negative) offset from `cfa_offset' to start of local variable space */
	unsigned int argc;
	unsigned int serial_words; /* # of words in com serial data */
	unsigned int code_flags = 0;
#define CODE_F_HASINBUF        0x0001 /* FLAG: Input buffer arguments exist */
#define CODE_F_HASOUBUF        0x0002 /* FLAG: Output buffer arguments exist */
#define CODE_F_HASBUF          0x0003 /* FLAG: Buffer arguments exist */
#define CODE_F_SERIAL_USE_LODS 0x0004 /* FLAG: Use `lods' to load non-buffer arguments (only ) */
#define CODE_F_SERIAL_USE_STOS 0x0008 /* FLAG: Use `stos' to store non-buffer arguments */
#ifndef __x86_64__
#define CODE_F_SAVED_PSI       0x4000 /* FLAG: %Psi was saved */
#define CODE_F_SAVED_PDI       0x8000 /* FLAG: %Pdi was saved */
#endif /* !__x86_64__ */

	/* Figure out  how many  words of  fixed serial  memory we  need.
	 * This number directly determines how much needs to be allocated
	 * from `libservice_shmbuf_alloc_nopr()' */
	serial_words = 0;
	for (argc = 0; argc < SERVICE_ARGC_MAX;) {
		service_typeid_t typ;
		typ = info->dl_params[argc];
		++argc;
		if (typ == SERVICE_TYPE_VOID)
			break;
#ifndef __x86_64__
		if (typ == SERVICE_TYPE_386_R64)
			++serial_words; /* This one needs 2 words! */
#endif /* !__x86_64__ */
		++serial_words;
	}

	/* Figure out how much needs to be allocated for a raw `struct service_com' */
	serial_alloc = offsetof(struct service_com, sc_generic.g_data) +
	               serial_words * sizeof(void *);
	serial_alloc_with_extra = CEIL_ALIGN(serial_alloc, SERVICE_SHM_ALLOC_ALIGN);
	serial_alloc_with_extra += SERVICE_SHM_ALLOC_EXTRA;
	if (serial_alloc_with_extra < SERVICE_SHM_ALLOC_MINSIZE)
		serial_alloc_with_extra = SERVICE_SHM_ALLOC_MINSIZE;

	/* Get to writing the wrapper function's implementation */
	tx_ptr = buffers->swb_txbuf;
	tx_end = tx_ptr + buffers->swb_txsiz;
#define putinstr(expr)                             \
	do {                                           \
		if (tx_ptr + GEN86_INSTRLEN_MAX >= tx_end) \
			goto more_tx;                          \
		expr;                                      \
	}	__WHILE0
#define R_service_shm_handle GEN86_R_PBX /* %Pbx: `REF struct service_shm_handle *shm;' */
#define R_service_com        GEN86_R_PBP /* %Pbp: `struct service_com *com;' */

	/* TODO: CFI instrumentation */

	/* Generate the lazy userprocmask initialization stub (see above) */
	Ltx_lazy_init_userprocmask_entry = tx_ptr;
	/* TODO: proper `cfa_offset' */
	/* TODO: instructions */
	Ltx_lazy_init_userprocmask_ret;


	cfa_offset = 1 * sizeof(void *); /* 1x return addr */
	buffers->swb_entry = tx_ptr;
	putinstr(gen86_pushP_r(&tx_ptr, R_service_com));
	cfa_offset += sizeof(void *);
	putinstr(gen86_pushP_r(&tx_ptr, R_service_shm_handle));
	cfa_offset += sizeof(void *);

#ifdef __x86_64__
	{
		unsigned int i, regcount;
		regcount = serial_words;
		if (regcount > REGISTER_ARGUMENT_COUNT)
			regcount > REGISTER_ARGUMENT_COUNT;
		/* Preserve all of the original arguments. */
		for (i = 0; i < regcount; ++i) {
			putinstr(gen86_pushP_r(&tx_ptr, sysvabi_registers[i]));
			cfa_offset += sizeof(void *);
		}
	}
#else /* __x86_64__ */
	/* On i386, only save these registers when there are buffer arguments,
	 * in which case we need to implement memcpy() or strlen(), which  can
	 * be implemented inline by using these registers. */
	if (code_flags & CODE_F_HASBUF)
		code_flags |= CODE_F_SAVED_PSI | CODE_F_SAVED_PDI;
	if (code_flags & CODE_F_SERIAL_USE_LODS)
		code_flags |= CODE_F_SAVED_PSI;
	if (code_flags & CODE_F_SERIAL_USE_STOS)
		code_flags |= CODE_F_SAVED_PDI;
	if (HAS_SAVED_PSI) {
		putinstr(gen86_pushP_r(&tx_ptr, GEN86_R_PSI));
		cfa_offset += sizeof(void *);
	}
	if (HAS_SAVED_PDI) {
		putinstr(gen86_pushP_r(&tx_ptr, GEN86_R_PDI));
		cfa_offset += sizeof(void *);
	}
#endif /* !__x86_64__ */

	/* By default,  */
	locvar_size = 2 * sizeof(void *);
	/* TODO: Figure out how much additional local variable memory we need (for dynamic buffers) */

	/* Allocate local variable space */
	assert(locvar_size >= 2 * sizeof(void *));
	if (locvar_size > 2 * sizeof(void *)) {
		putinstr(gen86_subP_imm_r(&tx_ptr, locvar_size - (2 * sizeof(void *)), GEN86_R_PSP));
		cfa_offset += locvar_size - (2 * sizeof(void *));
	}

	/* Disable preemption (~ala `setsigmaskfullptr()') */
	putinstr(gen86_call(&tx_ptr, &pthread_self));
	putinstr(gen86_pushP_r(&tx_ptr, GEN86_R_PAX)); /* Local variable: `pthread_t me;' */
	cfa_offset += sizeof(void *);
	putinstr(gen86_movP_db_r(&tx_ptr, offsetof(struct pthread, pt_pmask.lpm_pmask.pm_sigmask), GEN86_R_PAX, GEN86_R_PDX));
	putinstr(gen86_testP_r_r(&tx_ptr, GEN86_R_PDX, GEN86_R_PDX));
	putinstr(gen86_jz8(&tx_ptr, Ltx_lazy_init_userprocmask_entry));
	/* Resolve the return-jump relocation for the lazy userprocmask initializer. */
	*Ltx_lazy_init_userprocmask_ret = (int8_t)(intptr_t)(tx_ptr - ((byte_t *)Ltx_lazy_init_userprocmask_ret + 1));
	/* At this point, %Pax == pthread_self(), %Pdx = pt_pmask.lpm_pmask.pm_sigmask(%Pax) */
	putinstr(gen86_pushP_r(&tx_ptr, GEN86_R_PDX)); /* Local variable: `sigset_t *oldset;' */
	cfa_offset += sizeof(void *);
	{ /* Set the full signal mask. */
		static sigset_t const ss_full = __SIGSET_INIT((__ULONGPTR_TYPE__)-1);
		putinstr(gen86_movP_imm_db(&tx_ptr, &ss_full, /* movP $ss_full, pt_pmask.lpm_pmask.pm_sigmask(%Pax) */
		                           offsetof(struct pthread, pt_pmask.lpm_pmask.pm_sigmask), GEN86_R_PAX));
	}

	/* TODO: Exception handling: begin try (restore the old signal mask via finally) */


	/* Call the buffer allocation function. */
	putinstr(gen86_movP_imm_r(&tx_ptr, self, GEN86_R_FCALL0P));
	putinstr(gen86_movP_imm_r(&tx_ptr, serial_alloc_with_extra, GEN86_R_FCALL1P));
	putinstr(gen86_call(&tx_ptr, except_enabled ? &libservice_shmbuf_alloc_nopr
	                                            : &libservice_shmbuf_alloc_nopr_nx));

	if (!except_enabled) {
		byte_t *error_label;
		putinstr(gen86_testP_r_r(&tx_ptr, GEN86_R_PAX, GEN86_R_PAX));
		error_label = tx_ptr; /* TODO: Check for alloc error */
		putinstr(gen86_jz(&tx_ptr, error_label));
	}

	/* Store results in non-volatile registers. */
	putinstr(gen86_movP_r_r(&tx_ptr, GEN86_R_PAX, R_service_shm_handle));
	putinstr(gen86_movP_r_r(&tx_ptr, GEN86_R_PDX, R_service_com));

	/* Initialize the command descriptor. */

	/* movP $<dl_comid>, sc_code(R_service_com) */
	putinstr(gen86_movP_imm_mod(&tx_ptr, gen86_modrm_db, info->dl_comid,
	                            offsetof(struct service_com, sc_code),
	                            R_service_com));

	/* TODO: EH to free the previously allocated com-buffer. */

	/* TODO: Serialize non-buffer arguments (make use of lods/stos based on USE_LODS_THRESHOLD/USE_STOS_THRESHOLD) */

	/* TODO: Serialize  buffer arguments located in SHM (remember those that are via some kind of local variable)
	 *       The size of buffers not located in SHM should be summed, and if non-zero, a second allocation should
	 *       be made for a buffer large enough to hold all buffers.
	 *       Store SHM-offsets to appropriate buffer locations in the com-data-blob */

	/* TODO: If there are in/inout buffers not located in SHM memory, fill them with the caller-provided memory
	 *       blobs so that the server will be able to see their contents. */

	/* TODO: Post the command and wait for completion. */

	/* TODO: Copy out/inout buffers not located in SHM (those to  which
	 *       this applies have be marked as such during serialization!) */

	/* TODO: Free the dynamically allocated extended buffer blob (if it was allocated) */

	/* TODO: Check if the com status code has a special value (`SERVICE_COM_ISSPECIAL()') */

	/* TODO: Load the com return value */

	/* TODO: Free the dynamically allocated com-buffer */
	abort();

	if (code_flags & CODE_F_SAVED_PSI) {
		putinstr(gen86_pushP_r(&tx_ptr, GEN86_R_PSI));
		cfa_offset -= sizeof(void *);
	}

	putinstr(gen86_popP_r(&tx_ptr, R_service_shm_handle));
	putinstr(gen86_popP_r(&tx_ptr, R_service_com));
	putinstr(gen86_ret(&tx_ptr));
#undef R_service_shm_handle
#undef R_service_com
	return LIBSERVICE_DLSYM_CREATE_WRAPPER_SUCCESS;
#undef putinstr
more_tx:
	return LIBSERVICE_DLSYM_CREATE_WRAPPER_MORE_TX;
#undef except_enabled
}

DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */
