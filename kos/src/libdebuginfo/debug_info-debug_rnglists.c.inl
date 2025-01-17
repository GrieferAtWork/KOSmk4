/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "debug_info.c"
#define DEFINE_libdi_debuginfo_rnglists_iterator_next
//#define    DEFINE_libdi_debuginfo_rnglists_contains
//#define DEFINE_libdi_debuginfo_rnglists_contains_ex
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_libdi_debuginfo_rnglists_iterator_next) + \
     defined(DEFINE_libdi_debuginfo_rnglists_contains) +      \
     defined(DEFINE_libdi_debuginfo_rnglists_contains_ex)) != 1
#error "Must #define exactly one of these macros"
#endif /* ... */

#include <assert.h>

DECL_BEGIN

#ifndef addrsize_isvalid
#if __SIZEOF_POINTER__ > 4
#define addrsize_isvalid(v) ((v) == 1 || (v) == 2 || (v) == 4 || (v) == 8)
#else /* __SIZEOF_POINTER__ > 4 */
#define addrsize_isvalid(v) ((v) == 1 || (v) == 2 || (v) == 4)
#endif /* __SIZEOF_POINTER__ <= 4 */
#endif /* !addrsize_isvalid */

#ifdef DEFINE_libdi_debuginfo_rnglists_iterator_next
/* Yield the next range accessible through a given debug-ranges iterator. */
INTERN NONNULL((1, 2, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_rnglists_iterator_next)(di_debuginfo_rnglists_iterator_t *__restrict self,
                                                       uintptr_t *__restrict pmodule_relative_start_pc,
                                                       uintptr_t *__restrict pmodule_relative_end_pc)
#elif defined(DEFINE_libdi_debuginfo_rnglists_contains)
/* Check if a given `module_relative_pc' is apart of the given range selector.
 * @param: self: The ranges object to query for `module_relative_pc' */
INTERN NONNULL((1, 2, 5)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debuginfo_rnglists_contains)(di_debuginfo_rnglists_t const *__restrict self,
                                                  di_debuginfo_cu_parser_t const *__restrict parser,
                                                  uintptr_t cu_base,
                                                  uintptr_t module_relative_pc,
                                                  di_rnglists_sections_t const *__restrict sections)
#else /* DEFINE_libdi_debuginfo_rnglists_contains */
INTERN NONNULL((1, 2, 5, 6, 7)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debuginfo_rnglists_contains_ex)(di_debuginfo_rnglists_t const *__restrict self,
                                                     di_debuginfo_cu_parser_t const *__restrict parser,
                                                     uintptr_t cu_base,
                                                     uintptr_t module_relative_pc,
                                                     di_rnglists_sections_t const *__restrict sections,
                                                     uintptr_t *__restrict poverlap_start,
                                                     uintptr_t *__restrict poverlap_end)
#endif /* !DEFINE_libdi_debuginfo_rnglists_contains */
{
#ifdef DEFINE_libdi_debuginfo_rnglists_iterator_next
	/************************************************************************/
	/* LOCAL_* macros                                                       */
#define LOCAL_iter                       self->ri_pos
#define LOCAL_is_runglists               !self->ri_isranges
#define LOCAL_rnglists_end               self->ri_end
#define LOCAL_ranges_end                 self->ri_end
#define LOCAL_addrsize                   self->ri_addrsize
#define LOCAL_cu_base                    self->ri_cubase
#define LOCAL_R_DEBUG_INFO_ERROR_SUCCESS true
#define LOCAL_R_DEBUG_INFO_ERROR_NOFRAME false
#define LOCAL_R_DEBUG_INFO_ERROR_CORRUPT false
#define LOCAL_checkrange(range_start, range_end) \
	*pmodule_relative_start_pc = range_start;    \
	*pmodule_relative_end_pc   = range_end;      \
	return LOCAL_R_DEBUG_INFO_ERROR_SUCCESS
	/************************************************************************/

	if (self->ri_pos >= self->ri_end) {
		if (self->ri_end == (byte_t const *)-1) {
			*pmodule_relative_start_pc = self->ri_ranges->r_startpc;
			*pmodule_relative_end_pc   = self->ri_ranges->r_endpc;
			self->ri_end = NULL;
			return true;
		}
		return false;
	}
#else /* DEFINE_libdi_debuginfo_rnglists_iterator_next */
	byte_t const *iter;
	/************************************************************************/
	/* LOCAL_* macros                                                       */
#define LOCAL_iter                       iter
#define LOCAL_is_runglists               sections->drs_debug_rnglists_start < LOCAL_rnglists_end
#define LOCAL_rnglists_end               sections->drs_debug_rnglists_end
#define LOCAL_ranges_end                 sections->drs_debug_ranges_end
#define LOCAL_addrsize                   parser->dsp_addrsize
#define LOCAL_cu_base                    cu_base
#define LOCAL_R_DEBUG_INFO_ERROR_SUCCESS DEBUG_INFO_ERROR_SUCCESS
#define LOCAL_R_DEBUG_INFO_ERROR_NOFRAME DEBUG_INFO_ERROR_NOFRAME
#define LOCAL_R_DEBUG_INFO_ERROR_CORRUPT DEBUG_INFO_ERROR_CORRUPT
#ifdef DEFINE_libdi_debuginfo_rnglists_contains_ex
#define _LOCAL_saverange(range_start, range_end) \
	*poverlap_start = range_start;               \
	*poverlap_end   = range_end;
#else /* DEFINE_libdi_debuginfo_rnglists_contains_ex */
#define _LOCAL_saverange(range_start, range_end)
#endif /* !DEFINE_libdi_debuginfo_rnglists_contains_ex */
#define LOCAL_checkrange(range_start, range_end) \
	if (module_relative_pc >= range_start &&     \
	    module_relative_pc < range_end) {        \
		_LOCAL_saverange(range_start, range_end) \
		return LOCAL_R_DEBUG_INFO_ERROR_SUCCESS; \
	}
	/************************************************************************/

	if (DI_DEBUGINFO_RANGES_ISSINGLERANGE(self)) {
		if (module_relative_pc < self->r_startpc ||
		    module_relative_pc >= self->r_endpc)
			return LOCAL_R_DEBUG_INFO_ERROR_NOFRAME;
#ifdef DEFINE_libdi_debuginfo_rnglists_contains_ex
		*poverlap_start = self->r_startpc;
		*poverlap_end   = self->r_endpc;
#endif /* DEFINE_libdi_debuginfo_rnglists_contains_ex */
		return LOCAL_R_DEBUG_INFO_ERROR_SUCCESS;
	}
	if (self->r_startpc != (uintptr_t)-1)
		LOCAL_cu_base = self->r_startpc;
#endif /* !DEFINE_libdi_debuginfo_rnglists_iterator_next */
	assert(addrsize_isvalid(LOCAL_addrsize));

	/* Check if we're using new-style .debug_rnglists */
	if (LOCAL_is_runglists) {
#ifndef DEFINE_libdi_debuginfo_rnglists_iterator_next
		if unlikely(self->r_ranges_offset >= (size_t)(LOCAL_rnglists_end -
		                                              sections->drs_debug_rnglists_start))
			ERROR(err);
		LOCAL_iter = sections->drs_debug_rnglists_start + self->r_ranges_offset;
#endif /* !DEFINE_libdi_debuginfo_rnglists_iterator_next */

		while (LOCAL_iter < LOCAL_rnglists_end) {
			/* """
			 * Each range list entry begins with  a single byte identifying the  kind
			 * of that entry, followed by zero or more operands depending on the kind
			 * """ */
			byte_t type = *LOCAL_iter++; /* One of `DW_RLE_*' */
			uintptr_t range_start, range_end;
			switch (type) {

			case DW_RLE_end_of_list:
				/* End-of-rangelist */
				return LOCAL_R_DEBUG_INFO_ERROR_NOFRAME;

			case DW_RLE_offset_pair:
				range_start = dwarf_decode_uleb128(&LOCAL_iter);
				range_end   = dwarf_decode_uleb128(&LOCAL_iter);
				range_start += LOCAL_cu_base;
				range_end   += LOCAL_cu_base;
				break;

			case DW_RLE_base_address:
				switch (LOCAL_addrsize) {
				case 1: LOCAL_cu_base = UNALIGNED_GET8(LOCAL_iter), LOCAL_iter += 1; break;
				case 2: LOCAL_cu_base = UNALIGNED_GET16(LOCAL_iter), LOCAL_iter += 2; break;
				case 4: LOCAL_cu_base = UNALIGNED_GET32(LOCAL_iter), LOCAL_iter += 4; break;
#if __SIZEOF_POINTER__ > 4
				case 8: LOCAL_cu_base = UNALIGNED_GET64(LOCAL_iter), LOCAL_iter += 8; break;
#endif /* __SIZEOF_POINTER__ > 4 */
				default: __builtin_unreachable();
				}
				continue;

			case DW_RLE_start_end:
				switch (LOCAL_addrsize) {

				case 1:
					range_start = UNALIGNED_GET8(LOCAL_iter);
					LOCAL_iter += 1;
					range_end = UNALIGNED_GET8(LOCAL_iter);
					LOCAL_iter += 1;
					break;

				case 2:
					range_start = UNALIGNED_GET16(LOCAL_iter);
					LOCAL_iter += 2;
					range_end = UNALIGNED_GET16(LOCAL_iter);
					LOCAL_iter += 2;
					break;

				case 4:
					range_start = UNALIGNED_GET32(LOCAL_iter);
					LOCAL_iter += 4;
					range_end = UNALIGNED_GET32(LOCAL_iter);
					LOCAL_iter += 4;
					break;

#if __SIZEOF_POINTER__ > 4
				case 8:
					range_start = UNALIGNED_GET64(LOCAL_iter);
					LOCAL_iter += 8;
					range_end = UNALIGNED_GET64(LOCAL_iter);
					LOCAL_iter += 8;
					break;
#endif /* __SIZEOF_POINTER__ > 4 */

				default: __builtin_unreachable();
				}
				break;

			case DW_RLE_start_length:
				switch (LOCAL_addrsize) {
				case 1: range_start = UNALIGNED_GET8(LOCAL_iter), LOCAL_iter += 1; break;
				case 2: range_start = UNALIGNED_GET16(LOCAL_iter), LOCAL_iter += 2; break;
				case 4: range_start = UNALIGNED_GET32(LOCAL_iter), LOCAL_iter += 4; break;
#if __SIZEOF_POINTER__ > 4
				case 8: range_start = UNALIGNED_GET64(LOCAL_iter), LOCAL_iter += 8; break;
#endif /* __SIZEOF_POINTER__ > 4 */
				default: __builtin_unreachable();
				}
				range_end = range_start + dwarf_decode_uleb128(&LOCAL_iter);
				break;

			default:
				ERROR(err);
			}

			/* Check if address is contained in given range. */
			LOCAL_checkrange(range_start, range_end);
		}
	}

#ifndef DEFINE_libdi_debuginfo_rnglists_iterator_next
	if unlikely(self->r_ranges_offset >= (size_t)(LOCAL_ranges_end -
	                                              sections->drs_debug_ranges_start))
		ERROR(err);
	LOCAL_iter = sections->drs_debug_ranges_start + self->r_ranges_offset;
#endif /* !DEFINE_libdi_debuginfo_rnglists_iterator_next */

	while (LOCAL_iter < LOCAL_ranges_end) {
		uintptr_t range_start, range_end;
		switch (LOCAL_addrsize) {

		case 1:
			range_start = UNALIGNED_GET8(LOCAL_iter);
			LOCAL_iter += 1;
			range_end = UNALIGNED_GET8(LOCAL_iter);
			LOCAL_iter += 1;
			break;

		case 2:
			range_start = UNALIGNED_GET16(LOCAL_iter);
			LOCAL_iter += 2;
			range_end = UNALIGNED_GET16(LOCAL_iter);
			LOCAL_iter += 2;
			break;

		case 4:
			range_start = UNALIGNED_GET32(LOCAL_iter);
			LOCAL_iter += 4;
			range_end = UNALIGNED_GET32(LOCAL_iter);
			LOCAL_iter += 4;
			break;

#if __SIZEOF_POINTER__ > 4
		case 8:
			range_start = UNALIGNED_GET64(LOCAL_iter);
			LOCAL_iter += 8;
			range_end = UNALIGNED_GET64(LOCAL_iter);
			LOCAL_iter += 8;
			break;
#endif /* __SIZEOF_POINTER__ > 4 */

		default: __builtin_unreachable();
		}
		if (range_start == (uintptr_t)-1) {
			/* Base address selection entry! */
			LOCAL_cu_base = range_end;
			continue;
		} else if (!range_start && !range_end) {
			/* Range list end entry. */
			break;
		} else {
			range_start += LOCAL_cu_base;
			range_end   += LOCAL_cu_base;
		}

		LOCAL_checkrange(range_start, range_end);
	}
	return LOCAL_R_DEBUG_INFO_ERROR_NOFRAME;
err:
	return LOCAL_R_DEBUG_INFO_ERROR_CORRUPT;
#undef LOCAL_iter
#undef LOCAL_is_runglists
#undef LOCAL_rnglists_end
#undef LOCAL_ranges_end
#undef LOCAL_addrsize
#undef LOCAL_cu_base
#undef LOCAL_R_DEBUG_INFO_ERROR_SUCCESS
#undef LOCAL_R_DEBUG_INFO_ERROR_NOFRAME
#undef LOCAL_R_DEBUG_INFO_ERROR_CORRUPT
#undef _LOCAL_saverange
#undef LOCAL_checkrange
}

DECL_END

#undef DEFINE_libdi_debuginfo_rnglists_iterator_next
#undef DEFINE_libdi_debuginfo_rnglists_contains
#undef DEFINE_libdi_debuginfo_rnglists_contains_ex
