//MainFunction.cpp -- Ham chinh
//

#include "stdafx.h"
#include "Declare.h"

using namespace std;

Data* LayThongTin(wstring& file) {
	wstring temp;
	wifstream rf;
	rf.open(file);
	if (!rf.is_open()) {
		return NULL;
	}
	int lines = DemKiTu(L'\n', file) + 1;
	Data* arr = new Data[lines];
	for (int i = 0; i < lines; i++) {
		getline(rf, (arr + i)->MSSV, L',');
		getline(rf, (arr + i)->HoTen, L',');
		getline(rf, (arr + i)->Nganh, L',');
		//truong du lieu nien khoa
		getline(rf, temp, L',');
		(arr + i)->NienKhoa = stoi(temp);
		getline(rf, (arr + i)->NgaySinh, L',');
		getline(rf, (arr + i)->HinhAnh, L',');
		getline(rf, (arr + i)->MoTa, L',');
		getline(rf, (arr + i)->Email, L',');
		getline(rf, (arr + i)->SoThich, L'\n');
	}
	rf.close();
	return arr;
}
int TimTag(const wstring& chuoiCanTim, const wstring& chuoiHTML, int pos) {
	wstring::size_type n = chuoiHTML.find(chuoiCanTim, pos);
	if (n == wstring::npos) {
		return NOT_MATCH;
	}
	return n;
}
void XoaNoiDung(wstring& chuoi, int dau, int& cuoi) {
	//sua lai cuoi do sau khi xoa cuoi doi 1 doan = cuoi - dau
	chuoi.erase(chuoi.begin() + dau, chuoi.begin() + cuoi); //[first,last)
	cuoi = dau;
	return;
}
void ChenNoiDung(const wstring& sub, wstring& nguon, int pos) {
	nguon.insert(pos, sub);
	return;
}
int SinhVien(wstring& chuoiHTML,const Data& dulieu) {
	wstring tagMo;
	wstring tagDong;
	int viTriDau;
	int viTriCuoi;
	wstring NoiDung;
	//chen du lieu lan luot tu tren xuong duoi
	//title
	tagMo = L"<title>";
	tagDong = L"</title>";
	viTriDau = TimTag(tagMo, chuoiHTML) + tagMo.length();
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	NoiDung = InHoa(wstring(L"HMCUS - ") + dulieu.HoTen);
	ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	//Ho ten - MSSV
	tagMo = wstring(L"<span class=\"Personal_FullName\">");
	tagDong = L"</span>";
	viTriDau = TimTag(tagMo, chuoiHTML) + tagMo.length();
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	NoiDung = InHoa(dulieu.HoTen + wstring(L" - ") + dulieu.MSSV);
	ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	//Chuyen Nganh
	tagMo = wstring(L"<div class=\"Personal_Department\">");
	tagDong = L"</div>";
	viTriDau = TimTag(tagMo, chuoiHTML) + tagMo.length();
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	NoiDung = InHoa(dulieu.Nganh);
	ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	//Email
	tagMo = wstring(L"<div class=\"Personal_Phone\">");
	tagDong = L"</div>";
	viTriDau = TimTag(tagMo, chuoiHTML) + tagMo.length();
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	NoiDung = wstring(L"Email: ") + dulieu.Email;
	ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	//Hinh anh ca nhan
	tagMo = wstring(L"<div class=\"Personal_HinhcanhanKhung\">");
	tagDong = L"</div>";
	viTriDau = TimTag(tagMo, chuoiHTML) + tagMo.length();
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	NoiDung = wstring(L"<img src=\"Images/") + dulieu.HinhAnh + wstring(L"\" class=\"Personal_Hinhcanhan\" />");
	ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	//Thong tin ca nhan
	wstring* arr = new wstring[5];
	arr[0] = wstring(L"Ho va ten: ") + dulieu.HoTen;
	arr[1] = wstring(L"MSSV: ") + dulieu.MSSV;
	arr[2] = wstring(L"Sinh vien khoa ") + dulieu.Nganh;
	arr[3] = wstring(L"Ngay sinh: ") + dulieu.NgaySinh;
	arr[4] = wstring(L"Email: ") + dulieu.Email;
	for (int i = 0; i < 5; i++) {
		tagMo = wstring(L"<li>");
		tagDong = L"</li>";
		viTriDau = TimTag(tagMo, chuoiHTML, viTriCuoi) + tagMo.length();//tiep tuc tu vi tri truoc do
		viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
		NoiDung = arr[i];
		ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	}
	delete[] arr;
	//So thich
	//xoa tat ca so thich neu co
	int pos = viTriCuoi; //luu lai de sau con chen so thich vao
	tagMo = wstring(L"<ul class=\"TextInList\">");
	tagDong = L"</ul>";
	viTriDau = TimTag(tagMo, chuoiHTML,viTriCuoi) + tagMo.length();//tiep tuc tu vi tri truoc do
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	XoaNoiDung(chuoiHTML, viTriDau, viTriCuoi);
	//dem so so thich
	int dem = 1; //neu ko co so thich thi mac dinh la NULL nen dem = 1
	int n = TimTag(L",", dulieu.SoThich);
	while (n != NOT_MATCH) {
		dem++;
		n = TimTag(L",", dulieu.SoThich,n+1);
	}
	//lay du lieu
	arr = new wstring[dem];
	int vitri = 0;
	int i = 0;
	while (dulieu.SoThich[i]) {
		if (dulieu.SoThich[i] != L',') {
			arr[vitri].push_back(dulieu.SoThich[i]);
		}
		else {
			vitri++;
		}
		i++;
	}
	//chen du lieu
	for (int i = 0; i < dem; i++) {
		if (arr[i] != L"NULL") {
			NoiDung = wstring(L"<li>") + arr[i] + wstring(L"</li>");
			ChenNoiDung(NoiDung, chuoiHTML,viTriDau);
		}
	}
	delete[] arr;
	//Mo ta ban than
	tagMo = wstring(L"<div class=\"Description\">");
	tagDong = L"</div>";
	viTriDau = TimTag(tagMo, chuoiHTML) + tagMo.length();
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	NoiDung = dulieu.MoTa;
	ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	//Nguoi thuc hien
	tagMo = wstring(L"TH2012/03</br>");
	tagDong = L"</br>";
	viTriDau = TimTag(tagMo, chuoiHTML, viTriCuoi) + tagMo.length();//tiep tuc tu vi tri truoc do
	viTriCuoi = TimTag(tagDong, chuoiHTML, viTriDau);
	NoiDung = L"1712875 - Nguyen Manh Tuan";
	ChenThongTin(viTriDau, viTriCuoi, NoiDung, chuoiHTML);
	return 0;
}
void TaoHTML(wstring& fileHTML, wstring& SinhVien) {
	wofstream wf;
	wf.open(fileHTML);
	wf << SinhVien;
	return;
}

