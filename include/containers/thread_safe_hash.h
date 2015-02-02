#ifndef THREAD_SAFE_MAP_H_
#define THREAD_SAFE_MAP_H_

#include <exception>
#include <thread>
#include <stack>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>
#include <list>
#include <iostream>
#include <map>
#include <algorithm>
#include <libbase/rwlock.h>
#include <libbase/random_generator.h>

//#define OPTIMIZE
template<typename Key, typename Value, typename Hash = std::hash<Key> >
class threadsafe_lookup_table
{
private:
	class bucket_type
	{
	private:
		typedef std::pair<Key, Value> bucket_value;
		typedef std::list<bucket_value> bucket_data;
		typedef typename bucket_data::iterator bucket_iterator;
		bucket_data data;
		mutable std::mutex mutex;
		RWLock lock;

		bucket_iterator find_entry_for(Key const& key)
		{
			return std::find_if(data.begin(), data.end(),
					[&](const bucket_value& item)
					{	return item.first==key;});
		}
	public:
		Value value_for(Key const& key, Value const& default_value)
		{

#ifndef OPTIMIZE
			std::unique_lock < std::mutex > lock(mutex);
#else
			lock.lockReader();
#endif
			bucket_iterator const found_entry = find_entry_for(key);
			auto value= (found_entry == data.end()) ?
					default_value : found_entry->second;
#ifdef OPTIMIZE
			lock.unlockReader();
#endif
			return value;
		}

		void add_or_update_mapping(Key const& key, Value const& value)
		{
#ifndef OPTIMIZE
			std::unique_lock < std::mutex > lock(mutex);
#else
			lock.lockWriter();
#endif
			bucket_iterator const found_entry = find_entry_for(key);
			if (found_entry == data.end())
			{
				data.push_back(bucket_value(key, value));
			}
			else
			{
				found_entry->second = value;
			}
#ifdef OPTIMIZE
			lock.unlockWriter();
#endif
		}
		void remove_mapping(Key const& key)
		{
#ifndef OPTIMIZE
			std::unique_lock < std::mutex > lock(mutex);
#else
			lock.lockWriter();
#endif
			bucket_iterator const found_entry = find_entry_for(key);
			if (found_entry != data.end())
			{
				data.erase(found_entry);
			}
#ifdef OPTIMIZE
			lock.unlockWriter();
#endif
		}

		size_t get_size()
		{
			return data.size();
		}

		void printValues()
		{
#ifndef OPTIMIZE
			std::unique_lock < std::mutex > lock(mutex);
#else
			lock.lockWriter();
#endif
			for (auto it = data.begin(); it != data.end(); ++it)
			{
				std::cout << "Key= " << it->first << " Data=" << it->second
						<< std::endl;
			}
#ifdef OPTIMIZE
			lock.unlockWriter();
#endif
		}
	};

	std::vector<std::unique_ptr<bucket_type> > buckets;
	Hash hasher;

	bucket_type& get_bucket(Key const& key)
	{
		std::size_t const bucket_index = hasher(key) % buckets.size();
		return *buckets[bucket_index];
	}

public:
	typedef Key key_type;

	typedef Value mapped_type;
	typedef Hash hash_type;
	threadsafe_lookup_table(unsigned num_buckets = 19, Hash const& hasher_ =
			Hash()) :
			buckets(num_buckets), hasher(hasher_)
	{
		for (unsigned i = 0; i < num_buckets; ++i)
		{
			buckets[i].reset(new bucket_type);
		}
	}
	threadsafe_lookup_table(threadsafe_lookup_table const& other) = delete;
	threadsafe_lookup_table& operator=(threadsafe_lookup_table const& other) = delete;

	Value value_for(Key const& key, Value const& default_value = Value())
	{
		return get_bucket(key).value_for(key, default_value);
	}

	void add_or_update_mapping(Key const& key, Value const& value)
	{
		get_bucket(key).add_or_update_mapping(key, value);
	}

	void remove_mapping(Key const& key)
	{
		get_bucket(key).remove_mapping(key);
	}

	void displayAllItems()
	{
		for (auto it = buckets.begin(); it != buckets.end(); ++it)
		{
			(*it)->printValues();
		}
	}

	size_t get_size()
	{
		size_t numElements= 0;

		for(auto it=buckets.begin(); it != buckets.end(); ++it)
		{
			numElements+= (*it)->get_size();
		}

		return numElements;
	}
};

//NAIVE IMPLEMENTATION USED FOR COMPARISON
template<typename Key, typename Value>
class thread_safe_map
{
public:
	thread_safe_map()
	{

	}

	Value value_for(Key const& key, Value const& default_value = Value())
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		auto it= m_map.find(key);

		if (it == m_map.end())
		{
			return default_value;
		}
		else
		{
			return it->second;
		}
	}

	void add_or_update_mapping(Key const& key, Value const& value)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_map[key]= value;
	}

private:
	std::map<Key, Value> m_map;
	std::mutex m_mutex;
};


#endif /* THREAD_SAFE_MAP_H_ */
