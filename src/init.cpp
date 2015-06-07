#include <R_ext/Rdynload.h>
#include "unicode/uclean.h"

void R_init_icu(DllInfo* dll){
  UErrorCode status = U_ZERO_ERROR;
  u_init(&status);
}

void R_unload_icu(DllInfo* dll){
  u_cleanup();
}
