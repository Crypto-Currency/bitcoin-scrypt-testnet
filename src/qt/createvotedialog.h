#ifndef CREATEVOTEDIALOG_H
#define CREATEVOTEDIALOG_H

#include <QDialog>

namespace Ui {
    class CreateVoteDialog;
}
class ClientModel;

/** "CreateVote" dialog box */
class CreateVoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateVoteDialog(QWidget *parent = 0);
    ~CreateVoteDialog();

    void setModel(ClientModel *model);
private:
    Ui::CreateVoteDialog *ui;

private slots:
    void on_SendButton_clicked();
    void on_ClearButton_clicked();
    void on_CancelButton_clicked();
    void on_RefreshButton_clicked();
};

#endif // CREATEVOTEDIALOG_H
