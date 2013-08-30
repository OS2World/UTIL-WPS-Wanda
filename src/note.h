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

#ifndef _NOTE_H_
#define _NOTE_H_

#include "wanda.h"
#include "notedisp.h"

// ** classdef ************************************************************ /*FOLD00*/

/*
 Note() - erzeugt neue leere Note
 Note(psz) - erzeugt neue Note mit Inhalt psz
 Note(pf) - erzeugt neue Note mit Inhalt aus File pf


 Note mit Display erzeugen:
 - NoteDisplay_1(Note())

 Display einer Note aendern:
 - delete NoteDisplay_1
 - NoteDisplay_2(Note())



 Wrapper fuer
 - Titlebar
 - HS
 - VS
 - Tasklist
 - Wordwrap
 - Autohide
 - Autosize
 */

class Note
{
    friend class Notelist;

public:
    Note (VOID) { Init(); }         // create an empty note

    VOID      Text (STRING *pstr);    // set note's text
    STRING   *Text (VOID);            // query note's text

    VOID      Changed (VOID);
    USHORT    ID (VOID);

    VOID           Display (NoteDisplay &nd);
    NoteDisplay   *Display (VOID) { return pnd; }

    class Notelist *SetNotelist (Notelist &nl) {
        Notelist *pnlOld = this->pnl;
        this->pnl = &nl;
        return pnlOld;
    }

protected:
    Note (FILE *pf);
    Note (STRING *pstr, NID nid = NID_NIL);

    NID ID (NID nid) {
        NID nidOld = this->nid;
        this->nid = nid;
        return nidOld;
    }

    VOID RawText (STRING *pstr) {
        if (this->pstr) { delete this->pstr; }
        if (pstr) { this->pstr = strdup(pstr); }
    }

    VOID Init (VOID);

public:
    STRING *RawText (VOID) { return pstr; }

    VOID Close (VOID);

    BOOL MakeCurrent (VOID) {
        if (pnd) { return pnd->MakeCurrent(); }
        return TRUE;
    }

    VOID UpdateText (VOID);

    BOOL Hide (VOID) {
        if (pnd) { return pnd->Hide(); }
        return TRUE;
    }

    STRING *Headline (VOID);

#ifdef _DOFIND_
    LONG Find (PSZ pszFind, PSZ pszReplace = NULL, LONG l = 0);
    VOID Activate (VOID) { pnd->Activate( TRUE ); }
#endif

    ~Note (VOID) {
#ifdef _DEBUGLOG_
        Log("Note::~Note()\n");
#endif
        if (pstr) { delete pstr; }
        if (pnd) { delete pnd; }
        Changed();
    }

protected:

    BOOL Save (FILE *pf);

private:
    NID      nid;
    STRING  *pstr;
    NoteDisplay *pnd;

public: // FIXME ah well, NoteDisplay needs it, but ...
    Notelist    *pnl;
};

#include "notelist.h"

// ************************************************************************
#endif
