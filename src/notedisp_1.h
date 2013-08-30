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

#ifndef _NOTEDISP_1_H_
#define _NOTEDISP_1_H_

#include "wanda.h"
#include "tasklist.h"
#include "notelist.h"
#include "notedisp.h"
#include "nd_temp_1.h"
#include "note.h"

// ** classdef ************************************************************

class NoteDisplay_1 : public NoteDisplay
{
public:
    VOID Changed (BOOL f);

    NoteDisplay_1 (Note &n, NoteDisplayTemplate_1 *pndt);

    VOID Text (STRING *pstr);
    STRING *Text (VOID);

    VOID Save (FILE *pf);

    BOOL MakeCurrent (VOID) {
        WinSetWindowPos (hwndFrame, NULLHANDLE, 0,0, 0,0,
                         SWP_SHOW | SWP_ACTIVATE | SWP_RESTORE);
        // set title and tasklist entry (if window has one)
        Title(pn->Headline());
        return TRUE;
    }

    NoteDisplayTemplate_1 *Template (VOID); // FIXME put into base class

private:
    BOOL fTitlebar;

public:
    VOID Titlebar (BOOL f);
    BOOL Titlebar (VOID) { return fTitlebar; }

protected:
    virtual ~NoteDisplay_1 (VOID);

    VOID   Drag (VOID);

    static MRESULT EXPENTRY
        wpNewMLE (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    PFNWP  wpOldMLE;

    VOID Command (USHORT id);

    VOID Hide (BOOL f) {
        if (f)
            WinSetWindowPos(hwndFrame, NULLHANDLE, 0,0, 0,0,
                            SWP_SHOW | SWP_MINIMIZE);
        else
            WinSetWindowPos(hwndFrame, NULLHANDLE, 0,0, 0,0,
                            SWP_SHOW | SWP_RESTORE);
        Changed(TRUE);
    }

    BOOL Hide (VOID) {
        SWP swp;
        WinQueryWindowPos(hwndFrame, &swp);
        return (swp.fl & SWP_MINIMIZE);
    }

    VOID Close (VOID) {
#ifdef _DEBUGLOG_
        Log("NoteDisplay_1::Close()");
#endif
        pn->Close(); }

    VOID ContextMenu (VOID);

    VOID Activate( BOOL find_kludge = FALSE ) {
        if (fAutohide)
            // FIXME what is done here that hasn't been done already?
            MakeCurrent();
        if( find_kludge ) {
            MakeCurrent(); }
    }

    VOID Title (PSZ psz) {
        WinSetWindowText(hwndFrame, psz);
        Tasklist::Instance()->Change(hwndFrame, psz);
    }

    VOID Deactivate (VOID) {
        if (fAutohide)
            Hide(TRUE);
        Title(pn->Headline());
    }

    VOID RebuildMLE (COLOR color = 0x00000000, COLOR colorFG = 0x00ffffee,
                     PSZ psz = "");

    BOOL VerticalSB (VOID) { return fVertSB; }

    VOID VerticalSB (BOOL f) {
        if (fVertSB != f) {
            fVertSB = f;
            RebuildMLE();
        }
    }

    BOOL HorizontalSB (VOID) { return fHorizSB; }

    VOID HorizontalSB (BOOL f) {
        if (fHorizSB != f) {
            fHorizSB = f;
            RebuildMLE();
        }
    }

    BOOL Tasklist (VOID) { return fTasklist; }

    VOID Tasklist (BOOL f) {
        if (f)
            Tasklist::Instance()->Add(hwndFrame);
        else
            Tasklist::Instance()->Remove(hwndFrame);
        fTasklist = f;
        Changed(TRUE);
    }

    BOOL Wordwrap (VOID) { return fWordwrap; }

    VOID Wordwrap (BOOL f) {
        fWordwrap = f;
        WinSendMsg(hwndMLE, MLM_SETWRAP, MPFROMLONG (f), 0L);
        Changed(TRUE);
    }

    BOOL Autohide (VOID) { return fAutohide; }
    VOID Autohide (BOOL f) { fAutohide = f; Changed(TRUE); }

    VOID Undo (VOID) { WinSendMsg(hwndMLE, MLM_UNDO, 0L, 0L); }

#ifdef _DOFIND_
    BOOL Find( IPT &ipt );
#endif

private:
    static MRESULT EXPENTRY wp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    const PSZ PSZ_WCNAME = "wanda.wc.notedisplay_1";

    HWND hwndMLE, hwndFrame, hwndClient;
    HWND hwndSysMenu, hwndTitlebar, hwndMinMax;

    BOOL fHorizSB, fVertSB, fWordwrap, fAutohide, fAutosize, fTasklist;

    static HWND hwndMenu;

    static BOOL fClassRegistered;
};

// ************************************************************************
#endif
