#pragma once

inline void slurm_destroy_char(void *object)
{
  char *tmp = (char *)object;
  free(tmp);
}

extern "C"{
  extern void *slurm_xmalloc(size_t s, bool clear, const char *, int, const char *);
}
#define xmalloc(s) slurm_xmalloc( s, true, __FILE__, __LINE__, __func__ )


