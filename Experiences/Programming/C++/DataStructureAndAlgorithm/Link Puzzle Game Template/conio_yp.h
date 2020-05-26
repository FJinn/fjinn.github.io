// conio_yp.h
//
// NOTE by Ya-Ping Wong <ypwong@mmu.edu.my>
//
// ver 031102 02-Nov-2003
// - This file is modified from the conio.h file as 
//       found in the include directory of Dev-Cpp 4.9.8.4
// - The modification made by YPWong is marked from BEGIN_YPWONG to END_YPWONG
// - the modification is needed so that to use the conio.c, you just need
//       to #include "conio.h" (in all the files that required functions
//       from conio.c) and add conio.c into your project. If the modification
//       is not done, then we need to #include "conio.c" and if several
//       files require you to #include "conio.c", then you will faced the
//       problem of "multiple declaration".

/*
 * conio.h
 *
 * Low level console I/O functions. Pretty please try to use the ANSI
 * standard ones if you are writing new code.
 *
 * This file is part of the Mingw32 package.
 *
 * Contributors:
 *  Created by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 *
 *  THIS SOFTWARE IS NOT COPYRIGHTED
 *
 *  This source code is offered for use in the public domain. You may
 *  use, modify or distribute it freely.
 *
 *  This code is distributed in the hope that it will be useful but
 *  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAIMED. This includes but is not limited to warranties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Revision: 1.3 $
 * $Author: dannysmith $
 * $Date: 2001/11/29 04:26:33 $
 *
 */

#ifndef	__STRICT_ANSI__

#ifndef	_CONIO_H_
#define	_CONIO_H_

/* All the headers include this file. */
#include <_mingw.h>

#ifndef RC_INVOKED

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;

void hideCursor ();

char*	_cgets (char*);
int	_cprintf (const char*, ...);
int	_cputs (const char*);
int	_cscanf (char*, ...);

int	_getch (void);
int	_getche (void);
int	_kbhit (void);
int	_putch (int);
int	_ungetch (int);


#ifndef	_NO_OLDNAMES

int	getch (void);
int	getche (void);
int	kbhit (void);
int	putch (int);
int	ungetch (int);

#endif	/* Not _NO_OLDNAMES */

//BEGIN_YPWONG added by YPWong
// These are prototypes of functions found in conio.c
void gotoxy(int x, int y);
void clrscr ();
void clreol ();
void delline();
int _conio_gettext (int left, int top, int right, int bottom,
  char *str);
void puttext (int left, int top, int right, int bottom, char *str);
void _setcursortype (int type);
void textattr (int _attr);
void textbackground (int color);
void textcolor (int color);
int wherex ();
int wherey ();
//END_YPWONG added by YPWong

#ifdef	__cplusplus
}
#endif

#endif	/* Not RC_INVOKED */

#endif	/* Not _CONIO_H_ */

#endif	/* Not __STRICT_ANSI__ */
