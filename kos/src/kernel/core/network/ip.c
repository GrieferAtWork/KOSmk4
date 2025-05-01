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
#ifndef GUARD_KERNEL_SRC_NETWORK_IP_C
#define GUARD_KERNEL_SRC_NETWORK_IP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/printk.h>
#include <sched/async.h>
#include <sched/cpu.h>
#include <sched/tsc.h>

#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>

#include <kos/net/printf.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <network/arp.h>
#include <network/ip.h>
#include <network/network.h>
#include <network/packet.h>
#include <network/udp.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stdalign.h>
#include <string.h>

DECL_BEGIN


/* Finalize a given network IP datagrams descriptor. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL network_ip_datagrams_fini)(struct network_ip_datagrams *__restrict self) {
	size_t i;
	assert(self->nid_size <= self->nid_alloc);
	assert((self->nid_alloc != 0) == (self->nid_list != NULL));
	for (i = 0; i < self->nid_size; ++i)
		kfree(self->nid_list[i].dg_buf);
	kfree(self->nid_list);
}

/* Find the index containing the specified datagram (return!=NULL),
 * or the index where that datagram ~would~ exist at (return==NULL)
 * NOTE: The caller must be holding a lock to `self->nid_lock' */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 3)) struct ip_datagram *
NOTHROW(KCALL network_ip_datagrams_findentry)(struct network_ip_datagrams const *__restrict self,
                                              union ip_datagram_id id, size_t *__restrict pindex) {
	size_t i;
	BSEARCH (i, self->nid_list, self->nid_size, .dg_id.dg_uid, id.dg_uid) {
		*pindex = i;
		return &self->nid_list[i];
	}
	*pindex = i;
	return NULL;
}

/* Delete the indexed datagram.
 * NOTE: The caller is responsible to inherit the datagram's buffer,
 *       as well as be holding a lock to `self'! */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(KCALL network_ip_datagrams_delete)(struct network_ip_datagrams *__restrict self,
                                           size_t index) {
	/* Delete the datagram. */
	assert(self->nid_size != 0);
	--self->nid_size;
	memmovedown(&self->nid_list[index],
	            &self->nid_list[index + 1],
	            self->nid_size - index,
	            sizeof(struct ip_datagram));
	/* Try to truncate the datagram vector to release unused memory. */
	/* XXX: Also do this as part of `system_cc()' */
	if unlikely(self->nid_size + 128 < self->nid_alloc) {
		size_t new_alloc;
		struct ip_datagram *new_vector;
		new_alloc  = self->nid_size + 64;
		new_vector = (struct ip_datagram *)krealloc_nx(self->nid_list,
		                                               new_alloc * sizeof(struct ip_datagram),
		                                               GFP_ATOMIC);
		if likely(new_vector) {
			self->nid_list  = new_vector;
			self->nid_alloc = new_alloc;
		}
	}
}

/* Fill in a given section of the IP datagram payload and  update
 * hole descriptors accordingly. If There are no more holes,  and
 * the `IP_DATAGRAM_FLAG_GOTLAST' flag  has been  set, `true'  is
 * returned and `self->dg_hol'  may not  be updated  accordingly.
 * Otherwise (i.e. when the datagram remains incomplete), `false'
 * is returned. */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 4)) bool
NOTHROW(KCALL ip_datagram_write)(struct ip_datagram *__restrict self,
                                 u16 start_offset, u16 end_offset,
                                 void const *__restrict data, u16 length) {
#define holeat(offset) ((struct ip_datagram_hole *)((byte_t *)self->dg_buf + (offset)))
	struct ip_datagram_hole *hole;
	struct ip_datagram_hole *firsthole;
	u16 *hole_pself, hole_start;
	u16 firsthole_start;
	assert(length != 0);
	assert(start_offset + length == end_offset);
	assert(end_offset > start_offset);
	assert(end_offset <= self->dg_len);
	if unlikely(self->dg_hol == 0xffff) {
		/* Simple case: No holes left to be filled in. */
		memcpy((byte_t *)self->dg_buf + start_offset, data, length);
		return (self->dg_flg & IP_DATAGRAM_FLAG_GOTLAST) != 0;
	}
	assert(self->dg_hol < self->dg_len);
	hole = holeat(self->dg_hol);
	assert(hole->dh_end <= self->dg_len);
	if unlikely(start_offset >= hole->dh_end) {
		/* Simple case: the specified range lies beyond  the end of the last  hole.
		 *              In other words: This write doesn't actually fill any holes! */
writeall_return_false:
		memcpy((byte_t *)self->dg_buf + start_offset, data, length);
		return false;
	}
	/* Must  delete  all  holes  that   are  overlapping  with  the  given   range.
	 * First this, skip all leading holes that only begin after, or at `end_offset' */
	hole_pself = &self->dg_hol;
	hole_start = self->dg_hol;
	while (hole_start >= end_offset) {
		hole_pself = &hole->dh_prev;
		hole_start = hole->dh_prev;
		if (hole_start == 0xffff) {
			/* All holes only begin after `end_offset' */
			goto writeall_return_false;
		}
		hole = holeat(hole_start);
	}
	assert(hole_start < end_offset);
	/* Check for special case: The written range begins _after_ `hole' starts,
	 * meaning that the leading portion of `hole' doesn't get overwritten, and
	 * that `hole' may even be split into 2 new ones. */
	if (start_offset > hole_start) {
		if (end_offset >= hole->dh_end) {
			/* Simply truncate this hole. */
			hole->dh_end = start_offset;
		} else {
			struct ip_datagram_hole *newhole;
			/* Must set-up 2 holes:
			 *  - Truncate the existing hole
			 *  - Create a new hole at the end of the written area */
			newhole = holeat(end_offset);
			newhole->dh_prev = hole_start;
			newhole->dh_end  = hole->dh_end;
			hole->dh_end     = start_offset;
			*hole_pself      = end_offset;
		}
		goto writeall_return_false;
	}
	/* If this hole ends after `end_offset', then it has to be split in two at `end_offset'. */
	if (end_offset < hole->dh_end) {
		struct ip_datagram_hole *newhole;
		newhole = holeat(end_offset);
		newhole->dh_end  = hole->dh_end;
		newhole->dh_prev = hole->dh_prev;
		*hole_pself = end_offset;
		hole = newhole;
	}
	assert(start_offset <= hole_start);
	assert(end_offset > hole_start);
	assert(end_offset >= hole->dh_end);
	/* Find the first (or last from the right) hole  that
	 * still overlaps with the written range (or in other
	 * words: the hole where `->dh_end > start_offset'). */
	firsthole_start = hole->dh_prev;
	for (;;) {
		if (firsthole_start == 0xffff) {
			/* All leading holes are being overwritten. */
			*hole_pself = 0xffff;
			goto do_copy_and_check;
		}
		firsthole = holeat(firsthole_start);
		if (start_offset >= firsthole->dh_end) {
			/* This hole doesn't get overwritten. */
			*hole_pself = firsthole_start;
			goto writeall_return_false;
		}
		if (start_offset > firsthole_start) {
			/* This hole gets partially overwritten */
			*hole_pself = firsthole_start;
			firsthole->dh_end = start_offset;
			goto writeall_return_false;
		}
		firsthole_start = firsthole->dh_prev;
	}
do_copy_and_check:
	memcpy((byte_t *)self->dg_buf + start_offset, data, length);
	return (self->dg_hol == 0xffff) &&
	       (self->dg_flg & IP_DATAGRAM_FLAG_GOTLAST) != 0;
#undef holeat
}


