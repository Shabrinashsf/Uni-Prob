import socket

KEY = 3  

def caesar(text, shift):
    hasil = ""
    for c in text:
        if "A" <= c <= "Z":
            hasil += chr((ord(c) - 65 + shift) % 26 + 65)
        elif "a" <= c <= "z":
            hasil += chr((ord(c) - 97 + shift) % 26 + 97)
        else:
            hasil += c
    return hasil

encrypt = lambda t: caesar(t, KEY)
decrypt = lambda t: caesar(t, -KEY)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(("0.0.0.0", 5555))
server.listen()
print(f"[RECEIVER] Menunggu koneksi di port 5555 ...")
conn, addr = server.accept()
print(f"[RECEIVER] Terhubung dengan sender dari {addr}\n")

while True:
    ct = conn.recv(1024).decode()
    if not ct or ct == "/quit":
        break
    print(f"[SENDER] ciphertext diterima : {ct}")
    print(f"[SENDER] didekripsi (key={KEY})  : {decrypt(ct)}\n")

    pt = input("[RECEIVER] pesan balasan : ")
    ct2 = encrypt(pt)
    print(f"[RECEIVER] plaintext           : {pt}")
    print(f"[RECEIVER] ciphertext dikirim  : {ct2}\n")
    conn.sendall(ct2.encode())
    if pt == "/quit":
        break

conn.close()
print("[RECEIVER] Koneksi ditutup.")
