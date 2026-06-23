#pragma once
#include "../Def.h"
#include "../Write.h"

#ifndef _DATA_MAP_H_
#define _DATA_MAP_H_

const unsigned char* const mapPtr[TOTALMAP] = {
	ma0, ma1, ma2, ma3,
	ma4, ma5, ma6, ma7, ma8, ma9,
	ma10, ma11, ma12, ma13, ma14, ma15, ma16, ma17, ma18, ma19, ma20, ma21, ma22, ma23, ma24, ma25,
	ma26, ma27, ma28, ma29, ma30, ma31, ma32, ma33, ma34, ma35, ma36, ma37, ma38, ma39, ma40, ma41, ma42,
	ma43, ma44, ma45, ma46, ma47, ma48, ma49, ma50, ma51, ma52, ma53, ma54, ma55, ma56, ma57, ma58, ma59, ma60, ma61, ma62,
	ma63, ma64, ma65, ma66, ma67, ma68, ma69, ma70, ma71, ma72, ma73, ma74, ma75, ma76, ma77, ma78, ma79, ma80, ma81,
	ma82, ma83, ma84, ma85, ma86, ma87, ma88, ma89, ma90, ma91, ma92, ma93, ma94, ma95, ma96,
	ma97, ma98, ma99, ma100, ma101, ma102, ma103, ma104, ma105, ma106, ma107, ma108, ma109, ma110, ma111, ma112, ma113,
	ma114,
	ma115, ma116, ma117, ma118, ma119, ma120, ma121, ma122, ma123, ma124, ma125,
	ma126, ma127, ma128, ma129, ma130, ma131, ma132, ma133, ma134, ma135, ma136, ma137, ma138, ma139, ma140, ma141, ma142, ma143, ma144,
	ma145, ma146, ma147, ma148, ma149, ma150, ma151, ma152, ma153, ma154, ma155, ma156, ma157, ma158, ma159, ma160, ma161, ma162, ma163, ma164, ma165,
	ma166, ma167, ma168, ma169, ma170, ma171, ma172, ma173, ma174, ma175, ma176, ma177, ma178, ma179, ma180, ma181, ma182, ma183, ma184,
	ma185, ma186, ma187, ma188, ma189, ma190, ma191, ma192, ma193, ma194, ma195, ma196, ma197, ma198, ma199, ma200, ma201, ma202, ma203, ma204,
	ma205, ma206, ma207, ma208, ma209, ma210, ma211, ma212, ma213, ma214, ma215, ma216, ma217, ma218, ma219, ma220, ma221, ma222, ma223, ma224, ma225,
	ma226, ma227, ma228, ma229, ma230, ma231, ma232, ma233, ma234, ma235, ma236, ma237, ma238, ma239, ma240, ma241, ma242, ma243,
	ma244, ma245, ma246, ma247, ma248, ma249, ma250, ma251, ma252, ma253, ma254, ma255, ma256, ma257, ma258, ma259, ma260, ma261, ma262,
	ma263, ma264, ma265, ma266, ma267, ma268, ma269, ma270, ma271, ma272, ma273, ma274, ma275, ma276, ma277, ma278, ma279,
	ma280, ma281, ma282, ma283, ma284, ma285, ma286, ma287, ma288, ma289, ma290, ma291, ma292, ma293,
	ma294, ma295, ma296, ma297, ma298, ma299, ma300, ma301, ma302, ma303, ma304, ma305, ma306,
	ma307, ma308, ma309, ma310, ma311, ma312, ma313, ma314, ma315, ma316, ma317, ma318, ma319, ma320, ma321, ma322, ma323, ma324, ma325, ma326, ma327, ma328, ma329, ma330, ma331, ma332, ma333, ma334, ma335, ma336, ma337, ma338, ma339, ma340, ma341, ma342, ma343, ma344, ma345, ma346, ma347, ma348, ma349, ma350, ma351, ma352, ma353, ma354, ma355, ma356, ma357, ma358, ma359, ma360, ma361, ma362, ma363,
	ma364,
	ma365, ma366, ma367, ma368, ma369, ma370, ma371, ma372, ma373, ma374,
	ma375, ma376, ma377, ma378, ma379, ma380, ma381, ma382, ma383, ma384,
	ma385, ma386, ma387, ma388, ma389, ma390, ma391, ma392, ma393, ma394,
	ma395, ma396, ma397, ma398, ma399, ma400, ma401, ma402, ma403, ma404,
	ma405,
	ma406, ma407, ma408, ma409, ma410, ma411, ma412, ma413, ma414, ma415, ma416, ma417, ma418, ma419, ma420, ma421, ma422, ma423, ma424,

};

const unsigned char* const mapTilePtr[TOTALMAP] = {
	mt0, mt1, mt2, mt3,
	mt4, mt5, mt6, mt7, mt8, mt9,
	mt10, mt11, mt12, mt13, mt14, mt15, mt16, mt17, mt18, mt19, mt20, mt21, mt22, mt23, mt24, mt25,
	mt26, mt27, mt28, mt29, mt30, mt31, mt32, mt33, mt34, mt35, mt36, mt37, mt38, mt39, mt40, mt41, mt42,
	mt43, mt44, mt45, mt46, mt47, mt48, mt49, mt50, mt51, mt52, mt53, mt54, mt55, mt56, mt57, mt58, mt59, mt60, mt61, mt62,
	mt63, mt64, mt65, mt66, mt67, mt68, mt69, mt70, mt71, mt72, mt73, mt74, mt75, mt76, mt77, mt78, mt79, mt80, mt81,
	mt82, mt83, mt84, mt85, mt86, mt87, mt88, mt89, mt90, mt91, mt92, mt93, mt94, mt95, mt96,
	mt97, mt98, mt99, mt100, mt101, mt102, mt103, mt104, mt105, mt106, mt107, mt108, mt109, mt110, mt111, mt112, mt113,
	mt114,
	mt115, mt116, mt117, mt118, mt119, mt120, mt121, mt122, mt123, mt124, mt125,
	mt126, mt127, mt128, mt129, mt130, mt131, mt132, mt133, mt134, mt135, mt136, mt137, mt138, mt139, mt140, mt141, mt142, mt143, mt144,
	mt145, mt146, mt147, mt148, mt149, mt150, mt151, mt152, mt153, mt154, mt155, mt156, mt157, mt158, mt159, mt160, mt161, mt162, mt163, mt164, mt165,
	mt166, mt167, mt168, mt169, mt170, mt171, mt172, mt173, mt174, mt175, mt176, mt177, mt178, mt179, mt180, mt181, mt182, mt183, mt184,
	mt185, mt186, mt187, mt188, mt189, mt190, mt191, mt192, mt193, mt194, mt195, mt196, mt197, mt198, mt199, mt200, mt201, mt202, mt203, mt204,
	mt205, mt206, mt207, mt208, mt209, mt210, mt211, mt212, mt213, mt214, mt215, mt216, mt217, mt218, mt219, mt220, mt221, mt222, mt223, mt224, mt225,
	mt226, mt227, mt228, mt229, mt230, mt231, mt232, mt233, mt234, mt235, mt236, mt237, mt238, mt239, mt240, mt241, mt242, mt243,
	mt244, mt245, mt246, mt247, mt248, mt249, mt250, mt251, mt252, mt253, mt254, mt255, mt256, mt257, mt258, mt259, mt260, mt261, mt262,
	mt263, mt264, mt265, mt266, mt267, mt268, mt269, mt270, mt271, mt272, mt273, mt274, mt275, mt276, mt277, mt278, mt279,
	mt280, mt281, mt282, mt283, mt284, mt285, mt286, mt287, mt288, mt289, mt290, mt291, mt292, mt293,
	mt294, mt295, mt296, mt297, mt298, mt299, mt300, mt301, mt302, mt303, mt304, mt305, mt306,
	mt307, mt308, mt309, mt310, mt311, mt312, mt313, mt314, mt315, mt316, mt317, mt318, mt319, mt320, mt321, mt322, mt323, mt324, mt325, mt326, mt327, mt328, mt329, mt330, mt331, mt332, mt333, mt334, mt335, mt336, mt337, mt338, mt339, mt340, mt341, mt342, mt343, mt344, mt345, mt346, mt347, mt348, mt349, mt350, mt351, mt352, mt353, mt354, mt355, mt356, mt357, mt358, mt359, mt360, mt361, mt362, mt363,
	mt364,
	mt365, mt366, mt367, mt368, mt369, mt370, mt371, mt372, mt373, mt374,
	mt375, mt376, mt377, mt378, mt379, mt380, mt381, mt382, mt383, mt384,
	mt385, mt386, mt387, mt388, mt389, mt390, mt391, mt392, mt393, mt394,
	mt395, mt396, mt397, mt398, mt399, mt400, mt401, mt402, mt403, mt404,
	mt405,
	mt406, mt407, mt408, mt409, mt410, mt411, mt412, mt413, mt414, mt415, mt416, mt417, mt418, mt419, mt420, mt421, mt422, mt423, mt424,

};

const unsigned char* const mapRectPtr[TOTALMAP] = {
	mr0, mr1, mr2, mr3,
	mr4, mr5, mr6, mr7, mr8, mr9,
	mr10, mr11, mr12, mr13, mr14, mr15, mr16, mr17, mr18, mr19, mr20, mr21, mr22, mr23, mr24, mr25,
	mr26, mr27, mr28, mr29, mr30, mr31, mr32, mr33, mr34, mr35, mr36, mr37, mr38, mr39, mr40, mr41, mr42,
	mr43, mr44, mr45, mr46, mr47, mr48, mr49, mr50, mr51, mr52, mr53, mr54, mr55, mr56, mr57, mr58, mr59, mr60, mr61, mr62,
	mr63, mr64, mr65, mr66, mr67, mr68, mr69, mr70, mr71, mr72, mr73, mr74, mr75, mr76, mr77, mr78, mr79, mr80, mr81,
	mr82, mr83, mr84, mr85, mr86, mr87, mr88, mr89, mr90, mr91, mr92, mr93, mr94, mr95, mr96,
	mr97, mr98, mr99, mr100, mr101, mr102, mr103, mr104, mr105, mr106, mr107, mr108, mr109, mr110, mr111, mr112, mr113,
	mr114,
	mr115, mr116, mr117, mr118, mr119, mr120, mr121, mr122, mr123, mr124, mr125,
	mr126, mr127, mr128, mr129, mr130, mr131, mr132, mr133, mr134, mr135, mr136, mr137, mr138, mr139, mr140, mr141, mr142, mr143, mr144,
	mr145, mr146, mr147, mr148, mr149, mr150, mr151, mr152, mr153, mr154, mr155, mr156, mr157, mr158, mr159, mr160, mr161, mr162, mr163, mr164, mr165,
	mr166, mr167, mr168, mr169, mr170, mr171, mr172, mr173, mr174, mr175, mr176, mr177, mr178, mr179, mr180, mr181, mr182, mr183, mr184,
	mr185, mr186, mr187, mr188, mr189, mr190, mr191, mr192, mr193, mr194, mr195, mr196, mr197, mr198, mr199, mr200, mr201, mr202, mr203, mr204,
	mr205, mr206, mr207, mr208, mr209, mr210, mr211, mr212, mr213, mr214, mr215, mr216, mr217, mr218, mr219, mr220, mr221, mr222, mr223, mr224, mr225,
	mr226, mr227, mr228, mr229, mr230, mr231, mr232, mr233, mr234, mr235, mr236, mr237, mr238, mr239, mr240, mr241, mr242, mr243,
	mr244, mr245, mr246, mr247, mr248, mr249, mr250, mr251, mr252, mr253, mr254, mr255, mr256, mr257, mr258, mr259, mr260, mr261, mr262,
	mr263, mr264, mr265, mr266, mr267, mr268, mr269, mr270, mr271, mr272, mr273, mr274, mr275, mr276, mr277, mr278, mr279,
	mr280, mr281, mr282, mr283, mr284, mr285, mr286, mr287, mr288, mr289, mr290, mr291, mr292, mr293,
	mr294, mr295, mr296, mr297, mr298, mr299, mr300, mr301, mr302, mr303, mr304, mr305, mr306,
	mr307, mr308, mr309, mr310, mr311, mr312, mr313, mr314, mr315, mr316, mr317, mr318, mr319, mr320, mr321, mr322, mr323, mr324, mr325, mr326, mr327, mr328, mr329, mr330, mr331, mr332, mr333, mr334, mr335, mr336, mr337, mr338, mr339, mr340, mr341, mr342, mr343, mr344, mr345, mr346, mr347, mr348, mr349, mr350, mr351, mr352, mr353, mr354, mr355, mr356, mr357, mr358, mr359, mr360, mr361, mr362, mr363,
	mr364,
	mr365, mr366, mr367, mr368, mr369, mr370, mr371, mr372, mr373, mr374,
	mr375, mr376, mr377, mr378, mr379, mr380, mr381, mr382, mr383, mr384,
	mr385, mr386, mr387, mr388, mr389, mr390, mr391, mr392, mr393, mr394,
	mr395, mr396, mr397, mr398, mr399, mr400, mr401, mr402, mr403, mr404,
	mr405,
	mr406, mr407, mr408, mr409, mr410, mr411, mr412, mr413, mr414, mr415, mr416, mr417, mr418, mr419, mr420, mr421, mr422, mr423, mr424,
};

const unsigned int mapRectSize[TOTALMAP] = {
	sizeof(mr0) / 5, sizeof(mr1) / 5, sizeof(mr2) / 5, sizeof(mr3) / 5,
	sizeof(mr4) / 5, sizeof(mr5) / 5, sizeof(mr6) / 5, sizeof(mr7) / 5, sizeof(mr8) / 5, sizeof(mr9) / 5,
	sizeof(mr10) / 5, sizeof(mr11) / 5, sizeof(mr12) / 5, sizeof(mr13) / 5, sizeof(mr14) / 5, sizeof(mr15) / 5, sizeof(mr16) / 5, sizeof(mr17) / 5, sizeof(mr18) / 5, sizeof(mr19) / 5, sizeof(mr20) / 5, sizeof(mr21) / 5, sizeof(mr22) / 5, sizeof(mr23) / 5, sizeof(mr24) / 5, sizeof(mr25) / 5,
	sizeof(mr26) / 5, sizeof(mr27) / 5, sizeof(mr28) / 5, sizeof(mr29) / 5, sizeof(mr30) / 5, sizeof(mr31) / 5, sizeof(mr32) / 5, sizeof(mr33) / 5, sizeof(mr34) / 5, sizeof(mr35) / 5, sizeof(mr36) / 5, sizeof(mr37) / 5, sizeof(mr38) / 5, sizeof(mr39) / 5, sizeof(mr40) / 5, sizeof(mr41) / 5, sizeof(mr42) / 5,
	sizeof(mr43) / 5, sizeof(mr44) / 5, sizeof(mr45) / 5, sizeof(mr46) / 5, sizeof(mr47) / 5, sizeof(mr48) / 5, sizeof(mr49) / 5, sizeof(mr50) / 5, sizeof(mr51) / 5, sizeof(mr52) / 5, sizeof(mr53) / 5, sizeof(mr54) / 5, sizeof(mr55) / 5, sizeof(mr56) / 5, sizeof(mr57) / 5, sizeof(mr58) / 5, sizeof(mr59) / 5, sizeof(mr60) / 5, sizeof(mr61) / 5, sizeof(mr62) / 5,
	sizeof(mr63) / 5, sizeof(mr64) / 5, sizeof(mr65) / 5, sizeof(mr66) / 5, sizeof(mr67) / 5, sizeof(mr68) / 5, sizeof(mr69) / 5, sizeof(mr70) / 5, sizeof(mr71) / 5, sizeof(mr72) / 5, sizeof(mr73) / 5, sizeof(mr74) / 5, sizeof(mr75) / 5, sizeof(mr76) / 5, sizeof(mr77) / 5, sizeof(mr78) / 5, sizeof(mr79) / 5, sizeof(mr80) / 5, sizeof(mr81) / 5,
	sizeof(mr82) / 5, sizeof(mr83) / 5, sizeof(mr84) / 5, sizeof(mr85) / 5, sizeof(mr86) / 5, sizeof(mr87) / 5, sizeof(mr88) / 5, sizeof(mr89) / 5, sizeof(mr90) / 5, sizeof(mr91) / 5, sizeof(mr92) / 5, sizeof(mr93) / 5, sizeof(mr94) / 5, sizeof(mr95) / 5, sizeof(mr96) / 5,
	sizeof(mr97) / 5, sizeof(mr98) / 5, sizeof(mr99) / 5, sizeof(mr100) / 5, sizeof(mr101) / 5, sizeof(mr102) / 5, sizeof(mr103) / 5, sizeof(mr104) / 5, sizeof(mr105) / 5, sizeof(mr106) / 5, sizeof(mr107) / 5, sizeof(mr108) / 5, sizeof(mr109) / 5, sizeof(mr110) / 5, sizeof(mr111) / 5, sizeof(mr112) / 5, sizeof(mr113) / 5,
	sizeof(mr114) / 5,
	sizeof(mr115) / 5, sizeof(mr116) / 5, sizeof(mr117) / 5, sizeof(mr118) / 5, sizeof(mr119) / 5, sizeof(mr120) / 5, sizeof(mr121) / 5, sizeof(mr122) / 5, sizeof(mr123) / 5, sizeof(mr124) / 5, sizeof(mr125) / 5,
	sizeof(mr126) / 5, sizeof(mr127) / 5, sizeof(mr128) / 5, sizeof(mr129) / 5, sizeof(mr130) / 5, sizeof(mr131) / 5, sizeof(mr132) / 5, sizeof(mr133) / 5, sizeof(mr134) / 5, sizeof(mr135) / 5, sizeof(mr136) / 5, sizeof(mr137) / 5, sizeof(mr138) / 5, sizeof(mr139) / 5, sizeof(mr140) / 5, sizeof(mr141) / 5, sizeof(mr142) / 5, sizeof(mr143) / 5, sizeof(mr144) / 5,
	sizeof(mr145) / 5, sizeof(mr146) / 5, sizeof(mr147) / 5, sizeof(mr148) / 5, sizeof(mr149) / 5, sizeof(mr150) / 5, sizeof(mr151) / 5, sizeof(mr152) / 5, sizeof(mr153) / 5, sizeof(mr154) / 5, sizeof(mr155) / 5, sizeof(mr156) / 5, sizeof(mr157) / 5, sizeof(mr158) / 5, sizeof(mr159) / 5, sizeof(mr160) / 5, sizeof(mr161) / 5, sizeof(mr162) / 5, sizeof(mr163) / 5, sizeof(mr164) / 5, sizeof(mr165) / 5,
	sizeof(mr166) / 5, sizeof(mr167) / 5, sizeof(mr168) / 5, sizeof(mr169) / 5, sizeof(mr170) / 5, sizeof(mr171) / 5, sizeof(mr172) / 5, sizeof(mr173) / 5, sizeof(mr174) / 5, sizeof(mr175) / 5, sizeof(mr176) / 5, sizeof(mr177) / 5, sizeof(mr178) / 5, sizeof(mr179) / 5, sizeof(mr180) / 5, sizeof(mr181) / 5, sizeof(mr182) / 5, sizeof(mr183) / 5, sizeof(mr184) / 5,
	sizeof(mr185) / 5, sizeof(mr186) / 5, sizeof(mr187) / 5, sizeof(mr188) / 5, sizeof(mr189) / 5, sizeof(mr190) / 5, sizeof(mr191) / 5, sizeof(mr192) / 5, sizeof(mr193) / 5, sizeof(mr194) / 5, sizeof(mr195) / 5, sizeof(mr196) / 5, sizeof(mr197) / 5, sizeof(mr198) / 5, sizeof(mr199) / 5, sizeof(mr200) / 5, sizeof(mr201) / 5, sizeof(mr202) / 5, sizeof(mr203) / 5, sizeof(mr204) / 5,
	sizeof(mr205) / 5, sizeof(mr206) / 5, sizeof(mr207) / 5, sizeof(mr208) / 5, sizeof(mr209) / 5, sizeof(mr210) / 5, sizeof(mr211) / 5, sizeof(mr212) / 5, sizeof(mr213) / 5, sizeof(mr214) / 5, sizeof(mr215) / 5, sizeof(mr216) / 5, sizeof(mr217) / 5, sizeof(mr218) / 5, sizeof(mr219) / 5, sizeof(mr220) / 5, sizeof(mr221) / 5, sizeof(mr222) / 5, sizeof(mr223) / 5, sizeof(mr224) / 5, sizeof(mr225) / 5,
	sizeof(mr226) / 5, sizeof(mr227) / 5, sizeof(mr228) / 5, sizeof(mr229) / 5, sizeof(mr230) / 5, sizeof(mr231) / 5, sizeof(mr232) / 5, sizeof(mr233) / 5, sizeof(mr234) / 5, sizeof(mr235) / 5, sizeof(mr236) / 5, sizeof(mr237) / 5, sizeof(mr238) / 5, sizeof(mr239) / 5, sizeof(mr240) / 5, sizeof(mr241) / 5, sizeof(mr242) / 5, sizeof(mr243) / 5,
	sizeof(mr244) / 5, sizeof(mr245) / 5, sizeof(mr246) / 5, sizeof(mr247) / 5, sizeof(mr248) / 5, sizeof(mr249) / 5, sizeof(mr250) / 5, sizeof(mr251) / 5, sizeof(mr252) / 5, sizeof(mr253) / 5, sizeof(mr254) / 5, sizeof(mr255) / 5, sizeof(mr256) / 5, sizeof(mr257) / 5, sizeof(mr258) / 5, sizeof(mr259) / 5, sizeof(mr260) / 5, sizeof(mr261) / 5, sizeof(mr262) / 5,
	sizeof(mr263) / 5, sizeof(mr264) / 5, sizeof(mr265) / 5, sizeof(mr266) / 5, sizeof(mr267) / 5, sizeof(mr268) / 5, sizeof(mr269) / 5, sizeof(mr270) / 5, sizeof(mr271) / 5, sizeof(mr272) / 5, sizeof(mr273) / 5, sizeof(mr274) / 5, sizeof(mr275) / 5, sizeof(mr276) / 5, sizeof(mr277) / 5, sizeof(mr278) / 5, sizeof(mr279) / 5,
	sizeof(mr280) / 5, sizeof(mr281) / 5, sizeof(mr282) / 5, sizeof(mr283) / 5, sizeof(mr284) / 5, sizeof(mr285) / 5, sizeof(mr286) / 5, sizeof(mr287) / 5, sizeof(mr288) / 5, sizeof(mr289) / 5, sizeof(mr290) / 5, sizeof(mr291) / 5, sizeof(mr292) / 5, sizeof(mr293) / 5,
	sizeof(mr294) / 5, sizeof(mr295) / 5, sizeof(mr296) / 5, sizeof(mr297) / 5, sizeof(mr298) / 5, sizeof(mr299) / 5, sizeof(mr300) / 5, sizeof(mr301) / 5, sizeof(mr302) / 5, sizeof(mr303) / 5, sizeof(mr304) / 5, sizeof(mr305) / 5, sizeof(mr306) / 5,
	sizeof(mr307) / 5, sizeof(mr308) / 5, sizeof(mr309) / 5, sizeof(mr310) / 5, sizeof(mr311) / 5, sizeof(mr312) / 5, sizeof(mr313) / 5, sizeof(mr314) / 5, sizeof(mr315) / 5, sizeof(mr316) / 5, sizeof(mr317) / 5, sizeof(mr318) / 5, sizeof(mr319) / 5, sizeof(mr320) / 5, sizeof(mr321) / 5, sizeof(mr322) / 5, sizeof(mr323) / 5, sizeof(mr324) / 5, sizeof(mr325) / 5, sizeof(mr326) / 5, sizeof(mr327) / 5, sizeof(mr328) / 5, sizeof(mr329) / 5, sizeof(mr330) / 5, sizeof(mr331) / 5, sizeof(mr332) / 5, sizeof(mr333) / 5, sizeof(mr334) / 5, sizeof(mr335) / 5, sizeof(mr336) / 5, sizeof(mr337) / 5, sizeof(mr338) / 5, sizeof(mr339) / 5, sizeof(mr340) / 5, sizeof(mr341) / 5, sizeof(mr342) / 5, sizeof(mr343) / 5, sizeof(mr344) / 5, sizeof(mr345) / 5, sizeof(mr346) / 5, sizeof(mr347) / 5, sizeof(mr348) / 5, sizeof(mr349) / 5, sizeof(mr350) / 5, sizeof(mr351) / 5, sizeof(mr352) / 5, sizeof(mr353) / 5, sizeof(mr354) / 5, sizeof(mr355) / 5, sizeof(mr356) / 5, sizeof(mr357) / 5, sizeof(mr358) / 5, sizeof(mr359) / 5, sizeof(mr360) / 5, sizeof(mr361) / 5, sizeof(mr362) / 5, sizeof(mr363) / 5,
	sizeof(mr364) / 5,
	sizeof(mr365) / 5, sizeof(mr366) / 5, sizeof(mr367) / 5, sizeof(mr368) / 5, sizeof(mr369) / 5, sizeof(mr370) / 5, sizeof(mr371) / 5, sizeof(mr372) / 5, sizeof(mr373) / 5, sizeof(mr374) / 5,
	sizeof(mr375) / 5, sizeof(mr376) / 5, sizeof(mr377) / 5, sizeof(mr378) / 5, sizeof(mr379) / 5, sizeof(mr380) / 5, sizeof(mr381) / 5, sizeof(mr382) / 5, sizeof(mr383) / 5, sizeof(mr384) / 5,
	sizeof(mr385) / 5, sizeof(mr386) / 5, sizeof(mr387) / 5, sizeof(mr388) / 5, sizeof(mr389) / 5, sizeof(mr390) / 5, sizeof(mr391) / 5, sizeof(mr392) / 5, sizeof(mr393) / 5, sizeof(mr394) / 5,
	sizeof(mr395) / 5, sizeof(mr396) / 5, sizeof(mr397) / 5, sizeof(mr398) / 5, sizeof(mr399) / 5, sizeof(mr400) / 5, sizeof(mr401) / 5, sizeof(mr402) / 5, sizeof(mr403) / 5, sizeof(mr404) / 5,
	sizeof(mr405) / 5,
	sizeof(mr406) / 5, sizeof(mr407) / 5, sizeof(mr408) / 5, sizeof(mr409) / 5, sizeof(mr410) / 5, sizeof(mr411) / 5, sizeof(mr412) / 5, sizeof(mr413) / 5, sizeof(mr414) / 5, sizeof(mr415) / 5, sizeof(mr416) / 5, sizeof(mr417) / 5, sizeof(mr418) / 5, sizeof(mr419) / 5, sizeof(mr420) / 5, sizeof(mr421) / 5, sizeof(mr422) / 5, sizeof(mr423) / 5, sizeof(mr424) / 5,
};

const signed short* const mapBackPtr[TOTALMAP] = {
	mb0, mb1, mb2, mb3,
	mb4, mb5, mb6, mb7, mb8, mb9,
	mb10, mb11, mb12, mb13, mb14, mb15, mb16, mb17, mb18, mb19, mb20, mb21, mb22, mb23, mb24, mb25,
	mb26, mb27, mb28, mb29, mb30, mb31, mb32, mb33, mb34, mb35, mb36, mb37, mb38, mb39, mb40, mb41, mb42,
	mb43, mb44, mb45, mb46, mb47, mb48, mb49, mb50, mb51, mb52, mb53, mb54, mb55, mb56, mb57, mb58, mb59, mb60, mb61, mb62,
	mb63, mb64, mb65, mb66, mb67, mb68, mb69, mb70, mb71, mb72, mb73, mb74, mb75, mb76, mb77, mb78, mb79, mb80, mb81,
	mb82, mb83, mb84, mb85, mb86, mb87, mb88, mb89, mb90, mb91, mb92, mb93, mb94, mb95, mb96,
	mb97, mb98, mb99, mb100, mb101, mb102, mb103, mb104, mb105, mb106, mb107, mb108, mb109, mb110, mb111, mb112, mb113,
	mb114,
	mb115, mb116, mb117, mb118, mb119, mb120, mb121, mb122, mb123, mb124, mb125,
	mb126, mb127, mb128, mb129, mb130, mb131, mb132, mb133, mb134, mb135, mb136, mb137, mb138, mb139, mb140, mb141, mb142, mb143, mb144,
	mb145, mb146, mb147, mb148, mb149, mb150, mb151, mb152, mb153, mb154, mb155, mb156, mb157, mb158, mb159, mb160, mb161, mb162, mb163, mb164, mb165,
	mb166, mb167, mb168, mb169, mb170, mb171, mb172, mb173, mb174, mb175, mb176, mb177, mb178, mb179, mb180, mb181, mb182, mb183, mb184,
	mb185, mb186, mb187, mb188, mb189, mb190, mb191, mb192, mb193, mb194, mb195, mb196, mb197, mb198, mb199, mb200, mb201, mb202, mb203, mb204,
	mb205, mb206, mb207, mb208, mb209, mb210, mb211, mb212, mb213, mb214, mb215, mb216, mb217, mb218, mb219, mb220, mb221, mb222, mb223, mb224, mb225,
	mb226, mb227, mb228, mb229, mb230, mb231, mb232, mb233, mb234, mb235, mb236, mb237, mb238, mb239, mb240, mb241, mb242, mb243,
	mb244, mb245, mb246, mb247, mb248, mb249, mb250, mb251, mb252, mb253, mb254, mb255, mb256, mb257, mb258, mb259, mb260, mb261, mb262,
	mb263, mb264, mb265, mb266, mb267, mb268, mb269, mb270, mb271, mb272, mb273, mb274, mb275, mb276, mb277, mb278, mb279,
	mb280, mb281, mb282, mb283, mb284, mb285, mb286, mb287, mb288, mb289, mb290, mb291, mb292, mb293,
	mb294, mb295, mb296, mb297, mb298, mb299, mb300, mb301, mb302, mb303, mb304, mb305, mb306,
	mb307, mb308, mb309, mb310, mb311, mb312, mb313, mb314, mb315, mb316, mb317, mb318, mb319, mb320, mb321, mb322, mb323, mb324, mb325, mb326, mb327, mb328, mb329, mb330, mb331, mb332, mb333, mb334, mb335, mb336, mb337, mb338, mb339, mb340, mb341, mb342, mb343, mb344, mb345, mb346, mb347, mb348, mb349, mb350, mb351, mb352, mb353, mb354, mb355, mb356, mb357, mb358, mb359, mb360, mb361, mb362, mb363,
	mb364,
	mb365, mb366, mb367, mb368, mb369, mb370, mb371, mb372, mb373, mb374,
	mb375, mb376, mb377, mb378, mb379, mb380, mb381, mb382, mb383, mb384,
	mb385, mb386, mb387, mb388, mb389, mb390, mb391, mb392, mb393, mb394,
	mb395, mb396, mb397, mb398, mb399, mb400, mb401, mb402, mb403, mb404,
	mb405,
	mb406, mb407, mb408, mb409, mb410, mb411, mb412, mb413, mb414, mb415, mb416, mb417, mb418, mb419, mb420, mb421, mb422, mb423, mb424,
};

