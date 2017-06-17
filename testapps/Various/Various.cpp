#include <iostream>
#include <thread>
#include <string>

unsigned int my_atoi(const char* input)
{
	unsigned int result = 0;

	while(input && *input)
	{
		result = result*10 + (*input++ - '0');
	}

	return result;
}

bool checkIfLocalUsbPathAndGetAbsolutePath(const std::string& path, std::string& absolute, const std::string& tag)
{
	auto start = path.find("usb://");
	auto end = path.find("//");

	if (start == 0)
	{
		if (end != std::string::npos && end != path.size() - 1)
		{
			absolute = path.substr(end + 1);
			if (absolute.find(tag))
			{
				return true;
			}
			else
			{
				absolute = "";
			}
		}
	}

	return false;
}

#include <memory>

int main()
{
	int* ptr = nullptr;

	std::function<void (void)> l = []() { };

	std::unique_ptr<int, std::function<void (int*)> > p(new int(1), [&ptr](int* wrappPtr)
	{
		if (ptr)
		{
			std::cout << "ptr is not null: " << std::endl;
		}
		else
		{
			std::cout << "ptr is null: " << std::endl;
		}

		delete wrappPtr;
	});

	ptr= new int(1);

	return 0;
}
