#include "Func.h"
#include "Data.h"

unsigned int SqrtX256(unsigned int n)
{
#define STEP(k)		\
	nr = m + r;			\
	r >>= 1;			\
	if (nr <= n) {		\
		n -= nr;			\
		r |= m;			\
	}

	unsigned int m = 0x40000000;
	unsigned int r = 0, nr;

	if (n > 65535)
		return 0;

	n <<= 16;

	STEP(15); m >>= 2;
	STEP(14); m >>= 2;
	STEP(13); m >>= 2;
	STEP(12); m >>= 2;
	STEP(11); m >>= 2;
	STEP(10); m >>= 2;
	STEP(9); m >>= 2;
	STEP(8); m >>= 2;
	STEP(7); m >>= 2;
	STEP(6); m >>= 2;
	STEP(5); m >>= 2;
	STEP(4); m >>= 2;
	STEP(3); m >>= 2;
	STEP(2); m >>= 2;
	STEP(1); m >>= 2;
	STEP(0);

	return (r);
}

int BC_mathSin1024(int degree)
{
	degree = (degree + 36000) % 360;

	switch (degree / 90) {
	case 0:
		return sin1024[degree % 90];
	case 1:
		return sin1024[90 - (degree % 90)];
	case 2:
		return -sin1024[degree % 90];
	default:
		return -sin1024[90 - (degree % 90)];
	}
}

int BC_mathCos1024(int degree)
{
	degree = (degree + 36000) % 360;

	switch (degree / 90) {
	case 3:
		return sin1024[degree % 90];
	case 0:
		return sin1024[90 - (degree % 90)];
	case 1:
		return -sin1024[degree % 90];
	default:
		return -sin1024[90 - (degree % 90)];
	}
}

int Random(int limit)
{
	int number;

	if (limit <= 0)
		limit = 1;

	number = cocos2d::RandomHelper::random_int(0, limit - 1);
	return number;
}

int GotoObjXY(OBJECT* pObj, int targetX, int targetY, int speed)
{
	int x = targetX - pObj->x;
	int y = targetY - pObj->y;
	int fr, dx;

	if (speed == 0)
		return 0;

	pObj->dirX = (x > 0) ? RIGHT : LEFT;
	pObj->dirY = (y > 0) ? DOWN : UP;

	if (Abs(y) < Abs(x)) {
		if (x)
			dx = Abs(y * 10 * speed / x);
		else
			dx = 0;

		dx = (dx % 10 > 4) ? dx / 10 + 1 : dx / 10;
		pObj->dx = (2 * pObj->dirX - 1) * speed;
		pObj->dy = (2 * pObj->dirY - 1) * dx;
		fr = Abs(x) / speed;
	}
	else {
		if (y)
			dx = Abs(x * 10 * speed / y);
		else
			dx = 0;

		dx = (dx % 10 > 4) ? dx / 10 + 1 : dx / 10;
		pObj->dx = (2 * pObj->dirX - 1) * dx;
		pObj->dy = (2 * pObj->dirY - 1) * speed;
		fr = Abs(y) / speed;
	}

	return fr;
}

