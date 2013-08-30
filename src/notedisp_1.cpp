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

#include "notedisp_1.h"

BOOL NoteDisplay_1 :: fClassRegistered = FALSE;
HWND NoteDisplay_1 :: hwndMenu = NULLHANDLE;

// ** Changed ************************************************************* /*fold00*/

VOID NoteDisplay_1 :: Changed (BOOL f)
{
    NoteDisplay::Changed(f);
    if (f)
        pn->pnl->RestartTimer();
    else
        pn->pnl->StopTimer();
}

// ** NoteDisplay (from template) ***************************************** /*fold00*/

NoteDisplay_1 :: NoteDisplay_1 (Note &n, NoteDisplayTemplate_1 *pndt)
: NoteDisplay (n)
{
    hwndMLE = NULLHANDLE;
    fVertSB   = pndt->fVertSB;
    fHorizSB  = pndt->fHorizSB;
    fWordwrap = pndt->fWordwrap;
    fTasklist = pndt->fTasklist;
    fAutohide = pndt->fAutohide;
    fAutosize = FALSE;

    // if not already registered, register the window class
    if (! fClassRegistered) {
        WinRegisterClass(GETHAB, PSZ_WCNAME, wp, CS_SIZEREDRAW, 4L);
        fClassRegistered = TRUE;
    }

    // get the note popup menu
    if (! hwndMenu)
        hwndMenu = WinLoadMenu(HWND_DESKTOP, NULLHANDLE, IDM_NOTEPOPUP);

    // set the conditional cascade stuff
    SetConditionalCascade(hwndMenu, WID_PRINT, WID_PRINT_QUICK);
    SetConditionalCascade(hwndMenu, WID_NEWNOTEMENU, WID_NEWNOTE);

    // attach the accelerator table
    if (HACCEL haccel = WinLoadAccelTable(hab, NULLHANDLE, IDA_NOTE))
        WinSetAccelTable(hab, haccel, hwndFrame);

    ULONG fl = FCF_TITLEBAR | FCF_SYSMENU | FCF_SIZEBORDER |
        FCF_MINMAX | FCF_ICON | FCF_AUTOICON | FCF_NOBYTEALIGN;

    // indeed, we've got a titlebar, definitly and positivly!
    // (apart from when, although explicitly requested by us, the PM wouldn't
    // grant us one, an event rather unlikely to take place ;-)
    fTitlebar = TRUE;

    // create the window
    hwndFrame = WinCreateStdWindow(HWND_DESKTOP/*FIXME? pndt->swp.hwnd*/,
                                   FS_MOUSEALIGN, &fl,
                                   PSZ_WCNAME, NULL, 0x00, 0,
                                   IDM_WORKAROUND, &hwndClient);
    WinSetWindowPtr(hwndClient, 0, this);

    // We have to save this stuff for Titlebar()
    hwndSysMenu  = WinWindowFromID(hwndFrame, FID_SYSMENU);
    hwndTitlebar = WinWindowFromID(hwndFrame, FID_TITLEBAR);
    hwndMinMax   = WinWindowFromID(hwndFrame, FID_MINMAX);

    // this will (as there doesn't exist one by now) create the MLE
    RebuildMLE(pndt->colorFG, pndt->color, pndt->ach);

    // get height of titlebar
    SWP  swp;
    WinQueryWindowPos(hwndTitlebar, &swp);
    USHORT  cyTitlebar = swp.cy;

    // hide the titlebar if requested
    Titlebar(pndt->fTitlebar);

    // show, position, size window
    if (pndt->fMinimized) {
        if (!Titlebar())
            pndt->cy += cyTitlebar;
        WinSetWindowPos(hwndFrame, HWND_TOP, pndt->swp.x,pndt->swp.y,
                        pndt->swp.cx,pndt->swp.cy,
                        SWP_MOVE | SWP_SIZE | SWP_ACTIVATE);
        // FIXME we have to do this seperatly, otherwise text in MLE
        // gets doubled?!?
        WinSetWindowPos(hwndFrame, HWND_TOP, 0,0,0,0, SWP_MINIMIZE);

        WinSetWindowUShort(hwndFrame, QWS_XRESTORE, pndt->x);
        WinSetWindowUShort(hwndFrame, QWS_YRESTORE, pndt->y);
        WinSetWindowUShort(hwndFrame, QWS_CXRESTORE, pndt->cx);
        WinSetWindowUShort(hwndFrame, QWS_CYRESTORE, pndt->cy);
    } else {
        if (!Titlebar())
            pndt->swp.cy += cyTitlebar;
        WinSetWindowPos(hwndFrame, HWND_TOP, pndt->swp.x,pndt->swp.y,
                        pndt->swp.cx,pndt->swp.cy,
                        SWP_MOVE | SWP_SIZE | SWP_ACTIVATE);
    }

    // activate autohide if requested
    Autohide(fAutohide);

    // push it in the tasklist if requested
    Tasklist(fTasklist);

    WinShowWindow(hwndFrame, TRUE);
    Changed(FALSE);
}

