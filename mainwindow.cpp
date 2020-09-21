#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
/***********简易计算器+进制转换器**************/
/************mimo431************************/
/************2020-0921-1048****************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //void status();
    //setFixedSize(this->width(), this->height());
    system_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::system_init(){

    //进制转换
    input.addButton(ui->radioButton,2);
    input.addButton(ui->radioButton_2,8);
    input.addButton(ui->radioButton_3,10);
    input.addButton(ui->radioButton_7,16);
    ui->radioButton_3->setChecked(true);

    output.addButton(ui->radioButton_4,2);
    output.addButton(ui->radioButton_5,8);
    output.addButton(ui->radioButton_6,10);
    output.addButton(ui->radioButton_8,16);
    output.setId(ui->radioButton_6,10);
    ui->radioButton_6->setChecked(true);

    connect(&input, SIGNAL(buttonClicked(int)), this, SLOT( code_change()));
    connect(&output, SIGNAL(buttonClicked(int)), this, SLOT(code_change()));

    connect(ui->num0,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num1,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num2,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num3,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num4,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num5,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num6,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num7,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num8,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->num9,&QPushButton::clicked,this,&MainWindow::data_recv);

    connect(ui->jia,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->jian,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->chengfa,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->shang,&QPushButton::clicked,this,&MainWindow::data_recv);
    connect(ui->pingfang,&QPushButton::clicked,this,&MainWindow::data_recv);

    connect(ui->equal,&QPushButton::clicked,this,&MainWindow::data_recv);


}
void MainWindow::code_change(){
    QString ss=ui->lineEdit_input->text();
    qDebug()<<"sss"<<input.checkedId();
    on_lineEdit_input_textChanged(ss);
}
void MainWindow::on_lineEdit_input_textChanged(const QString &arg1)
{
    bool ok;
    qDebug()<<arg1;
    code_input=input.checkedId();
    code_resu=output.checkedId();
    switch (code_input) {
    case 2:
        start=arg1.toInt(&ok,2);
        break;
    case 8:
        start=arg1.toInt(&ok,8);
        break;
    case 10:
        start=arg1.toInt(&ok,10);
        break;
    case 16:
        start=arg1.toInt(&ok,16);
        break;
    }
    print_resu();
}
//进制转换输出
void MainWindow::print_resu(){
    switch (code_resu) {
    case 2:
        resu=QString::number(start,2);
        break;
    case 8:
        resu=QString::number(start,8);
        break;
    case 10:
       resu=QString::number(start,10);
        break;
    case 16:
        resu=QString::number(start,16);
        break;
    }
    ui->lineEdit_output->setText(resu);
}

//清屏
void MainWindow::on_btn_clear_clicked()
{
    ui->edit_show->clear();
}

void MainWindow::data_input_print()
{
    //ui->edit_show->insertPlainText("\n");
    ui->edit_show->insertPlainText(cal_recv);
    //ui->edit_show->insertPlainText("\n");

}
//数值接收chuli
void MainWindow::data_recv(){
    //没必要，后续可以改槽函数，直接传值，后续修改。。。。。
    QPushButton *btn=dynamic_cast<QPushButton*>(sender());
    cal_recv=btn->text();
    if(cal_recv=="=")
    {
        data_recv_deal();
        return;
    }
    //如果是运算符，赋予，直接返回
    if(cal_recv=="+"||cal_recv=="-"||cal_recv=="*"||cal_recv=="/"||cal_recv=="x²")
     {
        cal_deal=cal_recv;
        data_input_print();
        return;
     }
    //计算器保留上次计算结果，因此输入接收要注意

     if(cal_deal=="")
     {
        cal_x.append(cal_recv);
        qDebug()<<cal_x;
     }
     else {
         cal_y.append(cal_recv);
         //ui->edit_show->insertPlainText(cal_recv);
         qDebug()<<cal_y;
     }

     data_input_print();
}
void MainWindow::data_recv_guolu(){

}
//处理方式接收
void MainWindow::data_recv_deal(){
    qDebug()<<"start cal....";
    qDebug()<<cal_x;
    qDebug()<<cal_deal;
    qDebug()<<cal_y;
    if(cal_x=="")
        cal_x=cal_res;
    double x=cal_x.toDouble();
    double y=cal_y.toDouble();
    char *p=cal_deal.toLocal8Bit().data();
    qDebug()<<p;

    switch (*p) {
    case '+':
        cal_res=QString::number(x+y);
        break;
    case '-':
        cal_res=QString::number(x-y);
        break;
    case '*':
        cal_res=QString::number(x*y);
        break;
    case '/':
        cal_res=QString::number(x/y);
        break;
    default:
        cal_res=QString::number(x*x);
        break;
    }
    qDebug()<<cal_res;
    resu_print();

}
//結果輸出
void MainWindow::resu_print(){
    qDebug()<<"resu::"<<cal_res;

    ui->edit_show->insertPlainText("\n");
    ui->edit_show->insertPlainText("----------------\n");
    ui->edit_show->insertPlainText(cal_res+"\n");
    ui->edit_show->insertPlainText("----------------\n");
    //cal_x=cal_res;
   on_qingchu_clicked();


}
//CE，清除内存
void MainWindow::on_qingchu_clicked()
{
    cal_deal.clear();
    cal_x.clear();
    cal_y.clear();
}
