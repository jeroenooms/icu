#include "utils.h"

const char* lookup_native_enc(){
  UErrorCode status = U_ZERO_ERROR;
  UConverter* conv = ucnv_open(NULL, &status);
  return ucnv_getName(conv, &status);
}

SEXP R_get_native_enc(){
  return mkString(lookup_native_enc());
}

cetype_t getNativeCE() {
  const char* ucnv_name = lookup_native_enc();
  if (!strcmp(ucnv_name, "US-ASCII") || !strcmp(ucnv_name, "UTF-8"))
      return CE_UTF8;
  if (!strcmp(ucnv_name, "ISO-8859-1"))
      return CE_LATIN1;
  return CE_ANY;
}

int native_is_singlebyte(){
  UErrorCode status = U_ZERO_ERROR;
  UConverter* conv = ucnv_open(NULL, &status);
  return ucnv_getMaxCharSize(conv) == 1;
}
