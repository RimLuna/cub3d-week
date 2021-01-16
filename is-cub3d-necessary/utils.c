#include "cub3d.h"

int			ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int			atonum(char *s)
{
	int		n;

	n = 0;
	while (*s <= ' ')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + *s - '0';
		s++;
	}
	return (n);
}

char		*ft_trim(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] <= ' ')
		i--;
	str[i + 1] = '\0';
	return (str);
}


char		*rmempty(char *pline)
{
	int		i;
	int		nb_spaces;
	char	*new_pline;

	nb_spaces = 0;
	i = 0;
	while (pline[i])
	{
		if (pline[i] <= ' ')
			nb_spaces++;
		i++;
	}
	if (!(new_pline = malloc((ft_strlen(pline) - nb_spaces + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (*pline)
	{
		if (*pline > ' ')
			new_pline[i++] = *pline;
		pline++;
	}
	new_pline[i] = '\0';
	return (new_pline);
}

int				whereis(char c, char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
