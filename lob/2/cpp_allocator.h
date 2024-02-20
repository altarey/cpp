#pragma once

#pragma once

#include <cstddef> // For size_t
#include <new>     // For bad_alloc and ::operator new, ::operator delete
#include <utility> // For pair
#include <string>  // For string

#include "log.h"

using namespace std;

template <typename T>
class CPP_Allocator {
private:
    size_t allocatedMemory{};
    size_t deallocatedMemory{};
public:
    using value_type = T;

    CPP_Allocator() {
        //log("CPP_Allocator::ctor");
    };

    ~CPP_Allocator() {
        // log("CPP_Allocator::dtor");
        if (allocatedMemory > 0) {
          const string message = "Allocated: " + to_string(allocatedMemory) +
                                 ", Deallocated: " + to_string(deallocatedMemory);
          log(message);
        }
    }

    template <class U>
    constexpr explicit CPP_Allocator(const CPP_Allocator<U>&) noexcept {}

    T* allocate(const size_t n) {
        allocatedMemory += n * sizeof(T);
        return nullptr;
    }

    void deallocate(T* p, const size_t n) noexcept {
        deallocatedMemory += n * sizeof(T);
    }
};

template <class T, class U>
bool operator==(const CPP_Allocator<T>&, const CPP_Allocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const CPP_Allocator<T>&, const CPP_Allocator<U>&) { return false; }
