/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:29:18 by akheired          #+#    #+#             */
/*   Updated: 2024/11/03 10:42:08 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	count_word(const char *str)
{
	size_t	count;
	size_t	i;
	size_t	len;

	count = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		while (i < len && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (i < len)
			count++;
		while (i < len && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}
	return (count);
}

static size_t	count_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}

static char	*str_alloc(const char *str)
{
	size_t	wordlen;
	char	*word;
	size_t	i;

	wordlen = count_len(str);
	word = (char *)malloc(sizeof(char) * (wordlen + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < wordlen)
	{
		word[i] = str[i];
		i++;
	}
	word[wordlen] = '\0';
	return (word);
}

static int	allocate_and_copy(char ***strings, char *str, size_t *i)
{
	(*strings)[*i] = str_alloc(str);
	if (!(*strings)[*i])
	{
		free_strings(*strings, *i);
		return (0);
	}
	(*i)++;
	return (1);
}

char	**spliter(char *str)
{
	size_t	total_words;
	char	**strings;
	size_t	i;

	if (!str)
		return (NULL);
	total_words = count_word(str);
	strings = (char **)malloc(sizeof(char *) * (total_words + 1));
	if (!strings)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
			str++;
		if (*str && !allocate_and_copy(&strings, str, &i))
			return (NULL);
		while (*str && *str != ' ' && *str != '\t' && *str != '\n')
			str++;
	}
	strings[i] = NULL;
	return (strings);
}
