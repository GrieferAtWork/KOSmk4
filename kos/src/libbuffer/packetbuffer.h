/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBBUFFER_PACKETBUFFER_H
#define GUARD_LIBBUFFER_PACKETBUFFER_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stdbool.h>

#include <libbuffer/packetbuffer.h>

DECL_BEGIN

/* Begin construction of a new packet to-be appended to `self'
 * NOTES:
 *   - All of the packet's struct fields will have already been filled in by this function.
 *   - It is weakly undefined when a packet that was started before another was committed
 *     will  be  read.   It  may   happen  before,  but   it  may   also  happen   after.
 *   - The  only guaranty in concerns to packet read order is that packets that are
 *     generated linearly by the same thread will always be read in that same order
 *     in relation to each other.
 *   - Similarly, a packet that for which `pb_buffer_endwrite_commit()' was caled before
 *     the  call  to  `pb_buffer_startwrite()' of  another  packet will  always  be read
 *     before that other packet.
 * @return: * : Pointer to the packet's descriptor. Once the caller has finished filling
 *              in the packet's contents, they must use `pb_buffer_endwrite_commit()' in
 *              order to make the packet available for being read.
 *              In case that packet initialization should fail, `pb_buffer_endwrite_abort()'
 *              may  be  called  to  undo  what  was  previously  done  by  this   function.
 *              NOTE: The payload and ancillary data blobs of the packet should be accessed with:
 *                    >> void *pb_packet_payload(struct pb_packet *);
 *                    >> void *pb_packet_ancillary(struct pb_packet *);
 * @return: PB_BUFFER_STARTWRITE_TOOLARGE: [...]
 * @return: PB_BUFFER_STARTWRITE_READSOME: [...]
 * @return: PB_BUFFER_STARTWRITE_BADALLOC: [...] (user-space only)
 * @throw: E_BADALLOC: Failed to allocate more buffer memory (kernel only) */
#ifdef __KERNEL__
INTDEF WUNUSED NONNULL((1)) struct pb_packet *CC
lib_pb_buffer_startwrite(struct pb_buffer *__restrict self,
                         size_t payload_size,
                         size_t ancillary_size)
		THROWS(E_BADALLOC);
#else /* __KERNEL__ */
INTDEF WUNUSED NONNULL((1)) struct pb_packet *
NOTHROW(CC lib_pb_buffer_startwrite)(struct pb_buffer *__restrict self,
                                     size_t payload_size,
                                     size_t ancillary_size);
#endif /* !__KERNEL__ */


/* Abort writing/discard the given `packet' from the packet stream. */
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(CC lib_pb_buffer_endwrite_abort)(struct pb_buffer *__restrict self,
                                         struct pb_packet *__restrict packet);


/* Try to begin reading the next unread packet. If no unread packet exists,
 * or if the next unread packet is already being read at the moment, return
 * NULL without blocking.
 * In this case, the caller may wait for the next readable packet by doing
 * >> while ((packet = pb_buffer_startread(self)) == NULL) {
 * >> #ifdef __KERNEL__
 * >>     task_connect(&self->pb_psta);
 * >>     packet = pb_buffer_startread(self);
 * >>     if (packet) {
 * >>         task_disconnectall();
 * >>         break;
 * >>     }
 * >>     task_waitfor();
 * >> #else
 * >>     lfutex_t status;
 * >>     status = ATOMIC_READ(self->pb_psta);
 * >>     packet = pb_buffer_startread(self);
 * >>     if (packet)
 * >>         break;
 * >>     futex_waitwhile(&self->pb_psta, status);
 * >> #endif
 * >> }
 * Note that with this design, recursive- or parallel read operations
 * aren't allowed (which also wouldn't really make much sense,  since
 * packets are meant to be read in order, alongside the guaranty that
 * any packet will only ever be read once).
 * However, due to things such as VIO,  there is a good chance that  a
 * malicious program  might cause  a recursive  read operation  to  be
 * performed. (i.e. recv(2) is called  with a VIO-buffer, who's  write
 * callbacks  will invoke  recv(2) again).  If this  happens, then the
 * second call to recv(2) will  block indefinitely, and the  malicious
 * program will be soft-locked (but can still be CTRL+C'd, so it's ok)
 *
 * @return: * :   A pointer to a read-handle for the packet that is next-in-line to-be received.
 *                This handle must be released by a call to one of the  pb_buffer_read_[end/...]
 *                functions.
 * @return: NULL: No unread packet is available at the moment, or the most recent packet is
 *                currently being read. */
#ifdef __KERNEL__
INTDEF WUNUSED NONNULL((1)) struct pb_packet *CC
lib_pb_buffer_startread(struct pb_buffer *__restrict self)
		THROWS(E_WOULDBLOCK);
#else /* __KERNEL__ */
INTDEF WUNUSED NONNULL((1)) struct pb_packet *
NOTHROW(CC lib_pb_buffer_startread)(struct pb_buffer *__restrict self);
#endif /* !__KERNEL__ */


/* Truncate the packet from which the  caller is currently reading by  updating
 * its base-pointer, acting as though the first `bytes_to_consume' bytes of the
 * packet weren't actually apart of its payload.
 * This  can be called any number of times, though the caller must always ensure
 * that `bytes_to_consume <= packet->p_payload', and  that the returned  pointer
 * becomes the new handle that must be used for reading from the current packet:
 * >> struct pb_packet *packet;
 * >> packet = pb_buffer_startread(self);
 * >> if (packet) {
 * >>     size_t bytes_consumed;
 * >>     while ((bytes_consumed = PROCESS_PACKET(self)) != 0)
 * >>         packet = pb_buffer_truncate(self, packet, bytes_consumed);
 * >>     if (SHOULD_CONSUME(packet)) {
 * >>         pb_buffer_endread_consume(self, packet);
 * >>     } else {
 * >>         pb_buffer_endread_restore(self, packet);
 * >>     }
 * >> }
 * @return: * : A new handle that should be used for reading packet data. */
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct pb_packet *
NOTHROW(CC lib_pb_buffer_truncate_packet)(struct pb_buffer *__restrict self,
                                          struct pb_packet *__restrict packet,
                                          uint16_t bytes_to_consume);


/* End reading the  current packet, and  discard the packet  from the data  stream.
 * The next call to `pb_buffer_startread()' will return NULL or a different packet. */
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(CC lib_pb_buffer_endread_consume)(struct pb_buffer *__restrict self,
                                          struct pb_packet *__restrict packet);



/* Snapshot-style checks if reading/writing packets is possible right now. */
#ifdef __KERNEL__
INTDEF NOBLOCK WUNUSED NONNULL((1)) bool
(CC lib_pb_buffer_canread)(struct pb_buffer *__restrict self)
		THROWS(E_WOULDBLOCK);
INTDEF NOBLOCK WUNUSED NONNULL((1)) bool
(CC lib_pb_buffer_canwrite)(struct pb_buffer *__restrict self,
                            size_t payload_size,
                            size_t ancillary_size)
		THROWS(E_WOULDBLOCK);
#else /* __KERNEL__ */
INTDEF NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(CC lib_pb_buffer_canread)(struct pb_buffer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(CC lib_pb_buffer_canwrite)(struct pb_buffer *__restrict self,
                                   size_t payload_size,
                                   size_t ancillary_size);
#endif /* !__KERNEL__ */



DECL_END

#endif /* !GUARD_LIBBUFFER_PACKETBUFFER_H */
