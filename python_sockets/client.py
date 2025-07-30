import socket

HOST = '127.0.0.1' # La dirección IP del servidor
PORT = 8080        # El puerto del servidor

# Crear el socket del cliente y conectarse al servidor
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    print(f"Conectado al servidor simple en {HOST}:{PORT}")

    
    data = s.recv(1024) 
    message_received = data.decode('utf-8') 
    print(f"Mensaje recibido: \"{message_received}\"")

print("Cliente simple cerrado.")