/* Route a given IP packet.
 * @assume(packet_size >= 20); */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
ip_routepacket(struct nicdev *__restrict dev,
               void const *__restrict packet_data,
               size_t packet_size) {
	struct iphdr *hdr;
	u16 header_length, total_length, offset;
	assert(packet_size >= 20);
	hdr = (struct iphdr *)packet_data;
	if unlikely(hdr->ip_v != IPVERSION) {
		/* Bad IP version. */
		device_getname_lock_acquire(dev);
		printk(KERN_ERR "[ip:%s] Bad IP version in header isn't 4, but is %u\n",
		       device_getname(dev), hdr->ip_v);
		device_getname_lock_release(dev);
		return;
	}
	/* Check for simple case: The packet isn't fragmented. */
	offset        = ntohs(hdr->ip_off);
	total_length  = ntohs(hdr->ip_len);
	header_length = hdr->ip_hl * 4;
	if unlikely(header_length < 20) {
		/* Header too small. */
		device_getname_lock_acquire(dev);
		printk(KERN_ERR "[ip:%s] ip.siz[%" PRIu16 "] is less than 20\n",
		       device_getname(dev), header_length);
		device_getname_lock_release(dev);
		return;
	}
	if unlikely(header_length > total_length) {
		/* Header too large. */
		device_getname_lock_acquire(dev);
		printk(KERN_ERR "[ip:%s] iphdr.siz[%" PRIu16 "] exceeds dgram.siz[%" PRIu16 "]\n",
		       device_getname(dev), header_length, total_length);
		device_getname_lock_release(dev);
		return;
	}
	if unlikely(total_length > packet_size) {
		/* total too large. */
		device_getname_lock_acquire(dev);
		printk(KERN_ERR "[ip:%s] payload.siz[%" PRIu16 "] exceeds pck.siz[%" PRIuSIZ "]\n",
		       device_getname(dev), header_length, packet_size);
		device_getname_lock_release(dev);
		return;
	}
	/* Check for simple case: (offset == 0 && MF == 0) --> Non-fragmented */
	if ((offset & (IP_MF | IP_OFFMASK)) == 0) {
		/* Complete datagram (can be routed directly!) */
		assert(total_length >= 20);
		ip_routedatagram(dev, (struct iphdr *)packet_data, total_length);
		return;
	}
	{
		size_t i;
		u16 fragment_start, fragment_end, fragment_size;
		byte_t *fragment_payload; /* Fragment payload pointer. */
		union ip_datagram_id uid;
		struct ip_datagram *dg;
		struct timespec now;
		/* Calculate the fragment's effective size
		 * NOTE: There is a special case where the fragment with offset=0
		 *       is  also used to  set the header  of the final datagram! */
		fragment_start   = (offset & IP_OFFMASK) * 8;
		fragment_size    = total_length;
		fragment_payload = (byte_t *)packet_data;
		if (fragment_start != 0) {
			if (fragment_start < 20) {
				/* Only offset=0 fragments are allowed to write the IP header. */
				device_getname_lock_acquire(dev);
				printk(KERN_ERR "[ip:%s] dgram.frag[start=%" PRIu16 ",siz=%" PRIu16 "] clips into iphdr\n",
				       device_getname(dev), fragment_start, fragment_size);
				device_getname_lock_release(dev);
				return;
			}
			/* Non-first-fragment (only include the payload within the final datagram) */
			fragment_payload += header_length;
			fragment_size -= total_length;
		} else {
			assert(fragment_size >= 20);
		}
		/* Calculate the fragment's end-offset */
		if (OVERFLOW_UADD(fragment_start, fragment_size, &fragment_end)) {
			/* Fragment buffer area is out-of-bounds. */
			device_getname_lock_acquire(dev);
			printk(KERN_ERR "[ip:%s] dgram.frag[start=%" PRIu16 ",siz=%" PRIu16 "] overflows its end-offset\n",
			       device_getname(dev), fragment_start, fragment_size);
			device_getname_lock_release(dev);
			return;
		}
		/* Collect all of the information used to identify incoming datagrams. */
		uid.dg_src  = hdr->ip_src;
		uid.dg_did  = hdr->ip_id;
		uid.dg_pro  = hdr->ip_p;
		uid._dg_pad = 0;
		now = realtime();
		/* Complicated case: Fragmented packet.
		 * -> Search for an existing datagram. */
again_lock_datagrams:
		network_ip_datagrams_acquire(&dev->nd_net.n_ipgrams);
		dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
		if (dg) {
			/* Fragment already exists.
			 * Firstly: Check the packet's timeout field (we must ignore packets after they've timed out!). */
			if unlikely(now.tv_sec > dg->dg_tmo) {
				struct iphdr *datagram;
				/* Discard this packet. */
				device_getname_lock_acquire(dev);
				printk(KERN_ERR "[ip:%s] Timeout while receiving datagram "
				                "from " NET_PRINTF_IPADDR_FMT "\n",
				       device_getname(dev),
				       NET_PRINTF_IPADDR_ARG(uid.dg_src.s_addr));
				device_getname_lock_release(dev);
				datagram = dg->dg_buf; /* Inherit */
				/* Delete the datagram. */
				assert(dg == &dev->nd_net.n_ipgrams.nid_list[i]);
				network_ip_datagrams_delete(&dev->nd_net.n_ipgrams, i);
				network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
				kfree(datagram);
				return;
			}

			/* Check for simple case: This fragment fits into the pre-existing buffer. */
			if (fragment_end <= dg->dg_len) {
/*do_write_fragment:*/
				/* Set the `IP_DATAGRAM_FLAG_GOTLAST' flag if this fragment is the last one. */
				if (!(offset & IP_MF)) {
					/* Check if we've already had another last-fragment */
					if unlikely(dg->dg_flg & IP_DATAGRAM_FLAG_GOTLAST) {
						struct iphdr *datagram;
						/* Discard this packet. */
						device_getname_lock_acquire(dev);
						printk(KERN_ERR "[ip:%s] Multiple last fragments in datagram "
						                "from " NET_PRINTF_IPADDR_FMT "\n",
						       device_getname(dev),
							   NET_PRINTF_IPADDR_ARG(uid.dg_src.s_addr));
						device_getname_lock_release(dev);
						datagram = dg->dg_buf; /* Inherit */
						/* Delete the datagram. */
						assert(dg == &dev->nd_net.n_ipgrams.nid_list[i]);
						network_ip_datagrams_delete(&dev->nd_net.n_ipgrams, i);
						network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
						kfree(datagram);
						return;
					}
					dg->dg_flg |= IP_DATAGRAM_FLAG_GOTLAST;
				}
do_write_fragment_nogotlast:
				if (ip_datagram_write(dg, fragment_start, fragment_end, fragment_payload, fragment_size))
					goto datagram_complete_and_unlock;
				network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
				return;
			}

			/* The fragment doesn't fit into the already-allocated buffer.
			 * Make sure that  the `IP_DATAGRAM_FLAG_GOTLAST' flag  hasn't
			 * been set already. */
			if unlikely(dg->dg_flg & IP_DATAGRAM_FLAG_GOTLAST) {
				struct iphdr *datagram;
				/* Discard this packet. */
				device_getname_lock_acquire(dev);
				printk(KERN_ERR "[ip:%s] Fragment from " NET_PRINTF_IPADDR_FMT " "
				                "at %" PRIu16 "-%" PRIu16 " would exceed the "
				                "last fragment maximum at %" PRIu16 "\n",
				       device_getname(dev), NET_PRINTF_IPADDR_ARG(uid.dg_src.s_addr),
				       fragment_start, fragment_end - 1, dg->dg_len);
				device_getname_lock_release(dev);
				datagram = dg->dg_buf; /* Inherit */
				/* Delete the datagram. */
				assert(dg == &dev->nd_net.n_ipgrams.nid_list[i]);
				network_ip_datagrams_delete(&dev->nd_net.n_ipgrams, i);
				network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
				kfree(datagram);
				return;
			}
			/* Must extend the datagram's buffer. */
			{
				struct iphdr *new_buffer;
				u16 old_length;
				new_buffer = (struct iphdr *)krealloc_nx(dg->dg_buf, fragment_end, GFP_ATOMIC);
				if unlikely(!new_buffer) {
					/* Must extend while blocking... */
					network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
					new_buffer = (struct iphdr *)kmalloc(fragment_end, GFP_NORMAL);
					network_ip_datagrams_acquire(&dev->nd_net.n_ipgrams);
					/* Check to see if anything's changed... */
					dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
					if unlikely(!dg || fragment_end <= dg->dg_len ||
					            (dg->dg_flg & IP_DATAGRAM_FLAG_GOTLAST)) {
						network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
						kfree(new_buffer);
						goto again_lock_datagrams;
					}
					/* Copy already-written fragment data. */
					memcpy(new_buffer, dg->dg_buf, dg->dg_len);
					/* Free the old buffer.
					 * NOTE: Because hole-descriptors  use  buffer-relative  pointer,
					 *       we don't need to update them in this case, or the atomic
					 *       realloc case above! */
					kfree(dg->dg_buf);
				}
				dg->dg_buf = new_buffer;
				old_length = dg->dg_len;
				dg->dg_len = fragment_end;
				/* Set the `IP_DATAGRAM_FLAG_GOTLAST' flag if this fragment is the last one. */
				if (!(offset & IP_MF))
					dg->dg_flg |= IP_DATAGRAM_FLAG_GOTLAST;
				if (fragment_start == old_length) {
					/* The entirety of the fragment exists exactly at the end of the old datagram.
					 * With  this in mind,  we don't need  to create/update/delete/etc. hole data,
					 * since no new holes got created! */
					memcpy((byte_t *)dg->dg_buf + fragment_start, fragment_payload, fragment_size);
					if (dg->dg_flg & IP_DATAGRAM_FLAG_GOTLAST)
						goto datagram_complete_and_unlock;
				} else if (fragment_start > old_length) {
					/* The trailing fragment creates a new hole at `old_length...fragment_start-1' */
					struct ip_datagram_hole *hole;
					memcpy((byte_t *)dg->dg_buf + fragment_start, fragment_payload, fragment_size);
					hole = (struct ip_datagram_hole *)((byte_t *)dg->dg_buf + old_length);
					hole->dh_prev = dg->dg_hol;
					hole->dh_end  = fragment_start;
					dg->dg_hol    = old_length;
				} else {
					/* Highly unlikely case:  The current  fragment partially  overlaps
					 * with some older fragment such  that the new fragment is  larger.
					 * The standard allows this, however in practice there really isn't
					 * a good reason for this to ever happen...
					 * We handle this case by creating a new hole at the end, and doing
					 * a normal datagram write. */
					struct ip_datagram_hole *hole;
					if (dg->dg_hol != 0xffff) {
						hole = (struct ip_datagram_hole *)((byte_t *)dg->dg_buf + dg->dg_hol);
						if (hole->dh_end == old_length) {
							/* Extend this hole to include the new free space. */
							hole->dh_end = fragment_end;
							goto do_write_fragment_nogotlast;
						}
					}
					hole = (struct ip_datagram_hole *)((byte_t *)dg->dg_buf + old_length);
					hole->dh_prev = dg->dg_hol;
					hole->dh_end  = fragment_end;
					dg->dg_hol    = old_length;
					goto do_write_fragment_nogotlast;
				}
				network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
				return;
			}
		}
		{
			struct iphdr *datagram;
			/* Begin a new datagram.
			 * Step #1: Allocate the initial buffer for the datagram. */
			datagram = (struct iphdr *)kmalloc_nx(fragment_end, GFP_ATOMIC);
			if unlikely(!datagram) {
				/* Must allocate while blocking... */
				network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
				datagram = (struct iphdr *)kmalloc(fragment_end, GFP_NORMAL);
				network_ip_datagrams_acquire(&dev->nd_net.n_ipgrams);
				dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
				if unlikely(dg != NULL) {
					network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
					kfree(datagram);
					goto again_lock_datagrams;
				}
			}
			/* Step #2: Make sure that the datagram vector has sufficient space */
			assert(dev->nd_net.n_ipgrams.nid_size <= dev->nd_net.n_ipgrams.nid_alloc);
			if (dev->nd_net.n_ipgrams.nid_size >= dev->nd_net.n_ipgrams.nid_alloc) {
				size_t new_alloc;
				struct ip_datagram *new_vector;
				/* Must allocate space for more datagrams. */
				new_alloc  = dev->nd_net.n_ipgrams.nid_size + 64;
				new_vector = (struct ip_datagram *)krealloc_nx(dev->nd_net.n_ipgrams.nid_list,
				                                               new_alloc * sizeof(struct ip_datagram),
				                                               GFP_ATOMIC);
				if unlikely(!new_vector) {
					new_alloc  = dev->nd_net.n_ipgrams.nid_size + 1;
					new_vector = (struct ip_datagram *)krealloc_nx(dev->nd_net.n_ipgrams.nid_list,
					                                               new_alloc * sizeof(struct ip_datagram),
					                                               GFP_ATOMIC);
					if unlikely(!new_vector) {
						/* Must allocate while blocking. */
						network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
						new_alloc  = dev->nd_net.n_ipgrams.nid_size + 64;
						new_vector = (struct ip_datagram *)krealloc_nx(dev->nd_net.n_ipgrams.nid_list,
						                                               new_alloc * sizeof(struct ip_datagram),
						                                               GFP_NORMAL);
						if unlikely(!new_vector) {
							new_alloc  = dev->nd_net.n_ipgrams.nid_size + 1;
							TRY {
								new_vector = (struct ip_datagram *)krealloc(dev->nd_net.n_ipgrams.nid_list,
								                                            new_alloc * sizeof(struct ip_datagram),
								                                            GFP_NORMAL);
							} EXCEPT {
								kfree(datagram);
								RETHROW();
							}
						}
						network_ip_datagrams_acquire(&dev->nd_net.n_ipgrams);
						dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
						if unlikely(dg != NULL || new_alloc < dev->nd_net.n_ipgrams.nid_alloc) {
							network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
							kfree(new_vector);
							kfree(datagram);
							goto again_lock_datagrams;
						}
						/* Free the old datagram vector (since we didn't use krealloc() to re-use it). */
						kfree(dev->nd_net.n_ipgrams.nid_list);
					} /* if unlikely(!new_vector) */
				} /* if unlikely(!new_vector) */
				/* Install the new vector. */
				dev->nd_net.n_ipgrams.nid_list  = new_vector;
				dev->nd_net.n_ipgrams.nid_alloc = new_alloc;
			}
			assert(dev->nd_net.n_ipgrams.nid_size < dev->nd_net.n_ipgrams.nid_alloc);
			/* Construct (and fill) a new datagram in `dev->nd_net.n_ipgrams.nid_list[i]' */
			dg = &dev->nd_net.n_ipgrams.nid_list[i];
			memmoveup(dg + 1, dg,
			          dev->nd_net.n_ipgrams.nid_size - i,
			          sizeof(struct ip_datagram));
			dg->dg_id.dg_uid = uid.dg_uid;
			/* Use a timeout of 60 seconds, as specified here:
			 * https://tools.ietf.org/html/rfc2460#page-22 */
			dg->dg_tmo = now.tv_sec + 60;
			dg->dg_flg = IP_DATAGRAM_FLAG_NORMAL;
			dg->dg_len = fragment_end;
			dg->dg_buf = datagram;
			dg->dg_hol = 0xffff;
			/* Copy data for the first fragment. */
			memcpy(datagram + fragment_start, fragment_payload, fragment_size);
			if (fragment_start != 0) {
				/* Setup a hole descriptor for in front of this first segment. */
				struct ip_datagram_hole *hole;
				hole = (struct ip_datagram_hole *)datagram;
				hole->dh_prev = 0xffff;
				hole->dh_end  = fragment_start;
				dg->dg_hol    = 0; /* Fragment hole at offset=0 */
			}
			network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
			return;
		}
datagram_complete_and_unlock:
		{
			struct iphdr *datagram;
			u16 datagram_len;
			datagram     = dg->dg_buf; /* Inherit */
			datagram_len = dg->dg_len;
			/* Delete the datagram. */
			assert(dg == &dev->nd_net.n_ipgrams.nid_list[i]);
			network_ip_datagrams_delete(&dev->nd_net.n_ipgrams, i);
			network_ip_datagrams_release(&dev->nd_net.n_ipgrams);
			RAII_FINALLY { kfree(datagram); };
			ip_routedatagram(dev, datagram, datagram_len);
			return;
		}
	}
}


