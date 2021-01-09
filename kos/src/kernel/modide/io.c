/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODIDE_IO_C
#define GUARD_MODIDE_IO_C 1
#define _KOS_SOURCE 1

#include "ata.h"
/**/

DECL_BEGIN

/* PIO-based data transfer helpers for passing data to/from an ATA drive. */
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_ReadDataSectors(AtaBus *__restrict bus, AtaDrive *__restrict drive, USER CHECKED byte_t *buf, u16 num_sectors);
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_ReadDataSectorsPhys(AtaBus *__restrict bus, AtaDrive *__restrict drive, physaddr_t buf, u16 num_sectors);
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_ReadDataSectorsVector(AtaBus *__restrict bus, AtaDrive *__restrict drive, struct aio_buffer *__restrict buf, u16 num_sectors);
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_ReadDataSectorsVectorPhys(AtaBus *__restrict bus, AtaDrive *__restrict drive, struct aio_pbuffer *__restrict buf, u16 num_sectors);
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_WriteDataSectors(AtaBus *__restrict bus, AtaDrive *__restrict drive, USER CHECKED byte_t const *buf, u16 num_sectors);
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_WriteDataSectorsPhys(AtaBus *__restrict bus, AtaDrive *__restrict drive, physaddr_t buf, u16 num_sectors);
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_WriteDataSectorsVector(AtaBus *__restrict bus, AtaDrive *__restrict drive, struct aio_buffer *__restrict buf, u16 num_sectors);
LOCAL NONNULL((1, 2)) AtaError_t KCALL AtaBus_WriteDataSectorsVectorPhys(AtaBus *__restrict bus, AtaDrive *__restrict drive, struct aio_pbuffer *__restrict buf, u16 num_sectors);

DECL_END

/* Define I/O functions */
#ifndef __INTELLISENSE__

#define DEFINE_DATA_Virt
#define DEFINE_RW_Read
#include "io-transfer.c.inl"

#define DEFINE_DATA_Virt
#define DEFINE_RW_Write
#include "io-transfer.c.inl"

#define DEFINE_DATA_Phys
#define DEFINE_RW_Read
#include "io-transfer.c.inl"

#define DEFINE_DATA_Phys
#define DEFINE_RW_Write
#include "io-transfer.c.inl"

#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Read
#include "io-transfer.c.inl"

#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Write
#include "io-transfer.c.inl"

#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Read
#include "io-transfer.c.inl"

#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Write
#include "io-transfer.c.inl"



#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_Virt
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_Virt
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_Phys
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_Phys
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Dma
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Write
#include "io.c.inl"



#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_Virt
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_Virt
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_Phys
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_Phys
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Chs
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Write
#include "io.c.inl"




#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_Virt
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_Virt
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_Phys
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_Phys
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba28
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Write
#include "io.c.inl"




#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_Virt
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_Virt
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_Phys
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_Phys
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_VirtVector
#define DEFINE_RW_Write
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Read
#include "io.c.inl"

#define DEFINE_IOMETHOD_Lba48
#define DEFINE_DATA_PhysVector
#define DEFINE_RW_Write
#include "io.c.inl"

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_MODIDE_IO_C */
