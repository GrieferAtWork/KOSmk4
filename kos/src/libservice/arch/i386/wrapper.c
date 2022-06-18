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
#ifndef GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C
#define GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/minmax.h>
#include <hybrid/unaligned.h>

#include <kos/bits/userprocmask.h>
#include <kos/except.h>
#include <kos/types.h>
#include <sys/param.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h> /* qsort() */
#include <string.h>
#include <syscall.h>
#include <unwind.h> /* _Unwind_Resume() */

#include <libgen86/gen.h>
#include <libservice/client.h>
#include <libunwind/cfi.h>
#include <libunwind/dwarf.h>

#include "../../com.h"
#include "wrapper.h"

#ifdef __x86_64__
#include <libunwind/cfi/x86_64.h>
#else /* __x86_64__ */
#include <libunwind/cfi/i386.h>
#endif /* !__x86_64__ */

DECL_BEGIN

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#ifndef __getuserprocmask_defined
#error "Generated wrapper functions assume that userprocmask is available and supported!"
#endif /* !__getuserprocmask_defined */

#ifdef __GNUC__
/* GCC  complains that we're "taking the address of a packed struct memory" in all of
 * the `UNALIGNED_SET()' calls below. WELL YES I'M TAKING AN UNALIGNED ADDRESS!  WHAT
 * ELSE IS NEW IN? But seriously: I wish  there was some kind of way to disable  this
 * warning when the "unaligned address" is passed to one of the macros that are there
 * only to safely deal with reading/writing unaligned addresses. *sigh* */
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#endif /* __GNUC__ */

static_assert(SIZEOF_POINTER == sizeof(void *));


/* When the currently set exception is RT-level, return `false'.
 * Otherwise,   clear   the   exception   and   return   `true'. */
INTERN bool NOTHROW(FCALL libservice_aux_com_discard_nonrt_exception)(void) {
	struct exception_data *d = except_data();
	if (EXCEPTCLASS_ISRTLPRIORITY(d->e_class))
		return false;
	d->e_code = EXCEPT_CODEOF(E_OK); /* Clear exception */
	return true;
}

static_assert(offsetof(struct service_com_exceptinfo, e_code) == offsetof(struct exception_data, e_code));
static_assert(offsetof(struct service_com_exceptinfo, e_class) == offsetof(struct exception_data, e_class));
static_assert(offsetof(struct service_com_exceptinfo, e_subclass) == offsetof(struct exception_data, e_subclass));
static_assert(offsetof(struct service_com_exceptinfo, e_args) == offsetof(struct exception_data, e_args));

/* Set `errno' to the error code associated with `info' */
INTERN NOBLOCK NONNULL((2)) void
NOTHROW(FCALL libservice_aux_load_except_as_errno)(uintptr_t status,
                                                   struct service_comdesc *__restrict info) {
	errno_t error;
	if unlikely(status != SERVICE_COM_ST_EXCEPT) {
		/* Like below: HUP requested and command was canceled by outside entity. */
		error = ENOSYS;
	} else {
		error = except_as_errno((struct exception_data const *)&info->scd_com.sc_except);
	}
	errno =	error;
}

/* Populate `except_data()' with the given information. */
INTERN NOBLOCK NONNULL((2, 3)) void
NOTHROW(FCALL libservice_aux_load_except_as_error)(uintptr_t status,
                                                   struct service_comdesc *__restrict info,
                                                   void const *faultpc) {
	struct exception_data *d = except_data();
	if unlikely(status != SERVICE_COM_ST_EXCEPT) {
		/* Special  case: When we read back ECHO,  that can only mean that the
		 * command was canceled by some outside entity, of which there is only
		 * the case of a sudden HUP event.
		 * Simply handle this by throwing an E_SERVICE_EXITED */
		bzero(d, sizeof(info->scd_com.sc_except));
		d->e_code = EXCEPT_CODEOF(E_SERVICE_EXITED);
	} else {
		memcpy(d, &info->scd_com.sc_except, sizeof(info->scd_com.sc_except));
	}
	d->e_faultaddr = faultpc;
}



PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) int
compar_com_inline_buffer_param(void const *_a, void const *_b) {
#define _MASK (COM_INLINE_BUFFER_PARAM_FIN | COM_INLINE_BUFFER_PARAM_FOUT)
	static_assert(COM_INLINE_BUFFER_PARAM_FIN < COM_INLINE_BUFFER_PARAM_FOUT);
	struct com_inline_buffer_param const *a, *b;
	a = (struct com_inline_buffer_param const *)_a;
	b = (struct com_inline_buffer_param const *)_b;
	if ((a->cibp_flags & _MASK) < (b->cibp_flags & _MASK))
		return -1; /* Less than */
	if ((a->cibp_flags & _MASK) > (b->cibp_flags & _MASK))
		return 1; /* Greater than */

	/* Non-aligned buffer sizes go after those that are pointer-aligned.
	 * That  way, the number of buffers following those which leave %Pdi
	 * unaligned may be reduced by 1. */
	{
		bool is_a_aligned = IS_ALIGNED(a->cibp_sizeof, SERVICE_BUFFER_ALIGNMENT);
		bool is_b_aligned = IS_ALIGNED(b->cibp_sizeof, SERVICE_BUFFER_ALIGNMENT);
		if (is_a_aligned && !is_b_aligned)
			return -1; /* Less than */
		if (!is_a_aligned && is_b_aligned)
			return 1; /* Greater than */
	}

	/* Lastly, sort by serial argument stream offsets. */
	if (a->cibp_serial_offset < b->cibp_serial_offset)
		return -1; /* Less than */
	if (a->cibp_serial_offset > b->cibp_serial_offset)
		return 1; /* Greater than */

	/* Shouldn't get here! */
	return 0;
#undef _MASK
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) int
compar_com_buffer_param(void const *_a, void const *_b) {
#define _MASK (COM_BUFFER_PARAM_FIN | COM_BUFFER_PARAM_FOUT)
	static_assert(COM_BUFFER_PARAM_FIN < COM_BUFFER_PARAM_FOUT);
	struct com_buffer_param const *a, *b;
	a = (struct com_buffer_param const *)_a;
	b = (struct com_buffer_param const *)_b;
	if ((a->cbp_flags & _MASK) < (b->cbp_flags & _MASK))
		return -1; /* Less than */
	if ((a->cbp_flags & _MASK) > (b->cbp_flags & _MASK))
		return 1; /* Greater than */

	/* When `COM_BUFFER_PARAM_FRETMIN' is set, the
	 * parameter should come after another without
	 * that flag. */
	if ((a->cbp_flags & COM_BUFFER_PARAM_FRETMIN) < (b->cbp_flags & COM_BUFFER_PARAM_FRETMIN))
		return -1; /* Less than */
	if ((a->cbp_flags & COM_BUFFER_PARAM_FRETMIN) > (b->cbp_flags & COM_BUFFER_PARAM_FRETMIN))
		return 1; /* Greater than */

	/* Fixed-length buffers should come before those with flexible length.
	 * This way, we may have to re-align required buffer sizes less often! */
	if ((a->cbp_flags & COM_BUFFER_PARAM_FFIXED) < (b->cbp_flags & COM_BUFFER_PARAM_FFIXED))
		return 1; /* Greater than */
	if ((a->cbp_flags & COM_BUFFER_PARAM_FFIXED) > (b->cbp_flags & COM_BUFFER_PARAM_FFIXED))
		return -1; /* Less than */

	/* Lastly, sort by serial argument stream offsets. */
	if (a->cbp_serial_offset < b->cbp_serial_offset)
		return -1; /* Less than */
	if (a->cbp_serial_offset > b->cbp_serial_offset)
		return 1; /* Greater than */

	/* Shouldn't get here! */
	return 0;
#undef _MASK
}


/* Return the SP-offset of where the `param_index'th parameter is saved.
 * The returned  value  can  be  used as-is  as  an  offset  from  %Psp. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int16_t
NOTHROW(FCALL comgen_spoffsetof_param)(struct com_generator const *__restrict self,
                                       uint8_t param_index) {
	int16_t result;
	assert(param_index <= self->cg_paramc);
#ifdef __x86_64__
	if (param_index < 6) {
		result = self->cg_buf_paramc;
		if (result > 6)
			result = 6;
		result = -((2 + result) * 8);
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_RBX)
			result -= 8;
		result += param_index * 8;
	} else {
		result = (param_index - 6) * 8;
	}
#else /* __x86_64__ */
	result = param_index * 4;
#endif /* !__x86_64__ */
	result += self->cg_cfa_offset;
	return result;
}


/* Return the max # of consecutive integer params with
 * adjacent `cip_param_offset' or `cip_serial_offset',
 * where  `u16_field_offset' must be the offset to one
 * of those fields within `com_int_param' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uint8_t
NOTHROW(FCALL comgen_count_consecutive_intpar)(struct com_generator const *__restrict self,
                                               ptrdiff_t u16_field_offset) {
	uint8_t i, result = 0;
	for (i = 0; i < self->cg_int_paramc;) {
		uint8_t count = 1;
		uint16_t next;
		next = *(u16 const *)((byte_t const *)&self->cg_intpar[i] + u16_field_offset);
		for (;;) {
			++i;
			if (i >= self->cg_int_paramc)
				break;
			next += SIZEOF_POINTER;
			if (*(u16 const *)((byte_t const *)&self->cg_intpar[i] + u16_field_offset) != next)
				break;
			++count;
		}
		if (result < count)
			result = count;
	}
	return result;
}



/* Initialize the given com generator. Prior to calling
 * this function, the  caller must already  initialize:
 *  - self->cg_info
 * NOTE: This  function will leave the following fields
 *       uninitialized (which must be set-up by a later
 *       call to `comgen_reset()'):
 *  - self->cg_txbas, self->cg_ehbas
 *  - self->cg_txend, self->cg_ehend */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _comgen_init)(struct com_generator *__restrict self) {
	uint8_t i;
	int16_t param_offset;
	uint16_t serial_offset;

	/* Load and sort buffer arguments. */
#ifdef __x86_64__
	for (i = 0; i < SERVICE_ARGC_MAX; ++i) {
		if (self->cg_info.dl_params[i] == SERVICE_TYPE_VOID)
			break;
	}
	self->cg_paramc = i;

	/* On  x86_64, register parameters  are pushed at the  start of the function
	 * and therefor have negative offsets. Note  that for the time being,  these
	 * offsets are only correct when `COM_GENERATOR_FEATURE_USES_RBX' isn't set.
	 * Code  that may eventually set `COM_GENERATOR_FEATURE_USES_RBX' knows this
	 * and will adjust offsets to account for 8 more bytes of offset. */
	if (i > 6) /* First 6 arguments are passed through registers (and are therefor saved) */
		i = 6;
	param_offset = -((2 + i) * SIZEOF_POINTER);
#else /* __x86_64__ */

	/* On  i386, there only exist stack arguments which being immediately after
	 * the return address. Since CFA also points after the return address, it's
	 * effectively a zero-offset! */
	param_offset = 0;
#endif /* !__x86_64__ */

	self->cg_inline_buf_paramc = 0;
	self->cg_buf_paramc        = 0;
	self->cg_inbuf_paramc      = 0;
	self->cg_inoutbuf_paramc   = 0;
	self->cg_outbuf_paramc     = 0;
	self->cg_int_paramc        = 0;
	serial_offset              = offsetof(struct service_comdesc, scd_com.sc_generic.g_data);
	self->cg_features |= COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN;
	for (i = 0; i < SERVICE_ARGC_MAX; ++i) {
		uint8_t flags;
		service_typeid_t typ;
		typ = self->cg_info.dl_params[i];
		switch (typ & _SERVICE_TYPE_CLASSMASK) {

		case (SERVICE_TYPE_ARGBUF_IN(0) & _SERVICE_TYPE_CLASSMASK): {
			struct com_buffer_param *par;
do_flexible_inbuf_argument:
			flags = COM_BUFFER_PARAM_FIN;
			self->cg_features &= ~COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN;
			++self->cg_inbuf_paramc;
			__IF0 {
		case (SERVICE_TYPE_ARGBUF_OUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_BUFFER_PARAM_FOUT;
				++self->cg_outbuf_paramc;
			}
			__IF0 {
		case (SERVICE_TYPE_ARGBUF_INOUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_BUFFER_PARAM_FIN | COM_BUFFER_PARAM_FOUT;
				++self->cg_inoutbuf_paramc;
			}
			/* Buffer parameter. (NOTE: The sorting of these is done in a second step) */
			if ((typ & SERVICE_OUT_SIZEARG_RETURN_MINVAL) &&
			    (typ & _SERVICE_TYPE_CLASSMASK) != (SERVICE_TYPE_ARGBUF_IN(0) & _SERVICE_TYPE_CLASSMASK))
				flags |= COM_BUFFER_PARAM_FRETMIN;
			par = &self->cg_buf_paramv[self->cg_buf_paramc++];
			par->cbp_flags         = flags;
			par->cbp_param_index   = i;
			par->cbp_param_offset  = param_offset;
			par->cbp_serial_offset = serial_offset;
#ifndef __x86_64__
			/* `movs' is always used for copying of buffers here! */
			self->cg_features |= (COM_GENERATOR_FEATURE_USES_EDI |
			                      COM_GENERATOR_FEATURE_USES_ESI);
#endif /* !__x86_64__ */
		}	break;

		case (SERVICE_TYPE_FIXBUF_IN(0) & _SERVICE_TYPE_CLASSMASK): {
			uint16_t buffer_sizeof;
			flags = COM_INLINE_BUFFER_PARAM_FIN;
			__IF0 {
		case (SERVICE_TYPE_FIXBUF_OUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_INLINE_BUFFER_PARAM_FOUT;
			}
			__IF0 {
		case (SERVICE_TYPE_FIXBUF_INOUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_INLINE_BUFFER_PARAM_FIN | COM_INLINE_BUFFER_PARAM_FOUT;
			}
			buffer_sizeof = typ & _SERVICE_TYPE_PARAMMASK;
			if (buffer_sizeof <= COM_FIXBUF_INLINE_THRESHOLD) {
				/* Use a fixed-length inline buffer. */
				struct com_inline_buffer_param *par;
				if (buffer_sizeof >= COM_USEMOVS_THRESHOLD) {
					/* Use movs for copying data. */
#ifdef __x86_64__
					self->cg_features |= (COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS);
#else /* __x86_64__ */
					self->cg_features |= (COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS |
					                      COM_GENERATOR_FEATURE_USES_EDI |
					                      COM_GENERATOR_FEATURE_USES_ESI);
#endif /* !__x86_64__ */
				}
				par = &self->cg_inline_buf_paramv[self->cg_inline_buf_paramc++];
				par->cibp_param_index   = i;             /* [const] Parameter index in `:cg_info.dl_params' */
				par->cibp_flags         = flags;         /* [const] Parameter flags (set of `COM_INLINE_BUFFER_PARAM_F*') */
				par->cibp_param_offset  = param_offset;  /* [const] Offset from CFA to where this parameter is stored in memory */
				par->cibp_serial_offset = serial_offset; /* [const] Offset from `struct service_comdesc' to where the address of this buffer is saved */
/*				par->cibp_buffer_offset = ...;            * Initialized later */
				par->cibp_sizeof        = buffer_sizeof;
			} else {
				/* Use a dynamically allocated buffer. */
				struct com_buffer_param *par;
				static_assert(COM_INLINE_BUFFER_PARAM_FIN == COM_BUFFER_PARAM_FIN);
				static_assert(COM_INLINE_BUFFER_PARAM_FOUT == COM_BUFFER_PARAM_FOUT);
				par = &self->cg_buf_paramv[self->cg_buf_paramc++];
				par->cbp_flags         = flags | COM_BUFFER_PARAM_FFIXED;
				par->cbp_param_index   = i;
				par->cbp_param_offset  = param_offset;
				par->cbp_serial_offset = serial_offset;
				switch (flags) {
				case COM_INLINE_BUFFER_PARAM_FIN:
					/* This in  buffer has  a  fixed length,  so  don't
					 * unset `COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN'! */
					++self->cg_inbuf_paramc;
					break;
				case COM_INLINE_BUFFER_PARAM_FOUT:
					++self->cg_outbuf_paramc;
					break;
				case COM_INLINE_BUFFER_PARAM_FIN | COM_INLINE_BUFFER_PARAM_FOUT:
					++self->cg_inoutbuf_paramc;
					break;
				default: __builtin_unreachable();
				}
#ifndef __x86_64__
				/* `movs' is always used for copying of buffers here! */
				self->cg_features |= (COM_GENERATOR_FEATURE_USES_EDI |
				                      COM_GENERATOR_FEATURE_USES_ESI);
#endif /* !__x86_64__ */
			}
		}	break;

		default:
			switch (typ & _SERVICE_TYPE_PARAMMASK) {

			case SERVICE_TYPE_VOID & _SERVICE_TYPE_PARAMMASK:
				goto done_params;

			case SERVICE_TYPE_STR_IN & _SERVICE_TYPE_PARAMMASK:
				goto do_flexible_inbuf_argument;

#ifndef __x86_64__
			case SERVICE_TYPE_386_R64 & _SERVICE_TYPE_PARAMMASK:
				/* Double-wide integer argument. */
				self->cg_intpar[self->cg_int_paramc].cip_param_offset  = param_offset;
				self->cg_intpar[self->cg_int_paramc].cip_serial_offset = serial_offset;
				++self->cg_int_paramc;
				param_offset += SIZEOF_POINTER;
				serial_offset += SIZEOF_POINTER;
				ATTR_FALLTHROUGH
#endif /* !__x86_64__ */
			default:
				/* Integer argument. */
				self->cg_intpar[self->cg_int_paramc].cip_param_offset  = param_offset;
				self->cg_intpar[self->cg_int_paramc].cip_serial_offset = serial_offset;
				++self->cg_int_paramc;
				break;
			}
			break;
		}

		/* Adjust offsets for the next argument. */
		param_offset += SIZEOF_POINTER;
		serial_offset += SIZEOF_POINTER;

#ifdef __x86_64__
		/* Special case: Once we hit the `SAVED: %Pbp'-field, we've
		 * handled all register parameters  and must jump ahead  to
		 * continue on with stack-based arguments. */
		if (param_offset == -2 * SIZEOF_POINTER)
			param_offset = 0;
#endif /* __x86_64__ */
	}
done_params:
#ifndef __x86_64__
	self->cg_paramc = i;
#endif /* !__x86_64__ */

#ifdef __x86_64__
	/* When  at least  2 buffer parameters  exist, then `%rbx'  will be used
	 * by the implementation. As such, we  need to set the appropriate  code
	 * feature flag, as well as  adjust parameter offsets since all  offsets
	 * pointing into the argument save area will be shifted down by 8 bytes. */
	if (self->cg_buf_paramc >= 2) {
#define reloc_param_offset(x) ((x) < 0 ? (void)((x) -= 8) : (void)0)
		self->cg_features |= COM_GENERATOR_FEATURE_USES_RBX;
		for (i = 0; i < self->cg_int_paramc; ++i)
			reloc_param_offset(self->cg_intpar[i].cip_param_offset);
		for (i = 0; i < self->cg_inline_buf_paramc; ++i)
			reloc_param_offset(self->cg_inline_buf_paramv[i].cibp_param_offset);
		for (i = 0; i < self->cg_buf_paramc; ++i)
			reloc_param_offset(self->cg_buf_paramv[i].cbp_param_offset);
#undef reloc_param_offset
	}
#endif /* __x86_64__ */

	/* Sort `self->cg_inline_buf_paramv' */
	qsort(self->cg_inline_buf_paramv,
	      self->cg_inline_buf_paramc,
	      sizeof(self->cg_inline_buf_paramv[0]),
	      &compar_com_inline_buffer_param);

	/* Assign `self->cg_inline_buf_paramv[*].cibp_buffer_offset' */
	for (i = 0; i < self->cg_inline_buf_paramc; ++i) {
		/* Inline buffers are always aligned. */
		serial_offset = CEIL_ALIGN(serial_offset, SERVICE_BUFFER_ALIGNMENT);
		self->cg_inline_buf_paramv[i].cibp_buffer_offset = serial_offset;
		serial_offset += self->cg_inline_buf_paramv[i].cibp_sizeof;
	}

	/* The end address of the last inline buffer is equal to the minimum
	 * allocation  size  of   the  service_comdesc  descriptor   struct. */
	self->cg_sizeof_service_com = serial_offset;

	/* Sort `self->cg_buf_paramv' */
	qsort(self->cg_buf_paramv,
	      self->cg_buf_paramc,
	      sizeof(self->cg_buf_paramv[0]),
	      &compar_com_buffer_param);

	/* At this point, pretty much everything has been initialized, with
	 * the exception of:
	 *   - COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
	 *   - COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
	 *   - cg_locvar_offset
	 *   - cg_locvar_size
	 * Start out by figuring out if lods and/or stos should be used for
	 * loading integer arguments. */
	if (self->cg_int_paramc != 0) {
		uint8_t consecutive_param;
		uint8_t consecutive_serial;
		consecutive_param  = comgen_count_consecutive_intpar(self, offsetof(struct com_int_param, cip_param_offset));
		consecutive_serial = comgen_count_consecutive_intpar(self, offsetof(struct com_int_param, cip_serial_offset));
		if (consecutive_param >= 3) {
			self->cg_features |= COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS;
#ifndef __x86_64__
			self->cg_features |= COM_GENERATOR_FEATURE_USES_ESI;
#endif /* !__x86_64__ */
		}
		if (consecutive_serial >= 3) {
			self->cg_features |= COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS;
#ifndef __x86_64__
			self->cg_features |= COM_GENERATOR_FEATURE_USES_EDI;
#endif /* !__x86_64__ */
		}
	}

	/* Figure out the local variable area size. */
	self->cg_locvar_size = 3 * SIZEOF_POINTER; /* LOC_oldset, LOC_upm, LOC_shm */
	if (self->cg_buf_paramc != 0) {
		self->cg_locvar_size += 2 * SIZEOF_POINTER;                   /* LOC_bufpar_ptr, LOC_bufpar_shm */
		self->cg_locvar_size += self->cg_buf_paramc * SIZEOF_POINTER; /* LOC_bufparam_handles */
		if (self->cg_inbuf_paramc != 0 && (self->cg_inoutbuf_paramc != 0 || self->cg_outbuf_paramc != 0) &&
		    !(self->cg_features & COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN))
			self->cg_locvar_size += SIZEOF_POINTER; /* LOC_outbuffers_start */
	}

	/* Figure out where local variables end, which in turn determines where they start. */
	{
		int16_t locend;
#ifdef __x86_64__
		locend = -2 * SIZEOF_POINTER; /* RETURN_PC, saved %Pbp */
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_RBX)
			locend -= 8;                       /* Saved %rbx */
		locend -= MIN(self->cg_paramc, 6) * 8; /* Saved register params */
#else /* __x86_64__ */
		locend = -3 * SIZEOF_POINTER; /* RETURN_PC, saved %Pbp, saved %Pbx */
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_ESI)
			locend -= 4; /* Saved %esi */
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_EDI)
			locend -= 4; /* Saved %edi */
#endif /* !__x86_64__ */
		/* Remember where local variables start */
		self->cg_locvar_offset = locend - self->cg_locvar_size;
	}
}



/************************************************************************/
/* Assembly generation                                                  */
/************************************************************************/

#ifdef __x86_64__
/* Parameter register indices for the SysVAbi calling convention. */
static uint8_t const sysvabi_registers[6] = {
	GEN86_R_RDI,
	GEN86_R_RSI,
	GEN86_R_RDX,
	GEN86_R_RCX,
	GEN86_R_R8,
	GEN86_R_R9
};
#endif /* __x86_64__ */

/* Signal mask set by wrapper functions to disable preemption */
PRIVATE sigset_t const full_sigset = SIGSET_INIT_FULL;


/* Generate instrumentation to move the CFA PC to the current position.
 * The  .cfi_* macros in  GNU AS automatically do  this whenever any of
 * them are used, and will  also move the CFA  PC such that it  equates
 * the current PC.
 * >> if (self->cg_CFA_loc < self->cg_txptr) {
 * >>     uint32_t delta;
 * >>     delta = (uint32_t)(uintptr_t)(self->cg_txptr - self->cg_CFA_loc);
 * >>     comgen_eh_DW_CFA_advance_loc(self, delta);
 * >>     self->cg_CFA_loc = self->cg_txptr;
 * >> } */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_movehere)(struct com_generator *__restrict self) {
	if (self->cg_CFA_loc < self->cg_txptr) {
		uint32_t delta;
		delta = (uint32_t)(uintptr_t)(self->cg_txptr - self->cg_CFA_loc);
		comgen_eh_DW_CFA_advance_loc(self, delta);
		self->cg_CFA_loc = self->cg_txptr;
	}
}


/* .cfi_def_cfa_offset <regno> */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_DW_CFA_def_cfa_offset)(struct com_generator *__restrict self,
                                               int16_t offset) {
	assert((offset % SIZEOF_POINTER) == 0);
	if (!comgen_ehok1(self))
		return;
	if (offset != self->cg_cfa_offset) {
		comgen_eh_putb(self, DW_CFA_def_cfa_offset_sf);
		comgen_eh_putsleb128(self, -(offset / SIZEOF_POINTER));
		self->cg_cfa_offset = offset;
	}
}