const unsigned int mapBackSize[TOTALMAP] = {
	sizeof(mb0) / 6, sizeof(mb1) / 6, sizeof(mb2) / 6, sizeof(mb3) / 6,
	sizeof(mb4) / 6, sizeof(mb5) / 6, sizeof(mb6) / 6, sizeof(mb7) / 6, sizeof(mb8) / 6, sizeof(mb9) / 6,
	sizeof(mb10) / 6, sizeof(mb11) / 6, sizeof(mb12) / 6, sizeof(mb13) / 6, sizeof(mb14) / 6, sizeof(mb15) / 6, sizeof(mb16) / 6, sizeof(mb17) / 6, sizeof(mb18) / 6, sizeof(mb19) / 6, sizeof(mb20) / 6, sizeof(mb21) / 6, sizeof(mb22) / 6, sizeof(mb23) / 6, sizeof(mb24) / 6, sizeof(mb25) / 6,
	sizeof(mb26) / 6, sizeof(mb27) / 6, sizeof(mb28) / 6, sizeof(mb29) / 6, sizeof(mb30) / 6, sizeof(mb31) / 6, sizeof(mb32) / 6, sizeof(mb33) / 6, sizeof(mb34) / 6, sizeof(mb35) / 6, sizeof(mb36) / 6, sizeof(mb37) / 6, sizeof(mb38) / 6, sizeof(mb39) / 6, sizeof(mb40) / 6, sizeof(mb41) / 6, sizeof(mb42) / 6,
	sizeof(mb43) / 6, sizeof(mb44) / 6, sizeof(mb45) / 6, sizeof(mb46) / 6, sizeof(mb47) / 6, sizeof(mb48) / 6, sizeof(mb49) / 6, sizeof(mb50) / 6, sizeof(mb51) / 6, sizeof(mb52) / 6, sizeof(mb53) / 6, sizeof(mb54) / 6, sizeof(mb55) / 6, sizeof(mb56) / 6, sizeof(mb57) / 6, sizeof(mb58) / 6, sizeof(mb59) / 6, sizeof(mb60) / 6, sizeof(mb61) / 6, sizeof(mb62) / 6,
	sizeof(mb63) / 6, sizeof(mb64) / 6, sizeof(mb65) / 6, sizeof(mb66) / 6, sizeof(mb67) / 6, sizeof(mb68) / 6, sizeof(mb69) / 6, sizeof(mb70) / 6, sizeof(mb71) / 6, sizeof(mb72) / 6, sizeof(mb73) / 6, sizeof(mb74) / 6, sizeof(mb75) / 6, sizeof(mb76) / 6, sizeof(mb77) / 6, sizeof(mb78) / 6, sizeof(mb79) / 6, sizeof(mb80) / 6, sizeof(mb81) / 6,
	sizeof(mb82) / 6, sizeof(mb83) / 6, sizeof(mb84) / 6, sizeof(mb85) / 6, sizeof(mb86) / 6, sizeof(mb87) / 6, sizeof(mb88) / 6, sizeof(mb89) / 6, sizeof(mb90) / 6, sizeof(mb91) / 6, sizeof(mb92) / 6, sizeof(mb93) / 6, sizeof(mb94) / 6, sizeof(mb95) / 6, sizeof(mb96) / 6,
	sizeof(mb97) / 6, sizeof(mb98) / 6, sizeof(mb99) / 6, sizeof(mb100) / 6, sizeof(mb101) / 6, sizeof(mb102) / 6, sizeof(mb103) / 6, sizeof(mb104) / 6, sizeof(mb105) / 6, sizeof(mb106) / 6, sizeof(mb107) / 6, sizeof(mb108) / 6, sizeof(mb109) / 6, sizeof(mb110) / 6, sizeof(mb111) / 6, sizeof(mb112) / 6, sizeof(mb113) / 6,
	sizeof(mb114) / 6,
	sizeof(mb115) / 6, sizeof(mb116) / 6, sizeof(mb117) / 6, sizeof(mb118) / 6, sizeof(mb119) / 6, sizeof(mb120) / 6, sizeof(mb121) / 6, sizeof(mb122) / 6, sizeof(mb123) / 6, sizeof(mb124) / 6, sizeof(mb125) / 6,
	sizeof(mb126) / 6, sizeof(mb127) / 6, sizeof(mb128) / 6, sizeof(mb129) / 6, sizeof(mb130) / 6, sizeof(mb131) / 6, sizeof(mb132) / 6, sizeof(mb133) / 6, sizeof(mb134) / 6, sizeof(mb135) / 6, sizeof(mb136) / 6, sizeof(mb137) / 6, sizeof(mb138) / 6, sizeof(mb139) / 6, sizeof(mb140) / 6, sizeof(mb141) / 6, sizeof(mb142) / 6, sizeof(mb143) / 6, sizeof(mb144) / 6,
	sizeof(mb145) / 6, sizeof(mb146) / 6, sizeof(mb147) / 6, sizeof(mb148) / 6, sizeof(mb149) / 6, sizeof(mb150) / 6, sizeof(mb151) / 6, sizeof(mb152) / 6, sizeof(mb153) / 6, sizeof(mb154) / 6, sizeof(mb155) / 6, sizeof(mb156) / 6, sizeof(mb157) / 6, sizeof(mb158) / 6, sizeof(mb159) / 6, sizeof(mb160) / 6, sizeof(mb161) / 6, sizeof(mb162) / 6, sizeof(mb163) / 6, sizeof(mb164) / 6, sizeof(mb165) / 6,
	sizeof(mb166) / 6, sizeof(mb167) / 6, sizeof(mb168) / 6, sizeof(mb169) / 6, sizeof(mb170) / 6, sizeof(mb171) / 6, sizeof(mb172) / 6, sizeof(mb173) / 6, sizeof(mb174) / 6, sizeof(mb175) / 6, sizeof(mb176) / 6, sizeof(mb177) / 6, sizeof(mb178) / 6, sizeof(mb179) / 6, sizeof(mb180) / 6, sizeof(mb181) / 6, sizeof(mb182) / 6, sizeof(mb183) / 6, sizeof(mb184) / 6,
	sizeof(mb185) / 6, sizeof(mb186) / 6, sizeof(mb187) / 6, sizeof(mb188) / 6, sizeof(mb189) / 6, sizeof(mb190) / 6, sizeof(mb191) / 6, sizeof(mb192) / 6, sizeof(mb193) / 6, sizeof(mb194) / 6, sizeof(mb195) / 6, sizeof(mb196) / 6, sizeof(mb197) / 6, sizeof(mb198) / 6, sizeof(mb199) / 6, sizeof(mb200) / 6, sizeof(mb201) / 6, sizeof(mb202) / 6, sizeof(mb203) / 6, sizeof(mb204) / 6,
	sizeof(mb205) / 6, sizeof(mb206) / 6, sizeof(mb207) / 6, sizeof(mb208) / 6, sizeof(mb209) / 6, sizeof(mb210) / 6, sizeof(mb211) / 6, sizeof(mb212) / 6, sizeof(mb213) / 6, sizeof(mb214) / 6, sizeof(mb215) / 6, sizeof(mb216) / 6, sizeof(mb217) / 6, sizeof(mb218) / 6, sizeof(mb219) / 6, sizeof(mb220) / 6, sizeof(mb221) / 6, sizeof(mb222) / 6, sizeof(mb223) / 6, sizeof(mb224) / 6, sizeof(mb225) / 6,
	sizeof(mb226) / 6, sizeof(mb227) / 6, sizeof(mb228) / 6, sizeof(mb229) / 6, sizeof(mb230) / 6, sizeof(mb231) / 6, sizeof(mb232) / 6, sizeof(mb233) / 6, sizeof(mb234) / 6, sizeof(mb235) / 6, sizeof(mb236) / 6, sizeof(mb237) / 6, sizeof(mb238) / 6, sizeof(mb239) / 6, sizeof(mb240) / 6, sizeof(mb241) / 6, sizeof(mb242) / 6, sizeof(mb243) / 6,
	sizeof(mb244) / 6, sizeof(mb245) / 6, sizeof(mb246) / 6, sizeof(mb247) / 6, sizeof(mb248) / 6, sizeof(mb249) / 6, sizeof(mb250) / 6, sizeof(mb251) / 6, sizeof(mb252) / 6, sizeof(mb253) / 6, sizeof(mb254) / 6, sizeof(mb255) / 6, sizeof(mb256) / 6, sizeof(mb257) / 6, sizeof(mb258) / 6, sizeof(mb259) / 6, sizeof(mb260) / 6, sizeof(mb261) / 6, sizeof(mb262) / 6,
	sizeof(mb263) / 6, sizeof(mb264) / 6, sizeof(mb265) / 6, sizeof(mb266) / 6, sizeof(mb267) / 6, sizeof(mb268) / 6, sizeof(mb269) / 6, sizeof(mb270) / 6, sizeof(mb271) / 6, sizeof(mb272) / 6, sizeof(mb273) / 6, sizeof(mb274) / 6, sizeof(mb275) / 6, sizeof(mb276) / 6, sizeof(mb277) / 6, sizeof(mb278) / 6, sizeof(mb279) / 6,
	sizeof(mb280) / 6, sizeof(mb281) / 6, sizeof(mb282) / 6, sizeof(mb283) / 6, sizeof(mb284) / 6, sizeof(mb285) / 6, sizeof(mb286) / 6, sizeof(mb287) / 6, sizeof(mb288) / 6, sizeof(mb289) / 6, sizeof(mb290) / 6, sizeof(mb291) / 6, sizeof(mb292) / 6, sizeof(mb293) / 6,
	sizeof(mb294) / 6, sizeof(mb295) / 6, sizeof(mb296) / 6, sizeof(mb297) / 6, sizeof(mb298) / 6, sizeof(mb299) / 6, sizeof(mb300) / 6, sizeof(mb301) / 6, sizeof(mb302) / 6, sizeof(mb303) / 6, sizeof(mb304) / 6, sizeof(mb305) / 6, sizeof(mb306) / 6,
	sizeof(mb307) / 6, sizeof(mb308) / 6, sizeof(mb309) / 6, sizeof(mb310) / 6, sizeof(mb311) / 6, sizeof(mb312) / 6, sizeof(mb313) / 6, sizeof(mb314) / 6, sizeof(mb315) / 6, sizeof(mb316) / 6, sizeof(mb317) / 6, sizeof(mb318) / 6, sizeof(mb319) / 6, sizeof(mb320) / 6, sizeof(mb321) / 6, sizeof(mb322) / 6, sizeof(mb323) / 6, sizeof(mb324) / 6, sizeof(mb325) / 6, sizeof(mb326) / 6, sizeof(mb327) / 6, sizeof(mb328) / 6, sizeof(mb329) / 6, sizeof(mb330) / 6, sizeof(mb331) / 6, sizeof(mb332) / 6, sizeof(mb333) / 6, sizeof(mb334) / 6, sizeof(mb335) / 6, sizeof(mb336) / 6, sizeof(mb337) / 6, sizeof(mb338) / 6, sizeof(mb339) / 6, sizeof(mb340) / 6, sizeof(mb341) / 6, sizeof(mb342) / 6, sizeof(mb343) / 6, sizeof(mb344) / 6, sizeof(mb345) / 6, sizeof(mb346) / 6, sizeof(mb347) / 6, sizeof(mb348) / 6, sizeof(mb349) / 6, sizeof(mb350) / 6, sizeof(mb351) / 6, sizeof(mb352) / 6, sizeof(mb353) / 6, sizeof(mb354) / 6, sizeof(mb355) / 6, sizeof(mb356) / 6, sizeof(mb357) / 6, sizeof(mb358) / 6, sizeof(mb359) / 6, sizeof(mb360) / 6, sizeof(mb361) / 6, sizeof(mb362) / 6, sizeof(mb363) / 6,
	sizeof(mb364) / 6,
	sizeof(mb365) / 6, sizeof(mb366) / 6, sizeof(mb367) / 6, sizeof(mb368) / 6, sizeof(mb369) / 6, sizeof(mb370) / 6, sizeof(mb371) / 6, sizeof(mb372) / 6, sizeof(mb373) / 6, sizeof(mb374) / 6,
	sizeof(mb375) / 6, sizeof(mb376) / 6, sizeof(mb377) / 6, sizeof(mb378) / 6, sizeof(mb379) / 6, sizeof(mb380) / 6, sizeof(mb381) / 6, sizeof(mb382) / 6, sizeof(mb383) / 6, sizeof(mb384) / 6,
	sizeof(mb385) / 6, sizeof(mb386) / 6, sizeof(mb387) / 6, sizeof(mb388) / 6, sizeof(mb389) / 6, sizeof(mb390) / 6, sizeof(mb391) / 6, sizeof(mb392) / 6, sizeof(mb393) / 6, sizeof(mb394) / 6,
	sizeof(mb395) / 6, sizeof(mb396) / 6, sizeof(mb397) / 6, sizeof(mb398) / 6, sizeof(mb399) / 6, sizeof(mb400) / 6, sizeof(mb401) / 6, sizeof(mb402) / 6, sizeof(mb403) / 6, sizeof(mb404) / 6,
	sizeof(mb405) / 6,
	sizeof(mb406) / 6, sizeof(mb407) / 6, sizeof(mb408) / 6, sizeof(mb409) / 6, sizeof(mb410) / 6, sizeof(mb411) / 6, sizeof(mb412) / 6, sizeof(mb413) / 6, sizeof(mb414) / 6, sizeof(mb415) / 6, sizeof(mb416) / 6, sizeof(mb417) / 6, sizeof(mb418) / 6, sizeof(mb419) / 6, sizeof(mb420) / 6, sizeof(mb421) / 6, sizeof(mb422) / 6, sizeof(mb423) / 6, sizeof(mb424) / 6,
};

const signed short* const mapObjPtr[TOTALMAP] = {
	mo0, mo1, mo2, mo3,
	mo4, mo5, mo6, mo7, mo8, mo9,
	mo10, mo11, mo12, mo13, mo14, mo15, mo16, mo17, mo18, mo19, mo20, mo21, mo22, mo23, mo24, mo25,
	mo26, mo27, mo28, mo29, mo30, mo31, mo32, mo33, mo34, mo35, mo36, mo37, mo38, mo39, mo40, mo41, mo42,
	mo43, mo44, mo45, mo46, mo47, mo48, mo49, mo50, mo51, mo52, mo53, mo54, mo55, mo56, mo57, mo58, mo59, mo60, mo61, mo62,
	mo63, mo64, mo65, mo66, mo67, mo68, mo69, mo70, mo71, mo72, mo73, mo74, mo75, mo76, mo77, mo78, mo79, mo80, mo81,
	mo82, mo83, mo84, mo85, mo86, mo87, mo88, mo89, mo90, mo91, mo92, mo93, mo94, mo95, mo96,
	mo97, mo98, mo99, mo100, mo101, mo102, mo103, mo104, mo105, mo106, mo107, mo108, mo109, mo110, mo111, mo112, mo113,
	mo114,
	mo115, mo116, mo117, mo118, mo119, mo120, mo121, mo122, mo123, mo124, mo125,
	mo126, mo127, mo128, mo129, mo130, mo131, mo132, mo133, mo134, mo135, mo136, mo137, mo138, mo139, mo140, mo141, mo142, mo143, mo144,
	mo145, mo146, mo147, mo148, mo149, mo150, mo151, mo152, mo153, mo154, mo155, mo156, mo157, mo158, mo159, mo160, mo161, mo162, mo163, mo164, mo165,
	mo166, mo167, mo168, mo169, mo170, mo171, mo172, mo173, mo174, mo175, mo176, mo177, mo178, mo179, mo180, mo181, mo182, mo183, mo184,
	mo185, mo186, mo187, mo188, mo189, mo190, mo191, mo192, mo193, mo194, mo195, mo196, mo197, mo198, mo199, mo200, mo201, mo202, mo203, mo204,
	mo205, mo206, mo207, mo208, mo209, mo210, mo211, mo212, mo213, mo214, mo215, mo216, mo217, mo218, mo219, mo220, mo221, mo222, mo223, mo224, mo225,
	mo226, mo227, mo228, mo229, mo230, mo231, mo232, mo233, mo234, mo235, mo236, mo237, mo238, mo239, mo240, mo241, mo242, mo243,
	mo244, mo245, mo246, mo247, mo248, mo249, mo250, mo251, mo252, mo253, mo254, mo255, mo256, mo257, mo258, mo259, mo260, mo261, mo262,
	mo263, mo264, mo265, mo266, mo267, mo268, mo269, mo270, mo271, mo272, mo273, mo274, mo275, mo276, mo277, mo278, mo279,
	mo280, mo281, mo282, mo283, mo284, mo285, mo286, mo287, mo288, mo289, mo290, mo291, mo292, mo293,
	mo294, mo295, mo296, mo297, mo298, mo299, mo300, mo301, mo302, mo303, mo304, mo305, mo306,
	mo307, mo308, mo309, mo310, mo311, mo312, mo313, mo314, mo315, mo316, mo317, mo318, mo319, mo320, mo321, mo322, mo323, mo324, mo325, mo326, mo327, mo328, mo329, mo330, mo331, mo332, mo333, mo334, mo335, mo336, mo337, mo338, mo339, mo340, mo341, mo342, mo343, mo344, mo345, mo346, mo347, mo348, mo349, mo350, mo351, mo352, mo353, mo354, mo355, mo356, mo357, mo358, mo359, mo360, mo361, mo362, mo363,
	mo364,
	mo365, mo366, mo367, mo368, mo369, mo370, mo371, mo372, mo373, mo374,
	mo375, mo376, mo377, mo378, mo379, mo380, mo381, mo382, mo383, mo384,
	mo385, mo386, mo387, mo388, mo389, mo390, mo391, mo392, mo393, mo394,
	mo395, mo396, mo397, mo398, mo399, mo400, mo401, mo402, mo403, mo404,
	mo405,
	mo406, mo407, mo408, mo409, mo410, mo411, mo412, mo413, mo414, mo415, mo416, mo417, mo418, mo419, mo420, mo421, mo422, mo423, mo424,
};

const unsigned int mapObjSize[TOTALMAP] = {
	sizeof(mo0) / 6, sizeof(mo1) / 6, sizeof(mo2) / 6, sizeof(mo3) / 6,
	sizeof(mo4) / 6, sizeof(mo5) / 6, sizeof(mo6) / 6, sizeof(mo7) / 6, sizeof(mo8) / 6, sizeof(mo9) / 6,
	sizeof(mo10) / 6, sizeof(mo11) / 6, sizeof(mo12) / 6, sizeof(mo13) / 6, sizeof(mo14) / 6, sizeof(mo15) / 6, sizeof(mo16) / 6, sizeof(mo17) / 6, sizeof(mo18) / 6, sizeof(mo19) / 6, sizeof(mo20) / 6, sizeof(mo21) / 6, sizeof(mo22) / 6, sizeof(mo23) / 6, sizeof(mo24) / 6, sizeof(mo25) / 6,
	sizeof(mo26) / 6, sizeof(mo27) / 6, sizeof(mo28) / 6, sizeof(mo29) / 6, sizeof(mo30) / 6, sizeof(mo31) / 6, sizeof(mo32) / 6, sizeof(mo33) / 6, sizeof(mo34) / 6, sizeof(mo35) / 6, sizeof(mo36) / 6, sizeof(mo37) / 6, sizeof(mo38) / 6, sizeof(mo39) / 6, sizeof(mo40) / 6, sizeof(mo41) / 6, sizeof(mo42) / 6,
	sizeof(mo43) / 6, sizeof(mo44) / 6, sizeof(mo45) / 6, sizeof(mo46) / 6, sizeof(mo47) / 6, sizeof(mo48) / 6, sizeof(mo49) / 6, sizeof(mo50) / 6, sizeof(mo51) / 6, sizeof(mo52) / 6, sizeof(mo53) / 6, sizeof(mo54) / 6, sizeof(mo55) / 6, sizeof(mo56) / 6, sizeof(mo57) / 6, sizeof(mo58) / 6, sizeof(mo59) / 6, sizeof(mo60) / 6, sizeof(mo61) / 6, sizeof(mo62) / 6,
	sizeof(mo63) / 6, sizeof(mo64) / 6, sizeof(mo65) / 6, sizeof(mo66) / 6, sizeof(mo67) / 6, sizeof(mo68) / 6, sizeof(mo69) / 6, sizeof(mo70) / 6, sizeof(mo71) / 6, sizeof(mo72) / 6, sizeof(mo73) / 6, sizeof(mo74) / 6, sizeof(mo75) / 6, sizeof(mo76) / 6, sizeof(mo77) / 6, sizeof(mo78) / 6, sizeof(mo79) / 6, sizeof(mo80) / 6, sizeof(mo81) / 6,
	sizeof(mo82) / 6, sizeof(mo83) / 6, sizeof(mo84) / 6, sizeof(mo85) / 6, sizeof(mo86) / 6, sizeof(mo87) / 6, sizeof(mo88) / 6, sizeof(mo89) / 6, sizeof(mo90) / 6, sizeof(mo91) / 6, sizeof(mo92) / 6, sizeof(mo93) / 6, sizeof(mo94) / 6, sizeof(mo95) / 6, sizeof(mo96) / 6,
	sizeof(mo97) / 6, sizeof(mo98) / 6, sizeof(mo99) / 6, sizeof(mo100) / 6, sizeof(mo101) / 6, sizeof(mo102) / 6, sizeof(mo103) / 6, sizeof(mo104) / 6, sizeof(mo105) / 6, sizeof(mo106) / 6, sizeof(mo107) / 6, sizeof(mo108) / 6, sizeof(mo109) / 6, sizeof(mo110) / 6, sizeof(mo111) / 6, sizeof(mo112) / 6, sizeof(mo113) / 6,
	sizeof(mo114) / 6,
	sizeof(mo115) / 6, sizeof(mo116) / 6, sizeof(mo117) / 6, sizeof(mo118) / 6, sizeof(mo119) / 6, sizeof(mo120) / 6, sizeof(mo121) / 6, sizeof(mo122) / 6, sizeof(mo123) / 6, sizeof(mo124) / 6, sizeof(mo125) / 6,
	sizeof(mo126) / 6, sizeof(mo127) / 6, sizeof(mo128) / 6, sizeof(mo129) / 6, sizeof(mo130) / 6, sizeof(mo131) / 6, sizeof(mo132) / 6, sizeof(mo133) / 6, sizeof(mo134) / 6, sizeof(mo135) / 6, sizeof(mo136) / 6, sizeof(mo137) / 6, sizeof(mo138) / 6, sizeof(mo139) / 6, sizeof(mo140) / 6, sizeof(mo141) / 6, sizeof(mo142) / 6, sizeof(mo143) / 6, sizeof(mo144) / 6,
	sizeof(mo145) / 6, sizeof(mo146) / 6, sizeof(mo147) / 6, sizeof(mo148) / 6, sizeof(mo149) / 6, sizeof(mo150) / 6, sizeof(mo151) / 6, sizeof(mo152) / 6, sizeof(mo153) / 6, sizeof(mo154) / 6, sizeof(mo155) / 6, sizeof(mo156) / 6, sizeof(mo157) / 6, sizeof(mo158) / 6, sizeof(mo159) / 6, sizeof(mo160) / 6, sizeof(mo161) / 6, sizeof(mo162) / 6, sizeof(mo163) / 6, sizeof(mo164) / 6, sizeof(mo165) / 6,
	sizeof(mo166) / 6, sizeof(mo167) / 6, sizeof(mo168) / 6, sizeof(mo169) / 6, sizeof(mo170) / 6, sizeof(mo171) / 6, sizeof(mo172) / 6, sizeof(mo173) / 6, sizeof(mo174) / 6, sizeof(mo175) / 6, sizeof(mo176) / 6, sizeof(mo177) / 6, sizeof(mo178) / 6, sizeof(mo179) / 6, sizeof(mo180) / 6, sizeof(mo181) / 6, sizeof(mo182) / 6, sizeof(mo183) / 6, sizeof(mo184) / 6,
	sizeof(mo185) / 6, sizeof(mo186) / 6, sizeof(mo187) / 6, sizeof(mo188) / 6, sizeof(mo189) / 6, sizeof(mo190) / 6, sizeof(mo191) / 6, sizeof(mo192) / 6, sizeof(mo193) / 6, sizeof(mo194) / 6, sizeof(mo195) / 6, sizeof(mo196) / 6, sizeof(mo197) / 6, sizeof(mo198) / 6, sizeof(mo199) / 6, sizeof(mo200) / 6, sizeof(mo201) / 6, sizeof(mo202) / 6, sizeof(mo203) / 6, sizeof(mo204) / 6,
	sizeof(mo205) / 6, sizeof(mo206) / 6, sizeof(mo207) / 6, sizeof(mo208) / 6, sizeof(mo209) / 6, sizeof(mo210) / 6, sizeof(mo211) / 6, sizeof(mo212) / 6, sizeof(mo213) / 6, sizeof(mo214) / 6, sizeof(mo215) / 6, sizeof(mo216) / 6, sizeof(mo217) / 6, sizeof(mo218) / 6, sizeof(mo219) / 6, sizeof(mo220) / 6, sizeof(mo221) / 6, sizeof(mo222) / 6, sizeof(mo223) / 6, sizeof(mo224) / 6, sizeof(mo225) / 6,
	sizeof(mo226) / 6, sizeof(mo227) / 6, sizeof(mo228) / 6, sizeof(mo229) / 6, sizeof(mo230) / 6, sizeof(mo231) / 6, sizeof(mo232) / 6, sizeof(mo233) / 6, sizeof(mo234) / 6, sizeof(mo235) / 6, sizeof(mo236) / 6, sizeof(mo237) / 6, sizeof(mo238) / 6, sizeof(mo239) / 6, sizeof(mo240) / 6, sizeof(mo241) / 6, sizeof(mo242) / 6, sizeof(mo243) / 6,
	sizeof(mo244) / 6, sizeof(mo245) / 6, sizeof(mo246) / 6, sizeof(mo247) / 6, sizeof(mo248) / 6, sizeof(mo249) / 6, sizeof(mo250) / 6, sizeof(mo251) / 6, sizeof(mo252) / 6, sizeof(mo253) / 6, sizeof(mo254) / 6, sizeof(mo255) / 6, sizeof(mo256) / 6, sizeof(mo257) / 6, sizeof(mo258) / 6, sizeof(mo259) / 6, sizeof(mo260) / 6, sizeof(mo261) / 6, sizeof(mo262) / 6,
	sizeof(mo263) / 6, sizeof(mo264) / 6, sizeof(mo265) / 6, sizeof(mo266) / 6, sizeof(mo267) / 6, sizeof(mo268) / 6, sizeof(mo269) / 6, sizeof(mo270) / 6, sizeof(mo271) / 6, sizeof(mo272) / 6, sizeof(mo273) / 6, sizeof(mo274) / 6, sizeof(mo275) / 6, sizeof(mo276) / 6, sizeof(mo277) / 6, sizeof(mo278) / 6, sizeof(mo279) / 6,
	sizeof(mo280) / 6, sizeof(mo281) / 6, sizeof(mo282) / 6, sizeof(mo283) / 6, sizeof(mo284) / 6, sizeof(mo285) / 6, sizeof(mo286) / 6, sizeof(mo287) / 6, sizeof(mo288) / 6, sizeof(mo289) / 6, sizeof(mo290) / 6, sizeof(mo291) / 6, sizeof(mo292) / 6, sizeof(mo293) / 6,
	sizeof(mo294) / 6, sizeof(mo295) / 6, sizeof(mo296) / 6, sizeof(mo297) / 6, sizeof(mo298) / 6, sizeof(mo299) / 6, sizeof(mo300) / 6, sizeof(mo301) / 6, sizeof(mo302) / 6, sizeof(mo303) / 6, sizeof(mo304) / 6, sizeof(mo305) / 6, sizeof(mo306) / 6,
	sizeof(mo307) / 6, sizeof(mo308) / 6, sizeof(mo309) / 6, sizeof(mo310) / 6, sizeof(mo311) / 6, sizeof(mo312) / 6, sizeof(mo313) / 6, sizeof(mo314) / 6, sizeof(mo315) / 6, sizeof(mo316) / 6, sizeof(mo317) / 6, sizeof(mo318) / 6, sizeof(mo319) / 6, sizeof(mo320) / 6, sizeof(mo321) / 6, sizeof(mo322) / 6, sizeof(mo323) / 6, sizeof(mo324) / 6, sizeof(mo325) / 6, sizeof(mo326) / 6, sizeof(mo327) / 6, sizeof(mo328) / 6, sizeof(mo329) / 6, sizeof(mo330) / 6, sizeof(mo331) / 6, sizeof(mo332) / 6, sizeof(mo333) / 6, sizeof(mo334) / 6, sizeof(mo335) / 6, sizeof(mo336) / 6, sizeof(mo337) / 6, sizeof(mo338) / 6, sizeof(mo339) / 6, sizeof(mo340) / 6, sizeof(mo341) / 6, sizeof(mo342) / 6, sizeof(mo343) / 6, sizeof(mo344) / 6, sizeof(mo345) / 6, sizeof(mo346) / 6, sizeof(mo347) / 6, sizeof(mo348) / 6, sizeof(mo349) / 6, sizeof(mo350) / 6, sizeof(mo351) / 6, sizeof(mo352) / 6, sizeof(mo353) / 6, sizeof(mo354) / 6, sizeof(mo355) / 6, sizeof(mo356) / 6, sizeof(mo357) / 6, sizeof(mo358) / 6, sizeof(mo359) / 6, sizeof(mo360) / 6, sizeof(mo361) / 6, sizeof(mo362) / 6, sizeof(mo363) / 6,
	sizeof(mo364) / 6,
	sizeof(mo365) / 6, sizeof(mo366) / 6, sizeof(mo367) / 6, sizeof(mo368) / 6, sizeof(mo369) / 6, sizeof(mo370) / 6, sizeof(mo371) / 6, sizeof(mo372) / 6, sizeof(mo373) / 6, sizeof(mo374) / 6,
	sizeof(mo375) / 6, sizeof(mo376) / 6, sizeof(mo377) / 6, sizeof(mo378) / 6, sizeof(mo379) / 6, sizeof(mo380) / 6, sizeof(mo381) / 6, sizeof(mo382) / 6, sizeof(mo383) / 6, sizeof(mo384) / 6,
	sizeof(mo385) / 6, sizeof(mo386) / 6, sizeof(mo387) / 6, sizeof(mo388) / 6, sizeof(mo389) / 6, sizeof(mo390) / 6, sizeof(mo391) / 6, sizeof(mo392) / 6, sizeof(mo393) / 6, sizeof(mo394) / 6,
	sizeof(mo395) / 6, sizeof(mo396) / 6, sizeof(mo397) / 6, sizeof(mo398) / 6, sizeof(mo399) / 6, sizeof(mo400) / 6, sizeof(mo401) / 6, sizeof(mo402) / 6, sizeof(mo403) / 6, sizeof(mo404) / 6,
	sizeof(mo405) / 6,
	sizeof(mo406) / 6, sizeof(mo407) / 6, sizeof(mo408) / 6, sizeof(mo409) / 6, sizeof(mo410) / 6, sizeof(mo411) / 6, sizeof(mo412) / 6, sizeof(mo413) / 6, sizeof(mo414) / 6, sizeof(mo415) / 6, sizeof(mo416) / 6, sizeof(mo417) / 6, sizeof(mo418) / 6, sizeof(mo419) / 6, sizeof(mo420) / 6, sizeof(mo421) / 6, sizeof(mo422) / 6, sizeof(mo423) / 6, sizeof(mo424) / 6,
};

const signed short* const mapNeutralPtr[TOTALMAP] = {
	mn0, mn1, mn2, mn3,
	mn4, mn5, mn6, mn7, mn8, mn9,
	mn10, mn11, mn12, mn13, mn14, mn15, mn16, mn17, mn18, mn19, mn20, mn21, mn22, mn23, mn24, mn25,
	mn26, mn27, mn28, mn29, mn30, mn31, mn32, mn33, mn34, mn35, mn36, mn37, mn38, mn39, mn40, mn41, mn42,
	mn43, mn44, mn45, mn46, mn47, mn48, mn49, mn50, mn51, mn52, mn53, mn54, mn55, mn56, mn57, mn58, mn59, mn60, mn61, mn62,
	mn63, mn64, mn65, mn66, mn67, mn68, mn69, mn70, mn71, mn72, mn73, mn74, mn75, mn76, mn77, mn78, mn79, mn80, mn81,
	mn82, mn83, mn84, mn85, mn86, mn87, mn88, mn89, mn90, mn91, mn92, mn93, mn94, mn95, mn96,
	mn97, mn98, mn99, mn100, mn101, mn102, mn103, mn104, mn105, mn106, mn107, mn108, mn109, mn110, mn111, mn112, mn113,
	mn114,
	mn115, mn116, mn117, mn118, mn119, mn120, mn121, mn122, mn123, mn124, mn125,
	mn126, mn127, mn128, mn129, mn130, mn131, mn132, mn133, mn134, mn135, mn136, mn137, mn138, mn139, mn140, mn141, mn142, mn143, mn144,
	mn145, mn146, mn147, mn148, mn149, mn150, mn151, mn152, mn153, mn154, mn155, mn156, mn157, mn158, mn159, mn160, mn161, mn162, mn163, mn164, mn165,
	mn166, mn167, mn168, mn169, mn170, mn171, mn172, mn173, mn174, mn175, mn176, mn177, mn178, mn179, mn180, mn181, mn182, mn183, mn184,
	mn185, mn186, mn187, mn188, mn189, mn190, mn191, mn192, mn193, mn194, mn195, mn196, mn197, mn198, mn199, mn200, mn201, mn202, mn203, mn204,
	mn205, mn206, mn207, mn208, mn209, mn210, mn211, mn212, mn213, mn214, mn215, mn216, mn217, mn218, mn219, mn220, mn221, mn222, mn223, mn224, mn225,
	mn226, mn227, mn228, mn229, mn230, mn231, mn232, mn233, mn234, mn235, mn236, mn237, mn238, mn239, mn240, mn241, mn242, mn243,
	mn244, mn245, mn246, mn247, mn248, mn249, mn250, mn251, mn252, mn253, mn254, mn255, mn256, mn257, mn258, mn259, mn260, mn261, mn262,
	mn263, mn264, mn265, mn266, mn267, mn268, mn269, mn270, mn271, mn272, mn273, mn274, mn275, mn276, mn277, mn278, mn279,
	mn280, mn281, mn282, mn283, mn284, mn285, mn286, mn287, mn288, mn289, mn290, mn291, mn292, mn293,
	mn294, mn295, mn296, mn297, mn298, mn299, mn300, mn301, mn302, mn303, mn304, mn305, mn306,
	mn307, mn308, mn309, mn310, mn311, mn312, mn313, mn314, mn315, mn316, mn317, mn318, mn319, mn320, mn321, mn322, mn323, mn324, mn325, mn326, mn327, mn328, mn329, mn330, mn331, mn332, mn333, mn334, mn335, mn336, mn337, mn338, mn339, mn340, mn341, mn342, mn343, mn344, mn345, mn346, mn347, mn348, mn349, mn350, mn351, mn352, mn353, mn354, mn355, mn356, mn357, mn358, mn359, mn360, mn361, mn362, mn363,
	mn364,
	mn365, mn366, mn367, mn368, mn369, mn370, mn371, mn372, mn373, mn374,
	mn375, mn376, mn377, mn378, mn379, mn380, mn381, mn382, mn383, mn384,
	mn385, mn386, mn387, mn388, mn389, mn390, mn391, mn392, mn393, mn394,
	mn395, mn396, mn397, mn398, mn399, mn400, mn401, mn402, mn403, mn404,
	mn405,
	mn406, mn407, mn408, mn409, mn410, mn411, mn412, mn413, mn414, mn415, mn416, mn417, mn418, mn419, mn420, mn421, mn422, mn423, mn424,
};

