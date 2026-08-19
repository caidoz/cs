#pragma once

#ifndef _DATA_COUNT_H_
#define _DATA_COUNT_H_

//=============================================================================
// 콘텐츠 개수 (런타임)
//
// Config/Capacity.h 의 CAP_* 가 "용량"이라면 여기 있는 값은 "개수"다.
// 지금 실제로 몬스터가 몇 종류인지는 팩이 정한다.
//
//     용량 : 컴파일 상수. ID 구간과 배열 크기를 잡는다. 안 바뀐다.
//     개수 : 런타임 값. 루프와 범위검사가 쓴다. 팩이 바꾼다.
//
// 팩이 없으면 내장 데이터의 개수(TOTALENEMY 등)가 그대로 들어 있다.
// 팩을 읽으면 팩 안 배열의 길이로 바뀐다.
//
// [쓰는 법]
//     for (i = 0; i < gTotalEnemy; i++)      //O
//     for (i = 0; i < TOTALENEMY; i++)       //X. 내장 개수에 묶인다
//     int table[CAP_ENEMY];                  //O. 배열 크기는 용량으로
//
// 언제나 gTotal* <= CAP_* 다. 로더가 그걸 보장한다.
//=============================================================================

extern int gTotalEnemy;
extern int gTotalCrew;
extern int gTotalSkill;
extern int gTotalCastle;
extern int gTotalMap;

//팩을 읽은 뒤 개수를 다시 잡는다. 팩이 없으면 내장 개수로 되돌린다.
void DataCountRefresh(void);

#endif
