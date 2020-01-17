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
#ifdef __INTELLISENSE__
#include "generator.c"
#define MODE_DECODE 1
//#define MODE_ZERO 1
#endif

#if (defined(MODE_DECODE) + defined(MODE_ZERO)) != 1
#error "Must define exactly one of `MODE_DECODE, MODE_ZERO'"
#endif


#ifdef MODE_DECODE
#define IF_DECODE(...) __VA_ARGS__
#define IF_ZERO(...)   /* nothing */
#else                  /* MODE_DECODE */
#define IF_DECODE(...) /* nothing */
#define IF_ZERO(...) __VA_ARGS__
#endif /* !MODE_DECODE */


#ifdef MODE_ZERO
#define FUNC(x) x##_zero
#elif defined(MODE_DECODE)
#define FUNC(x) x
#endif

DECL_BEGIN



#ifndef LIBJSON_EMPTY_STRING_DEFINED
#define LIBJSON_EMPTY_STRING_DEFINED 1
INTDEF char const libjson_empty_string[1];
#endif /* !LIBJSON_EMPTY_STRING_DEFINED */



INTERN
	IF_DECODE(NONNULL((1, 2, 3, 4)))
	IF_ZERO  (NONNULL((1, 2, 3)))
	int
NOTHROW_NCX(CC FUNC(libjson_decode_INTO))(IF_DECODE(struct json_parser *__restrict parser, )
                                          byte_t **__restrict preader,
                                          void *__restrict dst_base,
                                          void *__restrict dst,
                                          uint8_t type
                                          IF_DECODE(, unsigned int gen_flags)) {
	IF_DECODE(int result;)
	IF_DECODE((void)gen_flags;)
	switch (type) {

	case JSON_TYPE_BOOLBIT(0) ... JSON_TYPE_BOOLBIT(7): {
		uint8_t mask;
		IF_DECODE(bool value;)
		mask = (uint8_t)1 << (type - JSON_TYPE_BOOLBIT(0));
#ifdef MODE_DECODE
		result = libjson_parser_getbool(parser, &value);
		if likely(result == JSON_ERROR_OK) {
			if (value)
				*(uint8_t *)dst |= mask;
			else {
				*(uint8_t *)dst &= ~mask;
			}
		}
#else /* MODE_DECODE */
		*(uint8_t *)dst &= ~mask;
#endif /* !MODE_DECODE */
	}	break;


#ifdef MODE_DECODE
	case JSON_TYPE_INT8:
	case JSON_TYPE_INT16:
	case JSON_TYPE_INT32:
	case JSON_TYPE_UINT8:
	case JSON_TYPE_UINT16:
#if __SIZEOF_POINTER__ == 8
	case JSON_TYPE_INT64:
	case JSON_TYPE_UINT32:
#endif
	{
		intptr_t number;
		result = libjson_parser_getnumber(parser, &number);
		if likely(result == JSON_ERROR_OK) {
			switch (type) {
			case JSON_TYPE_INT8:
			case JSON_TYPE_UINT8:
				*(int8_t *)dst = (int8_t)number;
				break;
			case JSON_TYPE_INT16:
			case JSON_TYPE_UINT16:
				UNALIGNED_SET16((uint16_t *)dst, (uint16_t)(int16_t)number);
				break;
			case JSON_TYPE_INT32:
				UNALIGNED_SET32((uint32_t *)dst, (uint32_t)(int32_t)number);
				break;
#if __SIZEOF_POINTER__ == 8
			case JSON_TYPE_INT64:
			case JSON_TYPE_UINT32:
#endif
			default: __builtin_unreachable();
			}
		}
	}	break;

#if __SIZEOF_POINTER__ != 8
	case JSON_TYPE_INT64: {
		int64_t value;
		result = libjson_parser_getint64(parser, &value);
		if likely(result == JSON_ERROR_OK) {
			UNALIGNED_SET64((uint64_t *)dst, (uint64_t)value);
		}
	}	break;
#endif

	case JSON_TYPE_UINT64: {
		uint64_t value;
		result = libjson_parser_getuint64(parser, &value);
		if likely(result == JSON_ERROR_OK) {
			UNALIGNED_SET64((uint64_t *)dst, value);
		}
	}	break;


	case JSON_TYPE_FLOAT:
	case JSON_TYPE_DOUBLE:
	case JSON_TYPE_LDOUBLE: {
		double value;
		result = libjson_parser_getfloat(parser, &value);
		if likely(result == JSON_ERROR_OK) {
			if (type == JSON_TYPE_DOUBLE)
				memcpy(dst, &value, sizeof(value));
			else if (type == JSON_TYPE_FLOAT) {
				float temp = (float)value;
				memcpy(dst, &temp, sizeof(temp));
			} else {
				long double temp = (long double)value;
				memcpy(dst, &temp, sizeof(temp));
			}
		}
	}	break;

#else /* MODE_DECODE */

	case JSON_TYPE_INT8:
	case JSON_TYPE_UINT8:
		*(uint8_t *)dst = 0;
		break;

	case JSON_TYPE_INT16:
	case JSON_TYPE_UINT16:
		UNALIGNED_SET16((uint16_t *)dst, 0);
		break;

	case JSON_TYPE_INT32:
	case JSON_TYPE_UINT32:
		UNALIGNED_SET32((uint32_t *)dst, 0);
		break;

	case JSON_TYPE_INT64:
	case JSON_TYPE_UINT64:
		UNALIGNED_SET64((uint64_t *)dst, 0);
		break;

	case JSON_TYPE_FLOAT: {
		float temp;
		temp = 0.0f;
		memcpy(dst, &temp, sizeof(temp));
	}	break;

	case JSON_TYPE_DOUBLE: {
		double temp;
		temp = 0.0;
		memcpy(dst, &temp, sizeof(temp));
	}	break;

	case JSON_TYPE_LDOUBLE: {
		long double temp;
		temp = 0.0L;
		memcpy(dst, &temp, sizeof(temp));
	}	break;

#endif /* !MODE_DECODE */

#ifdef MODE_DECODE
	case JSON_TYPE_STRING:
	case JSON_TYPE_STRING_OR_NULL:
	case JSON_TYPE_STRING_WITH_LENGTH_OP:
	case JSON_TYPE_INLINE_STRING_OP: {
		char *str;
		size_t len;
		if (type == JSON_TYPE_STRING_OR_NULL) {
			result = libjson_parser_getnull(parser);
			if (result != JSON_ERROR_NOOBJ) {
				if unlikely(result != JSON_ERROR_OK)
					goto done;
				UNALIGNED_SET((uintptr_t *)dst, (uintptr_t)NULL);
				break;
			}
			/* Not a NULL-value */
		}
		str = libjson_parser_getstring(parser, &len, &result);
		if unlikely(!str)
			goto done; /* JSON_ERROR_NOOBJ or JSON_ERROR_SYNTAX */
		result = JSON_ERROR_OK;
		if (type == JSON_TYPE_INLINE_STRING_OP) {
			uint16_t maxlen;
			maxlen = UNALIGNED_GET16((uint16_t *)*preader);
			*preader += 2;
			/* Make sure that the given string isn't too long */
			if unlikely(len > maxlen) {
				result = JSON_ERROR_NOOBJ;
				goto done;
			}
			/* Copy the used portion of the string, and clear the unused portion. */
			memcpy(dst, str, len, sizeof(char));
			memset((char *)dst + len, 0, ((size_t)maxlen - len) * sizeof(char));
		} else {
			if (type == JSON_TYPE_STRING_WITH_LENGTH_OP) {
				uint16_t len_offset;
				len_offset = UNALIGNED_GET16((uint16_t *)*preader);
				*preader += 2;
				UNALIGNED_SET((size_t *)((byte_t *)dst_base + len_offset), len);
			}
			UNALIGNED_SET((uintptr_t *)dst, (uintptr_t)str);
		}
	}	break;
#else /* MODE_DECODE */
	case JSON_TYPE_STRING_OR_NULL:
		UNALIGNED_SET((uintptr_t *)dst, (uintptr_t)NULL);
		break;

	case JSON_TYPE_INLINE_STRING_OP: {
		uint16_t len;
		len = UNALIGNED_GET16((uint16_t *)*preader);
		*preader += 2;
		memset(dst, 0, (size_t)len);
	}	break;

	case JSON_TYPE_STRING_WITH_LENGTH_OP: {
		uint16_t len_offset;
		len_offset = UNALIGNED_GET16((uint16_t *)*preader);
		*preader += 2;
		UNALIGNED_SET((size_t *)((byte_t *)dst_base + len_offset), 0);
	}	ATTR_FALLTHROUGH
	case JSON_TYPE_STRING:
		UNALIGNED_SET((uintptr_t *)dst, (uintptr_t)libjson_empty_string);
		break;
#endif /* !MODE_DECODE */

	default:
#ifdef MODE_DECODE
		result = JSON_ERROR_SYSERR;
		break;
#else /* MODE_DECODE */
		return JSON_ERROR_SYSERR;
#endif /* !MODE_DECODE */
	}
#ifdef MODE_DECODE
done:
	return result;
#else /* MODE_DECODE */
	return JSON_ERROR_OK;
#endif /* !MODE_DECODE */
}


