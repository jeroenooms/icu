#include <R_ext/Rdynload.h>
#include "unicode/uclean.h"

void R_init_unicode(DllInfo* dll){
  UErrorCode status = U_ZERO_ERROR;
  u_init(&status);
}

void R_unload_unicode(DllInfo* dll){
  u_cleanup();
}
