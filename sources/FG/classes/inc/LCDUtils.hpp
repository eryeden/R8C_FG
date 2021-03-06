//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : LCDUtils.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_LCDUTILS_H)
#define _LCDUTILS_H


// Vo 0.6 V くらい

/*
	データ書き込み流れ
	＃１　RSを設定、RWをLにする
	＃２　EをHにする
	＃３　データバスを設定する
	＃４　EをLにし、RS、RWを戻す
	＃５　待つ

	4bitモードの時
	＃１　RSを設定、RWをLにする
	＃２　書き込み上位４ビットの設定
	＃３　EをON、待ってからOFFにする
	＃４　書き込み下位4ビットの設定
	＃５　EをON、待ってからOFFにする
*/

class LCDUtils {
public:
	LCDUtils();
	void Initialize();
	void Write(unsigned char in);
	void WriteLineUp(char src[16]);
	void WriteLineDown(char src[16]);
	void Clear();
	void Test();
	void SetCursor(unsigned char x, unsigned char y);
	void WriteNumber(unsigned int num);
	void WriteNumber2(unsigned int num, unsigned char scale);
	void WriteNumber6(unsigned int num);
	void WriteString(const char *in);
	void EnableCursor(bool is_cursor_on);
private:

	void WriteData(unsigned char in);
	void WriteCommand(unsigned char in);
	void WriteInit(unsigned char in);

};

#endif  //_LCDUTILS_H
