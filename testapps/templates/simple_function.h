/*
 * simple_function.h
 *
 *  Created on: 4 Nov 2018
 *      Author: mitso23
 */

#ifndef SIMPLE_FUNCTION_H_
#define SIMPLE_FUNCTION_H_

#include <iostream>
#include <memory>
#include <cassert>
using namespace std;


struct ffoo
    {
        ffoo()
        {
            //ptr = std::shared_ptr<int>(new int(10));
        }

        void operator()(int)
        {
            std::cout << "calling ffoo with int " << std::endl;
        }

        void operator()(int, int)
        {
            std::cout << "calling ffoo with int, int" << std::endl;
        }


private:
        std::shared_ptr<int> ptr = std::shared_ptr<int>(new int(10));
    };

struct ffoo2
    {
        ffoo2()
        {

        }

        void operator()(int)
        {
            std::cout << "calling ffoo with int " << std::endl;
        }

        void operator()(int, int)
        {
            std::cout << "calling ffoo with int, int" << std::endl;
        }
    };




template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}


template<typename>
class naive_function;

template<typename ReturnValue, typename ... Args>
class naive_function<ReturnValue (Args...)>
{
public:
    naive_function()
    {

    }

    template<typename T>
    naive_function(T t)
    {

    }

    template <typename T>
    naive_function& operator=(const T& t)
    {
        callable_ = make_unique<CallableT<T>>(t);
        //new(internalStorage)T(t);
        return *this;
    }

    ReturnValue operator()(Args... args) const
    {

        return callable_->Invoke(args...);
    }

private:
    class ICallable
    {
    public:
        virtual ~ICallable() = default;
        virtual ReturnValue Invoke(Args...) = 0;
    };

    template <typename T>
    class CallableT : public ICallable
    {
    public:
        CallableT(const T& t)
        : t_(t)
        {
        }

        ~CallableT() override = default;

        ReturnValue Invoke(Args... args) override
        {
            return t_(args...);
        }

    private:
        T t_;
    };

    std::unique_ptr<ICallable> callable_;
    //ICallable* callable_;
    uint8_t internalStorage[32];
};

template<size_t size>
class StackBasedAllocator
{

public:
    uint8_t* allocate(size_t s)
    {
        if (s > size)
        {
            return nullptr;
        }

        return storage;
    }

private:
    uint8_t storage[size];
};

template<typename Result, typename... Arguments>
struct FunctorHolderBase
{
   virtual Result operator()(Arguments&&... args) = 0;

   virtual void copyInto(void* ) const = 0;

   virtual size_t GetSize() const = 0;

   virtual FunctorHolderBase<Result,Arguments...>* clone(uint8_t* memory) const = 0;

   virtual ~FunctorHolderBase()
   {

   }
};

template<typename F, typename Result, typename...Arguments>
struct FunctorHolder : public FunctorHolderBase<Result, Arguments...>
{
    FunctorHolder(F f_)
        : f(f_)
    {

    }

    Result operator()(Arguments&&... args) override
    {
        return f(std::forward<Arguments>(args)...);
    }

    void copyInto(void* destination) const override
    {
        new(destination)F(f);
    }

    size_t GetSize() const override
    {
        return sizeof(f);
    }

    FunctorHolderBase<Result,Arguments...>* clone(uint8_t* memory) const
    {
        return new(memory)FunctorHolder(f);
    }

    ~FunctorHolder()
    {
       f.~F();
    }

    F f;
};


template<typename, typename Allocator = StackBasedAllocator<32> >
class my_function2;

template<typename Result, typename ... Arguments, class Allocator>
class my_function2<Result(Arguments...), Allocator>
{
public:
    template<typename Functor>
    explicit my_function2(const Functor& f, const Allocator& allocator_ = Allocator())
        : allocator(allocator_)
    {
        std::cout << "constructor " << std::endl;

        uint8_t* memory = allocator.allocate(sizeof(FunctorHolder<Functor,Result, Arguments...>));
        functionHolderBase = new(memory)FunctorHolder<Functor,Result, Arguments...>(f);
    }

    Result operator()(Arguments&&... args)
    {
        (*functionHolderBase)(std::forward<Arguments>(args)...);
    }

    my_function2& operator = (const my_function2& rhs)
    {
        std::cout << "operator = " << rhs.functionHolderBase << std::endl;

        Destroy();

        CloneResource(rhs);

        return *this;
    }

    my_function2& operator = (const my_function2&& rhs)
    {
        std::cout << "move operator = " << rhs.functionHolderBase << std::endl;

        Destroy();

        CloneResource(rhs);

        return *this;
    }

    my_function2(const my_function2& rhs)
    {
        std::cout << "copy constructor " << rhs.functionHolderBase <<  std::endl;

        CloneResource(rhs);
    }

    my_function2(const my_function2&& rhs)
    {
       std::cout << "move constructor " << rhs.functionHolderBase <<  std::endl;

       CloneResource(rhs);
    }

    ~my_function2()
    {
        std::cout << "destructor is called " << functionHolderBase << std::endl;

        Destroy();
    }

private:
    void Destroy()
    {
        if (functionHolderBase)
        {
            functionHolderBase->~FunctorHolderBase();
        }
    }

    void CloneResource(const my_function2& rhs)
    {
        auto size = rhs.functionHolderBase->GetSize();
        allocator = rhs.allocator;
        auto* buffer = allocator.allocate(size);

        functionHolderBase = rhs.functionHolderBase->clone(buffer);
    }

private:
    FunctorHolderBase<Result, Arguments...>* functionHolderBase = nullptr;
    Allocator allocator;
};


template<typename>
class my_function;

template<typename Result, typename ... Arguments>
class my_function<Result(Arguments...)>
{
public:
    template<typename Functor>
    my_function(const Functor& f)
        : invokePtr (reinterpret_cast<invokePtr_t>(invoke<Functor>))
        , createPtr(reinterpret_cast<createPtr_t>(create<Functor>))

    {
        createPtr(&storage[0], &f);
    }

    Result operator()(Arguments&&... args)
    {
        invokePtr(storage, std::forward<Arguments>(args)...);
    }

private:
    using invokePtr_t = Result(*)(void*, Arguments&&...);
    using createPtr_t = void(*)(void*, const void*);
    using destroyPtr_t = void(*)(void*);

    invokePtr_t invokePtr;
    createPtr_t createPtr;
    destroyPtr_t destroyPtr;
    uint8_t storage[16];

    template<typename Functor>
    static Result invoke(Functor* f, Arguments&&... args)
    {
        return (*f)(std::forward<Arguments>(args)...);
    }

    template<typename Functor>
    static void create(Functor* destination, Functor* source)
    {
        new(destination)ffoo(*source);
    }
};


#endif /* SIMPLE_FUNCTION_H_ */