// ** RebuildMLE ********************************************************** /*fold00*/

VOID NoteDisplay_1 :: RebuildMLE (COLOR colorFG, COLOR color, PSZ psz)
{
    CHAR   ach[CB_FONTNAMESIZE];
    BOOL   f = FALSE;

    if (hwndMLE) {
        // if we've got a "previous" MLE, get it's parameters
        f = BOOL(WinSendMsg(hwndMLE, MLM_QUERYCHANGED, 0, 0));
        ULONG   ppid;
        WinQueryPresParam(hwndMLE, PP_BACKGROUNDCOLOR, 0, &ppid,
                          sizeof (color), &color, 0);
        WinQueryPresParam(hwndMLE, PP_FOREGROUNDCOLOR, 0, &ppid,
                          sizeof (colorFG), &colorFG, 0);
        WinQueryPresParam(hwndMLE, PP_FONTNAMESIZE, 0, &ppid,
                          CB_FONTNAMESIZE, ach, 0);
        // ... and destroy it
        WinDestroyWindow(hwndMLE);
    } else {
        // use the given values
        strcpy(ach, psz);
    }

    // being able to see the thing should prove a big advantage to the
    // user ;-)
    ULONG  fl = WS_VISIBLE;

    // if vertical/horizontal scrollbar requested, set the appropr. flags
    if (fVertSB)  { fl = fl | MLS_VSCROLL; }
    if (fHorizSB) { fl = fl | MLS_HSCROLL; }

    SWP  swp;
    WinQueryWindowPos(hwndClient, &swp);

    // create the MLE
    hwndMLE = WinCreateWindow(hwndClient, WC_MLE, PSZ (NULL), fl,
                              0,0, swp.cx,swp.cy, hwndClient, HWND_TOP, 1L,
                              NULL, NULL);
    wpOldMLE = WinSubclassWindow(hwndMLE, wpNewMLE);

    // set MLE's presentation parameters
    WinSetPresParam(hwndMLE, PP_BACKGROUNDCOLOR, sizeof(color), &color);
    WinSetPresParam(hwndMLE, PP_FOREGROUNDCOLOR, sizeof(colorFG), &colorFG);
    WinSetPresParam(hwndMLE, PP_FONTNAMESIZE, CB_FONTNAMESIZE, ach);

    Wordwrap(fWordwrap);

    // insert our corresponding note's text
    Text(pn->RawText());
//    DisplayError ("DEBUG", "<%s>", pn->RawText());

    WinSendMsg(hwndMLE, MLM_FORMAT, MPFROMSHORT(MLFIE_CFTEXT), 0);
    WinSendMsg(hwndMLE, MLM_SETCHANGED, MPFROMSHORT(f), 0);
}

// ** Text **************************************************************** /*fold00*/

VOID NoteDisplay_1 :: Text (STRING *pstr)
{
    // no time-consuming updating while we're at work
    WinSendMsg (hwndMLE, MLM_DISABLEREFRESH, 0,0);

    // clear all text from the MLE - FIXME do this better
    ULONG cbCopy =
        ULONG (WinSendMsg (hwndMLE, MLM_QUERYFORMATTEXTLENGTH,
                           MPFROMLONG(0), MPFROMLONG(-1)));
    WinSendMsg (hwndMLE, MLM_SETSEL, MPARAM (0L), MPARAM (cbCopy));
    WinSendMsg (hwndMLE, MLM_CLEAR, 0,0);

    if (pstr)
    {
        // insert the text
        WinSendMsg (hwndMLE, MLM_SETIMPORTEXPORT,
                    MPFROMP (pstr), MPFROMSHORT (strlen (pstr)));
        ULONG   ul = 0;
        WinSendMsg (hwndMLE, MLM_IMPORT, MPFROMP (&ul),
                    MPFROMLONG (strlen (pstr)));
    }

    // set title and tasklist entry (if window has one)
    Title(pn->Headline());

    // show the changes
    WinSendMsg (hwndMLE, MLM_ENABLEREFRESH, 0,0);
}

