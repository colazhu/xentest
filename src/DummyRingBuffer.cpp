#include "DummyRingBuffer.hpp"

EventRingBuffer::EventRingBuffer(int conIndex, domid_t domId,
                                 evtchn_port_t port, grant_ref_t ref,
                                 int offset, size_t size) :
    RingBufferOutBase<xendummy_event_page, xendummy_evt>(domId, port, ref,
                                                         offset, size),
    mConIndex(conIndex),
    mLog("InEventRing")
{
    LOG(mLog, DEBUG) << "Create event ring buffer, index: " << mConIndex;
}


CtrlRingBuffer::CtrlRingBuffer(EventRingBufferPtr eventBuffer,
               domid_t domId, evtchn_port_t port, grant_ref_t ref):
    RingBufferInBase<xen_dummyif_back_ring, xen_dummyif_sring,
                     xendummy_req, xendummy_resp>(domId, port, ref),
    mLog("CtrlRing")
{

}

void CtrlRingBuffer::processRequest(const xendummy_req& req)
{
    DLOG(mLog, DEBUG) << "Request received, cmd:"
                      << static_cast<int>(req.operation);

    xendummy_resp rsp;
    rsp.id = req.id;
    rsp.operation = req.operation;
    // rsp.status = mCommandHandler.processCommand(req);
    sendResponse(rsp);
}
