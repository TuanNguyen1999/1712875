//SupportFunction.cpp -- ham ho tro
//
#include "stdafx.h"
#include "Declare.h"
int ChinhSua(const wstring& fileTho, wstring& fileMoi) {
	wstring text;
	wofstream wf;
	wifstream rf;
	wf.open(fileMoi);
	rf.open(fileTho);
	if (!rf.is_open()) {
		return DONT_EXISTS; //DONT_EXISTS
	}
	std::wstringstream sstr;
	sstr << rf.rdbuf();
	text = sstr.str();
	LamSach(text);
	wf << text;
	rf.close();
	wf.close();
	return GOOD; //OK
}
void LamSach(wstring& data) {
	wstring::size_type from, to;
	wchar_t ws[] = L"\t\n ";
	from = data.find_first_not_of(ws);
	to = data.find_last_not_of(ws);
	data = data.substr(from, to - from + 1);
	return;
}
int SoDong(const wstring& file) {
	int dem = 0;
	wifstream rf(file);
	wstring temp;
	while (getline(rf, temp)) {
		dem++;
	}
	return dem;
}
int DuaVaoChuoi(wstring& filenguon, wstring& chuoidich) {
	chuoidich.resize(0);//xoa noi dung trong chuoi
	std::locale lo(std::locale::empty(), new std::codecvt_utf8<wchar_t>);
	wifstream rf;
	rf.imbue(lo);
	rf.open(filenguon);
	if (!rf.is_open()) {
		return DONT_EXISTS; //DONT_EXISTS
	}
	else {
		std::wstringstream ss;
		ss << rf.rdbuf();
		chuoidich = ss.str();
	}
	rf.close();
	return GOOD; //OK
}
void ChenThongTin(int vitriDau, int& vitriCuoi, const wstring& noiDung, wstring& chuoiHTML)
{
	//sua lai vi tri cuoi do sau khi xoa va chen noi dung moi vao 
	//thi vi tri cuoi ko con dung voi ban dau
	XoaNoiDung(chuoiHTML, vitriDau, vitriCuoi);// [dau,cuoi)
	ChenNoiDung(noiDung, chuoiHTML, vitriDau);
	vitriCuoi = vitriDau + noiDung.length();
}
wstring InHoa(const wstring& chuoi) {
	std::locale lo(""); //use enviroment locale
	const std::ctype<wchar_t>& f = std::use_facet<std::ctype<wchar_t>>(lo);//make ctype functions adapting enviroment locale
	wstring temp;
	for (int i = 0; i < chuoi.length(); i++) {
		temp.push_back(f.toupper(chuoi[i]));
	}
	return temp;
}
int TimChuoi(const wstring& chuoiCanTim, const wstring& chuoiHTML, int pos) {
	wstring::size_type n = chuoiHTML.find(chuoiCanTim, pos);
	if (n == wstring::npos) {
		return NOT_MATCH;
	}
	return n;
}
int TimChuoi(wchar_t KiTu, const wstring& chuoiHTML, int pos) {
	wstring::size_type n = chuoiHTML.find(KiTu, pos);
	if (n == wstring::npos) {
		return NOT_MATCH;
	}
	return n;
}
wstring& loai_bo_khoang_trang_nhay_kep(wstring& str) {
	wstring::size_type from = str.find_first_not_of(L" \"'");
	wstring::size_type to = str.find_last_not_of(L" \"'");
	str = str.substr(from, to - from + 1);
	return str;
}
