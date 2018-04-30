#include<iostream>
#include<vector>
using std::cout;
using std::cin;
//-----------------------------------------------------------------------------------------------------------------
/***namespace details***/
namespace details
{
	static const std::string function_list[49] =
	{
		"frac"         , "ncdf"         , "erfc"         , "erf"          ,
		"sgn"          , "abs"          , "acos"         , "acosh"        ,
		"asin"         , "asinh"        , "atan"         , "atanh"        ,
		"ceil"         , "cos"          , "cosh"         , "sin"          ,
		"sinc"         , "sinh"         , "tan"          , "tanh"         ,
		"cot"          , "sec"          , "csc"          , "round"        ,
		"exp"          , "expm1"        , "floor"        , "sqrt"         ,
		"log"          , "log10"        , "trunc"        , "log2"         ,
		"log1p"        , "logn"         , "rad2deg"      , "deg2rad"      ,
		"deg2grad"     , "grad2deg"     , "pow"          , "hypot"        ,
		"mod"          , "root"         , "sum"          , "rest"         ,
		"mul"          , "div"          , "avg"          , "max"          ,
		"min"
	};

	inline bool is_letter(std::size_t c) noexcept{
		return (c > 96 && c < 123) ||
			   (c > 64 && c < 91);
	}

	inline bool is_letter_or_digit(const char& c) noexcept{
		return (c > 47 && c <  58) ||
			   (c > 96 && c < 123) ||
			   (c > 64 && c <  91);
	}
}
//-----------------------------------------------------------------------------------------------------------------
/***namespace generator***/
namespace generator
{
	std::string get_variables( const std::string& expr )
	{
		std::vector<std::string> variables;
		std::string retVal;
		
		const char* end = expr.data() + expr.size();
		const char* c = expr.data();

		while(c != end)
		{
			while (' ' == *c)
			++c;

			if (details::is_letter(*c))
			{
				const char* begin = c;

				while (details::is_letter_or_digit(*c) || (*c) == '_')
					++c;

				std::string s(begin, c);

				if (s.length() > 2 && s.length() < 9)
				{
					bool is_function = false;
					for (int i = 0; i < 49; ++i)
					{
						if (details::function_list[i] == s)
						{
							is_function = true; break;
						}
					}
					if (is_function)
					continue;
				}
				bool found = false;
				for (const std::string& str : variables)
				{
					if (s == str)
						found = true;
				}
				
				if (!found)
				{
					variables.push_back(s);
					variables.push_back(",");
				}
				continue;
			}
			else
				++c;
		}
		variables.pop_back();
		
		for (std::string& s : variables)
			retVal += s;
		
		return retVal;
	}
}
//-----------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	std::string s;
	for (std::size_t i = 1; i < argc; ++i)
		s += argv[i];
	
	cout << generator::get_variables(s);
	
	return 0;
}