PRIVATE WUNUSED NONNULL((1)) byte_t *
NOTHROW(FCALL _eh_putsleb128)(byte_t *__restrict writer,
                              intptr_t value) {
	byte_t byte;
	for (;;) {
		byte = value & 0x7f;
		value >>= 7;
		if ((value == 0 && (byte & 0x40) == 0) ||
		    (value == -1 && (byte & 0x40) != 0))
			break;
		byte |= 0x80; /* more bytes to come */
		*writer++ = byte;
	}
	*writer++ = byte;
	return writer;
}

PRIVATE WUNUSED NONNULL((1)) byte_t *
NOTHROW(FCALL _eh_putuleb128)(byte_t *writer,
                              uintptr_t value) {
	uint8_t byte;
	for (;;) {
		byte = value & 0x7f;
		value >>= 7;
		if (value == 0)
			break;
		byte |= 0x80; /* more bytes to come */
		*writer++ = byte;
	}
	*writer++ = byte;
	return writer;
}



/* With %Psi and %Pdi already populated (and permission to clobber %Pcx),
 * generate  code to  copy exactly  `num_bytes' from  0(%Psi) to 0(%Pdi). */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_memcpy_with_rep_movs)(struct com_generator *__restrict self,
                                           size_t num_bytes) {
	size_t pwords;
	if (!comgen_txok1(self))
		return;
	pwords = num_bytes / SIZEOF_POINTER;
	/* Because `num_bytes' is fixed, we can encode a super-efficient memcpy */
	if (pwords >= COM_USEREP_THRESHOLD) {
		gen86_movP_imm_r(&self->cg_txptr, pwords, GEN86_R_PCX);
		gen86_rep_movsP(&self->cg_txptr);
	} else {
		size_t i;
		for (i = 0; i < pwords; ++i) {
			if (!comgen_txok1(self))
				return;
			gen86_movsP(&self->cg_txptr);
		}
	}
#ifdef __x86_64__
	if (num_bytes & 4)
		gen86_movsl(&self->cg_txptr);
#endif /* __x86_64__ */
	if (num_bytes & 2)
		gen86_movsw(&self->cg_txptr);
	if (num_bytes & 1)
		gen86_movsb(&self->cg_txptr);
}


/* Generate instructions:
 * >>     pushP_cfi_r %Pbp        # %Pbp is used for `struct service_comdesc *R_service_com'
 * >> #ifdef __x86_64__
 * >>     pushP_cfi_r %rbx        # only if COM_GENERATOR_FEATURE_USES_RBX
 * >>     pushP_cfi %r9           # only if cg_paramc >= 6
 * >>     pushP_cfi %r8           # only if cg_paramc >= 5
 * >>     pushP_cfi %rcx          # only if cg_paramc >= 4
 * >>     pushP_cfi %rdx          # only if cg_paramc >= 3
 * >>     pushP_cfi %rsi          # only if cg_paramc >= 2
 * >>     pushP_cfi %rdi          # only if cg_paramc >= 1
 * >> #else // __x86_64__
 * >>     pushP_cfi_r %Pbx        # %Pbx is needed for system calls
 * >>     pushP_cfi_r %Psi        # only if COM_GENERATOR_FEATURE_USES_ESI
 * >>     pushP_cfi_r %Pdi        # only if COM_GENERATOR_FEATURE_USES_EDI
 * >> #endif // !__x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_push_registers_on_entry)(struct com_generator *__restrict self) {
#define generate_pushP_cfi(GEN86_R_NAME)           \
	(gen86_pushP_r(&self->cg_txptr, GEN86_R_NAME), \
	 comgen_eh_movehere(self),                     \
	 comgen_eh_DW_CFA_adjust_cfa_offset(self, SIZEOF_POINTER))
#define generate_pushP_cfi_r(GEN86_R_NAME, CFI_X86_UNWIND_REGISTER_NAME) \
	(generate_pushP_cfi(GEN86_R_NAME),     \
	 comgen_eh_DW_CFA_rel_offset(self, CFI_X86_UNWIND_REGISTER_NAME, 0))

	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space  (yet) */
	generate_pushP_cfi_r(GEN86_R_PBP, CFI_X86_UNWIND_REGISTER_PBP); /* pushP_cfi_r %Pbp */

#ifdef __x86_64__
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_RBX)
		generate_pushP_cfi_r(GEN86_R_RBX, CFI_X86_64_UNWIND_REGISTER_RBX); /* pushP_cfi_r %rbx */
	/* Push argument registers. */
	{
		unsigned int i;
		for (i = self->cg_paramc; i--;) {
			generate_pushP_cfi(sysvabi_registers[i]);
		}
	}
#else /* __x86_64__ */
	generate_pushP_cfi_r(GEN86_R_PBX, CFI_X86_UNWIND_REGISTER_PBX); /* pushP_cfi_r %Pbx */
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_ESI)
		generate_pushP_cfi_r(GEN86_R_ESI, CFI_386_UNWIND_REGISTER_ESI); /* pushP_cfi_r %Psi */
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_EDI)
		generate_pushP_cfi_r(GEN86_R_EDI, CFI_386_UNWIND_REGISTER_EDI); /* pushP_cfi_r %Pdi */
#endif /* !__x86_64__ */

#undef generate_pushP_cfi_r
#undef generate_pushP_cfi
}


/* Generate instructions:
 * >> subP   $<cg_locvar_size - 2 * sizeof(void*)>, %Psp
 * >> .cfi_adjust_cfa_offset <cg_locvar_size - 2 * sizeof(void*)> */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_allocate_stack_space)(struct com_generator *__restrict self) {
	uint16_t delta;
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space  (yet) */
	delta = self->cg_locvar_size - 2 * SIZEOF_POINTER;
	if (delta != 0) {
		gen86_subP_imm_r(&self->cg_txptr, delta, GEN86_R_PSP);
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, delta);
	}
}


/* Generate instructions:
 * >>     call   getuserprocmask
 * >>     pushP_cfi %Pax                                  # LOC_upm
 * >>     pushP_cfi userprocmask::pm_sigmask(%Pax)        # LOC_oldset
 * >>     .cfi_remember_state
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset, %Pcx
 * >>     movP   %Pcx,         userprocmask::pm_sigmask(%Pax) # Disable preemption
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $full_sigset, userprocmask::pm_sigmask(%Pax) # Disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >> .Leh_preemption_pop_begin: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_disable_preemption)(struct com_generator *__restrict self) {
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space  (yet) */

	/* >> call   getuserprocmask */
	gen86_call(&self->cg_txptr, &getuserprocmask);

	/* >> pushP_cfi %Pax                                  # LOC_upm */
	gen86_pushP_r(&self->cg_txptr, GEN86_R_PAX);
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, SIZEOF_POINTER);

	/* >> pushP_cfi userprocmask::pm_sigmask(%Pax)        # LOC_oldset */
	gen86_pushP_mod(&self->cg_txptr, gen86_modrm_db,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PAX);
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, SIZEOF_POINTER);

	/* >> .cfi_remember_state */
	comgen_eh_DW_CFA_remember_state(self);

	/* NOTE: `__code_model_large__' is defined when `-mcmodel=large' is passed
	 *       to GCC on the commandline. In all other modes, this library would
	 *       already  be broken when _ANY_ of its symbols were located outside
	 *       of the signed 32-bit address range.
	 * As such, we only need to handle overly-large symbol addresses when the
	 * library was built for that configuration. */
#if defined(__x86_64__) && defined(__code_model_large__)
	if (!_gen86_fitsl((uintptr_t)&full_sigset)) {
		/* >> movabs $full_sigset, %Pcx */
		gen86_movabs_imm_r(&self->cg_txptr, &full_sigset, GEN86_R_PCX);

		/* >> movP   %Pcx,         userprocmask::pm_sigmask(%Pax) # Disable preemption */
		gen86_movP_r_db(&self->cg_txptr, GEN86_R_PCX,
		                offsetof(struct userprocmask, pm_sigmask),
		                GEN86_R_PAX);
	} else
#endif /* __x86_64__ && __code_model_large__ */
	{
		/* >>     movP   $full_sigset, userprocmask::pm_sigmask(%Pax) # Disable preemption */
		gen86_movP_imm_db(&self->cg_txptr, (uintptr_t)&full_sigset,
		                  offsetof(struct userprocmask, pm_sigmask),
		                  GEN86_R_PAX);
	}

	/* >> .Leh_preemption_pop_begin: */
	comgen_defsym(self, COM_SYM_Leh_preemption_pop_begin);
}



/* Convenience register names. */
#define GEN86_R_service_com GEN86_R_PBP
#ifndef __x86_64__
#define GEN86_R_shmbase GEN86_R_PBX
#endif /* __x86_64__ */


/* Generate instructions:
 * >> // Allocate the com buffer
 * >>     movP   $<cg_service>, %R_fcall0P   # Input constant (hard-coded)
 * >>     movP   $<ALLOC_SIZE>, %R_fcall1P   # Input constant (hard-coded)
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_pop_preemption
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, %R_service_com       # %R_service_com == %Pbx
 * >>     movP   %Pdx, LOC_shm(%Psp)
 * >> .Leh_free_service_com_begin: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_allocate_com_buffer)(struct com_generator *__restrict self) {
	size_t alloc_size;
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space  (yet) */

	/* >> movP   $<cg_service>, %R_fcall0P   # Input constant (hard-coded) */
	gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P);

	/* Calculate the allocation size for the  */
	alloc_size = self->cg_sizeof_service_com;
	if (alloc_size < offsetafter(struct service_comdesc, scd_com.sc_except))
		alloc_size = offsetafter(struct service_comdesc, scd_com.sc_except); /* Needed for `SERVICE_COM_ST_EXCEPT' */
	alloc_size = CEIL_ALIGN(alloc_size, SERVICE_SHM_ALLOC_ALIGN);
	alloc_size += SERVICE_SHM_ALLOC_EXTRA;
	if (alloc_size < SERVICE_SHM_ALLOC_MINSIZE)
		alloc_size = SERVICE_SHM_ALLOC_MINSIZE;

	/* >> movP   $<ALLOC_SIZE>, %R_fcall1P   # Input constant (hard-coded) */
	gen86_movP_imm_r(&self->cg_txptr, alloc_size, GEN86_R_FCALL1P);

	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		/* >> call   libservice_shmbuf_alloc_nopr_nx */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr_nx);

		/* >> testP  %Pax, %Pax */
		gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);

		/* >> jz     .Lerr_pop_preemption */
		gen86_jccl_offset(&self->cg_txptr, GEN86_CC_Z, -4);
		comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lerr_pop_preemption);
	} else {
		/* >> call   libservice_shmbuf_alloc_nopr */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr);
	}

	/* >> movP   %Pax, %R_service_com       # %R_service_com == %Pbx */
	gen86_movP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_service_com);

	/* >> movP   %Pdx, LOC_shm(%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                comgen_spoffsetof_LOC_shm(self),
	                GEN86_R_PSP);

	/* >> .Leh_free_service_com_begin: */
	comgen_defsym(self, COM_SYM_Leh_free_service_com_begin);
}



/* Generate instructions for the "#if cg_buf_paramc == 0"
 * case of `comgen_serialize_buffer_arguments()':
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pax  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pax, userprocmask::pm_sigmask(%Pdx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_com_buffer_alloc
 * >> .Ltest_pending_signals_after_com_buffer_alloc_return: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments_0)(struct com_generator *__restrict self) {
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space  (yet) */

	/* >> movP   LOC_oldset(%Psp), %Pax  # `sigset_t *oldset' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_oldset(self),
	                GEN86_R_PSP, GEN86_R_PAX);

	/* >> movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_upm(self),
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >> movP   %Pax, userprocmask::pm_sigmask(%Pdx) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PDX);

	/* >> test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx) */
	gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db, USERPROCMASK_FLAG_HASPENDING,
	                    offsetof(struct userprocmask, pm_flags), GEN86_R_PDX);

	/* >> jnz    .Ltest_pending_signals_after_com_buffer_alloc */
	gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4);
	comgen_hidden_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_com_buffer_alloc);

	/* >> .Ltest_pending_signals_after_com_buffer_alloc_return: */
	comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_com_buffer_alloc_return);
}




/* Generate instructions for the "#if cg_buf_paramc == 1"
 * case of `comgen_serialize_buffer_arguments()':
 * >>     movP   $0, LOC_bufpar_ptr(%Psp)
 * >>     movP   $<cg_service>,                             %R_fcall0P
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[0](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jnz    .Lsingle_buffers_is_in_band
 * >> #if cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE_WITH_ADJUSTMENT>, %R_fcall1P
 * >> #else // cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   ..., %R_fcall1P  # Buffer size requirements of cg_buf_paramv[0]
 * >>                             # Allowed to clobber %Pax, %Pcx, %Pdi, %Psi
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     movP   %R_fcall1P, %Psi    # Used by the out-of-band copy-in loop below!
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %Pax, %R_fcall1P   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #endif // !cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy an out-of-band in/inout buffer into SHM memory
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     movP   %Pax, %Pdi # Unconditionally use %Pdi for copying!
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     subP   service_shm_handle::ssh_shm(%Pdx), %Pax
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx)
 * >>     movP   %Pax, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_single_buffer_alloc
 * >> .Ltest_pending_signals_after_single_buffer_alloc_return:
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >> #if cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE>, %Pcx
 * >> #else // cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   %Psi,                                      %Pcx # This one was preserved above!
 * >> #endif // !cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Psi # Unconditionally use %Psi for copying!
 * >>     rep    movsb
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     jmp    .Lsingle_buffers_done
 * >>
 * >> .Lsingle_buffers_is_in_band:
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_single_buffers_is_in_band
 * >> .Ltest_pending_signals_after_single_buffers_is_in_band_return:
 * >>     # %Pax == libservice_shm_handle_ataddr_nopr(<cg_service>, <cg_buf_paramv[0].cbp_param_offset>(%Psp))
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com)
 * >> .Lsingle_buffers_done: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments_1)(struct com_generator *__restrict self) {
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space  (yet) */
	uint8_t param_index;
	service_typeid_t param_typ;
	size_t fixed_buffer_size;
	int8_t *pdisp_Lsingle_buffers_done;       /* Relocate PC8 */
	int8_t *pdisp_Lsingle_buffers_is_in_band; /* Relocate PC8 */

	param_index       = self->cg_buf_paramv[0].cbp_param_index;
	param_typ         = self->cg_info.dl_params[param_index];
	fixed_buffer_size = (size_t)-1;
	/* If the buffer's size if fixed, load it now. */
	switch (param_typ & _SERVICE_TYPE_CLASSMASK) {
	case SERVICE_TYPE_FIXBUF_IN(0) & _SERVICE_TYPE_CLASSMASK:
	case SERVICE_TYPE_FIXBUF_OUT(0) & _SERVICE_TYPE_CLASSMASK:
	case SERVICE_TYPE_FIXBUF_INOUT(0) & _SERVICE_TYPE_CLASSMASK:
		fixed_buffer_size = param_typ & _SERVICE_TYPE_PARAMMASK;
		break;
	default:
		break;
	}

	/* >> movP   $0, LOC_bufpar_ptr(%Psp) */
	gen86_movP_imm_db(&self->cg_txptr, 0,
	                  comgen_spoffsetof_LOC_bufpar_ptr(self),
	                  GEN86_R_PSP);

	/* >> movP   $<cg_service>, %R_fcall0P */
	gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P);

	/* >> movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %R_fcall1P */
	gen86_movP_db_r(&self->cg_txptr,
	                self->cg_cfa_offset + self->cg_buf_paramv[0].cbp_param_offset,
	                GEN86_R_PSP, GEN86_R_FCALL1P);

	/* >> call   libservice_shm_handle_ataddr_nopr */
	gen86_call(&self->cg_txptr, &libservice_shm_handle_ataddr_nopr);

	/* >> movP   %Pax, LOC_bufparam_handles[0](%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                comgen_spoffsetof_LOC_bufpar_handles(self, 0),
	                GEN86_R_PSP);

	/* >> testP  %Pax, %Pax */
	gen86_testP_r_r(&self->cg_txbas, GEN86_R_PAX, GEN86_R_PAX);

	/* >> jnz    .Lsingle_buffers_is_in_band */
	gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NZ, -1);
	pdisp_Lsingle_buffers_is_in_band = (int8_t *)(self->cg_txptr - 1);

	if (fixed_buffer_size != (size_t)-1) {
		size_t adjusted;
		adjusted = fixed_buffer_size;
		adjusted = CEIL_ALIGN(adjusted, SERVICE_SHM_ALLOC_ALIGN);
		adjusted += SERVICE_SHM_ALLOC_EXTRA;
		if (adjusted < SERVICE_SHM_ALLOC_MINSIZE)
			adjusted = SERVICE_SHM_ALLOC_MINSIZE;

		/* >> movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE_WITH_ADJUSTMENT>, %R_fcall1P */
		gen86_movP_imm_r(&self->cg_txptr, adjusted, GEN86_R_FCALL1P);
	} else {
		/* >> movP   ..., %R_fcall1P  # Buffer size requirements of cg_buf_paramv[0]
		 * >>                         # Allowed to clobber %Pax, %Pcx, %Pdi, %Psi */
		switch (param_typ) {

		case SERVICE_TYPE_STR_IN: {
			/* Encode an inlined call to `strlen()+1' and store the result in %R_fcall1P:
			 * >> movP   <self->cg_buf_paramv[0].cbp_param_offset>(%Psp), %Pdi
			 * >> movP   $-1,  %Pcx
			 * >> xorP   %Pax, %Pax
			 * >> repne  scasb
			 * >> subP   %Pcx,     %Pax
			 * >> leaP   -1(%Pax), %R_fcall1P # Yes: this -1 is correct, even though we
			 * >>                             #      do want +1 more than strlen() would
			 * >>                             #      return. For reference, the asm impl
			 * >>                             #      of strlen subtracts `2'! */
			gen86_movP_db_r(&self->cg_txptr,
			                self->cg_cfa_offset + self->cg_buf_paramv[0].cbp_param_offset,
			                GEN86_R_PSP, GEN86_R_PDI);
			gen86_movP_imm_r(&self->cg_txptr, -1, GEN86_R_PCX);
			gen86_xorP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);
			gen86_repne_scasb(&self->cg_txptr);
			gen86_subP_r_r(&self->cg_txptr, GEN86_R_PCX, GEN86_R_PAX);
			gen86_leaP_db_r(&self->cg_txptr, -1, GEN86_R_PAX, GEN86_R_FCALL1P);
		}	break;

		default: {
			/* Buffer size is given through another argument. */
			uint16_t bufsize_argid;
			int16_t bufsize_sp_offset;
			bufsize_argid     = (param_typ & (_SERVICE_TYPE_PARAMMASK & ~SERVICE_OUT_SIZEARG_RETURN_MINVAL));
			bufsize_sp_offset = comgen_spoffsetof_param(self, bufsize_argid);
			gen86_movP_db_r(&self->cg_txptr, bufsize_sp_offset, GEN86_R_PSP, GEN86_R_FCALL1P);
		}	break;

		}

		if (self->cg_buf_paramv[0].cbp_flags & COM_BUFFER_PARAM_FIN) {
			/* >> movP   %R_fcall1P, %Psi    # Used by the out-of-band copy-in loop below! */
			gen86_movP_r_r(&self->cg_txptr, GEN86_R_FCALL1P, GEN86_R_PSI);
		}

		/* >> addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P */
		gen86_addP_imm_r(&self->cg_txptr, SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1, GEN86_R_FCALL1P);

		/* >> andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P */
		gen86_andP_imm_r(&self->cg_txptr, ~(SERVICE_SHM_ALLOC_ALIGN - 1), GEN86_R_FCALL1P);

		/* >> movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax */
		gen86_movP_imm_r(&self->cg_txptr, SERVICE_SHM_ALLOC_MINSIZE, GEN86_R_PAX);

		/* >> cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE) */
		gen86_cmpP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_FCALL1P);

		/* >> cmovbP %Pax, %R_fcall1P   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE; */
		gen86_cmovbP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_FCALL1P);
	}

	/* >> movP   $<cg_service>, %R_fcall0P */
	gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P);

	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		/* >> call   libservice_shmbuf_alloc_nopr_nx */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr_nx);

		/* >> testP  %Pax, %Pax */
		gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);

		/* >> jz     .Lerr_free_service_com */
		gen86_jccl_offset(&self->cg_txptr, GEN86_CC_Z, -4);
		comgen_hidden_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lerr_free_service_com);
	} else {
		/* >> call   libservice_shmbuf_alloc_nopr */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr);
	}

	/* >> movP   %Pax, LOC_bufpar_ptr(%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                comgen_spoffsetof_LOC_bufpar_ptr(self),
	                GEN86_R_PSP);

	/* >> movP   %Pdx, LOC_bufpar_shm(%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                comgen_spoffsetof_LOC_bufpar_shm(self),
	                GEN86_R_PSP);

	/* >> .Leh_free_xbuf_begin: */
	comgen_defsym(self, COM_SYM_Leh_free_xbuf_begin);

	/* Copy an out-of-band in/inout buffer into SHM memory */
	if (self->cg_buf_paramv[0].cbp_flags & COM_BUFFER_PARAM_FIN) {
		/* >> movP   %Pax, %Pdi # Unconditionally use %Pdi for copying! */
		gen86_movP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PDI);
	}

	/* >> subP   service_shm_handle::ssh_shm(%Pdx), %Pax */
	gen86_subP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_PAX,
	                 offsetof(struct service_shm_handle, ssh_shm),
	                 GEN86_R_PDX);

	/* Re-enable preemption */
	/* >> movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_oldset(self),
	                GEN86_R_PSP, GEN86_R_PCX);

	/* >> movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_upm(self),
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >> movP   %Pcx, userprocmask::pm_sigmask(%Pdx) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PCX,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PDX);

	/* >> movP   %Pax, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                self->cg_buf_paramv[0].cbp_serial_offset,
	                GEN86_R_service_com);

	/* >> test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx) */
	gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db, USERPROCMASK_FLAG_HASPENDING,
	                    offsetof(struct userprocmask, pm_flags), GEN86_R_PDX);

	/* >> jnz    .Ltest_pending_signals_after_single_buffer_alloc */
	gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4);
	comgen_hidden_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_single_buffer_alloc);

	/* >> .Ltest_pending_signals_after_single_buffer_alloc_return: */
	comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_single_buffer_alloc_return);

	if (self->cg_buf_paramv[0].cbp_flags & COM_BUFFER_PARAM_FIN) {
		if (fixed_buffer_size != (size_t)-1) {
			/* >> movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Psi # Unconditionally use %Psi for copying! */
			gen86_movP_db_r(&self->cg_txptr,
			                self->cg_cfa_offset + self->cg_buf_paramv[0].cbp_param_offset,
			                GEN86_R_PSP, GEN86_R_PSI);

			/* >> movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE>, %Pcx */
			comgen_memcpy_with_rep_movs(self, fixed_buffer_size);
		} else {
			/* >> movP   %Psi, %Pcx # This one was preserved above! */
			gen86_movP_r_r(&self->cg_txptr, GEN86_R_PSI, GEN86_R_PCX);

			/* >> movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Psi # Unconditionally use %Psi for copying! */
			gen86_movP_db_r(&self->cg_txptr,
			                self->cg_cfa_offset + self->cg_buf_paramv[0].cbp_param_offset,
			                GEN86_R_PSP, GEN86_R_PSI);

			/* >> rep    movsb */
			gen86_rep_movsb(&self->cg_txptr);
		}
	}

	/* >> jmp    .Lsingle_buffers_done */
	gen86_jmp8_offset(&self->cg_txptr, -1);
	pdisp_Lsingle_buffers_done = (int8_t *)(self->cg_txptr - 1);

	/* >> .Lsingle_buffers_is_in_band: */
	*pdisp_Lsingle_buffers_is_in_band += (int8_t)(uint8_t)(uintptr_t)
	                                     (self->cg_txptr - (byte_t *)pdisp_Lsingle_buffers_is_in_band);

	/* Re-enable preemption */
	/* >> movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_oldset(self),
	                GEN86_R_PSP, GEN86_R_PCX);

	/* >> movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_upm(self),
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >> movP   %Pcx, userprocmask::pm_sigmask(%Pdx) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PCX,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PDX);

	/* >> test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx) */
	gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db, USERPROCMASK_FLAG_HASPENDING,
	                    offsetof(struct userprocmask, pm_flags), GEN86_R_PDX);

	/* >> jnz    .Ltest_pending_signals_after_single_buffers_is_in_band */
	gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4);
	comgen_hidden_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band);

	/* >> .Ltest_pending_signals_after_single_buffers_is_in_band_return: */
	comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band_return);

	/* >> movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Pdx */
	gen86_movP_db_r(&self->cg_txptr,
	                self->cg_cfa_offset + self->cg_buf_paramv[0].cbp_param_offset,
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >> subP   service_shm_handle::ssh_shm(%Pax), %Pdx */
	gen86_subP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_PDX,
	                 offsetof(struct service_shm_handle, ssh_shm),
	                 GEN86_R_PAX);

	/* >> movP   %Pdx, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                self->cg_buf_paramv[0].cbp_serial_offset,
	                GEN86_R_service_com);

	/* >> .Lsingle_buffers_done: */
	*pdisp_Lsingle_buffers_done += (int8_t)(uint8_t)(uintptr_t)
	                               (self->cg_txptr - (byte_t *)pdisp_Lsingle_buffers_done);
}



