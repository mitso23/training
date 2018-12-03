#include <memory>

class Weapon
{
	void weapon();
};
class Armor
{
	void armor();
};
class Helmet
{
	void helmet();
};

class Scroll
{
	void scroll();
};

class Potion
{
	void potion();
};

class Object
{
   struct ObjectConcept
   {
       virtual ~ObjectConcept() {}
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
