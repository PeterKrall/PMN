#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "configuration.h"
#include "network.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_exit_clicked()
{
    close();
}
#define use_gui
void MainWindow::on_bt_go_clicked()
{
    pnm::Configuration configuration
        (
#ifdef use_gui
          ui->ed_output_directory->text().toStdString().c_str() // std::string output_directory
        , ui->ed_outputfile_name->text().toStdString().c_str()  // std::string run_label
        , get_int(ui->ed_eternity)                              // int eternity
        , get_double(ui->ed_xchng_initial_a)                    // long double replacement_initial_a
        , get_double(ui->ed_xchng_final_a)                      // long double replacement_final_a
        , get_int(ui->ed_num_contacts_a)                        // int number_of_contact_events_per_day
        , get_int(ui->ed_ti_s0)                                 // int pre_active_state_duration_1
        , get_int(ui->ed_ti_s1)                                 // int pre_active_state_duration_2
        , get_int(ui->ed_ta_s0)                                 // int active_state_duration_1
        , get_int(ui->ed_ta_s1)                                 // int active_state_duration_2
        , get_double(ui->ed_p_trans_a_s0)                       // long double transmission_probability_1_a
        , get_double(ui->ed_p_trans_a_s1)                       // long double transmission_probability_2_a
        , get_int(ui->ed_transition_start)                      // int days_before_switch
        , get_int(ui->ed_num_contacts_b)                        // int number_of_contact_events_per_day_b
        , get_double(ui->ed_xchng_initial_b)                    // long double replacement_initial_b
        , get_double(ui->ed_xchng_final_b)                      // long double replacement_final_b
        , get_double(ui->ed_p_trans_b_s0)                       // long double transmission_probability_1_b
        , get_double(ui->ed_p_trans_b_s1)                       // long double transmission_probability_2_b
        , get_double(ui->ed_p_trans_x_s0)                       // long double additional_active_state_factor = 0
        , get_int(ui->ed_transition_period)                     // int transformation_period = 0
#else
          std::string("./../../data")
        , std::string("out_test")
#endif
#ifdef s1
        , 600
        , (0.025*1.0)
        , (0.025*0.0)
        , 20
        , 3
        , 0
        , 4
        , 0
        , 0.03
        , 0.045
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef s2
        , 600
        , (0.03*1.0)
        , (0.03*0.0)
        , 20
        , 2
        , 2
        , 3
        , 0
        , 0.03
        , 0.045
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef s3
        , 600
        , (0.06*1.0)
        , (0.06*0.0)
        , 20
        , 3
        , 3
        , 4
        , 0
        , 0.12
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef s4
        , 600
        , (0.12*1.0)
        , (0.12*0.0)
        , 20
        , 3
        , 3
        , 4
        , 0
        , 0.03
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef s3dec_p_initial
        , 600
        , (0.06*1.0)
        , (0.06*0.0)
        , 20
        , 3
        , 3
        , 4
        , 0
        , 0.12
        , 0
        , 200
        , 20
        , (0.06*0.3)
        , (0.06*0.7)
        , 0.12
        , 0
        , 0
        , 50
#endif
#ifdef s3dec_nc
        , 600
        , (0.06*1.0)
        , (0.06*0.0)
        , 20
        , 3
        , 3
        , 4
        , 0
        , 0.12
        , 0
        , 200
        , 4
        , (0.06*1.0)
        , (0.06*0.0)
        , 0.12
        , 0
        , 0
        , 50
#endif
#ifdef r1_s2_up
        , 600
        , (0.03*1.0)
        , (0.03*0.0)
        , 20
        , 2
        , 2
        , 3
        , 3
        , 0.03
        , 0.045
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef r2_up
        , 600
        , (0.1*1.0)
        , (0.1*0.0)
        , 20
        , 2
        , 2
        , 3
        , 3
        , 0.03
        , 0.045
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef r2_down_early
        , 600
        , (0.2*1.0)
        , (0.2*0.0)
        , 40
        , 4
        , 2
        , 2
        , 2
        , 0.125
        , 0.1
        , 0
        , 0
        , 0
        , 0

#endif
#ifdef period
        , 10000
        , (0.1*1.0)
        , (0.2*0.0)
        , 2
        , 1
        , 0
        , 1
        , 0
        , 0.65
        , 0.1
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef period_2
        , 1000 * 1000 * 10
        , (0.1*1.0)
        , (0.2*0.0)
        , 3
        , 2
        , 0
        , 1
        , 0
        , 0.5
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
        , 1 / pow(7,4)
#endif
#ifdef s7
        , 200
        , (0.2*1.0)
        , (0.2*0.0)
        , 40
        , 4
        , 2
        , 2
        , 0
        , 0.125
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
        , 0
#endif
#ifdef s3dec_nc_slow
        , 600
        , (0.06*1.0)
        , (0.06*0.0)
        , 20
        , 3
        , 3
        , 4
        , 0
        , 0.12
        , 0
        , 200
        , 4
        , (0.06*1.0)
        , (0.06*0.0)
        , 0.12
        , 0
        , 0
        , 30
#endif
#ifdef s3dec_p_initial_slow
        , 600
        , (0.06*1.0)
        , (0.06*0.0)
        , 20
        , 3
        , 3
        , 4
        , 0
        , 0.12
        , 0
        , 200
        , 20
        , (0.06*0.3)
        , (0.06*0.7)
        , 0.12
        , 0
        , 0
        , 30
#endif
    // 0.0468928

#ifdef dec_nc1
        , 10000
        , (0.025*1.0)
        , (0.06*0.0)
        , 100
        , 10
        , 0
        , 2
        , 0
        , 0.67
        , 0.0
        , 200 * 0
        , 1
        , (0.025*1.0)
        , (0.06*0.0)
        , 0.67
        , 0
        , 0
        , 30
#endif // 0.024946 | +
#ifdef dec_nc2 // 0.024948 |
        , 10000
        , (0.025*1.0)
        , (0.06*0.0)
        , 100
        , 1
        , 0
        , 100
        , 0
        , 0.0286
        , 0.0
        , 200
        , 1
        , (0.025*1.0)
        , (0.06*0.0)
        , 0.0286
        , 0
        , 0
        , 30
#endif
        );
    pnm::Network::run(configuration);
}

double MainWindow::get_double(QLineEdit* edit)
{
    return edit->text().trimmed().toDouble();
}
int MainWindow::get_int(QLineEdit* edit)
{
    return edit->text().trimmed().toInt();
}

void MainWindow::on_bt_select_output_directory_clicked()
{
    QString dir = QFileDialog::getExistingDirectory (
                                                      this
                                                    , tr("Output directory")
                                                    , ui->ed_output_directory->text()
                                                    , QFileDialog::ShowDirsOnly
                                                    );
    ui->ed_output_directory->setText(dir);
}
