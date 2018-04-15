#include<iostream>
#include<cassert>
#include<cmath>
#include<vector>
#include<map>
#include<memory>
using std::cout;
using std::cin;
//-----------------------------------------------------------------------------------------------------------------
/***namespace numeric_constant***/
namespace numeric_constant
{
	static constexpr double pi =  3.14159265358979323846264338327950288419716939937510;
	static constexpr double e  =  2.71828182845904523536028747135266249775724709369996;
}
//-----------------------------------------------------------------------------------------------------------------
/***function_impl***/
double function_impl(const double& args_val, int functionID)
{
	switch (functionID)
    {
                /*case 0://frac
        return std::frac(args_val);*/

                /*case -1:// ncdf
        return std::ncdf(args_val);*/

                case -2:// erfc
        return std::erfc(args_val);

                case -3:// erf
        return std::erf(args_val);

                case -4:// sgn
				if (args_val > 0) return +1;
                else if (args_val < 0) return -1;
                else               return 0;

                case -5:// abs
        return std::abs(args_val);

                case -6:// acos
        return std::acos(args_val);

                case -7:// acosh
        return std::acosh(args_val);

                case -8:// asin
        return std::asin(args_val);

                case -9:// asinh
        return std::asinh(args_val);

                case -10:// atan
        return std::atan(args_val);

                case -11:// atanh
        return std::atanh(args_val);

                case -12:// ceil
        return std::ceil(args_val);

                case -13:// cos
        return std::cos(args_val);

                case -14:// cosh
        return std::cosh(args_val);

                case -15:// exp
        return std::exp(args_val);

                case -16:// expm1
        return std::expm1(args_val);

                case -17://floor
        return std::floor(args_val);

                case -18:// log
        return std::log(args_val);

                case -19:// log10
        return std::log10(args_val);

                case -20:// log2
        return std::log2(args_val);

                case -21:// log1p
        return std::log1p(args_val);

                /*case -22:// logn
        return std::logn(args_val);*/

                case -23:// round
        return std::round(args_val);

                case -24:// sin
                return std::sin(args_val);

                case -25:// sinc
        return std::sin(args_val) / args_val;

                case -26:// sinh
        return std::sinh(args_val);

                case -27:// sqrt
        return std::sqrt(args_val);

                case -28:// tan
        return std::tan(args_val);

                case -29:// tanh
        return std::tanh(args_val);

                case -30:// trunc
        return std::trunc(args_val);

                case -31:// cot
        return 1/std::tan(args_val);

                case -32:// sec
        return 1/std::cos(args_val);

                case -33:// csc
        return 1/std::sin(args_val);

                case -34:// rad2deg
        return  args_val * (180/numeric_constant::pi);

                case -35:// deg2rad
        return args_val * (numeric_constant::pi/180);

                case -36:// deg2grad
        return args_val * 1.11112;

                case -37:// grad2deg
        return args_val * 0.9;
    }
}
//-----------------------------------------------------------------------------------------------------------------
/***class BST***/
struct BST
{
private:
	const std::size_t id;
	struct node
	{
		node(double val) : value(val)
		{}
		std::unique_ptr<node> left{nullptr};
		std::unique_ptr<node> right{nullptr};
		const double value;
	};
	std::unique_ptr<node> root{nullptr};
	using numeric_p = std::unique_ptr<node>;

	void addNodePrivate(double ival, const numeric_p& n) & noexcept
	{
		if (root == nullptr)
			root = std::make_unique<node>(ival);

		else if (ival < n->value)
		{
			if (n->left != nullptr)
				addNodePrivate(ival, n->left);
			else
				n->left = std::make_unique<node>(ival);
		}

		else if (ival > n->value)
		{
			if (n->right != nullptr)
				addNodePrivate(ival, n->right);
			else
				n->right = std::make_unique<node>(ival);
		}
	}

	double minValuePrivate(const numeric_p& n) const & noexcept
	{
		if (n->left != nullptr)
			return minValuePrivate(n->left);
		else
			return n->value;
	}

