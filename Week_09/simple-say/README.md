
This node app will connect to Spacebrew and open a subscriber called "words".  It will then wait for strings on the "words" channel.  When it receives a string, it will extract any words between quotes and read them aloud using [the OSX "say" command](http://developer.apple.com/library/mac/#documentation/Darwin/Reference/ManPages/man1/say.1.html).

Make sure to install the required modules before trying to run this app.

    cd /path/to/simple-say
    npm install