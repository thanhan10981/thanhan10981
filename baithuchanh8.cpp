#include <iostream>
#include <stack>
#include <conio.h>
#include <queue>

const int MAX =10;//khai giá trị Max cho phòng bệnh nhân
using namespace std;
#define ESC 27//mã 27 là phím ESC
//hàm lấy toán hạn có thể dùng chung cho 2 chức năng
bool laToanHang(char c) {
    return isalnum(static_cast<unsigned char>(c)); 
}
//hàm ưu tiên theo các phép tính 
int doUuTien(char c) {
    return (c == '+' || c == '-') ? 1 : (c == '*' || c == '/') ? 2 : 0;
}
//hàm chuyển tư trung tố sang hậu tố
string chuyenTrungToSangHauTo(const string& trungTo) {
    string hauTo;
    stack<char> nganXep;

    for (char c : trungTo) {
        if (laToanHang(c)) {
            hauTo.push_back(c);
        } else if (c == '(') {
            nganXep.push(c);
        } else if (c == ')') {
            while (!nganXep.empty() && nganXep.top() != '(') {
                hauTo.push_back(nganXep.top());
                nganXep.pop();
            }
            nganXep.pop(); // Lấy và loại bỏ '(' khỏi ngăn xếp
        } else { // c là toán tử
            while (!nganXep.empty() && doUuTien(nganXep.top()) >= doUuTien(c)) {
                hauTo.push_back(nganXep.top());
                nganXep.pop();
            }
            nganXep.push(c);
        }
    }

    while (!nganXep.empty()) {
        hauTo.push_back(nganXep.top());
        nganXep.pop();
    }

    return hauTo;
}
//hàm tính toán tử
double tinhToanTu(double operand1, double operand2, char oper) {
    switch (oper) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            cerr << "Toan tu khong hop le" << endl;
            return 0;
    }
}
//hàm tính gia trị hậu tố
double tinhGiaTriHauTo(const string& hauTo) {
    stack<double> nganXep;

    for (char c : hauTo) {
        if (isdigit(c)) {
            // Nếu là chữ số, chuyển ký tự sang số và đẩy vào ngăn xếp
            nganXep.push(c - '0');
        } else {
            if (nganXep.size() < 2) {
                cerr << "Loi: Khong du so luong toan hang de thuc hien phep toan." << endl;
                return 0;  // Hoặc xử lý lỗi theo yêu cầu của bạn
            }

            // Lấy 2 toán hạng từ ngăn xếp, thực hiện phép toán và đẩy kết quả vào ngăn xếp
            double operand2 = nganXep.top();
            nganXep.pop();
            double operand1 = nganXep.top();
            nganXep.pop();

            double ketQua = tinhToanTu(operand1, operand2, c);
            nganXep.push(ketQua);
        }
    }

    if (nganXep.size() != 1) {
        cerr << "Loi: Bieu thuc khong hop le." << endl;
        return 0;  // Hoặc xử lý lỗi theo yêu cầu của bạn
    }

    return nganXep.top();
}
//phân tích thành thừa số nguyên tố
void phanTichThanhThuaSoNguyenTo(int n, queue<int>& thuaSo) {
    for (int i = 2; i <= n; ++i) {
        while (n % i == 0) {
            thuaSo.push(i);
            n /= i;
        }
    }
}
//hàm tính thùa số
void tinhThuaSo(int soNguyen){ 
        queue<int> thuaSoQueue;
         phanTichThanhThuaSoNguyenTo(soNguyen, thuaSoQueue);
        cout << "Cac thua so nguyen to cua " << soNguyen << " la: ";
         while (!thuaSoQueue.empty()) {
                cout << thuaSoQueue.front() << " ";
                thuaSoQueue.pop();
            }
        cout << endl;
}
//hàm lấy số thư tự của bệnh nhân
void laySoThuTu(queue<int> &hangDoi){
int static soThuTu =1;
    if(soThuTu<MAX){
    hangDoi.push(soThuTu);
    cout<<"Da lay so thu tu la:"<<soThuTu<<endl;
    soThuTu++;
    }
    else{
        cout<<"Qua tai benh nhan"<<endl;
        _getch();
    }
    if(soThuTu==MAX){
        soThuTu = 1;
    }
    
}
//hàm bác sĩ gọi bênh nhân vào phòng khám
void goiVaoPhongKham(queue<int>& hangDoi) {
    if (!hangDoi.empty()) {
        int soThuTu = hangDoi.front();
        hangDoi.pop();
      cout << "Moi benh nhan co so thu tu la " << soThuTu << " vao phong kham." << endl;
    } else {
      cout << "Da het benh nhan." << endl;
    }
}
// menu mô phỏng quá trình hoạt động của bệnh viện
void menuBenhVien(){
    int chon;
    queue<int> hangDoi;
    while(true) {
    system("cls");
    cout<<"---------------Menu-----------------"<<endl;
    cout <<"1.Lay so thu tu benh nhan"<< endl;
    cout <<"2.Bac si goi benh nhan vao phong kham"<< endl;
    cout <<"3.De quay lai menu chinh."<< endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Nhap lua chon cua ban:"<<endl;
     chon = _getch();
    switch(chon){
        case '1':
            laySoThuTu(hangDoi);
            _getch();
             break;
        case '2':
            goiVaoPhongKham(hangDoi);
            _getch();
            break;
        case '3':
            return;
        default:
            cout<<"lua chon khong hop le. Vui long chon lai. "<< endl;
            _getch();
            break;
    }
    }

}
int main() {
    int luachon,soNguyen;
    string nhapHauTo;
    while(true){
    system("cls");
    cout<<"---------------------------Menu---------------------------"<<endl;
    cout<<"1.Chuong trinh chuyen bieu thuc hau to sang trung to"<<endl;
    cout<<"2.Chuong trinh tinh gia tri bieu thu hau to"<<endl;
    cout<<"3.Chuong trinh tinh cac thua so nguyen to"<<endl;
    cout<<"4.Chuong trinh mo phong qua trinh quan ly benh vien"<<endl;
    cout<<"ESC.Thoat"<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"Nhap lua chon cua ban: "<<endl;
    luachon = _getch();
    switch(luachon){
        case '1':
            cout<<"Nhap bieu thuc hau to : ";
            cin>>nhapHauTo;
            cout << "bieu thuc hau to: " << nhapHauTo << endl;
            cout << "bieu thuc trung to: " << chuyenTrungToSangHauTo(nhapHauTo) << endl;
            _getch();
            break;
        case '2':
            cout<<"Nhap bieu thuc hau to : ";
            cin>>nhapHauTo;
            cout << "bieu thuc hau to: " << nhapHauTo << endl;
            cout << "Gia tri cua bieu thuc Hau to: " << tinhGiaTriHauTo(nhapHauTo) << endl;
            _getch();
            break;
        case '3':
            cout << "Nhap vao mot so nguyen: ";
            cin >> soNguyen;
            tinhThuaSo( soNguyen);
            _getch();
            break;
        case '4':
            menuBenhVien();
            _getch();
            break;
        case ESC:
            cout<<"Ban da thoat chuong trinh!"<<endl;
            _getch();
            return 0;
        default:
            cout<<"lua chon khong hop le. Vui long chon lai. "<< endl;
            _getch();
            break;
         }
    }
}
