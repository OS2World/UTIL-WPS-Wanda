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

#include "nldisp_1.h"
#include "notedisp_1.h"
#include "note.h"

BOOL NotelistDisplay_1 :: fClassRegistered = FALSE;

// ** NotelistDisplay_1 *************************************************** /*fold00*/

NotelistDisplay_1 :: NotelistDisplay_1 (Notelist &nl,
                                        NotelistDisplayData_1 *pnldd)
    : NotelistDisplay (nl)
{
#ifdef _PARANOID_
    if (!pnldd) {
        DisplayError("NotelistDisplay_1", "pnldd == NULL");
        exit(PARANOID_ERROR);
    }
#endif

    // if not already registered, register the window class
    if (! fClassRegistered)
    {
        WinRegisterClass(GETHAB, PSZ_WCNAME, wp, CS_SIZEREDRAW, 4L);
        fClassRegistered = TRUE;
    }

    // some flags for the window
    ULONG fl =
        FCF_TASKLIST | FCF_TITLEBAR | FCF_SYSMENU | FCF_SIZEBORDER |
        FCF_MINMAX | FCF_ICON;

    // create the window
    hwndFrame =
        WinCreateStdWindow(HWND_DESKTOP, 0L, &fl,
                           PSZ_WCNAME, "Wanda  - Notelist", WS_VISIBLE,
                           0, IDM_WORKAROUND, &hwndClient);
    WinSetWindowPtr(hwndClient, 0, this);

    // attach the menu
    hwndMenu = WinLoadMenu (HWND_DESKTOP, NULLHANDLE, IDM_POPUP);

    // attach the accelerator table
    if (HACCEL haccel = WinLoadAccelTable (hab, NULLHANDLE, IDA_NOTELIST))
        WinSetAccelTable (hab, haccel, hwndFrame);

    // set the conditional cascade stuff
    SetConditionalCascade (hwndMenu, WID_NEWNOTEMENU, WID_NEWNOTE);
    MENUITEM mi;
    WinSendMsg (hwndMenu, MM_QUERYITEM, MPFROM2SHORT (WID_FORSELECTED, TRUE),
                &mi);
    SetConditionalCascade (mi.hwndSubMenu, WID_FS_TITLEBAR, WID_FS_TITLEBARON);
    SetConditionalCascade (mi.hwndSubMenu, WID_FS_VSB, WID_FS_VSBON);
    SetConditionalCascade (mi.hwndSubMenu, WID_FS_HSB, WID_FS_HSBON);
    SetConditionalCascade (mi.hwndSubMenu, WID_FS_TASKLIST, WID_FS_TASKLISTON);
    SetConditionalCascade (mi.hwndSubMenu, WID_FS_WORDWRAP, WID_FS_WORDWRAPON);
//    SetConditionalCascade (mi.hwndSubMenu, WID_FS_AUTOSIZE, WID_FS_AUTOSIZEON);
    SetConditionalCascade (mi.hwndSubMenu, WID_FS_AUTOHIDE, WID_FS_AUTOHIDEON);

    // create the listbox
    hwndLB = WinCreateWindow(hwndClient, WC_LISTBOX, PSZ (NULL),
                             WS_VISIBLE | LS_NOADJUSTPOS |
                             LS_MULTIPLESEL /*| LS_EXTENDEDSEL*/,
                             0,0,1,1,
                             hwndClient, HWND_TOP, WID_LB_NOTES, NULL, NULL);

    // set bg-color presentation parameter
    ULONG  ul = pnldd->color;
    WinSetPresParam(hwndLB, PP_BACKGROUNDCOLOR, sizeof(ul), &ul);

    // set fg-color presentation parameter
    ul = pnldd->colorFG;
    WinSetPresParam(hwndLB, PP_FOREGROUNDCOLOR, sizeof(ul), &ul);

    // set font presentation parameters
    CHAR  ach[CB_FONTNAMESIZE];
    strcpy(ach, pnldd->ach);
    WinSetPresParam(hwndLB, PP_FONTNAMESIZE, sizeof(ach), ach);

    if (pnldd->fMinimized)
        pnldd->swp.fl = SWP_SHOW | SWP_MOVE | SWP_SIZE | SWP_MINIMIZE;
    else
        pnldd->swp.fl = SWP_SHOW | SWP_MOVE | SWP_SIZE;
    WinSetWindowPos(hwndFrame, NULLHANDLE,
                    pnldd->swp.x, pnldd->swp.y, pnldd->swp.cx, pnldd->swp.cy,
                    pnldd->swp.fl);
    WinSetWindowUShort(hwndFrame, QWS_XRESTORE, pnldd->x);
    WinSetWindowUShort(hwndFrame, QWS_YRESTORE, pnldd->y);
    WinSetWindowUShort(hwndFrame, QWS_CXRESTORE, pnldd->cx);
    WinSetWindowUShort(hwndFrame, QWS_CYRESTORE, pnldd->cy);

#ifdef DONLDREMOVETITLE
    hwndSysMenu  = WinWindowFromID(hwndFrame, FID_SYSMENU);
    hwndTitlebar = WinWindowFromID(hwndFrame, FID_TITLEBAR);
    hwndMinMax   = WinWindowFromID(hwndFrame, FID_MINMAX);
    fTitlebar = TRUE;
    if( pset->QueryFlag( SEI_TITLEREMOVED ) ) {
        toggle_titlebar(); }
#endif
    // size, position, etc. window
/*    WinSetWindowPos(hwndFrame, NULLHANDLE,
                    swp.x,swp.y, swp.cx,swp.cy, swp.fl);*/

    Empty();

/*    DisplayError ("DEBUG", "a-0x%08lx", WinGetLastError (GETHAB));
    if (! WinIsWindow (GETHAB, hwndFrame))
        DisplayError ("DEBUG", "b-0x%08lx", WinGetLastError (GETHAB));*/
}

