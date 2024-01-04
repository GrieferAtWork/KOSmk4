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
#ifndef _LIBZLIB_ERROR_H
#define _LIBZLIB_ERROR_H 1

#include "api.h"

#define ZLIB_ERROR_OK                 0     /* No error */
#define ZLIB_ERROR_ALREADY            (-1)  /* Attempted to feed more data while existing data is still being processed */
#define ZLIB_ERROR_BAD_INTERNAL_STATE (-2)  /* Bad internal state */
#define ZLIB_ERROR_BAD_HEADER         (-3)  /* Bad zlib header */
#define ZLIB_ERROR_BAD_BLOCK_TYPE     (-4)  /* Bad zlib block type */
#define ZLIB_ERROR_BAD_RAW_CHECKSUM   (-5)  /* Bad checksum for a raw data block */
#define ZLIB_ERROR_UNKNOWN_SEQUENCE   (-6)  /* Unknown bit-sequence in compressed data */
#define ZLIB_ERROR_LEN_REPEAT_ZERO    (-7)  /* Attempted to repeat the previous symbol-length value when there was none. */
#define ZLIB_ERROR_LEN_REPEAT_LARGE   (-8)  /* The length of a run-len encoded sequence would exceed the data limit. */
#define ZLIB_ERROR_BAD_DISTANCE       (-9)  /* Invalid distance symbol during data-repeat */
#define ZLIB_ERROR_BAD_LENGTH         (-10) /* Invalid length value during data-repeat */
#define ZLIB_ERROR_OOB_DISTANCE       (-11) /* The distance during data-repeat is out-of-bounds */

#endif /* !_LIBZLIB_ERROR_H */
