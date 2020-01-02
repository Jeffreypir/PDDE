" Configuration of section
" Comment block code
:inoremap /* /* */<ESC>bi
:noremap co <ESC>j<c-v>/\/<ENTER>k:s/^/*<CR>:nohl<CR>
" Comment color
:highlight Comment ctermfg=blue 

"Line Number
:highlight LineNr ctermfg=red

"Number color
:highlight Number ctermfg=red

"Fold
:highlight Folded ctermfg=green
:highlight Folded ctermbg=black

"Color type
:highlight Type ctermfg=green

"Search color
:highlight Search ctermbg=blue 
:highlight Search ctermfg=white 

"Syntax function color
:syntax keyword cFunction printf  abs fabs puts
:highlight link cFunction Function 
:highlight Function ctermfg=11 cterm=bold

"Fold
setlocal foldmethod=syntax
setlocal foldignore=

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
 :call append('2','#include <++>')
:endfunction

" macro
:nnoremap <F4> viw~<ESC>A<space>
"call Library 
:nnoremap <leader>lb :call Lst()<CR>

"define
:nnoremap <silent><leader>de :call Def()<CR> 

"include
:nnoremap <silent><leader>ic :call Inc()<CR> 

"main
:nnoremap <leader>t1 :r /home/jefferson/template/template.c <CR> <bar>ggdd3j
:nnoremap <leader>mv :<ESC>iint main(void){<ESC>oreturn EXIT_SUCESS;<ESC>o}<ESC>
:nnoremap <leader>ma :<ESC>iint main(int argc, char *argv[]){<ESC>oreturn EXIT_SUCESS;<ESC>o}<ESC>
 
"structure loop
"for
:inoremap <leader>sf for (int i = 0; i <= n; i++){<ESC>o}<ESC>O
"while
:inoremap <leader>sw while (){<ESC>o}<ESC>1k6la

"if
:inoremap <leader>if if(<+arg+>){<ESC>o <++> <ESC>o}<ESC>0

"ifelse
:inoremap <leader>il :<ESC>oif(<++>){<ESC>o}else{<ESC>o<++><ESC>o}<ESC>3k<ESC>z

"print 
:inoremap <leader>pr printf("<+message+>%<+type+>\n",<+variable+>);<ESC>0

"fprintf
:inoremap <leader>fp fprintf(,"%<++>\n",<++>);<ESC>0

"functions
:inoremap <leader>fc <ESC>:r /home/jefferson/template/C/function.txt <CR><ESC>5jz 
":nnoremap <leader>fi :r /home/jefferson/template/C/integer.txt <CR><ESC>5jz 
":nnoremap <leader>ff :r /home/jefferson/template/C/float.txt <CR><ESC>5jz
":nnoremap <leader>fd :r /home/jefferson/template/C/double.txt <CR><ESC>5jz
":nnoremap <leader>fv :r /home/jefferson/template/C/void.txt <CR><ESC>5jz

"Atalhos
:inoremap { {}<ESC>i
:inoremap ( ()<ESC>i
:inoremap [ []<ESC>i
:inoremap " ""<ESC>i

"Abreviaturas
:iabbrev uns unsigned
:iabbrev gnu GNUPLOT "gnuplot -persist" 

"Leitura e escrita em arquivo
:nnoremap <leader>pt :r /home/jefferson/template/C/ler.txt <CR> \\z
:nnoremap <leader>gn :r /home/jefferson/template/C/gnuplot.txt <CR>
:noremap <silent><F7> viwdd<esc>koFILE<space>*<esc>pa;<esc>o<esc>i<tab><esc>pa = fopen("<++>","<++>");<esc>ofclose(<esc>pa);<esc>

"Compementation
:inoremap \c :<ESC>a<c-x><c-n>
"name
:inoremap -na <ESC>"%pa

"date
:inoremap -da <ESC>:pu = strftime('%c')<CR><ESC>i<BS><ESC>$a

"gcc
:nnoremap <F2> :!clear <CR> <bar> :!gcc -lm %<.c -o %< && ./%< <CR>