const unsigned int mapNeutralSize[TOTALMAP] = {
	sizeof(mn0) / 8, sizeof(mn1) / 8, sizeof(mn2) / 8, sizeof(mn3) / 8,
	sizeof(mn4) / 8, sizeof(mn5) / 8, sizeof(mn6) / 8, sizeof(mn7) / 8, sizeof(mn8) / 8, sizeof(mn9) / 8,
	sizeof(mn10) / 8, sizeof(mn11) / 8, sizeof(mn12) / 8, sizeof(mn13) / 8, sizeof(mn14) / 8, sizeof(mn15) / 8, sizeof(mn16) / 8, sizeof(mn17) / 8, sizeof(mn18) / 8, sizeof(mn19) / 8, sizeof(mn20) / 8, sizeof(mn21) / 8, sizeof(mn22) / 8, sizeof(mn23) / 8, sizeof(mn24) / 8, sizeof(mn25) / 8,
	sizeof(mn26) / 8, sizeof(mn27) / 8, sizeof(mn28) / 8, sizeof(mn29) / 8, sizeof(mn30) / 8, sizeof(mn31) / 8, sizeof(mn32) / 8, sizeof(mn33) / 8, sizeof(mn34) / 8, sizeof(mn35) / 8, sizeof(mn36) / 8, sizeof(mn37) / 8, sizeof(mn38) / 8, sizeof(mn39) / 8, sizeof(mn40) / 8, sizeof(mn41) / 8, sizeof(mn42) / 8,
	sizeof(mn43) / 8, sizeof(mn44) / 8, sizeof(mn45) / 8, sizeof(mn46) / 8, sizeof(mn47) / 8, sizeof(mn48) / 8, sizeof(mn49) / 8, sizeof(mn50) / 8, sizeof(mn51) / 8, sizeof(mn52) / 8, sizeof(mn53) / 8, sizeof(mn54) / 8, sizeof(mn55) / 8, sizeof(mn56) / 8, sizeof(mn57) / 8, sizeof(mn58) / 8, sizeof(mn59) / 8, sizeof(mn60) / 8, sizeof(mn61) / 8, sizeof(mn62) / 8,
	sizeof(mn63) / 8, sizeof(mn64) / 8, sizeof(mn65) / 8, sizeof(mn66) / 8, sizeof(mn67) / 8, sizeof(mn68) / 8, sizeof(mn69) / 8, sizeof(mn70) / 8, sizeof(mn71) / 8, sizeof(mn72) / 8, sizeof(mn73) / 8, sizeof(mn74) / 8, sizeof(mn75) / 8, sizeof(mn76) / 8, sizeof(mn77) / 8, sizeof(mn78) / 8, sizeof(mn79) / 8, sizeof(mn80) / 8, sizeof(mn81) / 8,
	sizeof(mn82) / 8, sizeof(mn83) / 8, sizeof(mn84) / 8, sizeof(mn85) / 8, sizeof(mn86) / 8, sizeof(mn87) / 8, sizeof(mn88) / 8, sizeof(mn89) / 8, sizeof(mn90) / 8, sizeof(mn91) / 8, sizeof(mn92) / 8, sizeof(mn93) / 8, sizeof(mn94) / 8, sizeof(mn95) / 8, sizeof(mn96) / 8,
	sizeof(mn97) / 8, sizeof(mn98) / 8, sizeof(mn99) / 8, sizeof(mn100) / 8, sizeof(mn101) / 8, sizeof(mn102) / 8, sizeof(mn103) / 8, sizeof(mn104) / 8, sizeof(mn105) / 8, sizeof(mn106) / 8, sizeof(mn107) / 8, sizeof(mn108) / 8, sizeof(mn109) / 8, sizeof(mn110) / 8, sizeof(mn111) / 8, sizeof(mn112) / 8, sizeof(mn113) / 8,
	sizeof(mn114) / 8,
	sizeof(mn115) / 8, sizeof(mn116) / 8, sizeof(mn117) / 8, sizeof(mn118) / 8, sizeof(mn119) / 8, sizeof(mn120) / 8, sizeof(mn121) / 8, sizeof(mn122) / 8, sizeof(mn123) / 8, sizeof(mn124) / 8, sizeof(mn125) / 8,
	sizeof(mn126) / 8, sizeof(mn127) / 8, sizeof(mn128) / 8, sizeof(mn129) / 8, sizeof(mn130) / 8, sizeof(mn131) / 8, sizeof(mn132) / 8, sizeof(mn133) / 8, sizeof(mn134) / 8, sizeof(mn135) / 8, sizeof(mn136) / 8, sizeof(mn137) / 8, sizeof(mn138) / 8, sizeof(mn139) / 8, sizeof(mn140) / 8, sizeof(mn141) / 8, sizeof(mn142) / 8, sizeof(mn143) / 8, sizeof(mn144) / 8,
	sizeof(mn145) / 8, sizeof(mn146) / 8, sizeof(mn147) / 8, sizeof(mn148) / 8, sizeof(mn149) / 8, sizeof(mn150) / 8, sizeof(mn151) / 8, sizeof(mn152) / 8, sizeof(mn153) / 8, sizeof(mn154) / 8, sizeof(mn155) / 8, sizeof(mn156) / 8, sizeof(mn157) / 8, sizeof(mn158) / 8, sizeof(mn159) / 8, sizeof(mn160) / 8, sizeof(mn161) / 8, sizeof(mn162) / 8, sizeof(mn163) / 8, sizeof(mn164) / 8, sizeof(mn165) / 8,
	sizeof(mn166) / 8, sizeof(mn167) / 8, sizeof(mn168) / 8, sizeof(mn169) / 8, sizeof(mn170) / 8, sizeof(mn171) / 8, sizeof(mn172) / 8, sizeof(mn173) / 8, sizeof(mn174) / 8, sizeof(mn175) / 8, sizeof(mn176) / 8, sizeof(mn177) / 8, sizeof(mn178) / 8, sizeof(mn179) / 8, sizeof(mn180) / 8, sizeof(mn181) / 8, sizeof(mn182) / 8, sizeof(mn183) / 8, sizeof(mn184) / 8,
	sizeof(mn185) / 8, sizeof(mn186) / 8, sizeof(mn187) / 8, sizeof(mn188) / 8, sizeof(mn189) / 8, sizeof(mn190) / 8, sizeof(mn191) / 8, sizeof(mn192) / 8, sizeof(mn193) / 8, sizeof(mn194) / 8, sizeof(mn195) / 8, sizeof(mn196) / 8, sizeof(mn197) / 8, sizeof(mn198) / 8, sizeof(mn199) / 8, sizeof(mn200) / 8, sizeof(mn201) / 8, sizeof(mn202) / 8, sizeof(mn203) / 8, sizeof(mn204) / 8,
	sizeof(mn205) / 8, sizeof(mn206) / 8, sizeof(mn207) / 8, sizeof(mn208) / 8, sizeof(mn209) / 8, sizeof(mn210) / 8, sizeof(mn211) / 8, sizeof(mn212) / 8, sizeof(mn213) / 8, sizeof(mn214) / 8, sizeof(mn215) / 8, sizeof(mn216) / 8, sizeof(mn217) / 8, sizeof(mn218) / 8, sizeof(mn219) / 8, sizeof(mn220) / 8, sizeof(mn221) / 8, sizeof(mn222) / 8, sizeof(mn223) / 8, sizeof(mn224) / 8, sizeof(mn225) / 8,
	sizeof(mn226) / 8, sizeof(mn227) / 8, sizeof(mn228) / 8, sizeof(mn229) / 8, sizeof(mn230) / 8, sizeof(mn231) / 8, sizeof(mn232) / 8, sizeof(mn233) / 8, sizeof(mn234) / 8, sizeof(mn235) / 8, sizeof(mn236) / 8, sizeof(mn237) / 8, sizeof(mn238) / 8, sizeof(mn239) / 8, sizeof(mn240) / 8, sizeof(mn241) / 8, sizeof(mn242) / 8, sizeof(mn243) / 8,
	sizeof(mn244) / 8, sizeof(mn245) / 8, sizeof(mn246) / 8, sizeof(mn247) / 8, sizeof(mn248) / 8, sizeof(mn249) / 8, sizeof(mn250) / 8, sizeof(mn251) / 8, sizeof(mn252) / 8, sizeof(mn253) / 8, sizeof(mn254) / 8, sizeof(mn255) / 8, sizeof(mn256) / 8, sizeof(mn257) / 8, sizeof(mn258) / 8, sizeof(mn259) / 8, sizeof(mn260) / 8, sizeof(mn261) / 8, sizeof(mn262) / 8,
	sizeof(mn263) / 8, sizeof(mn264) / 8, sizeof(mn265) / 8, sizeof(mn266) / 8, sizeof(mn267) / 8, sizeof(mn268) / 8, sizeof(mn269) / 8, sizeof(mn270) / 8, sizeof(mn271) / 8, sizeof(mn272) / 8, sizeof(mn273) / 8, sizeof(mn274) / 8, sizeof(mn275) / 8, sizeof(mn276) / 8, sizeof(mn277) / 8, sizeof(mn278) / 8, sizeof(mn279) / 8,
	sizeof(mn280) / 8, sizeof(mn281) / 8, sizeof(mn282) / 8, sizeof(mn283) / 8, sizeof(mn284) / 8, sizeof(mn285) / 8, sizeof(mn286) / 8, sizeof(mn287) / 8, sizeof(mn288) / 8, sizeof(mn289) / 8, sizeof(mn290) / 8, sizeof(mn291) / 8, sizeof(mn292) / 8, sizeof(mn293) / 8,
	sizeof(mn294) / 8, sizeof(mn295) / 8, sizeof(mn296) / 8, sizeof(mn297) / 8, sizeof(mn298) / 8, sizeof(mn299) / 8, sizeof(mn300) / 8, sizeof(mn301) / 8, sizeof(mn302) / 8, sizeof(mn303) / 8, sizeof(mn304) / 8, sizeof(mn305) / 8, sizeof(mn306) / 8,
	sizeof(mn307) / 8, sizeof(mn308) / 8, sizeof(mn309) / 8, sizeof(mn310) / 8, sizeof(mn311) / 8, sizeof(mn312) / 8, sizeof(mn313) / 8, sizeof(mn314) / 8, sizeof(mn315) / 8, sizeof(mn316) / 8, sizeof(mn317) / 8, sizeof(mn318) / 8, sizeof(mn319) / 8, sizeof(mn320) / 8, sizeof(mn321) / 8, sizeof(mn322) / 8, sizeof(mn323) / 8, sizeof(mn324) / 8, sizeof(mn325) / 8, sizeof(mn326) / 8, sizeof(mn327) / 8, sizeof(mn328) / 8, sizeof(mn329) / 8, sizeof(mn330) / 8, sizeof(mn331) / 8, sizeof(mn332) / 8, sizeof(mn333) / 8, sizeof(mn334) / 8, sizeof(mn335) / 8, sizeof(mn336) / 8, sizeof(mn337) / 8, sizeof(mn338) / 8, sizeof(mn339) / 8, sizeof(mn340) / 8, sizeof(mn341) / 8, sizeof(mn342) / 8, sizeof(mn343) / 8, sizeof(mn344) / 8, sizeof(mn345) / 8, sizeof(mn346) / 8, sizeof(mn347) / 8, sizeof(mn348) / 8, sizeof(mn349) / 8, sizeof(mn350) / 8, sizeof(mn351) / 8, sizeof(mn352) / 8, sizeof(mn353) / 8, sizeof(mn354) / 8, sizeof(mn355) / 8, sizeof(mn356) / 8, sizeof(mn357) / 8, sizeof(mn358) / 8, sizeof(mn359) / 8, sizeof(mn360) / 8, sizeof(mn361) / 8, sizeof(mn362) / 8, sizeof(mn363) / 8,
	sizeof(mn364) / 8,
	sizeof(mn365) / 8, sizeof(mn366) / 8, sizeof(mn367) / 8, sizeof(mn368) / 8, sizeof(mn369) / 8, sizeof(mn370) / 8, sizeof(mn371) / 8, sizeof(mn372) / 8, sizeof(mn373) / 8, sizeof(mn374) / 8,
	sizeof(mn375) / 8, sizeof(mn376) / 8, sizeof(mn377) / 8, sizeof(mn378) / 8, sizeof(mn379) / 8, sizeof(mn380) / 8, sizeof(mn381) / 8, sizeof(mn382) / 8, sizeof(mn383) / 8, sizeof(mn384) / 8,
	sizeof(mn385) / 8, sizeof(mn386) / 8, sizeof(mn387) / 8, sizeof(mn388) / 8, sizeof(mn389) / 8, sizeof(mn390) / 8, sizeof(mn391) / 8, sizeof(mn392) / 8, sizeof(mn393) / 8, sizeof(mn394) / 8,
	sizeof(mn395) / 8, sizeof(mn396) / 8, sizeof(mn397) / 8, sizeof(mn398) / 8, sizeof(mn399) / 8, sizeof(mn400) / 8, sizeof(mn401) / 8, sizeof(mn402) / 8, sizeof(mn403) / 8, sizeof(mn404) / 8,
	sizeof(mn405) / 8,
	sizeof(mn406) / 8, sizeof(mn407) / 8, sizeof(mn408) / 8, sizeof(mn409) / 8, sizeof(mn410) / 8, sizeof(mn411) / 8, sizeof(mn412) / 8, sizeof(mn413) / 8, sizeof(mn414) / 8, sizeof(mn415) / 8, sizeof(mn416) / 8, sizeof(mn417) / 8, sizeof(mn418) / 8, sizeof(mn419) / 8, sizeof(mn420) / 8, sizeof(mn421) / 8, sizeof(mn422) / 8, sizeof(mn423) / 8, sizeof(mn424) / 8,
};

const unsigned short* const mapEnemyPtr[TOTALMAP] = {
	me0, me1, me2, me3,
	me4, me5, me6, me7, me8, me9,
	me10, me11, me12, me13, me14, me15, me16, me17, me18, me19, me20, me21, me22, me23, me24, me25,
	me26, me27, me28, me29, me30, me31, me32, me33, me34, me35, me36, me37, me38, me39, me40, me41, me42,
	me43, me44, me45, me46, me47, me48, me49, me50, me51, me52, me53, me54, me55, me56, me57, me58, me59, me60, me61, me62,
	me63, me64, me65, me66, me67, me68, me69, me70, me71, me72, me73, me74, me75, me76, me77, me78, me79, me80, me81,
	me82, me83, me84, me85, me86, me87, me88, me89, me90, me91, me92, me93, me94, me95, me96,
	me97, me98, me99, me100, me101, me102, me103, me104, me105, me106, me107, me108, me109, me110, me111, me112, me113,
	me114,
	me115, me116, me117, me118, me119, me120, me121, me122, me123, me124, me125,
	me126, me127, me128, me129, me130, me131, me132, me133, me134, me135, me136, me137, me138, me139, me140, me141, me142, me143, me144,
	me145, me146, me147, me148, me149, me150, me151, me152, me153, me154, me155, me156, me157, me158, me159, me160, me161, me162, me163, me164, me165,
	me166, me167, me168, me169, me170, me171, me172, me173, me174, me175, me176, me177, me178, me179, me180, me181, me182, me183, me184,
	me185, me186, me187, me188, me189, me190, me191, me192, me193, me194, me195, me196, me197, me198, me199, me200, me201, me202, me203, me204,
	me205, me206, me207, me208, me209, me210, me211, me212, me213, me214, me215, me216, me217, me218, me219, me220, me221, me222, me223, me224, me225,
	me226, me227, me228, me229, me230, me231, me232, me233, me234, me235, me236, me237, me238, me239, me240, me241, me242, me243,
	me244, me245, me246, me247, me248, me249, me250, me251, me252, me253, me254, me255, me256, me257, me258, me259, me260, me261, me262,
	me263, me264, me265, me266, me267, me268, me269, me270, me271, me272, me273, me274, me275, me276, me277, me278, me279,
	me280, me281, me282, me283, me284, me285, me286, me287, me288, me289, me290, me291, me292, me293,
	me294, me295, me296, me297, me298, me299, me300, me301, me302, me303, me304, me305, me306,
	me307, me308, me309, me310, me311, me312, me313, me314, me315, me316, me317, me318, me319, me320, me321, me322, me323, me324, me325, me326, me327, me328, me329, me330, me331, me332, me333, me334, me335, me336, me337, me338, me339, me340, me341, me342, me343, me344, me345, me346, me347, me348, me349, me350, me351, me352, me353, me354, me355, me356, me357, me358, me359, me360, me361, me362, me363,
	me364,
	me365, me366, me367, me368, me369, me370, me371, me372, me373, me374,
	me375, me376, me377, me378, me379, me380, me381, me382, me383, me384,
	me385, me386, me387, me388, me389, me390, me391, me392, me393, me394,
	me395, me396, me397, me398, me399, me400, me401, me402, me403, me404,
	me405,
	me406, me407, me408, me409, me410, me411, me412, me413, me414, me415, me416, me417, me418, me419, me420, me421, me422, me423, me424,
};

const unsigned int mapEnemySize[TOTALMAP] = {
	sizeof(me0) / 8, sizeof(me1) / 8, sizeof(me2) / 8, sizeof(me3) / 8,
	sizeof(me4) / 8, sizeof(me5) / 8, sizeof(me6) / 8, sizeof(me7) / 8, sizeof(me8) / 8, sizeof(me9) / 8,
	sizeof(me10) / 8, sizeof(me11) / 8, sizeof(me12) / 8, sizeof(me13) / 8, sizeof(me14) / 8, sizeof(me15) / 8, sizeof(me16) / 8, sizeof(me17) / 8, sizeof(me18) / 8, sizeof(me19) / 8, sizeof(me20) / 8, sizeof(me21) / 8, sizeof(me22) / 8, sizeof(me23) / 8, sizeof(me24) / 8, sizeof(me25) / 8,
	sizeof(me26) / 8, sizeof(me27) / 8, sizeof(me28) / 8, sizeof(me29) / 8, sizeof(me30) / 8, sizeof(me31) / 8, sizeof(me32) / 8, sizeof(me33) / 8, sizeof(me34) / 8, sizeof(me35) / 8, sizeof(me36) / 8, sizeof(me37) / 8, sizeof(me38) / 8, sizeof(me39) / 8, sizeof(me40) / 8, sizeof(me41) / 8, sizeof(me42) / 8,
	sizeof(me43) / 8, sizeof(me44) / 8, sizeof(me45) / 8, sizeof(me46) / 8, sizeof(me47) / 8, sizeof(me48) / 8, sizeof(me49) / 8, sizeof(me50) / 8, sizeof(me51) / 8, sizeof(me52) / 8, sizeof(me53) / 8, sizeof(me54) / 8, sizeof(me55) / 8, sizeof(me56) / 8, sizeof(me57) / 8, sizeof(me58) / 8, sizeof(me59) / 8, sizeof(me60) / 8, sizeof(me61) / 8, sizeof(me62) / 8,
	sizeof(me63) / 8, sizeof(me64) / 8, sizeof(me65) / 8, sizeof(me66) / 8, sizeof(me67) / 8, sizeof(me68) / 8, sizeof(me69) / 8, sizeof(me70) / 8, sizeof(me71) / 8, sizeof(me72) / 8, sizeof(me73) / 8, sizeof(me74) / 8, sizeof(me75) / 8, sizeof(me76) / 8, sizeof(me77) / 8, sizeof(me78) / 8, sizeof(me79) / 8, sizeof(me80) / 8, sizeof(me81) / 8,
	sizeof(me82) / 8, sizeof(me83) / 8, sizeof(me84) / 8, sizeof(me85) / 8, sizeof(me86) / 8, sizeof(me87) / 8, sizeof(me88) / 8, sizeof(me89) / 8, sizeof(me90) / 8, sizeof(me91) / 8, sizeof(me92) / 8, sizeof(me93) / 8, sizeof(me94) / 8, sizeof(me95) / 8, sizeof(me96) / 8,
	sizeof(me97) / 8, sizeof(me98) / 8, sizeof(me99) / 8, sizeof(me100) / 8, sizeof(me101) / 8, sizeof(me102) / 8, sizeof(me103) / 8, sizeof(me104) / 8, sizeof(me105) / 8, sizeof(me106) / 8, sizeof(me107) / 8, sizeof(me108) / 8, sizeof(me109) / 8, sizeof(me110) / 8, sizeof(me111) / 8, sizeof(me112) / 8, sizeof(me113) / 8,
	sizeof(me114) / 8,
	sizeof(me115) / 8, sizeof(me116) / 8, sizeof(me117) / 8, sizeof(me118) / 8, sizeof(me119) / 8, sizeof(me120) / 8, sizeof(me121) / 8, sizeof(me122) / 8, sizeof(me123) / 8, sizeof(me124) / 8, sizeof(me125) / 8,
	sizeof(me126) / 8, sizeof(me127) / 8, sizeof(me128) / 8, sizeof(me129) / 8, sizeof(me130) / 8, sizeof(me131) / 8, sizeof(me132) / 8, sizeof(me133) / 8, sizeof(me134) / 8, sizeof(me135) / 8, sizeof(me136) / 8, sizeof(me137) / 8, sizeof(me138) / 8, sizeof(me139) / 8, sizeof(me140) / 8, sizeof(me141) / 8, sizeof(me142) / 8, sizeof(me143) / 8, sizeof(me144) / 8,
	sizeof(me145) / 8, sizeof(me146) / 8, sizeof(me147) / 8, sizeof(me148) / 8, sizeof(me149) / 8, sizeof(me150) / 8, sizeof(me151) / 8, sizeof(me152) / 8, sizeof(me153) / 8, sizeof(me154) / 8, sizeof(me155) / 8, sizeof(me156) / 8, sizeof(me157) / 8, sizeof(me158) / 8, sizeof(me159) / 8, sizeof(me160) / 8, sizeof(me161) / 8, sizeof(me162) / 8, sizeof(me163) / 8, sizeof(me164) / 8, sizeof(me165) / 8,
	sizeof(me166) / 8, sizeof(me167) / 8, sizeof(me168) / 8, sizeof(me169) / 8, sizeof(me170) / 8, sizeof(me171) / 8, sizeof(me172) / 8, sizeof(me173) / 8, sizeof(me174) / 8, sizeof(me175) / 8, sizeof(me176) / 8, sizeof(me177) / 8, sizeof(me178) / 8, sizeof(me179) / 8, sizeof(me180) / 8, sizeof(me181) / 8, sizeof(me182) / 8, sizeof(me183) / 8, sizeof(me184) / 8,
	sizeof(me185) / 8, sizeof(me186) / 8, sizeof(me187) / 8, sizeof(me188) / 8, sizeof(me189) / 8, sizeof(me190) / 8, sizeof(me191) / 8, sizeof(me192) / 8, sizeof(me193) / 8, sizeof(me194) / 8, sizeof(me195) / 8, sizeof(me196) / 8, sizeof(me197) / 8, sizeof(me198) / 8, sizeof(me199) / 8, sizeof(me200) / 8, sizeof(me201) / 8, sizeof(me202) / 8, sizeof(me203) / 8, sizeof(me204) / 8,
	sizeof(me205) / 8, sizeof(me206) / 8, sizeof(me207) / 8, sizeof(me208) / 8, sizeof(me209) / 8, sizeof(me210) / 8, sizeof(me211) / 8, sizeof(me212) / 8, sizeof(me213) / 8, sizeof(me214) / 8, sizeof(me215) / 8, sizeof(me216) / 8, sizeof(me217) / 8, sizeof(me218) / 8, sizeof(me219) / 8, sizeof(me220) / 8, sizeof(me221) / 8, sizeof(me222) / 8, sizeof(me223) / 8, sizeof(me224) / 8, sizeof(me225) / 8,
	sizeof(me226) / 8, sizeof(me227) / 8, sizeof(me228) / 8, sizeof(me229) / 8, sizeof(me230) / 8, sizeof(me231) / 8, sizeof(me232) / 8, sizeof(me233) / 8, sizeof(me234) / 8, sizeof(me235) / 8, sizeof(me236) / 8, sizeof(me237) / 8, sizeof(me238) / 8, sizeof(me239) / 8, sizeof(me240) / 8, sizeof(me241) / 8, sizeof(me242) / 8, sizeof(me243) / 8,
	sizeof(me244) / 8, sizeof(me245) / 8, sizeof(me246) / 8, sizeof(me247) / 8, sizeof(me248) / 8, sizeof(me249) / 8, sizeof(me250) / 8, sizeof(me251) / 8, sizeof(me252) / 8, sizeof(me253) / 8, sizeof(me254) / 8, sizeof(me255) / 8, sizeof(me256) / 8, sizeof(me257) / 8, sizeof(me258) / 8, sizeof(me259) / 8, sizeof(me260) / 8, sizeof(me261) / 8, sizeof(me262) / 8,
	sizeof(me263) / 8, sizeof(me264) / 8, sizeof(me265) / 8, sizeof(me266) / 8, sizeof(me267) / 8, sizeof(me268) / 8, sizeof(me269) / 8, sizeof(me270) / 8, sizeof(me271) / 8, sizeof(me272) / 8, sizeof(me273) / 8, sizeof(me274) / 8, sizeof(me275) / 8, sizeof(me276) / 8, sizeof(me277) / 8, sizeof(me278) / 8, sizeof(me279) / 8,
	sizeof(me280) / 8, sizeof(me281) / 8, sizeof(me282) / 8, sizeof(me283) / 8, sizeof(me284) / 8, sizeof(me285) / 8, sizeof(me286) / 8, sizeof(me287) / 8, sizeof(me288) / 8, sizeof(me289) / 8, sizeof(me290) / 8, sizeof(me291) / 8, sizeof(me292) / 8, sizeof(me293) / 8,
	sizeof(me294) / 8, sizeof(me295) / 8, sizeof(me296) / 8, sizeof(me297) / 8, sizeof(me298) / 8, sizeof(me299) / 8, sizeof(me300) / 8, sizeof(me301) / 8, sizeof(me302) / 8, sizeof(me303) / 8, sizeof(me304) / 8, sizeof(me305) / 8, sizeof(me306) / 8,
	sizeof(me307) / 8, sizeof(me308) / 8, sizeof(me309) / 8, sizeof(me310) / 8, sizeof(me311) / 8, sizeof(me312) / 8, sizeof(me313) / 8, sizeof(me314) / 8, sizeof(me315) / 8, sizeof(me316) / 8, sizeof(me317) / 8, sizeof(me318) / 8, sizeof(me319) / 8, sizeof(me320) / 8, sizeof(me321) / 8, sizeof(me322) / 8, sizeof(me323) / 8, sizeof(me324) / 8, sizeof(me325) / 8, sizeof(me326) / 8, sizeof(me327) / 8, sizeof(me328) / 8, sizeof(me329) / 8, sizeof(me330) / 8, sizeof(me331) / 8, sizeof(me332) / 8, sizeof(me333) / 8, sizeof(me334) / 8, sizeof(me335) / 8, sizeof(me336) / 8, sizeof(me337) / 8, sizeof(me338) / 8, sizeof(me339) / 8, sizeof(me340) / 8, sizeof(me341) / 8, sizeof(me342) / 8, sizeof(me343) / 8, sizeof(me344) / 8, sizeof(me345) / 8, sizeof(me346) / 8, sizeof(me347) / 8, sizeof(me348) / 8, sizeof(me349) / 8, sizeof(me350) / 8, sizeof(me351) / 8, sizeof(me352) / 8, sizeof(me353) / 8, sizeof(me354) / 8, sizeof(me355) / 8, sizeof(me356) / 8, sizeof(me357) / 8, sizeof(me358) / 8, sizeof(me359) / 8, sizeof(me360) / 8, sizeof(me361) / 8, sizeof(me362) / 8, sizeof(me363) / 8,
	sizeof(me364) / 8,
	sizeof(me365) / 8, sizeof(me366) / 8, sizeof(me367) / 8, sizeof(me368) / 8, sizeof(me369) / 8, sizeof(me370) / 8, sizeof(me371) / 8, sizeof(me372) / 8, sizeof(me373) / 8, sizeof(me374) / 8,
	sizeof(me375) / 8, sizeof(me376) / 8, sizeof(me377) / 8, sizeof(me378) / 8, sizeof(me379) / 8, sizeof(me380) / 8, sizeof(me381) / 8, sizeof(me382) / 8, sizeof(me383) / 8, sizeof(me384) / 8,
	sizeof(me385) / 8, sizeof(me386) / 8, sizeof(me387) / 8, sizeof(me388) / 8, sizeof(me389) / 8, sizeof(me390) / 8, sizeof(me391) / 8, sizeof(me392) / 8, sizeof(me393) / 8, sizeof(me394) / 8,
	sizeof(me395) / 8, sizeof(me396) / 8, sizeof(me397) / 8, sizeof(me398) / 8, sizeof(me399) / 8, sizeof(me400) / 8, sizeof(me401) / 8, sizeof(me402) / 8, sizeof(me403) / 8, sizeof(me404) / 8,
	sizeof(me405) / 8,
	sizeof(me406) / 8, sizeof(me407) / 8, sizeof(me408) / 8, sizeof(me409) / 8, sizeof(me410) / 8, sizeof(me411) / 8, sizeof(me412) / 8, sizeof(me413) / 8, sizeof(me414) / 8, sizeof(me415) / 8, sizeof(me416) / 8, sizeof(me417) / 8, sizeof(me418) / 8, sizeof(me419) / 8, sizeof(me420) / 8, sizeof(me421) / 8, sizeof(me422) / 8, sizeof(me423) / 8, sizeof(me424) / 8,
};


//맵 배경 기본 색상
const unsigned int mapColor[TOTALMAPTYPE] = {
	0xB1E7F1,	//톨렘마을 바깥
	0x151410,   //0x443C43,	//톨렘마을 집안
	0x334752,	//톨레아 습지
	0xFFFFD4,	//금단의 계곡
	0x26343A,	//아틀란티스
	0x152026,	//아델라인 지하도
	0xB3CFFF,	//아델라인 성
	0x99B8EC,	//아델 평원
	0xA2CEFF,	//벨로네 마을
	0x301734,	//홍염의 대지
	0x4A617D,	//유구한 빙원
	0x35251F,	//뇌전의 공방
	0x110F10,	//황혼의 성역
	0xDBD9E7,	//골렘의 협곡
	0x084149,	//칠흑의 심연
	0x564963,	//드래곤의 무덤
	0x302E53,	//금지된 땅
	0x84ABAD,	//마왕성
	0x010821,	//우주공간
};


const signed char doorToKey[TOTALDOORTYPE] = {
	-1,	//DOORIMG_SWAMP
	-1, //ITEM_KEY0,	//DOORIMG_VALLEY
	-1, //ITEM_KEY1,	//DOORIMG_VALLEY_BOSS
	-1, //ITEM_KEY3,	//DOORIMG_PLAIN
	-1, //ITEM_KEY7,	//DOORIMG_SEWAGE
	-1, //ITEM_KEY2,	//DOORIMG_ATLANTICE
	-1,	//DOORIMG_FLAME
	-1, //ITEM_KEY4,	//DOORIMG_FROST
	-1, //ITEM_KEY5,	//DOORIMG_THUNDER
	-1, //ITEM_KEY6,	//DOORIMG_HOLY
	-1, //ITEM_KEY8,	//DOORIMG_CANYON
	-1, //ITEM_KEY9,	//DOORIMG_DARK
	-1, //ITEM_KEY10,	//DOORIMG_DRAGON
	-1, //ITEM_KEY11,	//DOORIMG_GHOST
	-1, //ITEM_KEY12,	//DOORIMG_DEVIL
	-1,	//DOORIMG_TETRA_RED
};

const unsigned char doorArray[TOTALDOOR] = {
	//문 이미지 인덱스
	DOORIMG_SWAMP, //DOOR_14A
	DOORIMG_SWAMP, //DOOR_14B
	DOORIMG_SWAMP, //DOOR_21A
	DOORIMG_SWAMP, //DOOR_21B
	DOORIMG_VALLEY_BOSS, //DOOR_29A
	DOORIMG_VALLEY_BOSS, //DOOR_29B
	DOORIMG_ATLANTICE, //DOOR_61A
	DOORIMG_ATLANTICE, //DOOR_61B
	DOORIMG_SEWAGE, //DOOR_63A
	DOORIMG_SEWAGE, //DOOR_63B
	DOORIMG_SEWAGE, //DOOR_66A
	DOORIMG_SEWAGE, //DOOR_66B
	DOORIMG_SEWAGE, //DOOR_93A
	DOORIMG_SEWAGE, //DOOR_93B
	DOORIMG_PLAIN, //DOOR_108A
	DOORIMG_PLAIN, //DOOR_108B
	DOORIMG_FLAME, //DOOR_127A
	DOORIMG_FLAME, //DOOR_127B
	DOORIMG_FLAME, //DOOR_129A
	DOORIMG_FLAME, //DOOR_129B
	DOORIMG_FROST,	//DOOR_164A
	DOORIMG_FROST,	//DOOR_164B
	DOORIMG_THUNDER,	//DOOR_167A
	DOORIMG_THUNDER,	//DOOR_167B
	DOORIMG_HOLY,	//DOOR_188A
	DOORIMG_HOLY,	//DOOR_188B
	DOORIMG_CANYON,	//DOOR_205A
	DOORIMG_CANYON,	//DOOR_205B
	DOORIMG_DARK,		//DOOR_230A
	DOORIMG_DARK,		//DOOR_230B
	DOORIMG_DRAGON,		//DOOR_255A
	DOORIMG_DRAGON,		//DOOR_255B
	DOORIMG_GHOST,		//DOOR_273A
	DOORIMG_GHOST,		//DOOR_273B
	DOORIMG_DEVIL, //DOOR_292A
	DOORIMG_DEVIL, //DOOR_292B
	DOORIMG_DEVIL, //DOOR_295A//보스방 왼쪽
	DOORIMG_DEVIL, //DOOR_295B//보스방 오른쪽
	DOORIMG_TETRA_RED,		//DOOR_362
	DOORIMG_TETRA_RED,		//DOOR_363

};