STRING *NoteDisplay_1 :: Text (VOID)
{
    // if I remember right, I needed the following line because
    // exporting text does *not* work if the window is minimized.
    // WinSetWindowPos(hwndFrame, 0, 0,0, 0,0, SWP_RESTORE);

    // how many characters? bytes? are in the MLE?
    ULONG cbCopy =
        ULONG (WinSendMsg (hwndMLE, MLM_QUERYFORMATTEXTLENGTH,
                           MPFROMLONG(0), MPFROMLONG(-1)));

    // allocate a buffer to hold the text from the MLE.
    // when using DBCS would it be enough to just use a buffer with
    // twice the size (cbCopy*2) ?
    PSZ  psz = PSZ (malloc (cbCopy));
    if (! psz)
        return NULL;

    // tell the MLE to export the text to the above buffer.
    ULONG cbCopy2 = cbCopy;
    WinSendMsg (hwndMLE, MLM_SETIMPORTEXPORT,
                MPFROMP (psz), MPFROMSHORT (cbCopy));

    // export the text from the MLE into the buffer.
    LONG l = 0;
    WinSendMsg (hwndMLE, MLM_EXPORT, MPFROMP (&l), MPFROMP (&cbCopy));
    psz[cbCopy2] = '\0';

    // if we had restored the window (see start of function), we now
    // minimze it again.
    // WinSetWindowPos(hwndFrame, 0, 0,0, 0,0, SWP_MINIMIZE);
    return psz;
}

// ** wp ****************************************************************** /*fold00*/

MRESULT EXPENTRY
NoteDisplay_1 :: wp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    // get pointer to display object assoc. with this window (hwnd)
    NoteDisplay_1  *pnd = (NoteDisplay_1 *)(WinQueryWindowPtr (hwnd, 0));

    // unlikely, but who knows?
    if (! pnd) {
#ifdef _DEBUGLOG_
        Log("NoteDisplay_1::wp() [no pnd]\n");
#endif
        return WinDefWindowProc(hwnd, msg, mp1, mp2);
    }

#ifdef _DEBUGLOG_
    Log("NoteDisplay_1::wp() [%lx]\n", msg);
#endif

    switch (msg)
    {
    case WM_COMMAND: pnd->Command(SHORT1FROMMP(mp1)); return MRESULT(FALSE);
    case WM_CONTEXTMENU:     pnd->ContextMenu();      return MRESULT(FALSE);
    case WM_BEGINDRAG:       pnd->Drag();             return MRESULT(FALSE);
    case WM_CLOSE:
#ifdef _DEBUGLOG_
        Log("NoteDisplay_1::wp() [WM_CLOSE]\n");
#endif
        pnd->Close();
        return MRESULT(FALSE);

    case WM_ACTIVATE:
        if (SHORT1FROMMP (mp1))
            pnd->Activate();
        else
            pnd->Deactivate();
        return MRESULT (FALSE);

    case WM_SIZE:
        WinSetWindowPos (pnd->hwndMLE, 0L, 0,0,
                         SHORT1FROMMP (mp2), SHORT2FROMMP (mp2),
                         SWP_SIZE);
        /*            if (pnd->fAutosize)
                WinSendMsg (pnd->hwndMLE, MLM_SETFORMATRECT, NULL,
                            MPFROMLONG (MLFFMTRECT_LIMITVERT|
                                        MLFFMTRECT_LIMITHORZ));
            else */
        WinSendMsg (pnd->hwndMLE, MLM_SETFORMATRECT, NULL,
                    MPFROMLONG (MLFFMTRECT_MATCHWINDOW));
        pnd->Changed(TRUE);
        break;

    case WM_CONTROL:
        switch (SHORT2FROMMP (mp1))
        {
        case MLN_CHANGE:          pnd->Changed(TRUE);          break;
        }
        return MRESULT (FALSE);

    case WM_DESTROY:
#ifdef _DEBUGLOG_
        Log("NoteDisplay_1::wp() [WM_DESTROY]\n");
#endif
        break;

    case WM_MINMAXFRAME:
        // This is yukkiest but as we can't query an MLE's text when
        // it is not shown, we have to update the notes text now
        pnd->pn->UpdateText();
        break;
    }

    return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

// ** ~NoteDisplay_1 ****************************************************** /*fold00*/

