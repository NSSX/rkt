/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:48:06 by avella            #+#    #+#             */
/*   Updated: 2016/05/27 17:52:42 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	err(void)
{
	ft_putstr("BAD PARSING POTO\n");
	exit(1);
}

t_obj		*create(void)
{
	t_obj *obj;

	obj = malloc(sizeof(t_obj));
	obj->type = 0;
	obj->size = 1;
	obj->pos = (t_vec3d){0, 0, 0};
	obj->color = (t_vec3d){0, 0, 0};
	obj->color.x = 0.4;
	obj->color.y =0.4;
	obj->color.z = 0.4;
	obj->intens = 0.5;
	obj->rot = (t_vec3d){0, 0, 0};
	obj->next = NULL;
	return (obj);
}

t_obj		*add_list(t_env *e)
{
	t_obj	*actual;
	t_obj	*new_obj;
	int		i;

	if (!e)
		return NULL;
	actual = e->obj;
	i = 0;
	if (!actual)
	{
		e->obj = create();
		return (e->obj);
	}
	while (actual->next)
	{
		actual = actual->next;
	}
	new_obj = create();
	actual->next = new_obj;
	return (new_obj);
}

char	*chaine(char *ch)
{
	int i;

	i = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] == '}')
		{
			ch = ft_strsub(ch, 0, i);
			return (ch);
		}
		i++;
	}
	return (NULL);
}

char	*chaine2(char *ch)
{
	int i;

	i = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] == ')')
		{
			ch = ft_strsub(ch, 0, i + 1);
			return (ch);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_carac(char const *s1, char s2)
{
	char	*chaine;
	int		index;
	int		index2;

	index2 = 0;
	index = 0;
	if (!s1 || !s2)
		return (NULL);
	chaine = ft_memalloc(sizeof(char) * (ft_strlen(s1) + 10));
	if (chaine == NULL)
		return (NULL);
	while (s1[index] != '\0')
	{
		chaine[index] = s1[index];
		index++;
	}
	chaine[index] = s2;
	index++;
	index2++;
	chaine[index] = '\0';
	return (chaine);
}

void norme_val1(char *chaine, t_pars *pars)
{
  if ((chaine[pars->i + 1] >= '0' && chaine[pars->i + 1] <= '9') || chaine[pars->i + 1] == '-')
    pars->i++;
  else
    err();
  while (chaine[pars->i] != ',' && chaine[pars->i] != '\0')
    {
      pars->val1 = ft_strjoin_carac(pars->val1, chaine[pars->i]);
      pars->i++;
    }
  if ((chaine[pars->i + 1] >= '0' && chaine[pars->i + 1] <= '9')|| chaine[pars->i + 1] == '-')
    pars->i++;
  else
    err();  
}

void norme_val2(char *chaine, t_pars *pars)
{
  while (chaine[pars->i] != ',' && chaine[pars->i] != '\0')
    {
      pars->val2 = ft_strjoin_carac(pars->val2, chaine[pars->i]);
      pars->i++;
    }
  if ((chaine[pars->i + 1] >= '0' && chaine[pars->i + 1] <= '9')|| chaine[pars->i + 1] == '-')
    pars->i++;
  else
    err();
}

void norme_val3(char *chaine, t_pars *pars)
{
  while (chaine[pars->i] != ',' && chaine[pars->i] != '\0' && chaine[pars->i] != ')')
    {
      pars->val3 = ft_strjoin_carac(pars->val3, chaine[pars->i]);
      pars->i++;
    }
}

t_vec3d	*vec3d(t_env *e, char *chaine)
{
  t_pars pars;
  t_vec3d *tab;

	tab = malloc(sizeof(t_vec3d) * 1);
	pars.val1 = ft_memalloc(ft_strlen(chaine));
	pars.val2 = ft_memalloc(ft_strlen(chaine));
	pars.val3 = ft_memalloc(ft_strlen(chaine));
	pars.i = 0;
	while (chaine[pars.i] != '\0')
	{
		if (chaine[pars.i] == '(')
		{
		  norme_val1(chaine, &pars);
		  norme_val2(chaine, &pars);
		  norme_val3(chaine, &pars);
		  tab->x = ft_atoi(pars.val1);
		  tab->y = ft_atoi(pars.val2);
		  tab->z = ft_atoi(pars.val3);
		  return (tab);
		}
		pars.i++;
	}
	return (NULL);
}

double		get_single_var(char *chaine)
{
	int i;
	double val;
	char *tmp;


	tmp = ft_memalloc(sizeof(char) * ft_strlen(chaine));
	i = 0;
	val = 0;
	while (chaine[i] != '\0')
	{
		if (chaine[i] == '(')
		{
			if (chaine[i + 1] >= '0' && chaine[i + 1] <= '9')
				i++;
			while (chaine[i] >= '0' && chaine[i] <= '9' && chaine[i] != '\0')
			{
				tmp = ft_strjoin_carac(tmp, chaine[i]);
				i++;
			}
			return (ft_atoi(tmp));
		}
		i++;
	}
	return (val);
}

void		traitement(char *file, t_env *e)
{
	char	*here;
	char	*here2;
	char	*temp;
	t_vec3d	*pos;
	int		end;
	t_obj	*obj;

	end = 0;
	if((here = ft_strstr(file,"sphere{\n")) && here != NULL)
	{
		obj = add_list(e);
		temp = chaine(here);
		here[0] = 'W';
		if(temp == NULL)
			return;
		if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->pos = *vec3d(e, here2);
		}
		if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->color = *vec3d(e, here2);
			obj->color.x = lim(obj->color.x / 256, 0, 1);
			obj->color.y = lim(obj->color.y / 256, 0, 1);
			obj->color.z = lim(obj->color.z / 256, 0, 1);
		}
		if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->size = get_single_var(here2);
			obj->size /= 100;
		}
		if((here2 = ft_strstr(temp,"rot(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->rot = *vec3d(e, here2);
		}
		obj->type = 1;
		end++;
	}
	if((here = ft_strstr(file,"cone{\n")) && here != NULL)
	{
		obj = add_list(e);
		temp = chaine(here);
		here[0] = 'W';
		if(temp == NULL)
			return;
		if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->pos = *vec3d(e, here2);
		}
		if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->color = *vec3d(e, here2);
			obj->color.x = lim(obj->color.x / 256.0, 0.0, 1.0);
			obj->color.y = lim(obj->color.y / 256.0, 0.0, 1.0);
			obj->color.z = lim(obj->color.z / 256.0, 0.0, 1.0);
		}
		if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->size = get_single_var(here2);
			obj->size /= 100;
		}
		if((here2 = ft_strstr(temp,"rot(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->rot = *vec3d(e, here2);
		}
		obj->type = 2;
		end++;
	}
	if((here = ft_strstr(file,"cylinder{\n")) && here != NULL)
	{
		obj = add_list(e);
		temp = chaine(here);
		here[0] = 'W';
		if(temp == NULL)
			return;
		if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->pos = *vec3d(e, here2);
		}
		if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->color = *vec3d(e, here2);
			obj->color.x = lim(obj->color.x / 256.0, 0.0, 1.0);
			obj->color.y = lim(obj->color.y / 256.0, 0.0, 1.0);
			obj->color.z = lim(obj->color.z / 256.0, 0.0, 1.0);
		}
		if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->size = get_single_var(here2);
			obj->size /= 100;
		}
		if((here2 = ft_strstr(temp,"rot(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->rot = *vec3d(e, here2);
		}
		obj->type = 3;
		end++;
	}
	if((here = ft_strstr(file,"plane{\n")) && here != NULL)
	{
		obj = add_list(e);
		temp = chaine(here);
		here[0] = 'W';
		if(temp == NULL)
			return;
		if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->pos = *vec3d(e, here2);
		}
		if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->color = *vec3d(e, here2);
			obj->color.x = lim(obj->color.x / 256.0, 0.0, 1.0);
			obj->color.y = lim(obj->color.y / 256.0, 0.0, 1.0);
			obj->color.z = lim(obj->color.z / 256.0, 0.0, 1.0);
		}
		if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->size = get_single_var(here2);
		}
		if((here2 = ft_strstr(temp,"rot(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->rot = *vec3d(e, here2);
		}
		obj->type = 0;
		end++;
	}
	if((here = ft_strstr(file,"pov{\n")) && here != NULL)
	{
		obj = add_list(e);
		temp = chaine(here);
		here[0] = 'W';
		if(temp == NULL)
			return;
		if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->pos = *vec3d(e, here2);
		}
		if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->color = *vec3d(e, here2);
		}
		if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->size = get_single_var(here2);
		}
		if((here2 = ft_strstr(temp,"dir(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->rot = *vec3d(e, here2);
		}
		obj->type = 9;
		end++;
	}
	if((here = ft_strstr(file,"spot{\n")) && here != NULL)
	{
		obj = add_list(e);
		temp = chaine(here);
		here[0] = 'W';
		if(temp == NULL)
			return;
		if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->pos = *vec3d(e, here2);
		}
		if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->color = *vec3d(e, here2);
			obj->color.x = lim(obj->color.x / 256.0, 0.0, 1.0);
			obj->color.y = lim(obj->color.y / 256.0, 0.0, 1.0);
			obj->color.z = lim(obj->color.z / 256.0, 0.0, 1.0);
		}
		if((here2 = ft_strstr(temp,"int(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->intens = get_single_var(here2);
			obj->intens =  lim(obj->intens, 0.0, 99.0);
			obj->intens /= 100;
		}
		if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->size = get_single_var(here2);
			obj->size /= 100;
		}
		if((here2 = ft_strstr(temp,"rot(")) && here2 != NULL)
		{
			here2 = chaine2(here2);
			obj->rot = *vec3d(e, here2);
		}
		obj->type = 8;
		end++;
	}
	if(end != 0)
		traitement(file, e);
}

void		parsing(t_env *e, int argc, char *av)
{
	int		fd;
	char	*yt;
	char	*file;
	int		ret;


	e->obj = NULL;
	ret = 0;
	file = ft_memalloc(sizeof(char) * 1);
	if (argc != 2)
	{
		ft_putstr("bad arg\n");
		exit(1);
	}
	fd = 0;
	fd = open(av, O_RDONLY);
	while ((ret = get_next_line(fd, &yt)) && ret != -1)
	{
		file = ft_strjoin(file, yt);
		file = ft_strjoin(file, "\n");
	}
	traitement(file, e);
}
