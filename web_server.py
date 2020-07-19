from http.server import HTTPServer, BaseHTTPRequestHandler
import cgi
import time
import serial

led_active = 0
ser = serial.Serial('/dev/cu.usbmodem14101', 115200)

class pageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.endswith('/'):
            self.send_response(200)
            self.send_header('content_type','text/html')
            self.end_headers()

            output = '<html><body>'
            output += '<h1>Hello</h1>'
            output += '<form method="POST" enctype="multipart/form-data" action="/">'
            output += '<input type="submit" name="button" value="Forward">'
            output += '<input type="submit" name="button" value="Stop">'
            output += '<input type="submit" name="button" value="Backward">'
            output += '<input type="submit" name="button" value="SideLeft">'
            output += '<input type="submit" name="button" value="SideRight">'
            output += '</form>'
            output += '</html></body>'

            self.wfile.write(output.encode())

    def do_POST(self):
        global led_active

        if self.path.endswith('/'):
            ctype, pdict = cgi.parse_header(self.headers.get('Content-Type'))
            pdict['boundary'] = bytes(pdict['boundary'], 'utf-8')
            pdict['CONTENT-LENGTH'] = int(self.headers.get('Content-length'))
            if ctype == 'multipart/form-data':
                fields = cgi.parse_multipart(self.rfile, pdict)
                print(fields)
                button_state = fields.get('button')
                print(button_state)
                send_command(button_state[0])

            self.send_response(301)
            self.send_header('content_type','text/html')
            self.send_header('Location', '/')
            self.end_headers()


def send_command(cmd):
    if cmd == "Forward":
        ser.write(b'1')
    elif cmd == "Stop":
        ser.write(b'0')
    elif cmd == "Backward":
        ser.write(b'2')
    elif cmd == "SideRight":
        ser.write(b'3')
    elif cmd == "SideLeft":
        ser.write(b'4')

def change_led_state(led_active):
    if led_active:
        led_active = 0
    elif not led_active:
        led_active = 1

    print(led_active)

    ser.write(str(led_active).encode('utf-8'))
    return led_active

if __name__ == "__main__":
    PORT = 80
    server_address = ("", PORT)
    server = HTTPServer(server_address, pageHandler)
    print(f"Server running on port {PORT}")
    server.serve_forever()
