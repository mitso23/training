__author__ = 'root'

def varargtest(*kwarg) :
    print("the length is ", len(kwarg), "arguments are ", kwarg)

def testPrinting():
    name = 2
    score = [1, 2, 3, "Bloody Hell"]
    # Print is using *kwars which is equivelant to variable arguments macro
    print("Total score for ", name," is ",score)
    varargtest(1, 2, "Hello")