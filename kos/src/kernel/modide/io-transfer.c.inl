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
#ifdef __INTELLISENSE__
#include "io.c"
//#define DEFINE_RW_Read
#define DEFINE_RW_Write

//#define DEFINE_DATA_Virt
//#define DEFINE_DATA_Phys
#define DEFINE_DATA_VirtVector
//#define DEFINE_DATA_PhysVector
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>
#include <kernel/vm/phys.h>
#include <sched/tsc.h>

#include <sys/io.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#if (defined(DEFINE_RW_Read) + defined(DEFINE_RW_Write)) != 1
#error "Exactly 1 I/O operation must be defined"
#endif /* DEFINE_RW_... */

#if (defined(DEFINE_DATA_Virt) +   \
     defined(DEFINE_DATA_Phys) +   \
     defined(DEFINE_DATA_VirtVector) + \
     defined(DEFINE_DATA_PhysVector)) != 1
#error "Exactly 1 I/O data type must be defined"
#endif /* DEFINE_DATA_... */

DECL_BEGIN

#ifdef DEFINE_RW_Read
#define _ATA_RW_Name Read
#elif defined(DEFINE_RW_Write)
#define _ATA_RW_Name Write
#endif /* DEFINE_RW_... */

#ifdef DEFINE_DATA_Virt
#define _ATA_DATA_IS_VIRTUAL
#define _ATA_DATA_Name /* nothing */
#elif defined(DEFINE_DATA_Phys)
#define _ATA_DATA_IS_PHYSICAL
#define _ATA_DATA_Name Phys
#elif defined(DEFINE_DATA_VirtVector)
#define _ATA_DATA_IS_VIRTUAL
#define _ATA_DATA_Name Vector
#elif defined(DEFINE_DATA_PhysVector)
#define _ATA_DATA_IS_PHYSICAL
#define _ATA_DATA_Name VectorPhys
#endif /* DEFINE_DATA_... */

#ifdef DEFINE_DATA_Virt
#ifdef DEFINE_RW_Read
#define _ATA_DATA_TYPE USER CHECKED byte_t *
#elif defined(DEFINE_RW_Write)
#define _ATA_DATA_TYPE USER CHECKED byte_t const *
#endif /* DEFINE_RW_... */
#elif defined(DEFINE_DATA_Phys)
#define _ATA_DATA_TYPE physaddr_t
#elif defined(DEFINE_DATA_VirtVector)
#define _ATA_DATA_SIZE  aio_buffer_size
#define _ATA_DATA_ENTRY struct aio_buffer_entry
#define _ATA_DATA_TYPE  struct aio_buffer *__restrict
#elif defined(DEFINE_DATA_PhysVector)
#define _ATA_DATA_SIZE  aio_pbuffer_size
#define _ATA_DATA_ENTRY struct aio_pbuffer_entry
#define _ATA_DATA_TYPE  struct aio_pbuffer *__restrict
#endif /* DEFINE_DATA_... */

#ifdef DEFINE_DATA_Virt
#define _ATA_DATA_Name /* nothing */
#elif defined(DEFINE_DATA_Phys)
#define _ATA_DATA_Name Phys
#elif defined(DEFINE_DATA_VirtVector)
#define _ATA_DATA_Name Vector
#elif defined(DEFINE_DATA_PhysVector)
#define _ATA_DATA_Name VectorPhys
#endif /* DEFINE_DATA_... */

#if defined(DEFINE_RW_Read) && defined(_ATA_DATA_IS_PHYSICAL)
#define _ATA_LOWLEVEL_IO(port, buf, count) vm_insw_phys(port, buf, count)
#elif defined(DEFINE_RW_Read) && defined(_ATA_DATA_IS_VIRTUAL)
#define _ATA_LOWLEVEL_IO(port, buf, count) insw(port, buf, count)
#elif defined(DEFINE_RW_Write) && defined(_ATA_DATA_IS_PHYSICAL)
#define _ATA_LOWLEVEL_IO(port, buf, count) vm_outsw_phys(port, buf, count)
#elif defined(DEFINE_RW_Write) && defined(_ATA_DATA_IS_VIRTUAL)
#define _ATA_LOWLEVEL_IO(port, buf, count) \
	do {                                   \
		size_t _i, _cnt = (count);         \
		u16 *_buf = (u16 *)(buf);          \
		for (_i = 0; _i < _cnt; ++_i)      \
			outw(port, _buf[_i]);          \
	}	__WHILE0
#endif

#ifdef _ATA_DATA_IS_PHYSICAL
#define _ATA_DATA_READB(addr)          vm_readphysb((physaddr_t)(addr))
#define _ATA_DATA_WRITEB(addr, value) vm_writephysb((physaddr_t)(addr), value)
#elif defined(_ATA_DATA_IS_VIRTUAL)
#define _ATA_DATA_READB(addr)          (*(u8 const *)(addr))
#define _ATA_DATA_WRITEB(addr, value) (void)(*(u8 *)(addr) = (value))
#endif /* ... */


