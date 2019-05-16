/*

Usage examples (modulo addresses / credentials).

UNIX domain socket transport:

 Server:
   $ ./gdbus-example-peer --server --address unix:abstract=myaddr
   Server is listening at: unix:abstract=myaddr
   Client connected.
   Peer credentials: GCredentials:unix-user=500,unix-group=500,unix-process=13378
   Negotiated capabilities: unix-fd-passing=1
   Client said: Hey, it's 1273093080 already!

 Client:
   $ ./gdbus-example-peer --address unix:abstract=myaddr
   Connected.
   Negotiated capabilities: unix-fd-passing=1
   Server said: You said 'Hey, it's 1273093080 already!'. KTHXBYE!

Nonce-secured TCP transport on the same host:

 Server:
   $ ./gdbus-example-peer --server --address nonce-tcp:
   Server is listening at: nonce-tcp:host=localhost,port=43077,noncefile=/tmp/gdbus-nonce-file-X1ZNCV
   Client connected.
   Peer credentials: (no credentials received)
   Negotiated capabilities: unix-fd-passing=0
   Client said: Hey, it's 1273093206 already!

 Client:
   $ ./gdbus-example-peer -address nonce-tcp:host=localhost,port=43077,noncefile=/tmp/gdbus-nonce-file-X1ZNCV
   Connected.
   Negotiated capabilities: unix-fd-passing=0
   Server said: You said 'Hey, it's 1273093206 already!'. KTHXBYE!

TCP transport on two different hosts with a shared home directory:

 Server:
   host1 $ ./gdbus-example-peer --server --address tcp:host=0.0.0.0
   Server is listening at: tcp:host=0.0.0.0,port=46314
   Client connected.
   Peer credentials: (no credentials received)
   Negotiated capabilities: unix-fd-passing=0
   Client said: Hey, it's 1273093337 already!

 Client:
   host2 $ ./gdbus-example-peer -a tcp:host=host1,port=46314
   Connected.
   Negotiated capabilities: unix-fd-passing=0
   Server said: You said 'Hey, it's 1273093337 already!'. KTHXBYE!

TCP transport on two different hosts without authentication:

 Server:
   host1 $ ./gdbus-example-peer --server --address tcp:host=0.0.0.0 --allow-anonymous
   Server is listening at: tcp:host=0.0.0.0,port=59556
   Client connected.
   Peer credentials: (no credentials received)
   Negotiated capabilities: unix-fd-passing=0
   Client said: Hey, it's 1273093652 already!

 Client:
   host2 $ ./gdbus-example-peer -a tcp:host=host1,port=59556
   Connected.
   Negotiated capabilities: unix-fd-passing=0
   Server said: You said 'Hey, it's 1273093652 already!'. KTHXBYE!

 */

#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>

/* ---------------------------------------------------------------------------------------------------- */

static GDBusNodeInfo *introspection_data = NULL;

/* Introspection data for the service we are exporting */
static const gchar introspection_xml[] =
  "<node>"
  "  <interface name='org.gtk.GDBus.TestPeerInterface'>"
  "    <method name='HelloWorld'>"
  "      <arg type='s' name='greeting' direction='in'/>"
  "      <arg type='s' name='response' direction='out'/>"
  "    </method>"
  "  </interface>"
  "</node>";

/* ---------------------------------------------------------------------------------------------------- */

static void
handle_method_call (GDBusConnection       *connection,
                    const gchar           *sender,
                    const gchar           *object_path,
                    const gchar           *interface_name,
                    const gchar           *method_name,
                    GVariant              *parameters,
                    GDBusMethodInvocation *invocation,
                    gpointer               user_data)
{
  if (g_strcmp0 (method_name, "HelloWorld") == 0)
    {
      const gchar *greeting;
      gchar *response;

      g_variant_get (parameters, "(&s)", &greeting);
      response = g_strdup_printf ("You said '%s'. KTHXBYE!", greeting);
      g_dbus_method_invocation_return_value (invocation,
                                             g_variant_new ("(s)", response));
      g_free (response);
      g_print ("Client said: %s\n", greeting);
    }
}

static const GDBusInterfaceVTable interface_vtable =
{
  handle_method_call,
  NULL,
  NULL,
};

/* ---------------------------------------------------------------------------------------------------- */