    double maxValuePrivate(const numeric_p& n) const & noexcept
	{
		if (n->right != nullptr)
				return maxValuePrivate(n->right);
		else
			return n-> value;
	}

public:
	BST(const std::size_t& id) : id(id)
	{}

	double min() const & noexcept
	{
		return minValuePrivate(root);
	}

	double max() const & noexcept
	{
		return maxValuePrivate(root);
	};

	void add(double ival) & noexcept
	{
		addNodePrivate(ival, root);
	}
};
//-----------------------------------------------------------------------------------------------------------------
/***struct tree_stack***/
struct tree_stack
{
private:
	std::vector<BST> v;

public:
	void add_value(double val)
	{
		(v.back()).add(val);
	}

	void add_tree()
	{
		v.emplace_back(v.size());
	}

	double pop_max()
	{
		double n = (v.back()).max();
		v.pop_back();
		return n;
	}

	double pop_min()
	{
		double n = (v.back()).min();
		v.pop_back();
		return n;
	}

	void clear()
	{
		v.clear();
	}
};
//-----------------------------------------------------------------------------------------------------------------
/***struct arg_stack***/
struct arg_stack
{
private:
	double NaN = 2.22507e-308;
	std::vector<double> v;

public:
	arg_stack()
	{
		v.emplace_back(NaN);
	}

	void add_list()
	{
		v.emplace_back(NaN);
	}

	void add_value(double ival)
	{
		v.push_back(ival);
	}

	double pop_sum()
	{
		double result{0.0};
		while (v.back() != NaN)
		{
			result += (v.back());
			v.pop_back();
		}
		if (v.size() > 1)
			v.pop_back();

		return result;
	}

	double pop_rest()
	{
		double result{(v.back()) * 2};
		while (v.back() != NaN)
		{
			result -= (v.back());
			v.pop_back();
		}
		if (v.size() > 1)
			v.pop_back();

		return result;
	}

	double pop_mul()
	{
		double result{1.0};
		while (v.back() != NaN)
		{
			result *= (v.back());
			v.pop_back();
		}
		if (v.size() > 1)
			v.pop_back();

		return result;
	}

	double pop_div()
	{
		double result{std::pow((v.back()), 2)};
		while (v.back() != NaN)
		{
			result /= (v.back());
			v.pop_back();
		}
		if (v.size() > 1)
			v.pop_back();

		return result;
	}

	double pop_avg()
	{
		double result{0.0};
		std::size_t count = 0;
		while (v.back() != NaN)
		{
			++count;
			result += (v.back());
			v.pop_back();
		}
		if (v.size() > 1)
			v.pop_back();

		return result/count;
	}

	void clear()
	{
		v.clear();
	}
};
//-----------------------------------------------------------------------------------------------------------------
/***class expression_node***/
struct expression_node
{
public:
	virtual double value() const & noexcept = 0;
};
//-----------------------------------------------------------------------------------------------------------------
/***class function_node***/
struct function_node : public expression_node
{
private:
using expr_p = std::unique_ptr<expression_node>;

	expr_p m_args{nullptr};
	int m_ID;

public:
	function_node(int ID, expr_p&& args) : m_ID(ID), m_args(std::move(args))
	{}

	double value() const & noexcept override
	{
		return function_impl(m_args->value(), m_ID);
	}
};
//-----------------------------------------------------------------------------------------------------------------
/***class unary_neg_node***/
struct unary_neg_node : public expression_node
{
private:
using expr_p = std::unique_ptr<expression_node>;

	expr_p m_arg{nullptr};

public:
	unary_neg_node(expr_p&& arg) : m_arg(std::move(arg))
	{}

	double value() const & noexcept override
	{
		return -1 * m_arg->value();
	}
};
//-----------------------------------------------------------------------------------------------------------------
/***class binary_node***/
struct binary_node : public expression_node
{
private:
using expr_p = std::unique_ptr<expression_node>;

	expr_p m_left{nullptr};
	expr_p m_right{nullptr};
	int m_op;

public:
	binary_node(int op, expr_p&& l, expr_p&& r) : m_op(op), m_left(std::move(l)), m_right(std::move(r))
	{}

