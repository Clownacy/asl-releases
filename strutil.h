#ifndef _STRUTIL_H
#define _STRUTIL_H
/* strutil.h */
/*****************************************************************************/
/* SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only                     */
/*                                                                           */
/* AS-Portierung                                                             */
/*                                                                           */
/* haeufig benoetigte String-Funktionen                                      */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

#include "datatypes.h"

extern char HexStartCharacter;

extern const char *Blanks(int cnt);

#define HexString(pDest, DestSize, i, Stellen) SysString(pDest, DestSize, i, 16, Stellen, False, HexStartCharacter)

extern int SysString(char *pDest, size_t DestSize, LargeWord i, int System, int Stellen, Boolean ForceLeadZero, char StartCharacter);

extern char *as_strdup(const char *s);

extern int as_vsnprcatf(char *pDest, size_t DestSize, const char *pFormat, va_list ap);
extern int as_snprcatf(char *pDest, size_t DestSize, const char *pFormat, ...);
extern int as_vsnprintf(char *pDest, size_t DestSize, const char *pFormat, va_list ap);
extern int as_snprintf(char *pDest, size_t DestSize, const char *pFormat, ...);

extern int as_strcasecmp(const char *src1, const char *src2);
extern int as_strncasecmp(const char *src1, const char *src2, size_t maxlen);

#ifdef NEEDS_STRSTR
extern char *strstr(const char *haystack, const char *needle);
#endif

extern char *strrmultchr(const char *haystack, const char *needles);

extern size_t strmaxcpy(char *dest, const char *src, size_t Max);
extern size_t strmaxcat(char *Dest, const char *Src, size_t MaxLen);
extern void strprep(char *Dest, const char *Src);
extern void strmaxprep(char *Dest, const char *Src, size_t MaxLen);
extern void strins(char *Dest, const char *Src, int Pos);
extern void strmaxins(char *Dest, const char *Src, int Pos, size_t MaxLen); 

extern size_t as_strnlen(const char *pStr, size_t MaxLen);

extern int strreplace(char *pHaystack, const char *pFrom, const char *pTo, size_t ToMaxLen, size_t HaystackSize);

extern int strlencmp(const char *pStr1, unsigned Str1Len,
                     const char *pStr2, unsigned Str2Len);

extern unsigned fstrlenprint(FILE *pFile, const char *pStr, unsigned StrLen);

extern unsigned snstrlenprint(char *pDest, size_t DestLen,
                              const char *pStr, size_t StrLen,
                              char QuoteToEscape);

extern void ReadLn(FILE *Datei, char *Zeile);

extern int ReadLnCont(FILE *Datei, char *Zeile, int MaxLen);

extern int DigitVal(char ch, int Base);

extern LargeInt ConstLongInt(const char *inp, Boolean *pErr, LongInt Base);

extern char *ParenthPos(char *pHaystack, char Needle);

extern void KillBlanks(char *s);

extern int CopyNoBlanks(char *pDest, const char *pSrc, size_t MaxLen);

extern int KillPrefBlanks(char *s);

extern int KillPostBlanks(char *s);

extern char TabCompressed(char in);

extern int strqcmp(const char *s1, const char *s2);
  
extern char *strmov(char *pDest, const char *pSrc);

extern int strmemcpy(char *pDest, size_t DestSize, const char *pSrc, size_t SrcLen);
  
extern void strutil_init(void);

/* avoid nasty "subscript has type char..." messages on some platforms */

#define __chartouint(c) (((unsigned int)(c)) & 0xff)
#define as_toupper(c) (toupper(__chartouint(c)))
#define as_tolower(c) (tolower(__chartouint(c)))
#define as_isspace(c) (!!isspace(__chartouint(c)))
#define as_isdigit(c) (!!isdigit(__chartouint(c)))
#define as_isxdigit(c) (!!isxdigit(__chartouint(c)))
#define as_isprint(c) (!!isprint(__chartouint(c)))
#define as_isalpha(c) (!!isalpha(__chartouint(c)))

#endif /* _STRUTIL_H */