/* Process until _after_ the correct `JGEN_END' opcode is reached. */
INTDEF
	IF_DECODE(NONNULL((1, 2)))
	IF_ZERO  (NONNULL((1)))
	int
NOTHROW_NCX(CC FUNC(libjson_decode_OBJECT))(IF_DECODE(struct json_parser *__restrict parser, )
                                            byte_t **__restrict preader,
                                            void *__restrict dst,
                                            unsigned int gen_flags);

/* Process until _after_ the correct `JGEN_END' opcode is reached. */
INTDEF
	IF_DECODE(NONNULL((1, 2, 3)))
	IF_ZERO  (NONNULL((1, 2)))
	int
NOTHROW_NCX(CC FUNC(libjson_decode_ARRAY))(IF_DECODE(struct json_parser *__restrict parser, )
                                           byte_t **__restrict preader,
                                           void *__restrict dst,
                                           unsigned int gen_flags);


#ifndef LIBJSON_DECODE_OBJECT_ZERO_DEFINED
#define LIBJSON_DECODE_OBJECT_ZERO_DEFINED 1
#ifdef MODE_DECODE
INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_decode_designator_zero)(byte_t **__restrict preader,
                                               void *__restrict dst,
                                               unsigned int gen_flags);
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_decode_OBJECT_zero)(byte_t **__restrict preader,
                                           void *__restrict dst,
                                           unsigned int gen_flags);
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_decode_ARRAY_zero)(byte_t **__restrict preader,
                                          void *__restrict dst,
                                          unsigned int gen_flags);
