#include "get_next_line_bonus.h"

char	*ft_copy(char *str)
{
	int		i;
	char	*rtn;

	i =0;
	rtn = ft_calloc ((ft_strlen(str) + 1), sizeof(char));
	while (str[i])
	{
		rtn[i] = str[i];
		i++;
	}
	ft_del_content(str);
	return (rtn);
}

int	ft_did_have_a_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	*ft_check_new_line(char *str, int fd)
{
	int	read_size;

	read_size = 1;
	while (!(ft_did_have_a_nl(str)))
	{
		str = ft_cpy_and_increase(str);
		read_size = read (fd, &str[ft_strlen(str)], BUFFER_SIZE);
		if (!read_size)
			return (str);
	}
	return (str);
}

char	*ft_alloc_for_keep(char *str)
{
	char	*rtn;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || (str[i] == '\n' && !str[i + 1]))
		return (NULL);
	rtn = ft_calloc ((ft_strlen(str) - i), sizeof(char));
	return (rtn);
}

char	*get_next_line(int fd)
{
	static char	*keep[OPEN_MAX];
	char		*str;
	int			x;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (keep[fd])
		str = ft_copy(keep[fd]);
	else
	{
		str = ft_calloc ((BUFFER_SIZE + 1), sizeof(char));
		x = read (fd, (void *)str, BUFFER_SIZE);
		if (x == -1 || !x)
		{
			ft_del_content(str);
			return (NULL);
		}
	}
	str = ft_check_new_line(str, fd);
	keep[fd] = ft_alloc_for_keep(str);
	str = ft_split_rtn(str, keep[fd]);
	return (str);
}
