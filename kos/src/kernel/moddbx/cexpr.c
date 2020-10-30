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
#ifndef GUARD_MODDBX_CEXPR_C
#define GUARD_MODDBX_CEXPR_C 1
#define _KOS_SOURCE 1
#define __HAVE_FPU 1 /* Enable FPU access */

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/rt.h>
#include <kernel/types.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/cfi.h>

/**/
#include "include/cexpr.h"
#include "include/cparser.h"
#include "include/csymbol.h"
#include "include/ctype.h"
#include "include/error.h"
#include "include/malloc.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN


#define _GETFLOAT(T, addr, Tresult, result)    \
	do {                                       \
		T _temp;                               \
		memcpy(&_temp, (addr), sizeof(_temp)); \
		(result) = (Tresult)_temp;             \
	}	__WHILE0
#define _SETFLOAT(T, addr, value)              \
	do {                                       \
		T _temp = (T)(value);                  \
		memcpy((addr), &_temp, sizeof(_temp)); \
	}	__WHILE0

#define GETFLOAT_IEEE754_FLOAT(addr, Tresult, result)       _GETFLOAT(__IEEE754_FLOAT_TYPE__, addr, Tresult, result)
#define SETFLOAT_IEEE754_FLOAT(addr, value)                 _SETFLOAT(__IEEE754_FLOAT_TYPE__, addr, value)
#define GETFLOAT_IEEE754_DOUBLE(addr, Tresult, result)      _GETFLOAT(__IEEE754_DOUBLE_TYPE__, addr, Tresult, result)
#define SETFLOAT_IEEE754_DOUBLE(addr, value)                _SETFLOAT(__IEEE754_DOUBLE_TYPE__, addr, value)
#define GETFLOAT_IEEE854_LONG_DOUBLE(addr, Tresult, result) _GETFLOAT(__IEEE854_LONG_DOUBLE_TYPE__, addr, Tresult, result)
#define SETFLOAT_IEEE854_LONG_DOUBLE(addr, value)           _SETFLOAT(__IEEE854_LONG_DOUBLE_TYPE__, addr, value)

#define GETFLOAT_BYKIND(kind, addr, Tresult, result, handle_bad_kind, handle_fault) \
	do {                                                                            \
		TRY {                                                                       \
			switch (kind) {                                                         \
			case CTYPE_KIND_IEEE754_FLOAT:                                          \
				GETFLOAT_IEEE754_FLOAT(addr, Tresult, result);                      \
				break;                                                              \
			case CTYPE_KIND_IEEE754_DOUBLE:                                         \
				GETFLOAT_IEEE754_DOUBLE(addr, Tresult, result);                     \
				break;                                                              \
			case CTYPE_KIND_IEEE854_LONG_DOUBLE:                                    \
				GETFLOAT_IEEE854_LONG_DOUBLE(addr, Tresult, result);                \
				break;                                                              \
			default: handle_bad_kind;                                               \
			}                                                                       \
		} EXCEPT {                                                                  \
			handle_fault;                                                           \
		}                                                                           \
	}	__WHILE0

#define SETFLOAT_BYKIND(kind, addr, value, handle_bad_kind, handle_fault) \
	do {                                                                  \
		TRY {                                                             \
			switch (kind) {                                               \
			case CTYPE_KIND_IEEE754_FLOAT:                                \
				SETFLOAT_IEEE754_FLOAT(addr, value);                      \
				break;                                                    \
			case CTYPE_KIND_IEEE754_DOUBLE:                               \
				SETFLOAT_IEEE754_DOUBLE(addr, value);                     \
				break;                                                    \
			case CTYPE_KIND_IEEE854_LONG_DOUBLE:                          \
				SETFLOAT_IEEE854_LONG_DOUBLE(addr, value);                \
				break;                                                    \
			default: handle_bad_kind;                                     \
			}                                                             \
		} EXCEPT {                                                        \
			handle_fault;                                                 \
		}                                                                 \
	}	__WHILE0


/* [1..cexpr_stacksize] Stack of currently pushed C-values. (see the below API) */
PUBLIC struct cvalue *cexpr_stack        = NULL;
PUBLIC struct cvalue cexpr_stack_stub[1] = {};

/* # of used stack entries */
PUBLIC size_t cexpr_stacksize = 0;

/* When true, only allow read-only C expression operations.
 * During a debugger reset, this option is reset to `false' */
PUBLIC bool cexpr_readonly = false;

/* Don't calculate/keep track of c expression values, but
 * only simulate the effective expression type. - Used to
 * implement `typeof()' in C expressions, as well as for
 * the purpose of auto-completion of struct member names
 * and the like. */
PUBLIC bool cexpr_typeonly = false;


/* Finalize the given C-value. */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL cvalue_fini)(struct cvalue *__restrict self) {
	switch (self->cv_kind) {

	case CVALUE_KIND_DATA:
		dbx_free(self->cv_data);
		break;

	case CVALUE_KIND_EXPR:
		dbx_free(self->cv_expr.v_buffer);
		ATTR_FALLTHROUGH
	case CVALUE_KIND_IEXPR:
		cvalue_cfiexpr_fini(&self->cv_expr.v_expr);
		break;

	default:
		break;
	}
	ctyperef_fini(&self->cv_type);
}


/* Read/write the value of the given CFI expression to/from buf.
 * @return: DBX_EOK:     Success.
 * @return: DBX_EFAULT:  Faulty memory location accessed.
 * @return: DBX_EINTERN: Internal error. */
PUBLIC NONNULL((1, 2)) dbx_errno_t
NOTHROW(KCALL cvalue_cfiexpr_readwrite)(struct cvalue_cfiexpr const *__restrict self,
                                        void *buf, size_t buflen, bool write) {
	uintptr_t pc;
	unsigned int error;
	TRY {
		if (!self->v_expr.l_expr && !self->v_expr.l_llist) {
			size_t copy_error;
			copy_error = write ? dbg_writememory(self->v_objaddr, buf, buflen, false)
			                   : dbg_readmemory(self->v_objaddr, buf, buflen);
			error = UNWIND_SUCCESS;
			if unlikely(copy_error)
				error = UNWIND_SEGFAULT;
		} else {
			di_debuginfo_compile_unit_t cu;
			size_t num_accessed_bits;
			struct debugmodule *mod;
			memset(&cu, 0, sizeof(cu));
			cu.cu_ranges.r_startpc = self->v_cu_ranges_startpc;
			cu.cu_addr_base        = self->v_cu_addr_base;
			pc                     = dbg_getpcreg(DBG_REGLEVEL_VIEW);
			mod                    = self->v_module;
			if (write) {
				error = debuginfo_location_setvalue(&self->v_expr,
				                                    di_debug_sections_as_unwind_emulator_sections(&mod->dm_sections),
				                                    &dbg_getreg, (void *)(uintptr_t)DBG_REGLEVEL_VIEW,
				                                    &dbg_setreg, (void *)(uintptr_t)DBG_REGLEVEL_VIEW, &cu,
				                                    pc - module_getloadaddr(mod->dm_module, mod->dm_modtyp),
				                                    buf, buflen, &num_accessed_bits, &self->v_framebase,
				                                    self->v_objaddr, self->v_addrsize, self->v_ptrsize);
			} else {
				error = debuginfo_location_getvalue(&self->v_expr,
				                                    di_debug_sections_as_unwind_emulator_sections(&mod->dm_sections),
				                                    &dbg_getreg, (void *)(uintptr_t)DBG_REGLEVEL_VIEW, &cu,
				                                    pc - module_getloadaddr(mod->dm_module, mod->dm_modtyp),
				                                    buf, buflen, &num_accessed_bits, &self->v_framebase,
				                                    self->v_objaddr, self->v_addrsize, self->v_ptrsize);
			}
		}
	} EXCEPT {
		error = UNWIND_SEGFAULT;
	}
	if unlikely(error != UNWIND_SUCCESS) {
		if (error == UNWIND_SEGFAULT)
			return DBX_EFAULT;
		return DBX_EINTERN;
	}
	return DBX_EOK;
}


PRIVATE NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cvalue_rw_expr)(struct cvalue *__restrict self,
                              bool write) {
	dbx_errno_t result;
	void *buffer;
	buffer = self->cv_expr.v_ibuffer;
	if (self->cv_kind == CVALUE_KIND_EXPR) {
		buffer = self->cv_expr.v_buffer;
		if (!buffer) {
			if (write)
				return DBX_EOK; /* Not loaded */
			/* Load a new buffer. */
			if (self->cv_expr.v_buflen <= sizeof(self->cv_expr.v_ibuffer)) {
				self->cv_kind = CVALUE_KIND_IEXPR;
				result = cvalue_rw_expr(self, false);
				if unlikely(result != DBX_EOK) {
					self->cv_kind          = CVALUE_KIND_EXPR;
					self->cv_expr.v_buffer = NULL;
				}
				return result;
			}
			/* Allocate a dynamic buffer. */
			buffer = dbx_malloc(self->cv_expr.v_buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			self->cv_expr.v_buffer = buffer;
			result = cvalue_rw_expr(self, false);
			if unlikely(result != DBX_EOK) {
				self->cv_expr.v_buffer = NULL;
				dbx_free(buffer);
			}
			return result;
		}
	}
	result = cvalue_cfiexpr_readwrite(&self->cv_expr.v_expr,
	                                  buffer,
	                                  self->cv_expr.v_buflen,
	                                  write);
	return result;
}

/* Sign- or zero-extend a given buffer. */
PRIVATE dbx_errno_t
NOTHROW(FCALL buffer_extend)(byte_t *data, size_t old_size,
                             size_t new_size, bool sign_extend) {
	TRY {
		if (new_size > old_size) {
			uint8_t sign;
			sign = 0x00;
			if (sign_extend) {
				/* Check if we should sign-extend. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				if (data[old_size - 1] & 0x80)
					sign = 0xff;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
				if (data[0] & 0x80)
					sign = 0xff;
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported __BYTE_ORDER__"
#endif /* __BYTE_ORDER__ != ... */
			}
			/* Zero-/sign-extend the pointed-to data. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			memset(&data[old_size], sign, new_size - old_size);
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			memmoveup(&data[new_size - old_size],
			          &data[0], old_size);
			memset(&data[0], sign, new_size - old_size);
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported __BYTE_ORDER__"
#endif /* __BYTE_ORDER__ != ... */
		} else {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			/* Truncate the value */
			if (new_size < old_size) {
				memmovedown((byte_t *)data,
				            (byte_t *)data + (old_size - new_size),
				            new_size);
			}
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
		}
	} EXCEPT {
		return DBX_EFAULT;
	}
	return DBX_EOK;
}

PRIVATE bool
NOTHROW(FCALL buffer_istrue)(byte_t const *buf, size_t buflen) {
	while (buflen) {
		if (*buf)
			return true;
		--buflen;
		++buf;
	}
	return false;
}

PRIVATE void
NOTHROW(FCALL buffer_inv)(byte_t *buf, size_t buflen) {
	while (buflen) {
		*buf ^= 0xff;
		--buflen;
		++buf;
	}
}

PRIVATE void
NOTHROW(FCALL buffer_dec)(byte_t *buf, size_t buflen) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	while (buflen) {
		if (--*buf != 0xff)
			break;
		--buflen;
		++buf;
	}
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	buf += buflen;
	while (buflen) {
		--buf;
		if (--*buf != 0xff)
			break;
		--buflen;
	}
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __BYTE_ORDER__ != ... */
}




/* Write-back changes made by `self'
 * @return: DBX_EOK:     Success.
 * @return: DBX_EFAULT:  Faulty memory access.
 * @return: DBX_EINTERN: Internal error. */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cvalue_flush)(struct cvalue *__restrict self) {
	dbx_errno_t result = DBX_EOK;
	switch (self->cv_kind) {

	case CVALUE_KIND_EXPR:
	case CVALUE_KIND_IEXPR:
		result = cvalue_rw_expr(self, true);
		break;

	case CVALUE_KIND_REGISTER: {
		size_t bufsize, bufneed, reqsize;
		bufsize = ctype_sizeof(self->cv_type.ct_typ);
		bufneed = self->cv_register.r_buflen;
		if unlikely(bufsize != bufneed) {
			/* Sign-/Zero-extend the value based on if the old type was signed. */
			uintptr_t kind;
			kind   = self->cv_type.ct_typ->ct_kind;
			result = buffer_extend(self->cv_register.r_ibuffer, bufsize, bufneed,
			                       CTYPE_KIND_ISINT(kind) && !CTYPE_KIND_INT_ISUNSIGNED(kind));
			if unlikely(result != DBX_EOK)
				goto done;
		}
		reqsize = arch_dbg_setregbyid(DBG_REGLEVEL_VIEW,
		                              self->cv_register.r_regid,
		                              self->cv_register.r_ibuffer,
		                              bufneed);
		if unlikely(reqsize != bufneed)
			result = DBX_EINTERN;
	}	break;

	default:
		break;
	}
done:
	return result;
}


/* Initialize a copy `self' of the given C-value `src'.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PUBLIC WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cvalue_initcopy)(struct cvalue *__restrict self,
                               struct cvalue const *__restrict src) {
	memcpy(self, src, sizeof(struct cvalue));
	switch (self->cv_kind) {
	
	case CVALUE_KIND_DATA:
		if (src->cv_data != NULL) {
			size_t buflen;
			void *buffer;
			buflen = ctype_sizeof(src->cv_type.ct_typ);
			buffer = dbx_malloc(buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			buffer = memcpy(buffer, src->cv_data, buflen);
			self->cv_expr.v_buffer = buffer;
		}
		break;
	
	case CVALUE_KIND_EXPR:
		if (self->cv_expr.v_buffer) {
			void *buffer;
			buffer = dbx_malloc(self->cv_expr.v_buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			buffer = memcpy(buffer, src->cv_expr.v_buffer,
			                self->cv_expr.v_buflen);
			self->cv_expr.v_buffer = buffer;
		}
		ATTR_FALLTHROUGH
	case CVALUE_KIND_IEXPR:
		incref(self->cv_expr.v_expr.v_module);
		break;
	
	default:
		break;
	}
	incref(self->cv_type.ct_typ);
	xincref(self->cv_type.ct_info.ci_nameref);
	return DBX_EOK;
}


PRIVATE WUNUSED struct cvalue *
NOTHROW(FCALL _cexpr_pushalloc)(void) {
	size_t alloc_size;
	struct cvalue *result = cexpr_stack - 1;
	if (result == cexpr_stack_stub)
		result = NULL;
	alloc_size = dbx_malloc_usable_size(result) / sizeof(struct cvalue);
	if ((cexpr_stacksize + 2) > alloc_size) {
		result = (struct cvalue *)dbx_realloc(result,
		                                      (cexpr_stacksize + 2) *
		                                      sizeof(struct cvalue));
		if unlikely(!result)
			goto done;
		result = (struct cvalue *)memcpy(result, cexpr_stack_stub,
		                                 sizeof(struct cvalue));
		cexpr_stack = result + 1;
	}
	result += cexpr_stacksize + 1;
done:
	return result;
}

/* Push an element into the C-expression stack.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: [cexpr_pushregister_by_id] No such register. */
PUBLIC NONNULL((1)) dbx_errno_t /* Push `*(typ *)addr' */
NOTHROW(FCALL cexpr_pushaddr)(struct ctyperef const *__restrict typ,
                              USER void *addr) {
	struct cvalue *valp;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	ctyperef_initcopy(&valp->cv_type, typ);
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else {
		valp->cv_kind = CVALUE_KIND_ADDR;
		valp->cv_addr = addr;
	}
	++cexpr_stacksize;
	return DBX_EOK;
}

PUBLIC NONNULL((1, 2)) dbx_errno_t /* Push a CFI expression. */
NOTHROW(FCALL cexpr_pushexpr)(struct ctyperef const *__restrict typ,
                              struct cvalue_cfiexpr const *__restrict expr,
                              size_t buflen, size_t bufoff) {
	struct cvalue *valp;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	ctyperef_initcopy(&valp->cv_type, typ);
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else if (expr->v_objaddr && !expr->v_expr.l_expr && !expr->v_expr.l_llist) {
		/* Special case: non-CFI object-address expression. */
		valp->cv_kind = CVALUE_KIND_ADDR;
		valp->cv_addr = (byte_t *)expr->v_objaddr + buflen;
	} else {
		cvalue_cfiexpr_initcopy(&valp->cv_expr.v_expr, expr);
		valp->cv_kind          = CVALUE_KIND_EXPR;
		valp->cv_expr.v_buffer = NULL;
		valp->cv_expr.v_bufoff = bufoff;
		valp->cv_expr.v_buflen = buflen;
	}
	++cexpr_stacksize;
	return DBX_EOK;
}

FUNDEF NONNULL((1, 2)) dbx_errno_t /* Push `(typ)*(typ *)data' */
NOTHROW(FCALL cexpr_pushdata)(struct ctyperef const *__restrict typ,
                              void const *__restrict data) {
	struct cvalue *valp;
	void *buffer;
	size_t buflen;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else {
		buflen = ctype_sizeof(typ->ct_typ);
		if (buflen <= sizeof(valp->cv_idata)) {
			buffer        = valp->cv_idata;
			valp->cv_kind = CVALUE_KIND_IDATA;
		} else {
			buffer = dbx_malloc(buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			valp->cv_data = (byte_t *)buffer;
			valp->cv_kind = CVALUE_KIND_DATA;
		}
		memcpy(buffer, data, buflen);
	}
	ctyperef_initcopy(&valp->cv_type, typ);
	++cexpr_stacksize;
	return DBX_EOK;
}

FUNDEF NONNULL((1)) dbx_errno_t /* Push `(typ)value' */
NOTHROW(FCALL cexpr_pushint)(struct ctyperef const *__restrict typ,
                             __UINTMAX_TYPE__ value) {
	struct cvalue *valp;
	size_t buflen;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else {
		buflen = ctype_sizeof(typ->ct_typ);
		switch (buflen) {
		case 1: *(uint8_t *)valp->cv_idata = (uint8_t)value; break;
		case 2: UNALIGNED_SET16((uint16_t *)valp->cv_idata, (uint16_t)value); break;
		case 4: UNALIGNED_SET32((uint32_t *)valp->cv_idata, (uint32_t)value); break;
		case 8: UNALIGNED_SET64((uint64_t *)valp->cv_idata, (uint64_t)value); break;
		default:
			return DBX_EINTERN;
		}
		valp->cv_kind = CVALUE_KIND_IDATA;
	}
	ctyperef_initcopy(&valp->cv_type, typ);
	++cexpr_stacksize;
	return DBX_EOK;
}

/* Push a register, given its arch-specific ID, automatically selecting a proper type.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No such register. */
PUBLIC dbx_errno_t /* Push `(auto)%[reg:id]' */
NOTHROW(FCALL cexpr_pushregister_by_id)(unsigned int id) {
	struct cvalue *valp;
	size_t buflen;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	buflen = arch_dbg_setregbyid(DBG_REGLEVEL_VIEW, id,
	                             valp->cv_register.r_ibuffer,
	                             sizeof(valp->cv_register.r_ibuffer));
	if unlikely(buflen > sizeof(valp->cv_register.r_ibuffer))
		return DBX_EINTERN; /* Internal error */
	if unlikely(!buflen)
		return DBX_ENOENT; /* No such register */
	valp->cv_type.ct_typ = ctype_for_register(id, buflen);
	if unlikely(!valp->cv_type.ct_typ)
		return DBX_EINTERN; /* Internal error */
	ctypeinfo_init(&valp->cv_type.ct_info);
	valp->cv_type.ct_flags = CTYPEREF_FLAG_NORMAL;
	valp->cv_kind          = CVALUE_KIND_REGISTER;
	if (cexpr_typeonly)
		valp->cv_kind = CVALUE_KIND_VOID;
	++cexpr_stacksize;
	return DBX_EOK;
}


/* Same as above, but only require basic typ
 * information (typ flags, and name are pushed as 0/NULL) */
PUBLIC NONNULL((1)) dbx_errno_t /* Push `*(typ *)addr' */
NOTHROW(FCALL cexpr_pushaddr_simple)(struct ctype *__restrict typ,
                                     USER void *addr) {
	struct ctyperef ct;
	memset(&ct, 0, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_pushaddr(&ct, addr);
}

PUBLIC NONNULL((1, 2)) dbx_errno_t /* Push `(typ)*(typ *)data' */
NOTHROW(FCALL cexpr_pushdata_simple)(struct ctype *__restrict typ,
                                     void const *__restrict data) {
	struct ctyperef ct;
	memset(&ct, 0, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_pushdata(&ct, data);
}

PUBLIC NONNULL((1)) dbx_errno_t /* Push `(typ)value' */
NOTHROW(FCALL cexpr_pushint_simple)(struct ctype *__restrict typ,
                                    __UINTMAX_TYPE__ value) {
	struct ctyperef ct;
	memset(&ct, 0, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_pushint(&ct, value);
}



/* Pop the top element from the C expression stack.
 * @return: DBX_EOK:     Success.
 * @return: DBX_EINTERN: Stack was already empty. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_pop)(void) {
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	--cexpr_stacksize;
	cvalue_fini(&cexpr_stack[cexpr_stacksize]);
	return DBX_EOK;
}


/* Clear the C expression stack. */
PUBLIC void NOTHROW(FCALL cexpr_empty)(void) {
	while (cexpr_stacksize)
		cexpr_pop();
}

/* Duplicate the C expression top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_dup)(void) {
	dbx_errno_t result;
	struct cvalue *valp;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	result = cvalue_initcopy(valp, &cexpr_stacktop);
	if likely(result == DBX_EOK)
		++cexpr_stacksize;
	return result;
}

#define MOVE_CVALUE(dst, src) memcpy(&(dst), &(src), sizeof(struct cvalue))

/* Swap the two 2 c expression stack elements.
 * @return: DBX_EOK:     Success
 * @return: DBX_EINTERN: The stack size is < 2 */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_swap)(void) {
	struct cvalue temp;
	if unlikely(cexpr_stacksize < 2)
		return DBX_EINTERN;
	MOVE_CVALUE(temp, cexpr_stack[cexpr_stacksize - 1]);
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - 1], cexpr_stack[cexpr_stacksize - 2]);
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - 2], temp);
	return DBX_EOK;
}

/* Rotate the top n c expression stack elements left/right.
 * When `n <= 1', these calls are a no-op in regards to 
 * @return: DBX_EOK:     Success
 * @return: DBX_EINTERN: The stack size is < n */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_lrot)(unsigned int n) {
	struct cvalue temp;
	if unlikely(cexpr_stacksize < n)
		return DBX_EINTERN;
	if unlikely(n <= 1)
		return DBX_EOK; /* no-op */
	MOVE_CVALUE(temp, cexpr_stack[cexpr_stacksize - n]);
	memmovedown(&cexpr_stack[cexpr_stacksize - n],
	            &cexpr_stack[cexpr_stacksize - (n - 1)],
	            n - 1, sizeof(struct cvalue));
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - 1], temp);
	return DBX_EOK;
}

PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_rrot)(unsigned int n) {
	struct cvalue temp;
	if unlikely(cexpr_stacksize < n)
		return DBX_EINTERN;
	if unlikely(n <= 1)
		return DBX_EOK; /* no-op */
	MOVE_CVALUE(temp, cexpr_stack[cexpr_stacksize - 1]);
	memmoveup(&cexpr_stack[cexpr_stacksize - (n - 1)],
	          &cexpr_stack[cexpr_stacksize - n],
	          n - 1, sizeof(struct cvalue));
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - n], temp);
	return DBX_EOK;
}



/* Return a pointer to the data associated with the top expression stack element.
 * If the stack is empty, or an intermediate buffer is required for storing data,
 * and that buffer could not be allocated, return NULL instead.
 * When `cexpr_typeonly' is set to true, this function always returns `NULL' */
PUBLIC WUNUSED byte_t *
NOTHROW(FCALL cexpr_getdata)(void) {
	byte_t *result;
	struct cvalue *top;
	if unlikely(!cexpr_stacksize)
		return NULL;
	top = &cexpr_stacktop;
again:
	switch (top->cv_kind) {

	case CVALUE_KIND_ADDR:
		result = (byte_t *)top->cv_addr;
		break;

	case CVALUE_KIND_DATA:
		result = top->cv_data;
		break;

	case CVALUE_KIND_IDATA:
		result = top->cv_idata;
		break;

	case CVALUE_KIND_EXPR: {
		size_t bufavail;
		result = (byte_t *)top->cv_expr.v_buffer;
		/* Lazily load a CFI expression. */
		if (!result) {
			if (cvalue_rw_expr(top, false) == DBX_EOK)
				goto again;
			return NULL;
		}
		/* Assert that sufficient space is available for the type in use.
		 * If less space is available, return NULL to prevent writing past
		 * the end of the internal buffer for expressions.
		 * Note though, that this really shouldn't happen... */
		if (OVERFLOW_USUB(top->cv_expr.v_buflen, top->cv_expr.v_bufoff, &bufavail))
			return NULL;
		if (bufavail < ctype_sizeof(top->cv_type.ct_typ))
			return NULL;
		/* Adjust the buffer pointer for the expression-base-offset.
		 * This is used (e.g.) for accessing struct-through-CFI fields. */
		result += top->cv_expr.v_bufoff;
	}	break;

	case CVALUE_KIND_IEXPR:
		result = top->cv_expr.v_ibuffer + top->cv_expr.v_bufoff;
		break;

	case CVALUE_KIND_REGISTER:
		result = top->cv_register.r_ibuffer;
		break;

	default:
		result = NULL;
		break;
	}
	return result;
}

/* Return the actual size of the top element of the C expression stack.
 * If the stack is empty, return `0' instead. (s.a. `ctype_sizeof()') */
PUBLIC WUNUSED size_t
NOTHROW(FCALL cexpr_getsize)(void) {
	if unlikely(!cexpr_stacksize)
		return 0;
	return ctype_sizeof(cexpr_stacktop.cv_type.ct_typ);
}

/* Return the boolean value of the top stack element.
 * When `cexpr_typeonly' is set to true, this function's return value is undefined.
 * @return: 1:           Value is true.
 * @return: 0:           Value is false.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: The top stack element cannot be cast to bool. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_bool)(void) {
	struct ctype *ct;
	byte_t *data;
	size_t datalen;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	ct      = cexpr_stacktop.cv_type.ct_typ;
	data    = cexpr_getdata();
	datalen = cexpr_getsize();
	if (!data && cexpr_stacktop.cv_kind != CVALUE_KIND_VOID)
		return DBX_ENOMEM;
	TRY {
		switch (CTYPE_KIND_CLASSOF(ct->ct_kind)) {

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
do_check_for_non_zero_byte:
			if (data && buffer_istrue(data, datalen))
				return 1;
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_IEEE754_FLOAT):
			if (data) {
				switch (ct->ct_kind) {
	
				case CTYPE_KIND_IEEE754_FLOAT: {
					float f;
					memcpy(&f, data, sizeof(f));
					if (f != 0.0f)
						return 1;
				}	break;
	
				case CTYPE_KIND_IEEE754_DOUBLE: {
					double d;
					memcpy(&d, data, sizeof(d));
					if (d != 0.0)
						return 1;
				}	break;
	
				case CTYPE_KIND_IEEE854_LONG_DOUBLE: {
					__LONGDOUBLE ld;
					memcpy(&ld, data, sizeof(ld));
					if (ld != 0.0l)
						return 1;
				}	break;
	
				default:
					goto do_check_for_non_zero_byte;
				}
			}
			break;

		default:
			return DBX_ESYNTAX;
		}
	} EXCEPT {
		return DBX_EFAULT;
	}
	return 0; /* false */
}

/* Cast the stack-top element to `typ'.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: The top stack element cannot be cast to `typ'. */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cast)(struct ctyperef const *__restrict typ) {
	dbx_errno_t result;
	struct ctype *old_typ;
	struct ctype *new_typ;
	struct cvalue *top;
	byte_t *data;
again:
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top     = &cexpr_stacktop;
	new_typ = typ->ct_typ;
	if (CTYPE_KIND_ISVOID(new_typ->ct_kind)) {
		/* Anything can be cast to void */
		cvalue_fini(top);
		ctyperef_initcopy(&top->cv_type, typ);
		top->cv_kind = CVALUE_KIND_VOID;
		return DBX_EOK;
	}
	/* Make sure that stack-top is an R-value. */
	result = cexpr_rvalue();
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(top->cv_kind != CVALUE_KIND_DATA &&
	            top->cv_kind != CVALUE_KIND_IDATA &&
	            top->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen... */
	data = top->cv_idata;
	if (top->cv_kind == CVALUE_KIND_DATA)
		data = top->cv_data;
	old_typ = top->cv_type.ct_typ;
	/* Check for special case: cast from float. */
	if (CTYPE_KIND_ISFLOAT(old_typ->ct_kind)) {
		if (CTYPE_KIND_ISFLOAT(new_typ->ct_kind)) {
			/* Cast between floating-point types. */
			if (top->cv_kind != CVALUE_KIND_VOID) {
				__LONGDOUBLE value;
				GETFLOAT_BYKIND(old_typ->ct_kind, data, __LONGDOUBLE, value, return DBX_EINTERN, return DBX_EFAULT);
				SETFLOAT_BYKIND(new_typ->ct_kind, data, value, return DBX_EINTERN, return DBX_EFAULT);
			}
		} else {
			intmax_t floatval = 0;
			/* Re-push the float value as an integer */
			if (top->cv_kind != CVALUE_KIND_VOID) {
				GETFLOAT_BYKIND(old_typ->ct_kind, data, intmax_t, floatval,
				                return DBX_EINTERN, return DBX_EFAULT);
			}
			result = cexpr_pop();
			if unlikely(result != DBX_EOK)
				return result;
			result = cexpr_pushint_simple(&ctype_intmax_t, (uintmax_t)floatval);
			if unlikely(result != DBX_EOK)
				return result;
			goto again;
		}
		goto set_new_type;
	}
	/* Check for special case: cast to float. */
	if (CTYPE_KIND_ISFLOAT(new_typ->ct_kind)) {
		switch (CTYPE_KIND_CLASSOF(old_typ->ct_kind)) {

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR): {
			uintmax_t value;
			if (top->cv_kind == CVALUE_KIND_VOID)
				goto set_new_type;
			TRY {
				switch (CTYPE_KIND_SIZEOF(old_typ->ct_kind)) {
				case 1: value = *(uint8_t *)data; break;
				case 2: value = UNALIGNED_GET16((uint16_t *)data); break;
				case 4: value = UNALIGNED_GET32((uint32_t *)data); break;
				case 8: value = UNALIGNED_GET64((uint64_t *)data); break;
				default:
					return DBX_EINTERN;
				}
			} EXCEPT {
				return DBX_EFAULT;
			}
			if (CTYPE_KIND_CLASSOF(old_typ->ct_kind) ==
			    CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL))
				value = !!value;
			/* Write-back the integer value as a float. */
			SETFLOAT_BYKIND(new_typ->ct_kind, data, value,
			                return DBX_EINTERN, return DBX_EFAULT);
			goto set_new_type;
		}	break;

		default:
			return DBX_ESYNTAX;
		}
		goto set_new_type;
	}
	/* All right! With floating-point out of the way, move on to integer casts.
	 * For this purpose, allow any sort of cast to/from integer/bool/pointer types. */
	if (CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(old_typ->ct_kind) &&
	    CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(new_typ->ct_kind))
		goto ok;
	/* All other types of casts aren't allowed. */
	return DBX_ESYNTAX;
ok:
	/* Confirmed (apply value transformations) */
	if (top->cv_kind != CVALUE_KIND_VOID) {
		size_t old_size, new_size;
		old_size = ctype_sizeof(old_typ);
		new_size = ctype_sizeof(new_typ);
		if (new_size != old_size) {
			if (new_size > CVALUE_INLINE_MAXSIZE) {
				/* Must allocate a new heap-buffer */
				byte_t *old_data;
				byte_t *new_data;
				old_data = data;
				if (old_data == top->cv_idata)
					old_data = NULL;
				new_data = (byte_t *)dbx_realloc(old_data, new_size);
				if unlikely(!new_data)
					return DBX_ENOMEM;
				if (data == top->cv_idata)
					memcpy(new_data, data, old_size);
				top->cv_data = data = new_data;
				top->cv_kind = CVALUE_KIND_DATA;
			}
			/* Sign-/Zero-extend the value based on if the old type was signed. */
			result = buffer_extend(data, old_size, new_size,
			                       CTYPE_KIND_ISINT(old_typ->ct_kind) &&
			                       !CTYPE_KIND_INT_ISUNSIGNED(old_typ->ct_kind));
			if unlikely(result != DBX_EOK)
				return result;
		}
	}
set_new_type:
	ctyperef_fini(&top->cv_type);
	ctyperef_initcopy(&top->cv_type, typ);
/*done:*/
	return DBX_EOK;
}

PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cast_simple)(struct ctype *__restrict typ) {
	struct ctyperef ct;
	memset(&ct, 0, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_cast(&ct);
}



/* Convert the top C expression stack element into an R-value,
 * such that if a potentially pointed-to memory location is changed,
 * then the stack element retains the original value. This function
 * also promotes array->pointer types.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: Attempted to promote an address-less array to a pointer. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_rvalue)(void) {
	struct cvalue *top;
	dbx_errno_t result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top = &cexpr_stacktop;
	if (CTYPE_KIND_ISARRAY(top->cv_type.ct_typ->ct_kind)) {
		struct ctyperef array_elem_type;
		REF struct ctype *array_elem_pointer_type;
		STATIC_ASSERT_MSG(offsetof(struct cvalue, cv_addr) == offsetof(struct cvalue, cv_idata),
		                  "This is required so we don't have to copy the old address into the "
		                  "new inline-data field");
		/* Check if the address of the top-element can be taken. */
		if (top->cv_kind != CVALUE_KIND_ADDR &&
		    top->cv_kind != CVALUE_KIND_VOID)
			return DBX_ESYNTAX;
		ctypeinfo_init(&array_elem_type.ct_info);
		array_elem_type.ct_typ   = top->cv_type.ct_typ->ct_array.ca_elem;
		array_elem_type.ct_flags = top->cv_type.ct_flags;
		array_elem_pointer_type  = ctype_ptr(&array_elem_type, dbg_current_sizeof_pointer());
		if unlikely(!array_elem_pointer_type)
			return DBX_ENOMEM;
		ctyperef_fini(&top->cv_type);
		ctypeinfo_init(&top->cv_type.ct_info);
		top->cv_type.ct_typ   = array_elem_pointer_type; /* Inherit reference */
		top->cv_type.ct_flags = CTYPEREF_FLAG_NORMAL;
		if (top->cv_kind == CVALUE_KIND_ADDR)
			top->cv_kind = CVALUE_KIND_IDATA; /* Re-use the address-field as inline-rvalue-data. */
		return DBX_EOK;
	}
again_switch_kind:
	switch (top->cv_kind) {

	case CVALUE_KIND_VOID:
		/* No-op */
		break;

	case CVALUE_KIND_EXPR: {
		void *data = cexpr_getdata();
		if unlikely(!data)
			return DBX_ENOMEM;
		if (top->cv_kind != CVALUE_KIND_EXPR)
			goto again_switch_kind;
		/* Just inherit the expression buffer. */
		cvalue_cfiexpr_fini(&top->cv_expr.v_expr);
		top->cv_kind = CVALUE_KIND_DATA;
		top->cv_data = (byte_t *)data;
	}	break;

	case CVALUE_KIND_ADDR:
	case CVALUE_KIND_IEXPR:
	case CVALUE_KIND_REGISTER: {
		uintptr_t newkind;
		byte_t *buffer;
		size_t buflen;
		buflen  = ctype_sizeof(top->cv_type.ct_typ);
		buffer  = top->cv_idata;
		newkind = CVALUE_KIND_IDATA;
		if (buflen > CVALUE_INLINE_MAXSIZE) {
			newkind = CVALUE_KIND_DATA;
			buffer  = (byte_t *)dbx_malloc(buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
		}
		result = DBX_EOK;
		TRY {
			switch (top->cv_kind) {

			case CVALUE_KIND_ADDR:
				memcpy(buffer, top->cv_addr, buflen);
				break;

			case CVALUE_KIND_IEXPR:
				cvalue_cfiexpr_fini(&top->cv_expr.v_expr);
				memmove(buffer, top->cv_expr.v_ibuffer, buflen);
				break;

			case CVALUE_KIND_REGISTER:
				memcpy(buffer, top->cv_register.r_ibuffer, buflen);
				break;

			default:
				__builtin_unreachable();
			}
		} EXCEPT {
			result = DBX_EFAULT;
		}
		if unlikely(result != DBX_EOK) {
			if (newkind == CVALUE_KIND_DATA)
				dbx_free(buffer);
			return result;
		}
		top->cv_kind = newkind;
		if (newkind == CVALUE_KIND_DATA)
			top->cv_data = buffer;
	}	break;

	case CVALUE_KIND_DATA:
	case CVALUE_KIND_IDATA:
		/* Already an R-value! */
		break;

	default:
		return DBX_EINTERN;
	}
	return DBX_EOK;
}

