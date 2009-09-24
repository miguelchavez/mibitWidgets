#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtGui/QWidget>
class MibitTip;
class MibitDialog;

namespace Ui
{
    class mainView;
}

class mainView : public QWidget
{
    Q_OBJECT

public:
    mainView(QWidget *parent = 0);
    ~mainView();

private:
    Ui::mainView *ui;
    MibitTip *tip1;
    MibitTip *tip2;
    MibitTip *tip3;
    MibitDialog *dialog1;
    MibitDialog *dialog2;
private slots:
    void showTip1();
    void showTip2();
    void showTip3();
    void showDialog1();
    void showDialog2();
};

#endif // MAINVIEW_H
