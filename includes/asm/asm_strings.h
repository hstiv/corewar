/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_strings.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 05:13:21 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 14:53:26 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRINGS_H
# define ASM_STRINGS_H

/*
** prefix for strings defines: S_*
*/

# define S_NULL_STRING		""
# define S_USAGE			"Usage: ./asm <source_file.s>\n"
# define S_WRITE			"Writing output program to %s\n"

# define S_ERR_OPEN			"Can't open source file %s\n"
# define S_ERR_EXT			"File %s extension is invalid\n"
# define S_ERR_READ			"Can't read source file %s\n"
# define S_ERR_EMPTY		"File empty\n"
# define S_ERR_WRITE		"Can't create/write in output file %s\n"
# define S_ERR_CLOSE		"Can't close output file %s\n"

# define S_ERR_ALLOC		"Memory allocation error\n"

# define S_ERR_LONG_NAME	"Champion name too long (max length %d)\n"
# define S_ERR_LONG_COM		"Champion comment too long (max length %d)\n"
# define S_ERR_SYNTAX		"Syntax error at line %d\n"
# define S_ERR_LEXICAL		"Lexical error at line %d\n"
# define S_ERR_INV_ARG		"Invalid args for operation \"%s\" at line %d\n"
# define S_ERR_INV_OP		"Invalid operation at line %d\n"
# define S_ERR_LABEL_EXIST	"Label \"%s\" at line %d already exist\n"
# define S_ERR_LABEL_ARG	"Label \"%s\" in args at line %d doesn't exist\n"

#endif
