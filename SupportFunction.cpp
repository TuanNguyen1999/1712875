//SupportFunction.cpp -- ham ho tro
//
#include "stdafx.h"
#include "Declare.h"
#include <cwctype>
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
	while (rf.good())
	{
		rf.get(wc);
		text.push_back(wc);
	}
	if (!rf.eof()) {
		return UNKNOW_ERROR; //UNKNOW_ERROR
	}
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
	wstring text;
	wifstream rf;
	rf.open(filenguon);
	if (!rf.is_open()) {
		return DONT_EXISTS; //DONT_EXISTS
	}
	while (rf.good())
	{
		rf.get(wc);
		chuoidich.push_back(wc);
	}
	if (!rf.eof()) {
		return UNKNOW_ERROR; //UNKNOW_ERROR
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