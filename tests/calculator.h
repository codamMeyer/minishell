#ifndef CALCULATOR_H
#define CALCULATOR_H
#define TRUE 1
#define FALSE 0

typedef enum e_operation
{
	INVALID_OPERATION = -1,
	SUM = '+',
	SUBTRACTION = '-',
	MULTIPLICATION = '*',
	DIVISION = '/',
}	t_operation;

typedef int t_bool;

typedef struct s_optional_double
{
	double value;
	t_bool is_initialized;
} t_optional_double;


t_optional_double	create_empty_optional_double();
t_optional_double	create_optional_double(double value);

t_operation	get_operation(char operation_str);
double		sum(double first, double second);
double		subtrac(double first, double second);
double		multiply(double first, double second);
double		divide(double first, double second);
t_optional_double		calculator(double first, double second, char operation_str);

#endif