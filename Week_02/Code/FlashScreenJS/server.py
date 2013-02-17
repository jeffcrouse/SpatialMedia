"""
Serves files out of its current directory.
Doesn't handle POST requests.
"""
import SocketServer
import SimpleHTTPServer

PORT = 8000

#sketch
numClients=0

class CustomHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):

    def __init__(self, request, client_address, server):
        SimpleHTTPServer.SimpleHTTPRequestHandler.__init__(self, request, client_address, server)

    def do_GET(self):
        if self.path=='/':
            global numClients
            numClients+=1
            print numClients
            self.send_response(302)
            self.send_header("Location", '/index.html?name=Flash'+str(numClients))
            self.end_headers()
            return
        else:
            #serve files, and directory listings by following self.path from
            #current working directory
            SimpleHTTPServer.SimpleHTTPRequestHandler.do_GET(self)

httpd = SocketServer.ThreadingTCPServer(('localhost', PORT),CustomHandler)

print "serving at port", PORT
httpd.serve_forever()