#pragma once
#include <stdint.h>
#include <tinyxpc/base.h>
/**
 * TinyXPC messaging sub-protocol types.
 */
enum {
    TXPC_FRAME_TYPE_MSG = 0x01,
    TXPC_FRAME_TYPE_STREAM,
    TXPC_FRAME_TYPE_MSG_NACK,
    TXPC_FRAME_TYPE_STREAM_NACK,
    TXPC_FRAME_TYPE_PAUSE,
    TXPC_FRAME_TYPE_RESUME
};

/**
 * FRAME_TYPE_MSG message structure.
 * This type supports single-shot messages up to 255 bytes long.
 */
typedef struct {
    txpc_hdr_t hdr;
    uint8_t size;
    char msg[];
} txpc_msg_t;


/**
 * FRAME_TYPE_STREAM message structure.
 * This type supports messages which are not continuous.
 * These messages are used for large data transfers in-channel with other
 * messages.  They support a transaction ID for tracking, and a single-message
 * size up to 65535 bytes.  Messages may be sent out-of-order, the sequence
 * number denotes the relative location of this message in the stream.
 */
typedef struct {
    txpc_hdr_t hdr;
    uint16_t size;
    uint8_t id;
    uint8_t seq_num;
    char msg[];
} txpc_stream_pkt_t;

/**
 * FRAME_TYPE_STREAM_NACK message structure.
 * This type is designed to signal to a transmitter that a stream message was
 * not received correctly.  The transaction ID and sequence number denote which
 * frame was not received correctly, and in what transaction.
 * The possible ways in which this message can be triggered are:
 *  - CRC failure
 *  - Buffer out of space on receiving end.
 * In the case wehre the receiving buffer is out of space, or will be out of
 * space shortly, it is recommended to also send a PAUSE message.
 */
typedef struct {
    txpc_hdr_t hdr;
    uint8_t id;
    uint8_t seq_num;
} txpc_stream_nack_t;

/**
 * FRAME_TYPE_STREAM_PAUSE and FRAME_TYPE_STREAM_RESUME message structure.
 * This message is sent to pause a transaction stream, usually indicating that
 * a buffer on the receiving end is full.
 */
typedef struct {
    txpc_hdr_t hdr;
    uint8_t id;
} txpc_stream_pause_t;

typedef txpc_stream_pause_t txpc_stream_resume_t;
