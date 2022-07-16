#ifndef ALGORITHMCOMBOBOX_H
#define ALGORITHMCOMBOBOX_H

#include <QComboBox>

class AlgorithmComboBox : public QComboBox {
    Q_OBJECT

public:
    void showPopup() override;
};

#endif // ALGORITHMCOMBOBOX_H
