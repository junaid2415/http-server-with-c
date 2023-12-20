# test_backlog.py
import socket
import threading
import time

def connect_to_server():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(('localhost', 8080))
    time.sleep(1)  # Simulate some work
    client.close()

# Simulate multiple clients
num_clients = 10
threads = []

for _ in range(num_clients):
    thread = threading.Thread(target=connect_to_server)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()
