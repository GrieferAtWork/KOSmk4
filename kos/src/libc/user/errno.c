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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ERRNO_C
#define GUARD_LIBC_USER_ERRNO_C 1

#include "../api.h"
/**/

#include "errno.h"

DECL_BEGIN


#undef program_invocation_short_name
DEFINE_NOREL_GLOBAL_META(char *, program_invocation_short_name, ".crt.errno.utility");
#define program_invocation_short_name GET_NOREL_GLOBAL(program_invocation_short_name)



/*[[[start:implementation]]]*/

/*[[[skip:__errno_location]]]*/

/*[[[head:__p_program_invocation_short_name,hash:CRC-32=0x2a911ebc]]]*/
/* Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.errno.utility.__p_program_invocation_short_name") char **
NOTHROW_NCX(LIBCCALL libc___p_program_invocation_short_name)(void)
/*[[[body:__p_program_invocation_short_name]]]*/
{
	return &program_invocation_short_name;
}
/*[[[end:__p_program_invocation_short_name]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x2ec9f144]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(__p_program_invocation_short_name, libc___p_program_invocation_short_name);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ERRNO_C */