NoteDisplay_1 :: ~NoteDisplay_1 (VOID)
{
#ifdef _DEBUGLOG_
    Log("NoteDisplay_1::~NoteDisplay()\n");
#endif
    WinDestroyWindow(hwndFrame);
}

// ** Save **************************************************************** /*fold00*/

VOID NoteDisplay_1 :: Save (FILE *pf)
{
    NoteDisplayTemplate_1  *pndt = Template();
    pndt->Save(pf);
    delete pndt;
}

// ** Template ************************************************************ /*fold00*/

NoteDisplayTemplate_1 *NoteDisplay_1 :: Template (VOID)
{
    NoteDisplayTemplate_1 *pndt = new NoteDisplayTemplate_1();

    WinQueryWindowPos (hwndFrame, &(pndt->swp));
    pndt->swp.hwnd = HWND_DESKTOP;

    pndt->fMinimized = BOOL ((pndt->swp).fl & SWP_MINIMIZE);
    pndt->x = WinQueryWindowUShort (hwndFrame, QWS_XRESTORE);
    pndt->y = WinQueryWindowUShort (hwndFrame, QWS_YRESTORE);
    pndt->cx = WinQueryWindowUShort (hwndFrame, QWS_CXRESTORE);
    pndt->cy = WinQueryWindowUShort (hwndFrame, QWS_CYRESTORE);

    ULONG   ppid;
    WinQueryPresParam (hwndMLE, PP_BACKGROUNDCOLOR, 0, &ppid,
                       sizeof (pndt->color), &(pndt->color), 0);
    WinQueryPresParam (hwndMLE, PP_FOREGROUNDCOLOR, 0, &ppid,
                       sizeof (pndt->colorFG), &(pndt->colorFG), 0);
    WinQueryPresParam (hwndMLE, PP_FONTNAMESIZE, 0, &ppid,
                       CB_FONTNAMESIZE, pndt->ach, 0);

    pndt->fTitlebar = fTitlebar;
    pndt->fVertSB = fVertSB;
    pndt->fHorizSB = fHorizSB;
    pndt->fWordwrap = fWordwrap;

    pndt->fAutohide = fAutohide;
    pndt->fAutosize = fAutosize;
    pndt->fTasklist = fTasklist;

    return pndt;
}

// ** wpNewMLE ************************************************************ /*fold00*/

MRESULT EXPENTRY NoteDisplay_1 ::
wpNewMLE (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    HWND          hwndOwner = WinQueryWindow (hwnd, QW_OWNER);
    NoteDisplay_1 *pnd = (NoteDisplay_1 *)(WinQueryWindowPtr (hwndOwner, 0));

    switch (msg)
    {
    case WM_CONTEXTMENU:
        WinSendMsg (hwndOwner, WM_CONTEXTMENU, 0,0);
        break;

    case WM_BEGINDRAG:
        WinSendMsg (hwndOwner, WM_BEGINDRAG, 0,0);
        break;
    }

    return pnd->wpOldMLE (hwnd, msg, mp1, mp2);
}

// ** Drag **************************************************************** /*FOLD00*/

VOID NoteDisplay_1 :: Drag (VOID)
{
    HWND   hwnd = hwndFrame;

    // determine the new window position
    TRACKINFO   trackinfo ;
    memset (&trackinfo, 0, sizeof (trackinfo));

    trackinfo.cxBorder = 1;
    trackinfo.cyBorder = 1;
    trackinfo.cxGrid = 1;
    trackinfo.cyGrid = 1;
    trackinfo.cxKeyboard = 8;
    trackinfo.cyKeyboard = 8;
 
    SWP   swp;
    WinQueryWindowPos (hwnd, &swp);
    trackinfo.rclTrack.xLeft   = swp.x;
    trackinfo.rclTrack.xRight  = swp.x + swp.cx;
    trackinfo.rclTrack.yBottom = swp.y;
    trackinfo.rclTrack.yTop    = swp.y + swp.cy;

    WinQueryWindowPos (HWND_DESKTOP, &swp);
    trackinfo.rclBoundary.xLeft   = swp.x;
    trackinfo.rclBoundary.xRight  = swp.x + swp.cx;
    trackinfo.rclBoundary.yBottom = swp.y;
    trackinfo.rclBoundary.yTop    = swp.y + swp.cy;

    trackinfo.ptlMinTrackSize.x = 0;
    trackinfo.ptlMinTrackSize.y = 0;
    trackinfo.ptlMaxTrackSize.x = swp.cx;
    trackinfo.ptlMaxTrackSize.y = swp.cy;

    trackinfo.fs = TF_MOVE | TF_STANDARD | TF_ALLINBOUNDARY;

    if (WinTrackRect (HWND_DESKTOP, 0, &trackinfo))
        WinSetWindowPos (hwnd, 0, trackinfo.rclTrack.xLeft,
                         trackinfo.rclTrack.yBottom, 0, 0, SWP_MOVE);
    Changed(TRUE);
}