#ifdef __x86_64__
#define GEN86_R_temp_exbuf_size GEN86_R_RBX
#else /* __x86_64__ */
#define GEN86_R_temp_exbuf_size GEN86_R_ESI
#endif /* !__x86_64__ */

/* Generate instructions for the "#if cg_buf_paramc >= 2"
 * case     of     `comgen_serialize_buffer_arguments()':
 * >>     # >> %R_temp_exbuf_size is %esi on i386 and %rbx on x86_64
 * >>     # NOTE: On x86_64, compilation getting here imples `COM_GENERATOR_FEATURE_USES_RBX'!
 * >>     xorP   %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     movP   %R_temp_exbuf_size, LOC_bufpar_ptr(%Psp)
 * >> {foreach[BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     movP   $<cg_service>,            %R_fcall0P
 * >>     movP   <cbp_param_offset>(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[INDEX](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jz     1f
 * >>     movP   <cbp_param_offset>(%Psp),          %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, <cbp_serial_offset>(%R_service_com)
 * >>     jmp    2f
 * >> 1:  # NOTE: When only 1 buffer argument exists, %R_temp_exbuf_size isn't
 * >>     #       used and the allocated+initialization is done inline.
 * >>     addP   ..., %R_temp_exbuf_size  # Account for required buffer size (depending on buffer type)
 * >>                                     # NOTE: The buffer size calculated here must be ceil-aligned by SERVICE_BUFFER_ALIGNMENT,
 * >>                                     #       unless INDEX == self->cg_buf_paramc - 1, in which case this alignment
 * >>                                     #       is optional.
 * >>                                     # Allowed to clobber: %Pax, %Pcx, %Pdx, %Pdi (on i386, %Psi must be preserved!)
 * >> 2:
 * >> }}
 * >>     testP  %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     jz     .Lall_buffers_are_in_band
 * >>     movP   $<cg_service>,      %R_fcall0P
 * >>     movP   %R_temp_exbuf_size, %R_fcall1P
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %Pax, %R_fcall1P   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy out-of-band in/inout buffers into SHM memory
 * >> #if cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdi  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pcx  # `struct userprocmask *upm'
 * >>     movP   %Pdi, userprocmask::pm_sigmask(%Pcx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pcx)
 * >>     jnz    .Ltest_pending_signals_after_xbuf_alloc
 * >> .Ltest_pending_signals_after_xbuf_alloc_return:
 * >>     movP   %Pax, %Pdi                               # Unconditionally use %Pdi for copying!
 * >>     movP   service_shm_handle::ssh_shm(%Pdx), %Pdx  # %Pdx is the base address of the out-of-band buffer SHM mapping
 * >> {foreach[IN_INOUT_BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     cmpP   $0, LOC_bufparam_handles[INDEX](%Psp)
 * >>     jne    1f
 * >> #if cg_inbuf_paramc != 0 && cg_inoutbuf_paramc != 0 && cg_outbuf_paramc != 0
 * >> #if IS_FIRST_INOUT_BUFFER(INDEX) && !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif // IS_FIRST_INOUT_BUFFER(INDEX) && !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >> #endif // cg_inbuf_paramc != 0 && cg_inoutbuf_paramc != 0 && cg_outbuf_paramc != 0
 * >>
 * >>     # Set: %Pax = SHM_ADDR - SHM_BASE  (offset in SHM to input buffer)
 * >>     # NOTE: We don't have to about output buffers, since those appear after in/inout buffers
 * >>     movP   %Pdi, %Pax
 * >>     subP   %Pdx, %Pax
 * >>     movP   %Pax, <cbp_serial_offset>(%R_service_com) # Store SHM offset in serial data
 * >>
 * >>     movP   ...,                      %Pcx            # required buffer size (depending on buffer type)
 * >>                                                      # Allowed to clobber: %Pax, %Pdx, %Pcx, %Psi
 * >>     movP   <cbp_param_offset>(%Psp), %Psi            # Unconditionally use %Psi for copying!
 * >>     rep    movsb                                     # Copy input buffers into SHM
 * >> #if INDEX != cg_paramc - 1                           # If %Pdi will still be used, it must be re-aligned
 * >> #if cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #if !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT - (cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE & (SERVICE_BUFFER_ALIGNMENT - 1))>, %Pdi
 * >> #endif // !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >> #else // cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT-1>,    %Pdi
 * >>     andP   $<~(SERVICE_BUFFER_ALIGNMENT-1)>, %Pdi
 * >> #endif // !cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #endif // INDEX != cg_paramc - 1
 * >> 1:
 * >> }}
 * >> #if cg_inbuf_paramc != 0 && cg_inoutbuf_paramc == 0 && cg_outbuf_paramc != 0
 * >> #if !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif // !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >> #endif // cg_inbuf_paramc != 0 && cg_inoutbuf_paramc == 0 && cg_outbuf_paramc != 0
 * >>     jmp    .Lall_buffers_are_in_band_preemption_reenabled
 * >> #endif // cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >> .Lall_buffers_are_in_band:
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pax  # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    .Ltest_pending_signals_after_all_buffers_are_in_band
 * >> .Lall_buffers_are_in_band_preemption_reenabled: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments_n)(struct com_generator *__restrict self) {
	uint8_t i;
	int32_t *pdisp_Lall_buffers_are_in_band; /* Relocate PC32 */

	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space  (yet) */
	/* >> xorP   %R_temp_exbuf_size, %R_temp_exbuf_size */
	gen86_xorP_r_r(&self->cg_txptr, GEN86_R_temp_exbuf_size, GEN86_R_temp_exbuf_size);

	/* >> movP   %R_temp_exbuf_size, LOC_bufpar_ptr(%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_temp_exbuf_size,
	                comgen_spoffsetof_LOC_bufpar_ptr(self), GEN86_R_PSP);

	/* >> {foreach[BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: { */
	for (i = 0; i < self->cg_buf_paramc; ++i) {
		int8_t *pdisp_1; /* Relocate PC8 */
		int8_t *pdisp_2; /* Relocate PC8 */

		/* >> movP   $<cg_service>, %R_fcall0P */
		comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));

		/* >> movP   <cbp_param_offset>(%Psp), %R_fcall1P */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   self->cg_cfa_offset + self->cg_buf_paramv[i].cbp_param_offset,
		                                   GEN86_R_PSP, GEN86_R_FCALL1P));

		/* >> call   libservice_shm_handle_ataddr_nopr */
		comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_shm_handle_ataddr_nopr));

		/* >> movP   %Pax, LOC_bufparam_handles[INDEX](%Psp) */
		comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
		                                   comgen_spoffsetof_LOC_bufpar_handles(self, i),
		                                   GEN86_R_PSP));

		/* >> testP  %Pax, %Pax */
		comgen_instr(self, gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX));

		/* >> jz     1f */
		comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_Z, -1));
		pdisp_1 = (int8_t *)(self->cg_txptr - 1);

		/* >> movP   <cbp_param_offset>(%Psp),          %Pdx */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   self->cg_cfa_offset + self->cg_buf_paramv[i].cbp_param_offset,
		                                   GEN86_R_PSP, GEN86_R_PDX));

		/* >> subP   service_shm_handle::ssh_shm(%Pax), %Pdx */
		comgen_instr(self, gen86_subP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_PDX,
		                                    offsetof(struct service_shm_handle, ssh_shm),
		                                    GEN86_R_PAX));

		/* >> movP   %Pdx, <cbp_serial_offset>(%R_service_com) */
		comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
		                                   self->cg_buf_paramv[i].cbp_serial_offset,
		                                   GEN86_R_service_com));

		/* >> jmp    2f */
		comgen_instr(self, gen86_jmp8_offset(&self->cg_txptr, -1));
		pdisp_2 = (int8_t *)(self->cg_txptr - 1);

		/* >> 1: */
		*pdisp_1 += (int8_t)(uint8_t)(uintptr_t)
		            (self->cg_txptr - (byte_t *)pdisp_1);

		if (self->cg_buf_paramv[i].cbp_flags & COM_BUFFER_PARAM_FFIXED) {
			uint16_t fixed_size;
			fixed_size = self->cg_info.dl_params[self->cg_buf_paramv[i].cbp_param_index] & _SERVICE_TYPE_PARAMMASK;
			fixed_size = CEIL_ALIGN(fixed_size, SERVICE_BUFFER_ALIGNMENT);
			/* >> addP   ..., %R_temp_exbuf_size  # Account for required buffer size (depending on buffer type)
			 * >>                                 # NOTE: The buffer size calculated here must be ceil-aligned by SERVICE_BUFFER_ALIGNMENT */
			comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, fixed_size, GEN86_R_temp_exbuf_size));
		} else {
			service_typeid_t param_typ;
			/* >> addP   ..., %R_temp_exbuf_size  # Account for required buffer size (depending on buffer type)
			 * >>                                 # NOTE: The buffer size calculated here must be ceil-aligned by SERVICE_BUFFER_ALIGNMENT,
			 * >>                                 #       unless INDEX == self->cg_buf_paramc - 1, in which case this alignment
			 * >>                                 #       is optional.
			 * >>                                 # Allowed to clobber: %Pax, %Pcx, %Pdx, %Pdi (on i386, %Psi must be preserved!) */
			param_typ = self->cg_info.dl_params[self->cg_buf_paramv[i].cbp_param_index];
			switch (param_typ) {

			case SERVICE_TYPE_STR_IN: {
				/* Encode an inlined call to `strlen()+1' and add the result to %GEN86_R_temp_exbuf_size:
				 * >> movP   <self->cg_buf_paramv[i].cbp_param_offset>(%Psp), %Pdi
				 * >> movP   $-1,  %Pcx
				 * >> xorP   %Pax, %Pax
				 * >> repne  scasb
				 * >> subP   %Pcx, %Pax
				 * >> leaP   -1(%GEN86_R_temp_exbuf_size,%Pax), \
				 * >>        %GEN86_R_temp_exbuf_size # Yes: this -1 is correct, even though we
				 * >>                                 #      do want +1 more than strlen() would
				 * >>                                 #      return. For reference, the asm impl
				 * >>                                 #      of strlen subtracts `2'! */
				gen86_movP_db_r(&self->cg_txptr,
				                self->cg_cfa_offset + self->cg_buf_paramv[i].cbp_param_offset,
				                GEN86_R_PSP, GEN86_R_PDI);
				gen86_movP_imm_r(&self->cg_txptr, -1, GEN86_R_PCX);
				gen86_xorP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);
				gen86_repne_scasb(&self->cg_txptr);
				gen86_subP_r_r(&self->cg_txptr, GEN86_R_PCX, GEN86_R_PAX);
				gen86_leaP_dbi_r(&self->cg_txptr, -1, GEN86_R_temp_exbuf_size,
				                 GEN86_R_PAX, GEN86_R_temp_exbuf_size);
			}	break;

			default: {
				/* Buffer size is given through another argument. */
				uint16_t bufsize_argid;
				int16_t bufsize_sp_offset;
				bufsize_argid     = (param_typ & (_SERVICE_TYPE_PARAMMASK & ~SERVICE_OUT_SIZEARG_RETURN_MINVAL));
				bufsize_sp_offset = comgen_spoffsetof_param(self, bufsize_argid);
				gen86_addP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_temp_exbuf_size,
				                 bufsize_sp_offset, GEN86_R_PSP);
			}	break;

			}

			/* Re-align the required buffer size. */
			if (i != self->cg_buf_paramc - 1) {
				comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, SERVICE_BUFFER_ALIGNMENT - 1, GEN86_R_temp_exbuf_size));
				comgen_instr(self, gen86_andP_imm_r(&self->cg_txptr, ~(SERVICE_BUFFER_ALIGNMENT - 1), GEN86_R_temp_exbuf_size));
			}
		}

		/* >> 2: */
		*pdisp_2 += (int8_t)(uint8_t)(uintptr_t)
		            (self->cg_txptr - (byte_t *)pdisp_2);
	}
	/* >> }} */

	/* >> testP  %R_temp_exbuf_size, %R_temp_exbuf_size */
	comgen_instr(self, gen86_testP_r_r(&self->cg_txptr,
	                                   GEN86_R_temp_exbuf_size,
	                                   GEN86_R_temp_exbuf_size));

	/* >> jz     .Lall_buffers_are_in_band */
	comgen_instr(self, gen86_jccl_offset(&self->cg_txptr, GEN86_CC_Z, -4));
	pdisp_Lall_buffers_are_in_band = (int32_t *)(self->cg_txptr - 4);

	/* >> movP   $<cg_service>,      %R_fcall0P */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));

	/* >> movP   %R_temp_exbuf_size, %R_fcall1P */
	comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_temp_exbuf_size, GEN86_R_FCALL1P));

	/* >> addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P */
	comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr,
	                                    SERVICE_SHM_ALLOC_EXTRA +
	                                    SERVICE_SHM_ALLOC_ALIGN - 1,
	                                    GEN86_R_FCALL1P));

	/* >> andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P */
	comgen_instr(self, gen86_andP_imm_r(&self->cg_txptr,
	                                    ~(SERVICE_SHM_ALLOC_ALIGN - 1),
	                                    GEN86_R_FCALL1P));

	/* >> movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, SERVICE_SHM_ALLOC_MINSIZE, GEN86_R_PAX));

	/* >> cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE) */
	comgen_instr(self, gen86_cmpP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_FCALL1P));

	/* >> cmovbP %Pax, %R_fcall1P   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE; */
	comgen_instr(self, gen86_cmovbP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_FCALL1P));

	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		/* >> call   libservice_shmbuf_alloc_nopr_nx */
		comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr_nx));

		/* >> testP  %Pax, %Pax */
		comgen_instr(self, gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX));

		/* >> jz     .Lerr_free_service_com */
		comgen_instr(self, gen86_jccl_offset(&self->cg_txptr, GEN86_CC_Z, -4));
		comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lerr_free_service_com);
	} else {
		/* >> call   libservice_shmbuf_alloc_nopr */
		comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr));
	}

	/* >> movP   %Pax, LOC_bufpar_ptr(%Psp) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                                   comgen_spoffsetof_LOC_bufpar_ptr(self),
	                                   GEN86_R_PSP));

	/* >> movP   %Pdx, LOC_bufpar_shm(%Psp) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                                   comgen_spoffsetof_LOC_bufpar_shm(self),
	                                   GEN86_R_PSP));

	/* >> .Leh_free_xbuf_begin: */
	comgen_defsym(self, COM_SYM_Leh_free_xbuf_begin);

	/* Copy out-of-band in/inout buffers into SHM memory */
	if (self->cg_inbuf_paramc != 0 || self->cg_inoutbuf_paramc != 0) {
		/* Re-enable preemption */
		/* >> movP   LOC_oldset(%Psp), %Pdi  # `sigset_t *oldset' */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   comgen_spoffsetof_LOC_oldset(self),
		                                   GEN86_R_PSP, GEN86_R_PDI));

		/* >> movP   LOC_upm(%Psp),    %Pcx  # `struct userprocmask *upm' */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   comgen_spoffsetof_LOC_upm(self),
		                                   GEN86_R_PSP, GEN86_R_PCX));

		/* >> movP   %Pdi, userprocmask::pm_sigmask(%Pcx) */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, GEN86_R_PDI,
		                                   offsetof(struct userprocmask, pm_sigmask),
		                                   GEN86_R_PCX));

		/* >> test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pcx) */
		comgen_instr(self, gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db,
		                                       USERPROCMASK_FLAG_HASPENDING,
		                                       offsetof(struct userprocmask, pm_flags),
		                                       GEN86_R_PCX));

		/* >> jnz    .Ltest_pending_signals_after_xbuf_alloc */
		comgen_instr(self, gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4));
		comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_xbuf_alloc);

		/* >> .Ltest_pending_signals_after_xbuf_alloc_return: */
		comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_xbuf_alloc_return);

		/* >> movP   %Pax, %Pdi # Unconditionally use %Pdi for copying! */
		comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PDI));

		/* >> movP   service_shm_handle::ssh_shm(%Pdx), %Pdx  # %Pdx is the base address of the out-of-band buffer SHM mapping */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   offsetof(struct service_shm_handle, ssh_shm),
		                                   GEN86_R_PDX, GEN86_R_PDX));

		/* >> {foreach[IN_INOUT_BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: { */
		for (i = 0; i < self->cg_inbuf_paramc + self->cg_inoutbuf_paramc; ++i) {
			int8_t *pdisp_1; /* Relocate PC8 */
			/* >> cmpP   $0, LOC_bufparam_handles[INDEX](%Psp) */
			comgen_instr(self, gen86_cmpP_imm_mod(&self->cg_txptr, gen86_modrm_db, 0,
			                                      comgen_spoffsetof_LOC_bufpar_handles(self, i),
			                                      GEN86_R_PSP));

			/* >> jne    1f */
			comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NE, -1));
			pdisp_1 = (int8_t *)(self->cg_txptr - 1);

			if (self->cg_inbuf_paramc != 0 && self->cg_inoutbuf_paramc != 0 &&
			    self->cg_outbuf_paramc != 0 &&
			    i == self->cg_inbuf_paramc /* IS_FIRST_INOUT_BUFFER */ &&
			    !(self->cg_features & COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN)) {
				/* `LOC_outbuffers_start' contains the start of the first inout/out buffer  */
				/* >> movP   %Pdi, LOC_outbuffers_start(%Psp) */
				comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDI,
				                                   comgen_spoffsetof_LOC_outbuffers_start(self),
				                                   GEN86_R_PSP));
			}

			/* >> movP   %Pdi, %Pax */
			comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_PDI, GEN86_R_PAX));

			/* >> subP   %Pdx, %Pax */
			comgen_instr(self, gen86_subP_r_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_PAX));

			/* >> movP   %Pax, <cbp_serial_offset>(%R_service_com) # Store SHM offset in serial data */
			comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
			                                   self->cg_buf_paramv[i].cbp_serial_offset,
			                                   GEN86_R_service_com));

			if (self->cg_buf_paramv[i].cbp_flags & COM_BUFFER_PARAM_FFIXED) {
				uint16_t fixed_size;
				fixed_size = self->cg_info.dl_params[self->cg_buf_paramv[i].cbp_param_index] & _SERVICE_TYPE_PARAMMASK;
				/* >> movP   <cbp_param_offset>(%Psp), %Psi            # Unconditionally use %Psi for copying! */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
				                                   self->cg_cfa_offset + self->cg_buf_paramv[i].cbp_param_offset,
				                                   GEN86_R_PSP, GEN86_R_PSI));
				comgen_memcpy_with_rep_movs(self, fixed_size);
			} else {
				service_typeid_t param_typ;
				/* >> movP   ..., %Pcx # required buffer size (depending on buffer type)
				 * >>                  # Allowed to clobber: %Pax, %Pdx, %Pcx, %Psi */
				param_typ = self->cg_info.dl_params[self->cg_buf_paramv[i].cbp_param_index];
				switch (param_typ) {

				case SERVICE_TYPE_STR_IN: {
					/* Encode an inlined call to `strlen()+1' and add the result to %GEN86_R_temp_exbuf_size:
					 * >> movP   <self->cg_buf_paramv[i].cbp_param_offset>(%Psp), %Pdi
					 * >> movP   $-1,  %Pcx
					 * >> xorP   %Pax, %Pax
					 * >> repne  scasb
					 * >> negP   %Pcx
					 * >> decP   %Pcx # Yes: this -1 is correct, even though we
					 * >>             #      do want +1 more than strlen() would
					 * >>             #      return. For reference, the asm impl
					 * >>             #      of strlen subtracts `2'! */
					gen86_movP_db_r(&self->cg_txptr,
					                self->cg_cfa_offset + self->cg_buf_paramv[i].cbp_param_offset,
					                GEN86_R_PSP, GEN86_R_PDI);
					gen86_movP_imm_r(&self->cg_txptr, -1, GEN86_R_PCX);
					gen86_xorP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);
					gen86_repne_scasb(&self->cg_txptr);
					gen86_negP_r(&self->cg_txptr, GEN86_R_PCX);
					gen86_decP_r(&self->cg_txptr, GEN86_R_PCX);
				}	break;

				default: {
					/* Buffer size is given through another argument. */
					uint16_t bufsize_argid;
					int16_t bufsize_sp_offset;
					bufsize_argid     = (param_typ & (_SERVICE_TYPE_PARAMMASK & ~SERVICE_OUT_SIZEARG_RETURN_MINVAL));
					bufsize_sp_offset = comgen_spoffsetof_param(self, bufsize_argid);
					gen86_movP_db_r(&self->cg_txptr, bufsize_sp_offset, GEN86_R_PSP, GEN86_R_PCX);
				}	break;

				}

				/* >> movP   <cbp_param_offset>(%Psp), %Psi            # Unconditionally use %Psi for copying! */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
				                                   self->cg_cfa_offset + self->cg_buf_paramv[i].cbp_param_offset,
				                                   GEN86_R_PSP, GEN86_R_PSI));

				/* >> rep    movsb                                     # Copy input buffers into SHM */
				comgen_instr(self, gen86_rep_movsb(&self->cg_txptr));
			}

			/* If %Pdi will still be used, it must be re-aligned  */
			if (i != self->cg_buf_paramc - 1) {
				if (self->cg_buf_paramv[i].cbp_flags & COM_BUFFER_PARAM_FFIXED) {
					uint16_t fixed_size;
					fixed_size = self->cg_info.dl_params[self->cg_buf_paramv[i].cbp_param_index] & _SERVICE_TYPE_PARAMMASK;
					if (!IS_ALIGNED(fixed_size, SERVICE_BUFFER_ALIGNMENT)) {
						uint8_t align = SERVICE_BUFFER_ALIGNMENT - (fixed_size & (SERVICE_BUFFER_ALIGNMENT - 1));
						/* >> addP   $<SERVICE_BUFFER_ALIGNMENT - (cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE & (SERVICE_BUFFER_ALIGNMENT - 1))>, %Pdi */
						comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, align, GEN86_R_PDI));
					}
				} else {
					/* >> addP   $<SERVICE_BUFFER_ALIGNMENT-1>,    %Pdi */
					comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, SERVICE_BUFFER_ALIGNMENT - 1, GEN86_R_PDI));

					/* >> andP   $<~(SERVICE_BUFFER_ALIGNMENT-1)>, %Pdi */
					comgen_instr(self, gen86_andP_imm_r(&self->cg_txptr, ~(SERVICE_BUFFER_ALIGNMENT - 1), GEN86_R_PDI));
				}
			}

			/* >> 1: */
			*pdisp_1 += (int8_t)(uint8_t)(uintptr_t)
			            (self->cg_txptr - (byte_t *)pdisp_1);
		}
		/* >> }} */

		if (self->cg_inbuf_paramc != 0 && self->cg_inoutbuf_paramc == 0 &&
		    self->cg_outbuf_paramc != 0 && !(self->cg_features & COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN)) {
			/* >> movP   %Pdi, LOC_outbuffers_start(%Psp) # `LOC_outbuffers_start' contains the start of the first inout/out buffer */
			comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDI,
			                                   comgen_spoffsetof_LOC_outbuffers_start(self),
			                                   GEN86_R_PSP));
		}

		/* >> jmp    .Lall_buffers_are_in_band_preemption_reenabled */
		comgen_instr(self, gen86_jmpl_offset(&self->cg_txptr, -4));
		comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lall_buffers_are_in_band_preemption_reenabled);
	}

	/* >> .Lall_buffers_are_in_band: */
	*pdisp_Lall_buffers_are_in_band += (int32_t)(uint32_t)(uintptr_t)
	                                   (self->cg_txptr - (byte_t *)pdisp_Lall_buffers_are_in_band);

	/* Re-enable preemption */
	/* >> movP   LOC_oldset(%Psp), %Pdx  # `sigset_t *oldset' */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_oldset(self),
	                                   GEN86_R_PSP, GEN86_R_PDX));

	/* >> movP   LOC_upm(%Psp),    %Pax  # `struct userprocmask *upm' */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_upm(self),
	                                   GEN86_R_PSP, GEN86_R_PAX));

	/* >> movP   %Pdx, userprocmask::pm_sigmask(%Pax) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                                   offsetof(struct userprocmask, pm_sigmask),
	                                   GEN86_R_PAX));

	/* >> test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax) */
	comgen_instr(self, gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db,
	                                       USERPROCMASK_FLAG_HASPENDING,
	                                       offsetof(struct userprocmask, pm_flags),
	                                       GEN86_R_PAX));

	/* >> jnz    .Ltest_pending_signals_after_all_buffers_are_in_band */
	comgen_instr(self, gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4));
	comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_all_buffers_are_in_band);

	/* >> .Lall_buffers_are_in_band_preemption_reenabled: */
	comgen_defsym(self, COM_SYM_Lall_buffers_are_in_band_preemption_reenabled);
}




/* Generate    instructions:
 * >> #if cg_buf_paramc == 0
 * >> ...
 * >> #elif cg_buf_paramc == 1
 * >> ...
 * >> #else // #elif cg_buf_paramc >= 2
 * >> ...
 * >> #endif // #endif cg_buf_paramc >= 2
 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments)(struct com_generator *__restrict self) {
	switch (self->cg_buf_paramc) {
	case 0:
		comgen_serialize_buffer_arguments_0(self);
		break;
	case 1:
		comgen_serialize_buffer_arguments_1(self);
		break;
	default:
		comgen_serialize_buffer_arguments_n(self);
		break;
	}
}



/* Output `movsP' instructions
 * NOTE: Allowed to clobber %Pcx! */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_output_movsP_times_n)(struct com_generator *__restrict self,
                                           uint8_t n) {
	comgen_memcpy_with_rep_movs(self, n * SIZEOF_POINTER);
}

