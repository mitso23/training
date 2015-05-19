import copy

class Foo(object):
    def __init__(self, val):
         self.val = val

    def __repr__(self):
        return str(self.val)

# b = 1 a = 1, b = 2 a= 2,
def fibonnaci():
    a, b = 0, 1;
    fibonnaci = 1;
    while(fibonnaci < 50) :
        print(fibonnaci)
        fibonnaci= a + b;
        a= b
        b= fibonnaci

def testLists():
    foo = Foo(1)

    a = ['foo', foo]
    b = a[:]
    c = list(a)
    d = copy.copy(a)
    e = copy.deepcopy(a)
    nested= [[1, 2, 3], ['a', 'b', 'z']];

    # edit orignal list and instance
    # If we append something to the original it will not be visible in the shallow copies
    a.append('baz')
    # That will change the variable in all of the shallow copy instances
    foo.val = 5

    #print("original: %r\n slice: %r\n list(): %r\n copy: %r\n deepcopy: %r" \
    #       % (a, b, c, d, e))

    #print("Original is,  deep copy is ",  a, b);
    print(nested)
    print(nested[0])

    if [1, 2, 3] in nested:
        print("Success")
