//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : SSUbus.cpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#include "SSUbus.hpp"
#include "sfr_r829.h"

/*
	MCP4921について
	立ち上りエッジで読み込み
	書き込み時は〜CSピンをLOW
	図的にMSBファースト
	奇数エッジでデータ変化させる、つまり立ち上がりエッジで読み込ませる
	クロック停止時、SCK=Hになっているがこれでいいのか
*/


SSUbus::SSUbus(unsigned char mode){
	if (mode == MODE_4WIRES){
		Initialize4WiresMode();
	} else if(mode == MODE_SYNCHRONIZED_CLOCK){
		InitializeSynchronizedClockMode();
	} else{
	
	}
}

SSUbus::SSUbus(){
	;
}

void SSUbus::InitializeSynchronizedClockMode(){
	////クロック同期式通信モードの設定を行う　使うのはP3_5, P3_7
	////ピンの設定 使うのを入力にする
	pd3_5 = 0;
	pd3_7 = 0;

	pd3_4 = 1;
	p3_4 = 1;

	//SSUバス動作許可
	//しなくていいらしい

	//SSU/I2C切り替え設定
	iicsel = 0;

	//受信禁止、送信禁止
	sser = 0x00;

	//クロック同期式モードを選択　通信モード選択
	ssums_ssmr2 = 0;

	//MSBファーストに設定, 奇数エッジでデータ変化、クロック停止時SCK=H
	//ssmr = 0x08;
	cphs_ssmr = 0;
	cpos_ssmr = 0;
	mls_ssmr = 0;

	//マスタにする
	mss_sscrh = 1;

	//SSモード選択
	//クロック同期式通信モード
	//ssums_ssmr2 = 0;
	//使わない CMOS出力
	//csos_ssmr2 = 0;
	soos_ssmr2 = 0;
	//〜SCS端子選択　クロック同期式なので自動的にOFFされる
	//css0_ssmr2 = 0;
	//css1_ssmr2 = 0;
	//SCKS端子選択 シリアルクロックとして動作させる
	scks_ssmr2 = 1;
	//双方向モード設定 標準モードにする
	//bide_ssmr2 = 0;

	//転送クロックモードの設定
	//とりあえずf1/256とする
	cks0_sscrh = 1;
	cks1_sscrh = 1;
	cks2_sscrh = 0;
	//使わないがレシーブ継続設定
	rsstp_sscrh = 0;

	//オーバーランエラーフラグ なしに設定
	orer_sssr = 0;

	//送信を許可　受信を禁止に設定
	//re_sser = 0;
	te_sser = 1;
	//ceie_sser = 0; //コンフリクトエラー割り込み禁止
	//rie_sser = 0; //受信、オーバーランエラー割り込み禁止
	//teie_sser = 0; //送信終了割り込み禁止
	//tie_sser = 0; //送信データエンプティ割り込み禁止

	//pd3 = 0xff;
	//pd3_5 = 0;
	//pd3_7 = 0;
	//sser = 0x00;
	//ssums_ssmr2 = 1;//0だとクロック同期式
	//cphs_ssmr = 0;	//クロック変化タイミング設定
	//cpos_ssmr = 0;//クロック変化タイミング設定
	//mls_ssmr = 0;	//MSB fast
	//mss_sscrh = 1;
	//scks_ssmr2 = 1;
	//soos_ssmr2 = 0;//Nモスとかなんとかの設定らしいよくわからん・・・
	//css0_ssmr2 = 0;//この2つはよくわからん．
	//css1_ssmr2 = 0;//00で通常ポート動作
	//bide_ssmr2 = 0;	//1だと双方向モード
	//cks2_sscrh = 0;
	//cks1_sscrh = 0;
	//cks0_sscrh = 0;
	//rsstp_sscrh = 0;
	//char c;
	//c = orer_sssr;//なんか一度読みこまないとならないらしいよ．
	//orer_sssr = 0;

}


void SSUbus::Initialize4WiresMode(){
	//クロック同期式通信モードの設定を行う　使うのはP3_5, P3_7
	//ピンの設定 使うのを入力にする
	pd3_5 = 0;
	pd3_7 = 0;
	pd3_4 = 0;
	
	 

	//SSUバス動作許可
	//しなくていいらしい

	//SSU/I2C切り替え設定
	iicsel = 0;

	//受信禁止、送信禁止
	sser = 0x00;

	//4線モードを選択　通信モード選択
	ssums_ssmr2 = 1;

	//MSBファーストに設定, 奇数エッジでデータ変化、クロック停止時SCK=H
	ssmr = 0x08;

	//マスタにする
	mss_sscrh = 1;

	//SSモード選択
	//4線通信モード
	//ssums_ssmr2 = 1;
	//使わない CMOS出力
	csos_ssmr2 = 0;
	soos_ssmr2 = 0;
	//〜SCS端子選択　４線モードなので入力端子とするが、選択肢が2つあるのでよくわからない
	css0_ssmr2 = 1;
	css1_ssmr2 = 1;
	//SCKS端子選択 シリアルクロックとして動作させる
	scks_ssmr2 = 1;
	//双方向モード設定 標準モードにする
	bide_ssmr2 = 0;

	//転送クロックモードの設定
	//とりあえずf1/256とする
	cks0_sscrh = 1;
	cks1_sscrh = 1;
	cks2_sscrh = 0;
	//使わないがレシーブ継続設定
	rsstp_sscrh = 0;

	//オーバーランエラーフラグ なしに設定
	//char c = orer_sssr;
	orer_sssr = 0;

	//送信を許可　受信を禁止に設定
	re_sser = 0;
	te_sser = 1;
	ceie_sser = 0; //コンフリクトエラー割り込み禁止
	rie_sser = 0; //受信、オーバーランエラー割り込み禁止
	teie_sser = 0; //送信終了割り込み禁止
	tie_sser = 0; //送信データエンプティ割り込み禁止

	//sser = 0x01;
}

