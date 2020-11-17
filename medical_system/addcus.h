#ifndef ADDCUS_H
#define ADDCUS_H

#include <QDialog>

namespace Ui {
class addcus;
}

class addcus : public QDialog
{
    Q_OBJECT

public:
    explicit addcus(QWidget *parent = nullptr);
    ~addcus();

private slots:
    void on_text_zhengzhuang_textChanged();

    void on_text_address_textChanged();

    void on_text_mark_textChanged();

    void on_pb_cancel_clicked();

    void on_pb_ok_clicked();

    void on_le_danhao_editingFinished();

    void on_le_num_editingFinished();

private:
    Ui::addcus *ui;
};

#endif // ADDCUS_H
