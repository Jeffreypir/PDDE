" Search color
:highlight Search ctermbg=blue 
:highlight Search ctermfg=white 

"plugin for C
:function! Lst()
  :call append('0','#include <stdio.h>')
  :call append('1','#define EXIT_SUCESS 0')
endfunction

"function define
:function! Def()
 :call append('2','#define <++>')
:endfunction

"function define
:function! Inc()
 :call append('1','#include <++>')
:endfunction

" macro
:nnoremap <F4> viw~<ESC>A<space>
"call Library 
:nnoremap <leader>lb :call Lst()<CR>

"define
:nnoremap <silent><leader>d :call Def()<CR> 

"include
:nnoremap <silent><leader>c :call Inc()<CR> 

"main
:nnoremap <leader>t1 :r /home/jefferson/template/template.c <CR> <bar>ggdd3j
:nnoremap <leader>m :<ESC>iint main(void){<ESC>oreturn EXIT_SUCESS;<ESC>o}<ESC>
:nnoremap <leader>ma :<ESC>iint main(int argc, char *argv[]){<ESC>oreturn EXIT_SUCESS;<ESC>o}<ESC>

"structure loop
"for
:nnoremap <leader>sf :<ESC>ofor (int i = 0; i <= N; i++){<ESC>o}<ESC>1k

"while
:nnoremap <leader>sw :<ESC>owhile (){<ESC>o}<ESC>1k6la

"if
:nnoremap <leader>if :<ESC>oif(<++>){<ESC>o <++> <ESC>o}<ESC>3k

"ifelse
:nnoremap <leader>il :<ESC>oif(<++>){<ESC>o}else{<ESC>o<++><ESC>o}<ESC>3k<ESC>z

"print 
:nnoremap <leader>p :<ESC>oprintf("%<++>\n",<++>);<ESC>4b8li

"functions
":nnoremap <leader>fi :<ESC>iint (<++>){<ESC>o <++> <ESC>oreturn <++>;<ESC>o}<ESC>3k4li
":nnoremap <leader>ff :<ESC>ifloat (<++>){<ESC>o <++> <ESC>oreturn <++>;<ESC>o}<ESC>3k4li
":nnoremap <leader>fd :<ESC>idouble (<++>){<ESC>o <++> <ESC>oreturn <++>;<ESC>o}<ESC>3k4li
":nnoremap <leader>fv :<ESC>ivoid (<++>){<ESC>o <++> <ESC>o}<ESC>2k4li
":nnoremap c :<ESC>a<c-x><c-n>

"Atalhos
:inoremap { {}<ESC>i
:inoremap ( ()<ESC>i
:inoremap += +=<++>;<ESC>7h<space>

"Abreviaturas
:iabbrev uns unsigned

"gcc
:nnoremap <F10> :!clear <CR> <bar> :!gcc %<.c -o %< && ./%< <CR>
