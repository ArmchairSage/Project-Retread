from fastapi import FastAPI

import socket 
UDP_IP = "192.168.6.10" # IP of the esp32 on the network
UDP_PORT = 1234

app = FastAPI()

@app.post("/send-msg")
async def send_message():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto("test".encode("utf-8"), (UDP_IP, UDP_PORT))
    return {"message": "Message Sent"}