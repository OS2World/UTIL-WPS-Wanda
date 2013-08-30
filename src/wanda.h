/***
 This file belongs to the Wanda distribution.
 Copyright (C) 1998-2001 Thorsten Thielen <thth@gmx.net>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***/

#ifndef _WANDA_H_
#define _WANDA_H_

#define _PARANOID_

#define __MT__

#include <io.h>

// this should be provided I thought, but isn't
#define R_OK  4
#define W_OK  2

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

//#include <cpp/std/bastring.h>
//#include <algo.h>
//#include <list.h>
//#include <map.h>
//#include <vector.h>
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>

#include <fcntl.h>
#include <errno.h>

#define OS2EMX_PLAIN_CHAR
#define INCL_PM
#define INCL_DOS
#define INCL_DOSERRORS

#include <os2.h>

#include "config.h"
#include "log.h"

#include "id.h"
#include "version.h"

// ** some new types ****************************************************** /*FOLD00*/

typedef USHORT NID;
typedef CHAR STRING;

// ** some defines ******************************************************** /*FOLD00*/

#define CB_FONTNAMESIZE      31
#define PSZ_RCPIPENAME       "\\PIPE\\Wanda"
#define C_AUTOSAVESECS       pset->QueryLong(SEI_AUTOSAVEDELAY)
#define NID_NIL              65535
#define GETHAB               hab
#define GETMODULE            NULLHANDLE
#define PSZ_NOTESFILE        pset->QueryString(SEI_NOTESFILE)

#define WRITE_NDID(id,pf)    putc(id,pf)

enum { PS_TOFILE, PS_TODEVICE };
enum { PDEV_PRN, PDEV_LPT1, PDEV_LPT2, PDEV_LPT3, PDEV_NUL };
//PDEV_COM1, PDEV_COM2, PDEV_COM3, PDEV_COM4,

// ** some external vars ************************************************** /*FOLD00*/

extern HAB              hab;
extern class Settings  *pset;

// ** some function prototypes ******************************************** /*FOLD00*/

VOID DisplayError (PSZ pszTitle, PSZ psz, ...);
VOID SetConditionalCascade (HWND hwnd, USHORT id, USHORT us);
VOID AboutBox (HWND hwnd);

#include "settings.h"

#endif
