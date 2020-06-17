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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[default:section(".text.crt{|.dos}.debug")]

%{
#include <features.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/execinfo.h */
/* Copyright (C) 1998-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


#ifdef __CC__
}

@@Store up to SIZE return address of the current program state
@@in ARRAY and return the exact number of values stored
[[export_alias("__backtrace")]]
[[decl_include("<features.h>")]]
__STDC_INT_AS_UINT_T backtrace([[nonnull]] void **array,
                               __STDC_INT_AS_UINT_T size);

@@Return names of functions from the backtrace list
@@in ARRAY in a newly malloc()ed memory block
[[export_alias("__backtrace_symbols")]]
[[decl_include("<features.h>")]]
char **backtrace_symbols([[nonnull]] void *const *array,
                         __STDC_INT_AS_UINT_T size);

@@This function is similar to backtrace_symbols()
@@but it writes the result immediately to a file
[[export_alias("__backtrace_symbols_fd")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
void backtrace_symbols_fd([[nonnull]] void *const *array,
                          __STDC_INT_AS_UINT_T size, $fd_t fd);


%{
#endif /* __CC__ */

__SYSDECL_END

}
