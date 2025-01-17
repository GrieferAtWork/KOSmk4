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
#ifndef _LIBKEYMAP_KEYMAP_H
#define _LIBKEYMAP_KEYMAP_H 1

#include "api.h"
/**/

#include <bits/crt/format-printer.h>
#include <bits/types.h>

__DECL_BEGIN


/* KMP File format.
 * NOTE: KMP  files  are  the  compiled  versions  of  keymap  definition   files
 *       An API for invoking a compiler to create these files is provided via the
 *      `compileKeymap()' function found in `/kos/misc/libgen/libkeymap/compiler.dee'
 * Keymap source files can be found in `/kos/src/misc/keymaps/...'
 */

#define KMP_MAG0             'K'
#define KMP_MAG1             'm'
#define KMP_MAG2             'p'
#define KMP_MAG3              0x35
#define KMP_VERSION_CURRENT   1
#ifdef __CC__
typedef struct __ATTR_PACKED {
	__uint8_t   h_magic[4]; /* Header magic. */
	__uint8_t   h_version;  /* File version. */
	__uint8_t   h_hdrsize;  /* Total size of the header. (Absolute file-offset to a `Kmp_Data' structure) */
} Kmp_Header;
#endif /* __CC__ */


#define KMP_ENCODING_ASCII   0x00 /* All characters are encoded as 7-bit ascii characters with the 8th bit ZERO */
#define KMP_ENCODING_LATIN1  0x00 /* All characters are encoded as 8-bit integers (single-byte LATIN-1 characters) */
#define KMP_ENCODING_UTF8    0x01 /* All characters are encoded as UTF-8 sequences. */
#define KMP_ENCODING_UTF16LE 0x02 /* All  characters are  encoded as UTF-16  sequences (Little endian)  with a length
                                   * of a single character each (max. 2 UTF-16 characters; 1 if it isn't a surrogate) */
#define KMP_ENCODING_UTF16BE 0x03 /* Same as `KMP_ENCODING_UTF16LE', but big endian. */
#define KMP_ENCODING_UTF32LE 0x04 /* Characters are encoded as UTF32, little-endian (max 1 character) */
#define KMP_ENCODING_UTF32BE 0x05 /* Characters are encoded as UTF32, big-endian */
#define KMP_ENCODING_MCS     0x06 /* Multi-character-string (each character is encoded as UTF-8,
                                   * and   the  sequence  is  terminated  by  a  NUL-character). */
#define KMP_ENCODING_MAX     0x06 /* Max recognized encoding. */
#ifdef __CC__
typedef struct __ATTR_PACKED {
	__uint8_t   d_encoding; /* KMP default encoding (One of `KMP_ENCODING_*'). */
	__uint8_t   d_zero;     /* Must be zero */
	__uint8_t   d_code[1];  /* keyboard mapping pseudo-code (see below) */
} Kmp_Data;
#endif /* __CC__ */


/* KMP registers:
 *   - %pc            The current program counter.
 *   - %key           Points to the next key to-be defined. Pre-initialized to `KEY(0,0)'
 *   - %enc           The current encoding for large characters (Pre-initialized to `d_encoding')
 *   - CURRENT_KEY    The key that got pressed.
 *   - CURRENT_KEYMOD Set of keyboard modifiers currently active.
 */
#define KMP_OP_STOP       0x00 /* OPCODE: Stop execution */
#define KMP_OP_INCCOL     0x01 /* OPCODE: >> %key += KEY(0, 1); */
#define KMP_OP_DECCOL     0x02 /* OPCODE: >> %key -= KEY(0, 1); */
#define KMP_OP_SETENC     0x03 /* OPCODE: >> %enc  = *%pc; %pc += 1; */
#define KMP_OP_SETKEY     0x04 /* OPCODE: >> %key  = *%pc; %pc += 1; */
#define KMP_OP_DEFENC     0x05 /* OPCODE: >> %enc  = DEFAULT_ENCODING; (DEFAULT_ENCODING == `d_encoding') */
#define KMP_OP_SETKEY2    0x06 /* OPCODE: >> %key  = UNALIGNED_GETLE16(%pc); %pc += 2; */
/*      KMP_OP_           0x07  * ... */
/*      KMP_OP_           ...   * ... */
/*      KMP_OP_           0x19  * ... */
#define KMP_OP_SETKEYMOD2 0x1a /* OPCODE: >> mask = UNALIGNED_GETLE16(%pc); %pc += 2;
                                *         >> kchr = READ_CHARACTER(%pc, %enc);
                                *         >> if (CURRENT_KEYMOD == mask)
                                *         >>     return kchr; */
#define KMP_OP_SETKEYMOD  0x1b /* OPCODE: >> mask = *(u8 const *)%pc; %pc += 1;
                                *         >> kchr = READ_CHARACTER(%pc, %enc);
                                *         >> if (CURRENT_KEYMOD == mask)
                                *         >>     return kchr; */
