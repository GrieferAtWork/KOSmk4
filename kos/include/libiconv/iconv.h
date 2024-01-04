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
#ifndef _LIBICONV_ICONV_H
#define _LIBICONV_ICONV_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#ifdef GUARD_LIBICONV_API_H
#define LIBICONV_EXPOSE_INTERNAL
#endif /* GUARD_LIBICONV_API_H */


#ifdef LIBICONV_EXPOSE_INTERNAL
#include <bits/crt/mbstate.h>
#endif /* LIBICONV_EXPOSE_INTERNAL */

__DECL_BEGIN

#define _ICONV_DECODE_OPAQUE_POINTERS 5
#define _ICONV_ENCODE_OPAQUE_POINTERS 5


#ifdef LIBICONV_EXPOSE_INTERNAL
struct iconv_codepage;
struct iconv_7l_codepage;
struct iconv_7h_codepage;
struct iconv_iso646_codepage;
struct iconv_stateful_codepage;
struct iconv_stateful_encode_range;
struct iconv_mbcs_codepage;
struct iconv_mbcs_byte2_range;

union iconv_decode_data {
	struct {
		__byte_t         u_pbc;   /* # of pending bytes in `u_pb' */
		__byte_t         u_pb[3]; /* Pending byte(s). */
		struct __mbstate u_16;    /* Surrogate storage for utf-16 input. */
#define _ICONV_DECODE_UTF_BOM_TEXT      0 /* In normal text */

#define _ICONV_DECODE_UTF_BOM16LE_B1_FE 1 /* UTF16LE-BOM: Expecting 0xFE */
#define _ICONV_DECODE_UTF_BOM16LE_B0_FF 2 /* UTF16LE-BOM: Expecting 0xFF */

#define _ICONV_DECODE_UTF_BOM16BE_B1_FF 1 /* UTF16BE-BOM: Expecting 0xFF */
#define _ICONV_DECODE_UTF_BOM16BE_B0_FE 2 /* UTF16BE-BOM: Expecting 0xFE */

#define _ICONV_DECODE_UTF_BOM32LE_B3_00 1 /* UTF32LE-BOM: Expecting 0x00 */
#define _ICONV_DECODE_UTF_BOM32LE_B2_00 2 /* UTF32LE-BOM: Expecting 0x00 */
#define _ICONV_DECODE_UTF_BOM32LE_B1_FE 3 /* UTF32LE-BOM: Expecting 0xFE */
#define _ICONV_DECODE_UTF_BOM32LE_B0_FF 4 /* UTF32LE-BOM: Expecting 0xFF */

#define _ICONV_DECODE_UTF_BOM32BE_B3_FF 1 /* UTF32BE-BOM: Expecting 0xFF */
#define _ICONV_DECODE_UTF_BOM32BE_B2_FE 2 /* UTF32BE-BOM: Expecting 0xFE */
#define _ICONV_DECODE_UTF_BOM32BE_B1_00 3 /* UTF32BE-BOM: Expecting 0x00 */
#define _ICONV_DECODE_UTF_BOM32BE_B0_00 4 /* UTF32BE-BOM: Expecting 0x00 */
		__byte_t         u_bom;   /* BOM State (for -BOM codecs; one of `_ICONV_DECODE_UTF_BOM*') */
	} idd_utf; /* For UTF-16 and UTF-32 input data. */

	struct iconv_codepage const        *idd_cp;    /* [1..1][const] Code page (for 8-bit codecs) */
	struct iconv_7l_codepage const     *idd_cp7l;  /* [1..1][const] Code page (for 7l codecs) */
	struct iconv_7h_codepage const     *idd_cp7h;  /* [1..1][const] Code page (for 7h codecs) */
	struct iconv_iso646_codepage const *idd_cp646; /* [1..1][const] Code page (for iso686 codecs) */

#define _ICONV_DECODE_UTF8_BOM_TEXT  0 /* Normal UTF-8 text. */
#define _ICONV_DECODE_UTF8_BOM_B2_BF 1 /* Expecting third byte (0xBF) */
#define _ICONV_DECODE_UTF8_BOM_B1_BB 2 /* Expecting second byte (0xBB) */
#define _ICONV_DECODE_UTF8_BOM_B0_EF 3 /* Expecting first byte (0xEF) */
	__byte_t idd_utf8_bom_state; /* UTF-8 BOM decode state. (one of `_ICONV_DECODE_UTF8_BOM_*') */

