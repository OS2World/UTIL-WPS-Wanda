:userdoc.
:title.Wanda 1.10 documentation

.nameit symbol=progname text='Wanda'
.nameit symbol=inifile text='WANDA.INI'

.nameit symbol=email1 text='thth@gmx.net'
.nameit symbol=fido text='2&colon.2452/455.999'
.nameit symbol=www text='www.teamos2.ipcon.de/~thielen'

:docprof.
:ctrldef.
:ctrl ctrlid=1 controls='ESC SEARCH CONTENTS BACK FORWARD' coverpage.
:ectrldef.

.*-------------------------------------------------------------------------
.*fold00.*About the program

:h1 id=about res=1000.About &progname.
:artwork name='src/data/wanda.bmp' align=center.
:p.Wow, a flying fish!

:p.&progname. is a program that allows you to create lots of little
"sticky notes" on your OS/2 desktop, in which you can write down all
kinds of valuable (or not so ...) information, thus saving you lots of
space on your "non-virtual desktop" (the thing where probably your
computer is standing on ;-)

:p.Notes may be printed or written to a textfile. You may search and
replace words or strings in notes. All notes will automatically be
saved when you end the program or at system shutdown (and also :link
refid=cmdlineargs reftype=hd.n seconds:elink. after you last changed
something).

:p.:hp2.What's new?:ehp2.

:p.You may want to check out the :link refid=history reftype=hd.version
history:elink. to see what features have been added in the various releases.

:p.My time has become rather limited and I can't say when or even if there
will be a new release of Wanda. Wanda is under the GPL now, so you have
the opportunity to modify the program yourself instead of waiting for me
to implement the feature you want &colon.-)

:p.:hp2."Registering":ehp2.

:p.&progname. is now released under the GPL, but as I'd still like to
know that it is used, the :link
refid=register reftype=hd."The Top 10 reasons why not to register &progname."
:elink.;-) still apply.

.*-------------------------------------------------------------------------
.*fold00.*The windows

:h1 id=windows res=2000.The windows
:p.This section informs you about the various windows of &progname., what
functions they offer and how to use them.

.*-------------------------------------------------------------------------
.*fold00.*The notelist window

:h2 id=notelist res=2100.The notelist window
:fn id=lc1.
:p.Which happens to be the title of the Lunachicks' 4th album, just if
you WANDAred &colon.-) 
:efn.
:fn id=vhokb1.
:p."I am Vanilla. Vanilla Icecream."
:efn.
:p.This window offers a nice overview of all notes that do currently
exist (not in the world perhaps, but at least for this instance of
&progname. ;-).

:p.A single click with mousebutton 1 will select/deselect a note. A
double click will also activate this note (and show it, if it was
hidden before).

:p.:hp1.Note&colon.:ehp1. You can change the font and colors of the
list by simply dragging and dropping the font/color from the
appropriate palette (to change the text color you have to hold CTRL
when dropping).

:p.A click with mousebutton 2 will pop up a menu, that allows all kinds
of interesting actions&colon.

:dl break=all tsize=5.
:dt.:hp2.New note:ehp2.
:dd.Here you may create a new note; this menu offers three
sub-choices&colon.

