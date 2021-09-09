#ifndef GET_EXECUTABLE_PATH_H
# define GET_EXECUTABLE_PATH_H

# define PATH "PATH"
# define COLON ':'
# define FORWARD_SLASH '/'
# define CMD_BUFFER_SIZE 4096
# define TERMINATOR 1

int		is_executable(char *full_path_executable);
char	*get_executable_path(const char *command);

#endif
