/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_KERNEL_INCLUDE_DEV_ANSITTY_H
#define GUARD_KERNEL_INCLUDE_DEV_ANSITTY_H 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <dev/char.h>
#include <libansitty/ansitty.h>
#include <misc/atomic-ref.h>

DECL_BEGIN

#ifdef __CC__


struct ansitty_device
#ifdef __cplusplus
	: character_device
#endif
{
#ifndef __cplusplus
	struct character_device              at_cdev; /* The underling character-device */
#endif
	struct ansitty                       at_ansi; /* Ansi TTY support. */
	XATOMIC_WEAKLYREF(struct tty_device) at_tty;  /* [0..1] Weak reference to a connected TTY (used for injecting keyboard input) */
};
DEFINE_REFCOUNT_TYPE_SUBCLASS(ansitty_device, character_device);

#define character_device_isanansitty(self)                   \
	((self)->cd_heapsize >= sizeof(struct ansitty_device) && \
	 (self)->cd_type.ct_write == &ansitty_device_write)

FUNDEF NONNULL((1)) size_t KCALL
ansitty_device_write(struct character_device *__restrict self,
                     USER CHECKED void const *src,
                     size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL
ansitty_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                     USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
#define ansitty_device_fini(self) (void)0 /* For now... */


/* Initialize a given ansitty device.
 * NOTE: `ops->ato_output' must be set to NULL when calling this function.
 *       The internal routing of this callback to injecting keyboard output
 *       is done dynamically when the ANSI TTY is connected to the output
 *       channel of a `struct tty'
 * This function initializes the following operators:
 *   - cd_type.ct_write = &ansitty_device_write;  // Mustn't be re-assigned!
 *   - cd_type.ct_fini  = &ansitty_device_fini;   // Must be called by an override
 *   - cd_type.ct_ioctl = &ansitty_device_ioctl;  // Must be called by an override */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL ansitty_device_cinit)(struct ansitty_device *__restrict self,
                                    struct ansitty_operators const *__restrict ops);


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_ANSITTY_H */
