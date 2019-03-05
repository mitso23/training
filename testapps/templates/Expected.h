template<typename E>
class UnExpected
{
public:
	template<typename U=E>
	explicit UnExpected(U&& e)
		: error(std::forward<U>(e))
	{

	}

	E error;
};

///NOTE: If the objects are movable then use move semantics to eliminate copying
// if not move will default to a copy
template<typename T1, typename T2>
void swap(T1& t1, T2& t2)
{
	T1 temp = std::move(t1);
	t1 = std::move(t2);
	t2 = std::move(temp);
}

template<typename T, typename E>
class Expected
{
	/**
	 * NOTE: default constructors are not called when the union is created
	 * only enough storage is allocated to hold the largest
	 * object creation and destruction needs to be done manually
	 */
	union
	{
		T data;
		E error;
	};

public:
	Expected()
		: ok(true)
	{
		new(&data)T();
	}

	//constructors
	Expected(const Expected& rhs)
		: ok(rhs.ok)
	{
		if (ok)
		{
			new (&data)T(rhs.data);
		}
		else
		{
			new (&error)T(rhs.error);
		}
	}

	Expected(Expected&& rhs)
		: ok(rhs.ok)
	{
		if (ok)
		{
			new (&data)T(std::move(rhs.data));
		}
		else
		{
			new (&error)T(std::move(rhs.error));
		}
	}


	Expected(const T& rhs)
		: ok(true)
	{
		new (&data)T(rhs);
	}

	Expected(T&& rhs)
			: ok(true)
	{
		new (&data)T(std::move(rhs));
	}


	Expected(const UnExpected<E>& unexpected)
		: ok(false)
	{
		new(&error) E(unexpected.error);
	}

	Expected(UnExpected<E>&& unexpected)
			: ok(false)
	{
		new(&error) E(std::move(unexpected.error));
	}

	//copy operators
	Expected& operator = (const Expected& rhs)
	{
		if(ok && rhs.ok)
		{
			data = rhs.data;
		}
		else if (!ok && !rhs.ok)
		{
			error = rhs.error;
		}
		else if (ok && !rhs.ok)
		{
			data.~T();
			new(&error) E(rhs.error);
		}
		else if (!ok && rhs.ok)
		{
			error.~E();
			new (&data)T(rhs.data);
		}

		return *this;
	}

	Expected& operator = (Expected&& rhs)
	{
		if(ok && rhs.ok)
		{
			data = std::move(rhs.data);
		}
		else if (!ok && !rhs.ok)
		{
			error = std::move(rhs.error);
		}
		else if (ok && !rhs.ok)
		{
			data.~T();
			new(&error) E(std::move(rhs.error));
		}
		else if (!ok && rhs.ok)
		{
			error.~E();
			new (&data)T(std::move(rhs.data));
		}

		return *this;
	}

	Expected& operator = (const T& t)
	{
		data = t;
		return *this;
	}

	Expected& operator = (T&& t)
	{
		data = std::move(t);
		return *this;
	}


	Expected& operator = (const UnExpected<E>& rhs)
	{
		data.~T();
		new(&error) E(rhs.error);
		ok = false;
		return *this;
	}

	Expected& operator = (UnExpected<E>&& rhs)
	{
		data.~T();
		new(&error) E(std::move(rhs.error));
		ok = false;
		return *this;
	}

	//observers

	T& operator*()
	{
		assert(ok);

		return data;
	}

	const T& operator*() const
	{
		assert(ok);

		return data;
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
		return error;
	}

	E& Error()
	{
		assert(!ok);
		return error;
	}

	explicit operator bool() const
	{
		return ok;
	}

	//destructor
	~Expected()
	{
		if (ok)
		{
			data.~T();
		}
		else
		{
			error.~E();
		}
	}

	//swap
	void swap(Expected& rhs)
	{
		if (ok)
		{
			//both objects where fully constructed so invoke their copy/move constructors
			if (rhs.ok)
			{
				::swap(data, rhs.data);
			}
			else
			{
				// this is ok -> !ok scenario so recursively call swap to handle the !ok ok scenario which is defined below (to avoid duplicate code)
				rhs.swap(*this);
			}
		}
		else
		{
			//both objects have their error state setup so use the copy/move constructors directly
			if (!rhs.ok)
			{
				::swap(error, rhs.error);
			}
			else
			{
				// get a copy of the error object
				E e { std::move(error) };

				//destroy the current error object
				error.~E();

				// copy the valid object
				new(&data) T(std::move(rhs.data));
				ok = true;

				//now do the rhs part
				{
					//destroy the valid object
					rhs.data.~T();

					//copy current error
					new(&rhs.error) E(std::move(e));
					rhs.ok = false;
				}
			}
		}
	}

private:
	bool ok;
};
