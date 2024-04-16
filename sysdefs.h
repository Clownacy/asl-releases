#ifndef _SYSDEFS_H
#define _SYSDEFS_H
/* sysdefs.h */
/*****************************************************************************/
/* SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only                     */
/*                                                                           */
/* AS Port                                                                   */
/*                                                                           */
/* system-specific definitions                                               */
/*                                                                           */
/* History:  2001-04-13 activated DRSEP for Win32 platform                   */
/*           2001-09-11 added MacOSX                                         */
/*           2001-10-13 added ARM/Linux                                      */
/*                                                                           */
/*****************************************************************************/

#include <inttypes.h>
#include <stdint.h>
#include "config.h"

#if defined(_WIN32) || defined(__EMX__) || defined(__MSDOS__) || defined(__IBMC__)
# define OPENRDMODE "rb"
# define OPENWRMODE "wb"
# define OPENUPMODE "rb+"
# define SLASHARGS
# define PATHSEP '\\'
# define SPATHSEP "\\"
# define DIRSEP ';'
# define SDIRSEP ";"
# define DRSEP ':'
# define SDRSEP ":"
# define NULLDEV "NUL"
#else
# define OPENRDMODE "r"
# define OPENWRMODE "w"
# define OPENUPMODE "r+"
# define PATHSEP '/'
# define SPATHSEP "/"
# define DIRSEP ':'
# define SDIRSEP ":"
# define NULLDEV "/dev/null"
#endif

#if defined(vax)
# define VAXFLOAT
#else
# define IEEEFLOAT
#endif

// Note: SunOS and derived incorrectly defines int8_t as 'char'.
typedef int8_t Integ8;
typedef uint8_t Card8;
typedef int16_t Integ16;
typedef uint16_t Card16;
typedef int32_t Integ32;
#define PRIInteg32 PRId32
typedef uint32_t Card32;
typedef int64_t Integ64;
typedef uint64_t Card64;
#define HAS16
#define HAS64

/*---------------------------------------------------------------------------*/
/* We require C11, so we surely can use prototypes */

#define UNUSED(x) (void)x

#endif /* _SYSDEFS_H */
