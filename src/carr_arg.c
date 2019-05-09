/*
MIT License

Copyright (c) 2018 JWRR.COM

git clone https://github.com/jwrr/carr.git

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include "carr_cis.h"
#include "carr.h"

//=================================================

//=================================================

const carr_t* carr_arg(int argc, char** argv, const char* options)
{
   if isZERO(argc) return NULL;
   if isNULL(argv) return NULL;
   size_t options_size = isNULL(options) ? 1 : strlen(options) + 1;
   char options2[options_size];
   *options2 = '\0';
   if (options_size > 1) {
      strncpy(options2, options, options_size);
   }
   char* options2_p = options2;
   char* token = strtok_r(options2, " ", &options2_p);
   size_t i = 0;
   while (token) {
      printf("%ld: '%s'\n", i, token);
      token = strtok_r(options2_p, " ", &options2_p);
      i++;
   }
   getchar();
   return NULL;
}

// const char* carr_arg_get(const char* option, size_t index);
// carr_t* carr_arg_free(carr_t* ptr);

