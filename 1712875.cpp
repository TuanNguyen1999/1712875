// 1712875.cpp : Defines the entry point for the console application.
//
//buoc 1: extract csv file --> dung getline(cin, string, delimiter= ',') dua vao struct theo thu tu xac dinh truoc
	//buoc 1.1: chuyen tu excel -> text unicode -> save voi duoi .csv + encoding UTF-8
	//buoc 1.2: trich toan bo file csv vao chuoi
//buoc 2: viet ham tim vi tri cac tag can dien vao thong tin cua sinh vien -->int findTag(string tag, fstream& file)
//buoc 3: lam moi file html --> xoa het cac thong tin cua sinh vien truoc do (neu co)
//buoc 4: dua thong tin cua sinh vien moi vao file html o buoc 3
//buoc 5: nop do an va qua?y
#include "stdafx.h"
#include "Declare.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
using namespace std;
const wstring folder = L"WEBSITE\\";
int main()
{
	wstring TepCSV = L"Sinhviên.csv";
	wstring fileEdited = L"New_SinhViên.csv";
	int error = ChinhSua(TepCSV, fileEdited);
	switch (error) {
	case DONT_EXISTS:
		cout << "File not found!\n";
		break;
	case UNKNOW_ERROR:
		cout << "Unknown error happened!\n";
		break;
	case 0: default:
		break;
	}
	Data* duLieu = LayThongTin(fileEdited);
	wofstream wf;
	int soDong = DemKiTu(L'\n', fileEdited) + 1; // dong ket thuc ko co '\n'
	wstring form = folder + L"form.htm";
	wstring sentinel;
	int dem = 0;
	for (int i = 0; i < soDong; i++) {
		wstring fileSinhVien;
		if (duLieu[i].MSSV == L"NULL") {
			fileSinhVien = folder + L"NULL(" + to_wstring(++dem) + wstring(L").htm");
		}
		else {
			fileSinhVien = folder + duLieu[i].MSSV + wstring(L".htm");
		}
		wf.open(fileSinhVien);
		DuaVaoChuoi(form, sentinel);
		SinhVien(sentinel, duLieu[i]);
		wf << sentinel;
		wf.close();
	}
	/*wf.open(L"text.txt");
	for (int i = 0; i < soDong; i++) {
		wf << duLieu[i].MSSV << endl;
		wf << duLieu[i].HoTen << endl;;
		wf << duLieu[i].Nganh << endl;;
		wf << duLieu[i].NienKhoa << endl;
		wf << duLieu[i].NgaySinh << endl;
		wf << duLieu[i].HinhAnh << endl;
		wf << duLieu[i].MoTa << endl;
		wf << duLieu[i].Email << endl;
		wf << duLieu[i].SoThich << endl;
		wf << endl;
	}
	wf.close();*/
	
	return 0;
}

