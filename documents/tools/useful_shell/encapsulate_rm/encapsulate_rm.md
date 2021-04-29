- 编辑 /etc/bash.bashrc
```
alias rm='dir/encapsulate_rm.sh'
```

- 编辑 /etc/crontab
```
0  0    * * *   root    /home/xmk/Documents/shell_dir/clean_trash.sh
service cron restart
```

- 说明
```
如果想使用 rm, 直接调用 /bin/rm
```