const unsigned char pushArray[TOTALPUSH * 2] = {
	0, 0,	//PUSH_NORMAL
};

const unsigned char boxStar[TOTAL_BOX * 2] = {
	STAR1, 4,//BOX_INGAME = 0,
	STAR1, 5,//BOX_EQUIP_WOOD,
	STAR1, 6,//BOX_EQUIP_SILVER,
	STAR1, 7,//BOX_EQUIP_GOLD,
	STAR1, 8,//BOX_EQUIP_MAGIC,
	STAR1, 9,//BOX_EQUIP_HERO,
	STAR1, 10,//BOX_EQUIP_LEGEND,
	STAR1, 5,//BOX_CREW_SEBASTIAN,//동료들의 장비가 나오는 박스
	STAR1, 6,//BOX_CREW_PRINCESS,//동료들의 장비가 나오는 박스
	STAR1, 7,//BOX_CREW_KING,//동료들의 장비가 나오는 박스
	STAR1, 8,//BOX_CREW_DEVIL,//동료들의 장비가 나오는 박스
	STAR1, 3,//BOX_ATTR_FIRE,//몬스터 뽑기
	STAR1, 4,//BOX_ATTR_FROST,
	STAR1, 5,//BOX_ATTR_EARTH,
	STAR1, 6,//BOX_ATTR_THUNDER,
	STAR1, 7,//BOX_ATTR_LIGHT,
	STAR1, 8,//BOX_ATTR_DARK,
};

const unsigned char boxArray[TOTALBOX * 4] = {
	//타입, 레벨, 디테일, 등급(소비아이템은 갯수)
	ITEM_SWORD, 1, ITEM_SWORD_STICK, GRADE_NORMAL, //BOX_NORMAL	//습지, 인어의 상//인어의 머리핀
};

const unsigned char markArray[TOTALMARK * 7] = {
	//0 : 줄 갯수
	//1 : 첫번째 줄 화살표 방향(+10은 오른쪽이냐 왼쪽이냐)
	//2 : 첫번째 줄 텍스트
	//3 : 두번째 줄 화살표 방향
	//4 : 두번째 줄 텍스트
	//5 : 세번째 줄 화살표 방향
	//6 : 세번째 줄 텍스트
	1, 10 + DIR_RIGHT, AREA_DOCK, 0, 0, 0, 0,	//MARK_NORMAL : 톨레아 습지 15번방
};

const unsigned char itemArray[TOTALITEM * 3] = {
	//0 : 아이템 type
	//1 : 아이템 detail
	//2 : 아이템 motion
	ITEM_QUEST, ITEM_QUEST_MUSHROOM, GRADE_NORMAL,//ITEM_OPENING		//마일즈팔찌
	ITEM_SWORD, ITEM_SWORD_STICK, GRADE_NORMAL,//HIDDEN_0		//마일즈팔찌
};

const unsigned char dianaStoneArray[TOTALDIANASTONE] = {
	DIANASTONE,	//DIANASTONE
};

const unsigned char magmaArray[TOTALMAGMA] = {
	//마그마 솟는 높이
	10 * _2X,	//MAGMA
};

const unsigned char wormHoleArray[TOTALWORMHOLE * 3] = {
	97, 29, 20,		//WORMHOLE
};

const unsigned char warpArrayType[TOTALWARP] = {
	//type의 데이터
	//0: 일반 방간 이동
	//1: 문으로 들어가서 이동
	//2: 잠겨져 있어서 못들어가는 문
	0,			//WARP_14_1,//SWAP5
	0,        //WARP_21_1,//SWAMP12
	0,        //WARP_29_1,//VALLEY4
	0,        //WARP_61_1,//ATLANTICE19
	0,        //WARP_66_1,//SEWAGE4
	0,		  //WARP_93_1,//CASTLE12
	0,        //WARP_108_1,//PLAIN12
	0,        //WARP_129_1,//FLAME4
	0,        //WARP_164_1,//FROST20
	0,        //WARP_167_1,//THUNDER2
	0,        //WARP_188_1,//LIGHT4
	0,        //WARP_205_1,//GOLEMVALLEY1
	0,        //WARP_230_1,//DARKNESS5
	0,        //WARP_255_1,//DRAGON12
	0,        //WARP_273_1,//GHOST11
	0,        //WARP_292_1,//DEVIL13
	0,        //WARP_295_1,//SPACE2

	0,	//WARP_365_0
	0,        //WARP_366_0
	0,        //WARP_367_0
	0,        //WARP_368_0
	0,        //WARP_369_0
	0,        //WARP_370_0
	0,        //WARP_371_0
	0,        //WARP_372_0
	0,        //WARP_373_0
	0,        //WARP_374_0
	0,        //WARP_375_0
	0,        //WARP_366_0
	0,        //WARP_377_0
	0,        //WARP_378_0
	0,        //WARP_379_0
	0,        //WARP_380_0
	0,        //WARP_381_0
	0,        //WARP_382_0
	0,        //WARP_383_0
	0,        //WARP_384_0
	0,        //WARP_385_0
	0,        //WARP_386_0
	0,        //WARP_387_0
	0,        //WARP_388_0
	0,        //WARP_389_0
	0,        //WARP_390_0
	0,        //WARP_391_0
	0,        //WARP_392_0
	0,        //WARP_393_0
	0,        //WARP_394_0
	0,        //WARP_395_0
	0,        //WARP_396_0
	0,        //WARP_397_0
	0,        //WARP_398_0
	0,        //WARP_399_0
	0,        //WARP_400_0
	0,        //WARP_401_0
	0,        //WARP_402_0
	0,        //WARP_403_0mapDatas
	0,        //WARP_404_0
};

const signed short warpArray[TOTALWARP * 5] = {
	//이동전 데이터 0:dx, 1:dy,
	//이동후 데이터 2:mapIdx, 3:x, 4:y (이동후 좌표는 이전워프포인트와 주인공의 차이만큼을 이동후워프포인트에서 다시 살려준다.)
	//type의 데이터
	//0: 일반 방간 이동
	//1: 문으로 들어가서 이동
	//2: 잠겨져 있어서 못들어가는 문
	1, 32 * _2X, SWAMP5, 16 * _2X - 1, 256 * _2X,	//WARP_14_1,//SWAMP5
	1, 32 * _2X, SWAMP12, 16 * _2X - 1, 256 * _2X,	//WARP_21_1,//SWAMP12
	1, 32 * _2X, VALLEY4, 16 * _2X - 1, 256 * _2X,	//WARP_29_1,//VALLEY4
	1, 32 * _2X, ATLANTICE19, 16 * _2X - 1, 256 * _2X,	//WARP_61_1,//ATLANTICE19
	1, 32 * _2X, SEWAGE4, 16 * _2X - 1, 256 * _2X,	//WARP_66_1,//SEWAGE4
	1, 32 * _2X, PLAIN12, 16 * _2X - 1, 256 * _2X,	//WARP_108_1,//PLAIN12
	1, 32 * _2X, FLAME4, 16 * _2X - 1, 256 * _2X,	//WARP_129_1,//FLAME4
	1, 32 * _2X, FROST20, 16 * _2X - 1, 256 * _2X,	//WARP_164_1,//FROST20
	1, 32 * _2X, THUNDER2, 16 * _2X - 1, 256 * _2X,	//WARP_167_1,//THUNDER2
	1, 32 * _2X, LIGHT4, 16 * _2X - 1, 256 * _2X,		//WARP_188_1,//LIGHT4
	1, 32 * _2X, GOLEMVALLEY1, 16 * _2X - 1, 256 * _2X,	//WARP_205_1,//GOLEMVALLEY1
	1, 32 * _2X, DARKNESS5, 16 * _2X - 1, 256 * _2X,	//WARP_230_1,//DARKNESS5
	1, 32 * _2X, DRAGON12, 16 * _2X - 1, 256 * _2X,	//WARP_255_1,//DRAGON12
	1, 32 * _2X, GHOST11, 16 * _2X - 1, 256 * _2X,	//WARP_273_1,//GHOST11
	1, 32 * _2X, DEVIL13, 16 * _2X - 1, 256 * _2X,	//WARP_292_1,//DEVIL13
	1, 32 * _2X, SPACE2, 16 * _2X - 1, 256 * _2X,	//WARP_295_1,//SPACE2

	160 * _2X, 1, 0, 0, 0,		//WARP_365_0
	160 * _2X, 1, 0, 0, 0,		//WARP_366_0
	160 * _2X, 1, 0, 0, 0,		//WARP_367_0
	160 * _2X, 1, 0, 0, 0,		//WARP_368_0
	160 * _2X, 1, 0, 0, 0,		//WARP_369_0
	160 * _2X, 1, 0, 0, 0,		//WARP_370_0
	160 * _2X, 1, 0, 0, 0,		//WARP_371_0
	160 * _2X, 1, 0, 0, 0,		//WARP_372_0
	160 * _2X, 1, 0, 0, 0,		//WARP_373_0
	160 * _2X, 1, 0, 0, 0,		//WARP_374_0
	160 * _2X, 1, 0, 0, 0,		//WARP_375_0
	160 * _2X, 1, 0, 0, 0,		//WARP_366_0
	160 * _2X, 1, 0, 0, 0,		//WARP_377_0
	160 * _2X, 1, 0, 0, 0,		//WARP_378_0
	160 * _2X, 1, 0, 0, 0,		//WARP_379_0
	160 * _2X, 1, 0, 0, 0,		//WARP_380_0
	160 * _2X, 1, 0, 0, 0,		//WARP_381_0
	160 * _2X, 1, 0, 0, 0,		//WARP_382_0
	160 * _2X, 1, 0, 0, 0,		//WARP_383_0
	160 * _2X, 1, 0, 0, 0,		//WARP_384_0
	160 * _2X, 1, 0, 0, 0,		//WARP_385_0
	160 * _2X, 1, 0, 0, 0,		//WARP_386_0
	160 * _2X, 1, 0, 0, 0,		//WARP_387_0
	160 * _2X, 1, 0, 0, 0,		//WARP_388_0
	160 * _2X, 1, 0, 0, 0,		//WARP_389_0
	160 * _2X, 1, 0, 0, 0,		//WARP_390_0
	160 * _2X, 1, 0, 0, 0,		//WARP_391_0
	160 * _2X, 1, 0, 0, 0,		//WARP_392_0
	160 * _2X, 1, 0, 0, 0,		//WARP_393_0
	160 * _2X, 1, 0, 0, 0,		//WARP_394_0
	160 * _2X, 1, 0, 0, 0,		//WARP_395_0
	160 * _2X, 1, 0, 0, 0,		//WARP_396_0
	160 * _2X, 1, 0, 0, 0,		//WARP_397_0
	160 * _2X, 1, 0, 0, 0,		//WARP_398_0
	160 * _2X, 1, 0, 0, 0,		//WARP_399_0
	160 * _2X, 1, 0, 0, 0,		//WARP_400_0
	160 * _2X, 1, 0, 0, 0,		//WARP_401_0
	160 * _2X, 1, 0, 0, 0,		//WARP_402_0
	160 * _2X, 1, 0, 0, 0,		//WARP_403_0
	160 * _2X, 1, 0, 0, 0,		//WARP_404_0
};

const unsigned short backObjImg[TOTALBACKIMG * 4] = {
	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg0.bmp
	166 * _2X, 180 * _2X, 77 * _2X, 7 * _2X,	//0
	0 * _2X, 0 * _2X, 136 * _2X, 47 * _2X,	//1
	95 * _2X, 187 * _2X, 164 * _2X, 36 * _2X,	//2
	51 * _2X, 144 * _2X, 5 * _2X, 47 * _2X,	//3
	136 * _2X, 0 * _2X, 51 * _2X, 47 * _2X,	//4
	56 * _2X, 183 * _2X, 39 * _2X, 40 * _2X,	//5
	100 * _2X, 157 * _2X, 21 * _2X, 23 * _2X,	//6
	162 * _2X, 153 * _2X, 40 * _2X, 27 * _2X,	//7
	135 * _2X, 47 * _2X, 31 * _2X, 38 * _2X,	//8
	166 * _2X, 47 * _2X, 20 * _2X, 20 * _2X,	//9
	87 * _2X, 47 * _2X, 48 * _2X, 58 * _2X,	//10
	202 * _2X, 139 * _2X, 41 * _2X, 41 * _2X,	//11
	35 * _2X, 160 * _2X, 16 * _2X, 9 * _2X,	//12
	168 * _2X, 101 * _2X, 18 * _2X, 52 * _2X,	//13
	187 * _2X, 0 * _2X, 72 * _2X, 55 * _2X,	//14
	58 * _2X, 105 * _2X, 40 * _2X, 33 * _2X,	//15
	135 * _2X, 85 * _2X, 32 * _2X, 29 * _2X,	//16
	136 * _2X, 114 * _2X, 32 * _2X, 28 * _2X,	//17
	20 * _2X, 105 * _2X, 38 * _2X, 39 * _2X,	//18
	78 * _2X, 153 * _2X, 16 * _2X, 16 * _2X,	//19
	121 * _2X, 159 * _2X, 41 * _2X, 28 * _2X,	//20
	0 * _2X, 105 * _2X, 8 * _2X, 33 * _2X,	//21
	98 * _2X, 105 * _2X, 38 * _2X, 23 * _2X,	//22
	0 * _2X, 138 * _2X, 22 * _2X, 23 * _2X,	//23
	40 * _2X, 192 * _2X, 16 * _2X, 31 * _2X,	//24
	166 * _2X, 67 * _2X, 20 * _2X, 20 * _2X,	//25
	0 * _2X, 167 * _2X, 17 * _2X, 26 * _2X,	//26
	0 * _2X, 47 * _2X, 87 * _2X, 58 * _2X,	//27
	64 * _2X, 158 * _2X, 7 * _2X, 11 * _2X,	//28
	16 * _2X, 201 * _2X, 24 * _2X, 22 * _2X,	//29
	129 * _2X, 142 * _2X, 36 * _2X, 16 * _2X,	//30
	22 * _2X, 151 * _2X, 21 * _2X, 9 * _2X,	//31
	16 * _2X, 193 * _2X, 24 * _2X, 8 * _2X,	//32
	85 * _2X, 138 * _2X, 9 * _2X, 15 * _2X,	//33
	56 * _2X, 158 * _2X, 8 * _2X, 7 * _2X,	//34
	186 * _2X, 55 * _2X, 25 * _2X, 82 * _2X,	//35
	0 * _2X, 203 * _2X, 16 * _2X, 20 * _2X,	//36
	97 * _2X, 217 * _2X, 160 * _2X, 6 * _2X,	//37
	211 * _2X, 55 * _2X, 48 * _2X, 28 * _2X,	//38
	211 * _2X, 83 * _2X, 48 * _2X, 28 * _2X,	//39
	211 * _2X, 111 * _2X, 48 * _2X, 28 * _2X,	//40
	211 * _2X, 67 * _2X, 48 * _2X, 16 * _2X,	//41
	211 * _2X, 95 * _2X, 48 * _2X, 16 * _2X,	//42
	211 * _2X, 123 * _2X, 48 * _2X, 16 * _2X,	//43
	8 * _2X, 105 * _2X, 12 * _2X, 16 * _2X,	//44
	56 * _2X, 169 * _2X, 14 * _2X, 13 * _2X,	//45

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg1.bmp
	0 * _2X, 73 * _2X, 43 * _2X, 48 * _2X,	//46
	43 * _2X, 0 * _2X, 40 * _2X, 34 * _2X,	//47
	82 * _2X, 56 * _2X, 53 * _2X, 23 * _2X,	//48
	188 * _2X, 109 * _2X, 27 * _2X, 23 * _2X,	//49
	164 * _2X, 20 * _2X, 33 * _2X, 23 * _2X,	//50
	164 * _2X, 43 * _2X, 33 * _2X, 22 * _2X,	//51
	131 * _2X, 105 * _2X, 19 * _2X, 27 * _2X,	//52
	0 * _2X, 0 * _2X, 43 * _2X, 26 * _2X,	//53
	43 * _2X, 77 * _2X, 11 * _2X, 28 * _2X,	//54
	42 * _2X, 34 * _2X, 40 * _2X, 43 * _2X,	//55
	197 * _2X, 12 * _2X, 18 * _2X, 49 * _2X,	//56
	84 * _2X, 109 * _2X, 6 * _2X, 6 * _2X,	//57
	90 * _2X, 93 * _2X, 16 * _2X, 22 * _2X,	//58
	126 * _2X, 79 * _2X, 25 * _2X, 25 * _2X,	//59
	135 * _2X, 58 * _2X, 13 * _2X, 21 * _2X,	//60
	76 * _2X, 115 * _2X, 24 * _2X, 17 * _2X,	//61
	177 * _2X, 123 * _2X, 11 * _2X, 8 * _2X,	//62
	0 * _2X, 121 * _2X, 20 * _2X, 10 * _2X,	//63
	20 * _2X, 121 * _2X, 15 * _2X, 10 * _2X,	//64
	115 * _2X, 114 * _2X, 16 * _2X, 18 * _2X,	//65
	150 * _2X, 109 * _2X, 6 * _2X, 23 * _2X,	//66
	54 * _2X, 77 * _2X, 6 * _2X, 28 * _2X,	//67
	215 * _2X, 64 * _2X, 8 * _2X, 32 * _2X,	//68
	118 * _2X, 79 * _2X, 8 * _2X, 16 * _2X,	//69
	215 * _2X, 32 * _2X, 8 * _2X, 32 * _2X,	//70
	215 * _2X, 96 * _2X, 8 * _2X, 32 * _2X,	//71
	110 * _2X, 79 * _2X, 8 * _2X, 16 * _2X,	//72
	215 * _2X, 0 * _2X, 8 * _2X, 32 * _2X,	//73
	95 * _2X, 79 * _2X, 15 * _2X, 14 * _2X,	//74
	151 * _2X, 75 * _2X, 5 * _2X, 33 * _2X,	//75
	156 * _2X, 119 * _2X, 21 * _2X, 13 * _2X,	//76
	164 * _2X, 65 * _2X, 33 * _2X, 10 * _2X,	//77
	83 * _2X, 0 * _2X, 49 * _2X, 34 * _2X,	//78
	75 * _2X, 117 * _2X, 1 * _2X, 15 * _2X,	//79
	82 * _2X, 34 * _2X, 27 * _2X, 22 * _2X,	//80
	109 * _2X, 34 * _2X, 23 * _2X, 22 * _2X,	//81
	156 * _2X, 75 * _2X, 21 * _2X, 16 * _2X,	//82
	71 * _2X, 123 * _2X, 4 * _2X, 9 * _2X,	//83
	70 * _2X, 113 * _2X, 5 * _2X, 10 * _2X,	//84
	0 * _2X, 26 * _2X, 42 * _2X, 47 * _2X,	//85
	106 * _2X, 97 * _2X, 25 * _2X, 17 * _2X,	//86
	132 * _2X, 0 * _2X, 16 * _2X, 20 * _2X,	//87
	148 * _2X, 0 * _2X, 16 * _2X, 20 * _2X,	//88
	164 * _2X, 0 * _2X, 16 * _2X, 20 * _2X,	//89
	180 * _2X, 0 * _2X, 17 * _2X, 20 * _2X,	//90
	193 * _2X, 75 * _2X, 22 * _2X, 34 * _2X,	//91
	197 * _2X, 61 * _2X, 18 * _2X, 14 * _2X,	//92
	75 * _2X, 95 * _2X, 15 * _2X, 14 * _2X,	//93
	177 * _2X, 75 * _2X, 16 * _2X, 34 * _2X,	//94
	156 * _2X, 91 * _2X, 21 * _2X, 12 * _2X,	//95
	156 * _2X, 103 * _2X, 21 * _2X, 16 * _2X,	//96
	148 * _2X, 58 * _2X, 16 * _2X, 17 * _2X,	//97
	148 * _2X, 28 * _2X, 16 * _2X, 30 * _2X,	//98
	55 * _2X, 120 * _2X, 16 * _2X, 12 * _2X,	//99
	75 * _2X, 79 * _2X, 16 * _2X, 16 * _2X,	//100
	197 * _2X, 0 * _2X, 18 * _2X, 12 * _2X,	//101
	100 * _2X, 115 * _2X, 15 * _2X, 17 * _2X,	//102
	35 * _2X, 121 * _2X, 20 * _2X, 9 * _2X,	//103
	43 * _2X, 106 * _2X, 26 * _2X, 14 * _2X,	//104
	132 * _2X, 28 * _2X, 16 * _2X, 30 * _2X,	//105
	91 * _2X, 79 * _2X, 4 * _2X, 12 * _2X,	//106
	69 * _2X, 106 * _2X, 5 * _2X, 7 * _2X,	//107
	0 * _2X, 0 * _2X, 36 * _2X, 36 * _2X,	//108

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg2.bmp
	0 * _2X, 0 * _2X, 108 * _2X, 80 * _2X,	//109
	0 * _2X, 156 * _2X, 94 * _2X, 27 * _2X,	//110
	134 * _2X, 110 * _2X, 10 * _2X, 22 * _2X,	//111
	144 * _2X, 110 * _2X, 26 * _2X, 35 * _2X,	//112
	70 * _2X, 80 * _2X, 38 * _2X, 40 * _2X,	//113
	66 * _2X, 80 * _2X, 4 * _2X, 27 * _2X,	//114
	0 * _2X, 112 * _2X, 70 * _2X, 38 * _2X,	//115
	108 * _2X, 0 * _2X, 30 * _2X, 110 * _2X,	//116
	138 * _2X, 0 * _2X, 32 * _2X, 32 * _2X,	//117
	113 * _2X, 129 * _2X, 20 * _2X, 16 * _2X,	//118

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg3.bmp
	0 * _2X, 0 * _2X, 58 * _2X, 74 * _2X,	//119
	58 * _2X, 32 * _2X, 22 * _2X, 32 * _2X,	//120
	58 * _2X, 0 * _2X, 35 * _2X, 32 * _2X,	//121
	107 * _2X, 74 * _2X, 16 * _2X, 23 * _2X,	//122

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg4.bmp
	71 * _2X, 0 * _2X, 34 * _2X, 40 * _2X,	//123
	71 * _2X, 40 * _2X, 34 * _2X, 33 * _2X,	//124

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg5.bmp
	0 * _2X, 0 * _2X, 26 * _2X, 28 * _2X,	//125
	24 * _2X, 43 * _2X, 30 * _2X, 4 * _2X,	//126
	26 * _2X, 0 * _2X, 28 * _2X, 28 * _2X,	//127
	108 * _2X, 22 * _2X, 8 * _2X, 12 * _2X,	//128
	32 * _2X, 28 * _2X, 6 * _2X, 15 * _2X,	//129
	38 * _2X, 28 * _2X, 16 * _2X, 14 * _2X,	//130
	54 * _2X, 32 * _2X, 16 * _2X, 14 * _2X,	//131
	70 * _2X, 32 * _2X, 16 * _2X, 14 * _2X,	//132

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg6.bmp
	112 * _2X, 118 * _2X, 16 * _2X, 16 * _2X,	//133
	96 * _2X, 0 * _2X, 62 * _2X, 48 * _2X,	//134
	158 * _2X, 0 * _2X, 13 * _2X, 48 * _2X,	//135
	48 * _2X, 95 * _2X, 18 * _2X, 32 * _2X,	//136
	0 * _2X, 130 * _2X, 25 * _2X, 57 * _2X,	//137
	171 * _2X, 0 * _2X, 30 * _2X, 24 * _2X,	//138
	171 * _2X, 24 * _2X, 30 * _2X, 8 * _2X,	//139
	171 * _2X, 32 * _2X, 30 * _2X, 20 * _2X,	//140
	195 * _2X, 127 * _2X, 16 * _2X, 42 * _2X,	//141
	68 * _2X, 72 * _2X, 37 * _2X, 37 * _2X,	//142
	201 * _2X, 0 * _2X, 10 * _2X, 60 * _2X,	//143
	107 * _2X, 48 * _2X, 32 * _2X, 23 * _2X,	//144
	164 * _2X, 78 * _2X, 22 * _2X, 38 * _2X,	//145
	26 * _2X, 94 * _2X, 22 * _2X, 36 * _2X,	//146
	170 * _2X, 169 * _2X, 23 * _2X, 34 * _2X,	//147
	0 * _2X, 46 * _2X, 51 * _2X, 32 * _2X,	//148
	133 * _2X, 80 * _2X, 30 * _2X, 18 * _2X,	//149
	113 * _2X, 134 * _2X, 15 * _2X, 18 * _2X,	//150
	66 * _2X, 109 * _2X, 22 * _2X, 18 * _2X,	//151
	145 * _2X, 122 * _2X, 36 * _2X, 29 * _2X,	//152
	186 * _2X, 53 * _2X, 15 * _2X, 37 * _2X,	//153
	0 * _2X, 0 * _2X, 62 * _2X, 46 * _2X,	//154
	62 * _2X, 0 * _2X, 34 * _2X, 46 * _2X,	//155
	51 * _2X, 46 * _2X, 32 * _2X, 20 * _2X,	//156
	64 * _2X, 178 * _2X, 48 * _2X, 25 * _2X,	//157
	25 * _2X, 146 * _2X, 19 * _2X, 28 * _2X,	//158
	171 * _2X, 143 * _2X, 24 * _2X, 26 * _2X,	//159
	185 * _2X, 89 * _2X, 18 * _2X, 26 * _2X,	//160
	162 * _2X, 52 * _2X, 24 * _2X, 26 * _2X,	//161
	139 * _2X, 48 * _2X, 22 * _2X, 24 * _2X,	//162
	83 * _2X, 48 * _2X, 24 * _2X, 24 * _2X,	//163
	0 * _2X, 187 * _2X, 64 * _2X, 16 * _2X,	//164
	0 * _2X, 78 * _2X, 56 * _2X, 16 * _2X,	//165
	87 * _2X, 160 * _2X, 15 * _2X, 17 * _2X,	//166
	152 * _2X, 175 * _2X, 18 * _2X, 28 * _2X,	//167
	193 * _2X, 169 * _2X, 18 * _2X, 34 * _2X,	//168
	44 * _2X, 127 * _2X, 43 * _2X, 51 * _2X,	//169
	0 * _2X, 94 * _2X, 26 * _2X, 36 * _2X,	//170
	88 * _2X, 109 * _2X, 15 * _2X, 14 * _2X,	//171
	87 * _2X, 137 * _2X, 18 * _2X, 14 * _2X,	//172
	88 * _2X, 123 * _2X, 18 * _2X, 14 * _2X,	//173
	46 * _2X, 178 * _2X, 18 * _2X, 5 * _2X,	//174
	155 * _2X, 171 * _2X, 15 * _2X, 4 * _2X,	//175
	162 * _2X, 116 * _2X, 24 * _2X, 6 * _2X,	//176
	144 * _2X, 112 * _2X, 18 * _2X, 10 * _2X,	//177
	128 * _2X, 112 * _2X, 16 * _2X, 24 * _2X,	//178
	134 * _2X, 136 * _2X, 10 * _2X, 11 * _2X,	//179
	142 * _2X, 177 * _2X, 10 * _2X, 9 * _2X,	//180
	181 * _2X, 127 * _2X, 14 * _2X, 14 * _2X,	//181
	87 * _2X, 151 * _2X, 18 * _2X, 10 * _2X,	//182
	201 * _2X, 60 * _2X, 10 * _2X, 19 * _2X,	//183
	203 * _2X, 79 * _2X, 8 * _2X, 19 * _2X,	//184
	134 * _2X, 72 * _2X, 28 * _2X, 8 * _2X,	//185
	120 * _2X, 173 * _2X, 14 * _2X, 12 * _2X,	//186
	136 * _2X, 98 * _2X, 28 * _2X, 14 * _2X,	//187
	105 * _2X, 102 * _2X, 22 * _2X, 16 * _2X,	//188
	25 * _2X, 130 * _2X, 16 * _2X, 16 * _2X,	//189
	111 * _2X, 153 * _2X, 20 * _2X, 20 * _2X,	//190
	147 * _2X, 187 * _2X, 5 * _2X, 16 * _2X,	//191
	186 * _2X, 115 * _2X, 18 * _2X, 12 * _2X,	//192
	155 * _2X, 151 * _2X, 15 * _2X, 20 * _2X,	//193
	55 * _2X, 66 * _2X, 16 * _2X, 17 * _2X,	//194
	25 * _2X, 174 * _2X, 21 * _2X, 13 * _2X,	//195
	130 * _2X, 185 * _2X, 17 * _2X, 18 * _2X,	//196
	112 * _2X, 185 * _2X, 18 * _2X, 18 * _2X,	//197
	204 * _2X, 98 * _2X, 7 * _2X, 25 * _2X,	//198
	105 * _2X, 72 * _2X, 28 * _2X, 30 * _2X,	//199

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg7.bmp
	16 * _2X, 46 * _2X, 40 * _2X, 43 * _2X,	//200
	0 * _2X, 89 * _2X, 28 * _2X, 25 * _2X,	//201
	0 * _2X, 0 * _2X, 33 * _2X, 18 * _2X,	//202
	16 * _2X, 18 * _2X, 22 * _2X, 28 * _2X,	//203
	33 * _2X, 0 * _2X, 14 * _2X, 12 * _2X,	//204
	38 * _2X, 14 * _2X, 16 * _2X, 32 * _2X,	//205

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg8.bmp
	0 * _2X, 0 * _2X, 112 * _2X, 112 * _2X,	//206
	0 * _2X, 239 * _2X, 27 * _2X, 22 * _2X,	//207
	50 * _2X, 160 * _2X, 18 * _2X, 66 * _2X,	//208
	68 * _2X, 113 * _2X, 42 * _2X, 63 * _2X,	//209
	0 * _2X, 160 * _2X, 51 * _2X, 66 * _2X,	//210
	0 * _2X, 113 * _2X, 68 * _2X, 47 * _2X,	//211
	75 * _2X, 239 * _2X, 40 * _2X, 22 * _2X,	//212
	68 * _2X, 175 * _2X, 23 * _2X, 19 * _2X,	//213
	91 * _2X, 175 * _2X, 24 * _2X, 20 * _2X,	//214
	100 * _2X, 195 * _2X, 12 * _2X, 14 * _2X,	//215
	92 * _2X, 195 * _2X, 8 * _2X, 16 * _2X,	//216
	68 * _2X, 194 * _2X, 24 * _2X, 22 * _2X,	//217
	69 * _2X, 216 * _2X, 38 * _2X, 16 * _2X,	//218
	0 * _2X, 226 * _2X, 25 * _2X, 9 * _2X,	//219
	51 * _2X, 226 * _2X, 18 * _2X, 13 * _2X,	//220
	25 * _2X, 226 * _2X, 26 * _2X, 12 * _2X,	//221

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg9.bmp
	82 * _2X, 44 * _2X, 20 * _2X, 30 * _2X,	//222
	119 * _2X, 0 * _2X, 38 * _2X, 32 * _2X,	//223
	119 * _2X, 32 * _2X, 34 * _2X, 40 * _2X,	//224

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg10.bmp
	102 * _2X, 46 * _2X, 28 * _2X, 20 * _2X,	//225
	80 * _2X, 58 * _2X, 22 * _2X, 22 * _2X,	//226

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg11.bmp
	0 * _2X, 0 * _2X, 18 * _2X, 40 * _2X,	//227
	41 * _2X, 0 * _2X, 15 * _2X, 24 * _2X,	//228
	23 * _2X, 22 * _2X, 16 * _2X, 18 * _2X,	//229
	64 * _2X, 0 * _2X, 50 * _2X, 59 * _2X,	//230

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg12.bmp
	0 * _2X, 73 * _2X, 34 * _2X, 40 * _2X,	//231
	38 * _2X, 0 * _2X, 18 * _2X, 40 * _2X,	//232
	0 * _2X, 0 * _2X, 38 * _2X, 54 * _2X,	//233
	38 * _2X, 40 * _2X, 18 * _2X, 34 * _2X,	//234
	34 * _2X, 90 * _2X, 23 * _2X, 23 * _2X,	//235

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg13.bmp
	56 * _2X, 27 * _2X, 28 * _2X, 48 * _2X,	//236
	84 * _2X, 27 * _2X, 26 * _2X, 54 * _2X,	//237
	24 * _2X, 27 * _2X, 32 * _2X, 28 * _2X,	//238
	22 * _2X, 87 * _2X, 25 * _2X, 26 * _2X,	//239
	47 * _2X, 83 * _2X, 31 * _2X, 30 * _2X,	//240
	22 * _2X, 75 * _2X, 13 * _2X, 12 * _2X,	//241
	0 * _2X, 93 * _2X, 16 * _2X, 20 * _2X,	//242
	16 * _2X, 79 * _2X, 6 * _2X, 20 * _2X,	//243
	16 * _2X, 99 * _2X, 6 * _2X, 14 * _2X,	//244

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg14.bmp
	17 * _2X, 185 * _2X, 26 * _2X, 22 * _2X,	//0
	0 * _2X, 35 * _2X, 34 * _2X, 36 * _2X,	//1
	18 * _2X, 0 * _2X, 26 * _2X, 29 * _2X,	//2
	0 * _2X, 0 * _2X, 18 * _2X, 35 * _2X,	//3
	36 * _2X, 147 * _2X, 19 * _2X, 24 * _2X,	//4
	16 * _2X, 103 * _2X, 12 * _2X, 10 * _2X,	//5
	20 * _2X, 115 * _2X, 32 * _2X, 32 * _2X,	//6
	16 * _2X, 71 * _2X, 16 * _2X, 32 * _2X,	//7

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg15.bmp
	0 * _2X, 104 * _2X, 45 * _2X, 54 * _2X,	//8
	0 * _2X, 0 * _2X, 34 * _2X, 36 * _2X,	//9
	60 * _2X, 68 * _2X, 8 * _2X, 36 * _2X,	//10
	46 * _2X, 104 * _2X, 24 * _2X, 20 * _2X,	//11
	0 * _2X, 36 * _2X, 32 * _2X, 34 * _2X,	//12
	38 * _2X, 158 * _2X, 17 * _2X, 12 * _2X,	//13

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg16.bmp
	0 * _2X, 0 * _2X, 42 * _2X, 60 * _2X,	//14
	0 * _2X, 60 * _2X, 48 * _2X, 43 * _2X,	//15
	51 * _2X, 44 * _2X, 20 * _2X, 28 * _2X,	//16
	77 * _2X, 20 * _2X, 32 * _2X, 26 * _2X,	//17
	42 * _2X, 0 * _2X, 28 * _2X, 42 * _2X,	//18
	72 * _2X, 46 * _2X, 12 * _2X, 23 * _2X,	//19
	70 * _2X, 20 * _2X, 7 * _2X, 16 * _2X,	//20
	84 * _2X, 47 * _2X, 52 * _2X, 31 * _2X,	//21

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg17.bmp
	0 * _2X, 0 * _2X, 18 * _2X, 53 * _2X,	//22
	18 * _2X, 48 * _2X, 16 * _2X, 32 * _2X,	//23
	56 * _2X, 102 * _2X, 40 * _2X, 54 * _2X,	//24
	34 * _2X, 95 * _2X, 9 * _2X, 9 * _2X,	//25
	40 * _2X, 124 * _2X, 16 * _2X, 32 * _2X,	//26
	64 * _2X, 50 * _2X, 4 * _2X, 10 * _2X,	//27
	0 * _2X, 78 * _2X, 18 * _2X, 34 * _2X,	//28
	18 * _2X, 80 * _2X, 16 * _2X, 32 * _2X,	//29
	34 * _2X, 48 * _2X, 16 * _2X, 16 * _2X,	//30
	34 * _2X, 64 * _2X, 16 * _2X, 16 * _2X,	//31
	64 * _2X, 0 * _2X, 32 * _2X, 32 * _2X,	//32
	80 * _2X, 88 * _2X, 16 * _2X, 14 * _2X,	//33
	34 * _2X, 104 * _2X, 16 * _2X, 14 * _2X,	//34
	48 * _2X, 88 * _2X, 16 * _2X, 14 * _2X,	//35
	12 * _2X, 142 * _2X, 16 * _2X, 14 * _2X,	//36
	64 * _2X, 88 * _2X, 16 * _2X, 14 * _2X,	//37
	0 * _2X, 112 * _2X, 17 * _2X, 24 * _2X,	//38
	96 * _2X, 29 * _2X, 10 * _2X, 48 * _2X,	//39

	//BMP : C:\sktwipi\Projects\Mos5\Resource\bg18.bmp
	48 * _2X, 0 * _2X, 14 * _2X, 42 * _2X,	//40
	20 * _2X, 144 * _2X, 28 * _2X, 34 * _2X,	//41
};

