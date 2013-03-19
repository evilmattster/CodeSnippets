Creating text based adventure games is made simple by this lovely tool, just follow these guidlines.


[INTRO] -> [END_INTRO]
This is the text describing what is going on in your room.  The command [PAUSE] can be used to break
the text into manageable segments.  The [PAUSE] command will also clear the screen for you, but can 
only be used between the [INTRO] and [END_INTRO] tags.


[MENU] -> [END_MENU]
This is a required tag to have in your file.  Even if you don't want to use menus, just include the 
tags with nothing inbetween.  These tags allow you to add <OPTION> -> <END_OPT> objects to your room.
They are automatically numbered lists, and the numbers by the options corrispond to the position of
each command that needs to be carried out in the [RESOLVE] -> [END_RES] vector.


[COMMAND] -> [END_CMD]
These are much like the [MENU] -> [END_MENU] tags, however they are not displayed on the screen and
can have many commands to a single action.  This is handy for things such as the difference between
'walk north', 'go north', 'head north' etc.  Also spacing and capitalization are ignored for these 
commands.  The syntax for a list of equvilent commands is a comma separated vector. eg 
<go north, walknorth, HEADnorth>.  These also corrispond to positions in the [RESOLVE] tag, but they
go AFTER the menu Items.


[RESOLVE] -> [END_RES]
This tag is used to resolve the commands given in lists and command tags.  It is a vector or commands
to be carried out.  The commands currently supported are:
 <EXIT> (closes the program)
 <HELP> (displays the help screen)
 <GOTO> (connects this command with a room address, and changes your location)


[ROOMS] -> [END_ROOMS]
This tag is used to connect the <GOTO>'s with thier needed addresses.  It is simply a list of room names
in the same order that the <GOTO>'s were called in.  leave an empty line between each file name that has
a non-GOTO command between them.