	struct {
		struct __mbstate ce_utf8;   /* UTF-8 input multi-byte state */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_INIT  0  /* Expect first character after \ */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_HEX   1  /* Encountered \x */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_HEX_1 2  /* Encountered \x<?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_HEX_2 3  /* Encountered \x<?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_OCT_1 4  /* Encountered \<0-7> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_OCT_2 5  /* Encountered \<0-7><0-7> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U16   6  /* Encountered \u */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U16_1 7  /* Encountered \u<?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U16_2 8  /* Encountered \u<?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U16_3 9  /* Encountered \u<?><?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32   10 /* Encountered \U */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32_1 11 /* Encountered \U<?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32_2 12 /* Encountered \U<?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32_3 13 /* Encountered \U<?><?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32_4 14 /* Encountered \U<?><?><?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32_5 15 /* Encountered \U<?><?><?><?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32_6 16 /* Encountered \U<?><?><?><?><?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_U32_7 17 /* Encountered \U<?><?><?><?><?><?><?> */
#define _ICONV_DECODE_CESCAPE_ESC_MODE_SLF   18 /* Encountered \<CR> (skip <LF> if it's the next character) */
		__uint8_t ce_esc;    /* [valid_if(_ICONV_CDECODE_F_ESCAPE)] Escape mode (one of `_ICONV_DECODE_CESCAPE_ESC_MODE_*') */
		union { /* Escape-mode-specific data */
			__uint8_t       ce_esc_value; /* Value for \x and \0 */
			__CHAR16_TYPE__ ce_esc_u16;   /* Value for \u */
			__CHAR32_TYPE__ ce_esc_u32;   /* Value for \U */
		};
	} idd_cesc; /* c-escape */

	struct {
		struct __mbstate xe_utf8; /* UTF-8 input multi-byte state */
#define _ICONV_DECODE_XML_TXT 0 /* Basic text-mode */
#define _ICONV_DECODE_XML_OSM 1 /* Skip an optional ';' */
#define _ICONV_DECODE_XML_AND 2 /* Encountered & */
#define _ICONV_DECODE_XML_PND 3 /* Encountered &# */
#define _ICONV_DECODE_XML_DEC 4 /* Encountered &#<0-9> */
#define _ICONV_DECODE_XML_HEX 5 /* Encountered &#x */
#define _ICONV_DECODE_XML_ENT 6 /* Encountered &<alnum> */
		__uint8_t      xe_mode; /* Current state machine mode (one of `_ICONV_DECODE_XML_*') */
		union {
			__CHAR32_TYPE__ xe_chr; /* _ICONV_DECODE_XML_DEC, _ICONV_DECODE_XML_HEX: Escaped character */
			struct {
				__uint8_t   e_len; /* # of entity characters already written. */
				char const *e_str; /* [0..xe_elen] Entity characters already written. This string points
				                    * into  the internal database  of known xml  entities and is updated
				                    * every time yet another  character is encountered. Internally,  the
				                    * actual type of this field should be `xml_entity_t const *' */
			} xe_ent; /* _ICONV_DECODE_XML_ENT */
		};
	} idd_xml; /* xml-escape */

	struct {
#define _ICONV_DECODE_URI_TXT   0 /* Inside of normal text */
#define _ICONV_DECODE_URI_PCT   1 /* Encountered % */
#define _ICONV_DECODE_URI_PCT_1 2 /* Encountered %<?> */
		__uint8_t ue_mode; /* Current state machine mode (one of `_ICONV_DECODE_URI_*') */
		__uint8_t ue_chr;  /* In `_ICONV_DECODE_URI_PCT_1': already-parsed hex nibble, shifted left by 4 */
	} idd_uri; /* uri-escape */

	struct {
#define _ICONV_DECODE_BASE64_T0  0 /* Expecting first 6-bit character of triple  (......11 11112222 22333333) */
#define _ICONV_DECODE_BASE64_T6  1 /* Expecting second 6-bit character of triple (AAAAAA.. ....2222 22333333) */
#define _ICONV_DECODE_BASE64_T12 2 /* Expecting third 6-bit character of triple  (AAAAAABB BBBB.... 22333333) (byte "AAAAAABB" was already emit) */
#define _ICONV_DECODE_BASE64_T18 3 /* Expecting fourth 6-bit character of triple (AAAAAABB BBBBCCCC CC......) (byte "AAAAAABB" and "BBBBCCCC" were already emit) */
#define _ICONV_DECODE_BASE64_EQ2 4 /* Expecting second '=' after `AA=' */
#define _ICONV_DECODE_BASE64_EOF 5 /* End-of-file (refuse to parse further input) */
		__uint8_t b64_state;     /* Current state machine mode (one of `_ICONV_DECODE_URI_*') */
		__uint8_t b64_vprev;     /* Partial byte data from previous character.
		                          * _ICONV_DECODE_BASE64_T6:  v0 << 2
		                          * _ICONV_DECODE_BASE64_T12: v1 << 4
		                          * _ICONV_DECODE_BASE64_T18: v2 << 6 */
	} idd_base64; /* base64-escape */

	__uint8_t idd_hex; /* For "hex": 0x00-0xf0 when parsing the second nibble; 0x01 when parsing the first. */

