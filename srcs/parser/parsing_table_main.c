/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:19:56 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/21 20:19:57 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "grammer.h"

char	*get_line(int i)
{
	char	*line;

	line = NULL;
	if (i >= 0 && i <= 10)
		line = get_line_0_to_10(i);
	else if (i >= 11 && i <= 21)
		line = get_line_11_to_21(i);
	else if (i >= 22 && i <= 32)
		line = get_line_22_to_32(i);
	else if (i >= 33 && i <= 43)
		line = get_line_33_to_43(i);
	else if (i >= 44 && i <= 54)
		line = get_line_44_to_54(i);
	else if (i >= 55 && i <= 65)
		line = get_line_55_to_65(i);
	else if (i >= 66 && i <= 76)
		line = get_line_66_to_76(i);
	else if (i >= 77 && i <= 87)
		line = get_line_77_to_87(i);
	else if (i >= 88 && i <= 98)
		line = get_line_88_to_98(i);
	else
		line = get_line_99(i);
	return (line);
}
