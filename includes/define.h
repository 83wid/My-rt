/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:46:46 by aeddaqqa          #+#    #+#             */
/*   Updated: 2021/03/29 10:04:54 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
**				Error-gen
*/

# define W 800
# define H 800
# define WID 1000
# define HEI 850
# define DIFFUSE 1.0
# define SPECULER 1.0
# define MAX_REF 3
# define EQN_EPS 1e-9
# define EPSILLON 1e-6

typedef enum	e_error
{
	FLAG_SAVE,
	OPEN_FILE,
	EMPTY_FILE,
	MALLOC_ERROR,
	SCENE_NOT_FOUND,
	SYNTAX_ERROR
}				t_error;

typedef enum	e_matter
{
	GLASS = 1,
	WATER,
	DIAMOND,
	MIRROR
}				t_matter;

typedef enum	e_type_tex
{
	NONE,
	BOARD,
	TEX,
	SPECTRUM
}				t_type_tex;

typedef enum	e_light_type
{
	DIRECT = 1,
	PARALLEL
}				t_light_type;

typedef	enum	e_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	CAMERA,
	LIGHT,
	ELLIPSOID,
	PARABOLOID,
	TRIANGLE,
	TORUS,
	DISK,
	AMBIENT
}				t_type;

# define COLOR_1 0x192a56
# define COLOR_2 0xfbc531
# define COLOR_3 0xf5f6fa
# define COLOR_4 0x2f3640

#endif
