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

#include "notelist.h"

USHORT Notelist :: cDown = 0;
Notelist *Notelist :: pnl = NULL;

// ** Notelist ************************************************************ /*fold00*/

Notelist :: Notelist (PSZ psz)
{
    Init();

    FILE *pf;

    // is the notes file actually available for reading?
    if (! access(psz,0)) {
        // the above means "file is accessible" ...
        // though one might think the other way round
        if (! (pf = fopen(psz,"rb"))) {
            DisplayError ("FILE ERROR", "Could not open file \"%s\" "
                          "(errno=%ld).", psz, *_errno ());
            return;
        }
    } else return;

    // check the header so we don't accidently try to read a bad file
    if (! CheckHeader(pf, psz)) {
        fclose(pf);
        return;
    }

    // load all the notes from the file
    while (19)
    {
        BOOL f = getc(pf);  // the marked/unmarked flag
        if (! feof(pf))
        {
            // create a new note from the data from the file
            Note *pn = new Note(pf);
            // add it to the notelist
            Add(pn);
            // mark it if requested
            if (f) { Mark(pn->ID()); }
            // create a notedisplay from the data from the file and
            // give it to note
            pn->Display(*(NoteDisplayFactory::Instance()->New(*pn,pf)));
#ifdef _DEBUGLOG_
            Log("Notelist::Notelist() - red a note\n");
#endif
        }
        else break;
    }

    fclose(pf);
}

// ** CheckHeader ********************************************************* /*fold00*/

BOOL Notelist :: CheckHeader (FILE *pf, PSZ psz)
{
    CHAR    ach[CB_NOTESFILEHEADER];
    USHORT  us;

    fread(ach, 1, sizeof(ach), pf);
    if (strncmp(ach, PSZ_NOTESFILEHEADER, sizeof(ach)) != 0) {
        DisplayError ("WARNING", "The file \"%s\" is either corrupted or "
                      "not a valid Wanda notesfile.", psz);
        return FALSE;
    }

    fread(&us, sizeof(us), 1, pf);
    if (us != NOTESFILEVERSION) {
        DisplayError ("WARNING", "The file \"%s\" is either corrupted, not "
                      "a valid or Wanda notesfile or from an incompatible "
                      "Wanda version.", psz);
        return FALSE;
    }

    return TRUE;
}

// ** New ***************************************************************** /*fold00*/

NID Notelist :: New (VOID)
{
    Note *pn = new Note();
    pn->ID(GetFreeIndex());
    Add(pn);
    pn->Display(*(NoteDisplayFactory::Instance()->New(*pn)));
    return pn->ID();
}

NID Notelist :: NewFromClipboard (VOID)
{
    PSZ  psz;
    Note *pn;

    // get the text from the clipboard and make a note out of it
    WinOpenClipbrd(GETHAB);
    if ((psz = PSZ(WinQueryClipbrdData(GETHAB, CF_TEXT))))
        pn = new Note(psz);
    else
        pn = new Note();
    WinCloseClipbrd(GETHAB);

    pn->ID(GetFreeIndex());
    Add(pn);
    pn->Display(*(NoteDisplayFactory::Instance()->New(*pn)));
    return pn->ID();
}

NID Notelist :: NewFromFile (VOID)
{
    CHAR  ach[_MAX_PATH];
    if (! SelectFile(ach))
        return NID_NIL;

    // open file
    FILE *pf;
    if (! (pf = fopen(ach,"rb")))
    {
        DisplayError ("FILE ERROR", "Could not open file/device \"%s\" "
                      "(errno=%ld).", ach, *_errno ());
        return NID_NIL;
    }

    // get size of file
    fseek(pf, 0, SEEK_END);
    LONG l = ftell(pf);
    if (l > 32*1024)
    {
        DisplayError("FILE TOO BIG", "File is to big! Only the first 32K "
                     "will be loaded.");
        l = 32*1024;
    }
    fseek(pf, 0, SEEK_SET);

    // read file into allocated buffer
    PSZ  psz = PSZ(malloc(l+1));
    fread(psz, 1, l, pf);
    fclose(pf);

    psz[l] = '\0';

    Note *pn = new Note(psz);

    free(psz);

    pn->ID(GetFreeIndex());
    Add(pn);
    pn->Display(*(NoteDisplayFactory::Instance()->New(*pn)));
    return pn->ID();
}