	double value() const & noexcept override
	{
	    switch(m_op)
		{
			case 43: return m_left->value() + m_right->value();

			case 45: return m_left->value() - m_right->value();

			case 42: return m_left->value() * m_right->value();

			case 47: return m_left->value() / m_right->value();

			case 94: return std::pow(m_left->value(), m_right->value());
		}
	}
};
//-----------------------------------------------------------------------------------------------------------------
/***class numeric_node***/
struct numeric_node : public expression_node
{
private:
	double m_value{0.0};

public:
	numeric_node(double value) : m_value(value) {}

	double value() const & noexcept override
	{
		return m_value;
	}
};
//-----------------------------------------------------------------------------------------------------------------
/***struct token_t***/
struct token_t
{
	token_t() {}

	token_t(int id, const char*  begin, const char*  end) : ID(id), data(begin, end)
	{}

	token_t(int id) : ID(id), data(std::string(1, id))
	{}

	token_t(int id, const std::string& idata) : ID(id), data(std::move(idata))
	{}

	int ID;
	std::string data;
};
//-----------------------------------------------------------------------------------------------------------------
/***class expression***/
class expression
{
private:
	std::string m_expr_str;
	std::unique_ptr<expression_node> m_et{nullptr};
	double m_result{2.22507e-308};

public:
	expression()
	{}

	expression(std::string iexpr_str) : m_expr_str(std::move(iexpr_str))
	{}

	double value()
	{
		if (m_et != nullptr && m_result == 2.22507e-308)
		{
			m_result = m_et->value();
			return m_result;
		}
	}

	void set_expression(std::string iexpr_str)
	{
		m_expr_str = std::move(iexpr_str);
	}

	bool ready()
	{
		return m_et != nullptr;
	}

	void clear()
	{
		m_et.reset(nullptr);
		m_expr_str.clear();
		m_result = 2.22507e-308;
	}

	expression_node* release()
	{
		return m_et.release();
	}
private:
	friend class parser;
};
//-----------------------------------------------------------------------------------------------------------------
/***namespace details***/
namespace details
{
	inline bool icmp(const std::string& s1, const std::string& s2)
	{
		if (s1.length() == s2.length())
		{
			for (std::size_t i = 0, length = s1.length(); i < length; ++i)
				if (std::tolower(s1[i]) != std::tolower(s2[i]))
					return false;
				return true;
		}
		return false;
	}

	static const std::string function_list[49] =
	{
		"frac"         , "ncdf"         , "erfc"         , "erf"          ,
		"sgn"          , "abs"          , "acos"         ,"acosh"         ,
		"asin"         , "asinh"        , "atan"         , "atanh"        ,
		"ceil"         , "cos"          , "cosh"         , "exp"          ,
		"expm1"        , "floor"        , "log"          , "log10"        ,
		"log2"         , "log1p"        , "logn"         , "round"        ,
		"sin"          , "sinc"         , "sinh"         , "sqrt"         ,
		"tan"          , "tanh"         , "trunc"        , "cot"          ,
		"sec"          , "csc"          , "rad2deg"      , "deg2rad"      ,
		"deg2grad"     , "grad2deg"     , "pow"          , "hypot"        ,
		"mod"          , "root"         , "sum"          , "rest"         ,
		"mul"          , "div"          , "avg"          , "max"          ,
		"min"
	};

	inline int precedenceOf(int op) noexcept
    {
		switch (op)
		{
			case  43:// +
			case  45:// -
				return 1;

			case  42:// *
			case  47:// /
				return 2;

			case  94:// ^
				return 3;

			case 117:// u
				return 4;

			case  40:// (
			case  91:// [
			case 123:// {
				return 0;
		}
	}

	inline bool is_e(const char& c) noexcept{
		return c == 'e' || c == 'E';
	}

	inline bool is_sign(const char& c) noexcept{
		return c == '+' || c == '-';
	}

	inline bool is_letter(std::size_t c) noexcept{
		return (c > 96 && c < 123) ||
			   (c > 64 && c < 91);
	}

