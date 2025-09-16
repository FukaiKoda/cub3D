/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:57:29 by habdella          #+#    #+#             */
/*   Updated: 2025/09/16 16:03:15 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

int	ft_atoi(const char *nptr)
{
	int	num;

	num = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (!(*nptr >= '0' && *nptr <= '9'))
		clean_exit("only numbers are accepted\n");;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (*nptr - '0') + (num * 10);
		nptr++;
	}
    if (num >= 0 && num <= 255)
	    return (num);
	clean_exit("number out of RGB range\n");
    return (-1);
}

int	check(char *charset, char c)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_sizeof(char *str, char *charset)
{
	int		i;
	int		flag;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		flag = 0;
		while (str[i] && !check(charset, str[i]))
			i++;
		while (str[i] && check(charset, str[i]))
		{
			if (!flag)
				size++;
			flag = 1;
			i++;
		}
	}
	return (size);
}

int	ft_len(char *str, int n, char *charset)
{
	int		len;

	len = 0;
	while (str[n] && check(charset, str[n]))
	{
		len++;
		n++;
	}
	return (len);
}

char	**ft_split(char *str, char *charset, int *nb_words)
{
	char	**split;
	int		len;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_sizeof(str, charset);
	*nb_words = size;
	split = ft_malloc(8 * (size + 1));
	while (str[i])
	{
		while (str[i] && !check(charset, str[i]))
			i++;
		if (str[i])
		{
			len = ft_len(str, i, charset);
			split[j++] = ft_strduplen(&str[i], len);
			i += len;
		}
	}
	split[j] = NULL;
	return (split);
}