const unsigned short bgObjOff[TOTALBGOBJOFF * 4] = {
	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg0.bmp
	0 * _2X, 193 * _2X, 16 * _2X, 10 * _2X,	//0
	243 * _2X, 139 * _2X, 16 * _2X, 44 * _2X,	//1
	56 * _2X, 148 * _2X, 16 * _2X, 10 * _2X,	//2
	58 * _2X, 138 * _2X, 16 * _2X, 10 * _2X,	//3
	126 * _2X, 128 * _2X, 10 * _2X, 13 * _2X,	//4
	17 * _2X, 179 * _2X, 13 * _2X, 9 * _2X,	//5
	17 * _2X, 188 * _2X, 18 * _2X, 2 * _2X,	//6
	72 * _2X, 148 * _2X, 5 * _2X, 3 * _2X,	//7
	72 * _2X, 151 * _2X, 5 * _2X, 4 * _2X,	//8
	22 * _2X, 144 * _2X, 24 * _2X, 7 * _2X,	//9
	247 * _2X, 183 * _2X, 12 * _2X, 4 * _2X,	//10
	0 * _2X, 161 * _2X, 12 * _2X, 5 * _2X,	//11
	94 * _2X, 138 * _2X, 19 * _2X, 18 * _2X,	//12
	17 * _2X, 161 * _2X, 15 * _2X, 18 * _2X,	//13
	7 * _2X, 121 * _2X, 9 * _2X, 17 * _2X,	//14
	16 * _2X, 121 * _2X, 3 * _2X, 17 * _2X,	//15
	98 * _2X, 128 * _2X, 28 * _2X, 9 * _2X,	//16
	76 * _2X, 172 * _2X, 24 * _2X, 11 * _2X,	//17
	169 * _2X, 88 * _2X, 17 * _2X, 13 * _2X,	//18
	37 * _2X, 170 * _2X, 6 * _2X, 15 * _2X,	//19
	113 * _2X, 137 * _2X, 14 * _2X, 20 * _2X,	//20
	43 * _2X, 169 * _2X, 8 * _2X, 12 * _2X,	//21
	79 * _2X, 148 * _2X, 6 * _2X, 5 * _2X,	//22
	71 * _2X, 158 * _2X, 3 * _2X, 3 * _2X,	//23

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg2.bmp
	90 * _2X, 145 * _2X, 80 * _2X, 16 * _2X,	//24
	0 * _2X, 150 * _2X, 32 * _2X, 6 * _2X,	//25
	32 * _2X, 150 * _2X, 26 * _2X, 4 * _2X,	//26

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg3.bmp
	107 * _2X, 74 * _2X, 16 * _2X, 23 * _2X,	//27
	107 * _2X, 97 * _2X, 16 * _2X, 23 * _2X,	//28
	47 * _2X, 74 * _2X, 15 * _2X, 23 * _2X,	//29
	0 * _2X, 74 * _2X, 16 * _2X, 22 * _2X,	//30
	107 * _2X, 32 * _2X, 16 * _2X, 21 * _2X,	//31
	107 * _2X, 53 * _2X, 16 * _2X, 21 * _2X,	//32
	33 * _2X, 74 * _2X, 14 * _2X, 20 * _2X,	//33
	16 * _2X, 74 * _2X, 14 * _2X, 20 * _2X,	//34
	62 * _2X, 64 * _2X, 13 * _2X, 23 * _2X,	//35
	61 * _2X, 97 * _2X, 4 * _2X, 4 * _2X,	//36
	57 * _2X, 97 * _2X, 4 * _2X, 4 * _2X,	//37
	53 * _2X, 97 * _2X, 4 * _2X, 3 * _2X,	//38
	52 * _2X, 97 * _2X, 1 * _2X, 1 * _2X,	//39

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg4.bmp
	0 * _2X, 24 * _2X, 32 * _2X, 12 * _2X,	//40
	32 * _2X, 25 * _2X, 30 * _2X, 12 * _2X,	//41
	0 * _2X, 36 * _2X, 34 * _2X, 14 * _2X,	//42
	33 * _2X, 48 * _2X, 28 * _2X, 8 * _2X,	//43
	0 * _2X, 75 * _2X, 13 * _2X, 7 * _2X,	//44
	13 * _2X, 75 * _2X, 9 * _2X, 8 * _2X,	//45
	22 * _2X, 75 * _2X, 12 * _2X, 8 * _2X,	//46
	34 * _2X, 76 * _2X, 9 * _2X, 7 * _2X,	//47
	34 * _2X, 37 * _2X, 4 * _2X, 4 * _2X,	//48
	89 * _2X, 73 * _2X, 16 * _2X, 6 * _2X,	//49
	42 * _2X, 37 * _2X, 12 * _2X, 4 * _2X,	//50
	45 * _2X, 56 * _2X, 12 * _2X, 13 * _2X,	//51
	62 * _2X, 25 * _2X, 9 * _2X, 31 * _2X,	//52
	57 * _2X, 56 * _2X, 8 * _2X, 25 * _2X,	//53
	0 * _2X, 57 * _2X, 25 * _2X, 18 * _2X,	//54

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg5.bmp
	86 * _2X, 0 * _2X, 22 * _2X, 7 * _2X,	//55
	86 * _2X, 7 * _2X, 22 * _2X, 7 * _2X,	//56
	86 * _2X, 14 * _2X, 10 * _2X, 6 * _2X,	//57
	96 * _2X, 14 * _2X, 10 * _2X, 6 * _2X,	//58
	86 * _2X, 20 * _2X, 10 * _2X, 21 * _2X,	//59
	96 * _2X, 20 * _2X, 12 * _2X, 23 * _2X,	//60
	108 * _2X, 0 * _2X, 10 * _2X, 22 * _2X,	//61
	0 * _2X, 28 * _2X, 12 * _2X, 17 * _2X,	//62
	2 * _2X, 45 * _2X, 22 * _2X, 2 * _2X,	//63
	14 * _2X, 45 * _2X, 10 * _2X, 2 * _2X,	//64
	108 * _2X, 34 * _2X, 3 * _2X, 8 * _2X,	//65
	111 * _2X, 34 * _2X, 3 * _2X, 4 * _2X,	//66
	111 * _2X, 38 * _2X, 1 * _2X, 2 * _2X,	//67
	118 * _2X, 0 * _2X, 6 * _2X, 15 * _2X,	//68
	124 * _2X, 0 * _2X, 7 * _2X, 15 * _2X,	//69
	14 * _2X, 28 * _2X, 7 * _2X, 15 * _2X,	//70
	126 * _2X, 29 * _2X, 8 * _2X, 15 * _2X,	//71
	21 * _2X, 28 * _2X, 8 * _2X, 15 * _2X,	//72
	134 * _2X, 29 * _2X, 9 * _2X, 15 * _2X,	//73
	29 * _2X, 28 * _2X, 9 * _2X, 15 * _2X,	//74
	131 * _2X, 15 * _2X, 11 * _2X, 14 * _2X,	//75
	114 * _2X, 29 * _2X, 12 * _2X, 14 * _2X,	//76
	131 * _2X, 0 * _2X, 12 * _2X, 14 * _2X,	//77
	118 * _2X, 15 * _2X, 13 * _2X, 14 * _2X,	//78

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg7.bmp
	47 * _2X, 0 * _2X, 9 * _2X, 10 * _2X,	//79
	56 * _2X, 47 * _2X, 9 * _2X, 7 * _2X,	//80
	54 * _2X, 85 * _2X, 10 * _2X, 11 * _2X,	//81

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg9.bmp
	99 * _2X, 0 * _2X, 20 * _2X, 36 * _2X,	//82
	26 * _2X, 0 * _2X, 26 * _2X, 14 * _2X,	//83
	26 * _2X, 14 * _2X, 26 * _2X, 14 * _2X,	//84
	26 * _2X, 28 * _2X, 26 * _2X, 14 * _2X,	//85
	52 * _2X, 36 * _2X, 4 * _2X, 4 * _2X,	//86
	56 * _2X, 36 * _2X, 3 * _2X, 3 * _2X,	//87
	0 * _2X, 16 * _2X, 26 * _2X, 14 * _2X,	//88
	0 * _2X, 30 * _2X, 26 * _2X, 12 * _2X,	//89
	84 * _2X, 0 * _2X, 12 * _2X, 7 * _2X,	//90
	52 * _2X, 19 * _2X, 9 * _2X, 17 * _2X,	//91
	84 * _2X, 7 * _2X, 7 * _2X, 7 * _2X,	//92
	91 * _2X, 7 * _2X, 6 * _2X, 9 * _2X,	//93

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg11.bmp
	18 * _2X, 11 * _2X, 13 * _2X, 12 * _2X,	//94
	39 * _2X, 25 * _2X, 7 * _2X, 15 * _2X,	//95
	23 * _2X, 26 * _2X, 5 * _2X, 5 * _2X,	//96
	56 * _2X, 0 * _2X, 8 * _2X, 21 * _2X,	//97
	33 * _2X, 11 * _2X, 3 * _2X, 10 * _2X,	//98
	36 * _2X, 0 * _2X, 5 * _2X, 20 * _2X,	//99
	58 * _2X, 27 * _2X, 5 * _2X, 41 * _2X,	//100
	59 * _2X, 21 * _2X, 5 * _2X, 5 * _2X,	//101

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg12.bmp
	34 * _2X, 74 * _2X, 6 * _2X, 16 * _2X,	//102
	40 * _2X, 74 * _2X, 7 * _2X, 16 * _2X,	//103
	47 * _2X, 74 * _2X, 9 * _2X, 16 * _2X,	//104
	14 * _2X, 68 * _2X, 11 * _2X, 5 * _2X,	//105
	27 * _2X, 66 * _2X, 11 * _2X, 7 * _2X,	//106
	0 * _2X, 55 * _2X, 13 * _2X, 9 * _2X,	//107
	0 * _2X, 64 * _2X, 14 * _2X, 9 * _2X,	//108

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg13.bmp
	78 * _2X, 81 * _2X, 32 * _2X, 32 * _2X,	//109
	0 * _2X, 0 * _2X, 24 * _2X, 30 * _2X,	//110
	0 * _2X, 69 * _2X, 14 * _2X, 10 * _2X,	//111
	10 * _2X, 82 * _2X, 6 * _2X, 11 * _2X,	//112
	0 * _2X, 79 * _2X, 7 * _2X, 4 * _2X,	//113
	0 * _2X, 30 * _2X, 24 * _2X, 21 * _2X,	//114
	24 * _2X, 0 * _2X, 86 * _2X, 27 * _2X,	//115
	14 * _2X, 55 * _2X, 42 * _2X, 8 * _2X,	//116
	0 * _2X, 51 * _2X, 24 * _2X, 4 * _2X,	//117
	0 * _2X, 55 * _2X, 12 * _2X, 14 * _2X,	//118
	14 * _2X, 63 * _2X, 13 * _2X, 14 * _2X,	//119
	31 * _2X, 63 * _2X, 12 * _2X, 12 * _2X,	//120
	43 * _2X, 63 * _2X, 13 * _2X, 12 * _2X,	//121

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg14.bmp
	44 * _2X, 0 * _2X, 12 * _2X, 25 * _2X,	//122
	32 * _2X, 71 * _2X, 9 * _2X, 44 * _2X,	//123
	34 * _2X, 29 * _2X, 6 * _2X, 26 * _2X,	//124
	40 * _2X, 29 * _2X, 5 * _2X, 24 * _2X,	//125
	45 * _2X, 25 * _2X, 11 * _2X, 30 * _2X,	//126
	0 * _2X, 159 * _2X, 17 * _2X, 48 * _2X,	//127
	33 * _2X, 171 * _2X, 22 * _2X, 7 * _2X,	//128
	33 * _2X, 178 * _2X, 22 * _2X, 7 * _2X,	//129
	23 * _2X, 164 * _2X, 10 * _2X, 21 * _2X,	//130
	41 * _2X, 70 * _2X, 12 * _2X, 23 * _2X,	//131
	41 * _2X, 93 * _2X, 10 * _2X, 22 * _2X,	//132
	43 * _2X, 190 * _2X, 12 * _2X, 17 * _2X,	//133
	36 * _2X, 67 * _2X, 20 * _2X, 2 * _2X,	//134

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg15.bmp
	32 * _2X, 36 * _2X, 28 * _2X, 10 * _2X,	//135
	32 * _2X, 46 * _2X, 23 * _2X, 13 * _2X,	//136
	32 * _2X, 59 * _2X, 26 * _2X, 11 * _2X,	//137

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg16.bmp
	48 * _2X, 87 * _2X, 80 * _2X, 16 * _2X,	//138
	70 * _2X, 81 * _2X, 32 * _2X, 6 * _2X,	//139
	102 * _2X, 81 * _2X, 26 * _2X, 4 * _2X,	//140
	70 * _2X, 0 * _2X, 66 * _2X, 20 * _2X,	//141
	48 * _2X, 72 * _2X, 33 * _2X, 10 * _2X,	//142
	42 * _2X, 42 * _2X, 9 * _2X, 12 * _2X,	//143
	70 * _2X, 36 * _2X, 7 * _2X, 10 * _2X,	//144

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg17.bmp
	18 * _2X, 0 * _2X, 14 * _2X, 26 * _2X,	//145
	18 * _2X, 26 * _2X, 14 * _2X, 22 * _2X,	//146
	0 * _2X, 136 * _2X, 12 * _2X, 19 * _2X,	//147
	50 * _2X, 48 * _2X, 14 * _2X, 19 * _2X,	//148
	72 * _2X, 64 * _2X, 24 * _2X, 24 * _2X,	//149
	0 * _2X, 53 * _2X, 18 * _2X, 25 * _2X,	//150
	34 * _2X, 80 * _2X, 15 * _2X, 15 * _2X,	//151
	64 * _2X, 32 * _2X, 7 * _2X, 9 * _2X,	//152
	64 * _2X, 41 * _2X, 7 * _2X, 9 * _2X,	//153
	28 * _2X, 136 * _2X, 10 * _2X, 20 * _2X,	//154

	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg18.bmp
	0 * _2X, 162 * _2X, 20 * _2X, 20 * _2X,	//155
	48 * _2X, 42 * _2X, 12 * _2X, 13 * _2X,	//156
	48 * _2X, 61 * _2X, 10 * _2X, 10 * _2X,	//157
	48 * _2X, 55 * _2X, 6 * _2X, 6 * _2X,	//158
	48 * _2X, 71 * _2X, 9 * _2X, 9 * _2X,	//159
	48 * _2X, 80 * _2X, 10 * _2X, 11 * _2X,	//160
	0 * _2X, 182 * _2X, 18 * _2X, 20 * _2X,	//161
	18 * _2X, 178 * _2X, 12 * _2X, 16 * _2X,	//162
	18 * _2X, 194 * _2X, 7 * _2X, 8 * _2X,	//163
};