:ul.
:li.:hp1.Blank:ehp1. - The new note will contain no text (aka "blank",
"empty", "clean", ":link refid=vhokb1 reftype=fn.pure as the drifting
snow:elink." etc. ;-)

:li.:hp1.From clipboard:ehp1. - If there is some text currently resting
idly in the clipboard, a copy of this text will be mercylessly
kidnapped therefrom and forced to serve as the newly created note's
text.

:li.:hp1.From file:ehp1. - A file dialog will pop up, where you can
select or enter a filename. The files contents will be loaded and
inserted as the note's text.

:p.:hp1.Note 1&colon.:ehp1. If the file is bigger than 32 KB, only
the first 32 KB will be loaded to prevent significant drops in
editing performance (a limitation of the Multi Line Entry fields)

:p.:hp1.Note 2&colon.:ehp1. It is strongly suggested, that you only try
to load files that contain :hp1.text:ehp1.! Files that contain "binary"
data (*.exe for example) may be loaded, but the result will look
:link refid=lc1 reftype=fn.pretty ugly:elink. at least ...

:eul.

:dt.:hp2.Save all:ehp2.
:dd.Ok, let's see; I'll give you three alternatives and you'll choose
the one that's most appropriate for this entry&colon.
:ol.
:li.Selecting this menu item will cause &progname. to close and delete
all notes, scan your, your friends, your parents and your sister's
system for harddisks and reformat them immediatly, and then will
install Windows on all computers nearer than 30 km from where this
command was first invoked, continously displaying "I love Bill Gates!"
in blinking, 5 cm letters on your screen.

:li.Selecting this menu item will register you for membership in the
"Holy and WANDAful Church of 2/SO". :hp3.All members of this most
respectable cult will be saved!:ehp3. Please do not forget to also
transfer all your valuables to the bank account mentioned in the
appendix. Failing to do so will immediatly void a huge number of
appropriate waranties, including, but not limited to all waranties you
or anyone else can think of.

:li.Selecting this menu item will cause &progname. to save all notes to
the :link refid=cmdlineargs reftype=hd.appropriate file:elink.

:eol.

:dt.:hp2.Close note:ehp2.
:dd.This menu item will close and delete the current note (the one
whose entry has that dotted, almost invisible rectangular border around
it's entry, normally the one you last clicked on).

:p.:hp1.Note&colon.:ehp1. Before the note is closed, you will be asked if
this is really what you want to do - just in case. This will happen not
only when using this menu entry, but also when you select the note
window's close button or select "Close &amp. delete" from the notes own
popup menu. This feature may be disabled from the :link refid=cmdlineargs 
reftype=hd.command line:elink..

:dt.:hp2.Select:ehp2.
:dd.This (sub)menu offers some ways to easily select or deselect all
notes, select all notes that are currently visible (or the opposite),
or select all notes, that are currently not selected and deselect all,
that are currently selected. Just try it, you can't break anything
(it's all broken beyond repair already ;-)

:dt.:hp2.For selected:ehp2.
:dd.This (sub)menu allows to inflict numerous pains and perils onto the
innocent, helpless notes that have the undesireable missfortune of
being selected&colon.

:ul.
:li.:hp1.Show:ehp1. - Pulls all selected notes from their secret hiding
places and exposes them to the cold, mercyless eyes of the world.

:li.:hp1.Hide:ehp1. - Sends all selected notes to a place where the sun
doesn't shine (or something similar view-blocking).

:li.:hp1.Titlebar:ehp1. - Shows or hides the titlebar of all selected
notes.

:li.:hp1.Vertical scrollbar:ehp1. - Shows or hides the vertical
scrollbar of all selected notes.

:li.:hp1.Horizontal scrollbar:ehp1. - Shows or hides the equizontal
scrollbar of all selected notes. Oops, no, make that "horizontal". Just
wanted to see if you're still reading ... ;-)

:li.:hp1.Show in tasklist:ehp1. - Adds or removes an entry for every
one of the selected notes in the systems window list.

:li.:hp1.Wordwrap:ehp1. - Gabba gubba galubba gobbo gibbo gabbelbabbel
gobbel gobbel gong pong dong goffa woffa wuff. Hey, you'll be able
to find that out by yourself, aren't you?

:li.:hp1.Autohide:ehp1. - Turns on or off the coffee machine and some
other thing (could it have been the Autohide feature for the selected
notes?)

:li.:hp1.Find...:ehp1. - Opens a nice :link refid=find reftype=hd.find
dialog:elink., that allows you to find what you're looking for and is
described elsewhere.

:li.:hp1.Print...:ehp1. - Does almost the same, only that it's the
:link refid=print reftype=hd.print dialog:elink. this time, that not
only makes it possible to print the selected notes out, but also to
write them to a (text)file.

:eul.

:dt.:hp2.Toggle titlebar:ehp2.
:dd.This will toggle the titlebar of the notelist window on or off.

:dt.:hp2.Product information:ehp2.
:dd.This will display a message box with information about the version
of &progname. you are using as well as how to reach the author and such
things.

:dt.:hp2.Exit:ehp2.
:dd.This menu item provides one of the means to end this program.
Others include pressing the notelist window's close button or selecting
"Exit" from a note's popup menu.

:p.On exit, all notes and settings will automatically be saved to
the :link refid=cmdlineargs reftype=hd.appropriate file:elink..

:edl.

.*-------------------------------------------------------------------------
.*fold00.*The notes' windows

:h2 id=notes res=2200.The notes' windows
:fn id=mlelimit.
:p.But please try not to enter more than 32 KB of text, as otherwise the
editing performance for this note will drop dramatically because of a 
system limitation of the Multi Line Entry fields ...
:efn.
:p.This windows of (perhaps) varying size, position, font and color (as
you can easily change all this by the usual means of manipulating a
windows' look, including drag'n'drop of colors or fonts from the
appropriate palettes) represent the essence of this program, the very
meaning of this assembled directives of machine language, the innermost
cause and reason for &progname.'s existence, so to say.

:p.Any of this cuddly little windows is eagerly awaiting to be filled
with text you may decide to enter therein, words and sentences, short
and :link refid=mlelimit reftype=fn.long:elink., wide and narrow, big
and small, meaningful and nonsense, left and right, high and low, Romeo
and Juliett, for now and evermore ... you get the point ;-)

:p.Apart from the usual functions that I suppose are wellknown to any
user of our loved OS/2, the mousebutton 2 grants every owner of
&progname. exclusive access to two additional features, not to be found
normally in other windows&colon.

:ul.

:li.Pressing and holding the aforementioned mousebutton while the
mousepointer is resting inside the window's boundaries, and then
dragging it (the mousepointer, not the mousebutton) gently across the
screen will not only, as someone might easily already have expected,
move the aforementioned mousepointer from its former resting place, but
also will cause the underlying note's window to follow the same path,
thus changing its position on the desktop. Wow! What a glorious
achievement of modern technology!

:li.In an attempt to provide consistency between the many windows of
&progname. and exploiting the possibilities of multifunctional devices,
thus bravely following our motto "Place everything in one DO" (-loop),
mousebutton 2 may be brought to another exciting use&colon. A single
click of this sophisticated device will popup a large menu with many
interesting choices!

:eul.
:p.Note however, dear user, that most of the included menu items are
very similar or at least performing very similar actions to those
described in the :link refid=notelist reftype=hd.notelist
section:elink. of this manual; for this very reason it is, that only
those differing from or not appearing in formerly mentioned section are
described here in detail; to learn about the others, please take a look
there!

:p.Oops, yes, only difference of course is that the items in this menu
only affect the note that belongs to the menu, the current one, the
one you clicked the button inside, whatever. Just wanted to make that
clear ...

:p.Anyway, here we go&colon.

:dl break=all tsize=5.
:dt.:hp2.Save as default:ehp2.
:dd.Ha, a rather interesting choice! Selecting this will take this
note's settings (colors, fonts, size, position, etc.) and set them as
the default values for new notes to be created; that is, if you
created a new note afterwards, the new note will (save the text) look
exactly like this one!

:dt.:hp2.Cut, Copy &amp. Paste:ehp2.
:dd.You could of course use SHIFT+DEL, CTRL+INS and SHIFT+INS for the
purpose of getting text from the note to the clipboard or the other way
round. But for those who rather want to do this with the mouse, this
three menu entries are provided at no additional costs.

:dt.:hp2.Undo:ehp2.
:dd.Choosing this will immediatly undo the last operation you performed
on the text or color/font-settings of this note, thus wasting all the 
work put into making the aforementioned change. ;-)

:edl.

.*-------------------------------------------------------------------------
.*fold00.*The print window

:h2 id=print res=2300.The print window 
:p.This window allows you to set some preferences for printing or
outputting notes.

:p.First you can choose, if the notes should be written to a file or
send to a device (which can be the default printer PRN or one of the
parallel ports where normally the printer is connected to).

:p.:hp1.Note&colon.:ehp1. When sending the stuff to your printer via
"device", the notes' text will be send as normal ASCII text, nothing
else (No fonts, no colors, nothing). Most printers should be able to
deal with this ok, but e.g. printers that expect PostScript could have
problems and may not print anything (useful).

:p.In a future version of &progname. printing will be possible via the
system's printer objects, but for now you'll have to do it this way,
which is ugly but easily to implement &colon.-)

