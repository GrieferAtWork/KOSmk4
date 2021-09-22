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

#include "../../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/minmax.h>

#include <kos/bits/userprocmask.h>
#include <kos/except.h>
#include <kos/types.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>

#include <libgen86/gen.h>
#include <libservice/client.h>

#include "../../com.h"
#include "wrapper.h"

DECL_BEGIN

#ifndef __getuserprocmask_defined
#error "Generated wrapper functions assume that userprocmask is available and supported!"
#endif /* !__getuserprocmask_defined */



/* When the currently set exception is RT-level, return `false'.
 * Otherwise,   clear   the   exception   and   return   `true'. */
INTERN bool NOTHROW(FCALL libservice_aux_com_discard_nonrt_exception)(void) {
	struct exception_data *d = error_data();
	if (ERRORCLASS_ISRTLPRIORITY(d->e_class))
		return false;
	d->e_code = ERROR_CODEOF(E_OK); /* Clear exception */
	return true;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) int
compar_com_inline_buffer_param(void const *_a, void const *_b) {
#define _MASK (COM_INLINE_BUFFER_PARAM_FIN | COM_INLINE_BUFFER_PARAM_FOUT)
	STATIC_ASSERT(COM_INLINE_BUFFER_PARAM_FIN < COM_INLINE_BUFFER_PARAM_FOUT);
	struct com_inline_buffer_param const *a, *b;
	a = (struct com_inline_buffer_param const *)_a;
	b = (struct com_inline_buffer_param const *)_b;
	if ((a->cibp_flags & _MASK) < (b->cibp_flags & _MASK))
		return -1; /* Less than */
	if ((a->cibp_flags & _MASK) > (b->cibp_flags & _MASK))
		return 1; /* Greater than */

	/* Non-pointer-aligned buffer sizes go after those that are  pointer-aligned.
	 * That way, the number of buffers following those which leave %Pdi unaligned
	 * may be reduced by 1. */
	{
		bool is_a_aligned = IS_ALIGNED(a->cibp_sizeof, sizeof(void *));
		bool is_b_aligned = IS_ALIGNED(b->cibp_sizeof, sizeof(void *));
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
	STATIC_ASSERT(COM_BUFFER_PARAM_FIN < COM_BUFFER_PARAM_FOUT);
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

	/* Lastly, sort by serial argument stream offsets. */
	if (a->cbp_serial_offset < b->cbp_serial_offset)
		return -1; /* Less than */
	if (a->cbp_serial_offset > b->cbp_serial_offset)
		return 1; /* Greater than */

	/* Shouldn't get here! */
	return 0;
#undef _MASK
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
			next += sizeof(void *);
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
 *  - self->cg_txptr, self->cg_ehptr
 *  - self->cg_txbas, self->cg_ehbas
 *  - self->cg_txend, self->cg_ehend
 *  - self->cg_cfa_offset, self->cg_nrelocs */
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
	 * offsets are only correct when `COM_GENERATOR_FEATURE_USES_R12' isn't set.
	 * Code  that may eventually set `COM_GENERATOR_FEATURE_USES_R12' knows this
	 * and will adjust offsets to account for 8 more bytes of offset. */
	if (i > 6) /* First 6 arguments are passed through registers (and are therefor saved) */
		i = 6;
	param_offset = -((3 + i) * sizeof(void *));
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
	serial_offset              = offsetof(struct service_com, sc_generic.g_data);
	for (i = 0; i < SERVICE_ARGC_MAX; ++i) {
		uint8_t flags;
		service_typeid_t typ;
		typ = self->cg_info.dl_params[i];
		switch (typ & _SERVICE_TYPE_CLASSMASK) {

		case (SERVICE_TYPE_ARGBUF_IN(0) & _SERVICE_TYPE_CLASSMASK): {
			struct com_buffer_param *par;
do_flexible_inbuf_argument:
			flags = COM_BUFFER_PARAM_FIN;
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
				par->cibp_serial_offset = serial_offset; /* [const] Offset from `struct service_com' to where the address of this buffer is saved */
/*				par->cibp_buffer_offset = ...;            * Initialized later */
				par->cibp_sizeof        = buffer_sizeof;
			} else {
				/* Use a dynamically allocated buffer. */
				struct com_buffer_param *par;
				STATIC_ASSERT(COM_INLINE_BUFFER_PARAM_FIN == COM_BUFFER_PARAM_FIN);
				STATIC_ASSERT(COM_INLINE_BUFFER_PARAM_FOUT == COM_BUFFER_PARAM_FOUT);
				par = &self->cg_buf_paramv[self->cg_buf_paramc++];
				par->cbp_flags         = flags;
				par->cbp_param_index   = i;
				par->cbp_param_offset  = param_offset;
				par->cbp_serial_offset = serial_offset;
				switch (flags) {
				case COM_INLINE_BUFFER_PARAM_FIN:
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
				param_offset += sizeof(void *);
				serial_offset += sizeof(void *);
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
		param_offset += sizeof(void *);
		serial_offset += sizeof(void *);

#ifdef __x86_64__
		/* Special case: Once we hit the `SAVED: %Pbx'-field, we've
		 * handled all register parameters  and must jump ahead  to
		 * continue on with stack-based arguments. */
		if (param_offset == -3 * (int16_t)sizeof(void *))
			param_offset = 0;
#endif /* __x86_64__ */
	}
done_params:
#ifndef __x86_64__
	self->cg_paramc = i;
#endif /* !__x86_64__ */

#ifdef __x86_64__
	/* When  at least  2 buffer parameters  exist, then `%r12'  will be used
	 * by the implementation. As such, we  need to set the appropriate  code
	 * feature flag, as well as  adjust parameter offsets since all  offsets
	 * pointing into the argument save area will be shifted down by 8 bytes. */
	if (self->cg_buf_paramc >= 2) {
#define reloc_param_offset(x) ((x) < 0 ? (void)((x) -= 8) : (void)0)
		self->cg_features |= COM_GENERATOR_FEATURE_USES_R12;
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
		/* Inline buffers are always pointer-aligned. */
		serial_offset = CEIL_ALIGN(serial_offset, sizeof(void *));
		self->cg_inline_buf_paramv[i].cibp_buffer_offset = serial_offset;
		serial_offset += self->cg_inline_buf_paramv[i].cibp_sizeof;
	}

	/* The  end address  of the last  inline buffer is  equal to the
	 * minimum allocation size of the service_com descriptor struct. */
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
	self->cg_locvar_size = 2 * sizeof(void *); /* LOC_oldset, LOC_upm */
	if (self->cg_buf_paramc != 0) {
		self->cg_locvar_size += 2 * sizeof(void *);                   /* LOC_bufpar_ptr, LOC_bufpar_shm */
		self->cg_locvar_size += self->cg_buf_paramc * sizeof(void *); /* LOC_bufparam_handles */
		if (self->cg_inbuf_paramc != 0 && (self->cg_inoutbuf_paramc != 0 || self->cg_outbuf_paramc != 0))
			self->cg_locvar_size += sizeof(void *); /* LOC_outbuffers_start */
	}

	/* Figure out where local variables end, which in turn determines where they start. */
	{
		int16_t locend;
		locend = -3 * (int16_t)sizeof(void *); /* RETURN_PC, saved %Pbp, saved %Pbx */
#ifdef __x86_64__
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_R12)
			locend -= 8;                       /* Saved %r12 */
		locend -= MIN(self->cg_paramc, 6) * 8; /* Saved register params */
#else /* __x86_64__ */
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_ESI)
			locend -= 4; /* Saved %esi */
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_EDI)
			locend -= 4; /* Saved %edi */
#endif /* !__x86_64__ */
		/* Remember where local variables start */
		self->cg_locvar_offset = locend - self->cg_locvar_size;
	}
}




/* Compile  the  com generator  wrapper function.  Upon return,
 * the caller must check the status using `comgen_compile_st_*'
 * Only with both *_moretx and *_moreeh return `false' may  the
 * compile operation be  considered successful. Otherwise,  the
 * respective need-more-memory condition should be handled. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL comgen_compile)(struct com_generator *__restrict self) {
	/* TODO */
	(void)self;
	abort();
}





DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */
