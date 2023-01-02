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
#ifndef GUARD_MODDBX_INCLUDE_CEVAL_H
#define GUARD_MODDBX_INCLUDE_CEVAL_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <kernel/types.h>

/**/
#include "error.h"

DECL_BEGIN

struct ctype;
struct cparser;

/* Set to  true if  the `,'-operator  should be  interpreted as  it is  in
 * regular C, meaning that it is used to simply select the second operand.
 *
 * When set to `false' (which is the default) then the `,'-operator is used
 * to implement a  cast-to-array behavior, where  the LHS-operator is  then
 * expected to be a pointer:
 * >> &foo, 12
 *
 * Evaluated as:
 * >> *(typeof(foo)(*)[12])&foo
 *
 * Not that while parsing an expression within parenthesis,
 * this option is always set to `true':
 * >> (&foo, 12)
 * Always parsed as:
 * >> 12
 */
DATDEF __BOOL ceval_comma_is_select2nd;


/* Parse a  C-expression  from  `self'  and  push  its  value
 * onto the C-expression  stack, return  DBX_EOK on  success,
 * and a potential  error otherwise (in  the later case,  the
 * effective  size  of  the  C-expression  stack  will remain
 * unaltered). NOTE: The given `self' is expected to  already
 * point to the first token apart of the expression on entry. */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushparse)(struct cparser *__restrict self);

/* Light-weight wrapper around `cexpr_pushparse()', and also
 * the top-level function used for evaluating C expressions.
 * @param: expr:     The C expression that should be parsed.
 * @param: maxlen:   The max length of `expr' (actual length is `strnlen(expr, maxlen)')
 * @return: DBX_EOK: Success
 * @return: * :      Error (the effective c-expression-stack-size is unaltered) */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pusheval)(char const *__restrict expr,
                              size_t maxlen DFL((size_t)-1));

/* Parse a named type from  `self'. This function expects  that
 * `self' points at the first token of the named type on entry.
 * @return: presult:      Filled with the name type that was parsed (token from
 *                        `self' were yielded, and not point to the first token
 *                        after the returned type)
 * @param: p_varname:     When non-NULL, also parse a contained variable name, and
 *                        store its location here. If no variable name is defined,
 *                        but this argument is non-NULL, then NULL will be written
 *                        here. When `NULL', a potential variable name will not be
 *                        parsed, and if present, will result in `DBX_ESYNTAX'.
 * @param: p_varname_len: When non-NULL, store  the length of  `*p_varname' here,  but
 *                        only do so if `p_varname != NULL'. When `p_varname' is given
 *                        as `NULL', then this argument is simply ignored.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_ENOENT:  `self' does not refer to a named type.
 * @return: DBX_ESYNTAX: Syntax error. */
FUNDEF WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_eval)(struct cparser *__restrict self,
                          /*out:ref*/ struct ctyperef *__restrict presult,
                          char const **p_varname, size_t *p_varname_len);

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CEVAL_H */
