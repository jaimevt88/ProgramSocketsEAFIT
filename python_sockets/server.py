import socket

HOST = '0.0.0.0' # La dirección IP desde la cual escucha el server. Se utiliza 0.0.0.0 para que escuche por todas las direcciones
PORT = 8080        # El puerto en el que escuchará el servidor


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"Servidor simple escuchando en {HOST}:{PORT}...")

    # Aceptar una conexión entrante
    conn, addr = s.accept()
    with conn: # Usa 'with' para asegurar el cierre automático de la conexión
        print(f"Conexión aceptada de {addr}")
        message = "¡Hola desde el servidor simple de Python! Con menos líneas que en C"
        conn.sendall(message.encode('utf-8')) # Enviar mensaje (codificado a bytes)
        print(f"Mensaje enviado: \"{message}\"")

print("Servidor simple cerrado.")
