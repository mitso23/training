#include <libdatastructures/hash.h>

unsigned int generate_key(int key, unsigned size)
{
	return key % size;
}

DECLARE_HASH_FUNCTIONS(int, int)
DEFINE_HASH(int, int, hash)

DECLARE_HASH_FUNCTIONS(int, float)


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


	{
		//TESTING INT->INT HASH
		unsigned int hash_size = 10;
		hash_create(&hash, &hash_end, hash_size);
		int i = 0;
		for (; i < 20; i++) {
			hash_insert(hash, i + 10, i, generate_key, hash_size);
		}

		int value;
		int key;

		for (int i = 0; i < 5; ++i) {
			hash_erase(hash, i, generate_key, hash_size);
		}

		HASH_FOR_EACH(hash, hash_end, &value, &key)
		{
			printf("value: %d key: %d\n", value, key);
		}

		if (hash_find(hash, &value, 5,  generate_key, hash_size)) {
			printf("Found value %d\n", value);
		}
	}

	return 0;
}
