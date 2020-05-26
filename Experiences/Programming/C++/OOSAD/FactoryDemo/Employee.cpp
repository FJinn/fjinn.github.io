#include "Employee.h"

Programmer::Programmer()
{
	CreateAndBenefit(Laptop());
	CreateAndBenefit(Car());
	CreateAndBenefit(Girlfriend());
}

Artist::Artist()
{
	CreateAndBenefit(Laptop());
	CreateAndBenefit(Insurance());
	CreateAndBenefit(Allowance());
}

Designer::Designer()
{
	CreateAndBenefit(CellPhone());
	CreateAndBenefit(Laptop());
	CreateAndBenefit(Allowance());
}
