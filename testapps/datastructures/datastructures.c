#include <libdatastructures/hash.h>

unsigned int generate_key(int key, unsigned size)
{
	return key % size;
}

typedef struct
{
	int x;
	int y;
}coordinates_t;

DECLARE_HASH_FUNCTIONS(float, int)
DECLARE_HASH_FUNCTIONS(coordinates_t, int)
DECLARE_HASH_FUNCTIONS(int, int)
DEFINE_HASH(int, int, hash_int)
DEFINE_HASH(float, int, hash_float)
DEFINE_HASH(coordinates_t, int, hash_coordinates)

int main(int argc, char* argv[])
{
	//generic list tests
#if 0
	std::cout << "Adding elements to back " << std::endl;
	addElementsToListBack();
	displayIntList();

	std::cout << "delete elements test" << std::endl;
	removeNodeTest();
	displayIntList();

	std::cout << "clear list test " << std::endl;
	addElementsToListFront();
	clearList();

	displayIntList();
#endif

#if 1
	{
		//TESTING INT->INT HASH
		unsigned int hash_size = 10;
		hash_create_int(&hash_int, &hash_int_end, hash_size);
		int i = 0;
		for (; i < 20; i++) {
			hash_insert_int(hash_int, i + 10, i, generate_key, hash_size);
		}

		int value;
		int key;

		for (int i = 0; i < 5; ++i) {
			hash_erase_int(hash_int, i, generate_key, hash_size);
		}

		HASH_FOR_EACH(hash_int, hash_int_end, &value, &key, int)
		{
			printf("value: %d key: %d\n", value, key);
		}

		if (hash_find_int(hash_int, &value, 5,  generate_key, hash_size)) {
			printf("Found value %d\n", value);
		}
	}
#endif

	return 0;
}
