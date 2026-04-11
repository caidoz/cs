#pragma once
// =============================================================
// AUTO GENERATED - DO NOT EDIT
// Source : Definitions.xlsx
// Sheet  : TimeConstants
// Date   : 2026-02-26 17:21
// =============================================================


// ---
#define EPOCH_YR                   1970                     // Unix 에포크 기준 연도
#define YEAR0                      1900                     // tm_year 기준 연도
#define SECS_DAY                   (24L * 60L * 60L)        // 하루 초 수

// ---
#define LEAPYEAR(year) (!((year) % 4) && (((year) % 100) || !((year) % 400))) // 윤년 판별
#define YEARSIZE(year) (LEAPYEAR(year) ? 366 : 365) // 연도 일수
#define FIRSTSUNDAY(timp) (((timp)->tm_yday - (timp)->tm_wday + 420) % 7) // 첫 번째 일요일
#define FIRSTDAYOF(timp) (((timp)->tm_wday - (timp)->tm_yday + 420) % 7) // 첫 번째 요일

// ---