/* Route an IP datagram after it has been fully re-assembled.
 * @assume(packet->ip_hl >= 5);
 * @assume(packet->ip_hl * 4 <= packet_size);
 * @assume(packet_size >= 20); */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
ip_routedatagram(struct nicdev *__restrict dev,
                 struct iphdr const *__restrict packet,
                 u16 packet_size) {
	u16 iphdr_size, payload_len;
	byte_t const *payload;
	assert(packet_size >= 20);
	iphdr_size = packet->ip_hl * 4;
	assertf(iphdr_size >= 20, "Guarantied by the caller");
	assertf(iphdr_size <= packet_size, "Guarantied by the caller");
	payload     = (byte_t const *)packet + iphdr_size;
	payload_len = packet_size - iphdr_size;
	/* Route the datagram based on the protocol number. */
	switch (packet->ip_p) {

	case IPPROTO_UDP:
		if unlikely(payload_len < sizeof(struct udphdr)) {
			device_getname_lock_acquire(dev);
			printk(KERN_ERR "[ip:%s] udp packet of ip[siz=%" PRIu16 "] "
			                "from " NET_PRINTF_IPADDR_FMT " is too small\n",
			       device_getname(dev), packet_size,
			       NET_PRINTF_IPADDR_ARG(packet->ip_src.s_addr));
			device_getname_lock_release(dev);
			return;
		}
		udp_routepacket(dev, (struct udphdr const *)payload,
		                payload_len, packet);
		break;

	default:
		device_getname_lock_acquire(dev);
		printk(KERN_WARNING "[ip:%s] Unrecognized ip packet [prot=%#.2" PRIx8 ",siz=%" PRIu16 "]\n",
		       device_getname(dev), packet->ip_p, packet_size);
		device_getname_lock_release(dev);
		break;
	}
}