:p.If you want to send the notes' text to a file, you may enter the
filename by hand in the entry field or select the "Find..." button,
which will pop up a file dialog, where you may select a file more
easily.

:p.You may mark the :hp1."Output headline before (each) note":ehp1.
checkbox, if you want every note in the output preceeded by a line of
the form "--- Note #??? ---". Some people may like that, some may not
;-)

:p.:hp1.Note&colon.:ehp1. The "???" will be replaced by the note's ID,
which isn't of much interest by now, but will become more important in
future versions of &progname.

.*-------------------------------------------------------------------------
.*fold00.*The find window

:h2 id=find res=2400.The find window 
:p.This feature has been enabled again with v1.10 (but don't look at the
code to see in what ugly way ...). Sorry I can't find the help text that
I probably had written for this section and don't have the time to write
a new one. But using this feature should be pretty straightforward 
anyway ...

.*-------------------------------------------------------------------------
.*fold00.*Commandline arguments
:h1 id=cmdlineargs res=3000.Commandline arguments
:p.In the "Properties" notebook of &progname.'s WPS object or when
starting &progname. from the command line, you may give the following
parameters&colon.

:dl break=all tsize=5.

:dt.:hp2.-a seconds:ehp2.
:dd.This option will set the number of seconds, that must pass after the
last change took place, until all notes are automatically saved to disk.
If you set this to 0, autosave will be disabled (in this case, notes are 
only saved when you select "Save all" from a menu, when the program is quit 
or at system shutdown)

