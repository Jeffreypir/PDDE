"Load template in *c
au BufNewFile,BufRead *.c :set filetype=c
au BufNewFile *.c :r /home/jefferson/template/template.c
au BufNewFile *.c :normal ggdd
