#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS  1
#endif
#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

class FormClass {
private: 
	BOOL async_loop;
	DWORD CreateNewConsole(console* con);
	void OnKeyDown(WORD key);
protected: 
	HANDLE hout, hin;
	short width;
	short height;
	usefullist carr;
public:
	FormClass(void);
	DWORD CreateMainForm(void);         //c������� �������� �����
	DWORD AddBuffer(void);              //���������� ��������������� ������
	static WORD GetKey(HANDLE hin);     //���� ��������� �� ����������
	BOOL writeText(LPCWSTR str, short x, short y, DWORD len);
	void writeText(LPCSTR str, int len, short x, short y, WORD color); //����� ������ �� ��������� �������
	void drawRect(short x1, short y1, short x2, short y2, WORD color); //����� ��������������
	void drawRect(const SMALL_RECT& rc, WORD color);
	void drawCharRect(CHAR ch, short x1, short y1, short x2, short y2); //����� �������������� �� ��������
	void drawFrame(short x1, short y1, short x2, short y2, WORD color); //����� ����� ��������������
	void drawFrame(const SMALL_RECT& rc, WORD color);
	void fillChar(CHAR ch, const SMALL_RECT& rc); //������� ��������� ��������������
	BOOL fillChar(CHAR ch, short x, short y, DWORD len);
	BOOL fillAttribute(WORD color, short x, short y, DWORD len); //������� ����������
	void  setBufferSize(short new_width, short new_height); //������������� ������ ������ �������
	BOOL setWindowSize(SMALL_RECT& rc, BOOL absolute); //������������� ������ ���� �������
	SMALL_RECT getWindowSize(void) const;  //���������� ������� ������ ���� �������
	BOOL Reset(void); //������� �������
	short getWidth(void) const;  // ������ ������ �������
	short getHeight(void) const; // ������ ������ �������
	HANDLE getInput(void) const; //��������� �� ����� �����
	HANDLE getOutput(void) const; // ��������� �� ����� ������
};

