# <p align=center>UCODE-uchat</p>

This is my implementation of the real-time messaging application for the UCODE IT ACADEMY project. It is important to note, that it works **only** on the UNIX systems.

<h1 align=center> Used tools </h1>

<h1 align=center> Installation </h1>

**Important!** You need to already have installed GTK library on your device, so if you do not - install it first.
1. Download/clone the repo and move to the directory.
2. To *build* the project type ```make``` in the terminal.
3. First, you need to run the server, so type ```./uchat_server PORT``` where *PORT* is some number starting from 1030.
4. Now, you can run the client part which will be connected to the mentioned server and i recommend you to create a new terminal window for this. Type ```./uchat IPv4 PORT``` where *IPv4* is your address in the local network (if you are going to use client part on the same machine that server, type 127.0.0.1) and *PORT* is a number that you entered in the third step. 

To delete project enter ```make uninstall``` and to rebuild the project - ```make reinstall```.
