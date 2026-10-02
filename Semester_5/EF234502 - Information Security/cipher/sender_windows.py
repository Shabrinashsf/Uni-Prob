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

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("localhost", 5555))
print(f"[SENDER] Terhubung ke receiver di localhost:5555\n")

while True:
    pt = input("[SENDER] pesan : ")
    ct = encrypt(pt)
    print(f"[SENDER] plaintext           : {pt}")
    print(f"[SENDER] ciphertext dikirim  : {ct}\n")
    client.sendall(ct.encode())
    if pt == "/quit":
        break

    ct2 = client.recv(1024).decode()
    if not ct2 or ct2 == "/quit":
        break
    print(f"[RECEIVER] ciphertext diterima : {ct2}")
    print(f"[RECEIVER] didekripsi (key={KEY})  : {decrypt(ct2)}\n")

client.close()
print("[SENDER] Koneksi ditutup.")
