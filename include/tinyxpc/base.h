#pragma once
#include <stdint.h>
/**
 * These are the basic definitions needed by all TinyXPC sub-protocols.
 */

// 16 bit version declaration
//  - Upper 4 bits are the major version
//  - middle 4 bits are the minor version
//  - lower 4 bits are the patch number
#define VERSION(MAJ, MIN, PATCH) ((MAJ&0x0f<<12)|(MIN&0x0f<<8)|(PATCH&0xff))
#define TXPC_VERSION VERSION(0, 1, 0)

/**
 * TinyXPC Header block
 * This block precedes all other kinds of messages, regardless of TXPC version.
 * It contains the information required to:
 *  - Interpret the message's meaning
 *  - Perform message routing
 *  - Acknowledge a message or reply to the sender with another message.
 */
typedef struct {
    uint8_t type;
    uint8_t to;
    uint8_t from;
} txpc_hdr_t;
