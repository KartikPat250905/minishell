/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:40:50 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 14:08:24 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int	main(void)
{
	int ret;

	ret = parsing_main();
	printf("return is: %i", ret);
	return (0);
}
