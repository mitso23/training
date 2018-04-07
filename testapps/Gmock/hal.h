#ifndef HAL_H_
#define HAL_H_


class Turtle;

class HAL
{
public:
	static HAL& getInstance();
	virtual Turtle& getTurtle() = 0;
};

#endif /* HAL_H_ */
