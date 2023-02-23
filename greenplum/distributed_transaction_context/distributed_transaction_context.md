## 环境和版本号  

### 操作系统  

> LSB Version:	:core-4.1-amd64:core-4.1-noarch  
> Distributor ID:	CentOS  
> Description:	CentOS Linux release 7.9.2009 (Core)  
> Release:	7.9.2009  
> Codename:	Core  

### 数据库版本号  

> greenplum-6.12  

## 处理过程  

### sql示例  

#### 表结构  

> insert into tbl_test1 select * from tbl_test2;  

### QD  

### QE writer  

#### 处理 DTX_PROTOCOL_COMMAND_PREPARE  

函数performDtxProtocolPrepare  

```
static void
performDtxProtocolPrepare(const char *gid)
{
	StartTransactionCommand();

	// CurrentTransactionState->blockState 变更为 TBLOCK_PREPARE
	PrepareTransactionBlock();

	// CurrentTransactionState->blockState 变更为 TBLOCK_DEFAULT
	CommitTransactionCommand();
	// 设置 DistributedTransactionContext 为 DTX_CONTEXT_QE_PREPARED
	setDistributedTransactionContext(DTX_CONTEXT_QE_PREPARED);
}
```

#### 处理 DTX_PROTOCOL_COMMAND_COMMIT_PREPARED  

函数 performDtxProtocolCommand  

```
void
performDtxProtocolCommand(DtxProtocolCommand dtxProtocolCommand,
						  const char *gid,
						  DtxContextInfo *contextInfo)
{
	switch (dtxProtocolCommand)
	{
	case DTX_PROTOCOL_COMMAND_ABORT_PREPARED:
		// 设置 DistributedTransactionContext 为 DTX_CONTEXT_QE_FINISH_PREPARED
		setDistributedTransactionContext(DTX_CONTEXT_QE_FINISH_PREPARED);
		performDtxProtocolAbortPrepared(gid, true);
		break;
	}
}
```

调用函数performDtxProtocolPrepare，设置 DistributedTransactionContext为 DTX_CONTEXT_QE_FINISH_PREPARED  