static gboolean
on_new_connection (GDBusServer *server,
                   GDBusConnection *connection,
                   gpointer user_data)
{
  guint registration_id;
  GCredentials *credentials;
  gchar *s;

  credentials = g_dbus_connection_get_peer_credentials (connection);
  if (credentials == NULL)
    s = g_strdup ("(no credentials received)");
  else
    s = g_credentials_to_string (credentials);


  g_print ("Client connected.\n"
           "Peer credentials: %s\n"
           "Negotiated capabilities: unix-fd-passing=%d\n",
           s,
           g_dbus_connection_get_capabilities (connection) & G_DBUS_CAPABILITY_FLAGS_UNIX_FD_PASSING);

  g_object_ref (connection);
  registration_id = g_dbus_connection_register_object (connection,
                                                       "/org/gtk/GDBus/TestObject",
                                                       introspection_data->interfaces[0],
                                                       &interface_vtable,
                                                       NULL,  /* user_data */
                                                       NULL,  /* user_data_free_func */
                                                       NULL); /* GError** */
  g_assert (registration_id > 0);

  return TRUE;
}

/* ---------------------------------------------------------------------------------------------------- */

void merge(unsigned* outBuffer, unsigned* leftBuffer, unsigned leftBufferSize, unsigned* rightBuffer, unsigned rightBufferSize)
{
	unsigned int leftStart= 0;
	unsigned int rightStart = 0;

	while(leftStart < leftBufferSize && rightStart < rightBufferSize)
	{
		if (leftBuffer[leftStart] < rightBuffer[rightStart])
		{
			std::cout << "copy left: " << leftBuffer[leftStart] << std::endl;
			*outBuffer++ = leftBuffer[leftStart];
			++leftStart;
		}
		else
		{
			std::cout << "copy right: " << rightBuffer[rightStart] << std::endl;

			*outBuffer++ = rightBuffer[rightStart];
			++rightStart;
		}
	}

	while(leftStart < leftBufferSize)
	{
		std::cout << "copy left: " << leftBuffer[leftStart] << std::endl;

		*outBuffer++ = leftBuffer[leftStart++];
	}

	while(rightStart < rightBufferSize)
	{
		std::cout << "copy right: " << rightBuffer[rightStart] << std::endl;

		*outBuffer++ = rightBuffer[rightStart++];
	}
}

void mergeSort(unsigned* buffer, unsigned start, unsigned end)
{
	std::cout << "start: " << start << " end: " << end << std::endl;

	if (start == end)
	{
		std::cout << "return" << std::endl;
		return;
	}

	unsigned int middle = start + (end - start)/2;
	mergeSort(buffer, start, middle);
	mergeSort(buffer, middle + 1, end);

	unsigned leftSize = middle - start + 1;
	unsigned rightSize = end - (middle + 1) + 1;

	std::cout << "leftSize: " << leftSize << " rightSize: " << rightSize << std::endl;

	unsigned int leftBuffer[leftSize];
	unsigned int rightBuffer[rightSize];

	memcpy(leftBuffer, buffer + start, leftSize * sizeof(unsigned));
	memcpy(rightBuffer, buffer + middle + 1, rightSize * sizeof(unsigned));

	merge(buffer + start, leftBuffer, leftSize, rightBuffer, rightSize);

}

#include <iostream>

unsigned int getMinValue(unsigned int* arr, unsigned start, unsigned end)
{
	unsigned min = arr[start];

	for(unsigned int i=start; i<=end;++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}

	return min;
}

