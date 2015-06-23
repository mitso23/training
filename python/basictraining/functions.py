Z = 100

def testArguments() :
    name= "Sokratis";
    id = 8
    list = [ 1 , 2 , 3 ];
    list2 = list[:];
    args(name, id, list, list2)
    print(name, " ", id, " ", list, " ", list)

#Arguments are passed in by value and  there is no way of changing a global symbol name like Z
# from inside a function
def args(name, id, list, list2) :
    list3 = [ 1000 , 1001, 1002]

    # Strings are immutable so they will not change
    name = "Dimitris"
    id = 12

    # Can't change the value of a global
    Z = 50

    #This will change the list outside of the function
    list.append(4)

    #You can't change the reference so list2 will remain unchanged
    list2= list3;

