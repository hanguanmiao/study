## 版本号  

postgres-13.3  

## 宏定义  

![image.png](https://foruda.gitee.com/images/1675827607372362806/b83e9825_10017097.png)  
> #define MULTIXACT_OFFSETS_PER_PAGE		2048
> #define MultiXactIdToOffsetPage(xid)			(xid/2048)
> #define MultiXactIdToOffsetEntry(xid)			(xid%2048)
> #define MultiXactIdToOffsetSegment(xid)		(xid/2048)/32

![image.png](https://foruda.gitee.com/images/1675826035337194919/ab8d25b9_10017097.png)  
> #define MXACT_MEMBER_BITS_PER_XACT			8
> #define MXACT_MEMBER_FLAGS_PER_BYTE			1
> #define MXACT_MEMBER_XACT_BITMASK   			0xff
> #define MULTIXACT_FLAGBYTES_PER_GROUP			4
> #define MULTIXACT_MEMBERS_PER_MEMBERGROUP  	4
> #define MULTIXACT_MEMBERGROUP_SIZE			20
> #define MULTIXACT_MEMBERGROUPS_PER_PAGE		409
> #define MULTIXACT_MEMBERS_PER_PAGE			1636

![image.png](https://foruda.gitee.com/images/1675828228711763585/53b5d8db_10017097.png)  
> #define MAX_MEMBERS_IN_LAST_MEMBERS_PAGE		1036
> #define MXOffsetToMemberPage(xid)			((xid)/1636)
> #define MXOffsetToMemberSegment(xid)		((xid)/1636/24)
> #define MXOffsetToFlagsOffset(xid)			((((xid) / 4) % 409) * 20)
> #define MXOffsetToFlagsBitShift(xid)			(((xid) % 4) * 8)
> #define MXOffsetToMemberOffset(xid)			(((((xid) / 4) % 409) * 20) + 4 + ((xid) % 4) * 4)
> #define MULTIXACT_MEMBER_SAFE_THRESHOLD		2147483647
> #define MULTIXACT_MEMBER_DANGER_THRESHOLD	3221225472

## 函数 RecordNewMultiXact  

RecordNewMultiXact 用于记录 multixact  

```
static void
RecordNewMultiXact(MultiXactId multi, MultiXactOffset offset,
				   int nmembers, MultiXactMember *members)
{
	pageno = MultiXactIdToOffsetPage(multi); // offset页面号
	entryno = MultiXactIdToOffsetEntry(multi); // offset入口号

	for (i = 0; i < nmembers; i++, offset++)
	{
		pageno = MXOffsetToMemberPage(offset); // member页面号
		memberoff = MXOffsetToMemberOffset(offset); // member偏移量
		flagsoff = MXOffsetToFlagsOffset(offset);  // flag偏移量
		bshift = MXOffsetToFlagsBitShift(offset);  // 设置flag的比特位偏移量
	}
}
```

## 环境  
centos-7.9  

## 测试  
进程1，先执行sql  
![image.png](https://foruda.gitee.com/images/1675847825822236548/624d986f_10017097.png)  
> t_infomask 402转换成16进制为0x192，
>     0x0100 表示HEAP_XMIN_COMMITTED
>     0x0090 表示 HEAP_XMAX_LOCK_ONLY | HEAP_XMAX_KEYSHR_LOCK
>     0x0002 表示 HEAP_HASVARWIDTH
> t_xmax 3128表示进程3128获得了该锁

进程2![image.png](https://foruda.gitee.com/images/1675847837024818810/1e2fa67b_10017097.png)  
> t_infomask 402转换成16进制为11d2，
>     0x1000 表示HEAP_XMAX_IS_MULTI
>     0x00d2表示 HEAP_XMAX_LOCK_ONLY | HEAP_XMAX_EXCL_LOCK | HEAP_XMAX_KEYSHR_LOCK
> t_xmax 5表示 multixact 5 获得了该锁

## 文件解读  
记录multixact的有两个文件，分别是member, offset  
member位于pg_multixact/members  
offset位于pg_multixact/offsets  

### 文件offset  
![image.png](https://foruda.gitee.com/images/1675848973934022760/6a185cce_10017097.png)  
该文件的最后一个offset是 0900 0000， 经过MXOffsetToMemberOffset计算，member偏移量48 bytes  
经过MXOffsetToFlagsOffset计算，flag偏移量40 bytes  
经过MXOffsetToFlagsBitShift计算, flag bit偏移 8 bit  

### 文件member  
![image.png](https://foruda.gitee.com/images/1675855342457664020/3f498cf4_10017097.png)  
由offset可知 0000 0100 2e0c 0000 380c 0000 398c 0000 为member内容  
2e0c 0000是上一条的事务号  
380c 0000是事务号3128  
398c 0000是事务号3129  
00 01分别对应3128、3129锁类型 MultiXactStatusForKeyShare、MultiXactStatusForShare  

## 参考资料  
[PG的multixact是做什么的](https://www.modb.pro/db/14939)  