	inline bool is_operator(const char& c) noexcept{
		return
			   '+' == c
			|| '-' == c
	    	|| '*' == c
			|| '/' == c
			|| '^' == c
			|| ',' == c
			|| 'u' == c
			|| '=' == c;
	}

	inline bool is_left_bracket(const char& c) noexcept{
		return '(' == c
			|| '{' == c
			|| '[' == c;
	}

	inline bool is_right_bracket(const char& c) noexcept{
		return ')' == c
			|| '}' == c
			|| ']' == c;
	}

	inline bool is_letter_or_digit(const char& c) noexcept{
		return (c > 47 && c <  58) ||
			   (c > 96 && c < 123) ||
			   (c > 64 && c <  91);
	}

	inline bool is_digit(const char& c) noexcept{
		return c > 47 && c < 58;
	}
}

inline bool is_op(const char& c) noexcept
{
	return '*' == c
		|| '/' == c
		|| ',' == c;
}
using namespace details;
void toTeX(std::string& s)
{	
	std::size_t pos;
	int i = 0;
	
	while ((pos = s.find("+-")) != std::string::npos)
		s.replace(pos, 2, "\\pm");
	
	// Modify sqrt
	while ((pos = s.find("sqrt", i)) != std::string::npos)
	{
		s[i = pos+4] = '{';
		std::size_t count = 1; 
		while (++i)
		{
			if (is_left_bracket(s[i]))
				++count;
			else if (is_right_bracket(s[i]))
				--count;
			if (0 == count)
			{
				s[i] = '}';
				break;
			}
		}
		s.insert(pos, "\\");
	}
	
	// Modify Divisions
	while ((pos = s.find("/")) != std::string::npos)
	{
		i = pos;
		// Check for left expr between ()
		if (is_right_bracket(s[i-1]))
		{
			std::size_t count = 0;
			while (--i)
		    {
			    if (is_right_bracket(s[i]))
					++count;
			    else if (is_left_bracket(s[i]))
					--count;
			    if (0 == count)
					break;
		    }
		    s.insert(i, "{"); ++pos;
		}
		else
		{
            while (--i > -1)
			{
				if (is_sign(s[i]))
				{
					if (0 == i || is_op(s[i-1]))
					{
						s.insert(i, "{"); ++pos; break;
					}
					else
					{
						s.insert(i+1, "{"); ++pos; break;
					}
				}
				else if (is_op(s[i]))
				{
					s.insert(i+1, "{"); ++pos; break;
				}
				else if (details::is_left_bracket(s[i]))
				{
					s[i] = '{'; break;
				}
			}
		}
		
		// Check for right expr between ()
		i = pos;
		if (is_left_bracket(s[i+1]))
		{
			std::size_t count = 0;
			while (++i < s.length())
		    {
			    if (')' == s[i]) --count;
			    else if ('(' == s[i]) ++count;
			    if (0 == i) break;
		    }
			s.insert(i, "}");
		}
		else
		{
            while (++i)
			{
				if (details::is_right_bracket(s[i]))
				{
					s[i] = '}'; break;
				}
				
				else if (is_op(s[i]) || i == s.length())
				{
					s.insert(i, "}"); 
					if (i < s.length()-1)
						++pos; 
					break;
				}
			}
		}
		s.replace(pos, 1, "\\over");
	}
}