#endif /* MODE_DECODE */
#endif /* !LIBJSON_DECODE_OBJECT_ZERO_DEFINED */




/* Process the designator that must follow one of the following opcodes:
 *   - JGEN_FIELD
 *   - JGEN_INDEX
 *   - JGEN_INDEX_REP_OP
 * This designator can be one of the following:
 *   - JGEN_BEGINOBJECT
 *   - JGEN_BEGINARRAY
 *   - JGEN_INTO
 */
INTERN
	IF_DECODE(NONNULL((1, 2, 3)))
	IF_ZERO  (NONNULL((1, 2)))
	int
NOTHROW_NCX(CC FUNC(libjson_decode_designator))(IF_DECODE(struct json_parser *__restrict parser, )
                                                byte_t **__restrict preader,
                                                void *__restrict dst,
                                                unsigned int gen_flags) {
	int result;
	byte_t op, *reader = *preader;
	op = *reader++;
	switch (op) {

	case JGEN_BEGINOBJECT:
		result = FUNC(libjson_decode_OBJECT)(IF_DECODE(parser, )&reader, dst, gen_flags);
		break;

	case JGEN_BEGINARRAY:
		result = FUNC(libjson_decode_ARRAY)(IF_DECODE(parser, )&reader, dst, gen_flags);
		break;

	case JGEN_INTO: {
		uint16_t offset;
		uint8_t type;
		offset = UNALIGNED_GET16((uint16_t *)reader);
		reader += 2;
		type = *(uint8_t *)reader;
		reader += 1;
		result = FUNC(libjson_decode_INTO)(IF_DECODE(parser, )&reader,
		                                   dst, (byte_t *)dst + offset,
		                                   type IF_DECODE(, gen_flags));
	}	break;

	default:
		result = JSON_ERROR_SYSERR;
		break;
	}
	*preader = reader;
	return result;
}


/* Process until _after_ the correct `JGEN_END' opcode is reached. */
INTERN
	IF_DECODE(NONNULL((1, 2, 3)))
	IF_ZERO  (NONNULL((1, 2)))
	int
NOTHROW_NCX(CC FUNC(libjson_decode_OBJECT))(IF_DECODE(struct json_parser *__restrict parser, )
                                            byte_t **__restrict preader,
                                            void *__restrict dst,
                                            unsigned int gen_flags) {
	int result;
	byte_t op, *reader;
#ifdef MODE_DECODE
	result = libjson_parser_enterobject(parser);
	if (result != JSON_ERROR_OK) {
		if (result == JSON_ERROR_NOOBJ && (gen_flags & GENFLAG_OPTIONAL)) {
			/* ZERO-initialize all of the designated fields. */
			result = libjson_decode_OBJECT_zero(preader, dst, gen_flags);
		}
		return result;
	}
#endif /* MODE_DECODE */
	reader = *preader;
	for (;;) {
		unsigned int inner_flags = 0;
again_inner:
		op = *reader++;
		switch (op) {

		case JGEN_END:
			goto done_object;

		case JGEN_FIELD: {
			IF_DECODE(size_t namelen;)
#ifndef MODE_DECODE
			reader = (byte_t *)(strend((char *)reader) + 1);
#else /* !MODE_DECODE */
			namelen = strlen((char *)reader);
			result  = libjson_parser_findkey(parser, (char *)reader, namelen);
			reader += namelen + 1;
			/* parse the field designator. */
			if (result != JSON_ERROR_OK) {
				if (result == JSON_ERROR_NOOBJ && (inner_flags & GENFLAG_OPTIONAL)) {
					result = JSON_ERROR_OK;
					/* ZERO-initialize all of the designated fields. */
					result = libjson_decode_designator_zero(&reader, dst,
					                                        inner_flags | (gen_flags & ~GENFLAG_OPTIONAL));
				} else {
					goto done;
				}
			} else
#endif /* MODE_DECODE */
			{
				result = FUNC(libjson_decode_designator)(IF_DECODE(parser, )&reader, dst,
				                                         inner_flags | (gen_flags & ~GENFLAG_OPTIONAL));
				if unlikely(result != JSON_ERROR_OK)
					goto done;
			}
		}	break;

		case JGEN_OPTIONAL:
			if unlikely(inner_flags & GENFLAG_OPTIONAL)
				goto err_bad_usage;
			inner_flags |= GENFLAG_OPTIONAL;
			goto again_inner;

		default:
err_bad_usage:
			result = JSON_ERROR_SYSERR;
			goto done;
		}
	}
done_object:
#ifdef MODE_DECODE
	result = libjson_parser_leaveobject(parser);
#else /* MODE_DECODE */
	result = JSON_ERROR_OK;
#endif /* !MODE_DECODE */
done:
	*preader = reader;
	return result;
}




