if [ $# -lt 2 ];then
    echo "Usage: ./mbns.sh shoubai bj"
    exit 0
fi

shoubai_prefix="gr-feed.SearchBox"
new_shoubai_prefix="shoubai-gr-tucheng.SUPERPAGE"
wise_prefix="wise-gr-tucheng.SUPERPAGE"

if [ $1 = "shoubai" ]; then
    bns_str=${shoubai_prefix}"."$2
fi

if [ $1 = "new_shoubai" ]; then
    bns_str=${new_shoubai_prefix}"."$2
fi

if [ $1 = "wise" ]; then
    bns_str=${wise_prefix}"."$2
fi

get_instance_by_service ${bns_str} | head -10

