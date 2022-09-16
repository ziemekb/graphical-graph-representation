#ifndef WEIGHTTEXT_H
#define WEIGHTTEXT_H

#include <QGraphicsTextItem>
#include <QTextCursor>

class WeightText : public QGraphicsTextItem {
    Q_OBJECT
public:
    WeightText(QGraphicsItem *parent = nullptr);
    void setWeight(int weight);

private:
    QTextCursor cursor;
    QTextDocument *weightDocument;

    void setWeightFromText();
    int weight;

protected:
    bool sceneEvent(QEvent *event) override;

signals:
    void weightChange(int weight);
};

#endif // WEIGHTTEXT_H
