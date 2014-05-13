/* File: "gambit.h" */

/*
 * Copyright (c) 1994-2014 by Marc Feeley, All Rights Reserved.
 */

#ifndef ___GAMBIT_H
#define ___GAMBIT_H

#ifndef ___VERSION
#define ___VERSION 407002
#endif

#if ___VERSION != 407002
#include "gambit-not407002.h"
#else

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/*---------------------------------------------------------------------------*/

/*
 * This section determines the following characteristics of the target
 * platform:
 *
 *  - target operating system (WIN32, POSIX, etc)
 *  - target processor type (x86, PowerPC, etc)
 *  - byte order endianness (big-endian or little-endian)
 *  - width of the integer and floating-point types (char, short, int, etc)
 */

/*
 * Determine the target operating system type.  This is used mainly in
 * the implementation of operating system dependent runtime library
 * functions (i.e. lib/os*.c), but also to handle some OS quirks in
 * this include file.
 */

#ifdef _WIN32
#define ___OS_WIN32
#endif


/*
 * Determine the target processor type.  This is used for dynamic code
 * generation (to convert Scheme procedures into C functions) and to
 * determine byte order endianness.
 */

#ifndef ___CPU_x86

#ifdef I386
#define ___CPU_x86
#else
#ifdef _I386
#define ___CPU_x86
#else
#ifdef i386
#define ___CPU_x86
#else
#ifdef _i386
#define ___CPU_x86
#else
#ifdef __i386
#define ___CPU_x86
#else
#ifdef __i386__
#define ___CPU_x86
#else
#ifdef __i486
#define ___CPU_x86
#else
#ifdef __i486__
#define ___CPU_x86
#else
#ifdef __i586
#define ___CPU_x86
#else
#ifdef __i586__
#define ___CPU_x86
#else
#ifdef __i686
#define ___CPU_x86
#else
#ifdef __i686__
#define ___CPU_x86
#else
#ifdef __ix86
#define ___CPU_x86
#else
#ifdef M_I386
#define ___CPU_x86
#else
#ifdef _M_I386
#define ___CPU_x86
#else
#ifdef M_I86
#define ___CPU_x86
#else
#ifdef _M_I86
#define ___CPU_x86
#else
#ifdef _M_IX86
#define ___CPU_x86
#else
#ifdef _X86_
#define ___CPU_x86
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif

#ifndef ___CPU_x86_64

#ifdef __x86_64__
#define ___CPU_x86_64
#else
#ifdef _M_AMD64
#define ___CPU_x86_64
#endif
#endif

#endif

#ifndef ___CPU_ppc

#ifdef PPC
#define ___CPU_ppc
#else
#ifdef ppc
#define ___CPU_ppc
#else
#ifdef __ppc
#define ___CPU_ppc
#else
#ifdef __ppc__
#define ___CPU_ppc
#else
#ifdef _ARCH_PPC
#define ___CPU_ppc
#else
#ifdef __POWERPC__
#define ___CPU_ppc
#else
#ifdef powerpc
#define ___CPU_ppc
#else
#ifdef _POWER
#define ___CPU_ppc
#else
#ifdef _ARCH_PWR
#define ___CPU_ppc
#else
#ifdef _ARCH_PWR2
#define ___CPU_ppc
#else
#ifdef _M_PPC
#define ___CPU_ppc
#else
#ifdef _M_MPPC
#define ___CPU_ppc
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif

#ifndef ___CPU_ppc_64

#ifdef __ppc_64__
#define ___CPU_ppc_64
#endif

#endif

#ifndef ___CPU_sparc

#ifdef SPARC
#define ___CPU_sparc
#else
#ifdef __sparc
#define ___CPU_sparc
#else
#ifdef __sparc__
#define ___CPU_sparc
#else
#ifdef sparc
#define ___CPU_sparc
#else
#ifdef sparc64
#define ___CPU_sparc
#else
#ifdef sparclite
#define ___CPU_sparc
#endif
#endif
#endif
#endif
#endif
#endif

#endif

#ifndef ___CPU_alpha

#ifdef alpha
#define ___CPU_alpha
#else
#ifdef __alpha
#define ___CPU_alpha
#else
#ifdef __alpha__
#define ___CPU_alpha
#else
#ifdef ALPHA
#define ___CPU_alpha
#else
#ifdef _ALPHA_
#define ___CPU_alpha
#else
#ifdef __ALPHA
#define ___CPU_alpha
#else
#ifdef _M_ALPHA
#define ___CPU_alpha
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif

#ifndef ___CPU_mips

#ifdef mips
#define ___CPU_mips
#else
#ifdef _mips
#define ___CPU_mips
#else
#ifdef __mips
#define ___CPU_mips
#else
#ifdef __mips__
#define ___CPU_mips
#else
#ifdef MIPSEB
#define ___CPU_mips
#else
#ifdef _MIPSEB
#define ___CPU_mips
#else
#ifdef __MIPSEB
#define ___CPU_mips
#else
#ifdef __MIPSEB__
#define ___CPU_mips
#else
#ifdef MIPSEL
#define ___CPU_mips
#else
#ifdef _MIPSEL
#define ___CPU_mips
#else
#ifdef __MIPSEL
#define ___CPU_mips
#else
#ifdef __MIPSEL__
#define ___CPU_mips
#else
#ifdef _M_MRX000
#define ___CPU_mips
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif

#ifndef ___CPU_arm

#ifdef arm
#define ___CPU_arm
#else
#ifdef __arm
#define ___CPU_arm
#else
#ifdef __arm__
#define ___CPU_arm
#endif
#endif
#endif

#endif

#ifndef ___CPU_vax

#ifdef vax
#define ___CPU_vax
#else
#ifdef __vax
#define ___CPU_vax
#else
#ifdef __vax__
#define ___CPU_vax
#endif
#endif
#endif

#endif

/*
 * Determine the byte order endianness based on the processor type.
 * We assume that all processors are big-endian, except the x86, x86_64,
 * alpha and vax.  The PowerPC, MIPS and ARM can be either big-endian or
 * little-endian so extra tests are needed.
 */

#ifndef ___BIG_ENDIAN
#ifndef ___LITTLE_ENDIAN

#ifdef ___CPU_x86
#define ___LITTLE_ENDIAN
#endif

#ifdef ___CPU_x86_64
#define ___LITTLE_ENDIAN
#endif

#ifdef ___CPU_ppc
#ifdef _LITTLE_ENDIAN
#define ___LITTLE_ENDIAN
#endif
#ifdef __LITTLE_ENDIAN__
#define ___LITTLE_ENDIAN
#endif
#ifdef __LITTLE_ENDIAN_DATA__
#define ___LITTLE_ENDIAN
#endif
#endif

#ifdef ___CPU_ppc_64
#ifdef _LITTLE_ENDIAN
#define ___LITTLE_ENDIAN
#endif
#ifdef __LITTLE_ENDIAN__
#define ___LITTLE_ENDIAN
#endif
#ifdef __LITTLE_ENDIAN_DATA__
#define ___LITTLE_ENDIAN
#endif
#endif

#ifdef ___CPU_alpha
#define ___LITTLE_ENDIAN
#endif

#ifdef ___CPU_mips
#ifdef _MIPSEL
#define ___LITTLE_ENDIAN
#endif
#endif

#ifdef ___CPU_arm
#ifdef _LITTLE_ENDIAN
#define ___LITTLE_ENDIAN
#endif
#ifdef __LITTLE_ENDIAN__
#define ___LITTLE_ENDIAN
#endif
#ifdef __LITTLE_ENDIAN_DATA__
#define ___LITTLE_ENDIAN
#endif
#ifdef __ARMEL__
#define ___LITTLE_ENDIAN
#endif
#endif

#ifdef ___CPU_vax
#define ___LITTLE_ENDIAN
#endif

#ifdef EMSCRIPTEN
#define ___LITTLE_ENDIAN
#endif

#ifndef ___LITTLE_ENDIAN
#define ___BIG_ENDIAN
#endif

#endif
#endif

/*
 * Determine the number of bits in various integer and floating point
 * types and define appropriate macros accordingly.  The macro for a
 * given type is not defined if the type is not supported by the C
 * compiler or if it is not 8, 16, 32 or 64 bits wide.
 */

#ifndef ___CHAR_WIDTH
#ifdef ___DONT_HAVE_LIMITS_H

/*
 * If the file "limits.h" is not available then the symbol
 * ___DONT_HAVE_LIMITS_H must be defined (for example on the compiler's
 * command line) and the following definitions will be used:
 */

#define ___CHAR_WIDTH     8   /* if needed, edit to suit your platform */
#define ___SHORT_WIDTH    16
#define ___INT_WIDTH      32
#define ___LONG_WIDTH     32

#ifdef __GNUC__
#define ___LONGLONG_WIDTH 64
#endif

#else

/*
 * If the file "limits.h" is available then it contains macros
 * defining the range of the integer types.  The following
 * preprocessor conditional definitions are written so that they will
 * work regardless of the number of bits in the integer types
 * supported by the compiler (many compilers for 32 bit machines give
 * an error for C preprocessor expressions like ULONG_MAX >> 32 or
 * ULLONG_MAX == 18446744073709551615UL).  Some parentheses seem
 * redundant, but they are required for MS Visual C/C++ whose
 * preprocessor signals an error on: x >> 8 >> 8.
 */

#include <limits.h>

#ifdef UCHAR_MAX
#if (UCHAR_MAX & 255) == 255
#if (UCHAR_MAX >> 8) == 0
#define ___CHAR_WIDTH 8
#else
#if ((UCHAR_MAX >> 8) & 255) == 255
#if ((UCHAR_MAX >> 8) >> 8) == 0
#define ___CHAR_WIDTH 16
#else
#if (((UCHAR_MAX >> 8) >> 8) & 255) == 255
#if (((UCHAR_MAX >> 8) >> 8) >> 8) != 0
#if ((((UCHAR_MAX >> 8) >> 8) >> 8) & 255) == 255
#if ((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) == 0
#define ___CHAR_WIDTH 32
#else
#if (((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if (((((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((((UCHAR_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) == 0
#define ___CHAR_WIDTH 64
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef USHRT_MAX
#if (USHRT_MAX & 255) == 255
#if (USHRT_MAX >> 8) == 0
#define ___SHORT_WIDTH 8
#else
#if ((USHRT_MAX >> 8) & 255) == 255
#if ((USHRT_MAX >> 8) >> 8) == 0
#define ___SHORT_WIDTH 16
#else
#if (((USHRT_MAX >> 8) >> 8) & 255) == 255
#if (((USHRT_MAX >> 8) >> 8) >> 8) != 0
#if ((((USHRT_MAX >> 8) >> 8) >> 8) & 255) == 255
#if ((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) == 0
#define ___SHORT_WIDTH 32
#else
#if (((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if (((((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((((USHRT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) == 0
#define ___SHORT_WIDTH 64
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef UINT_MAX
#if (UINT_MAX & 255) == 255
#if (UINT_MAX >> 8) == 0
#define ___INT_WIDTH 8
#else
#if ((UINT_MAX >> 8) & 255) == 255
#if ((UINT_MAX >> 8) >> 8) == 0
#define ___INT_WIDTH 16
#else
#if (((UINT_MAX >> 8) >> 8) & 255) == 255
#if (((UINT_MAX >> 8) >> 8) >> 8) != 0
#if ((((UINT_MAX >> 8) >> 8) >> 8) & 255) == 255
#if ((((UINT_MAX >> 8) >> 8) >> 8) >> 8) == 0
#define ___INT_WIDTH 32
#else
#if (((((UINT_MAX >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((UINT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((UINT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((UINT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if (((((((UINT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((((UINT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((((UINT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((((UINT_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) == 0
#define ___INT_WIDTH 64
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef ULONG_MAX
#if (ULONG_MAX & 255) == 255
#if (ULONG_MAX >> 8) == 0
#define ___LONG_WIDTH 8
#else
#if ((ULONG_MAX >> 8) & 255) == 255
#if ((ULONG_MAX >> 8) >> 8) == 0
#define ___LONG_WIDTH 16
#else
#if (((ULONG_MAX >> 8) >> 8) & 255) == 255
#if (((ULONG_MAX >> 8) >> 8) >> 8) != 0
#if ((((ULONG_MAX >> 8) >> 8) >> 8) & 255) == 255
#if ((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) == 0
#define ___LONG_WIDTH 32
#else
#if (((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if (((((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((((ULONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) == 0
#define ___LONG_WIDTH 64
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef __GNUC__

#define ___LONGLONG_WIDTH 64

#else

/* Handle some non ISO C99 compilers that nevertheless support "long long". */

#ifndef ULLONG_MAX
#ifdef ULONGLONG_MAX
#define ULLONG_MAX ULONGLONG_MAX
#else
#ifdef ULONG_LONG_MAX
#define ULLONG_MAX ULONG_LONG_MAX
#endif
#endif
#endif

#ifdef ULLONG_MAX
#if (ULLONG_MAX & 255) == 255
#if (ULLONG_MAX >> 8) == 0
#define ___LONGLONG_WIDTH 8
#else
#if ((ULLONG_MAX >> 8) & 255) == 255
#if ((ULLONG_MAX >> 8) >> 8) == 0
#define ___LONGLONG_WIDTH 16
#else
#if (((ULLONG_MAX >> 8) >> 8) & 255) == 255
#if (((ULLONG_MAX >> 8) >> 8) >> 8) != 0
#if ((((ULLONG_MAX >> 8) >> 8) >> 8) & 255) == 255
#if ((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) == 0
#define ___LONGLONG_WIDTH 32
#else
#if (((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if (((((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if (((((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) != 0
#if ((((((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) & 255) == 255
#if ((((((((ULLONG_MAX >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) >> 8) == 0
#define ___LONGLONG_WIDTH 64
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif

#endif

/*
 * If the "long long" type is not supported, then substitute the type
 * "long".
 */

#ifndef ___LONGLONG_WIDTH
#define ___LONGLONG_WIDTH ___LONG_WIDTH
#define ___LONGLONG long
#define ___ULONGLONG unsigned long
#else
#define ___LONGLONG long long
#define ___ULONGLONG unsigned long long
#endif

/*
 * Some old C compilers do not support the "signed char" and "wchar_t"
 * types.  The following preprocessor directives allow these types to
 * be redefined (such as on the C compiler's command line, in
 * "config.h", ...).
 */

#ifndef ___SCHAR
#define ___SCHAR signed char
#endif

#ifndef ___WCHAR
#ifdef ___DONT_HAVE_WCHAR_H

/*
 * If the file "wchar.h" is not available then the symbol
 * ___DONT_HAVE_WCHAR_H must be defined (for example on the compiler's
 * command line) and the following definitions will be used:
 */

#define ___WCHAR unsigned char
#define ___WCHAR_MIN 0
#define ___WCHAR_MAX ((1<<___CHAR_WIDTH)-1)

#else

/*
 * If the file "wchar.h" is available then it should contain macros
 * defining the range of the wchar_t type.
 */

#include <wchar.h>

#define ___WCHAR wchar_t

#ifdef WCHAR_MIN
#define ___WCHAR_MIN WCHAR_MIN
#else
#define ___WCHAR_MIN 0
#endif

#ifdef WCHAR_MAX
#define ___WCHAR_MAX WCHAR_MAX
#else
#ifdef UINT_MAX
#define ___WCHAR_MAX UINT_MAX
#else
#define ___WCHAR_MAX ((1<<___CHAR_WIDTH)-1)
#endif
#endif

#endif
#endif

#ifdef ___DONT_HAVE_FLOAT_H

/*
 * If the file "float.h" is not available then the symbol
 * ___DONT_HAVE_FLOAT_H must be defined (for example on the compiler's
 * command line) and the following definitions will be used:
 */

#define ___FLOAT_WIDTH  32   /* if needed, edit to suit your platform */
#define ___DOUBLE_WIDTH 64

#else

/*
 * If the file "float.h" is available then it contains macros defining
 * the range of the floating point types.  The following preprocessor
 * conditional definitions are not completely correct (and may not
 * even compile properly because it is possible that FLT_MAX_EXP and
 * DBL_MAX_EXP are not constant expressions).  However, it appears to
 * work on a wide range of platforms.
 */

#include <float.h>

#ifdef FLT_MAX_EXP
#if FLT_MAX_EXP == 128
#define ___FLOAT_WIDTH 32
#else
#if FLT_MAX_EXP == 1024
#define ___FLOAT_WIDTH 64
#endif
#endif
#endif

#ifdef DBL_MAX_EXP
#if DBL_MAX_EXP == 128
#define ___DOUBLE_WIDTH 32
#else
#if DBL_MAX_EXP == 1024
#define ___DOUBLE_WIDTH 64
#endif
#endif
#endif

#endif
#endif

/*
 * Size of pointers.
 *
 * ___VOIDSTAR_WIDTH must be equal to sizeof(void*) * ___CHAR_WIDTH.
 * This value can't be computed with the "sizeof" operator because it
 * must be known at macro expansion time.  If in doubt just do
 *
 *  #define ___VOIDSTAR_WIDTH ___LONG_WIDTH
 *
 */

#ifndef ___VOIDSTAR_WIDTH
#define ___VOIDSTAR_WIDTH ___LONG_WIDTH
#endif

#if ___VOIDSTAR_WIDTH == 32
#undef ___USE_32_BIT_ADDR
#define ___USE_32_BIT_ADDR
#endif

/*---------------------------------------------------------------------------*/

/*
 * The following symbols must be defined to reflect the integer and
 * floating-point data types supported by the C compiler.  A symbol is
 * only defined if the data type exists.  At least ___F64 and one of
 * the pairs ___S32/___U32 and ___S64/___U64 must be defined.
 *
 *  define ___S8 as the signed integer type of exactly 8 bits
 *  define ___U8 as the unsigned integer type of exactly 8 bits
 *  define ___SM8 as the signed integer type of at least 8 bits
 *  define ___UM8 as the unsigned integer type of at least 8 bits
 *
 *  define ___S16 as the signed integer type of exactly 16 bits
 *  define ___U16 as the unsigned integer type of exactly 16 bits
 *  define ___SM16 as the signed integer type of at least 16 bits
 *  define ___UM16 as the unsigned integer type of at least 16 bits
 *
 *  define ___S32 as the signed integer type of exactly 32 bits
 *  define ___U32 as the unsigned integer type of exactly 32 bits
 *  define ___SM32 as the signed integer type of at least 32 bits
 *  define ___UM32 as the unsigned integer type of at least 32 bits
 *
 *  define ___S64 as the signed integer type of exactly 64 bits
 *  define ___U64 as the unsigned integer type of exactly 64 bits
 *  define ___SM64 as the signed integer type of at least 64 bits
 *  define ___UM64 as the unsigned integer type of at least 64 bits
 *
 *  define ___F32 as the 32 bit floating-point type
 *  define ___F64 as the 64 bit floating-point type
 */

/*
 * First we make sure that the width of all the integer and
 * floating-point types is known.
 */

#ifndef ___CHAR_WIDTH
#error "The definition for ___CHAR_WIDTH is missing"
#endif

#ifndef ___SHORT_WIDTH
#error "The definition for ___SHORT_WIDTH is missing"
#endif

#ifndef ___INT_WIDTH
#error "The definition for ___INT_WIDTH is missing"
#endif

#ifndef ___LONG_WIDTH
#error "The definition for ___LONG_WIDTH is missing"
#endif

#ifndef ___LONGLONG_WIDTH
#error "The definition for ___LONGLONG_WIDTH is missing"
#endif

#ifndef ___FLOAT_WIDTH
#error "The definition for ___FLOAT_WIDTH is missing"
#endif

#ifndef ___DOUBLE_WIDTH
#error "The definition for ___DOUBLE_WIDTH is missing"
#endif

#if ___INT_WIDTH == 8
#define ___S8 int
#define ___U8 unsigned int
#else
#if ___LONG_WIDTH == 8
#define ___S8 long
#define ___U8 unsigned long
#else
#if ___SHORT_WIDTH == 8
#define ___S8 short
#define ___U8 unsigned short
#else
#if ___CHAR_WIDTH == 8
#define ___S8 ___SCHAR
#define ___U8 unsigned char
#else
#if ___LONGLONG_WIDTH == 8
#define ___S8 ___LONGLONG
#define ___U8 unsigned ___LONGLONG
#endif
#endif
#endif
#endif
#endif

#if ___INT_WIDTH == 16
#define ___S16 int
#define ___U16 unsigned int
#else
#if ___LONG_WIDTH == 16
#define ___S16 long
#define ___U16 unsigned long
#else
#if ___SHORT_WIDTH == 16
#define ___S16 short
#define ___U16 unsigned short
#else
#if ___CHAR_WIDTH == 16
#define ___S16 ___SCHAR
#define ___U16 unsigned char
#else
#if ___LONGLONG_WIDTH == 16
#define ___S16 ___LONGLONG
#define ___U16 unsigned ___LONGLONG
#endif
#endif
#endif
#endif
#endif

#if ___INT_WIDTH == 32
#define ___S32 int
#define ___U32 unsigned int
#else
#if ___LONG_WIDTH == 32
#define ___S32 long
#define ___U32 unsigned long
#else
#if ___SHORT_WIDTH == 32
#define ___S32 short
#define ___U32 unsigned short
#else
#if ___CHAR_WIDTH == 32
#define ___S32 ___SCHAR
#define ___U32 unsigned char
#else
#if ___LONGLONG_WIDTH == 32
#define ___S32 ___LONGLONG
#define ___U32 unsigned ___LONGLONG
#endif
#endif
#endif
#endif
#endif

#if ___INT_WIDTH == 64
#define ___S64 int
#define ___U64 unsigned int
#else
#if ___LONG_WIDTH == 64
#define ___S64 long
#define ___U64 unsigned long
#else
#if ___SHORT_WIDTH == 64
#define ___S64 short
#define ___U64 unsigned short
#else
#if ___CHAR_WIDTH == 64
#define ___S64 ___SCHAR
#define ___U64 unsigned char
#else
#if ___LONGLONG_WIDTH == 64
#define ___S64 ___LONGLONG
#define ___U64 unsigned ___LONGLONG
#endif
#endif
#endif
#endif
#endif

#if ___FLOAT_WIDTH == 32
#define ___F32 float
#else
#if ___DOUBLE_WIDTH == 32
#define ___F32 double
#endif
#endif

#if ___DOUBLE_WIDTH == 64
#define ___F64 double
#else
#if ___FLOAT_WIDTH == 64
#define ___F64 float
#endif
#endif

#ifdef ___S64
#define ___BUILTIN_64BIT_INT_TYPE
#define ___SM64 ___S64
#define ___UM64 ___U64
#endif

#ifdef ___S32
#define ___SM32 ___S32
#define ___UM32 ___U32
#else
#define ___SM32 ___SM64
#define ___UM32 ___UM64
#endif

#ifdef ___S16
#define ___SM16 ___S16
#define ___UM16 ___U16
#else
#define ___SM16 ___SM32
#define ___UM16 ___UM32
#endif

#ifdef ___S8
#define ___SM8 ___S8
#define ___UM8 ___U8
#else
#define ___SM8 ___SM16
#define ___UM8 ___UM16
#endif

/*---------------------------------------------------------------------------*/

/* SANITY CHECKS AND SETTING OF DEFAULT OPTIONS */

/*
 * Verify that the byte order endianness is known.
 */

#ifdef ___BIG_ENDIAN
#ifdef ___LITTLE_ENDIAN
#error "Define either ___BIG_ENDIAN or ___LITTLE_ENDIAN"
#endif
#else
#ifndef ___LITTLE_ENDIAN
#error "Define either ___BIG_ENDIAN or ___LITTLE_ENDIAN"
#endif
#endif

/*
 * Generate a single host C procedure or multiple C host
 * procedures (default) per Scheme module?
 */

#ifdef ___SINGLE_HOST
#ifdef ___MULTIPLE_HOSTS
#error "Define either ___SINGLE_HOST or ___MULTIPLE_HOSTS"
#endif
#else
#ifndef ___MULTIPLE_HOSTS
#define ___MULTIPLE_HOSTS
#endif
#endif

/*
 * Compiling for dynamic loading or not (default).
 */

#ifdef ___DYNAMIC
#ifdef ___NONDYNAMIC
#error "Define either ___DYNAMIC or ___NONDYNAMIC"
#endif
#else
#ifndef ___NONDYNAMIC
#define ___NONDYNAMIC
#endif
#endif

/*
 * Define symbols appropriate for dynamic loading.
 */

#ifdef ___DYNAMIC
#undef ___PRIMAL
#define ___PRIMAL
#undef ___LIBRARY
#define ___LIBRARY
#undef ___SHARED
#define ___SHARED
#undef ___BIND_LATE
#define ___BIND_LATE
#endif

/*
 * Compiling to produce a library or an application with a "main" (default
 * unless compiling a flat link file).
 */

#ifdef ___LIBRARY
#ifdef ___APPLICATION
#error "Define either ___LIBRARY or ___APPLICATION"
#endif
#else
#ifndef ___APPLICATION
#ifdef ___FLAT_LINKFILE
#define ___LIBRARY
#else
#define ___APPLICATION
#endif
#endif
#endif

/*
 * Compiling to produce a shared-library or not (default).
 */

#ifdef ___DYNAMIC_LIB
#define ___SHARED
#endif

#ifdef ___SHARED
#ifdef ___NONSHARED
#error "Define either ___SHARED or ___NONSHARED"
#endif
#else
#ifndef ___NONSHARED
#define ___NONSHARED
#endif
#endif

/*
 * Select binding time for global variables, symbols, and keywords.
 * Early binding (default) produces faster code because it directly
 * accesses the resource.  Late binding does an indirection at run
 * time.
 */

#ifdef ___BIND_LATE
#ifdef ___BIND_EARLY
#error "Define either ___BIND_LATE or ___BIND_EARLY"
#endif
#else
#ifndef ___BIND_EARLY
#define ___BIND_EARLY
#endif
#endif

/*
 * Range and size of Scheme characters.
 *
 * ___MAX_CHR must be 0xff, 0xffff or 0x10ffff.  The value 0xff is
 * appropriate when text is limited to the ISO-8859-1 subset of
 * Unicode.  The value 0xffff is for when text is limited to the BMP
 * (Basic Multilingual Plane) subset of Unicode.  The value 0x10ffff
 * allows all Unicode characters in text.  Note that the number of
 * bytes per character in a string depends on ___MAX_CHR as follows:
 *
 *   ___MAX_CHR = 0xff      =>  1 byte per character
 *   ___MAX_CHR = 0xffff    =>  2 bytes per character
 *   ___MAX_CHR = 0x10ffff  =>  4 bytes per character
 *
 * If in doubt just do
 *
 *  #define ___MAX_CHR 0x10ffff
 *
 */

#ifndef ___MAX_CHR
#define ___MAX_CHR 0x10ffff
#endif

/*
 * Number of registers in the virtual machine.  These definitions must
 * agree with those in the file "gsc/_t-c-1.scm".  All Scheme sources
 * must be recompiled if these definitions are changed.
 *
 * ___NB_GVM_REGS = total number of registers available
 *                  3 <= ___NB_GVM_REGS <= 25
 * ___NB_ARG_REGS = maximum number of arguments passed in registers
 *                  1 <= ___NB_ARG_REGS <= min( 12, ___NB_GVM_REGS-2 )
 */

#define ___NB_GVM_REGS 5
#define ___NB_ARG_REGS 3

/*
 * Determine if label values (a gcc extension to C) should be used.
 */

#ifdef ___USE_LABEL_VALUES
#ifdef ___NOT_USE_LABEL_VALUES
#error "Define either ___USE_LABEL_VALUES or ___NOT_USE_LABEL_VALUES"
#endif
#else
#ifndef ___NOT_USE_LABEL_VALUES
#ifdef __GNUC__
#if __llvm__ && !__clang__ && (__GNUC__*1000+__GNUC_MINOR__)<4005
/* Avoid possible LLVM GCC bug with label values */
#define ___NOT_USE_LABEL_VALUES
#else
#define ___USE_LABEL_VALUES
#endif
#else
#define ___NOT_USE_LABEL_VALUES
#endif
#endif
#endif

/*
 * Allow multiple Gambit VM instances or not?
 */

#ifndef ___SINGLE_VM
#ifndef ___MULTIPLE_VMS
#define ___SINGLE_VM
#endif
#endif

#ifdef ___SINGLE_VM
#ifdef ___MULTIPLE_VMS
#error "Define either ___SINGLE_VM or ___MULTIPLE_VMS"
#endif
#endif

/*
 * Are Gambit VM instances single or multiple threaded at the OS
 * level?  In other words, is it allowed for multiple OS threads to be
 * running in a given VM instance?
 */

#ifndef ___SINGLE_THREADED_VMS
#ifndef ___MULTIPLE_THREADED_VMS
#define ___SINGLE_THREADED_VMS
#endif
#endif

#ifdef ___SINGLE_THREADED_VMS
#ifdef ___MULTIPLE_THREADED_VMS
#error "Define either ___SINGLE_THREADED_VMS or ___MULTIPLE_THREADED_VMS"
#endif
#endif

/*
 * Determine which thread system is being used.  This needs to be
 * known by this header file to allow the definition of macros which
 * expand to calls to thread system specific functions, thus avoiding
 * the overhead of a function call (which could be significant for
 * some basic operations such as ___MUTEX_LOCK and ___MUTEX_UNLOCK).
 */

#ifndef ___USE_NO_THREAD_SYSTEM

#ifndef ___USE_POSIX_THREADS
#ifndef ___USE_WIN32_THREADS
#define ___USE_NO_THREAD_SYSTEM
#endif
#endif

#ifdef ___USE_POSIX_THREADS
#ifdef ___USE_WIN32_THREADS
#error "Define either ___USE_POSIX_THREADS or ___USE_WIN32_THREADS"
#endif
#endif

#endif

/*
 * Determine which thread local storage class keyword to use.  The
 * configure script normally determines this because it depends on
 * many factors (the compiler, the version and the OS).  It is
 * normally __thread on gcc and __declspec(thread) on WIN32.
 */

#ifndef ___NO_THREAD_LOCAL_STORAGE_CLASS
#ifndef ___THREAD_LOCAL_STORAGE_CLASS
#define ___NO_THREAD_LOCAL_STORAGE_CLASS
#endif
#endif


/*---------------------------------------------------------------------------*/

/* Dependencies on language (i.e. C++, ANSI-C, and K&R C). */

#ifdef __cplusplus

#define ___P(ansi,kr)ansi
#define ___PVOID ()

#define ___BEGIN_C_LINKAGE extern "C" {
#define ___END_C_LINKAGE }

/*
 * Define ___BOOL as "bool" or "int", according to what is supported
 * by the compiler (this is determined by the configure script) unless
 * it is defined elsewhere.
 */

#ifndef ___BOOL
#define ___BOOL int
#endif

#define ___USE_CPLUSPLUS_NEW_DELETE
#define ___USE_CPLUSPLUS_CLEANUP

#else

#ifdef __STDC__

#define ___P(ansi,kr)ansi
#define ___PVOID (void)

#else

#define ___P(ansi,kr)kr
#define ___PVOID ()

#endif

#define ___BEGIN_C_LINKAGE
#define ___END_C_LINKAGE

#ifndef ___BOOL
#define ___BOOL int
#endif

#undef ___USE_SETJMP
#define ___USE_SETJMP

#endif


#ifdef ___USE_SETJMP

#ifdef ___DONT_HAVE_SETJMP_H

/*
 * If the file "setjmp.h" is not available then the symbol
 * ___DONT_HAVE_SETJMP_H must be defined (for example on the compiler's
 * command line).  In this case we assume that setjmp is defined as
 * a macro.
 */

#undef ___CAN_IMPORT_SETJMP_DYNAMICALLY
#define ___CAN_IMPORT_SETJMP_DYNAMICALLY

#else

/*
 * If the file "setjmp.h" is available then we can use the C
 * preprocessor to check if setjmp is a macro (otherwise it has to be
 * a function).  If it is a macro then we can't get a pointer to it!
 */

#include <setjmp.h>

#ifdef setjmp
#undef ___CAN_IMPORT_SETJMP_DYNAMICALLY
#define ___CAN_IMPORT_SETJMP_DYNAMICALLY
#endif

#endif

#endif


/*---------------------------------------------------------------------------*/

/* C math library properties. */

#ifndef ___DONT_HAVE_MATH_H
#include <math.h>
#endif

#ifdef _MSC_VER

/*
 * Older versions of the Microsoft Visual C compilers did not
 * implement some important math functions.  So we need to define them
 * in the Gambit runtime system.
 */

#define ___DEFINE_SCALBN
#define ___DEFINE_ILOGB
#define ___DEFINE_EXPM1
#define ___DEFINE_LOG1P
#define ___DEFINE_ASINH
#define ___DEFINE_ACOSH
#define ___DEFINE_ATANH

#if _MSC_VER >= 1800

/*
 * Starting with version 18 (released in 2013), the following
 * functions are supported by the C math library.
 */

#define ___HAVE_GOOD_SCALBN
#define ___HAVE_GOOD_ILOGB
#define ___HAVE_GOOD_EXPM1
#define ___HAVE_GOOD_LOG1P
#define ___HAVE_GOOD_ASINH
#define ___HAVE_GOOD_ACOSH
#define ___HAVE_GOOD_ATANH

#endif

/*
 * The following functions seem to be implemented in old versions.
 */

#define ___HAVE_GOOD_SINH
#define ___HAVE_GOOD_COSH
#define ___HAVE_GOOD_TANH

#else

/*
 * On other C compilers, we assume that the following math functions
 * were implemented.
 */

#define ___HAVE_GOOD_SCALBN
#define ___HAVE_GOOD_ILOGB
#define ___HAVE_GOOD_EXPM1
#define ___HAVE_GOOD_LOG1P
#define ___HAVE_GOOD_ASINH
#define ___HAVE_GOOD_ACOSH
#define ___HAVE_GOOD_ATANH
#define ___HAVE_GOOD_SINH
#define ___HAVE_GOOD_COSH
#define ___HAVE_GOOD_TANH

#endif

/*
 * We assume that no C compiler has good implementations of atan2 and
 * pow.  So we need to define them in the Gambit runtime system.
 */

#define ___DEFINE_ATAN2
#define ___DEFINE_POW


/*---------------------------------------------------------------------------*/

/* Visibility directives. */

#ifndef ___HIDDEN
#define ___HIDDEN static
#endif

#ifndef ___LOCAL
#define ___LOCAL static
#endif

#ifdef _MSC_VER
#define ___USE_DECLSPEC
#endif

#ifdef __WATCOMC__
#define ___USE_DECLSPEC
#endif

#ifdef ___USE_DECLSPEC
#define ___EXPORT_FUNC(type,name)__declspec(dllexport) type name
#define ___EXPORT_DATA(type,name)__declspec(dllexport) type name
#define ___IMPORT_FUNC(type,name)__declspec(dllimport) type name
#define ___IMPORT_DATA(type,name)__declspec(dllimport) type name
#endif

#ifndef ___EXPORT_FUNC
#define ___EXPORT_FUNC(type,name)type name
#endif

#ifndef ___EXPORT_DATA
#define ___EXPORT_DATA(type,name)type name
#endif

#ifndef ___IMPORT_FUNC
#define ___IMPORT_FUNC(type,name)extern type name
#endif

#ifndef ___IMPORT_DATA
#define ___IMPORT_DATA(type,name)extern type name
#endif

#define ___EXP_FUNC(type,name)type name
#define ___EXP_DATA(type,name)type name
#define ___IMP_FUNC(type,name)extern type name
#define ___IMP_DATA(type,name)extern type name

#ifdef ___SHARED
#ifdef ___LIBRARY
#undef ___EXP_FUNC
#define ___EXP_FUNC(type,name)___EXPORT_FUNC(type,name)
#undef ___EXP_DATA
#define ___EXP_DATA(type,name)___EXPORT_DATA(type,name)
#endif
#ifndef ___PRIMAL
#undef ___IMP_FUNC
#define ___IMP_FUNC(type,name)___IMPORT_FUNC(type,name)
#undef ___IMP_DATA
#define ___IMP_DATA(type,name)___IMPORT_DATA(type,name)
#endif
#endif

#ifndef ___OS_WIN32
#define ___CAN_IMPORT_EXPORTED
#endif

#ifndef ___CAN_IMPORT_EXPORTED
#ifdef ___SHARED
#ifndef ___PRIMAL
#undef ___BIND_LATE
#define ___BIND_LATE
#endif
#endif
#endif

/*---------------------------------------------------------------------------*/

#ifdef __GNUC__
#if __GNUC__ >= 3
#define ___USE_builtin_expect
#endif
#endif

#ifdef ___USE_builtin_expect
#define ___EXPECT_TRUE(x) __builtin_expect((x),1)
#define ___EXPECT_FALSE(x) __builtin_expect((x),0)
#else
#define ___EXPECT_TRUE(x) (x)
#define ___EXPECT_FALSE(x) (x)
#endif

/*---------------------------------------------------------------------------*/

/*
 * IMPORTANT NOTE
 *
 * As a general principle, the macros are written in such a way that all
 * macros which expand into C expressions yield PRIMARY C expressions.
 * Also, macros assume that arguments are PRIMARY expressions.  A PRIMARY
 * expression is either:
 *
 *   an identifier, or
 *   a non-negative constant, or
 *   a parenthesized expression.
 *
 * This convention avoids many operator priority problems and helps keep
 * the number of parentheses down.  On the other hand, it is easy to
 * introduce errors when modifying these macros so be careful.
 */

/*---------------------------------------------------------------------------*/

/*
 * The "___CAST" macro is useful to easily locate type casts in the
 * source code.  Unfortunately there are still places in the sources
 * that don't use this macro.
 */

#define ___CAST(type,val)((type)(val))

/*
 * Macros to access ___S64 and ___U64 data types.  Note that ___S64
 * and ___U64 are either defined as a macro or as a typedef.
 */

#define ___FETCH_S64(base,i)*(___CAST(___S64*,base)+(i))
#define ___STORE_S64(base,i,val)*(___CAST(___S64*,base)+(i)) = (val)
#define ___FETCH_U64(base,i)*(___CAST(___U64*,base)+(i))
#define ___STORE_U64(base,i,val)*(___CAST(___U64*,base)+(i)) = (val)
#define ___CAST_S64(x)___CAST(___S64,x)
#define ___CAST_U64(x)___CAST(___U64,x)

/*
 * Macros to access ___S32 and ___U32 data types.
 */

#ifdef ___S32

#define ___FETCH_S32(base,i)*(___CAST(___S32*,base)+(i))
#define ___STORE_S32(base,i,val)*(___CAST(___S32*,base)+(i)) = (val)
#define ___FETCH_U32(base,i)*(___CAST(___U32*,base)+(i))
#define ___STORE_U32(base,i,val)*(___CAST(___U32*,base)+(i)) = (val)
#define ___CAST_S32(x)___CAST(___S32,x)
#define ___CAST_U32(x)___CAST(___U32,x)

#else

#define ___FETCH_S32(base,i)___CAST_S32(___FETCH_U32(base,i))
#define ___STORE_S32(base,i,val)___STORE_U32(base,i,___CAST_U32(val))

#ifdef ___BIG_ENDIAN
#define ___FETCH_U32(base,i)(((i)&1) \
? (*(___CAST(___U64*,base)+((i)>>1))&0xffffffff) \
: ((*(___CAST(___U64*,base)+((i)>>1)))>>32))
#define ___STORE_U32(base,i,val)*(___CAST(___U64*,base)+((i)>>1)) = ((i)&1) \
? (*(___CAST(___U64*,base)+((i)>>1))&___CAST_U64(0xffffffff<<32))|(val) \
: (*(___CAST(___U64*,base)+((i)>>1))&0xffffffff)|___CAST_U64((val)<<32)
#else
#define ___FETCH_U32(base,i)(((i)&1) \
? ((*(___CAST(___U64*,base)+((i)>>1)))>>32) \
: (*(___CAST(___U64*,base)+((i)>>1))&0xffffffff))
#define ___STORE_U32(base,i,val)*(___CAST(___U64*,base)+((i)>>1)) = ((i)&1) \
? (*(___CAST(___U64*,base)+((i)>>1))&0xffffffff)|___CAST_U64((val)<<32) \
: (*(___CAST(___U64*,base)+((i)>>1))&___CAST_U64(0xffffffff<<32))|(val)
#endif

#define ___CAST_S32(x)(___CAST_S64((x)<<32)>>32)
#define ___CAST_U32(x)___CAST_U64((x)&0xffffffff)

#endif

/*
 * Macros to access ___S16 and ___U16 data types.
 */

#ifdef ___S16

#define ___FETCH_S16(base,i)*(___CAST(___S16*,base)+(i))
#define ___STORE_S16(base,i,val)*(___CAST(___S16*,base)+(i)) = (val)
#define ___FETCH_U16(base,i)*(___CAST(___U16*,base)+(i))
#define ___STORE_U16(base,i,val)*(___CAST(___U16*,base)+(i)) = (val)
#define ___CAST_S16(x)___CAST(___S16,x)
#define ___CAST_U16(x)___CAST(___U16,x)

#else

#define ___FETCH_S16(base,i)___CAST_S16(___FETCH_U16(base,i))
#define ___STORE_S16(base,i,val)___STORE_U16(base,i,___CAST_U16(val))

#ifdef ___S32

#ifdef ___BIG_ENDIAN
#define ___FETCH_U16(base,i)(((i)&1) \
? (*(___CAST(___U32*,base)+((i)>>1))&0xffff) \
: ((*(___CAST(___U32*,base)+((i)>>1)))>>16))
#define ___STORE_U16(base,i,val)*(___CAST(___U32*,base)+((i)>>1)) = ((i)&1) \
? (*(___CAST(___U32*,base)+((i)>>1))&___CAST_U32(0xffff<<16))|(val) \
: (*(___CAST(___U32*,base)+((i)>>1))&0xffff)|___CAST_U32((val)<<16)
#else
#define ___FETCH_U16(base,i)(((i)&1) \
? ((*(___CAST(___U32*,base)+((i)>>1)))>>16) \
: (*(___CAST(___U32*,base)+((i)>>1))&0xffff))
#define ___STORE_U16(base,i,val)*(___CAST(___U32*,base)+((i)>>1)) = ((i)&1) \
? (*(___CAST(___U32*,base)+((i)>>1))&0xffff)|___CAST_U32((val)<<16) \
: (*(___CAST(___U32*,base)+((i)>>1))&(0xffff<<16))|(___U32)(val)
#endif

#define ___CAST_S16(x)(___CAST_S32((x)<<16)>>16)
#define ___CAST_U16(x)___CAST_U32((x)&0xffff)

#else

#ifdef ___BIG_ENDIAN
#define ___FETCH_S16(base,i)(((i)&1) \
? ((*(___CAST(___S64*,base)+((i)>>1)))>>16) \
: ((*(___CAST(___S64*,base)+((i)>>1))<<16)>>16))
#define ___FETCH_U16(base,i) \
((*(___CAST(___U64*,base)+((i)>>2))>>((~(i)&3)<<4))&0xffff)
#define ___STORE_U16(base,i,val)*(___CAST(___U64*,base)+((i)>>2)) = \
(*(___CAST(___U64*,base)+((i)>>2))&~___CAST_U64(0xffff<<((~(i)&3)<<4))) | \
___CAST_U64((val)<<((~(i)&3)<<4))
#else
#define ___FETCH_U16(base,i) \
((*(___CAST(___U64*,base)+((i)>>2))>>(((i)&3)<<4))&0xffff)
#define ___STORE_U16(base,i,val)*(___CAST(___U64*,base)+((i)>>2)) = \
(*(___CAST(___U64*,base)+((i)>>2))&~___CAST_U64(0xffff<<(((i)&3)<<4))) | \
___CAST_U64((val)<<(((i)&3)<<4))
#endif

#define ___CAST_S16(x)(___CAST_S64((x)<<48)>>48)
#define ___CAST_U16(x)___CAST_U64((x)&0xffff)

#endif

#endif

/*
 * Macros to access ___S8 and ___U8 data types.
 */

#ifdef ___S8

#define ___FETCH_S8(base,i)*(___CAST(___S8*,base)+(i))
#define ___FETCH_U8(base,i)*(___CAST(___U8*,base)+(i))
#define ___STORE_S8(base,i,val)*(___CAST(___S8*,base)+(i)) = (val)
#define ___STORE_U8(base,i,val)*(___CAST(___U8*,base)+(i)) = (val)
#define ___CAST_S8(x)(___S8)(x)
#define ___CAST_U8(x)(___U8)(x)

#else

#define ___FETCH_S8(base,i)___CAST_S8(___FETCH_U8(base,i))
#define ___STORE_S8(base,i,val)___STORE_U8(base,i,___CAST_U8(val))

#ifdef ___S32

#ifdef ___BIG_ENDIAN
#define ___FETCH_U8(base,i) \
((*(___CAST(___U32*,base)+((i)>>2))>>((~(i)&3)<<3))&0xff)
#define ___STORE_U8(base,i,val)*(___CAST(___U32*,base)+((i)>>2)) = \
(*(___CAST(___U32*,base)+((i)>>2))&~___CAST_U32(0xff<<((~(i)&3)<<3))) | \
___CAST_U32((val)<<((~(i)&3)<<3))
#else
#define ___FETCH_U8(base,i) \
((*(___CAST(___U32*,base)+((i)>>2))>>(((i)&3)<<3))&0xff)
#define ___STORE_U8(base,i,val)*(___CAST(___U32*,base)+((i)>>2)) = \
(*(___CAST(___U32*,base)+((i)>>2))&~___CAST_U32(0xff<<(((i)&3)<<3))) | \
___CAST_U32((val)<<(((i)&3)<<3))
#endif

#define ___CAST_S8(x)(___CAST_S32((x)<<24)>>24)
#define ___CAST_U8(x)___CAST_U32((x)&0xff)

#else

#ifdef ___BIG_ENDIAN
#define ___FETCH_U8(base,i) \
((*(___CAST(___U64*,base)+((i)>>3))>>((~(i)&7)<<3))&0xff)
#define ___STORE_U8(base,i,val)*(___CAST(___U64*,base)+((i)>>3)) = \
(*(___CAST(___U64*,base)+((i)>>3))&~___CAST_U64(0xff<<((~(i)&7)<<3))) | \
___CAST_U64((val)<<((~(i)&7)<<3))
#else
#define ___FETCH_U8(base,i) \
((*(___CAST(___U64*,base)+((i)>>3))>>(((i)&7)<<3))&0xff)
#define ___STORE_U8(base,i,val)*(___CAST(___U64*,base)+((i)>>3)) = \
(*(___CAST(___U64*,base)+((i)>>3))&~___CAST_U64(0xff<<(((i)&7)<<3))) | \
___CAST_U64((val)<<(((i)&7)<<3))
#endif

#define ___CAST_S8(x)(___CAST_S64((x)<<56)>>56)
#define ___CAST_U8(x)___CAST_U64((x)&0xff)

#endif

#endif

/*
 * Macros to access ___F32 and ___F64 data types.
 */

#ifdef ___F32
#define ___FETCH_F32(base,i)*(___CAST(___F32*,base)+(i))
#define ___STORE_F32(base,i,val)*(___CAST(___F32*,base)+(i)) = (val)
#define ___CAST_F32(x)___CAST(___F32,x)
#endif

#ifdef ___F64
#define ___FETCH_F64(base,i)*(___CAST(___F64*,base)+(i))
#define ___STORE_F64(base,i,val)*(___CAST(___F64*,base)+(i)) = (val)
#define ___CAST_F64(x)___CAST(___F64,x)
#endif

/*---------------------------------------------------------------------------*/

/*
 * GENERAL DEFINITIONS
 *
 * ___WORD           an integer type able to contain a pointer with no loss
 * ___WORD_WIDTH     is equal to the number of bits in the type ___WORD
 * ___LOG_WORD_WIDTH is equal to the base 2 logarithm of ___WORD_WIDTH
 * ___WS             is equal to sizeof (___WORD)
 * ___LWS            is equal to the base 2 logarithm of ___WS
 * ___FLONUM_SIZE    is equal to sizeof (___F64) / ___WS
 */

#ifdef ___USE_32_BIT_ADDR
#define ___SIZE_T ___U32
#define ___SSIZE_T ___S32
#define ___PTRDIFF_T ___S32
#define ___WORD ___S32
#define ___WORD_WIDTH 32
#define ___LOG_WORD_WIDTH 5
#define ___WS 4
#define ___LWS 2
#define ___FLONUM_SIZE 2
#else
#define ___SIZE_T ___U64
#define ___SSIZE_T ___S64
#define ___PTRDIFF_T ___S64
#define ___WORD ___S64
#define ___WORD_WIDTH 64
#define ___LOG_WORD_WIDTH 6
#define ___WS 8
#define ___LWS 3
#define ___FLONUM_SIZE 1
#endif

#define ___SIZE_TS ___SSIZE_T /* temporary hack... in principle ___SIZE_TS should be replaced with ___SIZE_T (unsigned integer) */

#define ___SCMOBJ ___WORD
#define ___SCMOBJ_WIDTH ___WORD_WIDTH

#define ___ISO_8859_1 ___UM8
#define ___UTF_8 char
#define ___UTF_16 ___UM16
#define ___UCS_2 ___UM16
#define ___UCS_4 ___UM32
#define ___ISO_8859_1STRING ___ISO_8859_1*
#define ___UTF_8STRING ___UTF_8*
#define ___UTF_16STRING ___UTF_16*
#define ___UCS_2STRING ___UCS_2*
#define ___UCS_4STRING ___UCS_4*
#define ___WCHARSTRING ___WCHAR*

#if ___MAX_CHR <= 0xff
#define ___CS 1
#else
#if ___MAX_CHR <= 0xffff
#define ___CS 2
#else
#define ___CS 4
#endif
#endif

#if ___CS == 1
#define ___CS_SELECT(cs1,cs2,cs4)cs1
#else
#if ___CS == 2
#define ___CS_SELECT(cs1,cs2,cs4)cs2
#else
#define ___CS_SELECT(cs1,cs2,cs4)cs4
#endif
#endif

#define ___LCS ___CS_SELECT(0,1,2)

#define ___C ___CS_SELECT(___U8,___U16,___U32)

#if ___WORD_WIDTH == ___VOIDSTAR_WIDTH
#define ___FAKEWORD ___WORD*
#define ___CAST_FAKEWORD_TO_WORD(x)___CAST(___WORD,x)
#define ___CAST_WORDSTAR_TO_FAKEWORD(x)x
#define ___FAKEHOST ___host
#define ___CAST_HOST_TO_FAKEHOST(x)x
#define ___CAST_FAKEHOST_TO_HOST(x)x
#define ___FAKEVOIDSTAR void*
#define ___CAST_VOIDSTAR_TO_FAKEVOIDSTAR(x)___CAST(___FAKEVOIDSTAR,x)
#define ___CAST_FAKEVOIDSTAR_TO_VOIDSTAR(x)___CAST(void*,x)
#else
#define ___FAKEWORD ___WORD
#define ___CAST_FAKEWORD_TO_WORD(x)x
#define ___CAST_WORDSTAR_TO_FAKEWORD(x)___CAST(___WORD,x)
#define ___FAKEHOST ___WORD
#define ___CAST_HOST_TO_FAKEHOST(x)___CAST(___WORD,x)
#define ___CAST_FAKEHOST_TO_HOST(x)___CAST(___host,x)
#define ___FAKEVOIDSTAR ___WORD
#define ___CAST_VOIDSTAR_TO_FAKEVOIDSTAR(x)___CAST(___WORD,x)
#define ___CAST_FAKEVOIDSTAR_TO_VOIDSTAR(x)___CAST(void*,x)
#endif

/* Padding at end of objects so that they can be aligned to an address */
/* multiple of 4 or 8 by moving them up in memory.                     */

#ifdef ___USE_32_BIT_ADDR
#define ___PADDING ,0
#define ___PADDING_SIZE 1
#define ___PADDING_LBL ,{0,0,0,0}
#define ___PADDING_64 ,0,0
#else
#define ___PADDING
#define ___PADDING_SIZE 0
#define ___PADDING_LBL
#define ___PADDING_64
#endif

/* Utility macro to select code for SINGLE/MULTIPLE host. */

#ifdef ___SINGLE_HOST
#define ___SM(s,m)s
#else
#define ___SM(s,m)m
#endif

/*---------------------------------------------------------------------------*/

/* OBJECT REPRESENTATION */

/*
 * For a complete description of the object representation, read the
 * file "lib/mem.c".  These definitions must agree with those in the
 * files "lib/_gambit#.scm" and "gsc/_t-c-3.scm".
 */

/*
 * Type tag assignment.
 *
 * Type tags are located in the lower 2 bits of a ___SCMOBJ.
 *
 * ___TB = number of tag bits
 * ___tFIXNUM   = tag for fixnums (small integers), must be 0
 * ___tSPECIAL  = tag for other immediates (#f, #t, (), #!eof, chars, ...)
 * ___tMEM1     = tag #1 for memory allocated objects (lower bit must be 1)
 * ___tMEM2     = tag #2 for memory allocated objects (lower bit must be 1)
 * ___tSUBTYPED = ___tMEM1
 * ___tPAIR     = ___tMEM1 or ___tMEM2
 */

#define ___TB 2
#define ___tFIXNUM   0
#define ___tSPECIAL  2
#define ___tMEM1     1
#define ___tMEM2     3
#define ___tSUBTYPED ___tMEM1

#ifdef ___USE_SAME_TAG_FOR_PAIRS_AND_SUBTYPED
#define ___tPAIR ___tMEM1
#else
#define ___tPAIR ___tMEM2
#endif

#define ___MEM_ALLOCATED(obj)((obj)&1)
#define ___MEM_ALLOCATED_CLEAR(obj)((obj)&~___CAST(___WORD,1))
#define ___MEM_ALLOCATED_SET(obj)((obj)|1)

/*
 * Subtype tag assignment.
 *
 * These tags are stored in the head of memory allocated objects
 * (including pairs).
 *
 * ___SB = number of subtype tag bits
 * ___sVECTOR       = tag for vectors
 * ___sPAIR         = tag for pairs
 * ___sRATNUM       = tag for ratnums
 * ___sCPXNUM       = tag for cpxnums
 * ___sSTRUCTURE    = tag for structures
 * ___sBOXVALUES    = tag for box and multiple-values objects
 * ___sMEROON       = tag for Meroon objects
 * ___sJAZZ         = tag for Jazz objects
 * ___sSYMBOL       = tag for symbols
 * ___sKEYWORD      = tag for keywords
 * ___sFRAME        = tag for continuation frames
 * ___sCONTINUATION = tag for continuations
 * ___sPROMISE      = tag for promises
 * ___sWEAK         = tag for weak objects (wills and GC hash tables)
 * ___sPROCEDURE    = tag for procedures
 * ___sRETURN       = tag for returns
 * ___sFOREIGN      = tag for foreign data
 * ___sSTRING       = tag for strings
 * ___sS8VECTOR     = tag for 8-bit signed integer vectors
 * ___sU8VECTOR     = tag for 8-bit unsigned integer vectors
 * ___sS16VECTOR    = tag for 16-bit signed integer vectors
 * ___sU16VECTOR    = tag for 16-bit unsigned integer vectors
 * ___sS32VECTOR    = tag for 32-bit signed integer vectors
 * ___sU32VECTOR    = tag for 32-bit unsigned integer vectors
 * ___sF32VECTOR    = tag for 32-bit floating point number vectors
 * ___sS64VECTOR    = tag for 64-bit signed integer vectors
 * ___sU64VECTOR    = tag for 64-bit unsigned integer vectors
 * ___sF64VECTOR    = tag for 64-bit floating point number vectors
 * ___sFLONUM       = tag for flonums
 * ___sBIGNUM       = tag for bignums
 *
 * The five subtype tags ___sS64VECTOR, ___sU64VECTOR, ___sF64VECTOR,
 * ___sFLONUM, ___sBIGNUM must come last.  These object types (and
 * ___sFOREIGN which is always allocated as a ___STILL object) must
 * be aligned on a multiple of 8.
 */

#define ___SB 5
#define ___sVECTOR       0
#define ___sPAIR         1
#define ___sRATNUM       2
#define ___sCPXNUM       3
#define ___sSTRUCTURE    4
#define ___sBOXVALUES    5
#define ___sMEROON       6
#define ___sJAZZ         7
#define ___sSYMBOL       8
#define ___sKEYWORD      9
#define ___sFRAME        10
#define ___sCONTINUATION 11
#define ___sPROMISE      12
#define ___sWEAK         13
#define ___sPROCEDURE    14
#define ___sRETURN       15
#define ___sFOREIGN      18
#define ___sSTRING       19
#define ___sS8VECTOR     20
#define ___sU8VECTOR     21
#define ___sS16VECTOR    22
#define ___sU16VECTOR    23
#define ___sS32VECTOR    24
#define ___sU32VECTOR    25
#define ___sF32VECTOR    26
#define ___sS64VECTOR    27
#define ___sU64VECTOR    28
#define ___sF64VECTOR    29
#define ___sFLONUM       30
#define ___sBIGNUM       31

/*
 * Head type tag assignment.
 *
 * Head type tags are stored in the lower 3 bits of the head of memory
 * allocated objects.
 *
 * ___HTB = number of head tag bits
 * ___MOVABLE0 = tag for movable objects in generation 0
 * ___MOVABLE1 = tag for movable objects in generation 1
 * ___MOVABLE2 = tag for movable objects in generation 2
 * ___FORW     = tag for movable objects that have been forwarded
 * ___STILL    = tag for still objects
 * ___PERM     = tag for permanent objects
 *
 * note: the tag ___FORW+(1<<___TB) is also used for forwarding pointers
 */

#define ___HTB 3
#define ___MOVABLE0 0
#define ___MOVABLE1 1
#define ___MOVABLE2 2
#define ___FORW     3
#define ___STILL    5
#define ___PERM     6

/*
 * Miscellaneous masks.
 */

#define ___LF (___HTB+___SB)

#define ___TMASK ((1<<___TB)-1)
#define ___HTMASK ((1<<___HTB)-1)
#define ___SMASK (((1<<___SB)-1)<<___HTB)
#define ___LMASK (~___CAST(unsigned ___WORD,0)<<___LF)
#define ___LSMASK (~___CAST(unsigned ___WORD,0)<<___HTB)

/*
 * Value constructors for object references inside executable code.
 */

#define ___FAL ((___CAST(___WORD,-1)<<___TB)+___tSPECIAL)
#define ___TRU ((___CAST(___WORD,-2)<<___TB)+___tSPECIAL)
#define ___NUL ((___CAST(___WORD,-3)<<___TB)+___tSPECIAL)
#define ___EOF ((___CAST(___WORD,-4)<<___TB)+___tSPECIAL)
#define ___VOID ((___CAST(___WORD,-5)<<___TB)+___tSPECIAL)
#define ___ABSENT ((___CAST(___WORD,-6)<<___TB)+___tSPECIAL)
#define ___UNB1 ((___CAST(___WORD,-7)<<___TB)+___tSPECIAL)
#define ___UNB2 ((___CAST(___WORD,-8)<<___TB)+___tSPECIAL)
#define ___OPTIONAL ((___CAST(___WORD,-9)<<___TB)+___tSPECIAL)
#define ___KEYOBJ ((___CAST(___WORD,-10)<<___TB)+___tSPECIAL)
#define ___REST ((___CAST(___WORD,-11)<<___TB)+___tSPECIAL)
#define ___UNUSED ((___CAST(___WORD,-14)<<___TB)+___tSPECIAL)
#define ___DELETED ((___CAST(___WORD,-15)<<___TB)+___tSPECIAL)
#define ___FIX(x)(___CAST(___WORD,x)<<___TB)
#if ___SCMOBJ_WIDTH == 32
#define ___BIGFIX(i,x)___SUB(i)
#else
#define ___BIGFIX(i,x)___FIX(x)
#endif
#define ___CHR(x)((___CAST(___WORD,___CS_SELECT(___CAST_U8(x),___CAST_U16(x),___CAST_U32(x)))<<___TB)+___tSPECIAL)

#define ___SYM(i,id)___CAST_FAKEWORD_TO_WORD(___symtbl[i])
#define ___KEY(i,id)___CAST_FAKEWORD_TO_WORD(___keytbl[i])
#define ___CNS(i)___TAG((___ALIGNUP(___cnstbl,___WS)+i*(___PAIR_SIZE+1)),___tPAIR)
#define ___SUB(i)___CAST_FAKEWORD_TO_WORD(___subtbl[i])

/*
 * Value constructors for object references inside constant
 * memory allocated objects.
 */

#define ___REF_FAL ___FAL
#define ___REF_TRU ___TRU
#define ___REF_NUL ___NUL
#define ___REF_EOF ___EOF
#define ___REF_VOID ___VOID
#define ___REF_ABSENT ___ABSENT
#define ___REF_UNB1 ___UNB1
#define ___REF_UNB2 ___UNB2
#define ___REF_OPTIONAL ___OPTIONAL
#define ___REF_KEYOBJ ___KEYOBJ
#define ___REF_REST ___REST
#define ___REF_UNUSED ___UNUSED
#define ___REF_DELETED ___DELETED
#define ___REF_FIX(x)___FIX(x)
#if ___SCMOBJ_WIDTH == 32
#define ___REF_BIGFIX(i,x)___REF_SUB(i)
#else
#define ___REF_BIGFIX(i,x)___REF_FIX(x)
#endif
#define ___REF_CHR(x)___CHR(x)

#define ___REF_SYM(i,id)((___CAST(___WORD,-1-i)<<___TB)+___tMEM2)
#define ___REF_KEY(i,id)((___CAST(___WORD,-1-i)<<___TB)+___tMEM1)
#define ___REF_CNS(i)((___CAST(___WORD,i)<<___TB)+___tMEM2)
#define ___REF_SUB(i)((___CAST(___WORD,i)<<___TB)+___tMEM1)

#ifdef ___SUBCOUNT
#define ___REF_PRC(i)((___CAST(___WORD,___SUBCOUNT+i)<<___TB)+___tMEM1)
#else
#define ___REF_PRC(i)((___CAST(___WORD,i)<<___TB)+___tMEM1)
#endif

/*---------------------------------------------------------------------------*/

/* Miscellaneous macros */

#define ___IF(x) if (x) {
#define ___END_IF }

#define ___NOTHING

#define ___NBELEMS(table) (sizeof (table) / sizeof ((table)[0]))

#define ___INT(x)((x)>>___TB)

#define ___FIX_WIDTH (___SCMOBJ_WIDTH-___TB)
#define ___MIN_FIX (-(___CAST(___WORD,1)<<(___FIX_WIDTH-1)))
#define ___MAX_FIX ((___CAST(___WORD,1)<<(___FIX_WIDTH-1))-1)

#define ___MAX_FIX32 ((___CAST(___WORD,1)<<(32-___TB-1))-1)

#if ___TB == 2
#if ___SCMOBJ_WIDTH == 32
#define ___SQRT_MAX_FIX 23170
#else
#define ___SQRT_MAX_FIX 1518500249L
#endif
#endif

/*
 * Module prefix and C id prefix must match the definitions
 * in the file "gsc/_parms.scm".
 */

#define ___MODULE_PREFIX " "
#define ___C_ID_PREFIX "___"

/*---------------------------------------------------------------------------*/

#define ___ALIGNUP(x,mult) \
___CAST(___WORD*,(___CAST(___WORD,x)+((mult)-1))&~((mult)-1))

#define ___ALLOC(n) ___hp += (n)

#if ___SCMOBJ_WIDTH == 32

#define ___ALLOC_ALIGN64(n) \
___hp = ___CAST(___WORD*, (___CAST(___WORD,___hp) + (((n)<<___LWS) + 7)) & ~7)

#else

#define ___ALLOC_ALIGN64(n) ___ALLOC(n)

#endif

/* Type tests */

#define ___TAG(ptr,tag)(___CAST(___WORD,ptr)+(tag))
#define ___UNTAG(obj)___CAST(___WORD*,(obj)&-(1<<___TB))
#define ___UNTAG_AS(obj,tag)___CAST(___WORD*,(obj)-(tag))

#define ___TYP(x)((x)&___TMASK)
#define ___TESTTYPE(x,typ)(___TYP(x)==(typ))

#define ___TESTHEADERTAG(x,s)(((x)&___SMASK)==((s)<<___HTB))
#define ___TESTSUBTYPETAG(x,s)___TESTHEADERTAG(___HEADER(x),s)
#define ___TESTSUBTYPE(x,s)(___TYP((___temp=(x)))==___tSUBTYPED&&___TESTSUBTYPETAG(___temp,(s)))
#define ___TESTLENGTHSUBTYPETAG(x,bytes,s)((___HEADER(x)&___LSMASK)==___MAKE_HD(bytes,s,0))
#define ___TESTLENGTHSUBTYPE(x,bytes,s)(___TYP((___temp=(x)))==___tSUBTYPED&&___TESTLENGTHSUBTYPETAG(___temp,bytes,s))
#define ___HEADER(x)(*___UNTAG_AS(x,___tSUBTYPED))

#define ___BODY_OFS 1

#ifdef ___USE_HANDLES
#define ___PAIR_OVERHEAD 2
#define ___SUBTYPED_OVERHEAD 2
#define ___BODY(obj)___CAST(___WORD*,*(___UNTAG(obj)+___BODY_OFS)+___BODY_OFS)
#define ___BODY_AS(obj,tag)___CAST(___WORD*,*(___UNTAG_AS(obj,tag)+___BODY_OFS)+___BODY_OFS)
#else
#define ___PAIR_OVERHEAD 1
#define ___SUBTYPED_OVERHEAD 1
#define ___BODY(obj)(___UNTAG(obj)+___BODY_OFS)
#define ___BODY_AS(obj,tag)(___UNTAG_AS(obj,tag)+___BODY_OFS)
#endif

#define ___MAKE_HD(bytes,subtype,tag)(((bytes)<<___LF)+((subtype)<<___HTB)+(tag))
#define ___HD_TYP(head)((head)&___HTMASK)
#define ___HD_BYTES(head)(___CAST(unsigned ___WORD,head)>>___LF)
#define ___HD_WORDS(head)(((___CAST(unsigned ___WORD,head)+((___WS-1)<<___LF)))>>(___LF+___LWS))
#define ___HD_FIELDS(head)(___CAST(unsigned ___WORD,head)>>(___LF+___LWS))
#define ___HD_SUBTYPE(head)((head)>>___HTB&((1<<___SB)-1))

#define ___FIELD(obj,i)(*(___BODY_AS(obj,___tSUBTYPED)+i))

#define ___WORDS(bytes)(((bytes)+___WS-1)>>___LWS)

#define ___MAKE_HD_BYTES(bytes,subtype)___MAKE_HD(bytes,subtype,___MOVABLE0)
#define ___MAKE_HD_WORDS(words,subtype)___MAKE_HD(((words)<<___LWS),subtype,___MOVABLE0)

#define ___SYMBOL_SIZE 4
#define ___KEYWORD_SIZE 3
#define ___WILL_SIZE 3
#define ___TABLE_SIZE 5
#define ___PROMISE_SIZE 2
#define ___RATNUM_SIZE 2
#define ___CPXNUM_SIZE 2
#define ___CONTINUATION_SIZE 2
#define ___THREAD_SIZE 26
#define ___BOX_SIZE 1
#define ___FOREIGN_SIZE 3
#define ___FOREIGN_TAGS 0
#define ___FOREIGN_RELEASE_FN 1
#define ___FOREIGN_PTR 2

/* Flonum boxing and unboxing */

#define ___FLONUM_VAL(obj) *___CAST(___F64*,___BODY_AS(obj,___tSUBTYPED))

#define ___F64UNBOX(x) ___FLONUM_VAL(x)

#define ___F64BOX(x) \
(___ALLOC_ALIGN64(1+___FLONUM_SIZE), \
 ___hp[-(1+___FLONUM_SIZE)] = ___MAKE_HD_WORDS(___FLONUM_SIZE,___sFLONUM), \
 *___CAST(___F64*,___hp-___FLONUM_SIZE) = (x), \
 ___TAG((___hp-(1+___FLONUM_SIZE)),___tSUBTYPED))

#define ___D_F64(x)___F64 x;
#define ___SET_F64(x,y)x=y;

/* Bignum representation */

#define ___BIG_FBASE_WIDTH 8

#if ___SCMOBJ_WIDTH == 32
#define ___BIG_MBASE_WIDTH 16
#else
#define ___BIG_MBASE_WIDTH 32
#endif

#ifndef ___BUILTIN_64BIT_INT_TYPE
#define ___BIG_ABASE_WIDTH 32
#else
#define ___BIG_ABASE_WIDTH 64
#endif

#if ___BIG_ABASE_WIDTH == 32

#define ___BIGAFETCH(base,i) ___FETCH_U32(base,i)
#define ___BIGAFETCHSIGNED(base,i) ___FETCH_S32(base,i)
#define ___BIGASTORE(base,i,val) ___STORE_U32(base,i,val)
#define ___BIGASTORESIGNED(base,i,val) ___STORE_S32(base,i,val)
#define ___BIGALENGTH(vect) ___U32VECTORLENGTH(vect)
#define ___BIGADIGIT ___U32
#define ___BIGADIGITSIGNED ___S32
#define ___BIGASHRINK(x,y) ___U32VECTORSHRINK(x,y)
#define ___BIGATEMP ___u32_temp

#else

#define ___BIGAFETCH(base,i) ___FETCH_U64(base,i)
#define ___BIGAFETCHSIGNED(base,i) ___FETCH_S64(base,i)
#define ___BIGASTORE(base,i,val) ___STORE_U64(base,i,val)
#define ___BIGASTORESIGNED(base,i,val) ___STORE_S64(base,i,val)
#define ___BIGALENGTH(vect) ___U64VECTORLENGTH(vect)
#define ___BIGADIGIT ___U64
#define ___BIGADIGITSIGNED ___S64
#define ___BIGASHRINK(x,y) ___U64VECTORSHRINK(x,y)
#define ___BIGATEMP ___u64_temp

#endif

#define ___BIG_ABASE_MIN_1 (~___CAST(___BIGADIGIT,0))

#if ___BIG_ABASE_WIDTH == 32

#define ___S32UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___INT(___temp) \
 : ___BIGAFETCHSIGNED(___BODY_AS(___temp,___tSUBTYPED),0))

#define ___U32UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___CAST_U32(___INT(___temp)) \
 : ___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),0))

#define ___S64UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___S64_from_SM32(___INT(___temp)) \
 : (___HD_BYTES(___HEADER(___temp)) == (1<<2) \
    ? ___S64_from_SM32(___BIGAFETCHSIGNED(___BODY_AS(___temp,___tSUBTYPED),0)) \
    : ___S64_from_SM32_UM32(___BIGAFETCHSIGNED(___BODY_AS(___temp,___tSUBTYPED),1),___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),0))))

#define ___U64UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___U64_from_UM32(___CAST_U32(___INT(___temp))) \
 : (___HD_BYTES(___HEADER(___temp)) == (1<<2) \
    ? ___U64_from_UM32(___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),0)) \
    : ___U64_from_UM32_UM32(___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),1),___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),0))))

#if ___SCMOBJ_WIDTH == 32

#define ___S32BOX(x) \
(___s32_temp=(x), \
 (___s32_temp >= ___MIN_FIX && ___s32_temp <= ___MAX_FIX \
  ? ___FIX(___s32_temp) \
  : (___ALLOC(1+___WORDS(1<<2)), \
     ___hp[-(1+___WORDS(1<<2))] = ___MAKE_HD_BYTES(1<<2,___sBIGNUM), \
     ___BIGASTORESIGNED(___hp,-1,___s32_temp), \
     ___TAG((___hp-(1+___WORDS(1<<2))),___tSUBTYPED))))

#define ___U32BOX(x) \
(___u32_temp=(x), \
 (___u32_temp <= ___CAST_U32(___MAX_FIX) \
  ? ___FIX(___u32_temp) \
  : (___CAST_S32(___u32_temp) < 0 \
     ? (___ALLOC(1+___WORDS(2<<2)), \
        ___hp[-(1+___WORDS(2<<2))] = ___MAKE_HD_BYTES(2<<2,___sBIGNUM), \
        ___BIGASTORE(___hp,-2,___u32_temp), \
        ___BIGASTORE(___hp,-1,0), \
        ___TAG((___hp-(1+___WORDS(2<<2))),___tSUBTYPED)) \
     : (___ALLOC(1+___WORDS(1<<2)), \
        ___hp[-(1+___WORDS(1<<2))] = ___MAKE_HD_BYTES(1<<2,___sBIGNUM), \
        ___BIGASTORE(___hp,-1,___u32_temp), \
        ___TAG((___hp-(1+___WORDS(1<<2))),___tSUBTYPED)))))

#define ___S64BOX(x) \
(___s64_temp=(x), \
 (((___s32_temp = ___CAST_S32(___S64_lo32(___s64_temp)))>>31) \
  == ___S64_hi32(___s64_temp) \
  ? (___s32_temp >= ___MIN_FIX && ___s32_temp <= ___MAX_FIX \
     ? ___FIX(___s32_temp) \
     : (___ALLOC(1+___WORDS(1<<2)), \
        ___hp[-(1+___WORDS(1<<2))] = ___MAKE_HD_BYTES(1<<2,___sBIGNUM), \
        ___BIGASTORE(___hp,-1,___s32_temp), \
        ___TAG((___hp-(1+___WORDS(1<<2))),___tSUBTYPED))) \
  : (___ALLOC(1+___WORDS(2<<2)), \
     ___hp[-(1+___WORDS(2<<2))] = ___MAKE_HD_BYTES(2<<2,___sBIGNUM), \
     ___BIGASTORE(___hp,-2,___s32_temp), \
     ___BIGASTORESIGNED(___hp,-1,___S64_hi32(___s64_temp)), \
     ___TAG((___hp-(1+___WORDS(2<<2))),___tSUBTYPED))))

#define ___U64BOX(x) \
(___u64_temp=(x), \
 (___CAST_S32(___U64_hi32(___u64_temp)) < 0 \
  ? (___ALLOC(1+___WORDS(3<<2)), \
     ___hp[-(1+___WORDS(3<<2))] = ___MAKE_HD_BYTES(3<<2,___sBIGNUM), \
     ___BIGASTORE(___hp,-3,___U64_lo32(___u64_temp)), \
     ___BIGASTORE(___hp,-2,___U64_hi32(___u64_temp)), \
     ___BIGASTORE(___hp,-1,0), \
     ___TAG((___hp-(1+___WORDS(3<<2))),___tSUBTYPED)) \
  : (((___u32_temp = ___U64_lo32(___u64_temp)) & (___CAST_U32(1)<<31)) \
     == ___U64_hi32(___u64_temp) \
     ? (___u32_temp <= ___MAX_FIX \
        ? ___FIX(___u32_temp) \
        : (___ALLOC(1+___WORDS(1<<2)), \
           ___hp[-(1+___WORDS(1<<2))] = ___MAKE_HD_BYTES(1<<2,___sBIGNUM), \
           ___BIGASTORE(___hp,-1,___u32_temp), \
           ___TAG((___hp-(1+___WORDS(1<<2))),___tSUBTYPED))) \
     : (___ALLOC(1+___WORDS(2<<2)), \
        ___hp[-(1+___WORDS(2<<2))] = ___MAKE_HD_BYTES(2<<2,___sBIGNUM), \
        ___BIGASTORE(___hp,-2,___u32_temp), \
        ___BIGASTORESIGNED(___hp,-1,___S64_hi32(___u64_temp)), \
        ___TAG((___hp-(1+___WORDS(2<<2))),___tSUBTYPED)))))

#else

#define ___S32BOX(x) ___FIX(___CAST_S64(x))
#define ___U32BOX(x) ___FIX(___CAST_U64(x))

#define ___S64BOX(x) \
(___s64_temp=(x), \
 (___s64_temp >= ___MIN_FIX && ___s64_temp <= ___MAX_FIX \
  ? ___FIX(___s64_temp) \
  : ((___CAST_S32(___S64_lo32(___s64_temp))>>31) == ___S64_hi32(___s64_temp) \
     ? (___ALLOC(1+___WORDS(1<<2)), \
        ___hp[-(1+___WORDS(1<<2))] = ___MAKE_HD_BYTES(1<<2,___sBIGNUM), \
        ___BIGASTORE(___hp,-1,___S64_lo32(___s64_temp)), \
        ___TAG((___hp-(1+___WORDS(1<<2))),___tSUBTYPED)) \
     : (___ALLOC(1+___WORDS(2<<2)), \
        ___hp[-(1+___WORDS(2<<2))] = ___MAKE_HD_BYTES(2<<2,___sBIGNUM), \
        ___BIGASTORE(___hp,-2,___S64_lo32(___s64_temp)), \
        ___BIGASTORESIGNED(___hp,-1,___S64_hi32(___s64_temp)), \
        ___TAG((___hp-(1+___WORDS(2<<2))),___tSUBTYPED)))))

#define ___U64BOX(x) \
(___u64_temp=(x), \
 (___u64_temp <= ___CAST_U64(___MAX_FIX) \
  ? ___FIX(___u64_temp) \
  : (___CAST_S64(___u64_temp) < 0 \
     ? (___ALLOC(1+___WORDS(3<<2)), \
        ___hp[-(1+___WORDS(3<<2))] = ___MAKE_HD_BYTES(3<<2,___sBIGNUM), \
        ___BIGASTORE(___hp,-3,___U64_lo32(___u64_temp)), \
        ___BIGASTORE(___hp,-2,___U64_hi32(___u64_temp)), \
        ___BIGASTORE(___hp,-1,0), \
        ___TAG((___hp-(1+___WORDS(3<<2))),___tSUBTYPED)) \
     : ((___U64_lo32(___u64_temp) & (___CAST_U32(1)<<31)) == ___U64_hi32(___u64_temp) \
        ? (___ALLOC(1+___WORDS(1<<2)), \
           ___hp[-(1+___WORDS(1<<2))] = ___MAKE_HD_BYTES(1<<2,___sBIGNUM), \
           ___BIGASTORE(___hp,-1,___S64_lo32(___u64_temp)), \
           ___TAG((___hp-(1+___WORDS(1<<2))),___tSUBTYPED)) \
        : (___ALLOC(1+___WORDS(2<<2)), \
           ___hp[-(1+___WORDS(2<<2))] = ___MAKE_HD_BYTES(2<<2,___sBIGNUM), \
           ___BIGASTORE(___hp,-2,___S64_lo32(___u64_temp)), \
           ___BIGASTORESIGNED(___hp,-1,___S64_hi32(___u64_temp)), \
           ___TAG((___hp-(1+___WORDS(2<<2))),___tSUBTYPED))))))

#endif

#else

#define ___S32UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___INT(___temp) \
 : ___CAST_S32(___U64_lo32(___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),0))))

#define ___U32UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___CAST_U32(___INT(___temp)) \
 : ___U64_lo32(___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),0)))

#define ___S64UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___INT(___temp) \
 : ___BIGAFETCHSIGNED(___BODY_AS(___temp,___tSUBTYPED),0))

#define ___U64UNBOX(x) \
(___TYP((___temp=x)) == ___tFIXNUM \
 ? ___CAST_U64(___INT(___temp)) \
 : ___BIGAFETCH(___BODY_AS(___temp,___tSUBTYPED),0))

#if ___SCMOBJ_WIDTH == 32

#define ___S32BOX(x) \
(___s32_temp=(x), \
 (___s32_temp >= ___MIN_FIX && ___s32_temp <= ___MAX_FIX \
  ? ___FIX(___s32_temp) \
  : (___ALLOC_ALIGN64(1+___WORDS(1<<3)), \
     ___hp[-(1+___WORDS(1<<3))] = ___MAKE_HD_BYTES(1<<3,___sBIGNUM), \
     ___BIGASTORESIGNED(___hp,-1,___S64_from_SM32(___s32_temp)), \
     ___TAG((___hp-(1+___WORDS(1<<3))),___tSUBTYPED))))

#define ___U32BOX(x) \
(___u32_temp=(x), \
 (___u32_temp <= ___CAST_U32(___MAX_FIX) \
  ? ___FIX(___u32_temp) \
  : (___ALLOC_ALIGN64(1+___WORDS(1<<3)), \
     ___hp[-(1+___WORDS(1<<3))] = ___MAKE_HD_BYTES(1<<3,___sBIGNUM), \
     ___BIGASTORE(___hp,-1,___U64_from_UM32(___u32_temp)), \
     ___TAG((___hp-(1+___WORDS(1<<3))),___tSUBTYPED))))

#else

#define ___S32BOX(x) ___FIX(___CAST_S64(x))
#define ___U32BOX(x) ___FIX(___CAST_U64(x))

#endif

#define ___S64BOX(x) \
(___s64_temp=(x), \
 (___s64_temp >= ___MIN_FIX && ___s64_temp <= ___MAX_FIX \
  ? ___FIX(___s64_temp) \
  : (___ALLOC_ALIGN64(1+___WORDS(1<<3)), \
     ___hp[-(1+___WORDS(1<<3))] = ___MAKE_HD_BYTES(1<<3,___sBIGNUM), \
     ___BIGASTORESIGNED(___hp,-1,___s64_temp), \
     ___TAG((___hp-(1+___WORDS(1<<3))),___tSUBTYPED))))

#define ___U64BOX(x) \
(___u64_temp=(x), \
 (___u64_temp <= ___CAST_U64(___MAX_FIX) \
  ? ___FIX(___u64_temp) \
  : (___CAST_S64(___u64_temp) < 0 \
     ? (___ALLOC_ALIGN64(1+___WORDS(2<<3)), \
        ___hp[-(1+___WORDS(2<<3))] = ___MAKE_HD_BYTES(2<<3,___sBIGNUM), \
        ___BIGASTORE(___hp,-2,___u64_temp), \
        ___BIGASTORE(___hp,-1,0), \
        ___TAG((___hp-(1+___WORDS(2<<3))),___tSUBTYPED)) \
     : (___ALLOC_ALIGN64(1+___WORDS(1<<3)), \
        ___hp[-(1+___WORDS(1<<3))] = ___MAKE_HD_BYTES(1<<3,___sBIGNUM), \
        ___BIGASTORE(___hp,-1,___u64_temp), \
        ___TAG((___hp-(1+___WORDS(1<<3))),___tSUBTYPED)))))

#endif

#if ___BIG_ABASE_WIDTH == 32

#if ___SCMOBJ_WIDTH == 32

#define ___BIGFROMFIX(x) \
(___ALLOC(1+___WORDS(1<<2)), \
 ___hp[-(1+___WORDS(1<<2))] = ___MAKE_HD_BYTES(1<<2,___sBIGNUM), \
 ___BIGASTORESIGNED(___hp,-1,___INT(x)), \
 ___TAG((___hp-(1+___WORDS(1<<2))),___tSUBTYPED))

#else

#define ___BIGFROMFIX(x) \
(___ALLOC(1+___WORDS(2<<2)), \
 ___hp[-(1+___WORDS(2<<2))] = ___MAKE_HD_BYTES(2<<2,___sBIGNUM), \
 ___BIGASTORE(___hp,-2,___S64_lo32(___INT(x))), \
 ___BIGASTORESIGNED(___hp,-1,___S64_hi32(___INT(x))), \
 ___TAG((___hp-(1+___WORDS(2<<2))),___tSUBTYPED))

#endif

#else

#define ___BIGFROMFIX(x) \
(___ALLOC_ALIGN64(1+___WORDS(1<<3)), \
 ___hp[-(1+___WORDS(1<<3))] = ___MAKE_HD_BYTES(1<<3,___sBIGNUM), \
 ___BIGASTORESIGNED(___hp,-1,___CAST(___BIGADIGIT,___INT(x))), \
 ___TAG((___hp-(1+___WORDS(1<<3))),___tSUBTYPED))

#endif

#define ___BIGALESSP(x,y,i) \
(___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) \
 < (___BIGAFETCH(___BODY_AS(y,___tSUBTYPED),(i)>>___TB)))

#define ___BIGAEQP(x,y,i) \
(___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) \
 == (___BIGAFETCH(___BODY_AS(y,___tSUBTYPED),(i)>>___TB)))

#define ___BIGAONESP(x,i) \
(___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) == ___BIG_ABASE_MIN_1)

#define ___BIGAZEROP(x,i) \
(___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) == 0)

#define ___BIGANEGATIVEP(x,i) \
(___BIGAFETCHSIGNED(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) < 0)

#define ___BIGTOFIX(x) \
(___BIGATEMP=___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),0), \
 (___BIGATEMP == ___CAST(___BIGADIGIT,___INT(___FIX(___BIGATEMP))) ? ___FIX(___BIGATEMP) : ___FAL))


#define ___BIGACAT(x,i,hi,j,lo,k,divider) \
___BIGATEMP=((___BIGADIGIT)___BIGAFETCH(___BODY_AS(hi,___tSUBTYPED),(j)>>___TB) << ___INT(divider)) | \
            ((___BIGADIGIT)___BIGAFETCH(___BODY_AS(lo,___tSUBTYPED),(k)>>___TB) >> (___BIG_ABASE_WIDTH - ___INT(divider))); \
___BIGASTORE(___BODY_AS(x,___tSUBTYPED),(i)>>___TB,(___BIGADIGIT)___BIGATEMP);

#define ___BIGAAND(x,i,y,j) \
___BIGATEMP= ___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) & ___BIGAFETCH(___BODY_AS(y,___tSUBTYPED),(j)>>___TB); \
___BIGASTORE(___BODY_AS(x,___tSUBTYPED),(i)>>___TB,(___BIGADIGIT)___BIGATEMP);

#define ___BIGAIOR(x,i,y,j) \
___BIGATEMP= ___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) | ___BIGAFETCH(___BODY_AS(y,___tSUBTYPED),(j)>>___TB); \
___BIGASTORE(___BODY_AS(x,___tSUBTYPED),(i)>>___TB,(___BIGADIGIT)___BIGATEMP);

#define ___BIGAXOR(x,i,y,j) \
___BIGATEMP= ___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB) ^ ___BIGAFETCH(___BODY_AS(y,___tSUBTYPED),(j)>>___TB); \
___BIGASTORE(___BODY_AS(x,___tSUBTYPED),(i)>>___TB,(___BIGADIGIT)___BIGATEMP);

#define ___BIGANOT(x,i) \
___BIGATEMP= ~___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB); \
___BIGASTORE(___BODY_AS(x,___tSUBTYPED),(i)>>___TB,(___BIGADIGIT)___BIGATEMP);



#define ___BIGNEGATIVEP(x) \
(___BIGAFETCHSIGNED(___BODY_AS(x,___tSUBTYPED),___FIXSUB(___BIGALENGTH(x),___FIX_1)>>___TB) < 0)

#define ___BIGACOPY(result,i,y,j) \
___BIGASTORE(___BODY_AS(result,___tSUBTYPED),(i)>>___TB, \
___BIGAFETCH(___BODY_AS(y,___tSUBTYPED),(j)>>___TB));

#define ___BIGAINC(x,i) \
(___BIGATEMP = (___BIGADIGIT)___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB)+(___BIGADIGIT) 1, \
 ___BIGASTORE(___BODY_AS(x,___tSUBTYPED),(i)>>___TB,(___BIGADIGIT)___BIGATEMP), \
(___BIGATEMP == 0 ? ___FIX_1 : ___FIX_0))

#define ___BIGADEC(x,i) \
(___BIGATEMP = (___BIGADIGIT)___BIGAFETCH(___BODY_AS(x,___tSUBTYPED),(i)>>___TB)-(___BIGADIGIT) 1, \
 ___BIGASTORE(___BODY_AS(x,___tSUBTYPED),(i)>>___TB,(___BIGADIGIT)___BIGATEMP), \
(___BIGATEMP == ___BIG_ABASE_MIN_1 ? ___FIX_1 : ___FIX_0))

#define ___BIGAADD(result,i,y,j,carry) \
(carry ? (___BIGATEMP=(___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i))+ \
                      (___BIGADIGIT)___BIGAFETCH(___BODY_AS(     y,___tSUBTYPED),___INT(j))+ \
                      (___BIGADIGIT) 1, \
          ((___BIGADIGIT) ___BIGATEMP <= (___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i)) \
           ? \
           (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_1) \
           : \
           (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_0))) \
         : \
         (___BIGATEMP=(___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i))+ \
                      (___BIGADIGIT)___BIGAFETCH(___BODY_AS(     y,___tSUBTYPED),___INT(j)), \
          ((___BIGADIGIT) ___BIGATEMP < (___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i)) \
           ? \
           (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_1) \
           : \
           (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_0))))

#define ___BIGASUB(result,i,y,j,borrow) \
(borrow ? (___BIGATEMP=(___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i))- \
                       (___BIGADIGIT)___BIGAFETCH(___BODY_AS(     y,___tSUBTYPED),___INT(j))- \
                       (___BIGADIGIT) 1, \
           ((___BIGADIGIT) ___BIGATEMP >= (___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i)) \
            ? \
            (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_1) \
            : \
            (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_0))) \
          : \
          (___BIGATEMP=(___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i))- \
                       (___BIGADIGIT)___BIGAFETCH(___BODY_AS(     y,___tSUBTYPED),___INT(j)), \
           ((___BIGADIGIT) ___BIGATEMP > (___BIGADIGIT)___BIGAFETCH(___BODY_AS(result,___tSUBTYPED),___INT(i)) \
            ? \
            (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_1) \
            : \
            (___BIGASTORE(___BODY_AS(result,___tSUBTYPED),___INT(i),(___BIGADIGIT)___BIGATEMP), ___FIX_0))))

#if ___BIG_MBASE_WIDTH == 16

#ifdef ___BIG_ENDIAN

#if ___BIG_ABASE_WIDTH == 64
#define ___BIG_END_MFLIP(x)((x)^___FIX(3))
#else
#define ___BIG_END_MFLIP(x)((x)^___FIX(1))
#endif
#else
#define ___BIG_END_MFLIP(x)(x)
#endif

#define ___BIGMLENGTH(v) ___U16VECTORLENGTH(v)
#define ___BIGMFETCH(base,i) ___FETCH_U16(base,i)
#define ___BIGMSTORE(base,i,val) ___STORE_U16(base,i,val)
#define ___BIGMDIGIT ___U16
#define ___BIGMDOUBLEDIGIT ___U32

#else

#ifdef ___BIG_ENDIAN
#define ___BIG_END_MFLIP(x)((x)^___FIX(1))
#else
#define ___BIG_END_MFLIP(x)(x)
#endif

#define ___BIGMLENGTH(v) ___U32VECTORLENGTH(v)
#define ___BIGMFETCH(base,i) ___FETCH_U32(base,i)
#define ___BIGMSTORE(base,i,val) ___STORE_U32(base,i,val)
#define ___BIGMDIGIT ___U32
#define ___BIGMDOUBLEDIGIT ___U64

#endif

#define ___BIG_MBASE ((___BIGMDOUBLEDIGIT)1 << ___BIG_MBASE_WIDTH)

#define ___BIGMREF(x,j) \
___FIX(___BIGMFETCH(___BODY_AS(x,___tSUBTYPED),___BIG_END_MFLIP(j)>>___TB))

#define ___BIGMSET(result,i,carry) \
___BIGMSTORE(___BODY_AS(result,___tSUBTYPED),___BIG_END_MFLIP(i)>>___TB,___INT(carry));

#define ___BIGMMUL(result,i,y,j,multiplier,carry) \
     (___temp=(___BIGMDOUBLEDIGIT)___BIGMFETCH(___BODY_AS(result,___tSUBTYPED),___INT(___BIG_END_MFLIP(i))) \
      + (___BIGMDOUBLEDIGIT)___BIGMFETCH(___BODY_AS(y,___tSUBTYPED),___INT(___BIG_END_MFLIP(j))) \
      * (___BIGMDOUBLEDIGIT)___INT(multiplier) \
      + (___BIGMDOUBLEDIGIT)___INT(carry), \
      ___BIGMSTORE(___BODY_AS(result,___tSUBTYPED),___INT(___BIG_END_MFLIP(i)),(___BIGMDIGIT)___temp), \
      ___FIX((___BIGMDOUBLEDIGIT)___temp >> ___BIG_MBASE_WIDTH))

#define ___BIGMDIV(u,i,v,k,q,borrow) \
     (___temp = (___BIGMDOUBLEDIGIT)___BIGMFETCH(___BODY_AS(u,___tSUBTYPED),___INT(___BIG_END_MFLIP(i))) \
                -(___BIGMDOUBLEDIGIT)___BIGMFETCH(___BODY_AS(v,___tSUBTYPED),___INT(___BIG_END_MFLIP(k))) \
                 * (___BIGMDOUBLEDIGIT)___INT(q) \
                 + (___BIGMDOUBLEDIGIT)___INT(borrow),\
      ___BIGMSTORE(___BODY_AS(u,___tSUBTYPED),___INT(___BIG_END_MFLIP(i)),((___BIGMDIGIT) ___temp)), \
      ___temp >>= ___BIG_MBASE_WIDTH, \
      (___temp > 0 ? ___FIX(___temp - ___BIG_MBASE) : ___FIX(___temp)))


#define ___BIGMQUO(u,j,v) \
___FIX((((___BIGMDOUBLEDIGIT)___BIGMFETCH(___BODY_AS(u,___tSUBTYPED),___INT(___BIG_END_MFLIP(j))) << ___BIG_MBASE_WIDTH) \
+___BIGMFETCH(___BODY_AS(u,___tSUBTYPED),___INT(___BIG_END_MFLIP(j-___FIX(1)))))/___INT(v))


#define ___BIGMREM(u,j,v,q) \
___FIX((((___BIGMDOUBLEDIGIT)___BIGMFETCH(___BODY_AS(u,___tSUBTYPED),___INT(___BIG_END_MFLIP(j))) << ___BIG_MBASE_WIDTH) \
+___BIGMFETCH(___BODY_AS(u,___tSUBTYPED),___INT(___BIG_END_MFLIP(j-___FIX(1))))) \
-((___BIGMDOUBLEDIGIT)___INT(v)*(___BIGMDOUBLEDIGIT)___INT(q)))

#define ___BIGMTESTP(q,v,r,u) \
(((___BIGMDOUBLEDIGIT)___INT(v)*___INT(q))>((___BIGMDOUBLEDIGIT)___INT(r) << ___BIG_MBASE_WIDTH) +___INT(u))




#ifdef ___BIG_ENDIAN

#if ___BIG_ABASE_WIDTH == 64
#define ___BIG_END_FFLIP(x)((x)^___FIX(7))
#else
#define ___BIG_END_FFLIP(x)((x)^___FIX(3))
#endif

#else

#define ___BIG_END_FFLIP(x)(x)

#endif

#define ___BIGFREF(x,j)___U8VECTORREF(x,___BIG_END_FFLIP(j))

#define ___BIGFSET(result,i,carry)___U8VECTORSET(result,___BIG_END_FFLIP(i),carry)

#define ___BIGFLENGTH(x)___U8VECTORLENGTH(x)

/*---------------------------------------------------------------------------*/

/* Inlinable operations (for 'apply' and 'ifjump' GVM instructions) */

/* APPLY-able operations */

#define ___TYPE(x)___FIX(___TYP(x))
#define ___TYPECAST(x,y)(((x)&~___TMASK)+___INT(y))
#define ___SUBTYPE(x)((*___UNTAG(x)&___SMASK)>>(___HTB-___TB))
#define ___SUBTYPESET(x,y)___temp=(x);___HEADER(___temp)=(___HEADER(___temp)&~___SMASK)+((y)<<(___HTB-___TB));

/* IFJUMP-able operations */

#define ___FALSEP(x)((x)==___FAL)
#define ___BOOLEANP(x)(((x)==___FAL)||((x)==___TRU))
#define ___NULLP(x)((x)==___NUL)
#define ___UNBOUNDP(x)(((___temp=(x))==___UNB1)||(___temp==___UNB2))
#define ___EQP(x,y)((x)==(y))
#define ___EOFP(x)((x)==___EOF)

/* IFJUMP-able operations */

#define ___FIXNUMP(x)___TESTTYPE(x,___tFIXNUM)
#define ___FLONUMP(x)___TESTSUBTYPE(x,___sFLONUM)
#define ___SPECIALP(x)___TESTTYPE(x,___tSPECIAL)
#if ___tPAIR == ___tSUBTYPED
#define ___PAIRP(x)___TESTSUBTYPE(x,___sPAIR)
#else
#define ___PAIRP(x)___TESTTYPE(x,___tPAIR)
#endif
#define ___PAIRMUTABLEP(obj)(___HD_TYP(*___UNTAG_AS(obj,___tPAIR))!=___PERM)
#define ___SUBTYPEDP(x)___TESTTYPE(x,___tSUBTYPED)
#define ___SUBTYPEDMUTABLEP(obj)(___HD_TYP(*___UNTAG_AS(obj,___tSUBTYPED))!=___PERM)
#define ___SUBTYPEDVECTORP(x)___TESTSUBTYPETAG(x,___sVECTOR)
#define ___SUBTYPEDSYMBOLP(x)___TESTSUBTYPETAG(x,___sSYMBOL)
#define ___SUBTYPEDFLONUMP(x)___TESTSUBTYPETAG(x,___sFLONUM)
#define ___SUBTYPEDBIGNUMP(x)___TESTSUBTYPETAG(x,___sBIGNUM)
#define ___VECTORP(x)___TESTSUBTYPE(x,___sVECTOR)
#define ___RATNUMP(x)___TESTSUBTYPE(x,___sRATNUM)
#define ___CPXNUMP(x)___TESTSUBTYPE(x,___sCPXNUM)
#define ___STRUCTUREP(x)___TESTSUBTYPE(x,___sSTRUCTURE)
#define ___BOXP(x)(___TYP((___temp=x))==___tSUBTYPED&&(___HEADER(___temp)&___LSMASK)==___MAKE_HD((___BOX_SIZE<<___LWS),___sBOXVALUES,0))
#define ___VALUESP(x)(___TYP((___temp=x))==___tSUBTYPED&&___TESTSUBTYPETAG(___temp,___sBOXVALUES)&&(___HEADER(___temp)&___LSMASK)!=___MAKE_HD((___BOX_SIZE<<___LWS),___sBOXVALUES,0))
#define ___MEROONP(x)___TESTSUBTYPE(x,___sMEROON)
#define ___JAZZP(x)___TESTSUBTYPE(x,___sJAZZ)
#define ___SYMBOLP(x)___TESTSUBTYPE(x,___sSYMBOL)
#define ___KEYWORDP(x)___TESTSUBTYPE(x,___sKEYWORD)
#define ___SYMKEYP(x)(___SYMBOLP(x)||___KEYWORDP(x))
#define ___FRAMEP(x)___TESTSUBTYPE(x,___sFRAME)
#define ___CONTINUATIONP(x)___TESTSUBTYPE(x,___sCONTINUATION)
#define ___PROMISEP(x)___TESTSUBTYPE(x,___sPROMISE)
#define ___WILLP(x)___TESTLENGTHSUBTYPE(x,(___WILL_SIZE<<___LWS),___sWEAK)
#define ___GCHASHTABLEP(x)(___TYP((___temp=(x)))==___tSUBTYPED&&___TESTHEADERTAG((___temp=___HEADER(___temp)),___sWEAK)&&(___temp&___LSMASK)!=___MAKE_HD((___WILL_SIZE<<___LWS),___sWEAK,0))
#define ___MEMALLOCATEDP(x)___MEM_ALLOCATED(x)
#define ___PROCEDUREP(x)___TESTSUBTYPE(x,___sPROCEDURE)
#define ___RETURNP(x)___TESTSUBTYPE(x,___sRETURN)
#define ___FOREIGNP(x)___TESTSUBTYPE(x,___sFOREIGN)
#define ___STRINGP(x)___TESTSUBTYPE(x,___sSTRING)
#define ___S8VECTORP(x)___TESTSUBTYPE(x,___sS8VECTOR)
#define ___U8VECTORP(x)___TESTSUBTYPE(x,___sU8VECTOR)
#define ___S16VECTORP(x)___TESTSUBTYPE(x,___sS16VECTOR)
#define ___U16VECTORP(x)___TESTSUBTYPE(x,___sU16VECTOR)
#define ___S32VECTORP(x)___TESTSUBTYPE(x,___sS32VECTOR)
#define ___U32VECTORP(x)___TESTSUBTYPE(x,___sU32VECTOR)
#define ___S64VECTORP(x)___TESTSUBTYPE(x,___sS64VECTOR)
#define ___U64VECTORP(x)___TESTSUBTYPE(x,___sU64VECTOR)
#define ___F32VECTORP(x)___TESTSUBTYPE(x,___sF32VECTOR)
#define ___F64VECTORP(x)___TESTSUBTYPE(x,___sF64VECTOR)
#define ___BIGNUMP(x)___TESTSUBTYPE(x,___sBIGNUM)
#define ___CHARP(x)(___TYP((___temp=x))==___tSPECIAL&&___temp>=0)
#define ___NUMBERP(x)___COMPLEXP(x)
#define ___COMPLEXP(x)((___TYP((___temp=(x)))==___tFIXNUM)||(___TYP(___temp)==___tSUBTYPED&&((___temp=(___HEADER(___temp)&___SMASK))==(___sFLONUM<<___HTB)||___temp==(___sBIGNUM<<___HTB)||___temp==(___sRATNUM<<___HTB)||___temp==(___sCPXNUM<<___HTB))))

/* APPLY-able operations */

#define ___FIX_0 ___FIX(0)
#define ___FIXPOS(x)((___WORD)(x))
#define ___FIXMAX(x,y)(((x)<(y))?(y):(x))
#define ___FIXMIN(x,y)(((x)<(y))?(x):(y))
#define ___FIXADD(x,y)((___WORD)((x)+(y)))
#ifndef ___FIXADDP
#define ___FIXADDP(x,y)(___temp=___FIXADD(x,y),___EXPECT_FALSE(((___temp^(x))&(___temp^(y)))<0)?___FAL:___temp)
#endif
#define ___FIX_1 ___FIX(1)
#define ___FIXMUL(x,y)((___WORD)((x)*___INT(y)))
#define ___FIXMULP(x,y)(___EXPECT_FALSE(___FIXQUO((___temp=___FIXMUL(x,y)),y)!=(x))?___FAL:___temp)
#define ___FIXSQUARE(x)___FIXMUL(x,x)
#define ___FIXSQUAREP(x)(___EXPECT_FALSE(___CAST(unsigned ___WORD,___FIXADD(x,___FIX(___SQRT_MAX_FIX)))>(___CAST(unsigned ___WORD,___FIX(___SQRT_MAX_FIX))<<1))?___FAL:___FIXSQUARE(x))
#define ___FIXNEG(x)((___WORD)(-(x)))
#define ___FIXNEGP(x)(___EXPECT_FALSE((x)==___FIX(___MIN_FIX))?___FAL:___FIXNEG(x))
#define ___FIXSUB(x,y)((___WORD)((x)-(y)))
#ifndef ___FIXSUBP
#define ___FIXSUBP(x,y)(___temp=___FIXSUB(x,y),___EXPECT_FALSE(((___temp^(x))&((y)^(x)))<0)?___FAL:___temp)
#endif
#define ___FIXQUO(x,y)___FIX(((x)/(y)))
#define ___FIXREM(x,y)((___WORD)((x)%(y)))/****is this ok?*******/
#define ___FIXMOD(x,y)((___temp=___FIXREM((___ps->temp1=x),(___ps->temp2=y)))==0?___FIX(0):((___ps->temp1<0)==(___ps->temp2<0)?___temp:___FIXADD(___temp,___ps->temp2)))
#define ___FIXNOT(x)((___WORD)((x)^~___TMASK))
#define ___FIXAND(x,y)((___WORD)((x)&(y)))
#define ___FIX_M1 ___FIX(-1)
#define ___FIXIOR(x,y)((___WORD)((x)|(y)))
#define ___FIXXOR(x,y)((___WORD)((x)^(y)))
#define ___FIXIF(x,y,z)((___WORD)(((x)&(y))|(~(x)&(z))))
#define ___FIXABS(x)((x)<0?___FIXNEG(x):(x))
#define ___FIXABSP(x)((x)<0?((___EXPECT_FALSE((x)==___FIX(___MIN_FIX))?___FAL:___FIXNEG(x))):(x))

#if ___SCMOBJ_WIDTH == 32
#define ___SCMOBJ_MASK(x,y)y
#define ___BITCOUNT_TEMP() \
(___temp=(___temp&___SCMOBJ_MASK(0x55555555,0x55555555))+ \
         ((___temp>>1)&___SCMOBJ_MASK(0x55555555,0x55555555)), \
 ___temp=(___temp&___SCMOBJ_MASK(0x33333333,0x33333333))+ \
         ((___temp>>2)&___SCMOBJ_MASK(0x33333333,0x33333333)), \
 ___temp=(___temp&___SCMOBJ_MASK(0x0f0f0f0f,0x0f0f0f0f))+ \
         ((___temp>>4)&___SCMOBJ_MASK(0x0f0f0f0f,0x0f0f0f0f)), \
 ___temp=___temp+(___temp>>8), \
 ___temp=___temp+(___temp>>16), \
 ___FIX(___temp&0xff))
#define ___FIXLENGTH(x) \
(((___temp=___INT(x))<0)&&(___temp=~___temp), \
 ___temp|=(___temp>>1), \
 ___temp|=(___temp>>2), \
 ___temp|=(___temp>>4), \
 ___temp|=(___temp>>8), \
 ___temp|=(___temp>>16), \
 ___BITCOUNT_TEMP())
#define ___FIXFIRSTBITSET(x) \
(((___temp=(x))==0) \
 ?___FIX(-1) \
 :(___temp=(___temp&-___temp), \
   ___FIX((((___temp&~___SCMOBJ_MASK(0x55555555,0x55555555))!=0)| \
           (((___temp&~___SCMOBJ_MASK(0x33333333,0x33333333))!=0)<<1)| \
           (((___temp&~___SCMOBJ_MASK(0x0f0f0f0f,0x0f0f0f0f))!=0)<<2)| \
           (((___temp&~___SCMOBJ_MASK(0x00ff00ff,0x00ff00ff))!=0)<<3)| \
           (((___temp&~___SCMOBJ_MASK(0x0000ffff,0x0000ffff))!=0)<<4))-___TB)))
#else
#define ___SCMOBJ_MASK(x,y)((___CAST(___SCMOBJ,x)<<32)|y)
#define ___BITCOUNT_TEMP() \
(___temp=((___temp)&___SCMOBJ_MASK(0x55555555,0x55555555))+ \
         (((___temp)>>1)&___SCMOBJ_MASK(0x55555555,0x55555555)), \
 ___temp=(___temp&___SCMOBJ_MASK(0x33333333,0x33333333))+ \
         ((___temp>>2)&___SCMOBJ_MASK(0x33333333,0x33333333)), \
 ___temp=(___temp&___SCMOBJ_MASK(0x0f0f0f0f,0x0f0f0f0f))+ \
         ((___temp>>4)&___SCMOBJ_MASK(0x0f0f0f0f,0x0f0f0f0f)), \
 ___temp=___temp+(___temp>>8), \
 ___temp=___temp+(___temp>>16), \
 ___temp=___temp+(___temp>>32), \
 ___FIX(___temp&0xff))
#define ___FIXLENGTH(x) \
(((___temp=___INT(x))<0)&&(___temp=~___temp), \
 ___temp|=(___temp>>1), \
 ___temp|=(___temp>>2), \
 ___temp|=(___temp>>4), \
 ___temp|=(___temp>>8), \
 ___temp|=(___temp>>16), \
 ___temp|=(___temp>>32), \
 ___BITCOUNT_TEMP())
#define ___FIXFIRSTBITSET(x) \
(((___temp=(x))==0) \
 ?___FIX(-1) \
 :(___temp=(___temp&-___temp), \
   ___FIX((((___temp&~___SCMOBJ_MASK(0x55555555,0x55555555))!=0)| \
           (((___temp&~___SCMOBJ_MASK(0x33333333,0x33333333))!=0)<<1)| \
           (((___temp&~___SCMOBJ_MASK(0x0f0f0f0f,0x0f0f0f0f))!=0)<<2)| \
           (((___temp&~___SCMOBJ_MASK(0x00ff00ff,0x00ff00ff))!=0)<<3)| \
           (((___temp&~___SCMOBJ_MASK(0x0000ffff,0x0000ffff))!=0)<<4)| \
           (((___temp&~___SCMOBJ_MASK(0x00000000,0xffffffff))!=0)<<5))-___TB)))
#endif
#define ___FIXBITCOUNT(x) \
((((___temp=___INT(x))<0)&&(___temp=~___temp)),___BITCOUNT_TEMP())
#define ___FIXBITSETP(x,y)((y)&(___CAST(___SCMOBJ,1)<<(___INT(x)+___TB)))

#define ___FIXASH(x,y)((y)<0?___FIXASHR(x,(y)>=___FIX(-___FIX_WIDTH)?-(y):___FIX(___FIX_WIDTH)):___FIXASHL(x,(y)<=___FIX(___FIX_WIDTH)?(y):___FIX(___FIX_WIDTH)))
#define ___FIXASHP(x,y)((y)<0?___FIXASHR(x,(y)>=___FIX(-___FIX_WIDTH)?-(y):___FIX(___FIX_WIDTH)):___FIXASHLP2(x,(y)<=___FIX(___FIX_WIDTH)?(y):___FIX(___FIX_WIDTH)))
#define ___FIXASHL(x,y)((x)<<___INT(y))
#define ___FIXASHLP(x,y)((y)>=___FIX(0)?___FIXASHLP2(x,(y)<=___FIX(___FIX_WIDTH)?(y):___FIX(___FIX_WIDTH)):___FAL)
#define ___FIXASHLP2(x,y)((x)==((___temp=___FIXASHL(x,y))>>___INT(y))?___temp:___FAL)
#define ___FIXASHR(x,y)(((x)>>___INT(y))&~___TMASK)
#define ___FIXASHRP(x,y)((y)>=___FIX(0)?___FIXASHR(x,(y)<=___FIX(___FIX_WIDTH)?(y):___FIX(___FIX_WIDTH)):___FAL)
#define ___FIXLSHR(x,y)((___WORD)(((unsigned ___WORD)(x)>>___INT(y))&~___TMASK))
#define ___FIXLSHRP(x,y)((y)>=___FIX(0)?___FIXLSHR(x,(y)<=___FIX(___FIX_WIDTH)?(y):___FIX(___FIX_WIDTH)):___FAL)
#define ___FIXTOCHR(x)(((x)&~___TMASK)+___tSPECIAL)
#define ___FIXFROMCHR(x)((x)&~___TMASK)

/* IFJUMP-able operations */

#define ___FIXZEROP(x)((x)==0)
#define ___FIXPOSITIVEP(x)((x)>0)
#define ___FIXNEGATIVEP(x)((x)<0)
#define ___FIXODDP(x)((x)&___FIX(1))
#define ___FIXEVENP(x)!((x)&___FIX(1))
#define ___FIXEQ(x,y)((x)==(y))
#define ___FIXLT(x,y)((x)<(y))
#define ___FIXGT(x,y)((x)>(y))
#define ___FIXLE(x,y)((x)<=(y))
#define ___FIXGE(x,y)((x)>=(y))

/* APPLY-able operations */

#define ___F64TOFIX(x)___FIX(x)
#define ___F64FROMFIX(x)___INT(x)
#define ___F64_0 0.0
#define ___F64POS(x)x
#define ___F64MAX(x,y)(___F64NANP(x)?x:(((x)>(y))?(x):(y)))
#define ___F64MIN(x,y)(___F64NANP(x)?x:(((x)<(y))?(x):(y)))
#define ___F64ADD(x,y)((x)+(y))
#define ___F64_1 1.0
#define ___F64MUL(x,y)((x)*(y))
#define ___F64SQUARE(x)((x)*(x))
#define ___F64NEG(x)(-(x))
#define ___F64SUB(x,y)((x)-(y))
#define ___F64INV(x)(1.0/(x))
#define ___F64DIV(x,y)((x)/(y))
#define ___F64ABS(x)___CLIBEXT(fabs)(x)
#define ___F64FLOOR(x)___CLIBEXT(floor)(x)
#define ___F64CEILING(x)___CLIBEXT(ceil)(x)
#define ___F64TRUNCATE(x)___EXT(___trunc)(x)
#define ___F64ROUND(x)___EXT(___round)(x)
#ifdef ___HAVE_GOOD_SCALBN
#define ___F64SCALBN(x,n)___CLIBEXT(scalbn)(x,___INT(n))
#else
#define ___F64SCALBN(x,n)___EXT(___scalbn)(x,___INT(n))
#endif
#ifdef ___HAVE_GOOD_ILOGB
#define ___F64ILOGB(x)___FIX(___CLIBEXT(ilogb)(x))
#else
#define ___F64ILOGB(x)___FIX(___EXT(___ilogb)(x))
#endif
#define ___F64EXP(x)___CLIBEXT(exp)(x)
#ifdef ___HAVE_GOOD_EXPM1
#define ___F64EXPM1(x)___CLIBEXT(expm1)(x)
#else
#define ___F64EXPM1(x)___EXT(___expm1)(x)
#endif
#define ___F64LOG(x)___CLIBEXT(log)(x)
#ifdef ___HAVE_GOOD_LOG1P
#define ___F64LOG1P(x)___CLIBEXT(log1p)(x)
#else
#define ___F64LOG1P(x)___EXT(___log1p)(x)
#endif
#define ___F64SIN(x)___CLIBEXT(sin)(x)
#define ___F64COS(x)___CLIBEXT(cos)(x)
#define ___F64TAN(x)___CLIBEXT(tan)(x)
#define ___F64ASIN(x)___CLIBEXT(asin)(x)
#define ___F64ACOS(x)___CLIBEXT(acos)(x)
#define ___F64ATAN(x)___CLIBEXT(atan)(x)
#ifdef ___HAVE_GOOD_SINH
#define ___F64SINH(x)___CLIBEXT(sinh)(x)
#else
#define ___F64SINH(x)___EXT(___sinh)(x)
#endif
#ifdef ___HAVE_GOOD_COSH
#define ___F64COSH(x)___CLIBEXT(cosh)(x)
#else
#define ___F64COSH(x)___EXT(___cosh)(x)
#endif
#ifdef ___HAVE_GOOD_TANH
#define ___F64TANH(x)___CLIBEXT(tanh)(x)
#else
#define ___F64TANH(x)___EXT(___tanh)(x)
#endif
#ifdef ___HAVE_GOOD_ASINH
#define ___F64ASINH(x)___CLIBEXT(asinh)(x)
#else
#define ___F64ASINH(x)___EXT(___asinh)(x)
#endif
#ifdef ___HAVE_GOOD_ACOSH
#define ___F64ACOSH(x)___CLIBEXT(acosh)(x)
#else
#define ___F64ACOSH(x)___EXT(___acosh)(x)
#endif
#ifdef ___HAVE_GOOD_ATANH
#define ___F64ATANH(x)___CLIBEXT(atanh)(x)
#else
#define ___F64ATANH(x)___EXT(___atanh)(x)
#endif
#ifdef ___HAVE_GOOD_ATAN2
#define ___F64ATAN2(y,x)___CLIBEXT(atan2)(y,x)
#else
#define ___F64ATAN2(y,x)___EXT(___atan2)(y,x)
#endif
#ifdef ___HAVE_GOOD_POW
#define ___F64EXPT(x,y)___CLIBEXT(pow)(x,y)
#else
#define ___F64EXPT(x,y)___EXT(___pow)(x,y)
#endif
#define ___F64SQRT(x)___CLIBEXT(sqrt)(x)
#define ___F64COPYSIGN(x,y)___EXT(___copysign)(x,y)

/* IFJUMP-able operations */

#define ___F64INTEGERP(x)(!___F64INFINITEP(x) && (x)==___F64FLOOR(x))
#define ___F64ZEROP(x)((x)==0.0)
#define ___F64POSITIVEP(x)((x)>0.0)
#define ___F64NEGATIVEP(x)((x)<0.0)
#define ___F64ODDP(x)(___F64INTEGERP(x) && (x)!=2.0*___F64FLOOR((x)*0.5))
#define ___F64EVENP(x)(___F64INTEGERP(x) && (x)==2.0*___F64FLOOR((x)*0.5))
#define ___F64FINITEP(x)___EXT(___isfinite)(x)
#define ___F64INFINITEP(x)((x)!=0.0 && (x)==2.0*(x))
#ifdef ___USE_ISNAN
#define ___F64NANP(x)___EXT(___isnan)(x)
#else
#define ___F64NANP(x)((x)!=(x))
#endif
#if ___SCMOBJ_WIDTH == 32
#define ___F64FROMFIXEXACTP(x)(1)
#else
#define ___F64FROMFIXEXACTP(x)(___INT(x)==(___WORD)(___F64)___INT(x))
#endif
#define ___F64EQ(x,y)((x)==(y))
#define ___F64LT(x,y)((x)<(y))
#define ___F64GT(x,y)((x)>(y))
#define ___F64LE(x,y)((x)<=(y))
#define ___F64GE(x,y)((x)>=(y))

/* IFJUMP-able operations */

#define ___CHAREQP(x,y)((x)==(y))
#define ___CHARLTP(x,y)((x)<(y))
#define ___CHARGTP(x,y)((x)>(y))
#define ___CHARLEP(x,y)((x)<=(y))
#define ___CHARGEP(x,y)((x)>=(y))

#define ___CHARALPHABETICP(x)___EXT(___iswalpha(___INT(x)))
#define ___CHARNUMERICP(x)___EXT(___iswdigit(___INT(x)))
#define ___CHARWHITESPACEP(x)___EXT(___iswspace(___INT(x)))
#define ___CHARUPPERCASEP(x)___EXT(___iswupper(___INT(x)))
#define ___CHARLOWERCASEP(x)___EXT(___iswlower(___INT(x)))
#define ___CHARUPCASE(x)___CHR(___EXT(___towupper(___INT(x))))
#define ___CHARDOWNCASE(x)___CHR(___EXT(___towlower(___INT(x))))

/* APPLY-able operations */

#define ___PAIR_SIZE 2
#define ___PAIR_CDR_OFS 0
#define ___PAIR_CAR_OFS 1

#define ___PAIR_CAR(obj)(*(___BODY_AS(obj,___tPAIR)+___PAIR_CAR_OFS))
#define ___PAIR_CDR(obj)(*(___BODY_AS(obj,___tPAIR)+___PAIR_CDR_OFS))

#define ___ALLOC_PAIR_EXPR(x,y)(___hp[0]=___MAKE_HD_WORDS(___PAIR_SIZE,___sPAIR), \
___hp[___PAIR_CAR_OFS+1]=x,___hp[___PAIR_CDR_OFS+1]=y,___ALLOC(___PAIR_SIZE+1))
#define ___ALLOC_PAIR(x,y){___hp[0]=___MAKE_HD_WORDS(___PAIR_SIZE,___sPAIR); \
___hp[___PAIR_CAR_OFS+1]=x;___hp[___PAIR_CDR_OFS+1]=y;___ALLOC(___PAIR_SIZE+1);}
#define ___CONS(x,y)(___ALLOC_PAIR_EXPR(x,y),___TAG((___hp-___PAIR_SIZE-1),___tPAIR))

#define ___SETCAR(obj,car)___PAIR_CAR(obj)=car;
#define ___SETCDR(obj,cdr)___PAIR_CDR(obj)=cdr;
#define ___CAR(obj)___PAIR_CAR(obj)
#define ___CDR(obj)___PAIR_CDR(obj)
#define ___CAAR(obj)___CAR(___CAR(obj))
#define ___CADR(obj)___CAR(___CDR(obj))
#define ___CDAR(obj)___CDR(___CAR(obj))
#define ___CDDR(obj)___CDR(___CDR(obj))
#define ___CAAAR(obj)___CAR(___CAR(___CAR(obj)))
#define ___CAADR(obj)___CAR(___CAR(___CDR(obj)))
#define ___CADAR(obj)___CAR(___CDR(___CAR(obj)))
#define ___CADDR(obj)___CAR(___CDR(___CDR(obj)))
#define ___CDAAR(obj)___CDR(___CAR(___CAR(obj)))
#define ___CDADR(obj)___CDR(___CAR(___CDR(obj)))
#define ___CDDAR(obj)___CDR(___CDR(___CAR(obj)))
#define ___CDDDR(obj)___CDR(___CDR(___CDR(obj)))
#define ___CAAAAR(obj)___CAR(___CAR(___CAR(___CAR(obj))))
#define ___CAAADR(obj)___CAR(___CAR(___CAR(___CDR(obj))))
#define ___CAADAR(obj)___CAR(___CAR(___CDR(___CAR(obj))))
#define ___CAADDR(obj)___CAR(___CAR(___CDR(___CDR(obj))))
#define ___CADAAR(obj)___CAR(___CDR(___CAR(___CAR(obj))))
#define ___CADADR(obj)___CAR(___CDR(___CAR(___CDR(obj))))
#define ___CADDAR(obj)___CAR(___CDR(___CDR(___CAR(obj))))
#define ___CADDDR(obj)___CAR(___CDR(___CDR(___CDR(obj))))
#define ___CDAAAR(obj)___CDR(___CAR(___CAR(___CAR(obj))))
#define ___CDAADR(obj)___CDR(___CAR(___CAR(___CDR(obj))))
#define ___CDADAR(obj)___CDR(___CAR(___CDR(___CAR(obj))))
#define ___CDADDR(obj)___CDR(___CAR(___CDR(___CDR(obj))))
#define ___CDDAAR(obj)___CDR(___CDR(___CAR(___CAR(obj))))
#define ___CDDADR(obj)___CDR(___CDR(___CAR(___CDR(obj))))
#define ___CDDDAR(obj)___CDR(___CDR(___CDR(___CAR(obj))))
#define ___CDDDDR(obj)___CDR(___CDR(___CDR(___CDR(obj))))

/* APPLY-able operations */

#define ___BOX(x)(___ALLOC(2),___hp[-2]=___MAKE_HD_WORDS(1,___sBOXVALUES), \
___hp[-1]=x,___TAG((___hp-2),___tSUBTYPED))
#define ___UNBOX(x)___BODY_AS(x,___tSUBTYPED)[0]
#define ___SETBOX(x,y)___BODY_AS(x,___tSUBTYPED)[0]=y;

#define ___VECTORLENGTH(x)___FIX(___HD_FIELDS(___HEADER(x)))
#define ___VECTORREF(x,y)*(___WORD*)(((___WORD)___BODY_AS(x,___tSUBTYPED))+((y)<<(___LWS-___TB)))
#define ___VECTORSET(x,y,z)*(___WORD*)(((___WORD)___BODY_AS(x,___tSUBTYPED))+((y)<<(___LWS-___TB)))=z;
#define ___VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+___LWS));

#define ___STRINGLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>___LCS))
#define ___STRINGREF(x,y)___CHR(___CS_SELECT( \
___FETCH_U8(___BODY_AS(x,___tSUBTYPED),(y)>>___TB), \
___FETCH_U16(___BODY_AS(x,___tSUBTYPED),(y)>>___TB), \
___FETCH_U32(___BODY_AS(x,___tSUBTYPED),(y)>>___TB)))
#define ___STRINGSET(x,y,z)___CS_SELECT( \
___STORE_U8(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___INT(z)), \
___STORE_U16(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___INT(z)), \
___STORE_U32(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___INT(z)));
#define ___STRINGSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+___LCS));

#define ___S8VECTORLENGTH(x)___FIX(___HD_BYTES(___HEADER(x)))
#define ___S8VECTORREF(x,y) \
___FIX(___FETCH_S8(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___S8VECTORSET(x,y,z) \
___STORE_S8(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___INT(z));
#define ___S8VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB));

#define ___U8VECTORLENGTH(x)___FIX(___HD_BYTES(___HEADER(x)))
#define ___U8VECTORREF(x,y) \
___FIX(___FETCH_U8(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___U8VECTORSET(x,y,z) \
___STORE_U8(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___INT(z));
#define ___U8VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB));

#define ___S16VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>1))
#define ___S16VECTORREF(x,y) \
___FIX(___FETCH_S16(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___S16VECTORSET(x,y,z) \
___STORE_S16(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___INT(z));
#define ___S16VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+1));

#define ___U16VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>1))
#define ___U16VECTORREF(x,y) \
___FIX(___FETCH_U16(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___U16VECTORSET(x,y,z) \
___STORE_U16(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___INT(z));
#define ___U16VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+1));

#define ___S32VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>2))
#define ___S32VECTORREF(x,y) \
___S32BOX(___FETCH_S32(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___S32VECTORSET(x,y,z) \
___STORE_S32(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___S32UNBOX(z));
#define ___S32VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+2));

#define ___U32VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>2))
#define ___U32VECTORREF(x,y) \
___U32BOX(___FETCH_U32(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___U32VECTORSET(x,y,z) \
___STORE_U32(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___U32UNBOX(z));
#define ___U32VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+2));

#define ___S64VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>3))
#define ___S64VECTORREF(x,y) \
___S64BOX(___FETCH_S64(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___S64VECTORSET(x,y,z) \
___STORE_S64(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___S64UNBOX(z));
#define ___S64VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+3));

#define ___U64VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>3))
#define ___U64VECTORREF(x,y) \
___U64BOX(___FETCH_U64(___BODY_AS(x,___tSUBTYPED),(y)>>___TB))
#define ___U64VECTORSET(x,y,z) \
___STORE_U64(___BODY_AS(x,___tSUBTYPED),(y)>>___TB,___U64UNBOX(z));
#define ___U64VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+3));

#define ___F32VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>2))
#ifdef ___F32
#define ___F32VECTORREF(x,y)*(___F32*)(((___WORD)___BODY_AS(x,___tSUBTYPED))+((y)<<(2-___TB)))
#define ___F32VECTORSET(x,y,z)*(___F32*)(((___WORD)___BODY_AS(x,___tSUBTYPED))+((y)<<(2-___TB)))=z;
#else
#define ___F32VECTORREF(x,y)0.0
#define ___F32VECTORSET(x,y,z);
#endif
#define ___F32VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+2));

#define ___F64VECTORLENGTH(x)___FIX((___HD_BYTES(___HEADER(x))>>3))
#define ___F64VECTORREF(x,y)*(___F64*)(((___WORD)___BODY_AS(x,___tSUBTYPED))+((y)<<(3-___TB)))
#define ___F64VECTORSET(x,y,z)*(___F64*)(((___WORD)___BODY_AS(x,___tSUBTYPED))+((y)<<(3-___TB)))=z;
#define ___F64VECTORSHRINK(x,y)___temp=x;___HEADER(___temp)=(___HEADER(___temp)&~___LMASK)+((y)<<(___LF-___TB+3));

#define ___TYPEID(x)___VECTORREF(x,___FIX(1))
#define ___TYPENAME(x)___VECTORREF(x,___FIX(2))
#define ___TYPEFLAGS(x)___VECTORREF(x,___FIX(3))
#define ___TYPESUPER(x)___VECTORREF(x,___FIX(4))
#define ___TYPEFIELDS(x)___VECTORREF(x,___FIX(5))

#define ___STRUCTURETYPE(x)___VECTORREF(x,___FIX(0))
#define ___STRUCTURETYPESET(x,y)___VECTORSET(x,___FIX(0),y)
#define ___STRUCTUREDIOP(x,typeid)(___TESTSUBTYPE(x,___sSTRUCTURE)&&___TYPEID(___STRUCTURETYPE(___temp))==(typeid))
#define ___UNCHECKEDSTRUCTUREREF(x,y,type,proc)___VECTORREF(x,y)
#define ___UNCHECKEDSTRUCTURESET(x,y,z,type,proc)___VECTORSET(x,z,y)

#define ___CLOSURELENGTH(x)___FIX(___HD_FIELDS(___HEADER(x)))
#define ___CLOSURECODE(x)___CLO(x,0)
#define ___CLOSUREREF(x,y)___CLO(x,___INT(y))
#define ___CLOSURESET(x,y,z)___SET_CLO(x,___INT(y),z)

#define ___GLOBALVARSTRUCT(gv)___CAST(___glo_struct*,___FIELD(gv,___SYMBOL_GLOBAL))
#define ___GLOBALVARREF(gv)___GLOCELL(___GLOBALVARSTRUCT(gv)->val)
#define ___GLOBALVARPRIMREF(gv)___PRMCELL(___GLOBALVARSTRUCT(gv)->prm)
#define ___GLOBALVARSET(gv,x)___GLOCELL(___GLOBALVARSTRUCT(gv)->val) = x;
#define ___GLOBALVARPRIMSET(gv,x)___PRMCELL(___GLOBALVARSTRUCT(gv)->prm) = x;

#define ___MAKEPROMISE(x) \
(___ALLOC(___PROMISE_SIZE+1), \
___hp[-3]=___MAKE_HD_WORDS(___PROMISE_SIZE,___sPROMISE), \
___hp[-2]=x, ___hp[-1]=___TAG((___hp-___PROMISE_SIZE-1),___tSUBTYPED))

#define ___MAKEWILL(testator,action) \
(___hp[0]=___MAKE_HD_WORDS(___WILL_SIZE,___sWEAK), \
___hp[1]=___ps->nonexecutable_wills, \
___hp[2]=testator, \
___hp[3]=action, \
___ps->nonexecutable_wills=___TAG(___hp,0), \
___ALLOC(___WILL_SIZE+1), \
___TAG((___hp-___WILL_SIZE-1),___tSUBTYPED))
#define ___WILLTESTATOR(x)___BODY_AS(x,___tSUBTYPED)[1]

#define ___EXECUTABLE_WILL        1
#define ___UNMARKED_TESTATOR_WILL 2

#define ___GCHASHTABLEREF(x,y)___EXT(___gc_hash_table_ref)(x,y)
#define ___GCHASHTABLESET(x,y,z)___EXT(___gc_hash_table_set)(x,y,z)
#define ___GCHASHTABLEREHASH(x,y)___EXT(___gc_hash_table_rehash)(x,y)

#define ___GCHASHTABLE_HASH1(obj,mod) ((((obj)>>___TB)&___MAX_FIX)%(mod))
#define ___GCHASHTABLE_HASH2(obj,mod) (((((obj)>>___TB)&___MAX_FIX)%((mod)-1))+1)

#define ___GCHASHTABLE_FLAG_WEAK_KEYS      1
#define ___GCHASHTABLE_FLAG_WEAK_VALS      2
#define ___GCHASHTABLE_FLAG_KEY_MOVED      4
#define ___GCHASHTABLE_FLAG_ENTRY_DELETED  8
#define ___GCHASHTABLE_FLAG_MEM_ALLOC_KEYS 16
#define ___GCHASHTABLE_FLAG_NEED_REHASH    32

#define ___GCHASHTABLE_NEXT      0
#define ___GCHASHTABLE_FLAGS     1
#define ___GCHASHTABLE_COUNT     2
#define ___GCHASHTABLE_MIN_COUNT 3
#define ___GCHASHTABLE_FREE      4
#define ___GCHASHTABLE_KEY0      5
#define ___GCHASHTABLE_VAL0      6

#define ___CURRENTTHREAD ___ps->current_thread
#define ___RUNQUEUE ___ps->run_queue

#define ___THREAD_SAVE \
if (___R0 == ___GSTATE->handler_break) \
  frame = ___STK(-___BREAK_FRAME_NEXT); \
else \
  { \
    ___SET_STK(-___FRAME_STACK_RA,___R0) \
    ___R0 = ___GSTATE->handler_break; \
    frame = ___CAST(___SCMOBJ,___fp); \
    ___ADJFP(___BREAK_FRAME_SPACE) \
    ___SET_STK(-___BREAK_FRAME_NEXT,frame) \
    ___ps->stack_break = ___fp; \
  } \
thread = ___ps->current_thread; \
___FIELD(___FIELD(thread,___THREAD_CONT),___CONTINUATION_FRAME) = frame;

#define ___JUMP_THREAD_SAVE1(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ thread; \
  ___SCMOBJ frame; \
  ___POP_ARGS1(proc) \
  ___THREAD_SAVE \
  ___PUSH_ARGS1(thread) \
  jump(___SET_NARGS(1),proc) \
}

#define ___JUMP_THREAD_SAVE2(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ thread; \
  ___SCMOBJ frame; \
  ___POP_ARGS2(proc,arg1) \
  ___THREAD_SAVE \
  ___PUSH_ARGS2(thread,arg1) \
  jump(___SET_NARGS(2),proc) \
}

#define ___JUMP_THREAD_SAVE3(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___SCMOBJ thread; \
  ___SCMOBJ frame; \
  ___POP_ARGS3(proc,arg1,arg2) \
  ___THREAD_SAVE \
  ___PUSH_ARGS3(thread,arg1,arg2) \
  jump(___SET_NARGS(3),proc) \
}

#define ___JUMP_THREAD_SAVE4(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___SCMOBJ arg3; \
  ___SCMOBJ thread; \
  ___SCMOBJ frame; \
  ___POP_ARGS4(proc,arg1,arg2,arg3) \
  ___THREAD_SAVE \
  ___PUSH_ARGS4(thread,arg1,arg2,arg3) \
  jump(___SET_NARGS(4),proc) \
}

#define ___THREAD_RESTORE \
{ ___SCMOBJ cont = ___FIELD(thread,___THREAD_CONT); \
  ___fp = ___ps->stack_break; \
  ___SET_STK(-___BREAK_FRAME_NEXT,___FIELD(cont,___CONTINUATION_FRAME)) \
  ___FIELD(cont,___CONTINUATION_FRAME) = ___FIX(0); \
  ___INTERRUPT_MASK_SET(___FIELD(___FIELD(thread,___THREAD_DENV),___DENV_INTERRUPT_MASK)); \
  ___ps->current_thread = thread; \
  ___SET_R0(___GSTATE->handler_break) \
}

#define ___JUMP_THREAD_RESTORE2(jump) \
{ ___SCMOBJ thread; \
  ___SCMOBJ proc; \
  ___POP_ARGS2(thread,proc) \
  ___THREAD_RESTORE \
  jump(___SET_NARGS(0),proc) \
}

#define ___JUMP_THREAD_RESTORE3(jump) \
{ ___SCMOBJ thread; \
  ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___POP_ARGS3(thread,proc,arg1) \
  ___THREAD_RESTORE \
  ___PUSH_ARGS1(arg1) \
  jump(___SET_NARGS(1),proc) \
}

#define ___JUMP_THREAD_RESTORE4(jump) \
{ ___SCMOBJ thread; \
  ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___POP_ARGS4(thread,proc,arg1,arg2) \
  ___THREAD_RESTORE \
  ___PUSH_ARGS2(arg1,arg2) \
  jump(___SET_NARGS(2),proc) \
}

#define ___JUMP_THREAD_RESTORE5(jump) \
{ ___SCMOBJ thread; \
  ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___SCMOBJ arg3; \
  ___POP_ARGS5(thread,proc,arg1,arg2,arg3) \
  ___THREAD_RESTORE \
  ___PUSH_ARGS3(arg1,arg2,arg3) \
  jump(___SET_NARGS(3),proc) \
}

#define ___FRAME_OVERHEAD(n) (___FRAME_SPACE(n)-(n))
#define ___RETI_RA (-___FRAME_OVERHEAD(___NB_GVM_REGS+1))
#define ___FRAME_RETI_RA (1-___FRAME_RESERVE-___RETI_RA)

#define ___SYMKEY_NAME  0
#define ___SYMKEY_HASH  1
#define ___SYMKEY_NEXT  2
#define ___SYMBOL_GLOBAL 3
#define ___PROMISE_THUNK  0
#define ___PROMISE_RESULT 1
#define ___CONTINUATION_FRAME 0
#define ___CONTINUATION_DENV  1
#define ___THREAD_CONT        19
#define ___THREAD_DENV        20
#define ___THREAD_DENV_CACHE1 21
#define ___THREAD_DENV_CACHE2 22
#define ___THREAD_DENV_CACHE3 23
#define ___ENV_NAME_VAL 0
#define ___ENV_LEFT     1
#define ___ENV_RIGHT    2
#define ___DENV_LOCAL              0
#define ___DENV_DYNWIND            1
#define ___DENV_INTERRUPT_MASK     2
#define ___DENV_DEBUGGING_SETTINGS 3
#define ___DENV_EXCEPTION_HANDLER  4
#define ___DENV_INPUT_PORT         5
#define ___DENV_OUTPUT_PORT        6

#define ___FRAME_EXTRA_SLOTS 1
#define ___FRAME_STACK_RA 0
#define ___FRAME_RA 0

#define ___FRAME_STORE_RA(ra) \
if (___fp != ___ps->stack_break) \
  ___SET_STK(-___FRAME_STACK_RA,ra)

#define ___FRAME_FETCH_RA \
((___fp != ___ps->stack_break) \
? ___STK(-___FRAME_STACK_RA) \
: ___GSTATE->handler_break)

#define ___CONTINUATION_CAPTURE \
if (___R0 == ___GSTATE->handler_break) \
  frame = ___STK(-___BREAK_FRAME_NEXT); \
else \
  { \
    ___SET_STK(-___FRAME_STACK_RA,___R0) \
    ___R0 = ___GSTATE->handler_break; \
    frame = ___CAST(___SCMOBJ,___fp); \
  } \
___ADJFP(___ROUND_TO_MULT(___SUBTYPED_OVERHEAD+___CONTINUATION_SIZE,___FRAME_ALIGN)) \
___SET_STK(0,___MAKE_HD_WORDS(___CONTINUATION_SIZE,___sCONTINUATION)) \
___SET_STK(-1,frame) \
___SET_STK(-2,___FIELD(___ps->current_thread,___THREAD_DENV)) \
cont = ___TAG(&___STK(0),___tSUBTYPED); \
___ADJFP(___BREAK_FRAME_SPACE) \
___SET_STK(-___BREAK_FRAME_NEXT,frame) \
___ps->stack_break = ___fp;

#define ___JUMP_CONTINUATION_CAPTURE1(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ frame; \
  ___SCMOBJ cont; \
  ___POP_ARGS1(proc) \
  ___CONTINUATION_CAPTURE \
  ___PUSH_ARGS1(cont); \
  jump(___SET_NARGS(1),proc) \
}

#define ___JUMP_CONTINUATION_CAPTURE2(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ frame; \
  ___SCMOBJ cont; \
  ___POP_ARGS2(proc,arg1) \
  ___CONTINUATION_CAPTURE \
  ___PUSH_ARGS2(cont,arg1); \
  jump(___SET_NARGS(2),proc) \
}

#define ___JUMP_CONTINUATION_CAPTURE3(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___SCMOBJ frame; \
  ___SCMOBJ cont; \
  ___POP_ARGS3(proc,arg1,arg2) \
  ___CONTINUATION_CAPTURE \
  ___PUSH_ARGS3(cont,arg1,arg2); \
  jump(___SET_NARGS(3),proc) \
}

#define ___JUMP_CONTINUATION_CAPTURE4(jump) \
{ ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___SCMOBJ arg3; \
  ___SCMOBJ frame; \
  ___SCMOBJ cont; \
  ___POP_ARGS4(proc,arg1,arg2,arg3) \
  ___CONTINUATION_CAPTURE \
  ___PUSH_ARGS4(cont,arg1,arg2,arg3); \
  jump(___SET_NARGS(4),proc) \
}

#define ___CONTINUATION_GRAFT_NO_WINDING \
___fp = ___ps->stack_break; \
___SET_STK(-___BREAK_FRAME_NEXT,___FIELD(cont,___CONTINUATION_FRAME)) \
temp = ___FIELD(cont,___CONTINUATION_DENV); \
thread = ___ps->current_thread; \
___FIELD(thread,___THREAD_DENV) = temp; \
temp = ___FIELD(___FIELD(temp,___DENV_LOCAL),___ENV_NAME_VAL); \
___FIELD(thread,___THREAD_DENV_CACHE1) = temp; \
___FIELD(thread,___THREAD_DENV_CACHE2) = temp; \
___FIELD(thread,___THREAD_DENV_CACHE3) = temp; \
___SET_R0(___GSTATE->handler_break)

#define ___JUMP_CONTINUATION_GRAFT_NO_WINDING2(jump) \
{ ___SCMOBJ cont; \
  ___SCMOBJ proc; \
  ___SCMOBJ temp; \
  ___SCMOBJ thread; \
  ___POP_ARGS2(cont,proc) \
  ___CONTINUATION_GRAFT_NO_WINDING \
  jump(___SET_NARGS(0),proc) \
}

#define ___JUMP_CONTINUATION_GRAFT_NO_WINDING3(jump) \
{ ___SCMOBJ cont; \
  ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ temp; \
  ___SCMOBJ thread; \
  ___POP_ARGS3(cont,proc,arg1) \
  ___CONTINUATION_GRAFT_NO_WINDING \
  ___PUSH_ARGS1(arg1) \
  jump(___SET_NARGS(1),proc) \
}

#define ___JUMP_CONTINUATION_GRAFT_NO_WINDING4(jump) \
{ ___SCMOBJ cont; \
  ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___SCMOBJ temp; \
  ___SCMOBJ thread; \
  ___POP_ARGS4(cont,proc,arg1,arg2) \
  ___CONTINUATION_GRAFT_NO_WINDING \
  ___PUSH_ARGS2(arg1,arg2) \
  jump(___SET_NARGS(2),proc) \
}

#define ___JUMP_CONTINUATION_GRAFT_NO_WINDING5(jump) \
{ ___SCMOBJ cont; \
  ___SCMOBJ proc; \
  ___SCMOBJ arg1; \
  ___SCMOBJ arg2; \
  ___SCMOBJ arg3; \
  ___SCMOBJ temp; \
  ___SCMOBJ thread; \
  ___POP_ARGS5(cont,proc,arg1,arg2,arg3) \
  ___CONTINUATION_GRAFT_NO_WINDING \
  ___PUSH_ARGS3(arg1,arg2,arg3) \
  jump(___SET_NARGS(3),proc) \
}

#define ___JUMP_CONTINUATION_RETURN_NO_WINDING2(jump) \
{ ___SCMOBJ cont; \
  ___SCMOBJ result; \
  ___SCMOBJ temp; \
  ___SCMOBJ thread; \
  ___POP_ARGS2(cont,result) \
  ___SET_R1(result) \
  ___fp = ___ps->stack_break; \
  ___SET_STK(-___BREAK_FRAME_NEXT,___FIELD(cont,___CONTINUATION_FRAME)) \
  temp = ___FIELD(cont,___CONTINUATION_DENV); \
  thread = ___ps->current_thread; \
  ___FIELD(thread,___THREAD_DENV) = temp; \
  temp = ___FIELD(___FIELD(temp,___DENV_LOCAL),___ENV_NAME_VAL); \
  ___FIELD(thread,___THREAD_DENV_CACHE1) = temp; \
  ___FIELD(thread,___THREAD_DENV_CACHE2) = temp; \
  ___FIELD(thread,___THREAD_DENV_CACHE3) = temp; \
  ___JUMPPRM(___NOTHING,___GSTATE->handler_break) \
}

/*---------------------------------------------------------------------------*/

/* Stack manipulation */

#define ___FP_AFTER(fp1,fp2)((fp1) < (fp2))
#define ___FP_PUSH(fp,val)*--fp=(val);
#define ___FP_POP(fp)*fp++
#define ___FP_STK(fp,fpo)fp[-(fpo)]
#define ___FP_SET_STK(fp,fpo,val)fp[-(fpo)]=(val);
#define ___FP_ADJFP(fp,fpa)fp-=(fpa);

#define ___PUSH(val)___FP_PUSH(___fp,val)
#define ___POP ___FP_POP(___fp)
#define ___STK(fpo)___FP_STK(___fp,fpo)
#define ___SET_STK(fpo,val)___FP_SET_STK(___fp,fpo,val)
#define ___ADJFP(fpa)___FP_ADJFP(___fp,fpa)
#define ___PSSTK(fpo)___FP_STK(___PSFP,fpo)
#define ___PSADJFP(fpa)___FP_ADJFP(___PSFP,fpa)

#ifdef ___SINGLE_VM
#define ___GLOCELL_IN_VM(vm,x)x
#define ___GLOCELL(x)x
#else
#define ___GLOCELL_IN_VM(vm,x)vm->glos[x]
#define ___GLOCELL(x)___GLOCELL_IN_VM(___VMSTATE_FROM_PSTATE(___ps),x)
#endif

#define ___PRMCELL(x)x

#define ___PRM(i,glo)___PRMCELL(___GLOSTRUCT(i,glo).prm)
#define ___GLO(i,glo)___GLOCELL(___GLOSTRUCT(i,glo).val)
#define ___SET_GLO(i,glo,x)___GLO(i,glo)=x;
#ifdef ___BIND_LATE
#define ___GLOSTRUCT(i,glo)(*___CAST(___glo_struct*,___glotbl[i]))
#else
#define ___GLOSTRUCT(i,glo)glo
#endif

#define ___HOST_PROC ___SM(___MH_PROC,___PH_PROC)
#define ___HOST_LBL0 ___SM(1,___PH_LBL0)

#define ___BEGIN_M_COD ___SM(___BEGIN_COD,___NOTHING)
#define ___END_M_COD ___SM(___END_COD,___NOTHING)

#define ___BEGIN_M_HLBL ___SM(___BEGIN_HLBL,___NOTHING)
#define ___DEF_M_HLBL_INTRO ___SM(___DEF_HLBL_INTRO,___NOTHING)
#define ___DEF_M_HLBL(id)___SM(___DEF_HLBL(id),___NOTHING)
#define ___END_M_HLBL ___SM(___END_HLBL,___NOTHING)

#define ___BEGIN_M_SW ___SM(___BEGIN_SW,___NOTHING)
#define ___END_M_SW ___SM(___END_SW,___NOTHING)

#define ___BEGIN_P_COD ___SM(___NOTHING,___BEGIN_COD)
#define ___END_P_COD ___SM(___NOTHING,___END_COD)

#define ___BEGIN_P_HLBL ___SM(___NOTHING,___BEGIN_HLBL)
#define ___DEF_P_HLBL_INTRO ___SM(___NOTHING,___DEF_HLBL_INTRO)
#define ___DEF_P_HLBL(id)___SM(___NOTHING,___DEF_HLBL(id))
#define ___END_P_HLBL ___SM(___NOTHING,___END_HLBL)

#define ___BEGIN_P_SW ___SM(___NOTHING,___BEGIN_SW)
#define ___END_P_SW ___SM(___NOTHING,___END_SW)

#define ___D_ALL ___SM(___MD_ALL,___PD_ALL)
#define ___R_ALL ___SM(___MR_ALL,___PR_ALL)
#define ___W_ALL ___SM(___MW_ALL,___PW_ALL)

#define ___BEGIN_COD \
___HIDDEN ___WORD ___HOST_PROC ___P((___processor_state ___ps),(___ps) \
___processor_state ___ps;) { \
register ___WORD ___pc, ___start, ___temp; \
register ___S32 ___s32_temp; /*******************/ \
register ___U32 ___u32_temp; /*******************/ \
register ___S64 ___s64_temp; /*******************/ \
register ___U64 ___u64_temp; /*******************/ \
___D_ALL

#define ___END_COD \
___ps->pc=___pc; ___W_ALL return ___pc; }

#ifdef ___DEBUG_HOST_CHANGES
#define ___REGISTER_HOST_ENTRY \
___EXT(___register_host_entry) (___PSP ___start, ___MODULE_NAME);
#else
#define ___REGISTER_HOST_ENTRY
#endif

#define ___USES_INDIRECT_GOTO 1
#define ___SETUP_FIXUP_DONE   2

#ifdef ___USE_LABEL_VALUES

#define ___MODULE_FLAGS ___USES_INDIRECT_GOTO

#define ___BEGIN_HLBL static void *___hlbltbl[]={
#define ___DEF_HLBL_INTRO 0,
#define ___DEF_HLBL(id)&&id,
#define ___END_HLBL \
0}; if (___EXPECT_FALSE(___ps == 0)) return ___CAST(___WORD,___hlbltbl);

#define ___BEGIN_SW \
___R_ALL ___start=___MLBL(___HOST_LBL0); ___pc=___ps->pc; \
___REGISTER_HOST_ENTRY \
goto *___LABEL_HOST_LABEL(___pc);

#define ___DEF_SW(n)

#ifdef ___USE_INLINE_JUMPS

#define ___END_SW \
___jumpext:

#define ___JUMP(dest) \
{___pc=dest; \
 if (___EXPECT_TRUE(___LABEL_HOST(___pc) == ___HOST_PROC)) \
   goto *___LABEL_HOST_LABEL(___pc); \
 goto ___jumpext;}

#else

#define ___END_SW \
___jump: \
if (___EXPECT_TRUE(___LABEL_HOST(___pc) == ___HOST_PROC)) \
  goto *___LABEL_HOST_LABEL(___pc); \
___jumpext:

#define ___JUMP(dest){___pc=dest;goto ___jump;}

#endif

#define ___JUMPEXT(dest){___pc=dest;goto ___jumpext;}

#else

#define ___MODULE_FLAGS 0

#define ___BEGIN_HLBL
#define ___DEF_HLBL_INTRO
#define ___DEF_HLBL(id)
#define ___END_HLBL

#define ___BEGIN_SW \
___R_ALL ___start=___MLBL(___HOST_LBL0); ___pc=___ps->pc; \
___REGISTER_HOST_ENTRY \
___jump: \
switch((___pc-=___start)/(___LS*___WS)) \
{

#define ___DEF_SW(n)case ___PH_LBL0-___HOST_LBL0+n:

#define ___END_SW \
}___pc+=___start;___jumpext:

#define ___JUMP(dest){___pc=dest;goto ___jump;}
#define ___JUMPEXT(dest){___pc=dest;goto ___jumpext;}

#endif

#define ___BEGIN_P_SLBL ___SM(___NOTHING,___BEGIN_SLBL)
#define ___DEF_P_SLBL(id)
#define ___END_P_SLBL ___SM(___NOTHING,___END_SLBL)

#define ___LS 4

#define ___PSHEAP ___ps->hp
#define ___D_HEAP register ___WORD *___hp;
#define ___R_HEAP ___hp=___PSHEAP;
#define ___W_HEAP ___PSHEAP=___hp;

#define ___PSFP ___ps->fp
#define ___D_FP register ___WORD *___fp;
#define ___R_FP ___fp=___PSFP;
#define ___W_FP ___PSFP=___fp;

/*---------------------------------------------------------------------------*/

/* GVM registers */

#ifndef ___MAX_LOCAL_GVM_REGS
#define ___MAX_LOCAL_GVM_REGS 25
#endif

#if ___NB_ARG_REGS == 0
#define ___PUSH_ARGS1(a)___PUSH(a)
#define ___POP_ARGS1(a)a = ___POP;
#define ___PUSH_ARGS2(a,b)___PUSH(a)___PUSH(b)
#define ___POP_ARGS2(a,b)b = ___POP; a = ___POP;
#define ___PUSH_ARGS3(a,b,c)___PUSH(a)___PUSH(b)___PUSH(c)
#define ___POP_ARGS3(a,b,c)c = ___POP; b = ___POP; a = ___POP;
#define ___PUSH_ARGS4(a,b,c,d)___PUSH(a)___PUSH(b)___PUSH(c)___PUSH(d)
#define ___POP_ARGS4(a,b,c,d)d = ___POP; c = ___POP; b = ___POP; a = ___POP;
#define ___PUSH_ARGS5(a,b,c,d,e)___PUSH(a)___PUSH(b)___PUSH(c)___PUSH(d)___PUSH(e)
#define ___POP_ARGS5(a,b,c,d,e)e = ___POP; d = ___POP; c = ___POP; b = ___POP; a = ___POP;
#else
#define ___PUSH_ARGS1(a)___SET_R1(a)
#define ___POP_ARGS1(a)a = ___R1;
#if ___NB_ARG_REGS == 1
#define ___PUSH_ARGS2(a,b)___PUSH(a)___SET_R1(b)
#define ___POP_ARGS2(a,b)b = ___R1; a = ___POP;
#define ___PUSH_ARGS3(a,b,c)___PUSH(a)___PUSH(b)___SET_R1(c)
#define ___POP_ARGS3(a,b,c)c = ___R1; b = ___POP; a = ___POP;
#define ___PUSH_ARGS4(a,b,c,d)___PUSH(a)___PUSH(b)___PUSH(c)___SET_R1(d)
#define ___POP_ARGS4(a,b,c,d)d = ___R1; c = ___POP; b = ___POP; a = ___POP;
#define ___PUSH_ARGS5(a,b,c,d,e)___PUSH(a)___PUSH(b)___PUSH(c)___PUSH(d)___SET_R1(e)
#define ___POP_ARGS5(a,b,c,d,e)e = ___R1; d = ___POP; c = ___POP; b = ___POP; a = ___POP;
#else
#define ___PUSH_ARGS2(a,b)___SET_R1(a)___SET_R2(b)
#define ___POP_ARGS2(a,b)b = ___R2; a = ___R1;
#if ___NB_ARG_REGS == 2
#define ___PUSH_ARGS3(a,b,c)___PUSH(a)___SET_R1(b)___SET_R2(c)
#define ___POP_ARGS3(a,b,c)c = ___R2; b = ___R1; a = ___POP;
#define ___PUSH_ARGS4(a,b,c,d)___PUSH(a)___PUSH(b)___SET_R1(c)___SET_R2(d)
#define ___POP_ARGS4(a,b,c,d)d = ___R2; c = ___R1; b = ___POP; a = ___POP;
#define ___PUSH_ARGS5(a,b,c,d,e)___PUSH(a)___PUSH(b)___PUSH(c)___SET_R1(d)___SET_R2(e)
#define ___POP_ARGS5(a,b,c,d,e)e = ___R2; d = ___R1; c = ___POP; b = ___POP; a = ___POP;
#else
#define ___PUSH_ARGS3(a,b,c)___SET_R1(a)___SET_R2(b)___SET_R3(c)
#define ___POP_ARGS3(a,b,c)c = ___R3; b = ___R2; a = ___R1;
#if ___NB_ARG_REGS == 3
#define ___PUSH_ARGS4(a,b,c,d)___PUSH(a)___SET_R1(b)___SET_R2(c)___SET_R3(d)
#define ___POP_ARGS4(a,b,c,d)d = ___R3; c = ___R2; b = ___R1; a = ___POP;
#define ___PUSH_ARGS5(a,b,c,d,e)___PUSH(a)___PUSH(b)___SET_R1(c)___SET_R2(d)___SET_R3(e)
#define ___POP_ARGS5(a,b,c,d,e)e = ___R3; d = ___R2; c = ___R1; b = ___POP; a = ___POP;
#else
#define ___PUSH_ARGS4(a,b,c,d)___SET_R1(a)___SET_R2(b)___SET_R3(c)___SET_R4(d)
#define ___POP_ARGS4(a,b,c,d)d = ___R4; c = ___R3; b = ___R2; a = ___R1;
#if ___NB_ARG_REGS == 4
#define ___PUSH_ARGS5(a,b,c,d,e)___PUSH(a)___SET_R1(b)___SET_R2(c)___SET_R3(d)___SET_R4(e)
#define ___POP_ARGS5(a,b,c,d,e)e = ___R4; d = ___R3; c = ___R2; b = ___R1; a = ___POP;
#else
#define ___PUSH_ARGS5(a,b,c,d,e)___SET_R1(a)___SET_R2(b)___SET_R3(c)___SET_R4(d)___SET_R5(e)
#define ___POP_ARGS5(a,b,c,d,e)e = ___R5; d = ___R4; c = ___R3; b = ___R2; a = ___R1;
#endif
#endif
#endif
#endif
#endif

#define ___PSR0 ___ps->r[0]
#if ___MAX_LOCAL_GVM_REGS > 0
#define ___D_R0 register ___WORD ___r0;
#define ___R_R0 ___r0=___PSR0;
#define ___W_R0 ___PSR0=___r0;
#define ___R0 ___r0
#else
#define ___D_R0
#define ___R_R0
#define ___W_R0
#define ___R0 ___PSR0
#endif
#define ___SET_R0(val)___R0=val;
#define ___PUSH_R0 ___PUSH(___R0)
#define ___POP_R0 ___SET_R0(___POP)

#if ___NB_ARG_REGS == 0
#define ___PUSH_ARGS_IN_REGS(na)
#define ___POP_ARGS_IN_REGS(na)
#define ___PSSELF ___PSR1
#define ___SELF ___R1
#define ___LD_ARG_REGS
#define ___ST_ARG_REGS
#endif

#define ___PSR1 ___ps->r[1]
#if ___MAX_LOCAL_GVM_REGS > 1
#define ___D_R1 register ___WORD ___r1;
#define ___R_R1 ___r1=___PSR1;
#define ___W_R1 ___PSR1=___r1;
#define ___R1 ___r1
#else
#define ___D_R1
#define ___R_R1
#define ___W_R1
#define ___R1 ___PSR1
#endif
#define ___SET_R1(val)___R1=(val);
#define ___PUSH_R1_TO_R1 ___PUSH(___R1)
#define ___POP_R1_TO_R1 ___SET_R1(___POP)
#define ___LD_R1_TO_R1 ___D_R1 ___R_R1
#define ___ST_R1_TO_R1 ___W_R1

#if ___NB_ARG_REGS == 1
#define ___PUSH_ARGS_IN_REGS(na) \
if ((na)>0) ___PUSH_R1_TO_R1
#define ___POP_ARGS_IN_REGS(na) \
if ((na)>0) ___POP_R1_TO_R1
#define ___PSSELF ___PSR2
#define ___SELF ___R2
#define ___LD_ARG_REGS ___LD_R1_TO_R1
#define ___ST_ARG_REGS ___ST_R1_TO_R1
#endif

#if ___NB_GVM_REGS == 2

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R1
#define ___POP_REGS ___POP_R1_TO_R1 ___POP_R0

#else

#define ___PSR2 ___ps->r[2]
#if ___MAX_LOCAL_GVM_REGS > 2
#define ___D_R2 register ___WORD ___r2;
#define ___R_R2 ___r2=___PSR2;
#define ___W_R2 ___PSR2=___r2;
#define ___R2 ___r2
#else
#define ___D_R2
#define ___R_R2
#define ___W_R2
#define ___R2 ___PSR2
#endif
#define ___SET_R2(val)___R2=(val);
#define ___PUSH_R1_TO_R2 ___PUSH_R1_TO_R1 ___PUSH(___R2)
#define ___POP_R2_TO_R1 ___SET_R2(___POP)___POP_R1_TO_R1
#define ___LD_R1_TO_R2 ___D_R2 ___LD_R1_TO_R1 ___R_R2
#define ___ST_R1_TO_R2 ___ST_R1_TO_R1 ___W_R2

#if ___NB_ARG_REGS == 2
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  default: ___PUSH_R1_TO_R2 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  default: ___POP_R2_TO_R1 \
  }
#define ___PSSELF ___PSR3
#define ___SELF ___R3
#define ___LD_ARG_REGS ___LD_R1_TO_R2
#define ___ST_ARG_REGS ___ST_R1_TO_R2
#endif

#if ___NB_GVM_REGS == 3

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R2
#define ___POP_REGS ___POP_R2_TO_R1 ___POP_R0

#else

#define ___PSR3 ___ps->r[3]
#if ___MAX_LOCAL_GVM_REGS > 3
#define ___D_R3 register ___WORD ___r3;
#define ___R_R3 ___r3=___PSR3;
#define ___W_R3 ___PSR3=___r3;
#define ___R3 ___r3
#else
#define ___D_R3
#define ___R_R3
#define ___W_R3
#define ___R3 ___PSR3
#endif
#define ___SET_R3(val)___R3=(val);
#define ___PUSH_R1_TO_R3 ___PUSH_R1_TO_R2 ___PUSH(___R3)
#define ___POP_R3_TO_R1 ___SET_R3(___POP)___POP_R2_TO_R1
#define ___LD_R1_TO_R3 ___D_R3 ___LD_R1_TO_R2 ___R_R3
#define ___ST_R1_TO_R3 ___ST_R1_TO_R2 ___W_R3

#if ___NB_ARG_REGS == 3
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  default: ___PUSH_R1_TO_R3 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  default: ___POP_R3_TO_R1 \
  }
#define ___PSSELF ___PSR4
#define ___SELF ___R4
#define ___LD_ARG_REGS ___LD_R1_TO_R3
#define ___ST_ARG_REGS ___ST_R1_TO_R3
#endif

#if ___NB_GVM_REGS == 4

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R3
#define ___POP_REGS ___POP_R3_TO_R1 ___POP_R0

#else

#define ___PSR4 ___ps->r[4]
#if ___MAX_LOCAL_GVM_REGS > 4
#define ___D_R4 register ___WORD ___r4;
#define ___R_R4 ___r4=___PSR4;
#define ___W_R4 ___PSR4=___r4;
#define ___R4 ___r4
#else
#define ___D_R4
#define ___R_R4
#define ___W_R4
#define ___R4 ___PSR4
#endif
#define ___SET_R4(val)___R4=(val);
#define ___PUSH_R1_TO_R4 ___PUSH_R1_TO_R3 ___PUSH(___R4)
#define ___POP_R4_TO_R1 ___SET_R4(___POP)___POP_R3_TO_R1
#define ___LD_R1_TO_R4 ___D_R4 ___LD_R1_TO_R3 ___R_R4
#define ___ST_R1_TO_R4 ___ST_R1_TO_R3 ___W_R4

#if ___NB_ARG_REGS == 4
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  default: ___PUSH_R1_TO_R4 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  default: ___POP_R4_TO_R1 \
  }
#define ___PSSELF ___PSR5
#define ___SELF ___R5
#define ___LD_ARG_REGS ___LD_R1_TO_R4
#define ___ST_ARG_REGS ___ST_R1_TO_R4
#endif

#if ___NB_GVM_REGS == 5

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R4
#define ___POP_REGS ___POP_R4_TO_R1 ___POP_R0

#else

#define ___PSR5 ___ps->r[5]
#if ___MAX_LOCAL_GVM_REGS > 5
#define ___D_R5 register ___WORD ___r5;
#define ___R_R5 ___r5=___PSR5;
#define ___W_R5 ___PSR5=___r5;
#define ___R5 ___r5
#else
#define ___D_R5
#define ___R_R5
#define ___W_R5
#define ___R5 ___PSR5
#endif
#define ___SET_R5(val)___R5=(val);
#define ___PUSH_R1_TO_R5 ___PUSH_R1_TO_R4 ___PUSH(___R5)
#define ___POP_R5_TO_R1 ___SET_R5(___POP)___POP_R4_TO_R1
#define ___LD_R1_TO_R5 ___D_R5 ___LD_R1_TO_R4 ___R_R5
#define ___ST_R1_TO_R5 ___ST_R1_TO_R4 ___W_R5

#if ___NB_ARG_REGS == 5
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  default: ___PUSH_R1_TO_R5 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  default: ___POP_R5_TO_R1 \
  }
#define ___PSSELF ___PSR6
#define ___SELF ___R6
#define ___LD_ARG_REGS ___LD_R1_TO_R5
#define ___ST_ARG_REGS ___ST_R1_TO_R5
#endif

#if ___NB_GVM_REGS == 6

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R5
#define ___POP_REGS ___POP_R5_TO_R1 ___POP_R0

#else

#define ___PSR6 ___ps->r[6]
#if ___MAX_LOCAL_GVM_REGS > 6
#define ___D_R6 register ___WORD ___r6;
#define ___R_R6 ___r6=___PSR6;
#define ___W_R6 ___PSR6=___r6;
#define ___R6 ___r6
#else
#define ___D_R6
#define ___R_R6
#define ___W_R6
#define ___R6 ___PSR6
#endif
#define ___SET_R6(val)___R6=(val);
#define ___PUSH_R1_TO_R6 ___PUSH_R1_TO_R5 ___PUSH(___R6)
#define ___POP_R6_TO_R1 ___SET_R6(___POP)___POP_R5_TO_R1
#define ___LD_R1_TO_R6 ___D_R6 ___LD_R1_TO_R5 ___R_R6
#define ___ST_R1_TO_R6 ___ST_R1_TO_R5 ___W_R6

#if ___NB_ARG_REGS == 6
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  case 5:  ___PUSH_R1_TO_R5 break; \
  default: ___PUSH_R1_TO_R6 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  case 5:  ___POP_R5_TO_R1 break; \
  default: ___POP_R6_TO_R1 \
  }
#define ___PSSELF ___PSR7
#define ___SELF ___R7
#define ___LD_ARG_REGS ___LD_R1_TO_R6
#define ___ST_ARG_REGS ___ST_R1_TO_R6
#endif

#if ___NB_GVM_REGS == 7

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R6
#define ___POP_REGS ___POP_R6_TO_R1 ___POP_R0

#else

#define ___PSR7 ___ps->r[7]
#if ___MAX_LOCAL_GVM_REGS > 7
#define ___D_R7 register ___WORD ___r7;
#define ___R_R7 ___r7=___PSR7;
#define ___W_R7 ___PSR7=___r7;
#define ___R7 ___r7
#else
#define ___D_R7
#define ___R_R7
#define ___W_R7
#define ___R7 ___PSR7
#endif
#define ___SET_R7(val)___R7=(val);
#define ___PUSH_R1_TO_R7 ___PUSH_R1_TO_R6 ___PUSH(___R7)
#define ___POP_R7_TO_R1 ___SET_R7(___POP)___POP_R6_TO_R1
#define ___LD_R1_TO_R7 ___D_R7 ___LD_R1_TO_R6 ___R_R7
#define ___ST_R1_TO_R7 ___ST_R1_TO_R6 ___W_R7

#if ___NB_ARG_REGS == 7
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  case 5:  ___PUSH_R1_TO_R5 break; \
  case 6:  ___PUSH_R1_TO_R6 break; \
  default: ___PUSH_R1_TO_R7 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  case 5:  ___POP_R5_TO_R1 break; \
  case 6:  ___POP_R6_TO_R1 break; \
  default: ___POP_R7_TO_R1 \
  }
#define ___PSSELF ___PSR8
#define ___SELF ___R8
#define ___LD_ARG_REGS ___LD_R1_TO_R7
#define ___ST_ARG_REGS ___ST_R1_TO_R7
#endif

#if ___NB_GVM_REGS == 8

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R7
#define ___POP_REGS ___POP_R7_TO_R1 ___POP_R0

#else

#define ___PSR8 ___ps->r[8]
#if ___MAX_LOCAL_GVM_REGS > 8
#define ___D_R8 register ___WORD ___r8;
#define ___R_R8 ___r8=___PSR8;
#define ___W_R8 ___PSR8=___r8;
#define ___R8 ___r8
#else
#define ___D_R8
#define ___R_R8
#define ___W_R8
#define ___R8 ___PSR8
#endif
#define ___SET_R8(val)___R8=(val);
#define ___PUSH_R1_TO_R8 ___PUSH_R1_TO_R7 ___PUSH(___R8)
#define ___POP_R8_TO_R1 ___SET_R8(___POP)___POP_R7_TO_R1
#define ___LD_R1_TO_R8 ___D_R8 ___LD_R1_TO_R7 ___R_R8
#define ___ST_R1_TO_R8 ___ST_R1_TO_R7 ___W_R8

#if ___NB_ARG_REGS == 8
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  case 5:  ___PUSH_R1_TO_R5 break; \
  case 6:  ___PUSH_R1_TO_R6 break; \
  case 7:  ___PUSH_R1_TO_R7 break; \
  default: ___PUSH_R1_TO_R8 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  case 5:  ___POP_R5_TO_R1 break; \
  case 6:  ___POP_R6_TO_R1 break; \
  case 7:  ___POP_R7_TO_R1 break; \
  default: ___POP_R8_TO_R1 \
  }
#define ___PSSELF ___PSR9
#define ___SELF ___R9
#define ___LD_ARG_REGS ___LD_R1_TO_R8
#define ___ST_ARG_REGS ___ST_R1_TO_R8
#endif

#if ___NB_GVM_REGS == 9

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R8
#define ___POP_REGS ___POP_R8_TO_R1 ___POP_R0

#else

#define ___PSR9 ___ps->r[9]
#if ___MAX_LOCAL_GVM_REGS > 9
#define ___D_R9 register ___WORD ___r9;
#define ___R_R9 ___r9=___PSR9;
#define ___W_R9 ___PSR9=___r9;
#define ___R9 ___r9
#else
#define ___D_R9
#define ___R_R9
#define ___W_R9
#define ___R9 ___PSR9
#endif
#define ___SET_R9(val)___R9=(val);
#define ___PUSH_R1_TO_R9 ___PUSH_R1_TO_R8 ___PUSH(___R9)
#define ___POP_R9_TO_R1 ___SET_R9(___POP)___POP_R8_TO_R1
#define ___LD_R1_TO_R9 ___D_R9 ___LD_R1_TO_R8 ___R_R9
#define ___ST_R1_TO_R9 ___ST_R1_TO_R8 ___W_R9

#if ___NB_ARG_REGS == 9
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  case 5:  ___PUSH_R1_TO_R5 break; \
  case 6:  ___PUSH_R1_TO_R6 break; \
  case 7:  ___PUSH_R1_TO_R7 break; \
  case 8:  ___PUSH_R1_TO_R8 break; \
  default: ___PUSH_R1_TO_R9 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  case 5:  ___POP_R5_TO_R1 break; \
  case 6:  ___POP_R6_TO_R1 break; \
  case 7:  ___POP_R7_TO_R1 break; \
  case 8:  ___POP_R8_TO_R1 break; \
  default: ___POP_R9_TO_R1 \
  }
#define ___PSSELF ___PSR10
#define ___SELF ___R10
#define ___LD_ARG_REGS ___LD_R1_TO_R9
#define ___ST_ARG_REGS ___ST_R1_TO_R9
#endif

#if ___NB_GVM_REGS == 10

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R9
#define ___POP_REGS ___POP_R9_TO_R1 ___POP_R0

#else

#define ___PSR10 ___ps->r[10]
#if ___MAX_LOCAL_GVM_REGS > 10
#define ___D_R10 register ___WORD ___r10;
#define ___R_R10 ___r10=___PSR10;
#define ___W_R10 ___PSR10=___r10;
#define ___R10 ___r10
#else
#define ___D_R10
#define ___R_R10
#define ___W_R10
#define ___R10 ___PSR10
#endif
#define ___SET_R10(val)___R10=(val);
#define ___PUSH_R1_TO_R10 ___PUSH_R1_TO_R9 ___PUSH(___R10)
#define ___POP_R10_TO_R1 ___SET_R10(___POP)___POP_R9_TO_R1
#define ___LD_R1_TO_R10 ___D_R10 ___LD_R1_TO_R9 ___R_R10
#define ___ST_R1_TO_R10 ___ST_R1_TO_R9 ___W_R10

#if ___NB_ARG_REGS == 10
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  case 5:  ___PUSH_R1_TO_R5 break; \
  case 6:  ___PUSH_R1_TO_R6 break; \
  case 7:  ___PUSH_R1_TO_R7 break; \
  case 8:  ___PUSH_R1_TO_R8 break; \
  case 9:  ___PUSH_R1_TO_R9 break; \
  default: ___PUSH_R1_TO_R10 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  case 5:  ___POP_R5_TO_R1 break; \
  case 6:  ___POP_R6_TO_R1 break; \
  case 7:  ___POP_R7_TO_R1 break; \
  case 8:  ___POP_R8_TO_R1 break; \
  case 9:  ___POP_R9_TO_R1 break; \
  default: ___POP_R10_TO_R1 \
  }
#define ___PSSELF ___PSR11
#define ___SELF ___R11
#define ___LD_ARG_REGS ___LD_R1_TO_R10
#define ___ST_ARG_REGS ___ST_R1_TO_R10
#endif

#if ___NB_GVM_REGS == 11

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R10
#define ___POP_REGS ___POP_R10_TO_R1 ___POP_R0

#else

#define ___PSR11 ___ps->r[11]
#if ___MAX_LOCAL_GVM_REGS > 11
#define ___D_R11 register ___WORD ___r11;
#define ___R_R11 ___r11=___PSR11;
#define ___W_R11 ___PSR11=___r11;
#define ___R11 ___r11
#else
#define ___D_R11
#define ___R_R11
#define ___W_R11
#define ___R11 ___PSR11
#endif
#define ___SET_R11(val)___R11=(val);
#define ___PUSH_R1_TO_R11 ___PUSH_R1_TO_R10 ___PUSH(___R11)
#define ___POP_R11_TO_R1 ___SET_R11(___POP)___POP_R10_TO_R1
#define ___LD_R1_TO_R11 ___D_R11 ___LD_R1_TO_R10 ___R_R11
#define ___ST_R1_TO_R11 ___ST_R1_TO_R10 ___W_R11

#if ___NB_ARG_REGS == 11
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  case 5:  ___PUSH_R1_TO_R5 break; \
  case 6:  ___PUSH_R1_TO_R6 break; \
  case 7:  ___PUSH_R1_TO_R7 break; \
  case 8:  ___PUSH_R1_TO_R8 break; \
  case 9:  ___PUSH_R1_TO_R9 break; \
  case 10:  ___PUSH_R1_TO_R10 break; \
  default: ___PUSH_R1_TO_R11 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  case 5:  ___POP_R5_TO_R1 break; \
  case 6:  ___POP_R6_TO_R1 break; \
  case 7:  ___POP_R7_TO_R1 break; \
  case 8:  ___POP_R8_TO_R1 break; \
  case 9:  ___POP_R9_TO_R1 break; \
  case 10:  ___POP_R10_TO_R1 break; \
  default: ___POP_R11_TO_R1 \
  }
#define ___PSSELF ___PSR12
#define ___SELF ___R12
#define ___LD_ARG_REGS ___LD_R1_TO_R11
#define ___ST_ARG_REGS ___ST_R1_TO_R11
#endif

#if ___NB_GVM_REGS == 12

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R11
#define ___POP_REGS ___POP_R11_TO_R1 ___POP_R0

#else

#define ___PSR12 ___ps->r[12]
#if ___MAX_LOCAL_GVM_REGS > 12
#define ___D_R12 register ___WORD ___r12;
#define ___R_R12 ___r12=___PSR12;
#define ___W_R12 ___PSR12=___r12;
#define ___R12 ___r12
#else
#define ___D_R12
#define ___R_R12
#define ___W_R12
#define ___R12 ___PSR12
#endif
#define ___SET_R12(val)___R12=(val);
#define ___PUSH_R1_TO_R12 ___PUSH_R1_TO_R11 ___PUSH(___R12)
#define ___POP_R12_TO_R1 ___SET_R12(___POP)___POP_R11_TO_R1
#define ___LD_R1_TO_R12 ___D_R12 ___LD_R1_TO_R11 ___R_R12
#define ___ST_R1_TO_R12 ___ST_R1_TO_R11 ___W_R12

#if ___NB_ARG_REGS == 12
#define ___PUSH_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___PUSH_R1_TO_R1 break; \
  case 2:  ___PUSH_R1_TO_R2 break; \
  case 3:  ___PUSH_R1_TO_R3 break; \
  case 4:  ___PUSH_R1_TO_R4 break; \
  case 5:  ___PUSH_R1_TO_R5 break; \
  case 6:  ___PUSH_R1_TO_R6 break; \
  case 7:  ___PUSH_R1_TO_R7 break; \
  case 8:  ___PUSH_R1_TO_R8 break; \
  case 9:  ___PUSH_R1_TO_R9 break; \
  case 10:  ___PUSH_R1_TO_R10 break; \
  case 11:  ___PUSH_R1_TO_R11 break; \
  default: ___PUSH_R1_TO_R12 \
  }
#define ___POP_ARGS_IN_REGS(na) \
switch (na) \
  { \
  case 0:  break; \
  case 1:  ___POP_R1_TO_R1 break; \
  case 2:  ___POP_R2_TO_R1 break; \
  case 3:  ___POP_R3_TO_R1 break; \
  case 4:  ___POP_R4_TO_R1 break; \
  case 5:  ___POP_R5_TO_R1 break; \
  case 6:  ___POP_R6_TO_R1 break; \
  case 7:  ___POP_R7_TO_R1 break; \
  case 8:  ___POP_R8_TO_R1 break; \
  case 9:  ___POP_R9_TO_R1 break; \
  case 10:  ___POP_R10_TO_R1 break; \
  case 11:  ___POP_R11_TO_R1 break; \
  default: ___POP_R12_TO_R1 \
  }
#define ___PSSELF ___PSR13
#define ___SELF ___R13
#define ___LD_ARG_REGS ___LD_R1_TO_R12
#define ___ST_ARG_REGS ___ST_R1_TO_R12
#endif

#if ___NB_GVM_REGS == 13

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R12
#define ___POP_REGS ___POP_R12_TO_R1 ___POP_R0

#else

#define ___PSR13 ___ps->r[13]
#if ___MAX_LOCAL_GVM_REGS > 13
#define ___D_R13 register ___WORD ___r13;
#define ___R_R13 ___r13=___PSR13;
#define ___W_R13 ___PSR13=___r13;
#define ___R13 ___r13
#else
#define ___D_R13
#define ___R_R13
#define ___W_R13
#define ___R13 ___PSR13
#endif
#define ___SET_R13(val)___R13=(val);
#define ___PUSH_R1_TO_R13 ___PUSH_R1_TO_R12 ___PUSH(___R13)
#define ___POP_R13_TO_R1 ___SET_R13(___POP)___POP_R12_TO_R1
#define ___LD_R1_TO_R13 ___D_R13 ___LD_R1_TO_R12 ___R_R13
#define ___ST_R1_TO_R13 ___ST_R1_TO_R12 ___W_R13

#if ___NB_GVM_REGS == 14

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R13
#define ___POP_REGS ___POP_R13_TO_R1 ___POP_R0

#else

#define ___PSR14 ___ps->r[14]
#if ___MAX_LOCAL_GVM_REGS > 14
#define ___D_R14 register ___WORD ___r14;
#define ___R_R14 ___r14=___PSR14;
#define ___W_R14 ___PSR14=___r14;
#define ___R14 ___r14
#else
#define ___D_R14
#define ___R_R14
#define ___W_R14
#define ___R14 ___PSR14
#endif
#define ___SET_R14(val)___R14=(val);
#define ___PUSH_R1_TO_R14 ___PUSH_R1_TO_R13 ___PUSH(___R14)
#define ___POP_R14_TO_R1 ___SET_R14(___POP)___POP_R13_TO_R1
#define ___LD_R1_TO_R14 ___D_R14 ___LD_R1_TO_R13 ___R_R14
#define ___ST_R1_TO_R14 ___ST_R1_TO_R13 ___W_R14

#if ___NB_GVM_REGS == 15

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R14
#define ___POP_REGS ___POP_R14_TO_R1 ___POP_R0

#else

#define ___PSR15 ___ps->r[15]
#if ___MAX_LOCAL_GVM_REGS > 15
#define ___D_R15 register ___WORD ___r15;
#define ___R_R15 ___r15=___PSR15;
#define ___W_R15 ___PSR15=___r15;
#define ___R15 ___r15
#else
#define ___D_R15
#define ___R_R15
#define ___W_R15
#define ___R15 ___PSR15
#endif
#define ___SET_R15(val)___R15=(val);
#define ___PUSH_R1_TO_R15 ___PUSH_R1_TO_R14 ___PUSH(___R15)
#define ___POP_R15_TO_R1 ___SET_R15(___POP)___POP_R14_TO_R1
#define ___LD_R1_TO_R15 ___D_R15 ___LD_R1_TO_R14 ___R_R15
#define ___ST_R1_TO_R15 ___ST_R1_TO_R14 ___W_R15

#if ___NB_GVM_REGS == 16

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R15
#define ___POP_REGS ___POP_R15_TO_R1 ___POP_R0

#else

#define ___PSR16 ___ps->r[16]
#if ___MAX_LOCAL_GVM_REGS > 16
#define ___D_R16 register ___WORD ___r16;
#define ___R_R16 ___r16=___PSR16;
#define ___W_R16 ___PSR16=___r16;
#define ___R16 ___r16
#else
#define ___D_R16
#define ___R_R16
#define ___W_R16
#define ___R16 ___PSR16
#endif
#define ___SET_R16(val)___R16=(val);
#define ___PUSH_R1_TO_R16 ___PUSH_R1_TO_R15 ___PUSH(___R16)
#define ___POP_R16_TO_R1 ___SET_R16(___POP)___POP_R15_TO_R1
#define ___LD_R1_TO_R16 ___D_R16 ___LD_R1_TO_R15 ___R_R16
#define ___ST_R1_TO_R16 ___ST_R1_TO_R15 ___W_R16

#if ___NB_GVM_REGS == 17

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R16
#define ___POP_REGS ___POP_R16_TO_R1 ___POP_R0

#else

#define ___PSR17 ___ps->r[17]
#if ___MAX_LOCAL_GVM_REGS > 17
#define ___D_R17 register ___WORD ___r17;
#define ___R_R17 ___r17=___PSR17;
#define ___W_R17 ___PSR17=___r17;
#define ___R17 ___r17
#else
#define ___D_R17
#define ___R_R17
#define ___W_R17
#define ___R17 ___PSR17
#endif
#define ___SET_R17(val)___R17=(val);
#define ___PUSH_R1_TO_R17 ___PUSH_R1_TO_R16 ___PUSH(___R17)
#define ___POP_R17_TO_R1 ___SET_R17(___POP)___POP_R16_TO_R1
#define ___LD_R1_TO_R17 ___D_R17 ___LD_R1_TO_R16 ___R_R17
#define ___ST_R1_TO_R17 ___ST_R1_TO_R16 ___W_R17

#if ___NB_GVM_REGS == 18

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R17
#define ___POP_REGS ___POP_R17_TO_R1 ___POP_R0

#else

#define ___PSR18 ___ps->r[18]
#if ___MAX_LOCAL_GVM_REGS > 18
#define ___D_R18 register ___WORD ___r18;
#define ___R_R18 ___r18=___PSR18;
#define ___W_R18 ___PSR18=___r18;
#define ___R18 ___r18
#else
#define ___D_R18
#define ___R_R18
#define ___W_R18
#define ___R18 ___PSR18
#endif
#define ___SET_R18(val)___R18=(val);
#define ___PUSH_R1_TO_R18 ___PUSH_R1_TO_R17 ___PUSH(___R18)
#define ___POP_R18_TO_R1 ___SET_R18(___POP)___POP_R17_TO_R1
#define ___LD_R1_TO_R18 ___D_R18 ___LD_R1_TO_R17 ___R_R18
#define ___ST_R1_TO_R18 ___ST_R1_TO_R17 ___W_R18

#if ___NB_GVM_REGS == 19

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R18
#define ___POP_REGS ___POP_R18_TO_R1 ___POP_R0

#else

#define ___PSR19 ___ps->r[19]
#if ___MAX_LOCAL_GVM_REGS > 19
#define ___D_R19 register ___WORD ___r19;
#define ___R_R19 ___r19=___PSR19;
#define ___W_R19 ___PSR19=___r19;
#define ___R19 ___r19
#else
#define ___D_R19
#define ___R_R19
#define ___W_R19
#define ___R19 ___PSR19
#endif
#define ___SET_R19(val)___R19=(val);
#define ___PUSH_R1_TO_R19 ___PUSH_R1_TO_R18 ___PUSH(___R19)
#define ___POP_R19_TO_R1 ___SET_R19(___POP)___POP_R18_TO_R1
#define ___LD_R1_TO_R19 ___D_R19 ___LD_R1_TO_R18 ___R_R19
#define ___ST_R1_TO_R19 ___ST_R1_TO_R18 ___W_R19

#if ___NB_GVM_REGS == 20

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R19
#define ___POP_REGS ___POP_R19_TO_R1 ___POP_R0

#else

#define ___PSR20 ___ps->r[20]
#if ___MAX_LOCAL_GVM_REGS > 20
#define ___D_R20 register ___WORD ___r20;
#define ___R_R20 ___r20=___PSR20;
#define ___W_R20 ___PSR20=___r20;
#define ___R20 ___r20
#else
#define ___D_R20
#define ___R_R20
#define ___W_R20
#define ___R20 ___PSR20
#endif
#define ___SET_R20(val)___R20=(val);
#define ___PUSH_R1_TO_R20 ___PUSH_R1_TO_R19 ___PUSH(___R20)
#define ___POP_R20_TO_R1 ___SET_R20(___POP)___POP_R19_TO_R1
#define ___LD_R1_TO_R20 ___D_R20 ___LD_R1_TO_R19 ___R_R20
#define ___ST_R1_TO_R20 ___ST_R1_TO_R19 ___W_R20

#if ___NB_GVM_REGS == 21

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R20
#define ___POP_REGS ___POP_R20_TO_R1 ___POP_R0

#else

#define ___PSR21 ___ps->r[21]
#if ___MAX_LOCAL_GVM_REGS > 21
#define ___D_R21 register ___WORD ___r21;
#define ___R_R21 ___r21=___PSR21;
#define ___W_R21 ___PSR21=___r21;
#define ___R21 ___r21
#else
#define ___D_R21
#define ___R_R21
#define ___W_R21
#define ___R21 ___PSR21
#endif
#define ___SET_R21(val)___R21=(val);
#define ___PUSH_R1_TO_R21 ___PUSH_R1_TO_R20 ___PUSH(___R21)
#define ___POP_R21_TO_R1 ___SET_R21(___POP)___POP_R20_TO_R1
#define ___LD_R1_TO_R21 ___D_R21 ___LD_R1_TO_R20 ___R_R21
#define ___ST_R1_TO_R21 ___ST_R1_TO_R20 ___W_R21

#if ___NB_GVM_REGS == 22

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R21
#define ___POP_REGS ___POP_R21_TO_R1 ___POP_R0

#else

#define ___PSR22 ___ps->r[22]
#if ___MAX_LOCAL_GVM_REGS > 22
#define ___D_R22 register ___WORD ___r22;
#define ___R_R22 ___r22=___PSR22;
#define ___W_R22 ___PSR22=___r22;
#define ___R22 ___r22
#else
#define ___D_R22
#define ___R_R22
#define ___W_R22
#define ___R22 ___PSR22
#endif
#define ___SET_R22(val)___R22=(val);
#define ___PUSH_R1_TO_R22 ___PUSH_R1_TO_R21 ___PUSH(___R22)
#define ___POP_R22_TO_R1 ___SET_R22(___POP)___POP_R21_TO_R1
#define ___LD_R1_TO_R22 ___D_R22 ___LD_R1_TO_R21 ___R_R22
#define ___ST_R1_TO_R22 ___ST_R1_TO_R21 ___W_R22

#if ___NB_GVM_REGS == 23

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R22
#define ___POP_REGS ___POP_R22_TO_R1 ___POP_R0

#else

#define ___PSR23 ___ps->r[23]
#if ___MAX_LOCAL_GVM_REGS > 23
#define ___D_R23 register ___WORD ___r23;
#define ___R_R23 ___r23=___PSR23;
#define ___W_R23 ___PSR23=___r23;
#define ___R23 ___r23
#else
#define ___D_R23
#define ___R_R23
#define ___W_R23
#define ___R23 ___PSR23
#endif
#define ___SET_R23(val)___R23=(val);
#define ___PUSH_R1_TO_R23 ___PUSH_R1_TO_R22 ___PUSH(___R23)
#define ___POP_R23_TO_R1 ___SET_R23(___POP)___POP_R22_TO_R1
#define ___LD_R1_TO_R23 ___D_R23 ___LD_R1_TO_R22 ___R_R23
#define ___ST_R1_TO_R23 ___ST_R1_TO_R22 ___W_R23

#if ___NB_GVM_REGS == 24

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R23
#define ___POP_REGS ___POP_R23_TO_R1 ___POP_R0

#else

#define ___PSR24 ___ps->r[24]
#if ___MAX_LOCAL_GVM_REGS > 24
#define ___D_R24 register ___WORD ___r24;
#define ___R_R24 ___r24=___PSR24;
#define ___W_R24 ___PSR24=___r24;
#define ___R24 ___r24
#else
#define ___D_R24
#define ___R_R24
#define ___W_R24
#define ___R24 ___PSR24
#endif
#define ___SET_R24(val)___R24=(val);
#define ___PUSH_R1_TO_R24 ___PUSH_R1_TO_R23 ___PUSH(___R24)
#define ___POP_R24_TO_R1 ___SET_R24(___POP)___POP_R23_TO_R1
#define ___LD_R1_TO_R24 ___D_R24 ___LD_R1_TO_R23 ___R_R24
#define ___ST_R1_TO_R24 ___ST_R1_TO_R23 ___W_R24

#if ___NB_GVM_REGS == 25

#define ___PUSH_REGS ___PUSH_R0 ___PUSH_R1_TO_R24
#define ___POP_REGS ___POP_R24_TO_R1 ___POP_R0

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

/*---------------------------------------------------------------------------*/

/* Labels and switches */

#define ___NOT(x)!x
#define ___AND(x,y)(x&&y)

#define ___MLBL(n)___lp+((n)*___LS*___WS)
#define ___LBL(n)___start+((___PH_LBL0-___HOST_LBL0+n)*___LS*___WS)
#define ___DEF_SLBL(n,lbl)___DEF_SW(n)___DEF_GLBL(lbl)
#define ___DEF_GLBL(lbl)lbl:
#define ___GOTO(lbl)goto lbl;
#define ___IF_GOTO(test,lbl)if (test) ___GOTO(lbl)
#define ___JUMPINT(nargs,prc,lbl)___SM(___GOTO(lbl),{nargs ___JUMP(prc)})
#define ___JUMPEXTPRM(nargs,val){nargs ___JUMPEXT(val)}
#define ___JUMPEXTNOTSAFE(nargs,val) \
{nargs ___SELF=val; \
___JUMPEXT(___LABEL_ENTRY_OR_DESCR(___SELF))}
#define ___JUMPPRM(nargs,val){nargs ___JUMP(val)}

#define ___JUMPNOTSAFE(nargs,val) \
{nargs ___SELF=val; \
___JUMP(___LABEL_ENTRY_OR_DESCR(___SELF))}

#define ___JUMPSAFE(nargs,val) ___JUMPNOTSAFE(nargs,val) /***************/

#define ___JUMPGENNOTSAFE(nargs,val)___JUMPNOTSAFE(nargs,val)
#define ___JUMPGLONOTSAFE(nargs,i,glo)___JUMPNOTSAFE(nargs,___GLO(i,glo))
#define ___JUMPGENSAFE(nargs,val) \
{nargs ___SELF=val; \
if (___EXPECT_TRUE(___PROCEDUREP(___SELF))) \
  ___JUMP(___LABEL_ENTRY_OR_DESCR(___SELF)) \
___ps->temp1=___SELF;___JUMPEXTPRM(___NOTHING,___GSTATE->handler_not_proc)}
#define ___JUMPGLOSAFE(nargs,i,glo) \
{nargs ___SELF=___GLO(i,glo); \
if (___EXPECT_TRUE(___PROCEDUREP(___SELF))) \
  ___JUMP(___LABEL_ENTRY_OR_DESCR(___SELF)) \
___ps->temp4=(___WORD)&___GLOSTRUCT(i,glo);___JUMPEXTPRM(___NOTHING,___GSTATE->handler_not_proc_glo)}

#ifdef ___NOT_SAFE_CALLS
#undef ___JUMPGENSAFE
#undef ___JUMPGLOSAFE
#define ___JUMPGENSAFE(nargs,val)___JUMPGENNOTSAFE(nargs,val)
#define ___JUMPGLOSAFE(nargs,i,glo)___JUMPGLONOTSAFE(nargs,i,glo)
#endif

#ifdef ___SAFE_CALLS
#undef ___JUMPGENNOTSAFE
#undef ___JUMPGLONOTSAFE
#define ___JUMPGENNOTSAFE(nargs,val)___JUMPGENSAFE(nargs,val)
#define ___JUMPGLONOTSAFE(nargs,i,glo)___JUMPGLOSAFE(nargs,i,glo)
#endif

#define ___BEGIN_SWITCH(x) switch (x) {
#define ___SWITCH_CASE_GOTO(obj,lbl) case (obj): ___GOTO(lbl)
#define ___END_SWITCH }

#define ___BEGIN_SWITCH_FIXNUM(x) { ___SCMOBJ ___sw = (x); \
if (___EXPECT_TRUE(___FIXNUMP(___sw))) switch(___INT(___sw)) {
#define ___SWITCH_FIXNUM_CASE_GOTO(obj,lbl) case (___INT(obj)): ___GOTO(lbl)
#define ___END_SWITCH_FIXNUM }}

#define ___BEGIN_SWITCH_CHAR(x) { ___SCMOBJ ___sw = (x); \
if (___EXPECT_TRUE(___CHARP(___sw))) switch(___INT(___sw)) {
#define ___SWITCH_CHAR_CASE_GOTO(obj,lbl) case (___INT(obj)): ___GOTO(lbl)
#define ___END_SWITCH_CHAR }}

#define ___BEGIN_SWITCH_SYMKEY(x,mod,guard) { ___SCMOBJ ___sw = (x); \
if (___EXPECT_TRUE(guard(___sw))) switch(___INT(___FIELD(___sw,___SYMKEY_HASH)) & ((mod)-1)) {
#define ___SWITCH_SYMKEY_CASE(hash) case (hash):
#define ___SWITCH_SYMKEY_CASE_GOTO(obj,lbl) ___IF_GOTO(___EQP(___sw,obj),lbl)
#define ___END_SWITCH_SYMKEY }}

/*---------------------------------------------------------------------------*/

#define ___PRC(i)___start+((i-___HOST_LBL0)*___LS*___WS)

#define ___SET_NARGS(n)___ps->na=n;

#define ___IF_NARGS_EQ(n,code)if (___EXPECT_TRUE(___ps->na==n)) {code} else

#define ___WRONG_NARGS(lbl,nb_req,nb_opt,nb_key) \
{___ps->temp1=___LBL(lbl); \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_wrong_nargs)}

#define ___GET_REST(lbl,nb_req,nb_opt,nb_key) \
if (___ps->na>=0){___ps->temp1=___LBL(lbl); \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_get_rest)}

#define ___GET_KEY(lbl,nb_req,nb_opt,nb_key,key_descr) \
if (___ps->na>=0){___ps->temp1=___LBL(lbl);___ps->temp2=nb_req+nb_opt; \
___ps->temp3=key_descr;___JUMPEXTPRM(___NOTHING,___GSTATE->handler_get_key)}

#define ___GET_REST_KEY(lbl,nb_req,nb_opt,nb_key,key_descr) \
if (___ps->na>=0){___ps->temp1=___LBL(lbl);___ps->temp2=nb_req+nb_opt; \
___ps->temp3=key_descr;___ps->temp4=1; \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_get_key_rest)}

#define ___GET_KEY_REST(lbl,nb_req,nb_opt,nb_key,key_descr) \
if (___ps->na>=0){___ps->temp1=___LBL(lbl);___ps->temp2=nb_req+nb_opt; \
___ps->temp3=key_descr;___ps->temp4=0; \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_get_key_rest)}

#define ___BOOLEAN(x)(x)?___TRU:___FAL
#define ___EXPR(x)x;

#define ___ALLOC_CLO(n)(___ALLOC(n+2),___TAG((___hp-n-2),___tSUBTYPED))
#define ___BEGIN_SETUP_CLO(n,clo,lbl) \
{___WORD *___ptr=___UNTAG_AS(clo,___tSUBTYPED); \
___ptr[0]=___MAKE_HD_WORDS((n+1),___sPROCEDURE); ___ptr[1]=___LBL(lbl);
#define ___ADD_CLO_ELEM(i,val)___ptr[i+2]=(val);
#define ___END_SETUP_CLO(n) }
#define ___CLO(x,y)___BODY_AS(x,___tSUBTYPED)[y]
#define ___SET_CLO(x,y,z)___BODY_AS(x,___tSUBTYPED)[y]=z;

#define ___BEGIN_ALLOC_LIST(n,last)___ALLOC_PAIR(last,___NUL)
#define ___ADD_LIST_ELEM(i,val)___ALLOC_PAIR(val,___TAG((___hp-___PAIR_SIZE-1),___tPAIR))
#define ___END_ALLOC_LIST(n)
#define ___GET_LIST(n) ___TAG((___hp-___PAIR_SIZE-1),___tPAIR)

#define ___BEGIN_ALLOC_STRING(n) \
___hp[0]=___MAKE_HD_BYTES(n<<___LCS,___sSTRING);
#define ___ADD_STRING_ELEM(i,val)___CS_SELECT( \
___STORE_U8(___hp+1,i,___INT(val)), \
___STORE_U16(___hp+1,i,___INT(val)), \
___STORE_U32(___hp+1,i,___INT(val)));
#define ___END_ALLOC_STRING(n)___ALLOC(___WORDS(n<<___LCS)+1);
#define ___GET_STRING(n)___TAG((___hp-___WORDS(n<<___LCS)-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_S8VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n,___sS8VECTOR);
#define ___ADD_S8VECTOR_ELEM(i,val)___STORE_S8(___hp+1,i,___INT(val));
#define ___END_ALLOC_S8VECTOR(n)___ALLOC(___WORDS(n)+1);
#define ___GET_S8VECTOR(n)___TAG((___hp-___WORDS(n)-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_U8VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n,___sU8VECTOR);
#define ___ADD_U8VECTOR_ELEM(i,val)___STORE_U8(___hp+1,i,___INT(val));
#define ___END_ALLOC_U8VECTOR(n)___ALLOC(___WORDS(n)+1);
#define ___GET_U8VECTOR(n)___TAG((___hp-___WORDS(n)-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_S16VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<1,___sS16VECTOR);
#define ___ADD_S16VECTOR_ELEM(i,val)___STORE_S16(___hp+1,i,___INT(val));
#define ___END_ALLOC_S16VECTOR(n)___ALLOC(___WORDS(n<<1)+1);
#define ___GET_S16VECTOR(n)___TAG((___hp-___WORDS(n<<1)-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_U16VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<1,___sU16VECTOR);
#define ___ADD_U16VECTOR_ELEM(i,val)___STORE_U16(___hp+1,i,___INT(val));
#define ___END_ALLOC_U16VECTOR(n)___ALLOC(___WORDS(n<<1)+1);
#define ___GET_U16VECTOR(n)___TAG((___hp-___WORDS(n<<1)-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_S32VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<2,___sS32VECTOR);
#define ___ADD_S32VECTOR_ELEM(i,val)___STORE_S32(___hp+1,i,___S32UNBOX(val));
#define ___END_ALLOC_S32VECTOR(n)___ALLOC(___WORDS(n<<2)+1);
#define ___GET_S32VECTOR(n)___TAG((___hp-___WORDS(n<<2)-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_U32VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<2,___sU32VECTOR);
#define ___ADD_U32VECTOR_ELEM(i,val)___STORE_U32(___hp+1,i,___U32UNBOX(val));
#define ___END_ALLOC_U32VECTOR(n)___ALLOC(___WORDS(n<<2)+1);
#define ___GET_U32VECTOR(n)___TAG((___hp-___WORDS(n<<2)-1),___tSUBTYPED)

#if ___SCMOBJ_WIDTH == 32

#define ___BEGIN_ALLOC_S64VECTOR(n) \
{___WORD *___ptr = (___WORD*)((___WORD)(___hp+2)&~7); \
___ptr[-1]=___MAKE_HD_BYTES(n<<3,___sS64VECTOR);
#define ___ADD_S64VECTOR_ELEM(i,val)___STORE_S64(___ptr,i,___S64UNBOX(val));
#define ___END_ALLOC_S64VECTOR(n)___ALLOC(___WORDS(n<<3)+2);}
#define ___GET_S64VECTOR(n)___TAG((((___WORD*)((___WORD)(___hp-___WORDS(n<<3))&~7))-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_U64VECTOR(n) \
{___WORD *___ptr = (___WORD*)((___WORD)(___hp+2)&~7); \
___ptr[-1]=___MAKE_HD_BYTES(n<<3,___sU64VECTOR);
#define ___ADD_U64VECTOR_ELEM(i,val)___STORE_U64(___ptr,i,___U64UNBOX(val));
#define ___END_ALLOC_U64VECTOR(n)___ALLOC(___WORDS(n<<3)+2);}
#define ___GET_U64VECTOR(n)___TAG((((___WORD*)((___WORD)(___hp-___WORDS(n<<3))&~7))-1),___tSUBTYPED)

#else

#define ___BEGIN_ALLOC_S64VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<3,___sS64VECTOR);
#define ___ADD_S64VECTOR_ELEM(i,val)___STORE_S64(___hp+1,i,___S64UNBOX(val));
#define ___END_ALLOC_S64VECTOR(n)___ALLOC(___WORDS(n<<3)+1);
#define ___GET_S64VECTOR(n)___TAG((___hp-___WORDS(n<<3)-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_U64VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<3,___sU64VECTOR);
#define ___ADD_U64VECTOR_ELEM(i,val)___STORE_U64(___hp+1,i,___U64UNBOX(val));
#define ___END_ALLOC_U64VECTOR(n)___ALLOC(___WORDS(n<<3)+1);
#define ___GET_U64VECTOR(n)___TAG((___hp-___WORDS(n<<3)-1),___tSUBTYPED)

#endif

#define ___BEGIN_ALLOC_F32VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<2,___sF32VECTOR);
#ifdef ___F32
#define ___ADD_F32VECTOR_ELEM(i,val)((___F32*)(___hp+1))[i]=(val);
#else
#define ___ADD_F32VECTOR_ELEM(i,val);
#endif
#define ___END_ALLOC_F32VECTOR(n)___ALLOC(___WORDS(n<<2)+1);
#define ___GET_F32VECTOR(n)___TAG((___hp-___WORDS(n<<2)-1),___tSUBTYPED)

#if ___SCMOBJ_WIDTH == 32

#define ___BEGIN_ALLOC_F64VECTOR(n) \
{___WORD *___ptr = (___WORD*)((___WORD)(___hp+2)&~7); \
___ptr[-1]=___MAKE_HD_BYTES(n<<3,___sF64VECTOR);
#define ___ADD_F64VECTOR_ELEM(i,val)((___F64*)___ptr)[i]=(val);
#define ___END_ALLOC_F64VECTOR(n)___ALLOC(___WORDS(n<<3)+2);}
#define ___GET_F64VECTOR(n)___TAG((((___WORD*)((___WORD)(___hp-___WORDS(n<<3))&~7))-1),___tSUBTYPED)

#else

#define ___BEGIN_ALLOC_F64VECTOR(n) \
___hp[0]=___MAKE_HD_BYTES(n<<3,___sF64VECTOR);
#define ___ADD_F64VECTOR_ELEM(i,val)((___F64*)(___hp+1))[i]=(val);
#define ___END_ALLOC_F64VECTOR(n)___ALLOC(___WORDS(n<<3)+1);
#define ___GET_F64VECTOR(n)___TAG((___hp-___WORDS(n<<3)-1),___tSUBTYPED)

#endif

#define ___BEGIN_ALLOC_VECTOR(n)___hp[0]=___MAKE_HD_WORDS(n,___sVECTOR);
#define ___ADD_VECTOR_ELEM(i,val)___hp[i+1]=(val);
#define ___END_ALLOC_VECTOR(n)___ALLOC(n+1);
#define ___GET_VECTOR(n)___TAG((___hp-n-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_STRUCTURE(n)___hp[0]=___MAKE_HD_WORDS(n,___sSTRUCTURE);
#define ___ADD_STRUCTURE_ELEM(i,val)___hp[i+1]=(val);
#define ___END_ALLOC_STRUCTURE(n)___ALLOC(n+1);
#define ___GET_STRUCTURE(n)___TAG((___hp-n-1),___tSUBTYPED)

#define ___BEGIN_ALLOC_VALUES(n)___hp[0]=___MAKE_HD_WORDS(n,___sBOXVALUES);
#define ___ADD_VALUES_ELEM(i,val)___hp[i+1]=(val);
#define ___END_ALLOC_VALUES(n)___ALLOC(n+1);
#define ___GET_VALUES(n)___TAG((___hp-n-1),___tSUBTYPED)

#define ___NB_INTRS 4
#define ___INTR_USER      0
#define ___INTR_HEARTBEAT 1
#define ___INTR_GC        2
#define ___INTR_TERMINATE 3

#define ___INTERRUPT_FLAGS() (___ps->intr_flag[0]|___ps->intr_flag[1]|___ps->intr_flag[2]|___ps->intr_flag[3])

#define ___INTERRUPT_REQ(x, mask) (((x) & ___ps->intr_enabled & ~mask) != ___FIX(0))

#define ___INTERRUPT_MASK_SET(mask) \
if (___INTERRUPT_REQ(___INTERRUPT_FLAGS(), (___ps->intr_mask = mask))) \
  ___STACK_TRIP_ON()

#define ___STACK_TRIP_ON()___ps->stack_trip = ___ps->stack_start
#define ___STACK_TRIP_OFF()___ps->stack_trip = ___ps->stack_limit
#define ___STACK_TRIPPED (___fp < ___ps->stack_trip)

#ifdef ___HEARTBEAT_USING_POLL_COUNTDOWN
#define ___HEARTBEAT_INTERVAL_ENDED (___ps->heartbeat_countdown-- <= 0)
#define ___POLL_TRIGGER ___HEARTBEAT_INTERVAL_ENDED || ___STACK_TRIPPED
#else
#define ___POLL_TRIGGER ___STACK_TRIPPED
#endif

#ifdef ___DEBUG_STACK_LIMIT
#define ___POLL(n) \
if (___EXPECT_FALSE(___POLL_TRIGGER)) \
{___ps->temp1=___LBL(n); \
___ps->poll_file=__FILE__; \
___ps->poll_line=__LINE__; \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_stack_limit) \
}
#else
#define ___POLL(n) \
if (___EXPECT_FALSE(___POLL_TRIGGER)) \
{___ps->temp1=___LBL(n); \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_stack_limit) \
}
#endif

#define ___TASK_PUSH(i)
#define ___TASK_POP(n)

#ifdef ___DEBUG_HEAP_LIMIT
#define ___CHECK_HEAP(n,m) \
if (___EXPECT_FALSE(___hp>___ps->heap_limit)) \
{___ps->temp1=___LBL(n); \
___ps->check_heap_file=__FILE__; \
___ps->check_heap_line=__LINE__; \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_heap_limit) \
}
#else
#define ___CHECK_HEAP(n,m) \
if (___EXPECT_FALSE(___hp>___ps->heap_limit)) \
{___ps->temp1=___LBL(n); \
___JUMPEXTPRM(___NOTHING,___GSTATE->handler_heap_limit) \
}
#endif

#define ___FORCE1(n,src) \
if (___TYP((___temp=(src)))==___tSUBTYPED&&___SUBTYPE(___temp)==___sPROMISE<<___TB){___ps->temp1=___LBL(n);___ps->temp2=___temp;___JUMPEXTPRM(___NOTHING,___GSTATE->handler_force);
#define ___FORCE2 ___temp=___ps->temp2;}
#define ___FORCE3 ___temp

#define ___MODULE_KIND 0
#define ___LINKFILE_KIND 1

#define ___CLIBEXT(f)f
#define ___SETJMP(jmpbuf)setjmp (jmpbuf)
#define ___LONGJMP(jmpbuf,val)longjmp (jmpbuf,val)
#define ___EXT(f)f

#ifdef ___BIND_LATE

#ifndef ___CAN_IMPORT_CLIB_DYNAMICALLY
#undef ___CLIBEXT
#define ___CLIBEXT(f)(___GSTATE->f)
#undef ___LOCAL_GSTATE
#define ___LOCAL_GSTATE
#endif

#ifndef ___CAN_IMPORT_SETJMP_DYNAMICALLY
#undef ___SETJMP
#define ___SETJMP(x)(___GSTATE->setjmp) (x)
#endif

#ifndef ___CAN_IMPORT_DYNAMICALLY
#undef ___EXT
#define ___EXT(f)(___GSTATE->f)
#undef ___LOCAL_GSTATE
#define ___LOCAL_GSTATE
#endif

#endif

#ifdef ___LOCAL_GSTATE

#define ___GSTATE ___local_gstate
#define ___GSTATEDECL ___LOCAL ___global_state ___local_gstate;
#define ___SET_LOCAL_GSTATE(gs) ___local_gstate = gs;

#else

#define ___GSTATE (&___gstate0)
#define ___GSTATEDECL ___IMP_DATA(___global_state_struct,___gstate0);
#define ___SET_LOCAL_GSTATE(gs)

#endif

#ifdef ___USE_NO_THREAD_SYSTEM

/* Use direct access to the only pstate (this is probably fast) */

#define ___FAST_GET_PSTATE
#define ___GET_PSTATE() (&___GSTATE->vmstate0.pstate0)
#define ___SET_PSTATE(ps)

#else

#ifdef ___THREAD_LOCAL_STORAGE_CLASS

/* Use thread local storage class (this is probably fast) */

extern ___THREAD_LOCAL_STORAGE_CLASS void *___tls_ptr;

#define ___FAST_GET_PSTATE
#define ___GET_PSTATE() ___CAST(___processor_state,___tls_ptr)
#define ___SET_PSTATE(ps) ___tls_ptr = ___CAST(void*,ps)

#else

/* Use thread local storage getter/setter (this is probably slow) */

#define ___GET_PSTATE() ___CAST(___processor_state,___get_tls_ptr())
#define ___SET_PSTATE(ps) ___set_tls_ptr(___CAST(void*,ps))

#endif

#endif

#ifdef ___FAST_GET_PSTATE

/*
 * ___GET_PSTATE is fast, so it is acceptable to get the processor
 * state pointer at the top of every function that needs to access the
 * processor state.
 */

#define ___PSGET ___processor_state ___ps = ___PSTATE;

#define ___PSDNC
#define ___PSVNC

#define ___PSD
#define ___PSV
#define ___PSDKR

#define ___PSANC(ps)
#define ___PSA(ps)
#else

/*
 * ___GET_PSTATE is slow, so the processor state pointer will be
 * propagated from one function to its callees when possible.
 */

#define ___PSGET

#define ___PSDNC ___processor_state ___ps
#define ___PSVNC ___ps

#define ___PSD ___PSDNC,
#define ___PSV ___PSVNC,
#define ___PSDKR ___PSDNC;

#define ___PSANC(ps) ps
#define ___PSA(ps) ps,

#endif

#define ___PSPNC ___PSANC(___PSVNC)
#define ___PSP ___PSA(___PSVNC)

#ifdef ___SINGLE_THREADED_VMS
#define ___VMSTATE_FROM_PSTATE(ps) ___CAST(___virtual_machine_state,ps)
#else
#define ___VMSTATE_FROM_PSTATE(ps) ps->vmstate
#endif

#define ___PSTATE ___GET_PSTATE()
#define ___VMSTATE ___VMSTATE_FROM_PSTATE(___PSTATE)

#ifdef ___BIND_LATE

#define ___NEED_SYM(sym)
#define ___NEED_KEY(key)
#define ___NEED_GLO(glo)

#define ___BEGIN_SYM ___LOCAL ___UTF_8STRING ___sym_names[]={
#define ___DEF_SYM(i,sym,str)str,
#define ___END_SYM 0};

#define ___DEF_MOD_SYM(i,sym,str)

#define ___BEGIN_KEY ___LOCAL ___UTF_8STRING ___key_names[]={
#define ___DEF_KEY(i,key,str)str,
#define ___END_KEY 0};

#define ___DEF_MOD_KEY(i,key,str)

#define ___BEGIN_GLO ___LOCAL ___UTF_8STRING ___glo_names[]={
#define ___DEF_GLO(i,str)str,
#define ___END_GLO 0};

#define ___BEGIN_OLD_KEY
#define ___DEF_OLD_KEY(key)
#define ___END_OLD_KEY

#define ___BEGIN_OLD_SYM_GLO
#define ___DEF_OLD_SYM_GLO(sym,glo)
#define ___END_OLD_SYM_GLO

#define ___BEGIN_NEW_KEY
#define ___DEF_NEW_KEY(prevkey,key,str,hash)
#define ___END_NEW_KEY

#define ___BEGIN_NEW_SYM_GLO
#define ___DEF_NEW_SYM_GLO_SUP(prevsym,sym,str,hash,glo)
#define ___DEF_NEW_SYM_GLO(prevsym,sym,str,hash,glo)
#define ___END_NEW_SYM_GLO(prevsym,prevkey)___LINKFILE_DESCR(0,0)

#define ___DEF_SUB_NSTR(id,n)
#define ___NSTR0
#define ___NSTR1(a)
#define ___NSTR2(a,b)
#define ___NSTR3(a,b,c)
#define ___NSTR4(a,b,c,d)
#define ___NSTR5(a,b,c,d,e)
#define ___NSTR6(a,b,c,d,e,f)
#define ___NSTR7(a,b,c,d,e,f,g)
#define ___NSTR8(a,b,c,d,e,f,g,h)

#else

#define ___NEED_SYM(sym)___IMP_DATA(___symkey_struct,sym);
#define ___NEED_KEY(key)___IMP_DATA(___symkey_struct,key);
#define ___NEED_GLO(glo)___IMP_DATA(___glo_struct,glo);

#ifndef ___IMPORTED_ADR_IS_CONST

#define ___BEGIN_SYM ___LOCAL ___FAKEWORD ___symtbl[___SYMCOUNT];
#define ___DEF_SYM(i,sym,str)
#define ___END_SYM

#define ___DEF_MOD_SYM(i,sym,str)___symtbl[i]=(___FAKEWORD)(sym);

#define ___BEGIN_KEY ___LOCAL ___FAKEWORD ___keytbl[___KEYCOUNT];
#define ___DEF_KEY(i,key,str)
#define ___END_KEY

#define ___DEF_MOD_KEY(i,key,str)___keytbl[i]=(___FAKEWORD)(key);

#else

#define ___BEGIN_SYM ___LOCAL ___FAKEWORD ___symtbl[]={
#define ___DEF_SYM(i,sym,str)(___FAKEWORD)(sym),
#define ___END_SYM 0};

#define ___DEF_MOD_SYM(i,sym,str)

#define ___BEGIN_KEY ___LOCAL ___FAKEWORD ___keytbl[]={
#define ___DEF_KEY(i,key,str)(___FAKEWORD)(key),
#define ___END_KEY 0};

#define ___DEF_MOD_KEY(i,key,str)

#endif

#define ___BEGIN_GLO
#define ___DEF_GLO(i,str)
#define ___END_GLO

#define ___BEGIN_OLD_KEY
#define ___DEF_OLD_KEY(key)
#define ___END_OLD_KEY

#define ___BEGIN_OLD_SYM_GLO
#define ___DEF_OLD_SYM_GLO(sym,glo)
#define ___END_OLD_SYM_GLO

#define ___BEGIN_NEW_KEY
#define ___DEF_NEW_KEY(prevkey,key,str,hash) \
___EXP_DATA(___symkey_struct,key)={(___FAKEWORD)prevkey,(___FAKEWORD)str,0,0,0 ___PADDING};
#define ___END_NEW_KEY

#define ___BEGIN_NEW_SYM_GLO
#define ___DEF_NEW_SYM_GLO_SUP(prevsym,sym,str,hash,glo) \
___EXP_DATA(___glo_struct,glo) = {___UNB2, ___FIX(hash), 0}; \
___EXP_DATA(___symkey_struct,sym)={(___FAKEWORD)prevsym,(___FAKEWORD)str,0,0,(___FAKEWORD)&glo ___PADDING};
#define ___DEF_NEW_SYM_GLO(prevsym,sym,str,hash,glo) \
___EXP_DATA(___glo_struct,glo) = {___UNB1, ___FIX(hash), 0}; \
___EXP_DATA(___symkey_struct,sym)={(___FAKEWORD)prevsym,(___FAKEWORD)str,0,0,(___FAKEWORD)&glo ___PADDING};
#define ___END_NEW_SYM_GLO(prevsym,prevkey)___LINKFILE_DESCR(prevsym,prevkey)

#define ___DEF_SUB_NSTR(id,n) ___DEF_SUB_STR(id,n)
#define ___NSTR0 ___STR0
#define ___NSTR1(a) ___STR1(a)
#define ___NSTR2(a,b) ___STR2(a,b)
#define ___NSTR3(a,b,c) ___STR3(a,b,c)
#define ___NSTR4(a,b,c,d) ___STR4(a,b,c,d)
#define ___NSTR5(a,b,c,d,e) ___STR5(a,b,c,d,e)
#define ___NSTR6(a,b,c,d,e,f) ___STR6(a,b,c,d,e,f)
#define ___NSTR7(a,b,c,d,e,f,g) ___STR7(a,b,c,d,e,f,g)
#define ___NSTR8(a,b,c,d,e,f,g,h) ___STR8(a,b,c,d,e,f,g,h)

#endif

#define ___BEGIN_CNS \
___LOCAL ___WORD ___cnstbl[]={
#define ___DEF_CNS(car,cdr)___MAKE_HD((___PAIR_SIZE<<___LWS),___sPAIR,___PERM),cdr,car
#define ___END_CNS ___PADDING};

#define ___BEGIN_SUB \
___LOCAL ___FAKEWORD ___subtbl[]={
#define ___DEF_SUB(id)___CAST_WORDSTAR_TO_FAKEWORD(id)
#define ___END_SUB };

#define ___DEF_SUB_VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<___LWS),___sVECTOR,___PERM)

#define ___DEF_SUB_STRUCT(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<___LWS),___sSTRUCTURE,___PERM)/*****************/

#define ___DEF_SUB_STRUCTURE(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<___LWS),___sSTRUCTURE,___PERM)

#define ___DEF_SUB_BOX(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<___LWS),___sBOXVALUES,___PERM)

#define ___DEF_SUB_STR(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<___LCS),___sSTRING,___PERM)

#define ___DEF_SUB_RAT(id,num,den) \
___LOCAL ___WORD id[]={___MAKE_HD((___RATNUM_SIZE<<___LWS),___sRATNUM,___PERM),num,den ___PADDING};

#define ___DEF_SUB_FLO(id,hi,lo) \
___LOCAL ___WORD id[]={___MAKE_HD((___FLONUM_SIZE<<___LWS),___sFLONUM,___PERM) \
___F64VEC1(hi,lo)___F64VEC0

#define ___DEF_SUB_CPX(id,real,imag) \
___LOCAL ___WORD id[]={___MAKE_HD((___CPXNUM_SIZE<<___LWS),___sCPXNUM,___PERM),real,imag ___PADDING};

#define ___DEF_SUB_S8VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD(n,___sS8VECTOR,___PERM)

#define ___DEF_SUB_U8VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD(n,___sU8VECTOR,___PERM)

#define ___DEF_SUB_S16VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<1),___sS16VECTOR,___PERM)

#define ___DEF_SUB_U16VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<1),___sU16VECTOR,___PERM)

#define ___DEF_SUB_S32VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<2),___sS32VECTOR,___PERM)

#define ___DEF_SUB_U32VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<2),___sU32VECTOR,___PERM)

#define ___DEF_SUB_S64VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<3),___sS64VECTOR,___PERM)

#define ___DEF_SUB_U64VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<3),___sU64VECTOR,___PERM)

#define ___DEF_SUB_F32VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<2),___sF32VECTOR,___PERM)

#define ___DEF_SUB_F64VEC(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<3),___sF64VECTOR,___PERM)

#if ___SCMOBJ_WIDTH == 32

#ifdef ___BIG_ENDIAN

#define ___P4U8(a,b,c,d)((((((___WORD)___CAST_U8(a)<<8)+(___WORD)___CAST_U8(b))<<8)+(___WORD)___CAST_U8(c))<<8)+(___WORD)___CAST_U8(d)

#define ___P2U16(a,b)((___WORD)___CAST_U16(a)<<16)+(___WORD)___CAST_U16(b)

#define ___P1U32(a)a

#define ___P1U64(hi,lo)hi,lo

#else

#define ___P4U8(d,c,b,a)((((((___WORD)___CAST_U8(a)<<8)+(___WORD)___CAST_U8(b))<<8)+(___WORD)___CAST_U8(c))<<8)+(___WORD)___CAST_U8(d)

#define ___P2U16(b,a)((___WORD)___CAST_U16(a)<<16)+(___WORD)___CAST_U16(b)

#define ___P1U32(a)a

#define ___P1U64(hi,lo)lo,hi

#endif

#define ___S8VEC0 ___PADDING};
#define ___S8VEC1(a),___P4U8(a,0,0,0) ___PADDING};
#define ___S8VEC2(a,b),___P4U8(a,b,0,0) ___PADDING};
#define ___S8VEC3(a,b,c),___P4U8(a,b,c,0) ___PADDING};
#define ___S8VEC4(a,b,c,d),___P4U8(a,b,c,d) ___PADDING};
#define ___S8VEC5(a,b,c,d,e),___P4U8(a,b,c,d),___P4U8(e,0,0,0) ___PADDING};
#define ___S8VEC6(a,b,c,d,e,f),___P4U8(a,b,c,d),___P4U8(e,f,0,0) ___PADDING};
#define ___S8VEC7(a,b,c,d,e,f,g),___P4U8(a,b,c,d),___P4U8(e,f,g,0) ___PADDING};
#define ___S8VEC8(a,b,c,d,e,f,g,h),___P4U8(a,b,c,d),___P4U8(e,f,g,h)

#define ___U8VEC0 ___PADDING};
#define ___U8VEC1(a),___P4U8(a,0,0,0) ___PADDING};
#define ___U8VEC2(a,b),___P4U8(a,b,0,0) ___PADDING};
#define ___U8VEC3(a,b,c),___P4U8(a,b,c,0) ___PADDING};
#define ___U8VEC4(a,b,c,d),___P4U8(a,b,c,d) ___PADDING};
#define ___U8VEC5(a,b,c,d,e),___P4U8(a,b,c,d),___P4U8(e,0,0,0) ___PADDING};
#define ___U8VEC6(a,b,c,d,e,f),___P4U8(a,b,c,d),___P4U8(e,f,0,0) ___PADDING};
#define ___U8VEC7(a,b,c,d,e,f,g),___P4U8(a,b,c,d),___P4U8(e,f,g,0) ___PADDING};
#define ___U8VEC8(a,b,c,d,e,f,g,h),___P4U8(a,b,c,d),___P4U8(e,f,g,h)

#define ___S16VEC0 ___PADDING};
#define ___S16VEC1(a),___P2U16(a,0) ___PADDING};
#define ___S16VEC2(a,b),___P2U16(a,b) ___PADDING};
#define ___S16VEC3(a,b,c),___P2U16(a,b),___P2U16(c,0) ___PADDING};
#define ___S16VEC4(a,b,c,d),___P2U16(a,b),___P2U16(c,d)

#define ___U16VEC0 ___PADDING};
#define ___U16VEC1(a),___P2U16(a,0) ___PADDING};
#define ___U16VEC2(a,b),___P2U16(a,b) ___PADDING};
#define ___U16VEC3(a,b,c),___P2U16(a,b),___P2U16(c,0) ___PADDING};
#define ___U16VEC4(a,b,c,d),___P2U16(a,b),___P2U16(c,d)

#define ___S32VEC0 ___PADDING};
#define ___S32VEC1(a),___P1U32(a) ___PADDING};
#define ___S32VEC2(a,b),___P1U32(a),___P1U32(b)

#define ___U32VEC0 ___PADDING};
#define ___U32VEC1(a),___P1U32(a) ___PADDING};
#define ___U32VEC2(a,b),___P1U32(a),___P1U32(b)

#else

#ifdef ___BIG_ENDIAN

#define ___P8U8(a,b,c,d,e,f,g,h)((((((((((((((___WORD)___CAST_U8(a)<<8)+(___WORD)___CAST_U8(b))<<8)+(___WORD)___CAST_U8(c))<<8)+(___WORD)___CAST_U8(d))<<8)+(___WORD)___CAST_U8(e))<<8)+(___WORD)___CAST_U8(f))<<8)+(___WORD)___CAST_U8(g))<<8)+(___WORD)___CAST_U8(h)

#define ___P4U16(a,b,c,d)((((((___WORD)___CAST_U16(a)<<16)+(___WORD)___CAST_U16(b))<<16)+(___WORD)___CAST_U16(c))<<16)+(___WORD)___CAST_U16(d)

#define ___P2U32(a,b)((___WORD)___CAST_U32(a)<<32)+(___WORD)___CAST_U32(b)

#else

#define ___P8U8(h,g,f,e,d,c,b,a)((((((((((((((___WORD)___CAST_U8(a)<<8)+(___WORD)___CAST_U8(b))<<8)+(___WORD)___CAST_U8(c))<<8)+(___WORD)___CAST_U8(d))<<8)+(___WORD)___CAST_U8(e))<<8)+(___WORD)___CAST_U8(f))<<8)+(___WORD)___CAST_U8(g))<<8)+(___WORD)___CAST_U8(h)

#define ___P4U16(d,c,b,a)((((((___WORD)___CAST_U16(a)<<16)+(___WORD)___CAST_U16(b))<<16)+(___WORD)___CAST_U16(c))<<16)+(___WORD)___CAST_U16(d)

#define ___P2U32(b,a)((___WORD)___CAST_U32(a)<<32)+(___WORD)___CAST_U32(b)

#endif

#define ___P1U64(hi,lo)((___WORD)(hi)<<32)+___CAST_U32(lo)

#define ___S8VEC0 ___PADDING};
#define ___S8VEC1(a),___P8U8(a,0,0,0,0,0,0,0) ___PADDING};
#define ___S8VEC2(a,b),___P8U8(a,b,0,0,0,0,0,0) ___PADDING};
#define ___S8VEC3(a,b,c),___P8U8(a,b,c,0,0,0,0,0) ___PADDING};
#define ___S8VEC4(a,b,c,d),___P8U8(a,b,c,d,0,0,0,0) ___PADDING};
#define ___S8VEC5(a,b,c,d,e),___P8U8(a,b,c,d,e,0,0,0) ___PADDING};
#define ___S8VEC6(a,b,c,d,e,f),___P8U8(a,b,c,d,e,f,0,0) ___PADDING};
#define ___S8VEC7(a,b,c,d,e,f,g),___P8U8(a,b,c,d,e,f,g,0) ___PADDING};
#define ___S8VEC8(a,b,c,d,e,f,g,h),___P8U8(a,b,c,d,e,f,g,h)

#define ___U8VEC0 ___PADDING};
#define ___U8VEC1(a),___P8U8(a,0,0,0,0,0,0,0) ___PADDING};
#define ___U8VEC2(a,b),___P8U8(a,b,0,0,0,0,0,0) ___PADDING};
#define ___U8VEC3(a,b,c),___P8U8(a,b,c,0,0,0,0,0) ___PADDING};
#define ___U8VEC4(a,b,c,d),___P8U8(a,b,c,d,0,0,0,0) ___PADDING};
#define ___U8VEC5(a,b,c,d,e),___P8U8(a,b,c,d,e,0,0,0) ___PADDING};
#define ___U8VEC6(a,b,c,d,e,f),___P8U8(a,b,c,d,e,f,0,0) ___PADDING};
#define ___U8VEC7(a,b,c,d,e,f,g),___P8U8(a,b,c,d,e,f,g,0) ___PADDING};
#define ___U8VEC8(a,b,c,d,e,f,g,h),___P8U8(a,b,c,d,e,f,g,h)

#define ___S16VEC0 ___PADDING};
#define ___S16VEC1(a),___P4U16(a,0,0,0) ___PADDING};
#define ___S16VEC2(a,b),___P4U16(a,b,0,0) ___PADDING};
#define ___S16VEC3(a,b,c),___P4U16(a,b,c,0) ___PADDING};
#define ___S16VEC4(a,b,c,d),___P4U16(a,b,c,d)

#define ___U16VEC0 ___PADDING};
#define ___U16VEC1(a),___P4U16(a,0,0,0) ___PADDING};
#define ___U16VEC2(a,b),___P4U16(a,b,0,0) ___PADDING};
#define ___U16VEC3(a,b,c),___P4U16(a,b,c,0) ___PADDING};
#define ___U16VEC4(a,b,c,d),___P4U16(a,b,c,d)

#define ___S32VEC0 ___PADDING};
#define ___S32VEC1(a),___P2U32(a,0) ___PADDING};
#define ___S32VEC2(a,b),___P2U32(a,b)

#define ___U32VEC0 ___PADDING};
#define ___U32VEC1(a),___P2U32(a,0) ___PADDING};
#define ___U32VEC2(a,b),___P2U32(a,b)

#endif

#define ___S64VEC0 ___PADDING_64};
#define ___S64VEC1(hi,lo),___P1U64(hi,lo)

#define ___U64VEC0 ___PADDING_64};
#define ___U64VEC1(hi,lo),___P1U64(hi,lo)

#define ___STR0 ___CS_SELECT( \
___U8VEC0, \
___U16VEC0, \
___U32VEC0)

#define ___STR1(a)___CS_SELECT( \
___U8VEC1(a), \
___U16VEC1(a), \
___U32VEC1(a))

#define ___STR2(a,b)___CS_SELECT( \
___U8VEC2(a,b), \
___U16VEC2(a,b), \
___U32VEC2(a,b)___U32VEC0)

#define ___STR3(a,b,c)___CS_SELECT( \
___U8VEC3(a,b,c), \
___U16VEC3(a,b,c), \
___U32VEC2(a,b)___U32VEC1(c))

#define ___STR4(a,b,c,d)___CS_SELECT( \
___U8VEC4(a,b,c,d), \
___U16VEC4(a,b,c,d)___U16VEC0, \
___U32VEC2(a,b)___U32VEC2(c,d)___U32VEC0)

#define ___STR5(a,b,c,d,e)___CS_SELECT( \
___U8VEC5(a,b,c,d,e), \
___U16VEC4(a,b,c,d)___U16VEC1(e), \
___U32VEC2(a,b)___U32VEC2(c,d)___U32VEC1(e))

#define ___STR6(a,b,c,d,e,f)___CS_SELECT( \
___U8VEC6(a,b,c,d,e,f), \
___U16VEC4(a,b,c,d)___U16VEC2(e,f), \
___U32VEC2(a,b)___U32VEC2(c,d)___U32VEC2(e,f)___U32VEC0)

#define ___STR7(a,b,c,d,e,f,g)___CS_SELECT( \
___U8VEC7(a,b,c,d,e,f,g), \
___U16VEC4(a,b,c,d)___U16VEC3(e,f,g), \
___U32VEC2(a,b)___U32VEC2(c,d)___U32VEC2(e,f)___U32VEC1(g))

#define ___STR8(a,b,c,d,e,f,g,h)___CS_SELECT( \
___U8VEC8(a,b,c,d,e,f,g,h), \
___U16VEC4(a,b,c,d)___U16VEC4(e,f,g,h), \
___U32VEC2(a,b)___U32VEC2(c,d)___U32VEC2(e,f)___U32VEC2(g,h))

#if ___BIG_ABASE_WIDTH == 32

#define ___DEF_SUB_BIG(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((n<<2),___sBIGNUM,___PERM)

#define ___BIG0 ___U32VEC0
#define ___BIG1(a)___U32VEC1(a)
#define ___BIG2(a,b)___U32VEC2(a,b)

#else

#define ___DEF_SUB_BIG(id,n) \
___LOCAL ___WORD id[]={___MAKE_HD((((n+1)>>1)<<3),___sBIGNUM,___PERM)

#define ___BIG0 ___U64VEC0
#define ___BIG1(a)___BIG2(a,(___WORD)((a) & -0x80000000)?-1:0)___U64VEC0
#define ___BIG2(a,b)___U64VEC1(b,a)

#endif

#define ___DEF_SUB_BIGFIX(id,n)___DEF_SUB_BIG(id,n)

#define ___BIGFIX0 ___BIG0
#define ___BIGFIX1(a)___BIG1(a)
#define ___BIGFIX2(a,b)___BIG2(a,b)

#define ___F32VEC0 ___U32VEC0
#define ___F32VEC1(a)___U32VEC1(a)
#define ___F32VEC2(a,b)___U32VEC2(a,b)

#define ___F64VEC0 ___U64VEC0
#ifdef ___CRAY_FP_FORMAT
#define ___F64VEC1(hi,lo)___U64VEC1( \
((hi&0x7ff00000==0)?hi: \
((hi&0x80000000)+((hi>>4)&0x7ff0000)+0x3c028000+((hi>>5)&0x7fff))), \
((hi&0x7ff00000==0)?0: \
(((hi<<27)&0xf8000000)|((lo>>5)&0x7ffffff))))
#else
#define ___F64VEC1(hi,lo)___U64VEC1(hi,lo)
#endif

#define ___VEC0 ___PADDING};
#define ___VEC1(a),a

#define ___CEILING_DIV(n,m)(((n)+(m)-1)/(m))
#define ___ROUND_TO_MULT(n,m)(___CEILING_DIV(n,m)*(m))
#define ___BREAK_FRAME_NEXT 1/********************should be 0*/
#define ___BREAK_FRAME_SPACE ___ROUND_TO_MULT(1,___FRAME_ALIGN)

#define ___FRAME_SPACE(n)___ROUND_TO_MULT((n)+___FRAME_RESERVE,___FRAME_ALIGN)
#define ___FRAME_RESERVE 3
#define ___FRAME_ALIGN 4

#define ___BEGIN_LBL \
___LOCAL ___label_struct ___lbltbl[]={
#define ___DEF_LBL_INTRO(id,name,info,nlbls,cproc){___MAKE_HD((nlbls<<___LWS),___sVECTOR,___PERM),info,___CAST_VOIDSTAR_TO_FAKEVOIDSTAR(name),___CAST_HOST_TO_FAKEHOST(___CAST(___host,cproc))}
#define ___DEF_LBL_PROC(id,nbp,nbc){___PRD(nbp,nbc),0,0,___CAST_HOST_TO_FAKEHOST(___SM(___MH_PROC,id))}
#define ___DEF_LBL_RET(id,frm){___MAKE_HD((3<<___LWS),___sRETURN,___PERM),frm,0,___CAST_HOST_TO_FAKEHOST(___SM(___MH_PROC,id))}

#define ___END_LBL ___PADDING_LBL};

#ifdef ___OFDCOUNT
#define ___OFDTBL ___ofdtbl,sizeof(___ofdtbl)/sizeof(___WORD)
#else
#define ___OFDTBL 0,0
#endif

#define ___BEGIN_OFD \
___LOCAL ___WORD ___ofdtbl[]={
#define ___END_OFD ___PADDING};

#define ___DEF_OFD(kind,fs,link)(link<<16)+(fs<<2)+kind
#define ___OFD_KIND(x)((x)&((1<<2)-1))
#define ___OFD_FS(x)(((x)>>2)&((1<<14)-1))
#define ___OFD_LINK(x)(((x)>>16)&((1<<14)-1))

#define ___GCMAP0
#define ___GCMAP1(a),a
#if ___SCMOBJ_WIDTH == 32
#define ___GCMAP2(a,b),a,b
#else
#define ___GCMAP2(a,b),((___WORD)b<<32)+___CAST_U32(a)
#endif

#define ___U64VEC0 ___PADDING_64};
#define ___U64VEC1(hi,lo),___P1U64(hi,lo)

#define ___PRD(nbparms,nbclosed) \
___MAKE_HD(((nbclosed+1)<<12)+nbparms,___sPROCEDURE,___PERM)
#define ___PRD_NBPARMS(x)(((x)>>(___SB+___HTB))&((1<<12)-1))
#define ___PRD_NBCLOSED(x)((((x)>>(___SB+___HTB+12))&((1<<12)-1))-1)

#define ___IFD(kind,fs,link,gcmap)(gcmap<<12)+(link<<7)+(fs<<2)+kind
#define ___OFD(kind,fs,link,gcmap)___IFD(kind,0,0,0)
#define ___IS_IFD(x)((x)&3)

#define ___IFD_KIND(x)((x)&((1<<2)-1))
#define ___IFD_FS(x)(((x)>>2)&((1<<5)-1))
#define ___IFD_LINK(x)(((x)>>7)&((1<<5)-1))
#define ___IFD_GCMAP(x)(((x)>>12)&((1<<20)-1))


#define ___RETI_CFS_TO_FS(fs) \
___ROUND_TO_MULT(fs,___FRAME_ALIGN)+___FRAME_SPACE(___NB_GVM_REGS+1)-___FRAME_RESERVE

#define ___RETI_GET_CFS(ra,fs) \
{ ___WORD descr = ___LABEL_ENTRY_OR_DESCR(ra); \
if (___IS_IFD(descr)) \
fs = ___IFD_FS(descr); \
else \
fs = ___OFD_FS(*(___WORD*)descr); }

#define ___RETI_GET_FS(ra,fs) \
{ ___WORD descr = ___LABEL_ENTRY_OR_DESCR(ra); \
if (___IS_IFD(descr)) \
fs = ___RETI_CFS_TO_FS(___IFD_FS(descr)); \
else \
fs = ___RETI_CFS_TO_FS(___OFD_FS(*(___WORD*)descr)); }

#define ___RETN_GET_FS(ra,fs) \
{ ___WORD descr = ___LABEL_ENTRY_OR_DESCR(ra); \
if (___IS_IFD(descr)) \
fs = ___IFD_FS(descr); \
else \
fs = ___OFD_FS(*(___WORD*)descr); }

#define ___RETI_GET_FS_LINK(ra,fs,link) \
{ ___WORD descr = ___LABEL_ENTRY_OR_DESCR(ra); \
if (___IS_IFD(descr)) \
{ fs = ___RETI_CFS_TO_FS(___IFD_FS(descr)); link = ___IFD_LINK(descr); } \
else \
{ descr = *(___WORD*)descr; \
fs = ___RETI_CFS_TO_FS(___OFD_FS(descr)); link = ___OFD_LINK(descr); } }

#define ___RETN_GET_FS_LINK(ra,fs,link) \
{ ___WORD descr = ___LABEL_ENTRY_OR_DESCR(ra); \
if (___IS_IFD(descr)) \
{ fs = ___IFD_FS(descr); link = ___IFD_LINK(descr); } \
else \
{ descr = *(___WORD*)descr; \
fs = ___OFD_FS(descr); link = ___OFD_LINK(descr); } }

#define ___RETI_GET_FS_LINK_GCMAP(ra,fs,link,firstgcmap,nextgcmap) \
{ ___WORD descr = ___LABEL_ENTRY_OR_DESCR(ra); \
if (___IS_IFD(descr)) \
{ fs = ___RETI_CFS_TO_FS(___IFD_FS(descr)); link = ___IFD_LINK(descr); \
firstgcmap = ___IFD_GCMAP(descr); } \
else \
{ nextgcmap = (___WORD*)descr; descr = *nextgcmap++; firstgcmap = *nextgcmap++; \
fs = ___RETI_CFS_TO_FS(___OFD_FS(descr)); link = ___OFD_LINK(descr); } }

#define ___RETN_GET_FS_LINK_GCMAP(ra,fs,link,firstgcmap,nextgcmap) \
{ ___WORD descr = ___LABEL_ENTRY_OR_DESCR(ra); \
if (___IS_IFD(descr)) \
{ firstgcmap = ___IFD_GCMAP(descr); \
fs = ___IFD_FS(descr); link = ___IFD_LINK(descr); } \
else \
{ nextgcmap = (___WORD*)descr; descr = *nextgcmap++; firstgcmap = *nextgcmap++; \
fs = ___OFD_FS(descr); link = ___OFD_LINK(descr); } }




#define ___RETN 1
#define ___RETI 2
#define ___RETT 3

#ifdef ___GLOCOUNT
#ifdef ___BIND_LATE
#define ___GLODECL ___LOCAL ___FAKEWORD ___glotbl[___GLOCOUNT];
#define ___GLOTBL ___glotbl,___GLOCOUNT,___SUPCOUNT,___glo_names
#else
#define ___GLODECL
#define ___GLOTBL 0,0,0,0
#endif
#else
#define ___GLODECL
#define ___GLOTBL 0,0,0,0
#endif

#ifdef ___SYMCOUNT
#ifdef ___BIND_LATE
#define ___SYMDECL ___LOCAL ___FAKEWORD ___symtbl[___SYMCOUNT];
#define ___SYMTBL ___symtbl,___SYMCOUNT,___sym_names
#else
#define ___SYMDECL
#define ___SYMTBL ___symtbl,___SYMCOUNT,0
#endif
#else
#define ___SYMDECL
#define ___SYMTBL 0,0,0
#endif

#ifdef ___KEYCOUNT
#ifdef ___BIND_LATE
#define ___KEYDECL ___LOCAL ___FAKEWORD ___keytbl[___KEYCOUNT];
#define ___KEYTBL ___keytbl,___KEYCOUNT,___key_names
#else
#define ___KEYDECL
#define ___KEYTBL ___keytbl,___KEYCOUNT,0
#endif
#else
#define ___KEYDECL
#define ___KEYTBL 0,0,0
#endif

#ifdef ___LBLCOUNT
#define ___LBLTBL &___lp,___lbltbl,___LBLCOUNT
#else
#define ___LBLTBL 0,0,0
#endif

#ifdef ___CNSCOUNT
#define ___CNSTBL ___cnstbl,___CNSCOUNT
#else
#define ___CNSTBL 0,0
#endif

#ifdef ___SUBCOUNT
#define ___SUBTBL ___subtbl,___SUBCOUNT
#else
#define ___SUBTBL 0,0
#endif

#define ___BEGIN_MOD_PRM ___LOCAL ___WORD ___setup_mod ___PVOID {
#define ___DEF_MOD_PRM(i,glo,n)___PRM(i,glo)=___MLBL(n);
#define ___END_MOD_PRM return ___FIX(___NO_ERR); }

#define ___BEGIN_MOD_C_INIT ___LOCAL ___WORD ___init_mod \
   ___P((___PSDNC), \
        (___PSVNC) \
___PSDKR) { ___PSGET
#define ___END_MOD_C_INIT

#define ___BEGIN_MOD_GLO
#define ___DEF_MOD_GLO(i,glo,n)___GLO(i,glo)=___MLBL(n);
#define ___END_MOD_GLO return ___FIX(___NO_ERR); }

#define ___BEGIN_MOD_SYM_KEY ___LOCAL ___module_struct ___module_descr = { \
  ___VERSION, \
  ___MODULE_KIND, \
  ___MODULE_NAME, \
  ___MODULE_FLAGS, \
  ___GLOTBL, \
  ___SYMTBL, \
  ___KEYTBL, \
  ___LBLTBL, \
  ___OFDTBL, \
  ___CNSTBL, \
  ___SUBTBL, \
  ___setup_mod, \
  ___init_mod, \
  ___SCRIPT_LINE, \
  0,\
  0,0,0,0,0,0,0,0 \
,___MODDESCR /* TODO: move with above */ \
}; \
___BEGIN_C_LINKAGE \
___EXP_FUNC(___mod_or_lnk,___LINKER_ID) \
   ___P((___global_state ___gs), \
        (___gs) \
___global_state ___gs;) \
{ \
  ___SET_LOCAL_GSTATE(___gs)
#define ___END_MOD_SYM_KEY \
  return (___mod_or_lnk)&___module_descr; \
} \
___END_C_LINKAGE

#ifdef ___LIBRARY

#define ___MAIN_PROC

#else

#ifdef ___OS_WIN32
#ifdef _WINDOWS

#define ___MAIN_PROC \
___IMP_FUNC(int,___winmain) \
  ___P((HINSTANCE hInstance, \
        HINSTANCE hPrevInstance, \
        LPSTR lpCmdLine, \
        int nCmdShow, \
        ___mod_or_lnk (*linker)(___global_state), \
        char *script_line), \
       ()); \
int WINAPI WinMain ___P((HINSTANCE hInstance, \
                         HINSTANCE hPrevInstance, \
                         LPSTR lpCmdLine, \
                         int nCmdShow), \
                        (hInstance, \
                         hPrevInstance, \
                         lpCmdLine, \
                         nCmdShow) \
HINSTANCE hInstance; \
HINSTANCE hPrevInstance; \
LPSTR lpCmdLine; \
int nCmdShow;) \
{ \
  return ___winmain \
           (hInstance, \
            hPrevInstance, \
            lpCmdLine, \
            nCmdShow, \
            ___LINKER_ID, \
            ___SCRIPT_LINE); \
}

#endif
#endif

#ifndef ___MAIN_PROC
#ifdef _UNICODE

#define ___MAIN_PROC \
___IMP_FUNC(int,___main_UCS_2) \
  ___P((int argc, \
        ___UCS_2STRING argv[], \
        ___mod_or_lnk (*linker)(___global_state), \
        char *script_line), \
       ()); \
int wmain ___P((int argc, \
                wchar_t *argv[]), \
               (argc, \
                argv) \
int argc; \
wchar_t *argv[];) \
{ \
  return ___main_UCS_2 \
           (argc, \
            argv, \
            ___LINKER_ID, \
            ___SCRIPT_LINE); \
}

#else

#define ___MAIN_PROC \
___IMP_FUNC(int,___main_char) \
  ___P((int argc, \
        char *argv[], \
        ___mod_or_lnk (*linker)(___global_state), \
        char *script_line), \
       ()); \
int main ___P((int argc, \
               char *argv[]), \
              (argc, \
               argv) \
int argc; \
char *argv[];) \
{ \
  return ___main_char \
           (argc, \
            argv, \
            ___LINKER_ID, \
            ___SCRIPT_LINE); \
}

#endif
#endif

#endif

#define ___LINKFILE_DESCR(sym_list,key_list) \
___LOCAL ___linkfile_struct ___linkfile_descr = { \
  ___VERSION, \
  ___LINKFILE_KIND, \
  ___LINKFILE_NAME, \
  sym_list, \
  key_list, \
  ___linkertbl, \
  0,0,0,0,0,0,0,0 \
}; \
___BEGIN_C_LINKAGE \
___EXP_FUNC(___mod_or_lnk,___LINKER_ID) \
   ___P((___global_state ___gs), \
        (___gs) \
___global_state ___gs;) \
{ \
  ___SET_LOCAL_GSTATE(___gs) \
  return (___mod_or_lnk)&___linkfile_descr; \
} \
___END_C_LINKAGE \
___MAIN_PROC

#define ___BEGIN_OLD_LNK
#define ___DEF_OLD_LNK(id)___BEGIN_C_LINKAGE ___IMP_FUNC(___mod_or_lnk,id) \
___P((___global_state ___gs),()); ___END_C_LINKAGE
#define ___END_OLD_LNK

#define ___BEGIN_NEW_LNK
#define ___DEF_NEW_LNK(id)___BEGIN_C_LINKAGE ___mod_or_lnk id \
___P((___global_state ___gs),()); ___END_C_LINKAGE
#define ___END_NEW_LNK

#define ___BEGIN_LNK ___LOCAL ___linkinfo ___linkertbl[]={
#define ___DEF_LNK(id){ ___CAST(___mod_or_lnk,id), ___FIX(1) }
#define ___DEF_LNK_NOPRELOAD(id){ ___CAST(___mod_or_lnk,id), ___FIX(0) }
#define ___END_LNK , { 0, ___FIX(0) }};

/*---------------------------------------------------------------------------*/

/*
 * ___ERR_CODE is a type which represents the union of error codes
 * from various subsystems.  Currently 6 types of error codes are
 * supported: Windows HRESULT, MACOS errors, ANSI-C errno, netdb
 * h_errno, getaddrinfo error codes, and system specific error codes.
 * A Windows HRESULT error code is a 32 bit signed integer value
 * composed of (starting with the low bits) a 16 bit status code, a 11
 * bit facility code, a 4 bit reserved facility code and a 1 bit
 * severity code (negative means error).  It seems that only the 4
 * lower bits of the facility code are really used, the remaining 7
 * bits are zero.  This allows us to compact this 32 bit integer value
 * to a 30 bit integer value (which fits in a fixnum) by dropping the
 * top 2 bits of the facility code.  Of the 512 possible facility
 * codes, the codes 448 to 511 are assigned to Gambit specific error
 * codes, the codes 384 to 447 are assigned to MACOS errors, the codes
 * 320 to 382 are assigned to ANSI-C errno error codes, the code 319
 * is assigned to netdb h_errno error codes, and the code 318 is
 * assigned to getaddrinfo error codes.  The ``no error'' error code
 * of each subsystem is always mapped to ___NO_ERR which is equal to
 * 0, all other error codes are thus negative values.
 */

#define ___ERR_CODE int

#define ___ERR_CODE_FACILITY_SYSTEM   448
#define ___ERR_CODE_FACILITY_MACOS    384
#define ___ERR_CODE_FACILITY_ERRNO    320
#define ___ERR_CODE_FACILITY_H_ERRNO  319
#define ___ERR_CODE_FACILITY_GAI_CODE 318

#define ___ERR_CODE_BUILD(facility,code) \
((___CAST(___ERR_CODE,-1)<<29)+(___CAST(___ERR_CODE,facility)<<16)+(code))

#define ___ERR_CODE_FACILITY(err)(((err)>>16)&~(~___CAST(___ERR_CODE,0)<<9))

#define ___HRESULT_ERR(hresult) \
(((hresult)&~(~___CAST(___ERR_CODE,0)<<25)) | \
(((hresult)&~___CAST(___ERR_CODE,0)<<27)>>2))

#define ___HRESULT_FROM_ERR_CODE(err) \
(((err)&~(~___CAST(___ERR_CODE,0)<<25)) | \
(((err)&~___CAST(___ERR_CODE,0)<<25)<<2))

#define ___WIN32_ERR(win32err) \
___HRESULT_ERR(HRESULT_FROM_WIN32(win32err))

#define ___WIN32_FROM_ERR_CODE(err) \
HRESULT_CODE(___HRESULT_FROM_ERR_CODE(err))

#define ___MACOS_ERR(oserr) \
((oserr)==0?___NO_ERR:___ERR_CODE_BUILD(___ERR_CODE_FACILITY_MACOS,oserr))

#define ___MACOS_FROM_ERR_CODE(err) \
((err)==___NO_ERR?0:((err)-___ERR_CODE_BUILD(___ERR_CODE_FACILITY_MACOS,0)))

#define ___ERRNO_ERR(errno) \
((errno)==0?___NO_ERR:___ERR_CODE_BUILD(___ERR_CODE_FACILITY_ERRNO,errno))

#define ___ERRNO_FROM_ERR_CODE(err) \
((err)==___NO_ERR?0:((err)-___ERR_CODE_BUILD(___ERR_CODE_FACILITY_ERRNO,0)))

#define ___H_ERRNO_ERR(h_errno) \
((h_errno)==0?___NO_ERR:___ERR_CODE_BUILD(___ERR_CODE_FACILITY_H_ERRNO,(h_errno)))

#define ___H_ERRNO_FROM_ERR_CODE(err) \
((err)==___NO_ERR?0:((err)-___ERR_CODE_BUILD(___ERR_CODE_FACILITY_H_ERRNO,0)))

#define ___GAI_CODE_ERR(gai_code) \
((gai_code)==0?___NO_ERR:___ERR_CODE_BUILD(___ERR_CODE_FACILITY_GAI_CODE,(gai_code)))

#define ___GAI_CODE_FROM_ERR_CODE(err) \
((err)==___NO_ERR?0:((err)-___ERR_CODE_BUILD(___ERR_CODE_FACILITY_GAI_CODE,0)))

#define ___ERR_BASE ___ERR_CODE_BUILD(___ERR_CODE_FACILITY_SYSTEM,0)

#define ___NO_ERR                               0
#define ___UNWIND_C_STACK                       (___ERR_BASE+0)
#define ___SFUN_HEAP_OVERFLOW_ERR               (___ERR_BASE+1)
#define ___IMPL_LIMIT_ERR                       (___ERR_BASE+2)
#define ___UNKNOWN_ERR                          (___ERR_BASE+3)
#define ___UNIMPL_ERR                           (___ERR_BASE+4)
#define ___HEAP_OVERFLOW_ERR                    (___ERR_BASE+5)
#define ___CLOSED_DEVICE_ERR                    (___ERR_BASE+6)
#define ___INVALID_OP_ERR                       (___ERR_BASE+7)
#define ___MODULE_VERSION_TOO_OLD_ERR           (___ERR_BASE+8)
#define ___MODULE_VERSION_TOO_NEW_ERR           (___ERR_BASE+9)
#define ___MODULE_ALREADY_LOADED_ERR            (___ERR_BASE+10)
#define ___DYNAMIC_LOADING_NOT_AVAILABLE_ERR    (___ERR_BASE+11)
#define ___DYNAMIC_LOADING_LOOKUP_ERR           (___ERR_BASE+12)
#define ___KILL_PUMP                            (___ERR_BASE+13)
#define ___SELECT_SETUP_DONE                    (___ERR_BASE+14)
#define ___STOC_BASE ___STOC_S8_ERR
#define ___STOC_S8_ERR                          (___ERR_BASE+(1<<7))
#define ___STOC_U8_ERR                          (___ERR_BASE+(2<<7))
#define ___STOC_S16_ERR                         (___ERR_BASE+(3<<7))
#define ___STOC_U16_ERR                         (___ERR_BASE+(4<<7))
#define ___STOC_S32_ERR                         (___ERR_BASE+(5<<7))
#define ___STOC_U32_ERR                         (___ERR_BASE+(6<<7))
#define ___STOC_S64_ERR                         (___ERR_BASE+(7<<7))
#define ___STOC_U64_ERR                         (___ERR_BASE+(8<<7))
#define ___STOC_F32_ERR                         (___ERR_BASE+(9<<7))
#define ___STOC_F64_ERR                         (___ERR_BASE+(10<<7))
#define ___STOC_CHAR_ERR                        (___ERR_BASE+(11<<7))
#define ___STOC_SCHAR_ERR                       (___ERR_BASE+(12<<7))
#define ___STOC_UCHAR_ERR                       (___ERR_BASE+(13<<7))
#define ___STOC_ISO_8859_1_ERR                  (___ERR_BASE+(14<<7))
#define ___STOC_UCS_2_ERR                       (___ERR_BASE+(15<<7))
#define ___STOC_UCS_4_ERR                       (___ERR_BASE+(16<<7))
#define ___STOC_WCHAR_ERR                       (___ERR_BASE+(17<<7))
#define ___STOC_SIZE_T_ERR                      (___ERR_BASE+(18<<7))
#define ___STOC_SSIZE_T_ERR                     (___ERR_BASE+(19<<7))
#define ___STOC_PTRDIFF_T_ERR                   (___ERR_BASE+(20<<7))
#define ___STOC_SHORT_ERR                       (___ERR_BASE+(21<<7))
#define ___STOC_USHORT_ERR                      (___ERR_BASE+(22<<7))
#define ___STOC_INT_ERR                         (___ERR_BASE+(23<<7))
#define ___STOC_UINT_ERR                        (___ERR_BASE+(24<<7))
#define ___STOC_LONG_ERR                        (___ERR_BASE+(25<<7))
#define ___STOC_ULONG_ERR                       (___ERR_BASE+(26<<7))
#define ___STOC_LONGLONG_ERR                    (___ERR_BASE+(27<<7))
#define ___STOC_ULONGLONG_ERR                   (___ERR_BASE+(28<<7))
#define ___STOC_FLOAT_ERR                       (___ERR_BASE+(29<<7))
#define ___STOC_DOUBLE_ERR                      (___ERR_BASE+(30<<7))
#define ___STOC_STRUCT_ERR                      (___ERR_BASE+(31<<7))
#define ___STOC_UNION_ERR                       (___ERR_BASE+(32<<7))
#define ___STOC_TYPE_ERR                        (___ERR_BASE+(33<<7))
#define ___STOC_POINTER_ERR                     (___ERR_BASE+(34<<7))
#define ___STOC_NONNULLPOINTER_ERR              (___ERR_BASE+(35<<7))
#define ___STOC_FUNCTION_ERR                    (___ERR_BASE+(36<<7))
#define ___STOC_NONNULLFUNCTION_ERR             (___ERR_BASE+(37<<7))
#define ___STOC_BOOL_ERR                        (___ERR_BASE+(38<<7))
#define ___STOC_CHARSTRING_ERR                  (___ERR_BASE+(39<<7))
#define ___STOC_NONNULLCHARSTRING_ERR           (___ERR_BASE+(40<<7))
#define ___STOC_NONNULLCHARSTRINGLIST_ERR       (___ERR_BASE+(41<<7))
#define ___STOC_ISO_8859_1STRING_ERR            (___ERR_BASE+(42<<7))
#define ___STOC_NONNULLISO_8859_1STRING_ERR     (___ERR_BASE+(43<<7))
#define ___STOC_NONNULLISO_8859_1STRINGLIST_ERR (___ERR_BASE+(44<<7))
#define ___STOC_UTF_8STRING_ERR                 (___ERR_BASE+(45<<7))
#define ___STOC_NONNULLUTF_8STRING_ERR          (___ERR_BASE+(46<<7))
#define ___STOC_NONNULLUTF_8STRINGLIST_ERR      (___ERR_BASE+(47<<7))
#define ___STOC_UTF_16STRING_ERR                (___ERR_BASE+(48<<7))
#define ___STOC_NONNULLUTF_16STRING_ERR         (___ERR_BASE+(49<<7))
#define ___STOC_NONNULLUTF_16STRINGLIST_ERR     (___ERR_BASE+(50<<7))
#define ___STOC_UCS_2STRING_ERR                 (___ERR_BASE+(51<<7))
#define ___STOC_NONNULLUCS_2STRING_ERR          (___ERR_BASE+(52<<7))
#define ___STOC_NONNULLUCS_2STRINGLIST_ERR      (___ERR_BASE+(53<<7))
#define ___STOC_UCS_4STRING_ERR                 (___ERR_BASE+(54<<7))
#define ___STOC_NONNULLUCS_4STRING_ERR          (___ERR_BASE+(55<<7))
#define ___STOC_NONNULLUCS_4STRINGLIST_ERR      (___ERR_BASE+(56<<7))
#define ___STOC_WCHARSTRING_ERR                 (___ERR_BASE+(57<<7))
#define ___STOC_NONNULLWCHARSTRING_ERR          (___ERR_BASE+(58<<7))
#define ___STOC_NONNULLWCHARSTRINGLIST_ERR      (___ERR_BASE+(59<<7))
#define ___STOC_VARIANT_ERR                     (___ERR_BASE+(60<<7))
#define ___STOC_HEAP_OVERFLOW_ERR               (___ERR_BASE+(61<<7))
#define ___STOC_MAX                             (___ERR_BASE+(62<<7)-1)
#define ___CTOS_BASE ___CTOS_S8_ERR
#define ___CTOS_S8_ERR                          (___ERR_BASE+(65<<7))
#define ___CTOS_U8_ERR                          (___ERR_BASE+(66<<7))
#define ___CTOS_S16_ERR                         (___ERR_BASE+(67<<7))
#define ___CTOS_U16_ERR                         (___ERR_BASE+(68<<7))
#define ___CTOS_S32_ERR                         (___ERR_BASE+(69<<7))
#define ___CTOS_U32_ERR                         (___ERR_BASE+(70<<7))
#define ___CTOS_S64_ERR                         (___ERR_BASE+(71<<7))
#define ___CTOS_U64_ERR                         (___ERR_BASE+(72<<7))
#define ___CTOS_F32_ERR                         (___ERR_BASE+(73<<7))
#define ___CTOS_F64_ERR                         (___ERR_BASE+(74<<7))
#define ___CTOS_CHAR_ERR                        (___ERR_BASE+(75<<7))
#define ___CTOS_SCHAR_ERR                       (___ERR_BASE+(76<<7))
#define ___CTOS_UCHAR_ERR                       (___ERR_BASE+(77<<7))
#define ___CTOS_ISO_8859_1_ERR                  (___ERR_BASE+(78<<7))
#define ___CTOS_UCS_2_ERR                       (___ERR_BASE+(79<<7))
#define ___CTOS_UCS_4_ERR                       (___ERR_BASE+(80<<7))
#define ___CTOS_WCHAR_ERR                       (___ERR_BASE+(81<<7))
#define ___CTOS_SIZE_T_ERR                      (___ERR_BASE+(82<<7))
#define ___CTOS_SSIZE_T_ERR                     (___ERR_BASE+(83<<7))
#define ___CTOS_PTRDIFF_T_ERR                   (___ERR_BASE+(84<<7))
#define ___CTOS_SHORT_ERR                       (___ERR_BASE+(85<<7))
#define ___CTOS_USHORT_ERR                      (___ERR_BASE+(86<<7))
#define ___CTOS_INT_ERR                         (___ERR_BASE+(87<<7))
#define ___CTOS_UINT_ERR                        (___ERR_BASE+(88<<7))
#define ___CTOS_LONG_ERR                        (___ERR_BASE+(89<<7))
#define ___CTOS_ULONG_ERR                       (___ERR_BASE+(90<<7))
#define ___CTOS_LONGLONG_ERR                    (___ERR_BASE+(91<<7))
#define ___CTOS_ULONGLONG_ERR                   (___ERR_BASE+(92<<7))
#define ___CTOS_FLOAT_ERR                       (___ERR_BASE+(93<<7))
#define ___CTOS_DOUBLE_ERR                      (___ERR_BASE+(94<<7))
#define ___CTOS_STRUCT_ERR                      (___ERR_BASE+(95<<7))
#define ___CTOS_UNION_ERR                       (___ERR_BASE+(96<<7))
#define ___CTOS_TYPE_ERR                        (___ERR_BASE+(97<<7))
#define ___CTOS_POINTER_ERR                     (___ERR_BASE+(98<<7))
#define ___CTOS_NONNULLPOINTER_ERR              (___ERR_BASE+(99<<7))
#define ___CTOS_FUNCTION_ERR                    (___ERR_BASE+(100<<7))
#define ___CTOS_NONNULLFUNCTION_ERR             (___ERR_BASE+(101<<7))
#define ___CTOS_BOOL_ERR                        (___ERR_BASE+(102<<7))
#define ___CTOS_CHARSTRING_ERR                  (___ERR_BASE+(103<<7))
#define ___CTOS_NONNULLCHARSTRING_ERR           (___ERR_BASE+(104<<7))
#define ___CTOS_NONNULLCHARSTRINGLIST_ERR       (___ERR_BASE+(105<<7))
#define ___CTOS_ISO_8859_1STRING_ERR            (___ERR_BASE+(106<<7))
#define ___CTOS_NONNULLISO_8859_1STRING_ERR     (___ERR_BASE+(107<<7))
#define ___CTOS_NONNULLISO_8859_1STRINGLIST_ERR (___ERR_BASE+(108<<7))
#define ___CTOS_UTF_8STRING_ERR                 (___ERR_BASE+(109<<7))
#define ___CTOS_NONNULLUTF_8STRING_ERR          (___ERR_BASE+(110<<7))
#define ___CTOS_NONNULLUTF_8STRINGLIST_ERR      (___ERR_BASE+(111<<7))
#define ___CTOS_UTF_16STRING_ERR                (___ERR_BASE+(112<<7))
#define ___CTOS_NONNULLUTF_16STRING_ERR         (___ERR_BASE+(113<<7))
#define ___CTOS_NONNULLUTF_16STRINGLIST_ERR     (___ERR_BASE+(114<<7))
#define ___CTOS_UCS_2STRING_ERR                 (___ERR_BASE+(115<<7))
#define ___CTOS_NONNULLUCS_2STRING_ERR          (___ERR_BASE+(116<<7))
#define ___CTOS_NONNULLUCS_2STRINGLIST_ERR      (___ERR_BASE+(117<<7))
#define ___CTOS_UCS_4STRING_ERR                 (___ERR_BASE+(118<<7))
#define ___CTOS_NONNULLUCS_4STRING_ERR          (___ERR_BASE+(119<<7))
#define ___CTOS_NONNULLUCS_4STRINGLIST_ERR      (___ERR_BASE+(120<<7))
#define ___CTOS_WCHARSTRING_ERR                 (___ERR_BASE+(121<<7))
#define ___CTOS_NONNULLWCHARSTRING_ERR          (___ERR_BASE+(122<<7))
#define ___CTOS_NONNULLWCHARSTRINGLIST_ERR      (___ERR_BASE+(123<<7))
#define ___CTOS_VARIANT_ERR                     (___ERR_BASE+(124<<7))
#define ___CTOS_HEAP_OVERFLOW_ERR               (___ERR_BASE+(125<<7))
#define ___CTOS_MAX                             (___ERR_BASE+(126<<7)-1)

#define ___RETURN_POS 127

/*---------------------------------------------------------------------------*/

#define ___USE_RC_ALLOCATION_FOR_FOREIGN

#ifdef ___USE_RC_ALLOCATION_FOR_FOREIGN

#define ___CPLUSPLUS_ASSIGN_NEW(var,type) \
do { \
     void *___ptr = ___EXT(___alloc_rc) (___PSP sizeof (type)); \
     if (___ptr == 0) \
       var = 0; \
     else \
       var = new (___ptr) type; \
   } while (0)
#define ___CPLUSPLUS_ASSIGN_NEW_WITH_INIT(var,type,init) \
do { \
     void *___ptr = ___EXT(___alloc_rc) (___PSP sizeof (type)); \
     if (___ptr == 0) \
       var = 0; \
     else \
       var = new (___ptr) type (init); \
   } while (0)
#define ___CPLUSPLUS_DELETE_STRUCT(name,ptr) \
do { \
     ___EXT(___release_rc) (ptr); \
   } while (0)
#define ___CPLUSPLUS_DELETE_UNION(name,ptr) \
do { \
     ___EXT(___release_rc) (ptr); \
   } while (0)
#define ___CPLUSPLUS_DELETE_TYPE(name,ptr) \
do { \
     ___CAST(name*,ptr)->~name (); \
     ___EXT(___release_rc) (ptr); \
   } while (0)

#define ___C_ASSIGN_NEW(var,type) \
do { \
     var = ___CAST(type*,___EXT(___alloc_rc) (___PSP sizeof (type))); \
   } while (0)
#define ___C_ASSIGN_NEW_WITH_INIT(var,type,init) \
do { \
     if ((var = ___CAST(type*,___EXT(___alloc_rc) (___PSP sizeof (type)))) != 0) \
       *___CAST(type*,var) = init; \
   } while (0)
#define ___C_DELETE_STRUCT(name,ptr) \
do { \
     ___EXT(___release_rc) (ptr); \
   } while (0)
#define ___C_DELETE_UNION(name,ptr) \
do { \
     ___EXT(___release_rc) (ptr); \
   } while (0)
#define ___C_DELETE_TYPE(name,ptr) \
do { \
     ___EXT(___release_rc) (ptr); \
   } while (0)

#else

#define ___CPLUSPLUS_ASSIGN_NEW(var,type) \
do { \
     try { var = new type; } catch (std::bad_alloc) { var = 0; } \
   } while (0)
#define ___CPLUSPLUS_ASSIGN_NEW_WITH_INIT(var,type,init) \
do { \
     try { var = new type (init); } catch (std::bad_alloc) { var = 0; } \
   } while (0)
#define ___CPLUSPLUS_DELETE_STRUCT(name,ptr) \
do { \
     delete ___CAST(struct name*,ptr); \
   } while (0)
#define ___CPLUSPLUS_DELETE_UNION(name,ptr) \
do { \
     delete ___CAST(union name*,ptr); \
   } while (0)
#define ___CPLUSPLUS_DELETE_TYPE(name,ptr) \
do { \
     delete ___CAST(name*,ptr); \
   } while (0)

#define ___C_ASSIGN_NEW(var,type) \
do { \
     var = ___CAST(type*,___EXT(___alloc_mem) (sizeof (type))); \
   } while (0)
#define ___C_ASSIGN_NEW_WITH_INIT(var,type,init) \
do { \
     if ((var = ___CAST(type*,___EXT(___alloc_mem) (sizeof (type)))) != 0) \
       *___CAST(type*,var) = init; \
   } while (0)
#define ___C_DELETE_STRUCT(name,ptr) \
do { \
     ___EXT(___free_mem) (ptr); \
   } while (0)
#define ___C_DELETE_UNION(name,ptr) \
do { \
     ___EXT(___free_mem) (ptr); \
   } while (0)
#define ___C_DELETE_TYPE(name,ptr) \
do { \
     ___EXT(___free_mem) (ptr); \
   } while (0)

#endif

#ifdef ___USE_CPLUSPLUS_NEW_DELETE

#define ___ASSIGN_NEW(var,type) \
___CPLUSPLUS_ASSIGN_NEW(var,type)
#define ___ASSIGN_NEW_WITH_INIT(var,type,init) \
___CPLUSPLUS_ASSIGN_NEW_WITH_INIT(var,type,init)
#define ___DELETE_STRUCT(name,ptr) ___CPLUSPLUS_DELETE_STRUCT(name,ptr)
#define ___DELETE_UNION(name,ptr) ___CPLUSPLUS_DELETE_UNION(name,ptr)
#define ___DELETE_TYPE(name,ptr) ___CPLUSPLUS_DELETE_TYPE(name,ptr)

#else

#define ___ASSIGN_NEW(var,type) \
___C_ASSIGN_NEW(var,type)
#define ___ASSIGN_NEW_WITH_INIT(var,type,init) \
___C_ASSIGN_NEW_WITH_INIT(var,type,init)
#define ___DELETE_STRUCT(name,ptr) ___C_DELETE_STRUCT(name,ptr)
#define ___DELETE_UNION(name,ptr) ___C_DELETE_UNION(name,ptr)
#define ___DELETE_TYPE(name,ptr) ___C_DELETE_TYPE(name,ptr)

#endif

#ifdef ___USE_CPLUSPLUS_CLEANUP

#define ___BEGIN_CLEANUP(cleanup) \
{ struct ___cleanup { ~___cleanup () { cleanup; } } ___cleanup_object;
#define ___END_CLEANUP(cleanup) \
}

#else

#define ___BEGIN_CLEANUP(cleanup) \
{
#define ___END_CLEANUP(cleanup) \
cleanup; }

#endif

#ifdef ___USE_SETJMP

#define ___BEGIN_TRY \
{ ___jmpbuf_struct ___jbuf, *___old_catcher = ___ps->catcher; \
___ps->catcher = &___jbuf; ___err = ___SETJMP(___jbuf.buf); \
if (___err==___FIX(___NO_ERR)) {
#define ___END_TRY } ___ps->catcher = ___old_catcher; }
#define ___THROW(e)___LONGJMP(___ps->catcher->buf, e)
#define ___ON_THROW(stat1,stat2) \
___ON_THROW_AUX(___processor_state ___ps=___PSTATE;,stat1,stat2)

#else

#define ___BEGIN_TRY { ___err = ___FIX(___NO_ERR); try {
#define ___END_TRY } catch (___throw_struct ts) { ___err = ts.err; } }
#define ___THROW(e)do { ___throw_struct ts; ts.err = e; throw (ts); } while (0)
#define ___ON_THROW(stat1,stat2) \
___ON_THROW_AUX(,stat1,stat2)

#endif

#define ___ON_THROW_AUX(decl,stat1,stat2) \
do { \
     ___SCMOBJ ___err; decl \
     ___BEGIN_TRY stat1; ___END_TRY \
     if (___err != ___FIX(___NO_ERR)) stat2; \
   } while (0)

#define ___RELEASE_POINTER ___EXT(___release_pointer)

#define ___DEF_RELEASE_FN_STRUCT(name,id) \
___HIDDEN ___SCMOBJ id \
   ___P((void *___x), \
        (___x) \
void *___x;) \
{ ___DELETE_STRUCT(name,___x); return ___FIX(___NO_ERR); }

#define ___DEF_RELEASE_FN_UNION(name,id) \
___HIDDEN ___SCMOBJ id \
   ___P((void *___x), \
        (___x) \
void *___x;) \
{ ___DELETE_UNION(name,___x); return ___FIX(___NO_ERR); }

#define ___DEF_RELEASE_FN_TYPE(name,id) \
___HIDDEN ___SCMOBJ id \
   ___P((void *___x), \
        (___x) \
void *___x;) \
{ ___DELETE_TYPE(name,___x); return ___FIX(___NO_ERR); }

#define ___CFUN_CONV_ERROR if ((___err!=___FIX(___NO_ERR))&&(___err!=___FIX(___UNWIND_C_STACK))) {___ps->temp1=___err;___ps->temp2=___errmsg;___ps->temp3=___LBL(0);___JUMPEXTPRM(___SET_NARGS(___NARGS),___GSTATE->handler_cfun_conv_error;)}

#define ___STOC3(f,s,c,i)___err=___EXT(f)(___PSP s,c,i)
#define ___STOC4(f,s,c,t,i)___err=___EXT(f)(___PSP s,c,t,i)
#define ___CTOS3(f,c,s,i)___err=___EXT(f)(___ps,c,s,i)
#define ___CTOS5(f,c,t,r,s,i)___err=___EXT(f)(___ps,c,t,r,s,i)
#define ___IF_STOC3(f,s,c,i)if ((___STOC3(f,s,c,i))==___FIX(___NO_ERR))
#define ___IF_STOC4(f,s,c,t,i)if ((___STOC4(f,s,c,t,i))==___FIX(___NO_ERR))
#define ___IF_CTOS3(f,c,s,i)if ((___CTOS3(f,c,s,i))==___FIX(___NO_ERR))
#define ___IF_CTOS5(f,c,t,r,s,i)if ((___CTOS5(f,c,t,r,s,i))==___FIX(___NO_ERR))

#define ___BEGIN_SFUN_BODY
#define ___END_SFUN_BODY

#define ___BEGIN_SFUN_VOID(proc) ___processor_state ___ps=___PSTATE;___SCMOBJ ___marker;___SCMOBJ ___err;___SCMOBJ ___errmsg=___FAL;if ((___err=___EXT(___make_sfun_stack_marker) (___ps,&___marker,proc))==___FIX(___NO_ERR)) {
#define ___SFUN_CALL_VOID ___err=___EXT(___call) (___PSP ___NARGS,___FIELD(___marker,0),___marker);
#define ___SFUN_SET_RESULT_VOID /* no result to set */
#define ___SFUN_ERROR_VOID while ((___err!=___FIX(___NO_ERR))&&(___err!=___FIX(___UNWIND_C_STACK))) {___ps->temp1=___err;___ps->temp2=___errmsg;___ps->temp3=___marker;___err=___EXT(___call) (___PSP 0,___GSTATE->handler_sfun_conv_error,___marker);
#define ___END_SFUN_VOID } ___EXT(___kill_sfun_stack_marker) (___marker); } ___EXT(___propagate_error) (___PSP ___err);

#define ___BEGIN_SFUN_SCMOBJ(proc) ___processor_state ___ps=___PSTATE;___SCMOBJ ___marker;___SCMOBJ ___result;___SCMOBJ ___err;___SCMOBJ ___errmsg=___FAL;if ((___err=___EXT(___make_sfun_stack_marker) (___ps,&___marker,proc))==___FIX(___NO_ERR)) {
#define ___SFUN_CALL_SCMOBJ ___err=___EXT(___call) (___PSP ___NARGS,___FIELD(___marker,0),___marker);
#define ___SFUN_SET_RESULT_SCMOBJ ___result = ___SFUN_RESULT;
#define ___SFUN_ERROR_SCMOBJ while ((___err!=___FIX(___NO_ERR))&&(___err!=___FIX(___UNWIND_C_STACK))) {___ps->temp1=___err;___ps->temp2=___errmsg;___ps->temp3=___marker;___err=___EXT(___call) (___PSP 0,___GSTATE->handler_sfun_conv_error,___marker);
#define ___END_SFUN_SCMOBJ } ___EXT(___kill_sfun_stack_marker) (___marker); } ___EXT(___propagate_error) (___PSP ___err);

#define ___BEGIN_SFUN(proc,decl)___processor_state ___ps=___PSTATE;___SCMOBJ ___marker;decl;___SCMOBJ ___err;___SCMOBJ ___errmsg=___FAL;if ((___err=___EXT(___make_sfun_stack_marker) (___ps,&___marker,proc))==___FIX(___NO_ERR)) {
#define ___SFUN_CALL if ((___err=___EXT(___call) (___PSP ___NARGS,___FIELD(___marker,0),___marker))==___FIX(___NO_ERR))
#define ___SFUN_SET_RESULT /* done in conversion function */
#define ___SFUN_ERROR while ((___err!=___FIX(___NO_ERR))&&(___err!=___FIX(___UNWIND_C_STACK))) {___ps->temp1=___err;___ps->temp2=___errmsg;___ps->temp3=___marker;if ((___err=___EXT(___call) (___PSP 0,___GSTATE->handler_sfun_conv_error,___marker))==___FIX(___NO_ERR))
#define ___END_SFUN } ___EXT(___kill_sfun_stack_marker) (___marker); } ___EXT(___propagate_error) (___PSP ___err);

#define ___BEGIN_SFUN_ARG(i,arg)___SCMOBJ arg;
#define ___END_SFUN_ARG(i)
#define ___BEGIN_SFUN_ARG_SCMOBJ(i)
#define ___END_SFUN_ARG_SCMOBJ(i)
#define ___SFUN_ARG(i,arg)___PSSTK(___FRAME_SPACE(2)+i)=arg;
#define ___SFUN_RESULT ___PSR1

#define ___BEGIN_SFUN_SCMOBJ_TO_S8(s,c)___STOC3(___SCMOBJ_to_S8,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_S8(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_U8(s,c)___STOC3(___SCMOBJ_to_U8,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_U8(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_S16(s,c)___STOC3(___SCMOBJ_to_S16,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_S16(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_U16(s,c)___STOC3(___SCMOBJ_to_U16,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_U16(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_S32(s,c)___STOC3(___SCMOBJ_to_S32,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_S32(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_U32(s,c)___STOC3(___SCMOBJ_to_U32,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_U32(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_S64(s,c)___STOC3(___SCMOBJ_to_S64,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_S64(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_U64(s,c)___STOC3(___SCMOBJ_to_U64,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_U64(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_F32(s,c)___STOC3(___SCMOBJ_to_F32,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_F32(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_F64(s,c)___STOC3(___SCMOBJ_to_F64,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_F64(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_CHAR(s,c)___STOC3(___SCMOBJ_to_CHAR,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_CHAR(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_SCHAR(s,c)___STOC3(___SCMOBJ_to_SCHAR,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_SCHAR(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UCHAR(s,c)___STOC3(___SCMOBJ_to_UCHAR,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UCHAR(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_ISO_8859_1(s,c)___STOC3(___SCMOBJ_to_ISO_8859_1,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_ISO_8859_1(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UCS_2(s,c)___STOC3(___SCMOBJ_to_UCS_2,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UCS_2(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UCS_4(s,c)___STOC3(___SCMOBJ_to_UCS_4,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UCS_4(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_WCHAR(s,c)___STOC3(___SCMOBJ_to_WCHAR,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_WCHAR(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_SIZE_T(s,c)___STOC3(___SCMOBJ_to_SIZE_T,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_SIZE_T(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_SSIZE_T(s,c)___STOC3(___SCMOBJ_to_SSIZE_T,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_SSIZE_T(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_PTRDIFF_T(s,c)___STOC3(___SCMOBJ_to_PTRDIFF_T,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_PTRDIFF_T(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_SHORT(s,c)___STOC3(___SCMOBJ_to_SHORT,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_SHORT(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_USHORT(s,c)___STOC3(___SCMOBJ_to_USHORT,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_USHORT(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_INT(s,c)___STOC3(___SCMOBJ_to_INT,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_INT(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UINT(s,c)___STOC3(___SCMOBJ_to_UINT,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UINT(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_LONG(s,c)___STOC3(___SCMOBJ_to_LONG,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_LONG(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_ULONG(s,c)___STOC3(___SCMOBJ_to_ULONG,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_ULONG(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_FLOAT(s,c)___STOC3(___SCMOBJ_to_FLOAT,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_FLOAT(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_DOUBLE(s,c)___STOC3(___SCMOBJ_to_DOUBLE,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_DOUBLE(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_STRUCT(n,s,c,t)___STOC4(___SCMOBJ_to_STRUCT,s,&c,t,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_STRUCT(n,s,c,t)
#define ___BEGIN_SFUN_SCMOBJ_TO_UNION(n,s,c,t)___STOC4(___SCMOBJ_to_UNION,s,&c,t,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UNION(n,s,c,t)
#define ___BEGIN_SFUN_SCMOBJ_TO_TYPE(n,s,c,t)___STOC4(___SCMOBJ_to_TYPE,s,&c,t,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_TYPE(n,s,c,t)
#define ___BEGIN_SFUN_SCMOBJ_TO_POINTER(s,c,t)___STOC4(___SCMOBJ_to_POINTER,s,&c,t,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_POINTER(s,c,t)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLPOINTER(s,c,t)___STOC4(___SCMOBJ_to_NONNULLPOINTER,s,&c,t,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLPOINTER(s,c,t)
#define ___BEGIN_SFUN_SCMOBJ_TO_FUNCTION(s,cnv,c)___STOC4(___SCMOBJ_to_FUNCTION,s,___CAST(void*,cnv),&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_FUNCTION(s,cnv,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLFUNCTION(s,cnv,c)___STOC4(___SCMOBJ_to_NONNULLFUNCTION,s,___CAST(void*,cnv),&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLFUNCTION(s,cnv,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_BOOL(s,c)___STOC3(___SCMOBJ_to_BOOL,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_BOOL(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(s,c)___STOC3(___SCMOBJ_to_CHARSTRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_CHARSTRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLCHARSTRING(s,c)___STOC3(___SCMOBJ_to_NONNULLCHARSTRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLCHARSTRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLCHARSTRINGLIST(s,c)___STOC3(___SCMOBJ_to_NONNULLCHARSTRINGLIST,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLCHARSTRINGLIST(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_ISO_8859_1STRING(s,c)___STOC3(___SCMOBJ_to_ISO_8859_1STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_ISO_8859_1STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLISO_8859_1STRING(s,c)___STOC3(___SCMOBJ_to_NONNULLISO_8859_1STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLISO_8859_1STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLISO_8859_1STRINGLIST(s,c)___STOC3(___SCMOBJ_to_NONNULLISO_8859_1STRINGLIST,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLISO_8859_1STRINGLIST(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UTF_8STRING(s,c)___STOC3(___SCMOBJ_to_UTF_8STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UTF_8STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUTF_8STRING(s,c)___STOC3(___SCMOBJ_to_NONNULLUTF_8STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUTF_8STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUTF_8STRINGLIST(s,c)___STOC3(___SCMOBJ_to_NONNULLUTF_8STRINGLIST,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUTF_8STRINGLIST(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UTF_16STRING(s,c)___STOC3(___SCMOBJ_to_UTF_16STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UTF_16STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUTF_16STRING(s,c)___STOC3(___SCMOBJ_to_NONNULLUTF_16STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUTF_16STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUTF_16STRINGLIST(s,c)___STOC3(___SCMOBJ_to_NONNULLUTF_16STRINGLIST,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUTF_16STRINGLIST(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UCS_2STRING(s,c)___STOC3(___SCMOBJ_to_UCS_2STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UCS_2STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUCS_2STRING(s,c)___STOC3(___SCMOBJ_to_NONNULLUCS_2STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUCS_2STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUCS_2STRINGLIST(s,c)___STOC3(___SCMOBJ_to_NONNULLUCS_2STRINGLIST,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUCS_2STRINGLIST(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_UCS_4STRING(s,c)___STOC3(___SCMOBJ_to_UCS_4STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_UCS_4STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUCS_4STRING(s,c)___STOC3(___SCMOBJ_to_NONNULLUCS_4STRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUCS_4STRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLUCS_4STRINGLIST(s,c)___STOC3(___SCMOBJ_to_NONNULLUCS_4STRINGLIST,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLUCS_4STRINGLIST(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_WCHARSTRING(s,c)___STOC3(___SCMOBJ_to_WCHARSTRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_WCHARSTRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLWCHARSTRING(s,c)___STOC3(___SCMOBJ_to_NONNULLWCHARSTRING,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLWCHARSTRING(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_NONNULLWCHARSTRINGLIST(s,c)___STOC3(___SCMOBJ_to_NONNULLWCHARSTRINGLIST,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_NONNULLWCHARSTRINGLIST(s,c)
#define ___BEGIN_SFUN_SCMOBJ_TO_VARIANT(s,c)___STOC3(___SCMOBJ_to_VARIANT,s,&c,___RETURN_POS);
#define ___END_SFUN_SCMOBJ_TO_VARIANT(s,c)

#define ___BEGIN_SFUN_S8_TO_SCMOBJ(c,s,i)___IF_CTOS3(___S8_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_S8_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_U8_TO_SCMOBJ(c,s,i)___IF_CTOS3(___U8_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_U8_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_S16_TO_SCMOBJ(c,s,i)___IF_CTOS3(___S16_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_S16_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_U16_TO_SCMOBJ(c,s,i)___IF_CTOS3(___U16_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_U16_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_S32_TO_SCMOBJ(c,s,i)___IF_CTOS3(___S32_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_S32_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_U32_TO_SCMOBJ(c,s,i)___IF_CTOS3(___U32_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_U32_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_S64_TO_SCMOBJ(c,s,i)___IF_CTOS3(___S64_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_S64_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_U64_TO_SCMOBJ(c,s,i)___IF_CTOS3(___U64_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_U64_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_F32_TO_SCMOBJ(c,s,i)___IF_CTOS3(___F32_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_F32_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_F64_TO_SCMOBJ(c,s,i)___IF_CTOS3(___F64_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_F64_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_CHAR_TO_SCMOBJ(c,s,i)___IF_CTOS3(___CHAR_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_CHAR_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_SCHAR_TO_SCMOBJ(c,s,i)___IF_CTOS3(___SCHAR_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_SCHAR_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_UCHAR_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UCHAR_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UCHAR_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_ISO_8859_1_TO_SCMOBJ(c,s,i)___IF_CTOS3(___ISO_8859_1_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_ISO_8859_1_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_UCS_2_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UCS_2_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UCS_2_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_UCS_4_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UCS_4_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UCS_4_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_WCHAR_TO_SCMOBJ(c,s,i)___IF_CTOS3(___WCHAR_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_WCHAR_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_SIZE_T_TO_SCMOBJ(c,s,i)___IF_CTOS3(___SIZE_T_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_SIZE_T_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_SSIZE_T_TO_SCMOBJ(c,s,i)___IF_CTOS3(___SSIZE_T_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_SSIZE_T_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_PTRDIFF_T_TO_SCMOBJ(c,s,i)___IF_CTOS3(___PTRDIFF_T_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_PTRDIFF_T_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_SHORT_TO_SCMOBJ(c,s,i)___IF_CTOS3(___SHORT_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_SHORT_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_USHORT_TO_SCMOBJ(c,s,i)___IF_CTOS3(___USHORT_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_USHORT_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_INT_TO_SCMOBJ(c,s,i)___IF_CTOS3(___INT_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_INT_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_UINT_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UINT_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UINT_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_LONG_TO_SCMOBJ(c,s,i)___IF_CTOS3(___LONG_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_LONG_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_ULONG_TO_SCMOBJ(c,s,i)___IF_CTOS3(___ULONG_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_ULONG_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_FLOAT_TO_SCMOBJ(c,s,i)___IF_CTOS3(___FLOAT_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_FLOAT_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_DOUBLE_TO_SCMOBJ(c,s,i)___IF_CTOS3(___DOUBLE_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_DOUBLE_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_STRUCT_TO_SCMOBJ(n,c,t,r,s,i)___IF_CTOS5(___STRUCT_to_SCMOBJ,(void*)c,t,r,&s,i){
#define ___END_SFUN_STRUCT_TO_SCMOBJ(n,c,t,r,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_UNION_TO_SCMOBJ(n,c,t,r,s,i)___IF_CTOS5(___UNION_to_SCMOBJ,(void*)c,t,r,&s,i){
#define ___END_SFUN_UNION_TO_SCMOBJ(n,c,t,r,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_TYPE_TO_SCMOBJ(n,c,t,r,s,i)___IF_CTOS5(___TYPE_to_SCMOBJ,(void*)c,t,r,&s,i){
#define ___END_SFUN_TYPE_TO_SCMOBJ(n,c,t,r,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_POINTER_TO_SCMOBJ(c,t,r,s,i)___IF_CTOS5(___POINTER_to_SCMOBJ,(void*)c,t,r,&s,i){
#define ___END_SFUN_POINTER_TO_SCMOBJ(c,t,r,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLPOINTER_TO_SCMOBJ(c,t,r,s,i)___IF_CTOS5(___NONNULLPOINTER_to_SCMOBJ,(void*)c,t,r,&s,i){
#define ___END_SFUN_NONNULLPOINTER_TO_SCMOBJ(c,t,r,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_FUNCTION_TO_SCMOBJ(c,s,i)___IF_CTOS3(___FUNCTION_to_SCMOBJ,___CAST(void*,c),&s,i){
#define ___END_SFUN_FUNCTION_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLFUNCTION_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLFUNCTION_to_SCMOBJ,___CAST(void*,c),&s,i){
#define ___END_SFUN_NONNULLFUNCTION_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_BOOL_TO_SCMOBJ(c,s,i)___IF_CTOS3(___BOOL_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_BOOL_TO_SCMOBJ(c,s,i)}
#define ___BEGIN_SFUN_CHARSTRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___CHARSTRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_CHARSTRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLCHARSTRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLCHARSTRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLCHARSTRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLCHARSTRINGLIST_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLCHARSTRINGLIST_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLCHARSTRINGLIST_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_ISO_8859_1STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___ISO_8859_1STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_ISO_8859_1STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLISO_8859_1STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLISO_8859_1STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLISO_8859_1STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLISO_8859_1STRINGLIST_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLISO_8859_1STRINGLIST_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLISO_8859_1STRINGLIST_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_UTF_8STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UTF_8STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UTF_8STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUTF_8STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUTF_8STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUTF_8STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUTF_8STRINGLIST_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUTF_8STRINGLIST_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUTF_8STRINGLIST_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_UTF_16STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UTF_16STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UTF_16STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUTF_16STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUTF_16STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUTF_16STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUTF_16STRINGLIST_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUTF_16STRINGLIST_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUTF_16STRINGLIST_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_UCS_2STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UCS_2STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UCS_2STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUCS_2STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUCS_2STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUCS_2STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUCS_2STRINGLIST_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUCS_2STRINGLIST_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUCS_2STRINGLIST_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_UCS_4STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___UCS_4STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_UCS_4STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUCS_4STRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUCS_4STRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUCS_4STRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLUCS_4STRINGLIST_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLUCS_4STRINGLIST_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLUCS_4STRINGLIST_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_WCHARSTRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___WCHARSTRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_WCHARSTRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLWCHARSTRING_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLWCHARSTRING_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLWCHARSTRING_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_NONNULLWCHARSTRINGLIST_TO_SCMOBJ(c,s,i)___IF_CTOS3(___NONNULLWCHARSTRINGLIST_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_NONNULLWCHARSTRINGLIST_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}
#define ___BEGIN_SFUN_VARIANT_TO_SCMOBJ(c,s,i)___IF_CTOS3(___VARIANT_to_SCMOBJ,c,&s,i){
#define ___END_SFUN_VARIANT_TO_SCMOBJ(c,s,i)___EXT(___release_scmobj)(s);}


#define ___SFUN_CAST_AND_DEREF(type,arg)(*___CAST(type,arg))
#define ___SFUN_CAST(type,arg)___CAST(type,arg)

#define ___BEGIN_SFUN_COPY_STRUCT(n,r,arg){ void *r; ___ASSIGN_NEW_WITH_INIT(r,struct n,arg);
#define ___END_SFUN_COPY_STRUCT(n,r,arg)}
#define ___BEGIN_SFUN_COPY_UNION(n,r,arg){ void *r; ___ASSIGN_NEW_WITH_INIT(r,union n,arg);
#define ___END_SFUN_COPY_UNION(n,r,arg)}
#define ___BEGIN_SFUN_COPY_TYPE(n,r,arg){ void *r; ___ASSIGN_NEW_WITH_INIT(r,n,arg);
#define ___END_SFUN_COPY_TYPE(n,r,arg)}

#define ___CFUN_CAST_AND_DEREF(type,arg)(*___CAST(type,arg))
#define ___CFUN_CAST(type,arg)___CAST(type,arg)

#define ___CFUN_CALL_VOID(call)call;
#define ___CFUN_CALL(r,call)r = call;
#define ___CFUN_CALL_STRUCT(n,r,call)___ASSIGN_NEW_WITH_INIT(r,struct n,call);
#define ___CFUN_CALL_UNION(n,r,call)___ASSIGN_NEW_WITH_INIT(r,union n,call);
#define ___CFUN_CALL_TYPE(n,r,call)___ASSIGN_NEW_WITH_INIT(r,n,call);
#define ___CFUN_CALL_POINTER(r,call)r = call;
#define ___CFUN_CALL_NONNULLPOINTER(r,call)r = call;
#define ___CFUN_CALL_FUNCTION(r,call)r = call;
#define ___CFUN_CALL_NONNULLFUNCTION(r,call)r = call;

#define ___BEGIN_CFUN_BODY
#define ___END_CFUN_BODY ___AT_END
#define ___BEGIN_CFUN_BODY_CLEANUP ___W_ALL ___BEGIN_TRY
#define ___END_CFUN_BODY_CLEANUP ___AT_END ___END_TRY ___R_ALL

#define ___BEGIN_CFUN_VOID ___SET_STK(-___FRAME_STACK_RA,___R0) ___W_ALL {___SCMOBJ ___err=___FIX(___NO_ERR);___SCMOBJ ___errmsg=___FAL;
#define ___CFUN_SET_RESULT_VOID ___CFUN_RESULT = ___VOID;
#define ___CFUN_ERROR_VOID ___CFUN_CONV_ERROR
#define ___CFUN_ERROR_CLEANUP_VOID ___CFUN_CONV_ERROR ___EXT(___propagate_error) (___PSP ___err);
#define ___END_CFUN_VOID } ___R_ALL

#define ___BEGIN_CFUN_SCMOBJ ___SET_STK(-___FRAME_STACK_RA,___R0) ___W_ALL {___SCMOBJ ___err=___FIX(___NO_ERR);___SCMOBJ ___result;___SCMOBJ ___errmsg=___FAL;
#define ___CFUN_SET_RESULT_SCMOBJ ___CFUN_RESULT = ___result;
#define ___CFUN_ERROR_SCMOBJ ___CFUN_CONV_ERROR
#define ___CFUN_ERROR_CLEANUP_SCMOBJ ___CFUN_CONV_ERROR ___EXT(___propagate_error) (___PSP ___err);
#define ___END_CFUN_SCMOBJ } ___R_ALL

#define ___BEGIN_CFUN(decl)___SET_STK(-___FRAME_STACK_RA,___R0) ___W_ALL {___SCMOBJ ___err=___FIX(___NO_ERR);___SCMOBJ ___errmsg=___FAL;decl;
#define ___CFUN_SET_RESULT /* done in conversion function */
#define ___CFUN_ERROR ___CFUN_CONV_ERROR
#define ___CFUN_ERROR_CLEANUP ___CFUN_CONV_ERROR ___EXT(___propagate_error) (___PSP ___err);
#define ___END_CFUN } ___R_ALL

#define ___BEGIN_CFUN_ARG(i,decl)decl;
#define ___END_CFUN_ARG(i)
#define ___BEGIN_CFUN_ARG_SCMOBJ(i)
#define ___END_CFUN_ARG_SCMOBJ(i)
#define ___CFUN_ARG(i)___PSSTK((i-___FRAME_SPACE(___NARGS+1)))
#define ___CFUN_RESULT ___PSR1

#define ___BEGIN_CFUN_SCMOBJ_TO_S8(s,c,i)___IF_STOC3(___SCMOBJ_to_S8,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_S8(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_U8(s,c,i)___IF_STOC3(___SCMOBJ_to_U8,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_U8(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_S16(s,c,i)___IF_STOC3(___SCMOBJ_to_S16,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_S16(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_U16(s,c,i)___IF_STOC3(___SCMOBJ_to_U16,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_U16(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_S32(s,c,i)___IF_STOC3(___SCMOBJ_to_S32,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_S32(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_U32(s,c,i)___IF_STOC3(___SCMOBJ_to_U32,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_U32(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_S64(s,c,i)___IF_STOC3(___SCMOBJ_to_S64,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_S64(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_U64(s,c,i)___IF_STOC3(___SCMOBJ_to_U64,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_U64(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_F32(s,c,i)___IF_STOC3(___SCMOBJ_to_F32,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_F32(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_F64(s,c,i)___IF_STOC3(___SCMOBJ_to_F64,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_F64(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_CHAR(s,c,i)___IF_STOC3(___SCMOBJ_to_CHAR,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_CHAR(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_SCHAR(s,c,i)___IF_STOC3(___SCMOBJ_to_SCHAR,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_SCHAR(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_UCHAR(s,c,i)___IF_STOC3(___SCMOBJ_to_UCHAR,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UCHAR(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_ISO_8859_1(s,c,i)___IF_STOC3(___SCMOBJ_to_ISO_8859_1,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_ISO_8859_1(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_UCS_2(s,c,i)___IF_STOC3(___SCMOBJ_to_UCS_2,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UCS_2(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_UCS_4(s,c,i)___IF_STOC3(___SCMOBJ_to_UCS_4,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UCS_4(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_WCHAR(s,c,i)___IF_STOC3(___SCMOBJ_to_WCHAR,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_WCHAR(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_SIZE_T(s,c,i)___IF_STOC3(___SCMOBJ_to_SIZE_T,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_SIZE_T(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_SSIZE_T(s,c,i)___IF_STOC3(___SCMOBJ_to_SSIZE_T,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_SSIZE_T(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_PTRDIFF_T(s,c,i)___IF_STOC3(___SCMOBJ_to_PTRDIFF_T,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_PTRDIFF_T(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_SHORT(s,c,i)___IF_STOC3(___SCMOBJ_to_SHORT,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_SHORT(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_USHORT(s,c,i)___IF_STOC3(___SCMOBJ_to_USHORT,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_USHORT(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_INT(s,c,i)___IF_STOC3(___SCMOBJ_to_INT,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_INT(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_UINT(s,c,i)___IF_STOC3(___SCMOBJ_to_UINT,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UINT(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_LONG(s,c,i)___IF_STOC3(___SCMOBJ_to_LONG,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_LONG(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_ULONG(s,c,i)___IF_STOC3(___SCMOBJ_to_ULONG,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_ULONG(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_LONGLONG(s,c,i)___IF_STOC3(___SCMOBJ_to_LONGLONG,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_LONGLONG(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_ULONGLONG(s,c,i)___IF_STOC3(___SCMOBJ_to_ULONGLONG,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_ULONGLONG(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_FLOAT(s,c,i)___IF_STOC3(___SCMOBJ_to_FLOAT,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_FLOAT(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_DOUBLE(s,c,i)___IF_STOC3(___SCMOBJ_to_DOUBLE,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_DOUBLE(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_STRUCT(n,s,c,t,i)___IF_STOC4(___SCMOBJ_to_STRUCT,s,(void**)&c,t,i){
#define ___END_CFUN_SCMOBJ_TO_STRUCT(n,s,c,t,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_UNION(n,s,c,t,i)___IF_STOC4(___SCMOBJ_to_UNION,s,(void**)&c,t,i){
#define ___END_CFUN_SCMOBJ_TO_UNION(n,s,c,t,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_TYPE(n,s,c,t,i)___IF_STOC4(___SCMOBJ_to_TYPE,s,(void**)&c,t,i){
#define ___END_CFUN_SCMOBJ_TO_TYPE(n,s,c,t,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_POINTER(s,c,t,i)___IF_STOC4(___SCMOBJ_to_POINTER,s,(void**)&c,t,i){
#define ___END_CFUN_SCMOBJ_TO_POINTER(s,c,t,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLPOINTER(s,c,t,i)___IF_STOC4(___SCMOBJ_to_NONNULLPOINTER,s,(void**)&c,t,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLPOINTER(s,c,t,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_FUNCTION(s,cnv,c,i)___IF_STOC4(___SCMOBJ_to_FUNCTION,s,(void*)cnv,(void**)&c,i){
#define ___END_CFUN_SCMOBJ_TO_FUNCTION(s,cnv,c,i)___EXT(___release_function)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLFUNCTION(s,cnv,c,i)___IF_STOC4(___SCMOBJ_to_NONNULLFUNCTION,s,(void*)cnv,(void**)&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLFUNCTION(s,cnv,c,i)___EXT(___release_function)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_BOOL(s,c,i)___IF_STOC3(___SCMOBJ_to_BOOL,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_BOOL(s,c,i)}
#define ___BEGIN_CFUN_SCMOBJ_TO_CHARSTRING(s,c,i)___IF_STOC3(___SCMOBJ_to_CHARSTRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_CHARSTRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLCHARSTRING(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLCHARSTRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLCHARSTRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLCHARSTRINGLIST(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLCHARSTRINGLIST,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLCHARSTRINGLIST(s,c,i)___EXT(___release_string_list)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_ISO_8859_1STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_ISO_8859_1STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_ISO_8859_1STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLISO_8859_1STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLISO_8859_1STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLISO_8859_1STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLISO_8859_1STRINGLIST(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLISO_8859_1STRINGLIST,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLISO_8859_1STRINGLIST(s,c,i)___EXT(___release_string_list)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_UTF_8STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_UTF_8STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UTF_8STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUTF_8STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUTF_8STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUTF_8STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUTF_8STRINGLIST(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUTF_8STRINGLIST,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUTF_8STRINGLIST(s,c,i)___EXT(___release_string_list)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_UTF_16STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_UTF_16STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UTF_16STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUTF_16STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUTF_16STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUTF_16STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUTF_16STRINGLIST(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUTF_16STRINGLIST,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUTF_16STRINGLIST(s,c,i)___EXT(___release_string_list)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_UCS_2STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_UCS_2STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UCS_2STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUCS_2STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUCS_2STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUCS_2STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUCS_2STRINGLIST(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUCS_2STRINGLIST,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUCS_2STRINGLIST(s,c,i)___EXT(___release_string_list)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_UCS_4STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_UCS_4STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_UCS_4STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUCS_4STRING(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUCS_4STRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUCS_4STRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLUCS_4STRINGLIST(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLUCS_4STRINGLIST,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLUCS_4STRINGLIST(s,c,i)___EXT(___release_string_list)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_WCHARSTRING(s,c,i)___IF_STOC3(___SCMOBJ_to_WCHARSTRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_WCHARSTRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLWCHARSTRING(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLWCHARSTRING,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLWCHARSTRING(s,c,i)___EXT(___release_string)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_NONNULLWCHARSTRINGLIST(s,c,i)___IF_STOC3(___SCMOBJ_to_NONNULLWCHARSTRINGLIST,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_NONNULLWCHARSTRINGLIST(s,c,i)___EXT(___release_string_list)(c);}
#define ___BEGIN_CFUN_SCMOBJ_TO_VARIANT(s,c,i)___IF_STOC3(___SCMOBJ_to_VARIANT,s,&c,i){
#define ___END_CFUN_SCMOBJ_TO_VARIANT(s,c,i)___EXT(___release_variant)(c);}

#define ___BEGIN_CFUN_S8_TO_SCMOBJ(c,s)___CTOS3(___S8_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_S8_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_U8_TO_SCMOBJ(c,s)___CTOS3(___U8_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_U8_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_S16_TO_SCMOBJ(c,s)___CTOS3(___S16_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_S16_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_U16_TO_SCMOBJ(c,s)___CTOS3(___U16_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_U16_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_S32_TO_SCMOBJ(c,s)___IF_CTOS3(___S32_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_S32_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_U32_TO_SCMOBJ(c,s)___IF_CTOS3(___U32_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_U32_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_S64_TO_SCMOBJ(c,s)___IF_CTOS3(___S64_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_S64_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_U64_TO_SCMOBJ(c,s)___IF_CTOS3(___U64_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_U64_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_F32_TO_SCMOBJ(c,s)___IF_CTOS3(___F32_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_F32_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_F64_TO_SCMOBJ(c,s)___IF_CTOS3(___F64_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_F64_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_CHAR_TO_SCMOBJ(c,s)___CTOS3(___CHAR_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_CHAR_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_SCHAR_TO_SCMOBJ(c,s)___CTOS3(___SCHAR_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_SCHAR_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_UCHAR_TO_SCMOBJ(c,s)___CTOS3(___UCHAR_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_UCHAR_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_ISO_8859_1_TO_SCMOBJ(c,s)___CTOS3(___ISO_8859_1_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_ISO_8859_1_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_UCS_2_TO_SCMOBJ(c,s)___CTOS3(___UCS_2_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_UCS_2_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_UCS_4_TO_SCMOBJ(c,s)___CTOS3(___UCS_4_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_UCS_4_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_WCHAR_TO_SCMOBJ(c,s)___CTOS3(___WCHAR_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_WCHAR_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_SIZE_T_TO_SCMOBJ(c,s)___CTOS3(___SIZE_T_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_SIZE_T_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_SSIZE_T_TO_SCMOBJ(c,s)___CTOS3(___SSIZE_T_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_SSIZE_T_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_PTRDIFF_T_TO_SCMOBJ(c,s)___CTOS3(___PTRDIFF_T_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_PTRDIFF_T_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_SHORT_TO_SCMOBJ(c,s)___IF_CTOS3(___SHORT_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_SHORT_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_USHORT_TO_SCMOBJ(c,s)___IF_CTOS3(___USHORT_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_USHORT_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_INT_TO_SCMOBJ(c,s)___IF_CTOS3(___INT_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_INT_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_UINT_TO_SCMOBJ(c,s)___IF_CTOS3(___UINT_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_UINT_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_LONG_TO_SCMOBJ(c,s)___IF_CTOS3(___LONG_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_LONG_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_ULONG_TO_SCMOBJ(c,s)___IF_CTOS3(___ULONG_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_ULONG_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_LONGLONG_TO_SCMOBJ(c,s)___IF_CTOS3(___LONGLONG_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_LONGLONG_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_ULONGLONG_TO_SCMOBJ(c,s)___IF_CTOS3(___ULONGLONG_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_ULONGLONG_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_FLOAT_TO_SCMOBJ(c,s)___IF_CTOS3(___FLOAT_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_FLOAT_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_DOUBLE_TO_SCMOBJ(c,s)___IF_CTOS3(___DOUBLE_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_DOUBLE_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_STRUCT_TO_SCMOBJ(n,c,t,r,s)___IF_CTOS5(___STRUCT_to_SCMOBJ,(void*)c,t,r,&s,___RETURN_POS){
#define ___END_CFUN_STRUCT_TO_SCMOBJ(n,c,t,r,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_UNION_TO_SCMOBJ(n,c,t,r,s)___IF_CTOS5(___UNION_to_SCMOBJ,(void*)c,t,r,&s,___RETURN_POS){
#define ___END_CFUN_UNION_TO_SCMOBJ(n,c,t,r,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_TYPE_TO_SCMOBJ(n,c,t,r,s)___IF_CTOS5(___TYPE_to_SCMOBJ,(void*)c,t,r,&s,___RETURN_POS){
#define ___END_CFUN_TYPE_TO_SCMOBJ(n,c,t,r,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_POINTER_TO_SCMOBJ(c,t,r,s)___IF_CTOS5(___POINTER_to_SCMOBJ,(void*)c,t,r,&s,___RETURN_POS){
#define ___END_CFUN_POINTER_TO_SCMOBJ(c,t,r,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLPOINTER_TO_SCMOBJ(c,t,r,s)___IF_CTOS5(___NONNULLPOINTER_to_SCMOBJ,(void*)c,t,r,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLPOINTER_TO_SCMOBJ(c,t,r,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_FUNCTION_TO_SCMOBJ(c,s)___IF_CTOS3(___FUNCTION_to_SCMOBJ,___CAST(void*,c),&s,___RETURN_POS){
#define ___END_CFUN_FUNCTION_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLFUNCTION_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLFUNCTION_to_SCMOBJ,___CAST(void*,c),&s,___RETURN_POS){
#define ___END_CFUN_NONNULLFUNCTION_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_BOOL_TO_SCMOBJ(c,s)___CTOS3(___BOOL_to_SCMOBJ,c,&s,___RETURN_POS);
#define ___END_CFUN_BOOL_TO_SCMOBJ(c,s)
#define ___BEGIN_CFUN_CHARSTRING_TO_SCMOBJ(c,s)___IF_CTOS3(___CHARSTRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_CHARSTRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLCHARSTRING_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLCHARSTRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLCHARSTRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLCHARSTRINGLIST_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLCHARSTRINGLIST_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLCHARSTRINGLIST_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_ISO_8859_1STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___ISO_8859_1STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_ISO_8859_1STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLISO_8859_1STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLISO_8859_1STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLISO_8859_1STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLISO_8859_1STRINGLIST_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLISO_8859_1STRINGLIST_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLISO_8859_1STRINGLIST_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_UTF_8STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___UTF_8STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_UTF_8STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUTF_8STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUTF_8STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUTF_8STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUTF_8STRINGLIST_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUTF_8STRINGLIST_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUTF_8STRINGLIST_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_UTF_16STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___UTF_16STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_UTF_16STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUTF_16STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUTF_16STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUTF_16STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUTF_16STRINGLIST_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUTF_16STRINGLIST_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUTF_16STRINGLIST_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_UCS_2STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___UCS_2STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_UCS_2STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUCS_2STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUCS_2STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUCS_2STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUCS_2STRINGLIST_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUCS_2STRINGLIST_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUCS_2STRINGLIST_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_UCS_4STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___UCS_4STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_UCS_4STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUCS_4STRING_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUCS_4STRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUCS_4STRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLUCS_4STRINGLIST_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLUCS_4STRINGLIST_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLUCS_4STRINGLIST_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_WCHARSTRING_TO_SCMOBJ(c,s)___IF_CTOS3(___WCHARSTRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_WCHARSTRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLWCHARSTRING_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLWCHARSTRING_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLWCHARSTRING_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_NONNULLWCHARSTRINGLIST_TO_SCMOBJ(c,s)___IF_CTOS3(___NONNULLWCHARSTRINGLIST_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_NONNULLWCHARSTRINGLIST_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}
#define ___BEGIN_CFUN_VARIANT_TO_SCMOBJ(c,s)___IF_CTOS3(___VARIANT_to_SCMOBJ,c,&s,___RETURN_POS){
#define ___END_CFUN_VARIANT_TO_SCMOBJ(c,s)___EXT(___release_scmobj)(s);}

/*---------------------------------------------------------------------------*/

#ifndef ___DEFINES_ONLY

#ifdef _MSC_VER
#ifdef ___DYNAMIC
int _fltused; /* needed if floating-point used. */
#endif
#endif

#ifdef __BORLANDC__
#ifdef __WIN32__
#ifndef ___OS_WIN32
#define ___OS_WIN32
#endif
#endif
#ifdef ___SHARED
#define _RTLDLL
#endif
#endif

#ifdef ___OS_WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifndef ___DONT_HAVE_WINSOCK2_H
#include <winsock2.h>
#endif

#ifndef ___DONT_HAVE_WINDOWS_H
#include <windows.h>
#endif

#endif

#ifdef ___USE_CPLUSPLUS_NEW_DELETE

#ifndef ___DONT_HAVE_NEW
#include <new>
#endif

#endif

#ifdef ___USE_SETJMP

typedef struct ___jmpbuf_struct
  {
    jmp_buf buf;
  } ___jmpbuf_struct;

#else

typedef struct ___throw_struct
  {
    ___SCMOBJ err;
  } ___throw_struct;

#endif

typedef void *___VARIANT; /* not yet implemented */

#ifdef ___BUILTIN_64BIT_INT_TYPE

/*
 * If the symbol ___BUILTIN_64BIT_INT_TYPE is defined then the data
 * types ___S64 and ___U64 are builtin integer types.
 */

#define ___S64_from_SM32(val) \
___CAST_S64(___CAST_S32(val))

#define ___S64_from_SM32_UM32(hi32,lo32) \
((___CAST_S64(___CAST_S32(hi32)) << 32) + ___CAST_S64(___CAST_U32(lo32)))

#define ___S64_from_LONGLONG(val) \
___CAST_S64(val)

#define ___S64_to_LONGLONG(val) \
___CAST(___LONGLONG,val)

#define ___S64_fits_in_width(val,width) \
((((val) >> ((width)-1)) == 0) || (((val) >> ((width)-1)) == -1))

#define ___S64_hi32(val)___CAST_S32((val) >> 32)
#define ___S64_lo32(val)___CAST_U32(val)

#define ___U64_from_UM32(val) \
___CAST_U64(___CAST_U32(val))

#define ___U64_from_UM32_UM32(hi32,lo32) \
((___CAST_U64(___CAST_U32(hi32)) << 32) + ___CAST_U64(___CAST_U32(lo32)))

#define ___U64_from_ULONGLONG(val) \
___CAST_U64(val)

#define ___U64_to_ULONGLONG(val) \
___CAST(___ULONGLONG,val)

#define ___U64_fits_in_width(val,width) \
(((val) >> (width)) == 0)

#define ___U64_mul_UM32_UM32(x,y) \
(___CAST_U64(___CAST_U32(x)) * ___CAST_U32(y))

#define ___U64_add_U64_U64(x,y) \
(___CAST_U64(x) + ___CAST_U64(y))

#define ___U64_hi32(val)___CAST_U32((val) >> 32)
#define ___U64_lo32(val)___CAST_U32(val)

#else

/*
 * If the symbol ___BUILTIN_64BIT_INT_TYPE is not defined then the
 * data types ___S64 and ___U64 are structures.
 */

typedef struct
  {
#ifdef ___BIG_ENDIAN
    ___S32 hi32;
    ___U32 lo32;
#else
    ___U32 lo32;
    ___S32 hi32;
#endif
  } ___S64;

typedef struct
  {
#ifdef ___BIG_ENDIAN
    ___U32 hi32;
    ___U32 lo32;
#else
    ___U32 lo32;
    ___U32 hi32;
#endif
  } ___U64;

#define ___S64_from_SM32(val) \
___EXT(___S64_from_SM32_fn) (val)

#define ___S64_from_SM32_UM32(hi32,lo32) \
___EXT(___S64_from_SM32_UM32_fn) (hi32,lo32)

#define ___S64_from_LONGLONG(val) \
___EXT(___S64_from_LONGLONG_fn) (val)

#define ___S64_to_LONGLONG(val) \
___EXT(___S64_to_LONGLONG_fn) (val)

#define ___S64_fits_in_width(val,width) \
___EXT(___S64_fits_in_width_fn) (val,width)

#define ___S64_hi32(val)val.hi32
#define ___S64_lo32(val)val.lo32

#define ___U64_from_UM32(val) \
___EXT(___U64_from_UM32_fn) (val)

#define ___U64_from_UM32_UM32(hi32,lo32) \
___EXT(___U64_from_UM32_UM32_fn) (hi32,lo32)

#define ___U64_from_ULONGLONG(val) \
___EXT(___U64_from_ULONGLONG_fn) (val)

#define ___U64_to_ULONGLONG(val) \
___EXT(___U64_to_ULONGLONG_fn) (val)

#define ___U64_fits_in_width(val,width) \
___EXT(___U64_fits_in_width_fn) (val,width)

#define ___U64_mul_UM32_UM32(x,y) \
___EXT(___U64_mul_UM32_UM32_fn) (x,y)

#define ___U64_add_U64_U64(x,y) \
___EXT(___U64_add_U64_U64_fn) (x,y)

#define ___U64_hi32(val)val.hi32
#define ___U64_lo32(val)val.lo32

#endif

/* Symbol/keyword structure */

typedef ___FAKEWORD ___symkey_struct[5+___PADDING_SIZE];

/* Global variable structure */

typedef struct ___glo_struct
  {
    ___WORD val;
    ___WORD prm;
    struct ___glo_struct* next;
  } ___glo_struct;

/*---------------------------------------------------------------------------*/

/*
 * Thread system inlined operations.
 */

#ifdef ___USE_POSIX_THREAD_SYSTEM

#ifndef ___DONT_HAVE_PTHREAD_H
#include <pthread.h>
#endif

#define ___MUTEX pthread_mutex_t

#define ___MUTEX_INIT(mut) (pthread_mutex_init (&mut, NULL) == 0)
#define ___MUTEX_DESTROY(mut) (pthread_mutex_destroy (&mut) == 0)
#define ___MUTEX_LOCK(mut) (pthread_mutex_lock (&mut) == 0)
#define ___MUTEX_UNLOCK(mut) (pthread_mutex_unlock (&mut) == 0)

#endif


#ifdef ___USE_WIN32_THREAD_SYSTEM

#define ___MUTEX HANDLE

#define ___MUTEX_INIT(mut) ((mut = CreateMutex (NULL, FALSE, NULL)) != NULL)
#define ___MUTEX_DESTROY(mut) CloseHandle (mut)
#define ___MUTEX_LOCK(mut) (WaitForSingleObject (mut, INFINITE) != WAIT_FAILED)
#define ___MUTEX_UNLOCK(mut) ReleaseMutex (mut)

#endif


#if 0
/*TODO: enable*/
#if ___WS == 4
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
#define ___USE_sync_val_compare_and_swap
#endif
#else
#if ___WS == 8
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
#define ___USE_sync_val_compare_and_swap
#endif
#endif
#endif
#endif


#ifndef ___USE_sync_val_compare_and_swap
#ifdef ___USE_WIN32_THREAD_SYSTEM
#define ___USE_InterlockedCompareExchangePointer
#else
#ifdef ___USE_POSIX_THREAD_SYSTEM
#define ___USE_emulated_compare_and_swap_word
#endif
#endif
#endif


#ifdef ___USE_sync_val_compare_and_swap

#define ___COMPARE_AND_SWAP_WORD(p,newv,oldv) \
__sync_val_compare_and_swap(p,newv,oldv)

#endif


#ifdef ___USE_InterlockedCompareExchangePointer

#define ___COMPARE_AND_SWAP_WORD(p,newv,oldv) \
___CAST(___WORD,InterlockedCompareExchangePointer(___CAST(void**,p),___CAST(void*,oldv),___CAST(void*,newv)))

#endif


#ifdef ___USE_emulated_compare_and_swap_word

#define ___COMPARE_AND_SWAP_WORD(p,newv,oldv) \
___EXT(___emulated_compare_and_swap_word)(p,newv,oldv)

#endif


/*---------------------------------------------------------------------------*/

/* TODO: where to put this? */

/* Memory management */

/*
 * Movable Scheme objects are allocated in an area of memory
 * distributed in multiple noncontiguous sections (collectively
 * called the "msections").  All sections are of the same size and are
 * allocated through the '___alloc_mem' function.  The number of
 * sections can expand and contract to accommodate the needs of the
 * program.
 */

typedef struct ___msect
  {
    int index;             /* index in list of sections */
    int pos;               /* position in msections's 'sections' array */
    ___WORD *alloc;        /* heap allocation pointer, grows towards high addr. */
    struct ___msect *prev; /* previous section in list of sections */
    struct ___msect *next; /* next section in list of sections */
    ___WORD base[1];       /* content of section */
  } ___msection;

#define ___sizeof_msection(n) (sizeof (___msection) + ((n)-1) * ___WS)

typedef struct
  {
    int max_nb_sections;      /* actual size of 'sections' array */
    int nb_sections;          /* number of sections */
    ___msection *head;        /* head of doubly-linked list of sections */
    ___msection *tail;        /* tail of doubly-linked list of sections */
    ___msection *sections[1]; /* each section ordered by address */
                              /* (increasing order if ___ALLOC_MEM_UP */
                              /* is defined otherwise decreasing order) */
  } ___msections;

#define ___sizeof_msections(n) (sizeof (___msections) + ((n)-1) * sizeof (___msection*))

/*
 * Header structure of reference counted blocks of memory.
 */

typedef struct ___rc_header_struct
  {
    struct ___rc_header_struct *prev;
    struct ___rc_header_struct *next;
    ___SCMOBJ refcount; /* integer but declared ___SCMOBJ for alignment */
    ___SCMOBJ data; /* needed for C closures */
  } ___rc_header;

typedef struct ___pstate_mem_struct {

/* msection where continuation frames are currently being allocated */
___msection *stack_msection_;

/* start of allocation of continuation frames in stack_msection */
___WORD *alloc_stack_start_;

/* allocation pointer for continuation frames in stack_msection */
___WORD *alloc_stack_ptr_;

/* allocation limit for continuation frames in stack_msection */
___WORD *alloc_stack_limit_;

/* msection where movable objects are currently being allocated */
___msection *heap_msection_;

/* start of allocation of movable objects in heap_msection */
___WORD *alloc_heap_start_;

/* allocation pointer for movable objects in heap_msection */
___WORD *alloc_heap_ptr_;

/* allocation limit for movable objects in heap_msection */
___WORD *alloc_heap_limit_;

#ifdef ___CALL_GC_FREQUENTLY
int gc_calls_to_punt_;
#endif
} ___pstate_mem;

typedef struct ___vmstate_mem_struct {

/* size of heap in words (number of words that can be occupied) */
___SIZE_TS heap_size_;

/*
 * 'normal_overflow_reserve' is the number of words reserved in the
 * heap in normal circumstances for handling heap overflows.
 */
___SIZE_TS normal_overflow_reserve_;

/*
 * 'overflow_reserve' is the number of words currently reserved in the
 * heap for handling heap overflows.  Initially 'overflow_reserve' is
 * set to 'normal_overflow_reserve'.  When a heap overflow occurs,
 * some fraction of the 'overflow_reserve' is made available to the
 * heap overflow handler.  When a GC makes at least
 * 'normal_overflow_reserve' free, then 'overflow_reserve' is reset to
 * 'normal_overflow_reserve'.
 */
___SIZE_TS overflow_reserve_;

/* words occupied by nonmovable objects */
___SIZE_TS words_nonmovable_;

/* words occupied in heap by movable objects excluding current msections */
___SIZE_TS words_prev_msections_;

/* list of still objects */
___WORD still_objs_;

/* still objects remaining to scan */
___WORD still_objs_to_scan_;

/* the msections */
___msections *the_msections_;

/* location of tospace in each msection */
___BOOL tospace_at_top_;

/* number of msections used */
int nb_msections_used_;

/* last msection allocated */
___msection *alloc_msection_;

/* msection currently being scanned */
___msection *scan_msection_;

/* scan pointer in msection being scanned */
___WORD *scan_ptr_;

/* indicates if weak references must be traversed */
___BOOL traverse_weak_refs_;

/* GC hash tables reached by GC */
___WORD reached_gc_hash_tables_;

/* Head of list of reference counted blocks of memory */
___rc_header rc_head_;

/*
 * Garbage collection statistics.
 */

___F64 nb_gcs_;
___F64 gc_user_time_;
___F64 gc_sys_time_;
___F64 gc_real_time_;
___F64 bytes_allocated_minus_occupied_;

___F64 last_gc_user_time_;
___F64 last_gc_sys_time_;
___F64 last_gc_real_time_;
___F64 last_gc_heap_size_;
___F64 last_gc_alloc_;
___F64 last_gc_live_;
___F64 last_gc_movable_;
___F64 last_gc_nonmovable_;

} ___vmstate_mem;

typedef struct ___gstate_mem_struct {

  /*
   * Permanent objects are allocated in sections called "psections".
   * Each section contains multiple objects.  The sections are kept in a
   * list so that the storage they occupy can be reclaimed when the
   * program terminates.
   */

  void *psections;       /* list of psections */
  ___WORD *palloc_ptr;   /* allocation pointer in current psection */
  ___WORD *palloc_limit; /* allocation limit in current psection */

  /*
   * Global variables.
   */

  ___SIZE_T nb_glo_vars;    /* number of global variables */

  ___glo_struct *glo_list_head;  /* list of global variables */
  ___glo_struct *glo_list_tail;

} ___gstate_mem;

/*---------------------------------------------------------------------------*/

typedef struct ___processor_state_struct *___processor_state;
typedef struct ___virtual_machine_state_struct *___virtual_machine_state;
typedef struct ___global_state_struct *___global_state;

/* Processor structure */

typedef struct ___processor_state_struct
  {
    ___WORD *stack_trip;
    ___WORD *stack_limit;
    ___WORD *fp;
    ___WORD *stack_start;
    ___WORD *stack_break;

    ___WORD *heap_limit;
    ___WORD *hp;

    ___WORD current_thread;
    ___WORD run_queue;

    ___WORD r[___NB_GVM_REGS];
    ___WORD pc;
    ___WORD temp1;
    ___WORD temp2;
    ___WORD temp3;
    ___WORD temp4;

    int na;

    ___WORD intr_enabled; /* global interrupt enable */
    ___WORD intr_mask; /* 1 bit means interrupt disabled */
    ___WORD intr_flag[___NB_INTRS];

    ___WORD executable_wills;
    ___WORD nonexecutable_wills;

    ___pstate_mem mem; /* memory management state */

    void (*dummy8) ___PVOID;
    void (*dummy7) ___PVOID;
    void (*dummy6) ___PVOID;
    void (*dummy5) ___PVOID;
    void (*dummy4) ___PVOID;
    void (*dummy3) ___PVOID;
    void (*dummy2) ___PVOID;
    void (*dummy1) ___PVOID;

#ifndef ___SINGLE_THREADED_VMS

    /* TODO: replace circular list by array */
    struct ___processor_state_struct *prev; /* circular list links */
    struct ___processor_state_struct *next;

    struct ___virtual_machine_state_struct *vmstate; /* this processor's VM */

#endif

#ifdef ___USE_SETJMP
    ___jmpbuf_struct *catcher;
#endif

#ifdef ___DEBUG_STACK_LIMIT
    int poll_line;
    char *poll_file;
    int stack_limit_line;
    char *stack_limit_file;
#endif

#ifdef ___DEBUG_HEAP_LIMIT
    int check_heap_line;
    char *check_heap_file;
    int heap_limit_line;
    char *heap_limit_file;
#endif

#ifdef ___HEARTBEAT_USING_POLL_COUNTDOWN
    int heartbeat_interval;
    int heartbeat_countdown;
#endif
  } ___processor_state_struct;

typedef ___WORD (*___host) ___P((___processor_state ___ps),());

typedef struct ___label_struct
  {
    ___WORD header;
    ___WORD entry_or_descr;
    ___FAKEVOIDSTAR host_label;
    ___FAKEHOST host;
  } ___label_struct;

#ifdef ___LABEL_ACCESS_OLD

#define ___LABEL_ENTRY_OR_DESCR(lbl)(___CAST(___label_struct*,(lbl)-___tSUBTYPED)->entry_or_descr)
#define ___LABEL_HOST_LABEL(lbl)___CAST_FAKEVOIDSTAR_TO_VOIDSTAR(___CAST(___label_struct*,(lbl)-___tSUBTYPED)->host_label)
#define ___LABEL_HOST(lbl)___CAST_FAKEHOST_TO_HOST(___CAST(___label_struct*,(lbl)-___tSUBTYPED)->host)

#else

#define ___LABEL_ENTRY_OR_DESCR(lbl)(*___CAST(___WORD*,(lbl)+((1<<___LWS)-___tSUBTYPED)))
#define ___LABEL_HOST_LABEL(lbl)(*___CAST(___FAKEVOIDSTAR*,(lbl)+((2<<___LWS)-___tSUBTYPED)))
#define ___LABEL_HOST(lbl)(*___CAST(___FAKEHOST*,(lbl)+((3<<___LWS)-___tSUBTYPED)))

#endif

/* Module structure */

typedef struct ___module_struct
  {
    int version;
    int kind;
    ___UTF_8STRING name;
    int flags;
    ___FAKEWORD *glotbl; int glocount; int supcount;
    ___UTF_8STRING *glo_names;
    ___FAKEWORD *symtbl; int symcount;
    ___UTF_8STRING *sym_names;
    ___FAKEWORD *keytbl; int keycount;
    ___UTF_8STRING *key_names;
    ___WORD *lp;
    ___label_struct *lbltbl; int lblcount;
    ___WORD *ofdtbl; int ofd_length;
    ___WORD *cnstbl; int cnscount;
    ___FAKEWORD *subtbl; int subcount;
    ___WORD (*setup_mod) ___PVOID;
    ___WORD (*init_mod) ___P((___PSDNC),());
    ___UTF_8STRING script_line;
    struct ___module_struct *next;

    void (*dummy8) ___PVOID;
    void (*dummy7) ___PVOID;
    void (*dummy6) ___PVOID;
    void (*dummy5) ___PVOID;
    void (*dummy4) ___PVOID;
    void (*dummy3) ___PVOID;
    void (*dummy2) ___PVOID;
    void (*dummy1) ___PVOID;

    ___SCMOBJ moddescr; /* module descriptor */

  } ___module_struct;

/* Linkfile structure */

typedef struct ___linkinfo_struct
  {
    union ___mod_or_lnk_union *mol;
    ___SCMOBJ flags;
  } ___linkinfo;

typedef struct ___linkfile_struct
  {
    int version;
    int kind;
    ___UTF_8STRING name;
    ___FAKEWORD *sym_list;
    ___FAKEWORD *key_list;
    ___linkinfo *linkertbl;

    void (*dummy8) ___PVOID;
    void (*dummy7) ___PVOID;
    void (*dummy6) ___PVOID;
    void (*dummy5) ___PVOID;
    void (*dummy4) ___PVOID;
    void (*dummy3) ___PVOID;
    void (*dummy2) ___PVOID;
    void (*dummy1) ___PVOID;
  } ___linkfile_struct;

/* Module or linkfile structure */

typedef union ___mod_or_lnk_union
  {
    ___module_struct module;
    ___linkfile_struct linkfile;
  } *___mod_or_lnk;

/* Program startup information structure */

typedef struct ___program_startup_info_struct
  {
    ___UCS_2STRING *argv;
    ___UCS_2STRING script_line;

#ifdef ___OS_WIN32

    HINSTANCE hInstance;
    HINSTANCE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;

#endif
  } ___program_startup_info_struct;

/* Virtual machine state structure */

typedef struct ___virtual_machine_state_struct
  {
    ___processor_state_struct pstate0; /* first processor of this VM */

    ___vmstate_mem mem; /* memory management state */

    ___SCMOBJ main_module_id; /* symbol identifying the VM's main module */

    void (*dummy8) ___PVOID;
    void (*dummy7) ___PVOID;
    void (*dummy6) ___PVOID;
    void (*dummy5) ___PVOID;
    void (*dummy4) ___PVOID;
    void (*dummy3) ___PVOID;
    void (*dummy2) ___PVOID;
    void (*dummy1) ___PVOID;

#ifndef ___SINGLE_VM

    struct ___virtual_machine_state_struct *prev; /* circular list links */
    struct ___virtual_machine_state_struct *next;

    ___SCMOBJ *glos; /* Scheme global variables */

#endif

  } ___virtual_machine_state_struct;

/* Setup parameters structure */

typedef struct ___setup_params_struct
  {
    int version;
    ___UCS_2STRING *argv;
    ___SIZE_T min_heap;
    ___SIZE_T max_heap;
    int live_percent;
    ___SIZE_TS (*gc_hook) ___P((___SIZE_TS avail, ___SIZE_TS live),());
    void (*display_error) ___P((char **msgs),());
    void (*fatal_error) ___P((char **msgs),());
    int standard_level;
    int debug_settings;
    int file_settings;
    int terminal_settings;
    int stdio_settings;
    ___UCS_2STRING gambcdir;
    ___UCS_2STRING *gambcdir_map;
    ___UCS_2STRING remote_dbg_addr;
    ___UCS_2STRING rpc_server_addr;
    ___mod_or_lnk (*linker) ___P((___global_state),());

    ___UCS_2 reset_argv0[1]; /* defaults for argv */
    ___UCS_2STRING reset_argv[2];

    void (*dummy8) ___PVOID;
    void (*dummy7) ___PVOID;
    void (*dummy6) ___PVOID;
    void (*dummy5) ___PVOID;
    void (*dummy4) ___PVOID;
    void (*dummy3) ___PVOID;
    void (*dummy2) ___PVOID;
    void (*dummy1) ___PVOID;
  } ___setup_params_struct;

#define ___DEBUG_SETTINGS_LEVEL_MASK          15
#define ___DEBUG_SETTINGS_LEVEL_SHIFT         0
#define ___DEBUG_SETTINGS_UNCAUGHT_MASK       (1<<4)
#define ___DEBUG_SETTINGS_UNCAUGHT_PRIMORDIAL 0
#define ___DEBUG_SETTINGS_UNCAUGHT_ALL        1
#define ___DEBUG_SETTINGS_UNCAUGHT_SHIFT      4
#define ___DEBUG_SETTINGS_ERROR_MASK          (3<<5)
#define ___DEBUG_SETTINGS_ERROR_REPL          0
#define ___DEBUG_SETTINGS_ERROR_SINGLE_STEP   1
#define ___DEBUG_SETTINGS_ERROR_QUIT          2
#define ___DEBUG_SETTINGS_ERROR_SHIFT         5
#define ___DEBUG_SETTINGS_REPL_MASK           (3<<7)
#define ___DEBUG_SETTINGS_REPL_IDE            0
#define ___DEBUG_SETTINGS_REPL_CONSOLE        1
#define ___DEBUG_SETTINGS_REPL_STDIO          2
#define ___DEBUG_SETTINGS_REPL_REMOTE         3
#define ___DEBUG_SETTINGS_REPL_SHIFT          7
#define ___DEBUG_SETTINGS_USER_INTR_MASK      (3<<9)
#define ___DEBUG_SETTINGS_USER_INTR_REPL      0
#define ___DEBUG_SETTINGS_USER_INTR_DEFER     1
#define ___DEBUG_SETTINGS_USER_INTR_QUIT      2
#define ___DEBUG_SETTINGS_USER_INTR_SHIFT     9

#define ___DEBUG_SETTINGS_LEVEL(settings) \
(((settings) & ___DEBUG_SETTINGS_LEVEL_MASK) \
 >> ___DEBUG_SETTINGS_LEVEL_SHIFT)

#define ___DEBUG_SETTINGS_UNCAUGHT(settings) \
(((settings) & ___DEBUG_SETTINGS_UNCAUGHT_MASK) \
 >> ___DEBUG_SETTINGS_LEVEL_SHIFT)

#define ___DEBUG_SETTINGS_ERROR(settings) \
(((settings) & ___DEBUG_SETTINGS_ERROR_MASK) \
 >> ___DEBUG_SETTINGS_LEVEL_SHIFT)

#define ___DEBUG_SETTINGS_REPL(settings) \
(((settings) & ___DEBUG_SETTINGS_REPL_MASK) \
 >> ___DEBUG_SETTINGS_LEVEL_SHIFT)

#define ___DEBUG_SETTINGS_USER_INTR(settings) \
(((settings) & ___DEBUG_SETTINGS_USER_INTR_MASK) \
 >> ___DEBUG_SETTINGS_LEVEL_SHIFT)

#define ___DEBUG_SETTINGS_INITIAL \
((1 << ___DEBUG_SETTINGS_LEVEL_SHIFT) | \
 (___DEBUG_SETTINGS_UNCAUGHT_PRIMORDIAL \
  << ___DEBUG_SETTINGS_UNCAUGHT_SHIFT) | \
 (___DEBUG_SETTINGS_ERROR_QUIT \
  << ___DEBUG_SETTINGS_ERROR_SHIFT) | \
 (___DEBUG_SETTINGS_REPL_IDE \
  << ___DEBUG_SETTINGS_REPL_SHIFT) | \
 (___DEBUG_SETTINGS_USER_INTR_QUIT \
  << ___DEBUG_SETTINGS_USER_INTR_SHIFT))

#define ___DEBUG_SETTINGS_DEFAULT \
((1 << ___DEBUG_SETTINGS_LEVEL_SHIFT) | \
 (___DEBUG_SETTINGS_UNCAUGHT_PRIMORDIAL \
  << ___DEBUG_SETTINGS_UNCAUGHT_SHIFT) | \
 (___DEBUG_SETTINGS_ERROR_REPL \
  << ___DEBUG_SETTINGS_ERROR_SHIFT) | \
 (___DEBUG_SETTINGS_REPL_IDE \
  << ___DEBUG_SETTINGS_REPL_SHIFT) | \
 (___DEBUG_SETTINGS_USER_INTR_REPL \
  << ___DEBUG_SETTINGS_USER_INTR_SHIFT))

/* Global state structure */

typedef struct ___global_state_struct
  {
    ___virtual_machine_state_struct vmstate0; /* first VM */

    int setup_state; /* 0=pre-setup, 1=post-setup, 2=post-cleanup */

    struct ___setup_params_struct setup_params; /* params received by ___setup */

    ___WORD handler_sfun_conv_error;
    ___WORD handler_cfun_conv_error;
    ___WORD handler_stack_limit;
    ___WORD handler_heap_limit;
    ___WORD handler_not_proc;
    ___WORD handler_not_proc_glo;
    ___WORD handler_wrong_nargs;
    ___WORD handler_get_rest;
    ___WORD handler_get_key;
    ___WORD handler_get_key_rest;
    ___WORD handler_force;
    ___WORD handler_return_to_c;
    ___WORD handler_break;
    ___WORD internal_return;
    ___WORD dynamic_env_bind_return;

    ___SCMOBJ symbol_table;   /* Hash table of all interned symbols.  */
    ___SCMOBJ keyword_table;  /* Hash table of all interned keywords. */
    ___SCMOBJ command_line;   /* List of command line arguments.      */
    ___SCMOBJ program_descr;  /* Program descriptor.                  */

    ___gstate_mem mem; /* memory management state */

    void (*dummy8) ___PVOID;
    void (*dummy7) ___PVOID;
    void (*dummy6) ___PVOID;
    void (*dummy5) ___PVOID;
    void (*dummy4) ___PVOID;
    void (*dummy3) ___PVOID;
    void (*dummy2) ___PVOID;
    void (*dummy1) ___PVOID;

#ifndef ___CAN_IMPORT_CLIB_DYNAMICALLY
    double (*fabs)
       ___P((double x),
            ());
    double (*floor)
       ___P((double x),
            ());
    double (*ceil)
       ___P((double x),
            ());
    double (*scalbn)
       ___P((double x,
             int n),
            ());
    int (*ilogb)
       ___P((double x),
            ());
    double (*exp)
       ___P((double x),
            ());
    double (*expm1)
       ___P((double x),
            ());
    double (*log)
       ___P((double x),
            ());
    double (*log1p)
       ___P((double x),
            ());
    double (*sin)
       ___P((double x),
            ());
    double (*cos)
       ___P((double x),
            ());
    double (*tan)
       ___P((double x),
            ());
    double (*asin)
       ___P((double x),
            ());
    double (*acos)
       ___P((double x),
            ());
    double (*atan)
       ___P((double x),
            ());
    double (*sinh)
       ___P((double x),
            ());
    double (*cosh)
       ___P((double x),
            ());
    double (*tanh)
       ___P((double x),
            ());
    double (*asinh)
       ___P((double x),
            ());
    double (*acosh)
       ___P((double x),
            ());
    double (*atanh)
       ___P((double x),
            ());
    double (*atan2)
       ___P((double y,
             double x),
            ());
    double (*pow)
       ___P((double x,
             double y),
            ());
    double (*sqrt)
       ___P((double x),
            ());
#endif

#ifdef ___USE_SETJMP
#ifndef ___CAN_IMPORT_SETJMP_DYNAMICALLY
    int (*setjmp)
       ___P((jmp_buf env),
            ());
#endif
#endif

#ifndef ___CAN_IMPORT_DYNAMICALLY
    ___BOOL (*___iswalpha)
       ___P((___UCS_4 x),
            ());
    ___BOOL (*___iswdigit)
       ___P((___UCS_4 x),
            ());
    ___BOOL (*___iswspace)
       ___P((___UCS_4 x),
            ());
    ___BOOL (*___iswupper)
       ___P((___UCS_4 x),
            ());
    ___BOOL (*___iswlower)
       ___P((___UCS_4 x),
            ());
    ___UCS_4 (*___towupper)
       ___P((___UCS_4 x),
            ());
    ___UCS_4 (*___towlower)
       ___P((___UCS_4 x),
            ());
    ___SCMOBJ (*___string_collate)
       ___P((___SCMOBJ s1,
             ___SCMOBJ s2),
            ());
    ___SCMOBJ (*___string_collate_ci)
       ___P((___SCMOBJ s1,
             ___SCMOBJ s2),
            ());
    double (*___copysign)
       ___P((double x,
             double y),
            ());
    ___BOOL (*___isfinite)
       ___P((double x),
            ());
    ___BOOL (*___isnan)
       ___P((double x),
            ());
    double (*___trunc)
       ___P((double x),
            ());
    double (*___round)
       ___P((double x),
            ());
#ifdef ___DEFINE_SCALBN
    double (*___scalbn)
       ___P((double x,
             int n),
            ());
#endif
#ifdef ___DEFINE_ILOGB
    int (*___ilogb)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_EXPM1
    double (*___expm1)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_LOG1P
    double (*___log1p)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_SINH
    double (*___sinh)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_COSH
    double (*___cosh)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_TANH
    double (*___tanh)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_ASINH
    double (*___asinh)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_ACOSH
    double (*___acosh)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_ATANH
    double (*___atanh)
       ___P((double x),
            ());
#endif
#ifdef ___DEFINE_ATAN2
    double (*___atan2)
       ___P((double y,
             double x),
            ());
#endif
#ifdef ___DEFINE_POW
    double (*___pow)
       ___P((double x,
             double y),
            ());
#endif
    ___S64 (*___S64_from_SM32_fn)
       ___P((___SM32 val),
            ());
    ___S64 (*___S64_from_SM32_UM32_fn)
       ___P((___SM32 hi32,
             ___UM32 lo32),
            ());
    ___S64 (*___S64_from_LONGLONG_fn)
       ___P((___LONGLONG val),
            ());
    ___LONGLONG (*___S64_to_LONGLONG_fn)
       ___P((___S64 val),
            ());
    ___BOOL (*___S64_fits_in_width_fn)
       ___P((___S64 val,
             int width),
            ());
    ___U64 (*___U64_from_UM32_fn)
       ___P((___UM32 val),
            ());
    ___U64 (*___U64_from_UM32_UM32_fn)
       ___P((___UM32 hi32,
             ___UM32 lo32),
            ());
    ___U64 (*___U64_from_ULONGLONG_fn)
       ___P((___ULONGLONG val),
            ());
    ___ULONGLONG (*___U64_to_ULONGLONG_fn)
       ___P((___U64 val),
            ());
    ___BOOL (*___U64_fits_in_width_fn)
       ___P((___U64 val,
             int width),
            ());
    ___U64 (*___U64_mul_UM32_UM32_fn)
       ___P((___UM32 x,
             ___UM32 y),
            ());
    ___U64 (*___U64_add_U64_U64_fn)
       ___P((___U64 x,
             ___U64 y),
            ());
    ___SCMOBJ (*___SCMOBJ_to_S8)
       ___P((___PSD
             ___SCMOBJ obj,
             ___S8 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_U8)
       ___P((___PSD
             ___SCMOBJ obj,
             ___U8 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_S16)
       ___P((___PSD
             ___SCMOBJ obj,
             ___S16 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_U16)
       ___P((___PSD
             ___SCMOBJ obj,
             ___U16 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_S32)
       ___P((___PSD
             ___SCMOBJ obj,
             ___S32 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_U32)
       ___P((___PSD
             ___SCMOBJ obj,
             ___U32 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_S64)
       ___P((___PSD
             ___SCMOBJ obj,
             ___S64 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_U64)
       ___P((___PSD
             ___SCMOBJ obj,
             ___U64 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_F32)
       ___P((___PSD
             ___SCMOBJ obj,
             ___F32 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_F64)
       ___P((___PSD
             ___SCMOBJ obj,
             ___F64 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_CHAR)
       ___P((___PSD
             ___SCMOBJ obj,
             char *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_SCHAR)
       ___P((___PSD
             ___SCMOBJ obj,
             ___SCHAR *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UCHAR)
       ___P((___PSD
             ___SCMOBJ obj,
             unsigned char *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_ISO_8859_1)
       ___P((___PSD
             ___SCMOBJ obj,
             ___ISO_8859_1 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UCS_2)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_2 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UCS_4)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_4 *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_WCHAR)
       ___P((___PSD
             ___SCMOBJ obj,
             ___WCHAR *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_SIZE_T)
       ___P((___PSD
             ___SCMOBJ obj,
             ___SIZE_T *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_SSIZE_T)
       ___P((___PSD
             ___SCMOBJ obj,
             ___SSIZE_T *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_PTRDIFF_T)
       ___P((___PSD
             ___SCMOBJ obj,
             ___PTRDIFF_T *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_SHORT)
       ___P((___PSD
             ___SCMOBJ obj,
             short *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_USHORT)
       ___P((___PSD
             ___SCMOBJ obj,
             unsigned short *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_INT)
       ___P((___PSD
             ___SCMOBJ obj,
             int *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UINT)
       ___P((___PSD
             ___SCMOBJ obj,
             unsigned int *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_LONG)
       ___P((___PSD
             ___SCMOBJ obj,
             long *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_ULONG)
       ___P((___PSD
             ___SCMOBJ obj,
             unsigned long *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_LONGLONG)
       ___P((___PSD
             ___SCMOBJ obj,
             ___LONGLONG *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_ULONGLONG)
       ___P((___PSD
             ___SCMOBJ obj,
             ___ULONGLONG *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_FLOAT)
       ___P((___PSD
             ___SCMOBJ obj,
             float *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_DOUBLE)
       ___P((___PSD
             ___SCMOBJ obj,
             double *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_STRUCT)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             ___SCMOBJ tags,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UNION)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             ___SCMOBJ tags,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_TYPE)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             ___SCMOBJ tags,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_POINTER)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             ___SCMOBJ tags,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLPOINTER)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             ___SCMOBJ tags,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_FUNCTION)
       ___P((___PSD
             ___SCMOBJ obj,
             void *converter,
             void **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLFUNCTION)
       ___P((___PSD
             ___SCMOBJ obj,
             void *converter,
             void **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_BOOL)
       ___P((___PSD
             ___SCMOBJ obj,
             ___BOOL *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             int arg_num,
             int char_encoding,
             int fudge),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLSTRING)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             int arg_num,
             int char_encoding,
             int fudge),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLSTRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             void **x,
             int arg_num,
             int char_encoding),
            ());
    ___SCMOBJ (*___SCMOBJ_to_CHARSTRING)
       ___P((___PSD
             ___SCMOBJ obj,
             char **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLCHARSTRING)
       ___P((___PSD
             ___SCMOBJ obj,
             char **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLCHARSTRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             char ***x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_ISO_8859_1STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___ISO_8859_1STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLISO_8859_1STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___ISO_8859_1STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLISO_8859_1STRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             ___ISO_8859_1STRING **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UTF_8STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UTF_8STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUTF_8STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UTF_8STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUTF_8STRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UTF_8STRING **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UTF_16STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UTF_16STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUTF_16STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UTF_16STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUTF_16STRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UTF_16STRING **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UCS_2STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_2STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUCS_2STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_2STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUCS_2STRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_2STRING **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_UCS_4STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_4STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUCS_4STRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_4STRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLUCS_4STRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             ___UCS_4STRING **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_WCHARSTRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___WCHARSTRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLWCHARSTRING)
       ___P((___PSD
             ___SCMOBJ obj,
             ___WCHARSTRING *x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_NONNULLWCHARSTRINGLIST)
       ___P((___PSD
             ___SCMOBJ obj,
             ___WCHARSTRING **x,
             int arg_num),
            ());
    ___SCMOBJ (*___SCMOBJ_to_VARIANT)
       ___P((___PSD
             ___SCMOBJ obj,
             ___VARIANT *x,
             int arg_num),
            ());
    ___SCMOBJ (*___release_foreign)
       ___P((___SCMOBJ obj),
            ());
    ___SCMOBJ (*___release_pointer)
       ___P((void *x),
            ());
    ___SCMOBJ (*___release_function)
       ___P((void *x),
            ());
    void (*___addref_function)
       ___P((void *x),
            ());
    void (*___release_string)
       ___P((void *x),
            ());
    void (*___addref_string)
       ___P((void *x),
            ());
    void (*___release_string_list)
       ___P((void *x),
            ());
    void (*___addref_string_list)
       ___P((void *x),
            ());
    void (*___release_variant)
       ___P((___VARIANT x),
            ());
    void (*___addref_variant)
       ___P((___VARIANT x),
            ());
    ___SCMOBJ (*___S8_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___S8 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___U8_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___U8 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___S16_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___S16 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___U16_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___U16 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___S32_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___S32 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___U32_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___U32 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___S64_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___S64 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___U64_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___U64 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___F32_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___F32 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___F64_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___F64 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___CHAR_to_SCMOBJ)
       ___P((___processor_state ___ps,
             char x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___SCHAR_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___SCHAR x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UCHAR_to_SCMOBJ)
       ___P((___processor_state ___ps,
             unsigned char x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___ISO_8859_1_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___ISO_8859_1 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UCS_2_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_2 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UCS_4_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_4 x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___WCHAR_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___WCHAR x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___SIZE_T_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___SIZE_T x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___SSIZE_T_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___SSIZE_T x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___PTRDIFF_T_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___PTRDIFF_T x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___SHORT_to_SCMOBJ)
       ___P((___processor_state ___ps,
             short x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___USHORT_to_SCMOBJ)
       ___P((___processor_state ___ps,
             unsigned short x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___INT_to_SCMOBJ)
       ___P((___processor_state ___ps,
             int x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UINT_to_SCMOBJ)
       ___P((___processor_state ___ps,
             unsigned int x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___LONG_to_SCMOBJ)
       ___P((___processor_state ___ps,
             long x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___ULONG_to_SCMOBJ)
       ___P((___processor_state ___ps,
             unsigned long x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___LONGLONG_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___LONGLONG x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___ULONGLONG_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___ULONGLONG x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___FLOAT_to_SCMOBJ)
       ___P((___processor_state ___ps,
             float x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___DOUBLE_to_SCMOBJ)
       ___P((___processor_state ___ps,
             double x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___STRUCT_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ tags,
             ___SCMOBJ (*release_fn) ___P((void *ptr),()),
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UNION_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ tags,
             ___SCMOBJ (*release_fn) ___P((void *ptr),()),
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___TYPE_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ tags,
             ___SCMOBJ (*release_fn) ___P((void *ptr),()),
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___POINTER_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ tags,
             ___SCMOBJ (*release_fn) ___P((void *ptr),()),
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLPOINTER_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ tags,
             ___SCMOBJ (*release_fn) ___P((void *ptr),()),
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___FUNCTION_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLFUNCTION_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___BOOL_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___BOOL x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ *obj,
             int arg_num,
             int char_encoding),
            ());
    ___SCMOBJ (*___NONNULLSTRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ *obj,
             int arg_num,
             int char_encoding),
            ());
    ___SCMOBJ (*___NONNULLSTRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             void *x,
             ___SCMOBJ *obj,
             int arg_num,
             int char_encoding),
            ());
    ___SCMOBJ (*___CHARSTRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             char *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLCHARSTRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             char *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLCHARSTRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             char **x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___ISO_8859_1STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___ISO_8859_1STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLISO_8859_1STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___ISO_8859_1STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLISO_8859_1STRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___ISO_8859_1STRING *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UTF_8STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UTF_8STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUTF_8STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UTF_8STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUTF_8STRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UTF_8STRING *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UTF_16STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UTF_16STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUTF_16STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UTF_16STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUTF_16STRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UTF_16STRING *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UCS_2STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_2STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUCS_2STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_2STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUCS_2STRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_2STRING *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___UCS_4STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_4STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUCS_4STRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_4STRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLUCS_4STRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___UCS_4STRING *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___WCHARSTRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___WCHARSTRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLWCHARSTRING_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___WCHARSTRING x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___NONNULLWCHARSTRINGLIST_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___WCHARSTRING *x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___VARIANT_to_SCMOBJ)
       ___P((___processor_state ___ps,
             ___VARIANT x,
             ___SCMOBJ *obj,
             int arg_num),
            ());
    ___SCMOBJ (*___CHARSTRING_to_UCS_2STRING)
       ___P((char *str_char,
             ___UCS_2STRING *str_UCS_2),
            ());
    void (*___free_UCS_2STRING)
       ___P((___UCS_2STRING str_UCS_2),
            ());
    ___SCMOBJ (*___NONNULLCHARSTRINGLIST_to_NONNULLUCS_2STRINGLIST)
       ___P((char **str_list_char,
             ___UCS_2STRING **str_list_UCS_2),
            ());
    void (*___free_NONNULLUCS_2STRINGLIST)
       ___P((___UCS_2STRING *str_list_UCS_2),
            ());
    ___SCMOBJ (*___make_sfun_stack_marker)
       ___P((___processor_state ___ps,
             ___SCMOBJ *marker,
             ___SCMOBJ proc_or_false),
            ());
    void (*___kill_sfun_stack_marker)
       ___P((___SCMOBJ marker),
            ());
    void *(*___alloc_rc)
       ___P((___PSD
             ___SIZE_T bytes),
            ());
    void (*___release_rc)
       ___P((void *ptr),
            ());
    void (*___addref_rc)
       ___P((void *ptr),
            ());
    ___SCMOBJ (*___data_rc)
       ___P((void *ptr),
            ());
    void (*___set_data_rc)
       ___P((void *ptr,
             ___SCMOBJ val),
            ());
    ___SCMOBJ (*___alloc_scmobj)
       ___P((___processor_state ___ps,
             int subtype,
             ___SIZE_TS bytes),
            ());
    void (*___release_scmobj)
       ___P((___SCMOBJ obj),
            ());
    ___SCMOBJ (*___make_pair)
       ___P((___processor_state ___ps,
             ___SCMOBJ car,
             ___SCMOBJ cdr),
            ());
    ___SCMOBJ (*___make_vector)
       ___P((___processor_state ___ps,
             ___SIZE_TS length,
             ___SCMOBJ init),
            ());
    void (*___still_obj_refcount_inc)
       ___P((___SCMOBJ obj),
            ());
    void (*___still_obj_refcount_dec)
       ___P((___SCMOBJ obj),
            ());
    ___SCMOBJ (*___gc_hash_table_ref)
       ___P((___SCMOBJ ht,
             ___SCMOBJ key),
            ());
    ___SCMOBJ (*___gc_hash_table_set)
       ___P((___SCMOBJ ht,
             ___SCMOBJ key,
             ___SCMOBJ val),
            ());
    ___SCMOBJ (*___gc_hash_table_rehash)
       ___P((___SCMOBJ ht_src,
             ___SCMOBJ ht_dst),
            ());
    void (*___cleanup) ___PVOID;
    void (*___cleanup_and_exit_process)
       ___P((int status),
            ());
    ___SCMOBJ (*___setup_vmstate)
       ___P((___virtual_machine_state ___vms),
            ());
    void (*___cleanup_vmstate)
       ___P((___virtual_machine_state ___vms),
            ());
    ___SCMOBJ (*___setup_pstate)
       ___P((___processor_state ___ps,
             ___virtual_machine_state ___vms),
            ());
    void (*___cleanup_pstate)
       ___P((___processor_state ___ps),
            ());
    ___SIZE_T (*___get_min_heap) ___PVOID;
    void (*___set_min_heap)
       ___P((___SIZE_T bytes),
            ());
    ___SIZE_T (*___get_max_heap) ___PVOID;
    void (*___set_max_heap)
       ___P((___SIZE_T bytes),
            ());
    int (*___get_live_percent) ___PVOID;
    void (*___set_live_percent)
       ___P((int percent),
            ());
    int (*___get_standard_level) ___PVOID;
    void (*___set_standard_level)
       ___P((int level),
            ());
    void (*___set_gambcdir)
       ___P((___UCS_2STRING gambcdir),
            ());
    int (*___set_debug_settings)
       ___P((int mask,
             int new_settings),
            ());
    ___program_startup_info_struct *(*___get_program_startup_info) ___PVOID;
    ___SCMOBJ (*___call)
       ___P((___PSD
             int nargs,
             ___SCMOBJ proc,
             ___SCMOBJ marker),
            ());
    void (*___propagate_error)
       ___P((___PSD
             ___SCMOBJ err),
            ());
#ifdef ___DEBUG_HOST_CHANGES
    void (*___register_host_entry)
       ___P((___PSD
             ___WORD start,
             char *module_name),
            ());
#endif
    void (*___raise_interrupt_pstate)
       ___P((___processor_state ___ps,
             int code),
            ());
    void (*___raise_interrupt_vmstate)
       ___P((___virtual_machine_state ___vms,
             int code),
            ());
    void (*___raise_interrupt)
       ___P((int code),
            ());
    void (*___begin_interrupt_service_pstate)
       ___P((___PSDNC),
            ());
    ___BOOL (*___check_interrupt_pstate)
       ___P((___PSD
             int code),
            ());
    void (*___end_interrupt_service_pstate)
       ___P((___PSD
             int code),
            ());
    void (*___disable_interrupts_pstate)
       ___P((___PSDNC),
            ());
    void (*___enable_interrupts_pstate)
       ___P((___PSDNC),
            ());
    void *(*___alloc_mem)
       ___P((___SIZE_T bytes),
            ());
    void (*___free_mem)
       ___P((void *ptr),
            ());
    void *(*___alloc_mem_code)
       ___P((___SIZE_T bytes),
            ());
    void (*___free_mem_code)
       ___P((void *ptr),
            ());
#ifdef ___USE_emulated_compare_and_swap_word
    ___WORD (*___emulated_compare_and_swap_word)
       ___P((___WORD *ptr,
             ___WORD oldval,
             ___WORD newval),
            ());
#endif
#ifndef ___THREAD_LOCAL_STORAGE_CLASS
    void *(*___get_tls_ptr) ___PVOID;
    void (*___set_tls_ptr)
       ___P((void *ptr),
            ());
#endif
    void (*___disable_heartbeat_interrupts) ___PVOID;
    void (*___enable_heartbeat_interrupts) ___PVOID;
#endif
  } ___global_state_struct;

#ifdef ___LBLCOUNT
___LOCAL ___WORD ___lp; /* Module's label table pointer */
#endif

___GLODECL
___SYMDECL
___KEYDECL

#define ___CHAR_ENCODING(x)                       ((x)&(31<<0))
#define ___CHAR_ENCODING_MASK(x)                  ((x)&~(31<<0))
#define ___CHAR_ENCODING_ASCII                    (1<<0)
#define ___CHAR_ENCODING_ISO_8859_1               (2<<0)
#define ___CHAR_ENCODING_UTF_8                    (3<<0)
#define ___CHAR_ENCODING_UTF_16                   (4<<0)
#define ___CHAR_ENCODING_UTF_16BE                 (5<<0)
#define ___CHAR_ENCODING_UTF_16LE                 (6<<0)
#define ___CHAR_ENCODING_UTF_FALLBACK_ASCII       (7<<0)
#define ___CHAR_ENCODING_UTF_FALLBACK_ISO_8859_1  (8<<0)
#define ___CHAR_ENCODING_UTF_FALLBACK_UTF_8       (9<<0)
#define ___CHAR_ENCODING_UTF_FALLBACK_UTF_16      (10<<0)
#define ___CHAR_ENCODING_UTF_FALLBACK_UTF_16BE    (11<<0)
#define ___CHAR_ENCODING_UTF_FALLBACK_UTF_16LE    (12<<0)
#define ___CHAR_ENCODING_UCS_2                    (13<<0)
#define ___CHAR_ENCODING_UCS_2BE                  (14<<0)
#define ___CHAR_ENCODING_UCS_2LE                  (15<<0)
#define ___CHAR_ENCODING_UCS_4                    (16<<0)
#define ___CHAR_ENCODING_UCS_4BE                  (17<<0)
#define ___CHAR_ENCODING_UCS_4LE                  (18<<0)
#define ___CHAR_ENCODING_WCHAR                    (19<<0)
#define ___CHAR_ENCODING_NATIVE                   (20<<0)

#define ___CHAR_ENCODING_UTF ___CHAR_ENCODING_UTF_FALLBACK_UTF_8

#define ___CHAR_ENCODING_SUPPORTS_BMP(x) \
((x) >= ___CHAR_ENCODING_UTF_8 && \
 (x) <= ___CHAR_ENCODING_UCS_4LE)

#ifdef ___BIG_ENDIAN
#define ___CHAR_ENCODING_U8  ___CHAR_ENCODING_ISO_8859_1
#define ___CHAR_ENCODING_U16 ___CHAR_ENCODING_UCS_2BE
#define ___CHAR_ENCODING_U32 ___CHAR_ENCODING_UCS_4BE
#else
#define ___CHAR_ENCODING_U8  ___CHAR_ENCODING_ISO_8859_1
#define ___CHAR_ENCODING_U16 ___CHAR_ENCODING_UCS_2LE
#define ___CHAR_ENCODING_U32 ___CHAR_ENCODING_UCS_4LE
#endif

#define ___CHAR_ENCODING_ERRORS(x)      ((x)&(3<<5))
#define ___CHAR_ENCODING_ERRORS_MASK(x) ((x)&~(3<<5))
#define ___CHAR_ENCODING_ERRORS_ON      (1<<5)
#define ___CHAR_ENCODING_ERRORS_OFF     (2<<5)

#define ___EOL_ENCODING(x)      ((x)&(3<<7))
#define ___EOL_ENCODING_MASK(x) ((x)&~(3<<7))
#define ___EOL_ENCODING_LF      (1<<7)
#define ___EOL_ENCODING_CR      (2<<7)
#define ___EOL_ENCODING_CRLF    (3<<7)

#define ___BUFFERING(x)      ((x)&(3<<9))
#define ___BUFFERING_MASK(x) ((x)&~(3<<9))
#define ___NO_BUFFERING      (1<<9)
#define ___LINE_BUFFERING    (2<<9)
#define ___FULL_BUFFERING    (3<<9)
#define ___FULLY_BUFFERED(x)  (___BUFFERING(x)>=___FULL_BUFFERING)

#define ___DECODE_STATE(x)      ((x)&(3<<11))
#define ___DECODE_STATE_MASK(x) ((x)&~(3<<11))
#define ___DECODE_STATE_NONE    (0<<11)
#define ___DECODE_STATE_LF      (1<<11)
#define ___DECODE_STATE_CR      (2<<11)

#define ___TERMINAL_LINE_EDITING(x)      ((x)&(3<<16))
#define ___TERMINAL_LINE_EDITING_MASK(x) ((x)&~(3<<16))
#define ___TERMINAL_LINE_EDITING_ON      (1<<16)
#define ___TERMINAL_LINE_EDITING_OFF     (2<<16)

#define ___FILE_SETTINGS_INITIAL 0
#define ___TERMINAL_SETTINGS_INITIAL 0
#define ___STDIO_SETTINGS_INITIAL 0

#ifndef ___INCLUDED_FROM_C_INTF
___IMP_FUNC(___S64,___S64_from_SM32_fn)
   ___P((___SM32 val),
        ());
___IMP_FUNC(___S64,___S64_from_SM32_UM32_fn)
   ___P((___SM32 hi32,
         ___UM32 lo32),
        ());
___IMP_FUNC(___S64,___S64_from_LONGLONG_fn)
   ___P((___LONGLONG val),
        ());
___IMP_FUNC(___LONGLONG,___S64_to_LONGLONG_fn)
   ___P((___S64 val),
        ());
___IMP_FUNC(___BOOL,___S64_fits_in_width_fn)
   ___P((___S64 val,
         int width),
        ());
___IMP_FUNC(___U64,___U64_from_UM32_fn)
   ___P((___UM32 val),
        ());
___IMP_FUNC(___U64,___U64_from_UM32_UM32_fn)
   ___P((___UM32 hi32,
         ___UM32 lo32),
        ());
___IMP_FUNC(___U64,___U64_from_ULONGLONG_fn)
   ___P((___ULONGLONG val),
        ());
___IMP_FUNC(___ULONGLONG,___U64_to_ULONGLONG_fn)
   ___P((___U64 val),
        ());
___IMP_FUNC(___BOOL,___U64_fits_in_width_fn)
   ___P((___U64 val,
         int width),
        ());
___IMP_FUNC(___U64,___U64_mul_UM32_UM32_fn)
   ___P((___UM32 x,
         ___UM32 y),
        ());
___IMP_FUNC(___U64,___U64_add_U64_U64_fn)
   ___P((___U64 x,
         ___U64 y),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_S8)
   ___P((___PSD
         ___SCMOBJ obj,
         ___S8 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_U8)
   ___P((___PSD
         ___SCMOBJ obj,
         ___U8 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_S16)
   ___P((___PSD
         ___SCMOBJ obj,
         ___S16 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_U16)
   ___P((___PSD
         ___SCMOBJ obj,
         ___U16 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_S32)
   ___P((___PSD
         ___SCMOBJ obj,
         ___S32 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_U32)
   ___P((___PSD
         ___SCMOBJ obj,
         ___U32 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_S64)
   ___P((___PSD
         ___SCMOBJ obj,
         ___S64 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_U64)
   ___P((___PSD
         ___SCMOBJ obj,
         ___U64 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_F32)
   ___P((___PSD
         ___SCMOBJ obj,
         ___F32 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_F64)
   ___P((___PSD
         ___SCMOBJ obj,
         ___F64 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_CHAR)
   ___P((___PSD
         ___SCMOBJ obj,
         char *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_SCHAR)
   ___P((___PSD
         ___SCMOBJ obj,
         ___SCHAR *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UCHAR)
   ___P((___PSD
         ___SCMOBJ obj,
         unsigned char *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_ISO_8859_1)
   ___P((___PSD
         ___SCMOBJ obj,
         ___ISO_8859_1 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UCS_2)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_2 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UCS_4)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_4 *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_WCHAR)
   ___P((___PSD
         ___SCMOBJ obj,
         ___WCHAR *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_SIZE_T)
   ___P((___PSD
         ___SCMOBJ obj,
         ___SIZE_T *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_SSIZE_T)
   ___P((___PSD
         ___SCMOBJ obj,
         ___SSIZE_T *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_PTRDIFF_T)
   ___P((___PSD
         ___SCMOBJ obj,
         ___PTRDIFF_T *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_SHORT)
   ___P((___PSD
         ___SCMOBJ obj,
         short *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_USHORT)
   ___P((___PSD
         ___SCMOBJ obj,
         unsigned short *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_INT)
   ___P((___PSD
         ___SCMOBJ obj,
         int *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UINT)
   ___P((___PSD
         ___SCMOBJ obj,
         unsigned int *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_LONG)
   ___P((___PSD
         ___SCMOBJ obj,
         long *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_ULONG)
   ___P((___PSD
         ___SCMOBJ obj,
         unsigned long *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_LONGLONG)
   ___P((___PSD
         ___SCMOBJ obj,
         ___LONGLONG *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_ULONGLONG)
   ___P((___PSD
         ___SCMOBJ obj,
         ___ULONGLONG *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_FLOAT)
   ___P((___PSD
         ___SCMOBJ obj,
         float *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_DOUBLE)
   ___P((___PSD
         ___SCMOBJ obj,
         double *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_STRUCT)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         ___SCMOBJ tags,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UNION)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         ___SCMOBJ tags,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_TYPE)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         ___SCMOBJ tags,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_POINTER)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         ___SCMOBJ tags,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLPOINTER)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         ___SCMOBJ tags,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_FUNCTION)
   ___P((___PSD
         ___SCMOBJ obj,
         void *converter,
         void **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLFUNCTION)
   ___P((___PSD
         ___SCMOBJ obj,
         void *converter,
         void **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_BOOL)
   ___P((___PSD
         ___SCMOBJ obj,
         ___BOOL *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         int arg_num,
         int char_encoding,
         int fudge),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLSTRING)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         int arg_num,
         int char_encoding,
         int fudge),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLSTRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         void **x,
         int arg_num,
         int char_encoding),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_CHARSTRING)
   ___P((___PSD
         ___SCMOBJ obj,
         char **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLCHARSTRING)
   ___P((___PSD
         ___SCMOBJ obj,
         char **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLCHARSTRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         char ***x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_ISO_8859_1STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___ISO_8859_1STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLISO_8859_1STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___ISO_8859_1STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLISO_8859_1STRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         ___ISO_8859_1STRING **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UTF_8STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UTF_8STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUTF_8STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UTF_8STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUTF_8STRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UTF_8STRING **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UTF_16STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UTF_16STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUTF_16STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UTF_16STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUTF_16STRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UTF_16STRING **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UCS_2STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_2STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUCS_2STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_2STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUCS_2STRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_2STRING **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_UCS_4STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_4STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUCS_4STRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_4STRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLUCS_4STRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         ___UCS_4STRING **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_WCHARSTRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___WCHARSTRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLWCHARSTRING)
   ___P((___PSD
         ___SCMOBJ obj,
         ___WCHARSTRING *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_NONNULLWCHARSTRINGLIST)
   ___P((___PSD
         ___SCMOBJ obj,
         ___WCHARSTRING **x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCMOBJ_to_VARIANT)
   ___P((___PSD
         ___SCMOBJ obj,
         ___VARIANT *x,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___release_foreign)
   ___P((___SCMOBJ obj),
        ());
___IMP_FUNC(___SCMOBJ,___release_pointer)
   ___P((void *x),
        ());
___IMP_FUNC(___SCMOBJ,___release_function)
   ___P((void *x),
        ());
___IMP_FUNC(void,___addref_function)
   ___P((void *x),
        ());
___IMP_FUNC(void,___release_string)
   ___P((void *x),
        ());
___IMP_FUNC(void,___addref_string)
   ___P((void *x),
        ());
___IMP_FUNC(void,___release_string_list)
   ___P((void *x),
        ());
___IMP_FUNC(void,___addref_string_list)
   ___P((void *x),
        ());
___IMP_FUNC(void,___release_variant)
   ___P((___VARIANT x),
        ());
___IMP_FUNC(void,___addref_variant)
   ___P((___VARIANT x),
        ());
___IMP_FUNC(___SCMOBJ,___S8_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___S8 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___U8_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___U8 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___S16_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___S16 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___U16_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___U16 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___S32_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___S32 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___U32_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___U32 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___S64_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___S64 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___U64_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___U64 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___F32_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___F32 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___F64_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___F64 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___CHAR_to_SCMOBJ)
   ___P((___processor_state ___ps,
         char x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SCHAR_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___SCHAR x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UCHAR_to_SCMOBJ)
   ___P((___processor_state ___ps,
         unsigned char x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___ISO_8859_1_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___ISO_8859_1 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UCS_2_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_2 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UCS_4_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_4 x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___WCHAR_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___WCHAR x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SIZE_T_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___SIZE_T x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SSIZE_T_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___SSIZE_T x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___PTRDIFF_T_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___PTRDIFF_T x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___SHORT_to_SCMOBJ)
   ___P((___processor_state ___ps,
         short x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___USHORT_to_SCMOBJ)
   ___P((___processor_state ___ps,
         unsigned short x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___INT_to_SCMOBJ)
   ___P((___processor_state ___ps,
         int x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UINT_to_SCMOBJ)
   ___P((___processor_state ___ps,
         unsigned int x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___LONG_to_SCMOBJ)
   ___P((___processor_state ___ps,
         long x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___ULONG_to_SCMOBJ)
   ___P((___processor_state ___ps,
         unsigned long x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___LONGLONG_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___LONGLONG x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___ULONGLONG_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___ULONGLONG x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___FLOAT_to_SCMOBJ)
   ___P((___processor_state ___ps,
         float x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___DOUBLE_to_SCMOBJ)
   ___P((___processor_state ___ps,
         double x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___STRUCT_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ tags,
         ___SCMOBJ (*release_fn) ___P((void *ptr),()),
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UNION_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ tags,
         ___SCMOBJ (*release_fn) ___P((void *ptr),()),
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___TYPE_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ tags,
         ___SCMOBJ (*release_fn) ___P((void *ptr),()),
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___POINTER_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ tags,
         ___SCMOBJ (*release_fn) ___P((void *ptr),()),
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLPOINTER_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ tags,
         ___SCMOBJ (*release_fn) ___P((void *ptr),()),
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___FUNCTION_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLFUNCTION_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___BOOL_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___BOOL x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ *obj,
         int arg_num,
         int char_encoding),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLSTRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ *obj,
         int arg_num,
         int char_encoding),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLSTRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         void *x,
         ___SCMOBJ *obj,
         int arg_num,
         int char_encoding),
        ());
___IMP_FUNC(___SCMOBJ,___CHARSTRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         char *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLCHARSTRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         char *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLCHARSTRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         char **x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___ISO_8859_1STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___ISO_8859_1STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLISO_8859_1STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___ISO_8859_1STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLISO_8859_1STRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___ISO_8859_1STRING *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UTF_8STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UTF_8STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUTF_8STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UTF_8STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUTF_8STRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UTF_8STRING *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UTF_16STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UTF_16STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUTF_16STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UTF_16STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUTF_16STRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UTF_16STRING *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UCS_2STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_2STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUCS_2STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_2STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUCS_2STRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_2STRING *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___UCS_4STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_4STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUCS_4STRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_4STRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLUCS_4STRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___UCS_4STRING *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___WCHARSTRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___WCHARSTRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLWCHARSTRING_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___WCHARSTRING x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLWCHARSTRINGLIST_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___WCHARSTRING *x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___VARIANT_to_SCMOBJ)
   ___P((___processor_state ___ps,
         ___VARIANT x,
         ___SCMOBJ *obj,
         int arg_num),
        ());
___IMP_FUNC(___SCMOBJ,___CHARSTRING_to_UCS_2STRING)
   ___P((char *str_char,
         ___UCS_2STRING *str_UCS_2),
        ());
___IMP_FUNC(void,___free_UCS_2STRING)
   ___P((___UCS_2STRING str_UCS_2),
        ());
___IMP_FUNC(___SCMOBJ,___NONNULLCHARSTRINGLIST_to_NONNULLUCS_2STRINGLIST)
   ___P((char **str_list_char,
         ___UCS_2STRING **str_list_UCS_2),
        ());
___IMP_FUNC(void,___free_NONNULLUCS_2STRINGLIST)
   ___P((___UCS_2STRING *str_list_UCS_2),
        ());
___IMP_FUNC(___SCMOBJ,___make_sfun_stack_marker)
   ___P((___processor_state ___ps,
         ___SCMOBJ *marker,
         ___SCMOBJ proc_or_false),
        ());
___IMP_FUNC(void,___kill_sfun_stack_marker)
   ___P((___SCMOBJ marker),
        ());
#endif

#ifndef ___INCLUDED_FROM_MEM
___IMP_FUNC(void*,___alloc_rc)
   ___P((___PSD
         ___SIZE_T bytes),
        ());
___IMP_FUNC(void,___release_rc)
   ___P((void *ptr),
        ());
___IMP_FUNC(void,___addref_rc)
   ___P((void *ptr),
        ());
___IMP_FUNC(___SCMOBJ,___data_rc)
   ___P((void *ptr),
        ());
___IMP_FUNC(void,___set_data_rc)
   ___P((void *ptr,
         ___SCMOBJ val),
        ());
___IMP_FUNC(___SCMOBJ,___alloc_scmobj)
   ___P((___processor_state ___ps,
         int subtype,
         ___SIZE_TS bytes),
        ());
___IMP_FUNC(void,___release_scmobj)
   ___P((___SCMOBJ obj),
        ());
___IMP_FUNC(___SCMOBJ,___make_pair)
   ___P((___processor_state ___ps,
         ___SCMOBJ car,
         ___SCMOBJ cdr),
        ());
___IMP_FUNC(___SCMOBJ,___make_vector)
   ___P((___processor_state ___ps,
         ___SIZE_TS length,
         ___SCMOBJ init),
        ());
___IMP_FUNC(void,___still_obj_refcount_inc)
   ___P((___SCMOBJ obj),
        ());
___IMP_FUNC(void,___still_obj_refcount_dec)
   ___P((___SCMOBJ obj),
        ());
___IMP_FUNC(___SCMOBJ,___gc_hash_table_ref)
   ___P((___SCMOBJ ht,
         ___SCMOBJ key),
        ());
___IMP_FUNC(___SCMOBJ,___gc_hash_table_set)
   ___P((___SCMOBJ ht,
         ___SCMOBJ key,
         ___SCMOBJ val),
        ());
___IMP_FUNC(___SCMOBJ,___gc_hash_table_rehash)
   ___P((___SCMOBJ ht_src,
         ___SCMOBJ ht_dst),
        ());
#endif

#ifndef ___INCLUDED_FROM_SETUP
___GSTATEDECL
___IMP_FUNC(___BOOL,___iswalpha)
   ___P((___UCS_4 x),
        ());
___IMP_FUNC(___BOOL,___iswdigit)
   ___P((___UCS_4 x),
        ());
___IMP_FUNC(___BOOL,___iswspace)
   ___P((___UCS_4 x),
        ());
___IMP_FUNC(___BOOL,___iswupper)
   ___P((___UCS_4 x),
        ());
___IMP_FUNC(___BOOL,___iswlower)
   ___P((___UCS_4 x),
        ());
___IMP_FUNC(___UCS_4,___towupper)
   ___P((___UCS_4 x),
        ());
___IMP_FUNC(___UCS_4,___towlower)
   ___P((___UCS_4 x),
        ());
___IMP_FUNC(___SCMOBJ,___string_collate)
   ___P((___SCMOBJ s1,
         ___SCMOBJ s2),
        ());
___IMP_FUNC(___SCMOBJ,___string_collate_ci)
   ___P((___SCMOBJ s1,
         ___SCMOBJ s2),
        ());
___IMP_FUNC(double,___copysign)
   ___P((double x,
         double y),
        ());
___IMP_FUNC(___BOOL,___isfinite)
   ___P((double x),
        ());
___IMP_FUNC(___BOOL,___isnan)
   ___P((double x),
        ());
___IMP_FUNC(double,___trunc)
   ___P((double x),
        ());
___IMP_FUNC(double,___round)
   ___P((double x),
        ());
#ifdef ___DEFINE_SCALBN
___IMP_FUNC(double,___scalbn)
   ___P((double x,
         int n),
        ());
#endif
#ifdef ___DEFINE_ILOGB
___IMP_FUNC(int,___ilogb)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_EXPM1
___IMP_FUNC(double,___expm1)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_LOG1P
___IMP_FUNC(double,___log1p)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_SINH
___IMP_FUNC(double,___sinh)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_COSH
___IMP_FUNC(double,___cosh)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_TANH
___IMP_FUNC(double,___tanh)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_ASINH
___IMP_FUNC(double,___asinh)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_ACOSH
___IMP_FUNC(double,___acosh)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_ATANH
___IMP_FUNC(double,___atanh)
   ___P((double x),
        ());
#endif
#ifdef ___DEFINE_ATAN2
___IMP_FUNC(double,___atan2)
   ___P((double y,
         double x),
        ());
#endif
#ifdef ___DEFINE_POW
___IMP_FUNC(double,___pow)
   ___P((double x,
         double y),
        ());
#endif
___IMP_FUNC(void,___setup_params_reset)
   ___P((struct ___setup_params_struct *setup_params),
        ());
___IMP_FUNC(___SCMOBJ,___setup)
   ___P((struct ___setup_params_struct *setup_params),
        ());
___IMP_FUNC(void,___cleanup) ___PVOID;
___IMP_FUNC(void,___cleanup_and_exit_process)
   ___P((int status),
        ());
___IMP_FUNC(___SCMOBJ,___setup_vmstate)
   ___P((___virtual_machine_state ___vms),
        ());
___IMP_FUNC(void,___cleanup_vmstate)
   ___P((___virtual_machine_state ___vms),
        ());
___IMP_FUNC(___SCMOBJ,___setup_pstate)
   ___P((___processor_state ___ps,
         ___virtual_machine_state ___vms),
        ());
___IMP_FUNC(void,___cleanup_pstate)
   ___P((___processor_state ___ps),
        ());
___IMP_FUNC(___SIZE_T,___get_min_heap) ___PVOID;
___IMP_FUNC(void,___set_min_heap)
   ___P((___SIZE_T bytes),
        ());
___IMP_FUNC(___SIZE_T,___get_max_heap) ___PVOID;
___IMP_FUNC(void,___set_max_heap)
   ___P((___SIZE_T bytes),
        ());
___IMP_FUNC(int,___get_live_percent) ___PVOID;
___IMP_FUNC(void,___set_live_percent)
   ___P((int percent),
        ());
___IMP_FUNC(int,___get_standard_level) ___PVOID;
___IMP_FUNC(void,___set_standard_level)
   ___P((int level),
        ());
___IMP_FUNC(void,___set_gambcdir)
   ___P((___UCS_2STRING gambcdir),
        ());
___IMP_FUNC(int,___set_debug_settings)
   ___P((int mask,
         int new_settings),
        ());
___IMP_FUNC(___program_startup_info_struct*,___get_program_startup_info)
   ___PVOID;
___IMP_FUNC(___SCMOBJ,___call)
   ___P((___PSD
         int nargs,
         ___SCMOBJ proc,
         ___SCMOBJ marker),
        ());
___IMP_FUNC(void,___propagate_error)
   ___P((___PSD
         ___SCMOBJ err),
        ());
#ifdef ___DEBUG_HOST_CHANGES
___IMP_FUNC(void,___register_host_entry)
   ___P((___PSD
         ___WORD start,
         char *module_name),
        ());
#endif
___IMP_FUNC(void,___raise_interrupt_pstate)
   ___P((___processor_state ___ps,
         int code),
        ());
___IMP_FUNC(void,___raise_interrupt_vmstate)
   ___P((___virtual_machine_state ___vms,
         int code),
        ());
___IMP_FUNC(void,___raise_interrupt)
   ___P((int code),
        ());
___IMP_FUNC(void,___begin_interrupt_service_pstate)
   ___P((___PSDNC),
        ());
___IMP_FUNC(___BOOL,___check_interrupt_pstate)
   ___P((___PSD
         int code),
        ());
___IMP_FUNC(void,___end_interrupt_service_pstate)
   ___P((___PSD
         int code),
        ());
___IMP_FUNC(void,___disable_interrupts_pstate)
   ___P((___PSDNC),
        ());
___IMP_FUNC(void,___enable_interrupts_pstate)
   ___P((___PSDNC),
        ());
#endif

#ifndef ___INCLUDED_FROM_OS_BASE
___IMP_FUNC(void *,___alloc_mem)
   ___P((___SIZE_T bytes),
        ());
___IMP_FUNC(void,___free_mem)
   ___P((void *ptr),
        ());
___IMP_FUNC(void *,___alloc_mem_code)
   ___P((___SIZE_T bytes),
        ());
___IMP_FUNC(void,___free_mem_code)
   ___P((void *ptr),
        ());
#endif

#ifndef ___INCLUDED_FROM_OS_THREAD
#ifdef ___USE_emulated_compare_and_swap_word
___IMP_FUNC(___WORD,___emulated_compare_and_swap_word)
   ___P((___WORD *ptr,
         ___WORD oldval,
         ___WORD newval),
        ());
#endif
#ifndef ___THREAD_LOCAL_STORAGE_CLASS
___IMP_FUNC(void *,___get_tls_ptr) ___PVOID;
___IMP_FUNC(void,___set_tls_ptr)
   ___P((void *ptr),
        ());
#endif
#endif

#ifndef ___INCLUDED_FROM_OS_TIME
___IMP_FUNC(void,___disable_heartbeat_interrupts) ___PVOID;
___IMP_FUNC(void,___enable_heartbeat_interrupts) ___PVOID;
#endif

#endif
#endif

#endif
