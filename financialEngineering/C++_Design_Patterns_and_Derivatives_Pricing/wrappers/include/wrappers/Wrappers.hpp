#ifndef WRAPPERS_H
#define WRAPPERS_H
#include <memory>

template <class T>
class Wrapper
{
public:
    Wrapper()
    {
        dataPtr = 0;
    }

    Wrapper(const T &inner)
    {
        dataPtr = inner.clone();
    }

    Wrapper(std::unique_ptr<T> otherDataPtr)
    {
        dataPtr = std::move(otherDataPtr);
    }

    ~Wrapper()
    {
        if (dataPtr != 0)
            dataPtr.reset();
    }

    Wrapper(const Wrapper<T> &original)
    {
        if (original.dataPtr != 0)
            dataPtr = original.dataPtr->clone();
        else
            dataPtr = 0;
    }

    Wrapper &operator=(const Wrapper<T> &original)
    {
        if (this != &original)
        {
            if (dataPtr != 0)
                dataPtr.reset();
            dataPtr = (original.dataPtr != 0) ? original.dataPtr->clone() : 0;
        }

        return *this;
    }

    T &operator*()
    {
        return *dataPtr.get();
    }

    const T &operator*() const
    {
        return *dataPtr.get();
    }

    const T *const operator->() const
    {
        return dataPtr.get();
    }

    T *operator->()
    {
        return dataPtr.get();
    }

private:
    std::unique_ptr<T> dataPtr;
};

#endif