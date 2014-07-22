if &cp | set nocp | endif
nmap \ihn :IHN
nmap \is :IHS:A
nmap \ih :IHS
let s:cpo_save=&cpo
set cpo&vim
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
imap \ihn :IHN
imap \is :IHS:A
imap \ih :IHS
let &cpo=s:cpo_save
unlet s:cpo_save
set backspace=indent,eol,start
set cindent
set cinoptions={0,:0,g0,11,to,(0
set fileencodings=ucs-bom,utf-8,latin1
set guicursor=n-v-c:block,o:hor50,i-ci:hor15,r-cr:hor30,sm:block,a:blinkon0
set helplang=en
set history=50
set hlsearch
set ruler
set shiftwidth=4
set softtabstop=4
set tabstop=4
set viminfo='20,\"50
" vim: set ft=vim :
