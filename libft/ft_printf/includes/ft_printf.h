/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 11:16:21 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/15 22:47:29 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

/*
** ---------- COLORS ----------
*/

# define RES    "\033[0m"

# define BOLD   "\033[1m"
# define UNDR   "\033[4m"

# define WHT    "\x1B[97m"
# define RED    "\x1B[31m"
# define GRN    "\x1B[32m"
# define YEL    "\x1B[33m"
# define BLU    "\x1B[34m"
# define MAG    "\x1B[35m"
# define CYN    "\x1B[36m"
# define GRY    "\x1B[37m"

# define BG_WHT "\x1B[107m"
# define BG_RED "\x1B[41m"
# define BG_GRN "\x1B[42m"
# define BG_YEL "\x1B[43m"
# define BG_BLU "\x1B[44m"
# define BG_MAG "\x1B[45m"
# define BG_CYN "\x1B[46m"
# define BG_GRY "\x1B[47m"

/*
** ---------- FLAGS ----------
*/

# define F_LMHH (1u << 15u)
# define F_LMH  (1u << 14u)
# define F_LML  (1u << 13u)
# define F_LMLL (1u << 12u)
# define F_LMUL (1u << 11u)
# define F_LMJ  (1u << 10u)
# define F_LMZ  (1u << 9u)

# define F_ALTF (1u << 8u)
# define F_ZPAD (1u << 7u)
# define F_LPAD (1u << 6u)
# define F_SPC  (1u << 5u)
# define F_SIGN (1u << 4u)

# define F_PAD  (1u << 3u)
# define F_PREC (1u << 2u)

# define F_PNTR (1u << 1u)

/*
** ---------- MACROS ----------
*/

# define ABS(a)    ((a) > 0 ? (a) : -(a))
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define MIN(a, b) ((a) < (b) ? (a) : (b))

# define BUFF_SIZE    64
# define NULL_STR     "(null)"
# define L_NULL_STR   L"(null)"

# define OFFSET_SIZE 1024
# define F_BUFF_SIZE 2048

/*
** ---------- STRUCTURES ----------
*/

typedef struct	s_printf
{
	int				fd;
	char			*format;
	va_list			ap;
	char			buff[BUFF_SIZE];
	int				buff_i;
	int				out_len;
	unsigned short	f;
	int				width;
	int				prec;
	char			cnv;
	int				padding;
}				t_printf;

typedef	struct	s_float_parts
{
	char			whol[F_BUFF_SIZE];
	int				whol_size;
	long			whol_b;
	char			frac[F_BUFF_SIZE];
	int				frac_size;
	long			frac_b;
	int				sign;
	char			*s;
}				t_float_parts;

typedef struct	s_float_bits
{
	unsigned long	mant : 64;
	unsigned		expn : 15;
	unsigned		sign : 1;
}				t_float_bits;

typedef	union	u_float
{
	long double		f;
	t_float_bits	bits;
}				t_float;

/*
** ---------- MAIN FUNCTIONS ----------
*/

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_vprintf(const char *format, va_list ap);
int				ft_vdprintf(int fd, const char *format, va_list ap);

/*
** ---------- OTHER FUNCTIONS ----------
*/

/*
** output.c
*/
void			buffer(t_printf *p, char *src, int size);
void			padding(t_printf *p, int func_param);

/*
** parsing.c
*/
void			parse_format(t_printf *p);

/*
** int.c
*/
void			int_print(t_printf *p);

/*
** int_caster.c
*/
char			*int_cast(t_printf *p, intmax_t *n);
char			*int_base_cast(t_printf *p, uintmax_t *n);

/*
** float.c
*/
void			float_print(t_printf *p);

/*
** float_handler.c
*/
void			float_whol(t_float_parts *fp, int expn);
void			float_frac(t_float_parts *fp, unsigned expn, int sign);

/*
** float_utils.c
*/
char			*float_edge(t_printf *p, t_float_parts *fp);
void			float_add(char *dest, char *src);
void			float_pow(char *s, int n, int power, int *size);
void			float_mult(char *s, int mult, int *size);

/*
** float_prec.c
*/
void			float_prec(t_printf *p, t_float_parts *fp);

/*
** float_writer.c
*/
void			float_write(t_printf *p, t_float_parts *fp);

/*
** char.c
*/
void			str_print(t_printf *p);

/*
** colors.c
*/
int				color_check(t_printf *p);
void			color_print(t_printf *p);

/*
** miscellaneous.c
*/
void			wildcards(t_printf *p, int func_param);
void			pointer_print(t_printf *p);
void			out_len_write(t_printf *p);
void			percent_print(t_printf *p);
void			non_valid_print(t_printf *p);

#endif
