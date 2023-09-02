import socket
import threading

HOST = "127.0.0.1"
PORT = 50000

def handle_client(conn, addr):
    print(f"Connected by {addr}")
    while True:
        data = conn.recv(1024)
        if not data:
            print("Closing the connection")
            conn.close()
            break
        print(f"Client: {data.decode()}")
        server_message = input("Server: ")
        conn.sendall(server_message.encode())

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen()
print("Waiting for a client connection")

while True:
    conn, addr = s.accept()
    client_thread = threading.Thread(target=handle_client, args=(conn, addr))
    client_thread.start()