# tinyxpc
Lightweight, no-frills transactional point-to-point data transfer protocol.

## level 0: barebones
**Data Transfer Block:**
| Requestor ID  | Block ID | Target ID | Data... |
|:-------------:|:--------:|:---------:|:-------:|
|    1 Byte     |  1 Byte  |   1 Byte  | N Bytes |

Note that the `Responder ID` here is the same as the `Target ID` in the Request
Block, and the `Target ID` here is the same as the `Requestor ID` in the 
Request Block.

We choose not to waste any space here on data direction or block type at this
level.  The size of data is variable per block, as such it is not part of the
protocol.  Instead, the size and other type information may be encoded as
part of the data itself, and interpreted by communicating entities.

## level 1: checked
**Data Transfer Block:**
| Requestor ID  | Block ID | Target ID |  Type   | CRC 32  | Data... |
|:-------------:|:--------:|:---------:|:-------:|:-------:|:-------:|
|    1 Byte     |  1 Byte  |   1 Byte  | 1 Byte  | 4 bytes | N Bytes |

**Retransmission Request Block:**
| Responder ID  | Block ID | Target ID |  Type   |
|:-------------:|:--------:|:---------:|:-------:|
|    1 Byte     |  1 Byte  |   1 Byte  | 1 Byte  |


**Specification-Reserved Types:**
|          Name            | ID| Notes |
|:------------------------:|:-:|:-----:|
|  LEVEL1\_DATA\_REQUEST   | 0 |
| LEVEL1\_DATA\_RESPONSE   | 1 |
| LEVEL1\_RETRANSMIT\_REQ  | 2 | Block ID specifies the block which was missed.
| LEVEL1\_RENEGOTIATE\_REQ | 3 |

For reliable communcations, a 4-byte CRC is appended to each header. This
allows each  block to be checked at both ends, and trigger the use of a
retransmission request.

## Protocol Negotiation
All tinyxpc implementors should start in protocol negotiation mode.
Initiators should send a Negotiate Discovery block to the intended recipient,
and await a Negotiate Specification Descriptor in reply.
The initiator then chooses a spec level from within the range specified by the
recipient, and sends back a Negotiate Acknowledge block.  The number of
transmitters and receivers is assumed to be static by the negotiation protocol,
additional protocol levels may specify means by which to change these attributes
via other means.  Higher specification levels may also include their own
negotiation protocols which extend this one, allowing for transmission of
connection metadata inline with the actual data.

If for any reason, either end of a txpc connection needs to end communication,
it should send a Negotiate Disconnect block with no message content.

**Negotiate Discovery Block:**
| Discovery |
|:---------:|
|   0xAD    |

**Negotiate Specification Descriptor Block:**
|  Spec Min  |  Spec Max  | # Transmitters | # Receivers |
|:----------:|:----------:|:--------------:|:-----------:|
|   1 Byte   |   1 Byte   |     1 Byte     |    1 Byte   |

**Negotiate Acknowledge Block:**
| Spec Level |
|:----------:|
|   1 Byte   |

**Negotiate Disconnect Block:**
| Terminator |
|:----------:|
| 0x3F00003F |
