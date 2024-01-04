/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBKEYMAP_KEYMAP_H
#define GUARD_LIBKEYMAP_KEYMAP_H 1

#include "api.h"

#include <libkeymap/keymap.h>
#include <kos/types.h>
#include <format-printer.h>

DECL_BEGIN

/* Return the size (in bytes) of the keyboard translation code block,  that
 * is the number of bytes until after the terminating `KMP_OP_STOP' opcode.
 * @return: <0: The code contains unrecognized/invalid instructions. */
INTDEF NONNULL((1, 2)) ssize_t
NOTHROW_NCX(CC libkeymap_codesize)(byte_t const *__restrict code,
                                   uint8_t *__restrict preg_enc,
                                   uint8_t def_enc);

/* Same as `keymap_codesize()', but only return the length of a single instruction.
 * @return: 0:  The next instruction is `KMP_OP_STOP'
 * @return: <0: The code contains unrecognized/invalid instructions. */
INTDEF NONNULL((1, 2)) ssize_t
NOTHROW_NCX(CC libkeymap_instrlen)(byte_t const *__restrict code,
                                   uint8_t *__restrict preg_enc,
                                   uint8_t def_enc);

/* Translate a given key `key' when modifiers `mod' are applied into a unicode character.
 * @return: 0  : Either `printer' always returned 0, or the key doesn't have a mapping.
 * @return: *  : Sum of all calls to `printer'
 * @return: <0 : A call to `printer' returned this same negative value */
INTDEF ssize_t
NOTHROW_NCX(CC libkeymap_translate)(struct keymap *__restrict self,
                                    uint16_t const key,
                                    uint16_t const mod,
                                    pformatprinter printer, void *arg);

/* Wrapper for buffer-based translating, using snprintf()-like buffer printing.
 * NOTE: Upon success,  this function  will  optionally append  a  NUL-character
 *       if sufficient buffer space is available (`return < buflen'). Otherwise,
 *       when  `return == buflen',  no  trailing NUL-character  exists,  but the
 *       function still succeeds.
 * @param: buffer: The buffer to which to print translated characters.
 * @param: buflen: The given buffer size.
 * @return: 0 :    The given `key' cannot be translated with `mod'
 * @return: * :    The required number of buffer bytes. (excluding a trailing NUL-character) */
INTDEF size_t
NOTHROW_NCX(CC libkeymap_translate_buf)(struct keymap *__restrict self,
                                        uint16_t key, uint16_t mod,
                                        /*utf-8*/ char *buffer, size_t buflen);



/* Open a memory-blob of a KMP (KeyboardMaP) file (see above for the file format specs)
 * NOTE: The  caller must ensure that a keymap blob  loaded form some file must end with at
 *       least 5 additional trailing 0-bytes (i.e. `blob_base[blob_size+{0,1,2,3,4}] == 0')
 * NOTE: Upon success, the caller must also ensure that `self->km_ext...+=(blob_base+blob_size)-self->km_ext'
 *       will  not be freed.  Alternatively, the caller may  replace `self->km_ext' with  a duplicate of that
 *       memory region and free it themself after finalization
 * @return: true:  Successfully loaded the given blob and initialized `self'
 * @return: false: Failed to open the blob (not a valid KMP file) */
INTDEF bool
NOTHROW_NCX(CC libkeymap_openblob)(struct keymap *__restrict self,
                                   void const *blob_base,
                                   size_t blob_size);


DECL_END

#endif /* !GUARD_LIBKEYMAP_KEYMAP_H */
