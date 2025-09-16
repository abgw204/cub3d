/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:42:47 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/01 15:42:50 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*void	toUPPER(unsigned int i, char *s)
{
	unsigned int a;
	a = i;
	a = a + 1;
	*s = toupper(*s);
}
int	main()
{
	char s[] = "ooooopp";
	ft_striteri(s, toUPPER);
	printf("%s", s);
	return 0;
}*/
