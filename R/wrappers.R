#' Basic string processing
#'
#' Functions to manage and manipulate unicode strings.
#'
#' @export
#' @name unicode
#' @useDynLib unicode R_get_native_enc
#' @rdname unicode
#' @examples # Show native encoding
#' unicode::get_native_enc()
#' utils::localeToCharset()
get_native_enc <- function(){
  .Call(R_get_native_enc)
}

#' @param x a character vector
#' @export
#' @useDynLib unicode R_stri_length
#' @rdname unicode
#' @examples # Count length of strings
#' x <- c("Paris", "Zürich", "\346\235\261\344\272\254")
#' unicode::stri_length(x)
#' base::nchar(x)
stri_length <- function(x){
  .Call(R_stri_length, x)
}
