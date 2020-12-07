# Message_Broadcaster :
An uber simple message broadcasting server powered by boost asio & beast websockets.

# Description :
Multiple websocket clients can connect to the server concurrently and observe the transmitted message, which can be generated on the fly by connecting to a different module within server.

# Installing boost library :
This server has been coded on boost 1.74.0 and built with gcc 9.3.0, and tested in Ubuntu 16.04 only, currently.
<br>Gather boost latest for your **nix* destro - On Ubuntu, debian sort of distributions, the usual 'apt-get' works well.

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
    ./bootstrap.sh --prefix=/usr/
    `
<br><br>Generate the headers:<br><br>
    `
    ./b2 headers
    `
<br><br>Finally, build and install the library:<br><br>
    `
    sudo ./b2 install
    `
    
# Building :
Run the cmake build system by including the necessary boost::beast headers and installation path (install path that is included in your $PATH would be convenient):<br><br>
    `
    cmake -DINCLUDE_BEAST_ /path/to/top/level/CMakeLists.txt -DCMAKE_PREFIX_PATH= /your/choice/of/path/to/binary
    `
<br><br>Build it:<br><br>
    `
    cmake --build . --config release --clean-first
    `
# Usage :
Run your server with the following, with specifying port number that your server listens to:<br><br>
`
./Message_Broadcast_Server <PORT>
`
