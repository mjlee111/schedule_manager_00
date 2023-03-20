#include "schedule.h"
#include "./ui_schedule.h"

using namespace std;

schedule::schedule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::schedule)
{
    ui->setupUi(this);
    QApplication::setWindowIcon(QIcon("icon.ico"));
    current_day = ui->day_list->currentIndex();
    for(int i = 0 ; i < 7 ; i++){
        for (int j = 0 ; j < 6 ; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::white);
            ui->timetable->setItem(i, j, item);
        }
    }
    struct info save[1000];
}

schedule::~schedule()
{
    delete ui;
}

bool schedule::check_stat(void){
    bool texts_ok = 0;
    bool location_ok = 0;
    bool like_time_ok = 0;
    bool question_ok = 0;

    if(ui->input_num->value() != 0 && ui->name_box->text().isEmpty() == 0
       && ui->number_box->text().isEmpty() == 0
       && ui->phone_box->text().isEmpty() == 0
       && ui->department_box->text().isEmpty() == 0
       && ui->MBTI_box->text().isEmpty() == 0) texts_ok = 1;
    if(ui->home_1->isChecked() || ui->home_2->isChecked() || ui->home_3->isChecked()) location_ok = 1;
    if(ui->time_list_first->currentIndex() != 0 && ui->time_list_second->currentIndex() != 0 && ui->time_list_third->currentIndex() != 0) like_time_ok = 1;
    if(ui->question_box->text().isEmpty() == 0) question_ok = 1;

    if(texts_ok && location_ok && like_time_ok && question_ok){
        QMessageBox::information(this, "WARNING", "저장완료");
        return 1;
    }
    else if (!texts_ok){
        QMessageBox::critical(this, "WARNING", "텍스트 부분에 작성하지 않은 부분이 있습니다.");
        return 0;
    }
    else if (!location_ok){
        QMessageBox::critical(this, "WARNING", "장소 부분에 작성하지 않은 부분이 있습니다.");
        return 0;
    }
    else if (!like_time_ok){
        QMessageBox::critical(this, "WARNING", "선호 시간에 작성하지 않은 부분이 있습니다.");
        return 0;
    }
    else if (question_ok){
        QMessageBox::critical(this, "WARNING", "질문 부분에 작성하지 않은 부분이 있습니다.");
        return 0;
    }
    return 0;
}

void schedule::time_save_func(void){
    current_num = ui->input_num->value();
    if(ui->first_time->isChecked()) timetable_save[current_num][ui->day_list->currentIndex()][0] = 1;
    else if(ui->first_time->isChecked() == 0) timetable_save[current_num][ui->day_list->currentIndex()][0] = 2;

    if(ui->second_time->isChecked()) timetable_save[current_num][ui->day_list->currentIndex()][1] = 1;
    else if(ui->second_time->isChecked() == 0) timetable_save[current_num][ui->day_list->currentIndex()][1] = 2;

    if(ui->third_time->isChecked()) timetable_save[current_num][ui->day_list->currentIndex()][2] = 1;
    else if(ui->third_time->isChecked() == 0) timetable_save[current_num][ui->day_list->currentIndex()][2] = 2;

    if(ui->fourth_time->isChecked()) timetable_save[current_num][ui->day_list->currentIndex()][3] = 1;
    else if(ui->fourth_time->isChecked() == 0) timetable_save[current_num][ui->day_list->currentIndex()][3] = 2;

    if(ui->fifth_time->isChecked()) timetable_save[current_num][ui->day_list->currentIndex()][4] = 1;
    else if(ui->fifth_time->isChecked() == 0) timetable_save[current_num][ui->day_list->currentIndex()][4] = 2;

    if(ui->sixth_time->isChecked()) timetable_save[current_num][ui->day_list->currentIndex()][5] = 1;
    else if(ui->sixth_time->isChecked() == 0) timetable_save[current_num][ui->day_list->currentIndex()][5] = 2;

    if(ui->no_time->isChecked()) timetable_save[current_num][ui->day_list->currentIndex()][6] = 1;
    else if(ui->no_time->isChecked() == 0) timetable_save[current_num][ui->day_list->currentIndex()][6] = 2;
}

void schedule::whole_save_func(void){
    ofstream file;
    file.open("/Users/michael/Desktop/CODE/QTCreator/schedule_manager_00/schedule_manager/save.txt", ios::app);
    file << ui->input_num->text().toStdString() << " ";
    file << ui->name_box->text().toStdString() << " ";
    file << ui->number_box->text().toStdString() << " ";
    file << ui->phone_box->text().toStdString() << " ";
    file << ui->department_box->text().toStdString() << " ";
    file << ui->MBTI_box->text().toStdString() << " ";
    for(int k = 0 ; k < 5 ; k++) {
        for(int l = 0 ; l < 7 ; l++) file << timetable_save[current_num][k][l] << " ";
    }
    if(ui->home_1->isChecked()) file << "1 ";
    else if(ui->home_2->isChecked()) file << "2 ";
    else if(ui->home_3->isChecked()) file << "3 ";
    file << ui->time_list_first->currentText().toStdString() << " ";
    file << ui->time_list_second->currentText().toStdString() << " ";
    file << ui->time_list_third->currentText().toStdString() << " ";
    file << ui->question_box->text().toStdString() << endl;
    file.close();
}

