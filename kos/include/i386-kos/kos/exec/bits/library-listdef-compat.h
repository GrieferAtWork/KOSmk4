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
#ifndef _I386_KOS_KOS_EXEC_BITS_LIBRARY_LISTDEF_COMPAT_H
#define _I386_KOS_KOS_EXEC_BITS_LIBRARY_LISTDEF_COMPAT_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/types.h>

#include "library-listdef32.h"
#include "library-listdef64.h"

#ifdef __CC__
__SYSDECL_BEGIN

__LOCAL void
__NOTHROW_NCX(library_listdef32_to_library_listdef64)(struct library_listdef32 const *__restrict __self,
                                                      struct library_listdef64 *__restrict __result) {
	__result->lld_size                      = (__uint64_t)__self->lld_size;
	__result->lld_sizeof_pointer            = (__uint64_t)__self->lld_sizeof_pointer;
	__result->lld_flags                     = (__uint64_t)__self->lld_flags;
	__result->lld_first                     = (__HYBRID_PTR64(void))__self->lld_first;
	__result->lld_count                     = (__HYBRID_PTR64(void))__self->lld_count;
	__result->lld_module_offsetof_filename  = (__int64_t)__self->lld_module_offsetof_filename;
	__result->lld_module_offsetof_loadaddr  = (__int64_t)__self->lld_module_offsetof_loadaddr;
	__result->lld_module_offsetof_loadstart = (__int64_t)__self->lld_module_offsetof_loadstart;
	__result->lld_entry_offsetof_next       = (__int64_t)__self->lld_entry_offsetof_next;
	__result->lld_entry_offsetof_module     = (__int64_t)__self->lld_entry_offsetof_module;
}

__LOCAL void
__NOTHROW_NCX(library_listdef64_to_library_listdef32)(struct library_listdef64 const *__restrict __self,
                                                      struct library_listdef32 *__restrict __result) {
	__result->lld_size                      = (__uint32_t)__self->lld_size;
	__result->lld_sizeof_pointer            = (__uint32_t)__self->lld_sizeof_pointer;
	__result->lld_flags                     = (__uint32_t)__self->lld_flags;
	__result->lld_first                     = (__HYBRID_PTR32(void))__self->lld_first;
	__result->lld_count                     = (__HYBRID_PTR32(void))__self->lld_count;
	__result->lld_module_offsetof_filename  = (__int32_t)__self->lld_module_offsetof_filename;
	__result->lld_module_offsetof_loadaddr  = (__int32_t)__self->lld_module_offsetof_loadaddr;
	__result->lld_module_offsetof_loadstart = (__int32_t)__self->lld_module_offsetof_loadstart;
	__result->lld_entry_offsetof_next       = (__int32_t)__self->lld_entry_offsetof_next;
	__result->lld_entry_offsetof_module     = (__int32_t)__self->lld_entry_offsetof_module;
}

#ifdef __x86_64__
#define library_listdef_to_library_listdef32 library_listdef64_to_library_listdef32
#define library_listdef_to_library_listdef64(self, result) (*(result) = *(self))
#define library_listdef32_to_library_listdef library_listdef32_to_library_listdef64
#define library_listdef64_to_library_listdef(self, result) (*(result) = *(self))
#else /* __x86_64__ */
#define library_listdef_to_library_listdef32(self, result) (*(result) = *(self))
#define library_listdef_to_library_listdef64 library_listdef32_to_library_listdef64
#define library_listdef32_to_library_listdef(self, result) (*(result) = *(self))
#define library_listdef64_to_library_listdef library_listdef64_to_library_listdef32
#endif /* !__x86_64__ */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_EXEC_BITS_LIBRARY_LISTDEF_COMPAT_H */
