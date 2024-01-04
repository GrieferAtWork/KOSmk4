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
#ifndef GUARD_LIBKEYMAP_KEYMAP_C
#define GUARD_LIBKEYMAP_KEYMAP_C 1
#define _KOS_SOURCE 1 /* strend() */

#include "keymap.h"

#include "api.h"

#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/types.h>
#include <kos/keyboard.h>
#include <kos/types.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

#include <libkeymap/keymap.h>

#if !defined(NDEBUG) && !defined(__KERNEL__) && 0
#include <sys/syslog.h>
#define CASE(value)        case value: syslog(LOG_DEBUG, "%s(%d) : %s [reg_key=%#.4I16x]\n", __FILE__, __LINE__, #value, reg_key);
#define CASEF(value, ...)  case value: syslog(LOG_DEBUG, "%s(%d) : %s [reg_key=%#.4I16x] : ", __FILE__, __LINE__, #value, reg_key); syslog(LOG_DEBUG, __VA_ARGS__);
#define ERROR(label)       do{ syslog(LOG_ERR, "%s(%d) : Error\n", __FILE__, __LINE__); goto label; }__WHILE0
#define ERRORF(label, ...) do{ syslog(LOG_ERR, "%s(%d) : Error : ", __FILE__, __LINE__); syslog(LOG_ERR, __VA_ARGS__); goto label; }__WHILE0
#else
#define CASE(value)        case value:
#define CASEF(value, ...)  case value:
#define ERROR(label)       goto label
#define ERRORF(label, ...) goto label
#endif

DECL_BEGIN


/* Return the size (in bytes) of the keyboard translation code block,  that
 * is the number of bytes until after the terminating `KMP_OP_STOP' opcode.
 * @return: <0: The code contains unrecognized/invalid instructions. */
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(CC libkeymap_codesize)(byte_t const *__restrict code,
                                   uint8_t *__restrict preg_enc,
                                   uint8_t def_enc) {
	ssize_t temp, result = 1; /* +1 for the trailing KMP_OP_STOP */
	for (;;) {
		temp = libkeymap_instrlen(code,
		                          preg_enc,
		                          def_enc);
		if unlikely(temp < 0)
			goto err;
		if (!temp)
			break; /* STOP-instruction reached. */
		code += (size_t)temp;
		result += (size_t)temp;
	}
	return result;
err:
	return temp;
}

/* Same as `keymap_codesize()', but only return the length of a single instruction.
 * @return: 0:  The next instruction is `KMP_OP_STOP'
 * @return: <0: The code contains unrecognized/invalid instructions. */
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(CC libkeymap_instrlen)(byte_t const *__restrict code,
                                   uint8_t *__restrict preg_enc,
                                   uint8_t def_enc) {
	byte_t opcode;
	byte_t const *start;
	start  = code;
	opcode = *code++;
	switch (opcode & KMP_OP_MEXTENDED) {

	case 0x00:
		/* Multi-byte opcodes. */
		switch (opcode) {

		case KMP_OP_STOP:
			return 0;

		case KMP_OP_INCCOL:
		case KMP_OP_DECCOL:
			break;

		case KMP_OP_DEFENC:
			*preg_enc = def_enc;
			break;

		case KMP_OP_SETENC: {
			byte_t arg;
			arg = *code++;
			if unlikely(arg > KMP_ENCODING_MAX)
				ERROR(error);
			*preg_enc = arg;
		}	break;

		case KMP_OP_SETKEY:
			code += 1;
			break;

		case KMP_OP_SETKEY2:
			code += 2;
			break;

		case KMP_OP_SETKEYMOD:
			code += 1;
			goto skip_character;
		case KMP_OP_SETKEYMOD2:
			code += 2;
			goto skip_character;

		case KMP_OP_SETPRESS:
		case KMP_OP_SETSHIFT:
		case KMP_OP_SETALTGR:
skip_character:
			switch (*preg_enc) {

			case KMP_ENCODING_LATIN1:
				++code;
				break;
			case KMP_ENCODING_UTF8: {
				u8 len = unicode_utf8seqlen[*code];
				if unlikely(!len)
					ERROR(error);
				code += len;
			}	break;

			case KMP_ENCODING_UTF32LE:
			case KMP_ENCODING_UTF32BE:
				code += 4;
				break;

			case KMP_ENCODING_UTF16LE: {
				u16 word;
				word = UNALIGNED_GETLE16(code);
				goto do_check_surrogate_skip;
			case KMP_ENCODING_UTF16BE:
				word = UNALIGNED_GETBE16(code);
do_check_surrogate_skip:
				if (word >= UTF16_HIGH_SURROGATE_MIN &&
					word <= UTF16_HIGH_SURROGATE_MIN) {
					u16 hiword = UNALIGNED_GET16(code + 2);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					if (*preg_enc == KMP_ENCODING_UTF16BE)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
					if (*preg_enc == KMP_ENCODING_UTF16LE)
#endif
					{
						hiword = BSWAP16(hiword);
					}
					if unlikely(!(hiword >= UTF16_LOW_SURROGATE_MIN &&
					              hiword <= UTF16_LOW_SURROGATE_MIN))
						ERROR(error);
					code += 4;
				} else {
					if unlikely(word >= UTF16_LOW_SURROGATE_MIN &&
					            word <= UTF16_LOW_SURROGATE_MIN)
						ERROR(error);
					code += 2;
				}
			}	break;

			case KMP_ENCODING_MCS:
				code = (byte_t *)strend((char const *)code) + 1;
				break;

			default:
				ERROR(error);
			}
			break;

		case KMP_OP_NOP:
			break;

		default:
			ERROR(error);
		}
		break;

	case KMP_OP_FDEFLATIN:
	case KMP_OP_FDEFDIGIT:
	case KMP_OP_FSETROW:
	case KMP_OP_FSETCOL:
		break;

	default:
		ERROR(error);
	}
	return (size_t)(code - start);
error:
	return -1;
}


