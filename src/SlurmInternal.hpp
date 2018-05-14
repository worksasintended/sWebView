#pragma once

#include <slurm/slurm.h>
#include <functional>

inline void slurm_destroy_char(void *object)
{
  char *tmp = (char *)object;
  free(tmp);
}

extern "C"{
  extern void *slurm_xmalloc(size_t s, bool clear, const char *, int, const char *);
  extern char *slurm_xstrdup(const char *str);
}
#define xmalloc(s) slurm_xmalloc( s, true, __FILE__, __LINE__, __func__ )
#define xstrdup(s) slurm_xstrdup( s )

// convinience function for c++ to use xmalloc 
template <typename T>
T* slurm_malloc() {
  return (T*)xmalloc(sizeof(T));
}

inline auto to_slurm_str( const std::string& str ) {
  return xstrdup(str.c_str());
}

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

 
template <typename T, typename U>
inline void for_all( List l, U f ) {

  if ( !l ) {
    return;
  }

  auto it = slurm_list_iterator_create(l);
  while ( auto element = slurm_list_next(it) ){
    auto casted_element = (T*)element;
    f( casted_element );
  }
  slurm_list_iterator_destroy(it);
}
