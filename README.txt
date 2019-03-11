****************************************
Password Vault
Author: Anugesh Balasubramaniam
Date: 06-25-2017
****************************************

COMPILATION:

make

****************************************

USAGE:

./bin/runMe

****************************************

RUNTIME (example):

Welcome to the password vault program!

To perform an operation, enter the value corresponding to the operatios below:

1) Open an existing password file
2) Create a new password file
3) Change password for an existing system
4) Add a new system and password
5) Retrieve password of an existing system
6) Remove a system entirely from the password vault
7) Change the program password
8) Save changes to file
9) Quit






>>(enter value)

****************************************

LIMITATIONS:

My program only works with one file at one time. For example; if the user reads in an existing file, that file is currently in use. If the user creates a new file after reading an existing file, the new file is currently in use and the program discards the data read from the previous file.

Date file must be in the “docs” folder

My program assumes that the program password is stored as the first line inside of the input file.

My program also stores program password as the first line when outputing to a file.

****************************************
