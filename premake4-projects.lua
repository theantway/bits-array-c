project "bits_array"
  kind  "StaticLib"
  files { "bits_array.c" }

project "bits_array_tests"
  kind  "ConsoleApp"
  files { "bits_array_tests.c" }  
  links { "bits_array" }