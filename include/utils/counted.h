/*
 * counted.h
 *
 *  Created on: Apr 30, 2019
 *      Author: mitso23
 */

#ifndef INCLUDE_UTILS_COUNTED_H_
#define INCLUDE_UTILS_COUNTED_H_

/**
 * A simple object for keeping track of objects lifecycle
 */
template<typename T>
struct ObjCounter
{

    ObjCounter() noexcept
        : id(counter.created++)
    {

    }

    ~ObjCounter() noexcept
    {
        ++counter.destroyed;
    }

    ObjCounter(const ObjCounter& rhs) noexcept
        : id(rhs.id)
    {
        ++counter.copyConstructed;
    }

    ObjCounter(ObjCounter&& rhs) noexcept
        : id(rhs.id)
    {
        ++counter.moveConstructed;
    }

    ObjCounter& operator = (const ObjCounter& rhs) noexcept
    {
        id = rhs.id;
        ++counter.assigned;

        return *this;
    }

    ObjCounter& operator = (ObjCounter&& rhs) noexcept
    {
        id = rhs.id;
        ++counter.moveAssigned;

        return *this;
    }

    static void s_Reset()
    {
        counter.created = 0;
        counter.copyConstructed = 0;
        counter.moveConstructed = 0;
        counter.assigned = 0;
        counter.moveAssigned = 0;
        counter.destroyed = 0;
    }

    struct Counter
    {
        unsigned int created;
        unsigned int destroyed;

        unsigned int copyConstructed;
        unsigned int moveConstructed;

        unsigned int assigned;
        unsigned int moveAssigned;
    };

    static Counter counter;
    unsigned int id;
};

template<typename T>
class Counted: public T, public ObjCounter<T>
{
public:
    template<typename ...Args>
    explicit Counted(Args&&... args) : T(std::forward<Args>(args)...)
    {

    }
};

template<typename T> typename ObjCounter<T>::Counter ObjCounter<T>::counter;





#endif /* INCLUDE_UTILS_COUNTED_H_ */