void schedule::text_clear_func(void){
    ui->input_num->setValue(current_num+1);
    ui->name_box->setText("");
    ui->number_box->setText("");
    ui->phone_box->setText("");
    ui->department_box->setText("");
    ui->MBTI_box->setText("");
    ui->day_list->setCurrentIndex(0);
    ui->first_time->setCheckState(Qt::Unchecked);
    ui->second_time->setCheckState(Qt::Unchecked);
    ui->third_time->setCheckState(Qt::Unchecked);
    ui->fourth_time->setCheckState(Qt::Unchecked);
    ui->fifth_time->setCheckState(Qt::Unchecked);
    ui->sixth_time->setCheckState(Qt::Unchecked);
    ui->no_time->setCheckState(Qt::Unchecked);
    ui->home_1->setChecked(false);
    ui->home_2->setChecked(false);
    ui->home_3->setChecked(false);
    ui->time_list_first->setCurrentIndex(0);
    ui->time_list_second->setCurrentIndex(0);
    ui->time_list_third->setCurrentIndex(0);
    ui->question_box->setText("");
    for(int i = 0 ; i < 7 ; i++){
        for (int j = 0 ; j < 6 ; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::white);
            ui->timetable->setItem(i, j, item);
        }
    }
}

void schedule::save_file_reader(void){
    ifstream file;
    file.open("/Users/michael/Desktop/CODE/QTCreator/schedule_manager_00/schedule_manager/save.txt", ios::in);
    cnt = 0;
    while(true){
        if(file.eof()) break;
        file >> _save[cnt].num;
        if(file.eof()) break;
        for(int i = 0 ; i < 5 ; i++ ) file >> _save[cnt].text[i];
        if(file.eof()) break;
        for(int i = 0 ; i < 35 ; i++ ) file >> _save[cnt].timetable[i];
        if(file.eof()) break;
        file >> _save[cnt].location;
        if(file.eof()) break;
        for(int i = 0 ; i < 3 ; i++ ) file >> _save[cnt].want_time[i];
        if(file.eof()) break;
        file >> _save[cnt].question;
        if(file.eof()) break;
        cnt ++;
    }
    file.close();
}

void schedule::on_save_btn_clicked(){

    if(!check_stat()) return;
    whole_save_func();
    text_clear_func();
}

void schedule::on_day_list_currentIndexChanged(int index){
    if(ui->first_time->isChecked() == false &&
       ui->second_time->isChecked() == false &&
       ui->third_time->isChecked() == false &&
       ui->fourth_time->isChecked() == false &&
       ui->fifth_time->isChecked() == false &&
       ui->sixth_time->isChecked() == false &&
       ui->no_time->isChecked() == false){
       ui->day_list->setCurrentIndex(current_day);
       QMessageBox::critical(this, "WARNING", "시간이 선택되지 않았습니다.");
    }
    else if(ui->first_time->isChecked() == true ||
            ui->second_time->isChecked() == true ||
            ui->third_time->isChecked() == true ||
            ui->fourth_time->isChecked() == true ||
            ui->fifth_time->isChecked() == true ||
            ui->sixth_time->isChecked() == true ||
            ui->no_time->isChecked() == true){

        ui->first_time->setChecked(false);
        ui->second_time->setChecked(false);
        ui->third_time->setChecked(false);
        ui->fourth_time->setChecked(false);
        ui->fifth_time->setChecked(false);
        ui->sixth_time->setChecked(false);
        ui->no_time->setChecked(false);
        current_day = ui->day_list->currentIndex();

    }
}

void schedule::on_load_btn_clicked()
{
    save_file_reader();
    for(int j = 0 ; j < cnt ; j++){
        cout << (int)_save[j].num << " ";
        for(int i = 0 ; i < 5 ; i++ ) cout << _save[j].text[i] << " ";
        for(int i = 0 ; i < 35 ; i++ ) cout << _save[j].timetable[i] << " ";
        cout << _save[j].location << " ";
        for(int i = 0 ; i < 3 ; i++ ) cout << _save[j].want_time[i] << " ";
        cout << _save[j].question << endl;
    }
    int cpy = cnt;
    string string_cnt = to_string(cpy);
    QString my = QString::fromStdString(string_cnt);
    ui->current_cnt->setText(my);
}

void schedule::on_time_btn_clicked()
{
    time_save_func();
}

void schedule::on_first_time_clicked()
{
    time_save_func();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackground(Qt::yellow);
    ui->timetable->setItem(0, current_day, item);
}

void schedule::on_second_time_clicked()
{
    time_save_func();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackground(Qt::yellow);
    ui->timetable->setItem(1, current_day, item);
}

void schedule::on_third_time_clicked()
{
    time_save_func();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackground(Qt::yellow);
    ui->timetable->setItem(2, current_day, item);
}

void schedule::on_fourth_time_clicked()
{
    time_save_func();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackground(Qt::yellow);
    ui->timetable->setItem(3, current_day, item);
}

void schedule::on_fifth_time_clicked()
{
    time_save_func();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackground(Qt::yellow);
    ui->timetable->setItem(4, current_day, item);
}

void schedule::on_sixth_time_clicked()
{
    time_save_func();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackground(Qt::yellow);
    ui->timetable->setItem(5, current_day, item);
}

void schedule::on_no_time_clicked()
{
    time_save_func();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackground(Qt::yellow);
    ui->timetable->setItem(6, current_day, item);
}