#define KMP_OP_SETPRESS   0x1c /* OPCODE: >> kchr = READ_CHARACTER(%pc, %enc);
                                *         >> if (CURRENT_KEY == %key && KEYMOD_ISNORMAL(CURRENT_KEYMOD))
                                *         >>     return kchr;
                                *         >> %key += KEY(0,1); */
#define KMP_OP_SETSHIFT   0x1d /* OPCODE: >> kchr = READ_CHARACTER(%pc, %enc);
                                *         >> if (CURRENT_KEY == %key && KEYMOD_ISSHIFT(CURRENT_KEYMOD))
                                *         >>     return kchr; */
#define KMP_OP_SETALTGR   0x1e /* OPCODE: >> kchr = READ_CHARACTER(%pc, %enc);
                                *         >> if (CURRENT_KEY == %key && KEYMOD_ISALTGR(CURRENT_KEYMOD))
                                *         >>     return kchr; */
#define KMP_OP_NOP        0x1f /* OPCODE: >> // no-op */

/* Special opcodes that encode their operand as part of the instruction. */
#define KMP_OP_MEXTENDED 0xe0 /* Mask for merged operand instructions.
                               * >> if ((op & KMP_OP_MEXTENDED) == KMP_OP_FDEFLATIN) ...;
                               * >> if ((op & KMP_OP_MEXTENDED) == KMP_OP_FDEFDIGIT) ...;
                               * >> if ((op & KMP_OP_MEXTENDED) == KMP_OP_FSETROW) ...;
                               * >> if ((op & KMP_OP_MEXTENDED) == KMP_OP_FSETCOL) ...; */
#define KMP_OP_FDEFLATIN 0x20 /* >> press[%key] = 'a' + (op & 0x1f);
                               * >> shift[%key] = 'A' + (op & 0x1f);
                               * >> %key += KEY(0, 1); */
#define KMP_OP_FDEFDIGIT 0x40 /* >> press[%key] = '1' + (op & 0x1f);
                               * >> shift[%key] = '!' + (op & 0x1f);
                               * >> %key += KEY(0, 1); */
/*      KMP_OP_F         0x60  * ... */
/*      KMP_OP_F         0x80  * ... */
/*      KMP_OP_F         0xa0  * ... */
#define KMP_OP_FSETROW   0xc0 /* >> %key = KEY(op & 0x1f, 0); */
#define KMP_OP_FSETCOL   0xe0 /* >> %key = KEY(KEY_GETROW(%key), op & 0x1f); */



/* Max supported code size for keymaps (when code becomes larger than  this,
 * the kernel may choose to disallow the code being loaded into a the keymap
 * of some given keyboard; s.a. `KBD_IOC_SETKEYMAP') */
#ifndef KEYMAP_MAX_CODESIZE
#define KEYMAP_MAX_CODESIZE (1024 * 1024)
#endif /* !KEYMAP_MAX_CODESIZE */



#ifdef __CC__
struct basic_key {
	char bk_normal; /* Produced ASCII key under normal circumstances (or 0 if not given). */
	char bk_shift;  /* Produced ASCII key when shift is held (or 0 if not given). */
};

struct keymap {
	struct basic_key km_basic[128];  /* Basic keyboard mappings for key codes 0 ... 127.
	                                  * NOTE: Fields in this array are lazily initialized if possible. */
	__byte_t const  *km_ext;         /* [const][0..1] Key matching program (points to `Kmp_Data::d_code'). */
	__uint8_t        km_defencoding; /* [const] Default keymap encoding (One of `KMP_ENCODING_*'). */
};


/* Return the size (in bytes) of the keyboard translation code block,  that
 * is the number of bytes until after the terminating `KMP_OP_STOP' opcode.
 * @return: <0: The code contains unrecognized/invalid instructions. */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t
__NOTHROW_NCX_T(LIBKEYMAP_CC *PKEYMAP_CODESIZE)(__byte_t const *__restrict code,
                                                __uint8_t *__restrict preg_enc,
                                                __uint8_t def_enc);
#ifdef LIBKEYMAP_WANT_PROTOTYPES
LIBKEYMAP_DECL __ATTR_NONNULL((1, 2)) __ssize_t
__NOTHROW_NCX(LIBKEYMAP_CC keymap_codesize)(__byte_t const *__restrict code,
                                            __uint8_t *__restrict preg_enc,
                                            __uint8_t def_enc);
#endif /* LIBKEYMAP_WANT_PROTOTYPES */

/* Same as `keymap_codesize()', but only return the length of a single instruction.
 * @return: 0:  The next instruction is `KMP_OP_STOP'
 * @return: <0: The code contains unrecognized/invalid instructions. */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t
__NOTHROW_NCX_T(LIBKEYMAP_CC *PKEYMAP_INSTRLEN)(__byte_t const *__restrict code,
                                                __uint8_t *__restrict preg_enc,
                                                __uint8_t def_enc);
#ifdef LIBKEYMAP_WANT_PROTOTYPES
LIBKEYMAP_DECL __ATTR_NONNULL((1, 2)) __ssize_t
__NOTHROW_NCX(LIBKEYMAP_CC keymap_instrlen)(__byte_t const *__restrict code,
                                            __uint8_t *__restrict preg_enc,
                                            __uint8_t def_enc);
