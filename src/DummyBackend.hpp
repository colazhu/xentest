/*
 *  Dummy backend
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * Copyright (C) 2016 EPAM Systems Inc.
 */

#ifndef DUMMYBACKEND_HPP_
#define DUMMYBACKEND_HPP_

#include <string>
#include <xen/be/BackendBase.hpp>
#include <xen/be/FrontendHandlerBase.hpp>
#include <xen/be/RingBufferBase.hpp>
#include <xen/be/Log.hpp>
#include <xen/io/dummyif.h>
#include "DummyRingBuffer.hpp"
#include "DummyDev.hpp"

/***************************************************************************//**
 * Dummy frontend handler.
 * @ingroup dummy_be
 ******************************************************************************/
class DummyFrontendHandler : public XenBackend::FrontendHandlerBase
{
public:

    /**
     * @param DummyDevPtr   dummydev
     * @param backend   backend instance
     * @param domId     frontend domain id
     * @param devId     frontend device id
     */
    DummyFrontendHandler(DummyDevPtr dummydev,
                           const std::string& devName,
                           domid_t beDomId, domid_t feDomId, uint16_t devId);

protected:
    /**
     * Is called on connected state when ring buffers binding is required.
     */
    void onBind() override;

private:
    DummyDevPtr mDummyDev;
    XenBackend::Log mLog;

    void createConnector(const std::string& conPath, int conIndex);
//    void createConnector(const std::string& streamPath, int conIndex,
//                         BuffersStoragePtr bufferStorage);
};

/***************************************************************************//**
 * Dummy backend class.
 * @ingroup dummy_be
 ******************************************************************************/
class DummyBackend : public XenBackend::BackendBase
{
public:
    /**
     * @param dummydev      dummy device
     * @param deviceName    device name
     */
    DummyBackend(DummyDevPtr dummydev,
                const std::string& deviceName);

protected:
    /**
     * Is called when new dummy frontend appears.
     * @param domId domain id
     * @param devId device id
     */
    void onNewFrontend(domid_t domId, uint16_t devId);

private:
    DummyDevPtr mDummyDev;
};

#endif /* DUMMYBACKEND_HPP_ */
