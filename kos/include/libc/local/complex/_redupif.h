/* HASH CRC-32:0xe687d759 */
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
#ifndef __local__redupif_defined
#define __local__redupif_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_redupif) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(_redupif))(float __x) {
	/* Implementation derived from NetBSD. -- See the following copyright notice. */
	/*-
	 * Copyright (c) 2007 The NetBSD Foundation, Inc.
	 * All rights reserved.
	 *
	 * This code is derived from software written by Stephen L. Moshier.
	 * It is redistributed by the NetBSD Foundation by permission of the author.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 * 1. Redistributions of source code must retain the above copyright
	 *    notice, this list of conditions and the following disclaimer.
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in the
	 *    documentation and/or other materials provided with the distribution.
	 *
	 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
	 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
	 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
	 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
	 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	 * POSSIBILITY OF SUCH DAMAGE.
	 */
	float __t;




	long __i;
	__t = __x / (float)3.14159265358979323846f /*M_PI*/;

	if (__t >= 0.0f) {
		__t += 0.5f;
	} else {
		__t -= 0.5f;
	}
	__i = __t; /* the multiple */
	__t = __i;










	__t = ((__x - __t * 3.140625f) -
	     __t * 9.67502593994140625E-4f) -
	    __t * 1.509957990978376432E-7f;





	return __t;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__redupif_defined
#define __local___localdep__redupif_defined
#define __localdep__redupif __LIBC_LOCAL_NAME(_redupif)
#endif /* !__local___localdep__redupif_defined */
#endif /* !__local__redupif_defined */