// ** Add ***************************************************************** /*fold00*/

BOOL NotelistDisplay_1 :: Add (Note &n)
{
    ULONG ul =
        ULONG (WinSendMsg (hwndLB, LM_INSERTITEM,
                           MPFROM2SHORT (LIT_END,0),
                           MPFROMP (n.Headline())));
    WinSendMsg (hwndLB, LM_SETITEMHANDLE, MPFROMLONG (ul), MPFROMP (&n));

    // we've got at least one note in our list, so allow this
    WinEnableMenuItem(hwndMenu, WID_CLOSENOTE, TRUE);
    WinEnableMenuItem(hwndMenu, WID_SELECT, TRUE);
    WinEnableMenuItem(hwndMenu, WID_FORSELECTED, TRUE);

    return TRUE;
}

// ** Remove ************************************************************** /*fold00*/

BOOL NotelistDisplay_1 :: Remove (NID nid)
{
    LONG i = Index(nid);
    if (i >= 0) {
        WinDeleteLboxItem(hwndLB, i);
        return TRUE;
    }
    return FALSE;
}

// ** Mark **************************************************************** /*fold00*/

BOOL NotelistDisplay_1 :: Mark (NID nid)
{
    LONG i = Index(nid);
    if (i >= 0) {
        if (!IsSelected(i))
            WinSendMsg (hwndLB, LM_SELECTITEM, MPFROMSHORT(i),
                        MPFROMSHORT(TRUE));
        return TRUE;
    }
    return FALSE;
}

// ** Unmark ************************************************************** /*fold00*/

BOOL NotelistDisplay_1 :: Unmark (NID nid)
{
    LONG i = Index(nid);
    if (i >= 0) {
        if (IsSelected(i))
            WinSendMsg (hwndLB, LM_SELECTITEM, MPFROMSHORT(i),
                        MPFROMSHORT(FALSE));
        return TRUE;
    }
    return FALSE;
}

// ** QuerySelected ******************************************************* /*fold00*/

