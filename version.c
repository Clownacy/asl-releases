/* version.c */
/*****************************************************************************/
/* AS-Portierung                                                             */
/*                                                                           */
/* Lagert die Versionsnummer                                                 */
/*                                                                           */
/* Historie: 14.10.1997 Grundsteinlegung                                     */
/*           25. 7.1998 Version 1.41r8beta                                   */
/*           18.10.1998 Build 4                                              */
/*           25.10.1998 Build 5                                              */
/*           10. 1.1999 Build 6                                              */
/*           17. 1.1999 Build 7                                              */
/*           27. 1.1999 Build 8                                              */
/*           27. 1.1999 Build 9                                              */
/*            7. 2.1999 Build 10                                             */
/*           19. 4.1999 Build 11                                             */
/*           20. 4.1999 Build 12                                             */
/*            2. 5.1999 Build 13                                             */
/*            6. 7.1999 Build 14                                             */
/*           15. 9.1999 Build 15                                             */
/*            7.11.1999 Final Build                                          */
/*            9. 1.2000 Version 1.42beta                                     */
/*           13. 2.2000 Build 2                                              */
/*           13. 3.2000 Build 3                                              */
/*            4. 6.2000 Build 5                                              */
/*           18. 6.2000 Build 6                                              */
/*            6. 8.2000 Build 7                                              */
/*           20. 9.2000 Build 8                                              */
/*           15.10.2000 Build 9                                              */
/*            7. 1.2001 Build 10                                             */
/*           14. 1.2001 Build 11                                             */
/*            4. 2.2001 Build 12                                             */
/*           30. 5.2001 Build 13                                             */
/*            1. 7.2001 Build 14                                             */
/*           20. 8.2001 Build 15                                             */
/*            7.10.2001 Build 16                                             */
/*           2001-11-04 Build 17                                             */
/*           2002-01-13 Build 18                                             */
/*           2002-01-27 Build 19                                             */
/*                                                                           */
/*****************************************************************************/
/* $Id: version.c,v 1.8 2005/03/21 19:28:11 alfred Exp $                     */
/***************************************************************************** 
 * $Log: version.c,v $
 * Revision 1.8  2005/03/21 19:28:11  alfred
 * - Bld35
 *
 * Revision 1.7  2004/11/20 17:36:26  alfred
 * - Bld34
 *
 * Revision 1.6  2004/09/26 10:08:35  alfred
 * - Bld33
 *
 * Revision 1.5  2004/05/29 14:39:35  alfred
 * - Bld32 changelog
 *
 * Revision 1.4  2004/03/31 18:25:20  alfred
 * - Bld31
 *
 * Revision 1.3  2003/12/07 13:59:50  alfred
 * - fixed DebVersion
 *
 * Revision 1.2  2003/12/07 13:51:51  alfred
 * - 1.42 Bld 30
 *
 * Revision 1.1  2003/11/06 02:40:28  alfred
 * - recreated
 *
 * Revision 1.12  2003/08/17 14:06:59  alfred
 * - build 29
 *
 * Revision 1.11  2003/06/08 20:17:43  alfred
 * - stuff for Debian archive
 *
 * Revision 1.10  2003/05/25 13:01:12  alfred
 * - Build 28
 *
 * Revision 1.9  2003/03/29 20:00:54  alfred
 * - Build 27
 *
 * Revision 1.8  2003/02/26 19:27:50  alfred
 * - Build 26
 *
 * Revision 1.7  2003/02/02 13:32:24  alfred
 * - Build 25
 *
 * Revision 1.6  2002/11/23 14:48:02  alfred
 * . Build 24
 *
 * Revision 1.5  2002/10/11 08:34:54  alfred
 * - 1.42 Bld 23
 *
 * Revision 1.4  2002/10/09 17:55:07  alfred
 * - 1.42 Bld 22
 *
 * Revision 1.3  2002/05/25 20:39:23  alfred
 * - 1.42 Bld 21
 *
 * Revision 1.2  2002/03/10 10:50:48  alfred
 * - build 20
 *
 *****************************************************************************/

#include "stdinc.h"
#include <string.h>

char *Version="1.42 Beta [Bld 35]";
char *DebVersion = "1.42bld35-1";
LongInt VerNo=0x142f;

char *InfoMessCopyright="(C) 1992,2005 Alfred Arnold";

LongInt Magic=0x12372944;

void version_init(void)
{
  unsigned int z;
  char *CMess = InfoMessCopyright;
  LongWord XORVal;

  for (z = 0; z < strlen(CMess); z++)
  {
    XORVal = CMess[z];
    XORVal = XORVal << (((z + 1) % 4) * 8);
    Magic = Magic ^ XORVal;
  }
}