	struct {
#define _ICONV_DECODE_STATEFUL_SB  0 /* Single-byte */
#define _ICONV_DECODE_STATEFUL_DB0 1 /* Double-byte (expecting first) */
#define _ICONV_DECODE_STATEFUL_DB1 2 /* Double-byte (expecting second) */
		__uint8_t                             sf_state; /* Current state (one of `_ICONV_DECODE_STATEFUL_*') */
		__uint8_t                             sf_b0;    /* [valid_if(_ICONV_DECODE_STATEFUL_DB1)] Previous byte. */
		__uint8_t                            _sf_pad[sizeof(void *) - 2];
		struct iconv_stateful_codepage const *sf_cp;    /* [1..1][const] Code page. */
		__uint16_t const                     *sf_rab;   /* [1..1][const][== iconv_stateful_codepage__isc_rab(sf_cp)] */
		__CHAR16_TYPE__ const                *sf_u16;   /* [1..1][const][== iconv_stateful_codepage__isc_u16(sf_cp)] */
		__uint32_t const                     *sf_u32;   /* [1..1][const][== iconv_stateful_codepage__isc_u32(sf_cp)] */
	} idd_stateful; /* stateful codecs: ibm(930|933|935|937|939|1364|1371|1388|1390|1399) */

	struct {
		struct iconv_mbcs_codepage const    *mc_cp; /* [1..1][const] Multi-byte code page. */
		struct iconv_mbcs_byte2_range const *mc_b2; /* [0..1] When non-NULL, expecting second byte; else: first byte.
		                                             * In the case of the second byte, this is the first range  which
		                                             * which to try and decode it (s.a. `libiconv-mbcs.so' internals) */
	} idd_mbcs;

	void *__idd_pad[_ICONV_DECODE_OPAQUE_POINTERS];
};

union iconv_encode_data {
	struct {
		struct __mbstate ied_utf8; /* UTF-8 input data buffer. */
		union {
			struct iconv_codepage const        *ied_cp;     /* [1..1][const] Code page (for 8-bit codecs) */
			struct iconv_7l_codepage const     *ied_cp7l;   /* [1..1][const] Code page (for 7l codecs) */
			struct iconv_7h_codepage const     *ied_cp7h;   /* [1..1][const] Code page (for 7h codecs) */
			struct iconv_iso646_codepage const *ied_cp646;  /* [1..1][const] Code page (for iso686 codecs) */
			struct iconv_mbcs_codepage const   *ied_cpmbcs; /* [1..1][const] Code page (for mbcs codecs). */

			struct {
#define _ICONV_ENCODE_STATEFUL_SB     0 /* Single-byte */
#define _ICONV_ENCODE_STATEFUL_DB     1 /* Double-byte */
#define _ICONV_ENCODE_STATEFUL_DB_2CH 2 /* Double-byte (now handling second second character of double-uni sequence) */
				__uint8_t                                 sf_state;         /* Current state (one of `_ICONV_ENCODE_STATEFUL_*') */
				__uint8_t                                _sf_pad[sizeof(void *) - 1];
				struct iconv_stateful_codepage const     *sf_cp;            /* [1..1][const] Code page. */
				struct iconv_stateful_encode_range const *sf_encode_ranges; /* [1..1][const][== iconv_stateful_codepage__isc_encode_ranges(sf_cp)] */
				struct iconv_stateful_2char_encode const *sf_2char;         /* [1..1][valid_if(_ICONV_ENCODE_STATEFUL_DB_2CH)] */
			} ied_stateful; /* stateful codecs: ibm(930|933|935|937|939|1364|1371|1388|1390|1399) */

			struct {
#define _ICONV_ENCODE_BASE64_PEND_DATA 0x3f /* Mask of pending bits (starting at most significant bit) */
#define _ICONV_ENCODE_BASE64_PEND_SIZE 0xc0 /* # of pending bits, divided by 2 (meaning 0, 2, 4 or 6) */
#define _ICONV_ENCODE_BASE64_PEND_S0   0x00 /* 0 pending bits */
#define _ICONV_ENCODE_BASE64_PEND_S2   0x40 /* 2 pending bits */
#define _ICONV_ENCODE_BASE64_PEND_S4   0x80 /* 4 pending bits */
				__uint8_t b64_pend; /* Pending byte */
			} ied_base64; /* base64-encode */

			__BOOL ied_utf_bom_printed; /* True if the UTF* BOM was printed. */
		};
	};

	void *__ied_pad[_ICONV_ENCODE_OPAQUE_POINTERS];
};
#endif /* LIBICONV_EXPOSE_INTERNAL */