/* Translate a given key `key' when modifiers `mod' are applied into a unicode character.
 * @return: 0  : Either `printer' always returned 0, or the key doesn't have a mapping.
 * @return: *  : Sum of all calls to `printer'
 * @return: <0 : A call to `printer' returned this same negative value */
INTERN NONNULL((1, 4)) ssize_t
NOTHROW_NCX(CC libkeymap_translate)(struct keymap *__restrict self,
                                    uint16_t const key, /* `const' so we don't accidentally write this one instead of `reg_key' */
                                    uint16_t const mod, /* Make this one `const' as well. Just for good measure... */
                                    pformatprinter printer, void *arg) {
	struct basic_key *basic = NULL;
	ssize_t result;
	byte_t const *reader;
	byte_t opcode;
	uint8_t reg_enc;
	uint16_t reg_key;
	char cachable_character;
	/* Check if the translation for the key can be cached. */
	if (key < lengthof(self->km_basic) &&
	    (KEYMOD_ISNORMAL(mod) || KEYMOD_ISSHIFT(mod))) {
		/* Check if the translation is cached. */
		basic = &self->km_basic[key];
		cachable_character = KEYMOD_ISNORMAL(mod)
		                     ? basic->bk_normal
		                     : basic->bk_shift;
		if (cachable_character != 0) {
			/* Cached result. */
			result = (*printer)(arg, &cachable_character, 1);
			goto done;
		}
	}
	cachable_character = 0;
	reader = self->km_ext;
	if unlikely(!reader)
		goto unknown;
	reg_enc = self->km_defencoding;
	reg_key = KEY(0, 0);
	assert(reg_enc <= KMP_ENCODING_MAX);
	for (;;) {
		opcode = *reader++;
		switch (opcode & KMP_OP_MEXTENDED) {

		case 0x00:
			/* Multi-byte opcodes. */
			switch (opcode) {

			CASE(KMP_OP_STOP)
				goto unknown;

			CASE(KMP_OP_INCCOL)
				reg_key += KEY(0, 1);
				break;

			CASE(KMP_OP_DECCOL)
				reg_key -= KEY(0, 1);
				break;

			CASEF(KMP_OP_SETENC, "enc=%" PRIu8 "\n", *reader)
				reg_enc = *reader++;
				if unlikely(reg_enc > KMP_ENCODING_MAX)
					ERROR(error);
				break;

			CASE(KMP_OP_SETKEY)
				reg_key = *reader++;
				break;

			CASEF(KMP_OP_DEFENC, "enc=%" PRIu8 "\n", self->km_defencoding)
				reg_enc = self->km_defencoding;
				break;

			CASE(KMP_OP_SETKEY2)
				reg_key = UNALIGNED_GETLE16(reader);
				reader += 2;
				break;

			CASEF(KMP_OP_SETKEYMOD2, "mask=%#.4" PRIx16 "\n", UNALIGNED_GETLE16(reader)) {
				u16 mask;
				mask = UNALIGNED_GETLE16(reader);
				reader += 2;
				if (reg_key == key && mod == mask)
					goto found_character;
				goto skip_character;
			}	break;

			CASEF(KMP_OP_SETKEYMOD, "mask=%#.2" PRIx8 "\n", *reader) {
				u8 mask;
				mask = *reader++;
				if (reg_key == key && mod == mask)
					goto found_character;
				goto skip_character;
			}	break;

			CASE(KMP_OP_SETPRESS) {
				if (reg_key == key && KEYMOD_ISNORMAL(mod)) {
found_character:
					switch (reg_enc) {

					CASEF(KMP_ENCODING_LATIN1, "ch='%" PRIc8 "'\n", *reader) {
						char utf8[2], *end;
						u8 latin1;
						latin1 = *reader++;
						if (latin1 <= 0x7f)
							cachable_character = (char)latin1;
						end    = unicode_writeutf8(utf8, latin1);
						result = (*printer)(arg, utf8, (size_t)(end - utf8));
					}	break;

					CASEF(KMP_ENCODING_UTF8, "ch='%#$q'\n", (size_t)unicode_utf8seqlen[*reader], reader) {
						u8 temp;
						temp = *reader;
						if (temp <= 0x7f)
							cachable_character = (char)temp;
						temp = unicode_utf8seqlen[temp];
						if unlikely(!temp)
							ERROR(error);
						result = (*printer)(arg, (char const *)reader, temp);
					}	break;

					CASEF(KMP_ENCODING_UTF32LE, "ch='%" PRIc32 "'\n", UNALIGNED_GETLE32(reader)) {
						u32 ch32;
						char utf8[UNICODE_UTF8_CURLEN], *end;
						ch32 = UNALIGNED_GETLE32(reader);
						goto do_print_ch32;
					CASEF(KMP_ENCODING_UTF32BE, "ch='%" PRIc32 "'\n", UNALIGNED_GETBE32(reader))
						ch32 = UNALIGNED_GETBE32(reader);
do_print_ch32:
						if (ch32 <= 0x7f)
							cachable_character = (char)ch32;
						end    = unicode_writeutf8(utf8, ch32);
						result = (*printer)(arg, utf8, (size_t)(end - utf8));
						break;
					CASEF(KMP_ENCODING_UTF16LE, "ch='%" PRIc16 "'\n", UNALIGNED_GETLE16(reader)) {
						u16 word;
						word = UNALIGNED_GETLE16(reader);
						goto do_check_surrogate;
					CASEF(KMP_ENCODING_UTF16BE, "ch='%" PRIc16 "'\n", UNALIGNED_GETBE16(reader))
						word = UNALIGNED_GETBE16(reader);
do_check_surrogate:
						if (word >= UTF16_HIGH_SURROGATE_MIN &&
						    word <= UTF16_HIGH_SURROGATE_MIN) {
							u16 hiword = UNALIGNED_GET16(reader + 2);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
							if (reg_enc == KMP_ENCODING_UTF16BE)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
							if (reg_enc == KMP_ENCODING_UTF16LE)
#endif
							{
								hiword = BSWAP16(hiword);
							}
							if unlikely(!(hiword >= UTF16_LOW_SURROGATE_MIN &&
							              hiword <= UTF16_LOW_SURROGATE_MIN))
								ERROR(error);
							ch32  = (u32)(word - UTF16_HIGH_SURROGATE_MIN) << 10;
							ch32 |= (u32)(hiword - UTF16_LOW_SURROGATE_MIN) & 0x3ff;
							ch32 += UTF16_SURROGATE_SHIFT;
						} else {
							if unlikely(word >= UTF16_LOW_SURROGATE_MIN &&
							            word <= UTF16_LOW_SURROGATE_MIN)
								ERROR(error);
							ch32 = word;
						}
					}	goto do_print_ch32;
					}	break;

					CASEF(KMP_ENCODING_MCS, "str=%q\n", reader) {
						size_t len = strlen((char const *)reader);
						result = (*printer)(arg, (char const *)reader, len);
					}	break;

					default: __builtin_unreachable();
					}
					/* Cache simple keys. */
					if (cachable_character && basic) {
						if (KEYMOD_ISNORMAL(mod)) {
							basic->bk_normal = cachable_character;
						} else if (KEYMOD_ISSHIFT(mod)) {
							basic->bk_shift = cachable_character;
						}
					}
					goto done;
				}
skip_character:
				switch (reg_enc) {

				CASEF(KMP_ENCODING_LATIN1, "ch='%" PRIc8 "'\n", *reader)
					++reader;
					break;
				CASEF(KMP_ENCODING_UTF8, "ch='%#$q'\n", (size_t)unicode_utf8seqlen[*reader], reader) {
					u8 len = unicode_utf8seqlen[*reader];
					if unlikely(!len)
						ERROR(error);
					reader += len;
				}	break;

				CASEF(KMP_ENCODING_UTF32LE, "ch='%" PRIc32 "'\n", UNALIGNED_GETLE32(reader))
				CASEF(KMP_ENCODING_UTF32BE, "ch='%" PRIc32 "'\n", UNALIGNED_GETBE32(reader))
					reader += 4;
					break;

				CASEF(KMP_ENCODING_UTF16LE, "ch='%" PRIc16 "'\n", UNALIGNED_GETLE16(reader)) {
					u16 word;
					word = UNALIGNED_GETLE16(reader);
					goto do_check_surrogate_skip;
				CASEF(KMP_ENCODING_UTF16BE, "ch='%" PRIc16 "'\n", UNALIGNED_GETBE16(reader))
					word = UNALIGNED_GETBE16(reader);
do_check_surrogate_skip:
					if (word >= UTF16_HIGH_SURROGATE_MIN &&
					    word <= UTF16_HIGH_SURROGATE_MIN) {
						u16 hiword = UNALIGNED_GET16(reader + 2);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
						if (reg_enc == KMP_ENCODING_UTF16BE)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
						if (reg_enc == KMP_ENCODING_UTF16LE)
#endif
						{
							hiword = BSWAP16(hiword);
						}
						if unlikely(!(hiword >= UTF16_LOW_SURROGATE_MIN &&
						              hiword <= UTF16_LOW_SURROGATE_MIN))
							ERROR(error);
						reader += 4;
					} else {
						if unlikely(word >= UTF16_LOW_SURROGATE_MIN &&
						            word <= UTF16_LOW_SURROGATE_MIN)
							ERROR(error);
						reader += 2;
					}
				}	break;

				CASEF(KMP_ENCODING_MCS, "str=%q\n", reader)
					reader = (byte_t *)strend((char const *)reader) + 1;
					break;

				default: __builtin_unreachable();
				}
				if (opcode == KMP_OP_SETPRESS)
					reg_key += KEY(0, 1);
			}	break;

			CASE(KMP_OP_SETSHIFT)
				if (reg_key == key && KEYMOD_ISSHIFT(mod))
					goto found_character;
				goto skip_character;

			CASE(KMP_OP_SETALTGR)
				if (reg_key == key && KEYMOD_ISALTGR(mod))
					goto found_character;
				goto skip_character;

			CASE(KMP_OP_NOP)
				break;

			default:
				ERROR(error);
			}
			break;

		CASEF(KMP_OP_FDEFLATIN, "pair='%c,%c'\n", 'a' + (opcode & 0x1f), 'A' + (opcode & 0x1f))
			if (reg_key == key) {
				if (KEYMOD_ISNORMAL(mod)) {
					cachable_character = 'a' + (opcode & 0x1f);
					result = (*printer)(arg, &cachable_character, 1);
					if (basic)
						basic->bk_normal = cachable_character;
					goto done;
				}
				if (KEYMOD_ISSHIFT(mod)) {
					cachable_character = 'A' + (opcode & 0x1f);
					result = (*printer)(arg, &cachable_character, 1);
					if (basic)
						basic->bk_normal = cachable_character;
					goto done;
				}
			}
			reg_key += KEY(0, 1);
			break;

		CASEF(KMP_OP_FDEFDIGIT, "pair='%c,%c'\n", '1' + (opcode & 0x1f), '!' + (opcode & 0x1f))
			if (reg_key == key) {
				if (KEYMOD_ISNORMAL(mod)) {
					cachable_character = '1' + (opcode & 0x1f);
					result = (*printer)(arg, &cachable_character, 1);
					if (basic)
						basic->bk_normal = cachable_character;
					goto done;
				}
				if (KEYMOD_ISSHIFT(mod)) {
					cachable_character = '!' + (opcode & 0x1f);
					result = (*printer)(arg, &cachable_character, 1);
					if (basic)
						basic->bk_normal = cachable_character;
					goto done;
				}
			}
			reg_key += KEY(0, 1);
			break;

		CASE(KMP_OP_FSETROW)
			reg_key = KEY((opcode & 0x1f), 0);
			break;

		CASE(KMP_OP_FSETCOL)
			reg_key = KEY(KEY_GETROW(reg_key), (opcode & 0x1f));
			break;

		default:
			ERROR(error);
		}
	}
error:
unknown:
	result = 0;
done:
	return result;
}


