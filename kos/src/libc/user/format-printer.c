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
#ifndef GUARD_LIBC_USER_FORMAT_PRINTER_C
#define GUARD_LIBC_USER_FORMAT_PRINTER_C 1

#include "../api.h"
#include "format-printer.h"
#include "malloc.h"
#include "stdlib.h"
#include <string.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_format_aprintf_pack,hash:CRC-32=0xb8949415]]]*/
/* Pack and finalize a given aprintf format printer
 * Together with `format_aprintf_printer()', the aprintf
 * format printer sub-system should be used as follows:
 * >> char *result; ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_APRINTF_DATA_INIT;
 * >> error = format_printf(&format_aprintf_printer, &p, "%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_aprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_aprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_aprintf_pack()' is able to return `NULL' as well,
 *          but will finalize the given aprintf printer an all cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `strlen(return)' when NUL characters were
 *                  printed to the aprintf-printer at one point.
 *                  (e.g. `format_aprintf_printer(&my_printer, "\0", 1)') */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_format_aprintf_pack)(struct format_aprintf_data *__restrict self,
                                               size_t *pstrlen)
/*[[[body:libc_format_aprintf_pack]]]*/
/*AUTO*/{
	/* Free unused buffer memory. */
	char *result;
	if (self->ap_avail != 0) {
#ifdef __CRT_HAVE_realloc
		char *newbuf;
		newbuf = (char *)realloc(self->ap_base,
		                         (self->ap_used + 1) *
		                         sizeof(char));
		if likely(newbuf)
			self->ap_base = newbuf;
#endif /* __CRT_HAVE_realloc */
	} else {
		if unlikely(!self->ap_used) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->ap_base);
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
			self->ap_base = (char *)malloc(1 * sizeof(char));
			if unlikely(!self->ap_base)
				return NULL;
#elif defined(__CRT_HAVE_realloc)
			self->ap_base = (char *)realloc(NULL, 1 * sizeof(char));
			if unlikely(!self->ap_base)
				return NULL;
#else /* ... */
			return NULL;
#endif /* !... */
		}
	}
	result = self->ap_base;
	__hybrid_assert(result);
	result[self->ap_used] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->ap_used;
#ifndef NDEBUG
#if __SIZEOF_POINTER__ == 4
	self->ap_base  = (char *)__UINT32_C(0xcccccccc);
	self->ap_avail = __UINT32_C(0xcccccccc);
	self->ap_used  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	self->ap_base  = (char *)__UINT64_C(0xcccccccccccccccc);
	self->ap_avail = __UINT64_C(0xcccccccccccccccc);
	self->ap_used  = __UINT64_C(0xcccccccccccccccc);
#endif /* ... */
#endif /* !NDEBUG */
	return result;
}
/*[[[end:libc_format_aprintf_pack]]]*/

/*[[[head:libc_format_aprintf_printer,hash:CRC-32=0x66301058]]]*/
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned
 * This function is intended to be used as a pformatprinter-compatibile printer sink */
INTERN ATTR_SECTION(".text.crt.string.format") WUNUSED NONNULL((1, 2)) ssize_t
NOTHROW_NCX(LIBCCALL libc_format_aprintf_printer)(void *arg,
                                                  char const *__restrict data,
                                                  size_t datalen)
/*[[[body:libc_format_aprintf_printer]]]*/
/*AUTO*/{
	char *buf;
	buf = format_aprintf_alloc((struct format_aprintf_data *)arg,
	                           datalen);
	if unlikely(!buf)
		return -1;
	memcpyc(buf, data, datalen, sizeof(char));
	return (ssize_t)datalen;
}
/*[[[end:libc_format_aprintf_printer]]]*/

/*[[[head:libc_format_aprintf_alloc,hash:CRC-32=0x9cbd58df]]]*/
/* Allocate a buffer of `num_chars' characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_format_aprintf_alloc)(struct format_aprintf_data *__restrict self,
                                                size_t num_chars)
/*[[[body:libc_format_aprintf_alloc]]]*/
/*AUTO*/{
	char *result;
	if (self->ap_avail < num_chars) {
		char *newbuf;
		size_t min_alloc = self->ap_used + num_chars;
		size_t new_alloc = self->ap_used + self->ap_avail;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (char *)realloc(self->ap_base, (new_alloc + 1) * sizeof(char));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char *)realloc(self->ap_base, (new_alloc + 1) * sizeof(char));
			if unlikely(!newbuf)
				return NULL;
		}
		__hybrid_assert(new_alloc >= self->ap_used + num_chars);
		self->ap_base  = newbuf;
		self->ap_avail = new_alloc - self->ap_used;
	}
	result = self->ap_base + self->ap_used;
	self->ap_avail -= num_chars;
	self->ap_used  += num_chars;
	return result;
}
/*[[[end:libc_format_aprintf_alloc]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xe758d5ce]]]*/
DEFINE_PUBLIC_ALIAS(format_aprintf_pack, libc_format_aprintf_pack);
DEFINE_PUBLIC_ALIAS(format_aprintf_alloc, libc_format_aprintf_alloc);
DEFINE_PUBLIC_ALIAS(format_aprintf_printer, libc_format_aprintf_printer);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FORMAT_PRINTER_C */
