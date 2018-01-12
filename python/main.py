import os

def printFiles(directory, level):
    files = [f for f in os.listdir(directory) if os.path.isfile(directory + f)]
    directories = [d for d in os.listdir(directory) if not os.path.isfile(directory + d)]

    print('current directory:' + directory)

    for f in files:
	print(f)

    for d in directories:
	printFiles(str(directory) + d + '/')
	

def main() :
   printFiles('./', 1)


if __name__ == '__main__':
    main()
