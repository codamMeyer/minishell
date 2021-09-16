#include <commands/commands.h>
#include <parser/command_table.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "ctest.h"
#include <fcntl.h>

#define BUFFERSIZE 1024

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
    replace_redirection_w_whitespace(&str, 11, 0);
    ASSERT_STR(exp, str);
    free(str);
}

CTEST(file_name_tests, basic_file_name)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "test_file";
    ASSERT_EQUAL(ft_strlen(&file_name[0]), get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR(file_name, buffer);
}

CTEST(file_name_tests, file_name_with_spaces)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "\"      test_file      \"";
    ASSERT_EQUAL(ft_strlen(&file_name[0]), get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR("      test_file      ", buffer);
}

CTEST(file_name_tests, file_name_with_next_command)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "test_file | applesauces";
    ASSERT_EQUAL(9, get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR("test_file", buffer);
}

CTEST(file_name_tests, file_name_with_spaces_and_quotes)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "\"      test_file\"| applesauces";
    ASSERT_EQUAL(ft_strlen("      test_file") + 2, get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR("      test_file", buffer);
}

CTEST(handle_infile, basic_infile)
{
    char input[] = "test_file";
    int  fd     = -1;
    ASSERT_EQUAL(ft_strlen(input), open_infile(&input[0], &fd));
    ASSERT_NOT_EQUAL(-1, fd);
    close(fd);
}

CTEST(handle_infile, infile_with_space_no_quotes)
{
    char input[] = "      test_file";
    int  fd     = -1;
    ASSERT_EQUAL(ft_strlen(input), open_infile(&input[0], &fd));
    ASSERT_NOT_EQUAL(-1, fd);
    close(fd);
}

CTEST(handle_infile, infile_with_space_and_quotes)
{
    char input[] = "\"      test_file     \"";
    char no_implicit_quotes[] = "      test_file     ";
    int test_fd = open(&no_implicit_quotes[0], O_RDWR | O_CREAT | O_TRUNC, 0664);
    close(test_fd);
    int  fd     = -1;
    ASSERT_EQUAL(ft_strlen(input), open_infile(&input[0], &fd));
    ASSERT_NOT_EQUAL(-1, fd);
    close(fd);
}

CTEST(get_fds, operations_test)
{
    char *str = ft_strdup(" test_file echo halla | cat -e");
    t_files fd;

    int result = get_files_descriptors((char*)str, &fd, '<');
    ASSERT_EQUAL(ft_strlen(" test_file"), result);
    ASSERT_NOT_EQUAL(-1, fd.in);
    free(str);
}

CTEST(redirection_test, basic_infile)
{
    char *str = ft_strdup("echo < test_file | cat -e");
    const char *expected=("echo             | cat -e");
    t_files files;

    files = get_redirection(&str);
    ASSERT_NOT_EQUAL(-1, files.in);
    ASSERT_STR(expected, str);
    free(str);
}
