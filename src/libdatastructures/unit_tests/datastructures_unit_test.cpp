#define BOOST_TEST_MODULE stringtest
#include <utils/thread_safe_boost_check.h>
#include <libdatastructures/hash.h>
#include <libdatastructures/dynamic_queue.h>
#include <libdatastructures/list.h>
#include <libdatastructures/c_vector.h>

BOOST_AUTO_TEST_SUITE (datastructures) // name of the test suite is stringtest

unsigned int generate_key(int key, unsigned size)
{
	return key % size;
}

DECLARE_HASH_FUNCTIONS(int, int)
DECLARE_HASH_FUNCTIONS(float, int)
DECLARE_LIST_FUNCTIONS(int, int)
DECLARE_LIST_FUNCTIONS(int*, pint)
DECLARE_QUEUE_FUNCTIONS(unsigned, uint);
DECLARE_VECTOR_FUNCTIONS(int, int)

BOOST_AUTO_TEST_CASE(__hash_insert_int__)
{
	DEFINE_HASH(int, int, hash_int)

	unsigned int hash_size = 10;
	size_t hash_num_items= 0;
	hash_create_int(&hash_int, &hash_int_end, hash_size);
	unsigned  i = 0U;

	for (; i < 2000U; i++)
	{
		hash_insert_int(hash_int, i + 10, i, generate_key, hash_size, &hash_num_items);
	}

	BOOST_CHECK(hash_num_items == 2000U);
}

BOOST_AUTO_TEST_CASE(__hash_display_int__)
{
	DEFINE_HASH(int, int, hash_int)

	unsigned int hash_size = 10;
	size_t hash_num_items= 0;
	hash_create_int(&hash_int, &hash_int_end, hash_size);
	unsigned  i = 0U;

	for (; i < 2000U; i++)
	{
		hash_insert_int(hash_int, i + 10, i, generate_key, hash_size, &hash_num_items);
	}

	int value= 0;
	int key= 0;
	size_t actuan_num_elements= 0;

	HASH_FOR_EACH(hash_int, hash_int_end, &value, &key, int)
	{
		BOOST_CHECK(value == key + 10);
		++actuan_num_elements;
	}

	BOOST_CHECK(actuan_num_elements == hash_num_items);
}

BOOST_AUTO_TEST_CASE(__hash_erase_int__)
{
	DEFINE_HASH(int, int, hash_int)

	unsigned int hash_size = 10;
	size_t hash_num_items= 0;
	hash_create_int(&hash_int, &hash_int_end, hash_size);
	unsigned  i = 0U;

	for (; i < 2000U; i++)
	{
		hash_insert_int(hash_int, i + 10, i, generate_key, hash_size, &hash_num_items);
	}

	for (i=0; i < 2000U; i++)
	{
		hash_erase_int(hash_int, i, generate_key, hash_size,  &hash_num_items);
	}

	BOOST_CHECK(hash_num_items == 0U);
}

BOOST_AUTO_TEST_CASE(__hash_find_int__)
{
	DEFINE_HASH(int, int, hash_int)

	unsigned int hash_size = 10;
	size_t hash_num_items= 0;
	hash_create_int(&hash_int, &hash_int_end, hash_size);
	unsigned  i = 0U;

	for (; i < 2000U; i++)
	{
		hash_insert_int(hash_int, i + 10, i, generate_key, hash_size, &hash_num_items);
	}

	int value;
	bool found= hash_find_int(hash_int, &value, 5,  generate_key, hash_size);
	BOOST_CHECK(found && value == 15);

	hash_erase_int(hash_int, 5, generate_key, hash_size, &hash_num_items);
	found= hash_find_int(hash_int, &value, 5,  generate_key, hash_size);
	BOOST_CHECK(!found);
}

BOOST_AUTO_TEST_CASE(__hash_insert_float__)
{
	DEFINE_HASH(float, int, hash_float)

	unsigned int hash_size = 10;
	size_t hash_num_items= 0;
	hash_create_float(&hash_float, &hash_float_end, hash_size);
	float  i = 0.0f;

	for (; i < 2000U; i++)
	{
		hash_insert_float(hash_float, i + 10.0f, i, generate_key, hash_size, &hash_num_items);
	}


	BOOST_CHECK(hash_num_items == 2000U);
}

