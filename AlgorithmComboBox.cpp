#include "AlgorithmComboBox.h"

AlgorithmComboBox::AlgorithmComboBox()
{
    foreach(Algorithm alg, algorithms) {
        this->addItem(alg.name, alg.type);
    }
}

void AlgorithmComboBox::showPopup()
{
    QComboBox::showPopup();
    QWidget *popup = this->findChild<QFrame*>();
    popup->move(popup->x(), popup->y() + this->currentIndex() * this->height());
}