/* Wrapper for buffer-based translating, using snprintf()-like buffer printing.
 * NOTE: Upon success,  this function  will  optionally append  a  NUL-character
 *       if sufficient buffer space is available (`return < buflen'). Otherwise,
 *       when  `return == buflen',  no  trailing NUL-character  exists,  but the
 *       function still succeeds.
 * @param: buffer: The buffer to which to print translated characters.
 * @param: buflen: The given buffer size.
 * @return: 0 :    The given `key' cannot be translated with `mod'
 * @return: * :    The required number of buffer bytes. (excluding a trailing NUL-character) */
INTERN NONNULL((1, 4)) size_t
NOTHROW_NCX(CC libkeymap_translate_buf)(struct keymap *__restrict self,
                                        uint16_t key, uint16_t mod,
                                        /*utf-8*/ char *buffer, size_t buflen) {
	struct format_snprintf_data data;
	size_t result;
	data.sd_buffer = buffer;
	data.sd_bufsiz = buflen;
	result = (size_t)libkeymap_translate(self, key, mod,
	                                     &format_snprintf_printer,
	                                     &data);
	if (data.sd_bufsiz != 0)
		*data.sd_buffer = '\0';
	return result;
}



/* Open a memory-blob of a KMP (KeyboardMaP) file (see above for the file format specs)
 * NOTE: The  caller must ensure that a keymap blob  loaded form some file must end with at
 *       least 5 additional trailing 0-bytes (i.e. `blob_base[blob_size+{0,1,2,3,4}] == 0')
 * NOTE: Upon success, the caller must also ensure that `self->km_ext...+=(blob_base+blob_size)-self->km_ext'
 *       will  not be freed.  Alternatively, the caller may  replace `self->km_ext' with  a duplicate of that
 *       memory region and free it themself after finalization
 * @return: true:  Successfully loaded the given blob and initialized `self'
 * @return: false: Failed to open the blob (not a valid KMP file) */
