# SGDK_CJK
<p>
	<strong>1988年10月29日，世嘉MEGA DRIVE发售，首先祝贺MEGA DRIVE的36周岁生日🎂！</strong> 
</p>
<p>
	SGDK_CJK是一个基于SGDK开发套件的实现多语言显示的世嘉Mega Drive游戏框架。命名为CJK是因为最初计划只是在SGDK中实现中日韩统一表意文字的显示，不过后来又加入了对其他各国语言和表情符号的支持，理论上可以显示Shift-JIS(cp932)、GBK(cp936)、KS_C(cp949)、Big5(cp950)代码页的所有双字节全宽字符和UTF-8(cp65001)代码页中Unicode范围在0000~FFFF的所有从左向右书写的半宽字符，以及最大255个额外的自定义字符和最大255个自定义彩色表情图标。
</p>
<strong><span style="font-size:14px;">SGDK</span><span style="font-size:14px;"></span><span style="font-size:14px;">使用方法</span></strong><br />
<p>
	SGDK开发套件的部署和相关说明请参照：https://github.com/Stephane-D/SGDK
</p>
<p>
	<strong><span style="font-size:14px;">SGDK_CJK</span><span style="font-size:14px;"></span><span style="font-size:14px;">函数</span></strong> 
</p>
<strong>VDP_drawTextCJK</strong><strong>(VDPPlane plane, u8 palette, u8 backColor, unsigned char *text, int tileIndex, u8 x, u8 y, u8 w) </strong>绘制文本<br />
plane：显示平面（BG_A、BG_B、WINDOW）<br />
palette：调色盘（PAL0、PAL1、PAL2、PAL3）<br />
backColor：背景色在调色盘中的序号<br />
text：显示文本<br />
x：y：显示坐标（以左上角为基准，以tile为单位）<br />
w：显示宽度（以tile为单位）<br />
getLanguage(u8 lang) 设置当前语言<br />
lang：语言代码，预设支持以下6种语言<br />
zh_CN：简体中文；zh_HK：繁体中文；ja_JP：日文；ko_KR：韩文；en_US：英文；ru_RU：俄文<br />
可参考预设文件，自行在\src\localization目录添加其他语言，并在\src\language.c中包含头文件#include “localization/*.h”<br />
<strong>getString(u8 index)&nbsp;</strong>获取当前语言字符串<br />
index：字符串序号<br />
<strong>getStringEx(u8 lang, u8 index)</strong> 获取指定<span>语言</span>字符串<br />
lang：语言代码<br />
index：字符串序号<br />
<p>
	在\src\localization目录对应的*.c文件中可以编辑字符串数组，需要使用对应语言的代码页打开文件。
</p>
<p>
	<span style="font-size:14px;"><strong>控制字符</strong></span> 
</p>
在文本中插入以下控制字符可以实现一些特殊功能<br />
<strong>/0</strong>：空字符<br />
<strong>/n</strong>：换行回车<br />
<strong>/a</strong>：/a/x01-/a/xff 额外的自定义字符<br />
<strong>/e</strong>：/e/x01-/e/xff 彩色表情图标字符<br />
<strong>/t</strong>：水平制表符<br />
<strong>/v</strong>：垂直制表符<br />
<strong>/f</strong>：/f0-/f5 切换代码页，依次为UTF-8(cp65001)、Shift-JIS(cp932)、GBK(cp936)、KS_C(cp949)、Big5(cp950)，/f 切换代码页为当前语言默认代码页<br />
<strong>/r</strong>：/r0-/rf 切换文本颜色（调色盘序号15-0倒序）， /r 切换文本颜色为默认颜色（调色盘序号15）<br />
<p>
	<strong>/b</strong>：回退光标，使用“/f”和“/r”时，如果产生多余的空格，可以使用“/b”进行调整
</p>
<p>
	<span style="font-size:14px;"><strong>授权许可</strong></span> 
</p>
使用 「MIT 许可证」 授权。<br />
<p>
	虽然不强制，但是使用了SGDK_CJK的游戏项目，在正式发布时，希望能发一份拷贝给我
</p>
<p>
	<span style="font-size:14px;"><strong>配套工具</strong></span> 
</p>
有两个生成字符dat文件的小工具放在\tool目录<br />
SGDK_CJK用于生成常规字体文件<br />
SGDK_CJK_EX用于生成额外的附加字符和表情图标<br />
生成后的dat文件放到\res\font目录替换原文件<br />
<p>
	游戏开发调试时可直接使用预设字符dat文件，正式发布前建议重新生成dat文件，使用“Identify From Files”筛选游戏项目中实际使用的字符，并取消勾选“Anti-Overflow”选项，以节省空间
</p>
<p>
	<span style="font-size:14px;"><strong>点阵字体</strong></span> 
</p>
预设字符dat文件使用缝合像素字体12px生成<br />
<p>
	缝合像素字体 / Fusion Pixel Font：https://github.com/TakWolf/fusion-pixel-font
</p>
<p>
	<span style="font-size:14px;"><strong>表情图标</strong></span> 
</p>
预设字符文件中的示例表情图标参考了Google Noto Color Emoji（2008）<br />
仅供功能演示使用，请不要用在正式的游戏项目中<br />
