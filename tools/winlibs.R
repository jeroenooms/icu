# Build against ICU static libraries.
if(!file.exists("../windows/icu4c-55.1/include/unicode/regex.h")){
  setInternet2()
  download.file("https://github.com/rwinlib/icu4c/archive/v55.1.zip", "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")
}
