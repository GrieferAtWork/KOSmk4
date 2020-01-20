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


#if 1 || defined(_MSC_VER) || defined(__GNUC__) || \
    defined(__TPP_VERSION__) || defined(__DCC_VERSION__) || \
    defined(__DEEMON__)
#define __PREPROCESSOR_HAVE_CAT     1 /* #define CAT(a, b) a##b */
#define __PREPROCESSOR_HAVE_STR     1 /* #define STR(x) #x */
#define __PREPROCESSOR_HAVE_VA_ARGS 1 /* __VA_ARGS__ */
#endif
#if !defined(__INTELLISENSE__) && \
    (defined(__TPP_VERSION__) || defined(__GNUC__))
#define __PREPROCESSOR_HAVE_INCLUDE_NEXT 1 /* #include_next */
#define __PREPROCESSOR_HAVE_WARNING 1 /* #warning */
#endif


#ifdef __PREPROCESSOR_HAVE_STR
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#   define __PP_PRIVATE_STR(...) #__VA_ARGS__
#   define __PP_STR(...) __PP_PRIVATE_STR(__VA_ARGS__)
#else
#   define __PP_PRIVATE_STR(x) #x
#   define __PP_STR(x) __PP_PRIVATE_STR(x)
#endif
#else /* __PREPROCESSOR_HAVE_STR */
#   define __PP_PRIVATE_STR(x) "x"
#   define __PP_STR(x)         "x"
#endif /* !__PREPROCESSOR_HAVE_STR */

#ifdef __PREPROCESSOR_HAVE_CAT
#   define __PP_PRIVATE_CAT2(a, b)       a##b
#   define __PP_PRIVATE_CAT3(a, b, c)    a##b##c
#   define __PP_PRIVATE_CAT4(a, b, c, d) a##b##c##d
#   define __PP_CAT2(a, b)       __PP_PRIVATE_CAT2(a, b)
#   define __PP_CAT3(a, b, c)    __PP_PRIVATE_CAT3(a, b, c)
#   define __PP_CAT4(a, b, c, d) __PP_PRIVATE_CAT4(a, b, c, d)
#else /* __PREPROCESSOR_HAVE_CAT */
#   define __PP_PRIVATE_CAT2(a,b)     a/**/b
#   define __PP_PRIVATE_CAT3(a,b,c)   a/**/b/**/c
#   define __PP_PRIVATE_CAT4(a,b,c,d) a/**/b/**/c/**/d
#   define __PP_CAT2(a,b)             a/**/b
#   define __PP_CAT3(a,b,c)           a/**/b/**/c
#   define __PP_CAT4(a,b,c,d)         a/**/b/**/c/**/d
#endif /* !__PREPROCESSOR_HAVE_CAT */

#define __PP_PRIVATE_MUL8_0  0
#define __PP_PRIVATE_MUL8_1  8
#define __PP_PRIVATE_MUL8_2  16
#define __PP_PRIVATE_MUL8_4  32
#define __PP_PRIVATE_MUL8_8  64
#ifdef __PREPROCESSOR_HAVE_CAT
#define __PP_PRIVATE_MUL8(x) __PP_PRIVATE_MUL8_##x
#define __PP_MUL8(x)         __PP_PRIVATE_MUL8(x)
#else /* __PREPROCESSOR_HAVE_CAT */
#define __PP_PRIVATE_MUL8(x) __PP_PRIVATE_MUL8_/**/x
#define __PP_MUL8(x)         __PP_PRIVATE_MUL8_/**/x
#endif /* !__PREPROCESSOR_HAVE_CAT */