/* Generate    instructions:
 * >> // Serialize integer arguments (if they exist)
 * >> #if cg_int_paramc != 0
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >> #set _GENERATOR_VAR_Psi_offset = FIRST_NON_BUFFER_ARGUMENT.cip_param_offset  # Stack-offset of first argument
 * >>     leaP   <FIRST_NON_BUFFER_ARGUMENT.cip_param_offset>(%Psp), %Psi
 * >> #endif // COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >>
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >> #set _GENERATOR_VAR_Pdi_offset = FIRST_NON_BUFFER_ARGUMENT.cip_serial_offset # Serial-offset of first argument
 * >>     leaP   <FIRST_NON_BUFFER_ARGUMENT.cip_param_offset>(%Psp), %Pdi
 * >> #endif // COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >>
 * >> {foreach[NON_BUFFER_ARGUMENT: <cip_param_offset>, <cip_serial_offset>]: {
 * >>     # NOTE: cip_param_offset is the offset to the input parameter (from %Psp)
 * >>     # NOTE: cip_serial_offset is the offset in the serial stream (from %R_service_com)
 * >>     # NOTE: When both lodsP and stosP are used together, movsP may be generated instead!
 * >>
 * >>     # Load the argument value from the parameter-save or stack-argument area
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >> #if _GENERATOR_VAR_Psi_offset != cip_param_offset
 * >>     addP   $(<cip_param_offset - _GENERATOR_VAR_Psi_offset>), %Psi # Or subP
 * >> #endif
 * >>     lodsP
 * >> #set _GENERATOR_VAR_Psi_offset += SIZEOF_POINTER
 * >> #else // COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >>     movP   <cip_param_offset>(%Psp), %Pax
 * >> #endif // !COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >>
 * >>     # Write the argument value to serial com data area
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >> #if _GENERATOR_VAR_Pdi_offset != cip_serial_offset
 * >>     addP   $(<cip_serial_offset - _GENERATOR_VAR_Pdi_offset>), %Pdi # Or subP
 * >> #endif
 * >>     stosP
 * >> #set _GENERATOR_VAR_Pdi_offset += SIZEOF_POINTER
 * >> #else // COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >>     movP   %Pax, <cip_serial_offset>(%R_service_com)
 * >> #endif // !COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >> }}
 * >> #endif // cg_int_paramc != 0 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_integer_arguments)(struct com_generator *__restrict self) {
	uint8_t i, num_pending_movsP;
	int16_t psi_spoffset;       /* Current sp-offset of %Psi (or `-1' if undefined) */
	uint16_t pdi_serial_offset; /* Current serial-offset of %Pdi (or `(uint16_t)-1' if undefined) */
	if (self->cg_int_paramc == 0)
		return; /* Simple case... */
	psi_spoffset      = -1;
	pdi_serial_offset = (uint16_t)-1;
	num_pending_movsP = 0;
	for (i = 0; i < self->cg_int_paramc;) {
		struct com_int_param param;
		uint8_t num_consecutive = 1;
		int16_t spoffset;
		param = self->cg_intpar[i];
		/* Figure out how many parameters exist in consecutive locations both in serial and on-stack. */
		while (i + num_consecutive < self->cg_int_paramc &&
		       self->cg_intpar[i + num_consecutive].cip_param_offset == param.cip_param_offset + num_consecutive * SIZEOF_POINTER &&
		       self->cg_intpar[i + num_consecutive].cip_serial_offset == param.cip_serial_offset + num_consecutive * SIZEOF_POINTER)
			++num_consecutive;
		/* At this point, essentially generate code to copy `num_consecutive * SIZEOF_POINTER'
		 * bytes  of   memory  from   `param.cip_param_offset'  to   `param.cip_serial_offset' */
		spoffset = self->cg_cfa_offset + param.cip_param_offset;
		if (self->cg_features & (COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS |
		                         COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS)) {
			bool must_adjust_psi = false;
			bool must_adjust_pdi = false;
			/* Figure out if we have to adjust %Pdi and/or %Psi */
			if (self->cg_features & COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS)
				must_adjust_psi = (psi_spoffset + (num_pending_movsP * SIZEOF_POINTER)) != spoffset;
			if (self->cg_features & COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS)
				must_adjust_pdi = (pdi_serial_offset + (num_pending_movsP * SIZEOF_POINTER)) != param.cip_serial_offset;
			/* If too many adjustments need to be made with too few
			 * consecutive  data words, then  just don't use string
			 * instructions! */
			if ((int)must_adjust_pdi + (int)must_adjust_psi >= num_consecutive)
				goto do_word_wise_copy;
			/* Perform required adjustments */
			if (must_adjust_psi) {
				if (num_pending_movsP) {
					comgen_output_movsP_times_n(self, num_pending_movsP);
					psi_spoffset += num_pending_movsP * SIZEOF_POINTER;
					pdi_serial_offset += num_pending_movsP * SIZEOF_POINTER;
					num_pending_movsP = 0;
				}
				if (psi_spoffset == -1) {
					/* Initial load:
					 * >> leaP <spoffset>(%Psp), %Psi */
					comgen_instr(self, gen86_leaP_db_r(&self->cg_txptr, spoffset, GEN86_R_PSP, GEN86_R_PSI));
				} else {
					int16_t delta = spoffset - psi_spoffset;
					/* Delta adjustment:
					 * >> addP $<delta>, %Psi */
					assert(delta != 0);
					if likely(delta >= 0) {
						comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, delta, GEN86_R_PSI));
					} else {
						comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, -delta, GEN86_R_PSI));
					}
				}
				psi_spoffset = spoffset;
			}
			if (must_adjust_pdi) {
				if (num_pending_movsP) {
					comgen_output_movsP_times_n(self, num_pending_movsP);
					psi_spoffset += num_pending_movsP * SIZEOF_POINTER;
					pdi_serial_offset += num_pending_movsP * SIZEOF_POINTER;
					num_pending_movsP = 0;
				}
				if (pdi_serial_offset == (uint16_t)-1) {
					/* Initial load:
					 * >> leaP <param.cip_serial_offset>(%R_service_com), %Pdi */
					comgen_instr(self, gen86_leaP_db_r(&self->cg_txptr, param.cip_serial_offset,
					                                   GEN86_R_service_com, GEN86_R_PDI));
				} else {
					int16_t delta = (int16_t)param.cip_serial_offset -
					                (int16_t)pdi_serial_offset;
					/* Delta adjustment:
					 * >> addP $<delta>, %Pdi */
					assert(delta != 0);
					if likely(delta >= 0) {
						comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, delta, GEN86_R_PDI));
					} else {
						comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, -delta, GEN86_R_PDI));
					}
				}
				pdi_serial_offset = param.cip_serial_offset;
			}
			/* Perform the copy */
			switch (self->cg_features & (COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS |
			                             COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS)) {
			case COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS:
				/* >> lodsP
				 * >> movP   %Pax, <param.cip_serial_offset>(%R_service_com) */
				assert(num_pending_movsP == 0);
				comgen_instr(self, gen86_lodsP(&self->cg_txptr));
				comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
				                                   param.cip_serial_offset,
				                                   GEN86_R_service_com));
				psi_spoffset += SIZEOF_POINTER;
				break;
			case COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS:
				/* >> movP   <spoffset>(%Psp), %Pax
				 * >> stosP */
				assert(num_pending_movsP == 0);
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, spoffset,
				                                   GEN86_R_PSP, GEN86_R_PAX));
				comgen_instr(self, gen86_stosP(&self->cg_txptr));
				pdi_serial_offset += SIZEOF_POINTER;
				break;
			case COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS | COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS:
				/* >> movsP */
				++num_pending_movsP;
				break;
			default: __builtin_unreachable();
			}
		} else {
			/* Fallback: do a word-wise copy. */
			uint8_t j;
do_word_wise_copy:
			if (num_pending_movsP) {
				comgen_output_movsP_times_n(self, num_pending_movsP);
				psi_spoffset += num_pending_movsP * SIZEOF_POINTER;
				pdi_serial_offset += num_pending_movsP * SIZEOF_POINTER;
				num_pending_movsP = 0;
			}
			for (j = 0; j < num_consecutive; ++j) {
				/* >> movP   <spoffset>(%Psp), %Pax */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, spoffset, GEN86_R_PSP, GEN86_R_PAX));
				/* >> movP   %Pax, <param.cip_serial_offset>(%R_service_com) */
				comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
				                                   param.cip_serial_offset,
				                                   GEN86_R_service_com));
				spoffset += SIZEOF_POINTER;
				param.cip_serial_offset += SIZEOF_POINTER;
			}
		}
		i += num_consecutive;
	}
	if (num_pending_movsP)
		comgen_output_movsP_times_n(self, num_pending_movsP);
}



/* Generate instructions:
 * >> #if cg_inline_buf_paramc != 0
 * >> {foreach[INLINE_BUFFER_ARGUMENT: <cibp_buffer_offset>, <cibp_sizeof>, <cibp_param_offset>, <cibp_serial_offset>]: {
 * >>     # NOTE: `<cibp_buffer_offset>' (>= `<cibp_buffer_offset>') is the
 * >>     #       offset from service_comdesc to where inline buffer data is stored.
 * >>     leaP   <cibp_buffer_offset - service_comdesc::scd_com>(%Pdx), %Pax # SHM-relative address of the inline buffer
 * >>     movP   %Pax, <cibp_serial_offset>(%R_service_com)                  # Store relative address in serial stream
 * >> #if ARGUMENT_IS_IN_OR_INOUT_BUFFER # (Referring to the argument being enumerated)
 * >>     # Whether or not movs is used is determined on a per-argument basis
 * >> #if COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     leaP   <cibp_buffer_offset>(%R_service_com), %Pdi # This instruction is skipped if `Pdi' already has the
 * >>                                                       # correct value, which may be the case if a preceding
 * >>                                                       # inline buffer already set it up correctly.
 * >>     movP   <cibp_param_offset>(%Psp), %Psi
 * >>     movP   $<cibp_sizeof>,            %Pcx            # Or an equivalent series of inline `[rep] movsX' instructions
 * >>     rep    movsb
 * >> #else // COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     movP   <cibp_param_offset>(%Psp), %Pcx
 * >>     {INLINE_MEMCPY(_OFF, _BWLQ, <cibp_sizeof>) {
 * >>         mov{_BWLQ} _OFF(%Pcx), %{_BWLQ}ax
 * >>         mov{_BWLQ} %{_BWLQ}ax, <cibp_buffer_offset>+_OFF(%R_service_com)
 * >>     }}
 * >> #endif // !COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >> #endif // ARGUMENT_IS_IN_OR_INOUT_BUFFER
 * >> }}
 * >> #endif // cg_inline_buf_paramc != 0 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_inline_buffers)(struct com_generator *__restrict self) {
	uint8_t i;
	uint16_t current_pdi_offset = (uint16_t)-1;
	for (i = 0; i < self->cg_inline_buf_paramc; ++i) {
		/* >> leaP   <cibp_buffer_offset - service_comdesc::scd_com>(%Pdx), %Pax # SHM-relative address of the inline buffer */
		comgen_instr(self, gen86_leaP_db_r(&self->cg_txptr,
		                                   self->cg_inline_buf_paramv[i].cibp_buffer_offset -
		                                   offsetof(struct service_comdesc, scd_com),
		                                   GEN86_R_PDX, GEN86_R_PAX));

		/* >> movP   %Pax, <cibp_serial_offset>(%R_service_com) # Store relative address in serial stream */
		comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
		                                   self->cg_inline_buf_paramv[i].cibp_serial_offset,
		                                   GEN86_R_service_com));

		if (self->cg_inline_buf_paramv[i].cibp_flags & COM_INLINE_BUFFER_PARAM_FIN) {
			int16_t spoffset;
			uint16_t bufsiz, bufoff;
			bufsiz   = self->cg_inline_buf_paramv[i].cibp_sizeof;
			bufoff   = self->cg_inline_buf_paramv[i].cibp_buffer_offset;
			spoffset = self->cg_inline_buf_paramv[i].cibp_param_offset + self->cg_cfa_offset;
			if ((bufsiz >= COM_USEMOVS_THRESHOLD) &&
			    (self->cg_features & COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS)) {
				/* >> leaP   <cibp_buffer_offset>(%R_service_com), %Pdi # This instruction is skipped if `Pdi' already has the
				 * >>                                                   # correct value, which may be the case if a preceding
				 * >>                                                   # inline buffer already set it up correctly. */
				if (current_pdi_offset == (uint16_t)-1) {
					comgen_instr(self, gen86_leaP_db_r(&self->cg_txptr, bufoff,
					                                   GEN86_R_service_com, GEN86_R_PDI));
				} else if (current_pdi_offset < bufoff) {
					uint16_t delta = bufoff - current_pdi_offset;
					comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, delta, GEN86_R_PDI));
				} else if (current_pdi_offset > bufoff) {
					uint16_t delta = current_pdi_offset - bufoff;
					comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, delta, GEN86_R_PDI));
				}
				current_pdi_offset = bufoff;

				/* >> movP   <cibp_param_offset>(%Psp), %Psi */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, spoffset,
				                                   GEN86_R_PSP, GEN86_R_PSI));

				/* >> movP   $<cibp_sizeof>, %Pcx
				 * >> rep    movsb */
				comgen_memcpy_with_rep_movs(self, bufsiz);
				current_pdi_offset += bufsiz;
			} else if (bufsiz != 0) {
				uint16_t srcoff;
				/* >> movP   <cibp_param_offset>(%Psp), %Pcx */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, spoffset,
				                                   GEN86_R_PSP, GEN86_R_PCX));

				/* >> {INLINE_MEMCPY(_OFF, _BWLQ, <cibp_sizeof>) {
				 * >>     mov{_BWLQ} _OFF(%Pcx), %{_BWLQ}ax
				 * >>     mov{_BWLQ} %{_BWLQ}ax, <cibp_buffer_offset>+_OFF(%R_service_com)
				 * >> }} */
				srcoff = 0;
				while (bufsiz) {
#ifdef __x86_64__
					if (bufsiz >= 8) {
						comgen_instr(self, gen86_movq_db_r(&self->cg_txptr, srcoff, GEN86_R_PCX, GEN86_R_RAX));
						if (bufoff == current_pdi_offset) {
							comgen_instr(self, gen86_stosq(&self->cg_txptr));
							current_pdi_offset += 8;
						} else {
							comgen_instr(self, gen86_movq_r_db(&self->cg_txptr, GEN86_R_RAX,
							                                   bufoff, GEN86_R_service_com));
						}
						bufsiz -= 8;
						bufoff += 8;
						srcoff += 8;
						continue;
					}
#endif /* __x86_64__ */
					if (bufsiz >= 4) {
						comgen_instr(self, gen86_movl_db_r(&self->cg_txptr, srcoff, GEN86_R_PCX, GEN86_R_EAX));
						if (bufoff == current_pdi_offset) {
							comgen_instr(self, gen86_stosl(&self->cg_txptr));
							current_pdi_offset += 4;
						} else {
							comgen_instr(self, gen86_movl_r_db(&self->cg_txptr, GEN86_R_EAX,
							                                   bufoff, GEN86_R_service_com));
						}
						bufsiz -= 4;
						bufoff += 4;
						srcoff += 4;
						continue;
					}
					if (bufsiz >= 2) {
						comgen_instr(self, gen86_movw_db_r(&self->cg_txptr, srcoff,
						                                   GEN86_R_PCX, GEN86_R_AX));
						if (bufoff == current_pdi_offset) {
							comgen_instr(self, gen86_stosw(&self->cg_txptr));
							current_pdi_offset += 2;
						} else {
							comgen_instr(self, gen86_movw_r_db(&self->cg_txptr, GEN86_R_AX,
							                                   bufoff, GEN86_R_service_com));
						}
						bufsiz -= 2;
						bufoff += 2;
						srcoff += 2;
						continue;
					}
					comgen_instr(self, gen86_movb_db_r(&self->cg_txptr, srcoff,
					                                   GEN86_R_PCX, GEN86_R_AL));
					if (bufoff == current_pdi_offset) {
						comgen_instr(self, gen86_stosb(&self->cg_txptr));
						current_pdi_offset += 1;
					} else {
						comgen_instr(self, gen86_movb_r_db(&self->cg_txptr, GEN86_R_AL,
						                                   bufoff, GEN86_R_service_com));
					}
					break;
				}
			}
		}
	}
}



/* Generate instructions:
 * >>     movP   <cg_service->s_active_list>, %Pax                      # movabs via %Pcx if necessary on x86_64
 * >> 1:  movP   %Pax, service_comdesc::scd_active_link(%R_service_com)
 * >>     lock   cmpxchgP %Pdx, <cg_service->s_active_list>
 * >>     jne    1b */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_add_to_active)(struct com_generator *__restrict self) {
	byte_t *loc_1;

	/* >> movP   <cg_service->s_active_list>, %Pax # movabs via %Pcx if necessary on x86_64 */
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_active_list)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &self->cg_service->s_active_list, GEN86_R_PCX));
		comgen_instr(self, gen86_movP_b_r(&self->cg_txptr, GEN86_R_PCX, GEN86_R_PAX));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_movP_d_r(&self->cg_txptr,
		                                  (uintptr_t)&self->cg_service->s_active_list,
		                                  GEN86_R_PAX));
	}

	/* >> 1: */
	loc_1 = self->cg_txptr;

	/* >> movP   %Pax, service_comdesc::scd_active_link(%R_service_com) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                                   offsetof(struct service_comdesc, scd_active_link),
	                                   GEN86_R_service_com));

	/* >> lock   cmpxchgP %Pdx, <cg_service->s_active_list> */
	comgen_instr(self, gen86_lock(&self->cg_txptr));
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_active_list)) {
		comgen_instr(self, gen86_cmpxchgP_r_mod(&self->cg_txptr, gen86_modrm_b,
		                                        GEN86_R_PDX, GEN86_R_PCX));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_cmpxchgP_r_mod(&self->cg_txptr, gen86_modrm_d, GEN86_R_PDX,
		                                        (uintptr_t)&self->cg_service->s_active_list));
	}

	/* >> jne    1b */
	comgen_instr(self, gen86_jcc8(&self->cg_txptr, GEN86_CC_NE, loc_1));
}



/* Generate instructions:
 * >>     movP   service_shm::s_commands(%R_shmbase), %Pax
 * >> 1:  movP   %Pax, service_comdesc::scd_com::sc_link(%R_service_com)
 * >>     lock   cmpxchgP %Pdx, service_shm::s_commands(%R_shmbase)
 * >>     jne    1b
 * >> .Leh_com_waitfor_begin: */
#ifdef __x86_64__
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_schedule_command)(struct com_generator *__restrict self,
                                       uint8_t GEN86_R_shmbase)
#else /* __x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_schedule_command)(struct com_generator *__restrict self)
#endif /* !__x86_64__ */
{
	byte_t *loc_1;
	/* >> movP   service_shm::s_commands(%R_shmbase), %Pax */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_shm, s_commands),
	                                   GEN86_R_shmbase, GEN86_R_PAX));

	/* >> 1: */
	loc_1 = self->cg_txptr;

	/* >> movP   %Pax, service_comdesc::scd_com::sc_link(%R_service_com) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                                   offsetof(struct service_comdesc, scd_com.sc_link),
	                                   GEN86_R_service_com));

	/* >> lock   cmpxchgP %Pdx, service_shm::s_commands(%R_shmbase) */
	comgen_instr(self, gen86_lock(&self->cg_txptr));
	gen86_cmpxchgP_r_mod(&self->cg_txptr, gen86_modrm_db, GEN86_R_PDX,
	                     offsetof(struct service_shm, s_commands),
	                     GEN86_R_shmbase);

	/* >> jne    1b */
	comgen_instr(self, gen86_jcc8(&self->cg_txptr, GEN86_CC_NE, loc_1));

	/* >> .Leh_com_waitfor_begin: */
	comgen_defsym(self, COM_SYM_Leh_com_waitfor_begin);
}



#ifdef __x86_64__
PRIVATE byte_t const cfi_clear_eflags_ef_on_unwind[] = {
	DW_CFA_KOS_startcapsule,
/*[[[cfi{arch='x86_64', register='%rflags', mode='bytes'}
	push   %rflags
	and    ~$EFLAGS_DF
]]]*/
	22,49,7,146,49,0,11,255,251,26
/*[[[end]]]*/
};
#else /* __x86_64__ */
__LIBC void __i386_Xsyscall(void);
__LIBC void __i386_syscall(void);
#endif /* !__x86_64__ */

/* Generate assembly to perform a system call:
 * >> #ifdef __x86_64__
 * >>     syscall
 * >> #else // __x86_64__
 * >>     call   __i386_syscall
 * >> #endif // !__x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_do_syscall_nx)(struct com_generator *__restrict self) {
#ifdef __x86_64__
	/* >> syscall */
	comgen_instr(self, gen86_syscall(&self->cg_txptr));
#else /* __x86_64__ */
	comgen_instr(self, gen86_call(&self->cg_txptr, &__i386_syscall));
#endif /* !__x86_64__ */
}


/* Generate assembly to perform a system call:
 * >> #ifdef __x86_64__
 * >> #if COM_GENERATOR_FEATURE_FEXCEPT
 * >>     std
 * >>     .cfi_escape 56,22,49,7,146,49,0,11,255,251,26  # Disable EFLAGS.DF during unwind & landing
 * >>     syscall
 * >>     cld
 * >>     .cfi_escape 57
 * >> #else // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     syscall
 * >> #endif // !COM_GENERATOR_FEATURE_FEXCEPT
 * >> #else // __x86_64__
 * >> #if COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   __i386_Xsyscall
 * >> #else // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   __i386_syscall
 * >> #endif // !COM_GENERATOR_FEATURE_FEXCEPT
 * >> #endif // !__x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_do_syscall)(struct com_generator *__restrict self) {
	if (self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT) {
#ifdef __x86_64__
		/* >> std */
		comgen_instr(self, gen86_std(&self->cg_txptr));

		/* >> .cfi_escape 56,22,49,7,146,49,0,11,255,251,26  # Disable EFLAGS.DF during unwind & landing */
		comgen_eh_movehere(self);
		if unlikely(!comgen_ehav(self, sizeof(cfi_clear_eflags_ef_on_unwind))) {
			self->cg_ehptr = self->cg_ehend;
			return;
		}
		self->cg_ehptr = (byte_t *)mempcpy(self->cg_ehptr,
		                                   cfi_clear_eflags_ef_on_unwind,
		                                   sizeof(cfi_clear_eflags_ef_on_unwind));

		/* >> syscall */
		comgen_instr(self, gen86_syscall(&self->cg_txptr));

		/* >> cld */
		comgen_instr(self, gen86_cld(&self->cg_txptr));

		/* >> .cfi_escape 57 */
		comgen_eh_movehere(self);
		comgen_eh_putb(self, DW_CFA_KOS_endcapsule);
#else /* __x86_64__ */
		comgen_instr(self, gen86_call(&self->cg_txptr, &__i386_Xsyscall));
#endif /* !__x86_64__ */
	} else {
		comgen_do_syscall_nx(self);
	}
}



/* Generate instructions:
 * >>     movP   $SYS_lfutex, %Pax
 * >> #ifdef __x86_64__
 * >>     leaq   service_shm::s_commands(%R_shmbase), %rdi # NOTE: %R_shmbase was already initialized above!
 * >>     movq   $LFUTEX_WAKE,                        %rsi
 * >>     movq   $1,                                  %rdx
 * >> #else // __x86_64__
 * >> #if offsetof(service_shm, s_commands) != 0  # HINT: `%R_shmbase' is `%ebx' on i386!
 * >>     addl   $<service_shm::s_commands>, %ebx # NOTE: %R_shmbase was already initialized above!
 * >> #endif // offsetof(service_shm, s_commands) != 0
 * >>     movl   $LFUTEX_WAKE, %ecx
 * >>     movl   $1,           %edx
 * >> #endif // !__x86_64__
 * >>     <comgen_do_syscall_nx> */
#ifdef __x86_64__
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_wake_server)(struct com_generator *__restrict self,
                                  uint8_t GEN86_R_shmbase)
#else /* __x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_wake_server)(struct com_generator *__restrict self)
#endif /* !__x86_64__ */
{
	/* >> movP   $SYS_lfutex, %Pax */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, SYS_lfutex, GEN86_R_PAX));

#ifdef __x86_64__
	/* >> leaq   service_shm::s_commands(%R_shmbase), %rdi */
	if (GEN86_R_shmbase != GEN86_R_RDI) {
		comgen_instr(self, gen86_leaP_db_r(&self->cg_txptr,
		                                   offsetof(struct service_shm, s_commands),
		                                   GEN86_R_shmbase, GEN86_R_RDI));
	} else if (offsetof(struct service_shm, s_commands) != 0) {
		comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr,
		                                    offsetof(struct service_shm, s_commands),
		                                    GEN86_R_RDI));
	}

	/* >> movq   $LFUTEX_WAKE, %rsi */
#if LFUTEX_WAKE == 0
	comgen_instr(self, gen86_xorq_r_r(&self->cg_txptr, GEN86_R_RSI, GEN86_R_RSI));