// ** Titlebar ************************************************************ /*fold00*/

VOID NoteDisplay_1 :: Titlebar (BOOL f)
{
    HWND   hwnd = hwndFrame;
    BOOL   fWasVisible = WinIsWindowVisible (hwnd);

    if (fTitlebar == f)
        return;
    fTitlebar = f;

    // get original window position and state
    SWP   swpOld;
    WinQueryWindowPos (hwnd, &swpOld);

    // restore and hide the window
    WinEnableWindowUpdate (hwnd, FALSE);

    // determine client window and location
    SWP   swp;
    WinQueryWindowPos (hwnd, &swp);

    RECTL   rcl;
    rcl.xLeft   = swp.x;
    rcl.xRight  = swp.x + swp.cx;
    rcl.yBottom = swp.y;
    rcl.yTop    = swp.y + swp.cy;

    WinCalcFrameRect (hwnd, &rcl, TRUE);

    // get height of titlebar
    SHORT  cy;

    // hide or reveal the controls windows by changing their parentage
    if (f) {
        cy = - SHORT (WinQuerySysValue (HWND_DESKTOP, SV_CYTITLEBAR));
        WinSetParent (hwndSysMenu,  hwnd, TRUE);
        WinSetParent (hwndTitlebar, hwnd, TRUE);
        WinSetParent (hwndMinMax,   hwnd, TRUE);
        if (WinQueryActiveWindow (WinQueryWindow (hwnd, QW_PARENT)) == hwnd)
            WinSendMsg (WinWindowFromID (hwnd, FID_TITLEBAR), TBM_SETHILITE,
                        MPFROMLONG (TRUE), 0);
    } else {
        cy = SHORT (WinQuerySysValue (HWND_DESKTOP, SV_CYTITLEBAR));
        WinSetParent (hwndSysMenu,  HWND_OBJECT, FALSE);
        WinSetParent (hwndTitlebar, HWND_OBJECT, FALSE);
        WinSetParent (hwndMinMax,   HWND_OBJECT, FALSE);
    }

    // tell the frame that things have changed. let it update the window
    WinSendMsg (hwnd, WM_UPDATEFRAME,
                MPFROMSHORT (FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON), 0);

    // reposition the frame around the client window, which is left be
    WinCalcFrameRect (hwnd, &rcl, FALSE);
    if (! (swpOld.fl & SWP_MINIMIZE))
        WinSetWindowPos (hwnd, 0, rcl.xLeft, rcl.yBottom, rcl.xRight-rcl.xLeft,
                         rcl.yTop-rcl.yBottom+cy, SWP_SIZE | SWP_MOVE);

    // if window was maximized, put it back that way
    if (swpOld.fl & SWP_MAXIMIZE) {
        WinSetWindowPos (hwnd, 0, rcl.xLeft,  rcl.yBottom,
                         rcl.xRight - rcl.xLeft, rcl.yTop - rcl.yBottom,
                         SWP_SIZE | SWP_MOVE | (swpOld.fl & SWP_MAXIMIZE));
    }

    // if the window was visible in the first place, show it
    WinEnableWindowUpdate (hwnd, TRUE);
    if (fWasVisible)
        WinShowWindow (hwnd, TRUE);

    Changed(TRUE);
}

// ** ContextMenu ********************************************************* /*fold00*/

