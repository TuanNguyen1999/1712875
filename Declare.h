#ifndef DECLARE_H
#define DECLARE_H
#include <string>
#include <fstream>
#include <iostream>
#include <io.h>	//_setmode for console output
#include <fcntl.h>// _O_WTEXT -- Wide character mode
#include <locale> //change charset to utf-8 for file output
#include <codecvt> //std::codecvt_utf8<wchar_t> --  //conversion between wide character and utf-8
#include <sstream> //string buffer to recieve file buffer
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
int DuaVaoChuoi(wstring& filenguon, wstring& chuoidich);
void ChenThongTin(int vitriDau, int& vitriCuoi, const wstring& noiDung, wstring& chuoiHTML);//luu y: viet theo cau truc file html nhat dinh
int SoDong(const wstring&); //So dong ung voi so sinh vien
int TimChuoi(const wstring& ChuoiCanTim, const wstring& chuoi, int pos = 0);
int TimChuoi(wchar_t KiTu, const wstring& chuoi, int pos = 0);
wstring InHoa(const wstring& chuoi);
wstring& loai_bo_khoang_trang_nhay_kep(wstring&);
//main
Data* LayThongTin(wstring& fileDaChinhSua,int);
void XoaNoiDung(wstring& chuoi, int dau, int& cuoi);//xoa noi dung tu dau -> cuoi
void ChenNoiDung(const wstring& chuoiCanChen, wstring& chuoiDuocChen, int pos);
void TaoHTML(wstring& fileHTML, wstring& SinhVien);
int SinhVien(wstring& chuoiHTML,const Data& dulieu);
#endif