#else /* LFUTEX_WAKE == 0 */
	comgen_instr(self, gen86_movq_imm_r(&self->cg_txptr, LFUTEX_WAKE, GEN86_R_RSI));
#endif /* LFUTEX_WAKE != 0 */

	/* >> movq   $1, %rdx */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, 1, GEN86_R_RDX));
#else /* __x86_64__ */
	if (offsetof(struct service_shm, s_commands) != 0) {
		comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr,
		                                    offsetof(struct service_shm, s_commands),
		                                    GEN86_R_EBX));
	}

	/* >> movl   $LFUTEX_WAKE, %ecx */
#if LFUTEX_WAKE == 0
	comgen_instr(self, gen86_xorl_r_r(&self->cg_txptr, GEN86_R_ECX, GEN86_R_ECX));
#else /* LFUTEX_WAKE == 0 */
	comgen_instr(self, gen86_movl_imm_r(&self->cg_txptr, LFUTEX_WAKE, GEN86_R_ECX));
#endif /* LFUTEX_WAKE != 0 */

	/* >> movl   $1,           %edx */
	comgen_instr(self, gen86_movl_imm_r(&self->cg_txptr, 1, GEN86_R_EDX));
#endif /* !__x86_64__ */

	/* Invoke the system call. */
	comgen_do_syscall_nx(self);
}



/* Generate instructions:
 * >> .Lwaitfor_completion:
 * >>     movP   $SYS_lfutex, %Pax
 * >> #ifdef __x86_64__
 * >>     leaq   service_comdesc::scd_com::sc_code(%R_service_com), %rdi
 * >>     movq   $LFUTEX_WAIT_WHILE,                                %rsi
 * >>     movq   $<cg_info.dl_comid>,                               %rdx
 * >> #else // __x86_64__
 * >>     leaq   service_comdesc::scd_com::sc_code(%R_service_com), %ebx
 * >>     movl   $LFUTEX_WAIT_WHILE,                                %ecx
 * >>     movl   $<cg_info.dl_comid>,                               %edx
 * >> #endif // !__x86_64__
 * >>     <comgen_do_syscall>
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     cmpP   $(-ELIMIT), %Pax
 * >>     ja     .Lerr_com_abort_errno
 * >> #endif // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     # Check if the operation has completed
 * >>     movP   service_comdesc::scd_com::sc_code(%R_service_com), %R_fcall0P
 * >>     cmpP   $<cg_info.dl_comid>, %R_fcall0P
 * >>     je     .Lwaitfor_completion
 * >> .Leh_com_waitfor_end: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_waitfor_command)(struct com_generator *__restrict self) {
	byte_t *loc_Lwaitfor_completion;

	/* .Lwaitfor_completion: */
	loc_Lwaitfor_completion = self->cg_txptr;

	/* >> movP   $SYS_lfutex, %Pax */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, SYS_lfutex, GEN86_R_PAX));

#ifdef __x86_64__
	/* >> leaq   service_comdesc::scd_com::sc_code(%R_service_com), %rdi */
	comgen_instr(self, gen86_leaq_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_com.sc_code),
	                                   GEN86_R_service_com, GEN86_R_RDI));

	/* >> movq   $LFUTEX_WAIT_WHILE, %rsi */
	comgen_instr(self, gen86_movq_imm_r(&self->cg_txptr, LFUTEX_WAIT_WHILE, GEN86_R_RSI));

	/* >> movq   $<cg_info.dl_comid>, %rdx */
	comgen_instr(self, gen86_movq_imm_r(&self->cg_txptr, self->cg_info.dl_comid, GEN86_R_RSI));

#else /* __x86_64__ */
	/* >> leaq   service_comdesc::scd_com::sc_code(%R_service_com), %ebx */
	comgen_instr(self, gen86_leal_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_com.sc_code),
	                                   GEN86_R_service_com, GEN86_R_EBX));

	/* >> movl   $LFUTEX_WAIT_WHILE, %ecx */
	comgen_instr(self, gen86_movl_imm_r(&self->cg_txptr, LFUTEX_WAIT_WHILE, GEN86_R_ECX));

	/* >> movl   $<cg_info.dl_comid>, %edx */
	comgen_instr(self, gen86_movl_imm_r(&self->cg_txptr, self->cg_info.dl_comid, GEN86_R_EDX));
#endif /* !__x86_64__ */

	/* Invoke the system call. */
	comgen_do_syscall(self);

	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		/* >> cmpP   $(-ELIMIT), %Pax */
		comgen_instr(self, gen86_cmpP_imm_r(&self->cg_txptr, -ELIMIT, GEN86_R_PAX));

		/* >> ja     .Lerr_com_abort_errno */
		comgen_instr(self, gen86_jccl_offset(&self->cg_txptr, GEN86_CC_A, -4));
		comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lerr_com_abort_errno);
	}

	/* Check if the operation has completed */
	/* >> movP   service_comdesc::scd_com::sc_code(%R_service_com), %R_fcall0P */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_com.sc_code),
	                                   GEN86_R_service_com, GEN86_R_FCALL0P));

	/* >> cmpP   $<cg_info.dl_comid>, %R_fcall0P */
	comgen_instr(self, gen86_cmpP_imm_r(&self->cg_txptr,
	                                    self->cg_info.dl_comid,
	                                    GEN86_R_FCALL0P));

	/* >> je     .Lwaitfor_completion */
	comgen_instr(self, gen86_je(&self->cg_txptr, loc_Lwaitfor_completion));

	/* >> .Leh_com_waitfor_end: */
	comgen_defsym(self, COM_SYM_Leh_com_waitfor_end);
}



/* Generate instructions:
 * >>     leaP   service_comdesc::scd_com(%R_service_com), %Pax
 * >>     movP   LOC_shm(%Psp),                            %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pdx),        %Pax # %Pax == shm_offsetof_elem_com
 * >>     movP   service_comdesc::scd_active_link(%R_service_com), %Pdx
 * >>     lock   cmpxchgP %Pdx, <cg_service->s_active_list>           # movabs via %Pcx if necessary on x86_64
 * >>     jne    .Lremove_service_com_tryhard
 * >> .Lremove_service_com_tryhard_return: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_rem_from_active)(struct com_generator *__restrict self) {
	/* >> leaP   service_comdesc::scd_com(%R_service_com), %Pax */
	comgen_instr(self, gen86_leaP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_com),
	                                   GEN86_R_service_com, GEN86_R_PAX));

	/* >> movP   LOC_shm(%Psp), %Pdx */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_shm(self),
	                                   GEN86_R_PSP, GEN86_R_PDX));

	/* >> subP   service_shm_handle::ssh_shm(%Pdx), %Pax # %Pax == shm_offsetof_elem_com */
	comgen_instr(self, gen86_subP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_PAX,
	                                    offsetof(struct service_shm_handle, ssh_shm),
	                                    GEN86_R_PDX));

	/* >> movP   service_comdesc::scd_active_link(%R_service_com), %Pdx */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_active_link),
	                                   GEN86_R_service_com, GEN86_R_PDX));

	/* >> lock   cmpxchgP %Pdx, <cg_service->s_active_list> # movabs via %Pcx if necessary on x86_64 */
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_active_list)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &self->cg_service->s_active_list, GEN86_R_PCX));
		comgen_instr(self, gen86_lock(&self->cg_txptr));
		comgen_instr(self, gen86_cmpxchgP_r_mod(&self->cg_txptr, gen86_modrm_b,
		                                        GEN86_R_PDX, GEN86_R_PCX));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_lock(&self->cg_txptr));
		comgen_instr(self, gen86_cmpxchgP_r_mod(&self->cg_txptr, gen86_modrm_d, GEN86_R_PDX,
		                                        (uintptr_t)&self->cg_service->s_active_list));
	}

	/* >> jne    .Lremove_service_com_tryhard */
	comgen_instr(self, gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NE, -4));
	comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lremove_service_com_tryhard);

	/* >> .Lremove_service_com_tryhard_return: */
	comgen_defsym(self, COM_SYM_Lremove_service_com_tryhard_return);
}



/* Generate instructions:
 * >> {foreach[INLINE_INOUT_OUT_BUFFER_ARGUMENT: <cibp_buffer_offset>, <cibp_sizeof>, <cibp_param_offset>]: {
 * >> #if COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     leaP   <cibp_buffer_offset>(%R_service_com), %Psi # This instruction is skipped if `Psi' already has the
 * >>                                                       # correct value, which may be the case if a preceding
 * >>                                                       # inline buffer already set it up correctly.
 * >>                                                       # May also be encoded as `addP $..., %Psi' if appropriate
 * >>     movP   <cibp_param_offset>(%Psp),            %Pdi
 * >>     movP   $<cibp_sizeof>,                       %Pcx # Or an equivalent series of inline `[rep] movsX' instructions
 * >>     rep    movsb
 * >> #else // COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     movP   <cibp_param_offset>(%Psp), %Pcx
 * >>     {INLINE_MEMCPY(_OFF, _BWLQ, <cibp_sizeof>) {
 * >>         mov{_BWLQ} <cibp_buffer_offset>+_OFF(%R_service_com), %{_BWLQ}ax
 * >>         mov{_BWLQ} %{_BWLQ}ax,                                 _OFF(%Pcx)
 * >>     }}
 * >> #endif // !COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >> }} */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_deserialize_inline_buffers)(struct com_generator *__restrict self) {
	uint8_t i;
	uint16_t current_psi_offset = (uint16_t)-1;
	for (i = 0; i < self->cg_inline_buf_paramc; ++i) {
		int16_t spoffset;
		uint16_t bufsiz, bufoff;
		if (!(self->cg_inline_buf_paramv[i].cibp_flags & COM_INLINE_BUFFER_PARAM_FOUT))
			continue;
		bufsiz = self->cg_inline_buf_paramv[i].cibp_sizeof;
		if unlikely(bufsiz == 0)
			continue;
		bufoff   = self->cg_inline_buf_paramv[i].cibp_buffer_offset;
		spoffset = self->cg_inline_buf_paramv[i].cibp_param_offset + self->cg_cfa_offset;
		if ((bufsiz >= COM_USEMOVS_THRESHOLD) &&
		    (self->cg_features & COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS)) {
			/* >> leaP   <cibp_buffer_offset>(%R_service_com), %Psi # This instruction is skipped if `Psi' already has the
			 * >>                                                   # correct value, which may be the case if a preceding
			 * >>                                                   # inline buffer already set it up correctly.
			 * >>                                                   # May also be encoded as `addP $..., %Psi' if appropriate */
			if (current_psi_offset == (uint16_t)-1) {
				comgen_instr(self, gen86_leaP_db_r(&self->cg_txptr, bufoff,
				                                   GEN86_R_service_com, GEN86_R_PSI));
			} else if (current_psi_offset < bufoff) {
				uint16_t delta = bufoff - current_psi_offset;
				comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, delta, GEN86_R_PSI));
			} else if (current_psi_offset > bufoff) {
				uint16_t delta = current_psi_offset - bufoff;
				comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, delta, GEN86_R_PSI));
			}
			current_psi_offset = bufoff;

			/* >> movP   <cibp_param_offset>(%Psp), %Pdi */
			comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, spoffset,
			                                   GEN86_R_PSP, GEN86_R_PDI));

			/* >> movP   $<cibp_sizeof>, %Pcx
			 * >> rep    movsb */
			comgen_memcpy_with_rep_movs(self, bufsiz);
			current_psi_offset += bufsiz;
		} else {
			uint16_t dstoff;
			/* >> movP   <cibp_param_offset>(%Psp), %Pcx */
			comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, spoffset,
			                                   GEN86_R_PSP, GEN86_R_PCX));

			/* >> {INLINE_MEMCPY(_OFF, _BWLQ, <cibp_sizeof>) {
			 * >>         mov{_BWLQ} <cibp_buffer_offset>+_OFF(%R_service_com), %{_BWLQ}ax
			 * >>         mov{_BWLQ} %{_BWLQ}ax,                                 _OFF(%Pcx)
			 * >> }} */
			dstoff = 0;
			while (bufsiz) {
#ifdef __x86_64__
				if (bufsiz >= 8) {
					if (bufoff == current_psi_offset) {
						comgen_instr(self, gen86_lodsq(&self->cg_txptr));
						current_psi_offset += 8;
					} else {
						comgen_instr(self, gen86_movq_db_r(&self->cg_txptr, bufoff, GEN86_R_service_com, GEN86_R_RAX));
					}
					comgen_instr(self, gen86_movq_r_db(&self->cg_txptr, GEN86_R_RAX, dstoff, GEN86_R_PCX));
					bufsiz -= 8;
					bufoff += 8;
					dstoff += 8;
					continue;
				}
#endif /* __x86_64__ */
				if (bufsiz >= 4) {
					if (bufoff == current_psi_offset) {
						comgen_instr(self, gen86_lodsl(&self->cg_txptr));
						current_psi_offset += 4;
					} else {
						comgen_instr(self, gen86_movl_db_r(&self->cg_txptr, bufoff, GEN86_R_service_com, GEN86_R_EAX));
					}
					comgen_instr(self, gen86_movl_r_db(&self->cg_txptr, GEN86_R_EAX, dstoff, GEN86_R_PCX));
					bufsiz -= 4;
					bufoff += 4;
					dstoff += 4;
					continue;
				}
				if (bufsiz >= 2) {
					if (bufoff == current_psi_offset) {
						comgen_instr(self, gen86_lodsw(&self->cg_txptr));
						current_psi_offset += 2;
					} else {
						comgen_instr(self, gen86_movw_db_r(&self->cg_txptr, bufoff, GEN86_R_service_com, GEN86_R_AX));
					}
					comgen_instr(self, gen86_movw_r_db(&self->cg_txptr, GEN86_R_AX, dstoff, GEN86_R_PCX));
					bufsiz -= 2;
					bufoff += 2;
					dstoff += 2;
					continue;
				}
				if (bufoff == current_psi_offset) {
					comgen_instr(self, gen86_lodsb(&self->cg_txptr));
					current_psi_offset += 1;
				} else {
					comgen_instr(self, gen86_movb_db_r(&self->cg_txptr, bufoff, GEN86_R_service_com, GEN86_R_AL));
				}
				comgen_instr(self, gen86_movb_r_db(&self->cg_txptr, GEN86_R_AL, dstoff, GEN86_R_PCX));
				break;
			}
		}
	}
}



/* Generate instructions:
 * >> #if cg_inoutbuf_paramc != 0 || cg_outbuf_paramc != 0
 * >>     # Load %Psi with the SHM address of the first out-of-band inout/out buffer
 * >>     # NOTE: We unconditionally use %Psi for copying!
 * >> #if cg_inbuf_paramc != 0
 * >> #if COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   LOC_bufpar_ptr(%Psp), %Psi
 * >>     addP   $<SUM(IN_BUFFERS.each.FIXED_BUFFER_SIZE.ceil_align(SERVICE_BUFFER_ALIGNMENT)>, %Psi
 * >> #else // COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   LOC_outbuffers_start(%Psp), %Psi
 * >> #endif // !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >> #else // cg_inbuf_paramc != 0
 * >>     movP   LOC_bufpar_ptr(%Psp), %Psi
 * >> #endif // cg_inbuf_paramc == 0
 * >>
 * >>     # Copy out-of-band SHM buffers for inout/out arguments back to user-memory
 * >> {foreach[INOUT_OUT_BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     cmpP   $0, LOC_bufparam_handles[INDEX](%Psp)
 * >>     jne    1f
 * >>     movP   ...,                      %Pcx # required buffer size (depending on buffer type)
 * >>                                           # Allowed to clobber: %Pax, %Pdx, %Pdi
 * >>     movP   <cbp_param_offset>(%Psp), %Pdi # Unconditionally use %Psi for copying!
 * >>     rep    movsb
 * >> #if INDEX != cg_buf_paramc -1
 * >> #if cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #if !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT - (cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE & (SERVICE_BUFFER_ALIGNMENT - 1))>, %Psi   # Re-align by pointer size
 * >> #endif // !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >> #else // cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >>     ... # NOTE: In case of a `COM_BUFFER_PARAM_FRETMIN' param, also add the difference
 * >>         #       between `bufsize' and `return' to `%Psi' (when `return < bufsize')
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT-1>,    %Psi   # Re-align buffer pointer
 * >>     andP   $<~(SERVICE_BUFFER_ALIGNMENT-1)>, %Psi   # *ditto*
 * >> #endif // !cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #endif // INDEX != cg_buf_paramc -1
 * >> 1:
 * >> }}
 * >> #endif // cg_inoutbuf_paramc != 0 || cg_outbuf_paramc != 0 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_deserialize_buffer_arguments)(struct com_generator *__restrict self) {
	uint8_t i;
	if (self->cg_inoutbuf_paramc == 0 && self->cg_outbuf_paramc == 0)
		return;

	if (self->cg_inbuf_paramc != 0) {
		if (self->cg_features & COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN) {
			uint16_t total_aligned_in_buffer_size;

			/* >> movP   LOC_bufpar_ptr(%Psp), %Psi */
			comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
			                                   comgen_spoffsetof_LOC_bufpar_ptr(self),
			                                   GEN86_R_PSP, GEN86_R_PSI));

			/* >> addP   $<SUM(IN_BUFFERS.each.FIXED_BUFFER_SIZE.ceil_align(SERVICE_BUFFER_ALIGNMENT)>, %Psi */
			total_aligned_in_buffer_size = 0;
			for (i = 0; i < self->cg_inbuf_paramc; ++i) {
				uint8_t param_index;
				uint16_t param_size;
				assert(self->cg_buf_paramv[i].cbp_flags & COM_BUFFER_PARAM_FFIXED);
				param_index = self->cg_buf_paramv[i].cbp_param_offset;
				param_size  = self->cg_info.dl_params[param_index] & _SERVICE_TYPE_PARAMMASK;
				param_size  = CEIL_ALIGN(param_size, SERVICE_BUFFER_ALIGNMENT);
				total_aligned_in_buffer_size += param_size;
			}
			if (total_aligned_in_buffer_size != 0) {
				comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr,
				                                    total_aligned_in_buffer_size,
				                                    GEN86_R_PSI));
			}
		} else {
			/* >> movP   LOC_outbuffers_start(%Psp), %Psi */
			comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
			                                   comgen_spoffsetof_LOC_outbuffers_start(self),
			                                   GEN86_R_PSP, GEN86_R_PSI));
		}
	} else {
		/* >> movP   LOC_bufpar_ptr(%Psp), %Psi */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   comgen_spoffsetof_LOC_bufpar_ptr(self),
		                                   GEN86_R_PSP, GEN86_R_PSI));
	}

	/* >> {foreach[INOUT_OUT_BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>]: { */
	for (i = self->cg_inbuf_paramc; i < self->cg_buf_paramc; ++i) {
		int16_t param_offset;
		int8_t *pdisp_1;
		uint8_t param_index;
		service_typeid_t param_typ;
		param_offset = self->cg_buf_paramv[i].cbp_param_offset + self->cg_cfa_offset;
		param_index  = self->cg_buf_paramv[i].cbp_param_index;
		param_typ          = self->cg_info.dl_params[param_index];
		assert(self->cg_buf_paramv[i].cbp_flags & COM_BUFFER_PARAM_FOUT);

		/* >> cmpP   $0, LOC_bufparam_handles[INDEX](%Psp) */
		comgen_instr(self, gen86_cmpP_imm_mod(&self->cg_txptr, gen86_modrm_db, 0,
		                                      comgen_spoffsetof_LOC_bufpar_handles(self, i),
		                                      GEN86_R_PSP));

		/* >> jne    1f */
		comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NE, -1));
		pdisp_1 = (int8_t *)(self->cg_txptr - 1);

		if (self->cg_buf_paramv[i].cbp_flags & COM_BUFFER_PARAM_FFIXED) {
			uint16_t param_size;
			param_size = param_typ & _SERVICE_TYPE_PARAMMASK;
			/* >> movP   ...,                      %Pcx
			 * >> movP   <cbp_param_offset>(%Psp), %Pdi
			 * >> rep    movsb */
			comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, param_offset,
			                                   GEN86_R_PSP, GEN86_R_PDI));
			comgen_memcpy_with_rep_movs(self, param_size);

			if (i != self->cg_buf_paramc - 1 && !IS_ALIGNED(param_size, SERVICE_BUFFER_ALIGNMENT)) {
				/* Re-align buffer pointer */
				comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr,
				                                    SERVICE_BUFFER_ALIGNMENT - (param_size & (SERVICE_BUFFER_ALIGNMENT - 1)),
				                                    GEN86_R_PSI));
			}
		} else {
			uint16_t bufsize_argid;
			int16_t bufsize_sp_offset;
			/* Non-fixed-length output buffer means that the buffer's size
			 * depends on some parameter, optionally also affected by  the
			 * return value posted by the server. */

			bufsize_argid     = (param_typ & (_SERVICE_TYPE_PARAMMASK & ~SERVICE_OUT_SIZEARG_RETURN_MINVAL));
			bufsize_sp_offset = comgen_spoffsetof_param(self, bufsize_argid);
			if (self->cg_buf_paramv[i].cbp_flags & COM_BUFFER_PARAM_FRETMIN) {
				/* Must minimize `%Pcx' by the function's return value:
				 * >>     movP   service_comdesc::scd_com::sc_retval(%R_service_com), %Pcx
				 * >>     movP   bufsize_sp_offset(%Psp), %Pax
				 * >>     cmpP   %Pax, %Pcx
				 * >>     cmovbP %Pax, %Pcx
				 * >> #if i != self->cg_buf_paramc - 1
				 * >>     addP   %Psi, %Pax
				 * >> #endif // i != self->cg_buf_paramc - 1
				 * >>     movP   param_offset(%Psp), %Pdi
				 * >>     rep    movsb
				 * >> #if i != self->cg_buf_paramc - 1
				 * >>     movP   %Pax, %Psi
				 * >> #endif // i != self->cg_buf_paramc - 1 */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
				                                   offsetof(struct service_comdesc, scd_com.sc_retval),
				                                   GEN86_R_service_com, GEN86_R_PCX));
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, bufsize_sp_offset, GEN86_R_PSP, GEN86_R_PAX));
				comgen_instr(self, gen86_cmpP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PCX));
				comgen_instr(self, gen86_cmovbP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PCX));
				if (i != self->cg_buf_paramc - 1)
					comgen_instr(self, gen86_addP_r_r(&self->cg_txptr, GEN86_R_PSI, GEN86_R_PAX));
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, param_offset, GEN86_R_PSP, GEN86_R_PDI));
				comgen_instr(self, gen86_rep_movsb(&self->cg_txptr));
				if (i != self->cg_buf_paramc - 1)
					comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PSI));
			} else {
				/* >> movP   ..., %Pcx # required buffer size (depending on buffer type)
				 * >>                  # Allowed to clobber: %Pax, %Pdx, %Pdi */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, bufsize_sp_offset, GEN86_R_PSP, GEN86_R_PCX));

				/* >> movP   <cbp_param_offset>(%Psp), %Pdi # Unconditionally use %Psi for copying! */
				comgen_instr(self, gen86_movP_db_r(&self->cg_txptr, param_offset,
				                                   GEN86_R_PSP, GEN86_R_PDI));

				/* >> rep    movsb */
				comgen_instr(self, gen86_rep_movsb(&self->cg_txptr));
			}
			if (i != self->cg_buf_paramc - 1) {
				/* >> addP   $<SERVICE_BUFFER_ALIGNMENT-1>,    %Psi   # Re-align buffer pointer */
				comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, SERVICE_BUFFER_ALIGNMENT - 1, GEN86_R_PSI));

				/* >> andP   $<~(SERVICE_BUFFER_ALIGNMENT-1)>, %Psi   # *ditto* */
				comgen_instr(self, gen86_andP_imm_r(&self->cg_txptr, ~(SERVICE_BUFFER_ALIGNMENT - 1), GEN86_R_PSI));
			}
		}

		/* >> 1: */
		*pdisp_1 += (int8_t)(uint8_t)(uintptr_t)
		            (self->cg_txptr - (byte_t *)pdisp_1);
	}
	/* >> }} */
}



/* Generate instructions:
 * >>     movP   LOC_upm(%Psp), %Pax
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset,  %R_fcall0P
 * >>     movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $<cg_service>, %R_fcall0P
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >>     call   libservice_shmbuf_freeat_fast_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr)(struct com_generator *__restrict self) {
	/* >> movP   LOC_upm(%Psp), %Pax */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_upm(self),
	                                   GEN86_R_PSP, GEN86_R_PAX));

	/* NOTE: `__code_model_large__' is defined when `-mcmodel=large' is passed
	 *       to GCC on the commandline. In all other modes, this library would
	 *       already  be broken when _ANY_ of its symbols were located outside
	 *       of the signed 32-bit address range.
	 * As such, we only need to handle overly-large symbol addresses when the
	 * library was built for that configuration. */
#if defined(__x86_64__) && defined(__code_model_large__)
	if (!_gen86_fitsl((uintptr_t)&full_sigset)) {
		/* >> movabs $full_sigset,  %R_fcall0P */
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &full_sigset, GEN86_R_FCALL0P));

		/* >> movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption */
		comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_FCALL0P,
		                                   offsetof(struct userprocmask, pm_sigmask),
		                                   GEN86_R_PAX));

		/* >> movP   $<cg_service>, %R_fcall0P */
		comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));
	} else