VOID NoteDisplay_1 :: ContextMenu (VOID)
{
    // all notes share one popup menu, so we have to do this here
    WinCheckMenuItem(hwndMenu, WID_VERTICALSB, fVertSB);
    WinCheckMenuItem(hwndMenu, WID_HORIZSB, fHorizSB);
    WinCheckMenuItem(hwndMenu, WID_TASKLIST, fTasklist);
    WinCheckMenuItem(hwndMenu, WID_WORDWRAP, fWordwrap);
    WinCheckMenuItem(hwndMenu, WID_AUTOHIDE, fAutohide);
    WinCheckMenuItem(hwndMenu, WID_TITLEBAR, fTitlebar);

    USHORT us = USHORT(WinSendMsg(hwndMLE, MLM_QUERYUNDO, 0L, 0L));
    if (us)
    {
//        PSZ psz = NULL;
        WinEnableMenuItem(hwndMenu, WID_FS_UNDO, TRUE);
/*        switch (us) {
        case WM_CHAR:             psz = "Insert text";     break;
        case MLM_SETFONT:         psz = "Font change";     break;
        case MLM_SETTEXTCOLOR:    psz = "Color change";    break;
        case MLM_CUT:             psz = "Cut text";        break;
        case MLM_PASTE:           psz = "Paste text";      break;
        case MLM_CLEAR:           psz = "Clear text";      break;
        } */
    }
    else
        WinEnableMenuItem(hwndMenu, WID_FS_UNDO, FALSE);

    WinPopupMenu(hwndClient, hwndClient, hwndMenu, 150,150, WID_TITLEBAR,
                 PU_HCONSTRAIN | PU_VCONSTRAIN | PU_POSITIONONITEM |
                 PU_KEYBOARD | PU_MOUSEBUTTON1);
}

// ** Command ************************************************************* /*FOLD00*/

VOID NoteDisplay_1 :: Command (USHORT id)
{
    switch (id)
    {
    case WID_HIDENOTE:        Hide(TRUE);                        break;
    case WID_CLOSENOTE:       Close();                           break;
    case WID_TITLEBAR:        Titlebar(!Titlebar());             break;
    case WID_VERTICALSB:      VerticalSB(!VerticalSB());         break;
    case WID_HORIZSB:         HorizontalSB(!HorizontalSB());     break;
    case WID_TASKLIST:        Tasklist(!Tasklist());             break;
    case WID_WORDWRAP:        Wordwrap(!Wordwrap());             break;
    case WID_AUTOHIDE:        Autohide(!Autohide());             break;

    case WID_PRINT_DIALOG:
        if (! pn->pnl->pprn->Dialog())
            break;

    case WID_PRINT_QUICK: {
        FILE *pf;
        if ((pf = pn->pnl->pprn->OpenOutput ())) {
            pn->pnl->pprn->OutputNote(pf, pn);
            pn->pnl->pprn->CloseOutput(pf);
        }
    }
    break;

    case WID_SAVEASDEFAULT:
        NoteDisplayFactory::Instance()->Template(Template());
        break;

    case WID_CUT:       WinSendMsg(hwndMLE, MLM_CUT, 0, 0);      break;
    case WID_COPY:      WinSendMsg(hwndMLE, MLM_COPY, 0, 0);     break;
    case WID_PASTE:     WinSendMsg(hwndMLE, MLM_PASTE, 0, 0);    break;

    case WID_NEWNOTE:   pn->pnl->New();                          break;
    case WID_NEWNOTEFROMCLIPBOARD: pn->pnl->NewFromClipboard();  break;
    case WID_NEWNOTEFROMFILE:      pn->pnl->NewFromFile();       break;

    case WID_SAVEALL:   pn->pnl->Save(PSZ_NOTESFILE);            break;
    case WID_ABOUT:     AboutBox(hwndFrame);                     break;

    case WID_EXIT:      pn->pnl->Close();                        break;

    case WID_FS_UNDO:   Undo();                                  break;
    }
}

// ** Find **************************************************************** /*FOLD00*/

#ifdef _DOFIND_
BOOL NoteDisplay_1 :: Find( IPT &ipt )
{
    MLE_SEARCHDATA  msd;

    // fill the MLE_SEARCHDATA data structure
    msd.cb         = sizeof (msd);
    msd.pchFind    = pset->QueryString (SEI_FINDTEXT);
    msd.cchFind    = strlen (msd.pchFind);
    msd.iptStart   = ipt;
    msd.iptStop    = -1;

    // set search flags
    ULONG fl = MLFSEARCH_SELECTMATCH;
    if (pset->QueryFlag (SEI_FINDCASESENS))
        fl |= MLFSEARCH_CASESENSITIVE;

    // start the search
    if (WinSendMsg (hwndMLE, MLM_SEARCH, MPFROMLONG (fl), MPFROMP (&msd)))
    {
        if (pset->QueryFlag (SEI_FINDREPLACE))
            WinSendMsg (hwndMLE, MLM_INSERT,
                        MPFROMP (pset->QueryString (SEI_FINDREPLACETEXT)),
                        MPFROMP (&msd));
        ipt = msd.iptStart+1;  // FIXME?
        return TRUE;
    }

    ipt = 0L;
    return FALSE;
}
#endif

// ************************************************************************
