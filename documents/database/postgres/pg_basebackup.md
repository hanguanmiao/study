##说明
以下安装测试在同一台机器上
postgres9.6
##配置
###主从配置
1. 初始化主库
    ```
    initdb -D /home/hgm/Software/postgresql/pg_basebackup_test/master
    ```
2. 配置主库的master/postgresql.conf
    ```
    listen_addresses = '*' 
    max_connections = 3000
    port = 5432
    logging_collector = on
    wal_level = replica
 //   archive_mode = on
 //   archive_command = 'rsync %p username@hostname:archivedir_master/%f'
    max_wal_senders = 3
    synchronous_commit = on
    synchronous_standby_names = 'slavenode'
    ```
3. 配置主库的master/pg_hba.conf
    ```
    host    all             all         192.168.2.1/24          trust
    host    replication     hgm         192.168.2.1/24          trust
    ```
4. 启动主库
    ```
    pg_ctl start -D master
    ```
5. 使用pg_basebackup生成备库
    ```
    pg_basebackup -D /home/hgm/Software/postgresql/pg_basebackup_test/slave -F p -X stream -R -P -h 192.168.2.101 -p 5432 -U hgm
    ```
6. 修改备库的slave/postgresql.conf
    ```
    port = 5433
    hot_standby = on
    hot_standby_feedback = on
    #synchronous_commit = on
    #synchronous_standby_names = 'slavenode'
    ```
7. 修改备库slave/recovery.conf
    ```
    standby_mode = on
    primary_conninfo = 'user=hgm host=192.168.2.101 port=5432sslmode=disable sslcompression=1 application_name=slavenode'
    recovery_target_timeline = 'latest'
    ```
8. 启动备库
    ```
    pg_ctl start -D slave
    ```
9. 查看数据库状态和信息
    ![enter image description here](http://note.lotuseed.com/api/file/getImage?fileId=5c3ef032f25c5c38b100ae3d)
    ![enter image description here](http://note.lotuseed.com/api/file/getImage?fileId=5c3fdf98f25c5c38b100ae4b)
###测试
1. 主库执行sql
    ```
    psql -d postgres -p 5432
    create table aaa(id int, name varchar);
    insert into aaa select generate_series(1,10),'aaaaaa';
    ```
2. 备库执行sql
    ```
    psql -d postgres -p 5433
    insert into aaa select generate_series(11,20),'bbbbbbbbbbb';
    ```
    ![enter image description here](http://note.lotuseed.com/api/file/getImage?fileId=5c3fe3e1f25c5c38b100ae4d)
3. 停止备库
    ```
    pg_ctl stop -D slave
    ```
4. 主库执行sql
    ```
    psql -d postgres -p 5432
    insert into aaa select generate_series(21,30),'ccc';
    ```
    出现如下问题
    ![enter image description here](http://note.lotuseed.com/api/file/getImage?fileId=5c3fe546f25c5c38b100ae4e)
    由于设置了参数synchronous_commit = on，备库被关闭了，但数据依然被插入了
5. 启动备库
    ```
    pg_ctl start -D slave/
    ```
###准备切换
1 . 停止主库
    ```
    pg_ctl stop -D master
    ```
2. 查看检测点是否一致(如何检测)
    ```
    pg_controldata master
    pg_controldata slave
    ```
3. 提升备库为主库
    ```
    pg_ctl promote -D slave
    ```
4. 现主库(原备库)执行sql
    ```
    psql -d postgres -p 5433
    select * from aaa ;
    insert into aaa select generate_series(31,40),'dddd';
    ```
5. 修改现备库master/postgresql.conf
    ```
    #synchronous_commit = on
    #synchronous_standby_names = 'slavenode'
    ```
6. 配置现备库master/recovery.conf
    ```
    standby_mode = on
    primary_conninfo = 'user=hgm host=192.168.2.101 port=5433 sslmode=disable sslcompression=1 application_name=masternode'
    recovery_target_timeline = 'latest'
    ```
7. 启动现备库
    ```
    pg_ctl start -D master
    ```
8. 修改现主库slave/postgresql.conf
    ```
    synchronous_commit = on
    synchronous_standby_names = 'masternode'
    ```
9. 重读现主库配置文件
    ```
    pg_ctl reload -D slave
    ```
###在测试
1. 现主库sql
    ```
    psql -d postgres -p 5433
    insert into aaa select generate_series(41,50),'eeee';
    ```
2. 备库sql
    ```
    insert into aaa select generate_series(41,50),'eeee';
    select * from aaa ;
    ```
3. 停止备库
    ```
    pg_ctl stop -D master/
    ```
4. 主库sql
    ![enter image description here](http://note.lotuseed.com/api/file/getImage?fileId=5c3ff71ef25c5c38b100ae51)
5. 停止主库
    ```
    pg_ctl stop -D slave/
    ```
6. 复制pg_xlog
    ```
    cp -r master/pg_xlog/ .
    rm -rf master/pg_xlog/
    cp -r slave/pg_xlog/ master/
    ```
7. 启动并提升备库
    ```
    pg_ctl start -D master/
    pg_ctl promote -D master/
    ```
8. 主库sql
    ```
    psql -d postgres -p 5432
    insert into aaa select generate_series(61,70),'gggggggggg';
    ```
9. 配置从库，不在赘述
10. 主库sql
    ```
    psql -d postgres -p 5432
    insert into aaa select generate_series(71,80),'hhh';
    select * from aaa;
    ```
11. 备库sql
    ```
    select * from aaa;
    ```

##函数
pg_is_in_recovery()
true表示备库，false表示主库

##表
pg_stat_replication

##参考资料
[使用pg_basebackup工具搭建流复制环境以及主备切换方法](https://blog.csdn.net/prettyshuang/article/details/50898363)
[postgresql主从复制并切换](https://www.cnblogs.com/yhq1314/p/10119556.html)

