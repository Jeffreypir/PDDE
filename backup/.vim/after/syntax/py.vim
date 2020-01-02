" Coment color
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
:syntax keyword mFunction print  plot length  exp def range in  
:highlight link mFunction Function 
:highlight Function ctermfg=blue cterm=bold

"Syntax Repeat
:syntax keyword mRepeat for while if elseif else
:highlight link mRepeat Repeat 

:highlight CursorLine ctermfg=white


"Syntax Comment
:syntax match  mComment "\v#.*$" 
:syntax match  mComment "\v\\"
:syntax match  mComment "\v\\."
:syntax match  mComment "\v\+"
:syntax match  mComment "\v-"
:syntax match  mComment "\v\*"
:syntax match  mComment "\v/"
:syntax match  mComment "\v\<"
:syntax match  mComment "\v\>"
:syntax match  mComment "\v\="
:highlight link mComment Comment
:highlight Comment ctermfg=green

:syntax match mString "\v\".+\""
:highlight link mString String

"Syntax Special
:syntax keyword mSpecial name input output arguments arg paramenters message import

:highlight link mSpecial Special 
:highlight Special ctermfg=red

