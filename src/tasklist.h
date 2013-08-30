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

#ifndef _TASKLIST_H_
#define _TASKLIST_H_

#define INCL_WINSWITCHLIST
#define INCL_WINPROGRAMLIST

#define OS2EMX_PLAIN_CHAR

#include <os2.h>
#include <strings.h>

class Tasklist
{
public:
    BOOL Add (HWND hwnd, PSZ psz = NULL);
    BOOL Remove (HWND hwnd);

    BOOL Change (HWND hwnd, PSZ psz = NULL);

    static Tasklist *Instance (VOID) {
        if (! ptl) { ptl = new Tasklist; }
        return ptl;
    }

private:
    static Tasklist *ptl;
};

#endif
