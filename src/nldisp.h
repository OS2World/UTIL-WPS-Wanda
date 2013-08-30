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

#ifndef _NLDISP_H_
#define _NLDISP_H_

#include "wanda.h"
#include "notedisp.h"

class NotelistDisplay
{
    friend class Notelist;

protected:
    NotelistDisplay (class Notelist &nl) { pnl = &nl; }

    virtual BOOL Add (Note &n) = 0;
    virtual BOOL Remove (NID nid) = 0;

    virtual BOOL Mark (NID nid) = 0;
    virtual BOOL Unmark (NID nid) = 0;

    virtual VOID Empty (VOID) = 0;
    virtual BOOL Title (NID nid, PSZ psz) = 0;

    virtual VOID Save (VOID) = 0;

    class Notelist *pnl;

#ifdef DONLDREMOVETITLE
public:
    virtual BOOL   toggle_titlebar( VOID ) = 0;
protected:
    BOOL   fTitlebar;
    HWND   hwndSysMenu;
    HWND   hwndTitlebar;
    HWND   hwndMinMax;
#endif
};

#include "notelist.h"

#endif
