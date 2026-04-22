/* Pre-include header for system and Asterisk headers - must be first */
#ifndef PREINCLUDE_H
#define PREINCLUDE_H

/* Fix for newer glibc/GCC combinations - defines only, no includes */
#ifndef __BEGIN_DECLS
#define __BEGIN_DECLS
#endif

#ifndef __END_DECLS
#define __END_DECLS
#endif

#ifndef __THROW
#define __THROW
#endif

#ifndef __THROWNL
#define __THROWNL
#endif

#ifndef __GNUC_PREREQ
#define __GNUC_PREREQ(maj, min) 1
#endif

#ifndef __GLIBC_PREREQ
#define __GLIBC_PREREQ(maj, min) 1
#endif

#ifndef __GLIBC_USE
#define __GLIBC_USE(x) 1
#endif

#ifndef __nonnull
#define __nonnull(params)
#endif

#ifndef __wur
#define __wur
#endif

#ifndef __COLD
#define __COLD
#endif

#ifndef __glibc_clang_prereq
#define __glibc_clang_prereq(maj, min) 0
#endif

#ifndef __glibc_has_attribute
#define __glibc_has_attribute(x) 0
#endif

#ifndef __glibc_has_builtin
#define __glibc_has_builtin(x) 0
#endif

#ifndef __fortified_attr_access
#define __fortified_attr_access(x,y,z)
#endif

#ifndef __attr_access
#define __attr_access(x)
#endif

#ifndef __attribute_access__
#define __attribute_access__(x)
#endif

#ifndef __glibc_fortify
#define __glibc_fortify(f, __l, __c, __a, ...)
#endif

#ifndef __glibc_fortify_n
#define __glibc_fortify_n(f, __l, __c, __n, ...)
#endif

#ifndef __MATHCALL
#define __MATHCALL(function, suffix, args)
#endif

#ifndef __MATHDECL_1
#define __MATHDECL_1(type, function, suffix, args)
#endif

#ifndef __CONCAT
#define __CONCAT(x,y) x ## y
#endif

#ifndef _Mdouble_
#define _Mdouble_ double
#endif

#ifndef __attribute_malloc__
#define __attribute_malloc__
#endif

#ifndef __attribute_alloc_size__
#define __attribute_alloc_size__(x)
#endif

#ifndef __attribute_warn_unused_result__
#define __attribute_warn_unused_result__
#endif

#ifndef __attribute_pure__
#define __attribute_pure__
#endif

#ifndef __attribute_const__
#define __attribute_const__
#endif

#ifndef __attribute_deprecated__
#define __attribute_deprecated__
#endif

#ifndef __attribute_noinline__
#define __attribute_noinline__
#endif

/* Asterisk compiler.h compatibility */
#ifndef force_inline
#define force_inline inline
#endif

#ifndef attribute_pure
#define attribute_pure
#endif

#ifndef attribute_const
#define attribute_const
#endif

#ifndef attribute_unused
#define attribute_unused
#endif

#ifndef attribute_malloc
#define attribute_malloc
#endif

#ifndef attribute_format
#define attribute_format(x,y,z)
#endif

#ifndef attribute_noreturn
#define attribute_noreturn
#endif

#ifndef attribute_packed
#define attribute_packed
#endif

#ifndef attribute_aligned
#define attribute_aligned(x)
#endif

#ifndef attribute_warn_unused_result
#define attribute_warn_unused_result
#endif

#ifndef attribute_weak
#define attribute_weak
#endif

#ifndef attribute_used
#define attribute_used
#endif

#ifndef attribute_deprecated
#define attribute_deprecated
#endif

/* Essential system headers */
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>

/* Asterisk main header - must be before other Asterisk headers */
#include <asterisk.h>

#endif
