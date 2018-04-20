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
using namespace std;
const wstring folder = L"WEBSITE\\";
int main()
{
	_setmode(_fileno(stdout), _O_WTEXT);//for console ouput
	wstring TepCSV = L"SinhViên.csv";
	wstring fileEdited = L"New_SinhViên.csv";
	wcout << L"Nhận được file " << TepCSV << endl;
	wcout << L"Chỉnh sửa và tạo file mới: " << fileEdited << endl;
	int error = ChinhSua(TepCSV, fileEdited);
	switch (error) {
	case DONT_EXISTS:
		cout << "File not found!\n";
		return 0;
	case UNKNOW_ERROR:
		cout << "Unknown error happened!\n";
		return 0;
	case 0: default:
		wcout << L"Hoàn tất\n\n";
		break;
	}
	Data* duLieu = LayThongTin(fileEdited);
	int soDong = DemKiTu(L'\n', fileEdited) + 1; // dong ket thuc ko co '\n'
	wstring form = folder + L"form.htm";
	wcout << L"Nhận được " << soDong << L" sinh viên\n";
	wcout << L"Nhận dữ liệu sinh viên và đưa vào file htm:\n";
	wcout << L"Working...\n";
	wstring sentinel;
	wstring fileSinhVien;
	int dem = 0;
	for (int i = 0; i < soDong; i++) {
		wcout << L"MSSV: " << duLieu[i].MSSV << endl;
		wcout << L"Họ và tên: " << duLieu[i].HoTen << endl;;
		wcout << L"Ngành: " << duLieu[i].Nganh << endl;;
		wcout << L"Niên khóa: " << duLieu[i].NienKhoa << endl;
		wcout << L"Ngày sinh: " << duLieu[i].NgaySinh << endl;
		wcout << L"Hình ảnh: " << duLieu[i].HinhAnh << endl;
		wcout << L"Mô tả: " << duLieu[i].MoTa << endl;
		wcout << L"Email: " << duLieu[i].Email << endl;
		wcout << L"Sở thích: " << duLieu[i].SoThich << endl;
		if (duLieu[i].MSSV == L"NULL") {
			fileSinhVien = folder + L"NULL(" + to_wstring(++dem) + wstring(L").htm");
		}
		else {
			fileSinhVien = folder + duLieu[i].MSSV + wstring(L".htm");
		}
		wcout << L"Khởi tạo file " << fileSinhVien << L"..." << endl;
		DuaVaoChuoi(form, sentinel);
		SinhVien(sentinel, duLieu[i]);
		TaoHTML(fileSinhVien, sentinel);
		wcout << L"Khởi tạo thành công\n" << endl;
	}
	wcout << L"Done...\n";
	wcout << L"Vui lòng mở thư mục Website để kiểm tra.\n";
	wcout << L"Lưu ý nếu kí tự xuất ra console có dấu \"?\", \"♠\", \"□\" hoặc tương tự\n"
		L"vui lòng đổi font thành consolas.\n";
	delete[] duLieu;
	system("pause");
	return 0;
}

