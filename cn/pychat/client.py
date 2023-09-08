import socket
import threading
from tkinter import Tk, Entry, Text, Scrollbar, BOTTOM, END, VERTICAL, font // GUI

HOST = "127.0.0.1"
PORT = 50000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

def receive_message():
    while True:
        data = s.recv(1024)
        send_message(server_message=data.decode())

def send_message(event=None, server_message=None):
    chat_history.config(state="normal")
    if server_message:
        chat_history.insert(END, f"Client 2: {server_message}\n\n")
    else:
        user_message = input_box.get()
        if user_message:
            chat_history.insert(END, f"Client: {user_message}\n\n")
            s.sendall(user_message.encode())
    chat_history.config(state="disabled")
    chat_history.yview(END)
    input_box.delete(0, END)

// Configurações Gráficas
window = Tk()
window.geometry("300x400")
window.configure(bg="#282a36")
window.title("PyChat")

customFont = font.Font(family="Helvetica", size=12)

chat_history = Text(window, wrap="word", bg="#282a36", fg="#f8f8f2", state="disabled", font=customFont)
chat_history.pack(expand=1, fill="both")

scrollbar = Scrollbar(chat_history, orient=VERTICAL, bg="#6272a4")
scrollbar.pack(side="right", fill="y")
chat_history.config(yscrollcommand=scrollbar.set)
scrollbar.config(command=chat_history.yview)

input_box = Entry(window, width=300, bg="#282a36", fg="#f8f8f2", font=customFont)
input_box.pack(side=BOTTOM)
input_box.bind("<Return>", send_message)

// Cria outra thread independente pra não bloquear a atualização da GUI no envio/recebimento de mensagens
receive_thread = threading.Thread(target=receive_message)
receive_thread.start()

window.mainloop()
