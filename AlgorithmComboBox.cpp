#include "AlgorithmComboBox.h"

void AlgorithmComboBox::showPopup()
{
    QComboBox::showPopup();
    QWidget *popup = this->findChild<QFrame*>();
    popup->move(popup->x(), popup->y() + this->currentIndex() * this->height());
}
