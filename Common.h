#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// 景点信息文件
#define FILE_SPOT					"./Data/spot.txt"
// 路径信息文件
#define FILE_PATH					"./Data/path.txt"
// 教室信息文件
#define FILE_ACTIVITY               "./Data/activity.txt"
// 学生预约信息文件
#define FILE_BOOKING				"./Data/booking.txt"

// 原点的坐标
#define ORI_X						23
#define ORI_Y						31

// 字符串长度
#define STR_LEN						0x20
#define DATA_LEN					0x200

// 邻接矩阵的最大距离
#define MAXINF						32767

// 子窗体
typedef enum _tagWndType
{
	WND_DETAIL,
	WND_NAV,
	WND_CLASSROOM,
	WND_COUNT									// 子窗体数量

} WND_TYPE;

////////////////////////////////////////////
// 景点信息
typedef struct _tagNode
{
	int				nIndex;						// 景点序号

	char			strName[STR_LEN];			// 景点名字
	char			strDescription[DATA_LEN];	// 景点介绍

	_tagNode()
	{
		nIndex = -1;
		memset(strName, 0, sizeof(strName));
		memset(strDescription, 0, sizeof(strDescription));
	}

} NODE, *LPNODE;

typedef vector<NODE>				NODES;

////////////////////////////////////////////
//	教室信息
typedef struct _tagActivity
{
	char			strID[STR_LEN];				// 教室ID

	char			strContent[STR_LEN];		// 活动内容
	char			strDate[STR_LEN];			// 活动时间

	vector<int>		BookStudents;				// 预约的学生

	_tagActivity()
	{
		memset(strID, 0, sizeof(strID));
		memset(strContent, 0, sizeof(strContent));
		memset(strDate, 0, sizeof(strDate));
	}

} ACTIVITY, *LPACTIVITY;

typedef vector<ACTIVITY>			ACTIVITIES;