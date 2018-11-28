#!/usr/bin/python

import json
import socket

def safe_recv(sk, size):
    total = 0
    buf = ''

    while total < size:
        buf += sk.recv(size - total)
        total = len(buf)

    return buf

def main():
    sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sk.connect(('localhost', 3333))

    res = json.loads(sk.recv(2048))

    revision = res['revision']
    bufsize = res['bufsize']
    pid = res['pid']
    buf = safe_recv(sk, bufsize)

    print(res, buf)

    msg = dict()
    msg['pid'] = pid
    msg['revision'] = revision
    msg['type'] = 0
    msg['char'] = 'c'
    msg['pos'] = 10

    sk.send(json.dumps(msg))

    sk.close()

if __name__ == '__main__':
    main()