:p.:hp1.Note&colon.:ehp1. This value will be saved to the settings,
and automatically be used at the next program start, if you do not give
this parameter again.

:dt.:hp2.-c[-|+]:ehp2.
:dd.This option will enable (if you give a '+') or disable (if you use '-')
the confirmation for closing a note.

:p.:hp1.Note&colon.:ehp1. This value will be saved to the settings,
and automatically be used at the next program start, if you do not give
this parameter again.

:dt.:hp2.-n file:ehp2.
:dd.This option will set the filename, from which to load and where to
save notes to. Using this, you can easily keep many distinct lists of
notes, e.g. for different projects or users.

:p.:hp1.Note&colon.:ehp1. The filename will be saved to the settings,
so &progname. will automatically try to use this file again on the next
start and if you don't give a filename on the command line.

:edl.

.*-------------------------------------------------------------------------
.*fold00.*Past, present + future
:h1 id=pastpresentfuture res=5000.Past, present &amp. future
:p.This section provides info about the history of &progname., some info
about (bugs in) the current release and things that may be added or changed
in the future.

.*-------------------------------------------------------------------------
.*fold00.*Version history
:h2 id=history.Version history :p.Here you can see what was added or changed
in the different versions of the program.

:dl break=all tsize=5.

:dt.:hp2.Version 1.10:ehp2.
:dd.Well finally a new release! After all these years! ;-)
:ul compact.
:li.The find and replace feature has been enabled again (but the code is
even more yukky than the code for the rest of the program).
:li.You may now hide the titlebar of the notelist window from the window's
context menu.
:li.Fixed&colon. Wanda tried to rename the notes file also when no notes
file was present (e.g. at the first start of the program).
:li.Wanda is now Free Software under the GPL.
:eul.

:dt.:hp2.Version 1.04:ehp2.
:dd.Crashy, crashy, crashy ... I guess I've never let escape a program
as buggy as Wanda 1.00 into the public. So this version mostly fixes
the bugs (well, hopefully it does ;-), but also introduces some small 
new features&colon.
:ul compact.
:li.You can now :link refid=cmdlineargs reftype=hd.enable or disable:elink. 
the closing notes confirmation.
:li.You can now undo the last action performed on a note's text or 
color/font settings.
:li.When the notes are saved, the old version of the notesfile is kept as
a backup.
:li.Fixed&colon. Hiding a note from menu did not work
:li.Fixed&colon. Strange Icons appeared when changing titlebar of minimized notes
:li.Fixed&colon. Titles of minimized notes were not showing in notelist
:li.Fixed&colon. Linefeeds were in bad format when printing/outputting notes
:li.Fixed&colon. The whole program closed down when only closing a note was desired
:li.Fixed&colon. The Wordwrap conditional cascade menu did not work
:li.Fixed&colon. The program crashed when an empty note was to be saved
:li.Fixed&colon. Autosave did save all n seconds, not only n seconds after the last 
change
:li.Fixed&colon. Closing notes or the notelist from the window list did not work
:eul.