/* Calculate and fill in the `ip_sum' field of the given ip header. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL iphdr_calculate_sum)(struct iphdr *__restrict self) {
	u32 chksum;
	u16 i, cnt;
	be16 *base;
	self->ip_sum = htons(0);
	cnt  = self->ip_hl * 2;
	base = (be16 *)self;
	for (i = 0, chksum = 0; i < cnt; ++i) {
		chksum += ntohs(base[i]);
	}
	if (chksum > 0xffff)
		chksum += (chksum >> 16);
	chksum = ~chksum;
	self->ip_sum = htons((u16)chksum);
}



/* Add the ARP request response timeout to `timeout' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL nic_device_add_arp_response_timeout)(struct nicdev *__restrict self,
                                                   ktime_t *__restrict timeout) {
	(void)self;
	/* XXX: This timeout should be a field of the NIC device... */
	*timeout += relktime_from_milliseconds(100);
}


struct ip_arp_and_datagram_job: async {
	REF struct nicdev    *adj_dev;    /* [1..1][const] The associated network device. */
	REF struct net_peeraddr  *adj_peer;   /* [1..1][const][valid_if(adj_arpc != 0)] The peer who's mac address we're in need of. */
	REF struct nic_packet    *adj_gram;   /* [1..1][const][valid_if(adj_arpc != 0)] The IP datagram (with sufficient header space for an ethernet header) */
	REF struct mman          *adj_grammm; /* [1..1][const][valid_if(adj_arpc != 0)] The VM in the context of which `adj_gram' must be sent */
	ktime_t                   adj_arptmo; /* Timeout for ARP request responses. */
	unsigned int              adj_arpc;   /* # of remaining ARP request attempts (set to 0 when the peer's mac became available). */
	struct aio_handle_generic adj_done;   /* [valid_if(adj_arpc == 0)] AIO handle used to wait for transmit completion of `adj_gram' */
	/* XXX: Have another state where we wait for an ARP request to finish being sent?
	 *      Right  now, our ARP timeout starts as soon as the ARP request is started,
	 *      rather than waiting until the ARP request has made it through our NIC... */
};

