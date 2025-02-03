SRCS =	main.c getNextLine/get_next_line_utils.c getNextLine/get_next_line.c  texture/draw.c texture/control_kebord.c\
		texture/draw_util1.c  texture/ray.c texture/rander_util1.c  texture/rander_wall.c  texture/chek_distance_horizental.c  texture/draw_mini_map.c texture/chek_distance_vertical.c texture/door.c texture/control_kebord_util1.c\
		texture/control_kebord_util2.c parsing/checker1.c  parsing/checkers.c   parsing/spliter.c parsing/utils.c parsing/utils1.c parsing/utils2.c parsing/utils3.c

OBJS			= $(SRCS:.c=.o)

CC			= cc
RM			= rm -f
CFLAGS		=  -Wall -Wextra -Werror  
MLX_LIB		=  mlx/build/libmlx42.a -Iinclude -lglfw -L"/Users/akheired/.brew/Cellar/glfw/3.4/lib"
NAME		= cub3D
LIBFT 		= libft/libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
			make -C libft 
			$(CC) ${CFLAGS} -o ${NAME} ${LIBFT} ${OBJS} ${MLX_LIB}

bonus : all

%.o:	%.c cub3d.h
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			make -C libft clean
			$(RM) $(OBJS)

fclean:		clean
			make -C libft fclean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re