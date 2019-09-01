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


%[default_impl_section(.text.crt.system.reboot)]

%{

__SYSDECL_BEGIN

/* Linux compatibility header */
#define RB_AUTOBOOT    0x01234567 /* Do a hard reset immediately. */
#define RB_HALT_SYSTEM 0xcdef0123 /* Halt the system. */
#define RB_ENABLE_CAD  0x89abcdef /* Enable reboot with Ctrl-Alt-Delete. */
#define RB_DISABLE_CAD 0          /* Disable reboot with Ctrl-Alt-Delete. */
#define RB_POWER_OFF   0x4321fedc /* halt and switch off power (if possible). */
#define RB_SW_SUSPEND  0xd000fce2 /* Suspend the system using a software suspend. */
#define RB_KEXEC       0x45584543 /* Reboot into new kernel (not supported currently). */

#ifdef __CC__

}

@@Reboot or halt the system
@@@param: howto: One of the `RB_*' constants above
reboot:(int howto) -> int;

%{

#endif /* __CC__ */

__SYSDECL_END

}