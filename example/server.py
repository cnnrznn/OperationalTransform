#!/usr/bin/python

import json
import select
import socket
import subprocess as sp

__next_pid = 0

def next_pid():
    global __next_pid

    __next_pid += 1

    return __next_pid

def safe_send(sk, buf):
    sbuf = ''.join(buf)

    while len(sbuf) > 0:
        sbuf = sbuf[sk.send(sbuf):]

    return

def line2msg(line):
    data = line.split(',')

    msg = dict()
    msg['pid'] = int(data[0])
    msg['revision'] = int(data[1])
    msg['type'] = int(data[2])
    msg['char'] = data[3]
    msg['pos'] = int(data[4])

    return msg

def op_perform(buf, msg):
    typ = msg['type']
    c = msg['char']
    pos = msg['pos']

    if 1 == typ:
        if len(buf) < pos:
            buf.extend([' '] * (pos - len(buf)))
        buf.insert(pos, c)
    elif 2 == typ:
        buf.pop(pos)

    return buf

def main():
    revision = 0
    buf = []

    # start engine
    engine = sp.Popen(['./core/server'], stdin=sp.PIPE, stdout=sp.PIPE)

    lsk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    lsk.bind(('localhost', 3333))
    lsk.listen(10)

    sockets = set([lsk])

    while True:
        rlist, _, _ = select.select(sockets, [], [])

        ct = 0

        for rsk in rlist:
            if rsk == lsk:
                conn, addr = lsk.accept()

                res = dict()
                res['revision'] = revision
                res['bufsize'] = len(buf)
                res['pid'] = next_pid()

                conn.send(json.dumps(res))
                safe_send(conn, buf)

                sockets.add(conn)
            else:
                packet = rsk.recv(2048)
                if 0 == len(packet):
                    sockets.remove(rsk)
                else:
                    msg = json.loads(packet)
                    engine.stdin.write('{},{},{},{},{}\n'.format(msg['pid'], msg['revision'],
                                                            msg['type'], msg['char'], msg['pos']))
                    ct += 1

        #engine.stdin.write('{0},{1},{1},{1},{1}\n'.format(-2, 0))

        for i in range(ct):
            revision += 1

            data = engine.stdout.readline()
            msg = line2msg(data)
            buf = op_perform(buf, msg)

            # TODO broadcast msg

if __name__ == '__main__':
    main()
