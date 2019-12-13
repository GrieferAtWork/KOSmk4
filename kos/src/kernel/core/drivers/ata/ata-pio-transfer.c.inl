/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../ata.c"

#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
//#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_PHYS 1
#endif

#include <kernel/vm/phys.h>

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define exactly one of `DEFINE_IO_READ' or `DEFINE_IO_WRITE'"
#endif

#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define FUNC_VECTORPHYS(x)  x##VectorPhys
#define BUFFER_TYPE         struct aio_pbuffer *__restrict
#define VECTOR_TYPE         struct aio_pbuffer
#define ENTRY_TYPE          struct aio_pbuffer_entry
#elif defined(DEFINE_IO_VECTOR)
#define FUNC_VECTORPHYS(x)  x##Vector
#define BUFFER_TYPE         struct aio_buffer *__restrict
#define VECTOR_TYPE         struct aio_buffer
#define ENTRY_TYPE          struct aio_buffer_entry
#elif defined(DEFINE_IO_PHYS)
#define FUNC_VECTORPHYS(x)  x##Phys
#define BUFFER_TYPE         vm_phys_t
#elif defined(DEFINE_IO_READ)
#define FUNC_VECTORPHYS(x)  x
#define BUFFER_TYPE         USER CHECKED byte_t *
#else
#define FUNC_VECTORPHYS(x)  x
#define BUFFER_TYPE         USER CHECKED byte_t const *
#endif

DECL_BEGIN

#ifdef DEFINE_IO_PHYS
#if defined(DEFINE_IO_READ) ? !defined(INSW_PHYS_DEFINED) : !defined(OUTSW_PHYS_DEFINED)
#ifdef DEFINE_IO_READ
#define INSW_PHYS_DEFINED 1
LOCAL void KCALL vm_insw_phys(port_t port, vm_phys_t buf, size_t count)
#else /* DEFINE_IO_READ */
#define OUTSW_PHYS_DEFINED 1
LOCAL void KCALL vm_outsw_phys(port_t port, vm_phys_t buf, size_t count)
#endif /* !DEFINE_IO_READ */
{
#ifdef DEFINE_IO_READ
#define PAGEDIR_MAPPING_FLAGS  (PAGEDIR_MAP_FREAD|PAGEDIR_MAP_FWRITE)
#else
#define PAGEDIR_MAPPING_FLAGS   PAGEDIR_MAP_FREAD
#endif
	pagedir_pushval_t backup;
	vm_vpage_t tramp;
	bool is_first;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	assert(tramp != 0);
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_words;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(buf);
			page_words = (PAGESIZE - (buf & (PAGESIZE - 1))) / 2;
			if (page_words > count)
				page_words = count;
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAPPING_FLAGS);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAPPING_FLAGS);
			}
			pagedir_syncone(tramp);
			/* Transfer to/from memory. */
			assert(tramp != 0);
#ifdef DEFINE_IO_READ
			insw(port, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(buf & (PAGESIZE - 1))), page_words);
#elif 1 /* ATA output apparently requires a small pause before every written word. */
			{
				size_t i;
				u16 *src = (u16 *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(buf & (PAGESIZE - 1)));
				for (i = 0; i < page_words; ++i)
					outw(port, *src++);
			}
#else
			outsw(port, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(buf & (PAGESIZE - 1))), page_words);
#endif
			if (page_words >= count)
				break;
			count -= page_words;
			buf += page_words * 2;
		}
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
#undef PAGEDIR_MAPPING_FLAGS
}
#endif /* !(INSW|OUTSW)_PHYS_DEFINED */
#endif /* DEFINE_IO_PHYS */


