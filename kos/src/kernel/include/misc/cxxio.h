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
#ifndef GUARD_KERNEL_INCLUDE_MISC_CXXIO_H
#define GUARD_KERNEL_INCLUDE_MISC_CXXIO_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <sys/io.h>

#ifdef __CC__
DECL_BEGIN

#ifndef __cplusplus
#error "C++ I/O is only availble in C++ (obviously)"
#endif

extern "C++" {

template<class T> class io_access;
template<> class io_access<uint8_t> {
public:
	static inline uint8_t in(port_t port) __CXX_NOEXCEPT { return inb(port); }
	static inline void out(port_t port, uint8_t value) __CXX_NOEXCEPT { outb(port,value); }
	static inline uint8_t in_p(port_t port) __CXX_NOEXCEPT { return inb_p(port); }
	static inline void out_p(port_t port, uint8_t value) __CXX_NOEXCEPT { outb_p(port,value); }
};
template<> class io_access<uint16_t> {
public:
	static inline uint16_t in(port_t port) __CXX_NOEXCEPT { return inw(port); }
	static inline void out(port_t port, uint16_t value) __CXX_NOEXCEPT { outw(port,value); }
	static inline uint16_t in_p(port_t port) __CXX_NOEXCEPT { return inw_p(port); }
	static inline void out_p(port_t port, uint16_t value) __CXX_NOEXCEPT { outw_p(port,value); }
};
template<> class io_access<uint32_t> {
public:
	static inline uint32_t in(port_t port) __CXX_NOEXCEPT { return inl(port); }
	static inline void out(port_t port, uint32_t value) __CXX_NOEXCEPT { outl(port,value); }
	static inline uint32_t in_p(port_t port) __CXX_NOEXCEPT { return inl_p(port); }
	static inline void out_p(port_t port, uint32_t value) __CXX_NOEXCEPT { outl_p(port,value); }
};
template<class T> class io {
private:
	typedef io_access<T> ac;
	port_t m_port;
public:
	inline io(port_t port) __CXX_NOEXCEPT: m_port(port) {}
	inline T in() const __CXX_NOEXCEPT { return ac::in(m_port); }
	inline T in_p() const __CXX_NOEXCEPT { return ac::in_p(m_port); }
	inline void out(T value) const __CXX_NOEXCEPT { ac::out(m_port,value); }
	inline void out_p(T value) const __CXX_NOEXCEPT { ac::out_p(m_port,value); }
	inline operator T () const __CXX_NOEXCEPT { return ac::in(m_port); }
	inline io const &operator = (T value) const __CXX_NOEXCEPT { ac::out(m_port,value); return *this; }
	inline io const &operator += (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) + value); return *this; }
	inline io const &operator -= (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) - value); return *this; }
	inline io const &operator *= (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) * value); return *this; }
	inline io const &operator /= (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) / value); return *this; }
	inline io const &operator %= (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) % value); return *this; }
	inline io const &operator <<= (unsigned int shift) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) << shift); return *this; }
	inline io const &operator >>= (unsigned int shift) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) >> shift); return *this; }
	inline io const &operator |= (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) | value); return *this; }
	inline io const &operator &= (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) & value); return *this; }
	inline io const &operator ^= (T value) const __CXX_NOEXCEPT { ac::out(m_port,ac::in(m_port) ^ value); return *this; }
};

typedef io<uint8_t> iob;
typedef io<uint16_t> iow;
typedef io<uint32_t> iol;


}

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_MISC_CXXIO_H */
