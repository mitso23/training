def testNumbers():
    x=float()
    y= int()
    z= str()
    x= 17/3
    # NOTE y=x doesn't implicitly convert float to int
    y= int(x)
    print("X as a float is " + str(x) + "and as int is " + str(y))
