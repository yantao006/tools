set fenc=utf-8
set encoding=utf-8
set fileencodings=utf-8,gb18030,utf-16,big5
set termencoding=utf-8  "vim �������ʾ�ն�ʱʹ�õı��룬���һ��Ҫ�� �ն�( secureCRT) �ı���һ�£���ȻҲ���������

" ��������python-mode using Pathogen load
filetype off
call pathogen#infect()
call pathogen#helptags()
" ȡ�������۵�
"let g:pymode_folding = 0
" �򿪴�����
"let g:pymode_lint  = 0
" Turn on code completion support in the plugin
"let g:pymode_rope_completion = 1
"let g:pymode_rope = 0 "��ֹrope����
" ȡ������pythonĬ��ѡ��
"let g:pymode_options = 0
filetype plugin indent on

""""""����Vundle�����ʼ"""""����"""
set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" plugin on GitHub repo
Plugin 'SuperTab'
"Plugin 'scrooloose/nerdtree'
"Plugin 'jistr/vim-nerdtree-tabs'
"Plugin 'python-mode'
Bundle 'taglist.vim'


" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
 """"""����Vundle������""""""""

let g:SuperTabRetainCompletionType = 0

" �����ݼ������׺���β
" nmap lb 0
" nmap le $
" �����ݼ���ǰ׺����<Leader>
let mapleader=";"
" ���ÿ�ݼ���ѡ���ı��鸴����ϵͳ������
vnoremap <Leader>y "+y
" ���ÿ�ݼ���ϵͳ����������ճ���� vim
nmap <Leader>p "+p
" �����ݼ��رյ�ǰ�ָ��
nmap <Leader>q :q<CR>
" �����ݼ����浱ǰ��������
nmap <Leader>w :w<CR>
" �����ݼ��������д������ݲ��˳� vim
nmap <Leader>WQ :wa<CR>:q<CR>
" �����κα��棬ֱ���˳� vim
nmap <Leader>Q :qa!<CR>
" ���α����Ӵ���
nnoremap [w  <C-W><C-W>
" ��ת���ҷ��Ĵ���
" nnoremap <Leader>lw <C-W>l
" ��ת�����Ĵ���
" nnoremap <Leader>hw <C-W>h
" ��ת���Ϸ����Ӵ���
" nnoremap <Leader>kw <C-W>k
" ��ת���·����Ӵ���
" nnoremap <Leader>jw <C-W>j
" �����е�������ͬ�Ŀ��
"����ַ��https://nkcoder.github.io/2014/01/05/vim-basic-usage/ 
" nnoremap <Leader>w= <C-W>=
" vim ����������ģʽ���ܲ�ȫ
set wildmenu
" ������ʾ��ǰ��/��
set cursorline
" set cursorcolumn
nnoremap <leader>gd :YcmCompleter GoToDeclaration<CR>
" ֻ���� #include ���Ѵ򿪵��ļ�
nnoremap <leader>je :YcmCompleter GoToDefinition<CR>
"������ļ����ͼ�⹦�ܣ����൱���ļ����ͼ�⹦�ܵĿ���
filetype on
"����ʵʱ��������
set incsearch
"��������Сд����
set ignorecase
"��ǿģʽ�е��������Զ���ɲ���,��������������Tab�����������б�
set wildmenu
set wildmode=longest:list,full
"��������
set hlsearch
"��ʾ״̬��
set laststatus=2
"��ʾ�߱�
set ruler
 "�������Դ�Сд
set ignorecase smartcase
"�ر�vi����ģʽ
set nocompatible              
"��ʾ�к� 
set nu

"�Զ�����
set autoindent
" ���Ʊ����չΪ�ո�
set expandtab
" ���ñ༭ʱ�Ʊ��ռ�ÿո���
set tabstop=4
" �� vim �����������Ŀո���Ϊһ���Ʊ��
set softtabstop=4
"��ʹ���ƶ�(shift)����ʱ�ƶ����ַ���
set shiftwidth=4
set fileformat=unix
"���ñ�����ɫ
:set background="/dark" 
"�﷨����
syntax on
"����vundle
set rtp+=~/.vim/bundle/vundle/
map <C-F11> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR>
set ts=4
set nocp
set mouse=v  " always use mouse ʹ�����
set statusline=%F%m%r%h%w\ [POS=%04l,%04v][%p%%]\ [LEN=%L]
"���ð��﷨�����۵�
" set foldmethod=syntax

"��ɫ����
"colorscheme moss
"colorscheme solarized 
"colorscheme desert
"colorscheme Tomorrow-Night-Eighties 
"colorscheme Tomorrow-Night-Bright 


" YCM ��ȫ�˵���ɫ
" �˵�
highlight Pmenu ctermfg=2 ctermbg=3 guifg=#005f87 guibg=#EEE8D5
" ѡ����
highlight PmenuSel ctermfg=2 ctermbg=3 guifg=#AFD700 guibg=#106900
" ��ȫ������ע����ͬ����Ч
let g:ycm_complete_in_comments=1
" ���� vim ���� .ycm_extra_conf.py �ļ���������ʾ
let g:ycm_confirm_extra_conf=0
" ���� YCM ��ǩ��ȫ����
let g:ycm_collect_identifiers_from_tags_files=1
" ���� C++ ��׼��tags
set tags+=/home/work/yantao06/workspace_feedgr2/baidu/tags

" YCM ���� OmniCppComplete ��ȫ���棬�������ݼ�
inoremap <leader>; <C-x><C-o>
" ��ȫ���ݲ��Էָ��Ӵ�����ʽ���֣�ֻ��ʾ��ȫ�б�
set completeopt-=preview
" �ӵ�һ�������ַ��Ϳ�ʼ����ƥ����
let g:ycm_min_num_of_chars_for_completion=1
" ��ֹ����ƥ���ÿ�ζ���������ƥ����
let g:ycm_cache_omnifunc=0
" �﷨�ؼ��ֲ�ȫ         
let g:ycm_seed_identifiers_with_syntax=1
let g:ycm_server_keep_logfiles = 1
let g:ycm_server_log_level = 'debug'

" cscope ����
set nocscopeverbose
cs add /home/work/yantao06/workspace_feedgr2/baidu/cscope.out /home/work/yantao06/workspace_feedgr2/baidu/
nmap <F7> :cs find s <C-R>=expand("<cword>")<CR><CR>

" Ack�������
nnoremap <F5> :Ack -i<SPACE> 
"���� tagslist
"���ô��ļ��Զ�����Tlist
let Tlist_Auto_Open=0
"��taglist���ڳ�����Vim���ұ�
let Tlist_Use_Left_Window = 1
"��ͬʱ��ʾ����ļ��е�tagʱ������Ϊ1����ʹtaglistֻ��ʾ��ǰ�ļ�tag�������ļ���tag�����۵�����
let Tlist_File_Fold_Auto_Close = 1
"ֻ��ʾһ���ļ��е�tag��Ĭ��Ϊ��ʾ���
let Tlist_Show_One_File = 1
"taglist���������һ������ʱ�˳�VIM
let Tlist_Exit_OnlyWindow = 1
"Tag�������������������Ĭ���������ļ��г��ֵ�˳������
"let Tlist_Sort_Type ='name'
"Taglist���ڴ�ʱ�������л�Ϊ�н���״̬
let Tlist_GainFocus_On_ToggleOpen = 1
"���taglist���������һ�����ڣ����˳�vim
"let Tlist_Exit_OnlyWindow = 1
"���ô�����Ϊ32�����Ը����Լ�ϲ������
let Tlist_WinWidth = 32
"����Ƚ���Ҫ�ˣ�����ctags��λ��
"let Tlist_Ctags_Cmd ='/usr/local/bin/ctags'
let Tlist_Ctags_Cmd ='/usr/bin/ctags'
"�ȼ�����
map t :TlistToggle
"���õ���tag������tag�����λ��
let Tlist_Use_SingleClick = 1


nmap <F2> :NERDTreeToggle <CR>
" ����NERDTree�Ӵ��ڿ��
let NERDTreeWinSize=32
" ����NERDTree�Ӵ���λ��
let NERDTreeWinPos="left"
" ��ʾ�����ļ�
let NERDTreeShowHidden=1
" " NERDTree �Ӵ����в���ʾ���������Ϣ
let NERDTreeMinimalUI=0
" ɾ��ʱ�Զ�ɾ���ļ���Ӧ buffer
let NERDTreeAutoDeleteBuffer=1

" DoxygenToolKit.vim����
" :DoxLic
" :DoxAuthor
" :Dox
" :DoxBlock
" :DoxUndoc
