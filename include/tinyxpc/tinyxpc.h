#pragma once
#include <stdint.h>
/**
 * TinyXPC Header block
 * This block precedes all other kinds of messages, regardless of TXPC version.
 * It contains the information required to:
 *  - Interpret the message's meaning
 *  - Perform message routing
 *  - Acknowledge a message or reply to the sender with another message.
 */
#pragma pack(push, 1)
typedef struct {
    uint16_t size;
    uint8_t type;
    uint8_t to;
    uint8_t from;
} txpc_hdr_t;
#pragma pack(pop)

/**
 * XPC Message types
 * These are the valid values for the TinyXPC spec and the XPC relay.
 */
enum {
    TXPC_MSG_TYPE_RESET = 1,
    TXPC_MSG_TYPE_CONFIG = 2,
    TXPC_MSG_TYPE_XON = 3,
    TXPC_MSG_TYPE_XOFF = 4,
    TXPC_MSG_TYPE_ACK = 5,
    TXPC_MSG_TYPE_MSG = 6
};
