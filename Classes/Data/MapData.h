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

extern const unsigned int* mapRectSize;
enum { mapRectSize_COUNT = 425 };

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

extern const unsigned int* mapBackSize;
enum { mapBackSize_COUNT = 425 };

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

extern const unsigned int* mapObjSize;
enum { mapObjSize_COUNT = 425 };

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

extern const unsigned int* mapNeutralSize;
enum { mapNeutralSize_COUNT = 425 };

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

extern const unsigned int* mapEnemySize;
enum { mapEnemySize_COUNT = 425 };


//맵 배경 기본 색상
extern const unsigned int* mapColor;
enum { mapColor_COUNT = 19 };


extern const signed char* doorToKey;
enum { doorToKey_COUNT = 16 };

extern const unsigned char* doorArray;
enum { doorArray_COUNT = 40 };

extern const unsigned char* pushArray;
enum { pushArray_COUNT = 2 };

extern const unsigned char* boxStar;
enum { boxStar_COUNT = 56 };

extern const unsigned char* boxArray;
enum { boxArray_COUNT = 4 };

extern const unsigned char* markArray;
enum { markArray_COUNT = 7 };

extern const unsigned char* itemArray;
enum { itemArray_COUNT = 6 };

extern const unsigned char* dianaStoneArray;
enum { dianaStoneArray_COUNT = 1 };

extern const unsigned char* magmaArray;
enum { magmaArray_COUNT = 1 };

extern const unsigned char* wormHoleArray;
enum { wormHoleArray_COUNT = 3 };

extern const unsigned char* warpArrayType;
enum { warpArrayType_COUNT = 57 };

extern const signed short* warpArray;
enum { warpArray_COUNT = 280 };

extern const unsigned short* backObjImg;
enum { backObjImg_COUNT = 1148 };

extern const unsigned short* bgObjOff;
enum { bgObjOff_COUNT = 656 };

extern const signed short* bgObjMI;
enum { bgObjMI_COUNT = 3220 };

extern const unsigned short* sunShineOff;
enum { sunShineOff_COUNT = 24 };

extern const signed short* sunShineMI;
enum { sunShineMI_COUNT = 504 };

extern const unsigned char* sunShineMIC;
enum { sunShineMIC_COUNT = 44 };

extern const unsigned char sateliteMotionCnt[62];


extern const signed short* neutralData;
enum { neutralData_COUNT = 506 };


extern const unsigned short* mapBg;
enum { mapBg_COUNT = 76 };

extern const signed short* waterfallMI;
enum { waterfallMI_COUNT = 48 };

extern const unsigned short* atlanticeImg;
enum { atlanticeImg_COUNT = 80 };

extern const unsigned short* swampImg;
enum { swampImg_COUNT = 52 };

extern const signed char* swampSplash;
enum { swampSplash_COUNT = 56 };

extern const unsigned char* swampBubble;
enum { swampBubble_COUNT = 164 };

extern const signed char* sunShineMotion;
enum { sunShineMotion_COUNT = 48 };

extern const unsigned char* sewageFallHeight;
enum { sewageFallHeight_COUNT = 10 };


extern const unsigned char* tileEmpty;
enum { tileEmpty_COUNT = 1672 };
#endif