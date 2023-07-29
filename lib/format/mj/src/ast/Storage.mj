#pragma once


/// An `MjStorage` object is a memory backing for compile time emulation and execution as well as for storing raw data.
/// It provides methods for detecting overlap and modification or exclusive access to data. This allows assumptions to be
/// made about the data.
class MjStorage {
private:
    MjStorage *owner; // If non-null, the storage is managed by the other storage object
    void *data_;      // The storage data
public:


    MjStorage(
        u32 size
     ) {
        u8 *ptr;
        Memory::allocate<u8>(ptr, size);
        data_ = ptr;
    }


    MjStorage(
        MjStorage &owner,
        u32 offset
    ) :
        data_(owner.data<u8>() + offset)
    {}


    ~MjStorage() {
        if (!owner) {
            Memory::free(data_);
        }
    }


    template<class T>
    T *data() {
        return data_;
    }


    bool is_owned() const {
        return owner;
    }
};