PRIVATE NONNULL((1)) void KCALL
nic_device_send_arp_request(struct nicdev *__restrict self, be32 ip) {
	REF struct nic_packet *areq;
	areq = arp_makemacrequest(self, ip);
	FINALLY_DECREF_UNLIKELY(areq);
	nicdev_send_background(self, areq);
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ip_arp_and_datagram_destroy)(struct async *__restrict self) {
	struct ip_arp_and_datagram_job *me;
	me = (struct ip_arp_and_datagram_job *)self;
	if (me->adj_arpc == 0) {
		aio_handle_generic_fini(&me->adj_done);
	} else {
		decref_likely(me->adj_grammm);
		decref_likely(me->adj_gram);
		decref_unlikely(me->adj_peer);
	}
	decref_unlikely(me->adj_dev);
	kfree(me);
}


PRIVATE NONNULL((1)) ktime_t FCALL
ip_arp_and_datagram_connect(struct async *__restrict self) {
	struct ip_arp_and_datagram_job *me;
	me = (struct ip_arp_and_datagram_job *)self;
	if (me->adj_arpc == 0) {
		/* Wait for the send to be completed. */
		aio_handle_generic_connect_for_poll(&me->adj_done);
		return KTIME_INFINITE;
	}
	task_connect_for_poll(&me->adj_dev->nd_net.n_addravl);
	/* Setup a timeout before re-sending the ARP request. */
	return me->adj_arptmo;
}

PRIVATE NONNULL((1)) bool FCALL
ip_arp_and_datagram_test(struct async *__restrict self) {
	struct ip_arp_and_datagram_job *me;
	me = (struct ip_arp_and_datagram_job *)self;
	if (me->adj_arpc == 0) {
		/* Wait for the send to be completed. */
		return aio_handle_generic_hascompleted(&me->adj_done);
	}
	/* Wait for the peer's MAC to become available. */
	if (me->adj_peer->npa_flags & NET_PEERADDR_HAVE_MAC)
		return true; /* Move on to sending the datagram. */
	return false;
}

PRIVATE NONNULL((1)) unsigned int FCALL
ip_arp_and_datagram_work(struct async *__restrict self) {
	struct ip_arp_and_datagram_job *me;
	me = (struct ip_arp_and_datagram_job *)self;
	if (me->adj_arpc == 0) {
		assert(aio_handle_generic_hascompleted(&me->adj_done));
		aio_handle_generic_checkerror(&me->adj_done);
		return ASYNC_FINISHED;
	}
	/* Check if the MAC has become available. */
	if (me->adj_peer->npa_flags & NET_PEERADDR_HAVE_MAC) {
		/* There we go! */
		struct ethhdr *eth;
		eth = nic_packet_tallochead(me->adj_gram, struct ethhdr);
		memcpy(eth->h_dest, me->adj_peer->npa_hwmac, ETH_ALEN);
		memcpy(eth->h_source, me->adj_dev->nd_addr.na_hwmac, ETH_ALEN);
		eth->h_proto = htons(ETH_P_IP);

		/* Send the packet. */
		aio_handle_generic_init(&me->adj_done);
		{
			REF struct mman *oldmm;
			oldmm = task_xchmman(me->adj_grammm);
			RAII_FINALLY { task_setmman_inherit(oldmm); };
			nicdev_send(me->adj_dev, me->adj_gram, &me->adj_done);
		}

		/* Drop reference and switch to wait-for-transmit-complete mode. */
		COMPILER_BARRIER();
		decref_unlikely(me->adj_peer);
		decref_unlikely(me->adj_gram);
		decref_unlikely(me->adj_grammm);
		COMPILER_WRITE_BARRIER();
		me->adj_arpc = 0;
		COMPILER_BARRIER();
	}
	return ASYNC_RESUME;
}

PRIVATE NONNULL((1)) unsigned int FCALL
ip_arp_and_datagram_time(struct async *__restrict self) {
	struct ip_arp_and_datagram_job *me;
	me = (struct ip_arp_and_datagram_job *)self;
	assert(me->adj_arpc != 0);
	/* Check once again if the MAC has become available (unlikely) */
	if (me->adj_peer->npa_flags & NET_PEERADDR_HAVE_MAC)
		return ASYNC_RESUME;
	/* Check if this was the last attempt */
	if (me->adj_arpc == 1) {
		THROW(E_NET_HOST_UNREACHABLE); /* XXX: Exception pointers? */
	}
	--me->adj_arpc;
	/* Re-try sending the ARP request. */
	nic_device_send_arp_request(me->adj_dev,
	                            me->adj_peer->npa_ip);
	me->adj_arptmo = ktime();
	nic_device_add_arp_response_timeout(me->adj_dev, &me->adj_arptmo);
	return ASYNC_RESUME;
}

PRIVATE NONNULL((1)) void FCALL
ip_arp_and_datagram_cancel(struct async *__restrict self) {
	struct ip_arp_and_datagram_job *me;
	me = (struct ip_arp_and_datagram_job *)self;
	if (me->adj_arpc == 0) {
		aio_handle_cancel(&me->adj_done);
	} else {
		/* XXX: Cancel the current ARP request? */
	}
}


