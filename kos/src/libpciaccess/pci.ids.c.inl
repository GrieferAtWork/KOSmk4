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
#ifndef GUARD_LIBPCIACCESS_PCI_IDS_C_INL
#define GUARD_LIBPCIACCESS_PCI_IDS_C_INL 1
#define _KOS_SOURCE 1

#include "api.h"

/* The kernel doesn't include support for `pci.ids' database lookup! */
#ifndef __KERNEL__
#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <kos/anno.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <dlfcn.h>
#include <inttypes.h>
#include <pciaccess.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libpciaccess/paths.h>

DECL_BEGIN


/* PDI Device name ID. */
typedef uint64_t pci_devnameid_t;
#define PCI_DEVNAMEID_MAKE(vendor, device, subvendor, subdevice) \
	(((uint64_t)(uint16_t)(vendor) << 0) |                       \
	 ((uint64_t)(uint16_t)(device) << 16) |                      \
	 ((uint64_t)(uint16_t)(subvendor) << 32) |                   \
	 ((uint64_t)(uint16_t)(subdevice) << 48))
#define PCI_DEVNAMEID_GETVENDOR(id)     (uint16_t)((id) >> 0)
#define PCI_DEVNAMEID_GETDEVICE(id)     (uint16_t)((id) >> 16)
#define PCI_DEVNAMEID_GETSUBVENDOR(id)  (uint16_t)((id) >> 32)
#define PCI_DEVNAMEID_GETSUBDEVICE(id)  (uint16_t)((id) >> 48)

/************************************************************************/
/* Low-level database cache functions                                   */
/************************************************************************/
struct generic_cache_node {
	LLRBTREE_NODE(generic_cache_node) gcn_node; /* Tree node. */
};

struct vendor_cache_node {
	LLRBTREE_NODE(vendor_cache_node) vcn_node;  /* Tree node. */
	uint16_t                         vcn_id;    /* Vendor ID */
	uint8_t                          vcn_red;   /* Non-zero if this is a red node. */
	COMPILER_FLEXIBLE_ARRAY(char,    vcn_name); /* Vendor Name */
};

struct device_cache_node {
	LLRBTREE_NODE(device_cache_node) dcn_node;  /* Tree node. */
	pci_devnameid_t                  dcn_id;    /* Device ID */
	uint8_t                          dcn_red;   /* Non-zero if this is a red node. */
	COMPILER_FLEXIBLE_ARRAY(char,    dcn_name); /* Device Name */
};

DECL_END

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE_OMIT_INSERT
#define RBTREE_WANT_TRYINSERT
#define RBTREE(name)         device_cache_node_tree_##name
#define RBTREE_T             struct device_cache_node
#define RBTREE_Tkey          pci_devnameid_t
#define RBTREE_GETNODE(self) (self)->dcn_node
#define RBTREE_GETKEY(self)  (self)->dcn_id
#define RBTREE_REDFIELD      dcn_red
#include <hybrid/sequence/rbtree-abi.h>

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE_OMIT_INSERT
#define RBTREE_WANT_TRYINSERT
#define RBTREE(name)         vendor_cache_node_tree_##name
#define RBTREE_T             struct vendor_cache_node
#define RBTREE_Tkey          uint16_t
#define RBTREE_GETNODE(self) (self)->vcn_node
#define RBTREE_GETKEY(self)  (self)->vcn_id
#define RBTREE_REDFIELD      vcn_red
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* Caches PCI vendor/device names. */
PRIVATE LLRBTREE_ROOT(vendor_cache_node) vendor_cache = NULL;
PRIVATE LLRBTREE_ROOT(device_cache_node) device_cache = NULL;
PRIVATE struct atomic_rwlock string_cache_lock = ATOMIC_RWLOCK_INIT;