Note *NotelistDisplay_1 :: QuerySelected (VOID)
{
    Note  *pn;

    LONG   l = LONG(WinSendMsg(hwndLB, LM_QUERYSELECTION,
                               MPFROMSHORT(LIT_CURSOR), NULL));
    if (l < 0)
        pn = (Note *)(WinSendMsg(hwndLB, LM_QUERYITEMHANDLE,MPFROMLONG(0),0));
    else {
        pn = (Note *)(WinSendMsg(hwndLB, LM_QUERYITEMHANDLE,MPFROMLONG(l),0));
        if (! pn)
            pn = (Note *)(WinSendMsg(hwndLB, LM_QUERYITEMHANDLE,
                                     MPFROMLONG(0),0));
    }

    return pn;
}

// ** IsSelected ********************************************************** /*fold00*/

BOOL NotelistDisplay_1 :: IsSelected (LONG i)
{
    LONG l;

    // get index of cursor if required
    if (i == LIT_CURSOR)
        i = LONG (WinSendMsg (hwndLB, LM_QUERYSELECTION, MPFROMLONG(i), NULL));

    // find next selected item after "selected"
    if (i == 0)
        l = LONG (WinSendMsg (hwndLB, LM_QUERYSELECTION, MPFROMLONG(LIT_FIRST),
                              NULL));
    else
        l = LONG (WinSendMsg (hwndLB, LM_QUERYSELECTION, MPFROMLONG(i-1),
                              NULL));

    // if next selected is "selected" itself, it's marked
    if (l == i)
        return TRUE;
    return FALSE;
}

// ** wp ****************************************************************** /*fold00*/

MRESULT EXPENTRY
NotelistDisplay_1 :: wp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    // get pointer to display object assoc. with this window (hwnd)
    NotelistDisplay_1 *pnld = (NotelistDisplay_1 *)(WinQueryWindowPtr(hwnd, 0));

    if (! pnld)
        return WinDefWindowProc(hwnd, msg, mp1, mp2);

    switch (msg)
    {
    case WM_BUTTON2UP:
    case WM_CONTEXTMENU:
        {
            WinPopupMenu (hwnd, hwnd, pnld->hwndMenu, 150,150, WID_SAVEALL,
                          PU_HCONSTRAIN | PU_VCONSTRAIN | PU_POSITIONONITEM |
                          PU_KEYBOARD | PU_MOUSEBUTTON1);
        }
        return MRESULT (FALSE);

    case WM_SIZE:
        WinSetWindowPos (pnld->hwndLB, 0L, 0,0,
                         SHORT1FROMMP (mp2), SHORT2FROMMP (mp2), SWP_SIZE);
        break;

    case WM_COMMAND:
        pnld->Command(SHORT1FROMMP(mp1));
        return MRESULT(FALSE);

    case WM_CONTROL:
        switch (SHORT2FROMMP (mp1))
        {
        case LN_ENTER:
            pnld->pnl->Activate(pnld->QuerySelected()->ID());
            break;

        case LN_SELECT:
            if (pnld->IsSelected()) {
                pnld->pnl->Mark(pnld->QuerySelected()->ID());
            } else {
                pnld->pnl->Unmark(pnld->QuerySelected()->ID());
            }
            break;
        }
        return MRESULT (FALSE);

    case WM_SAVEAPPLICATION:
    case WM_CLOSE:
        pnld->Close();
        break;
    }

    return WinDefWindowProc (hwnd, msg, mp1, mp2);
}

// ** Empty *************************************************************** /*fold00*/

VOID NotelistDisplay_1 :: Empty (VOID)
{
#ifdef _DEBUGLOG_
    Log("NotelistDisplay_1::Empty()\n");
#endif
    WinEnableMenuItem(hwndMenu, WID_CLOSENOTE, FALSE);
    WinEnableMenuItem(hwndMenu, WID_SELECT, FALSE);
    WinEnableMenuItem(hwndMenu, WID_FORSELECTED, FALSE);
}

// ** Command ************************************************************* /*FOLD00*/

