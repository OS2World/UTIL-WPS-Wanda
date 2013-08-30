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

#include "finder.h"

// ** Dialog ************************************************************** /*FOLD00*/

BOOL FINDER :: Dialog (VOID)
{
    hwndDlg =
        WinLoadDlg (HWND_DESKTOP, HWND_DESKTOP, dp, GETMODULE, ID_DLG_FIND,
                    this);
    ULONG ul = WinProcessDlg (hwndDlg);
    WinDestroyWindow (hwndDlg);
    hwndDlg = NULLHANDLE;

    return (BOOL (ul));
}

// ** dp ****************************************************************** /*FOLD00*/

MRESULT EXPENTRY FINDER :: dp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static PFINDER pfnd = NULL;
    static BOOL    f = FALSE;

    switch (msg)
    {
    case WM_INITDLG:
        pfnd = PFINDER (mp2);

        WinSendDlgItemMsg (hwnd, WID_CB_FINDREPLACE, BM_SETCHECK,
                           MPFROMLONG (pset->QueryFlag (SEI_FINDREPLACE)),
                           MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_FINDCASESENS, BM_SETCHECK,
                           MPFROMLONG (pset->QueryFlag (SEI_FINDCASESENS)),
                           MPFROMLONG (0));

        // init search text entry field
        WinSendDlgItemMsg (hwnd, WID_E_FINDTEXT, EM_SETTEXTLIMIT,
                           (MPARAM)CMAX_FINDTEXT, (MPARAM)0);
        WinSetDlgItemText (hwnd, WID_E_FINDTEXT,
                           pset->QueryString (SEI_FINDTEXT));
        WinSendDlgItemMsg (hwnd, WID_E_FINDTEXT, EM_SETSEL,
                           MPFROM2SHORT (0, CMAX_FINDTEXT), (MPARAM)0);

        // init replace text entry field
        WinSendDlgItemMsg (hwnd, WID_E_FINDREPLACETEXT, EM_SETTEXTLIMIT,
                           (MPARAM)CMAX_FINDREPLACETEXT, (MPARAM)0);
        WinSetDlgItemText (hwnd, WID_E_FINDREPLACETEXT,
                           pset->QueryString (SEI_FINDREPLACETEXT));
        WinSendDlgItemMsg (hwnd, WID_E_FINDREPLACETEXT, EM_SETSEL,
                           MPFROM2SHORT (0, CMAX_FINDREPLACETEXT), (MPARAM)0);

        return MRESULT (FALSE);

    case WM_COMMAND:
        WinSendMsg (hwnd, UM_ADJUST, 0,0); // FIXME again
        switch (COMMANDMSG (&msg)->cmd)
        {
        case WID_PB_DOFIRST:
            if (pfnd->pnl->Find (TRUE))
                pfnd->EnableDoNext ();
            else
                pfnd->DisableDoNext ();
            break;

        case WID_PB_DONEXT:
            if (pfnd->pnl->Find (FALSE))
                pfnd->EnableDoNext ();
            else
                pfnd->DisableDoNext ();
            break;

        case DID_CANCEL:
            f = FALSE;
            WinSendMsg (hwnd, WM_CLOSE, 0,0);
            break;
        }
        return MRESULT (FALSE);

    case WM_CLOSE:
        WinSendMsg (hwnd, UM_ADJUST, 0,0);
        WinDismissDlg (hwnd, ULONG (f));
        return MRESULT (FALSE);

    case UM_ADJUST:
        {
            // adjust the settings
            pset->SetFlag (SEI_FINDREPLACE, BOOL (
                           WinSendDlgItemMsg (hwnd, WID_CB_FINDREPLACE,
                                              BM_QUERYCHECK, 0,0)));
            pset->SetFlag (SEI_FINDCASESENS, BOOL (
                           WinSendDlgItemMsg (hwnd, WID_CB_FINDCASESENS,
                                              BM_QUERYCHECK, 0,0)));

            // search text
            CHAR ach[CMAX_FINDTEXT+1];
            WinQueryDlgItemText (hwnd, WID_E_FINDTEXT, CMAX_FINDTEXT, ach);
            pset->SetString (SEI_FINDTEXT, ach);

            // replace text
            WinQueryDlgItemText (hwnd, WID_E_FINDREPLACETEXT, CMAX_FINDREPLACETEXT, ach);
            pset->SetString (SEI_FINDREPLACETEXT, ach);
        }
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ************************************************************************
