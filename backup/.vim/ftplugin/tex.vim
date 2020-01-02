"text
:set tw=110
" Search color
:highlight Search ctermbg=blue 
:highlight Search ctermfg=white 

"Line Number
:highlight LineNr ctermfg=red

"Number color
:highlight Number ctermfg=red

"Fold
:highlight Folded ctermfg=green
:highlight Folded ctermbg=black

"Color type
:highlight Type ctermfg=green

" Search color
:highlight Search ctermbg=blue 
:highlight Search ctermfg=white 

"Comment color
:highlight Comment ctermbg=blue 

"Fold
setlocal foldmethod=indent
setlocal foldignore= 

"Acentos
:inoremap ^ \^
:inoremap ' \'
:inoremap ~ \~
:inoremap ç \c c
:inoremap ^ \^
:inoremap \ct <esc> I% <esc>
:set tw=120

"Maiuscula
:nnoremap <F4> viw~<ESC>A<space>

" Configurando o make para latex
: set makeprg=pdflatex\ %
: nnoremap <F10> <esc>01la%<ESC>
: nnoremap <F11> <esc>02lx<ESC>
: nnoremap <F8> :!latex %< && bibtex %< && bibtex <CR>
": nnoremap <F10> <esc> :make <CR> <CR>
": nnoremap <F11> <esc> :!zathura %<.pdf & <CR> <CR>

" Configuraion of plugin
:noremap <F12> <ESC>:sp /home/jefferson/.vim/ftplugin/tex.vim <CR>

"Compilation 
: map <F2> <esc> :make <CR> <CR>
: nnoremap <F3> <esc> :!zathura %<.pdf & <CR> <CR>

"Shorcut for dissertation
": map <f2> :!pdflatex jefferson.tex <CR> <CR> 
": nnoremap <F3> <esc> :!zathura jefferson.pdf & <CR> <CR>

"Envirommente shortcut
:inoremap <leader>ali \begin{align}<ESC>o\end{align}<ESC>O\label {<++>}<ESC>o
:inoremap <leader>ani \begin{align*}<ESC>o\end{align*}<ESC>O
:inoremap <leader>fig \begin{figure}[!h]<ESC>o\centering<ESC>o\label{<++>} <ESC>o\end{figure}<ESC>O\includegraphics[width=<+size+>]{<+file+>}
:inoremap <leader>tab \begin{tabular}<ESC>o\end{tabular}
:inoremap <leader>sf \subfigure[<+title+>]{<ESC>o}<ESC>O\includegraphics[width=<+size+>]{<+file+>}


"Usepackage
:nnoremap <F7> viw<esc>a}<esc>bi\usepackage{<esc>

"Enviromment begin
:nnoremap <silent><leader>bg viwd<esc>i\begin{<esc>pa}<esc>o<esc>i\end{<esc>pa}<esc>O<esc>i<tab>

"Templates
:nnoremap <leader>t1 :r /home/jefferson/template/template.tex <CR> <bar>ggdd
:nnoremap <leader>t2 :r /home/jefferson/template/template2.tex <CR> <bar>ggdd
:nnoremap <leader>t3 :r /home/jefferson/template/template3.tex <CR> <bar>ggdd
:nnoremap <leader>tc :r /home/jefferson/template/comandos.tex <CR>
:nnoremap <leader>eq :r /home/jefferson/template/equatio.tex <CR>

"Dictionary
:inoremap <leader>gr <esc>:set dictionary+=/home/jefferson/dictionary/gregdic <CR><ESC>a<c-x><c-k>
:inoremap <leader>ev <esc>:set dictionary+=/home/jefferson/dictionary/envdic <CR><ESC>a<c-x><c-k>

"Left e right
:inoremap <silent><leader>lr <esc>i\left <+arg1+>\right <+arg2+><esc>7bi

"Atalhos
:inoremap { {}<ESC>i
:inoremap ( ()<ESC>i
:inoremap [ []<ESC>i
:inoremap < <><ESC>i
:inoremap \nn \nonumber
:inoremap \nl \nonumber \\
:inoremap \4 $$<ESC>i
:inoremap ** ^{}<ESC>i
:inoremap <leader>re <esc>o\resizebox{<++>\width}{!}{<esc>o}<esc>O
:inoremap <leader>fc \frac{<+arg1+>}{<+arg2+>}<esc>5ba
:inoremap <leader>exp e^{<+arg+>}
:inoremap -lb \left. <+arg1+> \right \|_{<+inf+>}^{<+sup+>}