// ** SelectFile ********************************************************** /*fold00*/

BOOL Notelist :: SelectFile (PSZ psz)
{
    FILEDLG  fdlg;

    memset(&fdlg, 0, sizeof(fdlg));

    fdlg.cbSize   = sizeof(fdlg);
    fdlg.fl       = FDS_OPEN_DIALOG | FDS_CENTER;
    fdlg.pszTitle = "Load from file";

    strcpy(fdlg.szFullFile, "*.txt");

    if (WinFileDlg(HWND_DESKTOP, HWND_DESKTOP, &fdlg))
    {
        if (fdlg.lReturn != DID_OK)
            return FALSE;
        strcpy(psz, fdlg.szFullFile);
        return TRUE;
    }

    return FALSE;
}

// ** Index *************************************************************** /*fold00*/

USHORT Notelist :: Index (Note &n)
{
    return Index(n.ID());
    // return pn->ID() ?
    /*        for (USHORT i = 0; i < c; i++)
     if (apn[i] == pn)
     return i;
     return NID_NIL; */
}

// ** Save **************************************************************** /*fold00*/

BOOL Notelist :: Save (PSZ psz)
{
    // we're about to save, so autosave is not necesarry
    StopTimer();

/*    DosBeep(100,50);
    DosBeep(200,50);
    DosBeep(300,50);*/

#ifdef _NOTELISTBACKUP_
    CHAR ach[_MAX_PATH];
    sprintf (ach, "%s.bak", psz);

    unlink(ach);

    if( access( psz, 0 ) == 0 ) {
#ifdef _PARANOID_
    if (
#endif
        rename(psz, ach)
#ifdef _PARANOID_
        != 0)
        DisplayError("RENAME ERROR", "Could not rename file '%s' to '%s' "
                     "(Error %d)", psz, _getname(ach), errno)
#endif
#endif
            ;
    }

    // save notelistdisplay's stuff
    if (pnld) { pnld->Save(); }

    FILE *pf;

    if (! (pf = fopen(psz,"wb")))
        return FALSE;

    // write header and version number
    fwrite(PSZ_NOTESFILEHEADER, CB_NOTESFILEHEADER, 1, pf);
    USHORT us = NOTESFILEVERSION;
    fwrite(&us, sizeof(us), 1, pf);

    for (USHORT i = 0; i < C_MAXNOTES; i++)
        if (apn[i])
        {
            putc(ab[i], pf);
            apn[i]->Save(pf);
        }

    fclose(pf);
    return TRUE;
}

// ** Tick **************************************************************** /*fold00*/

VOID Notelist :: Tick (PVOID)
{
    HMQ   hmq = WinCreateMsgQueue(hab, 0);

    while (pnl) {    // FIXME use of static pnl is ugly
        sleep(1);
        if (cDown) {
            cDown--;
            if (! cDown)
                if (pnl)
                    pnl->Save(PSZ_NOTESFILE);
            // FIXME Save should check if it is "already running"
        }
    }

    WinDestroyMsgQueue(hmq);
}

// ** ForSelected ********************************************************* /*FOLD00*/

