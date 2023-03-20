#include "schedule.h"
#include "./ui_schedule.h"

using namespace std;

schedule::schedule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::schedule)
{
    ui->setupUi(this);
    QApplication::setWindowIcon(QIcon(":/icon.ico"));
    current_day = ui->day_list->currentIndex();
    for(int i = 0 ; i < 7 ; i++){
        for (int j = 0 ; j < 6 ; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::white);
            ui->timetable->setItem(i, j, item);
        }
    }
    struct info save[1000];

    save_file_reader();
    int cpy = cnt;
    string string_cnt = to_string(cpy);
    QString my = QString::fromStdString(string_cnt);
    ui->current_cnt->setText(my);
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

void schedule::load_robit(void){
    ifstream file;
    file.open("/Users/michael/Desktop/CODE/QTCreator/schedule_manager_00/schedule_manager/robit.txt", ios::in);
    cnt_robit = 0;
    while(true){
        if(file.eof()) break;
        file >> _save[cnt_robit+99].num;
        if(file.eof()) break;
        for(int i = 0 ; i < 5 ; i++ ) file >> _save[cnt_robit+99].text[i];
        if(file.eof()) break;
        for(int i = 0 ; i < 35 ; i++ ) file >> _save[cnt_robit+99].timetable[i];
        if(file.eof()) break;
        file >> _save[cnt_robit+99].location;
        if(file.eof()) break;
        for(int i = 0 ; i < 3 ; i++ ) file >> _save[cnt_robit+99].want_time[i];
        if(file.eof()) break;
        file >> _save[cnt_robit+99].question;
        if(file.eof()) break;
        cnt_robit ++;
    }
    for(int i = 0 ; i < 7 ; i++)robit_name[i] = _save[i+99].text[0];
    file.close();
    for(const auto& option : robit_name) optionlist << QString::fromStdString(option);
    ui->robit_list->addItems(optionlist);
}

void schedule::load_new(void){
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
    for(int i = 0 ; i < cnt ; i++)new_name[i] = _save[i].text[0];
    file.close();
    for(const auto& option : new_name) optionlist_2 << QString::fromStdString(option);
    ui->new_list->addItems(optionlist_2);
}

void schedule::fill_robit_timetable(void){
    for(int i = 0 ; i < 7 ; i++){
        for (int j = 0 ; j < 6 ; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::white);
            ui->robit_time->setItem(i, j, item);
        }
    }
    int number = ui->robit_list->currentIndex();
    for(int i = 0 ; i < 35 ; i++){
        if(_save[99+number-1].timetable[i] == 1){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::yellow);
            int x, y;
            x = i % 7;
            y = (i / 7);
            ui->robit_time->setItem(x, y, item);
        }
    }
}

void schedule::fill_new_timetable(void){
    for(int i = 0 ; i < 7 ; i++){
        for (int j = 0 ; j < 6 ; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::white);
            ui->new_time->setItem(i, j, item);
        }
    }
    int number = ui->new_list->currentIndex();
    for(int i = 0 ; i < 35 ; i++){
        if(_save[number-1].timetable[i] == 1){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::red);
            int x, y;
            x = i % 7;
            y = (i / 7);
            ui->new_time->setItem(x, y, item);
        }
    }
}

void schedule::merge_timetable(void){
    for(int i = 0 ; i < 7 ; i++){
        for (int j = 0 ; j < 6 ; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::white);
            ui->new_time->setItem(i, j, item);
        }
    }
    int number = ui->new_list->currentIndex();
    int ro_number = ui->robit_list->currentIndex();
    for(int i = 0 ; i < 35 ; i++){
        if(_save[number-1].timetable[i] == 1 && _save[99+ro_number-1].timetable[i] != 1){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::red);
            int x, y;
            x = i % 7;
            y = (i / 7);
            ui->new_time->setItem(x, y, item);
        }
        else if(_save[number-1].timetable[i] == 1 && _save[99+ro_number-1].timetable[i] == 1){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::blue);
            int x, y;
            x = i % 7;
            y = (i / 7);
            ui->new_time->setItem(x, y, item);
        }
        else if(_save[number-1].timetable[i] != 1 && _save[99+ro_number-1].timetable[i] == 1){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::yellow);
            int x, y;
            x = i % 7;
            y = (i / 7);
            ui->new_time->setItem(x, y, item);
        }
    }
}

void schedule::setui_info(void){
    QString my_name = QString::fromStdString(_save[ui->new_list->currentIndex()-1].text[0]);
    ui->new_name->setText(my_name);

    QString my_student_num = QString::fromStdString(_save[ui->new_list->currentIndex()-1].text[1]);
    ui->new_student_num->setText(my_student_num);

    QString my_phone = QString::fromStdString(_save[ui->new_list->currentIndex()-1].text[2]);
    ui->new_phone_num->setText(my_phone);

    QString my_depart = QString::fromStdString(_save[ui->new_list->currentIndex()-1].text[3]);
    ui->new_department->setText(my_depart);

    QString my_mbti = QString::fromStdString(_save[ui->new_list->currentIndex()-1].text[4]);
    ui->new_MBTI->setText(my_mbti);

    if(_save[ui->new_list->currentIndex()-1].location == 1) ui->new_location->setText("통학");
    else if(_save[ui->new_list->currentIndex()-1].location == 2) ui->new_location->setText("기숙사");
    else if(_save[ui->new_list->currentIndex()-1].location == 3) ui->new_location->setText("학교 주변");

    QString my_time_like = QString::fromStdString(_save[ui->new_list->currentIndex()-1].want_time[0]);
    ui->new_time_like->setText(my_time_like);

    QString my_t = QString::fromStdString(_save[ui->new_list->currentIndex()-1].want_time[0]);
    ui->new_time_like->setText(my_t);

    QString my_q = QString::fromStdString(_save[ui->new_list->currentIndex()-1].question);
    ui->new_question->setText(my_q);
}