int GotoObjZoom(OBJECT* target, OBJECT* pObj, int speed, int xPlus, int yPlus, float zoomInc, float zoomEnd)
{
	int x = target->x + xPlus - pObj->x;
	int y = target->y + yPlus - pObj->y;
	int fr, dx;
	int targetX = target->x + xPlus;
	int targetY = target->y + yPlus;

	pObj->zoom += zoomInc;

	if (zoomInc > 0 && pObj->zoom > zoomEnd)
		pObj->zoom = zoomEnd;

	if (zoomInc < 0 && pObj->zoom < zoomEnd)
		pObj->zoom = zoomEnd;

	if (speed == 0)
		return 0;

	pObj->dirX = pObj->dirF = (x > 0) ? RIGHT : LEFT;
	pObj->dirY = (y > 0) ? DOWN : UP;

	if (Abs(y) < Abs(x)) {
		if (x)
			dx = Abs(y * 10 * speed / x);
		else
			dx = 0;

		dx = (dx % 10 > 4 * _2X) ? dx / 10 + 1 * _2X : dx / 10;
		pObj->dx = (2 * pObj->dirX - 1) * speed * _2X;
		pObj->dy = (2 * pObj->dirY - 1) * dx * _2X;
		fr = Abs(x) / speed;
	}
	else {
		if (y)
			dx = Abs(x * 10 * speed / y);
		else
			dx = 0 * _2X;

		dx = (dx % 10 > 4 * _2X) ? dx / 10 + 1 * _2X : dx / 10;
		pObj->dx = (2 * pObj->dirX - 1) * dx * _2X;
		pObj->dy = (2 * pObj->dirY - 1) * speed * _2X;
		fr = Abs(y) / speed;
	}

	if (pObj->x < targetX && pObj->x + pObj->dx > targetX) {
		pObj->dx = targetX - pObj->x;
	}
	else if (pObj->x > targetX && pObj->x + pObj->dx < targetX) {
		pObj->dx = targetX - pObj->x;
	}

	if (pObj->y < targetY && pObj->y + pObj->dy > targetY) {
		pObj->dy = targetY - pObj->y;
	}
	else if (pObj->y > targetY && pObj->y + pObj->dy < targetY) {
		pObj->dy = targetY - pObj->y;
	}

	if (!(pObj->x == targetX && pObj->y == targetY)) {
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	return fr;
}

int GotoObj(OBJECT* target, OBJECT* pObj, int speed)
{
	int x = target->x - pObj->x;
	int y = target->y - pObj->y - (target->cy - pObj->cy) / 2;
	int fr, dx;

	if (speed == 0) {
		pObj->dx = 0;
		pObj->dy = 0;
		return 0;
	}

	pObj->dirX = (x > 0) ? RIGHT : LEFT;
	pObj->dirY = (y > 0) ? DOWN : UP;

	if (Abs(y) < Abs(x)) {
		if (x)
			dx = Abs(y * 10 * speed / x);
		else
			dx = 0;

		dx = (dx % 10 > 4) ? (dx / 10 + 1) : (dx / 10);
		pObj->dx = (2 * pObj->dirX - 1) * speed;
		pObj->dy = (2 * pObj->dirY - 1) * dx;
		fr = Abs(x) / speed;
	}
	else {
		if (y)
			dx = Abs(x * 10 * speed / y);
		else
			dx = 0 * _2X;

		dx = (dx % 10 > 4) ? dx / 10 + 1 : dx / 10;
		pObj->dx = (2 * pObj->dirX - 1) * dx;
		pObj->dy = (2 * pObj->dirY - 1) * speed;
		fr = Abs(y) / speed;
	}

	return fr;
}

int GotoPositionLog(int targetX, int targetY, int logIdx, int speed, int type)
{
	LOG* pObj;
	int x;
	int y;
	int fr, dx, dy;
	int MAXSPAN = 10;

	pObj = &gameLog[logIdx];
	x = targetX - pObj->x;
	y = targetY - pObj->y;

	pObj->targetX = targetX;
	pObj->targetY = targetY;

	if (speed == 0)
		return 0;

	pObj->dirX = (x > 0) ? RIGHT : LEFT;
	pObj->dirY = (y > 0) ? DOWN : UP;

	if (Abs(y) < Abs(x)) {
		if (x)
			dx = Abs(y * MAXSPAN * speed / x) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		pObj->dx = (2 * pObj->dirX - 1) * speed;
		pObj->dy = (2 * pObj->dirY - 1) * dx;
		fr = Abs(x) / speed;
	}
	else {
		if (y)
			dx = Abs(x * MAXSPAN * speed / y) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		pObj->dx = (2 * pObj->dirX - 1) * dx;
		pObj->dy = (2 * pObj->dirY - 1) * speed;
		fr = Abs(y) / speed;
	}

	if (pObj->x < targetX && pObj->x + pObj->dx > targetX) {
		pObj->dx = targetX - pObj->x;
	}
	else if (pObj->x > targetX && pObj->x + pObj->dx < targetX) {
		pObj->dx = targetX - pObj->x;
	}

	if (pObj->y < targetY && pObj->y + pObj->dy > targetY) {
		pObj->dy = targetY - pObj->y;
	}
	else if (pObj->y > targetY && pObj->y + pObj->dy < targetY) {
		pObj->dy = targetY - pObj->y;
	}

	if (!(pObj->x == targetX && pObj->y == targetY)) {
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	return fr;
}

int GotoPositionBar(BAR* barP, int targetX, int targetY, int speed)
{
	int x;
	int y;
	int fr, dx, dy;
	int MAXSPAN = 10;

	x = targetX - barP->x;
	y = targetY - barP->y;

	barP->targetX = targetX;
	barP->targetY = targetY;

	if (speed == 0)
		return 0;

	barP->dirX = (x > 0) ? RIGHT : LEFT;
	barP->dirY = (y > 0) ? DOWN : UP;

	if (Abs(y) < Abs(x)) {
		if (x)
			dx = Abs(y * MAXSPAN * speed / x) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		barP->dx = (2 * barP->dirX - 1) * speed;
		barP->dy = (2 * barP->dirY - 1) * dx;
		fr = Abs(x) / speed;
	}
	else {
		if (y)
			dx = Abs(x * MAXSPAN * speed / y) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		barP->dx = (2 * barP->dirX - 1) * dx;
		barP->dy = (2 * barP->dirY - 1) * speed;
		fr = Abs(y) / speed;
	}

	if (barP->x < targetX && barP->x + barP->dx > targetX) {
		barP->dx = targetX - barP->x;
	}
	else if (barP->x > targetX && barP->x + barP->dx < targetX) {
		barP->dx = targetX - barP->x;
	}

	if (barP->y < targetY && barP->y + barP->dy > targetY) {
		barP->dy = targetY - barP->y;
	}
	else if (barP->y > targetY && barP->y + barP->dy < targetY) {
		barP->dy = targetY - barP->y;
	}

	if (!(barP->x == targetX && barP->y == targetY)) {
		barP->x += barP->dx;
		barP->y += barP->dy;
	}

	return fr;
}

int GotoEventMenu(int targetX, int targetY, int eventMenuIdx, int speed, int type)
{
	GAMEEVENT* pObj;
	int x;
	int y;
	int fr, dx, dy;
	int MAXSPAN = 10;

	pObj = &robin.gameEvent[eventMenuIdx];
	x = targetX - pObj->x;
	y = targetY - pObj->y;

	pObj->targetX = targetX;
	pObj->targetY = targetY;

	if (speed < 1 * _2X)
		speed = 1 * _2X;

	pObj->dirX = (x > 0) ? RIGHT : LEFT;
	pObj->dirY = (y > 0) ? DOWN : UP;

	if (Abs(y) < Abs(x)) {
		if (x)
			dx = Abs(y * MAXSPAN * speed / x) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		pObj->dx = (2 * pObj->dirX - 1) * speed;
		pObj->dy = (2 * pObj->dirY - 1) * dx;
		fr = Abs(x) / speed;
	}
	else {
		if (y)
			dx = Abs(x * MAXSPAN * speed / y) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		pObj->dx = (2 * pObj->dirX - 1) * dx;
		pObj->dy = (2 * pObj->dirY - 1) * speed;
		fr = Abs(y) / speed;
	}

	if (pObj->x < targetX && pObj->x + pObj->dx > targetX) {
		pObj->dx = targetX - pObj->x;
	}
	else if (pObj->x > targetX && pObj->x + pObj->dx < targetX) {
		pObj->dx = targetX - pObj->x;
	}

	if (pObj->y < targetY && pObj->y + pObj->dy > targetY) {
		pObj->dy = targetY - pObj->y;
	}
	else if (pObj->y > targetY && pObj->y + pObj->dy < targetY) {
		pObj->dy = targetY - pObj->y;
	}

	if (!(pObj->x == targetX && pObj->y == targetY)) {
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	return fr;
}

int GotoPosition(int targetX, int targetY, int iconMarkIdx, int speed, int type)
{
	ICONMARK* pObj;
	int x;
	int y;
	int fr, dx, dy;
	int MAXSPAN = 10;

	switch (type) {
	case ICONMARK_CURRENCY:
		pObj = &currencyMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_CURRENCY_POPUP:
		pObj = &currencyMark_PopUp[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_ITEM:
		pObj = &itemMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_CARD:
		pObj = &cardMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_REWARD:
		pObj = &rewardMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_BOX:
		pObj = &boxMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_BOXCARD:
		pObj = &boxCardMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_SOUL:
		pObj = &soulMark;
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_GOLDALPHA:
		pObj = &goldAlphaMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	case ICONMARK_CONTROLMARK:
		pObj = &controlMark[iconMarkIdx];
		x = targetX - pObj->x;
		y = targetY - pObj->y;
		break;
	default:
		//모르는 마크 종류면 pObj/x/y가 안 잡힌다. 그대로 두면 아래에서
		//초기화도 안 된 포인터에 targetX를 써넣는다.
		return false;
	}

	pObj->targetX = targetX;
	pObj->targetY = targetY;

	if (speed < 1 * _2X)
		speed = 1 * _2X;

	pObj->dirX = (x > 0) ? RIGHT : LEFT;
	pObj->dirY = (y > 0) ? DOWN : UP;

	if (Abs(y) < Abs(x)) {
		if (x)
			dx = Abs(y * MAXSPAN * speed / x) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		pObj->dx = (2 * pObj->dirX - 1) * speed;
		pObj->dy = (2 * pObj->dirY - 1) * dx;
		fr = Abs(x) / speed;
	}
	else {
		if (y)
			dx = Abs(x * MAXSPAN * speed / y) * _2X;
		else
			dx = 0 * _2X;

		dx = (dx % MAXSPAN > (MAXSPAN / 2 - 1)) ? dx / MAXSPAN + 1 : dx / MAXSPAN;
		pObj->dx = (2 * pObj->dirX - 1) * dx;
		pObj->dy = (2 * pObj->dirY - 1) * speed;
		fr = Abs(y) / speed;
	}

	if (pObj->x < targetX && pObj->x + pObj->dx > targetX) {
		pObj->dx = targetX - pObj->x;
	}
	else if (pObj->x > targetX && pObj->x + pObj->dx < targetX) {
		pObj->dx = targetX - pObj->x;
	}

	if (pObj->y < targetY && pObj->y + pObj->dy > targetY) {
		pObj->dy = targetY - pObj->y;
	}
	else if (pObj->y > targetY && pObj->y + pObj->dy < targetY) {
		pObj->dy = targetY - pObj->y;
	}

	if (!(pObj->x == targetX && pObj->y == targetY)) {
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	return fr;
}

int Proc(const unsigned short* var, int value)
{
	int i, j;

	for (i = 0, j = Random(var[value]); i < value; i++) {
		if (j < var[i])
			break;
	}

	return i;
}

long long int RoundDiv(long long int num, long long int divider)
{
	if (divider == 0)
		return num;

	return ((num << 4) / divider + 8) >> 4;
}

long long int UpDiv(long long int num, long long int divider)
{
	return ((num << 4) / divider + 15) >> 4;
}

void SetBit(signed char* var, int idx)
{
	var[idx >> 3] = var[idx >> 3] | (0x01 << (7 - (idx & 0x07)));
}

int TriHeight(int x1, int y1, int x2, int y2, int xx, int yy)
{
	int a1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	int b1 = (x1 - xx) * (x1 - xx) + (y1 - yy) * (y1 - yy);
	int c1 = (x2 - xx) * (x2 - xx) + (y2 - yy) * (y2 - yy);
	int area = (x1 * (y2 - yy) + x2 * (yy - y1) + xx * (y1 - y2)) / 2;

	if (a1 == 0)
		return 0;

	if (a1 + b1 < c1 || a1 + c1 < b1 || ((4 * area * area) / a1) < 0)
		return 10000;

	if (area > 30000)
		return ((4 * (area / 100) * area) / (a1 / 100));
	else
		return ((4 * area * area) / a1);
}
