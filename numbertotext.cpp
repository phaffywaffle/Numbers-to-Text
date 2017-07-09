#include <iostream>
#include <string>

typedef struct
{
	unsigned int Number;
	unsigned int Ones;
	unsigned int Tens;
	unsigned int Hundreds;
	unsigned int Thousands;
	unsigned int Millions;
	unsigned int Billions; // Should never be >4 with an unsigned int
} NumberFormat;

NumberFormat*
Convert(unsigned int Number)
{
	NumberFormat* Result = new NumberFormat();
	Result->Number = 	Number;
	Result->Ones = 		Number % 10;
	Result->Tens = 		Number % 100 			/ 10;
	Result->Hundreds = 	Number % 1000 			/ 100;
	Result->Thousands = Number % 1000000 		/ 1000;
	Result->Millions = 	Number % 1000000000 	/ 1000000;
	Result->Billions = 	Number % 1000000000000 	/ 1000000000; 
	return(Result);
}

std::string
GetOnes(int number)
{ 	
	switch(number)
	{ // Not usually a good idea to return inside case statements
		case(0): { return("Zero "); } break;
		case(1): { return("One "); } break;
		case(2): { return("Two "); } break;
		case(3): { return("Three "); } break;
		case(4): { return("Four "); } break;
		case(5): { return("Five "); } break;
		case(6): { return("Six "); } break;
		case(7): { return("Seven "); } break;
		case(8): { return("Eight "); } break;
		case(9): { return("Nine "); } break;
		default: { return("Error in the GetOnes() Function"); } break;
	}
}

std::string
GetTeens(int number)
{
	switch(number)
	{ // Not usually a good idea to return inside case statements
		case(0): { return("Ten "); } break;
		case(1): { return("Eleven "); } break;
		case(2): { return("Twelve "); } break;
		case(3): { return("Thirteen "); } break;
		case(4): { return("Fourteen "); } break;
		case(5): { return("Fifteen "); } break;
		case(6): { return("Sixteen "); } break;
		case(7): { return("Seventeen "); } break;
		case(8): { return("Eighteen "); } break;
		case(9): { return("Nineteen "); } break;
		default: { return("Error in the GetTeens() Function"); } break;
	}
}

std::string
GetTens(int number)
{
	switch(number)
	{ // Not usually a good idea to return inside case statements
		case(2): { return("Twenty "); } break;
		case(3): { return("Thirty "); } break;
		case(4): { return("Fourty "); } break;
		case(5): { return("Fifty "); } break;
		case(6): { return("Sixty "); } break;
		case(7): { return("Seventy "); } break;
		case(8): { return("Eighty "); } break;
		case(9): { return("Ninety "); } break;
		default: { return("Error in the GetTens() Function"); } break;
	}
}

std::string
GetHundreds(int Number, bool first=true)
{
	std::string Result = "";

	if(Number == 0) return(Result);
	
	int Ones = Number % 10;
	int Tens = Number % 100 / 10;
	int Hundreds = Number / 100;

	if(Hundreds) Result += GetOnes(Hundreds) + "Hundred ";

	// Convoluted, but it works
	if(first) first = Result.empty();
	if(Tens == 1)
	{
		if(first) first = false;
		else Result += "and ";
		Result += GetTeens(Ones);
	}
	else
	{
		if(first) first = false;
		else Result += "and ";
		if(Tens) Result += GetTens(Tens);
		if(Ones) Result += GetOnes(Ones);
	}

	return(Result);
}

inline void
Print(NumberFormat* Format)
{
	std::string s = "";

	if(Format->Billions)  s += GetOnes(Format->Billions) + "Billion ";
	if(Format->Millions)  s += GetHundreds(Format->Millions) + "Million ";
	if(Format->Thousands) s += GetHundreds(Format->Thousands) + "Thousand ";
	bool first = s.empty();
	s += GetHundreds(Format->Ones + Format->Tens * 10 + Format->Hundreds * 100, first);

	std::cout << s << std::endl;
/* Debugging 
	std::cout << "Format->Number: " << Format->Number << std::endl;
	std::cout << "Format->Ones: " << Format->Ones << std::endl;
	std::cout << "Format->Tens: " << Format->Tens << std::endl;
	std::cout << "Format->Hundreds: " << Format->Hundreds << std::endl;
	std::cout << "Format->Thousands: " << Format->Thousands << std::endl;
	std::cout << "Format->Millions: " << Format->Millions << std::endl;
	std::cout << "Format->Billions: " << Format->Billions << std::endl;
	std::cout << "Format->Ones + Format->Tens * 10 + Format->Hundreds * 100: " << (Format->Ones + Format->Tens * 10 + Format->Hundreds * 100) << std::endl;
*/
}

int
main(int argc, char* argv[])
{
	if(argc != 2) std::cout << "Need a number between 0 and 4294967296";
	else
	{
		unsigned int Number = (unsigned int)strtoul(argv[1], 0, 0);
		if(Number < 0) std::cout << "Too low" << std::endl;					// These checks would be nice, but will never work since strtoul() clamps values outside our range to UINT_MAX
		else if(Number > UINT_MAX) std::cout << "Too high" << std::endl;	// These checks would be nice, but will never work since strtoul() clamps values outside our range to UINT_MAX 
		else
		{
			NumberFormat* Test = Convert(Number);
			Print(Test);
		}
	}
	return 0;
}