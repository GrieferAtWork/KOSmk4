/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_RBTREE_C
#define GUARD_APPS_SYSTEM_TEST_TEST_RBTREE_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <hybrid/sequence/rbtree.h>

#include <kos/types.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

DECL_BEGIN

struct mynode {
#ifdef TESTING_LEFT_LEANING
	LLRBTREE_NODE(mynode) n_node;  /* RB-tree node. */
#else /* TESTING_LEFT_LEANING */
	RBTREE_NODE(mynode)   n_node;  /* RB-tree node. */
#endif /* !TESTING_LEFT_LEANING */
	bool                  n_isred; /* Is this node red?. */
	int                   n_key;   /* Node key. */
};

DECL_END

#define RBTREE_DEBUG /* Force-enable internal debug assertions. */
#ifdef TESTING_LEFT_LEANING
#define RBTREE_LEFT_LEANING
#else /* TESTING_LEFT_LEANING */
#define RBTREE_WANT_PREV_NEXT_NODE
#endif /* !TESTING_LEFT_LEANING */
#define RBTREE(name) rb_##name
#define RBTREE_T     struct mynode
#define RBTREE_Tkey  int

#define RBTREE_GETNODE(self) (self)->n_node
#define RBTREE_GETKEY(self)  (self)->n_key
#define RBTREE_REDFIELD      n_isred

#include <hybrid/sequence/rbtree-abi.h>
/**/

#include <stddef.h>
#include <system-test/ctest.h>

DECL_BEGIN

PRIVATE struct mynode *tree = NULL;
PRIVATE struct mynode nodes[10];
PRIVATE int const node_values[10] = { 1, 6, 8, 11, 13, 15, 17, 22, 25, 27 };

PRIVATE void create_node(unsigned int id, int key) {
	nodes[id].n_key = key;
	rb_insert(&tree, &nodes[id]);
}

PRIVATE void create_nodes(unsigned int const order[10]) {
	unsigned int i;
	for (i = 0; i < lengthof(nodes); ++i) {
		unsigned int id = order[i];
		create_node(id, node_values[id]);
	}
	for (i = 0; i < lengthof(nodes); ++i)
		EQp(rb_locate(tree, node_values[i]), &nodes[i]);
#ifndef TESTING_LEFT_LEANING
	for (i = 1; i < lengthof(nodes) - 1; ++i) {
		EQp(rb_prevnode(&nodes[i]), &nodes[i - 1]);
		EQp(rb_nextnode(&nodes[i]), &nodes[i + 1]);
	}
	EQp(rb_prevnode(&nodes[0]), NULL);
	EQp(rb_nextnode(&nodes[lengthof(nodes) - 1]), NULL);
#endif /* !TESTING_LEFT_LEANING */
}

PRIVATE void pop_nodes(unsigned int const order[10]) {
	unsigned int i;
	for (i = 0; i < lengthof(nodes); ++i) {
		unsigned int id = order[i];
		EQp(rb_remove(&tree, node_values[id]), &nodes[id]);
	}
	EQp(tree, NULL);
}

PRIVATE void create_and_pop_nodes(unsigned int const ins_order[10],
                                  unsigned int const pop_order[10]) {
	create_nodes(ins_order);
	pop_nodes(pop_order);
}

