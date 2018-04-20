//SupportFunction.cpp -- ham ho tro
//
#include "stdafx.h"
#include "Declare.h"
int ChinhSua(const wstring& fileTho, wstring& fileMoi) {
	wchar_t wc;
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
	wstring::size_type b_pos = wstring::npos;
	wstring::size_type e_pos = wstring::npos;
	// xoa dau
	for (wstring::size_type i = 0; i < data.length(); i++) {
		wchar_t wc = data.at(i);
		if (wc != L'\n' && wc != L' ') {
			b_pos = i;
			break;
		}
	}
	if(b_pos != wstring::npos)
		data.erase(0, b_pos);
	// xoa cuoi
	for (wstring::reverse_iterator i = data.rbegin(); i != data.rend(); i++) {
		if ((*i) != L'\n' && (*i) != L' ') {
			e_pos = data.rfind(*i);
			break;
		}
	}
	if (e_pos != wstring::npos)
		data.erase(e_pos + 1);
	return;
}
int DemKiTu(wchar_t kitu, wstring& file) {
	int dem = 0;
	wchar_t wc;
	wifstream rf;
	rf.open(file);
	if (rf.eof()) //empty string
		return 0;
	while (!rf.eof()){
		wc = rf.get();
		if (wc == kitu) dem++;
	}
	rf.close();
	return dem;
}
wstring Tach(wchar_t kitu, wstring& chuoi, wstring::size_type pos) {
	wstring::size_type n = chuoi.find(kitu,pos);
	if (n == wstring::npos)
		return NULL;
	wstring temp;
	for (wstring::size_type i = pos; i < n; i++) {
		temp.push_back(chuoi.at(i));
	}
	return temp;
}
int DuaVaoChuoi(wstring& filenguon, wstring& chuoidich) {
	wchar_t wc;
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
	wstring temp;
	int i = 0;
	while (chuoi[i]) {
		temp.push_back(towupper(chuoi[i++]));
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
