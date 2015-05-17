

// NOTE: When doing multiple inheritance we store a pointer to vtable in each class
// Using virtual inheritance adds another performance penalty as the derived classes need to have a pointer to the base members
// Using virtual function prevents the compiler from inlining a function as the compiler can't resolve at compile time which function is going to be called  

//Base* d= new Derived(); In the base class the compiler will have a pointer to a table which will have the functions of the Derived class and assign an index to 
// to each of the virtual function in base so it can find them later on the vtable

// Each vtable also might have stored the RTTI information that typeid is using to query the type of the object [typeifno, f1, f2,]
