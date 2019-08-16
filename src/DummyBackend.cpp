#include "DummyBackend.hpp"
#include <algorithm>
#include <vector>
#include <xen/be/XenStore.hpp>


/*******************************************************************************
 * DummyFrontendHandler
 ******************************************************************************/

void DummyFrontendHandler::onBind()
{
    LOG(mLog, DEBUG) << "On frontend bind : " << getDomId();
    // BuffersStoragePtr buffersStorage(new BuffersStorage(getDomId(), mDisplay));

    string conBasePath = getXsFrontendPath() + "/";
    int conIndex = 0;

    while(getXenStore().checkIfExist(conBasePath + to_string(conIndex)))
    {
        LOG(mLog, DEBUG) << "Found connector: " << conIndex;

//        createConnector(conBasePath + to_string(conIndex) + "/",
//                        conIndex, buffersStorage);

        conIndex++;
    }
}

//void DummyFrontendHandler::createConnector(const string& conPath,
//                                             int conIndex,
//                                             BuffersStoragePtr bufferStorage)
//{
//    evtchn_port_t port = getXenStore().readInt(conPath +
//                                               XENDISPL_FIELD_EVT_CHANNEL);

//    uint32_t ref = getXenStore().readInt(conPath +
//                                         XENDISPL_FIELD_EVT_RING_REF);

//    EventRingBufferPtr eventRingBuffer(new EventRingBuffer(conIndex, getDomId(),
//            port, ref, XENDISPL_IN_RING_OFFS, XENDISPL_IN_RING_SIZE));

//    addRingBuffer(eventRingBuffer);

//    port = getXenStore().readInt(conPath + XENDISPL_FIELD_REQ_CHANNEL);

//    ref = getXenStore().readInt(conPath + XENDISPL_FIELD_REQ_RING_REF);

//    auto id = getXenStore().readString(conPath + XENDISPL_FIELD_UNIQUE_ID);

//    auto connector = mDisplay->createConnector(id);

//    CtrlRingBufferPtr ctrlRingBuffer(
//            new CtrlRingBuffer(mDisplay,
//                               connector,
//                               bufferStorage,
//                               eventRingBuffer,
//                               getDomId(), port, ref));

//    addRingBuffer(ctrlRingBuffer);
//}


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
