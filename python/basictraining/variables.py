def testNumbers():
    # You can declare types in python but then they can just change as it is dynamically typed language
    x = float()
    y = int()
    z = str()

    x = 17/3

    # NOTE y=x doesn't implicitly convert float to int
    y = int(x)
    print("X as a float is " + str(x) + "and as int is " + str(y))
    print("2 to the power of 6 is " + str(2 ** 7))

    # Now x from float points to a string (Python magic)
    x = "Change Float to String now"

    # Use \\ or 'r' in front of the string to avoid displaying special characters
    print("C:\disk\\name")

    # The [:] Range is very useful
    # -1 starts from the end of the string
    print("Last character: " + x[-1] + " The first two characters: " + x[0:2] + " The last four characters are " + x[-4:])

    # Strings are immutable so can't change their value
    #x[0]=1;

    # A byte stream we need to decode it before printing
    print(b'\x45\x46\x47'.decode('utf-8'))
    x= str("Hello").encode("utf-8")
    y= bytes(x)
    print(str(y))

    firstArg= 1;
    secondArg= firstArg;
    secondArg= 2
    #print("First argument: " + str(firstArg) + " Second argument " + str(secondArg))
    x="My name is Dimitrios"

    if "name" in x:
        print("Hurray")
