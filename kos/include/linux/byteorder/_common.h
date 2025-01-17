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
#ifndef _LINUX_BYTEORDER_COMMON_H
#define _LINUX_BYTEORDER_COMMON_H 1

#include <__stdinc.h>

#include <hybrid/__byteswap.h>

#include <linux/stddef.h>
#include <linux/types.h>
#ifndef _LINUX_SWAB_H
#include <linux/swab.h>
#endif /* !_LINUX_SWAB_H */

#define __constant_htonl       __hybrid_htobe32_c
#define __constant_ntohl       __hybrid_betoh32_c
#define __constant_htons       __hybrid_htobe16_c
#define __constant_ntohs       __hybrid_betoh16_c
#define __constant_cpu_to_le64 __hybrid_htole64_c
#define __constant_le64_to_cpu __hybrid_letoh64_c
#define __constant_cpu_to_le32 __hybrid_htole32_c
#define __constant_le32_to_cpu __hybrid_letoh32_c
#define __constant_cpu_to_le16 __hybrid_htole16_c
#define __constant_le16_to_cpu __hybrid_letoh16_c
#define __constant_cpu_to_be64 __hybrid_htobe64_c
#define __constant_be64_to_cpu __hybrid_betoh64_c
#define __constant_cpu_to_be32 __hybrid_htobe32_c
#define __constant_be32_to_cpu __hybrid_betoh32_c
#define __constant_cpu_to_be16 __hybrid_htobe16_c
#define __constant_be16_to_cpu __hybrid_betoh16_c
#define __cpu_to_le64          __hybrid_htole64
#define __le64_to_cpu          __hybrid_letoh64
#define __cpu_to_le32          __hybrid_htole32
#define __le32_to_cpu          __hybrid_letoh32
#define __cpu_to_le16          __hybrid_htole16
#define __le16_to_cpu          __hybrid_letoh16
#define __cpu_to_be64          __hybrid_htobe64
#define __be64_to_cpu          __hybrid_betoh64
#define __cpu_to_be32          __hybrid_htobe32
#define __be32_to_cpu          __hybrid_betoh32
#define __cpu_to_be16          __hybrid_htobe16
#define __be16_to_cpu          __hybrid_betoh16

#define __cpu_to_le64p(/*__u64 const **/ p)  ((__le64)__cpu_to_le64(*(p)))
#define __le64_to_cpup(/*__le64 const **/ p) ((__u64)__le64_to_cpu(*(p)))
#define __cpu_to_le32p(/*__u32 const **/ p)  ((__le32)__cpu_to_le32(*(p)))
#define __le32_to_cpup(/*__le32 const **/ p) ((__u32)__le32_to_cpu(*(p)))
#define __cpu_to_le16p(/*__u16 const **/ p)  ((__le16)__cpu_to_le16(*(p)))
#define __le16_to_cpup(/*__le16 const **/ p) ((__u16)__le16_to_cpu(*(p)))
#define __cpu_to_be64p(/*__u64 const **/ p)  ((__be64)__cpu_to_be64(*(p)))
#define __be64_to_cpup(/*__be64 const **/ p) ((__u64)__be64_to_cpu(*(p)))
#define __cpu_to_be32p(/*__u32 const **/ p)  ((__be32)__cpu_to_be32(*(p)))
#define __be32_to_cpup(/*__be32 const **/ p) ((__u32)__be32_to_cpu(*(p)))
#define __cpu_to_be16p(/*__u16 const **/ p)  ((__be16)__cpu_to_be16(*(p)))
#define __be16_to_cpup(/*__be16 const **/ p) ((__u16)__be16_to_cpu(*(p)))

#define __cpu_to_le64s(x) (void)(*(x) = __cpu_to_le64(*(x)))
#define __le64_to_cpus(x) (void)(*(x) = __le64_to_cpu(*(x)))
#define __cpu_to_le32s(x) (void)(*(x) = __cpu_to_le32(*(x)))
#define __le32_to_cpus(x) (void)(*(x) = __le32_to_cpu(*(x)))
#define __cpu_to_le16s(x) (void)(*(x) = __cpu_to_le16(*(x)))
#define __le16_to_cpus(x) (void)(*(x) = __le16_to_cpu(*(x)))
#define __cpu_to_be64s(x) (void)(*(x) = __cpu_to_be64(*(x)))
#define __be64_to_cpus(x) (void)(*(x) = __be64_to_cpu(*(x)))
#define __cpu_to_be32s(x) (void)(*(x) = __cpu_to_be32(*(x)))
#define __be32_to_cpus(x) (void)(*(x) = __be32_to_cpu(*(x)))
#define __cpu_to_be16s(x) (void)(*(x) = __cpu_to_be16(*(x)))
#define __be16_to_cpus(x) (void)(*(x) = __be16_to_cpu(*(x)))

#endif /* _LINUX_BYTEORDER_COMMON_H */
