#pragma once
#ifndef _DATA_DEMO_H_
#define _DATA_DEMO_H_

#include "../Def.h"
#include "../Cmf.h"

extern const signed short* demoData;
enum { demoData_COUNT = 105 };


extern const signed short* frameData;
enum { frameData_COUNT = 162 };


//0:NPC �̸�
//1:�κ񿡼� x��ġ
//2:�κ񿡼� y��ġ
//3:�κ񿡼� �ٶ󺸴� ����

//4:������ �󼼺��⿡�� ���̴� ���ε���
//5:����Ʈ imgOffset x
//6:����Ʈ imgOffset y
//7:�⺻��� 
//8:�󼼺��� imgOffset x
//9	:�󼼺��� imgOffset y

extern const unsigned short* demoItem;
enum { demoItem_COUNT = 60 };
#endif