# CustomShell

CustomShell is a command line interface for Linux machines.

Introduction: 
The development of specific purpose shells assists network administration by simplifying the selection of commands and options, which can be used to achieve specific tasks. Design, build and test a specified purpose command shell to run on a Linux system. The purpose of the shell is to present a limited set of functionality to a Linux system user such that they can examine and set a limited selection of network related settings on Linux.

Instructions: 
Design, build and test a specified purpose command shell to run on a Linux system. The purpose of the shell is to present a limited set of functionality to a Linux system user, such that they can examine and set a limited selection of network related settings on Linux.

External Commands:
The shell should allow the user to run at least two external commands, to include pwd and ifconfig. • In the case of pwd • The abbreviation pw should be used in the shell to run pwd • No command-tail is required • If a command-tail is supplied it should be ignored • In the case of ifconfig • The abbreviation ifc should be used to run ifconfig • The default behavior of ifc is to display the settings for interface en0 • No command tail is required, but if one is supplied the behavior is to provide the ifconfig information for the specified interface instead of for en0

Internal Commands:
The shell should allow the user to run at least two internal commands, to include dt to display the date and time on the system and ud to display standard details for the currently logged-in user. • In the case of dt • The internal command dt should display the current date and time on the system, without using an external command, and to display it in the same format as would be displayed by the command • date +%Y%m%d%H%M%S • i.e. 20130926215222 • In the case of ud • The internal command ud should display the following user details, without using an external command • userID, groupID, username, groupname, iNode of user’s home directory • i.e. 501, 20, briankeegan, staff, 335665