/* Helper macros for `string_cache_lock' */
#define string_cache_mustreap()   0
#define string_cache_reap()       (void)0
#define _string_cache_reap()      (void)0
#define string_cache_write()      atomic_rwlock_write(&string_cache_lock)
#define string_cache_trywrite()   atomic_rwlock_trywrite(&string_cache_lock)
#define string_cache_endwrite()   (atomic_rwlock_endwrite(&string_cache_lock), string_cache_reap())
#define _string_cache_endwrite()  atomic_rwlock_endwrite(&string_cache_lock)
#define string_cache_read()       atomic_rwlock_read(&string_cache_lock)
#define string_cache_tryread()    atomic_rwlock_tryread(&string_cache_lock)
#define _string_cache_endread()   atomic_rwlock_endread(&string_cache_lock)
#define string_cache_endread()    (void)(atomic_rwlock_endread_ex(&string_cache_lock) && (string_cache_reap(), 0))
#define _string_cache_end()       atomic_rwlock_end(&string_cache_lock)
#define string_cache_end()        (void)(atomic_rwlock_end_ex(&string_cache_lock) && (string_cache_reap(), 0))
#define string_cache_upgrade()    atomic_rwlock_upgrade(&string_cache_lock)
#define string_cache_tryupgrade() atomic_rwlock_tryupgrade(&string_cache_lock)
#define string_cache_downgrade()  atomic_rwlock_downgrade(&string_cache_lock)
#define string_cache_reading()    atomic_rwlock_reading(&string_cache_lock)
#define string_cache_writing()    atomic_rwlock_writing(&string_cache_lock)
#define string_cache_canread()    atomic_rwlock_canread(&string_cache_lock)
#define string_cache_canwrite()   atomic_rwlock_canwrite(&string_cache_lock)
#define string_cache_waitread()   atomic_rwlock_waitread(&string_cache_lock)
#define string_cache_waitwrite()  atomic_rwlock_waitwrite(&string_cache_lock)



PRIVATE ATTR_PURE char *
NOTHROW(CC find_vendor_name)(uint16_t vendor_id) {
	struct vendor_cache_node *node;
	string_cache_read();
	node = vendor_cache_node_tree_locate(vendor_cache, vendor_id);
	string_cache_endread();
	if (node)
		return node->vcn_name;
	return NULL;
}

PRIVATE ATTR_PURE char *
NOTHROW(CC find_device_name)(pci_devnameid_t id) {
	struct device_cache_node *node;
	string_cache_read();
	node = device_cache_node_tree_locate(device_cache, id);
	string_cache_endread();
	if (node)
		return node->dcn_name;
	return NULL;
}

PRIVATE NONNULL((2)) char *
NOTHROW(CC remember_vendor_name)(uint16_t vendor_id, char const *name) {
	size_t namelen = strlen(name);
	struct vendor_cache_node *node;
	node = (struct vendor_cache_node *)malloc(offsetof(struct vendor_cache_node, vcn_name) +
	                                          (namelen + 1) * sizeof(char));
	if unlikely(!node)
		return NULL;
	memcpy(node->vcn_name, name, namelen + 1, sizeof(char));
	node->vcn_id = vendor_id;
	string_cache_write();
	if unlikely(!vendor_cache_node_tree_tryinsert(&vendor_cache, node)) {
		struct vendor_cache_node *real_node;
		real_node = vendor_cache_node_tree_locate(vendor_cache, vendor_id);
		assert(real_node);
		string_cache_endwrite();
		free(node);
		return real_node->vcn_name;
	}
	string_cache_endwrite();
	return node->vcn_name;
}

