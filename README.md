# tinyxpc
## this is very much beta quality, YMMV.

## Reference Implementation `xpc_relay`
The `xpc_relay` is the reference implementation of TinyXPC.  Its most notable
feature is that it does not require any kind of buffer.  All interfaces are
pluggable and it is intended to be dropped into any existing IO or event
system.  Only `memcmp` is required from the standard library, and any compliant
implementation will do, making it ideal for use in embedded systems.

## Documentation
The specification for the message types may be found in `tinyxpc_spec.md`.
The specification is not complete, and the `xpc_relay` does not support all
message types or modes.