INTERN NONNULL((1, 2)) bool
NOTHROW_NCX(CC libkeymap_openblob)(struct keymap *__restrict self,
                                   void const *blob_base,
                                   size_t blob_size) {
	Kmp_Header *hdr;
	Kmp_Data *data;
	if unlikely(blob_size <= sizeof(Kmp_Header))
		ERROR(nope);
	hdr = (Kmp_Header *)blob_base;
	if unlikely(hdr->h_magic[0] != KMP_MAG0 ||
	            hdr->h_magic[1] != KMP_MAG1 ||
	            hdr->h_magic[2] != KMP_MAG2 ||
	            hdr->h_magic[3] != KMP_MAG3)
		ERROR(nope);
	if unlikely(hdr->h_version > KMP_VERSION_CURRENT)
		ERROR(nope);
	if unlikely(hdr->h_hdrsize + offsetof(Kmp_Data, d_code) >= blob_size)
		ERROR(nope);
	data = (Kmp_Data *)((byte_t *)blob_base + hdr->h_hdrsize);
	if unlikely(data->d_zero != 0 && hdr->h_version != 0)
		ERROR(nope); /* This field only became mandatory-zero with version 1 */
	if unlikely(data->d_encoding > KMP_ENCODING_MAX)
		ERROR(nope);
	/* Initialize `self' */
	self->km_defencoding = data->d_encoding;
	self->km_ext         = data->d_code;
	bzero(self->km_basic, sizeof(self->km_basic));
	return true;
nope:
	return false;
}

DEFINE_PUBLIC_ALIAS(keymap_codesize, libkeymap_codesize);
DEFINE_PUBLIC_ALIAS(keymap_instrlen, libkeymap_instrlen);
DEFINE_PUBLIC_ALIAS(keymap_translate, libkeymap_translate);
DEFINE_PUBLIC_ALIAS(keymap_translate_buf, libkeymap_translate_buf);
DEFINE_PUBLIC_ALIAS(keymap_openblob, libkeymap_openblob);


DECL_END

#endif /* !GUARD_LIBKEYMAP_KEYMAP_C */
