/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:01:02 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/18 09:06:48 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *safe_malloc(size_t num)
{
    void *ret;

    ret = malloc(num);
    if(ret == NULL)
        error_input("malloc faild to allocate");
    return(ret);
}

