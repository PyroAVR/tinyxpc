# TinyXPC
Lightweight point-to-point messaging.

## Intended Use Case
TinyXPC is intended for use in applications where IP, MQTT, etc. are overkill.
Since it is a data-framing protocol, it can also be run over TCP/IP or UDP/IP.
The primary application, however, is for embedded applications or inter-process
communication, and development efforts will be focused there.

## Design Methodology
TinyXPC is designed to be modular both as application code and as an abstract
protocol.  No modules are required to have a fully-functioning framed data
protocol, though without any, only basic semaphores are easily implemented.