/* Process until _after_ the correct `JGEN_END' opcode is reached. */
INTERN
	IF_DECODE(NONNULL((1, 2, 3)))
	IF_ZERO  (NONNULL((1, 2)))
	int
NOTHROW_NCX(CC FUNC(libjson_decode_ARRAY))(IF_DECODE(struct json_parser *__restrict parser, )
                                           byte_t **__restrict preader,
                                           void *__restrict dst,
                                           unsigned int gen_flags) {
	int result;
	byte_t op, *reader;
	IF_DECODE(bool is_first = true;)
#ifdef MODE_DECODE
	result = libjson_parser_enterarray(parser);
	if (result != JSON_ERROR_OK) {
		if (result == JSON_ERROR_NOOBJ && (gen_flags & GENFLAG_OPTIONAL)) {
			/* ZERO-initialize all of the designated fields. */
			result = libjson_decode_ARRAY_zero(preader, dst, gen_flags);
		}
		return result;
	}
#endif /* MODE_DECODE */
	reader = *preader;
	for (;;) {
		unsigned int inner_flags = 0;
again_inner:
		op = *reader++;
		switch (op) {

		case JGEN_END:
			goto done_array;

		case JGEN_INDEX:
			/* parse the array element designator. */
#ifdef MODE_DECODE
			if (!is_first) {
				result = libjson_parser_yield(parser);
				if (result != ',') {
					if (result >= 0)
						result = JSON_ERROR_SYNTAX;
					goto done;
				}
			}
			is_first = false;
#endif /* MODE_DECODE */
			result = FUNC(libjson_decode_designator)(IF_DECODE(parser, )&reader, dst,
			                                         inner_flags | (gen_flags & ~GENFLAG_OPTIONAL));
			break;

		case JGEN_INDEX_REP_OP: {
			uint16_t count;
			uint16_t stride;
			size_t offset;
			byte_t *orig_reader;
			count   = UNALIGNED_GET16((uint16_t *)reader) + 1;
			reader += 2;
			stride  = UNALIGNED_GET16((uint16_t *)reader);
			reader += 2;
			offset  = 0;
			orig_reader = reader;
			do {
#ifdef MODE_DECODE
				if (!is_first) {
					result = libjson_parser_yield(parser);
					if (result != ',') {
						if (result >= 0)
							result = JSON_ERROR_SYNTAX;
						goto done;
					}
				}
				is_first = false;
#endif /* MODE_DECODE */
				/* parse the array element designator. */
				reader = orig_reader;
				result = FUNC(libjson_decode_designator)(IF_DECODE(parser, )&reader,
				                                         (byte_t *)dst + offset,
				                                         inner_flags | (gen_flags & ~GENFLAG_OPTIONAL));
				if unlikely(result != JSON_ERROR_OK)
					goto done;
				offset += stride;
			} while (--count != 0);
		}	break;

		case JGEN_OPTIONAL:
			if unlikely(inner_flags & GENFLAG_OPTIONAL)
				goto err_bad_usage;
			inner_flags |= GENFLAG_OPTIONAL;
			goto again_inner;

		default:
err_bad_usage:
			result = JSON_ERROR_SYSERR;
			goto done;
		}
	}
done_array:
#ifdef MODE_DECODE
	result = libjson_parser_leavearray(parser);
#else /* MODE_DECODE */
	result = JSON_ERROR_OK;
#endif /* !MODE_DECODE */
done:
	*preader = reader;
	return result;
}





DECL_END

#undef IF_DECODE
#undef IF_ZERO
#undef FUNC

#undef MODE_DECODE
#undef MODE_ZERO
