#pragma once
#include "cocos2d.h"

#ifndef _FUNC_H_
#include "Func.h"
#endif

#ifndef _CORE_H_
#include "Core.h"
#endif

#ifndef _NET_H_
#include "Net.h"
#endif

#ifndef _TEXT_H_
#include "Text.h"
#endif

void GotoNetwork(int type)
{
	#ifdef GXGPLAYER
	//netOldDraw가 존재한다면 네트워크 에러 경고창 띄우기
	netOldDraw = drawHandle;
	return;
	#endif

	#ifdef LGT
	if (netLock) {
		NetError(1);
		netStatus = NETSTATUS_LOCK;

		return;
	}
	#endif

	is_key_pressed = false;
	systemKey = null;
	is_press_finished = true;

	Stop();

	mustRefresh = true;

	if (netStatus < NETSTATUS_CONNECTED)
		progress = 0;

	showNotice = 0;
	couponBilled = 0;

	nBuff_Screen = 0;

	if (type == NET_SAVE) {
		screenOffset = 0;
		DecryptFile(saveFileName[0], saveMem, sizeof(ROBINDATA) * 3);
		DecryptFile(saveFileName[1], backupMem, sizeof(GAMEDATA));
		DecryptFile(saveFileName[2], backupMem + sizeof(GAMEDATA), sizeof(OPTION));
	}
	else if (type == NET_SCREEN) {
		screenRemain = SCREENUPLOADSIZE;
		screenOffset = 0;
		nBuff_Screen = MC_knlCalloc(DX * DY * 2);
		memset(tempStr, 0, sizeof(tempStr));
		MC_knlSprintk(tempStr, "screen%d.dat", scC);
		ReadFile(tempStr, MC_GETDPTR(nBuff_Screen), DX * DY * 2);
	}

	MC_knlUnsetTimer(&ntimer);
	netType = type;
	SetData(netType);

	#ifdef SKT
	Connect();
	#else
	//if (bNetConnected) {
	//	if (bSockConnected) {
	//		netStatus = NETSTATUS_INIT;
	//		SendData();
	//	}
	//	else
	//		OpenSocket();
	//}
	//else
		Connect();
	#endif

	MC_knlSetTimer(&ntimer, 15000, (void *)null);

	#ifdef KNLPRINT
	MC_knlPrintk("타이머 15초 셋팅");
	#endif

	//readString(TEXT_NET_ERROR);
}

void Close(bool bConnected, bool bPPPClose)
{
	//	bConnected
	//소켓의 종료 이벤트(GXG_NET_CLOSED) 발생 여부
	//true : 등록되어진 콜백 함수(GXGCONCB)로 GXG_NET_CLOSED 이벤트 발생.
	//false : GXG_NET_CLOSED 이벤트 발생하지 않음.

	//	bPPPClose
	//PPP 연결 유지 여부
	//true : 소켓 종료 후 인터넷 연결을 종료시킨다.
	//false : 소켓 종료 후 인터넷 연결은 유지 시킨다.

	MC_knlUnsetTimer(&ntimer);

	#ifdef SKT
	gxgClose(bConnected, bPPPClose);
	#else

	//if (bConnected && bSockConnected) {
	if (bSockConnected) {
		#ifdef LGT
		MC_netSocketClose(sockFD);
		#else
		MC_netBillSocketClose(sockFD);
		#endif

		bSockConnected = false;
		sockFD = 0;
	}

	//if (bPPPClose && bNetConnected) {
	if (bNetConnected) {
		MC_netClose();
		bNetConnected = false;
	}
	#endif

	if (bPPPClose == false) {
		netStatus = NETSTATUS_CONNECTED;
		MC_knlSetTimer(&ntimer, 300000, (void *)&frame);
	}
	else
		netStatus = NETSTATUS_OFFLINE;

	if (nBuff_Screen) {
		MC_knlFree(nBuff_Screen);
		nBuff_Screen = 0;
	}

	//사운드 플레이
	#ifdef LGT
	if (drawHandle == MD_PLAY || drawHandle == MD_MARK || drawHandle == MD_ALERT || drawHandle == MD_SHOP || drawHandle == MD_MAP || drawHandle == MD_HELPTALK || drawHandle == MD_GUILD)
	#endif
	if (running == true) {
		if (drawHandle == MD_TITLEMENU) {
			if (bConnected == false || curMenu == 0 || menuDepth <= 2 || (curMenu == 3 && menuPage == 3))
				PlayMusic(M_TITLE);
		}
		else {
			//만일 길드전에
			if (bConnected == false || (
				!(drawHandle == MD_GUILD && curMenu == 5) &&	//길드전 랭킹화면 나올때
				!(drawHandle == MD_GAMEMENU && (menuDepth == 11 || menuDepth == 12)) &&	//게임메뉴 넷인벤토리 나올때
				!(drawHandle == MD_SHOP && shopType == SHOPTYPE_NET && menuDepth == 0) &&	//넷상점
				!(keyHandle == MK_ARENARANKING)	//투기장 랭킹
				)
			)
				TimerMusic();
		}
	}
}

void Connect()
{
	netStatus = NETSTATUS_CONNECT;

	// 연결을 시도합니다.
	// 서버로부터 응답 또는 에러 발생시 등록되어진 ConnectCB 콜백 함수를 호출하게 됩니다.
	#ifdef SKT
	gxgConnect((GXGCONCB)ConnectCB, GXG_GW_SERVER_ADDRESS, GXG_GW_SERVER_PORT, USE_DOMAIN, (void *)NULL);
	#else
	MC_netConnect((NETCONNECTCB)ConnectCB, NULL);
	#endif
}

void NetError(int err)
{
	#ifdef KNLPRINT
	MC_knlPrintk("Entering NetError\n");
	#endif

	if (nBuff_Send) {
		nDataLen = 0;
		MC_knlFree(nBuff_Send);
		nBuff_Send = 0;
	}

	if (err) {
		switch (netType) {
			default:
				if (drawHandle == MD_PLAY && robin.map >= ARENASTART && alert == ALERT_ARENARESULT)
					SetAlert(ALERT_NETFAIL);
				else
					menuResult = TEXT_NET_ERROR;
				break;
			//case NET_RANK:
			//	break;
			//case NET_SHOP:
			//	break;
			//case NET_INVEN:
				break;
			case NET_SAVE:
			case NET_LOAD:
				menuDepth = 11;
				break;
			case NET_SHOP_BUY:
			case NET_SHOP_COUPON:
				switch (chargeStatus) {
					default:
						menuResult = TEXT_NETWORK_BUYITEM_FAIL;
						break;
					case 2:
						menuResult = TEXT_NETWORK_RESURRECTION_FAIL;
						break;
					case 3:
						menuResult = TEXT_NET_ERROR;
						break;
					case 4:
						menuResult = TEXT_NETWORK_BUYSLOT_FAIL;
						break;
				}
				break;
			case NET_GAME_BUY:
				if (chargeStatus == 10)
					SetAlert(ALERT_NETFAIL);
				else
					menuResult = TEXT_NETWORK_BUYITEM_FAIL;
				break;
			case NET_SHOP_DOWNLOAD:
			case NET_INVEN_DOWNLOAD:
				menuResult = TEXT_NETWORK_GETITEM_FAIL;
				break;
			case NET_INVEN_UPLOAD:
				menuResult = TEXT_NETWORK_SENDITEM_FAIL;
				break;
			case NET_INVEN_PRESENTS:
				menuResult = TEXT_NETWORK_PRESENT_FAIL;
				break;
			case NET_SHOP_ERASE:
			case NET_INVEN_ERASE:
				menuResult = TEXT_NETWORK_ERASEITEM_FAIL;
				break;

			#ifdef DOWNLOAD
			case NET_FILE_DOWNLOAD:
				menuDepth = 2;
				menuResult = TEXT_NETWORK_FILE_FAIL;
				break;
			#endif

			#ifdef ASSA
			case NET_ASSA:
				menuDepth = (menuDepth < 5 || menuDepth == 9) ? 9 : 11;
				break;
			#endif

			#ifdef USERCHECK
			case NET_USER_CHECK:
				menuDepth = 2;
				menuResult = TEXT_NET_ERROR;
				break;
			#endif

			#ifdef EXPVERSION
			case NET_VERIFY:
				buy_Mode = 3;
				break;
			#endif
		}

		if (isScreenShot)
			isScreenShot = 11;
	}
	#ifdef ASSA
	else if (netType == NET_ASSA)
		menuDepth = (menuDepth < 5 || menuDepth == 9) ? 9 : 11;
	#endif

	//GetResultMsg(err);
	netStatus = NETSTATUS_ERROR;
	Close(true, true);
}