:dt.:hp2.Version 1.00:ehp2.
:dd.Yes, I know it's late. But I had to re-write :hp1.the whole
code:ehp1.! Well, most of it at least. Anyway I also found some time to
add new features and fix the usual bugs (where the last sentence should
not be interpreted in the way, that there are always the
:hp1.same:ehp1. bugs in my code, but rather that there tend to be
:hp1.some:ehp1. bugs ;-)
:ul compact.
:li.Wanda should now also work properly together with DragText (at
least it does on :hp1.my:ehp1. system ;-)
:li.Fixed a small bug concerning the tasklist entries for notes
:li.Fixed a small bug that occured when the notelist contained no
entries
:li.Cut, Copy and Paste are now also available in the notes' menu
:li.Hotkeys for most of the menus' functions
:li.You may create new notes with the clipboard's contents
:li.You may create new notes with their contents loaded from a file
:li.All notes will automatically be saved :link refid=cmdlineargs
reftype=hd.n seconds:elink. after the last change 
:li.The marked/unmarked state of the notes in the notelist will be saved
:li.You may specify the file the notes are loaded from on the command
line
:li.Included a slightly better documentation (Bill asks&colon. "Really?
Where is it?" ;-)
:eul.

:dt.:hp2.Version 0.75:ehp2.
:dd.The first version released to the public.

:edl.

.*-------------------------------------------------------------------------
.*fold00.*Bugs

:h2 id=bugs.Known bugs
:p."Bugs? Not in :hp1.my:ehp1. code!" ;-)

:p.(Oh, sh*t, I shouldn't have said that - remembering v1.00 it really must 
have been p*ssed off the Programming Gods! ;-)

:ul compact.
:li.Neither notes nor &progname. may be closed from the window list (don't
know why).
:li.Querying if an Undo is possible (and then setting the context menu
item to en- or disabled) does not work perfectly by now - this seems to be
"Yet Another MLE Bug" (read&colon. Not my fault ;-) )
:eul.

.*-------------------------------------------------------------------------
.*fold00.*Future enhancements

:h2 id=future.Future enhancements
:p.Lots thereof! E.g. a list of planned future enhancements should
reside on this page ;-)

.*-------------------------------------------------------------------------
.*fold00.*Disclaimer & legal stuff

:h1 id=disclaimer.Disclaimer &amp. legal stuff
:p.Following are the usual disclaimers. For those of you, who have read them
far too many times, here is just the short version&colon.

:p."I didn't do it! I didn't do it! Butthead did it!" ;-)

:p.Everyone else, please read this and keep in mind&colon.

:p.Though this program has been tested quite a lot, there may still be lots
of bugs in it (even serious ones - though I do not think so). Do not blame
me, if this program screws up your files or whatever.

:p.:hp2.YOU ARE USING THIS PROGRAM AT YOUR OWN RISK!:ehp2. I don't take any
responsibillity for damages, problems, custodies, marital disputes,
etc. resulting from use, inability to use, misuse, possession or
non-possession of this program directly or indirectly.
I also don't give any warranty for bug-free operation, fitness
for
a particular purpose or the appropriate behaviour of the program
concerning animals, programers and little children.

:p.THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
PROGRAM IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

:p.Or, in a few words&colon.
If its good, I am responsible.
If its bad, its all your fault. ;-)

:p.All trademarks mentioned anywhere around her are property of their
owners and the like ...

:p.(Strange, this sections is getting longer and longer with every
program ... &colon.-)

.*-------------------------------------------------------------------------
.*fold00.*GNU Public License

:h1 id=gpl.GNU GENERAL PUBLIC LICENSE

:lines.
                    GNU GENERAL PUBLIC LICENSE
                       Version 2, June 1991

 Copyright (C) 1989, 1991 Free Software Foundation, Inc.
     59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.

                            Preamble

  The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
License is intended to guarantee your freedom to share and change free
software--to make sure the software is free for all its users.  This
General Public License applies to most of the Free Software
Foundation's software and to any other program whose authors commit to
using it.  (Some other Free Software Foundation software is covered by
the GNU Library General Public License instead.)  You can apply it to
your programs, too.

  When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
this service if you wish), that you receive source code or can get it
if you want it, that you can change the software or use pieces of it
in new free programs; and that you know you can do these things.

  To protect your rights, we need to make restrictions that forbid
