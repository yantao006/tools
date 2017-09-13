set fenc=utf-8
set encoding=utf-8
set fileencodings=utf-8,gb18030,utf-16,big5
set termencoding=utf-8  "vim 输出到显示终端时使用的编码，这个一定要和 终端( secureCRT) 的编码一致，不然也会出现乱码

" 用于配置python-mode using Pathogen load
filetype off
call pathogen#infect()
call pathogen#helptags()
" 取消代码折叠
"let g:pymode_folding = 0
" 打开代码检查
"let g:pymode_lint  = 0
" Turn on code completion support in the plugin
"let g:pymode_rope_completion = 1
"let g:pymode_rope = 0 "禁止rope功能
" 取消设置python默认选项
"let g:pymode_options = 0
filetype plugin indent on

""""""配置Vundle插件开始"""""“”"""
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
 """"""配置Vundle插件完成""""""""

let g:SuperTabRetainCompletionType = 0

" 定义快捷键到行首和行尾
" nmap lb 0
" nmap le $
" 定义快捷键的前缀，即<Leader>
let mapleader=";"
" 设置快捷键将选中文本块复制至系统剪贴板
vnoremap <Leader>y "+y
" 设置快捷键将系统剪贴板内容粘贴至 vim
nmap <Leader>p "+p
" 定义快捷键关闭当前分割窗口
nmap <Leader>q :q<CR>
" 定义快捷键保存当前窗口内容
nmap <Leader>w :w<CR>
" 定义快捷键保存所有窗口内容并退出 vim
nmap <Leader>WQ :wa<CR>:q<CR>
" 不做任何保存，直接退出 vim
nmap <Leader>Q :qa!<CR>
" 依次遍历子窗口
nnoremap [w  <C-W><C-W>
" 跳转至右方的窗口
" nnoremap <Leader>lw <C-W>l
" 跳转至方的窗口
" nnoremap <Leader>hw <C-W>h
" 跳转至上方的子窗口
" nnoremap <Leader>kw <C-W>k
" 跳转至下方的子窗口
" nnoremap <Leader>jw <C-W>j
" 让所有的屏有相同的宽度
"见网址：https://nkcoder.github.io/2014/01/05/vim-basic-usage/ 
" nnoremap <Leader>w= <C-W>=
" vim 自身命令行模式智能补全
set wildmenu
" 高亮显示当前行/列
set cursorline
" set cursorcolumn
nnoremap <leader>gd :YcmCompleter GoToDeclaration<CR>
" 只能是 #include 或已打开的文件
nnoremap <leader>je :YcmCompleter GoToDefinition<CR>
"命令打开文件类型检测功能，它相当于文件类型检测功能的开关
filetype on
"开启实时搜索功能
set incsearch
"忽略搜索小写功能
set ignorecase
"增强模式中的命令行自动完成操作,可以在命令行下Tab键给出命令列表
set wildmenu
set wildmode=longest:list,full
"高亮搜索
set hlsearch
"显示状态栏
set laststatus=2
"显示尺标
set ruler
 "搜索忽略大小写
set ignorecase smartcase
"关闭vi兼容模式
set nocompatible              
"显示行号 
set nu

"自动缩进
set autoindent
" 将制表符扩展为空格
set expandtab
" 设置编辑时制表符占用空格数
set tabstop=4
" 让 vim 把连续数量的空格视为一个制表符
set softtabstop=4
"当使用移动(shift)命令时移动的字符数
set shiftwidth=4
set fileformat=unix
"设置背景深色
:set background="/dark" 
"语法高亮
syntax on
"调用vundle
set rtp+=~/.vim/bundle/vundle/
map <C-F11> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR>
set ts=4
set nocp
set mouse=v  " always use mouse 使用鼠标
set statusline=%F%m%r%h%w\ [POS=%04l,%04v][%p%%]\ [LEN=%L]
"设置按语法进行折叠
" set foldmethod=syntax

"配色方案
"colorscheme moss
"colorscheme solarized 
"colorscheme desert
"colorscheme Tomorrow-Night-Eighties 
"colorscheme Tomorrow-Night-Bright 


" YCM 补全菜单配色
" 菜单
highlight Pmenu ctermfg=2 ctermbg=3 guifg=#005f87 guibg=#EEE8D5
" 选中项
highlight PmenuSel ctermfg=2 ctermbg=3 guifg=#AFD700 guibg=#106900
" 补全功能在注释中同样有效
let g:ycm_complete_in_comments=1
" 允许 vim 加载 .ycm_extra_conf.py 文件，不再提示
let g:ycm_confirm_extra_conf=0
" 开启 YCM 标签补全引擎
let g:ycm_collect_identifiers_from_tags_files=1
" 引入 C++ 标准库tags
set tags+=/home/work/yantao06/workspace_feedgr2/baidu/tags

" YCM 集成 OmniCppComplete 补全引擎，设置其快捷键
inoremap <leader>; <C-x><C-o>
" 补全内容不以分割子窗口形式出现，只显示补全列表
set completeopt-=preview
" 从第一个键入字符就开始罗列匹配项
let g:ycm_min_num_of_chars_for_completion=1
" 禁止缓存匹配项，每次都重新生成匹配项
let g:ycm_cache_omnifunc=0
" 语法关键字补全         
let g:ycm_seed_identifiers_with_syntax=1
let g:ycm_server_keep_logfiles = 1
let g:ycm_server_log_level = 'debug'

" cscope 设置
set nocscopeverbose
cs add /home/work/yantao06/workspace_feedgr2/baidu/cscope.out /home/work/yantao06/workspace_feedgr2/baidu/
nmap <F7> :cs find s <C-R>=expand("<cword>")<CR><CR>

" Ack插件配置
nnoremap <F5> :Ack -i<SPACE> 
"设置 tagslist
"设置打开文件自动开启Tlist
let Tlist_Auto_Open=0
"让taglist窗口出现在Vim的右边
let Tlist_Use_Left_Window = 1
"当同时显示多个文件中的tag时，设置为1，可使taglist只显示当前文件tag，其它文件的tag都被折叠起来
let Tlist_File_Fold_Auto_Close = 1
"只显示一个文件中的tag，默认为显示多个
let Tlist_Show_One_File = 1
"taglist窗口是最后一个窗口时退出VIM
let Tlist_Exit_OnlyWindow = 1
"Tag的排序规则，以名字排序。默认是以在文件中出现的顺序排序
"let Tlist_Sort_Type ='name'
"Taglist窗口打开时，立刻切换为有焦点状态
let Tlist_GainFocus_On_ToggleOpen = 1
"如果taglist窗口是最后一个窗口，则退出vim
"let Tlist_Exit_OnlyWindow = 1
"设置窗体宽度为32，可以根据自己喜好设置
let Tlist_WinWidth = 32
"这里比较重要了，设置ctags的位置
"let Tlist_Ctags_Cmd ='/usr/local/bin/ctags'
let Tlist_Ctags_Cmd ='/usr/bin/ctags'
"热键设置
map t :TlistToggle
"设置单击tag就跳到tag定义的位置
let Tlist_Use_SingleClick = 1


nmap <F2> :NERDTreeToggle <CR>
" 设置NERDTree子窗口宽度
let NERDTreeWinSize=32
" 设置NERDTree子窗口位置
let NERDTreeWinPos="left"
" 显示隐藏文件
let NERDTreeShowHidden=1
" " NERDTree 子窗口中不显示冗余帮助信息
let NERDTreeMinimalUI=0
" 删除时自动删除文件对应 buffer
let NERDTreeAutoDeleteBuffer=1

" DoxygenToolKit.vim配置
" :DoxLic
" :DoxAuthor
" :Dox
" :DoxBlock
" :DoxUndoc
