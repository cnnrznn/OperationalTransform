# OperationalTransform
C code for a generic operational transform collaboration system. Operations provided pertain to basic document editing.

## Using the engine
To use the engine, a program writes to `stdin` and reads from `stdout`.
The information communicated is different for the client and server side code, but **operations** are of the form:

`<pid>,<revision>,<op-type>,<op-char>,<op-position>`

... hehe, "opposition" :P

### Booting the engine
`./server`

`./client <pid> <revision>`

### Server
The server-side engine consumes operations from clients.
It produces transformed operations that should be broadcast to all clients, including the originating client.

### Client
The client-side engine consumes operations from the local environment (user, machine, etc.), as well as from the server.
For local operations, we need to tell the engine the engine by setting `pid` to -1.
For server operations, the `pid` field remains unchanged.

The client-side engine produces both operations to be sent to the server and operations to be applied locally.
Operations intended to be applied by the client are indicated by `pid = -1`.
Otherwise, the operation is intended for the server.

## Example Client/Server
An example of client and server code can be found under `example/`.

## Modularity

## References
