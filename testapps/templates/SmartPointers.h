class CounterPolicy
{
public:
	// the following four special members (constructors, destructor, and
	// copy assignment) need not be declared explicitly in some cases,
	// but they must be accessible
	CounterPolicy();
	CounterPolicy(CounterPolicy const&);
	~CounterPolicy();
	CounterPolicy& operator=(CounterPolicy const&);
	// assume T is the type of object pointed to
	template<typename T> void init(T*);        // initialization to one, possibly allocation
	template<typename T> void dispose(T*);     // possibly involves deallocation of the counter
	template<typename T> void increment(T*);   // atomic increment by one
	template<typename T> void decrement(T*);   // atomic decrement by one
	template<typename T> bool is_zero(T*);     // check for zero
};

class StandardObjectPolicy
{
public:
	template<typename T> void dispose(T* object)
	{
		delete object;
	}
};

class SimpleReferenceCount
{
private:
	size_t* counter;    // the allocated counter
public:
	SimpleReferenceCount()
	{
		counter = NULL;
	}

	// default copy constructor and copy-assignment operator
	// are fine in that they just copy the shared counter
public:
	// allocate the counter and initialize its value to one:
	template<typename T> void init(T*)
	{
		counter = new size_t();
		*counter = 1;
	}

	// dispose of the counter:
	template<typename T> void dispose(T*)
	{
		delete counter;
	}

	// increment by one:
	template<typename T> void increment(T*)
	{
		++*counter;
	}

	// decrement by one:
	template<typename T> void decrement(T*)
	{
		--*counter;
	}

	// test for zero:
	template<typename T> bool is_zero(T*)
	{
		return *counter == 0;
	}
};

template<typename ObjectT,        // the class type containing the counter
         typename CountT,         // the type of the pointer
         CountT ObjectT::*CountP> // the location of the counter
class MemberReferenceCount
{
  public:
    // the default constructor and destructor are fine
    // initialize the counter to one:
    void init (ObjectT* object) {
        object->*CountP = 1;
    }
    // no action is needed to dispose of the counter:
    void dispose (ObjectT*) {
    }
    // increment by one:
    void increment (ObjectT* object) {
        ++(object->*CountP);
    }
    // decrement by one:
    void decrement (ObjectT* object) {
        --(object->*CountP);
    }
    // test for zero:
   bool is_zero (ObjectT* object) {
        return object->*CountP == 0;
    }
};

template<typename T, typename CounterPolicy = SimpleReferenceCount,
		 typename ObjectPolicy = StandardObjectPolicy>
class CountingPtr: private CounterPolicy, private ObjectPolicy
{
private:
	// shortcuts:
	typedef CounterPolicy CP;
	typedef ObjectPolicy OP;
	T* object_pointed_to;      // the object referred to (or NULL if none)
public:
	// default constructor (no explicit initialization):
	CountingPtr()
	{
		this->object_pointed_to = NULL;
	}

	// a converting constructor (from a built-in pointer):
	explicit CountingPtr(T* p)
	{
		this->init(p);         // init with ordinary pointer
	}

	// copy constructor:
	CountingPtr(CountingPtr<T, CP, OP> const& cp) :
			CP((CP const&) cp),      // copy policies
			OP((OP const&) cp)
	{
		this->attach(cp);      // copy pointer and increment counter
	}

	// destructor:
	~CountingPtr()
	{
		this->detach();        // decrement counter
							   // (and dispose counter if last owner)
	}

	// assignment of a built-in pointer
	CountingPtr<T, CP, OP>& operator=(T* p)
	{
		// no counting pointer should point to *p yet:
		assert(p != this->object_pointed_to);
		this->detach();        // decrement counter
							   // (and dispose counter if last owner)
		this->init(p);         // init with ordinary pointer
		return *this;
	}

	// copy assignment (beware of self-assignment):
	CountingPtr<T, CP, OP>&
	operator=(CountingPtr<T, CP, OP> const& cp)
	{
		if (this->object_pointed_to != cp.object_pointed_to)
		{
			this->detach();    // decrement counter
							   // (and dispose counter if last owner)
			CP::operator=((CP const&) cp);  // assign policies
			OP::operator=((OP const&) cp);
			this->attach(cp);  // copy pointer and increment counter
		}
		return *this;
	}
	// the operators that make this a smart pointer:
	T* operator->() const
	{
		return this->object_pointed_to;
	}
	T& operator*() const
	{
		return *this->object_pointed_to;
	}
	// additional interfaces will be added later
private:
	// helpers:
	// - init with ordinary pointer (if any)
	void init(T* p)
	{
		if (p != NULL)
		{
			CounterPolicy::init(p);
		}
		this->object_pointed_to = p;
	}
	// - copy pointer and increment counter (if any)
	void attach(CountingPtr<T, CP, OP> const& cp)
	{
		this->object_pointed_to = cp.object_pointed_to;
		if (cp.object_pointed_to != NULL)
		{
			CounterPolicy::increment(cp.object_pointed_to);
		}
	}
	// - decrement counter (and dispose counter if last owner)
	void detach()
	{
		if (this->object_pointed_to != NULL)
		{
			CounterPolicy::decrement(this->object_pointed_to);
			if (CounterPolicy::is_zero(this->object_pointed_to))
			{
				// dispose counter, if necessary:
				CounterPolicy::dispose(this->object_pointed_to);
				// use object policy to dispose the object pointed to:
				ObjectPolicy::dispose(this->object_pointed_to);
			}
		}
	}
};

class ManagedType
{
private:
	size_t ref_count;
public:
	typedef CountingPtr<ManagedType,MemberReferenceCount<ManagedType, size_t, &ManagedType::ref_count> > Ptr;
	ManagedType()
		: ref_count(0)
		, x(0)

	{
		std::cout << "constructor count is " << ref_count << std::endl;
	}

	~ManagedType()
	{
		std::cout << "destructor count is " << ref_count << std::endl;
	}

	int x;

};