//-----------------------------------------------------------------------------------------------------------------
/***namespace generator***/
namespace generator
{
	void tokenize(const std::string& expr, std::vector<token_t>* tokens)
	{
		const char* end = expr.data() + expr.size();
		const char* c = expr.data();

		tokens->emplace_back(78, "0");
		tokens->emplace_back(43);

		while(c != end)
		{
			while (*c == ' ')
			++c;

			if (details::is_sign(*c))								                     // Sign
			{
				if (details::is_operator(*(c-1)) || details::is_left_bracket(*(c-1)))    // Unary Sign
				{
					if (*c == '-')
						tokens->emplace_back(117);// 'u'                                 // Unary Minus
					++c;															     // Skip Unary Plus
				}
				else																	 // Binary Sign
				{					
					tokens->emplace_back(static_cast<int>(*c));
					++c;
				}
				continue;
			}

			else if (details::is_digit(*c) || '.' == *c)								 // Number
			{
				const char* begin = c;
				bool dot_found = false;
				bool e_found = false;
				bool post_e_digit_found = false;
				bool post_e_sign_found = false;

				while (c != end)
				{
					if ('.' == *c)
					{
						assert (!dot_found);
						dot_found = true;
						++c;
						continue;
					}
					else if (details::is_e(*c))
					{
						assert (!e_found);
						e_found = true;
						++c;
						continue;
					}
					else if (e_found && details::is_sign(*c) && !post_e_digit_found)
					{
						assert (!post_e_sign_found);
						post_e_sign_found = true;
						++c;
						continue;
					}
					else if (e_found && details::is_digit(*c))
					{
						post_e_digit_found = true;
						++c;
						continue;
					}
					else if (('.' != (*c)) && !details::is_digit(*c))
					break;
					else// White space or Number
						++c;
				}
				if (e_found && !post_e_digit_found)// euler?
				{
					tokens->emplace_back(78, begin, c-1);// N
					tokens->emplace_back(42);// *
					tokens->emplace_back(101);// e
				}
				else
				tokens->emplace_back(78, begin, c);// N
				continue;
			}

			else if (details::is_letter(*c))									   	 	 // Symbol
			{
				if (details::is_digit(*(c-1)))                                           // Coefficient
				tokens->emplace_back(42);// *

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
							tokens->emplace_back(i * -1, s); 
							is_function = true; break;
						}
					}
					if (is_function)
					continue;
				}
				tokens->emplace_back(83, s);// S
				continue;
			}

			else if (details::is_left_bracket(*c))									 	 // Left Bracket
			{
				if (
					tokens->back().ID > 0 && !details::is_operator(tokens->back().ID) &&
					!details::is_left_bracket(*(c-1))
				)                       							                     // Multiplication
				tokens->emplace_back(42);// '*'

				tokens->emplace_back(40);// '('
				++c;
				continue;
			}

			else if (details::is_right_bracket(*c)) 								 	 // Right Bracket
			{
				tokens->emplace_back(41);// ')'
				++c;
				if (details::is_left_bracket(*c) || details::is_letter_or_digit(*c))     // Multiplication
					tokens->emplace_back(42);// '*'
				continue;
			}

			else if (details::is_operator(*c))                                       	 // Non Sign Operator
			{
				tokens->emplace_back(static_cast<int>(*c));
				++c;
				continue;
			}

			else																	 	 // Space?
				++c;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------
/***struct symbol_table***/
struct symbol_table
{
private:
typedef std::map<std::string, double>::const_iterator m_s_d_cit;
typedef std::map<std::string, double>::iterator m_s_d_it;
	std::map<std::string, double> var_store;
	bool using_constants = true;

public:
	bool symbol_exist(const std::string& iname) const & noexcept
	{
		if (using_constants)
		{
			if (details::icmp(iname, "pi")) return true;
			if (details::icmp(iname,  "e")) return true;
		}
		return (var_store.find(iname) != var_store.cend());
	}

	void add_variable(std::string name, double value) & noexcept
	{
		if (!symbol_exist(name))
			var_store.emplace(name, value);
	}

	bool replace_symbol_name(const std::string& old_name, const std::string& new_name)
	{
	    m_s_d_cit it = var_store.find(old_name);
		if (it != var_store.cend())
		{
			var_store.emplace(new_name, it->second);
			var_store.erase(it);
			return true;
		}
		return false;
	}

	bool replace_symbol_value(const std::string& isymbol_name, double new_value)
	{
	    m_s_d_it it = var_store.find(isymbol_name);
		if (it != var_store.cend())
        {
			it->second = new_value;
			return true;
		}
		return false;
	}

	bool delete_symbol(const std::string& old_symbol)
	{
	    m_s_d_cit it = var_store.find(old_symbol);
		if (it != var_store.cend())
        {
			var_store.erase(it);
			return true;
		}
		else
			return false;
	}

