#ifndef __TINY_XPC_H__
#define __TINY_XPC_H__
/*
 * tinyxpc spec definitions in C
 */

#include <stdint.h>

/*
 * Library types
 */
typedef void (txpc_send_fn)(void *ptr, void *bytes, uint32_t size);
typedef int (txpc_recv_fn)(void *ptr, void *bytes, uint32_t size);
typedef void (txpc_cb)(void *ptr, uint8_t level, uint8_t tx, uint8_t rx);

// FIXME REMOVE THESE
void send_fn(void *context, void *bytes, uint32_t size);
int recv_fn(void *context, void *bytes, uint32_t size);
void done_cb(void *context, uint8_t level, uint8_t tx, uint8_t rx);

typedef enum {
    TINY_XPC_LEVEL0,
    TINY_XPC_LEVEL1,
    TINY_XPC_LEVEL_MAX
} txpc_level;

/*
 * Negotiation sub-protocol headers
 */
typedef struct {
    uint8_t hdr;
} txpc_negotiate_discovery_t;

typedef struct {
    uint8_t spec_level_min;
    uint8_t spec_level_max;
    uint8_t transmitters_count;
    uint8_t receivers_count;
} txpc_negotiate_descriptor_t;

typedef struct {
    uint8_t spec_level;
} txpc_negotiate_ack_t;

typedef struct {
    uint8_t hdr[4];
} txpc_negotiate_disconnect_t;


typedef struct {
    txpc_send_fn *send;
    txpc_recv_fn *recv;
    txpc_cb *done_cb;
    void *send_cb_data, *recv_cb_data, *done_cb_data;
    uint8_t min_allowed, max_allowed;
} txpc_connect_options_t;

typedef struct {
    txpc_send_fn *send;
    txpc_recv_fn *recv;
    txpc_cb *done_cb;
    void *send_cb_data, *recv_cb_data, *done_cb_data;
    uint8_t min_supported, max_supported;
    uint8_t num_transmitters;
    uint8_t num_receivers;
} txpc_accept_options_t;

typedef struct {
    uint8_t level;
    uint8_t transmitters;
    uint8_t receivers;
} txpc_negotiate_settings_t;

/*
 * Negotiation  constants
 */
const static txpc_negotiate_discovery_t TXPC_DISCOVERY = { .hdr = 0xAD };
/*
 * Negotiation functions
 */
void txpc_connect(txpc_connect_options_t *opts);
void txpc_accept(txpc_accept_options_t *opts);


/*
 * Level 0 sub-protocol headers
 */
typedef struct {
    union {
        uint8_t requestor_id;
        uint8_t responder_id;
    };
    uint8_t block_id;
    uint8_t target_id;
} txpc_level0_xfer_t;

/*
 * Level 0 has no functions, as it is simple enough that the only layer beyond
 * reading from a serialized source (which is send_cb) is to interpret the data,
 * which the program does.
 */

/* 
 * Level 1 sub-protocol headers
 */
typedef struct {
    union {
        uint8_t requestor_id;
        uint8_t responder_id;
    };
    uint8_t block_id;
    uint8_t target_id;
    uint8_t type;
    uint32_t crc32;
} txpc_level1_xfer_t;

typedef struct {
    uint8_t type;
    uint8_t responder_id;
    uint8_t block_id;
    uint8_t target_id;
} txpc_retransmit_request;

/*
 *typedef struct {
 *    uint8_t type;
 *} txpc_level1_heartbeat;
 */

/*
 * Level 1 sub-protocol reserved values and names
 */
typedef enum {
    LEVEL1_DATA_REQUEST = 0,
    LEVEL1_DATA_RESPONSE,
    LEVEL1_RETRANSMIT_REQ,
    LEVEL1_RENEGOTIATE_REQ,
    /*
     *LEVEL1_HEARTBEAT = 255
     */
} txpc_level1_types;

/*
 * Internal names used by this implementation, exposed for documentation and
 * debugging purposes.
 */
typedef enum {
    TXPC_NEG_DISCOVER,
    TXPC_NEG_ACCEPTED,
    TXPC_NEG_EXPECT_SPEC,
    TXPC_NEG_FAILED
} txpc_neg_state;
#endif