#endif /* __x86_64__ && __code_model_large__ */
	{
		/* >> movP   $<cg_service>, %R_fcall0P */
		comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));

		/* >> movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption */
		comgen_instr(self, gen86_movP_imm_db(&self->cg_txptr, (uintptr_t)&full_sigset,
		                                     offsetof(struct userprocmask, pm_sigmask),
		                                     GEN86_R_PAX));
	}

	/* >> call   libservice_shmbuf_freeat_fast_nopr */
	comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_shmbuf_freeat_fast_nopr));

#ifndef __x86_64__
	/* >> .cfi_adjust_cfa_offset -8 */
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -8);
#endif /* !__x86_64__ */
}


/* Generate    instructions:
 * >> #if cg_buf_paramc != 0
 * >> .Leh_free_xbuf_end:
 * >>     movP   LOC_bufpar_ptr(%Psp), %Pdx
 * >>     testP  %Pdx, %Pdx
 * >>     jz     1f
 * >>     subP   $<sizeof(size_t)>, %Pdx
 * >> #ifdef __x86_64__
 * >>     movP   0(%Pdx), %Pcx
 * >> #else // __x86_64__
 * >>     pushl_cfi 0(%Pdx)
 * >>     pushl_cfi %Pdx
 * >> #endif // !__x86_64__
 * >>     movP   LOC_bufpar_shm(%Psp), %R_fcall1P
 * >>     <comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr>
 * >> 1:
 * >> #endif // cg_buf_paramc != 0 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_free_xbuf)(struct com_generator *__restrict self) {
	int8_t *pdisp_1;
	if (self->cg_buf_paramc == 0)
		return;

	/* >> .Leh_free_xbuf_end: */
	comgen_defsym(self, COM_SYM_Leh_free_xbuf_end);

	/* >> movP   LOC_bufpar_ptr(%Psp), %Pdx */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_bufpar_ptr(self),
	                                   GEN86_R_PSP, GEN86_R_PDX));

	/* >> testP  %Pdx, %Pdx */
	comgen_instr(self, gen86_testP_r_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_PDX));

	/* >> jz     1f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_Z, -1));
	pdisp_1 = (int8_t *)(self->cg_txptr - 1);

	/* >> subP   $<sizeof(size_t)>, %Pdx */
	comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, sizeof(size_t), GEN86_R_PDX));

#ifdef __x86_64__
	/* >> movP   0(%Pdx), %Pcx */
	comgen_instr(self, gen86_movP_b_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_PCX));
#else /* __x86_64__ */
	/* >> pushl_cfi 0(%Pdx) */
	comgen_instr(self, gen86_pushl_mod(&self->cg_txptr, gen86_modrm_b, GEN86_R_PDX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);

	/* >> pushl_cfi %Pdx */
	comgen_instr(self, gen86_pushl_r(&self->cg_txptr, GEN86_R_PDX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

	/* >> movP   LOC_bufpar_shm(%Psp), %R_fcall1P */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_bufpar_shm(self),
	                                   GEN86_R_PSP, GEN86_R_FCALL1P));

	/* >> <comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr> */
	comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr(self);

	/* >> 1: */
	*pdisp_1 += (int8_t)(uint8_t)(uintptr_t)
	            (self->cg_txptr - (byte_t *)pdisp_1);
}



/* Generate instructions:
 * >> .Leh_free_service_com_end:
 * >>     subP   $<sizeof(size_t)>, %R_service_com
 * >> #ifdef __x86_64__
 * >>     movq   0(%R_service_com), %rcx
 * >>     movq   %R_service_com,    %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi 0(%R_service_com)
 * >>     pushl_cfi %R_service_com
 * >> #endif // !__x86_64__
 * >>     movP   LOC_shm(%Psp), %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movq   service_comdesc::scd_com::sc_retval::scr_rax+<sizeof(size_t)>(%R_service_com), %rbp # Load return values
 * >> #else // __x86_64__
 * >> #if cg_info.dl_return == SERVICE_TYPE_386_R64
 * >>     movl   service_comdesc::scd_com::sc_retval::scr_edx+<sizeof(size_t)>(%R_service_com), %ebx # Load return values
 * >> #endif // cg_info.dl_return == SERVICE_TYPE_386_R64
 * >>     movl   service_comdesc::scd_com::sc_retval::scr_eax+<sizeof(size_t)>(%R_service_com), %ebp # *ditto*
 * >> #endif // !__x86_64__
 * >> #if cg_buf_paramc == 0
 * >>     movP   LOC_upm(%Psp), %Pax
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset,  %R_fcall0P
 * >>     movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $<cg_service>, %R_fcall0P
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >> #else // cg_buf_paramc == 0
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #endif // cg_buf_paramc != 0
 * >>     call   libservice_shmbuf_freeat_fast_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_free_combuf)(struct com_generator *__restrict self) {
	/* >> .Leh_free_service_com_end: */
	comgen_defsym(self, COM_SYM_Leh_free_service_com_end);

	/* >> subP   $<sizeof(size_t)>, %R_service_com */
	comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, sizeof(size_t),
	                                    GEN86_R_service_com));

#ifdef __x86_64__
	/* >> movq   0(%R_service_com), %rcx */
	comgen_instr(self, gen86_movq_b_r(&self->cg_txptr, GEN86_R_service_com, GEN86_R_RCX));

	/* >> movq   %R_service_com,    %rdx */
	comgen_instr(self, gen86_movq_r_r(&self->cg_txptr, GEN86_R_service_com, GEN86_R_RDX));
#else /* __x86_64__ */
	/* >> pushl_cfi 0(%R_service_com) */
	comgen_instr(self, gen86_pushl_mod(&self->cg_txptr, gen86_modrm_b, GEN86_R_service_com));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);

	/* >> pushl_cfi %R_service_com */
	comgen_instr(self, gen86_pushl_r(&self->cg_txptr, GEN86_R_service_com));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

	/* >> movP   LOC_shm(%Psp), %R_fcall1P */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_shm(self),
	                                   GEN86_R_PSP, GEN86_R_FCALL1P));

	/* <comgen_load_return_value_from_service_com(sizeof(size_t))> */
#ifdef __x86_64__
	/* >> movq   service_comdsec::scd_com::sc_retval::scr_rax+<sizeof(size_t)>(%R_service_com), %rbp # Load return values */
	comgen_instr(self, gen86_movq_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_com.sc_retval.scr_rax) + sizeof(size_t),
	                                   GEN86_R_service_com, GEN86_R_RBP));
#else /* __x86_64__ */
	if (self->cg_info.dl_return == SERVICE_TYPE_386_R64) {
		/* >> movl   service_comdsec::scd_com::sc_retval::scr_edx+<sizeof(size_t)>(%R_service_com), %ebx # Load return values */
		comgen_instr(self, gen86_movl_db_r(&self->cg_txptr,
		                                   offsetof(struct service_comdesc, scd_com.sc_retval.scr_edx) + sizeof(size_t),
		                                   GEN86_R_service_com, GEN86_R_EBX));
	}

	/* >> movl   service_comdsec::scd_com::sc_retval::scr_eax+<sizeof(size_t)>(%R_service_com), %ebp # *ditto* */
	comgen_instr(self, gen86_movl_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_com.sc_retval.scr_eax) + sizeof(size_t),
	                                   GEN86_R_service_com, GEN86_R_EBP));
#endif /* !__x86_64__ */

	if (self->cg_buf_paramc == 0) {
		/* >> movP   LOC_upm(%Psp), %Pax */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   comgen_spoffsetof_LOC_upm(self),
		                                   GEN86_R_PSP, GEN86_R_PAX));

#if defined(__x86_64__) && defined(__code_model_large__)
		if (!_gen86_fitsl((uintptr_t)&full_sigset)) {
			/* >> movabs $full_sigset,  %R_fcall0P */
			comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &full_sigset, GEN86_R_FCALL0P));

			/* >> movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption */
			comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_FCALL0P,
			                                   offsetof(struct userprocmask, pm_sigmask),
			                                   GEN86_R_PAX));

			/* >> movP   $<cg_service>, %R_fcall0P */
			comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));
		} else
#endif /* __x86_64__ && __code_model_large__ */
		{
			/* >> movP   $<cg_service>, %R_fcall0P */
			comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));

			/* >> movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption */
			comgen_instr(self, gen86_movP_imm_db(&self->cg_txptr, (uintptr_t)&full_sigset,
			                                     offsetof(struct userprocmask, pm_sigmask),
			                                     GEN86_R_PAX));
		}
	} else {
		/* >> movP   $<cg_service>, %R_fcall0P */
		comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));
	}

	/* >> call   libservice_shmbuf_freeat_fast_nopr */
	comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_shmbuf_freeat_fast_nopr));

#ifndef __x86_64__
	/* >> .cfi_adjust_cfa_offset -8 */
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -8);
#endif /* !__x86_64__ */
}



/* Generate instructions:
 * >> .Leh_preemption_pop_end:
 * >>     popP_cfi %Pdx              # `sigset_t *oldset'
 * >>     popP_cfi %Pax              # `struct userprocmask *upm'
 * >>     .cfi_remember_state
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    .Lcheck_signals_before_return
 * >> .Lafter_check_signals_before_return: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_restore_preemption)(struct com_generator *__restrict self) {
	/* >> .Leh_preemption_pop_end: */
	comgen_defsym(self, COM_SYM_Leh_preemption_pop_end);

	/* >> popP_cfi %Pdx              # `sigset_t *oldset' */
	comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PDX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

	/* >> popP_cfi %Pax              # `struct userprocmask *upm' */
	comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PAX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

	/* >> .cfi_remember_state */
	comgen_eh_DW_CFA_remember_state(self);

	/* >> movP   %Pdx, userprocmask::pm_sigmask(%Pax) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                                   offsetof(struct userprocmask, pm_sigmask),
	                                   GEN86_R_PAX));

	/* >> test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax) */
	comgen_instr(self, gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db,
	                                       USERPROCMASK_FLAG_HASPENDING,
	                                       offsetof(struct userprocmask, pm_flags),
	                                       GEN86_R_PAX));

	/* >> jnz    .Lcheck_signals_before_return */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NZ, -1));
	comgen_reloc(self, self->cg_txptr - 1, COM_R_PCREL8, COM_SYM_Lcheck_signals_before_return);

	/* >> .Lafter_check_signals_before_return: */
	comgen_defsym(self, COM_SYM_Lafter_check_signals_before_return);
}



/* Generate instructions:
 * >> #ifdef __x86_64__
 * >>     addP   $<cg_locvar_size + (MIN(cg_paramc, 6) * 8) - 2 * 8>, %Psp
 * >>     .cfi_adjust_cfa_offset -<cg_locvar_size + (MIN(cg_paramc, 6) * 8) - 2 * 8>
 * >> #else // __x86_64__
 * >>     addP   $<cg_locvar_size - 2 * 4>, %Psp        # local variables
 * >>     .cfi_adjust_cfa_offset -<cg_locvar_size - 2 * 4>
 * >> #endif // !__x86_64__
 * >> #ifdef __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_RBX
 * >>     popP_cfi_r %rbx        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_RBX
 * >> #else // __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_EDI
 * >>     popP_cfi_r %Pdi        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_EDI
 * >> #if COM_GENERATOR_FEATURE_USES_ESI
 * >>     popP_cfi_r %Psi        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_ESI
 * >> #endif // !__x86_64__
 * >>     // Set return values
 * >> #ifdef __x86_64__
 * >>     movq   %rbp, %rax
 * >> #else // __x86_64__
 * >>     movl   %ebp, %eax
 * >>     movl   %ebx, %edx
 * >> #endif // !__x86_64__
 * >>     // Restore preserved registers
 * >> #ifndef __x86_64__
 * >>     popP_cfi_r %Pbx
 * >> #endif // !__x86_64__
 * >>     popP_cfi_r %Pbp
 * >>     ret */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_normal_return)(struct com_generator *__restrict self) {
	int16_t sp_delta;
#ifdef __x86_64__
	/* >> addP   $<cg_locvar_size + (MIN(cg_paramc, 6) * 8)>, %Psp */
	sp_delta = (int16_t)self->cg_locvar_size;
	sp_delta += MIN(self->cg_paramc, 6) * 8;
	sp_delta -= 2 * 8;
#else /* __x86_64__ */
	/* >> addP   $<cg_locvar_size - 2 * 4>, %Psp        # local variables */
	sp_delta = (int16_t)self->cg_locvar_size;
	sp_delta -= 2 * 4;
#endif /* !__x86_64__ */
	if (sp_delta != 0) {
		/* >> addP   $<sp_delta>, %Psp        # local variables */
		comgen_instr(self, gen86_addP_imm_r(&self->cg_txptr, sp_delta, GEN86_R_PSP));

		/* >> .cfi_adjust_cfa_offset -<sp_delta> */
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, -sp_delta);
	}

#ifdef __x86_64__
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_RBX) {
		/* >> popP_cfi_r %rbx        # Only if used anywhere above */
		comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PBX));
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_restore(self, CFI_X86_UNWIND_REGISTER_PBX);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);
	}
#else /* __x86_64__ */
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_EDI) {
		/* >> popP_cfi_r %Pdi        # Only if used anywhere above */
		comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PDI));
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_restore(self, CFI_X86_UNWIND_REGISTER_PDI);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);
	}
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_ESI) {
		/* >> popP_cfi_r %Psi        # Only if used anywhere above */
		comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PSI));
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_restore(self, CFI_X86_UNWIND_REGISTER_PSI);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);
	}
#endif /* !__x86_64__ */

	/* Set return values */
#ifdef __x86_64__
	comgen_instr(self, gen86_movq_r_r(&self->cg_txptr, GEN86_R_RBP, GEN86_R_RAX));
#else /* __x86_64__ */
	comgen_instr(self, gen86_movl_r_r(&self->cg_txptr, GEN86_R_EBP, GEN86_R_EAX));
	comgen_instr(self, gen86_movl_r_r(&self->cg_txptr, GEN86_R_EBX, GEN86_R_EDX));
#endif /* !__x86_64__ */

	/* Restore preserved registers */
#ifndef __x86_64__
	/* >> popP_cfi_r %Pbx */
	comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PBX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_restore(self, CFI_X86_UNWIND_REGISTER_PBX);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);
#endif /* !__x86_64__ */

	/* >> popP_cfi_r %Pbp */
	comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PBP));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_restore(self, CFI_X86_UNWIND_REGISTER_PBP);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

	/* >> ret */
	comgen_instr(self, gen86_ret(&self->cg_txptr));
}

#ifndef NDEBUG
#define ASSERT_SYMBOL_DEFINED(self, id) assert((self)->cg_symbols[id] != 0)
#define comgen_gen86_jmp_symbol(self, id)                    \
	comgen_instr(self, (assert((self)->cg_symbols[id] != 0), \
	                    gen86_jmp(&(self)->cg_txptr,         \
	                              comgen_symaddr(self, id))))
#define comgen_gen86_jcc_symbol(self, cc, id)                \
	comgen_instr(self, (assert((self)->cg_symbols[id] != 0), \
	                    gen86_jcc(&(self)->cg_txptr, cc,     \
	                              comgen_symaddr(self, id))))
#else /* !NDEBUG */
#define ASSERT_SYMBOL_DEFINED(self, id) (void)0
#define comgen_gen86_jmp_symbol(self, id) \
	comgen_instr(self, gen86_jmp(&(self)->cg_txptr, comgen_symaddr(self, id)))
#define comgen_gen86_jcc_symbol(self, cc, id) \
	comgen_instr(self, gen86_jcc(&(self)->cg_txptr, cc, comgen_symaddr(self, id)))
#endif /* NDEBUG */


/* Generate instructions:
 * >>     .cfi_restore_state
 * >> .Lcheck_signals_before_return:
 * >>     call   chkuserprocmask
 * >>     jmp    .Lafter_check_signals_before_return
 * >>     .cfi_restore_state */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_sigcheck_before_return)(struct com_generator *__restrict self) {
	/* >> .cfi_restore_state */
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_restore_state(self);

	/* >> .Lcheck_signals_before_return: */
	comgen_defsym(self, COM_SYM_Lcheck_signals_before_return);

	/* >> call   chkuserprocmask */
	comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

	/* >> jmp    .Lafter_check_signals_before_return */
	comgen_gen86_jmp_symbol(self, COM_SYM_Lcheck_signals_before_return);

	/* >> .cfi_restore_state */
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_restore_state(self);
}



/* Generate    instructions:
 * >> #if cg_buf_paramc == 0
 * >> .Ltest_pending_signals_after_com_buffer_alloc:
 * >>     call   chkuserprocmask
 * >>     jmp    .Ltest_pending_signals_after_com_buffer_alloc_return
 * >> #elif cg_buf_paramc == 1
 * >> .Ltest_pending_signals_after_single_buffer_alloc:
 * >>     call   chkuserprocmask
 * >>     jmp    .Ltest_pending_signals_after_single_buffer_alloc_return
 * >> .Ltest_pending_signals_after_single_buffers_is_in_band:
 * >>     pushP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, SIZEOF_POINTER   # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     call   chkuserprocmask
 * >>     popP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 0                # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     jmp .Ltest_pending_signals_after_single_buffers_is_in_band_return
 * >> #else // #elif cg_buf_paramc >= 2
 * >> #if cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >> .Ltest_pending_signals_after_xbuf_alloc:
 * >>     pushP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, SIZEOF_POINTER   # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     pushP_cfi %Pdx
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 2*SIZEOF_POINTER # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     call   chkuserprocmask
 * >>     popP_cfi %Pdx
 * >> //  .cfi_escape DW_CFA_GNU_args_size, SIZEOF_POINTER   # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     popP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 0                # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     jmp .Ltest_pending_signals_after_xbuf_alloc_return
 * >> #endif // cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >> .Ltest_pending_signals_after_all_buffers_are_in_band:
 * >>     call   chkuserprocmask
 * >>     jmp    .Lall_buffers_are_in_band_preemption_reenabled:
 * >> #endif // #endif cg_buf_paramc >= 2 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_sigcheck_for_buffers)(struct com_generator *__restrict self) {
	switch (self->cg_buf_paramc) {

	case 0:
		/* >> .Ltest_pending_signals_after_com_buffer_alloc: */
		comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_com_buffer_alloc);

		/* >>     call   chkuserprocmask */
		comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

		/* >>     jmp    .Ltest_pending_signals_after_com_buffer_alloc_return */
		comgen_gen86_jmp_symbol(self, COM_SYM_Ltest_pending_signals_after_com_buffer_alloc_return);
		break;

	case 1:
		/* >> .Ltest_pending_signals_after_single_buffer_alloc: */
		comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_single_buffer_alloc);

		/* >> call   chkuserprocmask */
		comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

		/* >> jmp    .Ltest_pending_signals_after_single_buffer_alloc_return */
		comgen_gen86_jmp_symbol(self, COM_SYM_Ltest_pending_signals_after_single_buffer_alloc_return);

		/* >> .Ltest_pending_signals_after_single_buffers_is_in_band: */
		comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band);

		/* >> pushP_cfi %Pax */
		comgen_instr(self, gen86_pushP_r(&self->cg_txptr, GEN86_R_PAX));
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, SIZEOF_POINTER);

		/* >> call   chkuserprocmask */
		comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

		/* >> popP_cfi %Pax */
		comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PAX));
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

		/* >> jmp .Ltest_pending_signals_after_single_buffers_is_in_band_return */
		comgen_gen86_jmp_symbol(self, COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band_return);
		break;

	default:
		if (self->cg_inbuf_paramc != 0 || self->cg_inoutbuf_paramc != 0) {
			/* >> .Ltest_pending_signals_after_xbuf_alloc: */
			comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_xbuf_alloc);

			/* >> pushP_cfi %Pax */
			comgen_instr(self, gen86_pushP_r(&self->cg_txptr, GEN86_R_PAX));
			comgen_eh_movehere(self);
			comgen_eh_DW_CFA_adjust_cfa_offset(self, SIZEOF_POINTER);

			/* >> pushP_cfi %Pdx */
			comgen_instr(self, gen86_pushP_r(&self->cg_txptr, GEN86_R_PDX));
			comgen_eh_movehere(self);
			comgen_eh_DW_CFA_adjust_cfa_offset(self, SIZEOF_POINTER);

			/* >> call   chkuserprocmask */
			comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

			/* >> popP_cfi %Pdx */
			comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PDX));
			comgen_eh_movehere(self);
			comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

			/* >> popP_cfi %Pax */
			comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PAX));
			comgen_eh_movehere(self);
			comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

			/* >> jmp .Ltest_pending_signals_after_xbuf_alloc_return */
			comgen_gen86_jmp_symbol(self, COM_SYM_Ltest_pending_signals_after_xbuf_alloc_return);
		}

		/* >> .Ltest_pending_signals_after_all_buffers_are_in_band: */
		comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_all_buffers_are_in_band);

		/* >> call   chkuserprocmask */
		comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

		/* >> jmp    .Lall_buffers_are_in_band_preemption_reenabled: */
		comgen_gen86_jmp_symbol(self, COM_SYM_Lall_buffers_are_in_band_preemption_reenabled);
		break;
	}

}



/* Generate instructions:
 * >> #ifdef __x86_64__
 * >>     movq   $<cg_info.dl_error_return.scr_rax>, service_comdesc::scd_com::sc_retval::scr_rax(%R_service_com)
 * >> #else // __x86_64__
 * >> #if cg_info.dl_return == SERVICE_TYPE_386_R64
 * >>     movl   $<cg_info.dl_error_return.scr_eax>, service_comdesc::scd_com::sc_retval::scr_eax(%R_service_com)
 * >> #endif // cg_info.dl_return == SERVICE_TYPE_386_R64
 * >>     movl   $<cg_info.dl_error_return.scr_edx>, service_comdesc::scd_com::sc_retval::scr_edx(%R_service_com)
 * >> #endif // !__x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_set_error_return_value)(struct com_generator *__restrict self) {
#ifdef __x86_64__
	/* >> movq $<cg_info.dl_error_return.scr_rax>, service_comdesc::scd_com::sc_retval::scr_rax(%R_service_com) */
	comgen_instr(self, gen86_movq_imm_db(&self->cg_txptr, self->cg_info.dl_error_return.scr_rax,
	                                     offsetof(struct service_comdesc, scd_com.sc_retval.scr_rax),
	                                     GEN86_R_service_com));
#else /* __x86_64__ */
	if (self->cg_info.dl_return == SERVICE_TYPE_386_R64) {
		/* >> movl $<cg_info.dl_error_return.scr_eax>, service_comdesc::scd_com::sc_retval::scr_eax(%R_service_com) */
		comgen_instr(self, gen86_movl_imm_db(&self->cg_txptr, self->cg_info.dl_error_return.scr_edx,
		                                     offsetof(struct service_comdesc, scd_com.sc_retval.scr_edx),
		                                     GEN86_R_service_com));
	}
	/* >> movl $<cg_info.dl_error_return.scr_edx>, service_comdesc::scd_com::sc_retval::scr_edx(%R_service_com) */
	comgen_instr(self, gen86_movl_imm_db(&self->cg_txptr, self->cg_info.dl_error_return.scr_eax,
	                                     offsetof(struct service_comdesc, scd_com.sc_retval.scr_eax),
	                                     GEN86_R_service_com));
#endif /* !__x86_64__ */
}



#ifndef __x86_64__
#define USED_SET_ERRNO __set_errno_f
#ifndef ____set_errno_f_defined
#define ____set_errno_f_defined
__LIBC syscall_slong_t FCALL __set_errno_f(errno_t value);
#endif /* !____set_errno_f_defined */
#else /* !__x86_64__ */
#define USED_SET_ERRNO __set_errno
#ifndef ____set_errno_defined
#define ____set_errno_defined
__LIBC syscall_slong_t __set_errno(errno_t value);
#endif /* !____set_errno_defined */
#endif /* __x86_64__ */

/* Generate instructions:
 * >> .Lerr_com_abort_errno:
 * >>     negP   %Pax
 * >>     movP   %Pax, %R_fcall0P
 * >>     call   __set_errno_f
 * >>     movP   $<cg_service>,  %R_fcall0P
 * >>     movP   %R_service_com, %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movq   $<cg_info.dl_comid>, %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi $<cg_info.dl_comid>
 * >> #endif // !__x86_64__
 * >>     call   libservice_aux_com_abort
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -4
 * >> #endif // !__x86_64__
 * >>     testb  %al, %al                   # Check if command completed before it could be aborted
 * >>     jz     .Leh_free_service_com_end  # if (COMPLETED_BEFORE_ABORT) goto .Leh_free_service_com_end;
 * >>     // fallthru...
 * >>
 * >> .Lerr_free_service_com:
 * >>     SET_ERROR_RETURN_VALUE()
 * >>     jmp   .Leh_free_service_com_end
 * >>
 * >> .Lerr_pop_preemption:
 * >>     SET_ERROR_RETURN_VALUE()
 * >>     jmp   .Leh_preemption_pop_end */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_handle_errno_problems)(struct com_generator *__restrict self) {
	/* >> .Lerr_com_abort_errno: */
	comgen_defsym(self, COM_SYM_Lerr_com_abort_errno);

	/* >> negP   %Pax */
	comgen_instr(self, gen86_negP_r(&self->cg_txptr, GEN86_R_PAX));

	/* >> movP   %Pax, %R_fcall0P */
	comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_FCALL0P));

	/* >> call   __set_errno_f */
	comgen_instr(self, gen86_call(&self->cg_txptr, &USED_SET_ERRNO));

	/* >> movP   $<cg_service>,  %R_fcall0P */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));

	/* >> movP   %R_service_com, %R_fcall1P */
	comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_service_com, GEN86_R_FCALL1P));