unsigned int getMaxValue(unsigned int* arr, unsigned start, unsigned end)
{
	unsigned max = arr[start];

	for(unsigned int i=start; i<=end;++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	return max;
}

unsigned int print(unsigned int* arr, unsigned start, unsigned mid , unsigned end)
{
	for(unsigned int i=start; i <=mid; ++i)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << " + ";

	for(unsigned int i=mid + 1; i<=end; ++i)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;

	return 0;
}

void find_min_max_meets_conditions(unsigned* arr, unsigned size, unsigned value)
{
	if (size == 1)
	{
		return;
	}
	else if (size == 2)
	{
		if (arr[0] + arr[1] <= value)
		{
			std::cout << arr[0] << "+" << arr[1] << std::endl;
		}
	}

	unsigned int end = size - 1;
	unsigned int mid = size - 2;
	unsigned int start = 0;

	for(unsigned int i=mid; i>=0; --i)
	{

		auto maxValue = getMaxValue(arr, 0, i);
		auto minValue = getMinValue(arr, i + 1, end);

		std::cout << "min: " << minValue << " max: " << maxValue << " i: " << i << std::endl;

		if (minValue + maxValue < value)
		{
			print(arr, start, i, end);
		}

		if (i == 0)
			break;
	}
}

#include "utils/Noisy.h"
#include <memory>

class SharedPtrSingleton
{

public:
	static std::shared_ptr<Noisy> Get()
	{
		if (!n)
		{
			n = std::shared_ptr<Noisy>(new Noisy());
		}

		return n;
	}
private:
	static std::shared_ptr<Noisy> n;
};

std::shared_ptr<Noisy> SharedPtrSingleton::n;

class B
{
public:
	B()
	{
		m_n = SharedPtrSingleton::Get();
	}

	~B()
	{
		std::cout << "B is dying" << std::endl;
		m_n->getData();
	}

private:
	std::shared_ptr<Noisy> m_n;
};

class A
{
public:
	A()
	{
		m_n = SharedPtrSingleton::Get();
	}
	~A()
	{
		std::cout << "A is dying" << std::endl;
		m_n->getData();
	}

private:
	std::shared_ptr<Noisy> m_n;
};

static B b;
static A a;

#include <map>

class ICasProvider
{

public:
	virtual void Activate() = 0;

	virtual void Authorize() = 0;

	virtual bool isCloud() const = 0;

	virtual ~ICasProvider()
	{

	}
};

template <typename Communicator, typename Handler>
class CasProvider : public ICasProvider
{

public:
	CasProvider(Communicator& comm) :
		m_comm(comm)
	{

	}

	void Activate() override
	{
		static_cast<Handler*>(this)->Activate();
	}

	void Authorize() override
	{
		static_cast<Handler*>(this)->Authorize();
	}

	Communicator& GetCommunicator()
	{
		return m_comm;
	}

	Communicator& m_comm;
};


class DongleProvider : public CasProvider<DongleProvider, DongleProvider>
{
public:
	DongleProvider() : CasProvider(*this)
	{

	};

	bool isCloud() const override
	{
		return false;
	}

	void Activate() override
	{
		std::cout << "activating using the dongle provider: " << std::endl;
	}

	void Authorize() override
	{
		std::cout << "authorising using the dongle provider: " << std::endl;
	}

	///Information regarding the Communicator
	int getDongleInfo()
	{
		std::cout << "getting dongle info " << std::endl;
		return 1;
	}
};

struct CloudCommunicator
{
	void Ping()
	{
		std::cout << "ping from the cloud" << std::endl;
	}
};

class CloudProvider : public CasProvider<CloudCommunicator, CloudProvider>
{
public:
	CloudProvider() : CasProvider(*(new CloudCommunicator()))
	{

	}

	bool isCloud() const override
	{
	 return true;
	}

	void Activate()
	{
		std::cout << "activating using the cloud provider: " << std::endl;
	}

	void Authorize()
	{
		std::cout << "authorising using the dongle provider: " << std::endl;
	}
};

/**
 * @brief default deleter class for resources that have been allocated using new
 */
template<typename T>
struct DefaultNewDeleter
{
	DefaultNewDeleter()
	{

	}

	template <typename Y>
	//NOTE: this is necessary so we can assign a deleter of type DefaultNewDeleter<Base> p = DefaultNewDeleter<Derived>
	DefaultNewDeleter(const DefaultNewDeleter<Y>&)
	{

	}

	void operator ()(T* ptr)
    {
        if (ptr)
        {
            delete ptr;
        }
    }
};

template<typename T>
struct DefaultNewArrayDeleter
{
	DefaultNewArrayDeleter()
	{

	}

	template <typename Y>
	DefaultNewArrayDeleter(const DefaultNewDeleter<Y>&)
	{

	}

    void operator ()(T* ptr)
    {
        if (ptr)
        {
            delete[] ptr;
        }
    }
};

/**
 * @brief default deleter class for resources that have been allocated using malloc/calloc
 */
template<typename T>
struct DefaultMallocDeleter
{
	DefaultMallocDeleter()
	{

	}

	template <typename Y>
	DefaultMallocDeleter(const DefaultNewDeleter<Y>&)
	{

	}

    void operator ()(T* ptr)
    {
        if (ptr)
        {
            free(ptr);
        }
    }
};

/**
 * @brief the purpose of this class is to allow to perform simple bindings (this pointer and an argument)
 * allowing us to use member functions as custom deleters when using scoped lock with a custom deleter
 */
template<typename T, typename F, typename Arg1>
class Bind
{
public:
    /**
     * @brief Constructor
     * @param [in] f the function call back
     * @param [in] thisPtr the this pointer where f is member of
     */
    Bind(F f, T* thisPtr) : m_thisPtr(thisPtr), m_f(f)
    {

    }

    /**
     * @brief operator() implementation
     * @param [in] argument the passed in argument that the call back function will be called with
     */
    void operator()(Arg1* argument)
    {
        (m_thisPtr->*m_f)(argument);
    }

private:
    T* m_thisPtr;       /**< The this pointer where m_f is member of*/
    F m_f;              /**< Function call back*/
};

template <class T>
struct custom_remove_reference
{
    typedef T type;
};

template <class T>
struct custom_remove_reference<T&>
{
    typedef T type;
};

template <class T>
struct custom_remove_reference<T&&>
{
    typedef T type;
};

template <class T, class U>
struct custom_is_same
{
    bool operator()()
    {
        return false;
    }

};

template <class T>
struct custom_is_same<T, T>
{
    bool operator()()
    {
        return true;
    }
};

template< class T >
typename custom_remove_reference<T>::type&& custom_move(T&& t )
{
    return static_cast<typename custom_remove_reference<T>::type&&>(t);
}

template<typename T, typename F=DefaultNewDeleter<T> >
class ScopedPtr
{
public:
    /**
     * @brief default constructor
     */
    ScopedPtr() : m_ptr(NULL)
    {

    }

    /**
     * @brief Constructor
     * @param [in] ptr the raw resource that this class is going to own and manage
     */
    explicit ScopedPtr(T* ptr) : m_ptr(ptr)
    {

    }

    /**
     * @brief Constructor
     * @param [in] ptr the raw resource that this class is going to own and manage
     * @remarks to simplify the implementation we assume that the custom deleter is copyable
     * @remarks if you want to copy be reference then use std::ref
     * @param [in] f a custom deleter function
     */
    explicit ScopedPtr(T* ptr, F f) : m_ptr(ptr), m_callback(f)
    {

    }

    /**
     * @brief operator! implementation
     * @return true if the underlying pointer is not NULL or false if not
     */
    bool operator !() const
    {
        return !m_ptr;
    }

    /**
     * @brief implicit convertion of this class to bool
     */
    operator bool() const
    {
        return (m_ptr != NULL);
    }

    /**
     * @brief free the current resource and reassign it with the newly provided one
     * @param [in] the new pointer that this class is going to manage
     */
    void Reset(T* ptr)
    {
        m_FreeResource();
        m_ptr = ptr;
    }

    /**
     * @return the underlying raw resource
     */
    T* Get() const
    {
        return m_ptr;
    }

    /**
     * @brief restore the ownership back to the caller
     * @return the underlying raw resource
     */
    T* Release()
    {
        T* temp = m_ptr;
        m_ptr = NULL;
        return temp;
    }

    /**
     * @return the custom deleter functor
     */
    F GetDeleter() const
    {
        return m_callback;
    }

    /**
     * @brief operator* implementation
     */
    T* operator->() const
    {
        return m_ptr;
    }

    /**
     * @brief operator* implementation
     */
    T& operator*() const
    {
        return *m_ptr;
    }

    /**
     * @brief destructor
     */
    ~ScopedPtr()
    {
        m_FreeResource();
    }

    ScopedPtr(ScopedPtr&& rhs)
            : m_ptr(nullptr)
    		, m_callback(custom_move(rhs.m_callback))
    {
    	std::cout << "Move constructor has been called " << std::endl;
        Reset(rhs.Release());
    }

    template<typename Y, typename D>
    ScopedPtr(ScopedPtr<Y, D>&& rhs)
                : m_ptr(nullptr)
                , m_callback(custom_move(rhs.GetDeleter()))
	{
    	std::cout << "Move constructor with Y has been caleed " << std::endl;
		Reset((rhs.Release()));
	}

    ScopedPtr& operator=(ScopedPtr&& rhs)
    {
    	std::cout << "operator = " << std::endl;
        Reset(rhs.Release());
        m_callback = custom_move(rhs.GetDeleter());
        return *this;
    }

    template<typename Y, typename D>
    ScopedPtr& operator=(ScopedPtr<Y, D>&& rhs)
	{
       std::cout << "operator = Y" << std::endl;
	   Reset((rhs.Release()));
	   m_callback = custom_move(rhs.GetDeleter());
	   return *this;
	}

private:
    /**
     * @brief free the managed resource
     */
    void m_FreeResource()
    {
        if (m_ptr)
        {
            m_callback(m_ptr);
            m_ptr = NULL;
        }
    }
private:
    /**
     * @brief disable copying
     */
    ScopedPtr(const ScopedPtr& rhs);

    /**
     * @brief disable assignment operator
     */
    ScopedPtr& operator=(const ScopedPtr&rhs);
protected:
    T* m_ptr;               /**< The raw pointer that we are managing*/
    F m_callback;           /**< Callback function for releasing the resource*/
};

class Base
{
public:
	virtual ~Base()
	{
		std::cout << "base destructor is called " << std::endl;
	}
};

class Derived : public Base
{

public:
	~Derived()
	{
		std::cout << " derived destructor is called " << std::endl;
	}
};

template<typename T>
struct CustomNewDeleter
{
	CustomNewDeleter(bool* deleted) : m_deleted(deleted)
	{
		std::cout << "non default constructor called " << std::endl;
	}

	void operator ()(T* ptr)
    {
        if (ptr)
        {
        	std::cout << "Custom delete operator has been called" << std::endl;
        	delete ptr;

        	if (m_deleted)
        	{
        		std::cout << "setting the flag " << std::endl;
        		*m_deleted = true;
        	}
        }
    }

	bool* m_deleted = nullptr;
};

void testMove(ScopedPtr<Base> b)
{

}

bool binary_search(int* arr, int size, int value)
{
	int start = 0;
	int end = size - 1;

	while(start <= end)
	{
		int mid = start + (end - start)/2;

		std::cout << "mid: " << mid << " start: " << start << " end: " << end << std::endl;

		if (arr[mid] == value)
		{
			return true;
		}
		else if (value < arr[mid])
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}

	return false;
}

class Object
{

};

template<typename T>
class Factory
{
public:
	std::unique_ptr<T> Create()
	{
		return std::unique_ptr<T>(new T());
	}
};

template<typename T>
void foo(Factory<T>& f)
{
	auto o = f.Create();
}

class Skata
{
public:
	template<typename T>
	Skata(Factory<T>& f)
	{

	}
};

void swap(int* l, int* r)
{
    int temp = *l;
    *l = *r;
    *r = temp;
}


int partition(int* arr, int start, int end)
{
    //std::cout << "start: " << start << " end: " << end <<std::endl;
    int pivot = end;
    int i = start - 1;
    int swapLoc = start;

    while(i + 1< end)
    {
        ++i;

        if (arr[i] <= arr[pivot])
        {
            if (i != swapLoc)
            {
                //std::cout << "swapping " << arr[i] << " with: " << arr[swapLoc] << std::endl;
                swap(&arr[i], &arr[swapLoc]);
            }
            ++swapLoc;

            //std::cout << "swap loc: " << swapLoc << std::endl;
        }
    }

    swap(&arr[pivot], &arr[swapLoc]);

    //std::cout << "returning pivot " << swapLoc << std::endl;

    return swapLoc;
}

void sort(int* arr, int start, int end)
{
    if (start <= end)
    {
        int pivot = partition(arr, start, end);
        sort(arr, start, pivot -1);
        sort(arr, pivot + 1, end);
    }
}

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct EvenNumbers
{
    unsigned int evenFreq[36];
    unsigned int size = 0;
};

struct OddNumbers
{
    unsigned int oddFreq[36];
    unsigned int size = 0;
    unsigned int numberOnes = 0;
};

struct stringView
{
    const char* str;
    unsigned int len;
};


// N = 0 R = 1
// (N*16 + R)*res mod 16 = N*res + R*res/16
unsigned long long int calculatePermutations(unsigned int n)
{
    if (n == 1)
    {
        return 1;
    }

    unsigned int N = 0;
    unsigned int R = 1;
    unsigned int MAX = (1000000000 + 7);
    //unsigned int MAX = 16;

    for(unsigned int i=2; i<=n; ++i)
    {
        N = N * i;
        N+= (R*i) / MAX;
        R = (R * i) % MAX;
    }

    return R;
}

void CalculateLettersFrequency(stringView& view, unsigned int characterFreq[36])
{
    for(unsigned int i=0; i< view.len; ++i)
    {
        ++characterFreq[view.str[i] - 'a'];
    }
}


// O odds E even

// 3 odd numbers and 2 even
// 3*(1*2*3*4) = 3*(3+2 -1)! = O * (O + E - 1)!

// 3 odds
// 3! 1*2*3 O!

// 3 even
// 3! 1*2*3 E!

// N ones and E evens
// 11(22)(33)(44) 2 * ( 1*2*3) = N*(E!)
unsigned long long CreateHistogram(unsigned int characterFreq[36])
{
    EvenNumbers evenNumbers;
    OddNumbers oddNumbers;

    for(unsigned int i=0; i< 36; ++i)
    {
        if (characterFreq[i] != 0)
        {
            if (characterFreq[i] & 1)
            {
                if(characterFreq[i] == 1)
                {
                    ++oddNumbers.numberOnes;
                }
                else
                {
                    oddNumbers.oddFreq[oddNumbers.size++] = characterFreq[i];
                }
            }
            else
            {
                evenNumbers.evenFreq[evenNumbers.size++] = characterFreq[i] ;
            }
        }
    }

    // O odds E even
    // 3 odd numbers and 2 even
    // 3*(1*2*3*4) = 3*(3+2)! = O * (O + E)!
    if (evenNumbers.size != 0 && oddNumbers.size != 0)
    {
        return oddNumbers.size * calculatePermutations(evenNumbers.size + oddNumbers.size) +
               oddNumbers.numberOnes*calculatePermutations(evenNumbers.size + oddNumbers.size);
    }
    else if (oddNumbers.size != 0)
    {
        return calculatePermutations(oddNumbers.size) + oddNumbers.numberOnes;
    }
    else if (evenNumbers.size != 0 && oddNumbers.numberOnes == 0)
    {
        return calculatePermutations(evenNumbers.size);
    }
    else if (oddNumbers.numberOnes != 0 && evenNumbers.size != 0)
    {
        auto res = oddNumbers.numberOnes * calculatePermutations(evenNumbers.size);
    }
    else if (oddNumbers.numberOnes !=0 && evenNumbers.size == 0)
    {
        //abc max number of palindromes are a, b, c
        return oddNumbers.numberOnes;
    }

    return 0;
}

unsigned long long Calculate(const char* str, unsigned l, unsigned r)
{
    // hello l=2 an r=4
    // ell
    const char* subStr = str + (l - 1);
    stringView strView = { subStr, r - l + 1 };
    unsigned int characterFreq[36];
    memset(characterFreq, 0, sizeof(characterFreq));

    CalculateLettersFrequency(strView, characterFreq);
    return CreateHistogram(characterFreq);
}

int main (int argc, char *argv[])
{

    //calculatePermutations(10);

#if 0
    //ones but no evens
    {
        char str[] = "abc";
        //std::cout << "abc max perm: " << Calculate(str, 1, 3) << std::endl;
        if (Calculate(str, 1, 3) != 3)
        {

            //std::cerr << "abc" << std::endl;
            exit(1);
        }
    }

    //even + odds
    {
           char str[] = "cccbbbaa";
           //std::cout << "cccbbbaa max perm: " << Calculate(str, 1, strlen(str)) << std::endl;
           if (Calculate(str, 1, strlen(str)) != 4)
           {
              std::cerr << "cccbbbaa" << std::endl;
              exit(1);
           }
    }

    //even + odds + ones
    {
          char str[] = "cccbbbaagkl";
          //std::cout << "cccbbbaa max perm: " << Calculate(str, 1, strlen(str)) << std::endl;
          if (Calculate(str, 1, strlen(str)) != (4+3))
          {
             std::cerr << "cccbbbaagkl" << std::endl;
             exit(1);
          }
    }

    //only odds
    {
         char str[] = "ccbbaaddabcd";
         //std::cout << "cccbbbaa max perm: " << Calculate(str, 1, strlen(str)) << std::endl;
         if (Calculate(str, 1, strlen(str)) != 24)
         {
            std::cerr << "ccbbaaddabcd" << std::endl;
            exit(1);
         }
    }

    //only even
    {
        char str[] = "ccbbaadd";
        //std::cout << "cccbbbaa max perm: " << Calculate(str, 1, strlen(str)) << std::endl;
        if (Calculate(str, 1, strlen(str)) != 24)
        {
           std::cerr << "ccbbaadd" << std::endl;
           exit(1);
        }
    }

    //ones with even
    {
        char str[] = "week";
        //std::cout << "cccbbbaa max perm: " << Calculate(str, 1, strlen(str)) << std::endl;
        if (Calculate(str, 1, 4) != 2)
        {
           std::cerr << "week" << std::endl;
           exit(1);
        }
    }

    //ones with odd
    {
        char str[] = "weeek";
        //std::cout << "cccbbbaa max perm: " << Calculate(str, 1, strlen(str)) << std::endl;
        if (Calculate(str, 1, 4) != 2)
        {
           std::cerr << "week" << std::endl;
           exit(1);
        }
    }


    {
        /////////////// 12345678901234567890123456
        char str[27] = "wuhmbspjnfviogqzldrcxtaeyk";
        std::cout << "max perm: " << Calculate(str, 4, 5) << std::endl;
    }
    std::cout << "pass" << std::endl;

#endif


    std::ifstream input("input.txt");
    std::ifstream result("result.txt");

    if (input.bad() || result.bad())
    {
        std::cerr << "shit" << std::endl;
        exit(1);
    }

    char str[] = "wldsfubcsxrryqpqyqqxrlffumtuwymbybnpemdiwyqz";
    std::string inputLine;
    std::string currentResult;

    //auto nPerm = Calculate(str, 14, 24);

#if 1
    unsigned pass = 0;
    unsigned fail = 0;
    while(input.good() && result.good())
    {
        input >> inputLine;
        auto l = std::atoi(inputLine.c_str());
        input >> inputLine;
        auto r = std::atoi(inputLine.c_str());

        result >> currentResult;
        auto res = std::atoi(currentResult.c_str());

        auto nPerm = Calculate(str, l, r);

        if (nPerm != res)
        {
            ++fail;
            std::cout <<  "l: " << l << " r: " << r << " fail, expected: "<< res << " got: " << nPerm << std::endl;
        }
        else
        {
            ++pass;
            std::cout << "l: " << l << " r: " << r <<  " pass: " << nPerm << std::endl;
        }

        std::cout << "pass: " << pass << " fail: " << fail << std::endl;
        if (l == 14 && r == 24)
        {
            exit(1);
        }

    }
#endif

#if 0
	DongleProvider* dongleProvider = new DongleProvider();
	CloudProvider* cloudProvider = new CloudProvider();

	std::vector<ICasProvider*> providers;

	providers.push_back(dongleProvider);
	providers.push_back(cloudProvider);

	// generic provider interface
	for(auto& provider : providers)
	{
		provider->Activate();
		provider->Authorize();
	}

	// dongle specific communicator
	(static_cast<DongleProvider*>(providers[0]))->GetCommunicator().getDongleInfo();

	// cloud specific communicator
	(static_cast<CloudProvider*>(providers[1]))->GetCommunicator().Ping();
#endif

#if 0
  gint ret;
  gboolean opt_server;
  gchar *opt_address;
  GOptionContext *opt_context;
  gboolean opt_allow_anonymous;
  GError *error;
  GOptionEntry opt_entries[] =
    {
      { "server", 's', 0, G_OPTION_ARG_NONE, &opt_server, "Start a server instead of a client", NULL },
      { "address", 'a', 0, G_OPTION_ARG_STRING, &opt_address, "D-Bus address to use", NULL },
      { "allow-anonymous", 'n', 0, G_OPTION_ARG_NONE, &opt_allow_anonymous, "Allow anonymous authentication", NULL },
      { NULL}
    };

  ret = 1;

  opt_address = NULL;
  opt_server = FALSE;
  opt_allow_anonymous = FALSE;

  opt_context = g_option_context_new ("peer-to-peer example");
  error = NULL;
  g_option_context_add_main_entries (opt_context, opt_entries, NULL);
  if (!g_option_context_parse (opt_context, &argc, &argv, &error))
    {
      g_printerr ("Error parsing options: %s\n", error->message);
      g_error_free (error);
      goto out;
    }
  if (opt_address == NULL)
    {
      g_printerr ("Incorrect usage, try --help.\n");
      goto out;
    }
  if (!opt_server && opt_allow_anonymous)
    {
      g_printerr ("The --allow-anonymous option only makes sense when used with --server.\n");
      goto out;
    }

  /* We are lazy here - we don't want to manually provide
   * the introspection data structures - so we just build
   * them from XML.
   */
  introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, NULL);
  g_assert (introspection_data != NULL);

  if (opt_server)
    {
      GDBusServer *server;
      gchar *guid;
      GMainLoop *loop;
      GDBusServerFlags server_flags;

      guid = g_dbus_generate_guid ();

      server_flags = G_DBUS_SERVER_FLAGS_NONE;
      if (opt_allow_anonymous)
        server_flags= static_cast<GDBusServerFlags> ((static_cast<int> (server_flags)
							| static_cast<int> (G_DBUS_SERVER_FLAGS_AUTHENTICATION_ALLOW_ANONYMOUS)));

      error = NULL;
      server = g_dbus_server_new_sync (opt_address,
                                       server_flags,
                                       guid,
                                       NULL, /* GDBusAuthObserver */
                                       NULL, /* GCancellable */
                                       &error);
      g_dbus_server_start (server);
      g_free (guid);

      if (server == NULL)
        {
          g_printerr ("Error creating server at address %s: %s\n", opt_address, error->message);
          g_error_free (error);
          goto out;
        }
      g_print ("Server is listening at: %s\n", g_dbus_server_get_client_address (server));
      g_signal_connect (server,
                        "new-connection",
                        G_CALLBACK (on_new_connection),
                        NULL);

      loop = g_main_loop_new (NULL, FALSE);
      g_main_loop_run (loop);

      g_object_unref (server);
      g_main_loop_unref (loop);
    }
  else
    {
      GDBusConnection *connection;
      const gchar *greeting_response;
      GVariant *value;
      gchar *greeting;

      error = NULL;
      connection = g_dbus_connection_new_for_address_sync (opt_address,
                                                           G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT,
                                                           NULL, /* GDBusAuthObserver */
                                                           NULL, /* GCancellable */
                                                           &error);
      if (connection == NULL)
        {
          g_printerr ("Error connecting to D-Bus address %s: %s\n", opt_address, error->message);
          g_error_free (error);
          goto out;
        }

      sleep(5);

      g_print ("Connected.\n"
               "Negotiated capabilities: unix-fd-passing=%d\n",
               g_dbus_connection_get_capabilities (connection) & G_DBUS_CAPABILITY_FLAGS_UNIX_FD_PASSING);

      greeting = g_strdup_printf ("Hey, it's %" G_GUINT64_FORMAT " already!", (guint64) time (NULL));
      value = g_dbus_connection_call_sync (connection,
                                           NULL, /* bus_name */
                                           "/org/gtk/GDBus/TestObject",
                                           "org.gtk.GDBus.TestPeerInterface",
                                           "HelloWorld",
                                           g_variant_new ("(s)", greeting),
                                           G_VARIANT_TYPE ("(s)"),
                                           G_DBUS_CALL_FLAGS_NONE,
                                           -1,
                                           NULL,
                                           &error);
      if (value == NULL)
        {
          g_printerr ("Error invoking HelloWorld(): %s\n", error->message);
          g_error_free (error);
          goto out;
        }
      g_variant_get (value, "(&s)", &greeting_response);
      g_print ("Server said: %s\n", greeting_response);
      g_variant_unref (value);

      g_object_unref (connection);
    }
  g_dbus_node_info_unref (introspection_data);

  ret = 0;

 out:
  return ret;
#endif
}