LOCAL NONNULL((1, 2)) AtaError_t KCALL
PP_CAT4(AtaBus_, _ATA_RW_Name, DataSectors, _ATA_DATA_Name)(AtaBus *__restrict bus,
                                                            AtaDrive *__restrict drive,
                                                            _ATA_DATA_TYPE buf,
                                                            u16 num_sectors) {
#ifdef _ATA_DATA_ENTRY
	_ATA_DATA_ENTRY ent = buf->ab_head;
	size_t next_ent_index = 1;
	assert(_ATA_DATA_SIZE(buf) == 2 * num_sectors * ATA_SECTOR_SIZE(drive));
#endif /* _ATA_DATA_ENTRY */
	(void)drive;
	TRY {
		for (;;) {
			struct sig *signal;
			u8 status; /* Set of `ATA_DCR_*' */
			AtaError_t error;
			ATA_VERBOSE("[ata] Begin waiting on data transfer to become ready\n");
			assert(num_sectors);
			signal = task_trywait();
			if (!signal) {
				ktime_t timeout;
				timeout = ktime();
				timeout += relktime_from_nanoseconds(bus->ab_timeout_dat);
				signal = task_waitfor(timeout);
				if unlikely(!signal)
					return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_SECTOR_WAIT);
			}
			status = ATA_PIOINTR_ALT_DECODE(signal);
			if (status & (ATA_DCR_ERR | ATA_DCR_DF))
				return ATA_HW_GetErrorFromStatusRegister(status);
			if (num_sectors != 1) /* Re-connect for the next sector */
				task_connect(&bus->ab_piointr);
			error = AtaBus_HW_WaitForDrq(bus);
			if unlikely(error != ATA_ERROR_OK)
				return error;
#ifdef _ATA_DATA_ENTRY
			{
				size_t io_bytes = ATA_SECTOR_SIZE(drive);
				while (io_bytes) {
					size_t max_bytes = ent.ab_size;
					if (!max_bytes) {
						assert(next_ent_index < buf->ab_entc);
						AIO_BUFFER_GETENT(ent, buf, next_ent_index);
						++next_ent_index;
						max_bytes = ent.ab_size;
					}
					if (max_bytes > io_bytes)
						max_bytes = io_bytes;
					assert(max_bytes != 0);
					_ATA_LOWLEVEL_IO(bus->ab_busio + ATA_DATA, ent.ab_base, max_bytes / 2);
					if unlikely(max_bytes & 1) { /* Deal with unaligned buf entries. */
						assert(max_bytes == ent.ab_size);
						++max_bytes;
						assert(max_bytes <= io_bytes);
						union {
							u8 bytes[2];
							u16 word;
						} data;
#ifdef DEFINE_RW_Read
						data.word = inw(bus->ab_busio + ATA_DATA);
						_ATA_DATA_WRITEB(ent.ab_base + ent.ab_size - 1, data.bytes[0]);
#elif defined(DEFINE_RW_Write)
						data.bytes[0] = _ATA_DATA_READB(ent.ab_base + ent.ab_size - 1);
#endif /* ... */
						assert(next_ent_index < buf->ab_entc);
						AIO_BUFFER_GETENT(ent, buf, next_ent_index);
						assert(ent.ab_size);
						++next_ent_index;
#ifdef DEFINE_RW_Read
						_ATA_DATA_WRITEB(ent.ab_base, data.bytes[1]);
#elif defined(DEFINE_RW_Write)
						data.bytes[1] = _ATA_DATA_READB(ent.ab_base);
						outw(bus->ab_busio + ATA_DATA, data.word);
#endif /* ... */
						++ent.ab_base;
						--ent.ab_size;
					}
					ent.ab_base += max_bytes;
					ent.ab_size -= max_bytes;
					if (io_bytes >= max_bytes)
						break;
				}
			}
			if (num_sectors == 1)
				break;
#else /* _ATA_DATA_ENTRY */
			_ATA_LOWLEVEL_IO(bus->ab_busio + ATA_DATA, buf,
			                 ATA_SECTOR_SIZE(drive) / 2);
			if (num_sectors == 1)
				break;
			buf += ATA_SECTOR_SIZE(drive);
#endif /* !_ATA_DATA_ENTRY */
			--num_sectors;
		}
	} EXCEPT {
		/* Must reset the bus, so-as to abort the current I/O operation. */
		task_disconnectall();
		printk(KERN_NOTICE "[ata] Reseting IDE to abort PIO-I/O operation ("
		                   "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
		                   "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
		                   "dma:%#" PRIxN(__SIZEOF_PORT_T__) ")\n",
		       bus->ab_busio, bus->ab_ctrlio, bus->ab_dmaio);
		AtaBus_HW_ResetBusAuto(bus);
		RETHROW();
	}
	assert(!task_wasconnected());
	return ATA_ERROR_OK;
}

#undef _ATA_LOWLEVEL_IO

#undef _ATA_RW_Name
#undef _ATA_DATA_Name
#undef _ATA_DATA_TYPE
#undef _ATA_DATA_ENTRY
#undef _ATA_DATA_SIZE
#undef _ATA_DATA_IS_VIRTUAL
#undef _ATA_DATA_IS_PHYSICAL
#undef _ATA_DATA_READB
#undef _ATA_DATA_WRITEB

DECL_END

#undef DEFINE_RW_Read
#undef DEFINE_RW_Write

#undef DEFINE_DATA_Virt
#undef DEFINE_DATA_Phys
#undef DEFINE_DATA_VirtVector
#undef DEFINE_DATA_PhysVector