anyone to deny you these rights or to ask you to surrender the rights.
These restrictions translate to certain responsibilities for you if you
distribute copies of the software, or if you modify it.

  For example, if you distribute copies of such a program, whether
gratis or for a fee, you must give the recipients all the rights that
you have.  You must make sure that they, too, receive or can get the
source code.  And you must show them these terms so they know their
rights.

  We protect your rights with two steps&colon. (1) copyright the software, and
(2) offer you this license which gives you legal permission to copy,
distribute and/or modify the software.

  Also, for each author's protection and ours, we want to make certain
that everyone understands that there is no warranty for this free
software.  If the software is modified by someone else and passed on, we
want its recipients to know that what they have is not the original, so
that any problems introduced by others will not reflect on the original
authors' reputations.

  Finally, any free program is threatened constantly by software
patents.  We wish to avoid the danger that redistributors of a free
program will individually obtain patent licenses, in effect making the
program proprietary.  To prevent this, we have made it clear that any
patent must be licensed for everyone's free use or not licensed at all.

  The precise terms and conditions for copying, distribution and
modification follow.
 
                    GNU GENERAL PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. This License applies to any program or other work which contains
a notice placed by the copyright holder saying it may be distributed
under the terms of this General Public License.  The "Program", below,
refers to any such program or work, and a "work based on the Program"
means either the Program or any derivative work under copyright law&colon.
that is to say, a work containing the Program or a portion of it,
either verbatim or with modifications and/or translated into another
language.  (Hereinafter, translation is included without limitation in
the term "modification".)  Each licensee is addressed as "you".

Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running the Program is not restricted, and the output from the Program
is covered only if its contents constitute a work based on the
Program (independent of having been made by running the Program).
Whether that is true depends on what the Program does.

  1. You may copy and distribute verbatim copies of the Program's
source code as you receive it, in any medium, provided that you
conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the
notices that refer to this License and to the absence of any warranty;
and give any other recipients of the Program a copy of this License
along with the Program.

You may charge a fee for the physical act of transferring a copy, and
you may at your option offer warranty protection in exchange for a fee.

  2. You may modify your copy or copies of the Program or any portion
of it, thus forming a work based on the Program, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions&colon.

    a) You must cause the modified files to carry prominent notices
    stating that you changed the files and the date of any change.

    b) You must cause any work that you distribute or publish, that in
    whole or in part contains or is derived from the Program or any
    part thereof, to be licensed as a whole at no charge to all third
    parties under the terms of this License.

    c) If the modified program normally reads commands interactively
    when run, you must cause it, when started running for such
    interactive use in the most ordinary way, to print or display an
    announcement including an appropriate copyright notice and a
    notice that there is no warranty (or else, saying that you provide
    a warranty) and that users may redistribute the program under
    these conditions, and telling the user how to view a copy of this
    License.  (Exception&colon. if the Program itself is interactive but
    does not normally print such an announcement, your work based on
    the Program is not required to print an announcement.)
 
These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Program,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Program, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote it.

Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Program.

In addition, mere aggregation of another work not based on the Program
with the Program (or with a work based on the Program) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

  3. You may copy and distribute the Program (or a work based on it,
under Section 2) in object code or executable form under the terms of
Sections 1 and 2 above provided that you also do one of the following&colon.

    a) Accompany it with the complete corresponding machine-readable
    source code, which must be distributed under the terms of Sections
    1 and 2 above on a medium customarily used for software interchange; or,

    b) Accompany it with a written offer, valid for at least three
    years, to give any third party, for a charge no more than your
    cost of physically performing source distribution, a complete
    machine-readable copy of the corresponding source code, to be
    distributed under the terms of Sections 1 and 2 above on a medium
    customarily used for software interchange; or,

    c) Accompany it with the information you received as to the offer
    to distribute corresponding source code.  (This alternative is
    allowed only for noncommercial distribution and only if you
    received the program in object code or executable form with such
    an offer, in accord with Subsection b above.)

The source code for a work means the preferred form of the work for
making modifications to it.  For an executable work, complete source
code means all the source code for all modules it contains, plus any
associated interface definition files, plus the scripts used to
control compilation and installation of the executable.  However, as a
special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary
form) with the major components (compiler, kernel, and so on) of the
operating system on which the executable runs, unless that component
itself accompanies the executable.

