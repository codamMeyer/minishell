#include "calculator.h"
 
t_optional_double create_empty_optional_double() 
{
    t_optional_double optional = {
                                .value = 0,
                                .is_initialized = FALSE,
                            };

    return (optional);
}

t_optional_double create_optional_double(double value) 
{
    t_optional_double optional = {
                                .value = value,
                                .is_initialized = TRUE,
                            };

    return (optional);
}

t_operation get_operation(char operation_str) 
{
    if (operation_str == SUM)
        return (SUM);
    if (operation_str == SUBTRACTION)
        return (SUBTRACTION);
    if (operation_str == MULTIPLICATION)
        return (MULTIPLICATION);
    if (operation_str == DIVISION)
        return (DIVISION);
    return (INVALID_OPERATION);
}

double sum(double first, double second) 
{
    return (first + second);
}

double subtrac(double first, double second) 
{
    return (first - second);
}

double multiply(double first, double second) 
{
    return (first * second);  
}

double divide(double first, double second) 
{
    return (first / second);
}

t_optional_double calculator(double first, double second, char operation_str) 
{
    const t_operation operation = get_operation(operation_str);

    if (operation == INVALID_OPERATION)
        return (create_empty_optional_double());
    if (operation == SUM)
        return (create_optional_double(sum(first, second)));
    if (operation == SUBTRACTION)
        return (create_optional_double(subtrac(first, second)));
    if (operation == MULTIPLICATION)
        return (create_optional_double(multiply(first, second)));
    else
        return (create_optional_double(divide(first, second)));
}
