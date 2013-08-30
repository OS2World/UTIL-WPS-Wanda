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

#define OS2EMX_PLAIN_CHAR
#define INCL_WIN

#include <os2.h>

#include "wanda.h"

#include "note.h"
#include "notelist.h"
#include "nld_fact.h"

HAB  hab;
class Settings  *pset;

NotelistDisplayFactory* NotelistDisplayFactory::pnldf = NULL;
NoteDisplayFactory* NoteDisplayFactory::pndf = NULL;

#include "thth/thth_settings.cpp"

PTHTH_SE apse[] =
{
    new THTH_SEL (SEI_PRINTSTYLE, "Print", "Style", PS_TOFILE),
    new THTH_SES (SEI_PRINTFILENAME, "Print", "Filename", "wanda.txt"),
    new THTH_SEL (SEI_PRINTDEVICE, "Print", "Device", PDEV_PRN),
    new THTH_SEF (SEI_PRINTHEADLINE, "Print", "Headline", TRUE),

    new THTH_SES (SEI_FINDTEXT, "Find", "Text", "Windows"),
    new THTH_SEF (SEI_FINDREPLACE, "Find", "Replace", FALSE),
    new THTH_SES (SEI_FINDREPLACETEXT, "Find", "Replacetext", "OS/2 Warp"),
    new THTH_SEF (SEI_FINDCASESENS, "Find", "CaseSensitive", FALSE),

    new THTH_SEL (SEI_NLDTYPE, "Notelist", "DisplayType", 0),
    new THTH_SEB (SEI_NLDD, "Notelist", "DisplayData", 0, 0),

    new THTH_SES (SEI_NOTESFILE, "Files", "Notes", "wanda.nld"),

    new THTH_SEL (SEI_NDTYPE, "Note", "DisplayType", 0),
    new THTH_SEB (SEI_NDD, "Note", "DisplayData", 0, 0),

    new THTH_SEL (SEI_AUTOSAVEDELAY, "Autosave", "Delay", 10),

    new THTH_SEL (SEI_CONFIRMCLOSE, "Misc", "ConfirmClose", 1),
#ifdef DONLDREMOVETITLE
    new THTH_SEF (SEI_TITLEREMOVED, "Misc", "TitleRemoved", FALSE),
#endif
    NULL,
};

// ** ParseArgs ***********************************************************

VOID ParseArgs (int argc, PSZ argv[])
{
    for (USHORT i = 1; i < argc; i++) {
        if (stricmp (argv[i], "-n") == 0) {
            // have we got another argument? (the filename)
            if (i < argc-1)
                if (argv[i+1][0] != '-') {
                    i++;
                    pset->SetString(SEI_NOTESFILE, argv[i]);
                }
        } else if (stricmp (argv[i], "-a") == 0) {
            // have we got another argument? (the delay)
            if (i < argc-1)
                if (argv[i+1][0] != '-') {
                    i++;
                    pset->SetLong(SEI_AUTOSAVEDELAY, atol(argv[i]));
                }
        } else if (strnicmp (argv[i], "-c", 2) == 0) {
            pset->SetLong(SEI_CONFIRMCLOSE, LONG(argv[i][2] != '-'));
        } else {
            DisplayError("ERROR", "Unknown commandline argument \"%s\". "
                         "Will be ignored.", argv[i]);
        }
    }
}

// ** main **************************************************************** /*FOLD00*/

int main (int argc, PSZ argv[])
{
#ifdef _DEBUGLOG_
    OpenLog("wanda.log");
#endif

    hab = WinInitialize(0);
    HMQ hmq = WinCreateMsgQueue(hab, 0);

    pset = new Settings(apse);
    ParseArgs(argc, argv);

    // loads all notes and stuff ...
    Notelist *pnl = new Notelist(PSZ_NOTESFILE);
#ifdef _DEBUGLOG_
    Log("main()-0\n");
#endif
    pnl->Display(*(NotelistDisplayFactory::Instance()->New(*pnl)));
#ifdef _DEBUGLOG_
    Log("main()-0.1\n");
#endif

    QMSG qmsg;
    while (! pnl->DoClose())
        if (WinGetMsg (hab, &qmsg, 0L, 0, 0))
            WinDispatchMsg (hab, &qmsg);

#ifdef _DEBUGLOG_
    Log("main()-1\n");
#endif

    delete pset;
    delete pnl;

    WinDestroyMsgQueue (hmq);
    WinTerminate (hab);

#ifdef _DEBUGLOG_
    CloseLog();
#endif

    return 0;
}

// ** DisplayError ******************************************************** /*FOLD00*/

VOID DisplayError (PSZ pszTitle, PSZ psz, ...)
{
    CHAR      dstring[401];
    va_list   valst;

    va_start (valst, psz);
    vsnprintf (dstring, 401, psz, valst);
    va_end (valst);

    WinMessageBox (HWND_DESKTOP, WinQueryActiveWindow (HWND_DESKTOP), dstring,
                   pszTitle, 0, MB_OK | MB_ERROR | MB_APPLMODAL | MB_MOVEABLE);
}

// ** SetConditionalCascade *********************************************** /*FOLD00*/

VOID SetConditionalCascade (HWND hwnd, USHORT id, USHORT us)
{
    MENUITEM mi;
    WinSendMsg (hwnd, MM_QUERYITEM, MPFROM2SHORT (id, TRUE), &mi);
    WinSetWindowBits (mi.hwndSubMenu, QWL_STYLE, MS_CONDITIONALCASCADE,
                      MS_CONDITIONALCASCADE);
    WinSendMsg (mi.hwndSubMenu, MM_SETDEFAULTITEMID, MPFROMSHORT (us), NULL);
}

// ************************************************************************