	void enable_constants()
	{
		using_constants = true;
	}

	void disable_constants()
	{
		using_constants = false;
	}

	bool constants_enabled()
	{
		return using_constants;
	}

	double value_of(const std::string& iname) const & noexcept
	{
		if (using_constants)
		{
			if (details::icmp(iname, "pi")) return numeric_constant::pi;
			if (details::icmp(iname,  "e")) return numeric_constant::e;
		}

		m_s_d_cit it = var_store.find(iname);
		if (it != var_store.cend())
			return it->second;

		return 2.22507e-308;
	}
private:
friend class parser;
};
//----------------------------------------------------------------------------------------------------------------------
/***class parser***/
class parser
{
private:
	using expr_p = std::unique_ptr<expression_node>;
	using binary_p = std::unique_ptr<binary_node>;
	using unary_p = std::unique_ptr<unary_neg_node>;
	using numeric_p = std::unique_ptr<numeric_node>;
	using function_p = std::unique_ptr<function_node>;


	std::vector<symbol_table> m_symbol_table_list;// Symbol Table List
	symbol_table* c_symbol_table{nullptr};        // Current Symbol Table


	std::vector<token_t> m_token_list;            // Token_t List
	std::vector<expr_p> m_output;                 // Holder of AST
	std::vector<int> m_operators;				  // Operators
	std::vector<int> m_function_list;	          // Function List
	arg_stack arg_list;	                          // Args Holder
	tree_stack tree_list;				          // Min && Max


    bool insideFunction = false;                  // Helpers
	std::size_t count{0};

private:
	void clean_up() noexcept
	{
		insideFunction = false;
		count = 0;

		if (!m_symbol_table_list.size())
			c_symbol_table = nullptr;
		else
			c_symbol_table = &(m_symbol_table_list.back());

		m_output.clear();
		m_operators.clear();
		m_function_list.clear();
		m_token_list.clear();
		arg_list.clear();
		tree_list.clear();
	}

	void make_unary()
	{
		expr_p arg = std::move(m_output.back());  m_output.pop_back();

		unary_p p = std::make_unique<unary_neg_node>(std::move(arg));

		m_output.push_back(std::move(p));
	}

	void make_binary()
	{
		expr_p rhs = std::move(m_output.back());  m_output.pop_back();
		expr_p lhs = std::move(m_output.back());   m_output.pop_back();

		binary_p p = std::make_unique<binary_node>(m_operators.back(), std::move(lhs), std::move(rhs));

		m_output.push_back(std::move(p));
	}

    void process_operator(int op)
	{
		int opPrecedence = details::precedenceOf(op);
		while (m_operators.size() &&
			   details::precedenceOf(m_operators.back()) >=
			   opPrecedence
			   )
		{
			if ('u' == m_operators.back())
				make_unary();
			else
				make_binary();

			m_operators.pop_back();
		}
		m_operators.emplace_back(op);
    }

    void process_left_bracket()
    {
    	m_operators.emplace_back('(');

		if (insideFunction)
			++count;
    }

	void process_right_bracket()
	{
		 while (m_operators.back() != '(')
		 {
			if ('u' == m_operators.back())
				make_unary();
			else
				make_binary();

			m_operators.pop_back();
		 }
		 m_operators.pop_back();

		 if (insideFunction && !--count)
		 {
			if (m_function_list.back() > -38)		    // Unary
			{
				function_p p = std::make_unique<function_node>
				(m_function_list.back(), std::move(m_output.back()));

				m_output.pop_back();
				m_output.push_back(std::move(p));
			}
			else
				var_args_impl();					// Binary/Variadic

			m_function_list.pop_back();

			if (!m_function_list.size())
				insideFunction = false;
		 }
	}

