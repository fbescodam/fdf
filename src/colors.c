/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/06 17:37:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 18:46:48 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Parse argb color to one hex color
 * @param a		Alpha channel
 * @param r		Red channel
 * @param g		Green channel
 * @param b		Blue channel
 * @return		The hex containing all color values
 */
static unsigned int	argb_to_hex(t_col_rgba *col)
{
	return (col->a << 24 | col->r << 16 | col->g << 8 | col->b);
}

/**
 * Parse hex color to rgba color
 * @param color	A color in hex value
 * @return		A struct containing all individual color channels
 */
static void	hex_to_argb(unsigned int color, t_col_rgba *rgba)
{
	rgba->a = 0xFF & (color >> 24);
	rgba->r = 0xFF & (color >> 16);
	rgba->g = 0xFF & (color >> 8);
	rgba->b = 0xFF & (color);
}

/**
 * Get a color from a gradient based on a position in percentages
 * @param color_s	Starting color
 * @param color_e	Ending color
 * @param perc		Position in percentages (between 0 and 1)
 * @return			The color at the given position in a gradient
 */
unsigned int	get_gradient_color(unsigned int color_s, unsigned int color_e
					, double perc)
{
	t_col_rgba	res;
	t_col_rgba	start;
	t_col_rgba	end;

	hex_to_argb(color_s, &start);
	hex_to_argb(color_e, &end);
	res.a = 0;
	res.r = start.r + perc * (end.r - start.r);
	res.g = start.g + perc * (end.g - start.g);
	res.b = start.b + perc * (end.b - start.b);
	return (argb_to_hex(&res));
}

/**
 * Parse a color from a hex color string
 * @param s		The string to parse
 * @return		An unsigned int representation of the color
 */
unsigned int	parse_hex(const char *s)
{
	int				i;
	unsigned int	color;

	if (!s || !s[0] || !s[1])
		return (0);
	if (s[1] == 'x')
		i = 2;
	else
		i = 0;
	color = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			color = color * 16 + ((int)s[i] - '0');
		else if (s[i] >= 'A' && s[i] <= 'F')
			color = color * 16 + 10 + ((int)s[i] - 'A');
		else if (s[i] >= 'a' && s[i] <= 'f')
			color = color * 16 + 10 + ((int)s[i] - 'a');
		else
			break ;
		i++;
	}
	return (color);
}
