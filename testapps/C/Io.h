#ifndef IO_H
#define IO_H

#include <utils/utils.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

void sscanfTest()
{

#if 0
	//Simple case of parsing five space separated strings

	{
		char Name[10]=
		{	'\0'};
		char Surname[10] =
		{	'\0'};
		unsigned int day= 0;
		unsigned int month= 0;
		unsigned int year= 0;

		char dataToProcess[]=
		{	"Dimitrios Symonidis 15 08 1985"};

		if (sscanf(dataToProcess, "%s %s %u %u %u", Name, Surname, &day, &month, &year) != 5)
		{
			printf("sscanf failed ");
		}
		else
		{
			printf("Name: %s Surname: %s day: %u month %u year %u \n", Name, Surname, day, month, year);
		}
	};
#endif

#if 0
	//Simple case of parsing two space separated strings and three - separated ( we will need to use reg-ex to parse it)
	{
		char Name[10] =
		{ '\0' };
		char Surname[10] =
		{ '\0' };
		unsigned int day = 0;
		unsigned int month = 0;
		unsigned int year = 0;

		char dataToProcess[] =
		{ "Dimitrios Symonidis 15-08-1985" };

		if (sscanf(dataToProcess, "%10s %10s %2u-%2u-%4u", Name, Surname, &day,
				&month, &year) != 5)
		{
			printf("FAIL: Name: %s Surname: %s day: %2u month %2u year %4u \n", Name,
								Surname, day, month, year);
		}
		else
		{
			printf("Name: %s Surname: %s day: %02u month %02u year %4u \n", Name,
					Surname, day, month, year);
		}
	};
#endif

#if 0
	//Simple case of parsing one space separated strings and one \n and three - separated
	{
		char Name[10] =
		{ '\0' };
		char Surname[10] =
		{ '\0' };
		unsigned int day = 0;
		unsigned int month = 0;
		unsigned int year = 0;

		char dataToProcess[] =
		{ "Dimitrios Symonidis \n\n\n 15-08-1985" };

		if (sscanf(dataToProcess, "%10s %10s %2u-%2u-%4u", Name, Surname, &day,
				&month, &year) != 5)
		{
			printf("FAIL: Name: %s Surname: %s day: %2u month %2u year %4u \n",
					Name, Surname, day, month, year);
		}
		else
		{
			printf("Name: %s Surname: %s day: %02u month %02u year %4u \n",
					Name, Surname, day, month, year);
		}
	};
#endif

#if 0
	//Some basic regex parsing
	{
		char Name[10] =
		{ '\0' };
		char Surname[10] =
		{ '\0' };
		unsigned int day = 0;
		unsigned int month = 0;
		unsigned int year = 0;

		char dataToProcess[] =
		{ "Dimitrios--:Symonidis \n\n\n 15-08-123-1985" };

		if (sscanf(dataToProcess, "%10[^--:]--:%10[^--:] %2u-%2u-%*u-%4u", Name, Surname, &day,
				&month, &year) != 5)
		{
			printf("FAIL: Name: %s Surname: %s day: %2u month %2u year %4u \n",
					Name, Surname, day, month, year);
		} else
		{
			printf("Name: %s Surname: %s day: %02u month %02u year %4u \n",
					Name, Surname, day, month, year);
		}
	};
#endif

	//character parsing
	{
		char Name[10] =
		{ '\0' };
		char Surname[10] =
		{ '\0' };
		unsigned int day = 0;
		unsigned int month = 0;
		unsigned int year = 0;

		char dataToProcess[] =
		{ "Dimitrios Symonidis \n\n\n 15-08-123-1985" };

		//With the character parsing we need to explicitly eliminate white spaces and \n
		if (sscanf(dataToProcess, "%10c %9c   %2u-%2u-%*u-%4u",
				Name, Surname, &day, &month, &year) != 5)
		{
			printf("FAIL: Name: %s Surname: %s day: %2u month %2u year %4u \n",
					Name, Surname, day, month, year);
		} else
		{
			printf("Name: %s Surname: %s day: %02u month %02u year %4u \n",
					Name, Surname, day, month, year);
		}
	};
}

void sprintfTest()
{
	char name[] = { "Dimitrios" };
	char surname[] = { "Symonidis" };

	unsigned int day = 15;
	unsigned int month = 6;
	unsigned int year = 1985;

	char buffer[10];

	snprintf(buffer, sizeof(buffer) - 1, "%9s %9s %02u %02u %04u", name,surname, day, month, year);

	printf("%s", buffer);
}

void readFile()
{
	//Read line by line
#if 0
	FILE* fp= fopen("/home/mitso23/training/resources/testFile.txt", "r");
	if (!fp)
	{
		printf("failed to open file");
		return;
	}

	char data[100]= { 0 };
	while(!feof(fp))
	{
		//We need to actually attempt to read smth before realizing that we have failed
		if (!fgets(data, sizeof(data) - 1, fp))
		{
			printf("failed to read data");
			return;
		}

		printf("%s", data);
	}
#endif

#if 0
	//Read formatted data
	{
		FILE* fp = fopen("/home/mitso23/training/resources/testFile.txt", "r");
		if (!fp)
		{
			printf("failed to open file");
			return;
		}

		char name[10] =	{ 0 };
		char surname[10] = { 0 };

		unsigned int day = 0;
		unsigned int month = 0;
		unsigned int year = 0;

		while (!feof(fp))
		{
			if (fscanf(fp, "%10[^ ] %10[^ ] %2u-%2u-%4u ", name, surname, &day,
					&month, &year) != 5)
			{
				printf(
						"FAIL Name: %s Surname: %s day: %02u month %02u year %04u \n",
						name, surname, day, month, year);
				return;
			} else
			{
				printf(
						"Name: %s Surname: %s day: %02u month %02u year %04u \n",
						name, surname, day, month, year);
			}
		}
	}
#endif

#if 0
	//Read raw data
	char data[200] = { 0 };
	FILE* fp = fopen("/home/mitso23/training/resources/testFile.txt", "r");
	if (!fp)
	{
		printf("failed to open file");
		return;
	}

	size_t offset= 0;
	size_t numBytesRead;

	while(!feof(fp))
	{
		numBytesRead= fread(data + offset, 1, 10, fp);
		offset+=numBytesRead;

		if (numBytesRead != 10)
		{
			break;
		}
	}

	printf("%s", data);
#endif

#if 0
	//Read using the basic operations
	char data[200]= { 0 };
	int fd= open("/home/mitso23/training/resources/testFile.txt",O_RDONLY);
	off_t fileSize= lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	read(fd, data , fileSize);
	printf("%s", data);
#endif


}

#endif /* IO_H_ */
