###问题: Are you sure you want to continue connecting (yes/no)?
1,可以使用ssh -o 的参数进行设置
例如: ssh -o StrictHostKeyChecking=no root@192.168.111.22
2,修改/etc/ssh/ssh_config
将其中的# StrictHostKeyChecking ask 改成 StrictHostKeyChecking no
出现登录慢的解决方法:
先用ssh root@192.168.111.22 -vvv 查看出现在那一步比较慢
例如:出现 debug1: Unspecified GSS failure. Minor code may provide more information
No credentials cache found
均可以通过 ssh -o 的参数进行设置
出现如上问题可以使用: -o GSSAPIAuthentication=no
例如 : ssh -o GSSAPIAuthentication=no root@192.168.111.22

### ssh单双引号的区别
单引号变量替换成远程主机的值，双引号变量替换成本地主机的值
例如: "$HOME" 本地， '$HOME' 远程
