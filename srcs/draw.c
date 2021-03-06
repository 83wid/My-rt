/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <nabouzah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:53:08 by aeddaqqa          #+#    #+#             */
/*   Updated: 2021/04/26 13:04:37 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			copy_obj_help(t_object *n_obj, t_object *obj)
{
	n_obj->radius1 = obj->radius1;
	n_obj->radius2 = obj->radius2;
	n_obj->distance = obj->distance;
	n_obj->angle = obj->angle;
	n_obj->is_ref = obj->is_ref;
	n_obj->is_transp = obj->is_transp;
	n_obj->refraction_index = obj->refraction_index;
	n_obj->inter = obj->inter;
	n_obj->id = obj->id;
	n_obj->slice = obj->slice;
	n_obj->slice_check = obj->slice_check;
	n_obj->texture = obj->texture;
	n_obj->slice_flag = obj->slice_flag;
}

void			copy_obj(t_object *n_obj, t_object *obj)
{
	n_obj->type = obj->type;
	n_obj->position = obj->position;
	n_obj->translation = obj->translation;
	n_obj->rotation = obj->rotation;
	n_obj->color = obj->color;
	n_obj->point_a = obj->point_a;
	n_obj->point_b = obj->point_b;
	n_obj->point_c = obj->point_c;
	n_obj->point_d = obj->point_d;
	n_obj->corner[0] = obj->corner[0];
	n_obj->corner[1] = obj->corner[1];
	n_obj->orientation = obj->orientation;
	n_obj->normal = obj->normal;
	n_obj->height = obj->height;
	n_obj->radius = obj->radius;
	copy_obj_help(n_obj, obj);
}

unsigned int	pixel_color(t_rt *rt, t_ray *ray)
{
	double			x_t[2];
	t_object		close_tmp[2];
	t_object		*tmp;
	t_color			color;
	t_color			color1;

	tmp = rt->objects;
	x_t[1] = -1.0;
	color = (t_color){0, 0, 0};
	while (tmp)
	{
		copy_obj(&close_tmp[1], tmp);
		x_t[0] = rt->intersection[close_tmp[1].type](&close_tmp[1], ray);
		x_t[0] = slice_obj(&close_tmp[1], *ray, x_t[0]);
		if (x_t[0] != -1 && (x_t[0] < x_t[1] || x_t[1] == -1.0))
		{
			copy_obj(&close_tmp[0], &close_tmp[1]);
			x_t[1] = x_t[0]  + EPSILLON;
		}
		tmp = tmp->next;
	}
	if (x_t[1] != -1)
		to_rgb(&color, light(&close_tmp[0], ray, rt, x_t[1]));
	color1 = is_direct_light(rt, *ray, x_t[1]);
	return (rgb(add_color(color1, color)));
}

void			apply_antiliasing(t_rt *rt, int x, int y)
{
	int		z;
	t_col	col;
	t_ray	*ray;
	t_rr	r;

	z = 0;
	col = (t_col){0, 0, 0};
	r.r1 = 0.0000;
	r.r2 = 0.0000;
	while (z < 5)
	{
		r.r1 = ((double)(rand() % 10)) / 10.0;
		r.r2 = ((double)(rand() % 10)) / 10.0;
		ray = ray_init(rt, x, y, r);
		col = plus_color(col, int_to_rgb_yatak(pixel_color(rt, ray)));
		free(ray);
		z++;
	}
	col = divide_color(col, (double)(5.0));
	col.r = col.r > 255 ? 255 : col.r;
	col.g = col.g > 255 ? 255 : col.g;
	col.b = col.b > 255 ? 255 : col.b;
	rt->sdl->data[y * W + x] = rgb_to_int_yatak(col);
}

void			draw_scene(t_rt *rt, int x, int y)
{
	t_rr	r;
	t_ray	*ray;
	t_col	col1;
	t_col	col2;
	t_col	col;

	r.r1 = .5;
	r.r2 = .5;
	ray = ray_init(rt, x, y, r);
	if (rt->save_filter == 5)
	{
		col1 = int_to_rgb_yatak(pixel_color(rt, ray));
		ray->origin.x += 2.0;
		col2 = int_to_rgb_yatak(pixel_color(rt, ray));
		col1.g += 50;
		col1.r = 0;
		col2.r += 50;
		col2.g = 0;
		col = plus_color(col1, col2);
		col = divide_color(col, 2);
		rt->sdl->data[y * W + x] = rgb_to_int_yatak(col);
	}
	else
		rt->sdl->data[y * W + x] = pixel_color(rt, ray);
	free(ray);
}
