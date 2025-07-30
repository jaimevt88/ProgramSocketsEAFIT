import socket

HOST = '127.0.0.1' # La dirección IP de loopback (localhost)
PORT = 8080        # El puerto en el que escuchará el servidor

# Crear el socket, enlazarlo y ponerlo en modo de escucha
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Opcional: reutilizar el puerto
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"Servidor simple escuchando en {HOST}:{PORT}...")

    # Aceptar una conexión entrante
    conn, addr = s.accept()
    with conn: # Usa 'with' para asegurar el cierre automático de la conexión
        print(f"Conexión aceptada de {addr}")
        message = "Hola desde el servidor simple de Python!"
        conn.sendall(message.encode('utf-8')) # Enviar mensaje (codificado a bytes)
        print(f"Mensaje enviado: \"{message}\"")

print("Servidor simple cerrado.")
