/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roman_numeral_converter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 14:53:52 by elindber          #+#    #+#             */
/*   Updated: 2020/08/29 16:49:54 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define QUAD_CHAR 2
#define SMALL 3
#define INVALID_ORDER 4
#define TOO_BIG 5
#define VV_LL_DD 6
#define V_L_D_BEFORE_BIGGER 7

int		is_roman_numeral(char c)
{
	return (c == 'I' || c == 'V' || c == 'X' || c == 'C'
	|| c == 'D' || c == 'L' || c == 'M');
}

int		convert_sign(char c)
{
	if (c == 'I')
		return (1);
	else if (c == 'V')
		return (5);
	else if (c == 'X')
		return (10);
	else if (c == 'L')
		return (50);
	else if (c == 'C')
		return (100);
	else if (c == 'D')
		return (500);
	else if (c == 'M')
		return (1000);
	return (0);
}

int		print_error_message(int message)
{
	if (message == QUAD_CHAR)
		printf("Error: Number cannot have four same characters in a row.\n");
	else if (message == SMALL)
		printf("Error: Only one smaller character is allowed before bigger one.\n");
	else if (message == INVALID_ORDER)
		printf("Error: Invalid order of characters.\n");
	else if (message == TOO_BIG)
		printf("Error: Character following another cannot be more than 10 times bigger.\n");
	else if (message == VV_LL_DD)
		printf("Error: VV, LL and MM must be represented by X, C and M.\n");
	else if (message == V_L_D_BEFORE_BIGGER)
		printf("Error: V, L and D cannot be before bigger character.\n");
	return (FALSE);
}

int		check_number_correctness(int *nbrs, int size)
{
	int		i;

	i = 0;
	while (i < size - 1)
	{
		if (i < size - 3 && 
		nbrs[i] == nbrs[i + 1] && nbrs[i] == nbrs[i + 2] && nbrs[i] == nbrs[i + 3])
			return (print_error_message(QUAD_CHAR));
		if (i < size - 2 && nbrs[i] <= nbrs[i + 1] && nbrs[i] < nbrs[i + 2])
			return (print_error_message(SMALL));
		if (i < size - 2 && nbrs[i] < nbrs[i + 1] && nbrs[i] == nbrs[i + 2])
			return (print_error_message(INVALID_ORDER));
		if (i < size - 2 && nbrs[i] > nbrs[i + 1] && nbrs[i] < nbrs[i + 2])
			return (print_error_message(INVALID_ORDER));
		if ( nbrs[i] < nbrs[i + 1] / 10)
			return (print_error_message(TOO_BIG));
		if ((nbrs[i] == 5 && nbrs[i + 1] == 5)
		|| (nbrs[i] == 50 && nbrs[i + 1] == 50) || (nbrs[i] == 500 && nbrs[i + 1] == 500))
			return (print_error_message(VV_LL_DD));
		if ((nbrs[i] == 5 && nbrs[i + 1] > 5) || (nbrs[i] == 50 && nbrs[i + 1] > 50)
		|| (nbrs[i] == 500 && nbrs[i + 1] > 500))
			return (print_error_message(V_L_D_BEFORE_BIGGER));
		i++;
	}
	return (TRUE);
}

int		calculate_result(int *nbrs, int size)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (i < size)
	{
		if (i < size - 1 && nbrs[i] < nbrs[i + 1])
		{
			result += nbrs[i + 1] - nbrs[i];
			i++;
		}
		else
			result += nbrs[i];
		i++;
	}
	return (result);
}

int		convert_number(char *str)
{
	int		i;
	int		tab;
	int		digits;
	int		*nbrs;
	int		result;

	i = 0;
	tab = -1;
	digits = 0;
	while (str[i])
	{
		if (is_roman_numeral(str[i]))
			digits++;
		else if (!(is_roman_numeral(str[i])) && str[i] != '-')
			return (printf("Invalid input: allowed characters are 'I V X L C D M -'.\n"));
		i++;
	}
	if (!(nbrs = (int*)malloc(sizeof(int) * digits)))
		return (printf("Malloc error.\n"));
	i = str[0] == '-' ? 0 : -1;
	while (str[++i])
		nbrs[++tab] = convert_sign(str[i]);
	if (check_number_correctness(nbrs, digits) == FALSE)
		return (0);
	result = calculate_result(nbrs, digits);
	if (str[0] == '-')
		result *= -1;
	free(nbrs);
	return (printf("%d\n", result));
}

int		main(int ac, char **av)
{
	int		i;

	i = 0;
	if (ac < 2)
	{
		printf("You must give at least one argument.\n");
		return (0);
	}
	while (++i < ac)
		convert_number(av[i]);
	return (0);
}
