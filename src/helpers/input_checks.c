/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:50:49 by habdella          #+#    #+#             */
/*   Updated: 2025/09/16 17:20:10 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	putstr_fd(char *s, int fd)
{
	int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

int check_file_access(char *file_name)
{
    int fd;
    
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("");
        return (1);
    }
    close(fd);
    return (0);
}

int check_file_extension(char *str, char *extension)
{
    int i;
    int j;
    int str_len;
    int len2;

    str_len = ft_strlen(str);
    len2 = ft_strlen(extension);
    i = str_len - 1;
    j = len2 - 1;
    while (i >= 0 && j >= 0)
    {
        if (str[i] != extension[j])
            break;
        i--;
        j--;
    }
    if (j == -1 && i != -1)
        return (0);
    return (1);
}

int initial_checks(int argc, char **argv)
{
    if (argc != 2)
    {
        putstr_fd("Invalid number of arguments", 2);
        return (1);
    }
    if (check_file_extension(argv[1], ".cub"))
    {
        putstr_fd("Invalid file", 2);
        return (1);
    }
    if (check_file_access(argv[1]))
        return (1);
    return (0);
}
