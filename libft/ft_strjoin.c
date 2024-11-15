/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:21:46 by ahamdi            #+#    #+#             */
/*   Updated: 2023/12/25 18:44:37 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str_re;
	size_t	len_total;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_total = len_s1 + len_s2 + 1;
	str_re = malloc (len_total);
	if (str_re == NULL)
		return (NULL);
	ft_strlcpy (str_re, s1, len_total);
	ft_strlcat (str_re, s2, len_total);
	return (str_re);
}
