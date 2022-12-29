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
#ifndef GUARD_LIBC_USER_CTHREADS_C
#define GUARD_LIBC_USER_CTHREADS_C 1

#include "../api.h"
/**/

#include "cthreads.h"

DECL_BEGIN

/*[[[head:libc_cond_signal,hash:CRC-32=0xe00e4fe3]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") int
NOTHROW_NCX(LIBCCALL libc_cond_signal)(condition_t self)
/*[[[body:libc_cond_signal]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("cond_signal(self: %p)", self); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_cond_signal]]]*/

/*[[[head:libc_cond_broadcast,hash:CRC-32=0xf93317c3]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_cond_broadcast)(condition_t self)
/*[[[body:libc_cond_broadcast]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("cond_broadcast(self: %p)", self); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_cond_broadcast]]]*/

/*[[[head:libc_condition_wait,hash:CRC-32=0x2c0bb692]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_condition_wait)(condition_t self,
                                          mutex_t mutex)
/*[[[body:libc_condition_wait]]]*/
/*AUTO*/{
	(void)self;
	(void)mutex;
	CRT_UNIMPLEMENTEDF("condition_wait(self: %p, mutex: %p)", self, mutex); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_condition_wait]]]*/


/*[[[head:libc_condition_implies,hash:CRC-32=0x16aae42d]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_condition_implies)(condition_t implicator,
                                             condition_t implicatand)
/*[[[body:libc_condition_implies]]]*/
/*AUTO*/{
	(void)implicator;
	(void)implicatand;
	CRT_UNIMPLEMENTEDF("condition_implies(implicator: %p, implicatand: %p)", implicator, implicatand); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_condition_implies]]]*/

/*[[[head:libc_condition_unimplies,hash:CRC-32=0x5166a61d]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_condition_unimplies)(condition_t implicator,
                                               condition_t implicatand)
/*[[[body:libc_condition_unimplies]]]*/
/*AUTO*/{
	(void)implicator;
	(void)implicatand;
	CRT_UNIMPLEMENTEDF("condition_unimplies(implicator: %p, implicatand: %p)", implicator, implicatand); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_condition_unimplies]]]*/

/*[[[head:libc_cthread_sp,hash:CRC-32=0x6b62e437]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") vm_offset_t
NOTHROW_NCX(LIBCCALL libc_cthread_sp)(void)
/*[[[body:libc_cthread_sp]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("cthread_sp"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_cthread_sp]]]*/

/*[[[head:libc_ur_cthread_self,hash:CRC-32=0x97ca6daa]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ur_cthread_t
NOTHROW_NCX(LIBCCALL libc_ur_cthread_self)(void)
/*[[[body:libc_ur_cthread_self]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("ur_cthread_self"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_ur_cthread_self]]]*/

/*[[[head:libc_cthread_name,hash:CRC-32=0x6a3913d0]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ATTR_IN(1) char const *
NOTHROW_NCX(LIBCCALL libc_cthread_name)(cthread_t self)
/*[[[body:libc_cthread_name]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("cthread_name(self: %p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_cthread_name]]]*/

/*[[[head:libc_cthread_count,hash:CRC-32=0xbf5f5753]]]*/
/* >> cthread_count(3)
 * Return the number of running threads (s.a. `DLAUXCTRL_GET_MAIN_TLSSEG') */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") int
NOTHROW_NCX(LIBCCALL libc_cthread_count)(void)
/*[[[body:libc_cthread_count]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("cthread_count"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_cthread_count]]]*/

/*[[[head:libc_cthread_set_data,hash:CRC-32=0x696ab4e3]]]*/
/* >> cthread_set_data(3)
 * Set the value of a TLS variable for `self' */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ATTR_ACCESS_NONE(2) int
NOTHROW_NCX(LIBCCALL libc_cthread_set_data)(cthread_t self,
                                            void *value)
/*[[[body:libc_cthread_set_data]]]*/
/*AUTO*/{
	(void)self;
	(void)value;
	CRT_UNIMPLEMENTEDF("cthread_set_data(self: %p, value: %p)", self, value); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_cthread_set_data]]]*/

/*[[[head:libc_cthread_data,hash:CRC-32=0xb7359d0e]]]*/
/* >> cthread_data(3)
 * Get the value of a TLS variable for `self' */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void *
NOTHROW_NCX(LIBCCALL libc_cthread_data)(cthread_t self)
/*[[[body:libc_cthread_data]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("cthread_data(self: %p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_cthread_data]]]*/

/*[[[start:exports,hash:CRC-32=0x986f97a6]]]*/
DEFINE_PUBLIC_ALIAS(cond_signal, libc_cond_signal);
DEFINE_PUBLIC_ALIAS(cond_broadcast, libc_cond_broadcast);
DEFINE_PUBLIC_ALIAS(condition_wait, libc_condition_wait);
DEFINE_PUBLIC_ALIAS(condition_implies, libc_condition_implies);
DEFINE_PUBLIC_ALIAS(condition_unimplies, libc_condition_unimplies);
DEFINE_PUBLIC_ALIAS(cthread_sp, libc_cthread_sp);
DEFINE_PUBLIC_ALIAS(ur_cthread_self, libc_ur_cthread_self);
DEFINE_PUBLIC_ALIAS(cthread_name, libc_cthread_name);
DEFINE_PUBLIC_ALIAS(cthread_count, libc_cthread_count);
DEFINE_PUBLIC_ALIAS(cthread_set_data, libc_cthread_set_data);
DEFINE_PUBLIC_ALIAS(cthread_data, libc_cthread_data);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CTHREADS_C */
