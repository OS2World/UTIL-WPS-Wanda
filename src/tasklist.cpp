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

#include "tasklist.h"

Tasklist *Tasklist :: ptl = NULL;

BOOL Tasklist :: Add (HWND hwnd, PSZ psz)
{
    SWCNTRL swctl; // switch control data
    PID pid;       // process id

    WinQueryWindowProcess(hwnd, &pid, NULL);

    swctl.hwnd          = hwnd;          // window handle
    swctl.hwndIcon      = NULLHANDLE;    // icon handle
    swctl.hprog         = NULLHANDLE;    // program handle
    swctl.idProcess     = pid;           // process identifier
    swctl.idSession     = 0;             // session identifier
    swctl.uchVisibility = SWL_VISIBLE;   // visibility
    swctl.fbJump        = SWL_JUMPABLE;  // jump indicator
    swctl.bProgType     = PROG_DEFAULT;  // program type

    if (! psz)
        WinQueryWindowText(hwnd, MAXNAMEL, swctl.szSwtitle);
    else
        strncpy(swctl.szSwtitle, psz, MAXNAMEL);

    WinAddSwitchEntry(&swctl);
    return TRUE;
}

BOOL Tasklist :: Remove (HWND hwnd)
{
    HSWITCH  hswitch = WinQuerySwitchHandle(hwnd, 0);
    WinRemoveSwitchEntry(hswitch);
    return TRUE;
}

BOOL Tasklist :: Change (HWND hwnd, PSZ psz)
{
    HSWITCH hswitch = WinQuerySwitchHandle(hwnd, 0);
    SWCNTRL swctl;

    swctl.hwnd          = hwnd;
    swctl.hwndIcon      = NULLHANDLE;
    swctl.hprog         = NULLHANDLE;
    swctl.idProcess     = 0;
    swctl.idSession     = 0;
    swctl.uchVisibility = SWL_VISIBLE;
    swctl.fbJump        = SWL_JUMPABLE;
    swctl.bProgType     = PROG_DEFAULT;

    if (! psz)
        WinQueryWindowText(hwnd, MAXNAMEL, swctl.szSwtitle);
    else
        strncpy(swctl.szSwtitle, psz, MAXNAMEL);

    WinChangeSwitchEntry (hswitch, &swctl);
    return TRUE;
}
