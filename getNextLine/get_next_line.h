/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:37:55 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/17 14:45:51 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*ft_read(int fd, char *str, int r_byt);
char	*ft_premierstr(char *str, int i);
char	*ft_desiemstr(char *s, size_t i);
char	*get_next_line(int fd);
#endif
