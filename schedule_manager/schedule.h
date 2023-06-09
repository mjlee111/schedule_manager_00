#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QMessageBox>
#include <QString>

#include <iostream>
#include <fstream>

#include "struct.h"
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui { class schedule; }
QT_END_NAMESPACE

class schedule : public QWidget
{
    Q_OBJECT

public:
    schedule(QWidget *parent = nullptr);
    ~schedule();

    // variables
    int cnt = 0;
    int cnt_robit = 0;
    int load_cnt = 0;

    int timetable_save[28][5][7];
    int current_num = 0;
    int current_day = 0;

    int time_cnt[7] = {0, };
    std::string robit_name[7];
    std::string new_name[28];

    std::vector<std::string> options;
    QStringList optionlist;

    std::vector<std::string> options_2;
    QStringList optionlist_2;

    int num;
    std::string text[5];
    int timetable[30];
    int location;
    int want_time[3];
    std::string question;

    // functions
    bool check_stat(void);
    void time_save_func(void);
    void whole_save_func(void);
    void text_clear_func(void);
    void save_file_reader(void);
    void load_robit(void);
    void load_new(void);
    void fill_robit_timetable(void);
    void fill_new_timetable(void);
    void merge_timetable(void);
    void setui_info(void);
    void setui_info_ro(void);

private slots:
    void on_save_btn_clicked();
    void on_day_list_currentIndexChanged(int index);
    void on_first_time_clicked();
    void on_second_time_clicked();
    void on_third_time_clicked();
    void on_fourth_time_clicked();
    void on_fifth_time_clicked();
    void on_sixth_time_clicked();
    void on_no_time_clicked();
    void on_load_btn_clicked();
    void on_time_btn_clicked();
    void on_load_list_clicked();
    void on_robit_set_btn_clicked();
    void on_new_set_btn_clicked();
    void on_merge_btn_clicked();

private:
    Ui::schedule *ui;


};
#endif // SCHEDULE_H