BOOST_AUTO_TEST_CASE(__list_insert_back_int__)
{
	DECLARE_LIST(int, mylist)
	DECLARE_LIST(int, mylist2)

	//First List
	{
		for (int i = 0; i < 500; ++i)
		{
			list_push_back_int(&mylist, i);
		}

		int expected_value= 499;
		int current_value= 0;

		while(mylist.listHead != NULL)
		{
			int result= list_pop_back_int(&mylist, &current_value);
			BOOST_CHECK(result);
			BOOST_CHECK(current_value == expected_value);
			--expected_value;
		}
	}

	//Second List
	{
		for (int i = 0; i < 500; ++i)
		{
			list_push_back_int(&mylist2, i);
		}

		int expected_value= 499;
		int current_value= 0;

		while(mylist2.listHead != NULL)
		{
			int result= list_pop_back_int(&mylist2, &current_value);
			BOOST_CHECK(result);
			BOOST_CHECK(current_value == expected_value);
			--expected_value;
		}
	}
}

BOOST_AUTO_TEST_CASE(__list_insert_back_pint__)
{
	DECLARE_LIST(pint, mylist)
	int first_item = 5;
	int second_item = 6;
	list_push_back_pint(&mylist, &first_item);
	list_push_back_pint(&mylist, &second_item);

	int* pexpected_value= new int;

	int result= list_pop_back_pint(&mylist, &pexpected_value);
	BOOST_CHECK(result);
	BOOST_CHECK(*pexpected_value == second_item);

	result= list_pop_back_pint(&mylist, &pexpected_value);
	BOOST_CHECK(result);
	BOOST_CHECK(*pexpected_value == first_item);
}

BOOST_AUTO_TEST_CASE(__list_insert_front_int__)
{
	DECLARE_LIST(int, mylist)

	for (int i = 0; i < 500; ++i)
	{
		list_push_front_int(&mylist, i);
	}

	intNode* current= mylist.listHead;
	int expected_value= 499;

	LIST_FOR_EACH(mylist, current)
	{
		BOOST_CHECK(current->data == expected_value);
		--expected_value;
	}
}

BOOST_AUTO_TEST_CASE(__list_delete_int__)
{
	DECLARE_LIST(int, mylist)

	for (int i = 0; i < 5000000; ++i)
	{
		list_push_front_int(&mylist, i);
	}

	intNode* current= mylist.listHead;
	intNode* tmp= mylist.listHead;

	LIST_FOR_EACH_SAFE(mylist, current, tmp)
	{
		DELETE_SAFE_NODE(int, &mylist, current, tmp);
	}

	BOOST_CHECK(mylist.size == 0);
}

BOOST_AUTO_TEST_CASE(__queue_uint__)
{
	DECLARE_QUEUE(uint, myqueue)

	for (unsigned i = 0U; i < 500000U; ++i)
	{
		queue_push_back_uint(&myqueue, i);
	}

	unsigned int expected_value= 500000U - 1;
	unsigned int current_value= 0;

	while(!queue_is_empty_uint(&myqueue))
	{
		int result= queue_pop_back_uint(&myqueue, &current_value);
		BOOST_CHECK(result);
		BOOST_CHECK(current_value == expected_value);
		--expected_value;
	}

	BOOST_CHECK(queue_size_uint(&myqueue) == 0);

}

BOOST_AUTO_TEST_CASE(__vector__)
{
	DEFINE_VECTOR(int, myVector)

	for (int i=0; i< 1000; ++i)
	{
		vector_push_back_int(&myVector, i);
	}

	BOOST_CHECK(vector_size_int(&myVector) == 1000);
	BOOST_CHECK(vector_capacity_int(&myVector) == 1024);

	for(unsigned i=0; i< vector_size_int(&myVector); ++i)
	{
		BOOST_CHECK(vector_at_int(&myVector, (int)i) == i);
	}
}

BOOST_AUTO_TEST_SUITE_END( )