/*
 * ICONV: Using this API, you can make use of KOS's pformatprinter APIs to
 *        construct  transparent descriptors for  converting text from one
 *        codec to another.
 *        For this purpose, all functions either convert to, or from UTF-8,
 *        since that's the default encoding used by the KOS kernel, and all
 *        KOS system interfaces in general.
 *        However, you can easily connect an iconv_decode to  iconv_encode
 *        in order to convert from any codec to UTF-8, and directly follow
 *        up by converting to some other codec.
 *
 * Usage (decode; aka CODEC -> UTF-8):
 * >> struct iconv_decode decode;
 * >> struct iconv_printer input;
 * >> iconv_decode_init(&decode, &input, "cp437", &file_printer, stdout);
 * >> format_printf(input.ii_printer, input.ii_arg,
 * >>               "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n"
 * >>               "\xBA This is cp437 text \xBA\n"
 * >>               "\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n"
 * >>               );
 *
 *
 * Usage (encode; aka UTF-8 -> CODEC):
 * >> char buf[512];
 * >> struct format_snprintf_data cp437_printer;
 * >> format_snprintf_init(&cp437_printer, buf, sizeof(buf));
 * >>
 * >> struct iconv_printer input;
 * >> struct iconv_encode encode;
 * >> iconv_encode_init(&encode, &input, "cp437", &format_snprintf_printer, &cp437_printer);
 * >> format_printf(input.ii_printer, input.ii_arg,
 * >>               "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n"
 * >>               "\u2551 This is Unicode text \u2551\n"
 * >>               "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n"
 * >>               );
 * >>
 * >> size_t len = (size_t)(cp437_printer.sd_buffer - buf);
 * >> printf("Encoded into %" PRIuSIZ " bytes\n", len);
 * >> printf("%$[hex]\n", len, buf);
 *
 *
 *
 * !!! WARNING !!!
 *
 * libiconv  may use pformatprinter,  which documents its `data'  argument to be UTF-8.
 * This done _NOT_ (necessarily) apply for printers used/provided by libiconv! Instead,
 * the  codec of the data accepted by printers  depends on the context. After all, it's
 * the  purpose  of this  library to  facilitate  conversion between  different codecs.
 * Note however that it gets  a bit confusing when  dealing with mult-byte codecs  such
 * as  UTF16. In this case, input printers still work byte-wise, will require more than
 * one  byte to produce any output. Intermediate data is always stored in the encode or
 * decode descriptor, but for better understanding, take a look at this example:
 *
 * >> struct iconv_decode decode;
 * >> struct iconv_printer in;
 * >> iconv_decode_init(&decode, &in, "utf-16", &file_printer, stdout);
 * >> char16_t u16_text[] = u"Hello";
 * >> (*in.ii_printer)(in.ii_arg, (char *)u16_text, 10); // 10
 *
 * See how `10' is the size (!not length!) of the string (excluding the trailing NUL),
 * and also how  we have  to cast `u16_text'  to `char *'?  Technically speaking,  the
 * pformatprinter prototype needed for libiconv  decode input and encode output  would
 * look like this:
 *
 * >> // Should probably also be named something like `pdatasink'
 * >> typedef ssize_t (*pformatprinter)(void *arg, void const *__restrict data, size_t size);
 *
 * Because the format  in which codec-specific  data is presented  is dependent on  said
 * codec. However, to  keep things simple  and make it  a little more  obvious that  you
 * can use other pformatprinter-compatible interfaces everywhere, that prototype remains
 * accepted everything, even when it's not entirely correct.
 *
 *
 * pformatprinter return values:
 *  - All encode/decode operations always require the user to provide an output  printer
 *    In  turn, the return  value of the input  printers provided to  the caller are the
 *    accumulations of calls to the output printer, with the usual handling for negative
 *    values.
 *    The only addition made is that `-<number-of-input-bytes-not-parsed>' is  returned
 *    in  `ICONV_ERR_ERRNO'-mode when the input sequence cannot be decoded. This number
 *    relates to the `datasize' argument passed in the last call to the decoder's input
 *    function, thus allowing the  caller to figure out  the exact byte location  where
 *    the error happened:
 *    >> // Decode `data' and output to `out_printer'. Decode errors are handled locally.
 *    >> ssize_t decode_and_print(pformatpritner out_printer, void *out_arg,
 *    >>                          char const *data, size_t size,
 *    >>                          char const *data_codec) {
 *    >>     ssize_t result;
 *    >>     struct iconv_decode decode;
 *    >>     struct iconv_printer in;
 *    >>     iconv_decode_init(&decode, &in, data_codec, out_printer, out_arg,
 *    >>                       ICONV_ERR_ERROR); // Error-only (don't modify `errno')
 *    >>     result = (*in.ii_printer)(in.ii_arg, data, size);
 *    >>     if (result < 0) {
 *    >>         // This can happen for one of 2 reason: Either there was a decode error,
 *    >>         // or the `out_printer' given by our caller returned a negative value
 *    >>         // that is equal to `result'.
 *    >>         // If it's the former, `ICONV_HASERR' is set. If not, that flag will
 *    >>         // still be cleared. But note the case where `data_codec' is `utf-8'!
 *    >>         // In that case, error handling will still be up to `out_printer',
 *    >>         // since the library handles the INPUT_CODEC=OUTPUT_CODEC by making it
 *    >>         // so that `in.ii_printer == out_printer'.
 *    >>         // IOW: `out_printer' should still do its own error checking and
 *    >>         //      shouldn't blindly believe that its input is valid UTF-8!
 *    >>         if (decode.icd_flags & ICONV_HASERR) {
 *    >>             size_t error_offset = (size_t)(size + result);
 *    >>             fprintf(stderr, "Failed to decode byte at offset %" PRIuSIZ ": %#" PRIx8 "\n"
 *    >>                     error_offset, data[error_offset]);
 *    >>             abort();
 *    >>         }
 *    >>     } else {
 *    >>         // In this case, `result' is equal to the sum of return vaules from `out_printer'
 *    >>     }
 *    >>     return result;
 *    >> }
 *    The  same also goes for encode functions, though in this case a negative offset from
 *    the  end of the input buffer is returned  both when input data isn't valid UTF-8, in
 *    which  case the offset points to the start  of the byte sequence that doesn't form a
 *    valid UTF-8 character,  _OR_ to the  start of  a _valid_ utf-8  sequence, that  just
 *    happens to not be encodable  in the target codec.  Which of these two  possibilities
 *    is the case can't be  determined by the encoder's flags  alone, and can't easily  be
 *    tested either since doing so may rely on the internal mbstate_t of the encoder which
 *    isn't exposed and might be non-empty in case the invalid/unencodable utf-8  sequence
 *    isn't fully contained within the same data blob.
 *
 */