/* Force R-value, and promote the top C-expression-stack element:
 *   - Convert `int[42]'        -> `int *'     (already done by `cexpr_rvalue()')
 *   - Convert `int(int, long)' -> `int(*)(int, long)'
 *   - Convert `char'           -> `int'
 *   - Convert `short'          -> `int'
 *   - Convert `unsigned char'  -> `unsigned int'
 *   - Convert `unsigned short' -> `unsigned int'
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: Attempted to promote an address-less array to a pointer. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_promote)(void) {
	struct cvalue *top;
	dbx_errno_t result;
	struct ctype *old_type;
	result = cexpr_rvalue();
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN; /* Shouldn't happen */
	top = &cexpr_stacktop;
	if unlikely(top->cv_kind != CVALUE_KIND_DATA &&
	             top->cv_kind != CVALUE_KIND_IDATA)
		return DBX_EINTERN; /* Shouldn't happen */
	old_type = top->cv_type.ct_typ;
	if (CTYPE_KIND_ISINT_OR_BOOL(old_type->ct_kind) &&
	    CTYPE_KIND_SIZEOF(old_type->ct_kind) < sizeof(int))
		return cexpr_cast_simple(&ctype_int); /* Cast to `int' */
	if (old_type->ct_kind == CTYPE_KIND_IEEE754_FLOAT)
		return cexpr_cast_simple(&ctype_ieee754_double); /* Promote `float' to `double' */
	return DBX_EOK;
}


/* Access a field of a struct/union object in the C expression stack top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The C expression stack is empty.
 * @return: DBX_ESYNTAX: The C expression stack top-element isn't a struct/union.
 * @return: DBX_ENOENT:  The given `name' doesn't name a member of the top-element struct. */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_field)(char const *__restrict name,
                           size_t namelen) {
	dbx_errno_t result;
	struct ctyperef field_type;
	struct cvalue *top;
	ptrdiff_t field_offset;
	size_t field_size, temp;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top    = &cexpr_stacktop;
	result = ctype_struct_getfield(top->cv_type.ct_typ,
	                               name,
	                               namelen,
	                               &field_type,
	                               &field_offset);
	if unlikely(result != DBX_EOK)
		return result;
	field_size = ctype_sizeof(field_type.ct_typ);
	/* Make sure that the field is in-bounds of the structure as a whole. */
	if unlikely(OVERFLOW_UADD(field_offset, field_size, &temp) ||
	            temp > ctype_sizeof(top->cv_type.ct_typ))
		return DBX_EINTERN;
	switch (top->cv_kind) {

	case CVALUE_KIND_VOID:
		break;

	case CVALUE_KIND_ADDR:
		top->cv_addr = (byte_t *)top->cv_addr + field_offset;
		break;

	case CVALUE_KIND_EXPR:
	case CVALUE_KIND_IEXPR:
		top->cv_expr.v_bufoff += field_offset;
		break;

	case CVALUE_KIND_DATA: {
		byte_t *oldbuf = top->cv_data;
		if (field_size <= CVALUE_INLINE_MAXSIZE) {
			/* Switch over to the inline buffer */
			memcpy(top->cv_idata, oldbuf + field_offset, field_size);
			top->cv_kind = CVALUE_KIND_IDATA;
			dbx_free(oldbuf);
		} else {
			byte_t *newbuf;
			memmovedown(oldbuf, oldbuf + field_offset, field_size);
			/* Try to truncate the used buffer size. */
			newbuf = (byte_t *)dbx_realloc(oldbuf, field_size);
			if likely(newbuf)
				top->cv_data = newbuf;
		}
	}	break;

	case CVALUE_KIND_IDATA:
		memmovedown(&top->cv_idata[0],
		            &top->cv_idata[field_offset],
		            field_size);
		break;

	default:
		result = DBX_EINTERN;
		break;
	}
	if unlikely(result != DBX_EOK) {
		ctyperef_fini(&field_type);
		return result;
	}
	/* Copy over the field type into the C-value. */
	ctyperef_fini(&top->cv_type);
	memcpy(&top->cv_type, &field_type, sizeof(struct ctyperef));
	return DBX_EOK;
}


/* Ref/Deref the c-expression-stack top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_ESYNTAX: Operation not allowed.
 * @return: DBX_EINTERN: The C expression stack is empty. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_ref)(void) {
	struct cvalue *top;
	struct ctype *typ;
	STATIC_ASSERT_MSG(offsetof(struct cvalue, cv_addr) == offsetof(struct cvalue, cv_idata),
	                  "This is required so we don't have to copy the old address into the "
	                  "new inline-data field");
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top = &cexpr_stacktop;
	/* Make sure that the top-element is located in-memory. */
	if (top->cv_kind != CVALUE_KIND_ADDR &&
	    top->cv_kind != CVALUE_KIND_VOID)
		return DBX_ESYNTAX;
	/* Construct the pointer-type. */
	typ = ctype_ptr(&top->cv_type, dbg_current_sizeof_pointer());
	if unlikely(!typ)
		return DBX_ENOMEM;
	/* Switch over to inline-data, thus re-using the object address as the inline pointer value. */
	ctyperef_fini(&top->cv_type);
	memset(&top->cv_type, 0, sizeof(top->cv_type));
	top->cv_type.ct_typ = typ; /* Inherit reference. */
	if (top->cv_kind == CVALUE_KIND_ADDR)
		top->cv_kind = CVALUE_KIND_IDATA;
	return DBX_EOK;
}

PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_deref)(void) {
	dbx_errno_t result;
	struct cvalue *top;
	struct ctype *typ;
	byte_t *pointed_to_addr;
	/* Force an R-value expression (which we can dereference) */
	result = cexpr_rvalue();
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top = &cexpr_stacktop;
	/* Make sure that `top' has pointer typing.
	 * Note that we need to check for arrays here, since those will
	 * have already been promoted to base-pointers by `cexpr_rvalue()' */
	typ = top->cv_type.ct_typ;
	if unlikely(!CTYPE_KIND_ISPOINTER(typ->ct_kind))
		return DBX_ESYNTAX;
	switch (top->cv_kind) {

	case CVALUE_KIND_VOID:
		goto do_set_type;

	case CVALUE_KIND_IDATA:
		pointed_to_addr = *(byte_t **)top->cv_idata;
		break;

	case CVALUE_KIND_DATA:
		pointed_to_addr = *(byte_t **)top->cv_data;
		dbx_free(top->cv_data);
		break;

	default:
		return DBX_EINTERN; /* Shouldn't happen... */
	}
	/* switch back to referencing a memory location. */
	top->cv_addr = pointed_to_addr;
	top->cv_kind = CVALUE_KIND_ADDR;
	/* Replace the top item's pointer-type with the pointed-to type. */
do_set_type:
	ctypeinfo_fini(&top->cv_type.ct_info); /* inhert:`top->cv_type.ct_typ' in `typ' */
	ctyperef_initcopy(&top->cv_type, &typ->ct_pointer.cp_base);
	decref(typ);
	return DBX_EOK;
}


PRIVATE NONNULL((1)) void
NOTHROW(FCALL cvalue_setbool)(struct cvalue *__restrict self,
                              bool value) {
	assert(self->cv_kind == CVALUE_KIND_DATA ||
	       self->cv_kind == CVALUE_KIND_IDATA);
	if (self->cv_kind == CVALUE_KIND_DATA)
		dbx_free(self->cv_data);
	self->cv_kind = CVALUE_KIND_IDATA;
	memset(self->cv_idata, 0, sizeof(self->cv_idata));
	ctyperef_fini(&self->cv_type);
	memset(&self->cv_type, 0, sizeof(self->cv_type));
	self->cv_type.ct_typ    = incref(&ctype_bool);
	*(bool *)self->cv_idata = value;
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL cvalue_setptrdiff_t)(struct cvalue *__restrict self,
                                   ptrdiff_t value) {
	assert(self->cv_kind == CVALUE_KIND_DATA ||
	       self->cv_kind == CVALUE_KIND_IDATA);
	if (self->cv_kind == CVALUE_KIND_DATA)
		dbx_free(self->cv_data);
	self->cv_kind = CVALUE_KIND_IDATA;
	memset(self->cv_idata, 0, sizeof(self->cv_idata));
	ctyperef_fini(&self->cv_type);
	memset(&self->cv_type, 0, sizeof(self->cv_type));
	self->cv_type.ct_typ    = incref(&ctype_ptrdiff_t);
	*(ptrdiff_t *)self->cv_idata = value;
}


/* Perform a unary operation `op' on the top C expression stack element.
 * NOTE: This function automatically performs type promotions.
 * @param: op: One of:
 *             '+': Assert integer type / cast enum to integer.
 *             '-': Negate a value.
 *             '~': Bit-wise not.
 *             '!': Logical not.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty or invalid `op'.
 * @return: DBX_ESYNTAX: `op' not allowed here. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_op1)(unsigned int op) {
	dbx_errno_t result;
	struct cvalue *top;
	struct ctype *typ;
	byte_t *data;
	result = cexpr_promote(); /* R-value+promote */
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN; /* Shouldn't happen */
	top = &cexpr_stacktop;
	if unlikely(top->cv_kind != CVALUE_KIND_DATA &&
	            top->cv_kind != CVALUE_KIND_IDATA &&
	            top->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen */
	typ  = top->cv_type.ct_typ;
	data = top->cv_idata;
	if (top->cv_kind == CVALUE_KIND_DATA)
		data = top->cv_data;
	else if (top->cv_kind == CVALUE_KIND_VOID) {
		data = NULL;
	}
	switch (op) {

	case '+':
		if (!CTYPE_KIND_ISINT_OR_BOOL_OR_FLOAT(typ->ct_kind))
			return DBX_ESYNTAX;
		break;

	case '-': {
		if (!CTYPE_KIND_ISINT_OR_BOOL_OR_FLOAT(typ->ct_kind))
			return DBX_ESYNTAX;
		switch (CTYPE_KIND_CLASSOF(typ->ct_kind)) {

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
			/* No-op for boolean values. */
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
			/* Drop the enum-part and force signed. */
			if (CTYPE_KIND_ISENUM(typ->ct_kind))
				dw_debugloc_fini(&typ->ct_enum);
#define CTYPE_KIND_SIGNBIT (CTYPE_KIND_S8 ^ CTYPE_KIND_U8)
#define CTYPE_KIND_ENUMBIT ((CTYPE_KIND_ENUM8 & ~CTYPE_KIND_SIGNBIT) ^ (CTYPE_KIND_U8 & ~CTYPE_KIND_SIGNBIT))
			typ->ct_kind &= ~(CTYPE_KIND_SIGNBIT | CTYPE_KIND_ENUMBIT);
			/* Implement -x as `~(x - 1)' */
			if (data) {
				buffer_dec(data, CTYPE_KIND_SIZEOF(typ->ct_kind));
				buffer_inv(data, CTYPE_KIND_SIZEOF(typ->ct_kind));
			}
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_IEEE754_FLOAT):
			if (data) {
				__LONGDOUBLE ld;
				GETFLOAT_BYKIND(typ->ct_kind, data, __LONGDOUBLE, ld, return DBX_EINTERN, return DBX_EFAULT);
				ld = -ld;
				SETFLOAT_BYKIND(typ->ct_kind, data, ld, return DBX_EINTERN, return DBX_EFAULT);
			}
			break;

		default:
			return DBX_EINTERN;
		}
	}	break;

	case '~':
		if (!CTYPE_KIND_ISINT_OR_BOOL(typ->ct_kind))
			return DBX_ESYNTAX;
		if (CTYPE_KIND_ISINT(typ->ct_kind)) {
			/* Drop the enum-part and force signed. */
			if (CTYPE_KIND_ISENUM(typ->ct_kind))
				dw_debugloc_fini(&typ->ct_enum);
			typ->ct_kind &= ~(CTYPE_KIND_SIGNBIT | CTYPE_KIND_ENUMBIT);
		}
		if (data)
			buffer_inv(data, CTYPE_KIND_SIZEOF(typ->ct_kind));
		break;

	case '!':
		result = cexpr_bool();
		if unlikely(DBX_EISERR(result))
			return result;
		if (data)
			cvalue_setbool(top, !result);
		break;

	default:
		return DBX_EINTERN;
	}
	return DBX_EOK;
}

/* Perform a unary operation `op' on the top 2 C expression stack elements.
 * As far as operands go, STACK.TOP is RHS and STACK.TOP-1 is LHS (meaning
 * that LHS must be pushed first, and RHS second)
 * NOTE: This function automatically performs type promotions.
 * @param: op: One of:
 *             '+':                      Add.
 *             '-':                      Subtract.
 *             '*':                      Multiply.
 *             '/':                      Divide.
 *             '%':                      Remainder (modulo).
 *             '&':                      Bit-wise and
 *             '|':                      Bit-wise or
 *             '^':                      Bit-wise xor
 *             CTOKEN_TOK_LANGLE_LANGLE: Shift-left
 *             CTOKEN_TOK_RANGLE_RANGLE: Shift-right
 *             CTOKEN_TOK_EQUALS_EQUALS: Equals
 *             CTOKEN_TOK_XCLAIM_EQUALS: Not-Equals
 *             '<':                      Lower
 *             CTOKEN_TOK_LANGLE_EQUALS: Lower-or-equal
 *             '>':                      Greater
 *             CTOKEN_TOK_RANGLE_EQUALS: Greater-or-equal
 * @return: DBX_EOK:      Success.
 * @return: DBX_ENOMEM:   Out of memory.
 * @return: DBX_EDIVZERO: `op' is `/' or `%' and 
 * @return: DBX_EINTERN:  The stack contains less than 2 elements or invalid `op'.
 * @return: DBX_ESYNTAX:  `op' not allowed for its operands. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_op2)(unsigned int op) {
	dbx_errno_t result;
	struct cvalue *lhs, *rhs;
	struct ctype *lhs_typ, *rhs_typ;
	byte_t *lhs_data, *rhs_data;
	result = cexpr_promote(); /* R-value+promote */
	if unlikely(result != DBX_EOK)
		return result;
	result = cexpr_swap();
	if unlikely(result != DBX_EOK)
		return result;
	result = cexpr_promote(); /* R-value+promote */
	if unlikely(result != DBX_EOK)
		return result;
	result = cexpr_swap();
	if unlikely(result != DBX_EOK)
		return result;
again:
	if unlikely(cexpr_stacksize < 2)
		return DBX_EINTERN; /* Shouldn't happen */
	lhs = &cexpr_stack[cexpr_stacksize - 2];
	rhs = &cexpr_stack[cexpr_stacksize - 1];
	if unlikely(lhs->cv_kind != CVALUE_KIND_DATA &&
	            lhs->cv_kind != CVALUE_KIND_IDATA &&
	            rhs->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen */
	if unlikely(rhs->cv_kind != CVALUE_KIND_DATA &&
	            rhs->cv_kind != CVALUE_KIND_IDATA &&
	            rhs->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen */
	lhs_typ  = lhs->cv_type.ct_typ;
	rhs_typ  = rhs->cv_type.ct_typ;
	lhs_data = lhs->cv_idata;
	rhs_data = rhs->cv_idata;
	if (lhs->cv_kind == CVALUE_KIND_DATA)
		lhs_data = lhs->cv_data;
	else if (lhs->cv_kind == CVALUE_KIND_VOID) {
		lhs_data = NULL;
	}
	if (rhs->cv_kind == CVALUE_KIND_DATA)
		rhs_data = rhs->cv_data;
	else if (rhs->cv_kind == CVALUE_KIND_VOID) {
		rhs_data = NULL;
	}
	/* Swap operands such that a float always appears left. */
	if (CTYPE_KIND_ISFLOAT(lhs_typ->ct_kind)) {
		__LONGDOUBLE lhs_value, rhs_value;
		if (!rhs_data) {
			rhs_value = 0.0L;
		} else if (CTYPE_KIND_ISFLOAT(rhs_typ->ct_kind)) {
			GETFLOAT_BYKIND(rhs_typ->ct_kind, rhs_data, __LONGDOUBLE, rhs_value,
			                return DBX_EINTERN, return DBX_EFAULT);
		} else {
			if (!CTYPE_KIND_ISINT_OR_BOOL(rhs_typ->ct_kind))
				return DBX_ESYNTAX;
			if (CTYPE_KIND_ISBOOL(rhs_typ->ct_kind)) {
				rhs_value = 0.0L;
				if (buffer_istrue(rhs_data, CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)))
					rhs_value = 1.0L;
			} else {
				uintmax_t irhs_value;
				switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
				case 1: irhs_value = (*(uint8_t *)rhs_data); break;
				case 2: irhs_value = UNALIGNED_GET16((uint16_t *)rhs_data); break;
				case 4: irhs_value = UNALIGNED_GET32((uint32_t *)rhs_data); break;
				case 8: irhs_value = UNALIGNED_GET64((uint64_t *)rhs_data); break;
				default: return DBX_EINTERN;
				}
				rhs_value = (__LONGDOUBLE)irhs_value;
			}
		}
		if (lhs_data) {
			GETFLOAT_BYKIND(lhs_typ->ct_kind, lhs_data, __LONGDOUBLE, lhs_value,
			                return DBX_EINTERN, return DBX_EFAULT);
		} else {
			lhs_value = 0.0L;
		}
		switch (op) {

		case '+':
			lhs_value = lhs_value + rhs_value;
			break;

		case '-':
			lhs_value = lhs_value - rhs_value;
			break;

		case '*':
			lhs_value = lhs_value * rhs_value;
			break;

		case '/':
			/* Because of floats, divide-by-zero won't fault, but would become NaN */
			lhs_value = lhs_value / rhs_value;
			break;

		case CTOKEN_TOK_EQUALS_EQUALS:
		case CTOKEN_TOK_XCLAIM_EQUALS:
		case '<':
		case CTOKEN_TOK_LANGLE_EQUALS:
		case '>':
		case CTOKEN_TOK_RANGLE_EQUALS: {
			bool retval;
			switch (op) {
			case CTOKEN_TOK_EQUALS_EQUALS: retval = lhs_value == rhs_value; break;
			case CTOKEN_TOK_XCLAIM_EQUALS: retval = lhs_value != rhs_value; break;
			case '<': /*                */ retval = lhs_value < rhs_value; break;
			case CTOKEN_TOK_LANGLE_EQUALS: retval = lhs_value <= rhs_value; break;
			case '>': /*                */ retval = lhs_value > rhs_value; break;
			case CTOKEN_TOK_RANGLE_EQUALS: retval = lhs_value >= rhs_value; break;
			default: __builtin_unreachable();
			}
			if (lhs_data)
				cvalue_setbool(lhs, retval);
		}	break;

		case '%':
		case '&':
		case '|':
		case '^':
		case CTOKEN_TOK_LANGLE_LANGLE:
		case CTOKEN_TOK_RANGLE_RANGLE:
			return DBX_ESYNTAX;

		default:
			return DBX_EINTERN;
		}
		/* Write-back the result. */
		if (lhs_data) {
			SETFLOAT_BYKIND(lhs_typ->ct_kind, lhs_data, lhs_value,
			                return DBX_EINTERN, return DBX_EFAULT);
		}
		goto done;
	}
	if (CTYPE_KIND_ISFLOAT(rhs_typ->ct_kind)) {
		/* Cast the left operand to the type of the right one. */
		result = cexpr_swap();
		if unlikely(result != DBX_EOK)
			return result;
		result = cexpr_cast_simple(rhs_typ);
		if unlikely(result != DBX_EOK)
			return result;
swap_operands_and_again:
		result = cexpr_swap();
		if unlikely(result != DBX_EOK)
			return result;
		goto again;
	}
	/* And with that, everything relating to boolean types is off the table.
	 * Next up: Deal with pointer types. */
	if (CTYPE_KIND_ISPOINTER(lhs_typ->ct_kind)) {
		uintptr_t lhs_value, rhs_value;
		/* Only integer, bool or pointers can be used with pointers. */
		if (!CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(rhs_typ->ct_kind))
			return DBX_ESYNTAX;
		if (!lhs_data) {
			lhs_value = 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: lhs_value = *(uint8_t *)lhs_data; break;
			case 2: lhs_value = UNALIGNED_GET16((uint16_t *)lhs_data); break;
			case 4: lhs_value = UNALIGNED_GET32((uint32_t *)lhs_data); break;
			case 8: lhs_value = UNALIGNED_GET64((uint64_t *)lhs_data); break;
			default: return DBX_EINTERN;
			}
		}
		if (!rhs_data) {
			rhs_value = 0;
		} else if (CTYPE_KIND_ISBOOL(rhs_typ->ct_kind)) {
			rhs_value = buffer_istrue(rhs_data, CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) ? 1 : 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
			case 1: rhs_value = *(uint8_t *)rhs_data; break;
			case 2: rhs_value = UNALIGNED_GET16((uint16_t *)rhs_data); break;
			case 4: rhs_value = UNALIGNED_GET32((uint32_t *)rhs_data); break;
			case 8: rhs_value = UNALIGNED_GET64((uint64_t *)rhs_data); break;
			default: return DBX_EINTERN;
			}
			if (CTYPE_KIND_ISINT(rhs_typ->ct_kind) && !CTYPE_KIND_INT_ISUNSIGNED(rhs_typ->ct_kind)) {
				/* Must sign-extend loaded values */
				switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
				case 1: rhs_value = (uintmax_t)(intmax_t)(int8_t)(uint8_t)rhs_value; break;
				case 2: rhs_value = (uintmax_t)(intmax_t)(int16_t)(uint16_t)rhs_value; break;
				case 4: rhs_value = (uintmax_t)(intmax_t)(int32_t)(uint32_t)rhs_value; break;
				case 8: rhs_value = (uintmax_t)(intmax_t)(int64_t)(uint64_t)rhs_value; break;
				default: return DBX_EINTERN;
				}
			}
		}
		if (CTYPE_KIND_ISPOINTER(rhs_typ->ct_kind)) {
			/* Makre sure that pointer bases are identical. */
			if (!ctype_equal(lhs_typ->ct_pointer.cp_base.ct_typ,
			                 rhs_typ->ct_pointer.cp_base.ct_typ))
				return DBX_ESYNTAX;
			/* Only '-' and compare operators can be used with both operands are pointers. */
do_pointer_pointer_op:
			switch (op) {

			case '-': {
				size_t sizeof_base;
				sizeof_base = ctype_sizeof(lhs_typ->ct_pointer.cp_base.ct_typ);
				lhs_value -= rhs_value;
				if (sizeof_base)
					lhs_value /= sizeof_base;
				/* Write-back as a `ptrdiff_t' value. */
				cvalue_setptrdiff_t(lhs, (ptrdiff_t)lhs_value);
				goto done;
			}	break;

			case '+':
			case '*':
			case '/':
			case '%':
			case '&':
			case '|':
			case '^':
			case CTOKEN_TOK_LANGLE_LANGLE:
			case CTOKEN_TOK_RANGLE_RANGLE:
				return DBX_ESYNTAX;

			case CTOKEN_TOK_EQUALS_EQUALS:
			case CTOKEN_TOK_XCLAIM_EQUALS:
			case '<':
			case CTOKEN_TOK_LANGLE_EQUALS:
			case '>':
			case CTOKEN_TOK_RANGLE_EQUALS: {
				/* Handle the case of comparing pointers. */
				bool retval;
				if (!lhs_data)
					goto done;
				switch (op) {
				case CTOKEN_TOK_EQUALS_EQUALS: retval = lhs_value == rhs_value; break;
				case CTOKEN_TOK_XCLAIM_EQUALS: retval = lhs_value != rhs_value; break;
				case '<': /*                */ retval = lhs_value < rhs_value; break;
				case CTOKEN_TOK_LANGLE_EQUALS: retval = lhs_value <= rhs_value; break;
				case '>': /*                */ retval = lhs_value > rhs_value; break;
				case CTOKEN_TOK_RANGLE_EQUALS: retval = lhs_value >= rhs_value; break;
				default: __builtin_unreachable();
				}
				cvalue_setbool(lhs, retval);
				goto done;
			}	break;

			default:
				return DBX_EINTERN;
			}
		} else {
			switch (op) {

			case '-':
				rhs_value = 0 - rhs_value;
				ATTR_FALLTHROUGH
			case '+':
				/* Multiply `rhs_value' by the size of the underlying type of `lhs' */
				rhs_value *= ctype_sizeof(lhs_typ->ct_pointer.cp_base.ct_typ);
				lhs_value += rhs_value;
				break;

			case '*':
			case '/':
			case '%':
			case '&':
			case '|':
			case '^':
			case CTOKEN_TOK_LANGLE_LANGLE:
			case CTOKEN_TOK_RANGLE_RANGLE:
				return DBX_ESYNTAX;

			case CTOKEN_TOK_EQUALS_EQUALS:
			case CTOKEN_TOK_XCLAIM_EQUALS:
			case '<':
			case CTOKEN_TOK_LANGLE_EQUALS:
			case '>':
			case CTOKEN_TOK_RANGLE_EQUALS:
				/* Handle PTR <=> INT the same as PTR <=> PTR.
				 * Normally, C only allows this when INT is a constant
				 * literal equal to `0', but for convenience, and
				 * simplicity, we always allow such a comparison to be
				 * made. */
				goto do_pointer_pointer_op;

			default:
				return DBX_EINTERN;
			}
		}
		/* Write-back the LHS-value. */
		if (lhs_data) {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: *(uint8_t *)lhs_data = (uint8_t)lhs_value; break;
			case 2: UNALIGNED_SET16((uint16_t *)lhs_data, (uint16_t)lhs_value); break;
			case 4: UNALIGNED_SET32((uint32_t *)lhs_data, (uint32_t)lhs_value); break;
			case 8: UNALIGNED_SET64((uint64_t *)lhs_data, (uint64_t)lhs_value); break;
			default: return DBX_EINTERN;
			}
		}
		goto done;
	}
	if (CTYPE_KIND_ISPOINTER(rhs_typ->ct_kind)) {
		switch (op) {

		case '+':
			/* NON_PONITER + POINTER -> POINTER + NON_PONITER */
			goto swap_operands_and_again;

			/* We now that `lhs_typ' isn't a pointer, but `rhs_typ' is.
			 * For the comparison operators, simply flip the operands,
			 * as well as the operation so we can re-use the special
			 * handling already done when the LHS-operand is a pointer. */
		case CTOKEN_TOK_EQUALS_EQUALS:
		case CTOKEN_TOK_XCLAIM_EQUALS: goto swap_operands_and_again;
		case '<': /*                */ op = '>'; /*                */ goto swap_operands_and_again;
		case CTOKEN_TOK_LANGLE_EQUALS: op = CTOKEN_TOK_RANGLE_EQUALS; goto swap_operands_and_again;
		case '>': /*                */ op = '<'; /*                */ goto swap_operands_and_again;
		case CTOKEN_TOK_RANGLE_EQUALS: op = CTOKEN_TOK_LANGLE_EQUALS; goto swap_operands_and_again;

		case '-':
		case '*':
		case '/':
		case '%':
		case '&':
		case '|':
		case '^':
		case CTOKEN_TOK_LANGLE_LANGLE:
		case CTOKEN_TOK_RANGLE_RANGLE:
			/* None of these combinations are allowed. */
			return DBX_ESYNTAX;

		default:
			/* Bad `op' */
			return DBX_EINTERN;
		}
		__builtin_unreachable();
	}
	/* The last case: Operations with bool/integer/enum */
	if (!CTYPE_KIND_ISINT_OR_BOOL(lhs_typ->ct_kind))
		return DBX_ESYNTAX;
	if (!CTYPE_KIND_ISINT_OR_BOOL(rhs_typ->ct_kind))
		return DBX_ESYNTAX;
	{
		uintmax_t lhs_value, rhs_value;
		bool is_signed = false;
		/* Load the LHS-value. */
		if (!lhs_data) {
			lhs_value = 0;
		} else if (CTYPE_KIND_ISBOOL(lhs_typ->ct_kind)) {
			lhs_value = buffer_istrue(lhs_data, CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) ? 1 : 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: lhs_value = *(uint8_t *)lhs_data; break;
			case 2: lhs_value = UNALIGNED_GET16((uint16_t *)lhs_data); break;
			case 4: lhs_value = UNALIGNED_GET32((uint32_t *)lhs_data); break;
			case 8: lhs_value = UNALIGNED_GET64((uint64_t *)lhs_data); break;
			default: return DBX_EINTERN;
			}
			if (!CTYPE_KIND_INT_ISUNSIGNED(lhs_typ->ct_kind)) {
				/* Must sign-extend loaded values */
				switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
				case 1: lhs_value = (uintmax_t)(intmax_t)(int8_t)(uint8_t)lhs_value; break;
				case 2: lhs_value = (uintmax_t)(intmax_t)(int16_t)(uint16_t)lhs_value; break;
				case 4: lhs_value = (uintmax_t)(intmax_t)(int32_t)(uint32_t)lhs_value; break;
				case 8: lhs_value = (uintmax_t)(intmax_t)(int64_t)(uint64_t)lhs_value; break;
				default: return DBX_EINTERN;
				}
				is_signed = true;
			}
		}
		/* Load the RHS-value. */
		if (!rhs_data) {
			rhs_value = 0;
		} else if (CTYPE_KIND_ISBOOL(rhs_typ->ct_kind)) {
			rhs_value = buffer_istrue(rhs_data, CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) ? 1 : 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
			case 1: rhs_value = *(uint8_t *)rhs_data; break;
			case 2: rhs_value = UNALIGNED_GET16((uint16_t *)rhs_data); break;
			case 4: rhs_value = UNALIGNED_GET32((uint32_t *)rhs_data); break;
			case 8: rhs_value = UNALIGNED_GET64((uint64_t *)rhs_data); break;
			default: return DBX_EINTERN;
			}
			if (!CTYPE_KIND_INT_ISUNSIGNED(rhs_typ->ct_kind)) {
				/* Must sign-extend loaded values */
				switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
				case 1: rhs_value = (uintmax_t)(intmax_t)(int8_t)(uint8_t)rhs_value; break;
				case 2: rhs_value = (uintmax_t)(intmax_t)(int16_t)(uint16_t)rhs_value; break;
				case 4: rhs_value = (uintmax_t)(intmax_t)(int32_t)(uint32_t)rhs_value; break;
				case 8: rhs_value = (uintmax_t)(intmax_t)(int64_t)(uint64_t)rhs_value; break;
				default: return DBX_EINTERN;
				}
			}
		}

		/* Perform the requested operation. */
		switch (op) {

		case '+': lhs_value += rhs_value; break;
		case '-': lhs_value -= rhs_value; break;
		case '*': lhs_value *= rhs_value; break;
		case '&': lhs_value &= rhs_value; break;
		case '|': lhs_value |= rhs_value; break;
		case '^': lhs_value ^= rhs_value; break;

		case '/':
			if (!lhs_data)
				break;
			if unlikely(!rhs_value)
				return DBX_EDIVZERO;
			if (is_signed) {
				lhs_value = (uintmax_t)((intmax_t)lhs_value / rhs_value);
			} else {
				lhs_value /= rhs_value;
			}
			break;
		case '%':
			if (!lhs_data)
				break;
			if unlikely(!rhs_value)
				return DBX_EDIVZERO;
			if (is_signed) {
				lhs_value = (uintmax_t)((intmax_t)lhs_value % rhs_value);
			} else {
				lhs_value %= rhs_value;
			}
			break;

		case CTOKEN_TOK_LANGLE_LANGLE:
			lhs_value <<= rhs_value;
			break;

		case CTOKEN_TOK_RANGLE_RANGLE:
			/* Must differentiate between signed/unsigned right-shift */
			if (is_signed) {
				lhs_value = (uintmax_t)((intmax_t)lhs_value >> rhs_value);
			} else {
				lhs_value >>= rhs_value;
			}
			break;

		case CTOKEN_TOK_EQUALS_EQUALS:
		case CTOKEN_TOK_XCLAIM_EQUALS:
		case '<':
		case CTOKEN_TOK_LANGLE_EQUALS:
		case '>':
		case CTOKEN_TOK_RANGLE_EQUALS: {
			/* Handle generic compare. */
			bool retval;
			if (!lhs_data)
				goto done;
			if (op == CTOKEN_TOK_EQUALS_EQUALS)
				retval = lhs_value == rhs_value;
			else if (op == CTOKEN_TOK_XCLAIM_EQUALS)
				retval = lhs_value != rhs_value;
			else {
				/* Must account for the sign when comparing lower/greater */
				if (is_signed) {
					/* Signed compare */
					switch (op) {
					case '<': /*                */ retval = (intmax_t)lhs_value < (intmax_t)rhs_value; break;
					case CTOKEN_TOK_LANGLE_EQUALS: retval = (intmax_t)lhs_value <= (intmax_t)rhs_value; break;
					case '>': /*                */ retval = (intmax_t)lhs_value > (intmax_t)rhs_value; break;
					case CTOKEN_TOK_RANGLE_EQUALS: retval = (intmax_t)lhs_value >= (intmax_t)rhs_value; break;
					default: __builtin_unreachable();
					}
				} else {
					/* Unsigned compare */
					switch (op) {
					case '<': /*                */ retval = lhs_value < rhs_value; break;
					case CTOKEN_TOK_LANGLE_EQUALS: retval = lhs_value <= rhs_value; break;
					case '>': /*                */ retval = lhs_value > rhs_value; break;
					case CTOKEN_TOK_RANGLE_EQUALS: retval = lhs_value >= rhs_value; break;
					default: __builtin_unreachable();
					}
				}
			}
			cvalue_setbool(lhs, retval);
			goto done;
		}	break;

		default:
			return DBX_EINTERN;
		}

		/* Write-back the LHS-value. */
		if (lhs_data) {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: *(uint8_t *)lhs_data = (uint8_t)lhs_value; break;
			case 2: UNALIGNED_SET16((uint16_t *)lhs_data, (uint16_t)lhs_value); break;
			case 4: UNALIGNED_SET32((uint32_t *)lhs_data, (uint32_t)lhs_value); break;
			case 8: UNALIGNED_SET64((uint64_t *)lhs_data, (uint64_t)lhs_value); break;
			default: return DBX_EINTERN;
			}
		}
	} /* Scope... */
done:
	return cexpr_pop(); /* Pop `rhs' */
}




/* Perform an assignment operation between the top 2 stack elements,
 * where TOP is RHS, and the one before is LHS. When `cexpr_readonly'
 * is set to `true', then this function fails with `DBX_ERDONLY' */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_store)(void) {
	/* TODO: Not implemented... */
	return DBX_ENOMEM;
}

/* Pop `argc' operands, followed by popping the function to call.
 * Then, invoke the function and push its return value.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack does not contain enough elements. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_call)(size_t argc) {
	/* Not implemented... */
	(void)argc;
	return DBX_ENOMEM;
}

/* Push a currently visible symbol, as selected by the code location from
 * `dbg_current' and any possibly modifications made to `DBG_REGLEVEL_VIEW',
 * given that symbol's `name'. For this purpose, `name' can be (in order):
 *   - A function-to-compilation-unit-scoped variable/argument/enum
 *   - An PUBLIC/INTERN variable from the module containing the current PC
 * if (ADDR_ISUSER(CURRENT_PC)) {
 *   - A PUBLIC/INTERN variable from any loaded user-space module
 *   - A PUBLIC/INTERN variable from any loaded kernel-space module
 * } else {
 *   - A PUBLIC/INTERN variable from any loaded kernel-space module
 *   - A PUBLIC/INTERN variable from any loaded user-space module
 * }
 * Note that special handling is done for kernel-space PERxxx variables, which are
 * automatically linked to the associated address space for `dbg_current', such as
 * `this_task' automatically being loaded as the equivalent of `this_task@%fs_base'
 * This detection is done for all PUBLIC/INTERN+KERNEL_CORE symbols starting with
 * one of the following prefixes:
 *   - this_*      Addend is `(uintptr_t)dbg_current'
 *   - thiscpu_*   Addend is `(uintptr_t)dbg_current->t_cpu'
 *   - thisvm_*    Addend is `(uintptr_t)dbg_current->t_vm'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No object matches the given `name' */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushsymbol)(char const *__restrict name, size_t namelen) {
	dbx_errno_t result;
	struct csymbol csym;
	result = csymbol_lookup(name, namelen, &csym,
	                        CSYMBOL_SCOPE_ALL,
	                        CSYMBOL_LOOKUP_ANY);
	if (result != DBX_EOK)
		return result;
	if (csym.cs_kind == CSYMBOL_KIND_EXPR) {
		/* TODO: Special handling for this_* globals! */
		result = cexpr_pushexpr(&csym.cs_expr.e_type,
		                        &csym.cs_expr.e_expr,
		                        ctype_sizeof(csym.cs_expr.e_type.ct_typ),
		                        0);
	} else {
		result = DBX_ENOENT;
	}
	csymbol_fini(&csym);
	return result;
}

/* Push a register with its native typing, given its `name'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No register matches the given `name' */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushregister)(char const *__restrict name, size_t namelen) {
	unsigned int regno;
	regno = arch_dbg_regfromname(name, namelen);
	if (regno == ARCH_REGISTER_NONE)
		return DBX_ENOENT;
	return cexpr_pushregister_by_id(regno);
}



DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CEXPR_C */