PRIVATE NONNULL((2)) char *
NOTHROW(CC remember_device_name)(pci_devnameid_t id, char const *name) {
	size_t namelen = strlen(name);
	struct device_cache_node *node;
	node = (struct device_cache_node *)malloc(offsetof(struct device_cache_node, dcn_name) +
	                                          (namelen + 1) * sizeof(char));
	if unlikely(!node)
		return NULL;
	memcpy(node->dcn_name, name, namelen + 1, sizeof(char));
	node->dcn_id = id;
	string_cache_write();
	if unlikely(!device_cache_node_tree_tryinsert(&device_cache, node)) {
		struct device_cache_node *real_node;
		real_node = device_cache_node_tree_locate(device_cache, id);
		assert(real_node);
		string_cache_endwrite();
		free(node);
		return real_node->dcn_name;
	}
	string_cache_endwrite();
	return node->dcn_name;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC generic_cache_node_destroy_r)(struct generic_cache_node *__restrict self) {
	struct generic_cache_node *lhs, *rhs;
again:
	lhs = self->gcn_node.rb_lhs;
	rhs = self->gcn_node.rb_rhs;
	free(self);
	if (lhs) {
		if (rhs)
			generic_cache_node_destroy_r(rhs);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}

/* Cleanup all items form the vendor/device name cache. */
PRIVATE NOBLOCK void NOTHROW(CC fini_name_cache)(void) {
	if (vendor_cache)
		generic_cache_node_destroy_r((struct generic_cache_node *)vendor_cache);
	if (device_cache)
		generic_cache_node_destroy_r((struct generic_cache_node *)device_cache);
}
/************************************************************************/




#ifndef __pci_device_slist_defined
#define __pci_device_slist_defined
SLIST_HEAD(pci_device_slist, pci_device);
#endif /* !__pci_device_slist_defined */

#ifndef __libpci_devices_defined
#define __libpci_devices_defined
/* [0..n][const] List of PCI devices. (random order) */
INTDEF struct pci_device_slist libpci_devices;
#endif /* !__libpci_devices_defined */



typedef void *gzFile;
typedef gzFile (*PGZOPEN)(const char *filename, const char *mode);
typedef int (*PGZCLOSE)(gzFile file);
typedef char *(*PGZGETS)(gzFile file, char *buf, int len);

PRIVATE void *pdyn_libz       = NULL;
PRIVATE PGZOPEN pdyn_gzopen   = NULL;
PRIVATE PGZCLOSE pdyn_gzclose = NULL;
PRIVATE PGZGETS pdyn_gzgets   = NULL;
#define gzopen  (*pdyn_gzopen)
#define gzclose (*pdyn_gzclose)
#define gzgets  (*pdyn_gzgets)

PRIVATE char *fallback_gzgets(gzFile file, char *buf, int len) {
	return fgets(buf, (size_t)(unsigned int)len, (FILE *)file);
}

/* Library finalizer (linked by `-Wl,-fini=libpci_fini') */
INTERN NOBLOCK void libpci_fini(void) {
	fini_name_cache();
	if (pdyn_libz)
		dlclose(pdyn_libz);
}


/* Make sure that the above function prototypes have been loaded. */
#define load_libz() (pdyn_gzopen || (_load_libz(), 1))
PRIVATE void NOTHROW(CC _load_libz)(void) {
	void *libz = dlopen("libz.so", RTLD_LOCAL);
	if (libz) {
		PGZOPEN libz_gzopen;
		PGZCLOSE libz_gzclose;
		PGZGETS libz_gzgets;
		*(void **)&libz_gzopen  = dlsym(libz, "gzopen");
		*(void **)&libz_gzclose = dlsym(libz, "gzclose");
		*(void **)&libz_gzgets  = dlsym(libz, "gzgets");
		if (libz_gzopen && libz_gzclose && libz_gzgets) {
			pdyn_libz    = libz;
			pdyn_gzclose = libz_gzclose;
			pdyn_gzgets  = libz_gzgets;
			COMPILER_WRITE_BARRIER();
			pdyn_gzopen  = libz_gzopen;
			COMPILER_WRITE_BARRIER();
			return;
		}
		dlclose(libz);
	}
	pdyn_gzclose = (PGZCLOSE)&fclose;
	pdyn_gzgets  = &fallback_gzgets;
	COMPILER_WRITE_BARRIER();
	pdyn_gzopen  = (PGZOPEN)&fopen;
}

PRIVATE gzFile NOTHROW(CC pci_ids_open)(void) {
	gzFile result;
	load_libz();
	result = NULL;
	/* Only attempt to open the compressed database if libz was loaded. */
	if (pdyn_libz != NULL)
		result = gzopen(_PATH_PCI_IDS_GZ, "rb");
	/* Always fall back to loading the uncompressed database. */
	if (!result)
		result = gzopen(_PATH_PCI_IDS, "rb");
	return result;
}


struct pci_ids_parser {
	gzFile   pip_file;      /* [1..1][owned] File handle. */
	union {
		pci_devnameid_t pip_devnameid;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		struct {
			uint16_t pip_vendor;    /* The current vendor ID. */
			uint16_t pip_device;    /* The current device ID. (or PCI_MATCH_ANY for vendor names) */
			uint16_t pip_subvendor; /* The current sub-vendor ID. (or PCI_MATCH_ANY) */
			uint16_t pip_subdevice; /* The current sub-device ID. (or PCI_MATCH_ANY) */
		};
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		struct {
			uint16_t pip_subdevice; /* The current sub-device ID. (or PCI_MATCH_ANY) */
			uint16_t pip_subvendor; /* The current sub-vendor ID. (or PCI_MATCH_ANY) */
			uint16_t pip_device;    /* The current device ID. (or PCI_MATCH_ANY for vendor names) */
			uint16_t pip_vendor;    /* The current vendor ID. */
		};
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	};
	char    *pip_name;      /* Pointer to the associated name */
	char     pip_buf[128];  /* line buffer */
};

PRIVATE NONNULL((1)) bool
NOTHROW(CC pci_ids_parser_init)(struct pci_ids_parser *__restrict self) {
	if ((self->pip_file = pci_ids_open()) == NULL)
		return false;
	self->pip_vendor    = PCI_MATCH_ANY;
	self->pip_device    = PCI_MATCH_ANY;
	self->pip_subvendor = PCI_MATCH_ANY;
	self->pip_subdevice = PCI_MATCH_ANY;
	return true;
}

PRIVATE NONNULL((1)) void
NOTHROW(CC pci_ids_parser_fini)(struct pci_ids_parser *__restrict self) {
	gzclose(self->pip_file);
}

PRIVATE ATTR_CONST WUNUSED uint8_t
NOTHROW(CC decode_hex1)(char ch) {
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	if (ch >= 'a' && ch <= 'z')
		return 10 + ch - 'a';
	return 10 + ch - 'A';
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) uint16_t
NOTHROW(CC decode_hex4)(char const buf[4]) {
	uint16_t result = 0;
	result |= decode_hex1(buf[3]) << 0;
	result |= decode_hex1(buf[2]) << 4;
	result |= decode_hex1(buf[1]) << 8;
	result |= decode_hex1(buf[0]) << 12;
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(CC ishex4)(char const buf[4]) {
	return isxdigit(buf[0]) && isxdigit(buf[1]) &&
	       isxdigit(buf[2]) && isxdigit(buf[3]);
}

/* Read the next line from the database (returning `false' on EOF) */
PRIVATE NONNULL((1)) bool
NOTHROW(CC pci_ids_parser_readline)(struct pci_ids_parser *__restrict self) {
	while (gzgets(self->pip_file, self->pip_buf, sizeof(self->pip_buf)) != NULL) {
		unsigned int tabcount = 0;
		/* Relevant database lines have 1 of 3 formats:
		 * >>0000 foobar
		 * >>	0000 barfoo
		 * >>		0000 0000 bazbaz
		 */
		char *ptr;
		uint16_t id;
		while (tabcount < 3 && self->pip_buf[tabcount] == '\t')
			++tabcount;
		ptr = self->pip_buf + tabcount;
		if (!ishex4(ptr))
			continue;
		id = decode_hex4(ptr);
		ptr += 4;
		if (isspace(*ptr)) {
			do {
				++ptr;
			} while (isspace(*ptr));
		} else {
			if (*ptr != '\0')
				continue;
		}
		self->pip_name = ptr;
		if (tabcount == 0) {
			/* Vendor name. */
			self->pip_vendor    = id;
			self->pip_device    = PCI_MATCH_ANY;
			self->pip_subvendor = PCI_MATCH_ANY;
			self->pip_subdevice = PCI_MATCH_ANY;
		} else if (tabcount == 1) {
			/* Device name. */
			self->pip_device    = id;
			self->pip_subvendor = PCI_MATCH_ANY;
			self->pip_subdevice = PCI_MATCH_ANY;
		} else {
			/* Sub-device name. */
			uint16_t id2;
			if (!ishex4(ptr))
				continue;
			id2 = decode_hex4(ptr);
			ptr += 4;
			if (!isspace(*ptr) /*&& *ptr != '\0'*/)
				continue;
			self->pip_subvendor = id;
			self->pip_subdevice = id2;
			self->pip_name      = ptr;
		}
#if 0
		syslog(LOG_DEBUG, "pci_ids_parser_readline: %#.4x.%#.4x.%#.4x.%#.4x: %q\n",
		       self->pip_vendor,
		       self->pip_device,
		       self->pip_subvendor,
		       self->pip_subdevice,
		       self->pip_name);
#endif
		return true;
	}
	return false;
}


PRIVATE WUNUSED char const *
NOTHROW(CC get_vendor_name)(uint16_t vendor_id) {
	char *result;
	if (vendor_id == PCI_MATCH_ANY)
		return NULL;
	result = find_vendor_name(vendor_id);
	if (!result) {
		/* Search the database. */
		struct pci_ids_parser parser;
		if (pci_ids_parser_init(&parser)) {
			while (pci_ids_parser_readline(&parser)) {
				if (parser.pip_device != PCI_MATCH_ANY)
					continue; /* Not a vendor name... */
				if (parser.pip_vendor != vendor_id)
					continue; /* Some other vendor name... */
				/* Remember this vendor's name. */
				result = remember_vendor_name(vendor_id, strstrip(parser.pip_name));
				break;
			}
			pci_ids_parser_fini(&parser);
		}
		/* Remember that the database doesn't contain this vendor. */
		if (!result)
			result = remember_vendor_name(vendor_id, "");
	}
	if (result && !*result)
		result = NULL;
	return result;
}

PRIVATE WUNUSED char const *
NOTHROW(CC get_device_name)(pci_devnameid_t id) {
	char *result;
	result = find_device_name(id);
	if (!result) {
		/* Search the database. */
		struct pci_ids_parser parser;
		if (pci_ids_parser_init(&parser)) {
			while (pci_ids_parser_readline(&parser)) {
				if (parser.pip_device == PCI_MATCH_ANY)
					continue; /* This is a vendor name... */
				if (parser.pip_devnameid != id)
					continue; /* Some other device... */
				/* Remember this device's name. */
				result = remember_device_name(id, strstrip(parser.pip_name));
				break;
			}
			pci_ids_parser_fini(&parser);
		}
		/* Remember that the database doesn't contain this device. */
		if (!result)
			result = remember_device_name(id, "");
	}
	if (result && !*result)
		result = NULL;
	return result;
}


struct pci_vennameid_list {
	size_t                            pvl_size;  /* # of entries */
	COMPILER_FLEXIBLE_ARRAY(uint16_t, pvl_list); /* [pvl_size] Flexible array of entries */
};

struct pci_devnameid_list {
	size_t                                   pdl_size;  /* # of entries */
	COMPILER_FLEXIBLE_ARRAY(pci_devnameid_t, pdl_list); /* [pdl_size] Flexible array of entries */
};

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(CC pci_vennameid_list_contains)(struct pci_vennameid_list const *__restrict self,
                                        uint16_t id) {
	size_t index;
	BSEARCH (index, self->pvl_list, self->pvl_size, , id) {
		return true;
	}
	return false;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(CC pci_devnameid_list_contains)(struct pci_devnameid_list const *__restrict self,
                                        pci_devnameid_t id) {
	size_t index;
	BSEARCH (index, self->pdl_list, self->pdl_size, , id) {
		return true;
	}
	return false;
}


/* Try to insert the given `id' into the list (no-op if `ip' had already been inserted) */
PRIVATE NONNULL((1)) void
NOTHROW(CC pci_vennameid_list_insert)(struct pci_vennameid_list *__restrict self,
                                      uint16_t id) {
	size_t index;
	BSEARCH (index, self->pvl_list, self->pvl_size, , id) {
		/* Already defined. */
		return;
	}

	/* Insert a new element at `lo' */
	memmoveup(&self->pvl_list[index + 1],
	          &self->pvl_list[index],
	          self->pvl_size - index,
	          sizeof(self->pvl_list[0]));
	self->pvl_list[index] = id;
	++self->pvl_size;
}

/* Try to insert the given `id' into the list (no-op if `ip' had already been inserted) */
PRIVATE NONNULL((1)) void
NOTHROW(CC pci_devnameid_list_insert)(struct pci_devnameid_list *__restrict self,
                                      pci_devnameid_t id) {
	size_t index;
	BSEARCH (index, self->pdl_list, self->pdl_size, , id) {
		/* Already defined. */
		return;
	}

	/* Insert a new element at `lo' */
	memmoveup(&self->pdl_list[index + 1],
	          &self->pdl_list[index],
	          self->pdl_size - index,
	          sizeof(self->pdl_list[0]));
	self->pdl_list[index] = id;
	++self->pdl_size;
}


/* Collect used device and vendor name IDs. */
PRIVATE NONNULL((1, 2)) void
NOTHROW(CC collect_devname_ids)(struct pci_vennameid_list *ven_names,
                                struct pci_devnameid_list *dev_names) {
	struct pci_device *dev;
	SLIST_FOREACH (dev, &libpci_devices, _pd_link) {
		if (dev->pd_vendor_id == PCI_MATCH_ANY)
			continue; /* Ignored... */
		pci_vennameid_list_insert(ven_names, dev->pd_vendor_id);
		if (dev->pd_subvendor_id != PCI_MATCH_ANY)
			pci_vennameid_list_insert(ven_names, dev->pd_subvendor_id);
		pci_devnameid_list_insert(dev_names,
		                          PCI_DEVNAMEID_MAKE(dev->pd_vendor_id,
		                                             dev->pd_device_id,
		                                             PCI_MATCH_ANY,
		                                             PCI_MATCH_ANY));
		pci_devnameid_list_insert(dev_names,
		                          PCI_DEVNAMEID_MAKE(dev->pd_vendor_id,
		                                             dev->pd_device_id,
		                                             dev->pd_subvendor_id,
		                                             dev->pd_subdevice_id));
	}
}

/* Return upper limit estimates for how many vendor/device names are referenced. */
PRIVATE NONNULL((1, 2)) void
NOTHROW(CC get_pci_device_id_max_count)(size_t *__restrict pvendor_count,
                                        size_t *__restrict pdevice_count) {
	struct pci_device *dev;
	*pvendor_count = 0;
	*pdevice_count = 0;
	SLIST_FOREACH (dev, &libpci_devices, _pd_link) {
		if (dev->pd_vendor_id == PCI_MATCH_ANY)
			continue; /* Ignored... */
		++*pvendor_count;
		if (dev->pd_subvendor_id != PCI_MATCH_ANY &&
		    dev->pd_subvendor_id != dev->pd_vendor_id)
			++*pvendor_count;
		++*pdevice_count;
		if (dev->pd_subvendor_id != PCI_MATCH_ANY ||
		    dev->pd_subdevice_id != PCI_MATCH_ANY)
			++*pdevice_count;
	}
}

PRIVATE bool did_preload_system_pci_names = false;
PRIVATE void NOTHROW(CC preload_system_pci_names)(void) {
	struct pci_ids_parser parser;
	struct pci_vennameid_list *vennames;
	struct pci_devnameid_list *devnames;
	size_t vencount, devcount;

	/* Get upper-bound estimates on how many different vendor/device IDs we might need. */
	get_pci_device_id_max_count(&vencount, &devcount);

	/* Allocate buffers for the vendor/device ID lists (these lists will be sorted,
	 * meaning that we can check for relevant IDs in O(log2(N)) while scanning  the
	 * database) */
	vennames = (struct pci_vennameid_list *)alloca(offsetof(struct pci_vennameid_list, pvl_list) +
	                                               (vencount * sizeof(uint16_t)));
	devnames = (struct pci_devnameid_list *)alloca(offsetof(struct pci_devnameid_list, pdl_list) +
	                                               (devcount * sizeof(pci_devnameid_t)));

	/* Initially, both lists are empty. */
	vennames->pvl_size = 0;
	devnames->pdl_size = 0;

	/* Actually collect all of the different vendor/device IDs. */
	collect_devname_ids(vennames, devnames);
	assertf(vennames->pvl_size <= vencount,
	        "vennames->pvl_size = %" PRIuSIZ "\n"
	        "vencount           = %" PRIuSIZ "\n",
	        vennames->pvl_size, vencount);
	assertf(devnames->pdl_size <= devcount,
	        "devnames->pdl_size = %" PRIuSIZ "\n"
	        "devcount           = %" PRIuSIZ "\n",
	        devnames->pdl_size, devcount);

	/* Scan the database for the relevant IDs. */
	if (pci_ids_parser_init(&parser)) {
		while (pci_ids_parser_readline(&parser)) {
			if (parser.pip_device == PCI_MATCH_ANY) {
				/* Vendor name. */
				if (pci_vennameid_list_contains(vennames, parser.pip_vendor))
					remember_vendor_name(parser.pip_vendor, strstrip(parser.pip_name));
			} else {
				/* Device name. */
				if (pci_devnameid_list_contains(devnames, parser.pip_devnameid))
					remember_device_name(parser.pip_devnameid, strstrip(parser.pip_name));
			}
		}
		pci_ids_parser_fini(&parser);
	}

	/* Remember empty strings for all vendor/device names that  weren't
	 * contained in the database. This is still required to ensure that
	 * we won't try to reload the database the first time those strings
	 * will be requested. */
	{
		size_t i;
		for (i = 0; i < vennames->pvl_size; ++i) {
			if (find_vendor_name(vennames->pvl_list[i]) == NULL)
				remember_vendor_name(vennames->pvl_list[i], "");
		}
		for (i = 0; i < devnames->pdl_size; ++i) {
			if (find_device_name(devnames->pdl_list[i]) == NULL)
				remember_device_name(devnames->pdl_list[i], "");
		}
	}

	/* Remember that we've preloaded all system PCI device strings. */
	did_preload_system_pci_names = true;
}



/* Return device names (retrieved from the "pci.ids" database; only available in user-space) */
DEFINE_PUBLIC_ALIAS(pci_device_get_device_name, libpci_device_get_device_name);
INTERN WUNUSED NONNULL((1)) char const *
NOTHROW(CC libpci_device_get_device_name)(struct pci_device const *__restrict self) {
	if (!did_preload_system_pci_names)
		preload_system_pci_names();
	return get_device_name(PCI_DEVNAMEID_MAKE(self->pd_vendor_id,
	                                          self->pd_device_id,
	                                          PCI_MATCH_ANY,
	                                          PCI_MATCH_ANY));
}

DEFINE_PUBLIC_ALIAS(pci_device_get_subdevice_name, libpci_device_get_subdevice_name);
INTERN WUNUSED NONNULL((1)) char const *
NOTHROW(CC libpci_device_get_subdevice_name)(struct pci_device const *__restrict self) {
	if (!did_preload_system_pci_names)
		preload_system_pci_names();
	return get_device_name(PCI_DEVNAMEID_MAKE(self->pd_vendor_id,
	                                          self->pd_device_id,
	                                          self->pd_subvendor_id,
	                                          self->pd_subdevice_id));
}

DEFINE_PUBLIC_ALIAS(pci_device_get_vendor_name, libpci_device_get_vendor_name);
INTERN WUNUSED NONNULL((1)) char const *
NOTHROW(CC libpci_device_get_vendor_name)(struct pci_device const *__restrict self) {
	if (!did_preload_system_pci_names)
		preload_system_pci_names();
	return get_vendor_name(self->pd_vendor_id);
}

DEFINE_PUBLIC_ALIAS(pci_device_get_subvendor_name, libpci_device_get_subvendor_name);
INTERN WUNUSED NONNULL((1)) char const *
NOTHROW(CC libpci_device_get_subvendor_name)(struct pci_device const *__restrict self) {
	if (!did_preload_system_pci_names)
		preload_system_pci_names();
	return get_vendor_name(self->pd_subvendor_id);
}

/* Lookup the device names matching the given description. */
DEFINE_PUBLIC_ALIAS(pci_get_strings, libpci_get_strings);
INTERN NONNULL((1)) void
NOTHROW(CC libpci_get_strings)(/*[1..1]*/ struct pci_id_match const *__restrict match,
                               /*[0..1]*/ char const **pdevice_name,
                               /*[0..1]*/ char const **pvendor_name,
                               /*[0..1]*/ char const **psubdevice_name,
                               /*[0..1]*/ char const **psubvendor_name) {
	if (!did_preload_system_pci_names) {
		bool should_preload = false;
		struct pci_device *iter;
		SLIST_FOREACH (iter, &libpci_devices, _pd_link) {
			if (pvendor_name && (iter->pd_vendor_id == match->pim_vendor_id)) {
				should_preload = true;
				break;
			}
			if (psubvendor_name && (iter->pd_subvendor_id == match->pim_subvendor_id)) {
				should_preload = true;
				break;
			}
			if (pdevice_name &&
			    PCI_ID_COMPARE(iter->pd_vendor_id, match->pim_vendor_id) &&
			    PCI_ID_COMPARE(iter->pd_device_id, match->pim_device_id)) {
				should_preload = true;
				break;
			}
			if (psubdevice_name &&
			    PCI_ID_COMPARE(iter->pd_vendor_id, match->pim_vendor_id) &&
			    PCI_ID_COMPARE(iter->pd_device_id, match->pim_device_id) &&
			    PCI_ID_COMPARE(iter->pd_subvendor_id, match->pim_subvendor_id) &&
			    PCI_ID_COMPARE(iter->pd_subdevice_id, match->pim_subdevice_id)) {
				should_preload = true;
				break;
			}
		}
		if (should_preload)
			preload_system_pci_names();
	}
	if (pdevice_name != NULL) {
		*pdevice_name = get_device_name(PCI_DEVNAMEID_MAKE(match->pim_vendor_id,
		                                                   match->pim_device_id,
		                                                   PCI_MATCH_ANY,
		                                                   PCI_MATCH_ANY));
	}
	if (psubdevice_name != NULL) {
		*psubdevice_name = get_device_name(PCI_DEVNAMEID_MAKE(match->pim_vendor_id,
		                                                      match->pim_device_id,
		                                                      match->pim_subvendor_id,
		                                                      match->pim_subdevice_id));
	}
	if (pvendor_name)
		*pvendor_name = get_vendor_name(match->pim_vendor_id);
	if (psubvendor_name)
		*psubvendor_name = get_vendor_name(match->pim_subvendor_id);
}

DECL_END
#endif /* __KERNEL__ */

#endif /* !GUARD_LIBPCIACCESS_PCI_IDS_C_INL */
