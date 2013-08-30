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

#include "printer.h"

// ** Dialog ************************************************************** /*fold00*/

BOOL Printer :: Dialog (VOID)
{
    hwndDlg =
        WinLoadDlg (HWND_DESKTOP, HWND_DESKTOP, dp, GETMODULE, ID_DLG_PRINT,
                    this);

    // set print style
    // We have to do this here, otherwise this gets reset!
    switch (pset->QueryLong (SEI_PRINTSTYLE))
    {
    case PS_TODEVICE:
        WinSendDlgItemMsg (hwndDlg, WID_RB_PRINTTODEVICE, BM_CLICK,
                           MPFROMSHORT(TRUE), 0);
        break;
    default:
        WinSendDlgItemMsg (hwndDlg, WID_RB_PRINTTOFILE, BM_CLICK,
                           MPFROMSHORT(TRUE), 0);
        break;
    }

    ULONG ul = WinProcessDlg (hwndDlg);
    WinDestroyWindow (hwndDlg);
    hwndDlg = NULLHANDLE;

    return (BOOL (ul));
}

// ** dp ****************************************************************** /*fold00*/

MRESULT EXPENTRY Printer :: dp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static Printer *pprn = NULL;
    static BOOL     f = FALSE;

    switch (msg)
    {
    case WM_INITDLG:
        pprn = (Printer *) mp2;

        WinSendDlgItemMsg (hwnd, WID_CB_PRINTHEADLINE, BM_SETCHECK,
                           MPFROMLONG (pset->QueryFlag (SEI_PRINTHEADLINE)),
                           MPFROMLONG (0));

        // init filename entry field
        WinSendDlgItemMsg (hwnd, WID_E_PRINTFILENAME, EM_SETTEXTLIMIT,
                           (MPARAM)_MAX_PATH, (MPARAM)0);
        WinSetDlgItemText (hwnd, WID_E_PRINTFILENAME,
                           pset->QueryString (SEI_PRINTFILENAME));
        WinSendDlgItemMsg (hwnd, WID_E_PRINTFILENAME, EM_SETSEL,
                           MPFROM2SHORT (0, _MAX_PATH), (MPARAM)0);

       // init device ddl
       WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES, LM_INSERTITEM,
                          MPFROMLONG (PDEV_PRN),
                          PSZ ("PRN (The default printer, usually LPT1)"));
       WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES, LM_INSERTITEM,
                          MPFROMLONG (PDEV_LPT1),
                          PSZ ("LPT1 (First parallel port)"));
       WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES, LM_INSERTITEM,
                          MPFROMLONG (PDEV_LPT2),
                          PSZ ("LPT2 (Second parallel port)"));
       WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES, LM_INSERTITEM,
                          MPFROMLONG (PDEV_LPT3),
                          PSZ ("LPT3 (Third parallel port)"));
       WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES, LM_INSERTITEM,
                          MPFROMLONG (PDEV_NUL),
                          PSZ ("NUL (The bit bucket)"));

       WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES, LM_SELECTITEM,
                          MPFROMLONG (pset->QueryLong (SEI_PRINTDEVICE)),
                          MPFROMLONG (TRUE));
       WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES, CBM_SHOWLIST,
                          FALSE, 0);

       return MRESULT (FALSE);

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case WID_PB_FINDPRINTFILE:
            if (pprn->SelectFile ())
                WinSetDlgItemText (hwnd, WID_E_PRINTFILENAME,
                                   pprn->QueryFilename ());
            break;

        case WID_PB_OUTPUT:
            f = TRUE;
            WinSendMsg (hwnd, WM_CLOSE, 0,0);
            break;

        case DID_CANCEL:
            f = FALSE;
            WinSendMsg (hwnd, WM_CLOSE, 0,0);
            break;
        }
        return MRESULT (FALSE);

    case WM_CLOSE:
        {
            // adjust the settings
            pset->SetFlag (SEI_PRINTHEADLINE, BOOL (
                           WinSendDlgItemMsg (hwnd, WID_CB_PRINTHEADLINE,
                                              BM_QUERYCHECK, 0,0)));
            // print file name
            CHAR ach[_MAX_PATH];
            WinQueryDlgItemText (hwnd, WID_E_PRINTFILENAME, _MAX_PATH, ach);
            pset->SetString (SEI_PRINTFILENAME, ach);

            // get print style
            if (WinSendMsg (WinWindowFromID (hwnd, WID_RB_PRINTTOFILE),
                            BM_QUERYCHECK, 0,0))
                pset->SetLong (SEI_PRINTSTYLE, PS_TOFILE);
            else
                pset->SetLong (SEI_PRINTSTYLE, PS_TODEVICE);

            // get device
            pset->SetLong (SEI_PRINTDEVICE,
                           LONG (WinSendDlgItemMsg (hwnd, WID_DDL_DEVICES,
                                                    LM_QUERYSELECTION,
                                                    MPFROMLONG (LIT_FIRST),
                                                    MPARAM (NULL))));
            WinDismissDlg (hwnd, ULONG (f));
        }
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** SelectFile ********************************************************** /*fold00*/

BOOL Printer :: SelectFile (VOID)
{
    FILEDLG    fdlg;

    memset (&fdlg, 0, sizeof (fdlg));

    fdlg.cbSize   = sizeof (fdlg);
    fdlg.fl       = FDS_SAVEAS_DIALOG | FDS_CENTER | FDS_ENABLEFILELB;
    fdlg.pszTitle = "Select output file";

    strcpy (fdlg.szFullFile, QueryFilename ());

    if (WinFileDlg (HWND_DESKTOP, hwndDlg, &fdlg))
    {
        if (fdlg.lReturn != DID_OK)
            return FALSE;

        pset->SetString (SEI_PRINTFILENAME, fdlg.szFullFile);
        return TRUE;
    }

    return FALSE;
}

// ** OpenOutput ********************************************************** /*FOLD00*/

FILE *Printer :: OpenOutput (VOID)
{
    PSZ   psz;
    FILE  *pf;

    if (PrintToDevice ())
    {
        psz = QueryDevicename ();
        if (stricmp (psz, "NUL") == 0)
        {
            DisplayError ("DEVICE ERROR", "Device \"%s\" is full! ;-)", psz);
            return NULL;
        }
    }
    else
        psz = QueryFilename ();

    if (! (pf = fopen (psz, "wb")))
    {
        DisplayError ("FILE ERROR", "Could not open file/device \"%s\" "
                      "(errno=%ld).", psz, *_errno ());
        return NULL;
    }

    return pf;
}

// ** OutputNote ********************************************************** /*FOLD00*/

BOOL Printer :: OutputNote (FILE *pf, Note *pn)
{
    if (pset->FlagSet (SEI_PRINTHEADLINE))
        fprintf (pf, "--- Note #%ld ---\r\n", LONG (pn->ID ()));

    PSZ   psz = pn->Text();
    fputs (psz, pf);
    fputs ("\r\n\r\n", pf);

    return TRUE;
}

// ************************************************************************
