#include <memory>

class Weapon
{
    void fire();

	void weapon();
};

class Armor
{
    void fire();

	void armor();
};

class Helmet
{
    void fire();

	void helmet();
};

class Scroll
{
    void fire();

	void scroll();
};

class Potion
{
    void fire();

	void potion();
};

class Object
{
   struct ObjectConcept
   {
       virtual ~ObjectConcept() {}
       virtual void fire() = 0;
   };

   template< typename T > struct ObjectModel : ObjectConcept
   {
       ObjectModel( const T& t ) : object( t )
       {

       }

       virtual ~ObjectModel()
       {
    	   std::cout << "Destroying an ObjectModel: " << std::endl;
       }

       void fire() override
       {
           object.fire();
       }

     private:
       T object;
   };

 public:
   template< typename T > Object( const T& obj )
   	   : object( new ObjectModel<T>( obj ) )
	 {

	 }

   ~Object()
   {
	   std::cout << "Destroying an object: " << std::endl;
   }

 private:
   std::shared_ptr<ObjectConcept> object;
};

//Naive implementation
#if 0
template<typename Result, typename ...Arguments>
class function
{
public:
	function(Result(*functionPtr_)(Arguments...ars))
		:functionPtr(functionPtr_)
	{

	}

	Result operator()(Arguments...args)
	{
		return functionPtr(std::forward<Arguments>(args)...);
	}

private:
	Result(*functionPtr)(Arguments...ars) = nullptr;
};
#endif
