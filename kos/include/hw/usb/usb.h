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
#ifndef _HW_USB_USB_H
#define _HW_USB_USB_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <sys/io.h>

__SYSDECL_BEGIN

#define USB_REQUEST_RETYPE_DESTM 0x1f /* Mask for selecting the destination (recipient) */
#define    USB_REQUEST_RETYPE_DEST_DEV  0x00 /* Device destination */
#define    USB_REQUEST_RETYPE_DEST_INTF 0x01 /* Interface destination */
#define    USB_REQUEST_RETYPE_DEST_ENDP 0x02 /* Endpoint destination */
#define    USB_REQUEST_RETYPE_DEST_OTH  0x03 /* Other (???) */
/*         USB_REQUEST_RETYPE_DEST_...  0x1f  * Other values are reserved */
#define USB_REQUEST_RETYPE_TYPEM 0x60 /* Mask for the type of request to perform (command-namespace). */
#define    USB_REQUEST_RETYPE_TYPE_STD  0x00 /* Standard request */
#define    USB_REQUEST_RETYPE_TYPE_CLS  0x20 /* Device-class-specific request */
#define    USB_REQUEST_RETYPE_TYPE_VEN  0x40 /* Vendor-specific request */
/*         USB_REQUEST_RETYPE_TYPE_     0x60  * Reserved */
#define USB_REQUEST_RETYPE_DIRM  0x80 /* Mask for the transfer direction. */
#define    USB_REQUEST_RETYPE_DIR_H2D   0x00 /* Host-to-device (write/out). */
#define    USB_REQUEST_RETYPE_DIR_D2H   0x80 /* Device-to-host (read/in). */

/* Format of `ur_index' for `USB_REQUEST_RETYPE_DEST_INTF' */
#define USB_REQUEST_INTF_INDEX_ID   0x00ff /* Interface number. */

/* Format of `ur_index' for `USB_REQUEST_RETYPE_DEST_ENDP' */
#define USB_REQUEST_ENDP_INDEX_ID   0x000f /* Endpoint number */
#define USB_REQUEST_ENDP_INDEX_DIRM 0x0080 /* Mask for the transfer direction (how is this
                                            * different from  `USB_REQUEST_RETYPE_DIRM'?). */
#define    USB_REQUEST_ENDP_INDEX_DIR_OUT 0x0000 /* Out direction? */
#define    USB_REQUEST_ENDP_INDEX_DIR_IN  0x0080 /* In direction? */



/* Standard (USB_REQUEST_RETYPE_TYPE_STD) USB requests */
#define USB_REQUEST_GET_STATUS        0x00 /* LEN=2 */
#define USB_REQUEST_SET_FEATURE       0x03 /* Set device features. */
#define USB_REQUEST_SET_ADDRESS       0x05 /* Set device address. (new address is `ur_value', but must be <= 127) */
#define USB_REQUEST_GET_DESCRIPTOR    0x06 /* Read the device's descriptor structure
                                            * The `ur_value' field must be one of `USB_REQUEST_GET_DESCRIPTOR_VALUE_*' */
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE                    0x0100 /* `struct usb_descriptor' */
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION             0x0200
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING                    0x0300
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_INTERFACE                 0x0400
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_ENDPOINT                  0x0500
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE_QUALIFIER          0x0600
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_OTHER_SPEED_CONFIGURATION 0x0700
#define    USB_REQUEST_GET_DESCRIPTOR_VALUE_INTERFACE_POWER           0x0800
#define USB_REQUEST_SET_CONFIGURATION 0x09 /* Set  device configuration.  (The conf value  should be taken  from one of
                                            * the entries returned by `USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION',
                                            * and  should appear in the `ur_value' field,  with the upper 8 bits clear) */



/* Flags for `usb_configuration_descriptor::uc_attrib' */
#define USB_CONFIGURATION_ATTRIB_EXTPWR 0x40 /* When set to  1, then  the device runs  on an  external
                                              * power supply. Otherwise, it will run off of bus power. */
#define USB_CONFIGURATION_ATTRIB_ONE    0x80 /* Always 1 */