const signed short bgObjMI[805 * 4] = {
	//BG0_WATER0
	IMG_BE_6, -9 * _2X, -1 * _2X, N00T0X1,	//0
	IMG_BE_4, -5 * _2X, 1 * _2X, N00T1X1,	//1
	IMG_BE_7, -7 * _2X, 17 * _2X, N00T0X1,	//2
	IMG_BE_7, 2 * _2X, 17 * _2X, F00T0X1,	//3
	IMG_BE_8, -10 * _2X, 18 * _2X, N00T0X1,	//4
	IMG_BE_8, 5 * _2X, 18 * _2X, F00T0X1,	//5
	IMG_BE_7, 7 * _2X, 41 * _2X, N00T0X1,	//6
	IMG_BE_7, 18 * _2X, 41 * _2X, F00T0X1,	//7
	IMG_BE_8, 4 * _2X, 42 * _2X, N00T0X1,	//8
	IMG_BE_8, 21 * _2X, 42 * _2X, F00T0X1,	//9
	IMG_BE_8, -26 * _2X, 42 * _2X, N00T0X1,	//10
	IMG_BE_7, -23 * _2X, 41 * _2X, N00T0X1,	//11
	IMG_BE_8, -9 * _2X, 42 * _2X, F00T0X1,	//12
	IMG_BE_7, -12 * _2X, 41 * _2X, F00T0X1,	//13
	IMG_BE_2, -8 * _2X, -63 * _2X, N00T0X1,	//14
	IMG_BE_3, -8 * _2X, -47 * _2X, N00T1X1,	//15
	IMG_BE_9, -43 * _2X, -21 * _2X, N00T3X1,	//16
	IMG_BE_9, 19 * _2X, -21 * _2X, F00T3X1,	//17
	IMG_BE_5, -21 * _2X, 30 * _2X, N00T0X1,	//18
	IMG_BE_5, 8 * _2X, 30 * _2X, F00T0X1,	//19

	//BG0_WATER1
	IMG_BE_6, -9 * _2X, 0 * _2X, N00T0X1,	//20
	IMG_BE_4, -5 * _2X, 4 * _2X, F00T0X1,	//21
	IMG_BE_7, -6 * _2X, 18 * _2X, N00T1X1,	//22
	IMG_BE_7, 1 * _2X, 18 * _2X, F00T1X1,	//23
	IMG_BE_8, -9 * _2X, 19 * _2X, N00T1X1,	//24
	IMG_BE_8, 4 * _2X, 19 * _2X, F00T1X1,	//25
	IMG_BE_7, 8 * _2X, 41 * _2X, N00T1X1,	//26
	IMG_BE_7, 17 * _2X, 41 * _2X, F00T1X1,	//27
	IMG_BE_8, 5 * _2X, 42 * _2X, N00T1X1,	//28
	IMG_BE_8, 20 * _2X, 42 * _2X, F00T1X1,	//29
	IMG_BE_8, -25 * _2X, 42 * _2X, N00T1X1,	//30
	IMG_BE_7, -22 * _2X, 41 * _2X, N00T1X1,	//31
	IMG_BE_8, -10 * _2X, 42 * _2X, F00T1X1,	//32
	IMG_BE_7, -13 * _2X, 41 * _2X, F00T1X1,	//33
	IMG_BE_3, -8 * _2X, -71 * _2X, N00T2X1,	//34
	IMG_BE_2, -8 * _2X, -55 * _2X, N00T1X1,	//35
	IMG_BE_3, -8 * _2X, -39 * _2X, N00T2X1,	//36
	IMG_BE_9, -43 * _2X, -18 * _2X, F00T2X1,	//37
	IMG_BE_9, 19 * _2X, -18 * _2X, N00T2X1,	//38
	IMG_BE_5, -21 * _2X, 32 * _2X, F00T1X1,	//39
	IMG_BE_5, 8 * _2X, 32 * _2X, N00T1X1,	//40

	//BG0_WATER2
	IMG_BE_6, -9 * _2X, -1 * _2X, N00T0X1,	//41
	IMG_BE_4, -5 * _2X, 8 * _2X, F00T1X1,	//42
	IMG_BE_7, -7 * _2X, 18 * _2X, N00T0X1,	//43
	IMG_BE_7, 2 * _2X, 18 * _2X, F00T0X1,	//44
	IMG_BE_8, -10 * _2X, 19 * _2X, N00T0X1,	//45
	IMG_BE_8, 5 * _2X, 19 * _2X, F00T0X1,	//46
	IMG_BE_7, 7 * _2X, 42 * _2X, N00T0X1,	//47
	IMG_BE_7, 18 * _2X, 42 * _2X, F00T0X1,	//48
	IMG_BE_8, 4 * _2X, 43 * _2X, N00T0X1,	//49
	IMG_BE_8, 21 * _2X, 43 * _2X, F00T0X1,	//50
	IMG_BE_8, -26 * _2X, 43 * _2X, N00T0X1,	//51
	IMG_BE_7, -23 * _2X, 42 * _2X, N00T0X1,	//52
	IMG_BE_8, -9 * _2X, 43 * _2X, F00T0X1,	//53
	IMG_BE_7, -12 * _2X, 42 * _2X, F00T0X1,	//54
	IMG_BE_2, -8 * _2X, -36 * _2X, N00T1X1,	//55
	IMG_BE_3, -8 * _2X, -52 * _2X, N00T0X1,	//56
	IMG_BE_5, -21 * _2X, 34 * _2X, N00T2X1,	//57
	IMG_BE_5, 8 * _2X, 34 * _2X, F00T2X1,	//58

	//BG0_WATER3
	IMG_BE_6, -9 * _2X, -1 * _2X, N00T0X1,	//59
	IMG_BE_4, -5 * _2X, 2 * _2X, F00T2X1,	//60
	IMG_BE_7, -6 * _2X, 18 * _2X, N00T1X1,	//61
	IMG_BE_7, 1 * _2X, 18 * _2X, F00T1X1,	//62
	IMG_BE_8, -9 * _2X, 19 * _2X, N00T1X1,	//63
	IMG_BE_8, 4 * _2X, 19 * _2X, F00T1X1,	//64
	IMG_BE_7, 9 * _2X, 42 * _2X, N00T1X1,	//65
	IMG_BE_7, 16 * _2X, 42 * _2X, F00T1X1,	//66
	IMG_BE_8, 3 * _2X, 44 * _2X, N00T1X1,	//67
	IMG_BE_8, 22 * _2X, 44 * _2X, F00T1X1,	//68
	IMG_BE_8, -27 * _2X, 44 * _2X, N00T1X1,	//69
	IMG_BE_7, -21 * _2X, 42 * _2X, N00T1X1,	//70
	IMG_BE_8, -8 * _2X, 44 * _2X, F00T1X1,	//71
	IMG_BE_7, -14 * _2X, 42 * _2X, F00T1X1,	//72
	IMG_BE_3, -8 * _2X, -36 * _2X, N00T2X1,	//73
	IMG_BE_2, -8 * _2X, -71 * _2X, N00T1X1,	//74
	IMG_BE_9, -43 * _2X, -21 * _2X, F00T3X1,	//75
	IMG_BE_9, 19 * _2X, -21 * _2X, N00T3X1,	//76
	IMG_BE_5, -21 * _2X, 32 * _2X, F00T1X1,	//77
	IMG_BE_5, 8 * _2X, 32 * _2X, N00T1X1,	//78

	//BG0_WATER4
	IMG_BE_6, -9 * _2X, 0 * _2X, N00T0X1,	//79
	IMG_BE_4, -5 * _2X, 11 * _2X, F00T1X1,	//80
	IMG_BE_7, -6 * _2X, 17 * _2X, N00T0X1,	//81
	IMG_BE_7, 1 * _2X, 17 * _2X, F00T0X1,	//82
	IMG_BE_8, -9 * _2X, 18 * _2X, N00T0X1,	//83
	IMG_BE_8, 4 * _2X, 18 * _2X, F00T0X1,	//84
	IMG_BE_7, 8 * _2X, 41 * _2X, N00T0X1,	//85
	IMG_BE_7, 17 * _2X, 41 * _2X, F00T0X1,	//86
	IMG_BE_8, 5 * _2X, 42 * _2X, N00T0X1,	//87
	IMG_BE_8, 20 * _2X, 42 * _2X, F00T0X1,	//88
	IMG_BE_8, -25 * _2X, 42 * _2X, N00T0X1,	//89
	IMG_BE_7, -22 * _2X, 41 * _2X, N00T0X1,	//90
	IMG_BE_8, -10 * _2X, 42 * _2X, F00T0X1,	//91
	IMG_BE_7, -13 * _2X, 41 * _2X, F00T0X1,	//92
	IMG_BE_2, -8 * _2X, -36 * _2X, N00T1X1,	//93
	IMG_BE_3, -8 * _2X, -52 * _2X, N00T0X1,	//94
	IMG_BE_5, -21 * _2X, 34 * _2X, N00T2X1,	//95
	IMG_BE_5, 8 * _2X, 34 * _2X, F00T2X1,	//96
	IMG_BE_9, -43 * _2X, -18 * _2X, N00T2X1,	//97
	IMG_BE_9, 19 * _2X, -18 * _2X, F00T2X1,	//98

	//BG0_WATER_SIDE0
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T3X1,	//99
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T3X1,	//100
	IMG_BE_2, -40 * _2X, -53 * _2X, N00T3X1,	//101
	IMG_BE_3, -40 * _2X, -37 * _2X, N00T3X1,	//102

	//BG0_WATER_SIDE1
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T2X1,	//103
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T2X1,	//104
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T2X1,	//105
	IMG_BE_3, -40 * _2X, -61 * _2X, N00T2X1,	//106
	IMG_BE_2, -40 * _2X, -45 * _2X, N00T2X1,	//107
	IMG_BE_3, -40 * _2X, -29 * _2X, N00T2X1,	//108
	IMG_BE_3, -40 * _2X, -7 * _2X, N00T2X1,	//109
	IMG_BE_2, -40 * _2X, 9 * _2X, N00T2X1,	//110
	IMG_BE_10, -34 * _2X, 26 * _2X, N00T1X1,	//111

	//BG0_WATER_SIDE2
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T1X1,	//112
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T1X1,	//113
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T1X1,	//114
	IMG_BE_3, -40 * _2X, -61 * _2X, N00T1X1,	//115
	IMG_BE_2, -40 * _2X, -45 * _2X, N00T1X1,	//116
	IMG_BE_3, -40 * _2X, -8 * _2X, N00T1X1,	//117
	IMG_BE_2, -40 * _2X, 8 * _2X, N00T1X1,	//118
	IMG_BE_11, -34 * _2X, 25 * _2X, N00T0X1,	//119

	//BG0_WATER_SIDE3
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T0X1,	//120
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T0X1,	//121
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T0X1,	//122
	IMG_BE_3, -40 * _2X, -42 * _2X, N00T0X1,	//123
	IMG_BE_2, -40 * _2X, -26 * _2X, N00T0X1,	//124
	IMG_BE_3, -40 * _2X, 12 * _2X, N00T0X1,	//125
	IMG_BE_10, -34 * _2X, 25 * _2X, N00T0X1,	//126

	//BG0_WATER_SIDE4
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T0X1,	//127
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T0X1,	//128
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T0X1,	//129
	IMG_BE_2, -40 * _2X, -53 * _2X, N00T0X1,	//130
	IMG_BE_3, -40 * _2X, -37 * _2X, N00T1X1,	//131
	IMG_BE_2, -40 * _2X, 1 * _2X, N00T0X1,	//132
	IMG_BE_3, -40 * _2X, 17 * _2X, N00T1X1,	//133

	//BG0_WATER_SIDE5
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T0X1,	//134
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T0X1,	//135
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T0X1,	//136
	IMG_BE_2, -40 * _2X, -45 * _2X, N00T1X1,	//137
	IMG_BE_3, -40 * _2X, -61 * _2X, N00T2X1,	//138
	IMG_BE_2, -40 * _2X, 9 * _2X, N00T1X1,	//139
	IMG_BE_3, -40 * _2X, -7 * _2X, N00T2X1,	//140
	IMG_BE_3, -40 * _2X, -29 * _2X, N00T2X1,	//141
	IMG_BE_10, -34 * _2X, 26 * _2X, N00T1X1,	//142

	//BG0_WATER_SIDE6
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T0X1,	//143
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T0X1,	//144
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T0X1,	//145
	IMG_BE_2, -40 * _2X, -26 * _2X, N00T1X1,	//146
	IMG_BE_3, -40 * _2X, -42 * _2X, N00T1X1,	//147
	IMG_BE_3, -40 * _2X, 12 * _2X, N00T0X1,	//148
	IMG_BE_11, -34 * _2X, 25 * _2X, N00T0X1,	//149

	//BG0_WATER_SIDE7
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T0X1,	//150
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T0X1,	//151
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T0X1,	//152
	IMG_BE_2, -40 * _2X, -45 * _2X, N00T1X1,	//153
	IMG_BE_3, -40 * _2X, -61 * _2X, N00T2X1,	//154
	IMG_BE_2, -40 * _2X, 8 * _2X, N00T1X1,	//155
	IMG_BE_3, -40 * _2X, -8 * _2X, N00T2X1,	//156
	IMG_BE_10, -34 * _2X, 26 * _2X, N00T1X1,	//157

	//BG0_WATER_SIDE8
	IMG_BE_0, -40 * _2X, -70 * _2X, N00T0X1,	//158
	IMG_BE_1, -40 * _2X, -60 * _2X, N00T0X1,	//159
	IMG_BE_1, -40 * _2X, -16 * _2X, N00T0X1,	//160
	IMG_BE_2, -40 * _2X, -45 * _2X, N00T0X1,	//161
	IMG_BE_3, -40 * _2X, -29 * _2X, N00T1X1,	//162
	IMG_BE_2, -40 * _2X, 9 * _2X, N00T0X1,	//163
	IMG_BE_11, -34 * _2X, 25 * _2X, N00T1X1,	//164

	//BG0_WINDMETER0
	IMG_BE_19, 1 * _2X, -10 * _2X, F00T0X1,	//165
	IMG_BE_15, 1 * _2X, -25 * _2X, N00T0X1,	//166

	//BG0_WINDMETER1
	IMG_BE_18, -5 * _2X, -9 * _2X, F00T0X1,	//167
	IMG_BE_14, -1 * _2X, -25 * _2X, N00T0X1,	//168

	//BG0_WINDMETER2
	IMG_BE_17, -8 * _2X, -8 * _2X, F00T0X1,	//169
	IMG_BE_13, -3 * _2X, -25 * _2X, N00T0X1,	//170

	//BG0_WINDMETER3
	IMG_BE_12, -5 * _2X, -25 * _2X, N00T0X1,	//171
	IMG_BE_16, -11 * _2X, -8 * _2X, N00T0X1,	//172

	//BG0_WINDMETER4
	IMG_BE_17, -9 * _2X, -8 * _2X, N00T0X1,	//173
	IMG_BE_13, -3 * _2X, -25 * _2X, N00T0X1,	//174

	//BG0_WINDMETER5
	IMG_BE_18, -5 * _2X, -9 * _2X, N00T0X1,	//175
	IMG_BE_14, -1 * _2X, -25 * _2X, N00T0X1,	//176

	//BG0_WINDMETER6
	IMG_BE_19, 0 * _2X, -10 * _2X, N00T0X1,	//177
	IMG_BE_15, 1 * _2X, -25 * _2X, N00T0X1,	//178

	//BG0_SMOKE0
	IMG_BE_20, 3 * _2X, -7 * _2X, N00T3X1,	//179

	//BG0_SMOKE1
	IMG_BE_20, 5 * _2X, -15 * _2X, N00T2X1,	//180

	//BG0_SMOKE2
	IMG_BE_20, 4 * _2X, -20 * _2X, N00T1X1,	//181
	IMG_BE_21, 6 * _2X, -6 * _2X, N00T0X1,	//182

	//BG0_SMOKE3
	IMG_BE_20, 3 * _2X, -29 * _2X, N00T0X1,	//183
	IMG_BE_21, 4 * _2X, -10 * _2X, N00T2X1,	//184
	IMG_BE_21, 10 * _2X, -15 * _2X, N00T1X1,	//185

	//BG0_SMOKE4
	IMG_BE_20, 3 * _2X, -31 * _2X, N00T1X1,	//186
	IMG_BE_21, 4 * _2X, -12 * _2X, N00T1X1,	//187
	IMG_BE_21, 10 * _2X, -20 * _2X, N00T0X1,	//188
	IMG_BE_22, 8 * _2X, -5 * _2X, N00T0X1,	//189

	//BG0_SMOKE5
	IMG_BE_20, 3 * _2X, -34 * _2X, N00T0X1,	//190
	IMG_BE_21, 6 * _2X, -12 * _2X, N00T2X1,	//191
	IMG_BE_21, 12 * _2X, -39 * _2X, N00T1X1,	//192
	IMG_BE_23, 9 * _2X, -50 * _2X, N00T3X1,	//193
	IMG_BE_22, 8 * _2X, -45 * _2X, N00T2X1,	//194

	//BG0_SMOKE6
	IMG_BE_21, 12 * _2X, -49 * _2X, N00T2X1,	//195
	IMG_BE_21, 5 * _2X, -32 * _2X, N00T1X1,	//196
	IMG_BE_21, 8 * _2X, -24 * _2X, N00T3X1,	//197
	IMG_BE_22, 8 * _2X, -54 * _2X, N00T3X1,	//198

	//BG0_SMOKE7
	IMG_BE_20, 1 * _2X, -52 * _2X, N00T3X1,	//199
	IMG_BE_21, 8 * _2X, -31 * _2X, N00T3X1,	//200
	IMG_BE_21, 12 * _2X, -59 * _2X, N00T3X1,	//201

	//BG2_MIST0
	IMG_BE_24, 0 * _2X, 0 * _2X, N00E2X2,	//202
	IMG_BE_25, 10 * _2X, 34 * _2X, N00E2X2,	//203
	IMG_BE_26, 96 * _2X, 34 * _2X, N00E2X2,	//204

	//BG2_MIST1
	IMG_BE_24, 0 * _2X, 0 * _2X, N00E2X2,	//205
	IMG_BE_25, 30 * _2X, 28 * _2X, N00E2X2,	//206
	IMG_BE_26, 120 * _2X, 28 * _2X, N00E2X2,	//207

	//BG3_REED0
	IMG_BE_27, 0 * _2X, -23 * _2X, N00T0X1,	//208
	IMG_BE_30, 16 * _2X, -22 * _2X, N00T0X1,	//209
	IMG_BE_33, 32 * _2X, -20 * _2X, N00T0X1,	//210

	//BG3_REED1
	IMG_BE_28, 0 * _2X, -23 * _2X, N00T1X1,	//211
	IMG_BE_31, 16 * _2X, -21 * _2X, N00T1X1,	//212
	IMG_BE_34, 32 * _2X, -20 * _2X, N00T1X1,	//213

	//BG3_REED2
	IMG_BE_29, 1 * _2X, -23 * _2X, N00T1X1,	//214
	IMG_BE_32, 16 * _2X, -21 * _2X, N00T1X1,	//215
	IMG_BE_35, 32 * _2X, -22 * _2X, N00T1X1,	//216

	//BG3_REED3
	IMG_BE_27, 0 * _2X, -23 * _2X, N00T0X1,	//217
	IMG_BE_33, 16 * _2X, -20 * _2X, N00T0X1,	//218

	//BG3_REED4
	IMG_BE_28, 0 * _2X, -23 * _2X, N00T0X1,	//219
	IMG_BE_34, 16 * _2X, -20 * _2X, N00T0X1,	//220

	//BG3_REED5
	IMG_BE_29, 0 * _2X, -23 * _2X, N00T1X1,	//221
	IMG_BE_35, 15 * _2X, -22 * _2X, N00T1X1,	//222

	//BG3_REED_SEED0
	IMG_BE_38, 20 * _2X, -26 * _2X, N00T2X1,	//223

	//BG3_REED_SEED1
	IMG_BE_37, 27 * _2X, -28 * _2X, N00T1X1,	//224
	IMG_BE_39, 23 * _2X, -23 * _2X, N00T1X1,	//225

	//BG3_REED_SEED2
	IMG_BE_38, 25 * _2X, -30 * _2X, N00T1X1,	//226
	IMG_BE_39, 31 * _2X, -26 * _2X, N00T1X1,	//227
	IMG_BE_37, 36 * _2X, -26 * _2X, N00T1X1,	//228
	IMG_BE_39, 44 * _2X, -22 * _2X, N00T1X1,	//229

	//BG3_REED_SEED3
	IMG_BE_38, 31 * _2X, -27 * _2X, N00T0X1,	//230
	IMG_BE_39, 40 * _2X, -23 * _2X, N00T0X1,	//231
	IMG_BE_36, 46 * _2X, -28 * _2X, N00T0X1,	//232
	IMG_BE_39, 54 * _2X, -20 * _2X, N00T0X1,	//233

	//BG3_REED_SEED4
	IMG_BE_37, 33 * _2X, -28 * _2X, N00T2X1,	//234
	IMG_BE_39, 30 * _2X, -20 * _2X, N00T1X1,	//235
	IMG_BE_39, 42 * _2X, -23 * _2X, N00T1X1,	//236
	IMG_BE_38, 53 * _2X, -26 * _2X, N00T2X1,	//237
	IMG_BE_39, 60 * _2X, -30 * _2X, N00T1X1,	//238

	//BG3_REED_SEED5
	IMG_BE_39, 36 * _2X, -18 * _2X, N00T3X1,	//239
	IMG_BE_38, 48 * _2X, -23 * _2X, N00T3X1,	//240
	IMG_BE_39, 55 * _2X, -18 * _2X, N00T3X1,	//241
	IMG_BE_37, 59 * _2X, -30 * _2X, N00T3X1,	//242
	IMG_BE_39, 68 * _2X, -36 * _2X, N00T3X1,	//243

	//BG4_AQUA0
	IMG_BE_41, -14 * _2X, -63 * _2X, N00T1X1,	//244
	IMG_BE_46, -17 * _2X, -46 * _2X, N00T0X1,	//245
	IMG_BE_44, -33 * _2X, -39 * _2X, N00T0X1,	//246
	IMG_BE_47, -40 * _2X, -59 * _2X, N00T0X1,	//247
	IMG_BE_47, 31 * _2X, -59 * _2X, F00T0X1,	//248
	IMG_BE_46, 5 * _2X, -46 * _2X, F00T0X1,	//249
	IMG_BE_44, 21 * _2X, -39 * _2X, F00T0X1,	//250
	IMG_BE_45, -19 * _2X, -11 * _2X, N00T1X1,	//251
	IMG_BE_48, -6 * _2X, -8 * _2X, N00T1X1,	//252
	IMG_BE_47, -61 * _2X, -2 * _2X, N00T3X1,	//253
	IMG_BE_46, -38 * _2X, 11 * _2X, N00T3X1,	//254
	IMG_BE_44, -54 * _2X, 18 * _2X, N00T3X1,	//255
	IMG_BE_46, 26 * _2X, 11 * _2X, F00T3X1,	//256
	IMG_BE_44, 41 * _2X, 18 * _2X, F00T3X1,	//257
	IMG_BE_47, 52 * _2X, -2 * _2X, F00T3X1,	//258

	//BG4_AQUA1
	IMG_BE_46, -18 * _2X, -46 * _2X, N00T1X1,	//259
	IMG_BE_44, -33 * _2X, -40 * _2X, N00T1X1,	//260
	IMG_BE_47, -39 * _2X, -59 * _2X, N00T1X1,	//261
	IMG_BE_47, 30 * _2X, -59 * _2X, F00T1X1,	//262
	IMG_BE_46, 6 * _2X, -46 * _2X, F00T1X1,	//263
	IMG_BE_44, 21 * _2X, -40 * _2X, F00T1X1,	//264
	IMG_BE_45, -19 * _2X, -11 * _2X, N00T2X1,	//265
	IMG_BE_48, -6 * _2X, -8 * _2X, N00T2X1,	//266
	IMG_BE_47, -61 * _2X, 0 * _2X, N00T3X1,	//267
	IMG_BE_46, -40 * _2X, 13 * _2X, N00T3X1,	//268
	IMG_BE_44, -55 * _2X, 19 * _2X, N00T3X1,	//269
	IMG_BE_46, 28 * _2X, 13 * _2X, F00T3X1,	//270
	IMG_BE_44, 42 * _2X, 19 * _2X, F00T3X1,	//271
	IMG_BE_47, 52 * _2X, 0 * _2X, F00T3X1,	//272
	IMG_BE_42, -15 * _2X, -64 * _2X, N00T0X1,	//273

	//BG4_AQUA2
	IMG_BE_46, -17 * _2X, -46 * _2X, N00T2X1,	//274
	IMG_BE_44, -33 * _2X, -39 * _2X, N00T2X1,	//275
	IMG_BE_47, -40 * _2X, -59 * _2X, N00T2X1,	//276
	IMG_BE_47, 31 * _2X, -59 * _2X, F00T2X1,	//277
	IMG_BE_46, 5 * _2X, -46 * _2X, F00T2X1,	//278
	IMG_BE_44, 21 * _2X, -39 * _2X, F00T2X1,	//279
	IMG_BE_45, -19 * _2X, -11 * _2X, N00T3X1,	//280
	IMG_BE_48, -6 * _2X, -8 * _2X, N00T3X1,	//281
	IMG_BE_47, -61 * _2X, 0 * _2X, N00T3X1,	//282
	IMG_BE_46, -38 * _2X, 13 * _2X, N00T3X1,	//283
	IMG_BE_44, -54 * _2X, 20 * _2X, N00T3X1,	//284
	IMG_BE_46, 26 * _2X, 13 * _2X, F00T3X1,	//285
	IMG_BE_44, 41 * _2X, 20 * _2X, F00T3X1,	//286
	IMG_BE_47, 52 * _2X, 0 * _2X, F00T3X1,	//287
	IMG_BE_40, -14 * _2X, -64 * _2X, N00T0X1,	//288

	//BG4_AQUA3
	IMG_BE_46, -16 * _2X, -46 * _2X, N00T1X1,	//289
	IMG_BE_44, -33 * _2X, -38 * _2X, N00T1X1,	//290
	IMG_BE_47, -41 * _2X, -59 * _2X, N00T1X1,	//291
	IMG_BE_47, 32 * _2X, -59 * _2X, F00T1X1,	//292
	IMG_BE_46, 4 * _2X, -46 * _2X, F00T1X1,	//293
	IMG_BE_44, 21 * _2X, -38 * _2X, F00T1X1,	//294
	IMG_BE_45, -19 * _2X, -11 * _2X, N00T2X1,	//295
	IMG_BE_48, -6 * _2X, -8 * _2X, N00T2X1,	//296
	IMG_BE_47, -63 * _2X, 0 * _2X, N00T3X1,	//297
	IMG_BE_46, -38 * _2X, 13 * _2X, N00T3X1,	//298
	IMG_BE_44, -55 * _2X, 21 * _2X, N00T3X1,	//299
	IMG_BE_46, 26 * _2X, 13 * _2X, F00T3X1,	//300
	IMG_BE_44, 42 * _2X, 21 * _2X, F00T3X1,	//301
	IMG_BE_47, 54 * _2X, 0 * _2X, F00T3X1,	//302
	IMG_BE_41, -11 * _2X, -63 * _2X, N00T0X1,	//303

	//BG4_FISH0
	IMG_BE_49, -16 * _2X, -13 * _2X, N00T2X1,	//304
	IMG_BE_50, 1 * _2X, -8 * _2X, N00T3X1,	//305
	IMG_BE_49, -6 * _2X, -3 * _2X, N00T2X1,	//306

	//BG4_FISH1
	IMG_BE_49, -17 * _2X, -14 * _2X, N00T2X1,	//307
	IMG_BE_50, 1 * _2X, -10 * _2X, N00T2X1,	//308
	IMG_BE_49, -7 * _2X, -4 * _2X, N00T2X1,	//309

	//BG4_FISH2
	IMG_BE_49, -20 * _2X, -13 * _2X, N00T2X1,	//310
	IMG_BE_50, -1 * _2X, -11 * _2X, N00T2X1,	//311
	IMG_BE_49, -4 * _2X, -3 * _2X, N00T2X1,	//312

	//BG4_FISH3
	IMG_BE_49, -24 * _2X, -11 * _2X, N00T2X1,	//313
	IMG_BE_49, -4 * _2X, -1 * _2X, N00T2X1,	//314
	IMG_BE_50, -6 * _2X, -7 * _2X, N00T2X1,	//315

	//BG4_FISH4
	IMG_BE_49, -16 * _2X, -10 * _2X, N00T1X1,	//316
	IMG_BE_50, 1 * _2X, -5 * _2X, N00T1X1,	//317
	IMG_BE_49, -6 * _2X, 0 * _2X, N00T1X1,	//318

	//BG4_FISH5
	IMG_BE_49, -16 * _2X, -8 * _2X, N00T2X1,	//319
	IMG_BE_50, 3 * _2X, -4 * _2X, N00T2X1,	//320
	IMG_BE_49, -10 * _2X, 2 * _2X, N00T2X1,	//321

	//BG4_FISH6
	IMG_BE_49, -16 * _2X, -9 * _2X, N00T2X1,	//322
	IMG_BE_50, 2 * _2X, -7 * _2X, N00T3X1,	//323
	IMG_BE_49, -8 * _2X, -1 * _2X, N00T2X1,	//324

	//BG4_FISH7
	IMG_BE_49, -16 * _2X, -6 * _2X, N00T2X1,	//325
	IMG_BE_50, 1 * _2X, -1 * _2X, N00T3X1,	//326

	//BG4_FISH8
	IMG_BE_49, -17 * _2X, -7 * _2X, N00T2X1,	//327
	IMG_BE_50, 1 * _2X, -3 * _2X, N00T2X1,	//328

	//BG4_FISH9
	IMG_BE_49, -18 * _2X, -6 * _2X, N00T2X1,	//329
	IMG_BE_50, 3 * _2X, -1 * _2X, N00T2X1,	//330

	//BG4_FISH10
	IMG_BE_49, -17 * _2X, -4 * _2X, N00T2X1,	//331
	IMG_BE_50, 1 * _2X, 1 * _2X, N00T2X1,	//332

	//BG4_FISH11
	IMG_BE_49, -16 * _2X, -3 * _2X, N00T1X1,	//333
	IMG_BE_50, 1 * _2X, 2 * _2X, N00T1X1,	//334

	//BG4_FISH12
	IMG_BE_49, -16 * _2X, -3 * _2X, N00T2X1,	//335
	IMG_BE_50, 2 * _2X, 1 * _2X, N00T3X1,	//336

	//BG4_FISH13
	IMG_BE_49, -16 * _2X, -2 * _2X, N00T2X1,	//337
	IMG_BE_50, 1 * _2X, 3 * _2X, N00T3X1,	//338

	//BG4_SIDE0
	IMG_BE_51, -13 * _2X, -23 * _2X, F00T0X1,	//339
	IMG_BE_54, -7 * _2X, -28 * _2X, F27T0X1,	//340
	IMG_BE_51, -12 * _2X, -11 * _2X, F00T0X1,	//341
	IMG_BE_53, 0 * _2X, -25 * _2X, F00T0X1,	//342

	//BG4_SIDE1
	IMG_BE_52, 0 * _2X, -29 * _2X, F00T1X1,	//343
	IMG_BE_51, -17 * _2X, -27 * _2X, F00T0X1,	//344
	IMG_BE_51, -16 * _2X, -8 * _2X, F09T0X1,	//345

	//BG4_SIDE2
	IMG_BE_51, 2 * _2X, -8 * _2X, N09T1X1,	//346
	IMG_BE_54, -19 * _2X, -22 * _2X, F27T0X1,	//347
	IMG_BE_51, 2 * _2X, -24 * _2X, N00T0X1,	//348

	//BG5_WATERFALL0
	IMG_BE_63, -11 * _2X, 6 * _2X, N00T0X1,	//349
	IMG_BE_55, -11 * _2X, 3 * _2X, N00T1X1,	//350

	//BG5_WATERFALL1
	IMG_BE_63, -11 * _2X, 5 * _2X, N00T0X1,	//351
	IMG_BE_56, -11 * _2X, 4 * _2X, N00T1X1,	//352

	//BG5_WATERFALL2
	IMG_BE_63, -11 * _2X, 6 * _2X, N00T0X1,	//353
	IMG_BE_55, -11 * _2X, 3 * _2X, F00T2X1,	//354

	//BG5_WATERFALL3
	IMG_BE_63, -11 * _2X, 6 * _2X, N00T0X1,	//355
	IMG_BE_56, -11 * _2X, 4 * _2X, F00T1X1,	//356

	//BG5_WATERFALL4
	IMG_BE_63, -11 * _2X, 5 * _2X, N00T0X1,	//357
	IMG_BE_55, -11 * _2X, 2 * _2X, N00T2X1,	//358

	//BG5_WATERFALL5
	IMG_BE_64, -5 * _2X, 8 * _2X, N00T0X1,	//359
	IMG_BE_57, -5 * _2X, 5 * _2X, N00T1X1,	//360

	//BG5_WATERFALL6
	IMG_BE_64, -5 * _2X, 7 * _2X, N00T0X1,	//361
	IMG_BE_58, -5 * _2X, 6 * _2X, N00T1X1,	//362

	//BG5_WATERFALL7
	IMG_BE_64, -5 * _2X, 8 * _2X, N00T0X1,	//363
	IMG_BE_57, -5 * _2X, 6 * _2X, N00T2X1,	//364

	//BG5_WATERFALL8
	IMG_BE_64, -5 * _2X, 8 * _2X, N00T0X1,	//365
	IMG_BE_58, -5 * _2X, 6 * _2X, N00T1X1,	//366

	//BG5_WATERFALL9
	IMG_BE_64, -5 * _2X, 7 * _2X, N00T0X1,	//367
	IMG_BE_58, -5 * _2X, 5 * _2X, F00T2X1,	//368

	//BG5_WATER0
	IMG_BE_59, -11 * _2X, 24 * _2X, N00T0X1,	//369
	IMG_BE_60, -1 * _2X, 23 * _2X, N00T0X1,	//370
	IMG_BE_61, -11 * _2X, 56 * _2X, N00T1X1,	//371
	IMG_BE_62, -1 * _2X, 61 * _2X, N00T1X1,	//372

	//BG5_WATER1
	IMG_BE_59, -11 * _2X, 45 * _2X, N00T1X1,	//373
	IMG_BE_60, -1 * _2X, 44 * _2X, N00T1X1,	//374
	IMG_BE_61, -11 * _2X, 15 * _2X, N00T2X1,	//375
	IMG_BE_62, -1 * _2X, 20 * _2X, N00T2X1,	//376
	IMG_BE_61, 1 * _2X, 77 * _2X, F00T2X1,	//377
	IMG_BE_62, -11 * _2X, 82 * _2X, F00T2X1,	//378

	//BG5_WATER2
	IMG_BE_59, 1 * _2X, 89 * _2X, F00T1X1,	//379
	IMG_BE_60, -11 * _2X, 88 * _2X, F00T1X1,	//380
	IMG_BE_61, 1 * _2X, 63 * _2X, F00T0X1,	//381
	IMG_BE_62, -11 * _2X, 68 * _2X, F00T0X1,	//382

	//BG5_WATER3
	IMG_BE_59, 1 * _2X, 13 * _2X, F00T2X1,	//383
	IMG_BE_60, -11 * _2X, 12 * _2X, F00T2X1,	//384
	IMG_BE_61, 1 * _2X, 66 * _2X, F00T1X1,	//385
	IMG_BE_62, -11 * _2X, 71 * _2X, F00T1X1,	//386

	//BG5_WATER4
	IMG_BE_59, -11 * _2X, 32 * _2X, F00T0X1,	//387
	IMG_BE_60, -1 * _2X, 31 * _2X, F00T0X1,	//388
	IMG_BE_61, -11 * _2X, 64 * _2X, F00T1X1,	//389
	IMG_BE_62, -1 * _2X, 69 * _2X, F00T1X1,	//390

	//BG5_WATER5
	IMG_BE_59, -5 * _2X, 27 * _2X, N00T0X1,	//391
	IMG_BE_61, -5 * _2X, 65 * _2X, N00T1X1,	//392

	//BG5_WATER6
	IMG_BE_61, -5 * _2X, 19 * _2X, N00T2X1,	//393
	IMG_BE_59, -5 * _2X, 51 * _2X, N00T1X1,	//394

	//BG5_WATER7
	IMG_BE_59, -5 * _2X, 29 * _2X, F00T3X1,	//395
	IMG_BE_61, -5 * _2X, 67 * _2X, F00T1X1,	//396

	//BG5_WATER8
	IMG_BE_61, -5 * _2X, 15 * _2X, F00T2X1,	//397
	IMG_BE_59, -5 * _2X, 61 * _2X, F00T2X1,	//398

	//BG5_WATER9
	IMG_BE_59, -5 * _2X, 36 * _2X, F00T0X1,	//399
	IMG_BE_61, -5 * _2X, 82 * _2X, F00T1X1,	//400

	//BG5_CHAIN0
	IMG_BE_68, -3 * _2X, 0 * _2X, N00T0X1,	//401
	IMG_BE_68, -3 * _2X, 15 * _2X, N00T0X1,	//402
	IMG_BE_68, -3 * _2X, 30 * _2X, N00T0X1,	//403
	IMG_BE_68, -3 * _2X, 45 * _2X, N00T0X1,	//404

	//BG5_CHAIN1
	IMG_BE_68, -3 * _2X, 0 * _2X, N00T0X1,	//405
	IMG_BE_69, -2 * _2X, 15 * _2X, N00T0X1,	//406
	IMG_BE_71, 1 * _2X, 30 * _2X, N00T0X1,	//407
	IMG_BE_75, 5 * _2X, 45 * _2X, N00T0X1,	//408

	//BG5_CHAIN2
	IMG_BE_69, -3 * _2X, 0 * _2X, N00T0X1,	//409
	IMG_BE_71, 0 * _2X, 15 * _2X, N00T0X1,	//410
	IMG_BE_75, 4 * _2X, 30 * _2X, N00T0X1,	//411
	IMG_BE_77, 11 * _2X, 44 * _2X, N00T0X1,	//412

	//BG7_BUTTERFLY0
	IMG_BE_79, -5 * _2X, -4 * _2X, N00T0X1,	//413

	//BG7_BUTTERFLY1
	IMG_BE_80, -5 * _2X, -4 * _2X, N00T0X1,	//414

	//BG7_BUTTERFLY2
	IMG_BE_81, -5 * _2X, -8 * _2X, N00T0X1,	//415

	//BG9_STALACTITE0
	IMG_BE_82, -10 * _2X, -36 * _2X, N00T0X1,	//416

	//BG9_STALACTITE1
	IMG_BE_83, -13 * _2X, -9 * _2X, N00T2X1,	//417
	IMG_BE_82, -10 * _2X, -36 * _2X, N00T2X1,	//418

	//BG9_STALACTITE2
	IMG_BE_85, -13 * _2X, -9 * _2X, N00T1X1,	//419
	IMG_BE_86, -13 * _2X, -7 * _2X, N00T1X1,	//420
	IMG_BE_86, -2 * _2X, 0 * _2X, N00T1X1,	//421
	IMG_BE_86, 8 * _2X, -2 * _2X, N00T1X1,	//422
	IMG_BE_86, 11 * _2X, -9 * _2X, N00T1X1,	//423
	IMG_BE_86, -1 * _2X, -12 * _2X, N00T1X1,	//424
	IMG_BE_87, 4 * _2X, -13 * _2X, N00T1X1,	//425
	IMG_BE_87, -10 * _2X, -13 * _2X, N00T1X1,	//426
	IMG_BE_87, -12 * _2X, 0 * _2X, N00T1X1,	//427
	IMG_BE_87, 1 * _2X, -5 * _2X, N00T1X1,	//428
	IMG_BE_87, 13 * _2X, 0 * _2X, N00T1X1,	//429
	IMG_BE_87, -16 * _2X, -3 * _2X, N00T1X1,	//430

	//BG9_STALACTITE3
	IMG_BE_84, -13 * _2X, -8 * _2X, N00T0X1,	//431
	IMG_BE_86, -13 * _2X, -12 * _2X, N00T0X1,	//432
	IMG_BE_86, -5 * _2X, -3 * _2X, N00T0X1,	//433
	IMG_BE_86, 5 * _2X, -4 * _2X, N00T0X1,	//434
	IMG_BE_86, 10 * _2X, -13 * _2X, N00T0X1,	//435
	IMG_BE_86, -2 * _2X, -17 * _2X, N00T0X1,	//436
	IMG_BE_87, 2 * _2X, -21 * _2X, N00T0X1,	//437
	IMG_BE_87, -11 * _2X, -19 * _2X, N00T0X1,	//438
	IMG_BE_87, -14 * _2X, -2 * _2X, N00T0X1,	//439
	IMG_BE_87, -1 * _2X, -2 * _2X, N00T0X1,	//440
	IMG_BE_87, 14 * _2X, -4 * _2X, N00T0X1,	//441
	IMG_BE_87, -16 * _2X, -7 * _2X, N00T0X1,	//442

	//BG9_STALACTITE4
	IMG_BE_83, -13 * _2X, -9 * _2X, N00T0X1,	//443
	IMG_BE_86, -2 * _2X, -22 * _2X, N00T0X1,	//444
	IMG_BE_86, -10 * _2X, -25 * _2X, N00T0X1,	//445
	IMG_BE_86, -15 * _2X, -20 * _2X, N00T0X1,	//446
	IMG_BE_86, 1 * _2X, -13 * _2X, N00T0X1,	//447
	IMG_BE_86, 8 * _2X, -26 * _2X, N00T0X1,	//448
	IMG_BE_86, 12 * _2X, -17 * _2X, N00T0X1,	//449
	IMG_BE_87, -9 * _2X, -19 * _2X, N00T0X1,	//450
	IMG_BE_87, 4 * _2X, -27 * _2X, N00T0X1,	//451
	IMG_BE_87, 10 * _2X, -20 * _2X, N00T0X1,	//452
	IMG_BE_87, 18 * _2X, -15 * _2X, N00T0X1,	//453
	IMG_BE_87, -2 * _2X, -17 * _2X, N00T0X1,	//454
	IMG_BE_87, -9 * _2X, -11 * _2X, N00T0X1,	//455
	IMG_BE_87, -17 * _2X, -21 * _2X, N00T0X1,	//456
	IMG_BE_87, -17 * _2X, -12 * _2X, N00T0X1,	//457
	IMG_BE_87, -10 * _2X, -28 * _2X, N00T0X1,	//458
	IMG_BE_87, 14 * _2X, -20 * _2X, N00T0X1,	//459

	//BG9_STALACTITE5
	IMG_BE_84, -13 * _2X, -8 * _2X, N00T1X1,	//460
	IMG_BE_86, -13 * _2X, -18 * _2X, N00T1X1,	//461
	IMG_BE_86, -2 * _2X, -7 * _2X, N00T1X1,	//462
	IMG_BE_86, 8 * _2X, -12 * _2X, N00T1X1,	//463
	IMG_BE_86, 11 * _2X, -19 * _2X, N00T1X1,	//464
	IMG_BE_86, -1 * _2X, -25 * _2X, N00T1X1,	//465
	IMG_BE_87, 4 * _2X, -26 * _2X, N00T1X1,	//466
	IMG_BE_87, -10 * _2X, -23 * _2X, N00T1X1,	//467
	IMG_BE_87, -11 * _2X, -12 * _2X, N00T1X1,	//468
	IMG_BE_87, 1 * _2X, -15 * _2X, N00T1X1,	//469
	IMG_BE_87, 13 * _2X, -10 * _2X, N00T1X1,	//470
	IMG_BE_87, -16 * _2X, -14 * _2X, N00T1X1,	//471

	//BG9_STALACTITE6
	IMG_BE_85, -13 * _2X, -9 * _2X, N00T2X1,	//472
	IMG_BE_86, -13 * _2X, -11 * _2X, N00T2X1,	//473
	IMG_BE_86, -2 * _2X, -4 * _2X, N00T2X1,	//474
	IMG_BE_86, 8 * _2X, -6 * _2X, N00T2X1,	//475
	IMG_BE_86, 11 * _2X, -13 * _2X, N00T2X1,	//476
	IMG_BE_86, -1 * _2X, -16 * _2X, N00T2X1,	//477
	IMG_BE_87, 4 * _2X, -17 * _2X, N00T2X1,	//478
	IMG_BE_87, -10 * _2X, -17 * _2X, N00T2X1,	//479
	IMG_BE_87, -12 * _2X, -4 * _2X, N00T2X1,	//480
	IMG_BE_87, 1 * _2X, -9 * _2X, N00T2X1,	//481
	IMG_BE_87, 13 * _2X, -4 * _2X, N00T2X1,	//482
	IMG_BE_87, -16 * _2X, -7 * _2X, N00T2X1,	//483

	//BG9_STALACTITE7
	IMG_BE_83, -13 * _2X, -9 * _2X, N00T3X1,	//484
	IMG_BE_86, -18 * _2X, -8 * _2X, N00T3X1,	//485
	IMG_BE_86, 13 * _2X, -12 * _2X, N00T3X1,	//486
	IMG_BE_86, -4 * _2X, -12 * _2X, N00T3X1,	//487
	IMG_BE_87, -11 * _2X, -15 * _2X, N00T3X1,	//488
	IMG_BE_87, 17 * _2X, -2 * _2X, N00T3X1,	//489
	IMG_BE_87, -16 * _2X, -2 * _2X, N00T3X1,	//490
	IMG_BE_87, 6 * _2X, -11 * _2X, N00T3X1,	//491

	//BG9_MAGMA_FIRE0
	IMG_BE_87, 47 * _2X, -80 * _2X, N00E0X1,	//492
	IMG_BE_87, 0 * _2X, -74 * _2X, N00E0X1,	//493
	IMG_BE_87, -26 * _2X, -35 * _2X, N00E0X1,	//494
	IMG_BE_87, 24 * _2X, -70 * _2X, N00E0X1,	//495
	IMG_BE_87, 53 * _2X, -77 * _2X, N00E0X1,	//496
	IMG_BE_87, 5 * _2X, -78 * _2X, N00E0X1,	//497
	IMG_BE_87, -15 * _2X, -40 * _2X, N00E0X1,	//498
	IMG_BE_87, -4 * _2X, -29 * _2X, N00E0X1,	//499
	IMG_BE_87, 10 * _2X, -35 * _2X, N00E0X1,	//500
	IMG_BE_87, 41 * _2X, -67 * _2X, N00E0X1,	//501
	IMG_BE_87, -18 * _2X, -78 * _2X, N00E0X1,	//502
	IMG_BE_87, 5 * _2X, -55 * _2X, N00E0X1,	//503

	//BG9_MAGMA_FIRE1
	IMG_BE_87, 52 * _2X, -70 * _2X, N00E0X1,	//504
	IMG_BE_87, 5 * _2X, -64 * _2X, N00E0X1,	//505
	IMG_BE_87, -21 * _2X, -25 * _2X, N00E0X1,	//506
	IMG_BE_87, 29 * _2X, -60 * _2X, N00E0X1,	//507
	IMG_BE_87, 58 * _2X, -67 * _2X, N00E0X1,	//508
	IMG_BE_87, 10 * _2X, -68 * _2X, N00E0X1,	//509
	IMG_BE_87, -10 * _2X, -30 * _2X, N00E0X1,	//510
	IMG_BE_87, 1 * _2X, -19 * _2X, N00E0X1,	//511
	IMG_BE_87, 15 * _2X, -25 * _2X, N00E0X1,	//512
	IMG_BE_87, 46 * _2X, -57 * _2X, N00E0X1,	//513
	IMG_BE_87, -13 * _2X, -68 * _2X, N00E0X1,	//514
	IMG_BE_87, 10 * _2X, -45 * _2X, N00E0X1,	//515

	//BG9_MAGMA
	IMG_BE_89, 26 * _2X, -38 * _2X, N00T0X1,	//516
	IMG_BE_88, 49 * _2X, -31 * _2X, N00T0X1,	//517
	IMG_BE_90, 57 * _2X, -77 * _2X, N00T0X1,	//518

	//BG9_ETC0
	IMG_BE_91, 48 * _2X, 0 * _2X, N00T0X1,	//519

	//BG9_ETC1
	IMG_BE_92, 49 * _2X, -3 * _2X, N00T2X1,	//520

	//BG9_ETC2
	IMG_BE_93, 50 * _2X, -5 * _2X, N00T0X1,	//521

	//BG11_BACK0
	IMG_BE_94, 22 * _2X, 24 * _2X, N00T0X1,	//522
	IMG_BE_94, 35 * _2X, 24 * _2X, F00T0X1,	//523

	//BG11_BACK1
	IMG_BE_94, 22 * _2X, 25 * _2X, N00T0X1,	//524
	IMG_BE_94, 35 * _2X, 25 * _2X, F00T0X1,	//525

	//BG11_BACK2

	//BG11_BACK3
	IMG_BE_99, 36 * _2X, 59 * _2X, N00T0X1,	//526
	IMG_BE_100, 61 * _2X, 83 * _2X, N00T0X1,	//527
	IMG_BE_98, 87 * _2X, 41 * _2X, N00T0X1,	//528

	//BG11_BACK4
	IMG_BE_99, 36 * _2X, 58 * _2X, N00T0X1,	//529
	IMG_BE_100, 61 * _2X, 82 * _2X, N00T0X1,	//530
	IMG_BE_98, 87 * _2X, 40 * _2X, N00T0X1,	//531
	IMG_BE_95, 60 * _2X, 8 * _2X, N00T0X1,	//532
	IMG_BE_101, 61 * _2X, 24 * _2X, N00T3X1,	//533
	IMG_BE_97, 96 * _2X, 14 * _2X, N00T0X1,	//534

	//BG11_BACK5
	IMG_BE_99, 36 * _2X, 57 * _2X, N00T0X1,	//535
	IMG_BE_100, 61 * _2X, 81 * _2X, N00T0X1,	//536
	IMG_BE_98, 87 * _2X, 39 * _2X, N00T0X1,	//537
	IMG_BE_95, 60 * _2X, 9 * _2X, N00T0X1,	//538
	IMG_BE_101, 61 * _2X, 24 * _2X, N00T2X1,	//539
	IMG_BE_97, 97 * _2X, 14 * _2X, N00T0X1,	//540

	//BG11_BACK6
	IMG_BE_99, 36 * _2X, 58 * _2X, N00T0X1,	//541
	IMG_BE_100, 61 * _2X, 82 * _2X, N00T0X1,	//542
	IMG_BE_98, 87 * _2X, 40 * _2X, N00T0X1,	//543
	IMG_BE_101, 61 * _2X, 24 * _2X, N00T1X1,	//544
	IMG_BE_97, 98 * _2X, 14 * _2X, N00T0X1,	//545

	//BG11_BACK7
	IMG_BE_99, 36 * _2X, 59 * _2X, N00T0X1,	//546
	IMG_BE_100, 61 * _2X, 83 * _2X, N00T0X1,	//547
	IMG_BE_98, 87 * _2X, 41 * _2X, N00T0X1,	//548
	IMG_BE_101, 61 * _2X, 24 * _2X, N00T0X1,	//549
	IMG_BE_97, 99 * _2X, 14 * _2X, N00T0X1,	//550

	//BG11_BACK8
	IMG_BE_99, 36 * _2X, 60 * _2X, N00T0X1,	//551
	IMG_BE_100, 61 * _2X, 84 * _2X, N00T0X1,	//552
	IMG_BE_98, 87 * _2X, 42 * _2X, N00T0X1,	//553
	IMG_BE_101, 61 * _2X, 24 * _2X, N00T1X1,	//554
	IMG_BE_97, 98 * _2X, 14 * _2X, N00T0X1,	//555

	//BG11_BACK9
	IMG_BE_99, 36 * _2X, 61 * _2X, N00T0X1,	//556
	IMG_BE_100, 61 * _2X, 85 * _2X, N00T0X1,	//557
	IMG_BE_98, 87 * _2X, 43 * _2X, N00T0X1,	//558
	IMG_BE_101, 61 * _2X, 24 * _2X, N00T2X1,	//559
	IMG_BE_97, 97 * _2X, 14 * _2X, N00T0X1,	//560

	//BG11_BACK10
	IMG_BE_99, 36 * _2X, 60 * _2X, N00T0X1,	//561
	IMG_BE_100, 61 * _2X, 84 * _2X, N00T0X1,	//562
	IMG_BE_98, 87 * _2X, 42 * _2X, N00T0X1,	//563
	IMG_BE_101, 61 * _2X, 24 * _2X, N00T3X1,	//564
	IMG_BE_97, 96 * _2X, 14 * _2X, N00T0X1,	//565

	//BG12_FLOWER0
	IMG_BE_106, 16 * _2X, 18 * _2X, N00T3X1,	//566

	//BG12_FLOWER1
	IMG_BE_106, 16 * _2X, 18 * _2X, N00T2X1,	//567

	//BG12_FLOWER2
	IMG_BE_106, 16 * _2X, 18 * _2X, N00T1X1,	//568

	//BG12_FLOWER3
	IMG_BE_106, 16 * _2X, 18 * _2X, N00T0X1,	//569
	IMG_BE_107, 15 * _2X, 16 * _2X, N00T2X1,	//570

	//BG12_FLOWER4
	IMG_BE_107, 15 * _2X, 16 * _2X, N00T1X1,	//571

	//BG12_FLOWER5
	IMG_BE_107, 15 * _2X, 16 * _2X, N00T0X1,	//572
	IMG_BE_108, 15 * _2X, 16 * _2X, N00T2X1,	//573

	//BG12_FLOWER6
	IMG_BE_108, 15 * _2X, 16 * _2X, N00T0X1,	//574

	//BG12_FLOWER7
	IMG_BE_108, 15 * _2X, 16 * _2X, N00T1X1,	//575

	//BG12_LIGHT0
	IMG_BE_102, 9 * _2X, -56 * _2X, N00T3X1,	//576

	//BG12_LIGHT1
	IMG_BE_105, 51 * _2X, 87 * _2X, N00T3X1,	//577
	IMG_BE_102, 11 * _2X, -56 * _2X, N00T3X1,	//578
	IMG_BE_102, 15 * _2X, -40 * _2X, N00T3X1,	//579

	//BG12_LIGHT2
	IMG_BE_105, 52 * _2X, 86 * _2X, N00T3X1,	//580
	IMG_BE_103, 13 * _2X, -56 * _2X, N00T3X1,	//581
	IMG_BE_103, 17 * _2X, -40 * _2X, N00T3X1,	//582
	IMG_BE_103, 21 * _2X, -24 * _2X, N00T3X1,	//583

	//BG12_LIGHT3
	IMG_BE_105, 53 * _2X, 85 * _2X, N00T2X1,	//584
	IMG_BE_103, 15 * _2X, -56 * _2X, N00T3X1,	//585
	IMG_BE_103, 19 * _2X, -40 * _2X, N00T3X1,	//586
	IMG_BE_103, 23 * _2X, -24 * _2X, N00T3X1,	//587
	IMG_BE_103, 27 * _2X, -8 * _2X, N00T3X1,	//588

	//BG12_LIGHT4
	IMG_BE_105, 54 * _2X, 84 * _2X, N00T2X1,	//589
	IMG_BE_103, 17 * _2X, -55 * _2X, N00T3X1,	//590
	IMG_BE_103, 21 * _2X, -39 * _2X, N00T3X1,	//591
	IMG_BE_103, 25 * _2X, -23 * _2X, N00T3X1,	//592
	IMG_BE_103, 29 * _2X, -7 * _2X, N00T3X1,	//593
	IMG_BE_103, 33 * _2X, 9 * _2X, N00T3X1,	//594

	//BG12_LIGHT5
	IMG_BE_105, 55 * _2X, 83 * _2X, N00T2X1,	//595
	IMG_BE_104, 19 * _2X, -53 * _2X, N00T3X1,	//596
	IMG_BE_104, 23 * _2X, -37 * _2X, N00T3X1,	//597
	IMG_BE_104, 27 * _2X, -21 * _2X, N00T3X1,	//598
	IMG_BE_104, 31 * _2X, -5 * _2X, N00T3X1,	//599
	IMG_BE_104, 35 * _2X, 11 * _2X, N00T3X1,	//600
	IMG_BE_104, 39 * _2X, 27 * _2X, N00T3X1,	//601

	//BG12_LIGHT6
	IMG_BE_105, 56 * _2X, 82 * _2X, N00T2X1,	//602
	IMG_BE_104, 21 * _2X, -52 * _2X, N00T3X1,	//603
	IMG_BE_104, 25 * _2X, -36 * _2X, N00T3X1,	//604
	IMG_BE_104, 29 * _2X, -20 * _2X, N00T3X1,	//605
	IMG_BE_104, 33 * _2X, -4 * _2X, N00T3X1,	//606
	IMG_BE_104, 37 * _2X, 12 * _2X, N00T3X1,	//607
	IMG_BE_104, 41 * _2X, 28 * _2X, N00T3X1,	//608

	//BG12_LIGHT7
	IMG_BE_105, 57 * _2X, 81 * _2X, N00T2X1,	//609
	IMG_BE_104, 27 * _2X, -52 * _2X, N00T3X1,	//610
	IMG_BE_104, 31 * _2X, -36 * _2X, N00T3X1,	//611
	IMG_BE_104, 35 * _2X, -20 * _2X, N00T3X1,	//612
	IMG_BE_104, 39 * _2X, -4 * _2X, N00T3X1,	//613
	IMG_BE_104, 43 * _2X, 12 * _2X, N00T3X1,	//614
	IMG_BE_104, 47 * _2X, 28 * _2X, N00T3X1,	//615

	//BG12_LIGHT8
	IMG_BE_105, 58 * _2X, 80 * _2X, N00T2X1,	//616
	IMG_BE_104, 33 * _2X, -52 * _2X, N00T3X1,	//617
	IMG_BE_104, 37 * _2X, -36 * _2X, N00T3X1,	//618
	IMG_BE_104, 41 * _2X, -20 * _2X, N00T3X1,	//619
	IMG_BE_104, 45 * _2X, -4 * _2X, N00T3X1,	//620
	IMG_BE_104, 49 * _2X, 12 * _2X, N00T3X1,	//621

	//BG12_LIGHT9
	IMG_BE_105, 59 * _2X, 79 * _2X, N00T2X1,	//622
	IMG_BE_103, 39 * _2X, -54 * _2X, N00T3X1,	//623
	IMG_BE_103, 43 * _2X, -38 * _2X, N00T3X1,	//624
	IMG_BE_103, 47 * _2X, -22 * _2X, N00T3X1,	//625
	IMG_BE_103, 51 * _2X, -6 * _2X, N00T3X1,	//626

	//BG12_LIGHT10
	IMG_BE_105, 60 * _2X, 78 * _2X, N00T3X1,	//627
	IMG_BE_103, 43 * _2X, -50 * _2X, N00T3X1,	//628
	IMG_BE_103, 47 * _2X, -34 * _2X, N00T3X1,	//629
	IMG_BE_103, 51 * _2X, -18 * _2X, N00T3X1,	//630

	//BG12_LIGHT11
	IMG_BE_105, 61 * _2X, 77 * _2X, N00T3X1,	//631
	IMG_BE_103, 49 * _2X, -54 * _2X, N00T3X1,	//632
	IMG_BE_103, 53 * _2X, -38 * _2X, N00T3X1,	//633
	IMG_BE_103, 57 * _2X, -22 * _2X, N00T3X1,	//634

	//BG12_LIGHT12
	IMG_BE_105, 63 * _2X, 75 * _2X, N00T3X1,	//635
	IMG_BE_102, 55 * _2X, -52 * _2X, N00T3X1,	//636
	IMG_BE_102, 59 * _2X, -36 * _2X, N00T3X1,	//637

	//BG12_LIGHT13
	IMG_BE_105, 65 * _2X, 73 * _2X, N00T3X1,	//638
	IMG_BE_102, 59 * _2X, -50 * _2X, N00T3X1,	//639

	//BG12_LIGHT14
	IMG_BE_102, 63 * _2X, -50 * _2X, N00T3X1,	//640

	//BG13_STATUE0
	IMG_BE_111, 7 * _2X, 9 * _2X, N00T0X1,	//641
	IMG_BE_113, 1 * _2X, 23 * _2X, N00T0X1,	//642
	IMG_BE_113, 20 * _2X, 23 * _2X, F00T0X1,	//643
	IMG_BE_112, 4 * _2X, 30 * _2X, N00T0X1,	//644
	IMG_BE_112, 18 * _2X, 30 * _2X, N00T0X1,	//645

	//BG13_GOLEMSTEP0
	IMG_BE_114, -24 * _2X, -21 * _2X, N00E0X1,	//646
	IMG_BE_114, 0 * _2X, -21 * _2X, F00E0X1,	//647

	//BG13_GOLEMSTEP1
	IMG_BE_110, -24 * _2X, -30 * _2X, N00E2X1,	//648
	IMG_BE_110, 0 * _2X, -30 * _2X, F00E2X1,	//649

	//BG13_GOLEMSTEP2
	IMG_BE_110, -24 * _2X, -30 * _2X, N00E1X1,	//650
	IMG_BE_110, 0 * _2X, -30 * _2X, F00E1X1,	//651

	//BG13_GOLEMSTEP3
	IMG_BE_110, -24 * _2X, -30 * _2X, N00E0X1,	//652
	IMG_BE_110, 0 * _2X, -30 * _2X, F00E0X1,	//653
	IMG_BE_110, -24 * _2X, -30 * _2X, F18E1X1,	//654
	IMG_BE_110, 0 * _2X, -30 * _2X, N18E1X1,	//655

	//BG13_GOLEMSTEP4
	IMG_BE_110, -24 * _2X, -30 * _2X, N00E0X1,	//656
	IMG_BE_110, 0 * _2X, -30 * _2X, F00E0X1,	//657
	IMG_BE_110, -24 * _2X, -40 * _2X, F18E1X1,	//658
	IMG_BE_110, 0 * _2X, -40 * _2X, N18E1X1,	//659

	//BG13_GOLEMSTEP5
	IMG_BE_110, -24 * _2X, -30 * _2X, N00E0X1,	//660
	IMG_BE_110, 0 * _2X, -30 * _2X, F00E0X1,	//661
	IMG_BE_110, -24 * _2X, -50 * _2X, F18E2X1,	//662
	IMG_BE_110, 0 * _2X, -50 * _2X, N18E2X1,	//663

	//BG13_GOLEMSTEP6
	IMG_BE_110, -24 * _2X, -30 * _2X, N00E1X1,	//664
	IMG_BE_110, 0 * _2X, -30 * _2X, F00E1X1,	//665
	IMG_BE_110, -24 * _2X, -70 * _2X, F18E3X1,	//666
	IMG_BE_110, 0 * _2X, -70 * _2X, N18E3X1,	//667

	//BG13_GOLEMSTEP7
	IMG_BE_110, -24 * _2X, -30 * _2X, N00E2X1,	//668
	IMG_BE_110, 0 * _2X, -30 * _2X, F00E2X1,	//669

	//BG13_CLOUD0
	IMG_BE_115, 0 * _2X, 0 * _2X, N00T0X1,	//670

	//BG13_CLOUD1
	IMG_BE_115, 0 * _2X, 0 * _2X, N00T0X1,	//671
	IMG_BE_116, 64 * _2X, 27 * _2X, N00T0X1,	//672

	//BG13_CLOUD2
	IMG_BE_116, 14 * _2X, 0 * _2X, N00T0X1,	//673
	IMG_BE_117, 0 * _2X, 8 * _2X, N00T0X1,	//674
	IMG_BE_117, 44 * _2X, 8 * _2X, N00T0X1,	//675

	//BG13_STONE0
	IMG_BE_118, -6 * _2X, -7 * _2X, N00T0X1,	//676

	//BG13_STONE1
	IMG_BE_119, -7 * _2X, -7 * _2X, N00T0X1,	//677

	//BG13_STONE2
	IMG_BE_120, -6 * _2X, -6 * _2X, N00T0X1,	//678

	//BG13_STONE3
	IMG_BE_121, -6 * _2X, -5 * _2X, N00T0X1,	//679

	//BG14_AURORA0
	IMG_BE_122, 0 * _2X, 0 * _2X, N00E2X1,	//680

	//BG14_AURORA1
	IMG_BE_122, 2 * _2X, 0 * _2X, N00E1X1,	//681

	//BG14_AURORA2
	IMG_BE_122, 4 * _2X, 0 * _2X, N00E0X1,	//682
	IMG_BE_124, 16 * _2X, -1 * _2X, N00E2X1,	//683

	//BG14_AURORA3
	IMG_BE_122, 6 * _2X, 0 * _2X, N00E1X1,	//684
	IMG_BE_124, 18 * _2X, -1 * _2X, N00E1X1,	//685

	//BG14_AURORA4
	IMG_BE_122, 8 * _2X, 0 * _2X, N00E2X1,	//686
	IMG_BE_124, 20 * _2X, -1 * _2X, N00E0X1,	//687
	IMG_BE_125, 26 * _2X, 2 * _2X, N00E2X1,	//688

	//BG14_AURORA5
	IMG_BE_124, 22 * _2X, -1 * _2X, N00E1X1,	//689
	IMG_BE_125, 28 * _2X, 2 * _2X, N00E1X1,	//690

	//BG14_AURORA6
	IMG_BE_125, 30 * _2X, 2 * _2X, N00E0X1,	//691
	IMG_BE_126, 35 * _2X, 7 * _2X, N00E2X1,	//692

	//BG14_AURORA7
	IMG_BE_125, 32 * _2X, 2 * _2X, N00E1X1,	//693
	IMG_BE_126, 37 * _2X, 7 * _2X, N00E1X1,	//694

	//BG14_AURORA8
	IMG_BE_125, 34 * _2X, 2 * _2X, N00E2X1,	//695
	IMG_BE_126, 39 * _2X, 7 * _2X, N00E0X1,	//696
	IMG_BE_123, 50 * _2X, 0 * _2X, N00E2X1,	//697

	//BG14_AURORA9
	IMG_BE_126, 41 * _2X, 7 * _2X, N00E1X1,	//698
	IMG_BE_123, 52 * _2X, 0 * _2X, N00E1X1,	//699

	//BG14_AURORA10
	IMG_BE_126, 43 * _2X, 7 * _2X, N00E2X1,	//700
	IMG_BE_123, 54 * _2X, 0 * _2X, N00E0X1,	//701
	IMG_BE_127, 63 * _2X, -1 * _2X, N00E2X1,	//702

	//BG14_AURORA11
	IMG_BE_123, 56 * _2X, 0 * _2X, N00E1X1,	//703
	IMG_BE_127, 65 * _2X, -1 * _2X, N00E1X1,	//704

	//BG14_AURORA12
	IMG_BE_123, 58 * _2X, 0 * _2X, N00E2X1,	//705
	IMG_BE_127, 67 * _2X, -1 * _2X, N00E0X1,	//706

	//BG14_AURORA13
	IMG_BE_127, 69 * _2X, -1 * _2X, N00E1X1,	//707

	//BG14_AURORA14
	IMG_BE_127, 71 * _2X, -1 * _2X, N00E2X1,	//708

	//BG14_WATERFALL0
	IMG_BE_134, -11 * _2X, 6 * _2X, N00T0X1,	//709
	IMG_BE_128, -11 * _2X, 3 * _2X, N00T1X1,	//710

	//BG14_WATERFALL1
	IMG_BE_134, -11 * _2X, 5 * _2X, N00T0X1,	//711
	IMG_BE_129, -11 * _2X, 4 * _2X, N00T1X1,	//712

	//BG14_WATERFALL2
	IMG_BE_134, -11 * _2X, 6 * _2X, N00T0X1,	//713
	IMG_BE_128, -11 * _2X, 3 * _2X, F00T2X1,	//714

	//BG14_WATERFALL3
	IMG_BE_134, -11 * _2X, 6 * _2X, N00T0X1,	//715
	IMG_BE_129, -11 * _2X, 4 * _2X, F00T1X1,	//716

	//BG14_WATERFALL4
	IMG_BE_134, -11 * _2X, 5 * _2X, N00T0X1,	//717
	IMG_BE_128, -11 * _2X, 2 * _2X, N00T2X1,	//718

	//BG14_WATER0
	IMG_BE_130, -11 * _2X, 24 * _2X, N00T0X1,	//719
	IMG_BE_131, -1 * _2X, 23 * _2X, N00T0X1,	//720
	IMG_BE_132, -11 * _2X, 56 * _2X, N00T1X1,	//721
	IMG_BE_133, -1 * _2X, 61 * _2X, N00T1X1,	//722

	//BG14_WATER1
	IMG_BE_130, -11 * _2X, 45 * _2X, N00T1X1,	//723
	IMG_BE_131, -1 * _2X, 44 * _2X, N00T1X1,	//724
	IMG_BE_132, -11 * _2X, 15 * _2X, N00T2X1,	//725
	IMG_BE_133, -1 * _2X, 20 * _2X, N00T2X1,	//726
	IMG_BE_132, 1 * _2X, 77 * _2X, F00T2X1,	//727
	IMG_BE_133, -11 * _2X, 82 * _2X, F00T2X1,	//728

	//BG14_WATER2
	IMG_BE_130, 1 * _2X, 89 * _2X, F00T1X1,	//729
	IMG_BE_131, -11 * _2X, 88 * _2X, F00T1X1,	//730
	IMG_BE_132, 1 * _2X, 63 * _2X, F00T0X1,	//731
	IMG_BE_133, -11 * _2X, 68 * _2X, F00T0X1,	//732

	//BG14_WATER3
	IMG_BE_130, 1 * _2X, 13 * _2X, F00T2X1,	//733
	IMG_BE_131, -11 * _2X, 12 * _2X, F00T2X1,	//734
	IMG_BE_132, 1 * _2X, 66 * _2X, F00T1X1,	//735
	IMG_BE_133, -11 * _2X, 71 * _2X, F00T1X1,	//736

	//BG14_WATER4
	IMG_BE_130, -11 * _2X, 32 * _2X, F00T0X1,	//737
	IMG_BE_131, -1 * _2X, 31 * _2X, F00T0X1,	//738
	IMG_BE_132, -11 * _2X, 64 * _2X, F00T1X1,	//739
	IMG_BE_133, -1 * _2X, 69 * _2X, F00T1X1,	//740

	//BG15_FLAG0
	IMG_BE_135, 8 * _2X, -3 * _2X, N00T0X1,	//741

	//BG15_FLAG1
	IMG_BE_136, 8 * _2X, -5 * _2X, N00T0X1,	//742

	//BG15_FLAG2
	IMG_BE_137, 8 * _2X, 1 * _2X, N00T0X1,	//743

	//BG16_CLOUD0
	IMG_BE_138, 0 * _2X, 0 * _2X, N00E3X1,	//744
	IMG_BE_139, 5 * _2X, 17 * _2X, N00E3X1,	//745
	IMG_BE_140, 50 * _2X, 17 * _2X, N00E3X1,	//746
	IMG_BE_138, 30 * _2X, 21 * _2X, N00E3X1,	//747
	IMG_BE_139, 45 * _2X, 37 * _2X, N00E3X1,	//748
	IMG_BE_140, 90 * _2X, 37 * _2X, N00E3X1,	//749

	//BG16_CLOUD1
	IMG_BE_141, 0 * _2X, 0 * _2X, N00E2X1,	//750
	IMG_BE_142, 29 * _2X, 17 * _2X, N00E2X1,	//751

	//BG16_CLOUD2
	IMG_BE_142, 0 * _2X, 0 * _2X, N00E2X1,	//752

	//BG16_CANDLE0
	IMG_BE_144, 0 * _2X, -7 * _2X, N00E3X1,	//753

	//BG16_CANDLE1
	IMG_BE_144, 0 * _2X, -7 * _2X, N00E2X1,	//754
	IMG_BE_143, -1 * _2X, -9 * _2X, N00E3X1,	//755

	//BG16_CANDLE2
	IMG_BE_144, 0 * _2X, -7 * _2X, N00E1X1,	//756
	IMG_BE_143, -1 * _2X, -9 * _2X, N00E2X1,	//757

	//BG16_CANDLE3
	IMG_BE_144, 0 * _2X, -7 * _2X, N00E0X1,	//758
	IMG_BE_143, -1 * _2X, -9 * _2X, N00E1X1,	//759

	//BG16_CANDLE4
	IMG_BE_143, -1 * _2X, -9 * _2X, N00E0X1,	//760

	//BG17_CANDLE0
	IMG_BE_147, 3 * _2X, -19 * _2X, N00E0X1,	//761

	//BG17_CANDLE1
	IMG_BE_145, 2 * _2X, -25 * _2X, N00E0X1,	//762

	//BG17_CANDLE2
	IMG_BE_146, 2 * _2X, -23 * _2X, N00E0X1,	//763

	//BG17_CANDLE3
	IMG_BE_148, 2 * _2X, -19 * _2X, N00E0X1,	//764

	//BG17_MIRROR
	IMG_BE_151, 1 * _2X, 1 * _2X, N00E3X2,	//765
	IMG_BE_151, 1 * _2X, 1 * _2X, N00E2X1,	//766
	IMG_BE_149, 1 * _2X, 1 * _2X, N00T0X1,	//767
	IMG_BE_151, 1 * _2X, 34 * _2X, N18E3X2,	//768
	IMG_BE_151, 16 * _2X, 49 * _2X, N18E2X1,	//769
	IMG_BE_152, 1 * _2X, 21 * _2X, N00T0X1,	//770
	IMG_BE_150, 1 * _2X, 39 * _2X, N00T0X1,	//771
	IMG_BE_153, 24 * _2X, 55 * _2X, N00T0X1,	//772

	//BG17_ROUND
	IMG_BE_154, -10 * _2X, -10 * _2X, N00T0X1,	//773
	IMG_BE_154, 0 * _2X, -10 * _2X, F00T0X1,	//774

	//BG18_METEOR0
	IMG_BE_156, 27 * _2X, -41 * _2X, N00E0X1,	//775
	IMG_BE_157, 23 * _2X, -34 * _2X, N00E0X1,	//776
	IMG_BE_157, 18 * _2X, -29 * _2X, N00E0X1,	//777
	IMG_BE_157, 13 * _2X, -24 * _2X, N00E0X1,	//778
	IMG_BE_157, 8 * _2X, -19 * _2X, N00E0X1,	//779
	IMG_BE_155, 0 * _2X, -20 * _2X, N00E0X1,	//780

	//BG18_METEOR1
	IMG_BE_158, 12 * _2X, -18 * _2X, N00E0X1,	//781
	IMG_BE_158, 9 * _2X, -15 * _2X, N00E0X1,	//782
	IMG_BE_158, 6 * _2X, -12 * _2X, N00E0X1,	//783
	IMG_BE_158, 3 * _2X, -9 * _2X, N00E0X1,	//784
	IMG_BE_160, 15 * _2X, -26 * _2X, N00E0X1,	//785
	IMG_BE_159, 0 * _2X, -9 * _2X, N00E0X1,	//786

	//BG18_SATELITE0
	IMG_BE_161, 0 * _2X, 0 * _2X, N00T0X1,	//787
	IMG_BE_162, 24 * _2X, 13 * _2X, N00T0X1,	//788
	IMG_BE_163, 11 * _2X, 22 * _2X, N00T0X1,	//789

	//BG18_SATELITE1
	IMG_BE_161, 39 * _2X, 14 * _2X, N00T0X1,	//790
	IMG_BE_162, 17 * _2X, 5 * _2X, N00T0X1,	//791
	IMG_BE_163, 0 * _2X, 0 * _2X, N00T0X1,	//792
	IMG_BE_163, 10 * _2X, 18 * _2X, N09T0X1,	//793
	IMG_BE_163, 60 * _2X, 7 * _2X, N27T0X1,	//794
	IMG_BE_162, 66 * _2X, 12 * _2X, N09T0X1,	//795

	//BG18_SATELITE2
	IMG_BE_161, 35 * _2X, 12 * _2X, N27T0X1,	//796
	IMG_BE_162, 0 * _2X, 14 * _2X, N27T0X1,	//797
	IMG_BE_163, 4 * _2X, 1 * _2X, N00T0X1,	//798
	IMG_BE_163, 12 * _2X, 12 * _2X, N18T0X1,	//799
	IMG_BE_163, 64 * _2X, 11 * _2X, N09T0X1,	//800
	IMG_BE_163, 28 * _2X, 37 * _2X, N18T0X1,	//801
	IMG_BE_163, 68 * _2X, 30 * _2X, N00T0X1,	//802
	IMG_BE_163, 78 * _2X, 16 * _2X, N27T0X1,	//803
	IMG_BE_162, 91 * _2X, 30 * _2X, N00T0X1,	//804
};

