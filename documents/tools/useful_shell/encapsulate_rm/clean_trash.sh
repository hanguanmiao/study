# !/bin/bash

trash_dir=/tmp/trash_dir
#rm_dirs=$(find ${trash_dir} -maxdepth 1 -type d -mtime +3)
#echo ${rm_dirs}
find ${trash_dir} -maxdepth 1 -type d -mtime +3 -exec /bin/rm -rf {} \;