/* Flags for `usb_endpoint_descriptor::ue_addr' */
#define USB_ENDPOINT_ADDR_INDEX   0x0f /* Endpoint number (0-15) */
#define USB_ENDPOINT_ADDR_IN      0x80 /* Input-only endpoint (when  not set: output-only  endpoint)
                                        * This bit is ignored by control endpoints (aka. endpoint#0) */


/* Flags for `usb_endpoint_descriptor::ue_attrib' */
#define USB_ENDPOINT_ATTRIB_TRANSFERTYPEM  0x03 /* [bit(0:1)] Transfer type */
#define USB_ENDPOINT_ATTRIB_TRANSFERTYPES     0 /* Shift for `USB_ENDPOINT_ATTRIB_TRANSFERTYPEM' */
#define    USB_ENDPOINT_ATTRIB_TRANSFERTYPE_CONTROL     0x00 /* Control transfer */
#define    USB_ENDPOINT_ATTRIB_TRANSFERTYPE_ISOCHRONOUS 0x01 /* Isochronous */
#define    USB_ENDPOINT_ATTRIB_TRANSFERTYPE_BULK        0x02 /* Bulk */
#define    USB_ENDPOINT_ATTRIB_TRANSFERTYPE_INTERRUPT   0x03 /* Interrupt */
#define USB_ENDPOINT_ATTRIB_SYNCTYPEM     0x0c /* [bit(2:3)] Synchronization type (USB_ENDPOINT_ATTRIB_TRANSFERTYPE_ISOCHRONOUS-only) */
#define USB_ENDPOINT_ATTRIB_SYNCTYPES        2 /* Shift for `USB_ENDPOINT_ATTRIB_SYNCTYPEM' */
#define    USB_ENDPOINT_ATTRIB_SYNCTYPE_NONE  0x00 /* No synchronization */
#define    USB_ENDPOINT_ATTRIB_SYNCTYPE_ASYNC 0x04 /* Asynchronous */
#define    USB_ENDPOINT_ATTRIB_SYNCTYPE_ADAPT 0x08 /* Adaptive */
#define    USB_ENDPOINT_ATTRIB_SYNCTYPE_SYNC  0x0c /* Synchronous */
#define USB_ENDPOINT_ATTRIB_USAGETYPEM    0x30 /* [bit(4:5)] Usage Type (USB_ENDPOINT_ATTRIB_TRANSFERTYPE_ISOCHRONOUS-only) */
#define USB_ENDPOINT_ATTRIB_USAGETYPES       4 /* Shift for `USB_ENDPOINT_ATTRIB_USAGETYPEM' */
#define    USB_ENDPOINT_ATTRIB_USAGETYPE_DATA     0x00 /* Data endpoint */
#define    USB_ENDPOINT_ATTRIB_USAGETYPE_FEEDBACK 0x10 /* Feedback endpoint */
#define    USB_ENDPOINT_ATTRIB_USAGETYPE_IMPLFEED 0x20 /* Implicit feedback data endpoint */


#ifdef __CC__
struct __ATTR_PACKED usb_request {
	/* Format of the initial CONTROL packet send to a USB device. */
	__uint8_t  ur_reqtype; /* Request type (Set of `USB_REQUEST_RETYPE_*'). */
	__uint8_t  ur_request; /* The ID of the request (extended by `USB_REQUEST_RETYPE_TYPEM') (One of `USB_REQUEST_*'). */
	__uint16_t ur_value;   /* Potentially optional, request-specific argument (value). */
	__uint16_t ur_index;   /* Potentially optional, request-specific argument (index).
	                        * USB_REQUEST_RETYPE_DEST_INTF: Set of `USB_REQUEST_INTF_INDEX_*'
	                        * USB_REQUEST_RETYPE_DEST_ENDP: Set of `USB_REQUEST_ENDP_INDEX_*' */
	__uint16_t ur_length;  /* USB_REQUEST_RETYPE_DIR_H2D: Exact buffer size of the payload.
	                        * USB_REQUEST_RETYPE_DIR_D2H: Max buffer size of the payload. */
};

struct __ATTR_PACKED usb_device_descriptor {
	/* Structure returned by `USB_REQUEST_GET_DESCRIPTOR:USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE' */
	__uint8_t  ud_size;           /* Size of the descriptor (in bytes) */
	__uint8_t  ud_type;           /* Descriptor type (== `(USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE & 0xff00) >> 8') */
	__uint16_t ud_usbver;         /* USB version (in BCD; e.g. 2.0 is 0x0200) */
	__uint8_t  ud_dev_class;      /* Device class */
	__uint8_t  ud_dev_subclass;   /* Device subclass */
	__uint8_t  ud_dev_protocol;   /* Device protocol */
	__uint8_t  ud_maxpacketsize;  /* The max packet size accepted by this device. */
	__uint16_t ud_vendid;         /* Vendor ID */
	__uint16_t ud_prodid;         /* Product ID */
	__uint16_t ud_devicever;      /* Device version (in BCD; e.g. 2.0 is 0x0200) */
	__uint8_t  ud_str_vendor;     /* Vendor name (index for `USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING') */
	__uint8_t  ud_str_product;    /* Product name (index for `USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING') */
	__uint8_t  ud_str_serial;     /* Serial number name (index for `USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING') */
	__uint8_t  ud_confcount;      /* # of possible configurations. */
};

struct __ATTR_PACKED usb_configuration_descriptor {
	/* Structure returned by `USB_REQUEST_GET_DESCRIPTOR:USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION' */
	__uint8_t  uc_size;           /* Size of the descriptor (in bytes) */
	__uint8_t  uc_type;           /* Descriptor type (== `(USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION & 0xff00) >> 8') */
	__uint16_t uc_total_len;      /* Total length of the descriptor (including trailing data) */
	__uint8_t  uc_num_interfaces; /* Number of interfaces supported in this configuration */
	__uint8_t  uc_conf_value;     /* Value to-be passed to `USB_REQUEST_SET_CONFIGURATION' */
	__uint8_t  uc_conf_name;      /* String index describing the configuration */
	__uint8_t  uc_attrib;         /* Configuration attributes (Set of `USB_CONFIGURATION_ATTRIB_*') */
	__uint8_t  uc_maxpower;       /* Max amount of power draw from the USB bus (in units or 2mA) */
	/* More descriptors may follow here, each one lead by 2 fields:
	 * uint8_t SIZE;
	 * uint8_t TYPE; */
};

struct __ATTR_PACKED usb_interface_descriptor {
	__uint8_t ui_size;            /* Size of the descriptor (in bytes) */
	__uint8_t ui_type;            /* Descriptor type (== `(USB_REQUEST_GET_DESCRIPTOR_VALUE_INTERFACE & 0xff00) >> 8') */
	__uint8_t ui_intf;            /* Interface index. */
	__uint8_t ui_alt_setting;     /* Non-zero if this is an alternate interface for `ui_intf' */
	__uint8_t ui_endp_count;      /* Number of endpoints (excluding endpoint 0) */
	__uint8_t ui_intf_class;      /* Interface class. */
	__uint8_t ui_intf_subclass;   /* Interface subclass. */
	__uint8_t ui_intf_protocol;   /* Interface protocol. */
	__uint8_t ui_intf_str;        /* Interface name (index for `USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING') */
};

struct __ATTR_PACKED usb_endpoint_descriptor {
	__uint8_t  ue_size;           /* Size of the descriptor (in bytes) */
	__uint8_t  ue_type;           /* Descriptor type (== `(USB_REQUEST_GET_DESCRIPTOR_VALUE_ENDPOINT & 0xff00) >> 8') */
	__uint8_t  ue_addr;           /* Endpoint address (Set of `USB_ENDPOINT_ADDR_*') */
	__uint8_t  ue_attrib;         /* Endpoint attributes (Set of `USB_ENDPOINT_ATTRIB_*') */
	__uint16_t ue_maxpacketsize;  /* Max packet size supported by this endpoint. */
	__uint8_t  ue_interval;
};

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_HW_USB_USB_H */
