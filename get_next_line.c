#include "get_next_line.h"

char	*ft_copy(char *str)
{
	int		i;
	char	*rtn;

	i = -1;
	rtn = ft_calloc ((ft_strlen(str) + 1), sizeof(char));
	while (str[++i])
		rtn[i] = str[i];
	rtn[i] = 0;
	str = ft_del_content(str);
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
	int	str_len;

	read_size = 1;
	while (!(ft_did_have_a_nl(str)))
	{
		str = ft_cpy_and_increase(str);
		str_len = ft_strlen(str);
		read_size = read (fd, &str[str_len], BUFFER_SIZE);
		str[str_len + BUFFER_SIZE] = 0;
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
	static char	*keep;
	char		*str;
	int			x;

	str = NULL;
	if (fd < 0)
		return (NULL);
	if (keep)
		str = ft_copy(keep);
	else
	{
		str = ft_calloc ((BUFFER_SIZE + 1), sizeof(char));
		x = read (fd, (void *)str, BUFFER_SIZE);
		if (x == -1 || !x)
		{
			str = ft_del_content(str);
			return (NULL);
		}
		str[ft_strlen(str)] = 0;
	}
	str = ft_check_new_line(str, fd);
	keep = ft_alloc_for_keep(str);
	str = ft_split_rtn(str, keep);
	return (str);
}