	void var_args_impl()
	{
		numeric_p p;

		if (m_function_list.back() < -46)
		{
			tree_list.add_value((m_output.back())->value());
			m_output.pop_back();

		    p = (m_function_list.back() == -47) ?
			std::make_unique<numeric_node>(tree_list.pop_max())  :
			std::make_unique<numeric_node>(tree_list.pop_min());
		}
		else if (m_function_list.back() > -42)
		{
			double y = (m_output.back())->value();
			m_output.pop_back();

			double x = (m_output.back())->value();
			m_output.pop_back();

			switch (m_function_list.back())
			{
				case -38:// Pow
				p = std::make_unique<numeric_node>(std::pow(x, y));
				break;

				case -39:// Hypot
				p = std::make_unique<numeric_node>(std::hypot(x, y));
				break;

				case -40:// Mod
				p = std::make_unique<numeric_node>(x - std::floor(x/y) * y);
				break;

				case -41:// Root
				p = std::make_unique<numeric_node>(std::pow(x, 1/y));
			}
		}
		else
		{
			arg_list.add_value((m_output.back())->value());
			m_output.pop_back();

			switch (m_function_list.back())
			{
								case -46:// Avg
				p = std::make_unique<numeric_node>(arg_list.pop_avg());
				break;

								case -45:// Div
				p = std::make_unique<numeric_node>(arg_list.pop_div());
				break;

								case -44:// Mul
				p = std::make_unique<numeric_node>(arg_list.pop_mul());
				break;

								case -43:// Rest
				p = std::make_unique<numeric_node>(arg_list.pop_rest());
				break;

								case -42:// Sum
				p = std::make_unique<numeric_node>(arg_list.pop_sum());
			}
		}
 		m_output.push_back(std::move(p));
	}

	void process_numeric(const std::string& s) noexcept
	{
		m_output.push_back(std::make_unique<numeric_node>(std::stod(s)));
	}

	void process_symbol(std::string& s) noexcept
	{
		if (!c_symbol_table->symbol_exist(s))
		{
			double n{0.0};
			cout << s << " = ";
			cin >> n;
			c_symbol_table->add_variable(s, n);
			m_output.push_back(std::make_unique<numeric_node>(n));
		}
		else
		m_output.push_back(std::make_unique<numeric_node>(c_symbol_table->value_of(s)));
	}

	void process_comma()
	{
		while (m_operators.back() != '(')
		{
			if ('u' == m_operators.back())
				make_unary();
			else
				make_binary();

			m_operators.pop_back();
		}

		if (m_function_list.back() < -41)
		{
			switch (m_function_list.back())
			{
				case -48:
				case -47:
						tree_list.add_value((m_output.back())->value());
						m_output.pop_back();
						break;

				default:
						arg_list.add_value((m_output.back())->value());
						m_output.pop_back();
			}
		}
	}

	void process_function(int functionID)
	{
		switch (functionID)
		{
			case -42:		// Sum
			case -43:		// Rest
			case -44:		// Mul
			case -45:		// Div
			case -46:		// Avg
					arg_list.add_list();
					break;
			case -47:		// Max
			case -48:		// Min
					tree_list.add_tree();
		}
		m_function_list.push_back(functionID);
		insideFunction = true;
		count = 0;
	}

    binary_node* parse()
	{
		for (token_t& token : m_token_list)
		{
			switch (token.ID)
			{
				case 'u':
				case '+':
				case '-':
				case '*':
				case '/':
				case '^':
						process_operator(token.ID);
						break;

				case ')':
						process_right_bracket();
						break;

				case '(':
					    process_left_bracket();
						break;

				case 'S':
						process_symbol(token.data);
						break;

				case 'N':
						process_numeric(token.data);
						break;

				case ',':
				        process_comma();
				        break;

				default:
						process_function(token.ID);
			}
		}
		while (m_operators.size())
		{
			if ('u' == m_operators.back())
				make_unary();
			else
				make_binary();

			m_operators.pop_back();
		}
		assert (m_output.size() == 1);

		binary_node* p = dynamic_cast<binary_node*>((m_output.back()).release());

		return p;
	}

	void process_expression(expression& iexpr_t)
	{
		iexpr_t.m_et.reset(parse());
	}

	bool is_assignment()
	{
		return '=' == m_token_list[3].ID;
	}

