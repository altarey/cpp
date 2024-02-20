#pragma once

#include <cstdlib> // For malloc and free
#include <new>     // For bad_alloc
#include <utility> // For pair
#include <string>  // For string

#include "log.h"
#include "guid.h"

using namespace std;

template <typename T>
class C_Allocator {
private:
    size_t allocatedMemory{0};
    size_t deallocatedMemory{0};
    const string guid{makeGuid()};
public:
    using value_type = T;

    C_Allocator()
    {
        //log("C_Allocator::ctor (" + guid + ")");
    };

    ~C_Allocator()
    {
        //log("C_Allocator::dtor (" + guid + ")");
        if (allocatedMemory > 0) {
          const string message = "Allocated: " + to_string(allocatedMemory) +
                                 ", Deallocated: " + to_string(deallocatedMemory);
          log(message);
        }
    }

    template <class U>
    constexpr explicit C_Allocator(const C_Allocator<U>&) noexcept
    {

    }

    T* allocate(const size_t n) {
        if (n > static_cast<size_t>(-1) / sizeof(T)) {
            throw bad_alloc();
        }

        if (auto p = static_cast<T*>(malloc(n * sizeof(T)))) {
            allocatedMemory += n * sizeof(T);
            return p;
        }

        throw bad_alloc();
    }

    void deallocate(T* p, const size_t n) noexcept {
        free(p);
        deallocatedMemory += n * sizeof(T);
    }
};

template <class T, class U>
bool operator==(const C_Allocator<T>&, const C_Allocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const C_Allocator<T>&, const C_Allocator<U>&) { return false; }