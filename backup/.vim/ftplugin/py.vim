" Configuration of section
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

"Fold
setlocal foldmethod=syntax
setlocal foldignore=

" macro
:nnoremap <F4> viw~<ESC>A<space>
:inoremap <leader>fc def <+name+> (<+arg1+>):<ESC>o<+arg2+>


"structure loop
"for
:inoremap <leader>sf for i in range (<+arg+>):<ESC>o
"while
:inoremap <leader>sw while <+arg+>:<ESC>o<+arg2+>

"if
:inoremap <leader>if if(<+arg1+>):<ESC>o <+arg2+>

"ifelse
:inoremap <leader>il :<ESC>oif(<+arg1+>):<ESC>o<+arg2+><ESC>oelse:<ESC>o<+arg3+>

"print 
:inoremap <leader>pr print("<+message+>,<+variable+>)

"Atalhos
:inoremap { {}<ESC>i
:inoremap ( ()<ESC>i
:inoremap [ []<ESC>i
:inoremap " ""<ESC>i

"Compementation
:inoremap \c :<ESC>a<c-x><c-n>
"name
:inoremap -na <ESC>"%pa

"date
:inoremap -da <ESC>:pu = strftime('%c')<CR><ESC>i<BS><ESC>$a

"gcc
:nnoremap <F2> :!clear <CR> <bar> :!python3.5 %<.py <CR>
