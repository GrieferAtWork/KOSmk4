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
#ifndef _KOS_HOP_PIPE_H
#define _KOS_HOP_PIPE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

#define __OFFSET_HOP_PIPE_STAT_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_STAT_RDTOTAL     8
#define __OFFSET_HOP_PIPE_STAT_AVAIL       16
#define __OFFSET_HOP_PIPE_STAT_BUFCUR      24
#define __OFFSET_HOP_PIPE_STAT_BUFLIM      32
#define __SIZEOF_HOP_PIPE_STAT             40
#ifdef __CC__
struct hop_pipe_stat /*[PREFIX(ps_)]*/ {
	__uint32_t            ps_struct_size;    /* [== sizeof(struct hop_pipe_stat)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __ps_pad1;           /* ... */
	__uint64_t            ps_rdtotal;        /* Total number of bytes read since the pipe buffer was last defragmented (which must be done before it can be re-allocated) */
	__uint64_t            ps_avail;          /* Number of bytes currently available for reading */
	__uint64_t            ps_bufcur;         /* Current buffer size of the pipe */
	__uint64_t            ps_buflim;         /* Max buffer size of the pipe */
};
#endif /* __CC__ */


#define __OFFSET_HOP_PIPE_WRITESOME_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_WRITESOME_BUF         8
#define __OFFSET_HOP_PIPE_WRITESOME_BUFLEN      16
#define __OFFSET_HOP_PIPE_WRITESOME_WRITTEN     24
#define __SIZEOF_HOP_PIPE_WRITESOME             32
#ifdef __CC__
struct hop_pipe_writesome /*[PREFIX(pws_)]*/ {
	__uint32_t            pws_struct_size;   /* [== sizeof(struct hop_pipe_writesome)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __pws_pad1;          /* ... */
	void                 *pws_buf;           /* [IN] Base address of the data to write to the pipe */
	__HOP_PAD_POINTER  (__pws_pad2)          /* ... */
	__size_t              pws_buflen;        /* [IN] Length of the given `pws_buf' (in bytes) */
	__HOP_PAD_POINTER  (__pws_pad3)          /* ... */
	__size_t              pws_written;       /* [OUT] The number of written bytes */
	__HOP_PAD_POINTER  (__pws_pad4)          /* ... */
};
#endif /* __CC__ */


#define __OFFSET_HOP_PIPE_VWRITESOME_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_VWRITESOME_BUF         8
#define __OFFSET_HOP_PIPE_VWRITESOME_BUFCNT      16
#define __OFFSET_HOP_PIPE_VWRITESOME_WRITTEN     24
#define __SIZEOF_HOP_PIPE_VWRITESOME             32
#ifdef __CC__
struct iovec;
struct hop_pipe_vwritesome /*[PREFIX(pvws_)]*/ {
	__uint32_t            pvws_struct_size;  /* [== sizeof(struct hop_pipe_vwritesome)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __pvws_pad1;         /* ... */
	struct iovec const   *pvws_buf;          /* [IN] Vector of buffer locations */
	__HOP_PAD_POINTER  (__pvws_pad2)         /* ... */
	__size_t              pvws_bufcnt;       /* [IN] Number of IO-vectors (count) */
	__HOP_PAD_POINTER  (__pvws_pad3)         /* ... */
	__size_t              pvws_written;      /* [OUT] The number of written bytes */
	__HOP_PAD_POINTER  (__pvws_pad4)         /* ... */
};
#endif /* __CC__ */


#define __OFFSET_HOP_PIPE_SKIPDATA_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_SKIPDATA_NUM_BYTES   8
#define __OFFSET_HOP_PIPE_SKIPDATA_SKIPPED     16
#define __OFFSET_HOP_PIPE_SKIPDATA_RDPOS       24
#define __SIZEOF_HOP_PIPE_SKIPDATA             32
#ifdef __CC__
struct hop_pipe_skipdata /*[PREFIX(psd_)]*/ {
	__uint32_t            psd_struct_size;   /* [== sizeof(struct hop_pipe_skipdata)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __psd_pad1;          /* ... */
	__HOP_SIZE64_FIELD   (psd_num_bytes);    /* [IN] The max number of bytes to skip. */
	__uint64_t            psd_skipped;       /* [OUT] The number of skipped bytes */
	__uint64_t            psd_rdpos;         /* [OUT] The total number of read/skipped bytes since the buffer was last re-sized */
};
#endif /* __CC__ */

#define __OFFSET_HOP_PIPE_UNREAD_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_UNREAD_NUM_BYTES   8
#define __OFFSET_HOP_PIPE_UNREAD_UNREAD      16
#define __OFFSET_HOP_PIPE_UNREAD_RDPOS       24
#define __SIZEOF_HOP_PIPE_UNREAD             32
#ifdef __CC__
struct hop_pipe_unread /*[PREFIX(pur_)]*/ {
	__uint32_t            pur_struct_size;   /* [== sizeof(struct hop_pipe_unread)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __pur_pad1;          /* ... */
	__HOP_SIZE64_FIELD   (pur_num_bytes);    /* [IN] The max number of bytes to unread. */
	__uint64_t            pur_unread;        /* [OUT] The number of unread bytes */
	__uint64_t            pur_rdpos;         /* [OUT] The total number of read/skipped bytes since the buffer was last re-sized */
};
#endif /* __CC__ */