void SetData(int type)
{
	int i;

	if (nBuff_Send) {
		nDataLen = 0;
		MC_knlFree(nBuff_Send);
		nBuff_Send = 0;
	}

	switch (type) {
		case NET_RANK:
		case NET_GUILD_RANKING:
			nDataLen = sizeof(C2S_VIEWRANKING);
			break;
		case NET_RANK_REFRESH:
		case NET_RANK_ADD:
			nDataLen = sizeof(C2S_ADDRANKING);
			break;
		case NET_RANK_DETAIL:
			nDataLen = sizeof(C2S_DETAILRANKING);
			break;
		case NET_ARENA_NOTICE:
			nDataLen = sizeof(C2S_AGREE);
			break;
		case NET_SHOP:
		case NET_SHOPONLY:
		case NET_INVENTOSHOP:
			nDataLen = sizeof(C2S_SHOPINFO);
			break;
		case NET_INVEN:
		case NET_GUILD_START:
		case NET_GUILD_CURRENT:
		case NET_GUILD_REWARD:
		case NET_GUILD_RECORD:
			nDataLen = sizeof(C2S_INVENINFO);
			break;
		case NET_LOAD:
			nDataLen = sizeof(C2S_GETCHARACTOR);
			break;
		case NET_SAVE:
			if (screenOffset == 3)
				nDataLen = sizeof(GAMEDATA) + sizeof(OPTION) + 25;
			else
				nDataLen = sizeof(ROBINDATA) + 25;
			break;
		case NET_SCREEN:
			nDataLen = (screenRemain + 25);
			break;
		case NET_SHOP_BUY:
		case NET_GAME_BUY:
		case NET_STONE_ENCHANT:
		case NET_STONE_PROTECT:
		case NET_STONE_RECIPE:
		case NET_STONE_RESOLUTION:
		case NET_STONE_SOCKET:
			nDataLen = sizeof(C2S_BUYITEM);
			break;
		case NET_SHOP_DOWNLOAD:
		case NET_INVEN_DOWNLOAD:
			nDataLen = sizeof(C2S_GETITEM);
			break;
		case NET_INVEN_UPLOAD:
			nDataLen = sizeof(C2S_SENDITEM);
			break;
		case NET_INVEN_PRESENTS:
			nDataLen = sizeof(C2S_PRESENT);
			break;
		case NET_SHOP_ERASE:
		case NET_INVEN_ERASE:
			nDataLen = sizeof(C2S_ERASEITEM);
			break;
		case NET_SHOP_COUPON:
		case NET_SHOP_BUYSUCCESS:
		case NET_GAME_BUYSUCCESS:
			nDataLen = sizeof(C2S_BUYSUCCESS);
			break;
		case NET_SERVER_CLOSE:
			nDataLen = sizeof(C2S_SERVERCLOSE);
			break;
		case NET_AGREE:
			nDataLen = sizeof(C2S_AGREE);
			break;
		case NET_VERIFY:
			nDataLen = sizeof(C2S_VERIFY2);
			break;
		#ifdef USERCHECK
		case NET_USER_CHECK:
		#endif
			nDataLen = sizeof(C2S_VERIFY);
			break;
		#ifdef DOWNLOAD
		case NET_FILE_DOWNLOAD:
			nDataLen = sizeof(C2S_FILE);
			break;
		#endif
		#ifdef ASSA
		case NET_ASSA:
			nDataLen = 6;
			break;
		#endif
		case NET_DAILY_GETQUEST:
			nDataLen = sizeof(C2S_DAILYGET);
			break;
		case NET_DAILY_ENDQUEST:
			nDataLen = sizeof(C2S_NOTICE);
			break;
		case NET_RECOMMEND:
			nDataLen = sizeof(C2S_RECOMMEND);
			break;
	}

	nBuff_Send = MC_knlCalloc(nDataLen);

	#ifdef RELOCATE
	ReLocate();
	#endif

	//MC_GETDPTR(nBuff_Send) = MC_GETDPTR(nBuff_Send);
	memset(MC_GETDPTR(nBuff_Send), 0, nDataLen);

	//#ifdef SKT
	#ifdef ASSA
	//if (drawHandle != MD_BILLINFO)
	//	memcpy((char *)MC_GETDPTR(nBuff_Send) + 1, phone, 11);
	#else
	memcpy((char *)MC_GETDPTR(nBuff_Send) + 1, phone, 11);
	#endif
	//#else
	//sprintf((char *)MC_GETDPTR(nBuff_Send) + 1, "%d", nDataLen);
	//#endif

	switch (type) {
		default:
			{
				C2S_VIEWRANKING *data = (C2S_VIEWRANKING *)MC_GETDPTR(nBuff_Send);

				if (type == NET_GUILD_RANKING) {
					data->nCode = PTC_GUILDRANKING;
				}
				else {
					if (menuPage2 == 0)
						data->nCode = PTC_CHARRANKING;
					else
						data->nCode = PTC_ARENARANKING;
				}

				data->nRankStart = -1;

				//스킬
				for (i = 0; i < TOTALCHARSKILL; i++)
					data->nCharSkill[i] = GetSkillLv(robin.type * TOTALCHARSKILL + i);

				//저항
				for (i = 0; i < 5; i++)
					data->nCharRegist[i] = (unsigned char)robin.ps[PS_FIRE + i];

				//현재 호칭
				data->nCharCurTitle = game.currentTitle;

				//주인공 타입
				data->nCharType = robin.type;

				//레벨
				data->nCharLv = robin.lv;

				data->nCharHp = robin.ps[PS_HP];
				data->nCharMp = robin.ps[PS_MP];

				//접속 횟수
				data->nConnectCount = 0;

				//공격력
				data->nCharDamage = robin.ps[PS_DMG];

				//방어력
				data->nCharDefense = robin.ps[PS_ARMOR];

				//스탯
				data->nCharStr = robin.ps[PS_STR];
				data->nCharAgi = robin.ps[PS_AGI];
				data->nCharInt = robin.ps[PS_INT];
				data->nCharVit = robin.ps[PS_VIT];

				//골드
				data->nCharGold = (int)robin.gold;

				//점수
				data->nScore[0] = GetCharScore();
				data->nScore[1] = arenaScore;

				//장착 아이템
				for (i = 0; i < TOTALEQUIP; i++)
					data->costume[i] = robin.equip[i];

				//퀘스트
				for (i = 0, data->nCharQuest = 0; i < TOTALQUEST; i++) {
					if (robin.questStatus[i] % QUESTWORD == QUESTEND)
						data->nCharQuest++;
				}

				//호칭
				for (i = PLAYER_TITLE0, data->nCharTitle = 0; i < TOTAL_REPORT; i++) {
					if (game.report[i])
						data->nCharTitle++;
				}

				//달성도
				for (i = PLAYER_TITLE0, data->nCharReport = 0; i < TOTAL_REPORT; i++) {
					if (game.report[i])
						data->nCharReport++;
				}

				data->nGuild = robin.Guild;

				data->nVersion = VERSION;
			}
			break;
		case NET_RANK_REFRESH:
		case NET_RANK_ADD:
			{
				C2S_ADDRANKING *data = (C2S_ADDRANKING *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_RANKING_ADD;

				if (type == NET_RANK_REFRESH)
					data->rank = menuFocus - 1;
				else
					data->rank = scE3;

				if (drawHandle == MD_GUILD)
					data->type = 100;
				else
					data->type = menuPage2;

				data->nVersion = VERSION;
			}
			break;
		case NET_RANK_DETAIL:
			{
				C2S_DETAILRANKING *data = (C2S_DETAILRANKING *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_RANKING_DETAIL;
				data->userIdx = ranker[scC].userIdx;
				data->nVersion = VERSION;
			}
			break;
		case NET_ARENA_NOTICE:
			{
				C2S_AGREE *data = (C2S_AGREE *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_NOTICE_ARENA;
				data->nVersion = VERSION;
			}
			break;
		case NET_SHOP:
		case NET_SHOPONLY:
		case NET_INVENTOSHOP:
			{
				int j;
				C2S_SHOPINFO *data = (C2S_SHOPINFO *)MC_GETDPTR(nBuff_Send);

				switch (type) {
					case NET_SHOP:
						data->nCode = PTC_SHOPINFO;
						break;
					case NET_SHOPONLY:
						data->nCode = PTC_SHOPONLYINFO;
						break;
					case NET_INVENTOSHOP:
						data->nCode = PTC_INVENTOSHOP;
						break;
				}

				data->nType = menuPage2;
				data->nVersion = VERSION;

				for (i = 0; i < MAXNETSHOP; i++) {
					memset(&a.shop[i], 0, sizeof(ITEM));

					if (shopDesc[i]) {
						MC_knlFree(shopDesc[i]);
						shopDesc[i] = 0;
					}

					a.shop[i].type = 255;

					for (j = 0; j < 12; j++)
						a.shop[i].option[j][0] = 255;

					for (j = 0; j < 6; j++)
						a.shop[i].socket[j] = 255;
				}
			}
			break;
		case NET_INVEN:
			{
				C2S_INVENINFO *data = (C2S_INVENINFO *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_INVENINFO;
				data->nVersion = VERSION;
			}
			break;
		case NET_SAVE:
			{
				C2S_SENDCHARACTOR *data = (C2S_SENDCHARACTOR *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_SENDCHARACTOR;
				data->nVersion = VERSION;
				data->size = sizeof(ROBINDATA);
				data->index = screenOffset;

				switch (screenOffset) {
					case 0:
						memcpy(data->data, saveMem, sizeof(ROBINDATA));
						break;
					case 1:
						memcpy(data->data, saveMem + sizeof(ROBINDATA), sizeof(ROBINDATA));
						break;
					case 2:
						memcpy(data->data, saveMem + sizeof(ROBINDATA) * 2, sizeof(ROBINDATA));
						break;
					case 3:
						data->size = sizeof(GAMEDATA) + sizeof(OPTION);
						memcpy(data->data, backupMem, sizeof(GAMEDATA) + sizeof(OPTION));
						break;
				}
			}
			break;
		case NET_LOAD:
			{
				C2S_GETCHARACTOR *data = (C2S_GETCHARACTOR *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_GETCHARACTOR;
				data->size = sizeof(CHARSAVE);
				data->nVersion = VERSION;
			}
			break;
		case NET_SHOP_BUY:
			{
				C2S_BUYITEM *data = (C2S_BUYITEM *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_BUYITEM;

				switch (chargeStatus) {
					case 0:
						data->index = a.shop[scS3 * 4 + menuFocus].id;
						break;
					case 1:
						data->index = 409;
						break;
					case 2:
						data->index = 429;
						break;
					case 4:
						data->index = 428;
						break;
				}

				data->nVersion = VERSION;
			}
			break;
		case NET_STONE_ENCHANT:
		case NET_STONE_PROTECT:
		case NET_STONE_RECIPE:
		case NET_STONE_RESOLUTION:
		case NET_STONE_SOCKET:
			{
				C2S_BUYITEM *data = (C2S_BUYITEM *)MC_GETDPTR(nBuff_Send);

				chargeStatus = type - NET_STONE_ENCHANT + 5;
				data->nCode = PTC_QUICKBUYITEM;
				data->index = 401 + type - NET_STONE_ENCHANT + ITEM_NET_ENCHANT;
				data->nVersion = VERSION;
			}
			break;
		case NET_SHOP_COUPON:
			{
				C2S_BUYSUCCESS *data = (C2S_BUYSUCCESS *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_BUYSUCCESS;

				data->index = a.shop[scS3 * 4 + menuFocus].id;
				data->id = MakeItemId();
				data->type = 1;
				data->nVersion = VERSION;
			}
			break;
		case NET_GAME_BUY:
			{
				C2S_BUYITEM *data = (C2S_BUYITEM *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_QUICKBUYITEM;

				if (chargeStatus == 10) {
					data->index = 430;
				}
				else {
					if (shopType == SHOPTYPE_QUICK)
						data->index = 300 + a.shop[scS3 * 4 + menuFocus - 100].id;
					else
						data->index = a.shop[scS3 * 4 + menuFocus - 100].id;
				}

				data->nVersion = VERSION;
			}
			break;
		case NET_SHOP_DOWNLOAD:
			{
				C2S_GETITEM *data = (C2S_GETITEM *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_GETITEMATSHOP;
				data->nIndex = NetItemData[scS2 * 4 + menuFocus - 100].idx;
				data->nVersion = VERSION;
			}
			break;
		case NET_INVEN_DOWNLOAD:
			{
				C2S_GETITEM *data = (C2S_GETITEM *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_GETITEM;
				data->nIndex = NetItemData[scS2 * 4 + menuFocus].idx;
				data->nVersion = VERSION;
			}
			break;
		case NET_INVEN_UPLOAD:
			{
				C2S_SENDITEM *data = (C2S_SENDITEM *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_SENDITEM;
				data->nVersion = VERSION;

				if (scC == scT - 1) {
					//골드인 경우
					memset(&tempItem, 0, sizeof(ITEM));

					tempItem.lv = 1;
					tempItem.icon = ITEM_GOLD_ICON;
					tempItem.type = ITEM_GOLD;
					tempItem.gold= 1;
					tempItem.count = menuItemCount;
					tempItem.id= MakeItemId();

					for (i = 0; i < 6; i++) {
						tempItem.socket[i] = 255;
						tempItem.option[i * 2][0] = 255;
						tempItem.option[i * 2 + 1][0] = 255;
					}

					ReadString(TEXT_ITEMNAME_GOLD);
					MC_knlSprintk(tempItem.name, TEXTPTR(TEXT_ITEMNAME_GOLD), menuItemCount);
					TextFree(TEXT_ITEMNAME_GOLD);

					memcpy(&data->item, &tempItem, sizeof(ITEM));
				}
				else {
					ITEM *it = &robin.inven[scS * 4 + menuFocus - 100];

					memcpy(&tempItem, it, sizeof(ITEM));

					switch (it->type) {
						case ITEM_WASTE:
						case ITEM_IRON:
						case ITEM_LEATHER:
						case ITEM_CLOTH:
						case ITEM_WOOD:
						case ITEM_ESSENCE:
						case ITEM_NETITEM:
							if (it->count > 1 && menuItemCount < it->count) {
								tempItem.count = menuItemCount;
								tempItem.id++;
							}
							break;
					}

					memcpy(&data->item, &tempItem, sizeof(ITEM));
				}
			}
			break;
		case NET_INVEN_PRESENTS:
			{
				C2S_PRESENT *data = (C2S_PRESENT *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_PRESENT;
				data->nIndex = NetItemData[scS2 * 4 + menuFocus].idx;
				memcpy(data->nPhone, dmgStr, menuCount);
				data->nVersion = VERSION;
			}
			break;
		case NET_SHOP_ERASE:
		case NET_INVEN_ERASE:
			{
				C2S_ERASEITEM *data = (C2S_ERASEITEM *)MC_GETDPTR(nBuff_Send);
				data->nCode = (type == NET_INVEN_ERASE) ? PTC_ERASEITEM : PTC_ERASEITEMATSHOP;
				data->nCount = eraseCnt;
				memcpy(data->eIndex, needErase, sizeof(needErase));
				data->nVersion = VERSION;
			}
			break;
		case NET_SHOP_BUYSUCCESS:
			{
				C2S_BUYSUCCESS *data = (C2S_BUYSUCCESS *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_BUYSUCCESS;

				switch (chargeStatus) {
					case 0:
						data->index = a.shop[scS3 * 4 + menuFocus].id;

						if (a.shop[scS3 * 4 + menuFocus].broken)
							data->id = MakeItemId();
						break;
					case 1:
						data->index = 409;
						break;
					case 2:
						data->index = 429;
						break;
					case 4:
						data->index = 428;
						break;
					default:
						break;
				}

				data->type = 0;
				data->nVersion = VERSION;
			}
			break;
		case NET_GAME_BUYSUCCESS:
			{
				C2S_BUYSUCCESS *data = (C2S_BUYSUCCESS *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_QUICKBUYSUCCESS;

				if (chargeStatus == 10)
					data->index = 430;
				else if (chargeStatus >= 5)
					data->index = 401 + chargeStatus - 5 + ITEM_NET_ENCHANT;
				else if (shopType == SHOPTYPE_QUICK)
					data->index = 300 + a.shop[scS3 * 4 + menuFocus - 100].id;
				else
					data->index = a.shop[scS3 * 4 + menuFocus - 100].id;

				data->type = 0;
				data->nVersion = VERSION;
			}
			break;
		case NET_SERVER_CLOSE:
			{
				C2S_SERVERCLOSE *data = (C2S_SERVERCLOSE *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_SERVERCLOSE;
				data->nVersion = VERSION;
			}
			break;
		case NET_AGREE:
			{
				C2S_AGREE *data = (C2S_AGREE *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_AGREE;
				data->nVersion = VERSION;
			}
			break;
		case NET_VERIFY:
			{
				C2S_VERIFY2 *data = (C2S_VERIFY2 *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_VERIFY;

				#ifdef EXP_GXG
				data->nType = VERIFY_GXG;
				#elif defined EXP_NATE
				data->nType = VERIFY_NATE;
				#elif defined EXP_NHN
				data->nType = VERIFY_NHN;
				#elif defined EXP_DAUM
				data->nType = VERIFY_DAUM;
				#else
				data->nType = VERIFY_NORMAL;
				#endif

				data->nVersion = VERSION;
				chargeStatus = 3;
			}
			break;
		case NET_SCREEN:
			{
				C2S_SCREENSHOT *data = (C2S_SCREENSHOT *)MC_GETDPTR(nBuff_Send);

				screenRemain = Min(SCREENUPLOADSIZE, DX * DY * 2 - screenOffset);

				data->nCode = PTC_SCREENSHOT;
				data->dx = DX;
				data->dy = DY;
				data->size = screenRemain;
				data->nVersion = VERSION;

				memcpy((char*)data->data, (char *)MC_GETDPTR(nBuff_Screen) + screenOffset, screenRemain);

				MC_knlSprintk(tempStr, "업로드중 : %d%%", screenOffset * 100 / (DX * DY * 2));

				screenOffset += screenRemain;
			}
			break;
		#ifdef DOWNLOAD
		case NET_FILE_DOWNLOAD:
			{
				C2S_FILE *data = (C2S_FILE *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_FILE;
				data->nIndex = curFile;
				data->nVersion = VERSION;
			}
			break;
		#endif
		#ifdef ASSA
		case NET_ASSA:
			{
				ASSA_OUT_DATA *data = (ASSA_OUT_DATA *)MC_GETDPTR(nBuff_Send);

				data->command = MC_utilHtons(menuDepth < 5 ? 0x0003 : 0x0001);
				data->length = MC_utilHtons(6);
				data->data = MC_utilHtons(16);
			}
			break;
		#endif
		case NET_DAILY_GETQUEST:
			{
				C2S_DAILYGET *data = (C2S_DAILYGET *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_DAILYGET;
				data->nVersion = VERSION;
				memcpy(data->demoSeen, robin.demoSeen, sizeof(data->demoSeen));
			}
			break;
		case NET_DAILY_ENDQUEST:
			{
				C2S_DAILYEND *data = (C2S_DAILYEND *)MC_GETDPTR(nBuff_Send);

				data->nCode = PTC_DAILYEND;
				data->nVersion = VERSION;
				data->guildNum = robin.Guild;
				data->questIndex = robin.guildQuestIndex;
			}
			break;
		case NET_GUILD_START:
			{
				C2S_INVENINFO *data = (C2S_INVENINFO *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_GUILDSTART;
				data->nVersion = VERSION;
			}
			break;
		case NET_GUILD_CURRENT:
			{
				C2S_INVENINFO *data = (C2S_INVENINFO *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_GUILDCURRENT;
				data->nVersion = VERSION;
			}
			break;
		case NET_GUILD_REWARD:
			{
				C2S_INVENINFO *data = (C2S_INVENINFO *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_GUILDREWARD;
				data->nVersion = VERSION;
			}
			break;
		case NET_GUILD_RECORD:
			{
				C2S_INVENINFO *data = (C2S_INVENINFO *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_GUILDRECORD;
				data->nVersion = VERSION;
			}
			break;
		#ifdef USERCHECK
		case NET_USER_CHECK:
			{
				C2S_VERIFY *data = (C2S_VERIFY *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_USERCHECK;
				data->nVersion = VERSION;
			}
			break;
		#endif
		case NET_RECOMMEND:
			{
				C2S_RECOMMEND *data = (C2S_RECOMMEND *)MC_GETDPTR(nBuff_Send);
				data->nCode = PTC_RECOMMEND;
				data->nVersion = VERSION;
				memcpy(data->receiver, dmgStr, 11);
				data->receiver[11] = menuCur;
			}

			nDataLen = sizeof(C2S_RECOMMEND);
			break;
	}
}

void SendData()
{
	if (netStatus != NETSTATUS_INIT)
		return;

	MC_knlUnsetTimer(&ntimer);
	MC_knlSetTimer(&ntimer, 15000, (void *)null);

	#ifdef SKT
	netStatus = NETSTATUS_SEND;

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:Send Data!\n");
	#endif

	gxgSendData(MC_GETDPTR(nBuff_Send), nDataLen);
	#else
	netStatus = NETSTATUS_SEND;

	netFrame = 0;

	if (SendPacket() < 0) {

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:Send Failed!\n");
		#endif

		netStatus = NETSTATUS_ERROR;
		NetError(1);
	}
	#endif
}

void SetNetInventory(char *data)
{
	int i, j;

	for (i = 0; i < MAXNETINVEN; i++) {
		memset(&a.shop[i + NETINVENSTART], 0, sizeof(ITEM));

		a.shop[i + NETINVENSTART].type = 255;

		for (j = 0; j < 12; j++)
			a.shop[i + NETINVENSTART].option[j][0] = 255;

		for (j = 0; j < 6; j++)
			a.shop[i + NETINVENSTART].socket[j] = 255;

		if (i < nInvenCnt) {
			ServerItem *item = (ServerItem *)(data + sizeof(ServerItem) * i);

			NetItemData[i].idx = item->idx;
			memcpy(NetItemData[i].phone, &item->uploader, 4);
			a.shop[i + NETINVENSTART].count = item->count;
			a.shop[i + NETINVENSTART].value= item->value;
			a.shop[i + NETINVENSTART].id = item->id;
			a.shop[i + NETINVENSTART].gold = item->gold;
			a.shop[i + NETINVENSTART].set = item->set;

			memcpy(NetItemData[i].date, item->date, 4);

			a.shop[i + NETINVENSTART].lv = item->lv;
			a.shop[i + NETINVENSTART].requireLv = item->requireLv;
			a.shop[i + NETINVENSTART].requireStat= item->requireStat;
			memcpy(a.shop[i + NETINVENSTART].name, item->name, 40);
			a.shop[i + NETINVENSTART].icon = item->icon;
			a.shop[i + NETINVENSTART].type = item->type;
			a.shop[i + NETINVENSTART].detail = item->detail;
			a.shop[i + NETINVENSTART].grade = item->grade;
			a.shop[i + NETINVENSTART].broken= item->broken;
			a.shop[i + NETINVENSTART].cooldown = item->cooldown;
			memcpy(a.shop[i + NETINVENSTART].socket, item->socket, 6);
			memcpy(a.shop[i + NETINVENSTART].option, item->option, 24);

			#ifdef KNLPRINT
			MC_knlPrintk("디버그:%s, %s\n", NetItemData[i].phone, NetItemData[i].date);
			#endif
		}
	}
}

int SetNetShop(char *data)
{
	int i, j, offset = 0;

	for (i = 0; i < MAXNETSHOP; i++) {
		memset(&a.shop[i], 0, sizeof(ITEM));

		if (shopDesc[i]) {
			MC_knlFree(shopDesc[i]);
			shopDesc[i] = 0;
		}

		a.shop[i].type = 255;

		for (j = 0; j < 12; j++)
			a.shop[i].option[j][0] = 255;

		for (j = 0; j < 6; j++)
			a.shop[i].socket[j] = 255;

		if (i < nShopCnt) {
			ShopItem *item = (ShopItem *)(data + offset);

			while (drawHandle == MD_SHOP && item->type == ITEM_NETITEM && (item->detail == ITEM_NET_CHARACTER || item->detail == ITEM_NET_NETBAG)) {
				offset += item->length;
				nShopCnt--;
				item = (ShopItem *)(data + offset);
			}

			#ifdef LGT
			if (item->value == 800) {
				offset += item->length;
				nShopCnt--;
				item = (ShopItem *)(data + offset);
			}
			#endif

			a.shop[i].id = item->index;
			a.shop[i].icon = item->icon;
			a.shop[i].value = item->value;
			a.shop[i].lv = item->shop;
			a.shop[i].gold = item->coupon;
			a.shop[i].type = item->type;
			a.shop[i].detail = item->detail;
			a.shop[i].grade = item->grade;
			a.shop[i].count = item->count;
			a.shop[i].broken= item->broken;
			a.shop[i].cooldown = item->sale;
			a.shop[i].requireLv = item->hot;
			memcpy(a.shop[i].name, item->name, 20);

			if (item->length > 36) {
				shopDesc[i] = MC_knlCalloc(item->length - 35);
				#ifdef RELOCATE
				ReLocate();
				#endif
				memcpy(MC_GETDPTR(shopDesc[i]), item->desc, item->length - 36);
			}

			offset += item->length;
		}
	}

	return offset;
}

void ReceiveData()
{
	#ifdef KNLPRINT
	MC_knlPrintk("Receiving Data Allocation\n");
	#endif

	MC_knlUnsetTimer(&ntimer);
	MC_knlSetTimer(&ntimer, 15000, (void *)null);

	if (nBuff_Send) {
		nDataLen = 0;
		MC_knlFree(nBuff_Send);
		nBuff_Send = 0;
	}

	if (nBuff_Recv) {
		nDataLen = 0;
		MC_knlFree(nBuff_Recv);
		nBuff_Recv = 0;
	}

	switch (netType) {
		default:
			nDataLen = sizeof(S2C_VIEWRANKING) + 255;
			break;
		case NET_RANK_DETAIL:
			nDataLen = sizeof(S2C_DETAILRANKING);
			break;
		case NET_ARENA_NOTICE:
			nDataLen = sizeof(S2C_NOTICE) + 1;
			break;
		case NET_SHOP:
			nDataLen = sizeof(S2C_SHOPINFO) + 255;
			break;
		case NET_SHOPONLY:
		case NET_INVENTOSHOP:
			nDataLen = sizeof(S2C_SHOPONLYINFO);
			break;
		case NET_INVEN:
			nDataLen = sizeof(S2C_INVENINFO) + 255;
			break;
		case NET_SHOP_COUPON:
			if (couponBilled == 0) {
				temp = GetInvenIdx(ITEM_NETITEM, ITEM_NET_COUPON, GRADE_NORMAL);

				robin.inven[temp].count -= a.shop[scS3 * 4 + menuFocus].gold;

				if (robin.inven[temp].count == 0)
					EraseItem(ITEMPTR_INVEN + temp);

				couponBilled = 1;
				SaveFlag(0);
			}
		case NET_SHOP_BUY:
		case NET_INVEN_ERASE:
			nDataLen = sizeof(S2C_INVENINFO);
			break;
		case NET_SAVE:
			nDataLen = sizeof(S2C_SENDCHARACTOR);
			break;
		case NET_LOAD:
			nDataLen = sizeof(CHARSAVE) + 5;
			break;
		case NET_INVEN_DOWNLOAD:
			nDataLen = sizeof(S2C_GETITEM);
			break;
		case NET_INVEN_UPLOAD:
			nDataLen = sizeof(S2C_SENDITEM);

			//여기서 아이템을 삭제해준다.
			if (scC == scT - 1) {
				//골드인 경우
				robin.gold -= menuItemCount * 1000;
				SaveFlag(0);
			}
			else {
				ITEM *it = &robin.inven[scS * 4 + menuFocus - 100];

				switch (it->type) {
					case ITEM_WASTE:
					case ITEM_IRON:
					case ITEM_LEATHER:
					case ITEM_CLOTH:
					case ITEM_WOOD:
					case ITEM_ESSENCE:
					case ITEM_NETITEM:
						if (it->count > 1 && menuItemCount < it->count) {
							it->count -= menuItemCount;
							QuestItemCheck(it->type, it->detail, 0);
							break;
						}
					default:
						EraseItem(scS * 4 + menuFocus - 100);
						break;
				}

				scT = Max((drawHandle == MD_GAMEMENU ? 5 : 6), (robin.count + 3) / 4 + 1);

				SaveFlag(0);
			}
			break;
		case NET_INVEN_PRESENTS:
			nDataLen = sizeof(S2C_PRESENT);
			break;
		case NET_AGREE:
			nDataLen = sizeof(S2C_AGREE);
			break;
		case NET_VERIFY:
			nDataLen = sizeof(S2C_VERIFY);
			break;
		case NET_SCREEN:
			nDataLen = sizeof(S2C_SCREENSHOT);
			break;
		case NET_STONE_ENCHANT:
		case NET_STONE_PROTECT:
		case NET_STONE_RECIPE:
		case NET_STONE_RESOLUTION:
		case NET_STONE_SOCKET:
			nDataLen = sizeof(S2C_BUYITEM);
			break;

		#ifdef DOWNLOAD
		case NET_FILE_DOWNLOAD:
			nDataLen = downFileSize[curFile];
			break;
		#endif

		#ifdef ASSA
		case NET_ASSA:
			nDataLen = (menuDepth < 5 ? 5 : 905);
			break;
		#endif

		case NET_DAILY_GETQUEST:
			nDataLen = sizeof(S2C_DAILYGET);
			break;
		case NET_DAILY_ENDQUEST:
		case NET_GUILD_REWARD:
		#ifdef USERCHECK
		case NET_USER_CHECK:
		#endif
			nDataLen = sizeof(S2C_SERVERCLOSE);
			break;
		case NET_GUILD_START:
			nDataLen = sizeof(S2C_GUILDSTART) + 255;
			break;
		case NET_GUILD_CURRENT:
			nDataLen = sizeof(S2C_GUILDCURRENT) + 255;
			break;
		case NET_GUILD_RECORD:
			nDataLen = sizeof(S2C_GUILDRECORD) + 255;
			break;
		case NET_RECOMMEND:
			nDataLen = sizeof(S2C_RECOMMEND) + 255;
			break;
	}

	nDataLen += 1024;

	nBuff_Recv = MC_knlCalloc(nDataLen);
	#ifdef RELOCATE
	ReLocate();
	#endif
	//MC_GETDPTR(nBuff_Recv) = MC_GETDPTR(nBuff_Recv);
	memset(MC_GETDPTR(nBuff_Recv), 0, nDataLen);

	netStatus = NETSTATUS_RECEIVE;

	#ifdef SKT
	gxgReceiveData(MC_GETDPTR(nBuff_Recv));
	#else

	#ifdef KNLPRINT
	MC_knlPrintk("Try to Receive Data\n");
	#endif

	net_RemainSize = nDataLen;
	netFrame = 0;
	net_Offset = 0;
	size_recevied = 0;

	if (RecvPacket0(0) < 0) {
		netStatus = NETSTATUS_ERROR;
		NetError(1);
	}
	#endif
}

void SendErase(void)
{
	eraseCnt = EraseCopyItem();

	//if (eraseCnt) {
	//	char *sPkt;

	//	menuDepth = 4;
	//	SetData(NET_INVEN_ERASE);
	//	netStatus = NETSTATUS_INIT;
	//	sPkt = MC_GETDPTR(nBuff_Send);
	//	sPkt[0] = PTC_ERASECOPYITEM;
	//	SendData();
	//	MC_knlUnsetTimer(&ntimer);
	//	MC_knlSetTimer(&ntimer, 15000, (void *)null);
	//}
	//else {
		SetData(NET_SERVER_CLOSE);
		netStatus = NETSTATUS_INIT;
		SendData();
		MC_knlUnsetTimer(&ntimer);
		MC_knlSetTimer(&ntimer, 300000, (void *)&frame);
	//}
}

void ResultData_Ranking(unsigned char *rPkt)
{
	menuCur = 0;

	{
		int i;
		S2C_VIEWRANKING *rankData = (S2C_VIEWRANKING *)MC_GETDPTR(nBuff_Recv);

		memcpy(&ranker[0], &rankData->ranker[0], sizeof(RANKDEFAULT) * 10);

		if (showNotice) {
			memset(tempStr2, 0, sizeof(tempStr2));
			memcpy(tempStr2, &rPkt[417], rPkt[416]);
		}

		for (i = 0; i < 10; i++) {
			if (rankData->ranker[i].nCharLv == 0)
				break;

			//전화번호 텍스트 합성
			memset(phoneStr[i], 0, 8);
			memcpy(&phoneStr[i][1], rankData->ranker[i].phone, 4);
			phoneStr[i][0] = '~';

			//호칭 텍스트 합성
			SetTitleString(rankData->ranker[i].nCharType, rankData->ranker[i].nCharCurTitle, optionStr[i]);
		}

		scT = i;
		menuDepth = 3;

		if (scT == 0) {
			menuResult = TEXT_NORANKER;
			//curMenu = 0;
			//scC = 4;
		}
		else {
			memcpy(optionStr[11], equipImg, TOTALEQUIP);

			memcpy(equipImg, optionStr[11], TOTALEQUIP);
			scS3 = rankData->startRank;
			scC3 = rankData->myRank;
			scT3 = rankData->endRank;

			//달성도 체크 : 공신,원로,장(길드전에서 1등)
			if (rPkt[0] == PTS_GUILDRANKING && scC3 == 0)
				ReportCheck(PLAYER_TITLE0, 0);

			scC = 0;
			scS = 0;
			scE = scP = Min(scT, 3);
			scC2 = 0;

			if (netType == NET_RANK_ADD) {
				if (scS3 < scP3) {
					//위로 올린 경우
					scE = Max(3, Min(scP3 - 1, scT));
					scC = Min(scP3 - 1 - scS3, scE - 1);
				}
				else {
					//아래로 내린 경우
					scE = Min(scT, scP3 + 10 - scS3 + 3);
					scC = Max(scP3 + 10 - scS3, 0);
				}

				scS = scE - 3;
			}
			else {
				//내랭킹인 경우의 위치
				if (menuFocus == 0) {
					scC = rankData->myRank - rankData->startRank;
					scE = Min((scC == 0 ? 3 : scC + 2), scT);
					scS = (scP > scE ? 0 : scE - scP);
				}
			}

			if (scC >= scT)
				scC = scT - 1;

			imgLoaded = 0;
			////첫 세명 코스튬 입력
			//for (i = scS; i < scE; i++) {
			//	costumeImg[(i % 3) + 1] = (unsigned char)rankData->ranker[i].nCharType;
			//	ao[(i % 3) + 1].type = (i % 3) + 1;
			//	ao[(i % 3) + 1].cmf = costumeImg[(i % 3) + 1];

			//	memcpy(equipImg, rankData->ranker[i].nCharCos, TOTALEQUIP);

			//	for (j = 0; j < ROBIN_IMG_CNT; j++)
			//		LoadImg(DIANA_PART_IMG + (i % 3) * ROBIN_IMG_CNT + j);
			//}

			if (drawHandle == MD_GUILD)
				curMenu = 5;
			else if (drawHandle == MD_PLAY) {
				menuPage2 = 1;
				alert = ALERT_ARENARANKING;
				drawHandle = MD_ALERT;
				keyHandle = MK_ARENARANKING;
			}
		}
	}

	if (rPkt[0] == PTS_NOTICE_ARENA)
		Close(true, true);
	else
		Close(false, false);
}

void ResultData_RankingDetail(void)
{
	S2C_DETAILRANKING *detailData = (S2C_DETAILRANKING *)MC_GETDPTR(nBuff_Recv);

	memcpy(&rankerDetail, &detailData->ranker, sizeof(RANKDETAIL));
	Close(false, false);
	menuDepth = 4;
}

void ResultData_SendCharacter(void)
{
	S2C_SENDCHARACTOR *charData = (S2C_SENDCHARACTOR *)MC_GETDPTR(nBuff_Recv);

	if (charData->nResult == 125) {
		menuDepth = 6;
		MC_fsRemove(saveFileName[0], MC_DIR_PRIVATE_ACCESS);
		MC_fsRemove(saveFileName[1], MC_DIR_PRIVATE_ACCESS);
		MC_fsRemove(saveFileName[2], MC_DIR_PRIVATE_ACCESS);
	}
	else
		menuDepth = 11;

	Close(true, true);
}

void ResultData_GetCharacter(unsigned char *rPkt)
{
	S2C_GETCHARACTOR *charData = (S2C_GETCHARACTOR *)MC_GETDPTR(nBuff_Recv);

	switch (charData->nResult) {
		case 0:
			menuDepth = 11;
			break;
		case 1:
			menuDepth = 12;
			break;
		case 2:
			memcpy(&saveMem, charData->data, sizeof(ROBINDATA));
			memcpy((char *)(&saveMem) + sizeof(ROBINDATA), charData->data + charData->offset[0], sizeof(ROBINDATA));
			memcpy((char *)(&saveMem) + sizeof(ROBINDATA) * 2, charData->data + charData->offset[1], sizeof(ROBINDATA));
			memcpy(&game, charData->data + charData->offset[2], sizeof(GAMEDATA));
			memcpy(&option, charData->data + charData->offset[2] + sizeof(GAMEDATA), sizeof(OPTION));

			EncryptFile(saveFileName[0], saveMem, sizeof(ROBINDATA) * 3);
			EncryptFile(saveFileName[2], (char *)&game, sizeof(GAMEDATA));
			EncryptFile(saveFileName[2], (char *)&option, sizeof(OPTION));

			//InputCharData((CHARSAVE *)(rPkt + 4));
			menuDepth = 10;
			break;
	}

	Close(true, true);
}

void ResultData_ShopInfo(unsigned char *rPkt)
{
	S2C_SHOPINFO *shopData = (S2C_SHOPINFO *)MC_GETDPTR(nBuff_Recv);
	int ni_Size;

	memset(&NetItemData, 0, sizeof(NETITEMDATA) * MAXNETINVEN);

	nInvenMax = shopData->nSize;
	nInvenCnt = shopData->nCurrentSize;
	nShopCnt = shopData->nShopCount;

	#ifdef LGT
	SetNetInventory((char *)(rPkt + 4));
	ni_Size = SetNetShop((char *)(rPkt + 4 + sizeof(ServerItem) * nInvenCnt));
	#else
	SetNetInventory(rPkt + 4);
	ni_Size = SetNetShop(rPkt + 4 + sizeof(ServerItem) * nInvenCnt);
	#endif

	if (showNotice) {
		memset(tempStr2, 0, sizeof(tempStr2));
		memcpy(tempStr2, rPkt + 5 + nInvenCnt * sizeof(ServerItem) + ni_Size, rPkt[4 + nInvenCnt * sizeof(ServerItem) + ni_Size]);
	}

	if (nBuff_Recv) {
		nDataLen = 0;
		MC_knlFree(nBuff_Recv);
		nBuff_Recv = 0;
	}

	menuFocus = 0;

	if (a.shop[0].type < 255)
		SetNetString(ITEMPTR_SHOP);

	scS = 0;
	scS3 = 0;
	scC = 0;
	scC3 = 0;

	scE3 = scP3 = 6;
	scP = scE = 6;
	scT3 = Max(scP3, (nShopCnt + 3) / 4);
	scT = Max(scP, (robin.count + 3) / 4 + 1);

	switch (drawHandle) {
		case MD_PLAY:
			break;
		case MD_SHOP:
			menuFocus = 100;
			break;
		case MD_TITLEMENU:
			scE3 = scP3 = 6;
			scT3 = Max(scP3, (nShopCnt + 3) / 4);
			scE2 = scP2 = 6;
			scT2 = (nInvenMax + 3) / 4;

			menuDepth = 3;
			break;
	}

	SendErase();
}

void ResultData_ShopOnlyInfo(unsigned char *rPkt)
{
	S2C_SHOPONLYINFO *shopData = (S2C_SHOPONLYINFO *)MC_GETDPTR(nBuff_Recv);
	int ni_Size;

	nShopCnt = shopData->nShopCount;

	#ifdef LGT
	ni_Size = SetNetShop((char *)(rPkt + 4));
	#else
	ni_Size = SetNetShop(rPkt + 4);
	#endif

	if (rPkt[0] == PTS_INVENTOSHOP)
		menuPage = 1;

	if (nBuff_Recv) {
		nDataLen = 0;
		MC_knlFree(nBuff_Recv);
		nBuff_Recv = 0;
	}

	menuFocus = 0;
	scC3 = scS3 = 0;
	scE3 = scP3 = 6;
	scT3 = Max(scP3, (nShopCnt + 3) / 4);

	if (a.shop[0].type < 255)
		SetNetString(ITEMPTR_SHOP);

	switch (drawHandle) {
		case MD_PLAY:
			break;
		case MD_SHOP:
			menuFocus = 100;
			break;
		case MD_TITLEMENU:
			scS2 = scC2 = 0;
			scE2 = scP2 = 6;
			scT2 = (nInvenMax + 3) / 4;

			menuDepth = 3;
			break;
	}

	Close(false, false);
}

void ResultData_InvenOnlyInfo(unsigned char *rPkt)
{
	S2C_INVENINFO *shopData = (S2C_INVENINFO *)MC_GETDPTR(nBuff_Recv);

	memset(&NetItemData, 0, sizeof(NETITEMDATA) * MAXNETINVEN);

	nInvenMax = shopData->nSize;
	nInvenCnt = (unsigned char)shopData->nCurrentSize;

	#ifdef LGT
	SetNetInventory((char *)(rPkt + 4));
	#else
	SetNetInventory(rPkt + 4);
	#endif

	if (nBuff_Recv) {
		nDataLen = 0;
		MC_knlFree(nBuff_Recv);
		nBuff_Recv = 0;
	}

	//menuFocus = 0;
	scS2 = 0;
	scE2 = scP2 = 6;
	scT2 = (nInvenMax + 3) / 4;

	SendErase();
}

void ResultData_BuyItem(void)
{
	S2C_BUYITEM *buyData = (S2C_BUYITEM *)MC_GETDPTR(nBuff_Recv);

	switch (buyData->nResult) {
		default:
			//실패
			menuResult = TEXT_NETWORK_BUYITEM_FAIL;
			break;
		case 1:
			//한도초과
			#ifdef KTF
			if (buyData->nMaxCharge == 100000)
				menuResult = TEXT_NETWORK_MAXCHARGED2;
			else
				menuResult = TEXT_NETWORK_MAXCHARGED1;
			#elif defined SKT
			menuResult = TEXT_NETWORK_MAXCHARGED;
			#else
			menuResult = TEXT_NETWORK_MAXCHARGED_LGT;
			#endif
			break;
		case 2:
			//기타 예외(LGT는 임직원단말기)
			if (netType == NET_GAME_BUY && chargeStatus == 10)
				SetAlert(ALERT_LGTFELLOWS);
			else
				menuResult = TEXT_LGTFELLOWS;
			break;
		case 3:
			//구매성공
			#ifdef SKT

			switch (chargeStatus) {
				case 0:
					Charge(a.shop[scS3 * 4 + menuFocus].value);
					break;
				case 1:
					//응급부활약
					Charge(100);
					break;
				case 2:
					//유령 부활시
					Charge(100);
					break;
				case 4:
					//세이브 슬롯
					Charge(1000);
					break;
				default:
					//석시리즈
					Charge(1900);
					break;
			}

			#else

			AfterCharge();

			#endif

			MC_knlUnsetTimer(&ntimer);
			MC_knlSetTimer(&ntimer, 300000, (void *)&frame);
			return;
		case 4:
			//펌웨어 업글
			menuResult = TEXT_FIRMUPGLE;
			break;
		case 5:		//홀 한도 초과.
			menuResult = TEXT_LGHOLELIMITBUY;
			break;
		case 6:		//홀 연동 실패.
			menuResult = TEXT_LGHOLELINKFAIL;
			break;
		case 7:		//네트워크 에러 입니다. 잠시 후에 다시 시도해주세요.
			menuResult = TEXT_LGOTHERS;
			break;	
	}

	switch (chargeStatus) {
		case 1:
			//응급 부활약
		case 2:
			//유령 부활시
		case 4:
			//세이브 슬롯
			Close(true, true);
			break;
		default:
			Close(false, false);
			break;
	}
}

void ResultData_QuickBuyItem(void)
{
	int i;
	S2C_BUYITEM *buyData = (S2C_BUYITEM *)MC_GETDPTR(nBuff_Recv);

	switch (buyData->nResult) {
		default:
			menuResult = TEXT_NETWORK_BUYITEM_FAIL;
			break;
		case 1:
			if (netType == NET_GAME_BUY && chargeStatus == 10) {
				#ifdef KTF
				if (buyData->nMaxCharge == 100000)
					menuResult = TEXT_NETWORK_MAXCHARGED2;
				else
					menuResult = TEXT_NETWORK_MAXCHARGED1;
				#elif defined SKT
				menuResult = TEXT_NETWORK_MAXCHARGED;
				#else
				menuResult = TEXT_NETWORK_MAXCHARGED_LGT;
				#endif
			}
			else {
				#ifdef KTF
				if (buyData->nMaxCharge == 100000)
					SetAlert(ALERT_MAXCHARGED2);
				else
					SetAlert(ALERT_MAXCHARGED1);
				#elif defined SKT
				SetAlert(ALERT_MAXCHARGED);
				#else
				SetAlert(ALERT_MAXCHARGED_LGT);
				#endif
			}
			break;
		case 2:
			//기타 예외(LGT는 임직원단말기)
			if (netType == NET_GAME_BUY && chargeStatus == 10)
				SetAlert(ALERT_LGTFELLOWS);
			else
				menuResult = TEXT_LGTFELLOWS;
			break;
		case 3:
			//구매성공
			memset(recipeName, 0, sizeof(recipeName));

			for (i = 0; i < 30; i++)
				recipeName[i] = buyData->nItem[i];

			#ifdef SKT

			if (chargeStatus == 10)
				Charge(500);
			else if (chargeStatus >= 5)
				Charge(1900);
			else {
				//쿠폰상점인 경우
				if (menuPage2 == 2) {
					temp = GetInvenIdx(ITEM_NETITEM, ITEM_NET_COUPON, 0);
					robin.inven[temp].count -= a.shop[scS3 * 4 + menuFocus - 100].gold;

					if (robin.inven[temp].count <= 0)
						EraseItem(temp);

					AfterCharge2();
				}
				else
					Charge(a.shop[scS3 * 4 + menuFocus - 100].value);
			}

			#else

			if (chargeStatus < 5 && menuPage2 == 2) {
				temp = GetInvenIdx(ITEM_NETITEM, ITEM_NET_COUPON, 0);
				robin.inven[temp].count -= a.shop[scS3 * 4 + menuFocus - 100].gold;

				if (robin.inven[temp].count <= 0)
					EraseItem(temp);
			}

			AfterCharge2();

			#endif

			MC_knlUnsetTimer(&ntimer);
			MC_knlSetTimer(&ntimer, 300000, (void *)&frame);
			return;
		case 4:
			//펌웨어 업글
			menuResult = TEXT_FIRMUPGLE;
			break;
		case 5:		//홀 한도 초과.
			menuResult = TEXT_LGHOLELIMITBUY;
			break;
		case 6:		//홀 연동 실패.
			menuResult = TEXT_LGHOLELINKFAIL;
			break;
		case 7:		//네트워크 에러 입니다. 잠시 후에 다시 시도해주세요.
			menuResult = TEXT_LGOTHERS;
			break;	
	}

	switch (chargeStatus) {
		case 0:
			menuDepth = 0;

			if (shopType == SHOPTYPE_NET) {
				Close(false, false);
				return;
			}
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			menuDepth = 21;
			break;
		case 10:
			//투기장 입장 실패 관련.
			break;
	}

	Close(true, true);
}

void ResultData_BuySuccess(void)
{
	int i;
	ITEM *it = &a.shop[scS3 * 4 + menuFocus];

	//달성도 체크 : 진정한 갑부(유료 아이템 구입 개수)
	ReportCheck(PLAYER_TITLE12, 0);

	switch (chargeStatus) {
		case 0:
			if (it->type == ITEM_NETITEM) {
				switch (it->detail) {
					default:
						menuResult = TEXT_NETWORK_ITEMBUYRESULT1;
						break;
					case ITEM_NET_CHARACTER:
						SaveFlag(1);

						if (it->id == 208) {
							robin.ap = (robin.lv - 1) * LVUP_AP + 5;
							robin.stat[STAT_STR] = 5;
							robin.stat[STAT_AGI] = 5;
							robin.stat[STAT_VIT] = 5;
							robin.stat[STAT_INT] = 5;
							robin.sp = (robin.lv - 1) * LVUP_SP;

							for (i = 0; i < TOTALSKILL; i++)
								robin.skillLv[i] = 0;

							for (i = 0; i < MAXHOTKEY; i++) {
								if (robin.hotKey[i].type == HOTKEY_SKILL)
									FreeHotKey(i);
							}

							SaveFlag(0);
						}

						option.change = option.curSlot + 1;
						menuDepth = 3;
						menuPage2 = robin.type;
						curMenu = 0;
						NewGameImgLoad();
						Close(true, true);
						return;
					case ITEM_NET_SINGLEBAG:
						menuResult = TEXT_NETWORK_ITEMBUYRESULT2;

						if (it->id == 215) {
							robin.maxInven += 12;
							option.maxInven = Max(option.maxInven, robin.maxInven);
							SaveFlag(0);
						}
						break;
					case ITEM_NET_NETBAG:
						menuResult = TEXT_NETWORK_ITEMBUYRESULT3;

						if (it->id == 217) {
							nInvenMax += 8;
							scT2 = (nInvenMax + 3) / 4;
						}
						break;
					case ITEM_NET_APRESET:
						menuResult = TEXT_NETWORK_ITEMBUYRESULT4;

						if (it->id == 218) {
							robin.ap = (robin.lv - 1) * LVUP_AP + 5;
							robin.stat[STAT_STR] = 5;
							robin.stat[STAT_AGI] = 5;
							robin.stat[STAT_VIT] = 5;
							robin.stat[STAT_INT] = 5;
							SaveFlag(0);
						}
						break;
					case ITEM_NET_SPRESET:
						menuResult = TEXT_NETWORK_ITEMBUYRESULT5;

						if (it->id == 219) {
							robin.sp = (robin.lv - 1) * LVUP_SP;

							for (i = 0; i < TOTALSKILL; i++)
								robin.skillLv[i] = 0;

							for (i = 0; i < MAXHOTKEY; i++) {
								if (robin.hotKey[i].type == HOTKEY_SKILL)
									FreeHotKey(i);
							}

							SaveFlag(0);
						}
						break;
				}
			}
			else
				menuResult = TEXT_NETWORK_ITEMBUYRESULT1;

			Close(false, false);
			break;
		case 1:
			//죽었을때 응급부활시
			ResurrectionEffect();
			Close(true, true);
			break;
		case 2:
			//유령 부활시
			game.playMode[option.curSlot] = HELL_START;
			SaveFlag(2);
			Close(true, true);
			break;
		case 4:
			option.saveSlot++;
			SaveFlag(1);

			if (curMenu == 0) {
				menuDepth = 2;
				NewGameImgLoad();
			}

			Close(true, true);
			break;
	}
}

void ResultData_QuickBuySuccess(void)
{
	//달성도 체크 : 진정한 갑부(유료 아이템 구입 개수)
	ReportCheck(PLAYER_TITLE12, 0);

	if (chargeStatus == 10) {
		//투기장으로 보내준다.
		switch (robin.map) {
			case TOLEM1:
				GotoCave(CAVE_A_1);
				break;
			case ATLANTICE8:
				GotoCave(CAVE_B_1);
				break;
			case CASTLE14:
				GotoCave(CAVE_C_19);
				break;
			case ELF5:
				GotoCave(CAVE_D_3);
				break;
			case CASTLE7:
				GotoArena();
				break;
		}
	}
	else if (chargeStatus >= 5) {
		int idx = ((menuFocus < 100 && stoneWhere == 1) ? ITEMPTR_INVEN + scS * 4 + menuFocus : ITEMPTR_EQUIP + d.equipSlotPos[menuFocus / 100 * 4]);

		switch (chargeStatus) {
			case 6:
				invenGemCnt = 1;
			case 5:
				menuDepth = 17;
				break;
			case 7:
				StoneRecipe(idx);
				break;
			case 8:
				StoneResolution(idx);
				break;
			case 9:
				StoneSocket(idx);
				break;
		}
	}
	else {
		if (a.shop[scS3 * 4 + menuFocus - 100].type == ITEM_NETITEM) {
			switch (a.shop[scS3 * 4 + menuFocus - 100].detail) {
				default:
					menuResult = TEXT_NETWORK_ITEMBUYRESULT8;
					break;
				case ITEM_NET_SINGLEBAG:
					menuResult = TEXT_NETWORK_ITEMBUYRESULT2;
					break;
				case ITEM_NET_NETBAG:
					menuResult = TEXT_NETWORK_ITEMBUYRESULT3;
					break;
				case ITEM_NET_APRESET:
					menuResult = TEXT_NETWORK_ITEMBUYRESULT4;
					break;
				case ITEM_NET_SPRESET:
					menuResult = TEXT_NETWORK_ITEMBUYRESULT5;
					break;
			}
		}
		else
			menuResult = TEXT_NETWORK_ITEMBUYRESULT8;
	}

	if (chargeStatus >= 5 || shopType == SHOPTYPE_QUICK)
		Close(true, true);
	else
		Close(false, false);
}

void ResultData_InvenInfo(unsigned char *rPkt)
{
	S2C_INVENINFO *invenData = (S2C_INVENINFO *)MC_GETDPTR(nBuff_Recv);

	memset(&NetItemData, 0, sizeof(NETITEMDATA) * MAXNETINVEN);

	nInvenMax = invenData->nSize;
	nInvenCnt = (unsigned char)invenData->nCurrentSize;

	#ifdef LGT
	SetNetInventory((char *)(rPkt + 4));
	#else
	SetNetInventory(rPkt + 4);
	#endif

	if (showNotice) {
		memset(tempStr2, 0, sizeof(tempStr2));
		memcpy(tempStr2, rPkt + 4 + nInvenCnt * sizeof(ServerItem), rPkt[3 + nInvenCnt * sizeof(ServerItem)]);
	}

	SetPresentString(scS2 * 4 + menuFocus);
	SetItemString(ITEMPTR_SHOP + NETINVENSTART + scS2 * 4 + menuFocus);

	if (nBuff_Recv) {
		nDataLen = 0;
		MC_knlFree(nBuff_Recv);
		nBuff_Recv = 0;
	}

	scS = 0;
	scS2 = 0;
	scC = 0;
	scC2 = 0;

	if (drawHandle == MD_TITLEMENU) {
		scP2 = scE2 = 6;
		scP = scE = 6;

		menuDepth = 3;
	}
	else {
		scP2 = scE2 = 5;
		scP = scE = 5;

		menuDepth = 12;
	}

	scT2 = (nInvenMax + 3) / 4;
	scT = Max(scP, (robin.count + 3) / 4 + 1);

	SendErase();
}

void ResultData_GetItem(unsigned char *rPkt)
{
	S2C_GETITEM *getItemData = (S2C_GETITEM *)MC_GETDPTR(nBuff_Recv);
	ITEM *it = &a.shop[NETINVENSTART + scS2 * 4 + menuFocus - ((rPkt[0] == PTS_GETITEM) ? 0 : 100)];

	if (getItemData->nResult == 1) {
		switch (it->type) {
			case ITEM_GOLD:
				robin.gold += it->count * 1000;

				//달성도 체크 : 저축 습관(인벤토리에 있는 돈)
				ReportCheck(REPORT_ETC5, (int)robin.gold);
				break;
			case ITEM_NETITEM:
			case ITEM_WASTE:	//소모성 아이템들
			case ITEM_IRON:
			case ITEM_LEATHER:
			case ITEM_CLOTH:
			case ITEM_WOOD:
			case ITEM_ESSENCE:	//필수재료
				temp = GetInvenIdx(it->type, it->detail, it->grade);

				if (temp < robin.count && (it->type != ITEM_NETITEM || it->detail < ITEM_NET_BOX_WEAPON_HIGH)) {
					robin.inven[temp].count += it->count;
					QuestItemCheck(robin.inven[temp].type, robin.inven[temp].detail, 0);
					break;
				}
			default:
				memcpy(&robin.inven[robin.count], it, sizeof(ITEM));
				robin.count++;
				QuestItemCheck(robin.inven[robin.count - 1].type, robin.inven[robin.count - 1].detail, 0);
				break;
		}

		SaveFlag(0);

		if (rPkt[0] == PTS_GETITEM) {
			EraseNetItem(scS2 * 4 + menuFocus);
			scT3 = Max(6, (robin.count + 3) / 4 + 1);

			if (menuFocus < 100)
				SetItemString(ITEMPTR_SHOP + NETINVENSTART + scS2 * 4 + menuFocus);
		}
		else {
			EraseNetItem(scS2 * 4 + menuFocus - 100);

			if (menuFocus >= 100)
				SetItemString(ITEMPTR_SHOP + NETINVENSTART + scS2 * 4 + menuFocus - 100);
		}
	}
	else
		menuResult = TEXT_NETWORK_GETITEM_FAIL;

	Close(false, false);
}

void ResultData_SendItem(unsigned char *rPkt)
{
	S2C_SENDITEM *sendItemData = (S2C_SENDITEM *)MC_GETDPTR(nBuff_Recv);

	switch (sendItemData->nResult) {
		case 0:
			menuResult = TEXT_NETWORK_SENDITEM_FAIL;
			break;
		case 1:
			NetItemData[nInvenCnt].idx = sendItemData->nIndex;
			memset(NetItemData[nInvenCnt].date, 0, 4);
			memset(NetItemData[nInvenCnt].phone, 0, 4);

			memcpy(&a.shop[NETINVENSTART + nInvenCnt], &tempItem, sizeof(ITEM));
			nInvenCnt++;
			break;
		case 2:
			//인벤토리 부족
			menuResult = TEXT_NETWORK_ITEMBUYRESULT0;
			break;
	}

	if (nBuff_Recv) {
		nDataLen = 0;
		MC_knlFree(nBuff_Recv);
		nBuff_Recv = 0;
	}

	if (menuFocus >= 100)
		SetItemString(ITEMPTR_INVEN + scS * 4 + menuFocus - 100);

	EraseCopyItem();

	Close(false, false);
}

void ResultData_Present(void)
{
	S2C_PRESENT *data = (S2C_PRESENT *)MC_GETDPTR(nBuff_Recv);

	switch (data->nResult) {
		case 0:
			menuResult = TEXT_NETWORK_PRESENT_FAIL;
			break;
		case 1:
			menuResult = TEXT_NETWORK_NOUSER;
			break;
		case 2:
			menuResult = TEXT_NETWORK_OTHERUSERINVENFULL;
			break;
		case 3:
			EraseNetItem(scS2 * 4 + menuFocus);
			SetPresentString(scS2 * 4 + menuFocus);
			menuResult = TEXT_NETWORK_PRESENTSUCCEED;
			menuDepth = 3;
			break;
		case 4:
			menuResult = TEXT_NETWORK_NOTCERTIFIEDVER;
			break;
	}

	Close(false, false);
}

void ResultData_Verify(void)
{
	//네트워크에서 구매한 사용자인지 아닌지 받아올 변수
	//0 = 구매를 할거냐 묻는 창(초기값)
	//1 = 이전에 구매했던 기록이 있는 사용자,
	//2 = 구매하기 누른 후 구매 완료 되었을 때 창
	//3 = 구매에 실패 했을 경우 창
	S2C_VERIFY *data = (S2C_VERIFY *)MC_GETDPTR(nBuff_Recv);

	memset(tempStr, 0, sizeof(tempStr));
	memcpy(tempStr, data->nBody, data->nLength);

	switch (data->nResult) {
		case 1:
			//인증 성공
			#ifdef SKT
			Charge(4000);
			MC_knlSetTimer(&ntimer, 15000, (void *)null);
			#else
			AfterCharge();
			#endif
			break;
		case 2:
			//이미 인증완료
			buy_Mode = 1;
			Close(true, true);
			break;
		default:
			//기타 에러
			buy_Mode = 3;
			Close(true, true);
			break;
	}
}

void ResultData_ScreenShot(void)
{
	S2C_SCREENSHOT *data = (S2C_SCREENSHOT *)MC_GETDPTR(nBuff_Recv);

	memcpy(option.screen[scC].url, data->fileName, 24);

	Close(true, true);

	isScreenShot = 10;

	SaveFlag(1);
}

void ResultData_DailyGet(void)
{
	S2C_DAILYGET *data = (S2C_DAILYGET *)MC_GETDPTR(nBuff_Recv);

	robin.guildQuest[0] = data->questType;
	robin.guildQuest[1] = data->questDetail;
	robin.guildQuest[2] = data->questDetail2;
	robin.guildQuest[3] = data->questCount;

	memcpy(robin.guildQuestName, data->questName, sizeof(data->questName));
	memcpy(robin.guildQuestExplanation, data->questDesc, sizeof(data->questDesc));

	scT2 = LineTextStr(robin.guildQuestExplanation, 1000, 1000, 104, -1, -1) * 4 + 2;
	robin.guildQuestReward[0] = data->rewardType;
	robin.guildQuestReward[1] = data->rewardDetail;
	robin.guildQuestReward[2] = data->rewardGrade;
	robin.guildQuestReward[3] = data->rewardCount;
	robin.guildQuestIndex = data->questIndex;

	robin.oldTime = MC_knlCurrentTime() / 1000;

	SaveFlag(0);

	curMenu = 1;

	Close(true, true);
}

void ResultData_DailyEnd(void)
{
	//달성도 카운팅 : 매일 매일 꾸준히(데일리 퀘스트 수행 횟수)
	ReportCheck(REPORT_ARENA7, 0);

	//일일퀘스트 완료 요구 아이템삭제
	if (robin.guildQuest[0] == QUESTTYPE_ITEM_ONE) {
		temp = GetInvenIdx(robin.guildQuest[1], robin.guildQuest[2], GRADE_NORMAL);
		robin.inven[temp].count -= robin.guildQuest[3];

		if (robin.inven[temp].count == 0)
			EraseItem(ITEMPTR_INVEN + temp);

		QuestItemCheck(robin.guildQuest[1], robin.guildQuest[2], 0);
	}

	// 일일퀘스트 보상 주고
	GetItem(ITEM_NETITEM, 1, ITEM_NET_COUPON, GRADE_NORMAL, 1, 0);
	GetItem(robin.guildQuestReward[0], 1, robin.guildQuestReward[1], robin.guildQuestReward[2], robin.guildQuestReward[3], 0);
	robin.guildQuestStatus = QUESTEND;

	SaveFlag(0);

	//경고창 처리
	SetAlert(ALERT_DAILYQUESTCLEAR);

	ReadString(TEXT_DAILYQUESTCLEAR);
	memset(tempStr, 0, sizeof(tempStr));
	MC_knlSprintk(tempStr, TEXTPTR(TEXT_DAILYQUESTCLEAR), robin.guildQuestName);
	TextFree(TEXT_DAILYQUESTCLEAR);

	Close(true, true);
}

void ResultData_GuildStart(void)
{
	S2C_GUILDSTART *guildData = (S2C_GUILDSTART *)MC_GETDPTR(nBuff_Recv);

	guildTimeStr[0] = guildData->nFlag;
	guildTimeStr[1] = guildData->nNextMon;
	guildTimeStr[2] = guildData->nNextDay;
	guildTimeStr[3] = guildData->nNextTime1;
	guildTimeStr[4] = guildData->nNextTime2;

	if (guildData->length) {
		showNotice = 1;
		memset(tempStr2, 0, sizeof(tempStr2));
		memcpy(tempStr2, &guildData->data, guildData->length);
	}

	if (guildTimeStr[0] == 0) {
		memset(skillStr, 0, sizeof(skillStr));
		ReadString(TEXT_GUILDNO);
		MC_knlSprintk(skillStr, TEXTPTR(TEXT_GUILDNO), guildTimeStr[1], guildTimeStr[2], guildTimeStr[3], guildTimeStr[4]);
		TextFree(TEXT_GUILDNO);
		menuResult = 5000;
	}
	else
		curMenu = 7;

	Close(true, true);
}

void ResultData_GuildCurrent(void)
{
	S2C_GUILDCURRENT *guildData = (S2C_GUILDCURRENT *)MC_GETDPTR(nBuff_Recv);
	int i;

	//점수 입력
	for (i = 0; i < 4; i++)
		MC_knlSprintk(rankScore[i], "|d%d", guildData->score[i]);

	//지난주 우승길드
	guildWinner = guildData->lastWinGuild;
	rankRecord[0] = guildData->myRank;

	temp = (guildWinner == 0) ? TEXT_NONE : (TEXT_GUILDNAME0 - 1 + guildWinner);

	ReadString(temp);
	ReadString(TEXT_GUILDWINNER);

	MC_knlSprintk(optionStr[7], TEXTPTR(TEXT_GUILDWINNER), TEXTPTR(temp));
	TextFree(TEXT_GUILDWINNER);
	TextFree(temp);

	//보상
	guildRewardReceive = guildData->canReward;
	guildReward[0] = guildData->rewardItemType;
	guildReward[1] = guildData->rewardItemDetail;
	guildReward[2] = guildData->rewardItemCount;
	goldReward = guildData->goldReward;

	if (guildData->length) {
		showNotice = 1;
		memset(tempStr2, 0, sizeof(tempStr2));
		memcpy(tempStr2, &guildData->data, guildData->length);
	}

	yesNo = 0;
	curMenu = 3;

	Close(true, true);
}

void ResultData_Reward(void)
{
	int i;

	guildRewardReceive = false;
	robin.gold += goldReward;

	//달성도 체크 : 저축 습관(인벤토리에 있는 돈)
	ReportCheck(REPORT_ETC5, (int)robin.gold);

	if (guildReward[0] > ITEM_GEM && guildReward[0] != ITEM_RECIPE && (guildReward[0] != ITEM_NETITEM || guildReward[1] < ITEM_NET_BOX_WEAPON_HIGH))
		GetItem(guildReward[0], 1, guildReward[1], GRADE_NORMAL, guildReward[2], 0);
	else {
		i = guildReward[2];

		do {
			i--;
			GetItem(guildReward[0], 1, guildReward[1], GRADE_NORMAL, 1, 0);
		} while (i > 0);
	}

	SaveFlag(0);

	Close(true, true);
}

void ResultData_Record(void)
{
	S2C_GUILDRECORD *guildData = (S2C_GUILDRECORD *)MC_GETDPTR(nBuff_Recv);
	int i;

	for (i = 0; i < 16; i++)
		rankRecord[i] = guildData->score[i];

	rankWeek = guildData->week;

	guildCur = 3;

	for (i = 0; i < 4; i++)
		MC_knlSprintk(rankScore[i], "|d%d", rankRecord[guildCur * 4 + i]);

	if (guildData->length) {
		showNotice = 1;
		memset(tempStr2, 0, sizeof(tempStr2));
		memcpy(tempStr2, &guildData->data, guildData->length);
	}

	curMenu = 4;

	Close(true, true);
}

void ResultData_Recommend(void)
{
	S2C_RECOMMEND *guildData = (S2C_RECOMMEND *)MC_GETDPTR(nBuff_Recv);

	switch (guildData->nResult) {
		default:
			menuResult = TEXT_NET_ERROR;
			break;
		case 1:
			menuResult = TEXT_NETWORK_RECOMMEND_ALREADY;
			break;
		case 2:
			menuResult = TEXT_NETWORK_RECOMMEND_ALREADY2;
			break;
		case 125:
			menuResult = 3;

			ReadString(TEXT_NETWORK_RECOMMEND_COMPLETE);
			MC_knlSprintk(tempStr, TEXTPTR(TEXT_NETWORK_RECOMMEND_COMPLETE), dmgStr);
			TextFree(TEXT_NETWORK_RECOMMEND_COMPLETE);
			break;
	}

	Close(true, true);
}

void ResultData()
{
	unsigned char *rPkt = MC_GETDPTR(nBuff_Recv);

	if (netStatus != NETSTATUS_RECEIVE)
		return;

	netStatus = NETSTATUS_RESULT;

	#ifdef DOWNLOAD
	if (netType == NET_FILE_DOWNLOAD) {
		if (curFile + 1 == TOTALFILE) {
			//다운로드 완료
			WriteDownFile(MC_GETDPTR(nBuff_Recv), curFile);
			Close(true, true);
			netStatus = NETSTATUS_OFFLINE;
			isDown = true;

			if (oldDraw < MD_TITLE)
				GotoTitle();
			else if (oldDraw < MD_PLAY) {
				curMenu = 0;
				menuDepth = 1;
				drawHandle = MD_TITLEMENU;
				keyHandle = MK_TITLEMENU;
			}
			else {
				drawHandle = MD_PLAY;
				keyHandle = MK_PLAY;
			}
		}
		else {
			//파일 저장
			#ifndef SKT
			if (receiveSize == downFileSize[curFile])
			#endif
			{
				//파일 사이즈가 패킷사이즈와 일치한다면
				WriteDownFile(MC_GETDPTR(nBuff_Recv), curFile);
				curFile++;
				MC_knlSprintk(tempStr, "(%d/%d)", curFile, TOTALFILE);
			}

			SetData(NET_FILE_DOWNLOAD);
			netStatus = NETSTATUS_INIT;
			SendData();
			MC_knlUnsetTimer(&ntimer);
			MC_knlSetTimer(&ntimer, 300000, (void *)&frame);
		}

		return;
	}
	else
	#endif

	if (netType == NET_SCREEN && screenOffset < DX * DY * 2) {
		SetData(NET_SCREEN);
		netStatus = NETSTATUS_INIT;
		SendData();
		MC_knlUnsetTimer(&ntimer);
		MC_knlSetTimer(&ntimer, 15000, (void *)&frame);

		//MC_knlUnsetTimer(&ntimer);
		//MC_knlDefTimer(&stimer, ScreenTimer);
		//MC_knlUnsetTimer(&stimer);
		//MC_knlSetTimer(&stimer, 1000, NULL);

		return;
	}
	else if (netType == NET_SAVE && screenOffset < 3) {
		screenOffset++;
		SetData(NET_SAVE);
		netStatus = NETSTATUS_INIT;
		SendData();
		MC_knlUnsetTimer(&ntimer);
		MC_knlSetTimer(&ntimer, 15000, (void *)&frame);

		//MC_knlUnsetTimer(&ntimer);
		//MC_knlDefTimer(&stimer, ScreenTimer);
		//MC_knlUnsetTimer(&stimer);
		//MC_knlSetTimer(&stimer, 1000, NULL);

		return;
	}

	if (rPkt[0] == PTS_NOTICE_SHOP) {
		showNotice = 1;

		if (netType == NET_SHOP)
			rPkt[0] = PTS_SHOPINFO;
		else if (netType == NET_INVEN)
			rPkt[0] = PTS_INVENINFO;
	}

	switch (rPkt[0]) {
		case PTS_NOTICE_RANKING:
		case PTS_NOTICE_ARENA:
		case PTS_GUILDRANKING:
			showNotice = 1;
		case PTS_CHARRANKING:
		case PTS_ARENARANKING:
		case PTS_RANKING_ADD:
			ResultData_Ranking(rPkt);
			break;
		case PTS_RANKING_DETAIL:
			ResultData_RankingDetail();
			break;
		//case PTS_NOTICE:
		//	{
		//		memset(tempStr, 0, sizeof(tempStr));
		//		memcpy(tempStr, rPkt + 2, rPkt[1]);
		//		Close(true, true);
		//		netStatus = NETSTATUS_OFFLINE;
		//	}
		//	break;
		case PTS_SENDCHARACTOR:
			ResultData_SendCharacter();
			break;
		case PTS_GETCHARACTOR:
			ResultData_GetCharacter(rPkt);
			break;
		case PTS_SHOPINFO:
			ResultData_ShopInfo(rPkt);
			break;
		case PTS_INVENTOSHOP:
		case PTS_SHOPONLYINFO:
			ResultData_ShopOnlyInfo(rPkt);
			break;
		case PTS_INVENONLYINFO:
			ResultData_InvenOnlyInfo(rPkt);
			break;
		case PTS_BUYITEM:
			ResultData_BuyItem();
			break;
		case PTS_QUICKBUYITEM:
			ResultData_QuickBuyItem();
			break;
		case PTS_BUYSUCCESS:
			ResultData_BuySuccess();
			break;
		case PTS_QUICKBUYSUCCESS:
			ResultData_QuickBuySuccess();
			break;
		case PTS_INVENINFO:
			ResultData_InvenInfo(rPkt);
			break;
		case PTS_GETITEMATSHOP:
		case PTS_GETITEM:
			ResultData_GetItem(rPkt);
			break;
		case PTS_ERASEITEMATSHOP:
			EraseNetItem(scS2 * 4 + menuFocus - 100);
			Close(false, false);
			break;
		case PTS_SENDITEM:
			ResultData_SendItem(rPkt);
			break;
		case PTS_PRESENT:
			ResultData_Present();
			break;
		case PTS_ERASEITEM:
			EraseNetItem(scS2 * 4 + menuFocus);
			Close(false, false);
			break;
		case PTS_SERVERCLOSE:
			Close(false, false);
			break;
		//case PTS_AGREE:
		//	{
		//		S2C_AGREE *data = (S2C_AGREE *)MC_GETDPTR(nBuff_Recv);

		//		memset(tempStr, 0, sizeof(tempStr));
		//		memcpy(tempStr, data->nBody, data->nLength);

		//		//option.argee = 1;
		//		//SaveFlag(1);

		//		menuDepth = 2;
		//		Close(true, true);
		//	}
		//	break;
		case PTS_VERIFY:
			ResultData_Verify();
			break;
		case PTS_SCREENSHOT:
			ResultData_ScreenShot();
			break;
		case PTS_DAILYGET:
			ResultData_DailyGet();
			break;
		case PTS_DAILYEND:
			ResultData_DailyEnd();
			break;
		case PTS_GUILDSTART:
			ResultData_GuildStart();
			break;
		case PTS_GUILDCURRENT:
			ResultData_GuildCurrent();
			break;
		case PTS_GUILDREWARD:
			ResultData_Reward();
			break;
		case PTS_GUILDRECORD:
			ResultData_Record();
			break;
		case PTS_RECOMMEND:
			ResultData_Recommend();
			break;


		#ifdef USERCHECK
		case PTS_USERCHECK:
			{
				S2C_SERVERCLOSE *userData = (S2C_SERVERCLOSE *)MC_GETDPTR(nBuff_Recv);

				switch (userData->nSuccess) {
					case 0:
						//유저정보가 없음
						menuDepth = 2;
						menuResult = TEXT_USERCHECK_FAIL;
						break;
					case 1:
						//베타기간 만료
						menuDepth = 2;
						menuResult = TEXT_USERCHECK_EXPIRE;
						break;
					case 125:
						//성공
						menuDepth = 1;
						break;
				}

				Close(true, true);
			}
			break;
		#endif

	}
	if (touch) touchDrawButton = false;
}

void AfterCharge()
{
	int i;
	ITEM *it = &a.shop[scS3 * 4 + menuFocus];

	MC_knlUnsetTimer(&ntimer);
	MC_knlSetTimer(&ntimer, 300000, (void *)&frame);

	switch (chargeStatus) {
		case 0:
			if (it->type == ITEM_NETITEM) {
				switch (it->detail) {
					case ITEM_NET_SINGLEBAG:
						if (it->count > 1)
							robin.maxInven = 100;
						else
							robin.maxInven += 12;

						option.maxInven = Max(option.maxInven, robin.maxInven);
						SaveFlag(1);
						break;
					case ITEM_NET_NETBAG:
						nInvenMax += 8;
						scT2 = (nInvenMax + 3) / 4;
						break;
					case ITEM_NET_CHARACTER:
						//영혼의 변화
					case ITEM_NET_APRESET:
						robin.ap = (robin.lv - 1) * LVUP_AP + 5;
						robin.stat[STAT_STR] = 5;
						robin.stat[STAT_AGI] = 5;
						robin.stat[STAT_VIT] = 5;
						robin.stat[STAT_INT] = 5;

						if (it->detail == ITEM_NET_APRESET)
							break;
					case ITEM_NET_SPRESET:
						robin.sp = (robin.lv - 1) * LVUP_SP;

						for (i = 0; i < TOTALSKILL; i++)
							robin.skillLv[i] = 0;

						for (i = 0; i < MAXHOTKEY; i++) {
							if (robin.hotKey[i].type == HOTKEY_SKILL)
								FreeHotKey(i);
						}
						break;
				}

				//저장
				SaveFlag(0);
			}
			break;
		case 1:
			//죽었을때 응급부활시
			SaveFlag(1);

			// 투기장에서 부활약사용시, AI캐릭터가 살아있었다면 다시 활동시켜준다.
			if (robin.map >= ARENA1) {
				if (ao[1].hp > 0)
					ao[1].active = true;

				if (ao[2].hp > 0)
					ao[2].active = true;
			}

			//헬모드중 부활약 사용시 패널티없이 살려준다
			if (game.playMode[option.curSlot] == HELL_DIE) {
				game.playMode[option.curSlot] = HELL_START;
				SaveEtc();
			}

			//원래 배경음으로 돌려준다
			PlayMusic(mapData[10]);
			break;
		case 2:
			//유령 부활시
			break;
		case 3:
			//체험판 인증시
			option.BuyGame = true;
			option.verify[1] = phone[4];
			option.verify[2] = phone[5];
			option.verify[3] = phone[6];
			option.verify[4] = phone[7];
			option.verify[5] = phone[8];
			option.verify[6] = phone[9];
			option.verify[7] = phone[10];
			SaveOption();

			buy_Mode = 2;

			Close(true, true);
			return;
		case 4:
			//세이브슬롯 구매시
			break;
	}

	//게임시
	SetData(NET_SHOP_BUYSUCCESS);
	netStatus = NETSTATUS_INIT;
	SendData();
}

void AfterCharge2()
{
	int i;

	MC_knlUnsetTimer(&ntimer);
	MC_knlSetTimer(&ntimer, 300000, (void *)&frame);

	if (chargeStatus < 5) {
		switch (a.shop[scS3 * 4 + menuFocus - 100].detail) {
			case ITEM_NET_RESURRECTION:
				//영혼의 변화
				break;
			case ITEM_NET_SINGLEBAG:
				if (a.shop[scS3 * 4 + menuFocus - 100].count > 1)
					//가방 100칸
					robin.maxInven = 100;
				else
					//가방 12칸
					robin.maxInven += 12;

				scT = (robin.maxInven + 3) / 4;

				option.maxInven = Max(option.maxInven, robin.maxInven);
				SaveFlag(1);
				break;
			case ITEM_NET_NETBAG:
				//창고가방
				nInvenMax += 8;
				//scT2 = (nInvenMax + 3) / 4;
				break;
			case ITEM_NET_APRESET:
				//AP초기화
				robin.ap = (robin.lv - 1) * LVUP_AP + 5;
				robin.stat[STAT_STR] = 5;
				robin.stat[STAT_AGI] = 5;
				robin.stat[STAT_VIT] = 5;
				robin.stat[STAT_INT] = 5;

				RefreshStat();
				break;
			case ITEM_NET_SPRESET:
				//강화의 비약과 detail값이 같음. 분기.
				if (a.shop[scS3 * 4 + menuFocus - 100].type == ITEM_WASTE)
					break;

				//SP초기화
				robin.sp = (robin.lv - 1) * LVUP_SP;

				for (i = 0; i < TOTALSKILL; i++)
					robin.skillLv[i] = 0;

				for (i = 0; i < MAXHOTKEY; i++) {
					if (robin.hotKey[i].type == HOTKEY_SKILL)
						FreeHotKey(i);
				}

				RefreshStat();
				break;
		}
	}

	//아이템 생성
	for (i = 0; i < 30; i += 3) {
		if (recipeName[i] < 0 || recipeName[i] > 127)
			continue;

		switch (recipeName[i]) {
			default:
				GetItem(recipeName[i], 99, recipeName[i + 1], recipeName[i + 2], 1, 0);
				break;
			case ITEM_WASTE:
			case ITEM_IRON:
			case ITEM_LEATHER:
			case ITEM_CLOTH:
			case ITEM_WOOD:
			case ITEM_ESSENCE:
			case ITEM_RECIPE:
			case ITEM_QUEST:
				GetItem(recipeName[i], 99, recipeName[i + 1], GRADE_NORMAL, recipeName[i + 2], 0);
				break;
			case ITEM_NETITEM:
				if (recipeName[i + 1] < ITEM_NET_SINGLEBAG)
					GetItem(recipeName[i], 99, recipeName[i + 1], GRADE_NORMAL, recipeName[i + 2], 0);
				else
					GetItem(recipeName[i], 99, recipeName[i + 1], recipeName[i + 2], 1, 0);
				break;
			case ITEM_GOLD:
				robin.gold += recipeName[i + 1] * recipeName[i + 2] * 1000;

				//달성도 체크 : 저축 습관(인벤토리에 있는 돈)
				ReportCheck(REPORT_ETC5, (int)robin.gold);
				break;
		}
	}

	//저장
	SaveFlag(0);

	//게임시
	SetData(NET_GAME_BUYSUCCESS);
	netStatus = NETSTATUS_INIT;
	SendData();
}

#ifdef SKT
void Authorize()
{
	// 인증 결과를 콜백함수로부터 얻기 위해 어플의 상태를 변경한다.
	// 호출된 콜백함수의 결과값에 따라 상태를 변경하게 된다.
	netStatus = NETSTATUS_INIT;

	// 라이브러리를 사용하기 위해 GXGLibCB 콜백 함수를 등록한다.
	gxgSetCB((GXGCB)GXGLibCB, (void *)null);

	// 인증을 받기위해 gxgInit() 함수를 호출한다.
	// GW 서버로 연결할때는 100byte 모두 0으로
	// BP 서버로 연결할때는 100Byte에 GW서버에서 받은 Session key를 입력해야 함.
	gxgInit(_MCID, phone, BP_SERVER_IP, BP_SERVER_PORT, g_InitCfm.sessionkey, &g_InitCfm);
}

void Charge(int value)
{
	char chargeID[11];

	netStatus = NETSTATUS_SEND;

	memset(chargeID, 0, 11);

	#ifdef TSTORE

	switch (value) {
		case 100:
			MC_knlSprintk(chargeID, "9000499654");
			break;
		case 200:
			MC_knlSprintk(chargeID, "9000499657");
			break;
		case 300:
			MC_knlSprintk(chargeID, "9000499660");
			break;
		case 500:
			MC_knlSprintk(chargeID, "9000499663");
			break;
		case 700:
			MC_knlSprintk(chargeID, "9000499665");
			break;
		case 800:
			MC_knlSprintk(chargeID, "9000499668");
			break;
		case 900:
			MC_knlSprintk(chargeID, "9000499670");
			break;
		case 1000:
			MC_knlSprintk(chargeID, "9000499671");
			break;
		case 1500:
			MC_knlSprintk(chargeID, "9000499673");
			break;
		case 1900:
			MC_knlSprintk(chargeID, "9000499674");
			break;
		case 2000:
			MC_knlSprintk(chargeID, "9000499676");
			break;
		case 2500:
			MC_knlSprintk(chargeID, "9000499677");
			break;
		case 2900:
			MC_knlSprintk(chargeID, "9000499678");
			break;
		case 4000:
			MC_knlSprintk(chargeID, "9000511127");
			break;
	}

	#else

	switch (value) {
		case 100:
			MC_knlSprintk(chargeID, "9000499654");
			break;
		case 200:
			MC_knlSprintk(chargeID, "9000499657");
			break;
		case 300:
			MC_knlSprintk(chargeID, "9000499660");
			break;
		case 500:
			MC_knlSprintk(chargeID, "9000499663");
			break;
		case 700:
			MC_knlSprintk(chargeID, "9000499665");
			break;
		case 800:
			MC_knlSprintk(chargeID, "9000499668");
			break;
		case 900:
			MC_knlSprintk(chargeID, "9000499670");
			break;
		case 1000:
			MC_knlSprintk(chargeID, "9000499671");
			break;
		case 1500:
			MC_knlSprintk(chargeID, "9000499673");
			break;
		case 1900:
			MC_knlSprintk(chargeID, "9000499674");
			break;
		case 2000:
			MC_knlSprintk(chargeID, "9000499676");
			break;
		case 2500:
			MC_knlSprintk(chargeID, "9000499677");
			break;
		case 2900:
			MC_knlSprintk(chargeID, "9000499678");
			break;
		case 4000:
			#ifdef EXP_GXG
			MC_knlSprintk(chargeID, "9000511128");
			#elif defined EXP_NATE
			MC_knlSprintk(chargeID, "9000511129");
			#elif defined EXP_NHN
			MC_knlSprintk(chargeID, "9000511130");
			#elif defined EXP_DAUM
			MC_knlSprintk(chargeID, "9000511131");
			#else
			MC_knlSprintk(chargeID, "9000511127");
			#endif
			break;
	}

	#endif

	#ifdef TESTBILL
	gxgCharge("0000000000", true, &g_Confirm);
	#else
	gxgCharge(chargeID, true, &g_Confirm);
	#endif
}

void ConnectCB(int type, int err, void *param)
{
	switch (type) {
		case GXG_NET_INIT:
			//서버 연결을 위한 Socket 초기화 및 생성시
			if (err < GXG_SUCCESS) {
				// < GXG_SUCCESS 일 경우 socket 초기화 실패 (err 값으로 오류 상태 체크)
				if (err == GXG_ERR_ALREADYCONNECTED)
					Authorize();
				else
					NetError(err);

				return;
			}
			// GXG_SUCCESS 일 경우 Socket 초기화 성공
			break;
		case GXG_NET_CONNECTING:
			// Socket을 통해 서버에 연결중일 경우
			if (err < GXG_SUCCESS) {
				// < GXG_SUCCESS 일 경우 socket 연결 시 실패 (err 값으로 오류 상태 체크)
				NetError(err);
				return;
			}
			// GXG_SUCCESS 일 경우 Socket 연결 성공
			break;
		case GXG_NET_CONNECTED:
			// 서버와의 연결이 성공했을 경우
			if (err < GXG_SUCCESS) {
				NetError(err);
				return;
			}

			//성공인 경우 인증을 받기 위해 라이브러리 콜백을 등록시키고 인증 패킷을 보냄
			Authorize();
			break;
		case GXG_NET_DISCONNECTED:
			// 서버와의 연결에 실패하거나 연결이 종료된 경우
		case GXG_NET_CLOSED:
			// 네트워크 연결 종료 시
			if (err < GXG_SUCCESS)
				NetError(err);
			else
				netStatus = NETSTATUS_OFFLINE;

			//if (err < GXG_FAILED)
			//	NetError(err);
			//switch (reconType) {
			//	case 0:
			//		if (err < GXG_FAILED)
			//			NetError(err);
			//		else if (err == M_E_NETCLOSE || err == M_E_SOCKETCLOSE)
			//			// 서버에서 연결을 끊은 경우
			//			NetError(err);
			//		break;
			//	case 2:
			//		// 연결 종료 후 재 연결시 딜레이 처리
			//		// 임의의 작업을 하여 시간을 지연시켜줍니다.
			//		//MC_knlSetTimer(&ntimer, 2000L, (void *)null);
			//		break;
			//}
			break;
	}
}

void GXGLibCB(int type, int err, int errParam, void *param)
{
	// 작업 중인 상황이므로 처리 하지 않는다.
	// 보내기(GXG_CBTYPE_SENDDATA) 또는 받기(GXG_CBTYPE_RECVDATA) 일 경우 이곳에서
	// errParam 값을 확인 하여 쓰거나 받은 bytes 를 확인 할 수 있다.
	if (err == GXG_ERR_ACTIVE) {
		// 샘플 소스에서는 별도의 처리하지 않는다.
	}
	else if (err < 0) {
		// 보내기 또는 받기 실패의 경우 (GXG_ERR_SEND_FAIL or GXG_ERR_RECV_FAIL)
		// err에서 플랫폼에서 넘겨준 에러 종류를 알 수 있다.
		// 에러 처리를 한다.
		NetError(err);
	}
	else {
		// 에러가 발생하지 않았다면 성공으로 보고 작업의 종류에 따라 처리 한다.
		switch (type) {
			case GXG_CBTYPE_INIT:
				// 인증 작업
				switch (g_InitCfm.resultCode) {
					case GE_SUCCESS:
						//정상 인증 이용자.
						SendData();
						break;
					//case GE_RETURN_URL:
					//	//GE_RETURN_URL을 보내는 경우는 Close Beta 만료일 경우 밖에 없다.
					//	reconType = 1;
					//
					//	if (g_InitCfm.priceCode == GXG_CALLCHARGE_EXPIRE)
					//		// 통화료가 만료된 경우(클로즈 베타 서비스 사용자의 기간 만료)
					//		netStatus = NETSTATUS_EXPIRE_USER;
					//	else if (g_InitCfm.priceCode == GXG_INFOCHARGE_EXPIRE)
					//		// 정보료가 만료된 경우(클로즈 베타 서비스 기간 만료)
					//		g_nAppState = NETSTATUS_EXPIRE_SERVICE;
					//	break;
					//case GE_PRICING_AUTH_FAIL:
					//	// 요금제 인증 실패
					//	gxgPriceQuery(&g_QueryCfm);
					//	break;
					case GE_RECON_GATEWAY:
						// G/W 서버로 재 접속
					case GE_RECON_FREE_BPSERVER:
						// BP 서버로 재 접속(비과금)
					case GE_RECON_CHARGE_BPSERVER:
						// BP 서버로 재 접속(과금)
						// 소켓접속만 종료 후 재접속을 하기 위해 Close()함수의 두번째 매개변수를 false로 지정한다.
						// 두번째 매개변수가 false일 경우 인터넷 접속은 유지하되 소켓 접속만을 종료한다.
						Close(false, false);
						return;
					default:
						// 결과값을 처리해야 하는 것들을 처리 하지 못하고 default까지 온다면
						// 오류가 발생한 것으므로 오류 처리를 합니다.
						NetError(g_InitCfm.resultCode);
						break;
				}
				break;
			case GXG_CBTYPE_CHARGE:
				// 과금이 성공 되었으며 어플 상태를 과금 성공 상태로 변경 후 어플 상태에 맞게 출력한다.
				netStatus = NETSTATUS_RESULT;

				#ifdef TESTBILL
				if (netType == NET_GAME_BUY || chargeStatus >= 5)
					AfterCharge2();
				else
					AfterCharge();
				#else

				if (g_Confirm)
					// 에러 처리를 한다.
					NetError(g_Confirm);
				else {
					//과금후의 각종 처리
					if (netType == NET_GAME_BUY || chargeStatus >= 5)
						AfterCharge2();
					else
						AfterCharge();
				}
				#endif
				break;
			//case GXG_CBTYPE_SVRCHANGE:
			//	// 서버변경이 성공 되었으며 어플 상태를 과금 성공 상태로 변경 후 어플 상태에 맞게 출력한다.
			//	netStatus = NETSTATUS_SVRCHANGE_OK;

			//	if (g_Confirm)
			//		// 에러 처리를 한다.
			//		NetError(g_Confirm);
			//	break;
			case GXG_CBTYPE_SENDDATA:
				// 서버에 Data를 전송 후 수신 결과 Data를 받기 위해 gxgReceiveData를 호출 한다
				ReceiveData();
				break;
			case GXG_CBTYPE_RECVDATA:
				// 위에서 호출한 gxgReceiveData의 작업이 성공하여 g_TempData.m_pBuff의 값이 제대로 들어온것이므로
				// 어플의 상태를 데이타 받기 성공으로 바꾸고 어플 상태에 맞게 출력한다.
				//gxgGetHeader(&g_Header);
				ResultData();
				break;
			//case GXG_CBTYPE_P_QUERY:
			//	// 요금제 조회 위한 데이터 통신이 완료 되다면 요금제 데이타 개수 만큼
			//	// 메모리 할당을 받은 후 gxgGetPriceInfo() 함수를 호출 하여 데이타를 가져옵니다.
			//	if (g_QueryCfm.resultCode == GE_SUCCESS) {
			//		if (g_QueryCfm.data_cnt > 0) {
			//			if (nPriceID) {
			//				MC_knlFree(nPrice);
			//				nPriceID = 0;
			//			}

			//			nPrice = MC_knlCalloc(sizeof(GXG_PricingData) * g_QueryCfm.data_cnt);
			//			nPriceID = MC_GETDPTR(nPrice);

			//			gxgGetPriceInfo(g_QueryCfm.data_cnt, nPriceID);
			//		}

			//		// 만료된 요금제 코드를 가져와 분류하여 처리한다.
			//		if (g_InitCfm.priceCode == GXG_CALLCHARGE_EXPIRE)
			//			// 통화료 만료 일 경우 처리
			//			netStatus = NETSTATUS_P_EXPIRE_CALLCHARGE;
			//		else if (g_InitCfm.priceCode == GXG_INFOCHARGE_EXPIRE)
			//			// 정보료 만료 일 경우 처리
			//			netStatus = NETSTATUS_P_EXPIRE_INFOCHARGE;
			//		else if (g_InitCfm.priceCode == GXG_BOTHCHARGE_EXPIRE)
			//			// 정보료 + 통화료 만료 일 경우
			//			netStatus = NETSTATUS_P_EXPIRE_BOTHCHARGE;

			//		if (g_QueryCfm.data_cnt > 0)
			//			// 요금 제 조회 후 오류가 없을 경우 첫 요금제 구매 패킷을 보낸다.
			//			gxgPriceBuy(1, ((GXG_PricingData *)nPriceID)->pid, &g_BuyCfm);
			//		else
			//			NetError(GE_PRICING_BUY_FAIL);
			//	}
			//	else
			//		NetError(g_QueryCfm.resultCode);
			//	break;
			//case GXG_CBTYPE_P_BUY:
			//	switch (netStatus) {
			//		case NETSTATUS_P_EXPIRE_CALLCHARGE:
			//		case NETSTATUS_P_EXPIRE_INFOCHARGE:
			//		case NETSTATUS_P_EXPIRE_BOTHCHARGE:
			//			if (g_BuyCfm.resultCode) {
			//				// 에러 처리를 한다.
			//				NetError(err);
			//				return;
			//			}

			//
			//			break;
			//	}
			//	break;
		}
	}
}
#else
void OpenSocket()
{
	int	ip = ConvertToINAddr(BP_SERVER_IP);
	int	port = MC_utilHtons(BP_SERVER_PORT);
	#ifdef LGT
	int saveport = MC_utilHtons(BP_SAVE_PORT);
	#endif

	#ifdef ASSA
	//if (drawHandle == MD_BILLINFO) {
	//	ip = ConvertToINAddr(ASSA_SERVER_IP);
	//	port = MC_utilHtons(ASSA_SERVER_PORT);
	//}
	#endif

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:OpenSocket - billcomm\n");
	#endif

	#ifdef LGT
	if (netType == NET_SAVE)
		MC_netSocketConnect(sockFD, ip, saveport, (NETSOCKCONNECTCB)SocketConnectCB, NULL);
	else
		MC_netSocketConnect(sockFD, ip, port, (NETSOCKCONNECTCB)SocketConnectCB, NULL);
	#else
	MC_netBillSocketConnect(sockFD, ip, port, BILLCOMMMODE, (NETSOCKCONNECTCB)SocketConnectCB, NULL);
	#endif
}

void ConnectCB(int error, void *param)
{

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:ConnectCB\n");
	#endif

	bNetConnected = true;

	if (netStatus == NETSTATUS_WAIT)
		return;
	else if (netStatus != NETSTATUS_CONNECT) {
		NetError(1);
		return;
	}

	if (error == 0 || error == M_E_ISCONN) {

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:MC_netConnect Success!\n");
		#endif

		#ifdef LGT
		if (netType == NET_SAVE)
			sockFD = MC_netSocket(MC_AF_INET, MC_SOCKET_STREAM);
		else
			sockFD = MC_netBillSocket(MC_AF_INET, MC_SOCKET_STREAM);
		#else
		sockFD = MC_netSocket(MC_AF_INET, MC_SOCKET_STREAM);
		#endif
		OpenSocket();

		if (sockFD < 0) {
			#ifdef KNLPRINT
			MC_knlPrintk("디버그:ConnectCB() - failed to get sockFD(%d)\n", sockFD);
			#endif

			netStatus = NETSTATUS_ERROR;
			NetError(1);
			return;
		}
	}
	else if (error == M_E_ERROR) {

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:MC_netConnect fail!\n");
		#endif

		NetError(1);
		bNetConnected = false;
		netFrame = 0;
		netStatus = NETSTATUS_WAIT;
	}
	else {
		netStatus = NETSTATUS_ERROR;
		NetError(1);
	}

	return;
}

//소켓콜백
#ifdef LGT
void SocketConnectCB(int fd, int error, void *param)
#else
void SocketConnectCB(int error, void *param)
#endif
{

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:SocketConnectCB\n");
	#endif

	if (netStatus != NETSTATUS_CONNECT) {
		NetError(1);
		return;
	}

	if (error == 0) {
		netStatus = NETSTATUS_INIT;

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:netBillSocketConnect success!\n");
		#endif

		bSockConnected = true;
		SendData();
	}
	else if (error == M_E_ERROR) {

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:netBillSocketConnect failure!\n");
		#endif

		netStatus = NETSTATUS_ERROR;
		NetError(1);
		bSockConnected = false;
	}
	else {

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:netBillSocketConnect failure! error Num %d\n", error);
		#endif

		netStatus = NETSTATUS_ERROR;
		NetError(1);
	}

	return;
}

//패킷 보내기
int SendPacket()
{
	int ret = 0;

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:SendPacket\n");
	#endif

	if (netStatus == NETSTATUS_ERROR) {
		NetError(1);
		return -1;
	}

	if (bSockConnected) {
		net_Offset = 0;
		net_RemainSize = nDataLen;

		ret = SendPacket0();

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:SendPacket return1=%d\n", ret);
		#endif

		if (ret < 0) {
			netStatus = NETSTATUS_ERROR;
			NetError(1);
			return -1;
		}
		else
			return true;
	}
	else {

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:SendPacket return2=%d\n", ret);
		#endif

		netStatus = NETSTATUS_ERROR;
		NetError(1);
		return -1;
	}
}

//패킷 보내기0
int SendPacket0()
{
	int ret;

	while (1) {
		#ifdef LGT
		ret = MC_netSocketWrite(sockFD, (M_Byte *)MC_GETDPTR(nBuff_Send) + net_Offset, net_RemainSize);
		#else
		ret = MC_netBillSocketWrite(sockFD, (char *)MC_GETDPTR(nBuff_Send) + net_Offset, net_RemainSize);
		#endif

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:Sendreturn1=%d\n", ret);
		#endif

		if (ret < 0) {
			if (ret == M_E_WOULDBLOCK) {

				#ifdef KNLPRINT
				MC_knlPrintk("디버그:Write - [M_E_WOULDBLOCK] remainsize(%d)\n", net_RemainSize);
				#endif

				ret = MC_netSetWriteCB(sockFD, (NETSOCKWRITECB)SockWriteCB, NULL);

				if (ret < 0)
					return M_E_ERROR;

				return 0;
			}

			NetError(1);
			return M_E_ERROR;
		}
		else if (ret == 0) {
			NetError(1);
			return M_E_ERROR;
		}

		net_Offset += ret;
		net_RemainSize -= ret;

		if (net_RemainSize == 0)
			break;
	}

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:Call Receiver\n");
	#endif

	MC_knlSetTimer(&rtimer, 1000, (void *)null);

	//if (drawHandle == MD_BILLINFO) {
	//	MC_knlUnsetTimer(&ntimer);
	//	MC_knlSetTimer(&ntimer, 40000, (void *)null);
	//	#ifdef KNLPRINT
	//	MC_knlPrintk("타이머 40초 셋팅");
	//	#endif
	//}
	//else {
	//	MC_knlSetTimer(&ntimer, 15000, (void *)null);
	//	#ifdef KNLPRINT
	//	MC_knlPrintk("타이머 15초 셋팅");
	//	#endif
	//}

	return 0;
}

//소켓에 데이터 쓰기
static void SockWriteCB(int fd, int error, void *param)
{

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:App SockWriteCB\n");
	#endif

	if (netStatus != NETSTATUS_SEND) {
		NetError(1);
		return;
	}

	if (error < 0) {
		netStatus = NETSTATUS_ERROR;
		NetError(1);
		return;
	}

	SendPacket0();
}

//패킷 받기0
int RecvPacket0(int cmd)
{
	int ret, size;

	#ifdef ASSA
	//if (drawHandle == MD_BILLINFO) {
	//	net_Offset = 0;
	//	size_recevied = 1;
	//	net_RemainSize = (menuDepth < 5 ? 5 : 905);
	//	#ifdef DOWNLOAD
	//	receiveSize = net_RemainSize;
	//	#endif
	//}
	#endif

	if (size_recevied == 0) {
		while (1) {
			#ifdef LGT
			ret = MC_netSocketRead(sockFD, (M_Byte *)&size, 4);
			#else
			ret = MC_netBillSocketRead(sockFD, &size, 4);
			#endif

			#ifdef KNLPRINT
			MC_knlPrintk("디버그:Read Packet Size:%d\n", ret);
			#endif

			if (ret < 0) {
				if (ret == M_E_WOULDBLOCK) {

					#ifdef KNLPRINT
					MC_knlPrintk("디버그:Read - [M_E_WOULDBLOCK]\n");
					#endif

					ret = MC_netSetReadCB(sockFD, SockReadCB, (void *)cmd);

					if (ret < 0)
						return M_E_ERROR;

					return 0;
				}

				#ifdef KTF
				if (ret == M_E_BILLCOMM_NOTI)
					return M_E_BILLCOMM_NOTI;
				#endif

				NetError(1);
				return M_E_ERROR;
			}
			else if (ret == 0) {
				NetError(1);
				return M_E_ERROR;
			}

			net_Offset += ret;

			if (net_Offset >= 4) {
				net_Offset = 0;
				size_recevied = 1;
				net_RemainSize = MC_utilNtohl(size);
				#ifdef DOWNLOAD
				receiveSize = net_RemainSize;
				#endif
				break;
			}
		}
	}

	while (1) {
		#ifdef LGT
		ret = MC_netSocketRead(sockFD, (M_Byte *)MC_GETDPTR(nBuff_Recv) + net_Offset, net_RemainSize);
		#else
		ret = MC_netBillSocketRead(sockFD, (char *)MC_GETDPTR(nBuff_Recv) + net_Offset, net_RemainSize);
		#endif

		#ifdef KNLPRINT
		MC_knlPrintk("디버그:Read from %d to %d\n", net_Offset, net_RemainSize);
		#endif

		if (ret < 0) {
			if (ret == M_E_WOULDBLOCK) {

				#ifdef KNLPRINT
				MC_knlPrintk("디버그:Read - [M_E_WOULDBLOCK] remainsize(%d)\n", net_RemainSize);
				#endif

				ret = MC_netSetReadCB(sockFD, SockReadCB, (void *)cmd);

				if (ret < 0)
					return M_E_ERROR;

				return 0;
			}

			#ifdef KTF
			if (ret == M_E_BILLCOMM_NOTI)
				return M_E_BILLCOMM_NOTI;
			#endif

			NetError(1);
			return M_E_ERROR;
		}
		else if (ret == 0) {
			#ifdef KNLPRINT
			MC_knlPrintk("디버그:Cannot Read. Remain Size=%d\n", net_RemainSize);
			#endif

			NetError(1);
			return M_E_ERROR;
		}

		net_Offset += ret;
		net_RemainSize -= ret;

		if (net_RemainSize <= 0) {
			#ifdef KNLPRINT
			MC_knlPrintk("디버그:Receive Complete\n");
			#endif

			break;
		}
	}

	if (netStatus == NETSTATUS_ERROR) {
		NetError(1);
		return false;
	}

	ResultData();

	return 0;
}

static void SockReadCB(int fd, int error, void *param)
{
	int ret;

	#ifdef KNLPRINT
	MC_knlPrintk("디버그:App SockReadCB Err : %d\n", error);
	#endif

	if (netStatus == NETSTATUS_ERROR) {
		NetError(1);
		return;
	}

	if (error < 0) {
		netStatus = NETSTATUS_ERROR;
		NetError(1);
		return;
	}

	ret = RecvPacket0((M_Int32)param);

	#ifdef KTF
	if (ret == M_E_BILLCOMM_NOTI) {
		//memset(returnBuffer, 0, 256);
		//net_Buffer= (M_Int8 *)&returnBuffer;
		//net_Offset = 0;
		//net_RemainSize = 256;
	}
	#endif

	if (ret < 0)
		NetError(1);
}

//void ReceiveTimer(MCTimer *ptm, void *param)
//{
//	ReceiveData();
//}

//Address 변경
int ConvertToINAddr(char *psz)
{
	int ul = 0;
	int nByte = 0;
	char c;

	if (!psz)
		return 0;

	while (ISDIGIT(*psz))
	{
		M_Int32 n = 0;

		while (ISDIGIT(c = *psz)) {
			n = n * 10 + (c - '0');
			++psz;
		}

		((char *)&ul)[nByte++] = n;

		if (nByte == 4 || *psz != '.')
			break;
		++psz;
	}

	if (nByte < 4 || ISALNUM(*psz))
		ul = 0;
	return ul;
}
#endif

//void NetTimer(MCTimer *ptm, void *param)
//{
//	if (param)
//		NetError(0);
//	else
//		NetError(1);
//}

//void ScreenTimer(MCTimer *ptm, void *param)
//{
//	netStatus = NETSTATUS_INIT;
//	SendData();
//	MC_knlUnsetTimer(&ntimer);
//	MC_knlSetTimer(&ntimer, 15000, (void *)&frame);
//}

void NetConnectDraw(void)
{
	int i;
	int y = (netType == NET_LOAD || netType == NET_SAVE) ? (DY / 2 - 60) : (DY / 2 - 24);

	if (netStatus == NETSTATUS_LOCK) {
		DrawFrame(DX / 2 - 80, DY / 2 - 60, 160, 130, FRAME_NORMAL);
		LineText(TEXT_INTERNET_LOCK - 1 + netLock, DX / 2 - 72, DY / 2 - 52, 144);
		DrawButton(DX / 2 - 7, DY / 2 + 50, ALPHA_OK);
	}
	else if (netStatus >= NETSTATUS_CONNECT) {
		#ifdef DOWNLOAD
		if (netType == NET_FILE_DOWNLOAD) {
			int width = curFile * 100 / TOTALFILE;

			if (width > 0) {
				MemRect(DX / 2 - 87 + 37, DY / 2 - 99 + 137, Min(width, 100), 10, 0xFFCF5A);
				MemRect(DX / 2 - 87 + 37, DY / 2 - 99 + 140, Min(width, 100), 6, 0xFF8629);
				MemRect(DX / 2 - 87 + 37, DY / 2 - 99 + 142, Min(width, 100), 2, 0xFF6518);
				MemRect(DX / 2 - 30, DY / 2 - 99 + 151, 60, 11, 0x00000);
			}

			CenterTextStr(tempStr, DX / 2, DY / 2 - 99 + 150);
		}
		else
		#endif

		if (netType == NET_SCREEN) {
			int width = (screenOffset - SCREENUPLOADSIZE) * 100 / (DX * DY * 2);

			DrawFrame(DX / 2 - 54, DY / 2 - 110 + 121, 108, 31, FRAME_CHOICEBUTTON);

			if (width > 0) {
				MemRect(DX / 2 - 87 + 37, DY / 2 - 110 + 138, Min(width, 100), 10, 0xFFCF5A);
				MemRect(DX / 2 - 87 + 37, DY / 2 - 110 + 141, Min(width, 100), 6, 0xFF8629);
				MemRect(DX / 2 - 87 + 37, DY / 2 - 110 + 143, Min(width, 100), 2, 0xFF6518);
			}

			CenterTextStr(tempStr, DX / 2, DY / 2 - 110 + 123);
		}
		else
		#ifdef USERCHECK
		if (netType != NET_USER_CHECK)
		#endif
		{
			DrawFrame(DX / 2 - 42, y, 84, 24, FRAME_CHOICEBUTTON);

			for (i = 0; i < 10; i++)
				MemRect(DX / 2 - 40 + i * 8, y + 19, 8, 3, d.colorData[9 + Abs(8 - (frame + i) % 16)]);

			temp = TEXT_NET_CONNECT;

			if (netStatus == NETSTATUS_SEND)
				temp = TEXT_NET_SEND;
			else if (netStatus == NETSTATUS_RECEIVE)
				temp = TEXT_NET_RECEIVE;

			CenterText(temp, DX / 2, y + 4);

			progress++;
		}
	}
}