#endif /* LIBKEYMAP_WANT_PROTOTYPES */

/* Initialize the given keymap to represent the map keys according to the en_US layout.
 * This function should be used as fallback when the caller is unable to initialize the
 * desired keyboard layout, as ~any~ mapping is still better than no mapping at all. */
typedef __ATTR_NONNULL_T((1)) void
__NOTHROW_NCX_T(LIBKEYMAP_CC *PKEYMAP_INIT_EN_US)(struct keymap *__restrict self);
#ifdef LIBKEYMAP_WANT_PROTOTYPES
LIBKEYMAP_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBKEYMAP_CC keymap_init_en_US)(struct keymap *__restrict self);
#endif /* LIBKEYMAP_WANT_PROTOTYPES */


/* Translate a given key `key' when modifiers `mod' are applied into a unicode character.
 * @return: 0  : Either `printer' always returned 0, or the key doesn't have a mapping.
 * @return: *  : Sum of all calls to `printer'
 * @return: <0 : A call to `printer' returned this same negative value */
typedef __ATTR_NONNULL_T((1, 4)) __ssize_t
__NOTHROW_NCX_T(LIBKEYMAP_CC *PKEYMAP_TRANSLATE)(struct keymap *__restrict self,
                                                 __uint16_t key, __uint16_t mod,
                                                 __pformatprinter printer, void *arg);
#ifdef LIBKEYMAP_WANT_PROTOTYPES
LIBKEYMAP_DECL __ATTR_NONNULL((1, 4)) __ssize_t
__NOTHROW_NCX(LIBKEYMAP_CC keymap_translate)(struct keymap *__restrict self,
                                             __uint16_t key, __uint16_t mod,
                                             __pformatprinter printer, void *arg);
#endif /* LIBKEYMAP_WANT_PROTOTYPES */


/* Wrapper for buffer-based translating, using snprintf()-like buffer printing.
 * NOTE: Upon success,  this function  will  optionally append  a  NUL-character
 *       if sufficient buffer space is available (`return < buflen'). Otherwise,
 *       when  `return == buflen',  no  trailing NUL-character  exists,  but the
 *       function still succeeds.
 * @param: buffer: The buffer to which to print translated characters.
 * @param: buflen: The given buffer size.
 * @return: 0 :    The given `key' cannot be translated with `mod'
 * @return: * :    The required number of buffer bytes. (excluding a trailing NUL-character) */
typedef __ATTR_NONNULL_T((1, 4)) __size_t
__NOTHROW_NCX_T(LIBKEYMAP_CC *PKEYMAP_TRANSLATE_BUF)(struct keymap *__restrict self,
                                                     __uint16_t key, __uint16_t mod,
                                                     /*utf-8*/ char *buffer, __size_t buflen);
#ifdef LIBKEYMAP_WANT_PROTOTYPES
LIBKEYMAP_DECL __ATTR_NONNULL((1, 4)) __size_t
__NOTHROW_NCX(LIBKEYMAP_CC keymap_translate_buf)(struct keymap *__restrict self,
                                                 __uint16_t key, __uint16_t mod,
                                                 /*utf-8*/ char *buffer, __size_t buflen);
#endif /* LIBKEYMAP_WANT_PROTOTYPES */

#define KEYMAP_UNTRUSTED_NUM_TRAILING_ZERO_BYTES 9

/* Open a memory-blob of a KMP (KeyboardMaP) file (see above for the file format specs)
 * NOTE: If the keymap was loaded from an untrusted source, the caller should ensure that
 *       a keymap blob loaded form some file is followed by at least `KEYMAP_UNTRUSTED_NUM_TRAILING_ZERO_BYTES'
 *       additional trailing 0-bytes (i.e. `blob_base[blob_size+{0-8}] == 0')
 * NOTE: Upon success, the caller must also ensure that `self->km_ext...+=(blob_base+blob_size)-self->km_ext'
 *       will  not be freed.  Alternatively, the caller may  replace `self->km_ext' with  a duplicate of that
 *       memory region and free it themself after finalization
 * @return: true:  Successfully loaded the given blob and initialized `self'
 * @return: false: Failed to open the blob (not a valid KMP file) */
typedef __ATTR_NONNULL_T((1, 2)) __BOOL
__NOTHROW_NCX_T(LIBKEYMAP_CC *PKEYMAP_OPENBLOB)(struct keymap *__restrict self,
                                                void const *blob_base,
                                                __size_t blob_size);
#ifdef LIBKEYMAP_WANT_PROTOTYPES
LIBKEYMAP_DECL __ATTR_NONNULL((1, 2)) __BOOL
__NOTHROW_NCX(LIBKEYMAP_CC keymap_openblob)(struct keymap *__restrict self,
                                            void const *blob_base,
                                            __size_t blob_size);
#endif /* LIBKEYMAP_WANT_PROTOTYPES */

#endif /* __CC__ */


__DECL_END

#endif /* !_LIBKEYMAP_KEYMAP_H */
