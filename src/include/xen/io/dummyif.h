#ifndef __XEN_PUBLIC_IO_DUMMYIF_H__
#define __XEN_PUBLIC_IO_DUMMYIF_H__

#include "ring.h"
#include "../grant_table.h"

/*
 ******************************************************************************
 *                           Protocol version
 ******************************************************************************
 */
#define XENDUMMY_PROTOCOL_VERSION         2

/*
 ******************************************************************************
 *               XENSTORE FIELD AND PATH NAME STRINGS, HELPERS
 ******************************************************************************
 */
#define XENDUMMY_DRIVER_NAME              "vdummy"

#define XENDUMMY_LIST_SEPARATOR           ","
/* Field names */
#define XENDUMMY_FIELD_BE_VERSIONS        "versions"
#define XENDUMMY_FIELD_FE_VERSION         "version"
// #define XENDUMMY_FIELD_VCARD_SHORT_NAME   "short-name"
// #define XENDUMMY_FIELD_VCARD_LONG_NAME    "long-name"
// #define XENDUMMY_FIELD_RING_REF           "ring-ref"

#define XENDUMMY_FIELD_EVT_RING_REF       "evt-ring-ref"
#define XENDUMMY_FIELD_EVT_CHANNEL        "evt-event-channel"
#define XENDUMMY_FIELD_REQ_RING_REF   	  "req-ring-ref"
#define XENDUMMY_FIELD_REQ_CHANNEL        "req-event-channel"

#define XENDUMMY_FIELD_DEVICE_NAME        "name"
#define XENDUMMY_FIELD_TYPE               "type"
#define XENDUMMY_FIELD_UNIQUE_ID          "unique-id"
#define XENDUMMY_FIELD_CHANNELS_MIN       "channels-min"
#define XENDUMMY_FIELD_CHANNELS_MAX       "channels-max"
#define XENDUMMY_FIELD_SAMPLE_RATES       "sample-rates"
#define XENDUMMY_FIELD_SAMPLE_FORMATS     "sample-formats"
#define XENDUMMY_FIELD_BUFFER_SIZE        "buffer-size"

// total 64 byte
struct xendummy_req {
    uint16_t id;
    uint8_t operation;
    uint8_t reserved[61];
};

struct xendummy_resp {
    uint16_t id;
    uint8_t operation;
    uint8_t reserved[61];
};

struct xendummy_event_page {
    uint32_t in_cons;
    uint32_t in_prod;
    uint8_t reserved[56];
};

struct xendummy_evt {
    uint16_t id;
    uint8_t reserved[62];
};

DEFINE_RING_TYPES(xen_dummyif, struct xendummy_req, struct xendummy_resp);

#define XENDUMMY_EVENT_PAGE_SIZE 4096
#define XENDUMMY_IN_RING_OFFS (sizeof(struct xendummy_event_page))
#define XENDUMMY_IN_RING_SIZE (XENDUMMY_EVENT_PAGE_SIZE - XENDUMMY_IN_RING_OFFS)
#define XENDUMMY_IN_RING_LEN (XENDUMMY_IN_RING_SIZE / sizeof(struct xendummy_evt))
#define XENDUMMY_IN_RING(page) \
    ((struct xendummy_evt *)((char *)(page) + XENDUMMY_IN_RING_OFFS))
#define XENDUMMY_IN_RING_REF(page, idx) \
    (XENDUMMY_IN_RING((page))[(idx) % XENDUMMY_IN_RING_LEN])

#endif __XEN_PUBLIC_IO_DUMMYIF_H__
