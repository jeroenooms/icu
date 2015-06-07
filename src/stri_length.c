/* Adapted from 'stringi' code from Marek Gagolewski and Bartek Tartanus */

#include "utils.h"
#include <unicode/utypes.h>

SEXP R_stri_length(SEXP vec) {
  int vec_len = LENGTH(vec);
  SEXP ret = PROTECT(allocVector(INTSXP, vec_len));
  int* retint = INTEGER(ret);

  for (int i = 0; i < vec_len; i++) {
    SEXP str = STRING_ELT(vec, i);
    if (str == NA_STRING) {
      retint[i] = NA_INTEGER;
      continue;
    }

    int str_len = LENGTH(str);
    if (getCharCE(str) == CE_LATIN1 || (getCharCE(str) == CE_NATIVE && getNativeCE() == CE_LATIN1)) {
      retint[i] = str_len;
    } else if (getCharCE(str) == CE_BYTES) {
      UNPROTECT(1);
      error("Invalid encoding: bytes.");
    } else if (getCharCE(str) == CE_UTF8 || (getCharCE(str) == CE_NATIVE && getNativeCE() == CE_UTF8)) {
      UChar32 out = 0;
      const char* source = CHAR(str);
      R_len_t j = 0;
      int count;
      for (count = 0; out >= 0 && j < str_len; count++) {
        U8_NEXT(source, j, str_len, out); // faster that U8_FWD_1 & gives bad UChar32s
      }
      if (out < 0) {
        warning("Invalid UTF8 string: %s", source);
        retint[i] = NA_INTEGER;
      } else {
        retint[i] = count;
      }
    } else if (native_is_singlebyte()) { // native-8bit
      retint[i] = str_len;
    } else {
      // native encoding, not 8 bit
      UErrorCode status = U_ZERO_ERROR;
      UConverter* conv = ucnv_open(NULL, &status);
      const char* source = CHAR(str);
      const char* sourceLimit = source + str_len;
      int j;
      for (j = 0; source != sourceLimit; j++) {
        ucnv_getNextUChar(conv, &source, sourceLimit, &status);
      }
      retint[i] = j; // all right, we got it!
    }
  }

  UNPROTECT(1);
  return ret;
}