VOID NotelistDisplay_1 :: Command (USHORT id)
{
#ifdef _PARANOID_
    if (!pnl) {
        DisplayError("NotelistDisplay_1", "pnl == NULL");
        exit(PARANOID_ERROR);
    }
#endif

    switch (id)
    {
    case WID_NEWNOTE:             pnl->New();                        break;
    case WID_NEWNOTEFROMCLIPBOARD:pnl->NewFromClipboard();           break;
    case WID_NEWNOTEFROMFILE:     pnl->NewFromFile();                break;

    case WID_CLOSENOTE:
        pnl->Activate(QuerySelected()->ID());
        QuerySelected()->Close();
        break;

    case WID_SAVEALL:             pnl->Save(PSZ_NOTESFILE);             break;
    case WID_SELECT_ALL:          pnl->SelectAll ();                 break;
    case WID_SELECT_NONE:         pnl->SelectNone ();                break;
    case WID_SELECT_HIDDEN:       pnl->SelectHidden ();              break;
    case WID_SELECT_SHOWN:        pnl->SelectShown ();               break;
    case WID_SELECT_INVERT:       pnl->InvertSelection ();           break;

    case WID_FS_PRINT:
        // FIXME ?
        if (pnl->pprn->Dialog ())
            pnl->ForSelected(WID_FS_PRINT);
        break;

    case WID_FS_FIND:
#ifdef _DOFIND_
        // FIXME ?
        if (pnl->pfnd->Dialog ())
            pnl->ForSelected(WID_FS_FIND);
#else
        DisplayError("NO GO!",
                     "This feature had to be disabled for the current release "
                     "for technical reasons. Sorry 'bout that. Write me a "
                     "flame if that helps you ;-)");
#endif
        break;

#ifdef DONLDREMOVETITLE
    case WID_REMOVETITLE:
        pnl->pnld->toggle_titlebar();
        break;
#endif

    case WID_ABOUT:               AboutBox(hwndFrame);               break;
    case WID_EXIT:                Close();                           break;

    default:
        // FIXME this check is not the best way ...
        if ((id >= WID_FS_TITLEBARON) && (id <= WID_FS_PRINT))
            pnl->ForSelected(id);
        break;
    }
}

// ** Template ************************************************************ /*fold00*/

NotelistDisplayData_1 *NotelistDisplay_1 :: Template (VOID)
{
    NotelistDisplayData_1 *pnldd = new NotelistDisplayData_1();

    WinQueryWindowPos(hwndFrame, &(pnldd->swp));
    pnldd->swp.hwnd = HWND_DESKTOP;

    pnldd->fMinimized = BOOL((pnldd->swp).fl & SWP_MINIMIZE);
    pnldd->x = WinQueryWindowUShort(hwndFrame, QWS_XRESTORE);
    pnldd->y = WinQueryWindowUShort(hwndFrame, QWS_YRESTORE);
    pnldd->cx = WinQueryWindowUShort(hwndFrame, QWS_CXRESTORE);
    pnldd->cy = WinQueryWindowUShort(hwndFrame, QWS_CYRESTORE);

    ULONG   ppid;
    WinQueryPresParam(hwndLB, PP_BACKGROUNDCOLOR, 0, &ppid,
                      sizeof(pnldd->color), &(pnldd->color), 0);
    WinQueryPresParam(hwndLB, PP_FOREGROUNDCOLOR, 0, &ppid,
                      sizeof(pnldd->colorFG), &(pnldd->colorFG), 0);
    WinQueryPresParam(hwndLB, PP_FONTNAMESIZE, 0, &ppid,
                      CB_FONTNAMESIZE, pnldd->ach, 0);
    return pnldd;
}

// ** Close *************************************************************** /*fold00*/

VOID NotelistDisplay_1 :: Close (VOID)
{
    pnl->Close();
}

VOID NotelistDisplay_1 :: Save (VOID)
{
    pset->SetLong(SEI_NLDTYPE, 1);
    pset->SetBinary(SEI_NLDD, Template(), sizeof(NotelistDisplayData_1));
}

// ** Titlebar ************************************************************ /*fold00*/

#ifdef DONLDREMOVETITLE

BOOL NotelistDisplay_1 :: toggle_titlebar( VOID )
{
    HWND   hwnd = hwndFrame;
    BOOL   fWasVisible = WinIsWindowVisible (hwnd);

    fTitlebar = ! fTitlebar;
    pset->SetFlag( SEI_TITLEREMOVED, ! fTitlebar );

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
    if( fTitlebar ) {
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

    return fTitlebar;
}

#endif

// ************************************************************************
