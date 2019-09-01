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

%[define_replacement(sigset_t = struct __sigset_struct)]
%[default_impl_section(.text.crt.database.aliases)]


%{
#include <features.h>
#include <sys/types.h>

/* Documentation taken from Glibc /usr/include/aliases.h */
/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

__SYSDECL_BEGIN

#ifdef __CC__

}%[push_macro @undef { alias_name alias_members_len alias_members alias_local }]%{
/* Structure to represent one entry of the alias data base. */
struct aliasent {
	char          *alias_name;
	size_t         alias_members_len;
	char         **alias_members;
	__INT32_TYPE__ alias_local;
};
}%[pop_macro]%{

}


@@Open alias data base files
[cp_kos] setaliasent:();

@@Close alias data base files
endaliasent:();

@@Get the next entry from the alias data base
[cp_kos] getaliasent:() -> struct aliasent *;

@@Get the next entry from the alias data base and put it in RESULT_BUF
[cp_kos] getaliasent_r:(
	[nonnull] struct aliasent *__restrict result_buf,
	[nonnull] char *__restrict buffer, size_t buflen,
	[nonnull] struct aliasent **__restrict result) -> int;

@@Get alias entry corresponding to NAME
[cp_kos] getaliasbyname:([nonnull] char const *name) -> struct aliasent *;

@@Get alias entry corresponding to NAME and put it in RESULT_BUF
[cp_kos] getaliasbyname_r:(
	[nonnull] char const *__restrict name,
	[nonnull] struct aliasent *__restrict result_buf,
	[nonnull] char *__restrict buffer, size_t buflen,
	[nonnull] struct aliasent **__restrict result) -> int;



%{
#endif /* __CC__ */

__SYSDECL_END

}