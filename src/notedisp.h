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

#ifndef _NOTEDISP_H_
#define _NOTEDISP_H_

#include "wanda.h"

// ** classdef ************************************************************ /*FOLD00*/

class NoteDisplay
{
    friend class Note;

public:
    NoteDisplay (Note &n) { pn = &n; fChanged = FALSE; }

    virtual VOID Text (STRING *pstr) = 0;
    virtual STRING *Text (VOID) = 0;

    virtual VOID Save (FILE *pf) = 0;
    virtual VOID Close (VOID) = 0;

    virtual BOOL MakeCurrent (VOID) = 0;

    virtual VOID Hide (BOOL f) = 0;
    virtual BOOL Hide (VOID) = 0;

    virtual VOID Wordwrap (BOOL f) = 0;
    virtual BOOL Wordwrap (VOID) = 0;

    virtual BOOL VerticalSB (VOID) = 0;
    virtual VOID VerticalSB (BOOL f) = 0;

    virtual BOOL HorizontalSB (VOID) = 0;
    virtual VOID HorizontalSB (BOOL f) = 0;

    virtual BOOL Tasklist (VOID) = 0;
    virtual VOID Tasklist (BOOL f) = 0;

    virtual BOOL Autohide (VOID) = 0;
    virtual VOID Autohide (BOOL f) = 0;

    virtual BOOL Titlebar (VOID) = 0;
    virtual VOID Titlebar (BOOL f) = 0;

    virtual VOID Changed (BOOL f) { fChanged = f; }
    BOOL Changed (VOID) { BOOL f = fChanged; Changed(FALSE); return f; }

#ifdef _DOFIND_
    virtual BOOL Find( IPT &ipt ) = 0;
    virtual VOID Activate( BOOL find_kludge = FALSE ) {}
#endif

//    NoteDisplayTemplate *Template(VOID) = 0;

protected:
    virtual ~NoteDisplay (VOID) {};

    Note *pn;
    BOOL fChanged;
};

// ************************************************************************
#endif