PRIVATE struct async_ops const ip_arp_and_datagram = {
	.ao_driver  = &drv_self,
	.ao_destroy = &ip_arp_and_datagram_destroy,
	.ao_connect = &ip_arp_and_datagram_connect,
	.ao_test    = &ip_arp_and_datagram_test,
	.ao_work    = &ip_arp_and_datagram_work,
	.ao_time    = &ip_arp_and_datagram_time,
	.ao_cancel  = &ip_arp_and_datagram_cancel,
};


/* Send a given IP datagram packet `packet'.
 * NOTE: The caller is responsible to ensure that `packet'
 *       still  has sufficient head/tail memory to include
 *       ethernet headers.
 * Or in other words, this function assumes that:
 * >> assert(nic_packet_headfree(packet) >= ETH_PACKET_HEADSIZE);
 * >> assert(nic_packet_tailfree(packet) >= ETH_PACKET_TAILSIZE);
 * - Additionally, the caller  is responsible to  ensure that  the
 *   fully  initialized IP header (i.e. `struct iphdr') is pointed
 *   to by `packet->np_head' upon entry, as this function will try
 *   to read from that structure in order to figure out addressing
 *   information that are required for filling in information  for
 *   underlying network layers.
 * - NOTE: If necessary, this function will also perform the required
 *         ARP network traffic  in order to  translate the target  IP
 *         address pointed to by the IP header of `packet'.
 * NOTE: This function automatically fills in the following fields of the IP header:
 *   - ip_v      (With the value `4')
 *   - ip_len    (With the value `nic_packet_size(packet)')
 *   - ip_id     (using `struct net_peeraddr::npa_ipgramid')
 *   - ip_off    (as required for fragmentation; the RF and DF flags are not overwritten!)
 *   - ip_sum    (Only if not done by hardware, then will be filled with the correct value)
 * With this in mind, the caller must have already filled in:
 *   - ip_hl     (header length divided by 4; set to `5' if no IP options are present)
 *   - ip_tos    (Type of IP service)
 *   - ip_off.RF (Should already be cleared)
 *   - ip_off.DF (Don't-fragment flag)
 *   - ip_ttl    (Time to live)
 *   - ip_p      (IP Protocol; One of `IPPROTO_*')
 *   - ip_src    (Sender IP address (usually `dev->nd_addr.na_ip', or a broadcast IP))
 *   - ip_dst    (Target IP address) */
PUBLIC NONNULL((1, 2, 3)) void KCALL
ip_senddatagram(struct nicdev *__restrict dev,
                struct nic_packet *__restrict packet,
                struct aio_handle *__restrict aio) {
	struct iphdr *hdr;
	size_t total_packet_size;
	REF struct net_peeraddr *peer;
	u16 orig_offset;
	assert(nic_packet_headfree(packet) >= ETH_PACKET_HEADSIZE);
#if ETH_PACKET_TAILSIZE != 0
	assert(nic_packet_tailfree(packet) >= ETH_PACKET_TAILSIZE);
#endif /* ETH_PACKET_TAILSIZE != 0 */
	assert(nic_packet_headsize(packet) >= sizeof(struct iphdr));
	hdr = (struct iphdr *)packet->np_head;
	orig_offset = ntohs(hdr->ip_off);
	/* Check for simple case: the packet can fit into a single datagram. */
	total_packet_size = nic_packet_size(packet);
	if (total_packet_size > dev->nd_net.n_ipsize && !(orig_offset & IP_DF)) {
		/* Nope! In this case, we can't actually re-use `packet',
		 *       so use a packet descriptor instead, and off-load
		 *       the task to `ip_senddatagram_ex()'. */
		struct nic_packet_desc desc;
		nic_packet_desc_for_packet(&desc, packet);
		ip_senddatagram_ex(dev, &desc, aio);
		return;
	}
	peer = nic_device_requireip(dev, hdr->ip_dst.s_addr);
	{
		u16 dgramid;
		/* Fill in header fields that are automatically calculated.
		 * NOTE: We  use one  datagram ID per  peer so we  get the max
		 *       number of  unique IDs,  whilst not  leaking any  info
		 *       about how much we've been talking to different peers. */
		dgramid = atomic_fetchinc(&peer->npa_ipgramid);
		hdr->ip_v   = IPVERSION;
		hdr->ip_len = htons((u16)total_packet_size);
		hdr->ip_id  = htons(dgramid);
		hdr->ip_off = htons(orig_offset & (IP_RF | IP_DF));
		iphdr_calculate_sum(hdr);
	}
	if (peer->npa_flags & NET_PEERADDR_HAVE_MAC) {
		/* Simple case: we already have the MAC for this peer! */
		struct ethhdr *eth;
		eth = nic_packet_tallochead(packet, struct ethhdr);
		memcpy(eth->h_dest, peer->npa_hwmac, ETH_ALEN);
		decref_unlikely(peer);
		memcpy(eth->h_source, dev->nd_addr.na_hwmac, ETH_ALEN);
		eth->h_proto = htons(ETH_P_IP);
		/* Send the packet. */
		nicdev_send(dev, packet, aio);
		return;
	}
	{
		/* Send out an async job for doing the arp+send asynchronously */
		struct async *aj;
		struct ip_arp_and_datagram_job *job;
		/* Send the first ARP request.
		 * XXX: the async job should be configurable to wait for this... */
		TRY {
			nic_device_send_arp_request(dev, hdr->ip_dst.s_addr);
			aj = async_new_aio(struct ip_arp_and_datagram_job, &ip_arp_and_datagram, aio);
		} EXCEPT {
			decref_unlikely(peer);
			RETHROW();
		}
		job = (struct ip_arp_and_datagram_job *)aj;
		job->adj_dev    = (REF struct nicdev *)incref(dev);
		job->adj_peer   = peer; /* Inherit reference */
		job->adj_gram   = incref(packet);
		job->adj_grammm = incref(THIS_MMAN);
		job->adj_arptmo = ktime();
		nic_device_add_arp_response_timeout(dev, &job->adj_arptmo);
		job->adj_arpc = 5; /* Must not be 0, but should be configurable */
		/* Start the async job and attach it to the given AIO handle. */
		decref(async_start(aj));
	}
}



