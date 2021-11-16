#include "minishell.h"

static void	quotes_count(t_flags *flags, char *str, size_t *c_count, size_t *i)
{
	if (flags->q_double == 1 && str[*i] == Q_DOUBLE)
	{
		flags->q_double = 0;
		(*c_count)++;
		(*i)++;
	}
	else if (flags->q_single == 1 && str[*i] == Q_SINGLE)
	{
		flags->q_single = 0;
		(*c_count)++;
		(*i)++;
	}
	if (flags->q_single == 0 && (*i > 0 &&  str[*i - 1] != '\\') && str[*i] == Q_DOUBLE)
	{
		flags->q_double = 1;
		(*c_count)++;
		(*i)++;
	}
	else if (flags->q_double == 0 && (*i > 0 && str[*i - 1] != '\\') && str[*i] == Q_SINGLE)
	{
		flags->q_single = 1;
		(*c_count)++;
		(*i)++;
	}
}

char	*omit_quotes(char *str)
{
	t_flags	flags;
	char	*dst;
	size_t	i;
	size_t	j;
	size_t	c_count;

	i = 0;
	c_count = 0;
	init_flags(&flags);
	fprintf(stderr, "init count=%zu, (single, double)=(%d, %d)\n", c_count, flags.q_single, flags.q_double);
	while (i < ft_strlen(str))// && str[i] != '\0')
	//while (i <= next_quote_index)
	{
		//quotes_count(&flags, str, &c_count, &i);
		if (flags.q_single == 0 && (i == 0 && str[i] == Q_DOUBLE))
		{
			flags.q_double = 1;
			fprintf(stderr, "1. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			c_count++;
			i++;
		}
		else if (flags.q_double == 0 && (i == 0 && str[i] == Q_SINGLE))
		{
			flags.q_single = 1;
			fprintf(stderr, "2. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			c_count++;
			i++;
		}
		else if (flags.q_single == 0 && flags.q_double == 0 && (i > 0 &&  str[i - 1] != '\\') && str[i] == Q_DOUBLE)
		//if (flags.q_single == 0 && str[i] == Q_DOUBLE)
		{
			flags.q_double = 1;
			fprintf(stderr, "3. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			c_count++;
			i++;
		}
		else if (flags.q_double == 0 && flags.q_single == 0 && (i > 0 && str[i - 1] != '\\') && str[i] == Q_SINGLE)
		//else if (flags.q_double == 0 && str[i] == Q_SINGLE)
		{
			flags.q_single = 1;
			fprintf(stderr, "4. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			c_count++;
			//fprintf(stderr, "count=%zu\n", c_count);
			i++;
		}
		if (flags.q_double == 1 && str[i] == Q_DOUBLE)
		{
			flags.q_double = 0;
			fprintf(stderr, "5. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			c_count++;
			i++;
		}
		else if (flags.q_single == 1 && str[i] == Q_SINGLE)
		{
			flags.q_single = 0;
			fprintf(stderr, "6. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			c_count++;
			i++;
		}
		else
			i++;
/*
		if ((flags.q_single == 1 && str[i] == Q_SINGLE)
			|| (flags.q_double == 1 && str[i] == Q_DOUBLE))
			c_count++;
*/
	}
	fprintf(stderr, "omit count=%zu\n", c_count);
	//if (ft_strlen(str) == 2)
	if (ft_strlen(str) - c_count == 0)
	{
		return (ft_strdup("\'\'"));
		//dst[i] = str[1];
		//return (dst);
	}
	dst = (char *)malloc(sizeof(char) * (ft_strlen(str) - c_count + 1));
	i = 0;
	fprintf(stderr, "omit ch str=%s, count=%zu\n", str, c_count);
	i = 0;
	j = 0;
	while(str[i] != '\0')
	{

		if (flags.q_single == 0 && (i == 0 && str[i] == Q_DOUBLE))
		{
			fprintf(stderr, "1. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			flags.q_double = 1;
			i++;
		}
		else if (flags.q_double == 0 && (i == 0 && str[i] == Q_SINGLE))
		{
			fprintf(stderr, "2. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			flags.q_single = 1;
			i++;
		}
		else if (flags.q_single == 0 && flags.q_double == 0 && (i > 0 &&  str[i - 1] != '\\') && str[i] == Q_DOUBLE)
		{
			fprintf(stderr, "3. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			flags.q_double = 1;
			i++;
		}
		else if (flags.q_double == 0 && flags.q_single == 0 && (i > 0 && str[i - 1] != '\\') && str[i] == Q_SINGLE)
		{
			fprintf(stderr, "4. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			flags.q_single = 1;
			i++;
		}
		if (flags.q_double == 1 && str[i] == Q_DOUBLE)
		{
			fprintf(stderr, "5. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			flags.q_double = 0;
			i++;
		}
		else if (flags.q_single == 1 && str[i] == Q_SINGLE)
		{
			fprintf(stderr, "6. str[%zu] = %c, single, double = (%d, %d)\n", i, str[i], flags.q_single, flags.q_double);
			flags.q_single = 0;
			i++;
		}
		else
			dst[j++] = str[i++];
/*
		if ((flags.q_single == 1 && str[i] != Q_SINGLE))
		//	|| !(flags.q_double == 1 && str[i] == Q_DOUBLE))
			dst[j++] = str[i++];
		else if ((flags.q_double == 1 && str[i] != Q_DOUBLE))
			dst[j++] = str[i++];
		else
			i++;
*/
	}
	dst[j] = '\0';
	return (dst);
}

char	*omit_character(char *str, int c)
{
	char	*dst;
	size_t	i;
	size_t	j;
	size_t	c_count;
	//size_t	next_quote_index;

	i = 0;
	c_count = 0;
	while (str[i] != '\0')
	//while (i <= next_quote_index)
	{
		if (str[i] == c)
			c_count++;
		i++;
	}
	dst = (char *)malloc(sizeof(char) * (ft_strlen(str) - c_count + 1));
	i = 0;
	if (ft_strlen(str) - c_count == 0)
	{
		dst[i] = str[1];
		return (dst);
	}
	fprintf(stderr, "omit ch str=%s, count=%zu\n", str, c_count);
	i = 0;
	j = 0;
	while(str[i] != '\0')
	{
		//if (i <= next_quote_index && str[i] == c)
		if (str[i] == c)
			i++;
			//str++;
		else
			dst[j++] = str[i++];
	}
	dst[j] = '\0';
	return (dst);
}
