#ifndef MASTARVIEW_H
#define MASTARVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MastarView;
}
QT_END_NAMESPACE

class MastarView : public QWidget
{
    Q_OBJECT

public:
    MastarView(QWidget *parent = nullptr);
    ~MastarView();

private:
    Ui::MastarView *ui;
};
#endif // MASTARVIEW_H