/* ICONV decode/encode flags. */
#define ICONV_ERRMASK       0x000f /* Mask for error code. */
#define ICONV_ERR_ERRNO          0 /* Set the `ICONV_HASERR' flag, make `errno=EILSEQ', and have the pformatprinter
                                    * function return `-<number-of-input-bytes-not-parsed>', thus signaling that an
                                    * error happened. This will happen forever until the  iconv_encode/iconv_decode
                                    * object is re-initialized (or you  clear `ICONV_HASERR', though you  shouldn't
                                    * do that since it doesn't re-initialize other internal components).
                                    * NOTE: When  `ICONV_HASERR' gets set and a negative value is returned, there
                                    *       is also a guaranty that the  output printer didn't return a  negative
                                    *       value, meaning you can use the `ICONV_HASERR' flag to determine where
                                    *       an  error came from, and the actual  returned value to figure out how
                                    *       much of the (last chunk of) input data could not be parsed. */
#define ICONV_ERR_ERROR          1 /* Same as `ICONV_ERR_ERRNO', but leave `errno' unchanged. */
#define ICONV_ERR_DISCARD        2 /* Data that cannot be encoded/decoded is silently discarded. */
#define ICONV_ERR_REPLACE        3 /* Replace characters that cannot be encoded/decoded with ascii  '?'
                                    * If that character also doesn't exist in the target codec (this is
                                    * only  the case  for `iconv_encode'),  then use  some other codec-
                                    * specific replacement character. */
#define ICONV_ERR_IGNORE         4 /* Forward data that cannot be encoded/decoded as-is, but note that
                                    * doing this will most definitely result in data corruption as the
                                    * result will be encoded data mixed with data that's not encoded. */
#define ICONV_ERR_TRANSLIT  0x0010 /* FLAG: Try to perform transliteration (s.a. `unicode_fold(3)') when
                                    *       a unicode character cannot be  encoded in the target  codec.
                                    *       If successful, characters  will be replaced  by one or  more
                                    *       similar-looking  characters that can (hopefully) be encoded.
                                    * NOTE: This flag is meaningless for `iconv_decode', since anything
                                    *       can be encoded in the  UTF-8 stream generated by  decoders. */
#define ICONV_HASERR        0x0020 /* Used for `ICONV_ERR_ERRNO': keep setting EILSEQ and returning `-datasize'. */
/* NOTE: Other  flags  may have  arbitrary meaning  depending  on the  codec used.
 *       None of  them should  be set  when initializing  an encoder/decoder,  and
 *       should be considered to have undefined dispositions after initialization. */


#ifdef LIBICONV_EXPOSE_INTERNAL
/* For c-escape codecs (encode only) */
#define _ICONV_CENCODE_NOQUOTE 0x0100 /* [const] Flag: don't emit quotes. */
#define _ICONV_CENCODE_POSTHEX 0x0200 /* Flag: Immediately after a \xAB sequence.
                                       * iow: follow-up 0-9, a-f, A-F must also be escaped, or a new string must be started). */
#define _ICONV_CENCODE_POSTOCT 0x0400 /* Flag: Immediately after a \0-\77 sequence (but not \777; i.e. only for 1 or 2 oct digits).
                                       * iow: follow-up 0-7 must also be escaped, or a new string must be started). */
