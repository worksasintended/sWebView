#pragma once

#include <slurm/slurm.h>

inline void slurm_destroy_char(void *object)
{
  char *tmp = (char *)object;
  free(tmp);
}

extern "C"{
  extern void *slurm_xmalloc(size_t s, bool clear, const char *, int, const char *);
}
#define xmalloc(s) slurm_xmalloc( s, true, __FILE__, __LINE__, __func__ )


inline int list_count(List l)
{
  int ctr = 0; 
  auto it = slurm_list_iterator_create(l);

  while ( auto element = slurm_list_next(it) ){
    ctr++;
  }

  slurm_list_iterator_destroy(it);
  return ctr;
}