struct ip_arp_and_datagrams_job: async {
	REF struct nicdev         *adj_dev;    /* [1..1][const] The associated network device. */
	REF struct net_peeraddr       *adj_peer;   /* [1..1][const][valid_if(adj_arpc != 0)] The peer who's mac address we're in need of. */
	struct nic_packetlist          adj_gram;   /* [1..1][const][valid_if(adj_arpc != 0)] The IP datagram list (with sufficient header space for an ethernet header) */
	REF struct mman               *adj_grammm; /* [1..1][const][valid_if(adj_arpc != 0)] The VM in the context of which `adj_gram' must be sent */
	ktime_t                        adj_arptmo; /* Timeout for ARP request responses. */
	unsigned int                   adj_arpc;   /* # of remaining ARP request attempts (set to 0 when the peer's mac became available). */
	struct aio_multihandle_generic adj_done;   /* [valid_if(adj_arpc == 0)] AIO handle used to wait for transmit completion of `adj_gram' */
	/* XXX: Have another state where we wait for an ARP request to finish being sent?
	 *      Right  now, our ARP timeout starts as soon as the ARP request is started,
	 *      rather than waiting until the ARP request has made it through our NIC... */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ip_arp_and_datagrams_destroy)(struct async *__restrict self) {
	struct ip_arp_and_datagrams_job *me;
	me = (struct ip_arp_and_datagrams_job *)self;
	if (me->adj_arpc == 0) {
		aio_multihandle_generic_fini(&me->adj_done);
	} else {
		nic_packetlist_fini(&me->adj_gram);
		decref_unlikely(me->adj_grammm);
		decref_unlikely(me->adj_peer);
	}
	decref_unlikely(me->adj_dev);
	kfree(me);
}

PRIVATE NONNULL((1)) ktime_t FCALL
ip_arp_and_datagrams_connect(struct async *__restrict self) {
	struct ip_arp_and_datagrams_job *me;
	me = (struct ip_arp_and_datagrams_job *)self;
	if (me->adj_arpc == 0) {
		/* Wait for the send to be completed. */
		aio_multihandle_generic_connect_for_poll(&me->adj_done);
		return KTIME_INFINITE;
	}
	/* Wait for the peer's MAC to become available. */
	task_connect_for_poll(&me->adj_dev->nd_net.n_addravl);
	COMPILER_READ_BARRIER();
	return me->adj_arptmo;
}

PRIVATE ATTR_PURE NONNULL((1)) bool FCALL
ip_arp_and_datagrams_test(struct async *__restrict self) {
	struct ip_arp_and_datagrams_job *me;
	me = (struct ip_arp_and_datagrams_job *)self;
	if (me->adj_arpc == 0) {
		/* Wait for the send to be completed. */
		return aio_multihandle_generic_hascompleted(&me->adj_done);
	}
	if (me->adj_peer->npa_flags & NET_PEERADDR_HAVE_MAC)
		return true; /* Move on to sending the datagram. */
	return false;
}


PRIVATE NONNULL((1)) unsigned int FCALL
ip_arp_and_datagrams_work(struct async *__restrict self) {
	struct ip_arp_and_datagrams_job *me;
	me = (struct ip_arp_and_datagrams_job *)self;
	if (me->adj_arpc == 0) {
		assert(aio_multihandle_generic_hascompleted(&me->adj_done));
		aio_multihandle_generic_checkerror(&me->adj_done);
		return ASYNC_FINISHED;
	}
	/* Check if the MAC has become available. */
	if (me->adj_peer->npa_flags & NET_PEERADDR_HAVE_MAC) {
		/* There we go!
		 * Now all we've got to do is add ethernet headers to all segments. */
		size_t i;
		struct ethhdr hdr;
		memcpy(hdr.h_dest, me->adj_peer->npa_hwmac, ETH_ALEN);
		memcpy(hdr.h_source, me->adj_dev->nd_addr.na_hwmac, ETH_ALEN);
		hdr.h_proto = htons(ETH_P_IP);
		for (i = 0; i < me->adj_gram.npl_cnt; ++i) {
			struct ethhdr *eth;
			eth = nic_packet_tallochead(me->adj_gram.npl_vec[i], struct ethhdr);
			memcpy(eth, &hdr, sizeof(struct ethhdr));
		}

		/* Send all of the packets. */
		aio_multihandle_generic_init(&me->adj_done);
		TRY {
			REF struct mman *oldmm;
			oldmm = task_xchmman(me->adj_grammm);
			RAII_FINALLY { task_setmman_inherit(oldmm); };
			for (i = 0; i < me->adj_gram.npl_cnt; ++i) {
				struct aio_handle *hand;
				hand = aio_multihandle_allochandle(&me->adj_done);
				nicdev_send(me->adj_dev, me->adj_gram.npl_vec[i], hand);
			}
		} EXCEPT {
			aio_multihandle_cancel(&me->adj_done);
			RETHROW();
		}

		/* Drop reference and switch to wait-for-transmit-complete mode. */
		COMPILER_BARRIER();
		decref_unlikely(me->adj_peer);
		nic_packetlist_fini(&me->adj_gram);
		decref_unlikely(me->adj_grammm);
		COMPILER_WRITE_BARRIER();
		me->adj_arpc = 0;
		COMPILER_BARRIER();
	}
	return ASYNC_RESUME;
}

PRIVATE NONNULL((1)) unsigned int FCALL
ip_arp_and_datagrams_time(struct async *__restrict self) {
	struct ip_arp_and_datagrams_job *me;
	me = (struct ip_arp_and_datagrams_job *)self;
	assert(me->adj_arpc != 0);
	/* Check once again if the MAC has become available (unlikely) */
	if (me->adj_peer->npa_flags & NET_PEERADDR_HAVE_MAC)
		return ASYNC_RESUME;
	/* Check if this was the last attempt */
	if (me->adj_arpc == 1) {
		THROW(E_NET_HOST_UNREACHABLE); /* XXX: Exception pointers? */
	}
	--me->adj_arpc;
	/* Re-try sending the ARP request. */
	nic_device_send_arp_request(me->adj_dev,
	                            me->adj_peer->npa_ip);
	me->adj_arptmo = ktime();
	nic_device_add_arp_response_timeout(me->adj_dev, &me->adj_arptmo);
	return ASYNC_RESUME;
}

PRIVATE NONNULL((1)) void FCALL
ip_arp_and_datagrams_cancel(struct async *__restrict self) {
	struct ip_arp_and_datagrams_job *me;
	me = (struct ip_arp_and_datagrams_job *)self;
	if (me->adj_arpc == 0) {
		aio_multihandle_cancel(&me->adj_done);
	} else {
		/* XXX: Cancel the current ARP request? */
	}
}


PRIVATE struct async_ops const ip_arp_and_datagrams = {
	.ao_driver  = &drv_self,
	.ao_destroy = &ip_arp_and_datagrams_destroy,
	.ao_connect = &ip_arp_and_datagrams_connect,
	.ao_test    = &ip_arp_and_datagrams_test,
	.ao_work    = &ip_arp_and_datagrams_work,
	.ao_time    = &ip_arp_and_datagrams_time,
	.ao_cancel  = &ip_arp_and_datagrams_cancel,
};