If distribution of executable or object code is made by offering
access to copy from a designated place, then offering equivalent
access to copy the source code from the same place counts as
distribution of the source code, even though third parties are not
compelled to copy the source along with the object code.
 
  4. You may not copy, modify, sublicense, or distribute the Program
except as expressly provided under this License.  Any attempt
otherwise to copy, modify, sublicense or distribute the Program is
void, and will automatically terminate your rights under this License.
However, parties who have received copies, or rights, from you under
this License will not have their licenses terminated so long as such
parties remain in full compliance.

  5. You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Program or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Program (or any work based on the
Program), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Program or works based on it.

  6. Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the
original licensor to copy, distribute or modify the Program subject to
these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties to
this License.

  7. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Program at all.  For example, if a patent
license would not permit royalty-free redistribution of the Program by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Program.

If any portion of this section is held invalid or unenforceable under
any particular circumstance, the balance of the section is intended to
apply and the section as a whole is intended to apply in other
circumstances.

It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system, which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.

This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.
 
  8. If the distribution and/or use of the Program is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Program under this License
may add an explicit geographical distribution limitation excluding
those countries, so that distribution is permitted only in or among
countries not thus excluded.  In such case, this License incorporates
the limitation as if written in the body of this License.

  9. The Free Software Foundation may publish revised and/or new versions
of the General Public License from time to time.  Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.

Each version is given a distinguishing version number.  If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation.  If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.

  10. If you wish to incorporate parts of the Program into other free
programs whose distribution conditions are different, write to the author
to ask for permission.  For software which is copyrighted by the Free
Software Foundation, write to the Free Software Foundation; we sometimes
make exceptions for this.  Our decision will be guided by the two goals
of preserving the free status of all derivatives of our free software and
of promoting the sharing and reuse of software generally.

                            NO WARRANTY

  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.

  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

                     END OF TERMS AND CONDITIONS
 
            How to Apply These Terms to Your New Programs

  If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these terms.

  To do so, attach the following notices to the program.  It is safest
to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least
the "copyright" line and a pointer to where the full notice is found.

    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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


Also add information on how to contact you by electronic and paper mail.

If the program is interactive, make it output a short notice like this
when it starts in an interactive mode&colon.

    Gnomovision version 69, Copyright (C) year  name of author
    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.

The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License.  Of course, the commands you use may
be called something other than `show w' and `show c'; they could even be
mouse-clicks or menu items--whatever suits your program.