LONG Notelist :: ForSelected (USHORT us)
{
    // set mouse-ptr to "wait" shape
/*    HPOINTER   hptr = WinQueryPointer (HWND_DESKTOP);
    WinSetPointer (HWND_DESKTOP, WinQuerySysPointer (HWND_DESKTOP, SPTR_WAIT,
                                                     FALSE));

    ULONG   ul = ULONG (WinSendMsg (hwndLB, LM_QUERYSELECTION,
                                    MPFROMSHORT(LIT_FIRST), NULL)); */
    LONG   c = 0L;
    Note  *pn;
    NoteDisplay  *pnd;
    FILE    *pf = NULL;

    // if print, open file/device
    if (! (pf = pprn->OpenOutput()))
    {
//            WinSetPointer (HWND_DESKTOP, hptr);
        return 0L;
    }

    // do <whatever> for each selected note
    for (ULONG i = 0; i < C_MAXNOTES; i++) {
        if (! (pn = apn[i]))
            continue;
        if (! Marked(pn->ID()))
            continue;
        if (! (pnd = pn->Display()))
            continue;
        c++;

        switch (us)
        {
        case WID_FS_SHOW:         pnd->Hide(FALSE);             break;
        case WID_FS_HIDE:         pnd->Hide(TRUE);              break;

        case WID_FS_CLOSE:        pnd->Close();                 break;

        case WID_FS_WORDWRAPON:   pnd->Wordwrap(TRUE);          break;
        case WID_FS_WORDWRAPOFF:  pnd->Wordwrap(FALSE);         break;

        case WID_FS_VSBON:        pnd->VerticalSB(TRUE);        break;
        case WID_FS_VSBOFF:       pnd->VerticalSB(FALSE);       break;

        case WID_FS_HSBON:        pnd->HorizontalSB(TRUE);      break;
        case WID_FS_HSBOFF:       pnd->HorizontalSB(FALSE);     break;

        case WID_FS_TASKLISTON:   pnd->Tasklist(TRUE);          break;
        case WID_FS_TASKLISTOFF:  pnd->Tasklist(FALSE);         break;

/*        case WID_FS_AUTOSIZEON:   pnd->Autosize (TRUE);  break;
        case WID_FS_AUTOSIZEOFF:   pnd->Autosize (FALSE);  break;*/

        case WID_FS_AUTOHIDEON:   pnd->Autohide(TRUE);          break;
        case WID_FS_AUTOHIDEOFF:  pnd->Autohide(FALSE);         break;

        case WID_FS_TITLEBARON:   pnd->Titlebar(TRUE);          break;
        case WID_FS_TITLEBAROFF:  pnd->Titlebar(FALSE);         break;

        case WID_FS_PRINT:
            pprn->OutputNote(pf, pn);
            break;
        }
    }

end:
    if (pf)
        pprn->CloseOutput(pf);

    // set mouse-ptr to normal shape
/*    WinSetPointer (HWND_DESKTOP, hptr); */

    return c;
}

// ** Display ************************************************************* /*fold00*/

VOID Notelist :: Display (class NotelistDisplay &nld)
{
    // if we've got an old display, delete it now
    if (pnld) { delete pnld; }

    // this is our new display
    pnld = &nld;

    // add all notes in list to the display
    for (USHORT i = 0; i < C_MAXNOTES; i++) {
        if (apn[i])
            pnld->Add(*apn[i]);
        if (MarkedByIndex(i))
            pnld->Mark(apn[i]->ID());
    }
}

#ifdef _DOFIND_

// ** Find ****************************************************************  /*FOLD00*/

BOOL Notelist :: Find( BOOL from_first )
{
    static ULONG i = 0;
    static LONG ipt = 0L;

    // Start searching from beginning of first note?
    if( from_first ) {
        for( i = 0; i < C_MAXNOTES; i++ ) {
            if( ! apn[i] )
                continue;
            if( ! Marked( apn[i]->ID() ) )
                continue;
            if( ! apn[i]->Display() )
                continue;
            break;
        }
        ipt = 0L;
        // Do we have already reached the last note?
        if( i >= C_MAXNOTES ) {
            DosBeep( 1000, 100 );
            DosBeep( 2000, 100 );
            return FALSE;
        }
    }

    /* Search the current note from the current position in the text.
     ipt will get changed! If nothing was found, get next note
     until all notes searched. */
    while( ! apn[i]->pnd->Find( ipt ) )
    {
        // Find the next note.
        for( i += 1; i < C_MAXNOTES; i++ ) {
            if( ! apn[i] )
                continue;
            if( ! Marked( apn[i]->ID() ) )
                continue;
            if( ! apn[i]->Display() )
                continue;
            break;
        }
        // Do we have already reached the last note?
        if( i >= C_MAXNOTES )
        {
            DosBeep( 1000, 100 );
            DosBeep( 2000, 100 );
            DosBeep( 3000, 100 );
            return FALSE;
        }
        ipt = 0L;
    }

    // Show note where text was found.
    apn[i]->Activate();
    return TRUE;
}

// ************************************************************************

#endif
