#include <QTextDocument>
#include <QTextCharFormat>
#include <QKeyEvent>
#include "WeightText.h"

WeightText::WeightText(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    this->weight = 1;
    weightDocument = new QTextDocument;

    QTextCharFormat charFormat;
    QFont font("Monospace", 12);
    font.setBold(true);
    charFormat.setFont(font);

    QPen outlinePen = QPen (QColor(255, 255, 255), 0.75, Qt::SolidLine);
    charFormat.setTextOutline(outlinePen);

    cursor = QTextCursor(weightDocument);
    cursor.setCharFormat(charFormat);
    cursor.insertText(QString::number(weight));

    this->setDocument(weightDocument);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);

    connect(this->document(), &QTextDocument::contentsChanged, this, &WeightText::setWeightFromText);
}

void WeightText::setWeight(int weight)
{
    this->weight = weight;
    emit weightChange(weight);
}

void WeightText::setWeightFromText()
{
    bool ok;

    int tempWeight = this->toPlainText().QString::toInt(&ok);

    if(ok) {
        setWeight(tempWeight);
    }
    else {
        this->setPlainText(QString::number(this->weight));
    }
}

bool WeightText::sceneEvent(QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);

        switch (keyEvent->key()) {
        case Qt::Key_Space:
        case Qt::Key_Tab:
        case Qt::Key_Return:
            return true;
            break;
        default:
            break;
        }
    }
    return QGraphicsTextItem::sceneEvent(event);
}
