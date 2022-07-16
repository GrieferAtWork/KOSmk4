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
#ifndef GUARD_MODSHEBANG_SHEBANG_H
#define GUARD_MODSHEBANG_SHEBANG_H 1

#include <kernel/compiler.h>

#include <kernel/execabi.h>
#include <kernel/types.h>

DECL_BEGIN

/*[[[config CONFIG_MODSHEBANG_INTERPRETER_LINEMAX! = 1024
 * Max # of bytes from the  start of an executable file,  to
 * immediately after the line-feed following the first line.
 *
 * If more bytes than this amount appear in the  first
 * line (not counting the leading #!), exec will  fail
 * with `E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_TRUNC'
 * ]]]*/
#ifndef CONFIG_MODSHEBANG_INTERPRETER_LINEMAX
#define CONFIG_MODSHEBANG_INTERPRETER_LINEMAX 1024
#endif /* !CONFIG_MODSHEBANG_INTERPRETER_LINEMAX */
/*[[[end]]]*/

/* ABI exec function for #! */
INTDEF WUNUSED NONNULL((1)) unsigned int FCALL
shebang_exec(struct execargs *__restrict args);

/* ExecABI initializer for #! */
#define EXECABI_INIT_SHEBANG        \
	{                               \
		.ea_driver = &drv_self,     \
		.ea_magsiz = 2,             \
		.ea_magic  = { '#', '!' },  \
		.ea_exec   = &shebang_exec, \
	}


DECL_END

#endif /* !GUARD_MODSHEBANG_SHEBANG_H */
