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

#ifndef _NLDISP_1_H_
#define _NLDISP_1_H_

#include "wanda.h"

struct NotelistDisplayData_1
{
    NotelistDisplayData_1 (VOID) {
        swp.x = swp.y = x = y = 0;
        swp.cx = swp.cy = cx = cy = 150;
        swp.hwnd = HWND_DESKTOP;
        swp.fl = SWP_SHOW|SWP_MOVE|SWP_SIZE;

        color = 0x00ffffff;
        colorFG = 0x00000000;

        strcpy(ach, "8.Helv");

        fMinimized = FALSE;
    }

    SWP    swp;
    USHORT x, y, cx, cy;

    COLOR  color, colorFG;
    CHAR   ach[CB_FONTNAMESIZE];

    BOOL   fMinimized;
};

#include "nldisp.h"

// ** classdef ************************************************************ /*FOLD00*/

class NotelistDisplay_1 : public NotelistDisplay
{
public:
    NotelistDisplay_1 (Notelist &nl, NotelistDisplayData_1 *pnldd);

    virtual ~NotelistDisplay_1 (VOID) {
        WinDestroyWindow(hwndFrame);
    }

    BOOL toggle_titlebar( VOID );

protected:
    BOOL Add (Note &n);
    BOOL Remove (NID nid);

    BOOL Mark (NID nid);
    BOOL Unmark (NID nid);

    LONG Index (NID nid) {
        LONG c = WinQueryLboxCount(hwndLB);
        for (LONG i = 0; i < c/* Why +1??*/; i++)
            if (((Note  *)(WinSendMsg(hwndLB, LM_QUERYITEMHANDLE,
                                      MPFROMSHORT (i),
                                      0L)))->ID() == nid)
                return i;
        return -1;
    }

    Note *QuerySelected (VOID);
    BOOL  IsSelected (LONG i = LIT_CURSOR);

    VOID Empty (VOID);

    BOOL Title (NID nid, PSZ psz) {
        LONG l = Index(nid);
        if (l >= 0)
        {
            WinSendMsg(hwndLB, LM_SETITEMTEXT, MPFROMLONG (l), MPFROMP (psz));
            return TRUE;
        }
        return FALSE;
    }

    VOID Command (USHORT id);

    VOID Close (VOID);
    VOID Save (VOID);

    NotelistDisplayData_1 *Template (VOID);

private:
    static MRESULT EXPENTRY wp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    const PSZ PSZ_WCNAME = "wanda.wc.notelistdisplay_1";

    HWND hwndLB, hwndFrame, hwndClient, hwndMenu;

    static BOOL fClassRegistered;
};

#endif