#define __OFFSET_HOP_PIPE_UNWRITE_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_UNWRITE_NUM_BYTES   8
#define __OFFSET_HOP_PIPE_UNWRITE_UNWRITTEN   16
#define __OFFSET_HOP_PIPE_UNWRITE_WRPOS       24
#define __SIZEOF_HOP_PIPE_UNWRITE             32
#ifdef __CC__
struct hop_pipe_unwrite /*[PREFIX(puw_)]*/ {
	__uint32_t            puw_struct_size;   /* [== sizeof(struct hop_pipe_unwrite)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __puw_pad1;          /* ... */
	__HOP_SIZE64_FIELD   (puw_num_bytes);    /* [IN] The max number of bytes to unwrite. */
	__uint64_t            puw_unwritten;     /* [OUT] The number of unwritten bytes */
	__uint64_t            puw_wrpos;         /* [OUT] The total number of written bytes since the buffer was last re-sized */
};
#endif /* __CC__ */






/* For `HANDLE_TYPE_PIPE', `HANDLE_TYPE_PIPE_READER' and `HANDLE_TYPE_PIPE_WRITER' */
#define HOP_PIPE_STAT          0x000c0001 /* [struct hop_pipe_stat *result] Return statistics about the pipe */
#define HOP_PIPE_GETLIM        0x000c0002 /* [uint64_t *result] Return the max allocated size of the pipe. */
#define HOP_PIPE_SETLIM        0x000c0003 /* [size_t value] Set the max allocated pipe size to `value'. */
#define HOP_PIPE_XCHLIM        0x000c0004 /* [uint64_t *value] Exchange the old max allocated pipe size with `*value'. */
#define HOP_PIPE_WRITESOME     0x000c0005 /* [struct hop_pipe_writesome *data] A hybrid between `write()' with and without IO_NONBLOCK:
                                           * write() w/o IO_NONBLOCK: Block until _all_ data was written
                                           * write() w/ IO_NONBLOCK:  Don't block and only write data until the pipe limit is reached
                                           * HOP_PIPE_WRITESOME:      Block until _any_ data was written
                                           *                          NOTE: When this HOP is invoked with the `IO_NONBLOCK' flag,
                                           *                          it  will  behave   identical  to   `write() w/ IO_NONBLOCK' */
#define HOP_PIPE_VWRITESOME    0x000c0006 /* [struct hop_pipe_vwritesome *data] Vectored variant of `HOP_PIPE_WRITESOME' */
#define HOP_PIPE_SKIPDATA      0x000c0007 /* [struct hop_pipe_skipdata *data] Skip buffered data, rather than reading it. */
#define HOP_PIPE_UNREAD        0x000c0008 /* [struct hop_pipe_unread *data] Try to unread previously read, but not yet written data. */
#define HOP_PIPE_UNWRITE       0x000c0009 /* [struct hop_pipe_unwrite *data] Try to unwrite previously written, but not yet read data. */
#define HOP_PIPE_SETWRITTEN    0x000c000a /* [IN:uint64_t *data] Set the total number of written bytes to `*data' (no-op if `*data' is greater than what is currently written, but not read)
                                           * [OUT:uint64_t *data] Return the number of available bytes for reading afterwards. */
#define HOP_PIPE_CLOSE         0x000c000b /* Explicitly   close    the   pipe    (same   as    `HOP_PIPE_SETLIM(0)')
                                           * Internally,  this  is  automatically  done  when  either  last  reader,
                                           * or  the  last writer  object associated  with  some pipe  is destroyed.
                                           * When  a pipe is  closed, no new data  can be written  to it (since it's
                                           * limit is set to 0),  once all remaining data  has been read, read()  on
                                           * the pipe will no longer block, but instead always return 0 immediately.
                                           * A   pipe  can  be   un-closed  by  re-assigning   a  new  limit  value. */
#define HOP_PIPE_OPEN_PIPE     0x000c000c /* [struct hop_openfd *arg] Open the associated `HANDLE_TYPE_PIPE' of a `HANDLE_TYPE_PIPE_READER' or `HANDLE_TYPE_PIPE_WRITER'
                                           * @return: == arg->of_hint */
#define HOP_PIPE_CREATE_READER 0x000c000d /* [struct hop_openfd *arg] Create   a   new   reader   object   for   the   associated    pipe.
                                           * When the pipe(2) system call  is used to create a  new pipe, the internal  `HANDLE_TYPE_PIPE'
                                           * object is hidden from user-space,  and instead is wrapped by  1 reader, and 1 writer  object.
                                           * By using  `HOP_PIPE_CREATE_READER'  and  `HOP_PIPE_CREATE_WRITER',  additional  reader/writer
                                           * objects can be created for a pipe (although pretty much identical behavior can be achieved by
                                           * simply dup(2)-ing the original reader/writer).
                                           * Once either all reader objects have been destroyed, or all writer objects have, the underlying
                                           * pipe   object   is  closed   by   having  its   limit   set  to   0   (s.a.  `HOP_PIPE_CLOSE')
                                           * @return: == arg->of_hint */
#define HOP_PIPE_CREATE_WRITER 0x000c000e /* [struct hop_openfd *arg] Create   a   new   writer   object   for   the   associated    pipe.
                                           * When the pipe(2) system call  is used to create a  new pipe, the internal  `HANDLE_TYPE_PIPE'
                                           * object is hidden from user-space,  and instead is wrapped by  1 reader, and 1 writer  object.
                                           * By using  `HOP_PIPE_CREATE_READER'  and  `HOP_PIPE_CREATE_WRITER',  additional  reader/writer
                                           * objects can be created for a pipe (although pretty much identical behavior can be achieved by
                                           * simply dup(2)-ing the original reader/writer).
                                           * Once either all reader objects have been destroyed, or all writer objects have, the underlying
                                           * pipe   object   is  closed   by   having  its   limit   set  to   0   (s.a.  `HOP_PIPE_CLOSE')
                                           * @return: == arg->of_hint */

__DECL_END

#endif /* !_KOS_HOP_PIPE_H */