/* Similar to `ip_senddatagram()',  however instead of  taking a  NIC
 * packet object, this function takes a packet descriptor. With  this
 * in mind, this function is more efficient in cases where the caller
 * isn't given a packet object, but rather, is presented with an I/O-
 * vector, or similar.
 * Note however that if you've been given a NIC packet, you should really
 * use the above function instead, since  doing so reduces the amount  of
 * copying necessary when the datagram can fit into a single fragment.
 * NOTE: This function automatically fills in the following fields of the IP header:
 *   - ip_v      (With the value `4')
 *   - ip_len    (With the value `nic_packet_size(packet)')
 *   - ip_id     (using `struct net_peeraddr::npa_ipgramid')
 *   - ip_off    (as required for fragmentation; the RF and DF flags are not overwritten!)
 *   - ip_sum    (Only if not done by hardware, then will be filled with the correct value)
 * With this in mind, the caller must have already filled in:
 *   - ip_hl     (header length divided by 4; set to `5' if no IP options are present)
 *   - ip_tos    (Type of IP service)
 *   - ip_off.RF (Should already be cleared)
 *   - ip_off.DF (Don't-fragment flag)
 *   - ip_ttl    (Time to live)
 *   - ip_p      (IP Protocol; One of `IPPROTO_*')
 *   - ip_src    (Sender IP address (usually `dev->nd_addr.na_ip', or a broadcast IP))
 *   - ip_dst    (Target IP address) */
PUBLIC NONNULL((1, 2, 3)) void KCALL
ip_senddatagram_ex(struct nicdev *__restrict dev,
                   struct nic_packet_desc const *__restrict packet,
                   struct aio_handle *__restrict aio) {
	struct async *aj;
	struct ip_arp_and_datagrams_job *job;
	REF struct net_peeraddr *peer;
	struct iphdr *hdr;
	assert(nic_packet_desc_headsize(packet) >= sizeof(struct iphdr));
	hdr  = (struct iphdr *)packet->npd_head;
	peer = nic_device_requireip(dev, hdr->ip_dst.s_addr);
	TRY {
		if (!(peer->npa_flags & NET_PEERADDR_HAVE_MAC))
			nic_device_send_arp_request(dev, peer->npa_ip);
#ifndef __OPTIMIZE_SIZE__
		else {
			/* XXX: No need to have the send-part be started by the async-job.
			 *      When the MAC is already  available, then _we_ can do  that
			 *      already! */
		}
#endif /* !__OPTIMIZE_SIZE__ */
		aj  = async_new_aio(struct ip_arp_and_datagrams_job, &ip_arp_and_datagrams, aio);
		job = (struct ip_arp_and_datagrams_job *)aj;
		TRY {
			size_t i;
			u16 dgramid, offset, offset_addend;
			/* Take these two flags from the original `ip_off' */
			offset_addend = ntohs(hdr->ip_off) & (IP_RF | IP_DF);
			nic_packetlist_init(&job->adj_gram);
			TRY {
				/* Split the packet into multiple segments. */
				struct nic_packet_desc used_packet;
				memcpy(&used_packet, packet, sizeof(used_packet));

				/* Don't include the original IP header within datagram fragments.
				 * Instead, the  IP header  is replicated  within every  fragment. */
				used_packet.npd_head += sizeof(struct iphdr);
				used_packet.npd_headsz -= sizeof(struct iphdr);
				assert((dev->nd_net.n_ipsize & 7) == 0);
				if unlikely(offset_addend & IP_DF) {
					/* Ignore `n_ipsize' and never create fragments! */
					struct nic_packet *pck;
					pck = nic_packetlist_newpacketv(&job->adj_gram, dev,
					                                &used_packet.npd_payload,
					                                IP_PACKET_HEADSIZE + used_packet.npd_headsz,
					                                used_packet.npd_tailsz + IP_PACKET_TAILSIZE);
					memcpy(nic_packet_allochead(pck, used_packet.npd_headsz),
					       used_packet.npd_head, used_packet.npd_headsz);
					if unlikely(used_packet.npd_tailsz) {
						memcpy(nic_packet_alloctail(pck, used_packet.npd_tailsz),
						       used_packet.npd_tail, used_packet.npd_tailsz);
					}
				} else {
					nic_packetlist_segments_ex(&job->adj_gram,
					                           dev, &used_packet,
					                           dev->nd_net.n_ipsize,
					                           IP_PACKET_HEADSIZE,
					                           IP_PACKET_TAILSIZE);
				}
			} EXCEPT {
				nic_packetlist_fini(&job->adj_gram);
				RETHROW();
			}

			/* Fill in header fields that are automatically calculated.
			 * NOTE: We  use one  datagram ID per  peer so we  get the max
			 *       number of  unique IDs,  whilst not  leaking any  info
			 *       about how much we've been talking to different peers. */
			dgramid = atomic_fetchinc(&peer->npa_ipgramid);

			/* Construct the IP headers for all of the fragments. */
			offset = 0;
			for (i = 0; i < job->adj_gram.npl_cnt; ++i) {
				struct nic_packet *pck;
				struct iphdr *fragment_hdr;
				u16 fraglen, used_offset;
				pck = job->adj_gram.npl_vec[i];
				fragment_hdr = nic_packet_tallochead(pck, struct iphdr);

				/* Default-fill the IP header with the one from the original datagram. */
				memcpy(fragment_hdr, hdr, sizeof(struct iphdr));
				fragment_hdr->ip_v = IPVERSION;
				if (i != 0) {
					/* An extended IP header gets placed into the first fragment payload. */
					fragment_hdr->ip_hl = sizeof(struct iphdr) / 4;
				}
				fraglen = (u16)nic_packet_size(pck);
				fragment_hdr->ip_len = htons(fraglen);
				fragment_hdr->ip_id  = htons(dgramid);
				assert((offset & 7) == 0);
				used_offset = offset / 8;
				assert((used_offset & ~IP_OFFMASK) == 0);
				used_offset |= offset_addend;
				if (i != job->adj_gram.npl_cnt - 1)
					used_offset |= IP_MF; /* There are more fragments. */
				fragment_hdr->ip_off = htons(used_offset);
				iphdr_calculate_sum(fragment_hdr);
				offset += fraglen;
			}
		} EXCEPT {
			async_free(aj);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(peer);
		RETHROW();
	}
	job->adj_dev    = (REF struct nicdev *)incref(dev);
	job->adj_peer   = peer; /* Inherit reference */
	job->adj_arptmo = ktime();
	job->adj_grammm = incref(THIS_MMAN);
	nic_device_add_arp_response_timeout(dev, &job->adj_arptmo);
	job->adj_arpc = 5; /* Must not be 0, but should be configurable */
	decref(async_start(aj));
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_IP_C */