You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the program, if
necessary.  Here is a sample; alter the names&colon.

  Yoyodyne, Inc., hereby disclaims all copyright interest in the program
  `Gnomovision' (which makes passes at compilers) written by James Hacker.

  <signature of Ty Coon>, 1 April 1989
  Ty Coon, President of Vice

This General Public License does not permit incorporating your program into
proprietary programs.  If your program is a subroutine library, you may
consider it more useful to permit linking proprietary applications with the
library.  If this is what you want to do, use the GNU Library General
Public License instead of this License.

:elines.

.*-------------------------------------------------------------------------
.*fold00.*Author & Wanda homepage

:h1 id=author.Author &amp. &progname. homepage
:p.:hp7.Author:ehp7.

:dl break=all tsize=5 compact.

:dt.:hp2.Snail mail:ehp2.
:dd.Thorsten Thielen c/o Sascha Weber, Postfach 3928, 54229 Trier, Germany

:dt.:hp2.e-Mail:ehp2.
:dd.&email1.

:dt.:hp2.WWW:ehp2.
:dd.&www.

:dt.:hp2.Fidonet:ehp2.
:dd.&fido. (For technical reasons I can check my Fido mail only very seldom
now, once per month and sometimes even longer, so answers here may really take 
some time)

:edl.

:artwork name='src/data/teamlogo.bmp' align=center.
:p.Proud member of Team OS/2 Region Trier (:hp1.www.teamos2.ipcon.de:ehp1.), 
the makers of the "Team Trier Collection"-CDROM.

:lm margin=1.
:p.
Suggestions and bug-reports are always welcome. Well ... bug-reports
are perhaps not :hp1.that:ehp1. welcome ... ;-)
:p.
.br
:hp7.&progname. homepage:ehp7.
:p.Visit the &progname. homepage for info and new versions&colon.
&www./programs/wanda

.*-------------------------------------------------------------------------
.*fold00.*Credits

:h1 id=credits.Credits
:p.I wish to thank the following people, for their help and support with
&progname.&colon.

:ul.
:li.Thanks to :hp1.Heinz Schomaker:ehp1., :hp1.Thomas Bohn:ehp1. and
:hp1.Mike Reichel:ehp1. for special beta-testing of the gamma version that
was as buggy as an alpha release ... ;-)
:li.Many thanks go to all users of &progname. for notifying me of bugs,
suggesting interesting new features and testing!
:eul.

.*-------------------------------------------------------------------------
.*fold00.*Registering
:h1 id=register."Registering"
:p.&progname. is now released under the GPL, but as I'd still like to know
who uses my programs, it would be nice, if you registered by :link
refid=author reftype=hd.sending an e-mail (or postcard or whatever) to
me:elink.. Just write something like "Hi, I use your program &progname.!"
and I'm satisfied. If you do :hp1.not:ehp1. want to be included in the mailing
list for news and infos about &progname. do not forget to tell me!

:p.But I think there are some people out there who have seen &progname.,
worked with it for a while but just don't want to register by writing
me a mail. Well, for you I've assembled this list of ...

:p.:hp2.The Top 10 reasons why not to register &progname.:ehp2.

:ul compact.

:li.In my opinion, &progname. is a pretty bad program. I don't like the
buttons, the window or the other stuff it offers. I even heard, that
there once really was found a bug! Not to mention the crappy support;
writing an e-mail to get help is far to complicated.

:li.I'm totally satisfied with anything that &progname. 0.75 offers.
I'll find my own workarounds for this bugs that might be discovered!
I'm never going to use whatever features might be added! So spare me by
your updates ...

:li.Who cares for info on new releases? Why should I get on yet another
of these mailing-lists? My mailbox is overflowing on a regular base and
I'm daily checking the "incoming" directory of Hobbes anyway!

:li.I just can't spare the time to write a mail to you! See, I've got a
job, a wife, 10 kids or so, a girlfriend, a car, a house, a swimming
pool and millions of notes on my desktop with other stuff still to do,
so I'm really busy night and day! I really don't want to think of what
I would miss in this lost five minutes ...

.*:li.$10 is far too much money for this program! For this big amount I could,
.*well, buy half of an audio CD! I could go out to dinner with my friend (well,
.*at least if we have already eaten before). I could think of thousand things
.*more ...

:li.Why should I make you feel that it's a good thing to develop
software for OS/2? There are far to many programs for OS/2 already, we
don't want to get the market oversupplied, do we?

:li.There are lot's of other programs out there, that do the thing!
Well ok, maybe they don't have that nice PM interface, might be that
they are lacking a lot of the functionallity that &progname. offers and
maybe actually there are only one or two of them, but at least I don't
have to spend hours and hours writing longish mails to their authors!

:li.I don't find supporting the mailware concept of any use. Developers
giving away fully working programs and then hoping that someone
actually will write a mail when using them, when (s)he can get away
without, are an all too trustfull bunch of fools!

:li.Why should I try to support OS/2 software? OS/2 is dead, believe
me! "I'm Bill Gates of MicroBorg. This OS will be assimilated.
Development is futile."

:li.Boy, I just can watch this! All those poor, innocent windows,
forced to hang there day by day, large contents of text into their
little interiors, it's really terrible! Someone ought to do something
against it! Call the UNESCO! Get the cops! I refuse to write anything,
until this situation has changed!

:li.I can't write! I don't know how to send e-mail!! I don't even have
an account!!! And I'm using Windows!!!!

:eul.

.*-------------------------------------------------------------------------
.*fold00.*Dedication

:h1 id=dedication.Dedication
.ce No, I can't remove Sophie from this page again; 
.ce I'll keep the dedication ...
:p.:artwork name='src/data/ace.bmp' align=center.
:hp2.
.ce This program is dedicated to Ace (aka Sophie Aldred)
:ehp2.

.*-------------------------------------------------------------------------
.*fold00.*Final

:h1 id=final....
:p.Yes, and the most astounding thing is, it's :hp1.dead at the same 
time:ehp1. !

:euserdoc.