//1バイト送信
void SSUbus::WriteByte(unsigned char data) {
	//te_sser = 1;
	
	while (tdre_sssr != 1){ asm("nop"); }; //送信データが送られるまで待つ
	//p1_1 = 1;
	sstdr = data; //データ書き込み
	asm("nop"); //これがちょうどいいらしい　RenesasSSUコードより
	asm("nop");
	asm("nop"); //ここは要調整 #TODO
	
	while (tend_sssr != 1){asm("nop");}; //送信終了までまつ
	tend_sssr = 0;
	//p1_1 = 0;

	//te_sser = 0;

	//te_sser = 1;
	//while (tdre_sssr != 1);
	//sstdr = data;//最後2つもデータ
	//while (tend_sssr != 1);
	//tend_sssr = 0;
	//te_sser = 0;
}

void SSUbus::Write(unsigned char * data, unsigned char bytes) {
	//te_sser = 1;
	//bytes分データを送信
	for (char i = 0; i < bytes; ++i){
		while (tdre_sssr != 1){asm("nop");}; //送信データ移行完了までまつ
		sstdr = data[i]; //送信レジスタにデータ書き込み
		asm("nop"); //これがちょうどいいらしい　RenesasSSUコードより
		asm("nop");
		asm("nop"); //ここは要調整 #TODO
	}
	while (tend_sssr != 1){asm("nop");}; //送信終了までまつ
	tend_sssr = 0;
	//te_sser = 0;
}


void SSUbus::WriteSync(unsigned int word){
	p3_4 = 0;
	while (tdre_sssr != 1){ asm("nop"); }; //送信データ移行完了までまつ
	sstdr = ((unsigned char *)&word)[1]; //送信レジスタにデータ書き込み
	asm("nop"); //これがちょうどいいらしい　RenesasSSUコードより
	asm("nop");
	asm("nop"); //ここは要調整 #TODO

	while (tdre_sssr != 1){ asm("nop"); }; //送信データ移行完了までまつ
	sstdr = ((unsigned char *) &word)[0]; //送信レジスタにデータ書き込み
	asm("nop"); //これがちょうどいいらしい　RenesasSSUコードより
	asm("nop");
	asm("nop"); //ここは要調整 #TODO

	while (tend_sssr != 1){ asm("nop"); }; //送信終了までまつ
	p3_4 = 1;
}

void SSUbus::SInitializeSynchronizedClockMode(){
	////クロック同期式通信モードの設定を行う　使うのはP3_5, P3_7
	////ピンの設定 使うのを入力にする
	pd3_5 = 0;
	pd3_7 = 0;

	pd3_4 = 1;
	p3_4 = 1;

	//SSUバス動作許可
	//しなくていいらしい

	//SSU/I2C切り替え設定
	iicsel = 0;

	//受信禁止、送信禁止
	sser = 0x00;

	//クロック同期式モードを選択　通信モード選択
	ssums_ssmr2 = 0;

	//MSBファーストに設定, 奇数エッジでデータ変化、クロック停止時SCK=H
	//ssmr = 0x08;
	cphs_ssmr = 0;
	cpos_ssmr = 0;
	mls_ssmr = 0;

	//マスタにする
	mss_sscrh = 1;

	//SSモード選択
	//クロック同期式通信モード
	//ssums_ssmr2 = 0;
	//使わない CMOS出力
	//csos_ssmr2 = 0;
	soos_ssmr2 = 0;
	//〜SCS端子選択　クロック同期式なので自動的にOFFされる
	//css0_ssmr2 = 0;
	//css1_ssmr2 = 0;
	//SCKS端子選択 シリアルクロックとして動作させる
	scks_ssmr2 = 1;
	//双方向モード設定 標準モードにする
	//bide_ssmr2 = 0;

	//転送クロックモードの設定
	//とりあえずf1/256とする
	cks0_sscrh = 1;
	cks1_sscrh = 1;
	cks2_sscrh = 0;
	//使わないがレシーブ継続設定
	rsstp_sscrh = 0;

	//オーバーランエラーフラグ なしに設定
	orer_sssr = 0;

	//送信を許可　受信を禁止に設定
	//re_sser = 0;
	te_sser = 1;
	//ceie_sser = 0; //コンフリクトエラー割り込み禁止
	//rie_sser = 0; //受信、オーバーランエラー割り込み禁止
	//teie_sser = 0; //送信終了割り込み禁止
	//tie_sser = 0; //送信データエンプティ割り込み禁止
}

void SSUbus::SWriteSync(unsigned int word){
	p3_4 = 0;
	while (tdre_sssr != 1){ asm("nop"); }; //送信データ移行完了までまつ
	sstdr = ((unsigned char *) &word)[1]; //送信レジスタにデータ書き込み
	asm("nop"); //これがちょうどいいらしい　RenesasSSUコードより
	asm("nop");
	asm("nop"); //ここは要調整 #TODO

	while (tdre_sssr != 1){ asm("nop"); }; //送信データ移行完了までまつ
	sstdr = ((unsigned char *) &word)[0]; //送信レジスタにデータ書き込み
	asm("nop"); //これがちょうどいいらしい　RenesasSSUコードより
	asm("nop");
	asm("nop"); //ここは要調整 #TODO

	while (tend_sssr != 1){ asm("nop"); }; //送信終了までまつ
	p3_4 = 1;
}



