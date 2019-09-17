#include <tinyxpc/tinyxpc.h>
#include <stddef.h>

void txpc_connect(txpc_connect_options_t *opts) {
    int negotiated_level = 0;
    txpc_negotiate_descriptor_t descriptor = {0};
    // send a connection request
    opts->send(opts->send_cb_data, (void*)&TXPC_DISCOVERY,
         sizeof(txpc_negotiate_discovery_t));

    int resp_size = opts->recv(opts->recv_cb_data, (void*)(&descriptor),
        sizeof(txpc_negotiate_descriptor_t));

    if(resp_size <= 0) {
        negotiated_level = 255;
        goto exit;
    }

    // choose the highest available FIXME this should be configurable
    if(descriptor.spec_level_min > opts->max_allowed) {
        // fail
    }
    else if (descriptor.spec_level_max < opts->min_allowed) {
        // fail
    }
    else {
        txpc_negotiate_ack_t ack_block;
        ack_block.spec_level = opts->max_allowed;
        opts->send(opts->send_cb_data, (void*)&ack_block,
             sizeof(txpc_negotiate_ack_t));
        negotiated_level = ack_block.spec_level;

    }
exit:
    if(opts->done_cb != NULL) {
        opts->done_cb(
            opts->done_cb_data,
            negotiated_level,
            descriptor.transmitters_count,
            descriptor.receivers_count
        );
    }
}

void txpc_accept(txpc_accept_options_t *opts) {
    int negotiated_level = 0;
    txpc_negotiate_discovery_t discovery_block = {0};
    txpc_negotiate_descriptor_t descriptor_block = {0};
    // listen for a discovery packet
    int resp_size = opts->recv(opts->recv_cb_data, (void*)&discovery_block,
         sizeof(txpc_negotiate_discovery_t));

    if(resp_size <= 0 || discovery_block.hdr != 0xAD) {
        negotiated_level = 255;
        goto exit;
    }

    descriptor_block.spec_level_min = opts->min_supported;
    descriptor_block.spec_level_max = opts->max_supported;
    descriptor_block.transmitters_count = opts->num_transmitters;
    descriptor_block.receivers_count = opts->num_receivers;

    opts->send(opts->send_cb_data, (void*)&descriptor_block,
         sizeof(txpc_negotiate_descriptor_t));

    txpc_negotiate_ack_t ack_block;
    ack_block.spec_level = opts->max_supported;
    resp_size = opts->recv(opts->recv_cb_data, (void*)&ack_block,
         sizeof(txpc_negotiate_ack_t));

    if(resp_size <= 0) {
        // fail
    }

        negotiated_level = ack_block.spec_level;
exit:
    if(opts->done_cb != NULL) {
        opts->done_cb(
            opts->done_cb_data,
            negotiated_level,
            descriptor_block.transmitters_count,
            descriptor_block.receivers_count
        );
    }
}