void schedule::setui_info_ro(void){
    QString my_name = QString::fromStdString(_save[ui->robit_list->currentIndex()-1+99].text[0]);
    ui->ro_name->setText(my_name);

    QString my_student_num = QString::fromStdString(_save[ui->robit_list->currentIndex()-1+99].text[1]);
    ui->ro_student_num->setText(my_student_num);

    QString my_phone = QString::fromStdString(_save[ui->robit_list->currentIndex()-1+99].text[2]);
    ui->ro_phone_num->setText(my_phone);

    QString my_depart = QString::fromStdString(_save[ui->robit_list->currentIndex()-1+99].text[3]);
    ui->ro_department->setText(my_depart);

    QString my_mbti = QString::fromStdString(_save[ui->robit_list->currentIndex()-1+99].text[4]);
    ui->ro_MBTI->setText(my_mbti);

    if(_save[ui->robit_list->currentIndex()-1+99].location == 1) ui->ro_location->setText("통학");
    else if(_save[ui->robit_list->currentIndex()-1+99].location == 2) ui->ro_location->setText("기숙사");
    else if(_save[ui->robit_list->currentIndex()-1+99].location == 3) ui->ro_location->setText("학교 주변");

    QString my_time_like = QString::fromStdString(_save[ui->robit_list->currentIndex()-1+99].want_time[0]);
    ui->ro_time->setText(my_time_like);
}

void schedule::on_save_btn_clicked(){
    if(!check_stat()) return;
    whole_save_func();
    text_clear_func();
}

void schedule::on_day_list_currentIndexChanged(int index){
    for(int i = 0; i < 7 ; i ++) time_cnt[i] = 0;
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
    if(time_cnt[0] == 0){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::yellow);
        ui->timetable->setItem(0, current_day, item);
        time_cnt[0] = 1;
    }
    else if(time_cnt[0] == 1){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::white);
        ui->timetable->setItem(0, current_day, item);
        time_cnt[0] = 0;
    }
}

void schedule::on_second_time_clicked()
{
    time_save_func();
    if(time_cnt[1] == 0){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::yellow);
        ui->timetable->setItem(1, current_day, item);
        time_cnt[1] = 1;
    }
    else if(time_cnt[1] == 1){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::white);
        ui->timetable->setItem(1, current_day, item);
        time_cnt[1] = 0;
    }
}

void schedule::on_third_time_clicked()
{
    time_save_func();
    if(time_cnt[2] == 0){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::yellow);
        ui->timetable->setItem(2, current_day, item);
        time_cnt[2] = 1;
    }
    else if(time_cnt[2] == 1){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::white);
        ui->timetable->setItem(2, current_day, item);
        time_cnt[2] = 0;
    }
}

void schedule::on_fourth_time_clicked()
{
    time_save_func();
    if(time_cnt[3] == 0){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::yellow);
        ui->timetable->setItem(3, current_day, item);
        time_cnt[3] = 1;
    }
    else if(time_cnt[3] == 1){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::white);
        ui->timetable->setItem(3, current_day, item);
        time_cnt[3] = 0;
    }
}

void schedule::on_fifth_time_clicked()
{
    time_save_func();
    if(time_cnt[4] == 0){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::yellow);
        ui->timetable->setItem(4, current_day, item);
        time_cnt[4] = 1;
    }
    else if(time_cnt[4] == 1){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::white);
        ui->timetable->setItem(4, current_day, item);
        time_cnt[4] = 0;
    }
}

void schedule::on_sixth_time_clicked()
{
    time_save_func();
    if(time_cnt[5] == 0){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::yellow);
        ui->timetable->setItem(5, current_day, item);
        time_cnt[5] = 1;
    }
    else if(time_cnt[5] == 1){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::white);
        ui->timetable->setItem(5, current_day, item);
        time_cnt[5] = 0;
    }
}

void schedule::on_no_time_clicked()
{
    time_save_func();
    for(int i = 0 ; i < 7 ; i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::white);
        ui->timetable->setItem(i, current_day, item);
    }
    ui->first_time->setChecked(false);
    ui->second_time->setChecked(false);
    ui->third_time->setChecked(false);
    ui->fourth_time->setChecked(false);
    ui->fifth_time->setChecked(false);
    ui->sixth_time->setChecked(false);

}

void schedule::on_load_list_clicked()
{
    if(load_cnt == 0){
        load_robit();
        load_new();
        load_cnt ++;
    }
    else{
        QMessageBox::critical(this, "WARNING", "이미 값을 불러왔습니다.");
    }
}

void schedule::on_robit_set_btn_clicked()
{
    fill_robit_timetable();
    setui_info_ro();
}

void schedule::on_new_set_btn_clicked()
{
    fill_new_timetable();
    setui_info();
}


void schedule::on_merge_btn_clicked()
{
    merge_timetable();
}

