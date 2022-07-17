#ifndef WEIGHTTEXT_H
#define WEIGHTTEXT_H

#include <QGraphicsTextItem>
#include <QTextCursor>

class WeightText : public QGraphicsTextItem {
public:
    WeightText(QGraphicsItem *parent = nullptr);
    void setWeight(int weight);
    int getWeight();

private:
    QTextCursor cursor;
    QTextDocument *weightDocument;

    void setWeightFromText();
    int weight;
};

#endif // WEIGHTTEXT_H
