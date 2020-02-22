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
#ifndef GUARD_KERNEL_SRC_NETWORK_IP_C
#define GUARD_KERNEL_SRC_NETWORK_IP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <sched/async.h>
#include <sched/cpu.h>

#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>

#include <bits/in.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <network/arp.h>
#include <network/ip.h>
#include <network/network.h>
#include <network/packet.h>

#include <assert.h>
#include <inttypes.h>
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
	size_t i, lo, hi;
	BSEARCH_EX(i, lo, hi, self->nid_list, self->nid_size, .dg_id.dg_uid, id.dg_uid) {
		*pindex = i;
		return &self->nid_list[i];
	}
	assert(lo == hi);
	*pindex = lo;
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
	/* XXX: Also do this as part of `system_clearcaches()' */
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

/* Fill in a given section of the IP datagram payload and update
 * hole descriptors accordingly. If There are no more holes, and
 * the `IP_DATAGRAM_FLAG_GOTLAST' flag has been set, `true' is
 * returned and `self->dg_hol' may not be updated accordingly.
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
		/* Simple case: the specified range lies beyond the end of the last hole.
		 *              In other words: This write doesn't actually fill any holes! */
writeall_return_false:
		memcpy((byte_t *)self->dg_buf + start_offset, data, length);
		return false;
	}
	/* Must delete all holes that are overlapping with the given range.
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
	/* Find the first (or last from the right) hole that
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
ip_routepacket(struct nic_device *__restrict dev,
               void const *__restrict packet_data,
               size_t packet_size) {
	struct iphdr *hdr;
	u16 header_length, total_length, offset;
	assert(packet_size >= 20);
	hdr = (struct iphdr *)packet_data;
	if unlikely(hdr->ip_v != 4) {
		/* Bad IP version. */
		printk(KERN_WARNING "[ip:%s] Bad IP version in header isn't 4, but is %u\n",
		       dev->cd_name, hdr->ip_v);
		return;
	}
	/* Check for simple case: The packet isn't fragmented. */
	offset        = ntohs(hdr->ip_off);
	total_length  = ntohs(hdr->ip_len);
	header_length = hdr->ip_hl * 4;
	if unlikely(header_length < 20) {
		/* Header too small. */
		printk(KERN_WARNING "[ip:%s] IP header length is too small (%I16u < 20)\n",
		       dev->cd_name, header_length);
		return;
	}
	if unlikely(header_length > total_length) {
		/* Header too large. */
		printk(KERN_WARNING "[ip:%s] IP header exceeds datagram size (%I16u > %I16u)\n",
		       dev->cd_name, header_length, total_length);
		return;
	}
	if unlikely(total_length > packet_size) {
		/* total too large. */
		printk(KERN_WARNING "[ip:%s] Payload exceeds packet size (%I16u > %Iu)\n",
		       dev->cd_name, header_length, packet_size);
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
		 *       is also used to set the header of the final datagram! */
		fragment_start   = (offset & IP_OFFMASK) * 8;
		fragment_size    = total_length;
		fragment_payload = (byte_t *)packet_data;
		if (fragment_start != 0) {
			if (fragment_start < 20) {
				/* Only offset=0 fragments are allowed to write the IP header. */
				printk(KERN_WARNING "[ip:%s] Datagram fragment start-offset clips "
				                    "into IP header (start=%I16u,size=%I16u)\n",
				       dev->cd_name, fragment_start, fragment_size);
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
			printk(KERN_WARNING "[ip:%s] Datagram fragment end-offset overflows (start=%I16u,size=%I16u)\n",
			       dev->cd_name, fragment_start, fragment_size);
			return;
		}
		/* Collect all of the information used to identity incoming datagrams. */
		uid.dg_src  = hdr->ip_src;
		uid.dg_did  = hdr->ip_id;
		uid.dg_pro  = hdr->ip_p;
		uid._dg_pad = 0;
		now = realtime();
		/* Complicated case: Fragmented packet.
		 * -> Search for an existing datagram. */
again_lock_datagrams:
		sync_write(&dev->nd_net.n_ipgrams.nid_lock);
		dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
		if (dg) {
			/* Fragment already exists.
			 * Firstly: Check the packet's timeout field (we must ignore packets after they've timed out!). */
			if unlikely(now.tv_sec > dg->dg_tmo) {
				struct iphdr *datagram;
				/* Discard this packet. */
				printk(KERN_WARNING "[ip:%s] Timeout while receiving datagram from "
				                    "%" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8 "\n",
				       dev->cd_name,
				       ((u8 const *)&uid.dg_src.s_addr)[0],
				       ((u8 const *)&uid.dg_src.s_addr)[1],
				       ((u8 const *)&uid.dg_src.s_addr)[2],
				       ((u8 const *)&uid.dg_src.s_addr)[3]);
				datagram = dg->dg_buf; /* Inherit */
				/* Delete the datagram. */
				assert(dg == &dev->nd_net.n_ipgrams.nid_list[i]);
				network_ip_datagrams_delete(&dev->nd_net.n_ipgrams, i);
				sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
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
						printk(KERN_WARNING "[ip:%s] Multiple last fragments in datagram from "
						                    "%" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8 "\n",
						       dev->cd_name,
						       ((u8 const *)&uid.dg_src.s_addr)[0],
						       ((u8 const *)&uid.dg_src.s_addr)[1],
						       ((u8 const *)&uid.dg_src.s_addr)[2],
						       ((u8 const *)&uid.dg_src.s_addr)[3]);
						datagram = dg->dg_buf; /* Inherit */
						/* Delete the datagram. */
						assert(dg == &dev->nd_net.n_ipgrams.nid_list[i]);
						network_ip_datagrams_delete(&dev->nd_net.n_ipgrams, i);
						sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
						kfree(datagram);
						return;
					}
					dg->dg_flg |= IP_DATAGRAM_FLAG_GOTLAST;
				}
do_write_fragment_nogotlast:
				if (ip_datagram_write(dg, fragment_start, fragment_end, fragment_payload, fragment_size))
					goto datagram_complete_and_unlock;
				sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
				return;
			}

			/* The fragment doesn't fit into the already-allocated buffer.
			 * Make sure that the `IP_DATAGRAM_FLAG_GOTLAST' flag hasn't
			 * been set already. */
			if unlikely(dg->dg_flg & IP_DATAGRAM_FLAG_GOTLAST) {
				struct iphdr *datagram;
				/* Discard this packet. */
				printk(KERN_WARNING "[ip:%s] Fragment from %" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8 " at %I16u-%I16u "
				                    "would exceed the last fragment maximum at %I16u\n",
				       dev->cd_name,
				       ((u8 const *)&uid.dg_src.s_addr)[0],
				       ((u8 const *)&uid.dg_src.s_addr)[1],
				       ((u8 const *)&uid.dg_src.s_addr)[2],
				       ((u8 const *)&uid.dg_src.s_addr)[3],
				       fragment_start, fragment_end - 1,
				       dg->dg_len);
				datagram = dg->dg_buf; /* Inherit */
				/* Delete the datagram. */
				assert(dg == &dev->nd_net.n_ipgrams.nid_list[i]);
				network_ip_datagrams_delete(&dev->nd_net.n_ipgrams, i);
				sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
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
					sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
					new_buffer = (struct iphdr *)kmalloc(fragment_end, GFP_NORMAL);
					sync_write(&dev->nd_net.n_ipgrams.nid_lock);
					/* Check to see if anything's changed... */
					dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
					if unlikely(!dg || fragment_end <= dg->dg_len ||
					            (dg->dg_flg & IP_DATAGRAM_FLAG_GOTLAST)) {
						sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
						kfree(new_buffer);
						goto again_lock_datagrams;
					}
					/* Copy already-written fragment data. */
					memcpy(new_buffer, dg->dg_buf, dg->dg_len);
					/* Free the old buffer.
					 * NOTE: Because hole-descriptors use buffer-relative pointer,
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
					 * With this in mind, we don't need to create/update/delete/etc. hole data,
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
					/* Highly unlikely case: The current fragment partially overlaps
					 * with some older fragment such that the new fragment is larger.
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
				sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
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
				sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
				datagram = (struct iphdr *)kmalloc(fragment_end, GFP_NORMAL);
				sync_write(&dev->nd_net.n_ipgrams.nid_lock);
				dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
				if unlikely(dg != NULL) {
					sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
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
						sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
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
						sync_write(&dev->nd_net.n_ipgrams.nid_lock);
						dg = network_ip_datagrams_findentry(&dev->nd_net.n_ipgrams, uid, &i);
						if unlikely(dg != NULL || new_alloc < dev->nd_net.n_ipgrams.nid_alloc) {
							sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
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
			sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
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
			sync_endwrite(&dev->nd_net.n_ipgrams.nid_lock);
			TRY {
				ip_routedatagram(dev, datagram, datagram_len);
			} EXCEPT {
				kfree(datagram);
				RETHROW();
			}
			kfree(datagram);
			return;
		}
	}
}


/* Route an IP datagram after it has been fully re-assembled.
 * NOTE: The following fields of `packet' should be ignored and may contain invalid values:
 *   - packet->ip_len  (use `htons(packet_size)' instead)
 *   - packet->ip_sum  (re-calculate if needed)
 * @param: packet_size: == ntohs(packet->ip_len);
 * @assume(packet_size >= 20); */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
ip_routedatagram(struct nic_device *__restrict dev,
                 struct iphdr const *__restrict packet,
                 u16 packet_size) {
	assert(packet_size >= 20);
	printk(KERN_DEBUG "[ip:%s] Datagram from %u.%u.%u.%u (proto:%I8u):\n%$[hex]\n",
	       dev->cd_name,
	       ((u8 *)&packet->ip_src.s_addr)[0],
	       ((u8 *)&packet->ip_src.s_addr)[1],
	       ((u8 *)&packet->ip_src.s_addr)[2],
	       ((u8 *)&packet->ip_src.s_addr)[3],
	       packet->ip_p, packet_size, packet);
	/* TODO */
}






/* Send a given IP datagram packet `packet'.
 * NOTE: The caller is responsible to ensure that `packet'
 *       still has sufficient head/tail memory to include
 *       ethernet headers.
 * Or in other words, this function assumes that:
 * >> assert(nic_packet_headfree(packet) >= ETH_PACKET_HEADSIZE);
 * >> assert(nic_packet_tailfree(packet) >= ETH_PACKET_TAILSIZE);
 * - Additionally, the caller is responsible to ensure that the
 *   fully initialized IP header (i.e. `struct iphdr') is pointed
 *   to by `packet->np_head' upon entry, as this function will try
 *   to read from that structure in order to figure out addressing
 *   information that are required for filling in information for
 *   underlying network layers.
 * - NOTE: If necessary, this function will also perform the required
 *         ARP network traffic in order to translate the target IP
 *         address pointed to by the IP header of `packet'. */
PUBLIC NOBLOCK NONNULL((1, 2, 3)) void KCALL
ip_senddatagram(struct nic_device *__restrict dev,
                struct nic_packet *__restrict packet,
                struct aio_handle *__restrict aio) {
	struct iphdr *hdr;
	size_t total_packet_size;
	REF struct net_peeraddr *peer;
	assert(nic_packet_headfree(packet) >= ETH_PACKET_HEADSIZE);
#if ETH_PACKET_TAILSIZE != 0
	assert(nic_packet_tailfree(packet) >= ETH_PACKET_TAILSIZE);
#endif /* ETH_PACKET_TAILSIZE != 0 */
	/* Check for simple case: the packet can fit into a single datagram. */
	total_packet_size = nic_packet_size(packet);
	if (total_packet_size > dev->nd_net.n_ipsize) {
		/* Nope! In this case, we can't actually re-use `packet',
		 *       so use a packet descriptor instead, and off-load
		 *       the task to `ip_senddatagram_ex()'. */
		struct nic_packet_desc desc;
		nic_packet_desc_for_packet(&desc, packet);
		ip_senddatagram_ex(dev, &desc, aio);
		return;
	}
	assert(nic_packet_headsize(packet) >= sizeof(struct iphdr));
	hdr  = (struct iphdr *)packet->np_head;
	peer = network_peers_requireip(&dev->nd_net, hdr->ip_dst.s_addr);
	if (peer->npa_flags & NET_PEERADDR_HAVE_MAC) {
		/* Simple case: we already have the MAC for this peer! */
		struct ethhdr *eth;
		eth = nic_packet_tallochead(packet, struct ethhdr);
		memcpy(eth->h_dest, peer->npa_hwmac, ETH_ALEN);
		decref_unlikely(peer);
		memcpy(eth->h_source, dev->nd_addr.na_hwmac, ETH_ALEN);
		eth->h_proto = htons(ETH_P_IP);
		/* Send the packet. */
		nic_device_send(dev, packet, aio);
		return;
	}
	{
		/* Send out an ARP request */
		REF struct nic_packet *areq;
		FINALLY_DECREF_UNLIKELY(peer);
		areq = arp_makemacrequest(dev, peer->npa_ip);
		FINALLY_DECREF_UNLIKELY(areq);
		/* TODO: Use an async-job to wait for the MAC request to complete,
		 *       as well as retry the request a couple of times if necessary
		 *       before eventually filling in all of the missing data from
		 *       the original packet's header, and sending out that packet. */
		(void)dev;
		(void)hdr;
		(void)packet;
		(void)aio;
		/* TODO */
		THROW(E_NOT_IMPLEMENTED_TODO);
	}
}

/* Similar to `ip_senddatagram()', however instead of taking a NIC
 * packet object, this function takes a packet descriptor. With this
 * in mind, this function is more efficient in cases where the caller
 * isn't given a packet object, but rather, is presented with an I/O-
 * vector, or similar.
 * Note however that if you've been given a NIC packet, you should really
 * use the above function instead, since doing so reduces the amount of
 * copying necessary when the datagram can fit into a single fragment. */
PUBLIC NOBLOCK NONNULL((1, 2, 3)) void KCALL
ip_senddatagram_ex(struct nic_device *__restrict dev,
                   struct nic_packet_desc const *__restrict packet,
                   struct aio_handle *__restrict aio) {
	struct iphdr *hdr;
	assert(nic_packet_desc_headsize(packet) >= sizeof(struct iphdr));
	hdr = (struct iphdr *)packet->npd_head;
	(void)dev;
	(void)hdr;
	(void)packet;
	(void)aio;
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_IP_C */
