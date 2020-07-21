"use the key "jk" to replace <ESC>
inore jk <ESC>
"display line of number
set nu
"about search
"lighter
set incsearch
"background color is dark or light
set background=dark
"to provide colorful
syntax enable
"to ignore BIG or small
set ignorecase
"the conditions of backspace to delete
set backspace=indent,eol,start
set autoindent
"creat a file~ before recover the file
"if has("vms")
"	set nobackup
"else
"	set backup
"endif
set history=25
set ruler
set showcmd

set history=25
set ruler
vnoremap p <Esc>:let current_reg = @"<CR>gvs<C-R>=current_reg<CR><Esc>
set showcmd


if &t_Co > 2 || has("gui_running")
syntax on
set hlsearch
endif
"auto kown the type of file,then do something
filetype plugin indent on
"autocmd FileType text setlocal textwidth=78
map ## i#include <><ESC>i
filetype plugin on
set nohlsearch
set nowrap
set sidescroll=10
set whichwrap=b,s,<,>,[,]
"display the \t and \v
set list
set listchars=tab:>-,trail:-
set cmdheight=2
"the colorscheme in $VIMRUNTIME/colors(/usr/share/vim/vim74/colors)
"colorscheme default
"
"auto save file when change the file in multifile_edit
set autowrite
"create cope_file of source_file
set backup
"the sign of file of backword
"set backupext=.bak
set writebackup
"the dir of bak_file,default is the dir of source
"set backupdir=~/bak/
"
"set patchmode=.orig
"the height and width always equal when spilt or vsplit
"winheight
"winminheight
"winwidth
"winminwidth
set nobackup
set equalalways
