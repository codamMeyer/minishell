#include <commands/commands.h>
#include <defines.h>
#include <parser/command_table.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "ctest.h"
#include <fcntl.h>

CTEST(create_files, create_test_files)
{
    char no_implicit_quotes[] = "      test_file     ";
    int test_fd = open(&no_implicit_quotes[0], O_RDWR | O_CREAT | O_TRUNC, FILE_RIGHTS);
    close(test_fd);
    test_fd = open("test_file",  O_RDWR | O_CREAT | O_TRUNC, FILE_RIGHTS);
}

CTEST(spaces_test, empty_str)
{
    ASSERT_EQUAL(0, count_consecutive_spaces(""));
}

CTEST(spaces_test, spaced_str)
{
    ASSERT_EQUAL(4, count_consecutive_spaces("    "));
    ASSERT_EQUAL(4, count_consecutive_spaces("    cmd"));

}

CTEST(replace_with_whitespace, basic_test)
{
    char *str = ft_strdup("remove thisSuccess!");
    char exp[] = "           Success!";
    replace_redirection_w_space(&str, 11, 0);
    ASSERT_STR(exp, str);
    free(str);
}

CTEST(file_name_tests, basic_file_name)
{
    t_buffer buffer;
    init_buffer(&buffer);
    char file_name[] = "test_file";
    ASSERT_EQUAL(ft_strlen(&file_name[0]) + 1, get_file_name_and_length(&buffer, file_name, 0));
    ASSERT_STR(file_name, buffer.buf);
}

CTEST(file_name_tests, file_name_with_spaces)
{
    t_buffer buffer;
    init_buffer(&buffer);
    char file_name[] = "\"      test_file      \"";
    ASSERT_EQUAL(ft_strlen(&file_name[0]) + 1, get_file_name_and_length(&buffer, file_name, 0));
    ASSERT_STR("      test_file      ", buffer.buf);
    system("rm  \"      test_file     \"");
}

CTEST(file_name_tests, file_name_with_next_command)
{
    t_buffer buffer;
    init_buffer(&buffer);
    int expected = ft_strlen("test_file") + 1;
    char file_name[] = "test_file | applesauces";
    ASSERT_EQUAL(expected, get_file_name_and_length(&buffer, file_name, 0));
    ASSERT_STR("test_file", buffer.buf);
}

CTEST(file_name_tests, file_name_with_spaces_and_quotes)
{
    t_buffer buffer;
    init_buffer(&buffer);
    char file_name[] = "\"      test_file\"| applesauces";
    ASSERT_EQUAL(ft_strlen("      test_file") + 3, get_file_name_and_length(&buffer, file_name, 0));
    ASSERT_STR("      test_file", buffer.buf);
}

CTEST(handle_infile, basic_infile)
{
    char input[] = "< test_file";
    t_files  fd;

    fd.in = -1;
    ASSERT_EQUAL(ft_strlen(input), open_file(&input[0], &fd, LEFT_ANGLE));
    ASSERT_NOT_EQUAL(-1, fd.in);
    close(fd.in);
}

CTEST(handle_infile, infile_with_space_no_quotes)
{
    char input[] = "<      test_file";
     t_files  fd;

    fd.in = -1;
    ASSERT_EQUAL(ft_strlen(input), open_file(&input[0], &fd, LEFT_ANGLE));
    ASSERT_NOT_EQUAL(-1, fd.in);
    close(fd.in);
}

CTEST(handle_infile, infile_with_space_and_quotes)
{
    char input[] = "< \"      test_file     \"";
    char no_implicit_quotes[] = "      test_file     ";
    int test_fd = open(&no_implicit_quotes[0], O_RDWR | O_CREAT | O_TRUNC, FILE_RIGHTS);
    close(test_fd);
    t_files  fd;

    fd.in = -1;
    ASSERT_EQUAL(ft_strlen(input), open_file(&input[0], &fd, LEFT_ANGLE));
    ASSERT_NOT_EQUAL(-1, fd.in);
    close(fd.in);
    system("rm  \"      test_file     \"");
}

CTEST(get_fds, operations_test)
{
    char *str = ft_strdup(" test_file echo halla | cat -e");
    t_files fd;

    int result = open_file((char*)str, &fd, '<');
    ASSERT_EQUAL(ft_strlen(" test_file"), result);
    ASSERT_NOT_EQUAL(-1, fd.in);
    free(str);
}

CTEST(redirection_test, basic_infile)
{
    char *str = ft_strdup("echo < test_file | cat -e");
    const char *expected=("echo             | cat -e");
    t_files files;

    files = get_redirection(&str, get_set_index("echo < test_file | cat -e", "|"));
    ASSERT_NOT_EQUAL(-1, files.in);
    ASSERT_STR(expected, str);
    free(str);
    system("rm test_file");
}

CTEST(redirection_test, infile_inside_command_argument)
{
    int test_fd = open("test_file",  O_RDWR | O_CREAT | O_TRUNC, FILE_RIGHTS);
    close(test_fd);
    char *str = ft_strdup("echo halla <test_file everybody");
    const char *expected=("echo halla            everybody");
    t_files files;

    files = get_redirection(&str, get_set_index("echo halla <test_file everybody", "|"));
    ASSERT_NOT_EQUAL(-1, files.in);
    ASSERT_STR(expected, str);
    free(str);
    system("rm test_file");
}