#define _ICONV_CENCODE_INQUOTE 0x0800 /* Flag: a " or ' has been printed. */
#define _ICONV_CENCODE_USECHAR 0x1000 /* Flag: escape using ' instead of ". */
#define _ICONV_CENCODE_NOUNICD 0x2000 /* Flag: Don't escape \u or \U; interpret input as raw bytes and print \xAB sequences. */

/* For c-escape codecs (decode only). NOTE: c-escape decode expects input to be UTF-8!
 * Initial  state ("-bytes" suffix is ignored in codecs when it comes to decoding, and
 * only affects encoding where it causes \u and \U to be replaced by \x):
 *    - "c-escape":     _ICONV_CDECODE_ST_UNDEF
 *    - "c-escape-str": _ICONV_CDECODE_ST_STR
 *    - "c-escape-chr": _ICONV_CDECODE_ST_CHR
 * NOTE: "c-escape-str" and "c-escape-chr" will both skip over whitespace that  appears
 *       outside of '- or "-pairs, but will stop and indicate an error when a non-space
 *       character is encountered outside of the actual string.
 *       Similarly, "c-escape" will stop and indicate an  error when an unescaped " or  '
 *       character is encountered.  When used with  `ICONV_ERR_ERROR', this behavior  can
 *       be used to not just parse, but find  the end end of a string literal while  also
 *       concatenating  (unless "c-escape"  is used)  multiple consecutive  strings as is
 *       described  by the C standard (where >"foo" "bar"< is the same as >"foobar"<, and
 *       the   "c-escape-str"  codec   will  decode   >"foo"  "bar"<   in  its  entirety)
 *       But  note that unescaped line-feeds will also  cause errors, though in this case
 *       the internal shift-state will be non-zero, such that after an error you can test
 *       if it happened because the string was  fully parsed, or because a line-feed  was
 *       found in the middle of the string:
 *       >> if (iconv_decode_isshiftzero(&decode)) {
 *       >>     // String ended normally; error position points at the
 *       >>     // first non-space character after the string ended.
 *       >> } else {
 *       >>     // Invalid string (e.g. unescaped line-feed in the middle)
 *       >>     // The error position points at the bad character (e.g. the line-feed)
 *       >>     // Another example would be an illegal escape sequence, like \p or \x1234567
 *       >> }
 */
#define _ICONV_CDECODE_F_ONESTR 0x0080 /* Only parse a single string or character. */
#define _ICONV_CDECODE_STMASK   0xff00 /* Mask for state. */
#define _ICONV_CDECODE_ST_RAW   0x0000 /* Raw string type (no unescaped quotes allowed) */
#define _ICONV_CDECODE_ST_STRIN 0x0100 /* "-string (inside; linefeed characters will cause errors) */
#define _ICONV_CDECODE_ST_CHRIN 0x0200 /* '-string (inside; linefeed characters will cause errors) */
#define _ICONV_CDECODE_ST_ALLIN 0x0300 /* Inside some undefined string (where neither ' nor " must be escaped) */
#define _ICONV_CDECODE_ST_STR   0x0400 /* "-string (outside) */
#define _ICONV_CDECODE_ST_CHR   0x0500 /* '-string (outside) */
#define _ICONV_CDECODE_ST_UNDEF 0x0600 /* Unknown  string type; determine based on first fed character. Switches to
                                        * _ICONV_CDECODE_ST_RAW, _ICONV_CDECODE_ST_CHRIN or _ICONV_CDECODE_ST_STRIN */
#define _ICONV_CDECODE_F_ESCAPE 0x0800 /* Flag: currently inside of an escape sequence. */
/* Should "normal" characters be copied to output; iow: are we inside of a string? */
#define _ICONV_CDECODE_SHOULD_FLUSH(st) ((st) <= _ICONV_CDECODE_ST_ALLIN)
#endif /* LIBICONV_EXPOSE_INTERNAL */


struct iconv_printer {
	__pformatprinter ii_printer; /* [1..1] Printer. */
	void            *ii_arg;     /* [?..1] Printer cookie. */
};

/************************************************************************/
/* ICONV Decode  (aka. <Some-Codec> --> UTF-8)                          */
/************************************************************************/
struct iconv_decode {
	/* Convert from an arbitrary codec to UTF-8 */
	struct iconv_printer    icd_output; /* [1..1][in][const] Output printer. */
	__UINTPTR_HALF_TYPE__   icd_flags;  /* [const] Error mode and flags. */
#ifdef LIBICONV_EXPOSE_INTERNAL
	__UINTPTR_HALF_TYPE__   icd_codec;  /* [const] Internal codec ID. (s.a. `iconv_codec_t') */
	union iconv_decode_data icd_data;   /* Internal data. */
#else /* LIBICONV_EXPOSE_INTERNAL */
	__UINTPTR_HALF_TYPE__ __icd_codec;  /* [const] Internal codec ID. (s.a. `iconv_codec_t') */
	void                 *__icd_opaque[_ICONV_DECODE_OPAQUE_POINTERS]; /* [?..?] Codec-specific data fields. */
#endif /* !LIBICONV_EXPOSE_INTERNAL */
};


