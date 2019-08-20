#ifndef DUMMYRINGBUFFER_HPP_
#define DUMMYRINGBUFFER_HPP_

#include <xen/be/RingBufferBase.hpp>
#include <xen/be/Log.hpp>
#include <xen/io/dummyif.h>


/***************************************************************************//**
 * Ring buffer used to send events to the frontend.
 * @ingroup displ_be
 ******************************************************************************/
class EventRingBuffer : public XenBackend::RingBufferOutBase<xendummy_event_page, xendummy_evt>
{
public:
    /**
     * @param conIndex  connector index
     * @param domId     frontend domain id
     * @param port      event channel port number
     * @param ref       grant table reference
     * @param offset    start of the ring buffer inside the page
     * @param size      size of the ring buffer
     */
    EventRingBuffer(int conIndex, domid_t domId, evtchn_port_t port, grant_ref_t ref, int offset, size_t size);

private:
    int mConIndex;
    XenBackend::Log mLog;
};

typedef std::shared_ptr<EventRingBuffer> EventRingBufferPtr;


/***************************************************************************//**
 * Ring buffer used for the connector control.
 * @ingroup displ_be
 ******************************************************************************/
class CtrlRingBuffer : public XenBackend::RingBufferInBase<
        xen_dummyif_back_ring, xen_dummyif_sring, xendummy_req, xendummy_resp>
{
public:
    /**
     * @param eventBuffer    event ring buffer
     * @param domId          frontend domain id
     * @param port           event channel port number
     * @param ref            grant table reference
     */
    CtrlRingBuffer(EventRingBufferPtr eventBuffer,
                   domid_t domId, evtchn_port_t port, grant_ref_t ref);

    virtual ~CtrlRingBuffer() {}

//    /**
//     * @param display        display object
//     * @param connector      connector object
//     * @param buffersStorage buffers storage
//     * @param eventBuffer    event ring buffer
//     * @param domId          frontend domain id
//     * @param port           event channel port number
//     * @param ref            grant table reference
//     */
//    CtrlRingBuffer(DisplayItf::DisplayPtr display,
//                   DisplayItf::ConnectorPtr connector,
//                   BuffersStoragePtr buffersStorage,
//                   EventRingBufferPtr eventBuffer,
//                   domid_t domId, evtchn_port_t port, grant_ref_t ref);

private:
//    DisplayCommandHandler mCommandHandler;
    XenBackend::Log mLog;

    void processRequest(const xendummy_req& req);
};

typedef std::shared_ptr<CtrlRingBuffer> CtrlRingBufferPtr;

#endif /* DUMMYRINGBUFFER_HPP_ */
