#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// ������Ϣ�ļ�
#define FILE_SPOT					"./Data/spot.txt"
// ·����Ϣ�ļ�
#define FILE_PATH					"./Data/path.txt"
// ������Ϣ�ļ�
#define FILE_ACTIVITY               "./Data/activity.txt"
// ѧ��ԤԼ��Ϣ�ļ�
#define FILE_BOOKING				"./Data/booking.txt"

// ԭ�������
#define ORI_X						23
#define ORI_Y						31

// �ַ�������
#define STR_LEN						0x20
#define DATA_LEN					0x200

// �ڽӾ����������
#define MAXINF						32767

// �Ӵ���
typedef enum _tagWndType
{
	WND_DETAIL,
	WND_NAV,
	WND_CLASSROOM,
	WND_COUNT									// �Ӵ�������

} WND_TYPE;

////////////////////////////////////////////
// ������Ϣ
typedef struct _tagNode
{
	int				nIndex;						// �������

	char			strName[STR_LEN];			// ��������
	char			strDescription[DATA_LEN];	// �������

	_tagNode()
	{
		nIndex = -1;
		memset(strName, 0, sizeof(strName));
		memset(strDescription, 0, sizeof(strDescription));
	}

} NODE, *LPNODE;

typedef vector<NODE>				NODES;

////////////////////////////////////////////
//	������Ϣ
typedef struct _tagActivity
{
	char			strID[STR_LEN];				// ����ID

	char			strContent[STR_LEN];		// �����
	char			strDate[STR_LEN];			// �ʱ��

	vector<int>		BookStudents;				// ԤԼ��ѧ��

	_tagActivity()
	{
		memset(strID, 0, sizeof(strID));
		memset(strContent, 0, sizeof(strContent));
		memset(strDate, 0, sizeof(strDate));
	}

} ACTIVITY, *LPACTIVITY;

typedef vector<ACTIVITY>			ACTIVITIES;