/* Initialize the given iconv decoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:             [in|out] iconv decode controller.
 * @param: input_codec_name: [in]  The name of the codec in which input data will be presented.
 * @param: input:            [out] Location  where to write callback+cookie for data input.
 *                                 The written function+cookie may only be used for as long
 *                                 as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `input_codec_name' */
typedef __ATTR_NONNULL_T((1, 2, 3)) int
__NOTHROW_NCX_T(LIBICONV_CC *_PICONV_DECODE_INIT)(/*in|out*/ struct iconv_decode *__restrict self,
                                                  /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                                  /*in*/ char const *__restrict input_codec_name);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(LIBICONV_CC _iconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                              /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                              /*in*/ char const *__restrict input_codec_name);
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(iconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                 /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                 /*in*/ char const *__restrict input_codec_name,
                                 __pformatprinter output_printer, /* Accepting `UTF-8' */
                                 void *output_printer_arg,
                                 int error_mode __DFL(ICONV_ERR_ERRNO)) {
	self->icd_output.ii_printer = output_printer;
	self->icd_output.ii_arg     = output_printer_arg;
	self->icd_flags             = (__UINTPTR_HALF_TYPE__)(unsigned int)error_mode;
	return _iconv_decode_init(self, input, input_codec_name);
}
#endif /* LIBICONV_WANT_PROTOTYPES */

/* Check  if the given decoder is in its default (zero) shift state. If it isn't,
 * then that must mean that it's still waiting for more input data to arrive, and
 * that  you should either feed it said data,  or deal with the fact that there's
 * something missing in your input.
 * WARNING: This  function DOESN'T work  when the given decoder  is used to parse
 *          UTF-8 input! This is because special optimizations are performed when
 *          decoding  UTF-8 (since  decoders also  always output  UTF-8). In this
 *          case this function will always return `true'
 * Hint: the optimization is that  `iconv_decode_init:input == self->icd_output',
 *       so if you want to programmatically handle this case you can check for it
 *       by doing `self->icd_output.ii_printer == :input->ii_printer', where  the
 *       given `:input' is the one filled in by `iconv_decode_init(3)' */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
__NOTHROW_NCX_T(LIBICONV_CC *PICONV_DECODE_ISSHIFTZERO)(struct iconv_decode const *__restrict self);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(LIBICONV_CC iconv_decode_isshiftzero)(struct iconv_decode const *__restrict self);
#endif /* LIBICONV_WANT_PROTOTYPES */
/************************************************************************/







/************************************************************************/
/* ICONV Encode  (aka. UTF-8 --> <Some-Codec>)                          */
/************************************************************************/
struct iconv_encode {
	/* Convert from UTF-8 to an arbitrary codec */
	struct iconv_printer    ice_output; /* [1..1][in][const] Output printer. */
	__UINTPTR_HALF_TYPE__   ice_flags;  /* [const] Error mode and flags. */
#ifdef LIBICONV_EXPOSE_INTERNAL
	__UINTPTR_HALF_TYPE__   ice_codec;  /* [const] Internal codec ID. (s.a. `iconv_codec_t') */
	union iconv_encode_data ice_data;   /* Internal data. */
#else /* LIBICONV_EXPOSE_INTERNAL */
	__UINTPTR_HALF_TYPE__ __ice_codec;  /* [const] Internal codec ID. (s.a. `iconv_codec_t') */
	void                 *__ice_opaque[_ICONV_ENCODE_OPAQUE_POINTERS]; /* [?..?] Codec-specific data fields. */
#endif /* !LIBICONV_EXPOSE_INTERNAL */
};


/* Initialize the given iconv encoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:              [in|out] iconv encode controller.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location  where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `output_codec_name' */
typedef __ATTR_NONNULL_T((1, 2, 3)) int
__NOTHROW_NCX_T(LIBICONV_CC *_PICONV_ENCODE_INIT)(/*in|out*/ struct iconv_encode *__restrict self,
                                                  /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                                  /*in*/ char const *__restrict output_codec_name);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(LIBICONV_CC _iconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                              /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                              /*in*/ char const *__restrict output_codec_name);
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(iconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                 /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                 /*in*/ char const *__restrict output_codec_name,
                                 __pformatprinter output_printer, /* Accepting `output_codec_name' */
                                 void *output_printer_arg,
                                 int error_mode __DFL(ICONV_ERR_ERRNO)) {
	self->ice_output.ii_printer = output_printer;
	self->ice_output.ii_arg     = output_printer_arg;
	self->ice_flags             = (__UINTPTR_HALF_TYPE__)(unsigned int)error_mode;
	return _iconv_encode_init(self, input, output_codec_name);
}
#endif /* LIBICONV_WANT_PROTOTYPES */