const unsigned short sunShineOff[TOTALSUNSHINEOFF * 4] = {
	//BMP : C:\SktWipi\Projects\Mos5\Resource\shine.bmp
	46 * _2X, 0 * _2X, 20 * _2X, 20 * _2X,	//0
	46 * _2X, 20 * _2X, 14 * _2X, 14 * _2X,	//1
	59 * _2X, 34 * _2X, 12 * _2X, 12 * _2X,	//2
	46 * _2X, 34 * _2X, 13 * _2X, 13 * _2X,	//3
	60 * _2X, 21 * _2X, 7 * _2X, 7 * _2X,	//4
	60 * _2X, 28 * _2X, 3 * _2X, 3 * _2X,	//5
};

const signed short sunShineMI[126 * 4] = {
	//SUNSHINE0
	IMG_SL_0, -60 * _2X, -39 * _2X, N00E3X3,	//0
	IMG_SL_0, -60 * _2X, 21 * _2X, N27E3X3,	//1
	IMG_SL_2, -106 * _2X, 101 * _2X, N00E3X1,	//2
	IMG_SL_3, -117 * _2X, 109 * _2X, N00E0X1,	//3
	IMG_SL_4, -98 * _2X, 90 * _2X, N00E0X1,	//4
	IMG_SL_3, -100 * _2X, 82 * _2X, N00E0X2,	//5
	IMG_SL_4, -125 * _2X, 121 * _2X, N00E0X1,	//6
	IMG_SL_1, -71 * _2X, 55 * _2X, N00E2X2,	//7
	IMG_SL_1, -43 * _2X, 45 * _2X, N00E3X1,	//8
	IMG_SL_0, -69 * _2X, 7 * _2X, N00E3X2,	//9
	IMG_SL_0, -29 * _2X, 7 * _2X, N09E3X2,	//10
	IMG_SL_0, -29 * _2X, 47 * _2X, N18E3X2,	//11
	IMG_SL_0, -69 * _2X, 47 * _2X, N27E3X2,	//12

	//SUNSHINE1
	IMG_SL_0, -64 * _2X, -35 * _2X, N00E2X3,	//13
	IMG_SL_0, -4 * _2X, -35 * _2X, N09E2X3,	//14
	IMG_SL_0, -4 * _2X, 25 * _2X, N18E2X3,	//15
	IMG_SL_0, -64 * _2X, 25 * _2X, N27E2X3,	//16
	IMG_SL_1, -47 * _2X, 49 * _2X, N00E3X1,	//17
	IMG_SL_3, -102 * _2X, 84 * _2X, N00E1X2,	//18
	IMG_SL_3, -108 * _2X, 102 * _2X, N00E1X1,	//19
	IMG_SL_4, -116 * _2X, 114 * _2X, N00E2X1,	//20
	IMG_SL_0, -71 * _2X, 5 * _2X, N00E3X2,	//21
	IMG_SL_0, -31 * _2X, 5 * _2X, N09E3X2,	//22
	IMG_SL_0, -31 * _2X, 45 * _2X, N18E3X2,	//23
	IMG_SL_0, -71 * _2X, 45 * _2X, N27E3X2,	//24
	IMG_SL_1, -71 * _2X, 69 * _2X, N00E3X1,	//25

	//SUNSHINE2
	IMG_SL_0, -73 * _2X, 11 * _2X, N00E3X2,	//26
	IMG_SL_0, -33 * _2X, 11 * _2X, N09E3X2,	//27
	IMG_SL_0, -33 * _2X, 51 * _2X, N18E3X2,	//28
	IMG_SL_0, -73 * _2X, 51 * _2X, N27E3X2,	//29
	IMG_SL_0, -68 * _2X, -31 * _2X, N00E3X3,	//30
	IMG_SL_0, -8 * _2X, -31 * _2X, N09E3X3,	//31
	IMG_SL_0, -8 * _2X, 29 * _2X, N18E3X3,	//32
	IMG_SL_0, -68 * _2X, 29 * _2X, N27E3X3,	//33
	IMG_SL_1, -51 * _2X, 53 * _2X, N00E3X1,	//34
	IMG_SL_3, -114 * _2X, 82 * _2X, N00E2X3,	//35
	IMG_SL_3, -110 * _2X, 103 * _2X, N00E2X1,	//36

	//SUNSHINE3
	IMG_SL_0, -72 * _2X, -26 * _2X, N00E3X3,	//37
	IMG_SL_0, -12 * _2X, -26 * _2X, N09E3X3,	//38
	IMG_SL_0, -12 * _2X, 34 * _2X, N18E3X3,	//39
	IMG_SL_0, -72 * _2X, 34 * _2X, N27E3X3,	//40
	IMG_SL_1, -55 * _2X, 55 * _2X, N00E3X1,	//41
	IMG_SL_3, -116 * _2X, 83 * _2X, N00E3X3,	//42

	//SUNSHINE4
	IMG_SL_0, -72 * _2X, -26 * _2X, N00E3X3,	//43
	IMG_SL_0, -12 * _2X, -26 * _2X, N09E3X3,	//44
	IMG_SL_0, -12 * _2X, 34 * _2X, N18E3X3,	//45
	IMG_SL_0, -72 * _2X, 34 * _2X, N27E3X3,	//46
	IMG_SL_5, -52 * _2X, 63 * _2X, N00E0X1,	//47

	//SUNSHINE5

	//SUNSHINE6
	IMG_SL_0, -56 * _2X, -43 * _2X, N00E3X3,	//48
	IMG_SL_0, -56 * _2X, 17 * _2X, N27E3X3,	//49

	//SUNSHINE7
	IMG_SL_0, -60 * _2X, -39 * _2X, N00E3X3,	//50
	IMG_SL_0, -60 * _2X, 21 * _2X, N27E3X3,	//51
	IMG_SL_2, -87 * _2X, 84 * _2X, N00E3X1,	//52
	IMG_SL_4, -99 * _2X, 99 * _2X, N00E0X1,	//53
	IMG_SL_4, -110 * _2X, 109 * _2X, N00E0X1,	//54

	//SUNSHINE8
	IMG_SL_0, -56 * _2X, -43 * _2X, N00E3X3,	//55
	IMG_SL_0, -56 * _2X, 17 * _2X, N27E3X3,	//56
	IMG_SL_2, -89 * _2X, 86 * _2X, N00E3X1,	//57

	//SUNSHINE9
	IMG_SL_0, -60 * _2X, -39 * _2X, N00E3X3,	//58
	IMG_SL_0, -60 * _2X, 21 * _2X, N27E3X3,	//59
	IMG_SL_4, -99 * _2X, 99 * _2X, N00E0X1,	//60
	IMG_SL_4, -110 * _2X, 109 * _2X, N00E0X1,	//61

	//SUNSHINE10

	//SUNSHINE11
	IMG_SL_0, -56 * _2X, -43 * _2X, N00E3X3,	//62
	IMG_SL_0, -56 * _2X, 17 * _2X, N27E3X3,	//63

	//SUNSHINE12
	IMG_SL_0, -60 * _2X, -39 * _2X, N00E3X3,	//64
	IMG_SL_0, -60 * _2X, 21 * _2X, N27E3X3,	//65
	IMG_SL_2, -87 * _2X, 84 * _2X, N00E3X1,	//66

	//SUNSHINE13
	IMG_SL_0, -56 * _2X, -43 * _2X, N00E3X3,	//67
	IMG_SL_0, -56 * _2X, 17 * _2X, N27E3X3,	//68
	IMG_SL_1, -47 * _2X, 49 * _2X, N00E3X1,	//69

	//SUNSHINE14
	IMG_SL_0, -62 * _2X, 1 * _2X, N00E3X2,	//70
	IMG_SL_0, -22 * _2X, 1 * _2X, N09E3X2,	//71
	IMG_SL_0, -22 * _2X, 41 * _2X, N18E3X2,	//72
	IMG_SL_0, -62 * _2X, 41 * _2X, N27E3X2,	//73
	IMG_SL_2, -87 * _2X, 84 * _2X, N00E3X1,	//74
	IMG_SL_1, -66 * _2X, 52 * _2X, N00E2X2,	//75
	IMG_SL_4, -99 * _2X, 99 * _2X, N00E0X1,	//76
	IMG_SL_4, -110 * _2X, 109 * _2X, N00E0X1,	//77

	//SUNSHINE15
	IMG_SL_0, -50 * _2X, -49 * _2X, N00E3X3,	//78
	IMG_SL_0, -50 * _2X, 11 * _2X, N27E3X3,	//79
	IMG_SL_2, -96 * _2X, 81 * _2X, N00E3X2,	//80
	IMG_SL_1, -69 * _2X, 54 * _2X, N00E1X2,	//81
	IMG_SL_2, -103 * _2X, 98 * _2X, N00E3X1,	//82
	IMG_SL_2, -115 * _2X, 108 * _2X, N00E3X1,	//83
	IMG_SL_0, -66 * _2X, 5 * _2X, N00E2X2,	//84
	IMG_SL_0, -26 * _2X, 5 * _2X, N09E2X2,	//85
	IMG_SL_0, -26 * _2X, 45 * _2X, N18E2X2,	//86
	IMG_SL_0, -66 * _2X, 45 * _2X, N27E2X2,	//87

	//SUNSHINE2_0
	IMG_SL_3, 26 * _2X, -25 * _2X, N00E0X1,	//88
	IMG_SL_1, -27 * _2X, 5 * _2X, N00E3X2,	//89
	IMG_SL_1, -74 * _2X, 46 * _2X, N00E3X2,	//90
	IMG_SL_2, -2 * _2X, -13 * _2X, N00E3X2,	//91
	IMG_SL_5, 40 * _2X, -29 * _2X, N00E0X1,	//92
	IMG_SL_0, -80 * _2X, 0 * _2X, N00E2X2,	//93
	IMG_SL_0, -40 * _2X, 0 * _2X, N09E2X2,	//94
	IMG_SL_0, -40 * _2X, 40 * _2X, N18E2X2,	//95
	IMG_SL_0, -80 * _2X, 40 * _2X, N27E2X2,	//96
	IMG_SL_3, 13 * _2X, -15 * _2X, N00E0X1,	//97

	//SUNSHINE2_1
	IMG_SL_1, -29 * _2X, 7 * _2X, N00E3X2,	//98
	IMG_SL_0, -88 * _2X, 5 * _2X, N00E2X2,	//99
	IMG_SL_0, -48 * _2X, 5 * _2X, N09E2X2,	//100
	IMG_SL_0, -48 * _2X, 45 * _2X, N18E2X2,	//101
	IMG_SL_0, -88 * _2X, 45 * _2X, N27E2X2,	//102
	IMG_SL_3, 24 * _2X, -24 * _2X, N00E2X1,	//103
	IMG_SL_1, -76 * _2X, 48 * _2X, N00E3X2,	//104
	IMG_SL_3, -6 * _2X, -11 * _2X, N00E0X2,	//105
	IMG_SL_3, 9 * _2X, -11 * _2X, N00E2X1,	//106

	//SUNSHINE2_2
	IMG_SL_2, -2 * _2X, -13 * _2X, N00E2X2,	//107
	IMG_SL_1, -14 * _2X, -7 * _2X, N00E2X2,	//108

	//SUNSHINE2_3
	IMG_SL_2, -5 * _2X, -11 * _2X, N00E3X2,	//109
	IMG_SL_1, -16 * _2X, -6 * _2X, N00E3X2,	//110

	//SUNSHINE2_4
	IMG_SL_2, 30 * _2X, -28 * _2X, N00E3X1,	//111
	IMG_SL_1, 37 * _2X, -36 * _2X, N00E3X1,	//112
	IMG_SL_4, 21 * _2X, -16 * _2X, N00E0X1,	//113
	IMG_SL_2, 7 * _2X, -9 * _2X, N00E3X1,	//114
	IMG_SL_1, -59 * _2X, 46 * _2X, N00E3X1,	//115

	//SUNSHINE2_5
	IMG_SL_0, -76 * _2X, -3 * _2X, N00E3X2,	//116
	IMG_SL_0, -36 * _2X, -3 * _2X, N09E3X2,	//117
	IMG_SL_0, -36 * _2X, 37 * _2X, N18E3X2,	//118
	IMG_SL_0, -76 * _2X, 37 * _2X, N27E3X2,	//119
	IMG_SL_2, 17 * _2X, -17 * _2X, N00E3X1,	//120
	IMG_SL_3, 26 * _2X, -25 * _2X, N00E0X1,	//121
	IMG_SL_5, 40 * _2X, -29 * _2X, N00E0X1,	//122
	IMG_SL_2, -1 * _2X, -13 * _2X, N00E2X2,	//123
	IMG_SL_1, -16 * _2X, 9 * _2X, N00E3X1,	//124
	IMG_SL_1, -71 * _2X, 43 * _2X, N00E3X2,	//125
};

