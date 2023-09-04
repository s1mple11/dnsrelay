#pragma once
#include "head.h"

//打印信息
void listTitle() {
	
	printf("DNS [Version 1.0] Build:May 2022\n");
	printf("小组成员:李子锋，刘爽，陆润东\n");
	printf("命令语法: dnsrelay [-d | -dd] [<dns-server>] [<db-file>]\n");
	printf("\n");
}

//读取命令及响应函数
void readParameters(int argc, char* argv[]) {
	bool setDNSFlag = false;
	bool setFilePath = false;
	if (argc > 1 && argv[1][0] == '-') {
		if (argv[1][1] == 'd')
			debugLevel = 1;
		if (argv[1][2] == 'd')
			debugLevel = 2;
	}

	if (argc > 2) {
		setDNSFlag = true;
		strcpy(outDNSServerIP, argv[2]);
	}

	if (argc > 3) {
		setFilePath = true;
		strcpy(filePath, argv[3]);
	}

	if (setDNSFlag)
		printf("设置上级DNS为:%s\n", outDNSServerIP);
	else
		printf("使用默认上级DNS:%s\n", outDNSServerIP);

	if (setFilePath)
		printf("设置本地缓存路径为:%s\n", filePath);
	else
		printf("使用默认本地缓存路径:%s\n", filePath);

	printf("Debug level : %d\n", debugLevel);
}

//读取本地ip-url映射表
void readIPURLReflectTable() {
	FILE* fp = NULL;
	if ((fp = fopen(filePath, "r+")) == NULL) {
		perror("FAIL TO READ!");
		exit(1);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", IPTable[CurrentTableNumber], URLTable[CurrentTableNumber]);
		if (debugLevel >= 2)
			printf("IP:%s->URL:%s\n", IPTable[CurrentTableNumber], URLTable[CurrentTableNumber]);
		CurrentTableNumber++;
		TotalTableNumber++;
	}
	if (debugLevel >= 0)
		printf("读取本地缓存成功\n");
	if (debugLevel >= 1)
		printf("读取本地缓存的行数为：%d\n", TotalTableNumber);

	fclose(fp);
}

void initTransferTable() {
	int i = 0;
	for (; i < MAX_ID_TARNSFER_TABLE_LENGTH; i++)
		isDone[i] = true;
}