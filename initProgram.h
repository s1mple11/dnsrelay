#pragma once
#include "head.h"

//��ӡ��Ϣ
void listTitle() {
	
	printf("DNS [Version 1.0] Build:May 2022\n");
	printf("С���Ա:���ӷ棬��ˬ��½��\n");
	printf("�����﷨: dnsrelay [-d | -dd] [<dns-server>] [<db-file>]\n");
	printf("\n");
}

//��ȡ�����Ӧ����
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
		printf("�����ϼ�DNSΪ:%s\n", outDNSServerIP);
	else
		printf("ʹ��Ĭ���ϼ�DNS:%s\n", outDNSServerIP);

	if (setFilePath)
		printf("���ñ��ػ���·��Ϊ:%s\n", filePath);
	else
		printf("ʹ��Ĭ�ϱ��ػ���·��:%s\n", filePath);

	printf("Debug level : %d\n", debugLevel);
}

//��ȡ����ip-urlӳ���
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
		printf("��ȡ���ػ���ɹ�\n");
	if (debugLevel >= 1)
		printf("��ȡ���ػ��������Ϊ��%d\n", TotalTableNumber);

	fclose(fp);
}

void initTransferTable() {
	int i = 0;
	for (; i < MAX_ID_TARNSFER_TABLE_LENGTH; i++)
		isDone[i] = true;
}