PRIVATE void create_and_pop_nodes2(unsigned int const ins_order[10]) {
#define CREATE_AND_POP_WITH_ORDER(...)                       \
	do {                                                     \
		PRIVATE unsigned int const _order[10] = __VA_ARGS__; \
		create_and_pop_nodes(ins_order, _order);             \
	}	__WHILE0
	CREATE_AND_POP_WITH_ORDER({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	CREATE_AND_POP_WITH_ORDER({ 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 });
	CREATE_AND_POP_WITH_ORDER({ 8, 9, 0, 1, 2, 3, 4, 5, 6, 7 });
	CREATE_AND_POP_WITH_ORDER({ 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 });
	CREATE_AND_POP_WITH_ORDER({ 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 });
	CREATE_AND_POP_WITH_ORDER({ 5, 6, 7, 8, 9, 0, 1, 2, 3, 4 });
	CREATE_AND_POP_WITH_ORDER({ 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 });
	CREATE_AND_POP_WITH_ORDER({ 3, 4, 5, 6, 7, 8, 9, 0, 1, 2 });
	CREATE_AND_POP_WITH_ORDER({ 2, 3, 4, 5, 6, 7, 8, 9, 0, 1 });
	CREATE_AND_POP_WITH_ORDER({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 });
/*[[[deemon
import * from random;
local r = Random();
function createRandomOrder() {
	local result = [];
	local pool = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
	while (pool)
		result.append(pool.pop(r.rand32() % #pool));
	return result;
}
for (none: [:64])
	print("	CREATE_AND_POP_WITH_ORDER({ ", ", ".join(createRandomOrder()), " });");
]]]*/
	CREATE_AND_POP_WITH_ORDER({ 4, 8, 0, 7, 2, 5, 9, 3, 6, 1 });
	CREATE_AND_POP_WITH_ORDER({ 3, 9, 5, 1, 8, 4, 7, 2, 0, 6 });
	CREATE_AND_POP_WITH_ORDER({ 5, 9, 4, 0, 6, 8, 7, 1, 2, 3 });
	CREATE_AND_POP_WITH_ORDER({ 2, 7, 4, 0, 9, 1, 3, 6, 8, 5 });
	CREATE_AND_POP_WITH_ORDER({ 9, 5, 6, 4, 8, 0, 2, 7, 1, 3 });
	CREATE_AND_POP_WITH_ORDER({ 7, 0, 3, 4, 8, 1, 9, 6, 5, 2 });
	CREATE_AND_POP_WITH_ORDER({ 6, 9, 2, 7, 4, 5, 3, 1, 8, 0 });
	CREATE_AND_POP_WITH_ORDER({ 3, 8, 7, 4, 1, 6, 2, 0, 5, 9 });
	CREATE_AND_POP_WITH_ORDER({ 3, 1, 9, 0, 2, 8, 4, 6, 7, 5 });
	CREATE_AND_POP_WITH_ORDER({ 1, 8, 6, 2, 5, 4, 7, 3, 0, 9 });
	CREATE_AND_POP_WITH_ORDER({ 7, 2, 5, 0, 4, 6, 8, 9, 1, 3 });
	CREATE_AND_POP_WITH_ORDER({ 2, 0, 4, 8, 9, 3, 6, 5, 1, 7 });
	CREATE_AND_POP_WITH_ORDER({ 8, 1, 6, 5, 2, 9, 3, 7, 0, 4 });
	CREATE_AND_POP_WITH_ORDER({ 0, 8, 5, 2, 1, 9, 6, 3, 7, 4 });
	CREATE_AND_POP_WITH_ORDER({ 5, 2, 3, 6, 4, 0, 7, 1, 9, 8 });
	CREATE_AND_POP_WITH_ORDER({ 5, 4, 7, 0, 6, 1, 9, 2, 8, 3 });
	CREATE_AND_POP_WITH_ORDER({ 8, 1, 0, 3, 7, 6, 2, 5, 4, 9 });
	CREATE_AND_POP_WITH_ORDER({ 8, 3, 5, 9, 6, 7, 4, 2, 1, 0 });
	CREATE_AND_POP_WITH_ORDER({ 6, 2, 0, 8, 4, 7, 3, 9, 5, 1 });
	CREATE_AND_POP_WITH_ORDER({ 8, 9, 5, 2, 1, 7, 6, 3, 0, 4 });
	CREATE_AND_POP_WITH_ORDER({ 6, 4, 2, 9, 3, 8, 0, 1, 5, 7 });
	CREATE_AND_POP_WITH_ORDER({ 3, 7, 9, 1, 5, 6, 4, 0, 8, 2 });
	CREATE_AND_POP_WITH_ORDER({ 2, 8, 9, 6, 3, 1, 0, 5, 7, 4 });
	CREATE_AND_POP_WITH_ORDER({ 5, 8, 3, 2, 6, 4, 7, 1, 9, 0 });
	CREATE_AND_POP_WITH_ORDER({ 2, 6, 4, 5, 1, 8, 7, 9, 3, 0 });
	CREATE_AND_POP_WITH_ORDER({ 8, 0, 7, 1, 5, 3, 9, 6, 4, 2 });
	CREATE_AND_POP_WITH_ORDER({ 3, 4, 9, 8, 2, 1, 6, 0, 7, 5 });
	CREATE_AND_POP_WITH_ORDER({ 0, 1, 6, 9, 2, 4, 3, 8, 7, 5 });
	CREATE_AND_POP_WITH_ORDER({ 6, 1, 7, 0, 5, 4, 9, 2, 8, 3 });
	CREATE_AND_POP_WITH_ORDER({ 9, 5, 2, 8, 1, 4, 7, 6, 0, 3 });
	CREATE_AND_POP_WITH_ORDER({ 0, 2, 5, 9, 4, 3, 8, 7, 1, 6 });
	CREATE_AND_POP_WITH_ORDER({ 8, 5, 3, 0, 9, 2, 1, 6, 7, 4 });
	CREATE_AND_POP_WITH_ORDER({ 3, 7, 8, 1, 9, 5, 6, 2, 0, 4 });
	CREATE_AND_POP_WITH_ORDER({ 7, 0, 3, 1, 6, 9, 4, 8, 5, 2 });
	CREATE_AND_POP_WITH_ORDER({ 3, 9, 1, 7, 2, 6, 8, 5, 4, 0 });
	CREATE_AND_POP_WITH_ORDER({ 1, 6, 7, 4, 2, 5, 3, 8, 9, 0 });
	CREATE_AND_POP_WITH_ORDER({ 1, 9, 2, 4, 8, 6, 5, 3, 7, 0 });
	CREATE_AND_POP_WITH_ORDER({ 5, 4, 9, 7, 2, 8, 3, 0, 6, 1 });
	CREATE_AND_POP_WITH_ORDER({ 1, 7, 5, 0, 9, 6, 3, 2, 4, 8 });
	CREATE_AND_POP_WITH_ORDER({ 6, 7, 9, 0, 4, 5, 8, 3, 1, 2 });
	CREATE_AND_POP_WITH_ORDER({ 8, 5, 1, 0, 4, 7, 6, 2, 9, 3 });
	CREATE_AND_POP_WITH_ORDER({ 9, 2, 3, 1, 4, 8, 6, 0, 5, 7 });
	CREATE_AND_POP_WITH_ORDER({ 6, 2, 5, 7, 3, 9, 0, 1, 8, 4 });
	CREATE_AND_POP_WITH_ORDER({ 2, 0, 6, 1, 5, 4, 8, 3, 7, 9 });
	CREATE_AND_POP_WITH_ORDER({ 2, 0, 5, 1, 4, 8, 6, 9, 3, 7 });
	CREATE_AND_POP_WITH_ORDER({ 9, 3, 6, 1, 2, 0, 8, 7, 5, 4 });
	CREATE_AND_POP_WITH_ORDER({ 9, 8, 7, 3, 0, 2, 5, 4, 6, 1 });
	CREATE_AND_POP_WITH_ORDER({ 4, 9, 5, 7, 1, 0, 6, 8, 3, 2 });
	CREATE_AND_POP_WITH_ORDER({ 3, 1, 5, 7, 6, 4, 9, 8, 0, 2 });
	CREATE_AND_POP_WITH_ORDER({ 9, 4, 6, 3, 5, 2, 8, 1, 7, 0 });
	CREATE_AND_POP_WITH_ORDER({ 6, 8, 1, 0, 7, 3, 5, 2, 4, 9 });
	CREATE_AND_POP_WITH_ORDER({ 6, 7, 3, 2, 9, 0, 4, 8, 5, 1 });
	CREATE_AND_POP_WITH_ORDER({ 4, 3, 0, 9, 2, 6, 7, 8, 5, 1 });
	CREATE_AND_POP_WITH_ORDER({ 2, 5, 1, 7, 0, 6, 9, 8, 4, 3 });
	CREATE_AND_POP_WITH_ORDER({ 7, 4, 6, 8, 3, 1, 5, 2, 9, 0 });
	CREATE_AND_POP_WITH_ORDER({ 2, 4, 1, 7, 8, 0, 3, 6, 9, 5 });
	CREATE_AND_POP_WITH_ORDER({ 7, 5, 4, 2, 0, 3, 9, 8, 1, 6 });
	CREATE_AND_POP_WITH_ORDER({ 1, 8, 9, 2, 0, 4, 3, 7, 5, 6 });
	CREATE_AND_POP_WITH_ORDER({ 4, 3, 6, 9, 1, 0, 5, 8, 2, 7 });
	CREATE_AND_POP_WITH_ORDER({ 2, 8, 9, 1, 3, 4, 7, 0, 6, 5 });
	CREATE_AND_POP_WITH_ORDER({ 9, 3, 5, 1, 8, 6, 7, 2, 4, 0 });
	CREATE_AND_POP_WITH_ORDER({ 6, 4, 2, 9, 3, 5, 8, 7, 0, 1 });
	CREATE_AND_POP_WITH_ORDER({ 4, 6, 3, 8, 7, 5, 2, 9, 1, 0 });
	CREATE_AND_POP_WITH_ORDER({ 9, 3, 0, 7, 4, 5, 1, 2, 8, 6 });
/*[[[end]]]*/

#undef CREATE_AND_POP_WITH_ORDER
}


#ifdef TESTING_LEFT_LEANING
DEFINE_TEST(llrbtree)
#else /* TESTING_LEFT_LEANING */
DEFINE_TEST(rbtree)
#endif /* !TESTING_LEFT_LEANING */
{
#define CREATE_WITH_ORDER_AND_POP(...)                       \
	do {                                                     \
		PRIVATE unsigned int const _order[10] = __VA_ARGS__; \
		create_and_pop_nodes2(_order);                       \
	}	__WHILE0
	CREATE_WITH_ORDER_AND_POP({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	CREATE_WITH_ORDER_AND_POP({ 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 });
	CREATE_WITH_ORDER_AND_POP({ 8, 9, 0, 1, 2, 3, 4, 5, 6, 7 });
	CREATE_WITH_ORDER_AND_POP({ 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 });
	CREATE_WITH_ORDER_AND_POP({ 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 });
	CREATE_WITH_ORDER_AND_POP({ 5, 6, 7, 8, 9, 0, 1, 2, 3, 4 });
	CREATE_WITH_ORDER_AND_POP({ 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 });
	CREATE_WITH_ORDER_AND_POP({ 3, 4, 5, 6, 7, 8, 9, 0, 1, 2 });
	CREATE_WITH_ORDER_AND_POP({ 2, 3, 4, 5, 6, 7, 8, 9, 0, 1 });
	CREATE_WITH_ORDER_AND_POP({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 });
/*[[[deemon
import * from random;
local r = Random();
function createRandomOrder() {
	local result = [];
	local pool = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
	while (pool)
		result.append(pool.pop(r.rand32() % #pool));
	return result;
}
for (none: [:64])
	print("	CREATE_WITH_ORDER_AND_POP({ ", ", ".join(createRandomOrder()), " });");
]]]*/
	CREATE_WITH_ORDER_AND_POP({ 6, 0, 5, 4, 9, 3, 8, 7, 1, 2 });
	CREATE_WITH_ORDER_AND_POP({ 1, 4, 6, 3, 0, 8, 5, 9, 7, 2 });
	CREATE_WITH_ORDER_AND_POP({ 4, 0, 1, 2, 8, 3, 7, 6, 9, 5 });
	CREATE_WITH_ORDER_AND_POP({ 5, 0, 6, 7, 9, 2, 1, 3, 4, 8 });
	CREATE_WITH_ORDER_AND_POP({ 0, 5, 9, 1, 4, 8, 7, 2, 6, 3 });
	CREATE_WITH_ORDER_AND_POP({ 5, 1, 2, 8, 9, 4, 6, 3, 0, 7 });
	CREATE_WITH_ORDER_AND_POP({ 1, 8, 0, 5, 9, 7, 2, 4, 3, 6 });
	CREATE_WITH_ORDER_AND_POP({ 7, 1, 4, 6, 9, 3, 0, 8, 5, 2 });
	CREATE_WITH_ORDER_AND_POP({ 9, 8, 4, 2, 3, 1, 0, 7, 5, 6 });
	CREATE_WITH_ORDER_AND_POP({ 7, 4, 6, 8, 3, 2, 5, 9, 1, 0 });
	CREATE_WITH_ORDER_AND_POP({ 2, 4, 6, 9, 0, 3, 8, 7, 5, 1 });
	CREATE_WITH_ORDER_AND_POP({ 2, 3, 6, 1, 4, 5, 8, 7, 0, 9 });
	CREATE_WITH_ORDER_AND_POP({ 8, 2, 7, 4, 9, 1, 5, 6, 3, 0 });
	CREATE_WITH_ORDER_AND_POP({ 7, 6, 2, 5, 9, 8, 0, 1, 4, 3 });
	CREATE_WITH_ORDER_AND_POP({ 8, 2, 0, 3, 7, 4, 6, 1, 9, 5 });
	CREATE_WITH_ORDER_AND_POP({ 6, 7, 4, 3, 0, 8, 5, 2, 1, 9 });
	CREATE_WITH_ORDER_AND_POP({ 7, 1, 4, 9, 6, 2, 8, 3, 0, 5 });
	CREATE_WITH_ORDER_AND_POP({ 9, 0, 8, 6, 7, 3, 5, 2, 4, 1 });
	CREATE_WITH_ORDER_AND_POP({ 5, 6, 8, 7, 1, 3, 2, 4, 9, 0 });
	CREATE_WITH_ORDER_AND_POP({ 6, 8, 2, 1, 3, 5, 4, 9, 0, 7 });
	CREATE_WITH_ORDER_AND_POP({ 9, 1, 4, 0, 6, 3, 5, 7, 2, 8 });
	CREATE_WITH_ORDER_AND_POP({ 5, 4, 8, 3, 7, 9, 0, 1, 2, 6 });
	CREATE_WITH_ORDER_AND_POP({ 3, 9, 0, 7, 5, 8, 1, 6, 2, 4 });
	CREATE_WITH_ORDER_AND_POP({ 9, 5, 3, 0, 4, 6, 8, 1, 7, 2 });
	CREATE_WITH_ORDER_AND_POP({ 9, 5, 6, 1, 3, 7, 4, 8, 2, 0 });
	CREATE_WITH_ORDER_AND_POP({ 0, 4, 6, 3, 9, 8, 7, 5, 1, 2 });
	CREATE_WITH_ORDER_AND_POP({ 1, 8, 4, 6, 0, 3, 5, 2, 7, 9 });
	CREATE_WITH_ORDER_AND_POP({ 7, 4, 5, 2, 1, 0, 8, 3, 6, 9 });
	CREATE_WITH_ORDER_AND_POP({ 1, 8, 3, 9, 6, 0, 2, 7, 4, 5 });
	CREATE_WITH_ORDER_AND_POP({ 7, 8, 5, 6, 0, 4, 1, 9, 2, 3 });
	CREATE_WITH_ORDER_AND_POP({ 4, 6, 7, 8, 9, 5, 0, 3, 1, 2 });
	CREATE_WITH_ORDER_AND_POP({ 2, 6, 0, 7, 9, 3, 8, 4, 5, 1 });
	CREATE_WITH_ORDER_AND_POP({ 1, 8, 2, 4, 9, 0, 6, 3, 7, 5 });
	CREATE_WITH_ORDER_AND_POP({ 8, 3, 2, 1, 7, 6, 0, 4, 9, 5 });
	CREATE_WITH_ORDER_AND_POP({ 0, 8, 6, 4, 1, 5, 9, 2, 3, 7 });
	CREATE_WITH_ORDER_AND_POP({ 5, 7, 2, 4, 1, 3, 9, 0, 8, 6 });
	CREATE_WITH_ORDER_AND_POP({ 9, 1, 4, 2, 7, 5, 8, 6, 0, 3 });
	CREATE_WITH_ORDER_AND_POP({ 7, 9, 1, 2, 5, 0, 4, 3, 6, 8 });
	CREATE_WITH_ORDER_AND_POP({ 8, 5, 9, 7, 0, 1, 2, 6, 3, 4 });
	CREATE_WITH_ORDER_AND_POP({ 1, 0, 3, 7, 2, 5, 8, 9, 4, 6 });
	CREATE_WITH_ORDER_AND_POP({ 2, 4, 6, 1, 7, 9, 0, 5, 8, 3 });
	CREATE_WITH_ORDER_AND_POP({ 6, 0, 4, 9, 3, 2, 7, 1, 5, 8 });
	CREATE_WITH_ORDER_AND_POP({ 8, 7, 5, 1, 4, 9, 0, 2, 6, 3 });
	CREATE_WITH_ORDER_AND_POP({ 3, 7, 8, 4, 6, 1, 2, 0, 9, 5 });
	CREATE_WITH_ORDER_AND_POP({ 1, 6, 9, 2, 7, 3, 5, 0, 8, 4 });
	CREATE_WITH_ORDER_AND_POP({ 3, 9, 4, 0, 2, 8, 5, 7, 6, 1 });
	CREATE_WITH_ORDER_AND_POP({ 4, 1, 7, 0, 2, 8, 9, 6, 5, 3 });
	CREATE_WITH_ORDER_AND_POP({ 5, 1, 0, 3, 8, 6, 4, 7, 2, 9 });
	CREATE_WITH_ORDER_AND_POP({ 1, 2, 3, 9, 0, 7, 8, 4, 5, 6 });
	CREATE_WITH_ORDER_AND_POP({ 3, 9, 5, 2, 6, 7, 8, 4, 0, 1 });
	CREATE_WITH_ORDER_AND_POP({ 0, 5, 6, 8, 7, 4, 9, 3, 1, 2 });
	CREATE_WITH_ORDER_AND_POP({ 9, 0, 5, 8, 6, 3, 4, 2, 7, 1 });
	CREATE_WITH_ORDER_AND_POP({ 9, 5, 8, 6, 1, 7, 0, 4, 2, 3 });
	CREATE_WITH_ORDER_AND_POP({ 2, 6, 1, 0, 8, 3, 4, 9, 7, 5 });
	CREATE_WITH_ORDER_AND_POP({ 7, 5, 4, 6, 8, 9, 2, 0, 3, 1 });
	CREATE_WITH_ORDER_AND_POP({ 9, 6, 0, 5, 3, 2, 7, 1, 4, 8 });
	CREATE_WITH_ORDER_AND_POP({ 5, 4, 3, 6, 0, 7, 2, 9, 1, 8 });
	CREATE_WITH_ORDER_AND_POP({ 6, 7, 4, 2, 0, 8, 5, 3, 9, 1 });
	CREATE_WITH_ORDER_AND_POP({ 0, 4, 1, 5, 6, 9, 2, 3, 8, 7 });
	CREATE_WITH_ORDER_AND_POP({ 4, 9, 5, 2, 0, 1, 7, 8, 6, 3 });
	CREATE_WITH_ORDER_AND_POP({ 0, 1, 7, 8, 6, 3, 9, 2, 5, 4 });
	CREATE_WITH_ORDER_AND_POP({ 5, 2, 0, 1, 9, 6, 3, 4, 7, 8 });
	CREATE_WITH_ORDER_AND_POP({ 1, 6, 4, 3, 7, 0, 5, 2, 9, 8 });
	CREATE_WITH_ORDER_AND_POP({ 4, 3, 6, 2, 9, 1, 7, 5, 8, 0 });
/*[[[end]]]*/

#undef CREATE_WITH_ORDER_AND_POP
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_RBTREE_C */
