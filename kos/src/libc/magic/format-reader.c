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

%[define_replacement(pformatreader = __pformatreader)]

%[default_impl_section(.text.crt.string.format)]

%{
#include <features.h>
#include <bits/format-printer.h>


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __pformatreader_defined
#define __pformatreader_defined 1
/* Callback function for custom data providers, to-be used by data consumers.
 * @param: BUF:       The base address of a `NUM_BYTES' bytes long vector that should be filled.
 * @param: NUM_BYTES: The max number of bytes that should be returned in `BUF'
 * @param: ARG:       The user-defined closure parameter passed alongside this function pointer.
 * @return: < 0:      An error occurred and the calling function shall return with this same value.
 * @return: >= 0:     The number of leading bytes of `BUF' that were filled. */
typedef __pformatreader pformatreader;
#endif /* !__pformatreader_defined */

}


/* ... */


%{

__SYSDECL_END
#endif /* __CC__ */

}

