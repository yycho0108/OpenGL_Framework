set path=.
set path+=/usr/include
set path+=/usr/local/include
let g:clang_complete_macros = 1
let g:syntastic_cpp_compiler_options = '-std=c++11'
let g:ycm_extra_conf = './.ycm_extra_conf.py'
