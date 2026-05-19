#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
  int i = 0;
  /* FIX: added `s[i] &&` so the loop stops at '\0' when c isn't found
     (original walked past the end of the string). */
  while (s[i] && s[i] != c)
    i++;
  if (s[i] == c)
    return s + i;
  return NULL;
}

/* FIX: rewrote with a forward `i < n` loop. The original `while (--n > 0)`
   was off-by-one and never copied the last byte. */
void *ft_memcpy(void *dest, const void *src, size_t n)
{
  size_t i = 0;
  while (i < n)
  {
    ((char *)dest)[i] = ((char *)src)[i];
    i++;
  }
  return dest;
}

size_t ft_strlen(char *s)
{
  size_t res = 0;
  /* FIX: guard against NULL — str_append_mem passes *s1 which is NULL
     on the first append. */
  if (!s)
    return 0;
  while (*s)
  {
    s++;
    res++;
  }
  return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
  size_t size1 = ft_strlen(*s1);
  char *tmp = malloc(size2 + size1 + 1);
  if (!tmp)
    return 0;
  /* FIX: only copy the old buffer when *s1 isn't NULL; the original
     unconditionally ft_memcpy'd from NULL on the first call. */
  if (*s1)
    ft_memcpy(tmp, *s1, size1);
  ft_memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = '\0';
  free(*s1);
  *s1 = tmp;
  return 1;
}

int str_append_str(char **s1, char *s2)
{
  return str_append_mem(s1, s2, ft_strlen(s2));
}

/* FIX: removed ft_memmove — it had infinite recursion in the
   `dest > src` branch and was never called by get_next_line anyway. */

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;
  char *tmp = ft_strchr(b, '\n');

  while (!tmp)
  {
    if (!str_append_str(&ret, b))
      return (NULL);
    int read_ret = read(fd, b, BUFFER_SIZE);
    /* FIX: on read error, free the accumulated `ret` before returning
       so we don't leak. */
    if (read_ret == -1)
    {
      free(ret);
      return (NULL);
    }
    b[read_ret] = 0;
    /* FIX: handle EOF (read_ret == 0). The original had no EOF branch
       and would loop forever once read started returning 0.
       Return the accumulated line, or NULL if nothing was read. */
    if (read_ret == 0)
    {
      if (*ret == '\0')
      {
        free(ret);
        return (NULL);
      }
      return (ret);
    }
    /* FIX: recompute tmp after the new read — the original computed it
       once before the loop and never refreshed it. */
    tmp = ft_strchr(b, '\n');
  }
  if (!str_append_mem(&ret, b, tmp - b + 1))
  {
    free(ret);
    return (NULL);
  }
  /* FIX: preserve the bytes after '\n' in the static buffer for the
     next call (the original lost them on the next read). */
  size_t rest = ft_strlen(tmp + 1);
  ft_memcpy(b, tmp + 1, rest);
  b[rest] = '\0';
  return (ret);
}
