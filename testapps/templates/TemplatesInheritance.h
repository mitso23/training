template<typename Base, int D>
class Discriminator: public Base
{

};

class DefaultPolicy1
{

};

class DefaultPolicy2
{

};

class DefaultPolicy3
{

};

class DefaultPolicy4
{

};

template<typename Setter1, typename Setter2, typename Setter3, typename Setter4>
class PolicySelector: public Discriminator<Setter1, 1>,
					  public Discriminator<Setter2, 2>,
					  public Discriminator<Setter3, 3>,
					  public Discriminator<Setter4, 4>
{

};

// name default policies as P1, P2, P3, P4
class DefaultPolicies
{
  public:
    typedef DefaultPolicy1 P1;
    typedef DefaultPolicy2 P2;
    typedef DefaultPolicy3 P3;
    typedef DefaultPolicy4 P4;
};

// class to define a use of the default policy values
// avoids ambiguities if we derive from DefaultPolicies more than once
class DefaultPolicyArgs: virtual public DefaultPolicies
{

};

//Finally, we also need some templates to override the default policy values:
template<typename Policy>
class Policy1_is: virtual public DefaultPolicies
{
public:
	typedef Policy P1;  // overriding typedef
};
template<typename Policy>
class Policy2_is: virtual public DefaultPolicies
{
public:
	typedef Policy P2;  // overriding typedef
};
template<typename Policy>
class Policy3_is: virtual public DefaultPolicies
{
public:
	typedef Policy P3;  // overriding typedef
};
template<typename Policy>
class Policy4_is: virtual public DefaultPolicies
{
public:
	typedef Policy P4;  // overriding typedef
};


template <typename PolicySetter1 = DefaultPolicyArgs,
          typename PolicySetter2 = DefaultPolicyArgs,
          typename PolicySetter3 = DefaultPolicyArgs,
          typename PolicySetter4 = DefaultPolicyArgs>
class BreadSlicer
{
    typedef PolicySelector<PolicySetter1, PolicySetter2, PolicySetter3, PolicySetter4> Policies;

    // use Policies::P1, Policies::P2, … to refer to the various policies
};

typedef int CustomPolicy;

BreadSlicer<Policy3_is<CustomPolicy> > bc;


//EMPTY CLASS OPTIMIZATION an empty class will most likely have size = 1 to be able to represent an array of empty classes
class Empty
{
    typedef int Int;  // typedef members don't make a class nonempty
};

class EmptyToo : public Empty
{

};

//In this case Empty and EmptyToo need to have different address so NonEmpty will have a size of 2
class NonEmpty : public Empty, public EmptyToo
{

};

template<typename CountedType, unsigned int numObjects = 1>
class ObjectCounter
{
private:
	static size_t count;    // number of existing objects
protected:
	// default constructor
	ObjectCounter()
	{
		++ObjectCounter<CountedType>::count;
		if (live() > numObjects)
		{
			throw 1;
		}
	}

	// copy constructor
	ObjectCounter(ObjectCounter<CountedType> const&)
	{
		++ObjectCounter<CountedType>::count;
		if (live() > numObjects)
		{
			throw 1;
		}
	}

	// destructor
	~ObjectCounter()
	{
		--ObjectCounter<CountedType>::count;
	}

public:
	// return number of existing objects:
	static size_t live()
	{
		return ObjectCounter<CountedType>::count;
	}
};

template <typename CountedType, unsigned int numObjects>
size_t ObjectCounter<CountedType, numObjects>::count = 0;

class SingleObject : private ObjectCounter<SingleObject>
{

};

class NotVirtual
{

};


class Virtual
{
public:
	virtual void foo()
	{
	}

	virtual ~Virtual()
	{

	}
};


template<typename VBase>
class BBase: private VBase
{
public:
	// the virtuality of foo() depends on its declaration
	// (if any) in the base class VBase
	void foo()
	{
		std::cout << "Base::foo()" << '\n';
	}
};


template<typename V>
class Derived: public BBase<V>
{
public:
	void foo()
	{
		std::cout << "Derived::foo()" << '\n';
	}
};





