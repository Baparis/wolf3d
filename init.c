/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:20:48 by baparis           #+#    #+#             */
/*   Updated: 2017/06/04 17:26:27 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		*texture_read(int width, int height, char *path)
{
	unsigned char	tmp[54];
	int				*tex;
	FILE			*img;
	int				x;
	int				y;
	int				tmp2[1];

	if (!(tex = (int*)malloc(sizeof(int) * 4097)))
		ft_error(2);
	img = fopen(path, "r");
	fread(tmp, sizeof(unsigned char), 54, img);
	fseek(img, tmp[10], SEEK_SET);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			fread(tmp2, 3, 1, img);
			tex[4095 - (y * width + x)] = tmp2[0];
		}
	}
	return (tex);
}

int		**texture_loader(int width, int height)
{
	int	**texture;
	
	if (!(texture = (int**)malloc(sizeof(int*) * 17)))
		ft_error(2);
	texture[0] = texture_read(width, height, "textures/asylimwall.bmp");
	texture[1] = texture_read(width, height, "textures/chamberwall.bmp");
	texture[2] = texture_read(width, height, "textures/ceiling.bmp");
	texture[3] = texture_read(width, height, "textures/asylumfloor.bmp");
	texture[4] = texture_read(width, height, "textures/autodoor.bmp");
	texture[5] = texture_read(width, height, "textures/roomwall.bmp");
	texture[6] = texture_read(width, height, "textures/vent.bmp");
	texture[7] = texture_read(width, height, "textures/vententry.bmp");
	texture[8] = texture_read(width, height, "textures/rightexit.bmp");
	texture[9] = texture_read(width, height, "textures/leftexit.bmp");
	texture[10] = texture_read(width, height, "textures/leftwindow.bmp");
	texture[11] = texture_read(width, height, "textures/midwindow.bmp");
	texture[12] = texture_read(width, height, "textures/rightwindow.bmp");
	texture[13] = texture_read(width, height, "textures/kury.bmp");
	texture[14] = texture_read(width, height, "textures/asyroomdoorext.bmp");
	texture[15] = texture_read(width, height, "textures/vbaudin.bmp");
	texture[16] = texture_read(width, height, "textures/vpd.bmp");
	return (texture);
}

t_para	*ft_mlx_init(char *name)
{
	t_para	*para;

	if (!(para = (t_para*)malloc(sizeof(t_para))))
		ft_error(2);
	if (!(para->p = (t_play*)malloc(sizeof(t_play))))
		ft_error(2);
	para->title = name;
	para->map = map_loader(para->title, para);
	para->mlx_ptr = mlx_init();
	*name = ft_toupper(*name);
	printf("You don't know\n");
	para->win_ptr = mlx_new_window(para->mlx_ptr, 1280, 800,\
			ft_strjoin("wolf3d : ", name));
	printf("what you are doing here\n");
	para->texture = texture_loader(64, 64);
	para->p->view = 0;
	para->p->posx = 2;
	para->p->posy = 2;
	para->door = 0;
	para->vent = 0;
	para->p->planex = 0;
	para->p->dirx = -1;
	para->p->diry = 0;
	para->p->planey = 0.66;
	return (para);
}

t_ima	*ft_new_frame(t_para *par)
{
	t_ima	*ima;
	int		i;

	i = -1;
	if (!(ima = (t_ima*)malloc(sizeof(t_ima) * 4)))
		ft_error(2);
	while (++i < 4)
	{
		(ima)[i].img_ptr = mlx_new_image(par->mlx_ptr, 640, 400);
		(ima)[i].ima = mlx_get_data_addr((ima)[i].img_ptr,\
				&(ima)[i].bpp, &ima[i].sl, &ima[i].en);
	}
	return (ima);
}

t_dda	*dda_init(t_para *p, double raydirx, double raydiry)
{
	t_dda	*d;

	if (!(d = (t_dda*)malloc(sizeof(t_dda))))
		ft_error(2);
	d->deltadistx = sqrt(1 + (raydiry * raydiry) / (raydirx * raydirx));
	d->deltadisty = sqrt(1 + (raydirx * raydirx) / (raydiry * raydiry));
	d->mapx = (int)(p->p->posx);
	d->mapy = (int)(p->p->posy);
	d->hit = 0;
	return (d);
}
