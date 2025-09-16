# coding: windows-1251
import struct
from typing import List
from pathlib import Path
import os

SBOX_TEST = [
    [4,10,9,2,13,8,0,14,6,11,1,12,7,15,5,3],
    [14,11,4,12,6,13,15,10,2,3,8,1,0,7,5,9],
    [5,8,1,13,10,3,4,2,14,15,12,7,6,0,9,11],
    [7,13,10,1,0,8,9,15,14,4,6,12,11,2,5,3],
    [6,12,7,1,5,15,13,8,4,10,9,14,0,3,11,2],
    [4,11,10,0,7,2,1,13,3,6,8,5,9,12,15,14],
    [13,11,4,1,3,15,5,9,0,10,14,7,6,8,2,12],
    [1,15,13,0,5,7,10,4,9,2,3,14,6,11,8,12],
]
MASK32 = 0xFFFFFFFF

def rol32(x: int, n: int) -> int:
    return ((x << n) & MASK32) | ((x & MASK32) >> (32 - n))

def sbox_substitution(value: int, sbox: List[List[int]]) -> int:
    out = 0
    for i in range(8):
        nibble = (value >> (4 * i)) & 0xF
        sub = sbox[i][nibble] & 0xF
        out |= (sub << (4 * i))
    return out

def round_f(part: int, key32: int, sbox: List[List[int]]) -> int:
    tmp = (part + key32) & MASK32
    tmp = sbox_substitution(tmp, sbox)
    tmp = rol32(tmp, 11)
    return tmp

def make_key_schedule_enc() -> List[int]:
    schedule = []
    for _ in range(3):
        schedule.extend(range(8))
    schedule.extend(reversed(range(8)))
    return schedule

def make_key_schedule_dec() -> List[int]:
    enc = make_key_schedule_enc()
    return list(reversed(enc))

def bytes_to_key_parts(key_bytes: bytes) -> List[int]:
    if len(key_bytes) != 32:
        raise ValueError("Key must be 32 bytes (256 bits)")
    return list(struct.unpack('<8I', key_bytes))

def gost_encrypt_block(block8: bytes, key_parts: List[int], sbox: List[List[int]]) -> bytes:
    if len(block8) != 8:
        raise ValueError("Block must be 8 bytes")
    n1, n2 = struct.unpack('<II', block8)
    L, R = n1, n2
    schedule = make_key_schedule_enc()
    for idx in schedule:
        Ki = key_parts[idx] & MASK32
        F = round_f(R, Ki, sbox)
        newL = R
        newR = L ^ F
        L, R = newL & MASK32, newR & MASK32
    # Финальная упаковка: (R, L)
    return struct.pack('<II', R, L)

def gost_decrypt_block(block8: bytes, key_parts: List[int], sbox: List[List[int]]) -> bytes:
    if len(block8) != 8:
        raise ValueError("Block must be 8 bytes")
    n1, n2 = struct.unpack('<II', block8)
    L, R = n1, n2
    schedule = make_key_schedule_dec()
    for idx in schedule:
        Ki = key_parts[idx] & MASK32
        F = round_f(R, Ki, sbox)
        newL = R
        newR = L ^ F
        L, R = newL & MASK32, newR & MASK32
    return struct.pack('<II', R, L)

def pkcs7_pad(data: bytes, block_size: int = 8) -> bytes:
    pad_len = block_size - (len(data) % block_size)
    if pad_len == 0:
        pad_len = block_size
    return data + bytes([pad_len]) * pad_len

def pkcs7_unpad(data: bytes, block_size: int = 8) -> bytes:
    if not data or len(data) % block_size != 0:
        raise ValueError("Invalid padded data length")
    pad_len = data[-1]
    if pad_len <= 0 or pad_len > block_size:
        raise ValueError("Invalid padding")
    if data[-pad_len:] != bytes([pad_len]) * pad_len:
        raise ValueError("Invalid padding bytes")
    return data[:-pad_len]

def encrypt_data_ecb(plaintext: bytes, key_bytes: bytes, sbox: List[List[int]] = SBOX_TEST) -> bytes:
    key_parts = bytes_to_key_parts(key_bytes)
    data = pkcs7_pad(plaintext, 8)
    out = bytearray()
    for i in range(0, len(data), 8):
        out.extend(gost_encrypt_block(data[i:i+8], key_parts, sbox))
    return bytes(out)

def decrypt_data_ecb(ciphertext: bytes, key_bytes: bytes, sbox: List[List[int]] = SBOX_TEST) -> bytes:
    if len(ciphertext) % 8 != 0:
        raise ValueError("Ciphertext must be multiple of 8 bytes")
    key_parts = bytes_to_key_parts(key_bytes)
    out = bytearray()
    for i in range(0, len(ciphertext), 8):
        out.extend(gost_decrypt_block(ciphertext[i:i+8], key_parts, sbox))
    return pkcs7_unpad(bytes(out), 8)

def encrypt_file_ecb(in_path: str, out_path: str, key_bytes: bytes, sbox: List[List[int]] = SBOX_TEST):
    data = Path(in_path).read_bytes()
    ct = encrypt_data_ecb(data, key_bytes, sbox)
    Path(out_path).write_bytes(ct)

def decrypt_file_ecb(in_path: str, out_path: str, key_bytes: bytes, sbox: List[List[int]] = SBOX_TEST):
    ct = Path(in_path).read_bytes()
    pt_bytes = decrypt_data_ecb(ct, key_bytes, sbox)
    Path(out_path).write_bytes(pt_bytes)


if __name__ == "__main__":
    input_file = Path("input.txt")
    encrypted_file = Path("encrypted.bin")
    decrypted_file = Path("decrypted.txt")

    if not input_file.exists():
        test_text = "Тестовый пример текста для шифрования по ГОСТ 28147-89."
        input_file.write_text(test_text, encoding="utf-8")
        print(f"Файл '{input_file}' отсутствовал — создан с тестовым текстом.")

    key_path = Path("key.bin")
    key_bytes = os.urandom(32)
    key_path.write_bytes(key_bytes)
    print("Сгенерирован новый ключ и сохранён в 'key.bin'.")

    encrypt_file_ecb(str(input_file), str(encrypted_file), key_bytes)
    print(f"Входной файл '{input_file}' зашифрован в '{encrypted_file}'.")
    decrypt_file_ecb(str(encrypted_file), str(decrypted_file), key_bytes)
    print(f"Файл '{encrypted_file}' расшифрован в '{decrypted_file}'.")