#ifdef __x86_64__
	/* >> movq   $<cg_info.dl_comid>, %rdx */
	comgen_instr(self, gen86_movq_imm_r(&self->cg_txptr,
	                                    self->cg_info.dl_comid,
	                                    GEN86_R_RDX));
#else /* __x86_64__ */
	/* >> pushl_cfi $<cg_info.dl_comid> */
	comgen_instr(self, gen86_pushl_imm(&self->cg_txptr, self->cg_info.dl_comid));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

	/* >> call   libservice_aux_com_abort */
	comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_aux_com_abort));

#ifndef __x86_64__
	/* >> .cfi_adjust_cfa_offset -4 */
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -4);
#endif /* !__x86_64__ */

	/* >> testb  %al, %al # Check if command completed before it could be aborted */
	comgen_instr(self, gen86_testb_r_r(&self->cg_txptr, GEN86_R_AL, GEN86_R_AL));

	/* >> jz     .Leh_free_service_com_end  # if (COMPLETED_BEFORE_ABORT) goto .Leh_free_service_com_end; */
	comgen_gen86_jcc_symbol(self, GEN86_CC_Z, COM_SYM_Leh_free_service_com_end);

	/* >> .Lerr_free_service_com: */
	comgen_defsym(self, COM_SYM_Lerr_free_service_com);

	/* >> SET_ERROR_RETURN_VALUE() */
	comgen_set_error_return_value(self);

	/* >> jmp   .Leh_free_service_com_end */
	comgen_gen86_jmp_symbol(self, COM_SYM_Leh_free_service_com_end);

	/* >> .Lerr_pop_preemption: */
	comgen_defsym(self, COM_SYM_Lerr_pop_preemption);

	/* >> SET_ERROR_RETURN_VALUE() */
	comgen_set_error_return_value(self);

	/* >> jmp   .Leh_preemption_pop_end */
	comgen_gen86_jmp_symbol(self, COM_SYM_Leh_preemption_pop_end);
}



/* Generate instructions:
 * >> .Lremove_service_com_tryhard:
 * >>     leaP   service_comdesc::scd_com(%R_service_com), %Pdx
 * >>     movP   LOC_shm(%Psp),                            %Pax
 * >>     subP   service_shm_handle::ssh_shm(%Pax),        %Pdx # %Pdx = shm_offsetof_elem_com
 * >> // preemption_pushoff();
 * >>     movP   LOC_upm(%Psp), %Pax
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption (movabs via %Pdi on x86_64)
 * >> // atomic_lock_acquire(&s_shm_lock);
 * >> 1:  movl   $1, %eax
 * >>     xchgl  %eax, <cg_service->s_shm_lock.a_lock>         # (movabs via %Pdi on x86_64)
 * >>     testl  %eax, %eax
 * >>     jz     2f
 * >>     movP   $SYS_sched_yield, %Pax
 * >>     syscall                                              # Or `call __i386_syscall' on i386
 * >>     jmp    1b
 * >> 2:  movP   <cg_service->s_active_list>, %Pax                       # uintptr_t first = s_active_list;                     # (movabs via %Pdi on x86_64)
 * >> 3:  cmpP   %Pdx, %Pax                                              # 3: if (first == shm_offsetof_elem_com) {
 * >>     jne    4f                                                      #     ...
 * >>     movP   service_comdesc::scd_active_link(%R_service_com), %Pcx  #     %Pcx = next = elem->scd_active_link;
 * >>     lock   cmpxchgP %Pcx, <cg_service->s_active_list>              #     if (!ATOMIC_CMPXCH(s_active_list, first, next))  # (movabs via %Pdi on x86_64)
 * >>     jz     3b                                                      #     { first = s_active_list; goto 3b; }
 * >>     jmp    6f                                                      # } else
 * >> 4:  testP  %Pax, %Pax                                              # if (first != 0) {
 * >>     jz     6f                                                      #     ...
 * >> 5:  movP   <cg_service->s_shm>, %Pcx                               # 5:  %Pcx = s_shm;                          # (movabs via %Pdi on x86_64)
 * >>     movP   service_shm_handle::ssh_base(%Pcx), %Pcx                #     %Pcx = s_shm->ssh_base;
 * >>     addP   %Pax, %Pcx                                              #     %Pcx = &COMDESC_FROM_COM_OFFSET(first)->scd_com
 * >>     movP   <service_comdesc::scd_active_link-                      #     ...
 * >>             service_comdesc::scd_com>(%Pcx), %Pax                  #     %Pax = first = container_of(%Pcx, struct service_comdesc, scd_com)->scd_active_link
 * >>     testP  %Pax, %Pax                                              #     if (first != 0) {
 * >>     jz     6f                                                      #         ...
 * >>     cmpP   %Pdx, %Pax                                              #         if (first != shm_offsetof_elem_com)
 * >>     jne    5b                                                      #             goto 5b;
 * >>     movP   service_comdesc::scd_active_link(%R_service_com), %Pax  #         %Pax = elem->scd_active_link;
 * >>     movP   %Pax, <service_comdesc::scd_active_link-                #         ...
 * >>                   service_comdesc::scd_com>(%Pcx)                  #         container_of(%Pcx, struct service_comdesc, scd_com)->scd_active_link = %Pax;
 * >>                                                                    #     }
 * >>                                                                    # }
 * >> 6:
 * >> // atomic_lock_release(&s_shm_lock);
 * >>     movl   $0, <cg_service->s_shm_lock.a_lock>           # (movabs via %Pdi on x86_64)
 * >> // PREEMPTION_POP();
 * >>     movP   LOC_oldset(%Psp), %Pdx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pax  # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    8f
 * >> 7:  movP   service_comdesc::scd_com::sc_code(%R_service_com), %R_fcall0P   # Restore to expected value
 * >>     jmp    .Lremove_service_com_tryhard_return
 * >> 8:  call   chkuserprocmask
 * >>     jmp    7b */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_remove_service_com_tryhard)(struct com_generator *__restrict self) {
	byte_t *loc_1;
	int8_t *pdisp_2;
	byte_t *loc_3;
	int8_t *pdisp_4;
	byte_t *loc_5;
	int8_t *pdisp_6_1;
	int8_t *pdisp_6_2;
	int8_t *pdisp_6_3;
	byte_t *loc_7;
	int8_t *pdisp_8;

	/* >> .Lremove_service_com_tryhard: */
	comgen_defsym(self, COM_SYM_Lremove_service_com_tryhard);

	/* >> leaP   service_comdesc::scd_com(%R_service_com), %Pdx */
	gen86_leaP_db_r(&self->cg_txptr,
	                offsetof(struct service_comdesc, scd_com),
	                GEN86_R_service_com, GEN86_R_PDX);

	/* >> movP   LOC_shm(%Psp), %Pax */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_shm(self),
	                                   GEN86_R_PSP, GEN86_R_PAX));

	/* >> subP   service_shm_handle::ssh_shm(%Pax), %Pdx # %Pdx = shm_offsetof_elem_com */
	comgen_instr(self, gen86_subP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_PDX,
	                                    offsetof(struct service_shm_handle, ssh_shm),
	                                    GEN86_R_PAX));

	/* >> movP   LOC_upm(%Psp), %Pax */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_upm(self),
	                                   GEN86_R_PSP, GEN86_R_PAX));

	/* >> movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption (movabs via %Pdi on x86_64) */
#if defined(__x86_64__) && defined(__code_model_large__)
	if (!_gen86_fitsl((uintptr_t)&full_sigset)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &full_sigset, GEN86_R_PDI));
		comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDI,
		                                   offsetof(struct userprocmask, pm_sigmask),
		                                   GEN86_R_PAX));
	} else
#endif /* __x86_64__ && __code_model_large__ */
	{
		/* >> movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption */
		comgen_instr(self, gen86_movP_imm_db(&self->cg_txptr, (uintptr_t)&full_sigset,
		                                     offsetof(struct userprocmask, pm_sigmask),
		                                     GEN86_R_PAX));
	}

	/* >> 1: */
	loc_1 = self->cg_txptr;

	/* >> movl   $1, %eax */
	comgen_instr(self, gen86_movl_imm_r(&self->cg_txptr, 1, GEN86_R_EAX));

	/* >> xchgl  %eax, <cg_service->s_shm_lock.a_lock> # (movabs via %Pdi on x86_64) */
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_shm_lock.a_lock)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &self->cg_service->s_shm_lock.a_lock, GEN86_R_PDI));
		comgen_instr(self, gen86_xchgl_r_mod(&self->cg_txptr, gen86_modrm_b, GEN86_R_PAX, GEN86_R_PDI));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_xchgl_r_mod(&self->cg_txptr, gen86_modrm_d, GEN86_R_PAX,
		                                     (uintptr_t)&self->cg_service->s_shm_lock.a_lock));
	}

	/* >> testl  %eax, %eax */
	comgen_instr(self, gen86_testl_r_r(&self->cg_txptr, GEN86_R_EAX, GEN86_R_EAX));

	/* >> jz     2f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_Z, -1));
	pdisp_2 = (int8_t *)(self->cg_txptr - 1);

	/* >> movP   $SYS_sched_yield, %Pax */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, SYS_sched_yield, GEN86_R_PAX));

	/* >> syscall # Or `call __i386_syscall' on i386 */
	comgen_do_syscall_nx(self);

	/* >> jmp    1b */
	comgen_instr(self, gen86_jmp8(&self->cg_txptr, loc_1));

	/* >> 2: */
	*pdisp_2 += (int8_t)(uint8_t)(uintptr_t)(self->cg_txptr - (byte_t *)pdisp_2);

	/* >> movP   <cg_service->s_active_list>, %Pax # (movabs via %Pdi on x86_64) */
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_active_list)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &self->cg_service->s_active_list, GEN86_R_PDI));
		comgen_instr(self, gen86_movP_b_r(&self->cg_txptr, GEN86_R_PDI, GEN86_R_PAX));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_movP_d_r(&self->cg_txptr,
		                                  (uintptr_t)&self->cg_service->s_active_list,
		                                  GEN86_R_PAX));
	}

	/* >> 3: */
	loc_3 = self->cg_txptr;

	/* >> cmpP   %Pdx, %Pax */
	comgen_instr(self, gen86_cmpP_r_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_PAX));

	/* >> jne    4f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NE, -1));
	pdisp_4 = (int8_t *)(self->cg_txptr - 1);

	/* >> movP   service_comdesc::scd_active_link(%R_service_com), %Pcx */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_active_link),
	                                   GEN86_R_service_com, GEN86_R_PCX));

	/* >> lock   cmpxchgP %Pcx, <cg_service->s_active_list> # (movabs via %Pdi on x86_64) */
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_active_list)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &self->cg_service->s_active_list, GEN86_R_PDI));
		comgen_instr(self, gen86_lock(&self->cg_txptr));
		comgen_instr(self, gen86_cmpxchgP_r_mod(&self->cg_txptr, gen86_modrm_b, GEN86_R_PCX, GEN86_R_PDI));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_lock(&self->cg_txptr));
		comgen_instr(self, gen86_cmpxchgP_r_mod(&self->cg_txptr, gen86_modrm_d, GEN86_R_PCX,
		                                        (uintptr_t)&self->cg_service->s_active_list));
	}

	/* >> jz     3b */
	comgen_instr(self, gen86_jcc8(&self->cg_txptr, GEN86_CC_Z, loc_3));

	/* >> jmp    6f */
	comgen_instr(self, gen86_jmp8_offset(&self->cg_txptr, -1));
	pdisp_6_1 = (int8_t *)(self->cg_txptr - 1);

	/* >> 4: */
	*pdisp_4 += (int8_t)(uint8_t)(uintptr_t)(self->cg_txptr - (byte_t *)pdisp_4);

	/* >> testP  %Pax, %Pax */
	comgen_instr(self, gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX));

	/* >> jz     6f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_Z, -1));
	pdisp_6_2 = (int8_t *)(self->cg_txptr - 1);

	/* >> 5: */
	loc_5 = self->cg_txptr;

	/* >> movP   <cg_service->s_shm>, %Pcx # (movabs via %Pdi on x86_64) */
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_shm)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &self->cg_service->s_shm, GEN86_R_PDI));
		comgen_instr(self, gen86_movP_b_r(&self->cg_txptr, GEN86_R_PDI, GEN86_R_PCX));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_movP_d_r(&self->cg_txptr,
		                                  (uintptr_t)&self->cg_service->s_shm,
		                                  GEN86_R_PCX));
	}

	/* >> movP   service_shm_handle::ssh_base(%Pcx), %Pcx */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_shm_handle, ssh_base),
	                                   GEN86_R_PCX, GEN86_R_PCX));

	/* >> addP   %Pax, %Pcx */
	comgen_instr(self, gen86_addP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PCX));

	/* >> movP   <service_comdesc::scd_active_link-service_comdesc::scd_com>(%Pcx), %Pax */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   (ptrdiff_t)offsetof(struct service_comdesc, scd_active_link) -
	                                   (ptrdiff_t)offsetof(struct service_comdesc, scd_com),
	                                   GEN86_R_PCX, GEN86_R_PCX));

	/* >> testP  %Pax, %Pax */
	comgen_instr(self, gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX));

	/* >> jz     6f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_Z, -1));
	pdisp_6_3 = (int8_t *)(self->cg_txptr - 1);

	/* >> cmpP   %Pdx, %Pax */
	comgen_instr(self, gen86_cmpP_r_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_PAX));

	/* >> jne    5b */
	comgen_instr(self, gen86_jcc8(&self->cg_txptr, GEN86_CC_NE, loc_5));

	/* >> movP   service_comdesc::scd_active_link(%R_service_com), %Pax */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_active_link),
	                                   GEN86_R_service_com, GEN86_R_PAX));

	/* >> movP   %Pax, <service_comdesc::scd_active_link-service_comdesc::scd_com>(%Pcx) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                                   (ptrdiff_t)offsetof(struct service_comdesc, scd_active_link) -
	                                   (ptrdiff_t)offsetof(struct service_comdesc, scd_com),
	                                   GEN86_R_PCX));

	/* >> 6: */
	*pdisp_6_1 += (int8_t)(uint8_t)(uintptr_t)(self->cg_txptr - (byte_t *)pdisp_6_1);
	*pdisp_6_2 += (int8_t)(uint8_t)(uintptr_t)(self->cg_txptr - (byte_t *)pdisp_6_2);
	*pdisp_6_3 += (int8_t)(uint8_t)(uintptr_t)(self->cg_txptr - (byte_t *)pdisp_6_3);

	/* >> movl   $0, <cg_service->s_shm_lock.a_lock> # (movabs via %Pdi on x86_64) */
#ifdef __x86_64__
	if (!_gen86_fitsl((uintptr_t)&self->cg_service->s_shm_lock.a_lock)) {
		comgen_instr(self, gen86_movabs_imm_r(&self->cg_txptr, &self->cg_service->s_shm_lock.a_lock, GEN86_R_PDI));
		comgen_instr(self, gen86_movl_imm_b(&self->cg_txptr, 0, GEN86_R_PDI));
	} else
#endif /* __x86_64__ */
	{
		comgen_instr(self, gen86_movl_imm_d(&self->cg_txptr, 0,
		                                    (uintptr_t)&self->cg_service->s_shm_lock.a_lock));
	}

	/* >> movP   LOC_oldset(%Psp), %Pdx # `sigset_t *oldset' */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_oldset(self),
	                                   GEN86_R_PSP, GEN86_R_PDX));

	/* >> movP   LOC_upm(%Psp), %Pax # `struct userprocmask *upm' */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_upm(self),
	                                   GEN86_R_PSP, GEN86_R_PAX));

	/* >> movP   %Pdx, userprocmask::pm_sigmask(%Pax) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                                   offsetof(struct userprocmask, pm_sigmask),
	                                   GEN86_R_PAX));

	/* >> test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax) */
	comgen_instr(self, gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db,
	                                       USERPROCMASK_FLAG_HASPENDING,
	                                       offsetof(struct userprocmask, pm_flags),
	                                       GEN86_R_PAX));

	/* >> jnz    8f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NZ, -1));
	pdisp_8 = (int8_t *)(self->cg_txptr - 1);

	/* >> 7: */
	loc_7 = self->cg_txptr;

	/* >> movP   service_comdesc::scd_com::sc_code(%R_service_com), %R_fcall0P # Restore to expected value */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   offsetof(struct service_comdesc, scd_com.sc_code),
	                                   GEN86_R_service_com, GEN86_R_FCALL0P));

	/* >> jmp    .Lremove_service_com_tryhard_return */
	comgen_gen86_jmp_symbol(self, COM_SYM_Lremove_service_com_tryhard_return);

	/* >> 8: */
	*pdisp_8 += (int8_t)(uint8_t)(uintptr_t)
	            (self->cg_txptr - (byte_t *)pdisp_8);

	/* >> call   chkuserprocmask */
	comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

	/* >> jmp    7b */
	comgen_instr(self, gen86_jmp8(&self->cg_txptr, loc_7));
}



/* Generate   instructions:
 * >> .Lcom_special_return:
 * >>     cmpP   $SERVICE_COM_ST_ECHO, %R_fcall0P
 * >>     jbe    1f
 * >>     # Normal return with non-zero errno
 * >>     negP   %R_fcall0P
 * >>     call   __set_errno_f
 * >>     jmp    .Lcom_special_return_resume
 * >> 1:  movP   %R_service_com, %R_fcall1P
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_aux_load_except_as_errno
 * >> #if cg_buf_paramc != 0
 * >>     jmp    .Leh_free_xbuf_end
 * >> #else // cg_buf_paramc != 0
 * >>     jmp    .Leh_free_service_com_end
 * >> #endif // cg_buf_paramc == 0
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >> #ifdef __x86_64__
 * >>     movP   <cg_cfa_offset-P>(%Psp), %R_sysvabi2P
 * >>     call   libservice_aux_load_except_as_error
 * >> #else // __x86_64__
 * >>     pushP_cfi <cg_cfa_offset-P>(%Psp)
 * >>     call   libservice_aux_load_except_as_error
 * >>     .cfi_adjust_cfa_offset -4
 * >> #endif // !__x86_64__
 * >> #if cg_buf_paramc != 0
 * >>     jmp    .Leh_free_xbuf_entry
 * >> #else // cg_buf_paramc != 0
 * >>     jmp    .Leh_free_service_com_entry
 * >> #endif // cg_buf_paramc == 0
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_custom_status_return)(struct com_generator *__restrict self) {
	int8_t *pdisp_1;

	/* >> .Lcom_special_return: */
	comgen_defsym(self, COM_SYM_Lcom_special_return);

	/* >> cmpP   $SERVICE_COM_ST_ECHO, %R_fcall0P */
	comgen_instr(self, gen86_cmpP_imm_r(&self->cg_txptr,
	                                    SERVICE_COM_ST_ECHO,
	                                    GEN86_R_FCALL0P));

	/* >> jbe    1f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_BE, -1));
	pdisp_1 = (int8_t *)(self->cg_txptr - 1);

	/* Normal return with non-zero errno */
	/* >> negP   %R_fcall0P */
	comgen_instr(self, gen86_negP_r(&self->cg_txptr, GEN86_R_FCALL0P));

	/* >> call   __set_errno_f */
	comgen_instr(self, gen86_call(&self->cg_txptr, &USED_SET_ERRNO));

	/* >> jmp    .Lcom_special_return_resume */
	comgen_gen86_jmp_symbol(self, COM_SYM_Lcom_special_return_resume);

	/* >> 1: */
	*pdisp_1 += (int8_t)(uint8_t)(uintptr_t)
	            (self->cg_txptr - (byte_t *)pdisp_1);

	/* >> movP   %R_service_com, %R_fcall1P */
	comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_service_com, GEN86_R_FCALL1P));

	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		unsigned int return_symbol;
		/* >> call   libservice_aux_load_except_as_errno */
		comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_aux_load_except_as_errno));

		if (self->cg_buf_paramc != 0) {
			/* >> jmp    .Leh_free_xbuf_end */
			return_symbol = COM_SYM_Leh_free_xbuf_end;
		} else {
			/* >> jmp    .Leh_free_service_com_end */
			return_symbol = COM_SYM_Leh_free_service_com_end;
		}
		comgen_gen86_jmp_symbol(self, return_symbol);
	} else {
		unsigned int return_symbol;

#ifdef __x86_64__
		/* >> movP   <cg_cfa_offset-P>(%Psp), %R_fcall1P */
		comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
		                                   self->cg_cfa_offset - SIZEOF_POINTER,
		                                   GEN86_R_PSP, GEN86_R_RDX)); /* %rdx <=> %R_sysvabi2P */
#else  /* __x86_64__ */
		/* >> pushP_cfi <cg_cfa_offset-P>(%Psp) */
		comgen_instr(self, gen86_pushP_mod(&self->cg_txptr, gen86_modrm_db,
		                                   self->cg_cfa_offset - SIZEOF_POINTER,
		                                   GEN86_R_PSP));
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

		/* >> call   libservice_aux_load_except_as_errno */
		comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_aux_load_except_as_error));

#ifndef __x86_64__
		/* >> .cfi_adjust_cfa_offset -4 */
		comgen_eh_movehere(self);
		comgen_eh_DW_CFA_adjust_cfa_offset(self, -4);
#endif /* !__x86_64__ */

		if (self->cg_buf_paramc != 0) {
			/* >> jmp    .Leh_free_xbuf_entry */
			return_symbol = COM_SYM_Leh_free_xbuf_entry;
		} else {
			/* >> jmp    .Leh_free_service_com_entry */
			return_symbol = COM_SYM_Leh_free_service_com_entry;
		}
		comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NZ, -1));
		comgen_reloc(self, self->cg_txptr - 1, COM_R_PCREL8, return_symbol);
	}
}



/* Generate     instructions:
 * >> .Leh_com_waitfor_entry:
 * >>     movP   $<cg_service>,  %R_fcall0P
 * >>     movP   %R_service_com, %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movq   $<cg_info.dl_comid>, %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi $<cg_info.dl_comid>
 * >> #endif // !__x86_64__
 * >>     call   libservice_aux_com_abort
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -4
 * >> #endif // !__x86_64__
 * >>     testb  %al, %al   # Check if command completed before it could be aborted
 * >>     jnz    1f         # if (ABORTED) goto 1f;
 * >>     call   libservice_aux_com_discard_nonrt_exception # Try to clear non-RT exceptions
 * >>     testb  %al, %al
 * >>     jnz    .Leh_com_waitfor_end
 * >> 1: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_com_waitfor_entry)(struct com_generator *__restrict self) {
	int8_t *pdisp_1;

	/* >> .Leh_com_waitfor_entry: */
	comgen_defsym(self, COM_SYM_Leh_com_waitfor_entry);

	/* >> movP   $<cg_service>,  %R_fcall0P */
	comgen_instr(self, gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P));

	/* >> movP   %R_service_com, %R_fcall1P */
	comgen_instr(self, gen86_movP_r_r(&self->cg_txptr, GEN86_R_service_com, GEN86_R_FCALL1P));

#ifdef __x86_64__
	/* >> movq   $<cg_info.dl_comid>, %rdx */
	comgen_instr(self, gen86_movq_imm_r(&self->cg_txptr,
	                                    self->cg_info.dl_comid,
	                                    GEN86_R_RDX));
#else /* __x86_64__ */
	/* >> pushl_cfi $<cg_info.dl_comid> */
	comgen_instr(self, gen86_pushl_imm(&self->cg_txptr, self->cg_info.dl_comid));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

	/* >> call   libservice_aux_com_abort */
	comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_aux_com_abort));

#ifndef __x86_64__
	/* >> .cfi_adjust_cfa_offset -4 */
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -4);
#endif /* !__x86_64__ */

	/* >> testb  %al, %al   # Check if command completed before it could be aborted */
	comgen_instr(self, gen86_testb_r_r(&self->cg_txptr, GEN86_R_AL, GEN86_R_AL));

	/* >> jnz    1f         # if (ABORTED) goto 1f; */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NZ, -1));
	pdisp_1 = (int8_t *)(self->cg_txptr - 1);

	/* >> call   libservice_aux_com_discard_nonrt_exception # Try to clear non-RT exceptions */
	comgen_instr(self, gen86_call(&self->cg_txptr, &libservice_aux_com_discard_nonrt_exception));

	/* >> testb  %al, %al */
	comgen_instr(self, gen86_testb_r_r(&self->cg_txptr, GEN86_R_AL, GEN86_R_AL));

	/* >> jnz    .Leh_com_waitfor_end */
	comgen_gen86_jcc_symbol(self, GEN86_CC_NZ, COM_SYM_Leh_com_waitfor_end);

	/* >> 1: */
	*pdisp_1 += (int8_t)(uint8_t)(uintptr_t)
	            (self->cg_txptr - (byte_t *)pdisp_1);
}