const unsigned char sunShineMIC[TOTALSUNSHINEMOTION * 2] = {
	0, 13,	//0
	13, 13,	//1
	26, 11,	//2
	37, 6,	//3
	43, 5,	//4
	48, 0,	//5
	48, 2,	//6
	50, 5,	//7
	55, 3,	//8
	58, 4,	//9
	62, 0,	//10
	62, 2,	//11
	64, 3,	//12
	67, 3,	//13
	70, 8,	//14
	78, 10,	//15
	88, 10,	//16
	98, 9,	//17
	107, 2,	//18
	109, 2,	//19
	111, 5,	//20
	116, 10,	//21
};

const unsigned char sateliteMotionCnt[62] = {
	0, 8,	//205
	8, 8,	//206
	16, 8,	//207
	24, 10,	//208
	34, 10,	//209
	44, 1,	//210
	45, 3,	//211
	48, 1,	//212
	49, 1,	//213
	50, 2,	//214

	52, 7,	//0
	59, 7,	//1
	66, 6,	//2
	72, 6,	//3
	78, 5,	//4
	83, 5,	//5
	88, 5,	//6
	93, 7,	//7
	100, 10,	//8
	110, 10,	//9
	120, 9,	//10
	129, 10,	//11
	139, 6,	//12
	145, 5,	//13
	150, 7,	//14
	157, 9,	//15
	166, 8,	//16
	174, 8,	//17
	182, 9,	//18
	191, 7,	//19
	198, 6,	//20
};


const signed short neutralData[TOTALNEUTRAL * NEUTRALDATASIZE] = {
	//0 : Block
	//1 : Shadow
	//2 : xoff
	//3 : yoff
	//4 : cpx
	//5 : cpy
	//6 : cx
	//7 : cy
	//8 : status
	//9 : motion
	//10 : movehandler

	//DrawArray로 그리는 오브젝트
	true, 1, 0 * _2X, TSIZE * 2, -TSIZE, -TSIZE * 2, TSIZE * 2, TSIZE * 2, FALL, IMG_OBJ_STONE, SIDEMOVE,	//OBJ_MOVE
	true, 0, TSIZE, TSIZE * 2, -TSIZE, -TSIZE * 2, TSIZE * 2, TSIZE * 2, FALL, 0, DROPMOVE,	//OBJ_DROP
	true, 1, 0 * _2X, 8 * _2X, -TSIZE, -18 * _2X, TSIZE * 2, 18 * _2X, FALL, IMG_OBJ_SEWAGESTONE, SEWAGESTONEMOVE,	//OBJ_SEWAGESTONE
	true, 0, 0 * _2X, 8 * _2X, -TSIZE, 0 * _2X, TSIZE * 2, TSIZE * 3 - 1, CLOSED, 0, DOORMOVE,	//OBJ_DOOR
	false, 0, 0 * _2X, 4 * _2X, -TSIZE, -TSIZE, TSIZE * 2, TSIZE * 2, 0, 0, REPULSIONMOVE,	//OBJ_REPULSION
	false, 1, 0 * _2X, 0 * _2X, -13 * _2X, -36 * _2X, 26 * _2X, 29 * _2X, 0, IMG_OBJ_MARK, 0,	//OBJ_MARK
	false, 0, 0 * _2X, 0 * _2X, -8 * _2X, -16 * _2X, TSIZE, TSIZE, 0, 0, 0,	//OBJ_ITEM
	false, 0, 0 * _2X, 4 * _2X, -TSIZE, TSIZE, TSIZE * 2, TSIZE, 0, IMG_OBJ_CLOAKING, CLOAKINGMOVE,	//OBJ_CLOAKING
	false, 0, 0 * _2X, 0 * _2X, -4 * _2X, 0 * _2X, 8 * _2X, 36 * _2X, 0, 0, NULL,	//OBJ_SOUL
	false, 0, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0, 0xFF, WARPMOVE,	//OBJ_WARP

	//DrawNeutral로 그리는 오브젝트
	false, 0, 0 * _2X, 0 * _2X, -11 * _2X, -24 * _2X, 22 * _2X, 28 * _2X, 0, OBJ_LEVER0, LEVERMOVE,	//OBJ_LEVER
	true, 0, 0 * _2X, 0 * _2X, -TSIZE, -TSIZE * 2, TSIZE * 2, TSIZE * 2, WALK, OBJ_PUSH0, PUSHMOVE,	//OBJ_PUSH
	false, 1, 0 * _2X, 0 * _2X, -12 * _2X, -22 * _2X, 24 * _2X, 22 * _2X, CLOSED, OBJ_BOX0, BOXMOVE,	//OBJ_BOX
	true, 1, 0 * _2X, 16 * _2X, -19 * _2X, -24 * _2X, 38 * _2X, 24 * _2X, 0, OBJ_CARPET0, CARPETMOVE,	//OBJ_CARPET
	false, 0, 0 * _2X, 0 * _2X, -128 * _2X, -59 * _2X, 127 * _2X, 59 * _2X, 0, OBJ_ROBINWIND0, ROBINTRAPMOVE,	//OBJ_ROBINTRAP
	false, 0, 0 * _2X, 0 * _2X, -16 * _2X, -8 * _2X, 32 * _2X, 16 * _2X, 0, OBJ_STAMP0, DIANATRAPMOVE,	//OBJ_DIANATRAP
	false, 0, 0 * _2X, -6 * _2X, -16 * _2X, 0 * _2X, 32 * _2X, 0 * _2X, 0, OBJ_BOARD3, DIANASTONEMOVE,	//OBJ_DIANASTONE
	true, 4, 0 * _2X, 6 * _2X, -16 * _2X, -32 * _2X, 32 * _2X, 20 * _2X, 0, OBJ_MAXXSTONE0, MAXXTRAPMOVE,	//OBJ_MAXXTRAP
	false, 0, 0 * _2X, 20 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0, OBJ_GATE0, 0,	//OBJ_GATE
	true, 4, 0 * _2X, 6 * _2X, -16 * _2X, -32 * _2X, 32 * _2X, 20 * _2X, 0, OBJ_SUNBLOCK0, SUNBLOCKMOVE,	//OBJ_SUNBLOCK
	true, 1, 0 * _2X, TSIZE * 2, -TSIZE, -TSIZE * 2, TSIZE * 2, TSIZE * 2, 0, OBJ_BREAK0, BREAKSTONEMOVE,	//OBJ_BREAKSTONE
	false, 0, 0 * _2X, 0 * _2X, -TSIZE, -TSIZE, TSIZE * 2, TSIZE * 2, 0, OBJ_DARK0, DARKSTONEMOVE,	//OBJ_DARKSTONE
	false, 0, 0 * _2X, 4 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0, OBJ_BUBBLE_UP0, BUBBLEMOVE,	//OBJ_BUBBLE
	false, 1, 0 * _2X, 0 * _2X, -TSIZE, -TSIZE, TSIZE * 2, TSIZE * 2, 0, OBJ_DARK0, DEMODARKMOVE,	//OBJ_DEMODARK
	true, 0, 0 * _2X, 0 * _2X, -TSIZE, 0 * _2X, TSIZE * 2, 0 * _2X, 0, 0, MAGMAMOVE,	//OBJ_MAGMA
	true, 1, 0 * _2X, 4 * _2X, -TSIZE * 2, -20 * _2X, TSIZE * 4 * _2X, TSIZE, 0, OBJ_MAGMASTONE0, MAGMABLOCKMOVE,	//OBJ_MAGMABLOCK
	true, 0, 0 * _2X, 0 * _2X, 0 * _2X, -TSIZE * 2, 0 * _2X, TSIZE * 2, 0, OBJ_BRIDGE0, BRIDGEMOVE,	//OBJ_BRIDGE
	false, 0, 0 * _2X, 36 * _2X, -10 * _2X, -16 * _2X, 20 * _2X, 16 * _2X, 0, BG9_STALACTITE0, STALACTITEMOVE,	//OBJ_STALACTITE
	false, 0, 0 * _2X, 24 * _2X, -TSIZE, -20 * _2X, TSIZE * 2, TSIZE, 0, OBJ_SPIKE0, SPIKEMOVE,	//OBJ_SPIKE
	false, 0, TSIZE, 20 * _2X, -TSIZE, -TSIZE, TSIZE * 2, TSIZE * 2, 0, 0, MAGNETMOVE,	//OBJ_MAGNET
	true, 2, 0 * _2X, 0 * _2X, -24 * _2X, -14 * _2X, 48 * _2X, 14 * _2X, FALL, OBJ_SLED0, SLEDMOVE,	//OBJ_SLED
	true, 0, 0 * _2X, 6 * _2X, -TSIZE, -TSIZE * 5 * _2X, TSIZE * 2, TSIZE * 5 * _2X, 0, OBJ_SLEDSTONE0, ICEBREAKMOVE,	//OBJ_ICEBREAK
	false, 0, 0 * _2X, 4 * _2X, -TSIZE, 10 * _2X, TSIZE * 2, 18 * _2X, 0, OBJ_INVISIBLE0, INVISIBLEMOVE,	//OBJ_INVISIBLE
	false, 0, 0 * _2X, 13 * _2X, -1 * _2X, -15 * _2X, 2 * _2X, 1 * _2X, 0, OBJ_DIMENSION0, NULL,	//OBJ_DIMENSION

	true, 0, 0 * _2X, 0 * _2X, -TSIZE * 2, -TSIZE * 4 * _2X, TSIZE * 4 * _2X, TSIZE * 4 * _2X, 0, OBJ_GOLEMBLOCK0, GOLEMBLOCKMOVE,	//OBJ_GOLEMBLOCK
	false, 1, 0 * _2X, 0 * _2X, -8 * _2X, -8 * _2X, TSIZE, TSIZE, 0, OBJ_BALL0, BALLMOVE,	//OBJ_BALL
	false, 0, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0, NULL, PITCHERMOVE,	//OBJ_PITCHER
	false, 0, 0 * _2X, 0 * _2X, -24 * _2X, -2 * _2X, TSIZE * 3 * _2X, 8 * _2X, 0, NULL, NULL,	//OBJ_CATCHER
	true, 0, 0 * _2X, 0 * _2X, 0 * _2X, -TSIZE * 3 * _2X, TSIZE, TSIZE * 3 * _2X, 0, OBJ_BALLBLOCK0, NULL,	//OBJ_BALLBLOCK
	false, 0, 0 * _2X, 0 * _2X, -8 * _2X, -8 * _2X, TSIZE, 8 * _2X, 0, OBJ_CYCLON0, NULL,	//OBJ_CYCLON
	false, 0, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X, 2 * _2X, 2 * _2X, 0, OBJ_BLACKHOLE0, BLACKHOLEMOVE,	//OBJ_BLACKHOLE
	false, 0, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X, 2 * _2X, 2 * _2X, 0, OBJ_WORMHOLE0, WORMHOLEMOVE,	//OBJ_WORMHOLE

	false, 1, 0 * _2X, 0 * _2X, -8 * _2X, -16 * _2X, TSIZE, TSIZE, 0, NULL, NULL,	//OBJ_FLOWER
	false, 1, 0 * _2X, 0 * _2X, -8 * _2X, -16 * _2X, TSIZE, TSIZE, 0, NULL, NULL,	//OBJ_GOLD

	false, 1, 0 * _2X, 0 * _2X, -8 * _2X, -16 * _2X, TSIZE, TSIZE, 0, NULL, NULL,	//OBJ_TREE
	false, 1, 0 * _2X, 0 * _2X, -8 * _2X, -16 * _2X, TSIZE, TSIZE, 0, NULL, NULL,	//OBJ_FLAG

};


const unsigned short mapBg[TOTALMAPTYPE * 4] = {
	//0 : width
	//1 : height
	//2 : 반전이미지 여부(1:원본대로 2:반전으로)
	//3 :

	48 * _2X, 255 * _2X, 96 * _2X, 240 * _2X,		//톨렘마을 바깥
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,					//톨렘마을 집안
	128 * _2X, 240 * _2X, 128 * _2X, 228 * _2X,	//톨레아 습지
	128 * _2X, 216 * _2X, 128 * _2X, 216 * _2X,	//금단의 계곡
	128 * _2X, 224 * _2X, 128 * _2X, 224 * _2X,	//아틀란티스
	128 * _2X, 205 * _2X, 128 * _2X, 0 * _2X,		//아델라인 지하도
	128 * _2X, 176 * _2X, 128 * _2X, 0 * _2X,		//아델라인 성
	128 * _2X, 207 * _2X, 128 * _2X, 0 * _2X,		//아델 평원
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//벨로네 마을
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//홍염의 대지
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//유구한 빙원
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//뇌전의 공방
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//황혼의 성역
	128 * _2X, 202 * _2X, 128 * _2X, 202 * _2X,	//골렘의 협곡
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//칠흑의 심연
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//드래곤의 무덤
	128 * _2X, 205 * _2X, 128 * _2X, 208 * _2X,	//금지된 땅
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//마왕성
	128 * _2X, 208 * _2X, 128 * _2X, 208 * _2X,	//우주공간
};

const signed short waterfallMI[12 * 4] = {
	//BG_WATERFALL_SPLASH0
	IMG_ATLANTICE_5, -16 * _2X, -32 * _2X, N00E0X1,	//0
	IMG_ATLANTICE_13, -20 * _2X, -40 * _2X, N00T0X1,	//1

	//BG_WATERFALL_SPLASH1
	IMG_ATLANTICE_7, -14 * _2X, -26 * _2X, N00E0X1,	//2
	IMG_ATLANTICE_12, -20 * _2X, -30 * _2X, N00T1X1,	//3

	//BG_WATERFALL_SPLASH2
	IMG_ATLANTICE_6, -13 * _2X, -29 * _2X, N00E0X1,	//4
	IMG_ATLANTICE_11, -15 * _2X, -8 * _2X, N00T2X1,	//5

	//BG_WATERFALL_SPLASH3
	IMG_ATLANTICE_13, -20 * _2X, -40 * _2X, N00T0X1,	//6
	IMG_ATLANTICE_17, -6 * _2X, -28 * _2X, N00E0X1,	//7

	//BG_WATERFALL_SPLASH4
	IMG_ATLANTICE_18, -7 * _2X, -25 * _2X, N00E0X1,	//8
	IMG_ATLANTICE_12, -20 * _2X, -30 * _2X, N00T1X1,	//9

	//BG_WATERFALL_SPLASH5
	IMG_ATLANTICE_19, -6 * _2X, -28 * _2X, N00E0X1,	//10
	IMG_ATLANTICE_11, -15 * _2X, -8 * _2X, N00T2X1,	//11
};

const unsigned short atlanticeImg[4 * TOTALATLANTICEIMG] = {
	//BMP : C:\SktWipi\Projects\Mos5\Resource\water.bmp
	48 * _2X, 50 * _2X, 33 * _2X, 12 * _2X,	//0
	48 * _2X, 62 * _2X, 30 * _2X, 10 * _2X,	//1
	48 * _2X, 12 * _2X, 31 * _2X, 9 * _2X,	//2
	48 * _2X, 21 * _2X, 30 * _2X, 11 * _2X,	//3
	48 * _2X, 32 * _2X, 25 * _2X, 18 * _2X,	//4
	0 * _2X, 115 * _2X, 30 * _2X, 14 * _2X,	//5
	30 * _2X, 115 * _2X, 24 * _2X, 9 * _2X,	//6
	54 * _2X, 115 * _2X, 26 * _2X, 8 * _2X,	//7
	50 * _2X, 123 * _2X, 30 * _2X, 14 * _2X,	//8
	26 * _2X, 128 * _2X, 24 * _2X, 9 * _2X,	//9
	0 * _2X, 129 * _2X, 26 * _2X, 8 * _2X,	//10
	48 * _2X, 0 * _2X, 28 * _2X, 10 * _2X,	//11
	39 * _2X, 84 * _2X, 38 * _2X, 18 * _2X,	//12
	0 * _2X, 102 * _2X, 39 * _2X, 13 * _2X,	//13
	48 * _2X, 72 * _2X, 28 * _2X, 10 * _2X,	//14
	0 * _2X, 84 * _2X, 38 * _2X, 18 * _2X,	//15
	39 * _2X, 102 * _2X, 39 * _2X, 13 * _2X,	//16
	42 * _2X, 115 * _2X, 12 * _2X, 9 * _2X,	//17
	54 * _2X, 115 * _2X, 13 * _2X, 7 * _2X,	//18
	30 * _2X, 116 * _2X, 12 * _2X, 8 * _2X,	//19
};

const unsigned short swampImg[4 * TOTALSWAMPIMG] = {
	//BMP : C:\SktWipi\Projects\Mos5\Resource\bg2.bmp
	124 * _2X, 161 * _2X, 33 * _2X, 12 * _2X,	//0
	94 * _2X, 161 * _2X, 30 * _2X, 10 * _2X,	//1
	139 * _2X, 90 * _2X, 31 * _2X, 9 * _2X,	//2
	140 * _2X, 99 * _2X, 30 * _2X, 11 * _2X,	//3
	108 * _2X, 111 * _2X, 25 * _2X, 18 * _2X,	//4
	94 * _2X, 171 * _2X, 16 * _2X, 12 * _2X,	//5
	110 * _2X, 171 * _2X, 16 * _2X, 12 * _2X,	//6
	70 * _2X, 143 * _2X, 16 * _2X, 13 * _2X,	//7
	85 * _2X, 129 * _2X, 28 * _2X, 8 * _2X,	//8
	85 * _2X, 137 * _2X, 28 * _2X, 8 * _2X,	//9
	138 * _2X, 80 * _2X, 32 * _2X, 10 * _2X,	//10
	126 * _2X, 173 * _2X, 22 * _2X, 10 * _2X,	//11
	88 * _2X, 120 * _2X, 21 * _2X, 9 * _2X,	//12
};

const signed char swampSplash[14 * 4] = {
	//WAVE
	IMG_SWAMP_WAVE1, -21 * _2X, -12 * _2X, -14 * _2X,
	IMG_SWAMP_WAVE2, -20 * _2X, -10 * _2X, -14 * _2X,
	IMG_SWAMP_WAVE1, -21 * _2X, -12 * _2X, -16 * _2X,
	IMG_SWAMP_WAVE2, -20 * _2X, -10 * _2X, -15 * _2X,
	IMG_SWAMP_WAVE1, -21 * _2X, -12 * _2X, -14 * _2X,
	IMG_SWAMP_WAVE2, -20 * _2X, -10 * _2X, -15 * _2X,

	//SPLASH
	IMG_SWAMP_SPLASH3, -17 * _2X, -7 * _2X, -25 * _2X,
	IMG_SWAMP_SPLASH2, -21 * _2X, -9 * _2X, -16 * _2X,
	IMG_SWAMP_SPLASH1, -22 * _2X, -10 * _2X, -14 * _2X,

	//BUBBLE
	IMG_SWAMP_BUBBLE1, -14 * _2X, -6 * _2X, 0 * _2X,
	IMG_SWAMP_BUBBLE2, -14 * _2X, -5 * _2X, 0 * _2X,
	IMG_SWAMP_BUBBLE3, -16 * _2X, -7 * _2X, 0 * _2X,
	IMG_SWAMP_BUBBLE4, -11 * _2X, -9 * _2X, 0 * _2X,
	IMG_SWAMP_BUBBLE5, -10 * _2X, -12 * _2X, 0 * _2X,
};

const unsigned char swampBubble[4 * TOTALBUBBLE] = {
	//10 * _2X, 32 * _2X, 112
	10 * _2X, 12 * _2X, 30 * _2X, 0 * _2X,	//48 * _2X, 120
	10 * _2X, 18 * _2X, 31 * _2X, 2 * _2X,	//72 * _2X, 124
	10 * _2X, 15 * _2X, 29 * _2X, 4 * _2X,	//60 * _2X, 116
	10 * _2X, 20 * _2X, 30 * _2X, 6 * _2X,	//80 * _2X, 120

	//11 * _2X, 32 * _2X, 112
	11 * _2X, 12 * _2X, 31 * _2X, 0 * _2X,	//48 * _2X, 124
	11 * _2X, 16 * _2X, 29 * _2X, 3 * _2X,	//64 * _2X, 116
	11 * _2X, 13 * _2X, 30 * _2X, 6 * _2X,	//52 * _2X, 120

	//11 * _2X, 144 * _2X, 160
	11 * _2X, 39 * _2X, 43 * _2X, 7 * _2X,	//160 * _2X, 172
	11 * _2X, 44 * _2X, 41 * _2X, 2 * _2X,	//176 * _2X, 164
	11 * _2X, 42 * _2X, 42 * _2X, 5 * _2X,	//168 * _2X, 168

	//11 * _2X, 272 * _2X, 128
	11 * _2X, 71 * _2X, 35 * _2X, 1 * _2X,	//288 * _2X, 140
	11 * _2X, 76 * _2X, 33 * _2X, 4 * _2X,	//304 * _2X, 132
	11 * _2X, 74 * _2X, 34 * _2X, 7 * _2X,	//296 * _2X, 136

	//11 * _2X, 384 * _2X, 128
	11 * _2X, 99 * _2X, 34 * _2X, 2 * _2X,	//400 * _2X, 140
	11 * _2X, 104 * _2X, 33 * _2X, 5 * _2X,	//416 * _2X, 132
	11 * _2X, 102 * _2X, 35 * _2X, 0 * _2X,	//408 * _2X, 136

	//12 * _2X, 32 * _2X, 112
	12 * _2X, 12 * _2X, 26 * _2X, 0 * _2X,	//48 * _2X, 120
	12 * _2X, 24 * _2X, 25 * _2X, 1 * _2X,	//96 * _2X, 116
	12 * _2X, 18 * _2X, 27 * _2X, 2 * _2X,	//72 * _2X, 124
	12 * _2X, 15 * _2X, 25 * _2X, 4 * _2X,	//60 * _2X, 116
	12 * _2X, 22 * _2X, 27 * _2X, 5 * _2X,	//88 * _2X, 124
	12 * _2X, 20 * _2X, 26 * _2X, 6 * _2X,	//80 * _2X, 120

	//12 * _2X, 208 * _2X, 96
	12 * _2X, 56 * _2X, 26 * _2X, 0 * _2X,	//224 * _2X, 104
	12 * _2X, 62 * _2X, 27 * _2X, 2 * _2X,	//248 * _2X, 108
	12 * _2X, 59 * _2X, 25 * _2X, 4 * _2X,	//236 * _2X, 100
	12 * _2X, 64 * _2X, 26 * _2X, 6 * _2X,	//256 * _2X, 104

	//13 * _2X, 32 * _2X, 192
	13 * _2X, 12 * _2X, 51 * _2X, 0 * _2X,	//48 * _2X, 204
	13 * _2X, 16 * _2X, 49 * _2X, 3 * _2X,	//64 * _2X, 196
	13 * _2X, 13 * _2X, 50 * _2X, 6 * _2X,	//52 * _2X, 200

	//18 * _2X, 160 * _2X, 288
	18 * _2X, 44 * _2X, 74 * _2X, 0 * _2X,	//192 * _2X, 296
	18 * _2X, 50 * _2X, 75 * _2X, 2 * _2X,	//216 * _2X, 300
	18 * _2X, 47 * _2X, 73 * _2X, 4 * _2X,	//204 * _2X, 292
	18 * _2X, 52 * _2X, 74 * _2X, 6 * _2X,	//224 * _2X, 296

	//19 * _2X, 176 * _2X, 272
	19 * _2X, 48 * _2X, 70 * _2X, 0 * _2X,	//208 * _2X, 280
	19 * _2X, 54 * _2X, 71 * _2X, 2 * _2X,	//232 * _2X, 284
	19 * _2X, 51 * _2X, 69 * _2X, 4 * _2X,	//220 * _2X, 276
	19 * _2X, 56 * _2X, 70 * _2X, 6 * _2X,	//240 * _2X, 280

	//23 * _2X, 208 * _2X, 256
	23 * _2X, 68 * _2X, 66 * _2X, 0 * _2X,	//272 * _2X, 264
	23 * _2X, 74 * _2X, 67 * _2X, 2 * _2X,	//296 * _2X, 268
	23 * _2X, 71 * _2X, 65 * _2X, 4 * _2X,	//284 * _2X, 260
	23 * _2X, 76 * _2X, 66 * _2X, 6 * _2X,	//304 * _2X, 264
};

const signed char sunShineMotion[48] = {
	SUNSHINE0,
	SUNSHINE1,
	SUNSHINE2,
	SUNSHINE3,
	SUNSHINE4,
	SUNSHINE5,
	SUNSHINE6,
	SUNSHINE6,
	SUNSHINE7,
	SUNSHINE8,
	SUNSHINE9,
	SUNSHINE6,
	SUNSHINE10,
	SUNSHINE10,
	SUNSHINE11,
	SUNSHINE12,
	SUNSHINE8,
	SUNSHINE13,
	SUNSHINE6,
	SUNSHINE10,
	SUNSHINE10,
	SUNSHINE13,
	SUNSHINE14,
	SUNSHINE15,

	SUNSHINE2_0,
	SUNSHINE2_1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	SUNSHINE2_2,
	SUNSHINE2_3,
	-1,
	-1,
	-1,
	-1,
	-1,
	SUNSHINE2_2,
	SUNSHINE2_3,
	-1,
	-1,
	-1,
	-1,
	-1,
	SUNSHINE2_4,
	SUNSHINE2_5,
};

const unsigned char sewageFallHeight[10] = {
	//넓은 폭포
	78 * _2X, 100 * _2X, 111 * _2X, 88 * _2X, 85 * _2X,

	//좁은 폭포
	77 * _2X, 62 * _2X, 79 * _2X, 72 * _2X, 94 * _2X,
};


const unsigned char tileEmpty[19 * MAXTILECOUNT] = {
	//t0.png
	1, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 1, 1,
	1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0,

	//t1.png
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t2.png
	1, 1, 1, 1, 0, 0, 0, 1,
	0, 0, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t3.png
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t4.png
	1, 1, 1, 1, 1, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 0, 1, 0, 0,
	1, 1, 1, 0, 0, 1, 0, 0,
	0, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t5.png
	1, 1, 0, 1, 0, 0, 0, 1,
	0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 1, 0, 0,
	1, 1, 1, 0, 0, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 0,
	0, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t6.png
	1, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 0, 0, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t7.png
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t8.png
	1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 0, 1, 0, 0,
	1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t9.png
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 0, 1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 1, 1,
	0, 0, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t10.png
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 0, 0, 1, 0, 0,
	0, 0, 1, 0, 0, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t11.png
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 0, 0, 1, 0, 0,
	1, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 1, 1, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t12.png
	1, 1, 1, 1, 0, 1, 0, 0,
	1, 1, 1, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t13.png
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t14.png
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t15.png
	1, 1, 0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t16.png
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t17.png
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 1,
	0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	//t18.png
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 1,
	0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};
#endif