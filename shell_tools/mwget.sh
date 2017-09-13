if [ $# -lt 1 ];then
    echo "Usage: ./mwget.sh filename"
    exit 0
fi
if [ ! -d $1 ] && [ ! -f $1 ];then
    echo "path $1 invalid"
    exit 0
fi
m_path=`readlink -f $1`

if [ -f $m_path ];then
    file_name=`echo "$m_path" | awk -F "/" '{print $NF}'`
    m_path=$m_path" -O "$file_name
elif [ -d $m_path ];then
    dir_depth=`echo "$m_path" | awk -F "/" '{print NF-2}'`
    m_path=$m_path" -r -nH --level=0 --cut-dir="$dir_depth
fi

m_host=`hostname`
m_host="wget ftp://"${m_host}$m_path
echo $m_host
