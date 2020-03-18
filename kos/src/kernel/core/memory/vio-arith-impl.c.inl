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

#ifdef __INTELLISENSE__
#include "vio.c"

#define DEFINE_VIO_NAME              xch
#define DEFINE_VIO_OP(oldval, value) value
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#define FUNC3(name, bwlq) vio_##name##bwlq
#define FUNC2(name, bwlq) FUNC3(name, bwlq)
#define FUNC(bwlq)        FUNC2(DEFINE_VIO_NAME, bwlq)

#define COMPONENT3(name) dtv_##name
#define COMPONENT2(name) COMPONENT3(name)
#define COMPONENT        COMPONENT2(DEFINE_VIO_NAME)

PUBLIC NONNULL((1)) u8 KCALL
FUNC(b)(struct vio_args *__restrict args, pos_t addr, u8 value, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	u8 result, new_result;
	if (type->COMPONENT.f_byte)
		return (*type->COMPONENT.f_byte)(args, addr, value, atomic);
	result = vio_readb(args, addr);
	while ((new_result = vio_cmpxch_or_writeb(args, addr, result, DEFINE_VIO_OP(result, value), atomic)) != result)
		result = new_result;
	return new_result;
}

PUBLIC NONNULL((1)) u16 KCALL
FUNC(w)(struct vio_args *__restrict args, pos_t addr, u16 value, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	u16 result, new_result;
	if (type->COMPONENT.f_word && ((uintptr_t)addr & 1) == 0)
		return (*type->COMPONENT.f_word)(args, addr, value, atomic);
	result = vio_readw(args, addr);
	while ((new_result = vio_cmpxch_or_writew(args, addr, result, DEFINE_VIO_OP(result, value), atomic)) != result)
		result = new_result;
	return new_result;
}

PUBLIC NONNULL((1)) u32 KCALL
FUNC(l)(struct vio_args *__restrict args, pos_t addr, u32 value, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	u32 result, new_result;
	if (type->COMPONENT.f_dword && ((uintptr_t)addr & 3) == 0)
		return (*type->COMPONENT.f_dword)(args, addr, value, atomic);
	result = vio_readl(args, addr);
	while ((new_result = vio_cmpxch_or_writel(args, addr, result, DEFINE_VIO_OP(result, value), atomic)) != result)
		result = new_result;
	return new_result;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PUBLIC NONNULL((1)) u64 KCALL
FUNC(q)(struct vio_args *__restrict args, pos_t addr, u64 value, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	u64 result, new_result;
	if (type->COMPONENT.f_qword && ((uintptr_t)addr & 7) == 0)
		return (*type->COMPONENT.f_qword)(args, addr, value, atomic);
	result = vio_readq(args, addr);
	while ((new_result = vio_cmpxch_or_writeq(args, addr, result, DEFINE_VIO_OP(result, value), atomic)) != result)
		result = new_result;
	return new_result;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

#undef DEFINE_VIO_OP
#undef FUNC3
#undef FUNC2
#undef FUNC
#undef COMPONENT3
#undef COMPONENT2
#undef COMPONENT
#undef DEFINE_VIO_NAME

DECL_END

