template<typename E>
class UnExpected
{
public:
	template<typename U=E>
	UnExpected(U&& e)
		: nay(std::forward<U>(e))
	{

	}

	E nay;
};

template<typename T, typename E>
class Expected
{
	/**
	 * NOTE: default constructors are not called when the union is created
	 * only enough storage is allocated to hold the largest
	 */
	union
	{
		T yay;
		E nay;
	};

public:
	Expected()
		: ok(true)
	{
		new(&yay)T();
	}

	//constructors
	Expected(const Expected& rhs)
		: ok(rhs.ok)
	{
		if (ok)
		{
			new (&yay)T(rhs.yay);
		}
		else
		{
			new (&nay)T(rhs.nay);
		}
	}


	Expected(Expected&& rhs)
		: ok(rhs.ok)
	{
		if (ok)
		{
			new (&yay)T(std::move(rhs.yay));
		}
		else
		{
			new (&nay)T(std::move(rhs.nay));
		}
	}

	template<typename U=T>
	Expected(U&& rhs)
		: ok(true)
	{
		new (&yay)T(std::forward<U>(rhs));
	}


	Expected(const UnExpected<E>& unexpected)
		: ok(false)
	{
		new(&nay) E(unexpected.nay);
	}

	Expected(UnExpected<E>&& unexpected)
			: ok(false)
	{
		new(&nay) E(std::move(unexpected.nay));
	}

	//observers
	T& operator*()
	{
		assert(ok);

		return yay;
	}

	const T& operator*() const
	{
		assert(ok);

		return yay;
	}

	T* operator->()
	{
		return &**this;
	}

	const T* operator->() const
	{
		return &**this;
	}

	const E& Error() const
	{
		assert(!ok);
		return nay;
	}

	explicit operator bool() const
	{
		return ok;
	}

	~Expected()
	{
		if (ok)
		{
			yay.~T();
		}
		else
		{
			nay.~E();
		}
	}

private:
	bool ok;
};
