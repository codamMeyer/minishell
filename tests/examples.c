#include <stdlib.h>
#include "ctest.h"
#include "calculator.h"


// A test suite without a setup/teardown function
CTEST(get_opeartion_test, invalid_operation)
{
    t_operation operation = get_operation('v');
    ASSERT_DBL_NEAR(INVALID_OPERATION, operation);
}

CTEST(get_opeartion_test, valid_operations)
{
    ASSERT_EQUAL(SUM, get_operation('+'));
    ASSERT_EQUAL(SUBTRACTION, get_operation('-'));
    ASSERT_EQUAL(MULTIPLICATION, get_operation('*'));
    ASSERT_EQUAL(DIVISION, get_operation('/'));
}

// A test suite with a setup function
CTEST_DATA(operations_test)
{
    double first_number;
    double second_number;
};

// Optional setup function for suite, called before every test in suite
CTEST_SETUP(operations_test)
{
    data->first_number = 10;
    data->second_number = 5;
}

// These tests are called with the struct* (named data) as argument
CTEST2(operations_test, basic_sum)
{
    ASSERT_EQUAL(15, sum(data->first_number, data->second_number));
}

CTEST2_SKIP(operations_test, invalid_sum)
{
    // instead of commenting the test, if you write _SKIP the test will be skipped
    (void)data;
    ASSERT_FALSE(1);
}

CTEST2(operations_test, basic_subtraction)
{
    ASSERT_EQUAL(5, subtrac(data->first_number, data->second_number));
}

CTEST2(operations_test, basic_multiplication)
{
    ASSERT_EQUAL(50, multiply(data->first_number, data->second_number));
}

CTEST2(operations_test, basic_division)
{
    ASSERT_EQUAL(2, divide(data->first_number, data->second_number));
}


CTEST_DATA(calculator_first_bigger_than_second_test)
{
    double first_number;
    double second_number;
    t_optional_double result;
};

CTEST_SETUP(calculator_first_bigger_than_second_test)
{
    data->first_number = 20;
    data->second_number = 10;
    data->result = create_empty_optional_double();
}

CTEST2(calculator_first_bigger_than_second_test, invalid_operation)
{
    data->result = calculator(data->first_number, data->second_number, '.');
    ASSERT_FALSE(data->result.is_initialized);
}

CTEST2(calculator_first_bigger_than_second_test, sum)
{
    data->result = calculator(data->first_number, data->second_number, SUM);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(30.0, data->result.value);
}

CTEST2(calculator_first_bigger_than_second_test, subtraction)
{
    data->result = calculator(data->first_number, data->second_number, SUBTRACTION);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(10.0, data->result.value);
}

CTEST2(calculator_first_bigger_than_second_test, multiplication)
{
    data->result = calculator(data->first_number, data->second_number, MULTIPLICATION);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(200.0, data->result.value);
}

CTEST2(calculator_first_bigger_than_second_test, division)
{
    data->result = calculator(data->first_number, data->second_number, DIVISION);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(2.0, data->result.value);
}

CTEST_DATA(calculator_second_bigger_than_first_test)
{
    double first_number;
    double second_number;
    t_optional_double result;
};

CTEST_SETUP(calculator_second_bigger_than_first_test)
{
    data->first_number = 10;
    data->second_number = 20;
    data->result = create_empty_optional_double();
}

CTEST2(calculator_second_bigger_than_first_test, sum)
{
    data->result = calculator(data->first_number, data->second_number, SUM);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(30.0, data->result.value);
}

CTEST2(calculator_second_bigger_than_first_test, subtraction)
{
    data->result = calculator(data->first_number, data->second_number, SUBTRACTION);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(-10.0, data->result.value);
}

CTEST2(calculator_second_bigger_than_first_test, multiplication)
{
    data->result = calculator(data->first_number, data->second_number, MULTIPLICATION);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(200.0, data->result.value);
}

CTEST2(calculator_second_bigger_than_first_test, division)
{
    data->result = calculator(data->first_number, data->second_number, DIVISION);
    ASSERT_TRUE(data->result.is_initialized);
    ASSERT_DBL_NEAR(0.5, data->result.value);
}
