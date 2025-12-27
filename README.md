# Message_Broadcaster :
An uber simple message broadcasting server powered by boost asio & beast websockets.

# Platforms :
*nix distributions with compatible boost library support built with gcc 9.3.0 and cmake 3.17.5 .

# Description :
Multiple websocket clients can connect to the server concurrently and observe the transmitted message, which can be generated on the fly by connecting to a different module within server.

# Installing boost library :
This server has been coded on boost 1.74.0 and built with gcc 9.3.0, and tested in Ubuntu 16.04 only, currently.
<br>Gather boost latest for your *nix destro - On Ubuntu, debian sort of distributions, the usual 'apt-get' works well.<br><br>
    `
    $ sudo apt-get update    
    `
<br><br>Install boost:<br><br>
    `
    $ sudo apt-get install build-essential libboost-all-dev
    `
<br><br>Alternatively, for a specific boost version one may custom build it. In order to build boost version 1.xx.x for debian systems, start off by obtaining the boost sources:<br><br>
    `
    $ wget -O boost_1_XX_X.tar.bz2 https://sourceforge.net/projects/boost/files/boost/1.xx.x/boost_1_xx_x.tar.bz2/download
    `
<br><br>Decompress and untar this to recover the sources. Configure the build and set the installation path from inside the above boost_1_xx_x directory:<br><br>
    `
    $ ./bootstrap.sh --prefix=/usr/
    `
<br><br>Generate the headers:<br><br>
    `
    $ ./b2 headers
    `
<br><br>Finally, build and install the library:<br><br>
    `
    $ sudo ./b2 install
    `
    
# Building the server :
Run the cmake build system by specifying the installation path (install path that is included in your $PATH would be convenient). Within the root directory "Message_Broadcaster":<br><br>
    `
    $ cmake /path/to/top/level/CMakeLists.txt -DCMAKE_PREFIX_PATH= /your/choice/of/path/to/binary
    `
<br><br>Build it, this builds the websocket client project too :<br><br>
    `
    $ cmake --build . --config release --clean-first --target install
    `
    
# Usage :
1.) Run your server with the following, specifying port number that your server listens to (default port is <i>9000</i>) :<br><br>
`
$ ./Message_Broadcasting_Server <PORT>
`
<br><br> 2.) Connect your server with websocket client to check the broadcasted data. Many clients can connect to the server concurrently.<br><br>
`
$ ./Websocket_Client <SERVER> <PORT>
`
<br><br> 3.) In order to change the broadcasted message on-the-fly, connect to the broadcast message module with any other communication client tool viz, <i>telnet, netcat, putty, nc </i>:<br><br>
`
$ nc <SERVER> <PORT> + 1
`
<br><br>For example, if your websocket server runs on <i>localhost:9000</i> then :<br><br>
`
$ nc localhost 9001
`
<br><br> 4.) Type in your message to be broadcasted and then end with the tag <i>endofmsg</i> like so :<br><br>
`
$ Hello World endofmsg
`
<br><br>will broadcast <i>Hello World</i> on all the listening clients. 

# docker support :
1.) Start off by building the docker image :<br><br>
`
$ docker build -t <your image name> <Dockerfile directory>
`
<br><br> 2.) Check if the image was built successfully :<br><br>
`
$ docker images -a
`
<br><br> 3.) After a successful build run the container  :<br><br>
`
$ docker run -d -it -p 9000:9000 -p 9001:9001 --name=<your container name> <your image name> Message_Broadcasting_Server localhost 9000
`
<br><br> Since the `Dockerfile` explicitly `EXPOSE`s port `9000` and `9001` these should be modified as per user's needs. Once the container is up and running, Message_Broadcasting_Server can be interacted with the websocket client or any other utility as aforementioned.<br><br>
`
$ nc localhost 9000
`
