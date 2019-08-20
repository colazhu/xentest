#ifndef DUMMYDEV_HPP_
#define DUMMYDEV_HPP_

#include <xen/be/RingBufferBase.hpp>
#include <xen/be/Log.hpp>

class DummyDev {
public:
    DummyDev();
};

typedef std::shared_ptr<DummyDev> DummyDevPtr;
#endif
