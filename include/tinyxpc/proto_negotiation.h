#pragma once
#include <stdint.h>
#include <tinyxpc/base.h>

/**
 * TinyXPC Protocol negotiation sub-protocol types.
 * These are the universally-supported type fields
 */
enum {
    TXPC_NEG_TYPE_ENDIANNESS = 1,
    TXPC_NEG_TYPE_CRC_CONFIG,
    TXPC_NEG_TYPE_EXTENSION_REQ, /* IN REVIEW: REALISTIC? */
    TXPC_NEG_TYPE_REPORT_VERSION,
    TXPC_NEG_TYPE_DISCONNECT = 0xff
};

/**
 * NEG_TYPE_ENDIANNESS message structure.
 * This message informs a receiver what endianness the transmitter uses for
 * data storage.
 */
typedef struct {
    txpc_hdr_t hdr;
    uint8_t endianness;
} txpc_neg_endianness_t;

enum {
    TXPC_NEG_ENDIANNESS_LE = 0x01,
    TXPC_NEG_ENDIANNESS_BE = 0x80
};

/**
 * NEG_TYPE_CRC_CONFIG message structure.
 * This message sets the crc size and the polynomial.
 */
typedef struct {
    txpc_hdr_t hdr;
    uint8_t crc_bytes;
    char polyn[];
} txpc_neg_config_crc_t;

/**
 * NEG_TYPE_REPORT_VERSION message structure.
 * This message reports the protocol version of TinyXPC the sender is using.
 */
typedef struct {
    txpc_hdr_t hdr;
    uint16_t version;
} txpc_neg_version_t;

/**
 * NEG_TYPE_DISCONNECT message structure.
 * This message is only the TXPC header.
 */
typedef txpc_hdr_t txpc_neg_disconnect_t;
