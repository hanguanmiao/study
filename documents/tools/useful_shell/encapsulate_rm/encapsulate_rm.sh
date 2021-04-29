#!/bin/bash

trash_dir=/tmp/trash_dir	#创建回收站
if [ ! -d ${trash_dir} ];then
    mkdir -p -m 777 ${trash_dir}
    if [ $? -ne 0 ];then
        exit 1
    fi
fi

trash_dir_date=${trash_dir}/`date +%Y%m%d`
if [ ! -d ${trash_dir_date} ];then
    mkdir -p -m 777 ${trash_dir_date}
    if [ $? -ne 0 ];then
        exit 1
    fi
fi

WHO=$(whoami)
sub_trash_dir="${trash_dir_date}/${WHO}_`date +%H%M%S`"
if [ ! -d ${sub_trash_dir} ];then
    mkdir -p ${sub_trash_dir}
    if [ $? -ne 0 ];then
        exit 1
    fi
fi

for i in $*
do
    if [ ! -d "${i}" ] && [ ! -f "${i}" ]; then
        if [ "${i}" = "-rf" ] || [ "${i}" = "-r" ]; then # 判断-rf -r
            echo "rm是对mv的封装，请使用mv的参数"
            exit 1
        fi
    fi
done

mv $* "${sub_trash_dir}"

if [ $? -eq 0 ];then
    echo "completed"
fi