/* Reset the internal shift state to its  default and print the associated byte  sequence
 * to the output printer of the encode descriptor, returning the sum of its return values
 * or the first negative return value.
 * This  function should be  called once all input  data has been  printed and will ensure
 * that input didn't end with an incomplete byte sequence, and that output doesn't contain
 * any unmatched shift-state changes.
 * Simply  call this once you're out of input  and treat its return value like you're
 * treating the return values of the input printer returned by `iconv_encode_init(3)' */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBICONV_CC *PICONV_ENCODE_FLUSH)(struct iconv_encode *__restrict self);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_NONNULL((1)) __ssize_t LIBICONV_CC
iconv_encode_flush(struct iconv_encode *__restrict self);
#endif /* LIBICONV_WANT_PROTOTYPES */

/* Check if UTF-8 input taken by the given encoder is in its default (zero) shift
 * state. If it isn't, then that must mean that it's still waiting for more UTF-8
 * data to arrive, and that you should either feed it said data, or deal with the
 * fact that there's something missing in your input.
 * WARNING: This function DOESN'T work when  the given encoder is targeting  UTF-8.
 *          This is because special optimizations are performed when encoding UTF-8
 *          (since  encoder also always  takes UTF-8 as input).  In this case, this
 *          function will always return `true';
 * - s.a. `union iconv_encode_data::ied_utf8'
 * @return: true:  UTF-8 input is in a zero-shift state.
 * @return: false: The encoder is still expecting more UTF-8 input. */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
__NOTHROW_NCX_T(LIBICONV_CC *PICONV_ENCODE_ISINPUTSHIFTZERO)(struct iconv_encode const *__restrict self);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(LIBICONV_CC iconv_encode_isinputshiftzero)(struct iconv_encode const *__restrict self);
#endif /* LIBICONV_WANT_PROTOTYPES */
/************************************************************************/







/************************************************************************/
/* ICONV Transcode  (aka. <Some-Codec> --> <Some-Codec>)                */
/************************************************************************/
struct iconv_transcode {
	struct iconv_decode it_decode; /* Decoder */
	struct iconv_encode it_encode; /* Encoder */
};

/* The  combination  of the  encode+decode functions  into  a single  one which
 * allows  for conversion from an arbitrary codec into another arbitrary codec.
 * This is pretty much just a convenience wrapper around the other 2 functions,
 * and you can  easily tell as  much if you  were to look  at this one's  impl.
 * @param: self:              [in|out] iconv encode/decode controller.
 * @param: input_codec_name:  [in]  The name of the codec in which input data will be presented.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location  where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `input_codec_name' or `output_codec_name' */
typedef __ATTR_NONNULL_T((1, 2, 3, 4)) int
__NOTHROW_NCX_T(LIBICONV_CC *_PICONV_TRANSCODE_INIT)(/*in|out*/ struct iconv_transcode *__restrict self,
                                                     /*out*/ struct iconv_printer *__restrict input,   /* Accepts `input_codec_name' */
                                                     /*in*/ char const *__restrict input_codec_name,   /* For decode */
                                                     /*in*/ char const *__restrict output_codec_name); /* For encode */
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_NONNULL((1, 2, 3, 4)) int
__NOTHROW_NCX(LIBICONV_CC _iconv_transcode_init)(/*in|out*/ struct iconv_transcode *__restrict self,
                                                 /*out*/ struct iconv_printer *__restrict input,   /* Accepts `input_codec_name' */
                                                 /*in*/ char const *__restrict input_codec_name,   /* For decode */
                                                 /*in*/ char const *__restrict output_codec_name); /* For encode */
__FORCELOCAL __ATTR_NONNULL((1, 2, 3, 4)) int
__NOTHROW_NCX(iconv_transcode_init)(/*in|out*/ struct iconv_transcode *__restrict self,
                                    /*out*/ struct iconv_printer *__restrict input,  /* Accepts `input_codec_name' */
                                    /*in*/ char const *__restrict input_codec_name,  /* For decode */
                                    /*in*/ char const *__restrict output_codec_name, /* For encode */
                                    __pformatprinter output_printer,                 /* Accepting `output_codec_name' */
                                    void *output_printer_arg,
                                    int error_mode __DFL(ICONV_ERR_ERRNO)) {
	self->it_encode.ice_output.ii_printer = output_printer;
	self->it_encode.ice_output.ii_arg     = output_printer_arg;
	self->it_encode.ice_flags             = (__UINTPTR_HALF_TYPE__)(unsigned int)error_mode;
	return _iconv_transcode_init(self, input, input_codec_name, output_codec_name);
}
#endif /* LIBICONV_WANT_PROTOTYPES */
/************************************************************************/






__DECL_END

#endif /* !_LIBICONV_ICONV_H */
