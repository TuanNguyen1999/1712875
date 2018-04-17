#ifndef DECLARE_H
#define DECLARE_H
#include <string>
#include <fstream>
#include <iostream>
using std::wstring;
using std::string;
using std::wifstream;
using std::wofstream;
const int DONT_EXISTS = 2;
const int UNKNOW_ERROR = 1;
const int GOOD = 0;
const int NOT_MATCH = -1;
struct Data {
	wstring MSSV;
	wstring HoTen;
	wstring Nganh;
	int NienKhoa;
	wstring NgaySinh;
	wstring HinhAnh;
	wstring Email;
	wstring MoTa;
	wstring SoThich;
};
//support (co the dung hoac ko)
int ChinhSua(const wstring& fileCu, wstring& fileMoi);//UTF-8 only, file moi ko co khoang trang hoac \n o dau hoac cuoi file
void LamSach(wstring& fileDaChinhSua); //xoa cac khoang trang hoac xuong dong o dau chuoi
int DemKiTu(wchar_t kitu, wstring& fileDaChinhSua); //luu y: so dong = so luong sinh vien => sau nay delete
int DuaVaoChuoi(wstring& filenguon, wstring& chuoidich);
void ChenThongTin(int vitriDau, int& vitriCuoi, const wstring& noiDung, wstring& chuoiHTML);//luu y: viet theo cau truc file html nhat dinh
wstring InHoa(const wstring& chuoi);
wstring Tach(wchar_t kitu, wstring& chuoi, wstring::size_type pos = 0); //tra ra chuoi dung truoc kitu
int TimChuoi(const wstring& ChuoiCanTim, const wstring& chuoi, int pos = 0);//luu y: viet theo cau truc file html nhat dinh
int TimChuoi(wchar_t KiTu, const wstring& chuoi, int pos = 0);//luu y: viet theo cau truc file html nhat dinh
wstring& loai_bo_khoang_trang_nhay_kep(wstring&);
//main
Data* LayThongTin(wstring& fileDaChinhSua);
void XoaNoiDung(wstring& chuoi, int dau, int& cuoi);//xoa noi dung tu dau -> cuoi
void ChenNoiDung(const wstring& chuoiCanChen, wstring& chuoiDuocChen, int pos);
void TaoHTML(wstring& fileHTML, wstring& SinhVien);
int SinhVien(wstring& chuoiHTML,const Data& dulieu);
#endif