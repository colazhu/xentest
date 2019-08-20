#include "DummyBackend.hpp"
#include <algorithm>
#include <vector>
#include <xen/be/XenStore.hpp>

using namespace std;
using namespace XenBackend;

/*******************************************************************************
 * DummyFrontendHandler
 ******************************************************************************/
DummyFrontendHandler::DummyFrontendHandler(DummyDevPtr dummydev,
                       const std::string& devName,
                       domid_t beDomId, domid_t feDomId, uint16_t devId) :
    FrontendHandlerBase("DummyFrontend", devName,
                        beDomId, feDomId, devId),
    mDummyDev(dummydev),
    mLog("DummyFrontend")
{

}

void DummyFrontendHandler::onBind()
{
    LOG(mLog, DEBUG) << "On frontend bind : " << getDomId();
    // BuffersStoragePtr buffersStorage(new BuffersStorage(getDomId(), mDisplay));

    int conIndex = 0;
    string conBasePath = getXsFrontendPath() + "/";

    while (getXenStore().checkIfExist(conBasePath + to_string(conIndex)))
    {
        LOG(mLog, DEBUG) << "Found connector: " << conIndex;

        createConnector(conBasePath + to_string(conIndex) + "/", conIndex);
//        createConnector(conBasePath + to_string(conIndex) + "/", conIndex, buffersStorage);

        conIndex++;
    }
}


void DummyFrontendHandler::createConnector(const string& conPath, int conIndex /*, BuffersStoragePtr bufferStorage*/)
{
    evtchn_port_t port = getXenStore().readInt(conPath + XENDUMMY_FIELD_EVT_CHANNEL);

    uint32_t ref = getXenStore().readInt(conPath + XENDUMMY_FIELD_EVT_RING_REF);

    EventRingBufferPtr eventRingBuffer(new EventRingBuffer(conIndex, getDomId(), port, ref, XENDUMMY_IN_RING_OFFS, XENDUMMY_IN_RING_SIZE));

    addRingBuffer(eventRingBuffer);

    port = getXenStore().readInt(conPath + XENDUMMY_FIELD_REQ_CHANNEL);

    ref = getXenStore().readInt(conPath + XENDUMMY_FIELD_REQ_RING_REF);

    auto id = getXenStore().readString(conPath + XENDUMMY_FIELD_UNIQUE_ID);

//    auto connector = mDisplay->createConnector(id);
//    CtrlRingBufferPtr ctrlRingBuffer(
//            new CtrlRingBuffer(mDisplay,
//                               connector,
//                               bufferStorage,
//                               eventRingBuffer,
//                               getDomId(), port, ref));

    CtrlRingBufferPtr ctrlRingBuffer(new CtrlRingBuffer(eventRingBuffer, getDomId(), port, ref));
    addRingBuffer(ctrlRingBuffer);
}


/*******************************************************************************
 * DummyBackend
 ******************************************************************************/
DummyBackend::DummyBackend(DummyDevPtr dummydev,
                            const string& deviceName) :
    BackendBase("DummyBackend", deviceName),
    mDummyDev(dummydev)
{
    // mDummyDev->start();
}

void DummyBackend::onNewFrontend(domid_t domId, uint16_t devId)
{
    addFrontendHandler(FrontendHandlerPtr(
            new DummyFrontendHandler(mDummyDev, getDeviceName(),
                                       getDomId(), domId, devId)));
}
