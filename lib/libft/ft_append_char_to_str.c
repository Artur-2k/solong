#include "libft.h"
// Appends a char to a string keeping it null terminated.
// Returns a new allocated string and frees the old one.
char	*ft_append_char_to_str(char *str, char c)
{
	char	*nstr;
	size_t			len;

	len = 0;
	if (str)
		len = ft_strlen((const char *)str);
	nstr = (char *)malloc(sizeof(char) * len + 2);
	if (!nstr)
		return (free(str), NULL);
	len = 0;
	while (str && str[len])
	{
		nstr[len] = str[len];
		len++;
	}
	nstr[len] = c;
	nstr[++len] = '\0';
	free(str);
	return (nstr);
}
