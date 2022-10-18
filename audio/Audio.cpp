﻿#include "Audio.h"
#include <Windows.h>
#include <cassert>
#include <fstream>


Audio* Audio::GetInstance()
{
	static Audio instance;

	return &instance;
}

bool Audio::Initialize(const std::string& directoryPath)
{

	directoryPath_ = directoryPath;

	HRESULT result;
	IXAudio2MasteringVoice* masterVoice;

	// XAudioエンジンのインスタンスを生成
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if FAILED(result)
	{
		assert(0);
		return false;
	}

	// マスターボイスを生成
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	if FAILED(result)
	{
		assert(0);
		return false;
	}

	return true;
}

void Audio::Finalize()
{
	//XAudio2解放
	xAudio2.Reset();
	//音声データ解放
	std::map<std::string, SoundData>::iterator it = soundDatas_.begin();
	for (; it != soundDatas_.end(); ++it)
	{
		Unload(&it->second);
	}
	soundDatas_.clear();
}

void Audio::LoadWave(const std::string& filename)
{
	if (soundDatas_.find(filename) != soundDatas_.end())
	{
		//重複読み込みなので、何もせず抜ける
		return;
	}

	//ディレクトリパスとファイル名を連結してフルパスを得る
	std::string fullpath = directoryPath_ + filename;

	// ファイルストリーム
	std::ifstream file;
	// Waveファイルをバイナリモードで開く
	file.open(fullpath, std::ios_base::binary);
	// ファイルオープン失敗を検出する
	assert(file.is_open());

	// RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
	{
		assert(0);
	}
	// ファイルがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0)
	{
		assert(0);
	}

	// Formatチャンクの読み込み
	FormatChunk format = {};
	file.read((char*)&format, sizeof(ChunkHeader));

	if (strncmp(format.chunk.id, "fmt ", 4) != 0)
	{
		assert(0);
	}

	// チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	//Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0)
	{
		//読み取り位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));
	}

	// LISTチャンクを検出した場合
	if (strncmp(data.id, "LIST", 4) == 0)
	{
		//読み取り位置をLISTチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data ", 4) != 0)
	{
		assert(0);
	}

	//Dataチャンクのデータ部 (波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	// Waveファイルを閉じる
	file.close();

	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	//サウンドデータを連想配列に格納
	soundDatas_.insert(std::make_pair(filename, soundData));
}

void Audio::Unload(SoundData* soundData)
{
	//バッファのメモリを解放
	delete[] soundData->pBuffer;

	soundData->wfex = {};
	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
}

void Audio::CreateSoundData(SoundData& soundData)
{
	HRESULT result;
	//波形フォーマットを元にSourceVoiceの生成
	result = xAudio2->CreateSourceVoice(&soundData.pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));
}

void Audio::PlayWave(const std::string& filename, float volume, bool LoopFlag)
{
	HRESULT result;

	std::map<std::string, SoundData>::iterator it = soundDatas_.find(filename);
	//未読み込みの検出
	assert(it != soundDatas_.end());
	//サウンドデータの参照を取得
	SoundData& soundData = it->second;

	if (soundData.playNowFlag == true)
	{
		return;
	}

	CreateSoundData(soundData);

	//再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	if (LoopFlag)
	{
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	//波形データの再生
	result = soundData.pSourceVoice->SubmitSourceBuffer(&buf);
	result = soundData.pSourceVoice->SetVolume(volume);
	result = soundData.pSourceVoice->Start();

	//再生確認フラグの確認
	if (soundData.playNowFlag == false)
	{
		soundData.playNowFlag = true;
	}

}

void Audio::SoundStop(const std::string& filename)
{
	std::map<std::string, SoundData>::iterator it = soundDatas_.find(filename);
	//未読み込みの検出
	assert(it != soundDatas_.end());
	//サウンドデータの参照を取得
	SoundData& soundData = it->second;

	if (soundData.playNowFlag == false)
	{
		return;
	}

	soundData.pSourceVoice->Stop(0);
	soundData.pSourceVoice->FlushSourceBuffers();
	soundData.pSourceVoice->SubmitSourceBuffer(&buf);

	soundData.playNowFlag = false;
}