	void process_assignment()
	{
		std::string isymbol = std::move(m_token_list[2].data);

		m_token_list[2] = token_t(78, "0");
		m_token_list[3].ID = 43;

		if (!c_symbol_table->symbol_exist(isymbol))
		    c_symbol_table->add_variable(isymbol, parse()->value());

		else
			c_symbol_table->replace_symbol_value(isymbol, parse()->value());
	}

public:
	void register_symbol_table(symbol_table& i_symtab) &
	{
		m_symbol_table_list.push_back(i_symtab);
	}

	void remove_symbol_tables() & noexcept
	{
		 m_symbol_table_list.clear();
	}

	bool compile(expression& iexpr_t, const std::string& iexpr_str) &
	{
		if (!iexpr_str.length() || is_assignment())
			return false;

		generator::tokenize(iexpr_str, &m_token_list);
	    process_expression(iexpr_t);

		clean_up();

		return true;
	}

	bool compile(expression& iexpr_t, std::string& iexpr_str, symbol_table& itemp_symtab) &
	{
		if (!iexpr_str.length())
			return false;

		c_symbol_table = &itemp_symtab;
		generator::tokenize(iexpr_str, &m_token_list);

		if (is_assignment())
	        process_assignment();
		else
		{
	        process_expression(iexpr_t);
			
			toTeX(iexpr_str);
			cout.precision(100);
			
			cout << "<hr color = \"red\" size = \"15\"/>";
			cout << "<h2 class = \"rojo\" align = \"center\"><ins> Resultado: </ins></h2>";
		    cout << "<p class = \"azul_fuerte\" align = \"center\"><font size = \"4\">$$" << iexpr_str << " = " << iexpr_t.value() << "$$</font></p>";
			cout << "<hr color = \"red\" size = \"15\"/>";
			cout << "<h2 class = \"rojo\" align = \"center\"><ins> TOKENS: </ins></h2>";
			for (std::size_t i = 2, size = m_token_list.size(); i < size; ++i)
			{
				switch (m_token_list.at(i).ID)
				{
					case 78:
						cout << "<p/ align = \"center\"><span class = \"morado\"><strong>Número</strong></span> <span align = \"center\">::= <strong>" << m_token_list.at(i).data << "</strong></span></p>";
					break;
					
					case 83:
						cout << "<p/ align = \"center\"><span class = \"morado\"><strong>Símbolo</strong></span> <span align = \"center\">::= <strong>" << m_token_list.at(i).data << "</strong></span></p>";
					break;	
					
					case 'u':
						cout << "<p/ align = \"center\" class = \"rojo\"><strong>\'-\' Unario</strong></p>";
					break;		
					
					default:
						if (m_token_list.at(i).ID > 0)
							cout << "<p/ align = \"center\"><span class = \"morado\"><strong>Operador</strong></span> <span align = \"center\">::= <strong>" << (char)m_token_list.at(i).ID << "</strong></span></p>";
						else
							cout << "<p/ align = \"center\"><span class = \"morado\"><strong>Función</strong></span> <span align = \"center\">::= <strong>" << m_token_list.at(i).data << "</strong></span></p>";
				}
			}
		}
			
		clean_up();

		return true;
	}

	bool compile(expression& iexpr_t) &
	{
		if (!iexpr_t.m_expr_str.length() || is_assignment())
			return false;

		generator::tokenize(iexpr_t.m_expr_str, &m_token_list);
	    process_expression(iexpr_t);

		clean_up();

		return true;
	}

	bool compile(expression& iexpr_t, symbol_table& itemp_symtab) &
	{
		if (!iexpr_t.m_expr_str.length())
			return false;

		c_symbol_table = &itemp_symtab;
		generator::tokenize(iexpr_t.m_expr_str, &m_token_list);

		if (is_assignment())
	        process_assignment();
		else
	        process_expression(iexpr_t);

		clean_up();

		return true;
	}
};
//-----------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	std::string s(argv[1]);
	
	symbol_table t;
	//t.disable_constants();
	parser p;
	expression e;
	
	p.compile(e, s, t);
	
	return 0;
}