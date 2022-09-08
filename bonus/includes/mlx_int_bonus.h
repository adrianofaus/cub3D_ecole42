/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:08 by afaustin          #+#    #+#             */
/*   Updated: 2022/09/07 20:41:59 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INT_BONUS_H

# define MLX_INT_BONUS_H

# include <sys/mman.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# include <X11/XKBlib.h>

# define MLX_TYPE_SHM_PIXMAP 3
# define MLX_TYPE_SHM 2
# define MLX_TYPE_XIMAGE 1
# define MLX_MAX_EVENT 36
# define ENV_DISPLAY "DISPLAY"
# define LOCALHOST "localhost"
# define ERR_NO_TRUECOLOR "\
MinilibX Error : No TrueColor Visual available.\n"
# define WARN_SHM_ATTACH "\
MinilibX Warning : X server can't attach shared memory.\n"

typedef struct s_xpm_col
{
	int		name;
	int		col;
}				t_xpm_col;

struct s_col_name
{
	char	*name;
	int		color;
};

typedef struct s_event_list
{
	int		mask;
	int		(*hook)();
	void	*param;
}				t_event_list;

typedef struct s_win_list
{
	Window				window;
	GC					gc;
	struct s_win_list	*next;
	int					(*mouse_hook)();
	int					(*key_hook)();
	int					(*expose_hook)();
	void				*mouse_param;
	void				*key_param;
	void				*expose_param;
	t_event_list		hooks[MLX_MAX_EVENT];
}				t_win_list;

typedef struct s_img
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}				t_img;

typedef struct s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
	int			(*loop_hook)();
	void		*loop_param;
	int			use_xshm;
	int			pshm_format;
	int			do_flush;
	int			decrgb[6];
	Atom		wm_delete_window;
	Atom		wm_protocols;
	int			end_loop;
}	t_xvar;

#endif
