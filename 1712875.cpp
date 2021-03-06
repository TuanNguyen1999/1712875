// 1712875.cpp -- executing file
//
//bước 1: lấy dữ liệu từ file csv (lưu ý định dạng csv phải là utf-8, sử dụng struct) đồng thời tính số sinh viên
//bước 2: từ bước 1 tạo mảng động của n sinh viên, đưa dữ liệu mỗi sinh viên vào từng phần tử
	//dùng locale và codecvt_utf8 để chuyển đổi giữa utf8 và chuỗi wide rồi imbue vào filebuffer
	//dùng stringbuffer để nhận dữ liệu từ filebuffer rồi từ đó truyền vô chuỗi
	//(nếu truyền thẳng lại bị lỗi kí tự khi xuất ra file htm???)
//bước 3: mỗi sinh viên tạo 1 file htm
	//trước khi truyền dữ liệu vào file nhớ imbue(locale(locale::empty(),codecvt_utf8<wchar_t>))
	//để kí tự xuất vào file từ chuỗi wide thành các kí tự có encoding UTF-8
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
		wcout << L"File not found!\n";
		return 0;
	case UNKNOW_ERROR:
		wcout << L"Unknown error happened!\n";
		return 0;
	case 0: default:
		wcout << L"Hoàn tất\n\n";
		break;
	}
	int soSinhVien = SoDong(fileEdited);
	Data* duLieu = LayThongTin(fileEdited, soSinhVien);
	wstring form = folder + L"form.htm";
	wcout << L"Nhận được " << soSinhVien << L" sinh viên\n";
	wcout << L"Nhận dữ liệu sinh viên và đưa vào file htm:\n";
	wcout << L"Working...\n";
	wstring sentinel;
	wstring fileSinhVien;
	int dem = 0;
	for (int i = 0; i < soSinhVien; i++) {
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
		L"please change font to consolas.\n";
	delete[] duLieu;
	system("pause");
	return 0;
}

