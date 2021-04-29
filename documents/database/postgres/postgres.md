## psql命令  
-E	启动时加-E，可以打印"\"开头的命令的实际sql
\set ECHO_HIDDEN {on|off}	开关打印"\"开头的命令的实际sql
\set AUTOCOMMIT {on|off}	开关自动提交
\set VERBOSITY verbose	开启详细的错误报告

## 允许修改某些系统表
```
set allow_system_table_mods='dml'
```

## 删除某个schema下的table
```
with table_name as (SELECT n.nspname as "Schema",
  c.relname as "Name"
FROM pg_catalog.pg_class c
     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.relnamespace
WHERE c.relkind IN ('r','v','m','S','f','')
      AND n.nspname <> 'pg_catalog'
      AND n.nspname <> 'information_schema'
      AND n.nspname !~ '^pg_toast'
  AND pg_catalog.pg_table_is_visible(c.oid)
ORDER BY 1,2) select 'drop table if exists '||table_name."Schema"||'.'||table_name."Name" from table_name;
\gexec
```

## 死锁查看  
```
SELECT blocked_locks.pid     AS blocked_pid,

         blocked_activity.usename  AS blocked_user,

         blocking_locks.pid     AS blocking_pid,

         blocking_activity.usename AS blocking_user,

         blocked_activity.query    AS blocked_statement,

         blocking_activity.query   AS current_statement_in_blocking_process

   FROM  pg_catalog.pg_locks         blocked_locks

    JOIN pg_catalog.pg_stat_activity blocked_activity  ON blocked_activity.pid = blocked_locks.pid

    JOIN pg_catalog.pg_locks         blocking_locks 

        ON blocking_locks.locktype = blocked_locks.locktype

        AND blocking_locks.DATABASE IS NOT DISTINCT FROM blocked_locks.DATABASE

        AND blocking_locks.relation IS NOT DISTINCT FROM blocked_locks.relation

        AND blocking_locks.page IS NOT DISTINCT FROM blocked_locks.page

        AND blocking_locks.tuple IS NOT DISTINCT FROM blocked_locks.tuple

        AND blocking_locks.virtualxid IS NOT DISTINCT FROM blocked_locks.virtualxid

        AND blocking_locks.transactionid IS NOT DISTINCT FROM blocked_locks.transactionid

        AND blocking_locks.classid IS NOT DISTINCT FROM blocked_locks.classid

        AND blocking_locks.objid IS NOT DISTINCT FROM blocked_locks.objid

        AND blocking_locks.objsubid IS NOT DISTINCT FROM blocked_locks.objsubid

        AND blocking_locks.pid != blocked_locks.pid

     JOIN pg_catalog.pg_stat_activity blocking_activity ON blocking_activity.pid = blocking_locks.pid

   WHERE NOT blocked_locks.GRANTED;
```
