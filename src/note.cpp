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

#include "note.h"

// ** Changed ************************************************************* /*fold00*/

VOID Note :: Changed (VOID)
{
    pnl->RestartTimer();
}

// ** Note **************************************************************** /*fold00*/

Note :: Note (STRING *pstr, NID nid = NID_NIL)
{
    Init();
    if (pstr)
        this->pstr = strdup(pstr);
    this->nid = nid;
    /*        DisplayError ("DEBUG", "nid='%d', pstr='%s'",
     ID(), this->pstr);*/
}

Note :: Note (FILE *pf)
{
    Init();

    // read the note-id
    fread(&nid, sizeof(nid), 1, pf);

    // read the note's text
    // FIXME since we know it's only a char* ... otherwise: change this!
    ULONG cb;
    fread(PVOID (&cb), sizeof(cb), 1, pf);
    pstr = (STRING *)malloc(cb+1);
    fread(pstr, cb, 1, pf);
    pstr[cb] = '\0';
}

VOID Note :: Init (VOID)
{
    pnl = NULL;
    this->pstr = NULL;
    nid = NID_NIL;
    pnd = NULL;
}

// ** ID ****************************************************************** /*fold00*/

USHORT Note :: ID (VOID) { return nid; }

// ** Headline ************************************************************ /*fold00*/

STRING *Note :: Headline (VOID)
{
    STRING  *str = Text();
    static CHAR  ach[51];
    if (str) {
        strncpy(ach, str, 51);
        ach[50] = '\0';
        strtok(ach, "\n\r");
    } else {
        sprintf(ach, "Note %d", ID());
    }
    if (pnl)
        pnl->Title(ID(), ach);
    return ach;
}

// ** Close *************************************************************** /*fold00*/

VOID Note :: Close (VOID)
{
    if (! pset->QueryLong(SEI_CONFIRMCLOSE)) {
        pnl->Remove(ID());
        return;
    }

#ifdef _DEBUGLOG_
        Log("Note::Close()");
#endif
    if (pnd)
        pnd->Autohide(FALSE);
    if (WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, "Really delete this note?",
                      "ATTENTION", 0,
                      MB_OKCANCEL | MB_QUERY | MB_DEFBUTTON2) == MBID_OK)
    {
#ifdef _PARANOID_
        if (!pnl)
            DisplayError("ERROR","Note::Close() - pnl==NULL");
        else
#endif
            pnl->Remove(ID());
    }
}

// ** Save **************************************************************** /*fold00*/

BOOL Note :: Save (FILE *pf)
{
    // get note id 'n save it
    NID nid = ID();
    fwrite(PVOID(&nid), sizeof(nid), 1, pf);

    // get the note text 'n save it
    STRING *pstr = Text();

    // FIXME since we know it's only a char* ... otherwise: change this!
    if (!pstr)
        pstr = "";

    ULONG cb = strlen(pstr);
    fwrite(PVOID (&cb), sizeof(cb), 1, pf);
    fwrite(pstr, cb, 1, pf);

    // save the display's data - FIXME insert marker for "no display" if !pnd
    if (pnd) pnd->Save(pf);

    return TRUE;
}

// ** Find **************************************************************** /*FOLD00*/

#ifdef _DOFIND_
LONG Find (PSZ pszFind, PSZ pszReplace, LONG l)
{
/*    // FIXME since we know it's only a char* ... otherwise: change this!
    if (l >= strlen(pstr))
        return -1;

    PSZ psz = strstr(pstr+l, pszFind), psz2 = pszFind;

    if (! psz)
        return -1;

    // if replace requested, replace! :-)
    if (pszReplace) {
        // FIXME this is all not very well done ...
        size_t cb = strlen(pstr)-strlen(pszFind)+strlen(pszReplace);
        if (! (psz2 = (STRING *) malloc(cb)))
            return -1;
        *psz = '\0';

        // construct the new notetext
        strcpy(psz2, pstr);
        strcat(psz2, pszReplace);
        strcat(psz2, psz+strlen(pszFind));

        Text(psz2);
        psz2 = pszReplace;
    }

    // mark the found/replaced string in the notedisplay
    if (pnd)
//        pnd->Mark(psz2, l);

    return LONG(psz-pstr); */
}
#endif

// ** Text **************************************************************** /*fold00*/

VOID Note :: UpdateText (VOID)
{
    if (pnd) {
        if (pnd->Changed()) {
            if (! pnd->Hide()) {
                STRING *pstr2 = pnd->Text();
                if (pstr2) {
                    RawText(pstr2);
                    delete pstr2;
                }
            }
        }
    }
}

STRING *Note :: Text (VOID)
{
    // performance kluge because we don't want to update the note's
    // text everytime the user enters or changes something in the
    // note's display (which is the main input device normally)
    UpdateText();
    return RawText();
}

VOID Note :: Text (STRING *pstr)
{
    RawText(pstr);
    if (pnd) { pnd->Text (pstr); }
    Changed();
}

// ** Text ****************************************************************

VOID Note :: Display (NoteDisplay &nd)
{
    if (pnd) {
        // same reason as above
        STRING *pstr2 = pnd->Text();
        RawText(pstr2);
        delete pstr2;
        delete pnd;
        pnd = NULL;
    }
    // init the new display
    nd.Text(Text());
    pnd = &nd;
    // ... and maybe some other stuff with time
    Changed();
}

