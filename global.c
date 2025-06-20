/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:46:20 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/18 09:52:26 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_const n = {
    .ERROR = 1,
    .SUCCESS = 0,
    .BUFF_SIZE = 4096,
    .EMPTY = 0,
    .PIPE = 6,
    .END = 7,
    .STDIN = 0,
    .STDOUT = 1,
    .STDERR = 2,
    .SKIP = 1,
    .NOSKIP = 0,
    .UNKNOWN_COMMAND = 127,
    .IS_DIRECTORY = 126

};