/* Generate    instructions:
 * >> #if cg_buf_paramc != 0
 * >> .Leh_free_xbuf_entry:
 * >>     movP   LOC_bufpar_ptr(%Psp), %Pdx
 * >>     testP  %Pdx, %Pdx
 * >>     jz     1f
 * >>     subP   $<sizeof(size_t)>, %Pdx
 * >> #ifdef __x86_64__
 * >>     movP   0(%Pdx), %Pcx
 * >> #else // __x86_64__
 * >>     pushP_cfi 0(%Pdx)
 * >>     pushP_cfi %Pdx
 * >> #endif // !__x86_64__
 * >>     movP   LOC_bufpar_shm(%Psp), %R_fcall1P
 * >>     <comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr>
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__
 * >> 1:
 * >> #endif // cg_buf_paramc != 0 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_free_xbuf_entry)(struct com_generator *__restrict self) {
	int8_t *pdisp_1;
	if (self->cg_buf_paramc == 0)
		return;

	/* >> .Leh_free_xbuf_entry: */
	comgen_defsym(self, COM_SYM_Leh_free_xbuf_entry);

	/* >> movP   LOC_bufpar_ptr(%Psp), %Pdx */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_bufpar_ptr(self),
	                                   GEN86_R_PSP, GEN86_R_PDX));

	/* >> testP  %Pdx, %Pdx */
	comgen_instr(self, gen86_testP_r_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_PDX));

	/* >> jz     1f */
	comgen_instr(self, gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_Z, -1));
	pdisp_1 = (int8_t *)(self->cg_txptr - 1);

	/* >> subP   $<sizeof(size_t)>, %Pdx */
	comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, sizeof(size_t), GEN86_R_PDX));

#ifdef __x86_64__
	/* >> movP   0(%Pdx), %Pcx */
	comgen_instr(self, gen86_movP_b_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_PCX));
#else /* __x86_64__ */
	/* >> pushl_cfi 0(%Pdx) */
	comgen_instr(self, gen86_pushl_mod(&self->cg_txptr, gen86_modrm_b, GEN86_R_PDX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);

	/* >> pushl_cfi %Pdx */
	comgen_instr(self, gen86_pushl_r(&self->cg_txptr, GEN86_R_PDX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

	/* >> movP   LOC_bufpar_shm(%Psp), %R_fcall1P */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_bufpar_shm(self),
	                                   GEN86_R_PSP, GEN86_R_FCALL1P));

	/* >> <comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr> */
	comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr(self);

	/* >> 1: */
	*pdisp_1 += (int8_t)(uint8_t)(uintptr_t)
	            (self->cg_txptr - (byte_t *)pdisp_1);
}



/* Generate instructions:
 * >> .Leh_free_service_com_entry:
 * >>     subP   $<sizeof(size_t)>, %R_service_com
 * >> #ifdef __x86_64__
 * >>     movq   0(%R_service_com), %rcx
 * >>     movq   %R_service_com,    %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi 0(%R_service_com)
 * >>     pushl_cfi %R_service_com
 * >> #endif // !__x86_64__
 * >>     movP   LOC_shm(%Psp), %R_fcall1P
 * >>     <comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr> */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_free_service_com_entry)(struct com_generator *__restrict self) {
	/* >> .Leh_free_service_com_entry: */
	comgen_defsym(self, COM_SYM_Leh_free_service_com_entry);

	/* >> subP   $<sizeof(size_t)>, %R_service_com */
	comgen_instr(self, gen86_subP_imm_r(&self->cg_txptr, sizeof(size_t),
	                                    GEN86_R_service_com));

#ifdef __x86_64__
	/* >> movq   0(%R_service_com), %rcx */
	comgen_instr(self, gen86_movq_b_r(&self->cg_txptr, GEN86_R_service_com, GEN86_R_RCX));

	/* >> movq   %R_service_com,    %rdx */
	comgen_instr(self, gen86_movq_r_r(&self->cg_txptr, GEN86_R_service_com, GEN86_R_RDX));
#else /* __x86_64__ */
	/* >> pushl_cfi 0(%R_service_com) */
	comgen_instr(self, gen86_pushl_mod(&self->cg_txptr, gen86_modrm_b, GEN86_R_service_com));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);

	/* >> pushl_cfi %R_service_com */
	comgen_instr(self, gen86_pushl_r(&self->cg_txptr, GEN86_R_service_com));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

	/* >> movP   LOC_shm(%Psp), %R_fcall1P */
	comgen_instr(self, gen86_movP_db_r(&self->cg_txptr,
	                                   comgen_spoffsetof_LOC_shm(self),
	                                   GEN86_R_PSP, GEN86_R_FCALL1P));

	/* >> <comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr> */
	comgen_disable_preemption_and_call_libservice_shmbuf_freeat_nopr(self);
}



/* Generate instructions:
 * >> .Leh_preemption_pop_entry:
 * >>     popP_cfi %Pdx              # `sigset_t *oldset'
 * >>     popP_cfi %Pax              # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     call   chkuserprocmask
 * >> #ifdef __x86_64__
 * >>     xorq   %rdi, %rdi
 * >> #else // __x86_64__
 * >>     pushl_cfi $0
 * >> #endif // !__x86_64__
 * >>     call   _Unwind_Resume
 * >>     nop */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_preemption_pop_entry)(struct com_generator *__restrict self) {
	/* >> .Leh_preemption_pop_entry: */
	comgen_defsym(self, COM_SYM_Leh_preemption_pop_entry);

	/* >> popP_cfi %Pdx              # `sigset_t *oldset' */
	comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PDX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

	/* >> popP_cfi %Pax              # `struct userprocmask *upm' */
	comgen_instr(self, gen86_popP_r(&self->cg_txptr, GEN86_R_PAX));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, -SIZEOF_POINTER);

	/* >> movP   %Pdx, userprocmask::pm_sigmask(%Pax) */
	comgen_instr(self, gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                                   offsetof(struct userprocmask, pm_sigmask),
	                                   GEN86_R_PAX));

	/* >> call   chkuserprocmask */
	comgen_instr(self, gen86_call(&self->cg_txptr, &chkuserprocmask));

#ifdef __x86_64__
	/* >> xorq   %rdi, %rdi */
	comgen_instr(self, gen86_xorq_r_r(&self->cg_txptr, GEN86_R_RDI, GEN86_R_RDI));
#else /* __x86_64__ */

	/* >> pushl_cfi $0 */
	comgen_instr(self, gen86_pushl_imm(&self->cg_txptr, 0));
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, 4);
#endif /* !__x86_64__ */

	/* >> call   _Unwind_Resume */
	comgen_instr(self, gen86_call(&self->cg_txptr, &_Unwind_Resume));

	/* >> nop */
	comgen_instr(self, gen86_nop(&self->cg_txptr));
}


/* Generate the .gcc_except_table and return a pointer to its base address. */
PRIVATE NONNULL((1)) uint8_t *
NOTHROW(FCALL comgen_gcc_except_table)(struct com_generator *__restrict self) {
	uint8_t *result;
	uintptr_t sizeof_handlers;

	result = self->cg_txptr;
	if unlikely(!comgen_txok1(self))
		goto done;

	/* The following configuration makes offsets function-relative, using 2-byte offsets. */
	_gen86_putb(&self->cg_txptr, DW_EH_PE_omit);   /* gcc_lsda::gl_landing_enc */
	_gen86_putb(&self->cg_txptr, DW_EH_PE_omit);   /* gcc_lsda::gl_typetab_enc */
	_gen86_putb(&self->cg_txptr, DW_EH_PE_udata2); /* gcc_lsda::gl_callsite_enc */

	/* 8 == 4*2  // 2 because of `DW_EH_PE_udata2'; 4 because # of fields
	 *           // in `gcc_lsda_callsite', s.a.: `DEFINE_HANDLER' below. */
	sizeof_handlers = 3 * 8;
	if (self->cg_buf_paramc != 0)
		sizeof_handlers += 8; /* +1 additional handler */
	self->cg_txptr = _eh_putuleb128(self->cg_txptr, sizeof_handlers); /* gcc_lsda::gl_callsite_siz */
	if unlikely(!comgen_txav(self, sizeof_handlers)) {
		self->cg_txptr = self->cg_txend;
		goto done;
	}

#define DEFINE_HANDLER(name)                                                               \
	(ASSERT_SYMBOL_DEFINED(self, name##begin),                                             \
	 ASSERT_SYMBOL_DEFINED(self, name##end),                                               \
	 ASSERT_SYMBOL_DEFINED(self, name##entry),                                             \
	 /* gcs_start   */ _gen86_putw(&self->cg_txptr, comgen_symreladdr(self, name##begin)), \
	 /* gcs_size    */ _gen86_putw(&self->cg_txptr, comgen_symreladdr(self, name##end)),   \
	 /* gcs_handler */ _gen86_putw(&self->cg_txptr, comgen_symreladdr(self, name##entry)), \
	 /* gcs_action  */ _gen86_putw(&self->cg_txptr, 1))

	/* Define exception handlers... */
	DEFINE_HANDLER(COM_SYM_Leh_com_waitfor_);
	if (self->cg_buf_paramc != 0)
		DEFINE_HANDLER(COM_SYM_Leh_free_xbuf_);
	DEFINE_HANDLER(COM_SYM_Leh_free_service_com_);
	DEFINE_HANDLER(COM_SYM_Leh_preemption_pop_);
#undef DEFINE_HANDLER

done:
	return result;
}












/************************************************************************/
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_apply_relocations)(struct com_generator *__restrict self) {
	uint8_t i;
	for (i = 0; i < self->cg_nrelocs; ++i) {
		byte_t *addr;
		uintptr_t value;
		value = (uintptr_t)(addr = self->cg_txbas);
		addr += self->cg_relocs[i].cr_offset;
		value += self->cg_symbols[self->cg_relocs[i].cr_symbol];
		assertf(self->cg_symbols[self->cg_relocs[i].cr_symbol] != 0,
		        "Undefined symbol: %u", self->cg_relocs[i].cr_symbol);
		switch (self->cg_relocs[i].cr_type) {

		case COM_R_PCREL32:
			/* [*(s32 *)ADDR += (32)(u32)(VALUE - (uintptr_t)ADDR)] PC-relative, 32-bit */
			*(s32 *)addr += (s32)(u32)(value - (uintptr_t)addr);
			break;

		case COM_R_PCREL8:
			/* [*(s8 *)ADDR += (s8)(u8)(VALUE - (uintptr_t)ADDR)] PC-relative, 8-bit */
			*(s8 *)addr += (s8)(u8)(value - (uintptr_t)addr);
			break;

		case COM_R_ABSPTR:
			/* [*(uintptr_t *)ADDR += VALUE] Absolute, pointer-sized */
			*(uintptr_t *)addr += value;
			break;

		default: __builtin_unreachable();
		}
	}
}
/************************************************************************/



/* Initializer pattern for com function .eh_frame data. */
PRIVATE struct com_eh_frame const eh_frame_pattern = {
	.cef_cie_size = 0, /* Should be `offsetof(struct com_eh_frame, cef_fde_size)', but only  set
	                    * as such on compilation success. Until that point, this being `0'  will
	                    * tell other pieces of code which may  already be making use of the  eh-
	                    * frame data buffer we're using, that the section ends here, rather than
	                    * containing the (not fully initialized) unwind descriptor found  below. */
	.cef_cie_id        = 0,
	.cef_cie_version   = 1,
	.cef_cie_augstr    = { 'z', 'L', 'P' },
	.cef_cie_codealign = 1,
#ifdef __x86_64__
	.cef_cie_dataalign = 0x78,
	.cef_cie_retreg    = CFI_X86_64_UNWIND_REGISTER_RIP,
	.cef_cie_auglen    = 9,
#else /* __x86_64__ */
	.cef_cie_dataalign = 0x7c,
	.cef_cie_retreg    = CFI_386_UNWIND_REGISTER_EIP,
	.cef_cie_auglen    = 5,
#endif /* !__x86_64__ */
	.cef_cie_lsdaenc   = DW_EH_PE_absptr,
	.cef_cie_persoenc  = DW_EH_PE_absptr,
	.cef_cie_persoptr  = NULL, /* Dynamically filled */
	/* CIE init text would go here... */

	/* FDE */
	.cef_fde_size      = 0, /* Dynamically filled */
	.cef_fde_cie_off   = offsetof(struct com_eh_frame, cef_fde_cie_off),
	.cef_fde_funbase   = NULL, /* Dynamically filled */
	.cef_fde_funsize   = 0,    /* Dynamically filled */
	.cef_fde_auglen    = SIZEOF_POINTER,
	.cef_fde_lsda      = NULL, /* Dynamically filled */
};


/* Do the initial setup of .eh_frame */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL comgen_eh_frame_setup)(struct com_generator *__restrict self) {
	/* Fill in the .eh_frame description header. */
	struct com_eh_frame *eh_hdr = (struct com_eh_frame *)self->cg_ehbas;
	memcpy(eh_hdr, &eh_frame_pattern, offsetof(struct com_eh_frame, cef_fde_text));
	self->cg_ehptr = eh_hdr->cef_fde_text;
}

#define comgen_eh_frame(self)           ((struct com_eh_frame *)(self)->cg_ehbas)
#define comgen_eh_frame_startproc(self) UNALIGNED_SET((uintptr_t *)&comgen_eh_frame(self)->cef_fde_funbase, (uintptr_t)(self)->cg_txptr)
#define comgen_eh_frame_endproc(self)   UNALIGNED_SET(&comgen_eh_frame(self)->cef_fde_funsize, (size_t)((self)->cg_txptr - (self)->cg_txbas))
#define comgen_eh_set_lsda(self, ptr)   UNALIGNED_SET((uintptr_t *)&comgen_eh_frame(self)->cef_fde_lsda, (uintptr_t)(ptr))

__LIBC void __gcc_personality_v0(void);

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL comgen_eh_frame_finish)(struct com_generator *__restrict self) {
	/* Finalize the .eh_frame description header. */
	struct com_eh_frame *eh_hdr = (struct com_eh_frame *)self->cg_ehbas;
	UNALIGNED_SET((uintptr_t *)&eh_hdr->cef_cie_persoptr, (uintptr_t)(void *)&__gcc_personality_v0);
	UNALIGNED_SET(&eh_hdr->cef_fde_size, (uint32_t)(size_t)(self->cg_ehptr - (byte_t *)&eh_hdr->cef_fde_size));

	/* After the following write has been done, other threads may _immediately_
	 * start to parse our newly generated unwind data, _as_ _well_ _as_  access
	 * the generated wrapper function.
	 * In a sense, making this write is a point-of-no-return */
	COMPILER_BARRIER();
	UNALIGNED_SET(&eh_hdr->cef_cie_size, offsetof(struct com_eh_frame, cef_fde_size));
	COMPILER_BARRIER();
}

/* Compile  the  com generator  wrapper function.  Upon return,
 * the caller must check the status using `comgen_compile_st_*'
 * Only with both *_moretx and *_moreeh return `false' may  the
 * compile operation be  considered successful. Otherwise,  the
 * respective need-more-memory condition should be handled.
 *
 * @return: true:  Compilation succeed (you may assume `comgen_compile_isok(self) == true')
 * @return: false: Compilation failed due to lack of .text- or  .eh_frame-memory
 *                 Check which is the case with `comgen_compile_st_moretx()' and
 *                 `comgen_compile_st_moreeh()'
 *
 * NOTE: Upon  success, the  used EH  buffer size  will indicate 4
 *       bytes more than should actually be accounted as belonging
 *       to the associated function. These bytes may not be freed,
 *       but should be overwritten  (iow: passed as `cg_ehbas'  in
 *       some  future compilation operation),  as they represent a
 *       sentinel marker in unwind debug data.
 *       The implementation of  this function takes  care to  maintain
 *       the  sentinel until the  point in time when  eh data has been
 *       finalized, at which point other threads may immediately begin
 *       parsing generated debug data.
 *       Until  that point,  the sentinel  must be  kept to prevent
 *       other threads from accessing incomplete debug information! */
INTERN NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL comgen_compile)(struct com_generator *__restrict self) {
#ifdef __x86_64__
	uint8_t GEN86_R_shmbase;
#endif /* __x86_64__ */
	int16_t normal_cfa_offset; /* "normal" CFA offset (as set following the first ".cfi_remember_state") */

	/* Assert that the given buffer meets the minimum size requirements. */
	assert((size_t)(self->cg_txend - self->cg_txbas) >= COM_GENERATOR_INITIAL_TX_BUFSIZ);
	assert((size_t)(self->cg_ehend - self->cg_ehbas) >= COM_GENERATOR_INITIAL_EH_BUFSIZ);
#ifndef NDEBUG
	/* So that we can detect uninitialized symbols in assertions. */
	bzero(self->cg_symbols, sizeof(self->cg_symbols));
#endif /* !NDEBUG */

	self->cg_txptr      = self->cg_txbas;
	self->cg_nrelocs    = 0;
	self->cg_CFA_loc    = self->cg_txptr;
	comgen_eh_frame_setup(self);
	comgen_eh_frame_startproc(self);
	comgen_eh_DW_CFA_def_cfa(self, CFI_X86_UNWIND_REGISTER_PSP, SIZEOF_POINTER);

	/* Generate the unconditional push instructions at the start of the wrapper. */
	comgen_push_registers_on_entry(self);

	/* Allocate space for local variables */
	comgen_allocate_stack_space(self);

	/* Disable preemption */
	comgen_disable_preemption(self);
	normal_cfa_offset = self->cg_cfa_offset;

	/* Allocate the com buffer */
	comgen_allocate_com_buffer(self);

	/* Serialize buffer arguments */
	comgen_serialize_buffer_arguments(self);

	/* Serialize integer arguments */
	comgen_serialize_integer_arguments(self);

	/* Set the function code within the com descriptor */
	/* >> movP   $<cg_info.dl_comid>, service_comdesc::scd_com::sc_code(%R_service_com) */
	if unlikely(!comgen_txok1(self))
		goto fail;
	gen86_movP_imm_db(&self->cg_txptr, self->cg_info.dl_comid,
	                  offsetof(struct service_comdesc, scd_com.sc_code),
	                  GEN86_R_service_com);

#ifdef __x86_64__
	/* On i386, `%R_shmbase' is '%Pbx'. On x86_64, `%R_shmbase' is:
	 * (cg_inline_buf_paramc && COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS) ? '%r8' : '%Pdi' */
	GEN86_R_shmbase = GEN86_R_PDI;
	if (self->cg_inline_buf_paramc != 0 &&
	    (self->cg_features & COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS))
		GEN86_R_shmbase = GEN86_R_R8;
#endif /* __x86_64__ */

	/* Calculate the SHM-relative address of `service_comdesc' */
	/* >> leaP   service_comdesc::scd_com(%R_service_com), %Pdx */
	if unlikely(!comgen_txok1(self))
		goto fail;
	gen86_leaP_db_r(&self->cg_txptr,
	                offsetof(struct service_comdesc, scd_com),
	                GEN86_R_service_com, GEN86_R_PDX);

	/* >> movP   LOC_shm(%Psp), %R_shmbase */
	if unlikely(!comgen_txok1(self))
		goto fail;
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_shm(self),
	                GEN86_R_PSP, GEN86_R_shmbase);

	/* >> movP   service_shm_handle::ssh_shm(%R_shmbase), %R_shmbase */
	if unlikely(!comgen_txok1(self))
		goto fail;
	gen86_movP_db_r(&self->cg_txptr,
	                offsetof(struct service_shm_handle, ssh_shm),
	                GEN86_R_shmbase, GEN86_R_shmbase);

	/* >> subP   %R_shmbase, %Pdx */
	if unlikely(!comgen_txok1(self))
		goto fail;
	gen86_subP_r_r(&self->cg_txptr, GEN86_R_shmbase, GEN86_R_PDX);

	/* Serialize fixed-length inline buffers */
	comgen_serialize_inline_buffers(self);
	if unlikely(!comgen_txok1(self))
		goto fail;

	/* Add the service_comdesc to the list of active commands `cg_service->s_active_list' */
	comgen_add_to_active(self);

	/* Insert the command into the server's pending list */
#ifdef __x86_64__
	comgen_schedule_command(self, GEN86_R_shmbase);
#else /* __x86_64__ */
	comgen_schedule_command(self);
#endif /* !__x86_64__ */
	if unlikely(!comgen_txok1(self))
		goto fail;

	/* Tell the server that a new command has become available */
#ifdef __x86_64__
	comgen_wake_server(self, GEN86_R_shmbase);
#else /* __x86_64__ */
	comgen_wake_server(self);
#endif /* !__x86_64__ */

	/* Wait for the command to complete */
	comgen_waitfor_command(self);
	if unlikely(!comgen_txok1(self))
		goto fail;
	if unlikely(!comgen_ehok1(self))
		goto fail;

	/* Remove the service_comdesc to the list of active commands `cg_service->s_active_list' */
	comgen_rem_from_active(self);
	if unlikely(!comgen_txok1(self))
		goto fail;

	/* Check if the command completed with a special status code */
	if (SERVICE_COM_ST_SUCCESS == 0) {
		/* >> testP  %Pax, %Pax */
		gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);

		/* >> jnz    .Lcom_special_return */
		gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4);
	} else {
		/* >> cmpP   $SERVICE_COM_ST_SUCCESS, %Pax */
		gen86_cmpP_imm_r(&self->cg_txptr, SERVICE_COM_ST_SUCCESS, GEN86_R_PAX);

		/* >> jne    .Lcom_special_return */
		gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NE, -4);
	}
	comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lcom_special_return);

	/* >> .Lcom_special_return_resume: */
	comgen_defsym(self, COM_SYM_Lcom_special_return_resume);
	if unlikely(!comgen_txok1(self))
		goto fail;

	/* Deserialize fixed-length inline buffers */
	comgen_deserialize_inline_buffers(self);

	/* Copy out-of-band inout/out buffers back into user-provided storage */
	comgen_deserialize_buffer_arguments(self);
	if unlikely(!comgen_txok1(self))
		goto fail;

	/* Free the xbuf buffer */
	comgen_free_xbuf(self);

	/* Free the com buffer */
	comgen_free_combuf(self);
	if unlikely(!comgen_txok1(self))
		goto fail;
#ifndef __x86_64__
	if unlikely(!comgen_ehok1(self))
		goto fail;
#endif /* !__x86_64__ */

	/* Restore preemption */
	assert(normal_cfa_offset == self->cg_cfa_offset);
	comgen_restore_preemption(self);

	/* Normal return */
	comgen_normal_return(self);
	if unlikely(!comgen_txok1(self))
		goto fail;
	if unlikely(!comgen_ehok1(self))
		goto fail;

	assertf(self->cg_cfa_offset == SIZEOF_POINTER,
	        "self->cg_cfa_offset = %" PRId16,
	        self->cg_cfa_offset);

	/* NOTE: Technically,  we'd need to restore our `cg_cfa_offset' member
	 *       to  equal its value prior to `comgen_restore_preemption()' at
	 *       this point. However, that isn't needed because nothing within
	 *       `comgen_sigcheck_before_return()' makes use of it! */

	/* Check signals */
	comgen_sigcheck_before_return(self);

	/* Error/Exception  handlers all run  in the context of  the normal CFA offset.
	 * As far as  unwind information  goes, this  value has  already been  restored
	 * by the second `.cfi_restore_state' inside `comgen_sigcheck_before_return()',
	 * but that didn't update our  notion of the CFA  offset, yet. As such,  simply
	 * do that now so we're up to date once again! */
	self->cg_cfa_offset = normal_cfa_offset;

	/* Check signals when re-enabling preemption after buffer xbuf alloc */
	comgen_sigcheck_for_buffers(self);
	if unlikely(!comgen_txok1(self))
		goto fail;
	if unlikely(!comgen_ehok1(self))
		goto fail;

	/* Define non-exception errno handles. */
	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		comgen_handle_errno_problems(self);
		if unlikely(!comgen_txok1(self))
			goto fail;
		if unlikely(!comgen_ehok1(self))
			goto fail;
	}

	/* Try-hard removal of commands from the active list */
	comgen_remove_service_com_tryhard(self);
	if (!comgen_compile_isok(self))
		goto fail;

	/* Handling for custom completion status codes */
	comgen_custom_status_return(self);
	if (!comgen_compile_isok(self))
		goto fail;
	if unlikely(!comgen_ehok1(self))
		goto fail;

	/* Define exception handlers. */
	comgen_eh_com_waitfor_entry(self);
	comgen_eh_free_xbuf_entry(self);
	comgen_eh_free_service_com_entry(self);
	comgen_eh_preemption_pop_entry(self);
	if (!comgen_compile_isok(self))
		goto fail;

	/* Mark the end of the .eh_frame procedure.
	 * The rest of the .text section is (ab-)used as .gcc_except_table. */
	comgen_eh_frame_endproc(self);

	/* Need at least 4 more bytes at the end of .eh_frame (for the sentinel chunk) */
	if (!comgen_ehav(self, 4))
		goto fail;
	UNALIGNED_SET32((u32 *)self->cg_ehptr, 0);

	/* Generate  LSDA (like it would appear in .gcc_except_table)
	 * This data we simply put into .text (even though it doesn't
	 * need to be executable, doing so is the easiest way for  us
	 * to define it) */
	{
		uint8_t *gcc_except_table;
		gcc_except_table = comgen_gcc_except_table(self);
		comgen_eh_set_lsda(self, gcc_except_table);
	}

	/* Do one last check if everything went OK */
	if (!comgen_compile_isok(self))
		goto fail;

	/* Apply relocations. (this can't fail,  so
	 * we can do it after the last isok check!) */
	comgen_apply_relocations(self);

	/* Finalize the eh_frame descriptor. This _must_ be done last, as
	 * this operation includes a point-of-no-return, as it (may) make
	 * the newly generated function (and its unwind data) visible  to
	 * other threads. */
	comgen_eh_frame_finish(self);
	return true;
fail:
	return false;
}





DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */
