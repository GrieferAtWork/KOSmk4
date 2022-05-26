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
#ifndef GUARD_MODDBX_INCLUDE_CEXPR_H
#define GUARD_MODDBX_INCLUDE_CEXPR_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <kernel/types.h>

#include <hybrid/typecore.h>

#include <kos/exec/module.h>

#include <libc/string.h>
#include <libdebuginfo/debug_info.h>

/**/
#include "cmodule.h"
#include "cparser.h"
#include "ctype.h"
#include "error.h"

DECL_BEGIN

#define CVALUE_INLINE_MAXSIZE 16 /* Max buffer size for in-line R-value data. */

#define CVALUE_KIND_VOID     0 /* No value */
#define CVALUE_KIND_ADDR     1 /* L-value: Value is stored in-memory */
#define CVALUE_KIND_EXPR     2 /* LR-value: Value uses a custom CFI expression */
#define CVALUE_KIND_IEXPR    3 /* LR-value: Value uses a custom CFI expression (with an in-line buffer) */
#define CVALUE_KIND_REGISTER 4 /* LR-value: Register */
#define CVALUE_KIND_DATA     5 /* R-value: Value is stored in-line. */
#define CVALUE_KIND_IDATA    6 /* R-value: Value is stored in-line. */

struct cvalue_cfiexpr {
	REF struct cmodule     *v_module;            /* [0..1] Debug-info for `v_expr' */
	di_debuginfo_location_t v_expr;              /* CFI expression. */
	di_debuginfo_location_t v_framebase;         /* Frame-base expression. */
	uintptr_t               v_cu_ranges_startpc; /* == di_debuginfo_compile_unit_t::cu_ranges::r_startpc */
	uintptr_t               v_cu_addr_base;      /* == di_debuginfo_compile_unit_t::cu_addr_base */
	uint8_t                 v_addrsize;          /* == di_debuginfo_cu_simple_parser_t::dsp_addrsize */
	uint8_t                 v_ptrsize;           /* == di_debuginfo_cu_simple_parser_t::dsp_ptrsize */
	void                   *v_objaddr;           /* [0..1] Object address. */
};


#define cvalue_cfiexpr_fini(self) \
	(xdecref((self)->v_module))
#define cvalue_cfiexpr_initcopy(self, src)                          \
	(void)(__libc_memcpy(self, src, sizeof(struct cvalue_cfiexpr)), \
	       xincref((src)->v_module))

/* Read/write the value of the given CFI expression to/from buf.
 * @return: DBX_EOK:     Success.
 * @return: DBX_EFAULT:  Faulty memory location accessed.
 * @return: DBX_EINTERN: Internal error. */
FUNDEF NONNULL((1, 2)) dbx_errno_t
NOTHROW(KCALL cvalue_cfiexpr_readwrite)(struct cvalue_cfiexpr const *__restrict self,
                                        void *buf, size_t buflen, bool write);

/* Lookup a C-Value CFI expression, given the name of a local/global variable. */
FUNDEF NONNULL((1, 2)) dbx_errno_t
NOTHROW(KCALL cvalue_cfiexpr_byname)(/*out*/ struct cvalue_cfiexpr *__restrict self,
                                     char const *__restrict name, size_t namelen);



struct cvalue {
	struct ctyperef cv_type; /* Value type. */
	uintptr_t       cv_kind; /* Value kind (one of `CVALUE_KIND_*') */
	union {
		void   *cv_addr;                         /* [valid_if(CVALUE_KIND_ADDR)] In-memory address of this value. */
		byte_t *cv_data;                         /* [valid_if(CVALUE_KIND_DATA)][1..1][owned] In-line data. */
		byte_t  cv_idata[CVALUE_INLINE_MAXSIZE]; /* [valid_if(CVALUE_KIND_IDATA)] In-line data. */

		struct {
			struct cvalue_cfiexpr   v_expr;   /* CFI expression. */
			size_t                  v_buflen; /* Buffer length */
			size_t                  v_bufoff; /* Offset into `v_buffer' */
			union {
				void               *v_buffer; /* [0..v_buflen][owned] Lazily allocated expression data-buffer. */
				byte_t              v_ibuffer[sizeof(void *)]; /* [valid_if(CVALUE_KIND_IEXPR)] In-line buffer. */
			};
		}            cv_expr;     /* [valid_if(CVALUE_KIND_EXPR | CVALUE_KIND_IEXPR)] CFI expression. */
		struct {
			unsigned int r_regid;                          /* Arch-specific register index. */
			size_t       r_buflen;                         /* Buffer length. */
			byte_t       r_ibuffer[CVALUE_INLINE_MAXSIZE]; /* In-line buffer. */
		} cv_register; /* [valid_if(CVALUE_KIND_REGISTER)] Register. */
	};
};

/* Finalize the given C-value. */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL cvalue_fini)(struct cvalue *__restrict self);

/* Write-back changes made by `self'
 * @return: DBX_EOK:     Success.
 * @return: DBX_EFAULT:  Faulty memory access.
 * @return: DBX_EINTERN: Internal error. */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cvalue_flush)(struct cvalue *__restrict self);

/* Initialize a copy `self' of the given C-value `src'.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
FUNDEF WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cvalue_initcopy)(struct cvalue *__restrict self,
                               struct cvalue const *__restrict src);


/* [1..cexpr_stacksize] Stack of currently pushed C-values. (see the below API) */
DATDEF struct cvalue *cexpr_stack;
DATDEF struct cvalue cexpr_stack_stub[1]; /* Stub-stack */

/* # of used stack entries */
DATDEF size_t cexpr_stacksize;

/* Return the current stack-top element. If the stack is otherwise empty,
 * then this will  instead return a  stub-void expression, ala  `(void)0' */
#define cexpr_stacktop cexpr_stack[cexpr_stacksize - 1]

/* When true, only allow read-only C expression operations.
 * During a debugger reset, this option is reset to `false' */
DATDEF __BOOL cexpr_readonly;

/* Don't calculate/keep track of c expression values, but
 * only simulate the effective expression type. - Used to
 * implement `typeof()' in C expressions, as well as  for
 * the  purpose of auto-completion of struct member names
 * and the like. */
DATDEF __BOOL cexpr_typeonly;

/* Set  to  true  if  memory  writes  should  be   forced.
 * This is the 4'th argument in calls to dbg_writememory()
 * Defaults to `false' */
DATDEF __BOOL cexpr_forcewrite;


/* Push an element into the C-expression stack.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
FUNDEF NONNULL((1)) dbx_errno_t /* Push `*(typ *)addr' */
NOTHROW(FCALL cexpr_pushaddr)(struct ctyperef const *__restrict typ, USER void *addr);
FUNDEF NONNULL((1, 2)) dbx_errno_t /* Push a CFI expression. */
NOTHROW(FCALL cexpr_pushexpr)(struct ctyperef const *__restrict typ,
                              struct cvalue_cfiexpr const *__restrict expr,
                              size_t buflen, size_t bufoff);
FUNDEF NONNULL((1, 2)) dbx_errno_t /* Push `(typ)(*(typ const *)data)' */
NOTHROW(FCALL cexpr_pushdata)(struct ctyperef const *__restrict typ,
                              void const *__restrict data);
FUNDEF NONNULL((1)) dbx_errno_t /* Push `(typ)value' */
NOTHROW(FCALL cexpr_pushint)(struct ctyperef const *__restrict typ,
                             __UINTMAX_TYPE__ value);

/* Push a register, given its arch-specific ID, automatically selecting a proper type.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No such register. */
FUNDEF dbx_errno_t /* Push `(auto)%[reg:id]' */
NOTHROW(FCALL cexpr_pushregister_by_id)(unsigned int id);

/* Same as above, but only require basic typ
 * information (typ flags, and name are pushed as 0/NULL) */
FUNDEF NONNULL((1)) dbx_errno_t /* Push `*(typ *)addr' */
NOTHROW(FCALL cexpr_pushaddr_simple)(struct ctype *__restrict typ, USER void *addr);
FUNDEF NONNULL((1, 2)) dbx_errno_t /* Push `(typ)(*(typ const *)data)' */
NOTHROW(FCALL cexpr_pushdata_simple)(struct ctype *__restrict typ,
                                     void const *__restrict data);
FUNDEF NONNULL((1)) dbx_errno_t /* Push `(typ)value' */
NOTHROW(FCALL cexpr_pushint_simple)(struct ctype *__restrict typ,
                                    __UINTMAX_TYPE__ value);
#define cexpr_pushvoid() cexpr_pushaddr_simple(&ctype_void, __NULLPTR)


/* Pop the top element from the C expression stack.
 * @return: DBX_EOK:     Success.
 * @return: DBX_EINTERN: Stack was already empty. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_pop)(void);

/* Clear the C expression stack. */
FUNDEF void NOTHROW(FCALL cexpr_empty)(void);

/* Duplicate the C expression top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_dup)(void);

/* Swap the two 2 c expression stack elements.
 * @return: DBX_EOK:     Success
 * @return: DBX_EINTERN: The stack size is < 2 */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_swap)(void);

/* Rotate the top n c expression stack elements left/right.
 * When  `n <= 1', these  calls are  a no-op  in regards to
 * @return: DBX_EOK:     Success
 * @return: DBX_EINTERN: The stack size is < n */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_lrot)(unsigned int n);
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_rrot)(unsigned int n);

/* Return a pointer to the data associated with the top expression stack  element.
 * If the stack is empty or `cexpr_typeonly' is `true', write-back a NULL pointer.
 * WARNING: The pointer written back to `*presult' may point to arbitrary
 *          user- or out-of-mman memory, meaning that it must be accessed
 *          through use of `dbg_(read|write)memory'!
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Insufficient memory to allocate an intermediate buffer.
 * @return: DBX_EFAULT:  A CFI expression caused a memory fault.
 * @return: DBX_EINTERN: Internal error. */
FUNDEF WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_getdata)(byte_t **__restrict presult);

/* Return the actual size of the top element of the C expression stack.
 * If the stack is empty,  return `0' instead. (s.a.  `ctype_sizeof()') */
FUNDEF ATTR_PURE WUNUSED size_t NOTHROW(FCALL cexpr_getsize)(void);

/* Return the boolean value of the top stack element.
 * When `cexpr_typeonly' is set to true, this function's return value is undefined.
 * @return: 1:           Value is true.
 * @return: 0:           Value is false.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: The top stack element cannot be cast to bool. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_bool)(void);

/* Cast the stack-top element to `typ'.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: The top stack element cannot be cast to `typ'. */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cast)(struct ctyperef const *__restrict typ);
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cast_simple)(struct ctype *__restrict typ);

/* Convert  the  top C  expression  stack element  into  an R-value,
 * such that if a potentially pointed-to memory location is changed,
 * then the stack element retains the original value. This  function
 * also promotes array->pointer types.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: Attempted to promote an address-less array to a pointer. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_rvalue)(void);

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
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_promote)(void);

/* Access a field of a struct/union object in the C expression stack top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The C expression stack is empty.
 * @return: DBX_ESYNTAX: The C expression stack top-element isn't a struct/union.
 * @return: DBX_ENOENT:  The given `name' doesn't name a member of the top-element struct. */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_field)(char const *__restrict name, size_t namelen);

/* Ref/Deref the c-expression-stack top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_ESYNTAX: Operation not allowed.
 * @return: DBX_ENOADDR: Cannot take address of optimized variable.
 * @return: DBX_EINTERN: The C expression stack is empty. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_ref)(void);   /* Implements `&' */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_deref)(void); /* Implements `*' */

/* Perform a unary operation `op' on the top C expression stack element.
 * NOTE: This   function   automatically   performs   type   promotions.
 * @param: op: One of:
 *             '+': Assert integer type / cast enum to integer.
 *             '-': Negate a value.
 *             '~': Bit-wise not.
 *             '!': Logical  not.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty or invalid `op'.
 * @return: DBX_EINTERN: `op' is not one of the above constants.
 * @return: DBX_ESYNTAX: `op' not allowed here. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_op1)(unsigned int op);

/* Perform a binary operation `op' on the top 2 C expression stack elements.
 * As  far as operands go, STACK.TOP is  RHS and STACK.TOP-1 is LHS (meaning
 * that LHS must be pushed first, and RHS second)
 * NOTE: This function automatically performs type promotions.
 * @param: op: One of:
 *             '+':                      Add.
 *             '-':                      Subtract.
 *             '*':                      Multiply.
 *             '/':                      Divide.
 *             '%':                      Remainder (modulo).
 *             '&':                      Bit-wise        and
 *             '|':                      Bit-wise         or
 *             '^':                      Bit-wise        xor
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
 * @return: DBX_EDIVZERO: `op' is `/' or `%' and the rhs-operand is equal to 0
 * @return: DBX_EINTERN:  The stack contains less than 2 elements or invalid `op'.
 * @return: DBX_EINTERN:  `op' is not one of the above constants.
 * @return: DBX_ESYNTAX:  `op' not allowed for its operands. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_op2)(unsigned int op);

/* Perform an assignment operation between the top 2 stack  elements,
 * where TOP is RHS, and the one before is LHS. When `cexpr_readonly'
 * is set to `true', then this function fails with `DBX_ERDONLY' */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_store)(void);

/* Pop `argc' operands, followed by popping the function to call.
 * Then,  invoke  the  function   and  push  its  return   value.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack does not contain enough elements. */
FUNDEF dbx_errno_t NOTHROW(FCALL cexpr_call)(size_t argc);

/* Push  a currently visible  symbol, as selected by  the code location from
 * `dbg_current' and any possibly modifications made to `DBG_REGLEVEL_VIEW',
 * given that symbol's `name'. For this  purpose, `name' can be (in  order):
 *   - A function-to-compilation-unit-scoped variable/argument/enum
 *   - A PUBLIC/INTERN variable from the module containing the current PC
 * if (ADDR_ISUSER(CURRENT_PC)) {
 *   - A PUBLIC/INTERN variable from any loaded user-space module
 *   - A PUBLIC/INTERN variable from any loaded kernel-space module
 * } else {
 *   - A PUBLIC/INTERN variable from any loaded kernel-space module
 *   - A PUBLIC/INTERN variable from any loaded user-space module
 * }
 * Note that special handling is done for kernel-space PERxxx variables, which  are
 * automatically  linked to the associated address space for `dbg_current', such as
 * `this_task' automatically being loaded as the equivalent of `this_task@%fs_base'
 * This detection is done for  all PUBLIC/INTERN+KERNEL_CORE symbols starting  with
 * one of the following prefixes:
 *   - this_*      Addend is `(uintptr_t)dbg_current'
 *   - thiscpu_*   Addend is `(uintptr_t)dbg_current->t_cpu'
 *   - thisvm_*    Addend is `(uintptr_t)dbg_current->t_mman'
 * @param: automatic_symbol_addend: When  set to `false', do include automatic symbol
 *                                  addend for special this_* namespaces (s.a. above)
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No object matches the given `name' */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushsymbol)(struct cmodsyminfo *__restrict sym,
                                __BOOL automatic_symbol_addend DFL(1));
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushsymbol_byname)(char const *__restrict name, size_t namelen,
                                      __BOOL automatic_symbol_addend DFL(1));

/* Push a register with its native typing, given its `name'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No register matches the given `name' */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushregister)(char const *__restrict name, size_t namelen);

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CEXPR_H */
