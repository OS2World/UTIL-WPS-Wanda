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

#ifndef _NOTELIST_H_
#define _NOTELIST_H_

#include "wanda.h"

#include "note.h"
#include "nd_fact.h"
#include "nldisp.h"
#include "printer.h"

#ifdef _DOFIND_
#include "finder.h"
#endif

// ** classdef ************************************************************ /*FOLD00*/

class Notelist
{
#ifdef DONLDREMOVETITLE
    friend class NotelistDisplay_1;
#endif

private:
    const USHORT   C_MAXNOTES = 512;

public:
    Notelist (VOID) { Init(); }
    Notelist (PSZ psz);

    ~Notelist (VOID) {
        pnl = NULL;
        StopTimer();
        if (pnld) { delete pnld; pnld = NULL; }
    }

protected:
    BOOL CheckHeader (FILE *pf, PSZ psz);

    VOID Init (VOID) {
        fDoClose = FALSE;
        c = 0;
        pnld = NULL;
        memset(apn, NULL, sizeof(apn[0])*C_MAXNOTES);
        memset(ab, FALSE, sizeof(ab[0])*C_MAXNOTES);
        pnl = this;
        _beginthread (Tick, NULL, 1024L*32L, NULL);
        RestartTimer();
        pprn = new Printer(this);
#ifdef _DOFIND_
        pfnd = new Finder( this );
#endif
    }

#ifdef _DOFIND_
public:
    class Finder *pfnd;

    BOOL Find( BOOL from_first );

protected:
#endif

    BOOL IndexValid (USHORT i) { return BOOL ((i < C_MAXNOTES) && apn[i]); }

    BOOL MarkByIndex (USHORT i) {
        if (!IndexValid(i)) { return FALSE; }
        ab[i] = TRUE;
        if (pnld)
            pnld->Mark(apn[i]->ID());
        return TRUE;
    }

public:
    BOOL Mark (NID nid) { return MarkByIndex(Index(nid)); }

protected:
    BOOL UnmarkByIndex (USHORT i) {
        if (!IndexValid(i)) { return FALSE; }
        ab[i] = FALSE;
        if (pnld)
            pnld->Unmark(apn[i]->ID());
        return TRUE;
    }

public:
    BOOL Unmark (NID nid) { return UnmarkByIndex(Index(nid)); }

protected:
    USHORT Index (NID nid) {
        if (!IndexValid(nid)) { return C_MAXNOTES; }
        return nid;
/*        for (USHORT i = 0; i < c; i++)
            if (apn[i]->ID () == nid)
                return i;
        return NID_NIL; */
    }

    USHORT Index (Note &n);

    NID GetFreeIndex (VOID) {
        USHORT i;
        for (i = 0; i < C_MAXNOTES; i++)
            if (apn[i] == NULL)
                break;
        return i;
    }

    BOOL Add (Note *pn) { return Add(*pn); }

    BOOL Add (Note &n) {
        n.SetNotelist(*this);
        apn[n.ID()] = &n;
        c++;
        if (pnld) { pnld->Add(n); }
        return TRUE;
    }

public:
    USHORT Count (VOID) { return c; }

    NID New (VOID);
    NID NewFromClipboard (VOID);
    NID NewFromFile (VOID);

    BOOL SelectFile (PSZ psz);

    BOOL Remove (NID nid) {
#ifdef _DEBUGLOG_
        Log("NoteList::Remove(%d)\n", nid);
#endif
        USHORT i = Index(nid);
        if (apn[i] && (i < C_MAXNOTES)) {
            if (pnld) { pnld->Remove(nid); }
            c--;
            delete apn[i];
            apn[i] = NULL;
            if (c == 0) { Empty(); }
            return TRUE;
        }
        return FALSE;
    }

    VOID Display (class NotelistDisplay &nld);

    VOID SelectAll (VOID) {
        for (USHORT i = 0; i < C_MAXNOTES; i++) { MarkByIndex(i); }
    }

    VOID SelectNone (VOID) {
        for (USHORT i = 0; i < C_MAXNOTES; i++) { UnmarkByIndex(i); }
    }

    VOID SelectHidden (VOID) {
        for (USHORT i = 0; i < C_MAXNOTES; i++)
            if (apn[i])
                if (apn[i]->Hide())
                    MarkByIndex(i);
                else
                    UnmarkByIndex(i);
    }

    VOID SelectShown (VOID) {
        for (USHORT i = 0; i < C_MAXNOTES; i++)
            if (apn[i])
                if (! apn[i]->Hide())
                    MarkByIndex(i);
                else
                    UnmarkByIndex(i);
    }

    LONG Notelist :: ForSelected (USHORT us);

protected:
    BOOL MarkedByIndex (USHORT i) {
        if (!IndexValid(i)) { return FALSE; }
        return ab[i];
    }

public:
    VOID InvertSelection (VOID) {
        for (USHORT i = 0; i < C_MAXNOTES; i++) {
            if (MarkedByIndex(i))
                UnmarkByIndex(i);
            else
                MarkByIndex(i);
        }
    }

    BOOL Save (PSZ psz);

    BOOL Activate (NID nid) {
        USHORT i = Index(nid);
        if (!IndexValid(i)) { return FALSE; }
        return apn[i]->MakeCurrent();
    }

    VOID Empty (VOID) {
#ifdef _DEBUGLOG_
        Log("NoteList::Empty()\n");
#endif
        if (pnld) { pnld->Empty(); } }

    BOOL Title (NID nid, PSZ psz) {
        if (pnld) { return pnld->Title(nid, psz); }
        return TRUE;
    }

    BOOL Marked (NID nid) { return MarkedByIndex(Index(nid)); }

private:
    static BOOL      fTickOn;
    static USHORT    cDown;
    static Notelist *pnl;

    static VOID Tick (PVOID);

public:
    VOID RestartTimer (VOID) {
//        DosBeep(500,500);
        cDown = C_AUTOSAVESECS;
    }

    VOID StopTimer (VOID) { cDown = 0; }

    VOID Close (VOID) {
#ifdef _DEBUGLOG_
        Log("NoteList::Close()\n");
#endif
        Save(PSZ_NOTESFILE);
        fDoClose = TRUE;
    }

    BOOL DoClose (VOID) { return fDoClose; }

private:
    USHORT   c;
    BOOL     fDoClose;
    Note    *apn[C_MAXNOTES];
    BOOL     ab[C_MAXNOTES];
    NotelistDisplay *pnld;

    const PSZ      PSZ_NOTESFILEHEADER = "Wanda notes file\r\n\x1a";
    const USHORT   CB_NOTESFILEHEADER = 19;
    const USHORT   NOTESFILEVERSION = 2;

public:
    Printer  *pprn;
};

// ************************************************************************
#endif