/* PIO-based data transfer helpers for passing data to/from an ATA drive. */
LOCAL errr_t
#ifdef DEFINE_IO_READ
(KCALL FUNC_VECTORPHYS(Ata_ReceiveDataSectors))
#else
(KCALL FUNC_VECTORPHYS(Ata_TransmitDataSectors))
#endif
                                                (struct ata_bus *__restrict bus,
                                                 struct ata_drive *__restrict drive,
                                                 BUFFER_TYPE buffer,
                                                 u16 num_sectors)
{
#ifdef DEFINE_IO_VECTOR
	ENTRY_TYPE ent        = buffer->ab_head;
	size_t next_ent_index = 1;
#ifdef DEFINE_IO_PHYS
	assert(aio_pbuffer_size(buffer) == 2 * num_sectors * ATA_SECTOR_SIZE(drive));
#else /* DEFINE_IO_PHYS */
	assert(aio_buffer_size(buffer) == 2 * num_sectors * ATA_SECTOR_SIZE(drive));
#endif /* !DEFINE_IO_PHYS */
#endif /* DEFINE_IO_VECTOR */
	TRY {
		for (;;) {
			struct sig *signal;
			u8 status; /* Set of `ATA_DCR_*' */
			ATA_VERBOSE("Begin waiting on data transfer to become ready\n");
			assert(num_sectors);
			signal = task_trywait();
			if (!signal) {
				qtime_t timeout;
				timeout = quantum_time();
				timeout.add_seconds(2);
				signal = task_waitfor(&timeout);
				if unlikely(!signal)
					return ERRR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_SECTOR_WAIT);
			}
			status = ATA_PIOINTR_ALT_DECODE(signal);
			if (status & (ATA_DCR_ERR | ATA_DCR_DF))
				return ATA_GetErrrForStatusRegister(status);
			if (num_sectors != 1)
				task_connect(&bus->b_piointr);
			Ata_WaitForDrq(bus->b_ctrlio);
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_READ)
#define DO_IO(port, buf, count) vm_insw_phys(port, buf, count)
#elif defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_WRITE)
#define DO_IO(port, buf, count) vm_outsw_phys(port, buf, count)
#elif defined(DEFINE_IO_READ)
#define DO_IO(port, buf, count) insw(port, buf, count)
#elif defined(DEFINE_IO_WRITE)
#define DO_IO(port, buf, count) \
			do {                              \
				size_t _i, _cnt = (count);    \
				u16 *_buf = (u16 *)(buf);     \
				for (_i = 0; _i < _cnt; ++_i) \
					outw(port, _buf[_i]);     \
			} __WHILE0
#endif
#ifdef DEFINE_IO_VECTOR
			{
				size_t io_bytes = ATA_SECTOR_SIZE(drive);
				while (io_bytes) {
					size_t max_bytes = ent.ab_size;
					if (!max_bytes) {
						assert(next_ent_index < buffer->ab_entc);
						AIO_BUFFER_GETENT(ent, buffer, next_ent_index);
						++next_ent_index;
						max_bytes = ent.ab_size;
					}
					if (max_bytes > io_bytes)
						max_bytes = io_bytes;
					assert(max_bytes != 0);
					DO_IO(bus->b_busio + ATA_DATA, ent.ab_base, max_bytes / 2);
					if unlikely(max_bytes & 1) { /* Deal with unaligned buffer entries. */
						assert(max_bytes == ent.ab_size);
						++max_bytes;
						assert(max_bytes <= io_bytes);
						union {
							u8 bytes[2];
							u16 word;
						} data;
#ifdef DEFINE_IO_READ
						data.word = inw(bus->b_busio + ATA_DATA);
#ifdef DEFINE_IO_PHYS
						vm_writephysb((vm_phys_t)(ent.ab_base + ent.ab_size - 1), data.bytes[0]);
#else /* DEFINE_IO_PHYS */
						((u8 *)ent.ab_base)[ent.ab_size - 1] = data.bytes[0];
#endif /* !DEFINE_IO_PHYS */
#else /* DEFINE_IO_READ */
#ifdef DEFINE_IO_PHYS
						data.bytes[0] = vm_readphysb((vm_phys_t)(ent.ab_base + ent.ab_size - 1));
#else /* DEFINE_IO_PHYS */
						data.bytes[0] = ((u8 *)ent.ab_base)[ent.ab_size - 1];
#endif /* !DEFINE_IO_PHYS */
#endif /* !DEFINE_IO_READ */
						assert(next_ent_index < buffer->ab_entc);
						AIO_BUFFER_GETENT(ent, buffer, next_ent_index);
						assert(ent.ab_size);
						++next_ent_index;
#ifdef DEFINE_IO_READ
#ifdef DEFINE_IO_PHYS
						vm_writephysb(ent.ab_base, data.bytes[1]);
						++ent.ab_base;
#else /* DEFINE_IO_PHYS */
						((u8 *)ent.ab_base)[0] = data.bytes[1];
						ent.ab_base            = (byte_t *)ent.ab_base + 1;
#endif /* !DEFINE_IO_PHYS */
#else /* DEFINE_IO_READ */
#ifdef DEFINE_IO_PHYS
						data.bytes[1] = vm_readphysb(ent.ab_base);
						++ent.ab_base;
#else /* DEFINE_IO_PHYS */
						data.bytes[1] = ((u8 *)ent.ab_base)[0];
						ent.ab_base   = (byte_t *)ent.ab_base + 1;
#endif /* !DEFINE_IO_PHYS */
						outw(bus->b_busio + ATA_DATA, data.word);
#endif /* !DEFINE_IO_READ */
						--ent.ab_size;
					}
					ent.ab_size -= max_bytes;
#ifdef DEFINE_IO_PHYS
					ent.ab_base += max_bytes;
#else
					ent.ab_base = (byte_t *)ent.ab_base + max_bytes;
#endif
					if (io_bytes >= max_bytes)
						break;
				}
			}
			if (num_sectors == 1)
				break;
#else
			DO_IO(bus->b_busio + ATA_DATA, buffer, ATA_SECTOR_SIZE(drive) / 2);
			if (num_sectors == 1)
				break;
			buffer += ATA_SECTOR_SIZE(drive);
#endif
#undef DO_IO
			--num_sectors;
		}
	} EXCEPT {
		/* Must reset the bus, so-as to abort the current I/O operation. */
		task_disconnectall();
		printk(KERN_NOTICE "Reseting IDE to abort PIO-I/O operation (bus:%#I16x;ctrl:%#I16x;dma:%#I16x)\n",
		       bus->b_busio, bus->b_ctrlio, bus->b_dmaio);
		Ata_ResetAndReinitializeBus(bus);
		RETHROW();
	}
	assert(!task_isconnected());
	return ERRR_OK;
}



DECL_END

#undef FUNC_VECTORPHYS
#undef BUFFER_TYPE
#undef VECTOR_TYPE
#undef ENTRY_TYPE
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_PHYS
