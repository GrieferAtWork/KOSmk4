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
#ifndef _KOS_BITS_PROCESS_H
#define _KOS_BITS_PROCESS_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <hybrid/__byteorder.h>
#include <elf.h>

#ifndef ELF_HOST_ISVALID_CLASS
#ifndef ELF_HOST_REQUIRED_CLASS
#if __SIZEOF_POINTER__ > 4
#define ELF_HOST_REQUIRED_CLASS      ELFCLASS64
#define ELF_HOST_REQUIRED_CLASS_S   "ELFCLASS64"
#else /* __SIZEOF_POINTER__ > 4 */
#define ELF_HOST_REQUIRED_CLASS      ELFCLASS32
#define ELF_HOST_REQUIRED_CLASS_S   "ELFCLASS32"
#endif /* __SIZEOF_POINTER__ <= 4 */
#endif /* !ELF_HOST_REQUIRED_CLASS */
#define ELF_HOST_ISVALID_CLASS(x)   ((x) == ELF_HOST_REQUIRED_CLASS)
#endif /* !ELF_HOST_ISVALID_CLASS */

#ifndef ELF_HOST_ISVALID_DATA
#ifndef ELF_HOST_REQUIRED_DATA
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define ELF_HOST_REQUIRED_DATA       ELFDATA2LSB
#define ELF_HOST_REQUIRED_DATA_S    "ELFDATA2LSB"
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define ELF_HOST_REQUIRED_DATA       ELFDATA2MSB
#define ELF_HOST_REQUIRED_DATA_S    "ELFDATA2MSB"
#else /* ... */
#error "Unsupported endian"
#endif/* !... */
#endif /* !ELF_HOST_REQUIRED_DATA */
#define ELF_HOST_ISVALID_DATA(x)    ((x) == ELF_HOST_REQUIRED_DATA)
#endif /* !ELF_HOST_ISVALID_DATA */

#ifndef ELF_HOST_ISVALID_MACHINE
#ifdef ELF_HOST_REQUIRED_MACHINE
#define ELF_HOST_ISVALID_MACHINE(x)   ((x) == ELF_HOST_REQUIRED_MACHINE)
#else /* ELF_HOST_REQUIRED_MACHINE */
#define ELF_HOST_ISVALID_MACHINE(x)   0
#endif /* !ELF_HOST_REQUIRED_MACHINE */
#endif /* !ELF_HOST_ISVALID_MACHINE */

#ifndef ELF_HOST_MAXPROGRAMHEADERCOUNT
#define ELF_HOST_MAXPROGRAMHEADERCOUNT 64
#endif /* !ELF_HOST_MAXPROGRAMHEADERCOUNT */

#endif /* !_KOS_BITS_PROCESS_H */
