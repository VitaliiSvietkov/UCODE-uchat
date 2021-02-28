# <p align=center>UCODE-uchat</p>

This is my implementation of the real-time messaging application for the UCODE IT ACADEMY project. It is important to note, that it works **only** on the UNIX systems.

<p align="center"><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Logo-FHD.png?raw=true" alt="Impulse logo" width="720" height="400"></p>

<h1 align=center> Used tools </h1>

<h1 align=center> Installation </h1>

**Important!** You need to already have installed GTK library on your device, so if you do not - install it first.
1. Download/clone the repo and move to the directory.
2. To *build* the project type ```make``` in the terminal.
3. First, you need to run the server, so type ```./uchat_server PORT``` where *PORT* is some number starting from 1030.
4. Now, you can run the client part which will be connected to the mentioned server and i recommend you to create a new terminal window for this. Type ```./uchat IPv4 PORT``` where *IPv4* is your address in the local network (if you are going to use client part on the same machine that server, type 127.0.0.1) and *PORT* is a number that you entered in the third step. 

To delete project enter ```make uninstall``` and to rebuild the project - ```make reinstall```.

<h1 align=center> Implemented features </h1>

<h2> Client part </h2>

*  **Basic authentication** by username and password. A new user can log in and sign up using corresponding buttons on the authorization form at the start of the app. After the registration password will be encoded using improved Caesar encrypting algorithm without the possibility of decoding. During the authorization encrypted password from the log in form wil be compared with the password in the data base.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Registration1.png?raw=true" alt="Registration1" width="350" height="350">   <img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Registration%20Error.png?raw=true" alt="Registration with error" width="350" height="350"></p>
*  **Reconnection**. If the uchat app lost connection with the server, client will constantly try to reconnect. Appropriate messages will be displayed. <p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Reconnection.gif?raw=true" alt="Reconnection gif"></p>
*  The user can **delete, edit and copy** the text from the message after it send. In the message the time of its sending is displayed.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/MessageInteraction.gif?raw=true" alt="Message interaction" width="900" height="450"></p>
*  **Image sending**. The user can select a message for attachment and send it. Size of the image must be less than 5mb, in other case an appropriate message will be displayed. Large images will be sized down and after sending both recipient and sender can open it in the original size if its less then 1920x1080 pixels or in the mentioned size.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/ImageSend3.png?raw=true" alt="Image sending" width="600" height="450"></p>
*  **Avatar change**. Each user can change the default profile picture. The selected object will be sized to the square, but not cut.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Screen%20Shot%202021-02-15%20at%206.31.58%20PM.png?raw=true" alt="First avatar" width="350" height="150"><b>-----></b><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Screen%20Shot%202021-02-15%20at%206.32.41%20PM.png?raw=true" alt="Second avatar" width="350" height="150"></p>
* **Search**. The user can type a name of another one and start conversation with him or her. After selecting a new room, it will be added to the chats list in the left and on the recipient side it will be displayed only after message arriving. If there are no messages in the room, it will not be displayed after next authorization at all.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Search.gif?raw=true" alt="Search gif" width="400" height="300"></p>
* **Choosing a theme**. In setting, user can change colors of the application from standard black and white to another pink and white.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Theme1.png?raw=true" alt="Theme1" width="400" height="300"><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/Theme2.png?raw=true" alt="Theme2" width="400" height="300"></p>
* **Changing a language**. In setting, user can change language of the application to Russian, Ukrainian or English. The last one is default.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/XMLform2.png?raw=true" alt="Language" width="600" height="450"></p>
* **Modifying profile information**. In the 'edit user' form user can change all information about him/her but not password. The 'description' field was implemented for the future feature, but there were no time for it.<p align="center"><br><img src="https://github.com/VitaliiSvietkov/UCODE-uchat/blob/main/media/XMLform1.png?raw=true" alt="Edit user form" width="600" height="450"></p>

<h2> Server part </h2>

* **Concurrency**. For each user information processing are responsible different threads.
* ```uchat_server``` works as a **daemon**, listening to the specified port. 
* All necessary data is saved into the **database**. SQLite database was used. Each image is firstly encrypted using base64 algorithm and only then sent to the server where inserted to the database.
