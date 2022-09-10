/* HASH CRC-32:0x32d97f97 */
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
#ifndef GUARD_LIBC_AUTO_ATTR_ATTRIBUTES_C
#define GUARD_LIBC_AUTO_ATTR_ATTRIBUTES_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/attr.attributes.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <attr/bits/attributes.h>
#include <libc/errno.h>
#include <attr/asm/attributes.h>
INTERN ATTR_SECTION(".text.crt.libattr") int
NOTHROW_NCX(LIBCCALL libc_attr_multi)(char const *path,
                                      struct attr_multiop *oplist,
                                      int count,
                                      int flags) {
	int i, result = 0;
	if unlikely(flags & ~ATTR_DONTFOLLOW) {

		return __libc_seterrno(EINVAL);



	}
	for (i = 0; i < count; ++i) {
		struct attr_multiop *ent = &oplist[i];
		int ent_flags = ent->am_flags | flags;
		switch (ent->am_opcode) {

		case ATTR_OP_GET:
			result |= libc_attr_get(path,
			                   ent->am_attrname,
			                   ent->am_attrvalue,
			                   &ent->am_length,
			                   ent_flags);
			break;

		case ATTR_OP_SET:
			result |= libc_attr_set(path,
			                   ent->am_attrname,
			                   ent->am_attrvalue,
			                   ent->am_length,
			                   ent_flags);
			break;

		case ATTR_OP_REMOVE:
			result |= libc_attr_remove(path,
			                      ent->am_attrname,
			                      ent_flags);
			break;

		default:

			result = __libc_seterrno(EINVAL);



			break;
		}
	}
	return result;
}
#include <attr/bits/attributes.h>
#include <libc/errno.h>
#include <attr/asm/attributes.h>
INTERN ATTR_SECTION(".text.crt.libattr") int
NOTHROW_NCX(LIBCCALL libc_attr_multif)(fd_t fd,
                                       struct attr_multiop *oplist,
                                       int count,
                                       int flags) {
	int i, result = 0;
	if unlikely(flags & ~ATTR_DONTFOLLOW) {

		return __libc_seterrno(EINVAL);



	}
	for (i = 0; i < count; ++i) {
		struct attr_multiop *ent = &oplist[i];
		int ent_flags = ent->am_flags | flags;
		switch (ent->am_opcode) {

		case ATTR_OP_GET:
			result |= libc_attr_getf(fd,
			                    ent->am_attrname,
			                    ent->am_attrvalue,
			                    &ent->am_length,
			                    ent_flags);
			break;

		case ATTR_OP_SET:
			result |= libc_attr_setf(fd,
			                    ent->am_attrname,
			                    ent->am_attrvalue,
			                    ent->am_length,
			                    ent_flags);
			break;

		case ATTR_OP_REMOVE:
			result |= libc_attr_removef(fd,
			                       ent->am_attrname,
			                       ent_flags);
			break;

		default:

			result = __libc_seterrno(EINVAL);



			break;
		}
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(attr_multi, libc_attr_multi);
DEFINE_PUBLIC_ALIAS(attr_multif, libc_attr_multif);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ATTR_ATTRIBUTES_C */
